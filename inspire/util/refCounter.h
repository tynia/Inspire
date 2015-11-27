#ifndef _INSPIRE_UTIL_REF_COUNTER_H_
#define _INSPIRE_UTIL_REF_COUNTER_H_

#include "inspire.h"
#include "atomic.h"

namespace inspire {

   class refCounter
   {
   public:
      refCounter() : _referCount(0) {}

      refCounter(const refCounter& rhs) : _referCount(rhs._referCount) {}

      refCounter operator= (const refCounter& rhs)
      {
         refCounter ref(rhs);
         return ref;
      }

      const int retain() const
      {
         return _referCount;
      }

      ~refCounter()
      {}

      void _inc()
      {
         utilFetchAndAdd32(&_referCount, 1);
      }

      void _dec()
      {
         utilFetchAndAdd32(&_referCount, -1);
      }

   private:
      volatile int _referCount;
   };
}
#endif
