#include "threadMgr.h"
#include "thread.h"
#include "entryPoint.h"

namespace inspire {

   threadMgr::threadMgr() : IControl(MOD_THREAD)
   {

   }

   threadMgr::~threadMgr()
   {
      threadContainer::iterator it = _mapRunningThread.begin();
      for (; _mapRunningThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         entity->stop();
         delete entity;
         entity = NULL;
      }

      threadContainer::iterator it = _mapIdleThread.begin();
      for (; _mapIdleThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         entity->destroy();
         delete entity;
         entity = NULL;
      }
   }

   threadEntity* threadMgr::createEntity(THREAD_ENTRY_TYPES t, void* argv, int64& id)
   {
#ifdef _DEBUG
      systemThreadContainer::iterator it = _mapSystemThread.begin();
      for (; _mapSystemThread.end() != it; ++it)
      {
         if (t == *it)
         {
            LogEvent("duplicate system thread created, type: %d", t);
            break;
         }
      }
#endif
      //lock
      threadEntity* entity = new threadEntity(t, argv);
      if (NULL == entity)
      {
         LogError("Failed to create threadEntity, type: %d", t);
         return;
      }

      entity->init();

      id = entity->id();

      if (entity->isSystemThread())
      {
         _mapSystemThread.push_back(t);
      }
      _mapIdleThread.push_back(entity);
      // release lock
   }

   void threadMgr::destroyEntity(const int64 id)
   {
      threadContainer::iterator it = _mapRunningThread.begin();
      for (; _mapRunningThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         if (id == entity->id())
         {
            entity->destroy();
            LogEvent("destroy running thread, thread id: %lld", id);
            return;
         }
      }

      threadContainer::iterator it = _mapIdleThread.begin();
      for (; _mapIdleThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         if (id == entity->id())
         {
            entity->resume();
            entity->destroy();
            LogEvent("destroy idle thread, thread id: %lld", id);
            return;
         }
      }
   }

   void threadMgr::activeEntity(const int64 id)
   {
      threadContainer::iterator it = _mapIdleThread.begin();
      for (; _mapIdleThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         if (id == entity->id())
         {
            entity->run();
            threadEntryPoint* info = getEntryPoint(entity->type());
            LogEvent("run thread, thread id: %lld, name: %s, system: %s", id,
                     info->_desc, entity->isSystemThread() ? "Yes" : "No");
            return;
         }
      }

#ifdef _DEBUG
      threadContainer::iterator it = _mapRunningThread.begin();
      for (; _mapRunningThread.end() != it; ++it)
      {
         if (id == (*it)->id())
         {
            LogEvent("thread is running, id: %lld", id);
            break;
         }
      }
#endif
      LogError("cannot find thread, id: %lld", id);
   }

   threadEntity* threadMgr::getEntity( const int64 id )
   {
      threadContainer::iterator it = _mapIdleThread.begin();
      for (; _mapIdleThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         if (id == entity->id())
         {
            return entity;
         }
      }

#ifdef _DEBUG
      threadContainer::iterator it = _mapRunningThread.begin();
      for (; _mapRunningThread.end() != it; ++it)
      {
         threadEntity* entity = *it;
         if (id == entity->id())
         {
            return entity;
         }
      }
#endif
      LogError("cannot find thread, id: %lld", id);
   }

}