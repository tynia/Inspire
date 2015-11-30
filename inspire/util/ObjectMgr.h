#ifndef _INSPIRE_UTIL_OBJECT_MGR_H_
#define _INSPIRE_UTIL_OBJECT_MGR_H_

#include "AllocatorMgr.h"

namespace inspire {

   class ObjectMgr
   {
   private:
      ObjectMgr(AllocatorMgr* mgr);
      ~ObjectMgr();

   public:
      template<class T>
#ifdef _DEBUG
      T* create(const char* file, const uint line)
      {
         char* ptr = _alMgr->alloc(sizeof(T), file, line);
         if (NULL == ptr)
         {
            return NULL;
         }

         return new(ptr) T();
      }
#else
      T* create()
      {
         char* ptr = _alMgr->alloc(sizeof(T));
         if (NULL == ptr)
         {
            return NULL;
         }

         return new(ptr) T();
      }
#endif

      template<class T>
      void destroy(T* pt)
      {
         pt->~T();
         _alMgr->dealloc((const char*)pt);
      }

      static ObjectMgr* instance();
   private:
      AllocatorMgr* _alMgr;
   };
}

#ifdef _DEBUG
#define INSPIRE_CREATE_OBJECT(cls) \
inspire::ObjectMgr::instance()->create<cls>(__FILE__, __LINE__);
#else
#define INSPIRE_CREATE_OBJECT(cls) \
inspire::ObjectMgr::instance()->create<cls>();
#endif
#define INSPIRE_DESTROY_OBJECT(cls, obj) \
inspire::ObjectMgr::instance()->destroy<cls>(obj);
#endif