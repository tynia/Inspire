#ifndef _INSPIRE_BSON_UTIL_H_
#define _INSPIRE_BSON_UTIL_H_

namespace inspire {

   namespace util {

      inline const unsigned int roundUp(const unsigned int original,
                                        const unsigned int bytes = 4)
      {
         return ((original+(bytes-1)) - ((original+(bytes-1))%bytes));
      }

      inline const unsigned int roundDown(const unsigned int original,
                                          const unsigned int bytes = 4)
      {
         return (original/bytes) * bytes;
      }
   }

   inline void Panic()
   {
#ifdef _DEBUG
      __asm int 3;
#else
      int *p = NULL;
      *p = 1;
#endif
   }
}
#endif