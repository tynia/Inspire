#include "ossFile.h"
#include "assert.h"
#include "string_t.h"
#include "system.h"

namespace inspire {

#ifdef _WIN32
   ossFile::ossFile() : _handle(NULL)
#else
   ossFile::ossFile() : _fd(-1)
#endif
   {
      memset(_filename, 0, MAX_LOG_FILE_NAME + 1);
   }

   ossFile::~ossFile()
   {
      close();
   }

   bool ossFile::isOpened() const
   {
#ifdef _WIN32
      return INVALID_HANDLE_VALUE != _handle;
#else
      return (0 != _fd) && (-1 != _fd);
#endif
   }

   bool ossFile::openFile(const char* filename, const int mode, const int permission)
   {
      memcpy(_filename, filename, MAX_LOG_FILE_NAME);
      int iPermission = _matchPermission(permission);
#ifdef _WIN32
      inspire_string_t fname(_filename);
      int crMode = 0;
      int rwMode = 0;
      int sharedMode = 0;
      int attri = 0;
      _matchMode(mode, crMode, rwMode, sharedMode, attri);
      _handle = ::CreateFile(fname.toString(), rwMode, sharedMode, NULL, crMode, attri, NULL );
      if (INVALID_HANDLE_VALUE == _handle)
      {
         unsigned int err = (unsigned int)GetLastError();
         if (ERROR_SHARING_VIOLATION == err)
         {
            LogError("Failed to open file, filename = %s, no permission", _filename);
         }
         else
         {
            LogError("Failed to open file, filename = %s, io exception", _filename);
         }
         return false;
      }
#else
      int iMode = _matchMode(mode);
      _fd = open(_filename, iMode, iPermission);
      if (-1 == _fd)
      {
         unsigned int err = errno;
         if (EINVAL == err)
         {
            LogError("Failed to open file, filename = %s, direct io exist", _filename);
         }
         else if (ETXTBSY == err)
         {
            LogError("Failed to open file, filename = %s, system busy", _filename);
         }
         else if (ENOENT == err)
         {
            LogError("Failed to open file, filename = %s, file not exist", _filename);
         }
         else if (EEXIST == err)
         {
            LogError("Failed to open file, filename = %s, file existed", _filename);
         }
         else if (EACCES == err)
         {
            LogError("Failed to open file, filename = %s, no permission", _filename);
         }
         else
         {
            LogError("Failed to open file, filename = %s, io exception", _filename);
         }
         return false;
      }
      return true;
#endif
   }

   const int ossFile::read(char* buffer, const int bufferLen, const int toRead)
   {
      INSPIRE_ASSERT(buffer, "buffer cannot be NULL");
      return 0;
   }

   const int ossFile::write(char* buffer, const int bufferLen, const int toWrite)
   {
      return 0;
   }

   void ossFile::close()
   {
#ifdef _WIN32
      if (INVALID_HANDLE_VALUE == _handle)
      {
         ::CloseHandle(_handle);
         _handle = INVALID_HANDLE_VALUE;
      }
#else
     if (isOpened())
     {
        ::close(_fd);
        _fd = 0;
     }
#endif
   }

   void ossFile::seek(const size_t offset)
   {

   }

   const int ossFile::seekAndRead(const size_t offset, const int toRead, const char* buffer, const int bufferLen)
   {
      return 0;
   }

   const int ossFile::seekAndWrite(const size_t offset, const int toWrite, const char* buffer, const int bufferLen)
   {
      return 0;
   }

   void ossFile::_reset()
   {

   }

#ifdef _WIN32
   void ossFile::_matchMode( const int mode, int& crMode, int& rwMode, int& sharedMode, int& attri)
   {
      // create/open mode
      switch (mode & MODE_CREATE)
      {
      case MODE_DEFAULT:
         crMode = OPEN_EXISTING;
         break;
      case MODE_CREATEONLY:
         crMode = CREATE_NEW;
         break;
      case MODE_REPLACE:
         crMode = CREATE_ALWAYS;
         break;
      case MODE_CREATE:
         crMode = OPEN_ALWAYS;
         break;
      }

      // read/write access
      switch (mode & ACCESS_READWRITE)
      {
      case ACCESS_WRITEONLY:
         if (mode & SHAREDREAD)
         {
            rwMode = GENERIC_READ | GENERIC_WRITE;
         }
         else
         {
            rwMode = GENERIC_WRITE;
         }
         break;
      case ACCESS_READONLY:
         if ((mode | SHAREDREAD) == EXCLUSIVE )
         {
            rwMode = GENERIC_READ | GENERIC_WRITE;
         }
         else
         {
            rwMode = GENERIC_READ;
         }
         break;
      case ACCESS_READWRITE:
         rwMode = GENERIC_READ | GENERIC_WRITE;
         break;
      }

      // shared mode
      switch (mode | SHAREDWRITE)
      {
      case EXCLUSIVE:
         sharedMode = 0;
         break;
      case SHAREDREAD:
         if (mode | ACCESS_WRITEONLY)
         {
            sharedMode = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;
         }
         else
         {
            sharedMode = FILE_SHARE_READ ;
         }
         break;
      case SHAREDWRITE:
         sharedMode = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;
         break;
      }

      // I/O
      if (mode & DIRECTIO)
      {
         attri |= FILE_FLAG_NO_BUFFERING;
      }

      if(mode & WRITETHROUGH)
      {
         attri |= FILE_FLAG_WRITE_THROUGH;
      }
   }
#else
   const int ossFile::_matchMode(const int mode)
   {
      int iMode = 0;
      // create/open mode
      switch (mode & MODE_CREATE)
      {
      case MODE_DEFAULT:
         iMode = 0;
         break;
      case MODE_CREATEONLY:
         iMode = O_CREAT | O_EXCL;
         break;
      case MODE_REPLACE:
         iMode = O_CREAT | O_TRUNC;
         break;
      case MODE_CREATE:
         iMode = O_CREAT;
      default:
         break;
      }

      // read/write access
      switch (mode | ACCESS_READWRITE)
      {
      case ACCESS_WRITEONLY:
         if(mode | SHAREDREAD)
         {
            iMode |= O_RDWR;
         }
         else
         {
            iMode |= O_WRONLY;
         }
      case ACCESS_READONLY:
         if ((mode | SHAREDREAD) == EXCLUSIVE)
         {
            iMode |= O_RDWR;
         }
         else
         {
            iMode |= O_RDONLY;
         }
      case ACCESS_READWRITE:
         iMode |= O_RDWR;
         break;
      }

      // I/O
      if (mode | DIRECTIO)
      {
         iMode = O_DIRECT;
      }

      if (mode | WRITETHROUGH)
      {
         iMode |= O_SYNC;
      }

      return iMode;
   }
#endif

   const int ossFile::_matchPermission( const int permission )
   {
      if ( 0 == permission )
      {
         return DEFAULT_FILE_ACCESS;
      }
      return permission;
   }

}