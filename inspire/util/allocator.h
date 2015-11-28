#ifndef _INSPIRE_UTIL_ALLOCATOR_H_
#define _INSPIRE_UTIL_ALLOCATOR_H_

#include "inspire.h"
#include "noncopyable.h"
#include "mutex.h"

namespace inspire {

   class CAllocator
   {
   public:
      CAllocator() {}
      virtual ~CAllocator() {}

   public:
      char* alloc(const uint size, const char* fine, const int line);
      void  dealloc(const char* ptr);
      void  reorganize();

   private:
      uint locate(const uint size)
      {
         // we need find which allocator should allocate the size
         // and we use binary search
         uint count = 9;
         uint point = count / 2;
         while (true)
         {
            if (( size >> (point + 3)) > 8)
            {
               point += (count - point) / 2;
            }
            else if (( size >> (point + 3)) < 0)
            {
               point = point / 2;
            }
            else
            {
               point = 0;//
            }
         }
      }

   private:
      //  0   1   2   3   4   5   6   7    8
      // 2^3 2^4 2^5 2^6 2^7 2^8 2^9 2^10 2^11+ 
      //  8   16  32  64 128 256 512 1024  x
      IAllocator* _allocators[9];
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
