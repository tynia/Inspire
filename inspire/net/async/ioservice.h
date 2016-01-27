#ifndef _INSPIRE_NET_IO_SERVICE_H_
#define _INSPIRE_NET_IO_SERVICE_H_

#include "network.h"
#include "util/inspire.h"

namespace inspire {

   class asyncConnection;
   enum IOEvent;
   class IOServiceOverlapped;

   class IOService
   {
   public:
      IOService();
      virtual ~IOService();

      void init();

      void bind(asyncConnection* conn);

      void run();

      void stop();

      void destroy();

      void associate(IOServiceOverlapped* pOverlapped);

      void postEvent(IOServiceOverlapped* pOverlapped, IOEvent ioe);

      bool stopped() const;

   protected:
      void _doAccept();
      void _doSend();
      void _doRecv();

   protected:
      bool              _stopService;
      HANDLE            _hIOCP;
      asyncConnection*  _conn;
   };
}
#endif