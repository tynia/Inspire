#ifndef _INSPIRE_NET_TCP_CONNECTION_H_
#define _INSPIRE_NET_TCP_CONNECTION_H_

#include "connection.h"

namespace inspire {

   class COStream;
   class CEvent;

   class ITCPConnection : IConnection
   {
   public:
      virtual ~ITCPConnection() {};

      virtual void bind() = 0;

      virtual void listen() = 0;

      virtual void connect() = 0;

      virtual void accept(int& fd, sockaddr_in& addr) = 0;

      virtual void send(CEvent& ev) = 0;

      virtual void recv(CEvent& ev) = 0;
   };

   class TCPConnection : public ITCPConnection
   {
   public:
      TCPConnection(const unsigned int port);
      TCPConnection(const char* ip, const unsigned int port);
      TCPConnection(const int socket);
      TCPConnection(const TCPConnection& rhs);
      virtual ~TCPConnection() {}

   public:
      virtual const int socket() const;
      virtual const int64 id() const;
      virtual void bind();
      virtual void listen();
      virtual void connect();
      virtual void accept(int& fd, sockaddr_in& addr);
      void sendEvent(CEvent& ev);
      void recvEvent(CEvent& ev);

   protected:
      void _init();
      void _initAddr();
      void _initAddr(const char* ip, const unsigned int port);
      void _recvLen(char* buffer, unsigned int recvLen);

   protected:
      int          _fd;
      int64        _id;
      unsigned int _port;  // port for peer
      sockaddr_in  _addr;  // addr for peer
   };
}
#endif