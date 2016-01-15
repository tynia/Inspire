#include "servconnection.h"

namespace inspire {

   servConnection::servConnection() : _stop(true)
   {}

   servConnection::~servConnection()
   {}

   int servConnection::start(const uint port, const uint maxconn, ACCEPT_CALLBACK cb)
   {
      int rc = 0;
      rc = initialize();
      if (rc)
      {
         LogError("Failed to init socket, errno: %d", fetchNetError());
         return rc;
      }

      rc = bind(port, _addr);
      if (rc)
      {
         LogError("Failed to bind on port: %d, errno: %d", port, fetchNetError());
         return rc;
      }

      rc = listen(maxconn);
      if (rc)
      {
         LogError("Failed to listen at socket, errno: %d", fetchNetError());
         return rc;
      }

      return runLoop();
   }

   int servConnection::send(CEvent& ev)
   {
      return Connection::send(ev);
   }

   int servConnection::recv(CEvent& ev)
   {
      return Connection::recv(ev);
   }

   int servConnection::runLoop()
   {
      while (running())
      {
         endpoint remote;
         int fd = accept(_fd, remote);
         if (SOCKET_ERROR == fd)
         {
            LogError("Failed to accept a remote connection, errno: %d", fetchNetError());
            continue;
         }

         Connection* conn = new Connection((void*)this, fd, remote);
         if (NULL == conn)
         {
            LogError("Failed to allocate connection object, out of memory");
            return NULL;
         }

         _conn.insert(conn);

         if (NULL != _cb)
         {
            cbAccept(conn);
         }
         else
         {
            _cb(conn);
         }
      }
   }
}