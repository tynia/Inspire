#ifndef _INSPIRE_NET_IO_SERVICE_H_
#define _INSPIRE_NET_IO_SERVICE_H_

#include "inspire.h"

namespace inspire {

   class IAsyncConnection;

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

   protected:
      void _initWorkThread();
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