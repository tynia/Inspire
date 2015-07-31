#include "allocator.h"

namespace inspire {

   namespace bson {

      Allocator::Allocator()
      {
         _setSanity((void*)&_hdr, 0);
      }

      Allocator::~Allocator()
      {
         _resetRest();
      }

      Allocator* Allocator::instance()
      {
         static Allocator allocator;
         return &allocator;
      }

      char* Allocator::alloc(const unsigned int size)
      {
         //
         // mutex lock

         header* hdr = &_hdr;
         while (NULL != hdr->next)
         {
            header* toReturn = hdr->next;
            if (toReturn->size >= size)
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

         _setSanity(ptr, size);
         return (ptr + sizeof(header));
      }

      void Allocator::dealloc(const char* ptr)
      {
         //
         // mutex lock
         bool ok = _checkSanity(ptr);
         if (!ok)
         {
            LogError("pointer: 0x%x sanity checked failed, it may not be "
                     "allocated by allocator", (unsigned long long*)ptr);
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

      void Allocator::pray()
      {
         //
         // mutex lock
         _resetRest();
      }

      bool Allocator::_checkSanity(const char* ptr)
      {
         header* hdr = (header*)(ptr - sizeof(header));
         bool eq1 = ::memcmp(hdr->eyecatcher, "inspired", 8);
         bool eq2 = true;
#ifdef _DEBUG
         eq2 = (debug == hdr->debug);
#endif
         return !(eq1 && eq2);
      }

      void Allocator::_setSanity(void* ptr, const unsigned size)
      {
         ::memset(ptr, 0x0, sizeof(header));
         header* hdr = (header*)ptr;
         ::memmove(hdr->eyecatcher, "inspired", 8);
         hdr->used = 0;
         hdr->size = size;
         hdr->next = NULL;
#ifdef _DEBUG
         hdr->debug = debug;
#endif
      }

      void Allocator::_resetRest()
      {
         while (NULL != _hdr.next)
         {
            header* ptr = _hdr.next;
            _hdr.next = ptr->next;
            ::free((void*)ptr);
         }
      }
   }
}
