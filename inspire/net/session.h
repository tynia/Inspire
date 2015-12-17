#ifndef _INSPIRE_NET_SESSION_H_
#define _INSPIRE_NET_SESSION_H_

#include "async/asyncconnection.h"
#include "thread/thread.h"

namespace inspire {

   class IProcessor;

   class ISession : public INetAsyncEventHandler
   {
   public:
      virtual ~ISession() {};

      virtual void init() = 0;
      virtual void run(IProcessor* processor) = 0;
      virtual void destroy() = 0;
   };

   class OverlappedContext;
   class Session : public ISession//, public threadEntity
   {
   public:
      Session(OverlappedContext* lpContext);
      Session(const int socket);
      virtual ~Session();

   public:
      // ISession
      virtual void init();
      virtual void run(IProcessor* processor);
      virtual void destroy();

      // INetAsyncEventHandler
      virtual void sendEvent(CEvent& ev);
      virtual void onEvent(CEvent& ev);

   protected:
      IAsyncConnection* _conn;
      threadEntity*     _entity;
#ifdef _WIN32
      HANDLE  _hIOCP;
#else
      int _fd;
#endif
   };
}
#endif