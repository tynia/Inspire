#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "async/async.h"

namespace inspire {

   class asyncConnection
   {
   public:
      asyncConnection();
      virtual ~asyncConnection();

      virtual void asyncWrite(CEvent& ev);
      virtual void OnRead(const CEvent& ev);

      virtual void init();

      virtual void accept(int& fd, sockaddr_in& addr);

      virtual void sendEvent(CEvent& ev);

      virtual void onEvent(CEvent& ev);

   private:
      //IOService* _hIOCP;
   };
}
#endif