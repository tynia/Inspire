#include "allocator.h"

namespace inspire {

   namespace bson {

      Allocator::Allocator() : _hdr(NULL)
      {
         _hdr = new header();
         _hdr->next = NULL;
         _hdr->size = 0;
      }

      Allocator::~Allocator()
      {
         while (NULL != _hdr)
         {
            header* ptr = _hdr->next;
            _hdr = ptr->next;
            ::free((void*)ptr);
         }
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

         header* hdr = _hdr;
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

         ::memset(ptr, 0x00, sizeof(header));
         hdr = (header*)ptr;
         hdr->size = size;
         hdr->next = 0;
         ++hdr->used;
         ::memset(hdr->eyecatcher, "inspire", 8);
         ::memset(hdr->padding, 0xfe, 8);

         return (ptr + sizeof(header));
      }

      void Allocator::dealloc(const char* ptr)
      {
         //
         // mutex lock
         bool ok = _check(ptr);
         if (!ok)
         {
            LogError("ptr:0x%x checked failed, it may not be a buffer "
                     "allocated by allocator", (unsigned long long*)ptr);
            ::free(ptr);
            return;
         }

         header* hdr = (header*)(ptr - sizeof(header));
         ::memset(ptr, 0xfe, hdr->size);
         hdr->next = _hdr->next;
         _hdr->next = hdr;
      }

      bool Allocator::_check(const char* ptr)
      {
         header* hdr = (header*)(ptr - sizeof(header));
         bool eq1 = ::memcmp(hdr->eyecatcher, "inspire", 8);
         bool eq2 = ::memcmp(hdr->padding, 0xfe, 8);

         return !(eq1 & eq2);
      }
   }
}
