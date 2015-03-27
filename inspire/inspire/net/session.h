#ifndef _INSPIRE_NET_SESSION_H_
#define _INSPIRE_NET_SESSION_H_

#include "inspire.h"
#include "tcpconnection.h"

namespace inspire {

   class IProcessor;

   class ISession
   {
   public:
      virtual ~ISession() {}
      virtual void init() = 0;
      virtual void run(IProcessor* processor) = 0;
      virtual void destroy() = 0;
      virtual void onEventReceived(CEvent& ev) = 0;
   };

   class Session
   {
   public:
      Session(const int socket);
      virtual ~Session();

   public:
      virtual void init();
      virtual void run (IProcessor* processor);
      virtual void destroy();
      virtual void onEventReceived(CEvent& ev);

   protected:
      TCPConnection* _conn;
   };
}
#endif