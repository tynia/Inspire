#ifndef _INSPIRE_UTIL_REFERENCE_H_
#define _INSPIRE_UTIL_REFERENCE_H_

#include "refCounter.h"
#include "assert.h"

namespace inspire {

   class IReference
   {
   protected:
      IReference() : _refCounter(NULL)
      {
         _refCounter = new refCounter();
         INSPIRE_ASSERT(NULL != _refCounter, "Failed to allocate refCounter");
         _refCounter->_inc();
      }

      IReference(IReference& rhs)
      {
         _refCounter->_dec();
         _refCounter = rhs._refCounter;

         _refCounter->_inc();
      }

      virtual ~IReference()
      {
         _refCounter->_dec();
         if (0 == _refCounter->retain())
         {
            delete _refCounter;
            _refCounter = NULL;
         }
      }

   public:
      bool shared() const { return 0 != _refCounter->retain(); }

   protected:
      refCounter* _refCounter;
   };
}
#endif
