#ifndef _INSPIRE_UTIL_ALLOCATOR_H_
#define _INSPIRE_UTIL_ALLOCATOR_H_

#include "inspire.h"
#include "noncopyable.h"
#include "mutex.h"

namespace inspire {

#define INSPIRE_ALLOC_OBJECT(cls, file, line) \
       return CAllocator()->create<cls>(file, line)

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
      //  0   1   2   3   4   5   6   7    8
      // 2^3 2^4 2^5 2^6 2^7 2^8 2^9 2^10 2^11+ 
      //  8   16  32  64 128 256 512 1024  x
      IAllocator* _allocators[9];
   };

   class allocator// public noncopyable
   {
      static const uint64 magic = 0xFFFFFFFFFFFAFBFE;
   public:
      virtual char* alloc(const uint size, const char* file, const int line);
      virtual void dealloc(const char* ptr);
      virtual void pray();

      template<class T>
      T* create(const char* file, const int line)
      {
         char* ptr = alloc(sizeof(T), file, line);
         if (NULL == ptr)
         {
            reorganize();
            ptr = alloc(sizeof(T), file, line);
         }

         if (NULL == ptr)
         {
            LogError("Failed to allocate memory, size: %d", sizeof(T));
            return NULL;
         }

         return new(ptr) T;
      }
   protected:
      allocator();
      virtual ~allocator();

   private:
      #define MAX_HEADER_COUNT 9
      bool _checkSanity(const char* ptr);
      void _setSanity(void* ptr, const char* file, const int line);
      void _resetRest();
      uint _locate(const uint size)
      {
         // we need find which allocator should allocate the size
         // and we use binary search
         uint high  = MAX_HEADER_COUNT - 1;
         uint low   = 0;
         uint point = 0;
         while (true)
         {
            point = (high + low) / 2;
            if (size >= 2 * _alloc[point].size)
            {
               low = point;
            }
            else if (size < _alloc[point].size)
            {
               high = point;
            }
            else
            {
               break;
            }
         }
      }

   private:
      struct header
      {
         char eyecatcher[8]; // inspire + '\0'                       8 bytes
#ifdef _DEBUG
         const char* file;
         const uint  line;
#endif
         header* next;       // next buffer header                 4/8 bytes
         uint64 magic;       // magic number                         8 bytes
      };

      struct unit
      {
         uint size;
         header hdr;
      };

      unit _alloc[MAX_HEADER_COUNT];
      mutex_t _mtx;
   };
}
#endif