#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "event/eventhandler.h"
#include "connection/connection.h"

namespace inspire {

   class IAsyncConnection : public INetEventHandler, public IConnection
   {
   public:
      virtual ~IAsyncConnection() {}

      virtual void init() = 0;

      virtual void bind() = 0;

      virtual void listen() = 0;

      virtual void connect() = 0;

      virtual void accept() = 0;

   protected:
      int _fd;
      int64 _id;
   };
}
#endif