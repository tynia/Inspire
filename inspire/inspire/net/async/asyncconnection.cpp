#include "asyncconnection.h"
#include "helper/nethelper.h"

namespace inspire {

   AsyncConnection::AsyncConnection(const uint port) : IAsyncConnection(port)
   {
   }

   AsyncConnection::AsyncConnection(const char* ip, const uint port) : IAsyncConnection(ip, port)
   {
   }

   AsyncConnection::AsyncConnection(const int sock) : IAsyncConnection(sock)
   {
      _fd = sock;
   }

   AsyncConnection::AsyncConnection(const AsyncConnection& rhs) : IAsyncConnection(rhs)
   {
      _fd = rhs._fd;
      _id = rhs._fd;
      _port = rhs._port;
      memcpy(&_addr, &rhs._addr, sizeof(_addr));
   }

   AsyncConnection::~AsyncConnection()
   {
      close();
   }

   void AsyncConnection::init()
   {
      util::initNetwork();
      _fd = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
      if (INVALID_SOCKET == _fd)
      {
         LogError("Failed to init async socket, errno: %d", WSAGetLastError());
      }
   }

   void AsyncConnection::accept(int& fd, sockaddr_in& addr)
   {
      int addrLen = sizeof(sockaddr_in);
      int rc = WSAAccept(fd, (struct sockaddr*)&addr, &addrLen, NULL, NULL);
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to accept a connection");
      }
   }

   void AsyncConnection::sendEvent(CEvent& ev)
   {
   }

   void AsyncConnection::onEvent(CEvent& ev)
   {

   }
}