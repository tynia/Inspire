#include "asyncConnection.h"

namespace inspire {

   asyncConnection::asyncConnection(const uint port)
   {
   }

   asyncConnection::~asyncConnection()
   {
      close();
   }

   void asyncConnection::init()
   {
      _fd = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
      if (INVALID_SOCKET == _fd)
      {
         LogError("Failed to init async socket, errno: %d", WSAGetLastError());
      }
   }

   void asyncConnection::accept(int& fd, sockaddr_in& addr)
   {
      int addrLen = sizeof(sockaddr_in);
      int rc = WSAAccept(fd, (struct sockaddr*)&addr, &addrLen, NULL, NULL);
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to accept a connection");
      }
   }

   void asyncConnection::sendEvent(CEvent& ev)
   {
   }

   void asyncConnection::onEvent(CEvent& ev)
   {

   }
}