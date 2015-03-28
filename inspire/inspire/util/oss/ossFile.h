#ifndef _INSPIRE_OSS_FILE_H_
#define _INSPIRE_OSS_FILE_H_

#include "platform.h"

namespace inspire {

#define MAX_LOG_FILE_NAME 255

   class ossFile
   {
   public:
      ossFile();
      ossFile(const char* filename);
      virtual ~ossFile();

   public:
      bool isOpened() const;
      void open(const int mod);
      void openFile(const char* filename);
      void read(char* buffer, const int bufferLen, const int toRead, int& readed);
      void write(char* buffer, const int bufferLen, const int toWrite, int& readed);
      void close();

   private:
#ifdef _WIN32
      HANDLE _handle;
#else
      int _fd;
#endif
      char _filename[MAX_LOG_FILE_NAME + 1];
   };
}
#endif