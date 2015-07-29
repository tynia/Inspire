#ifndef _INSPIRE_UTIL_ALLOCATOR_H_
#define _INSPIRE_UTIL_ALLOCATOR_H_

#include "inspire.h"

namespace inspire {

   static const unsigned int szBlock = 4096;
   static const unsigned int szAlignment = sizeof(void*);

   class allocator : public noncopyable
   {
   public:
      allocator();
      virtual ~allocator();

      void* alloc(const unsigned int size);
      void dealloc(const char* ptr);

   protected:
      char* _align(char* origin);
      void* _addMemory(const size_t size);

   private:
      struct header
      {
         char* _hdBlock;
      };
      char* _ptrBegin;
      char* _ptrEnd;
      char* _ptrCurrent;
      char  _data[szBlock];
   };

   
}
#endif