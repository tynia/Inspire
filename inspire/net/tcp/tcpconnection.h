#ifndef _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_
#define _INSPIRE_NET_INTERFACE_TCP_CONNECTION_H_

#include "IConnection.h"

namespace inspire {

   class tcpConnection : public IConnection
   {
   public:
      tcpConnection();
      tcpConnection(const int sock);
      virtual ~tcpConnection();

      int writeTo(CEvent& ev);
      int readFrom(CEvent& ev);

   protected:
      int   _fd;
      uint  _port;  // port for local
      sockaddr_in _addr;
   };
}
#endif