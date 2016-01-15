#ifndef _INSPIRE_NET_SERVER_CONNECTION_H_
#define _INSPIRE_NET_SERVER_CONNECTION_H_

#include "connection.h"

namespace inspire {

   class CEvent;

   typedef Connection*(*ACCEPT_CALLBACK)(Connection*);

   class servConnection : protected Connection
   {
   public:
      servConnection();
      virtual ~servConnection();

   public:
      int  start(const uint port, const uint maxconn, ACCEPT_CALLBACK cb = NULL);
      void stop() { _stop = true; }
      bool running() const { return !_stop; }
      int  send(CEvent& ev);
      int  recv(CEvent& ev);

   private:
      int  runLoop();
      Connection* cbAccept(Connection* conn) { return NULL; }

   private:
      bool _stop;
      ACCEPT_CALLBACK _cb;
      std::set<Connection*> _conn;
   };
}
#endif