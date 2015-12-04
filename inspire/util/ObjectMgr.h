#ifndef _INSPIRE_UTIL_OBJECT_MGR_H_
#define _INSPIRE_UTIL_OBJECT_MGR_H_

#include "memory/AllocatorMgr.h"
#include "container/deque.h"

namespace inspire {

   template<class O>
   class ObjectMgr
   {
   public:
      ObjectMgr()
      {
         _alMgr = AllocatorMgr::instance();
         STRONG_ASSERT(NULL != _alMgr, "AllocatorMgr cannot be NULL");
      }

      ~ObjectMgr()
      {
         _destroy();
         _alMgr = NULL;
      }

   public:
      O* create()
      {
         O* obj = _require();
         if (NULL == obj)
         {
            char* ptr = _alMgr->alloc(sizeof(O));
            if (NULL == ptr)
            {
               return NULL;
            }
            return new(ptr) O;
         }
         return obj;
      }

      template<class T>
      O* create(T& t)
      {
         O* obj = _require();
         if (NULL == obj)
         {
            char* ptr = _alMgr->alloc(sizeof(O));
            if (NULL == ptr)
            {
               return NULL;
            }
            return new(ptr) O(t1);
         }
         return obj;
      }

      template<class T1, class T2>
      O* create(T1& t1, T2& t2)
      {
         O* obj = _require();
         if (NULL == obj)
         {
            char* ptr = _alMgr->alloc(sizeof(O));
            if (NULL == ptr)
            {
               return NULL;
            }
            return new(ptr) O(t1, t2);
         }
         return obj;
      }

      template<class T1, class T2, class T3>
      O* create(T1& t1, T2& t2, T3& t3)
      {
         O* obj = _require();
         if (NULL == obj)
         {
            char* ptr = _alMgr->alloc(sizeof(O));
            if (NULL == ptr)
            {
               return NULL;
            }
            return new(ptr) O(t1, t2, t3);
         }
         return obj;
      }

      void destroy(O* obj)
      {
         obj->~O();
         ::memset((void*)obj, 0x0, sizeof(O));
         _objs.push_back(obj);
      }

   private:
      void _destroy()
      {
         while (!_objs.empty())
         {
            O* obj = _objs.pop_front();
            INSPIRE_ASSERT(NULL != obj, "Get an invalid obj");
            _alMgr->dealloc(obj);
         }
      }

      O* _require()
      {
         O* obj = NULL;
         if (_objs.pop_front(obj))
         {
            return obj;
         }
         return NULL;
      }

   private:
      AllocatorMgr* _alMgr;
      deque<O*>     _objs;
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