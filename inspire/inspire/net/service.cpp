#include "service.h"
#include "connection.h"
#include "async/ioservice.h"

namespace inspire {

   Service::Service(const unsigned int servicePort, IControl* threadMng) : _stop(true), _threadMng(threadMng)
   {
      INSPIRE_ASSERT((NULL != threadMng));
      //_async = new Connection(servicePort);
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
      _async->bind();
      _async->listen();
      _ioservice = new IOService();
      if (NULL == _ioservice)
      {
         //LogError...
         return;
      }
      _ioservice->init();
      _ioservice->bind();
   }

   void Service::stop()
   {
      _stop = true;
   }

   void Service::run( IProcessor* processor )
   {
      initService();
      unsigned int _id = 0;

      while (!_stop)
      {
         int rc = 0;
         int fd = 0;
         sockaddr_in addr;
         _async->accept(fd, addr);

         //ISession* ss = new ISession(fd);
         //_sessions.insert(std::make_pair(fd, ss));
         // start new thread
      }
   }
}