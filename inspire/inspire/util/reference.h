#ifndef _INSPIRE_UTIL_REFERENCE_H_
#define _INSPIRE_UTIL_REFERENCE_H_

#include "refCounter.h"

namespace inspire {

   class IReference
   {
   protected:
      IReference() : _refCounter(NULL) {}
      IReference(IReference& rhs) : _refCounter(rhs._refCounter)
      { _refCounter->_inc(); }

      virtual ~IReference()
      {
         _refCounter->_dec();
      }

   public:
      bool shared() const { return 0 != _refCounter->get(); }
   protected:
      refCounter* _refCounter;
   };
}
#endif
