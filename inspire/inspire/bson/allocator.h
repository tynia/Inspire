#ifndef _INSPIRE_BSON_MEMORY_ALLOCATOR_H_
#define _INSPIRE_BSON_MEMORY_ALLOCATOR_H_

#include "inspire.h"

namespace inspire {

   namespace bson {

      class Allocator : public noncopyable
      {
      public:
         Allocator();
         virtual ~Allocator();

         char* alloc(const unsigned int size);
         void dealloc(const char* ptr);

      protected:
         char* _align(char* origin);
         void* _addMemory(const size_t size);

      private:
         struct header
         {
            unsigned int size;
            header* next;
         };
         header* _hdr;
      };

   }
}
#endif