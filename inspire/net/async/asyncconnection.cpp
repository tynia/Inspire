#include "asyncConnection.h"

namespace inspire {

   asyncConnection::asyncConnection() : _IOService(NULL)
   {
   }

   asyncConnection::~asyncConnection()
   {
      close();
   }

   int asyncConnection::initialize()
   {
      int rc = 0;
      _fd = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
      if (INVALID_SOCKET == _fd)
      {
         rc = WSAGetLastError();
         LogError("Failed to init async socket, errno: %d", rc);
         return rc;
      }
      return rc;
   }

   int asyncConnection::doWrite(CEvent& ev)
   {
      int rc = 0;
      return rc;
   }

   int asyncConnection::doRead(const CEvent& ev)
   {
      int rc = 0;
      return rc;
   }

   int asyncConnection::doAccept(asyncConnection& conn)
   {
      int addrLen = sizeof(_addr.addr);
      int rc = ::WSAAccept(_fd, (struct sockaddr*)&_addr.addr, &addrLen, NULL, NULL);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to accept a connection, errno: %d", rc);
         return rc;
      }
      // TODO:
      // create a connection of remote client
      return rc;
   }

   int asyncConnection::listenOn(const uint port)
   {
      int rc = 0;
      toServerEndpoint(port, _addr);
      if (SOCKET_ERROR == bind(_fd, (struct sockaddr*)&_addr.addr, sizeof(_addr.addr)))
      {
         rc = fetchNetError();
         LogError("Failed to bind service addr to listen socket, errno: %d", rc);
         return rc;
      }

      if (SOCKET_ERROR == listen(_fd, SOMAXCONN))
      {
         rc = fetchNetError();
         LogError("Failed to listen on socket, errno: %d", rc);
         return rc;
      }
   }

   void asyncConnection::sendEvent(CEvent& ev)
   {
   }

   void asyncConnection::onEvent(CEvent& ev)
   {

   }
}