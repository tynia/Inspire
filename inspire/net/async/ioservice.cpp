#include "ioservice.h"
#include "assert.h"
#include "async.h"
#include "threadentity.h"
#include "threadMgr.h"
#include "entry/entry.h"
#include "overlappedMgr.h"
#include "net.h"
#include "connection.h"

namespace inspire {

   IOService::IOService() : _stopService(true), _hIOCP(NULL), _conn(NULL)
   {
      
   }

   IOService::~IOService()
   {
      _conn = NULL;
   }

   void IOService::init()
   {
      // create i/o completion port
      _hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
      if (NULL == _hIOCP)
      {
         LogError("Failed to create iocp handle, errno = d%", GetLastError());
      }

      _overlappedMgr = GetOverlappedMgr();
   }

   void IOService::bind(asyncConnection* conn)
   {
      INSPIRE_ASSERT(NULL == conn, "Connection should not be NULL");
      if (NULL != conn)
      {
         _conn = conn;
         uint threadCount = (0 == threadCount ? 2 * cpuCount() : threadCount);
         HANDLE h = CreateIoCompletionPort((HANDLE)_conn->native(), _hIOCP, (ULONG_PTR)_conn->native(), threadCount);
         INSPIRE_ASSERT(_hIOCP == h, "Failed to bind IO complete port to socket");
         if (GetLastError())
         {
            LogError("Failed to bind socket to iocp handle, errno = ", GetLastError());
         }
      }
   }

   void IOService::run()
   {
      threadMgr* _threadMgr = getKernel()->getThreadMgr();
      INSPIRE_ASSERT(NULL != _threadMgr, "Failed to get thread manager");
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
      INSPIRE_ASSERT(NULL != _threadMgr, "Failed to get thread manager");
      // destroy thread
      for (int idx = 0; idx < _threadCount; ++idx)
      {
         _threadMgr->destroyEntity(_threadID[idx]);
      }
   }

   void IOService::_initWorkThread()
   {
      threadMgr* _threadMgr = getKernel()->getThreadMgr();
      INSPIRE_ASSERT(NULL != _threadMgr, "Failed to get thread manager");

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