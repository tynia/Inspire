#include "service.h"
#include "connection.h"
#include "async/ioservice.h"
#include "async/asyncconnection.h"
#include "tcpconnection.h"

namespace inspire {

   Service::Service(const unsigned int servicePort, IControl* threadMgr) : _stop(true), _threadMgr(threadMgr)
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

   void Service::initService()
   {
      _async->init();
      _async->bindAndListen();
      _ioservice = new IOService();
      if (NULL == _ioservice)
      {
         LogError("Failed to create IOService");
         return;
      }
      _ioservice->init();
      _ioservice->bind(_async);
   }

   void Service::stop()
   {
      _stop = true;
   }

   void Service::run()
   {
      initService();
      unsigned int _id = 0;
      _ioservice->run();
      while (!_stop)
      {
         int rc = 0;
         int fd = 0;
         sockaddr_in addr;
         _async->accept(fd, addr);

         //ISession* ss = new Session(fd);
         //ss->init();
         //ss->run(processor);
         //_sessions.insert(std::make_pair(fd, ss));
         // start new thread
      }
   }
}