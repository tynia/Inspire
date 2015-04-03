#include "tcpconnection.h"
#include "helper/nethelper.h"

namespace inspire {

   tcpConnection::tcpConnection(const unsigned int port) : _id(0), _port(port)
   {
      init();
      memset(&_addr, 0, sizeof(_addr));
   }

   tcpConnection::tcpConnection(const char* ip, const unsigned int port) : _id(0), _port(0)
   {
      init();
      _initAddr(ip, port);
   }

   tcpConnection::tcpConnection(const int sock) : _fd(sock)
   {
   }

   tcpConnection::tcpConnection(const tcpConnection& rhs)
   {
      _fd = rhs._fd;
      _port = rhs._port;
      _id = rhs._id;
      memcpy(&_addr, &rhs._addr, sizeof(_addr));
   }

   tcpConnection::~tcpConnection()
   {
      close();
   }

   void tcpConnection::bindAndListen(const unsigned int maxConn /*= 10*/)
   {
      bind();

      listen(maxConn);
   }

   void tcpConnection::bind()
   {
      sockaddr_in local;
      _initAddr(local);

      int rc = ::bind(_fd, (sockaddr*)&local, sizeof(local));
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to bind on port: %d, rc = %d", _port, rc);
      }
   }

   void tcpConnection::listen(const unsigned int maxConn /*= 10*/)
   {
      int rc = ::listen(_fd, maxConn);
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to listen, rc = %d", rc);
      }
   }

   void tcpConnection::connect()
   {
      int rc = ::connect(_fd, (struct sockaddr*)&_addr, sizeof(sockaddr_in));
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to connect to %s:%d", getIP(&_addr), getPort(&_addr));
      }
   }

   void tcpConnection::close()
   {
      if (INVALID_SOCKET != _fd)
      {
         ::closesocket(_fd);
      }
   }

   void tcpConnection::_initAddr(sockaddr_in& addr)
   {
      memset(&addr, 0, sizeof(sockaddr_in));
      addr.sin_family = AF_INET;
      addr.sin_port = ::htons(_port);
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
   }

   void tcpConnection::_initAddr(const char* ip, const unsigned int port)
   {
      _addr.sin_family = AF_INET;
      _addr.sin_port = ::htons(port);
      inet_pton(AF_INET, ip, &_addr.sin_addr.s_addr);
      //_addr.sin_addr.s_addr = inet_addr(ip);
   }
}