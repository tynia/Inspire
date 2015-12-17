#ifndef _INSPIRE_NET_SERVICE_MANAGER_H_
#define _INSPIRE_NET_SERVICE_MANAGER_H_

#include "util/inspire.h"
#include "control.h"

namespace inspire {

   class ISession;
   class IService;
   class IProcessor;
   typedef std::map<int64, ISession> SessionList;

   class insServiceMgr// : public IControl
   {
   private:
      insServiceMgr();
      virtual ~insServiceMgr() {}

   public:
      static insServiceMgr* instance();



      ISession* createSession(const int64 sid = 0);
      ISession* destorySession(const int64 sid);
      ISession* destorySession(ISession* session);

   private:
      IProcessor* _processor;
      IService*   _service;
      SessionList _sessions;
   };
}
#endif