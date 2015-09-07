#include "allocator.h"

namespace inspire {

   namespace bson {

      inspire::allocator _allocator;

      inspire::allocator* memMgr()
      {
         return &_allocator;
      }
   }
}