#include "lock.h"

namespace inspire {

   scopeLock(ossMutex* mx) : _mutex(mx)
   {
      _mutex.lock();
   }

   scopeLock::~scopeLock()
   {
      _mutex->unlock();
      _mutex = NULL;
   }
}