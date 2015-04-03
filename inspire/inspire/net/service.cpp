#include "service.h"
#include "tcpconnection.h"
#include "async/ioservice.h"

namespace inspire {

   Service::Service(const unsigned int servicePort, IControl* threadMng) : _stop(true), _threadMng(threadMng)
   {
      INSPIRE_ASSERT((NULL != threadMng));
      _server = new TCPConnection(servicePort);
      if (NULL == _server)
      {
         //LogError
      }
   }

   Service::~Service()
   {
      if (NULL != _server)
      {
         delete _server;
         _server = NULL;
      }
   }

   void Service::initService()
   {
      _server->bind();
      _server->listen();
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
         _server->accept(fd, addr);

         //ISession* ss = new ISession(fd);
         //_sessions.insert(std::make_pair(fd, ss));
         // start new thread
      }
   }
}