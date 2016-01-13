#include "tcpconnection.h"

namespace inspire {
   
   tcpConnection::tcpConnection() : _fd(INVALID_FD), _port(0)
   {
      ASSERT_STRONG(util::netok(), "Failed to init network");
   }

   tcpConnection::tcpConnection(const char* ip, const uint port) : _port(0)
   {
      _init();
      _initAddr(ip, port);
      memset(&_addr, 0, sizeof(_addr));
   }

   tcpConnection::tcpConnection(const int sock) : _fd(sock)
   {
      util::getPeerAddr(&_fd, _addr);
      _port = util::port(&_addr);
   }

   tcpConnection::tcpConnection(const tcpConnection& rhs)
   {
      _fd = rhs._fd;
      _port = rhs._port;
      memcpy(&_addr, &rhs._addr, sizeof(_addr));
   }

   tcpConnection::~tcpConnection()
   {
      close();
   }

   void tcpConnection::_init()
   {
#ifdef _WIN32
      if ( !util::netok() )
      {
         LogError("Init network module Failed, errno: %d", util::fetchNetError());
         return;
      }
#endif // _WIN32
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      ASSERT_STRONG(INVALID_SOCKET != _fd, "Failed to create socket");
   }

   void tcpConnection::bind()
   {
      sockaddr_in local;
      _initAddr(local);

      int rc = ::bind(_fd, (sockaddr*)&local, sizeof(local));
      ASSERT_STRONG(SOCKET_ERROR != rc,
                    "Failed to bind on port: %d, net error: %d", _port, util::fetchNetError());
   }

   void tcpConnection::listen(const uint maxConn /*= 20*/)
   {
      int rc = ::listen(_fd, maxConn);
      ASSERT_STRONG(SOCKET_ERROR != rc,
                    "Failed to listen, net error: %d", util::fetchNetError());
   }

   void tcpConnection::accept(int& fd, sockaddr_in& addr)
   {
      int len = sizeof(addr);
      fd = ::accept(_fd, (sockaddr*)&addr, &len);
         ASSERT_STRONG((INVALID_SOCKET != fd),
                        "Failed to accept a remote connection, net error: %d",
                        util::fetchNetError());
   }

   

   void tcpConnection::connect(const char* ip, const uint port)
   {
      close();
      toEndpoint(ip, port, _remote);
      int rc = ::connect(_fd, (struct sockaddr*)&_remote, sizeof(sockaddr_in));
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to connect to %s:%d, errno: d%",
                  util::ip(&_addr), util::port(&_addr), util::fetchNetError());
      }
   }

   void tcpConnection::send(const char* data, const uint len)
   {
      INSPIRE_ASSERT(NULL != data, "data to send cannot be NULL");
      uint sent = 0;
      while (sent < len)
      {
         int sendLen = ::send(_fd, data + sent, len - sent, 0);
         if (-1 == sendLen)
         {
            LogError("Failed to send data, net error: %d", util::fetchNetError());
            break;
         }
         sent += sendLen;
      }
   }

   void tcpConnection::recv(char* buffer, const uint toRecv, uint &recvLen)
   {
      INSPIRE_ASSERT(NULL != buffer, "buffer cannot be NULL");
      recvLen = 0;
      while (recvLen < toRecv)
      {
         int len = ::recv(_fd, buffer, toRecv - recvLen, 0);
         if (0 == len)
         {
            LogError("peer unexpected shutdown");
            break;
         }
         recvLen += len;
      }
   }

   void tcpConnection::close()
   {
      if (INVALID_SOCKET != _fd)
      {
         ::closesocket(_fd);
      }
      memset(&_addr, 0, sizeof(_addr));
      _port = 0 ;
   }
}