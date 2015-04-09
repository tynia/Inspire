#ifndef _INSPIRE_INSPIRE_MUTEX_H_
#define _INSPIRE_INSPIRE_MUTEX_H_

#include "inspire.h"

namespace inspire {

   enum RWType
   {
      SHARED,
      EXCLUSIVE,
   };

   class ossMutex
   {
   public:
      ossMutex();
      ~ossMutex();

      void lock();
      void unlock();

   private:
      CRITICAL_SECTION cs;
   };
}
#endif