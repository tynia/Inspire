#ifndef _INSPIRE_UTIL_OSS_HELPER_H_
#define _INSPIRE_UTIL_OSS_HELPER_H_

#include "ossFile.h"

namespace inspire {

   bool ossAccess( const char* path, int flags = 0 );

   const int seekAndRead( ossFile& file, const int64 offset, const int toRead, const char* buffer, const int bufferLen);

   const int seekAndWrite(ossFile& file, const int64 offset, const int toWrite, const char* buffer, const int bufferLen);
}
#endif