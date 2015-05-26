#include "entry.h"

namespace inspire {

   //////////////////////////////////////////////////////////////////////////
   threadEntryPoint::threadEntryPoint(bool system, THREAD_ENTRY_TYPES t,
                                      THREAD_ENTRY entry, const char* desc)
   : _system(system), _type(t), _entry(entry), _desc(desc)
   {
   }

   threadEntryPoint::~threadEntryPoint()
   {}

   //////////////////////////////////////////////////////////////////////////
   threadEntryPointMgr::threadEntryPointMgr()
   {
      _mapEntryPoint.clear();
   }

   threadEntryPointMgr::~threadEntryPointMgr()
   {
      std::map<THREAD_ENTRY_TYPES, threadEntryPoint*>::iterator it = _mapEntryPoint.begin();
      while (_mapEntryPoint.end() != it)
      {
         threadEntryPoint*& pEntryPoint = it->second;
         delete pEntryPoint;
         pEntryPoint = NULL;
      }
   }

   threadEntryPointMgr* threadEntryPointMgr::instance()
   {
      static threadEntryPointMgr st;
      return &st;
   }

   threadEntryPoint* threadEntryPointMgr::createEntryPoint(bool system, THREAD_ENTRY_TYPES t, THREAD_ENTRY entry, const char* desc)
   {
      std::map<THREAD_ENTRY_TYPES, threadEntryPoint*>::iterator it = _mapEntryPoint.find(t);
      if (_mapEntryPoint.end() != it)
      {
         LogError("thread entry conflict, type:%d, name:%s", t, desc);
         return NULL;
      }

      threadEntryPoint* pEntryPoint = new threadEntryPoint(system, t, entry, desc);
      if (NULL == pEntryPoint)
      {
         LogError("Failed to allocate threadEntryPoint object, out of memory");
         return NULL;
      }

      _addEntryPoint(pEntryPoint);
      return pEntryPoint;
   }

   threadEntryPoint* threadEntryPointMgr::getEntryPonit(THREAD_ENTRY_TYPES t)
   {
      std::map<THREAD_ENTRY_TYPES, threadEntryPoint*>::iterator it = _mapEntryPoint.find(t);
      if (_mapEntryPoint.end() != it)
      {
         return it->second;
      }
      // shouldn't hit here
      return NULL;
   }

   const char* threadEntryPointMgr::getEntryPonitName( THREAD_ENTRY_TYPES t )
   {
      std::map<THREAD_ENTRY_TYPES, threadEntryPoint*>::iterator it = _mapEntryPoint.find(t);
      if (_mapEntryPoint.end() != it)
      {
         return it->second->_desc;
      }
      // shouldn't hit here
      return NULL;
   }

   void threadEntryPointMgr::_addEntryPoint(threadEntryPoint* pEntryPoint)
   {
      INSPIRE_ASSERT(NULL != pEntryPoint, "Thread entry point is NULL");

      _mapEntryPoint[pEntryPoint->_type] = pEntryPoint;
   }
}