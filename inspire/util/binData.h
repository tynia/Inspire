#ifndef _INSPIRE_UTIL_BIN_DATA_H_
#define _INSPIRE_UTIL_BIN_DATA_H_

#include "inspire.h"
#include "memory/iObject.h"

namespace inspire {

   struct binData : public iObject
   {
      const char* str;
      uint64  len;

      binData(const char* src, const uint64 l) : str(src), len(l) {}
      virtual ~binData() { str = NULL; len = 0; }
   };


}
#endif
