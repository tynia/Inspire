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

   /**
    * init network of windows
    */
   inline bool netok()
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

   /**
    * init remote address for connecting
    */
   inline bool initRemoteAddr(const char* ip, const unsigned port, sockaddr_in& addr)
   {
      memset(&addr, 0, sizeof(sockaddr_in));

      if (NULL == ip || port <= 1024)
      {
         return false;
      }

      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip);
      addr.sin_port = htons(port);

      return true;
   }

   /**
    * init local address for bind
    */
   inline bool initLocalAddr(const unsigned port, sockaddr_in& addr)
   {
      if (port <= 1024)
      {

         return false;
      }
      STRONG_ASSERT(port > 1024, "port");
      memset(&addr, 0, sizeof(sockaddr_in));
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      addr.sin_port = htons(port);

      return true;
   }

   /**
    * get local net address by socket
    */
   inline bool getLocalAddr(int* fd, sockaddr_in& addr)
   {
      memset(&addr, 0, sizeof(sockaddr_in));

      if (NULL == fd)
         return false;

      socklen_t len = sizeof(addr);
      int rc = getsockname(*fd, (sockaddr*)&addr, &len);
      if (rc)
      {
         return false;
      }
      return true;
   }

   /**
    * get peer address by socket
    */
   inline bool getPeerAddr(int* fd, sockaddr_in& addr)
   {
      memset(&addr, 0, sizeof(sockaddr_in));
      if (NULL == fd)
      {
         return false;
      }

      socklen_t len = sizeof(addr);
      int rc = getpeername(*fd, (sockaddr*)&addr, &len);
      if (rc)
      {
         return false;
      }
      return true;
   }

   /**
    * get port from net address
    */
   inline const unsigned short port(sockaddr_in* addr)
   {
      return ntohs(addr->sin_port);
   }

   /**
    * get ip from net address
    */
   inline const unsigned long ip(sockaddr_in* addr)
   {
      return ntohl(addr->sin_addr.s_addr);
   }
}
#endif