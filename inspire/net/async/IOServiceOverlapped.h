#ifndef _INSPIRE_NET_ASYNC_IO_H_
#define  _INSPIRE_NET_ASYNC_IO_H_

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

   struct IOServiceOverlapped : OVERLAPPED
   {
      IOEvent  ioeType;
      endpoint remote;
      WSABUF   wsaBuffer;
      char     buffer[MAX_BUFFER_SIZE];
   };
}
#endif