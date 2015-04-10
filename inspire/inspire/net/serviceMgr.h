#ifndef _INSPIRE_NET_SERVICE_MANAGER_H_
#define _INSPIRE_NET_SERVICE_MANAGER_H_

#include "inspire.h"
#include "control.h"

namespace inspire {

   class ISession;
   class IService;
   class IProcessor;
   typedef std::map<int64, ISession> SessionList;

   class insSessionMgr : public IControl
   {
   public:
      virtual ~insSessionMgr() {}

   private:
      IProcessor* _processor;
      IService*   _service;
      SessionList _sessions;
   };
}
#endif