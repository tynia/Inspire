#include "allocator.h"

namespace inspire {

   namespace bson {

      static inspire::allocator _allocator;

      inspire::allocator* memMgr()
      {
         return &_allocator;
      }
   }
}