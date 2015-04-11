#ifndef _INSPIRE_THREAD_MANAGER_H_
#define _INSPIRE_THREAD_MANAGER_H_

#include "application.h"
#include "entry/entry.h"

#include <map>

namespace inspire {

   class threadEntity;
   typedef std::map<int64, threadEntity*> threadMap;

   class IThreadMgr
   {
   public:
      virtual ~IThreadMgr();

      virtual threadEntity* createEntity(THREAD_ENTRY_TYPES t, void* argv, int64& id) = 0;

      virtual void destroyEntity(const int64 id) = 0;

      virtual void registerEntity(const int64 id) = 0;

      virtual void activeEntity(const int64 id) = 0;

      virtual threadEntity* getEntity(const int64 id) = 0;
   };

   class threadMgr : public IControl, public IThreadMgr
   {
   public:
      threadMgr();
      ~threadMgr();

      virtual threadEntity* createEntity(THREAD_ENTRY_TYPES t, void* argv, int64& id);

      virtual void destroyEntity(const int64 id);

      virtual void registerEntity(const int64 id);

      virtual void activeEntity(const int64 id);

      virtual threadEntity* getEntity(const int64 id);

   private:
      threadMap _mapSystemThread;
      threadMap _mapIdleThread;
   };
}
#endif