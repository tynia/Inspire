#include "allocator.h"

namespace inspire {

   namespace bson {

      inspire::allocator _allocator;

      inspire::allocator* GetAllocator()
      {
         return &_allocator;
      }
   }
}