#include "ioservice.h"
#include "assert.h"
#include "async.h"
#include "thread.h"
#include "threadMgr.h"
#include "entry/entry.h"

namespace inspire {

   IOService::IOService() : _stopService(true), _hIOCP(NULL), _threadCount(0),
                            _conn(NULL), _threadID(NULL), _lpfnAcceptEx(NULL)
   {
      
   }

   IOService::~IOService()
   {
      _conn = NULL;
      if (0 != _threadCount && NULL != _threadID)
      {
         delete [] _threadID;
         _threadID = NULL ;
      }
   }

   void IOService::init(const unsigned int threadCount)
   {
      _threadCount = (0 == threadCount ? 2 * cpuCount() : threadCount);

      // create i/o completion port
      _hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0/*threadCount*/);
      if (NULL == _hIOCP)
      {
         LogError("Failed to create iocp handle, errno = d%", GetLastError());
      }

      _initWorkThread();
   }

   void IOService::bind(IAsyncConnection* conn)
   {
      INSPIRE_ASSERT((NULL == conn));
      if (NULL != conn)
      {
         _conn = conn;
         HANDLE h = CreateIoCompletionPort((HANDLE)_conn->socket(), _hIOCP, (ULONG_PTR)_conn->socket(), _threadCount);
         INSPIRE_ASSERT((_hIOCP == h));
         if (GetLastError())
         {
            LogError("Failed to bind socket to iocp handle, errno = ", GetLastError());
         }
      }

      DWORD bytes = 0 ;
      GUID guidAcceptEx = WSAID_ACCEPTEX;  
      GUID guidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS; 
      int rc = WSAIoctl(_conn->socket(), SIO_GET_EXTENSION_FUNCTION_POINTER,
                        &guidAcceptEx, sizeof(guidAcceptEx), &_lpfnAcceptEx,
                        sizeof(_lpfnAcceptEx), &bytes, NULL, NULL) ;
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to get AcceptEx addr");
         return;
      }

      for (int idx = 0; idx < MAX_POST_ACCEPT; ++idx)
      {
         postEvent(&_overlappedContext[idx], IOE_ACCEPT);
      }
   }

   void IOService::run()
   {
      threadMgr* _threadMgr = getKernel()->getThreadMgr();
      INSPIRE_ASSERT((NULL != _threadMgr));
      _stopService = false;
      // active thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         _threadMgr->activeEntity(_threadID[idx]);
      }
   }

   void IOService::stop()
   {
      _stopService = true;
   }

   void IOService::destroy()
   {
      threadMgr* _threadMgr = getKernel()->getThreadMgr();
      INSPIRE_ASSERT((NULL != _threadMgr));
      // destroy thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         _threadMgr->destroyEntity(_threadID[idx]);
      }
   }

   void IOService::_initWorkThread()
   {
      threadMgr* _threadMgr = getKernel()->getThreadMgr();
      INSPIRE_ASSERT((NULL != _threadMgr));

      THREAD_ENTRY_TYPES t = THREAD_SERVICE_ACCEPTOR;
      
      _threadID = new int64[_threadCount];
      // create thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         int64 id = 0;
         threadEntity* entity = _threadMgr->createEntity(t, this, id);
         if (NULL == entity)
         {
            LogError("Failed to create thread entity, idx = %d", idx);
            return;
         }
         _threadID[idx] = id;
      }
   }

   void IOService::associate(OverlappedContext* ctx)
   {
      HANDLE h = CreateIoCompletionPort((HANDLE)ctx->_fd, _hIOCP, (DWORD)ctx, 0);
      if (NULL == h)
      {
         LogError("Failed to associate with iocp, errno = %d", WSAGetLastError());
      }
   }

   void IOService::postEvent( OverlappedContext* ctx, IOEvent ioe )
   {
      if (IOE_ACCEPT == ioe)
      {
         DWORD   dwBytes = 0;
         WSABUF* wsabuf  = &ctx->_wsabuf;
         OVERLAPPED* pOverlapped = &ctx->_overlapped;
         ctx->zero();
         ctx->_eventType = ioe;

         ctx->_fd = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
         if (INVALID_SOCKET == ctx->_fd)
         {
            LogError("Failed to init acceptable socket, errno = %d", WSAGetLastError());
            return;
         }

         int rc = _lpfnAcceptEx( _conn->socket(), ctx->_fd, wsabuf->buf,
                                 wsabuf->len - ((sizeof(SOCKADDR_IN) + 16) * 2),
                                 sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &dwBytes, pOverlapped);
         if (SOCKET_ERROR == rc && WSA_IO_PENDING != WSAGetLastError())
         {
            LogError("Failed to accept remote session");
            return;
         }
      }
      else if (IOE_SEND == ioe)
      {
         
      }
      else if (IOE_RECV == ioe)
      {
         DWORD   dwFlags = 0;
         DWORD   dwBytes = 0;
         WSABUF* wsabuf  = &ctx->_wsabuf;
         OVERLAPPED* pOverlapped = &ctx->_overlapped;
         ctx->zero();
         ctx->_eventType = ioe;

         int nBytesRecv = WSARecv( ctx->_fd, wsabuf, 1, &dwBytes, &dwFlags, pOverlapped, NULL );
         if ((SOCKET_ERROR == nBytesRecv) && (WSA_IO_PENDING != WSAGetLastError()))
         {
            LogError("Post RECV event error, errno = %d", WSAGetLastError());
            return;
         }
      }
      else
      {
         LogError("Error IO event post, event=%d", ioe);
      }
   }

   bool IOService::stopped() const
   {
      return _stopService;
   }

   void IOService::_doAccept()
   {

   }

   void IOService::_doSend()
   {

   }

   void IOService::_doRecv()
   {

   }

}