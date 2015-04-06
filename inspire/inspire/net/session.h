#ifndef _INSPIRE_NET_SESSION_H_
#define _INSPIRE_NET_SESSION_H_

#include "async/asyncconnection.h"
#include "thread.h"

namespace inspire {

   class IProcessor;

   class ISession : public INetAsyncEventHandler
   {
   public:
      virtual ~ISession() {};
      virtual void run(IProcessor* processor) = 0;
   };

   class Session : public ISession, public threadEntity
   {
   public:
      Session(const int socket);
      virtual ~Session();

   public:
      // ISession
      virtual void run(IProcessor* processor);

      // IThread
      virtual void init();
      virtual void run();
      virtual void destroy();

      // INetHandler
      virtual void SendEvent(CEvent& ev);
      virtual void OnEvent(CEvent& ev);

   protected:
      IAsyncConnection *_conn;
#ifdef _WIN32
      HANDLE  _hIOCP;
#else
      int _fd;
#endif
   };
}
#endif