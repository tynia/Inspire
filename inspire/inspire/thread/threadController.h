#ifndef _INSPIRE_THREAD_CONTROLLER_H_
#define _INSPIRE_THREAD_CONTROLLER_H_

#include "application.h"
#include "entry/threadentry.h"

#include <map>

namespace inspire {

   class threadEntity;
   typedef std::map<int64, threadEntity*> threadMap;

   class threadController : public IControl
   {
   public:
      threadController();
      ~threadController();

      void createEntity(THREAD_TYPES t, void* argv, int64& id);

      void destroyEntity(const int64 id);

      void registerEntity(const int64 id);

      void activeEntity(const int64 id);

      threadEntity* getEntity(const int64 id);

   private:
      threadMap _mapSystemThread;
      threadMap _mapCustomThread;
   };
}
#endif