#ifndef _INSPIRE_UTIL_OSS_FILE_H_
#define _INSPIRE_UTIL_OSS_FILE_H_

#include "platform.h"

namespace inspire {

#define MAX_LOG_FILE_NAME 255

   class ossFile
   {
   public:
      ossFile();
      virtual ~ossFile();

   public:
      bool isOpened() const;
      bool openFile(const char* filename, const int mode, const int permission);
      const int read(char* buffer, const int bufferLen, const int toRead);
      const int write(char* buffer, const int bufferLen, const int toWrite);
      void close();

      void seek(const size_t offset);
      const int seekAndRead(const size_t offset, const int toRead, const char* buffer, const int bufferLen);
      const int seekAndWrite(const size_t offset, const int toWrite, const char* buffer, const int bufferLen);

   protected:
      void _reset();
#ifdef _WIN32
      void _matchMode(const int mode, int& crMode, int& rwMode, int& sharedMode, int& attri);
#else
      const int _matchMode(const int mode);
#endif
      const int _matchPermission(const int permission);

   private:
#ifdef _WIN32
      HANDLE _handle;
#else
      int _fd;
#endif
      size_t _roffset;
      size_t _woffset;
      char   _filename[MAX_LOG_FILE_NAME + 1];
   };
}
#endif