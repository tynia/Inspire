#include "service.h"
#include "connection.h"
#include "async/ioservice.h"
#include "async/asyncconnection.h"
#include "tcpconnection.h"

namespace inspire {

   Service::Service(const unsigned int servicePort, IThreadMgr* threadMgr) : _threadMgr(threadMgr)
   {
      INSPIRE_ASSERT((NULL != threadMgr));
      _async = new AsyncConnection(servicePort);
      if (NULL == _async)
      {
         //LogError
      }
   }

   Service::~Service()
   {
      if (NULL != _async)
      {
         delete _async;
         _async = NULL;
      }
   }

   void Service::init()
   {
      _async->init();
      _async->bindAndListen();
      _ioservice = new IOService(_threadMgr);
      if (NULL == _ioservice)
      {
         LogError("Failed to create IOService");
         return;
      }
   }

   void Service::initService()
   {
      if (_ioservice)
      {
         _ioservice->init();
         _ioservice->bind(_async);
      }
   }

   void Service::stop()
   {
      _ioservice->stop();
   }

   void Service::run()
   {
      initService();
      _ioservice->run();
   }

   void Service::destroy()
   {
      _ioservice->destroy();
      delete _async;
      _async = NULL;
   }
}