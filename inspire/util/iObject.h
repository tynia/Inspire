#ifndef _INSPIRE_BASE_OBJECT_H_
#define _INSPIRE_BASE_OBJECT_H_

#include "inspire.h"
#include "AllocatorMgr.h"

namespace inspire {

   class iObject
   {
#define INSPIRE_MALLOC(x) AllocatorMgr::instance()->alloc(size, __FILE__, __LINE__)
#define INSPIRE_FREE(p)   AllocatorMgr::instance()->dealloc(p)
   protected:
      iObject() {}
      virtual ~iObject() {}

   public:
      void* operator new (uint size) throw (const char*)
      {
         void* ptr = INSPIRE_MALLOC(size);
         if (NULL == ptr)
         {
            throw "Allocate Failed";
         }
         return ptr;
      }

      void* operator new[] (uint size) throw (const char*)
      {
         void* ptr = INSPIRE_MALLOC(size);
         if (NULL == ptr)
         {
            throw "Allocate Failed";
         }
         return ptr;
      }

      void operator delete (void *p)
      {
         INSPIRE_FREE(p);
      }

      void operator delete[](void *p)
      {
         INSPIRE_FREE(p);
      }

      void * operator new (size_t size, const char *file, uint line) throw (const char *)
      {
         void *p = INSPIRE_MALLOC(size, file, line);
      if (!p) throw "Allocate Failed";
      return p;
      }

      void * operator new[](size_t size, const char *file, uint line) throw (const char *)
      {
         void *p = INSPIRE_MALLOC(size, file, line);
         if (!p) throw "Allocate Failed";
         return p;
      }

      void operator delete (void *p, const char *file, uint line)
      {
         INSPIRE_FREE(p);
      }

      void operator delete[](void *p, const char *file, uint line)
      {
         INSPIRE_FREE(p);
      }

      void * operator new (size_t size, const std::nothrow_t &)
      {
         return INSPIRE_MALLOC(size);
      }

      void * operator new[](size_t size, const std::nothrow_t &)
      {
         return INSPIRE_MALLOC(size);
      }

      void operator delete (void *p, const std::nothrow_t &)
      {
         INSPIRE_FREE(p);
      }

      void operator delete[](void *p, const std::nothrow_t &)
      {
         INSPIRE_FREE(p);
      }

      void * operator new (size_t size, const char *file,
                           uint line, const std::nothrow_t &)
      {
         return INSPIRE_MALLOC(size, file, line);
      }

      void * operator new[](size_t size, const char *file,
                            uint line, const std::nothrow_t &)
      {
         return INSPIRE_MALLOC(size, file, line);
      }

      void operator delete (void *p, const char *file,
                            uint line, const std::nothrow_t &)
      {
         INSPIRE_FREE(p);
      }

      void operator delete[](void *p, const char *file,
                             uint line, const std::nothrow_t &)
      {
         INSPIRE_FREE(p);
      }
   };
}
#endif