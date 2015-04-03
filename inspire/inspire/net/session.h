#ifndef _INSPIRE_NET_SESSION_H_
#define _INSPIRE_NET_SESSION_H_

#include "inspire.h"
#include "tcpconnection.h"
#include "event/eventhandler.h"
#include "thread.h"

namespace inspire {

   class IProcessor;
   class IThread;

   class ISession : public INetEventHandler
   {
   public:
      virtual ~ISession() {};

      virtual void init();

      virtual void run(IProcessor* processor);

      virtual void destroy();

      virtual void sendEvent(CEvent& ev);
   };

   class Session : public ISession, public IThread
   {
   public:
      Session(const int socket);
      virtual ~Session();

   public:
      // IThread
      virtual void init();
      virtual void run (IProcessor* processor);
      virtual void destroy();

      // INetHandler
      virtual void SendEvent(CEvent& ev);
      virtual void OnEvent(CEvent& ev);

   protected:
      
#ifdef _WIN32
      SOCKET  _conn;
      HANDLE  _hIOCP;
#else
      int _fd;
#endif
   };
}
#endif