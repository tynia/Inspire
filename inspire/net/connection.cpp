#include "connection.h"

namespace inspire {

   Connection::Connection()
   {
   }

   Connection::Connection(const int sock, const endpoint& remote) : tcpConnection(sock)
   {
      memmove(&_addr, &remote, sizeof(remote));
   }

   Connection::~Connection()
   {
      close();
   }

   int Connection::connect(const char* hostname, const uint port)
   {
      int rc = tcpConnection::connect(hostname, port, _addr);
      if (SOCKET_ERROR == rc)
      {
         LogError("try to connect to remote server, errno: %d", fetchNetError());
         return rc;
      }

      return 0;
   }

   int Connection::send(CEvent& ev)
   {
      NOStream nos;
      ev.saveStream(nos);

      return writeTo(nos.data(), nos.size());
   }

   int Connection::recv(CEvent& ev)
   {
      char buffer[8192] = { 0 };
      uint len = 0;
      int rc = readFrom(buffer, 8192, len);
      if (rc)
      {
         LogError("Error occurs when receiving msg, erron: %d", fetchNetError());
         return rc;
      }

      NIStream nis(buffer, len);
      ev.loadStream(nis)

      return rc;
   }

}