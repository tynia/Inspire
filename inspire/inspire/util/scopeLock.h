#ifndef _INSPIRE_UTIL_LOCK_H_
#define _INSPIRE_UTIL_LOCK_H_

#include "inspire.h"
#include "mutex.h"

namespace inspire {

   class insMutex;

   class scopeLock
   {
   public:
      scopeLock(insMutex* mtx) : _mutex(mtx)
      {
         INSPIRE_ASSERT(NULL != mtx, "mutex cannot be NULL");
         _mutex->lock();
      }

      ~scopeLock()
      {
         _mutex->unlock();
      }

   private:
      insMutex* _mutex;
   };
}
#endif