#ifndef _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_
#define _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_

#include "inspire.h"

namespace inspire {

   class tcpConnection
   {
   public:
      tcpConnection();
      tcpConnection(const char* ip, const uint port);
      tcpConnection(const int sock);
      tcpConnection(const tcpConnection& conn);
      virtual ~tcpConnection();

      const int native() const { return _fd; }
      bool connected();
      void connect(const char* ip, const uint port);
      void send(const char* data, const uint len);
      void recv(char* buffer, const uint buflen, uint &recvLen);
      void close();

   protected:
      void bind();
      void listen(const uint maxConn = 20);
      void accept(int& fd, sockaddr_in& addr);

   protected:
      void _initAddr(sockaddr_in& addr);
      void _initAddr(const char* ip, const uint port);
      void _init();

   protected:
      int   _fd;
      uint  _port;  // port for local
      sockaddr_in _addr;
   };
}
#endif