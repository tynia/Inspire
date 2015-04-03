#ifndef _INSPIRE_NET_CONNECTION_H_
#define _INSPIRE_NET_CONNECTION_H_

#include "inspire.h"

namespace inspire {

   class IConnection
   {
   public:
      virtual ~IConnection();

      virtual const int socket() const = 0;

      virtual const int64 id() const = 0;
   };
}
#endif