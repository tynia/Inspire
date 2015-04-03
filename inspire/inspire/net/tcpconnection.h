#ifndef _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_
#define _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_

#include "inspire.h"

namespace inspire {

   class tcpConnection
   {
   public:
      tcpConnection(const unsigned int port);
      tcpConnection(const char* ip, const unsigned int port);
      tcpConnection(const int sock);
      tcpConnection(const tcpConnection& conn);
      virtual ~tcpConnection();

      const int socket() const { return _fd; }
      const int64 id() const { return _id; }
      void bindAndListen(const unsigned int maxConn = 10);
      
   public:
      // interface impl by derived class
      virtual void init() = 0;
      virtual void accept(int& fd, sockaddr_in& addr) = 0;

   protected:
      void _initAddr(sockaddr_in& addr);
      void _initAddr(const char* ip, const unsigned int port);
      void bind();
      void listen(const unsigned int maxConn = 10);
      void connect();
      void close();

   protected:
      int   _fd;
      int64 _id;
      unsigned int _port;  // port for local
      sockaddr_in  _addr;  // addr for peer
   };
}
#endif