#ifndef _INSPIRE_BSON_MEMORY_ALLOCATOR_H_
#define _INSPIRE_BSON_MEMORY_ALLOCATOR_H_

#include "inspire.h"

namespace inspire {

   namespace bson {

      static const unsigned debug = 0xFFFAFBFE;

      class Allocator : public noncopyable
      {
      public:
         static Allocator* instance();

         char* alloc(const unsigned int size);
         void dealloc(const char* ptr);
         void pray();

      protected:
         Allocator();
         virtual ~Allocator();

      private:
         bool _checkSanity(const char* ptr);
         void _setSanity(void* ptr, const unsigned size);
         void _resetRest();

         struct header
         {
            char eyecatcher[8];
            unsigned used;
            unsigned size;
            header* next;
#ifdef _DEBUG
            unsigned debug;
#endif
         };
         header _hdr;
      };
   }
}
#endif
