#ifndef _INSPIRE_UTIL_H_
#define _INSPIRE_UTIL_H_

namespace inspire {

   inline void Panic()
   {
#ifdef _DEBUG
      __asm int 3;
#else
      int *p = NULL;
      *p = 1;
#endif
   }

   namespace util {

      inline const uint roundUp(const uint original, const uint bytes = 4)
      {
         return ((original+(bytes-1)) - ((original+(bytes-1))%bytes));
      }

      inline const uint roundDown(const uint original, const uint bytes = 4)
      {
         return (original/bytes) * bytes;
      }
   }
}
#endif