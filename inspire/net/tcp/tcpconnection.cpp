#include "tcpconnection.h"

namespace inspire {
   
   tcpConnection::tcpConnection()
   {
   }

   tcpConnection::tcpConnection(const int sock) : IConnection(sock)
   {
   }

   tcpConnection::~tcpConnection()
   {
      close();
   }

   int tcpConnection::writeTo(const char* data, const uint len)
   {
      INSPIRE_ASSERT(NULL != data, "data to send cannot be NULL");
      uint pos = 0;
      while (pos < len)
      {
         int sendLen = ::send(_fd, data + pos, len - pos, 0);
         if (-1 == sendLen)
         {
            int rc = fetchNetError();
            LogError("Failed to send data, net error: %d", rc);
            return rc;
         }
         pos += sendLen;
      }
   }

   int tcpConnection::readFrom(char* buffer, const uint bufferLen, uint &recvLen)
   {
      INSPIRE_ASSERT(NULL != buffer, "buffer cannot be NULL");
      int rc = 0;
      // receive msg len first
      rc = ::recv(_fd, buffer, sizeof(int), 0);
      if (SOCKET_ERROR == rc)
      {
         rc = fetchNetError();
         LogError("Failed to receive msg size, errno: %d", rc);
         return rc;
      }

      int recvLen = rc;

      // calculate message is endian check or not
      int size = *(int*)buffer;
      if (-1 != size)
      {
         //TODO:
      }
      // receive rest after message len received
      while (recvLen < size)
      {
         int len = ::recv(_fd, buffer + recvLen, size - recvLen, 0);
         if (0 == len)
         {
            LogError("peer unexpected shutdown");
            break;
         }
         else if (-1 == len)
         {
            rc = fetchNetError();
            LogError("Network error occurs when receiving, errno: %d", rc);
            return rc;
         }

         recvLen += len;
      }
      return rc;
   }
}