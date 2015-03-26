#ifndef _INSPIRE_NET_TCP_CONNECTION_H_
#define _INSPIRE_NET_TCP_CONNECTION_H_

#include "connection.h"

namespace inspire {

   class COStream;
   class CEvent;

   class TCPConnection : public IConnection
   {
   public:
      TCPConnection(const unsigned int port);
      TCPConnection(const char* ip, const unsigned int port);
      TCPConnection(const int socket);
      TCPConnection(const TCPConnection& rhs);
      virtual ~TCPConnection() {}

   public:
      void bind();
      void listen();
      void connect();
      void accept(int& fd, sockaddr_in& addr);
      void sendEvent(CEvent& ev);
      void recvEvent(CEvent& ev);

   protected:
      void _init();
      void _initAddr();
      void _initAddr(const char* ip, const unsigned int port);
      void _recvLen(char* buffer, unsigned int recvLen);

   protected:
      unsigned int _port;  // port for peer
      sockaddr_in  _addr;  // addr for peer
   };
}
#endif