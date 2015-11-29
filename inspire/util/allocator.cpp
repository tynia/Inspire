#include "allocator.h"
#include "util.h"
#include "logger/logger.h"
#include "condition.h"

namespace inspire {

   allocator::allocator()
   {
      _setSanity((void*)&_hdr, NULL, 0);
   }

   allocator::~allocator()
   {
      _resetRest();
   }

   char* allocator::alloc(const uint size, const char* file, const int line)
   {
      //
      // mutex lock
      char* ptr = _alloc(size);
      if (NULL == ptr)
      {
         pray();
         ptr = _alloc(size);
      }

      if (NULL != ptr)
      {
         _setSanity(ptr, file, line);
         ::memset(ptr + sizeof(header), 0, size);
         return (ptr + sizeof(header));
      }

      LogError("Failed to allocate memory, size: %d", size);
      return NULL;
   }

   char* allocator::_alloc(const uint size)
   {
      condition_t cond(&_mtx);
      header* hdr = _hdr;
      while (NULL != hdr)
      {
         header* toReturn = hdr;
         if (NULL != toReturn)
         {
            hdr = toReturn->next;
            toReturn->next = NULL;
            return (char*)toReturn;
         }
         else
         {
            hdr = hdr->next;
         }
      }

      char* ptr = (char*)::malloc(size + sizeof(header));
      if (NULL == ptr)
      {
         LogError("Failed to alloc memory, size = d%", size + sizeof(header));
         return NULL;
      }
   }

   void allocator::dealloc(const char* ptr)
   {
      //
      // mutex lock
      bool ok = _checkSanity(ptr);
      if (!ok)
      {
         LogError("pointer: 0x%x sanity checked failed, it may not be "
                  "allocated by allocator", (uint64*)ptr);
         //::free(ptr);
#ifdef _DEBUG
         Panic();
#endif
         return;
      }

      condition_t cond(&_mtx);
      header* hdr = (header*)(ptr - sizeof(header));
      ::memset((void*)ptr, 0xfe, _size);
      hdr->next = _hdr;
      _hdr = hdr;
   }

   void allocator::pray()
   {
      _resetRest();
   }

   bool allocator::_checkSanity(const char* ptr)
   {
      header* hdr = (header*)(ptr - sizeof(header));
      bool eq1 = (0 == ::memcmp(hdr->eyecatcher, "inspire", 8));
      bool eq2 = (magic == hdr->magic);
      return !(eq1 && eq2);
   }

   void allocator::_setSanity(void* ptr, const char* file, const int line)
   {
      ::memset(ptr, 0x0, sizeof(header));
      header* hdr = (header*)ptr;
      ::memmove(hdr->eyecatcher, "inspire", 7);
      hdr->file = file;
      hdr->line = line;
      hdr->next = NULL;
      hdr->magic = magic;
   }

   void allocator::_resetRest()
   {
      while (NULL != _hdr)
      {
         header* ptr = _hdr;
         _hdr = _hdr->next;
         ::free((void*)ptr);
      }
   }
}
