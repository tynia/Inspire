#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "endpoint.h"

namespace inspire {

   class CEvent;

   class asyncConnection
   {
   public:
      asyncConnection();

      virtual ~asyncConnection();

      int doWrite(CEvent& ev);

      int doRead(const CEvent& ev);

      int doAccept(asyncConnection& conn);

      int listenOn(const uint port);

      void close();

   protected:
      endpoint   _remote;
      IOService* _hIOCP;
   };
}
#endif