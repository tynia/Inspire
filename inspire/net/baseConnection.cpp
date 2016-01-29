#include "baseConnection.h"

namespace inspire {

   baseConnection::baseConnection() : _fd(INVALID_FD)
   {
      ::memset(&_addr, 0, sizeof(endpoint));
   }

   baseConnection::baseConnection(int sock) : _fd(sock)
   {
      INSPIRE_ASSERT(INVALID_FD == _fd, "try to init baseConnection using invalid socket");
   }

   bool baseConnection::alive()
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

   void baseConnection::close()
   {
      if (INVALID_FD != _fd)
      {
         ::closesocket(_fd);
         _fd = INVALID_FD;
      }
   }

}