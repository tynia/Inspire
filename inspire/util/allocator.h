#ifndef _INSPIRE_UTIL_ALLOCATOR_H_
#define _INSPIRE_UTIL_ALLOCATOR_H_

#include "inspire.h"
#include "noncopyable.h"

namespace inspire {

   class allocator// public noncopyable
   {
      static const uint64 magic = 0xFFFFFFFFFFFAFBFE;
   public:
      virtual char* alloc(const uint size);
      virtual void dealloc(const char* ptr);
      virtual void pray();

   protected:
      allocator();
      virtual ~allocator();

   private:
      bool _checkSanity(const char* ptr);
      void _setSanity(void* ptr, const unsigned size);
      void _resetRest();

      struct header
      {
         char eyecatcher[8]; // inspire + '\0'                       8 bytes
         uint64 magic;       // magic number                         8 bytes
         uint version;       // version of inspire library           4 bytes
         uint tSize;         // total size, header included          4 bytes
         uint size;          // buffer size, header is not included  4 bytes
         uint used;          // times of assigned to use             4 bytes
         header* next;       // next buffer header                 4/8 bytes
         char padding[512 - 8 - 8 - 4 - 4 - 4 - 4 - sizeof(void*)];
      };
      header _hdr;
   };
}
#endif
