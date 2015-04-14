#ifndef _INSPIRE_UTIL_LOCK_H_
#define _INSPIRE_UTIL_LOCK_H_

#include "mutex.h"

namespace inspire {

   class scopeLock
   {
   public:
      scopeLock(mutex* mtx);
      ~scopeLock();

   private:
      mutex* _mutex;
   };
}
#endif