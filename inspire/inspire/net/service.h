#ifndef _INSPIRE_NET_SERVICE_H_
#define _INSPIRE_NET_SERVICE_H_

#include "inspire.h"
#include "thread.h"

namespace inspire {

   class IProcessor;
   class Connection;
   class IControl;
   class ISession;

   typedef std::map<int64, ISession*> SessionList;

   class IService
   {
   public:
      virtual ~IService() {}

      virtual void run(IProcessor* processor) {};

      virtual void notifyEvent( CEvent *ev) {};
   };

   class IOService;
   class Service : public IService, public threadEntity
   {
   public:
      Service(const unsigned int servicePort, IControl* threadMng);
      virtual ~Service();

      void initService();
      void stop();

      virtual void run(IProcessor* processor);
   protected:
      bool              _stop;
      IControl*         _threadMng;
      IAsyncConnection* _async;
      IOService*        _ioservice;
      SessionList       _sessions;
   };

}
#endif