#include "connection.h"
#include "iostream.h"
#include "event/eventid.h"
#include "event/event.h"
#include "helper/nethelper.h"

namespace inspire {

   static const unsigned int UINT_SIZE = sizeof(unsigned int);

   Connection::Connection(const unsigned int port) : tcpConnection(port)
   {
   }

   Connection::Connection(const char* ip, const unsigned int port) : tcpConnection(ip, port)
   {
   }

   Connection::Connection(const int sock) : tcpConnection(sock)
   {
   }

   Connection::Connection(const Connection& rhs) : tcpConnection(rhs)
   {
   }

   Connection::~Connection()
   {
   }

   void Connection::init()
   {
      initNetModule();
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (INVALID_SOCKET == _fd)
      {
         LogError("Failed to init socket");
      }
   }

   void Connection::accept(int& fd, sockaddr_in& addr)
   {
      int addrLen = sizeof(sockaddr_in);
      int rc = ::accept(fd, (struct sockaddr*)&addr, &addrLen);
      if (SOCKET_ERROR == rc)
      {
         LogError("Failed to accept");
      }
   }

   void Connection::sendEvent(CEvent& ev)
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
            LogError("Failed to send msg");
            return;
         }
         len -= sendLen;
         pSend += sendLen;
      }
   }

   void Connection::recvEvent(CEvent& ev)
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
            LogEvent("Received a none matched msg, id:%lld", *(int64*)pRecv);
            continue;
         }
      }

      ev.loadStream(is);
   }

   void Connection::_recvLen(char* buffer, unsigned int recvLen)
   {
      int len = 0;
      char* pRecv = buffer;
      while (recvLen > 0)
      {
         len = ::recv(_fd, (char*)pRecv, recvLen, 0);
         if (SOCKET_ERROR == len)
         {
            LogError("Failed to recv msg");
            return;
         }
         recvLen -= len;
         pRecv += len;
      }
   }
}