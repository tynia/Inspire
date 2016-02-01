#include "asyncConnection.h"
#include "nostream.h"
#include "event/event.h"

namespace inspire {

   asyncConnection::asyncConnection() : baseConnection()
   {
   }

   asyncConnection::asyncConnection(int sock) : baseConnection(sock)
   {
   }

   asyncConnection::~asyncConnection()
   {
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

   int asyncConnection::doWrite(const char* data, const uint len)
   {
      int rc = 0;
      
      return rc;
   }

   int asyncConnection::doRead(char* buffer, uint64 bufferLen, uint64& readLen)
   {
      int rc = 0;
      DWORD dwFlags = 0;
      DWORD dwBytes = 0;
      WSABUF wsabuf;
      wsabuf.buf = buffer;
      wsabuf.len = bufferLen;
      int nBytesRecv = WSARecv(_fd, &wsabuf, 1, (LPDWORD)&bufferLen, &dwFlags, pOverlapped, NULL);
      if ((SOCKET_ERROR == nBytesRecv) && (WSA_IO_PENDING != WSAGetLastError()))
      {
         rc = fetchNetError();
         LogError("Post RECV event error, errno = %d", rc);
         return rc;
      }
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
}