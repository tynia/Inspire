#ifndef _INSPIRE_NET_ASYNC_H_
#define _INSPIRE_NET_ASYNC_H_

#include "util/inspire.h"
#include "tcpconnection.h"
#include "event/eventhandler.h"

namespace inspire {

   class asyncConnection
   {
   public:
      virtual ~asyncConnection() {}

      virtual void asyncWrite(CEvent& ev) = 0;
      virtual void OnRead(const CEvent& ev) = 0;

   protected:
      int initialize();

   };
}
#endif