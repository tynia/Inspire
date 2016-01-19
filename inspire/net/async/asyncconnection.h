#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "endpoint.h"

namespace inspire {

   class CEvent;
   class IOService;

   class asyncConnection
   {
   public:
      asyncConnection();

      virtual ~asyncConnection();

      IOService* ioservice() const { return _IOService; }

      int initialize();

      int doWrite(CEvent& ev);

      int doRead(const CEvent& ev);

      int doAccept(asyncConnection& conn);

      int listenOn(const uint port);

      void close();

   protected:
      int _fd;
      endpoint   _remote;
      IOService* _IOService;
   };
}
#endif