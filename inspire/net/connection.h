#ifndef _INSPIRE_NET_CONNECTION_H_
#define _INSPIRE_NET_CONNECTION_H_

#include "endpoint.h"
#include "tcp/tcpconnection.h"

namespace inspire {

   class CEvent;

   class Connection : public tcpConnection
   {
   public:
      Connection();
      Connection(void* owner, const int sock, const endpoint& remote);
      virtual ~Connection();

      int connect(const char* hostname, const uint port);
      int send(CEvent& ev);
      int recv(CEvent& ev);

   protected:
      endpoint _addr;
      void* _owner;
   };
}
#endif