#ifndef _INSPIRE_UTIL_ALLOCATOR_H_
#define _INSPIRE_UTIL_ALLOCATOR_H_

#include "inspire.h"
#include "noncopyable.h"
#include "mutex.h"

namespace inspire {

   class IAllocator
   {
   public:
      virtual ~IAllocator() {}

      virtual char* alloc(const uint size, const char* fine, const int line)  = 0;
      virtual void  dealloc(const char* ptr) = 0;
      virtual void  reorganize()  = 0;
   };

   class CAllocator : public IAllocator
   {
   public:
      CAllocator() {}
      virtual ~CAllocator() {}

   public:
      virtual char* alloc(const uint size, const char* fine, const int line);
      virtual void  dealloc(const char* ptr);
      virtual void  reorganize();

   private:
      void locate(const uint size)
      {
         int tmp = 0;
         while (size >> 3)
         {
            tmp = size;
         }
      }

   private:
      // 8 16 32 64 128 256 512 1024
      IAllocator* _allocators[8];
   };

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

   private:
      struct header
      {
         char eyecatcher[8]; // inspire + '\0'                       8 bytes
         uint64 magic;       // magic number                         8 bytes
         uint version;       // version of inspire library           4 bytes
         uint tSize;         // total size, header included          4 bytes
         uint size;          // buffer size, header is not included  4 bytes
         uint used;          // times of assigned to use             4 bytes
         header* next;       // next buffer header                 4/8 bytes
         char padding[128 - 8 - 8 - 4 - 4 - 4 - 4 - sizeof(void*)];
      };
      header _hdr;
      mutex_t _mtx;
   };
}
#endif
