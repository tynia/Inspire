#ifndef _INSPIRE_NET_SERVICE_MANAGER_H_
#define _INSPIRE_NET_SERVICE_MANAGER_H_

#include "inspire.h"

namespace inspire {

   class ISession;
   class IService;
   class IProcessor;
   typedef std::map<int64, ISession> SessionList;

   class SessionManager
   {
   public:
      virtual ~SessionManager() {}

      void notifyAccept(ISession* session);

      void notifyRead(ISession* session);

      void notifyWrite(ISession* session);

      void notifyClose(ISession* session);

      SessionManager* instance();

   private:
      IProcessor* _processor;
      IService*   _service;
      SessionList _sessions;
   };
}
#endif