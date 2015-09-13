#ifndef _INSPIRE_MEMORY_ALLOCATOR_H_
#define _INSPIRE_MEMORY_ALLOCATOR_H_

#include "inspire.h"

namespace inspire {

   static const unsigned debug = 0xFFFAFBFE;

   class IAllocator
   {
   public:
      virtual ~IAllocator() {}

      virtual char* alloc(const uint size) = 0;

      virtual void dealloc(const void* ptr) = 0;

      virtual void pray() = 0;
   };

   class allocator : public IAllocator, public noncopyable
   {
   public:
      static allocator* instance();

      virtual char* alloc(const uint size);
      virtual void dealloc(const void* ptr);
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
         char eyecatcher[8];
         uint used;
         uint size;
         header* next;
#ifdef _DEBUG
         unsigned debug;
#endif
      };
      header _hdr;
   };
}
#endif
