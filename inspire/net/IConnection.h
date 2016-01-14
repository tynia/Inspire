#ifndef _INSPIRE_NET_INTERFACE_CONNECTION_H_
#define _INSPIRE_NET_INTERFACE_CONNECTION_H_

#include "endpoint.h"

namespace inspire {

   class CEvent;

   class IConnection
   {
   public:
      virtual void writeTo(CEvent& ev) = 0;
      virtual void readFrom(CEvent& ev) = 0;
      virtual void close();

   public:
      const int native() const { return _fd; }
      bool alive() const;

   protected:
      int initialize();
      int bind(uint port);
      int listen(uint maxconn = 10);
      int accept(int& fd, endpoint& remote);

   protected:
      IConnection();
      IConnection(int sock);
      virtual ~IConnection() {}

   protected:
      int _fd;
   };
}
#endif