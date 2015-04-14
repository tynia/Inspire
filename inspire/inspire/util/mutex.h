#ifndef _INSPIRE_UTIL_MUTEX_H_
#define _INSPIRE_UTIL_MUTEX_H_

#include "inspire.h"

namespace inspire {

   enum RWType
   {
      SHARED,
      EXCLUSIVE,
   };

   class mutex
   {
   public:
      mutex();
      ~mutex();

      void lock();
      void unlock();
      bool tryLock();

   private:
#ifdef _WIN32
      CRITICAL_SECTION _cs;
#else
      pthread_mutex_t _mtx;
#endif
   };

}
#endif