#ifndef _INSPIRE_NET_ASYNC_H_
#define _INSPIRE_NET_ASYNC_H_

#include "inspire.h"
#include "tcpconnection.h"
#include "event/eventhandler.h"

namespace inspire {

   inline const DWORD cpuCount()
   {
      SYSTEM_INFO info = {} ;
      GetSystemInfo(&info);

      return info.dwNumberOfProcessors ;
   }

   class IOService;
   struct threadContext
   {
      IOService* _ioservice;
      int    idx;
      HANDLE hThread;
   };

   class IAsyncConnection : public tcpConnection, public INetAsyncEventHandler
   {
   public:
      IAsyncConnection(const int port) : tcpConnection(port)
      {}
      IAsyncConnection(const char* ip, const uint port) : tcpConnection(ip, port)
      {}
      IAsyncConnection(const int sock) : tcpConnection(sock)
      {}
      IAsyncConnection(const IAsyncConnection& rhs) : tcpConnection(rhs)
      {}
      virtual ~IAsyncConnection() {}
   };
}
#endif