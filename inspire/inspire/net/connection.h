#ifndef _INSPIRE_NET_CONNECTION_H_
#define _INSPIRE_NET_CONNECTION_H_

#include "inspire.h"

namespace inspire {

   class IConnection
   {
   public:
      IConnection();
      IConnection(const int socket);
      virtual ~IConnection();

      const int socket() const;
      void close();

   protected:
      int _fd;    // socket
   };
}
#endif