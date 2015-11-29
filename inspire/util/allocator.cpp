#include "allocator.h"
#include "util.h"
#include "logger\logger.h"

namespace inspire {

   allocator::allocator()
   {
      _setSanity((void*)&_hdr, 0);
   }

   allocator::~allocator()
   {
      _resetRest();
   }

   char* allocator::alloc(const uint size, const char* file, const int line)
   {
      //
      // mutex lock
      uint locate = _locate(size);
      header* hdr = &_alloc[locate].hdr;
      while (NULL != hdr->next)
      {
         header* toReturn = hdr->next;
         if (NULL != toReturn)
         {
            hdr->next = toReturn->next;
            toReturn->next = NULL;
            return ((char*)toReturn) + sizeof(header);
         }
         else
         {
            hdr = hdr->next;
         }
      }

      char* ptr = (char*)::malloc(size + sizeof(header));
      if (NULL == ptr)
      {
         LogError("Failed to alloc memory, size = d%", size + sizeof(header));
         return NULL;
      }

      _setSanity(ptr, file, line);
      ::memset(ptr + sizeof(header), 0, size);
      return (ptr + sizeof(header));
   }

   void allocator::dealloc(const char* ptr)
   {
      //
      // mutex lock
      bool ok = _checkSanity(ptr);
      if (!ok)
      {
         LogError("pointer: 0x%x sanity checked failed, it may not be "
                  "allocated by allocator", (uint64*)ptr);
         //::free(ptr);
#ifdef _DEBUG
         Panic();
#endif
         return;
      }

      header* hdr = (header*)(ptr - sizeof(header));
      ::memset((void*)ptr, 0xfe, hdr->size);
      hdr->next = _hdr.next;
      _hdr.next = hdr;
   }

   void allocator::pray()
   {
      _resetRest();
   }

   bool allocator::_checkSanity(const char* ptr)
   {
      header* hdr = (header*)(ptr - sizeof(header));
      bool eq1 = (0 == ::memcmp(hdr->eyecatcher, "inspire", 8));
      bool eq2 = (magic == hdr->magic);
      return !(eq1 && eq2);
   }

   void allocator::_setSanity(void* ptr, const char* file, const int line)
   {
      ::memset(ptr, 0x0, sizeof(header));
      header* hdr = (header*)ptr;
      ::memmove(hdr->eyecatcher, "inspire", 7);
      hdr->magic = magic;
      hdr->next = NULL;
   }

   void allocator::_resetRest()
   {
      while (NULL != _hdr.next)
      {
         header* ptr = _hdr.next;
         _hdr.next = ptr->next;
         ::free((void*)ptr);
      }
   }
}
