#include "tcpconnection.h"
#include "helper/util.h"

namespace inspire {

   tcpConnection::tcpConnection(const uint port) : _port(port)
   {
      _init();
      memset(&_addr, 0, sizeof(_addr));
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
      if ( !util::initNetwork() )
      {
         LogError("Init network module Failed, errno: %d", util::netError());
         return;
      }
#endif // _WIN32
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (INVALID_SOCKET == _fd)
      {
         LogError("Failed to create socket");
      }
   }

   void tcpConnection::bind()
   {
      sockaddr_in local;
      _initAddr(local);

      int rc = ::bind(_fd, (sockaddr*)&local, sizeof(local));
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to bind on port: %d, rc = %d", _port, util::netError());
      }
   }

   void tcpConnection::listen(const uint maxConn /*= 10*/)
   {
      int rc = ::listen(_fd, maxConn);
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to listen, errno = %d", util::netError());
      }
   }

   void tcpConnection::accept( int& fd, sockaddr_in& addr )
   {
      int len = sizeof(addr);
      fd = ::accept(_fd, (sockaddr*)&addr, &len);
      if (INVALID_SOCKET == fd)
      {
         LogError("accept an remote connection failed, errno: %d", util::netError());
      }
   }

   void tcpConnection::connect()
   {
      int rc = ::connect(_fd, (struct sockaddr*)&_addr, sizeof(sockaddr_in));
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to connect to %s:%d, errno: d%",
                  util::ip(&_addr), util::port(&_addr), util::netError());
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

   void tcpConnection::_initAddr(sockaddr_in& addr)
   {
      util::initLocalAddr(_port, addr);
   }

   void tcpConnection::_initAddr(const char* ip, const uint port)
   {
      util::initRemoteAddr(ip, port, _addr);
   }
}