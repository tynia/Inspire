#ifndef _INSPIRE_NET_SERVICE_H_
#define _INSPIRE_NET_SERVICE_H_

#include "inspire.h"
#include "thread.h"

namespace inspire {

   class IProcessor;
   class TCPConnection;
   class IControl;
   class ISession;

   typedef std::map<int64, ISession*> SessionList;

   class IService : public IThread
   {
   public:
      virtual ~IService() {}

      virtual void run(IProcessor* processor) = 0;
   };

   class Service : public IService
   {
   public:
      Service(const unsigned int port);
      virtual ~Service();

      void initService();
      void stop();

      virtual void run(IProcessor* processor);
   protected:
      bool           _stop;
      IControl*      _threadMng;
      TCPConnection* _server;
      SessionList    _sessions;
   };

}
#endif