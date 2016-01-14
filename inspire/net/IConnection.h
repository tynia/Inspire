#ifndef _INSPIRE_NET_INTERFACE_CONNECTION_H_
#define _INSPIRE_NET_INTERFACE_CONNECTION_H_

#include "endpoint.h"

namespace inspire {

   class CEvent;

   class IConnection
   {
   public:
      const int native() const { return _fd; }
      bool alive() const;
      void close();

   protected:
      int initialize();
      int bind(const uint port, endpoint& addr);
      int listen(const uint maxconn = 10);
      int accept(int& fd, endpoint& remote);
      int connect(const char* hostname, const uint port, endpoint& remote);

   protected:
      IConnection();
      IConnection(const int sock);
      virtual ~IConnection() {}

   protected:
      int _fd;
   };
}
#endif