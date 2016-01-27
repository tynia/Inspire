#ifndef _INSPIRE_NET_ASYNC_OVERLAPPED_H_
#define _INSPIRE_NET_ASYNC_OVERLAPPED_H_

#include "network.h"
#include "endpoint.h"

namespace inspire {

   enum IOEvent
   {
      IOE_INVALID,
      IOE_ACCEPT,
      IOE_READ,
      IOE_WRITE,
   };

   enum
   {
      MAX_BUFFER_SIZE = 8192,
   };

   struct overlappedContext : OVERLAPPED
   {
      //OVERLAPPED        overlapped;
      IOEvent           ioeType;
      IAsyncConnection* conn;
      WSABUF            wsaBuffer;
      char              buffer[MAX_BUFFER_SIZE];

      overlappedContext() : ioeType(IOE_INVALID), conn(NULL)
      {
         zero();
         wsaBuffer.buf = buffer;
      }

      void zero()
      {
         memset(buffer, 0, MAX_BUFFER_SIZE);
         wsaBuffer.len = MAX_BUFFER_SIZE;
      }
   };
}
#endif