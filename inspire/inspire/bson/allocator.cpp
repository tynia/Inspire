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

      char* Allocator::alloc(const unsigned int size)
      {
         header* hdr = _hdr->next;
         if (NULL != hdr)
         {
            if (hdr->size >= size)
            {
               return (char*)hdr + sizeof(header);
            }
            
         }
      }

   }
}