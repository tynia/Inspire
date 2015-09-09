#ifndef _INSPIRE_BSON_HEX_H_
#define _INSPIRE_BSON_HEX_H_

#include "util.h"

namespace inspire {

   namespace bson {
      static const char upper[] = "0123456789ABCDEF";
      static const char lower[] = "0123456789abcdef";

      inline int fromHex(const char c)
      {
         if ('0' <= c && '9' >= c)
            return c - '0';
         else if ('a' <= c && 'f' >= c)
            return c - 'a' + 10;
         else if ('A' <= c && 'F' >= c)
            return c - 'A' + 10;
         inspire::Panic();
         return 0xff;
      }

      inline char fromHex(const char* p)
      {
         return (char)((fromHex(*p) << 4) | fromHex(*(p + 1)));
      }

      inline const char* toHex(const void* in, unsigned int len, bool lower = false)
      {
         const char* standard = lower ? lower : upper;
         const char* ptr = reinterpret_cast<const char*>(in);
         for (int i = 0; i < len; ++i)
         {
            char c = *(ptr + len);
            char hi = standard[(c & 0xF0) >> 4];
            char lo = standard[c & 0x0F];
            os << hi << lo;
         }
         return os.c_str();
      }
   }
}
#endif
