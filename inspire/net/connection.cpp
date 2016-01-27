#include "connection.h"

namespace inspire {

   Connection::Connection() : _fd(INVALID_FD)
   {
      ::memset(&_addr, 0, sizeof(endpoint));
   }

   Connection::Connection(int sock) : _fd(sock)
   {
      INSPIRE_ASSERT(INVALID_FD == _fd, "try to init connection using invalid socket");
   }

   bool Connection::alive()
   {
      if (INVALID_FD == _fd)
      {
         return false;
      }

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

   void Connection::close()
   {
      if (INVALID_FD != _fd)
      {
         ::closesocket(_fd);
         _fd = INVALID_FD;
      }
   }

}