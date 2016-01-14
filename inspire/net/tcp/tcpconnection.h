#ifndef _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_
#define _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_

#include "IConnection.h"

namespace inspire {

   class tcpConnection// : public IConnection
   {
   public:
      tcpConnection();
      tcpConnection(const int sock);
      virtual ~tcpConnection();

      void initialize();
      void connect(const char* ip, const uint port);
      void writeTo(CEvent& ev);
      void readFrom(CEvent& ev);
      void close();


   protected:
      void bind();
      void listen(const uint maxConn = 20);
      void accept(int& fd, sockaddr_in& addr);

   protected:
      void _init();

   protected:
      int   _fd;
      uint  _port;  // port for local
      sockaddr_in _addr;
   };
}
#endif