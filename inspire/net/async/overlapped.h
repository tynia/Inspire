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

   class asyncConnection;
   struct overlappedContext
   {
      OVERLAPPED       overlapped;
      IOEvent          ioeType;
      asyncConnection* conn;
      WSABUF           wsaBuffer;
      char             buffer[MAX_BUFFER_SIZE];

      overlappedContext() : ioeType(IOE_INVALID), conn(NULL)
      {
         zero();
         wsaBuffer.buf = buffer;
      }

//       ~overlappedContext()
//       {
//          zero();
//          wsaBuffer.buf = buffer;
//       }

      void zero()
      {
         memset(&overlapped, 0, sizeof(OVERLAPPED));
         memset(buffer, 0, MAX_BUFFER_SIZE);
         wsaBuffer.len = MAX_BUFFER_SIZE;
      }
   };

   class EventHandler
   {
   public:
      virtual ~EventHandler() {}

      virtual int handle(overlappedContext* overlapped) = 0;
   };
}
#endif