#ifndef _INSPIRE_UTIL_REF_COUNTER_H_
#define _INSPIRE_UTIL_REF_COUNTER_H_

#include "inspire.h"

namespace inspire {

   class refCounter
   {
   public:
      refCounter() : _referCount(0) {}

      refCounter(const refCounter& rhs) : _referCount(rhs._referCount) {}

      refCounter& operator= (const refCounter& rhs)
      {
         _referCount = rhs._referCount;
      }

      const uint retain() const
      {
         return _referCount;
      }

      ~refCounter()
      {}

      void _inc()
      {
         ++_referCount;
      }

      void _dec()
      {
         --_referCount;
      }

   private:
      volatile uint _referCount;
   };
}
#endif
