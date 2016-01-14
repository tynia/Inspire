#include "IConnection.h"

namespace inspire {

   IConnection::IConnection() : _fd(INVALID_FD)
   {
   }

   IConnection::IConnection(const int sock) : _fd(sock)
   {
      INSPIRE_ASSERT(INVALID_FD == _fd, "try to init connection using invalid socket");
   }

   IConnection::~IConnection()
   {
   }

   bool IConnection::alive() const
   {
      int rc = 0;
#if defined(_WINDOWS)
      rc = ::send(_fd, "", 0, 0);
      if (SOCKET_ERROR == rc)
#elif defined(_AIX)
      rc = ::send(_fd, "", 0, 0);
      if (0 == rc)
#else
      rc = ::recv(_fd, NULL, 0, MSG_DONTWAIT);
      if (0 == rc)
#endif
      {
         return false;
      }
      return true;
   }

   void IConnection::close()
   {
      if (INVALID_FD != _fd)
      {
         ::closesocket(_fd);
         _fd = INVALID_FD;
      }
   }

   int IConnection::initialize()
   {
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (INVALID_SOCKET == _fd)
      {
         int rc = fetchNetError();
         LogError("Failed to init socket, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   int IConnection::bind(const uint port, endpoint& addr)
   {
      int addrLen = sizeof(addr.addr);
      toServerEndpoint(port, addr);
      int rc = ::bind(_fd, (struct sockaddr*)&addr.addr, addrLen);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to bind socket and port, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   int IConnection::listen(const uint maxconn)
   {
      int rc = ::listen(_fd, maxconn);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to listen on socket, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   int IConnection::accept(int& fd, endpoint& remote)
   {
      int addrLen = sizeof(remote.addr);
      int rc = ::accept(fd, (struct sockaddr*)&remote.addr, &addrLen);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to accept remote client, errno: %d", rc);
         return rc;
      }
      toEndpoint(fd, &remote);
      return 0;
   }

   int IConnection::connect(const char* hostname, const uint port, endpoint& remote)
   {
      toEndpoint(hostname, port, remote);
      int addrLen = sizeof(remote.addr);
      int rc = ::connect(_fd, (struct sockaddr*)&remote.addr, addrLen);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to connect to remote server, errno: %d", rc);
         return rc;
      }

      return 0;
   }

   /*
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
            LogEvent("Received a none matched msg, id:"fmt64, *(int64*)pRecv);
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
   }*/
}