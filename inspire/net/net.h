#ifndef _INSPIRE_NET_BASE_H_
#define _INSPIRE_NET_BASE_H_

#include "util/inspire.h"
#include "util/assert.h"
#include <ws2tcpip.h>

namespace inspire {

   enum
   {
      INVALID_FD = -1,
   };

   struct netEnvironment
   {
      netEnvironment()
      {
         initializeNet();
      }
   };

   /**
    * init network of windows
    */
   inline void initializeNet()
   {
      int rc = NO_ERROR;
#ifdef _WIN32
      static bool initialized = false;
      // init
      WSADATA wsaData;
      if (!initialized)
      {
         rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
         STRONG_ASSERT(NO_ERROR != rc, "Failed to init windows network environment");
         initialized = true;
      }
#endif
   }

   /**
    * return network error
    */
   inline int fetchNetError()
   {
#ifdef _WIN32
      return WSAGetLastError();
#else
      return errno;
#endif
   }
}
#endif