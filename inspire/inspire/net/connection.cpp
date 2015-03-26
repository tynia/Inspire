#include "connection.h"

namespace inspire {

   IConnection::IConnection() : _fd(INVALID_SOCKET)
   {
   }

   IConnection::IConnection(const int socket) : _fd(socket)
   {
   }

   IConnection::~IConnection()
   {
      close();
   }

   const int IConnection::socket() const
   {
      return _fd;
   }

   void IConnection::close()
   {
      if (INVALID_SOCKET != _fd)
      {
         ::closesocket(_fd);
      }
   }
}