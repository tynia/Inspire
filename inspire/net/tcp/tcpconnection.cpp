#include "endpoint.h"
#include "tcpconnection.h"

namespace inspire {

   tcpConnection::tcpConnection() : _fd(INVALID_FD)
   {
   }

   tcpConnection::tcpConnection(const int sock) : _fd(sock)
   {
      INSPIRE_ASSERT(INVALID_FD == _fd, "try to init connection using invalid socket");
   }

   tcpConnection::~tcpConnection()
   {
   }

   bool tcpConnection::alive() const
   {
      int rc = 0;
#if defined(_WINDOWS)
      rc = ::send(_fd, "", 0, 0);
      if (SOCKET_ERROR == rc)
#elif defined(_AIX)
      rc = ::send(_fd, "", 0, 0);
      if (0 == rc)
#else
      rc = ::recv(_fd, NULL, 0, MSG_DONTWAIT);
      if (0 == rc)
#endif
      {
         return false;
      }
      return true;
   }

   void tcpConnection::close()
   {
      if (INVALID_FD != _fd)
      {
         ::closesocket(_fd);
         _fd = INVALID_FD;
      }
   }

   int tcpConnection::initialize()
   {
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (INVALID_SOCKET == _fd)
      {
         int rc = fetchNetError();
         LogError("Failed to init socket, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   int tcpConnection::bind(const uint port, endpoint& addr)
   {
      int addrLen = sizeof(addr.addr);
      toServerEndpoint(port, addr);
      int rc = ::bind(_fd, (struct sockaddr*)&addr.addr, addrLen);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to bind socket and port, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   int tcpConnection::listen(const uint maxconn)
   {
      int rc = ::listen(_fd, maxconn);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to listen on socket, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   int tcpConnection::accept(int& fd, endpoint& remote)
   {
      int addrLen = sizeof(remote.addr);
      int rc = ::accept(fd, (struct sockaddr*)&remote.addr, &addrLen);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to accept remote client, errno: %d", rc);
         return rc;
      }
      toEndpoint(fd, &remote);
      return 0;
   }

   int tcpConnection::connect(const char* hostname, const uint port, endpoint& remote)
   {
      toEndpoint(hostname, port, remote);
      int addrLen = sizeof(remote.addr);
      int rc = ::connect(_fd, (struct sockaddr*)&remote.addr, addrLen);
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to connect to remote server, errno: %d", fetchNetError());
         return rc;
      }

      return 0;
   }

   int tcpConnection::writeTo(const char* data, const uint len)
   {
      INSPIRE_ASSERT(NULL != data, "data to send cannot be NULL");
      uint pos = 0;
      while (pos < len)
      {
         int sendLen = ::send(_fd, data + pos, len - pos, 0);
         if (-1 == sendLen)
         {
            int rc = fetchNetError();
            LogError("Failed to send data, net error: %d", rc);
            return rc;
         }
         pos += sendLen;
      }
   }

   int tcpConnection::readFrom(char* buffer, const uint bufferLen, uint &recvLen)
   {
      INSPIRE_ASSERT(NULL != buffer, "buffer cannot be NULL");
      int rc = 0;
      // receive msg len first
      rc = ::recv(_fd, buffer, sizeof(int), 0);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to receive msg size, errno: %d", rc);
         return rc;
      }

      int recvLen = rc;

      // calculate message is endian check or not
      int size = *(int*)buffer;
      if (-1 != size)
      {
         //TODO:
      }
      // receive rest after message len received
      while (recvLen < size)
      {
         int len = ::recv(_fd, buffer + recvLen, size - recvLen, 0);
         if (0 == len)
         {
            LogError("peer unexpected shutdown");
            break;
         }
         else if (-1 == len)
         {
            rc = fetchNetError();
            LogError("Network error occurs when receiving, errno: %d", rc);
            return rc;
         }

         recvLen += len;
      }
      return rc;
   }
}