#ifndef _INSPIRE_NET_IO_SERVICE_H_
#define _INSPIRE_NET_IO_SERVICE_H_

#include "inspire.h"

namespace inspire {

   class IAsyncConnection;

   enum IOEvent
   {
      IOE_ACCEPT,
      IOE_RECV,
      IOE_SEND,
   };

   class IOService
   {
   public:
      IOService();
      IOService(IAsyncConnection* ss);
      virtual ~IOService();

      void init(const unsigned int threadCount = 0);

      void bind(IAsyncConnection* ss);

      void run();

      void stop();

      void destroy();

      void associate(int& _fd);

      void postEvent(IOEvent ioe);

   protected:
      void _initWorkThread();
      void _doAccept();
      void _doSend();
      void _doRecv();

   protected:
      IAsyncConnection* _conn;
      unsigned int _threadCount;
#ifdef _WIN32
      HANDLE _hIOCP;
#else

#endif
      threadContext *_ctxThread;
   };
}
#endif