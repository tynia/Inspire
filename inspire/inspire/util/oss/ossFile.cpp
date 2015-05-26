#include "ossFile.h"
#include "assert.h"
#include "string_t.h"
#include "system.h"

namespace inspire {

#ifdef _WIN32
   ossFile::ossFile() : _handle(NULL)
#else
   ossFile::ossFile() : _fd(0)
#endif
   {
      memset(_filename, 0, MAX_FILE_NAME_SIZE + 1);
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

   const int ossFile::read(const char* buffer, const int bufferLen, const int toRead)
   {
      INSPIRE_ASSERT(buffer, "buffer cannot be NULL");
      INSPIRE_ASSERT(bufferLen >= toRead, "buffer size cannot less than bytes to read");
      int64 totalRead = 0;
#ifdef _WIN32
      bool bSuccess = ::ReadFile(_handle, (LPVOID)buffer, toRead, (LPDWORD)&totalRead, NULL);
      if (!bSuccess)
      {
         LogError("Failed to read file:%s to buffer, error = %d", _filename, ossGetLastError());
         return -1;
      }
#else
      int totalRead = read(_fd, buffer, toRead);
      if (-1 == totalRead)
      {
         LogError("Failed to read file:%s to buffer, error = %d", _filename, ossGetLastError());
         return -1;
      }
#endif
      return (int)totalRead;
   }

   const int ossFile::write(const char* buffer, const int bufferLen, const int toWrite)
   {
      INSPIRE_ASSERT(bufferLen <= toWrite, "buffer size cannot less than bytes to write");
      if (NULL == buffer)
      {
         return 0;
      }
      int64 totalWritten = 0;
#ifdef _WIN32
      bool bSuccess = ::WriteFile(_handle, buffer, toWrite, (LPDWORD)&totalWritten, NULL);
      if (!bSuccess)
      {
         LogError("Failed to write buffer to file, rc = %d", GetLastError());
         return -1;
      }
#else
      int totalWritten = write(_fd, buffer, toWrite);
      if (-1 == totalWritten)
      {
         LogError("Failed to read file:%s to buffer, error = %d", _filename, ossGetLastError());
         return -1;
      }
#endif
      return (int)totalWritten;
   }

   void ossFile::close()
   {
      if (isOpened())
      {
#ifdef _WIN32
         ::CloseHandle(_handle);
         _handle = INVALID_HANDLE_VALUE;
#else
        ::close(_fd);
        _fd = 0;
#endif
      }
   }

   const int64 ossFile::filesize()
   {
      int64 totalSize = 0;
#ifdef _WIN32
      LARGE_INTEGER li;
      if (!GetFileSizeEx(_handle, &li))
      {
         LogError("Filed to get file size, GetFileSizeEx()");
      }
      totalSize = li.QuadPart;
#else
      struct stat sb;
      int rc = 0;
      rc = fstat(_fd, &sb);
      if (-1 == rc)
      {
         LogError("Failed to get file size, fstat(), error: %d", ossGetLastError());
      }
      else
      {
         switch (sb.st_mode & S_IFMT)
         {
         case S_IFLNK:
         case S_IFREG:
            totalSize = sb.st_size;
            break;
         default:
            LogError("Invalid file type, file:%s", _filename);
            break;
         }
      }
#endif
      return totalSize;
   }

   const char* ossFile::filename()
   {
      return _filename;
   }

   void ossFile::seek( const int64 offset, SEEK_MOD whence )
   {
#ifdef _WIN32
      INSPIRE_ASSERT(_handle, "File should be opened first");
      LARGE_INTEGER li;
      li.QuadPart = offset;
      li.LowPart = SetFilePointer( _handle, li.LowPart, &li.HighPart, (DWORD)whence );
      if (INVALID_SET_FILE_POINTER == li.LowPart && NO_ERROR == ossGetLastError())
      {
         LogError("io exception occurred when seek, file:%s", _filename);
      }
#else
      INSPIRE_ASSERT(_fd, "File should be opened first");
      int64 seekoff = 0;
      seekoff = lseek(_fd, offset, whence);
      if (-1 == seekoff)
      {
         LogError("Failed to lseek, file:%s", _filename);
      }
#endif
   }

   void ossFile::seekToEnd()
   {
      seek(0, INSPIRE_SEEK_END);
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
   const int ossFile::_matchMode(const int mode, int& iMode)
   {
      iMode = 0;
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