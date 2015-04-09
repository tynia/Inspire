#include "threadController.h"

namespace inspire {

   threadController::threadController() : IControl(MOD_THREAD)
   {

   }

   threadController::~threadController()
   {
      threadMap::iterator it = _mapCustomThread.begin();
      for (; _mapCustomThread.end() != it; ++it)
      {
         threadEntity* entity = it->second;
         delete entity;
         entity = NULL;
      }
   }

   void threadController::createEntity(THREAD_TYPES t, void* argv, int64& id)
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
   }


}