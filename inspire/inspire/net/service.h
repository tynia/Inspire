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

      virtual void init() = 0;

      virtual void run() = 0;

      virtual void destroy() = 0;
   };

   class IOService;
   class IThreadMgr;
   class Service : public IService//, public threadEntity
   {
   public:
      Service(const unsigned int servicePort, IThreadMgr* threadMgr);
      virtual ~Service();

      void initService();
      void stop();

      virtual void init();
      virtual void run();
      virtual void destroy();

   protected:
      bool              _stop;
      IThreadMgr*       _threadMgr;
      IAsyncConnection* _async;
      IOService*        _ioservice;
      threadEntity*     _entity;
      SessionList       _sessions;
   };

}
#endif