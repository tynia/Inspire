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

   protected:
      IConnection();
      IConnection(int sock);
      virtual ~IConnection() {}

      const int native() const { return _fd; }
      bool connected() const;

   protected:
      void _initAddr();

   protected:
      int _fd;
      endpoint _remote;
      endpoint _local;
   };
}
#endif