#ifndef _INSPIRE_NET_ASYNC_CONNECTION_H_
#define _INSPIRE_NET_ASYNC_CONNECTION_H_

#include "baseConnection.h"

namespace inspire {

   class CEvent;
   class IOService;

   class asyncConnection : public baseConnection
   {
   public:
      asyncConnection();

      asyncConnection(int sock);

      virtual ~asyncConnection();

      int initialize();

      int doWrite(const char* data, const uint len);

      int doRead(char* buffer, uint64 bufferLen, uint64& readLen);

      int doAccept(asyncConnection& conn);

      int listenOn(const uint port);
   };
}
#endif