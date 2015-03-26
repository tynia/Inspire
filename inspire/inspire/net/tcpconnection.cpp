#include "tcpconnection.h"
#include "iostream.h"
#include "eventid.h"
#include "event.h"

namespace inspire {

   static const unsigned int UINT_SIZE = sizeof(unsigned int);

   TCPConnection::TCPConnection(const unsigned int port) : IConnection(port)
   {
      _init();
   }

   TCPConnection::TCPConnection(const char* ip, const unsigned int port) : IConnection()
   {
      _init();
      _initAddr(ip, port);
   }

   TCPConnection::TCPConnection(const int socket) : IConnection(socket)
   {
   }

   TCPConnection::TCPConnection(const TCPConnection& rhs) : IConnection(rhs)
   {
   }

   void TCPConnection::bind()
   {
      sockaddr_in local;
      local.sin_family = AF_INET;
      local.sin_port = ::htons(_port);
      local.sin_addr.s_addr = htonl(INADDR_ANY);

      int rc = ::bind(_fd, (sockaddr*)&local, sizeof(local));
      if (SOCKET_ERROR == rc)
      {
         //LogError
      }
   }

   void TCPConnection::listen()
   {
      int rc = ::listen(_fd, 5);
      if (SOCKET_ERROR == rc)
      {
         //LogError(...)
      }
   }

   void TCPConnection::connect()
   {
      int rc = ::connect(_fd, (struct sockaddr*)&_addr, sizeof(sockaddr_in));
      if (SOCKET_ERROR == rc)
      {
         //LogError(...)
      }
   }

   void TCPConnection::accept(int& fd, sockaddr_in& addr)
   {
      int addrLen = sizeof(sockaddr_in);
      int rc = ::accept(fd, (struct sockaddr*)&addr, &addrLen);
      if (SOCKET_ERROR == rc)
      {
         //LogError(...)
      }
   }

   void TCPConnection::sendEvent(CEvent& ev)
   {
      COStream os;
      ev.saveStream(os);

      size_t len = os.size();
      const char* pSend = os.data();
      int sendLen = 0;

      while (len > 0)
      {
         sendLen = ::send(_fd, pSend, len, 0);
         if (SOCKET_ERROR == sendLen)
         {
            //LogError
            return;
         }
         len -= sendLen;
         pSend += sendLen;
      }
   }

   void TCPConnection::recvEvent(CEvent& ev)
   {
      CIStream is;
      int msgLen = 0;
      int len = 0;

      int eventID = EVENT_INVALID;
      while (eventID != ev.getEventID())
      {
         _recvLen((char*)&len, UINT_SIZE);
         msgLen = ENDIAN::N2H(len);

         is.reverse(msgLen);
         *(unsigned int*)is.data() = msgLen;

         char* pRecv = is.data() + UINT_SIZE;
         _recvLen(pRecv, msgLen - UINT_SIZE);

         if (*(int64*)pRecv != eventID)
         {
            // LogWarning(...received a error msg)
            continue;
         }
      }

      ev.loadStream(is);
   }

   void TCPConnection::_init()
   {
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (INVALID_SOCKET == _fd)
      {
         //LogError
         return;
      }
   }

   void TCPConnection::_initAddr()
   {
      sockaddr_in local;
      memset(&local, 0, sizeof(sockaddr_in));
      local.sin_family = AF_INET;
      local.sin_port = ::htons(_port);
      local.sin_addr.s_addr = htonl(INADDR_ANY);
   }

   void TCPConnection::_initAddr(const char* ip, const unsigned int port)
   {
      _addr.sin_family = AF_INET;
      _addr.sin_port = ::htons(port);
      _addr.sin_addr.s_addr = inet_addr(ip);
   }

   void TCPConnection::_recvLen(char* buffer, unsigned int recvLen)
   {
      int len = 0;
      char* pRecv = NULL;
      while (recvLen > 0)
      {
         len = ::recv(_fd, (char*)pRecv, recvLen, 0);
         if (SOCKET_ERROR == len)
         {
            //LogError
            return;
         }
         recvLen -= len;
         pRecv += len;
      }
   }
}