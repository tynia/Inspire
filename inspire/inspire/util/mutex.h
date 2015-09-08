#ifndef _INSPIRE_UTIL_SYNV_MUTEX_H_
#define _INSPIRE_UTIL_SYNV_MUTEX_H_

#include "inspire.h"

namespace inspire {

   class insMutex
   {
   public:
      insMutex();
      ~insMutex();

      void lock();
      void unlock();
      bool tryLock();

   private:
#ifdef _WIN32
      HANDLE  _mutex;
#else
      pthread_mutex_t _mutex;
#endif
   };
}
#endif