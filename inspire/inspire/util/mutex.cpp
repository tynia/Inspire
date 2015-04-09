#include "mutex.h"

namespace inspire {

   ossMutex::ossMutex()
   {
      ::InitializeCriticalSection(&cs);
   }

   ossMutex::~ossMutex()
   {
      ::DeleteCriticalSection(&cs);
   }

   void ossMutex::lock()
   {
      ::EnterCriticalSection(&cs);
   }

   void ossMutex::unlock()
   {
      ::LeaveCriticalSection(&cs);
   }

}