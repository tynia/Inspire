#ifndef _INSPIRE_NET_TCP_CONNECTION_H_
#define _INSPIRE_NET_TCP_CONNECTION_H_

#include "tcpconnection.h"
#include "event/eventhandler.h"

namespace inspire {

   class COStream;
   class CEvent;

   class Connection : public tcpConnection, public INetEventHandler
   {
   public:
      Connection(const unsigned int port);
      Connection(const char* ip, const unsigned int port);
      Connection(const int sock);
      Connection(const Connection& rhs);
      virtual ~Connection();

   public:
      virtual void init();
      virtual void accept(int& fd, sockaddr_in& addr);

      virtual void sendEvent(CEvent& ev);
      virtual void recvEvent(CEvent& ev);

   protected:
      void _recvLen(char* buffer, unsigned int recvLen);
   };
}
#endif