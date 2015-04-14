#include "lock.h"
#include "mutex.h"

namespace inspire {

   scopeLock(mutex* mtx) : _mutex(mtx)
   {
      _mutex.lock();
   }

   scopeLock::~scopeLock()
   {
      _mutex->unlock();
      _mutex = NULL;
   }
}