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
      _fd = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
      if (INVALID_SOCKET == _fd)
      {
         int rc = WSAGetLastError();
         LogError("Failed to init async socket, errno: %d", rc);
         return rc;
      }
   }

   int asyncConnection::doAccept(asyncConnection& conn)
   {
      int addrLen = sizeof(_remote.addr);
      int rc = WSAAccept(_fd, (struct sockaddr*)&_remote.addr, &addrLen, NULL, NULL);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to accept a connection, errno: %d", rc);
         return rc;
      }
      _IOService->createSession()
   }

   void asyncConnection::sendEvent(CEvent& ev)
   {
   }

   void asyncConnection::onEvent(CEvent& ev)
   {

   }
}