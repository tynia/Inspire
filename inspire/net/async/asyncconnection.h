#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "connection.h"

namespace inspire {

   class CEvent;
   class IOService;

   class asyncConnection : public Connection
   {
   public:
      asyncConnection();

      asyncConnection(int fd);

      virtual ~asyncConnection();

      int initialize();

      int doWrite(CEvent& ev);

      int doRead(const CEvent& ev);

      int doAccept(asyncConnection& conn);

      int listenOn(const uint port);
   };
}
#endif