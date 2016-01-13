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
   inline bool initializeNet()
   {
      int rc = NO_ERROR;
#ifdef _WIN32
      static bool initialized = false;
      // init
      WSADATA wsaData;
      if (!initialized)
      {
         rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
         if (NO_ERROR != rc)
         {
            //LogError
            return false;
         }
         initialized = true;
      }
#endif
      return true;
   }

   /**
    * return network error
    */
   inline int netError()
   {
#ifdef _WIN32
      return WSAGetLastError();
#else
      return errno;
#endif
   }
}
#endif