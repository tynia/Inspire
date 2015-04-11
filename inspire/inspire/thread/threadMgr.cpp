#include "threadMgr.h"
#include "thread.h"

namespace inspire {

   threadMgr::threadMgr() : IControl(MOD_THREAD)
   {

   }

   threadMgr::~threadMgr()
   {
      threadMap::iterator it = _mapSystemThread.begin();
      for (; _mapSystemThread.end() != it; ++it)
      {
         threadEntity* entity = it->second;
         entity->stop();
         delete entity;
         entity = NULL;
      }

      threadMap::iterator it = _mapIdleThread.begin();
      for (; _mapIdleThread.end() != it; ++it)
      {
         threadEntity* entity = it->second;
         entity->stop();
         delete entity;
         entity = NULL;
      }
   }

   threadEntity* threadMgr::createEntity(THREAD_ENTRY_TYPES t, void* argv, int64& id)
   {
#ifdef _DEBUG
      threadMap::iterator it = _mapSystemThread.begin();
      for (; _mapSystemThread.end() != it; ++it)
      {
         if ( t == (it->second)->type() )
         {
            LogWarning("duplicate system thread created, type:%d", t);
         }
      }
#endif

      threadEntity* entity = new threadEntity(t, argv);
      if (NULL == entity)
      {
         LogError("Failed to create threadEntity, type:%d", t);
         return;
      }

      entity->init();

      id = entity->id();
      //lock
      _mapIdleThread.insert(std::make_pair(id, entity));
   }

}