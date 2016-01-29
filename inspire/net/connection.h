#ifndef _INSPIRE_NET_CONNECTION_H_
#define _INSPIRE_NET_CONNECTION_H_

#include "endpoint.h"

namespace inspire {

   class Connection
   {
   public:
      const int native() const { return _fd; }

      const char* toString() const { return _addr.toString().c_str(); }

      bool alive();

      void close();

   protected:
      Connection();

      Connection(int sock);

      virtual ~Connection() { close(); }

   protected:
      int _fd;
      endpoint _addr;
   };
}
#endif