#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "async/async.h"
#include "tcpconnection.h"

namespace inspire {

   class AsyncConnection : public IAsyncConnection
   {
   public:
      AsyncConnection(const uint port);
      AsyncConnection(const char* ip, const uint port);
      AsyncConnection(const int sock);
      AsyncConnection(const AsyncConnection& rhs);
      virtual ~AsyncConnection();

      virtual void init();

      virtual void accept(int& fd, sockaddr_in& addr);

      virtual void sendEvent(CEvent& ev);

      virtual void onEvent(CEvent& ev);

   private:
      //IOService* _hIOCP;
   };
}
#endif