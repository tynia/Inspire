#ifndef _INSPIRE_NET_IO_SERVICE_H_
#define _INSPIRE_NET_IO_SERVICE_H_

#include "inspire.h"

namespace inspire {

   class IAsyncConnection;

   enum IOEvent
   {
      IOE_INVALID,
      IOE_ACCEPT,
      IOE_RECV,
      IOE_SEND,
   };

   static const unsigned int MAX_BUFFER_SIZE = 8192;
   static const unsigned int MAX_POST_ACCEPT = 20;

   struct OverlappedContext
   {
      IOEvent    _eventType;
      OVERLAPPED _overlapped;
      int        _fd;
      WSABUF     _wsabuf;
      char       _buffer[MAX_BUFFER_SIZE];

      OverlappedContext() : _eventType(IOE_INVALID), _fd(INVALID_SOCKET)
      {
         ZeroMemory(&_overlapped, sizeof(_overlapped));  
         ZeroMemory(_buffer,MAX_BUFFER_SIZE);
         _wsabuf.buf = _buffer;
         _wsabuf.len = MAX_BUFFER_SIZE;
      }

      void zero()
      {
         ZeroMemory(_buffer, MAX_BUFFER_SIZE);
      }
   };

   class IThreadMgr;
   class IOService
   {
   public:
      IOService(IThreadMgr* threadMgr);
      virtual ~IOService();

      void init(const unsigned int threadCount = 0);

      void bind(IAsyncConnection* conn);

      void run();

      void stop();

      void destroy();

      void associate(OverlappedContext* ctx);

      void postEvent(OverlappedContext* ctx, IOEvent ioe);

   protected:
      void _initWorkThread();
      void _doAccept();
      void _doSend();
      void _doRecv();

   protected:
      IAsyncConnection* _conn;
      IThreadMgr*       _threadMgr;
      unsigned int  _threadCount;
      LPFN_ACCEPTEX _lpfnAcceptEx;
#ifdef _WIN32
      HANDLE _hIOCP;
#else
#endif
      int64* _threadID;
   private:
      OverlappedContext _overlappedContext[MAX_POST_ACCEPT];
   };
}
#endif