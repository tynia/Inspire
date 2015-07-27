#include "allocator.h"
#include "insLog.h"

namespace inspire {

   allocator::allocator()
   {}

   allocator::~allocator()
   {}

   char* allocator::_align(char* ptr)
   {
      unsigned int offset = ((szAlignment - (size_t(ptr) & (szAlignment - 1))) & (szAlignment - 1));
      return ptr + offset;
   }
   
   void* allocator::alloc(const unsigned int size)
   {
      char* ptr = NULL;
      if ((_ptrEnd - _ptrCurrent < szAlignment) || (ptr + size > _ptrEnd))
      {
         size_t toAlloc = 0;
         if (size > szBlock)
         {
            toAlloc = ((size/szBlock) + 1)*szBlock;
         }

         char* newAddr = (char*)_addMemory(toAlloc);
         if (NULL == newAddr)
         {
            LogError("Failed to add memory to pool");
         }

         char* begin = _align(newAddr);
         header* hd = reinterpret_cast<header*>(begin);
         hd->_hdBlock = _ptrBegin;
         _ptrBegin = newAddr;
         _ptrCurrent = begin + sizeof(header);
         _ptrEnd = newAddr + toAlloc;

         ptr = _align(_ptrCurrent);
      }
      else
      {
         ptr = _align(_ptrCurrent);
      }

      _ptrCurrent = ptr + size;
      return ptr;
   }

   void* allocator::_addMemory( const size_t size )
   {
      void* ptr = new char[size];
      if(NULL == ptr)
      {
         LogError("Failed to alloc memory for pool, out of memory");
         Panic();
      }
      return ptr;
   }

}