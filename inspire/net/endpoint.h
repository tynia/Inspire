#ifndef _INSPIRE_NET_ENDPOINT_H_
#define _INSPIRE_NET_ENDPOINT_H_

#include "net.h"

namespace inspire {

   struct endpoint
   {
      sockaddr_in addr;

      endpoint()
      {
         memset(&addr, 0, sizeof(addr));
      }

      const uint64 ip() const
      {
         return ntohl(addr.sin_addr.s_addr);
      }

      const ushort port() const
      {
         return ntohs(addr.sin_port);
      }

      std::string toString() const
      {
         std::string str;
         str = inet_ntoa(addr.sin_addr);
         str += ":";
         str += ntohs(addr.sin_port);

         return str;
      }
   };

   inline void toServerEndpoint(uint port, endpoint& ep)
   {
      memset(&ep.addr, 0, sizeof(sockaddr_in));
      ep.addr.sin_family = AF_INET;
      ep.addr.sin_addr.s_addr = htonl(INADDR_ANY);
      ep.addr.sin_port = htons(port);
   }

   inline bool toEndpoint(int fd, endpoint* remote, endpoint* local)
   {
      if (INVALID_SOCKET == fd)
      {
         return false;
      }

      int len = sizeof(sockaddr_in);
      // fetch remote addr from socket
      if (NULL != remote)
      {
         int rc = getpeername(fd, (struct sockaddr*)&remote->addr, &len);
         if (rc)
         {
            return false;
         }
      }
      // fetch local addr from socket
      if (NULL != local)
      {
         int rc = getsockname(fd, (struct sockaddr*)&local->addr, &len);
         if (rc)
         {
            return false;
         }
      }

      return true;
   }

   inline void toEndpoint(const char* hostname, uint port, endpoint& ep)
   {
      struct hostent* hp;
#ifdef _WIN32
      if ((hp = gethostbyname(hostname)))
#elif _LINUX
      struct hostent hent;
      struct hostent* ret = NULL;
      int error = 0;
      char hbuf[8192] = { 0 };
      hp = &hent;
      if ((0 == gethostbyname_r(hostname, &hp, hbuf, sizeof(hbuf), &ret, &error))
          && NULL != ret)
#elif _AIX
      struct host hent;
      struct hostent_data hdata;
      hp = &hent;
      if ((0 == gethostbyname_r(hostname, hp, &hdata)))
#endif
      {
         uint* pAddr = (uint*)hp->h_addr_list[0];
         if (pAddr)
         {
            ep.addr.sin_addr.s_addr = *pAddr;
         }
      }
      else
      {
         ep.addr.sin_addr.s_addr = inet_addr(hostname);
      }
      ep.addr.sin_port = htons(port);
   }
}
#endif
