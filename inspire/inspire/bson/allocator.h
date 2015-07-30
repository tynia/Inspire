#ifndef _INSPIRE_BSON_MEMORY_ALLOCATOR_H_
#define _INSPIRE_BSON_MEMORY_ALLOCATOR_H_

#include "inspire.h"

namespace inspire {

   namespace bson {

      class Allocator : public noncopyable
      {
      public:
         static Allocator* instance();

         char* alloc(const unsigned int size);
         void dealloc(const char* ptr);

      protected:
         Allocator();
         virtual ~Allocator();

      private:
         bool _check(const char* ptr);

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
