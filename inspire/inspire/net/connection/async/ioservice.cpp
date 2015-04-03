#include "ioservice.h"
#include "assert.h"
#include "async.h"

namespace inspire {

   IOService::IOService() : _conn(NULL)
   {}

   IOService::IOService(IAsyncConnection* conn) : _conn(conn)
   {}

   IOService::~IOService()
   {
      _conn = NULL;
   }

   void IOService::init(const unsigned int threadCount)
   {
      _threadCount = (0 == threadCount ? 2 * cpuCount() : threadCount);

      // create i/o completion port
      _hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, threadCount);
      if (NULL == _hIOCP)
      {
         //LogError..
      }

      _initWorkThread();
   }

   void IOService::bind(IAsyncConnection* conn)
   {
      INSPIRE_ASSERT((NULL == conn));
      if (NULL != conn)
      {
         _conn = conn;
         HANDLE h = CreateIoCompletionPort((HANDLE)_conn->socket(), _hIOCP, (ULONG_PTR)_conn->socket(), 0);
         INSPIRE_ASSERT((_hIOCP == h));
         if (GetLastError())
         {
            //LogError
         }
      }
   }

   void IOService::run()
   {
      // active thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         ResumeThread(_ctxThread[idx].hThread);
      }
   }

   void IOService::stop()
   {

   }

   void IOService::destroy()
   {
      // destroy thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         CloseHandle(_ctxThread[idx].hThread);
      }
   }

   void IOService::_initWorkThread()
   {
      _ctxThread = new threadContext[_threadCount];
      // create thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         _ctxThread[idx].hThread = (HANDLE)_beginthreadex(NULL, 0, /*callback*/NULL, NULL, CREATE_SUSPENDED, NULL);
         if (INVALID_HANDLE_VALUE == _ctxThread[idx].hThread)
         {
            //LogError
         }
      }
   }

}