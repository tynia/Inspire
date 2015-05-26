#ifndef _INSPIRE_UTIL_OSS_FILE_H_
#define _INSPIRE_UTIL_OSS_FILE_H_

#include "platform.h"

namespace inspire {

#define MAX_FILE_NAME_SIZE 255

   enum SEEK_MOD
   {
      INSPIRE_SEEK_SET = 0,
      INSPIRE_SEEK_CUR,
      INSPIRE_SEEK_END,
   };

   enum
   {
      MODE_DEFAULT     = 0,
      MODE_CREATEONLY  = 1 << 0,
      MODE_REPLACE     = 1 << 1,
      MODE_CREATE      = MODE_CREATEONLY | MODE_REPLACE,

      ACCESS_READONLY  = 1 << 2,
      ACCESS_WRITEONLY = 1 << 3,
      ACCESS_READWRITE = ACCESS_READONLY | ACCESS_WRITEONLY
   };

   enum
   {
      EXCLUSIVE    = 0,
      SHAREDREAD   = 1 << 1,
      SHAREDWRITE  = 1 << 5 | SHAREDREAD,
      WRITETHROUGH = 1 << 6,
      DIRECTIO     = 1 << 7,
   };


#ifdef _WIN32
   enum ACCESS_PERMITION
   {
      ACCESS_STICKY = 0,

      U_READ  = 1 << 10,
      U_WRITE = 1 << 9,
      U_EXEC  = 1 << 8,
      U_RWX   = U_READ | U_WRITE | U_EXEC,

      G_READ  = 1 << 6,
      G_WRITE = 1 << 5,
      G_EXEC  = 1 << 4,
      G_RWX   = G_READ | G_WRITE | G_EXEC,

      O_READ  = 1 << 2,
      O_WRITE = 1 << 1,
      O_EXEC  = 1 << 0,
      O_RWX   = O_READ | O_WRITE | O_EXEC,

      DEFAULT_FILE_ACCESS = U_RWX | G_READ | G_EXEC, // rwxr-x---
      DEFAULT_DIR_ACCESS  = U_RWX | G_READ | G_EXEC, // rwxr-x---
   };
#else
   enum ACCESS_PERMITION
   {
      ACCESS_STICKY = S_ISVTX,

      U_READ  = S_IRUSR,
      U_WRITE = S_IWUSR,
      U_EXEC  = S_IXUSR,
      U_RWX   = S_IRWXU,

      G_READ  = S_IRGRP,
      G_WRITE = S_IWGRP,
      G_EXEC  = S_IXGRP,
      G_RWX   = S_IRWXG,

      O_READ  = S_IROTH,
      O_WRITE = S_IWOTH,
      O_EXEC  = S_IXOTH,
      O_RWX   = S_IRWXO,

      DEFAULT_FILE_ACCESS = U_READ | U_WRITE | G_READ, // rw-r-----
      DEFAULT_DIR_ACCESS  = U_RWX | G_READ | G_EXEC,   // rwxr-x---
   };
#endif

   class ossFile
   {
   public:
      ossFile();
      virtual ~ossFile();

   public:
      bool isOpened() const;
      bool openFile(const char* filename, const int mode, const int permission);
      const int read(const char* buffer, const int bufferLen, const int toRead);
      const int write(const char* buffer, const int bufferLen, const int toWrite);
      void close();
      const int64 filesize();
      const char* filename();
      void seek(const int64 offset, SEEK_MOD seek);
      void seekToEnd();

   protected:
#ifdef _WIN32
      void _matchMode(const int mode, int& crMode, int& rwMode, int& sharedMode, int& attri);
#else
      void _matchMode(const int mode, int& iMode);
#endif
      const int _matchPermission(const int permission);

   private:
#ifdef _WIN32
      HANDLE _handle;
#else
      int _fd;
#endif
      char _filename[MAX_FILE_NAME_SIZE + 1];
      // TODO:
      // a lock is needed to thread safe
   };
}
#endif