#ifndef _INSPIRE_NET_ENDPOINT_H_
#define _INSPIRE_NET_ENDPOINT_H_

#include "net.h"

namespace inspire {

   struct endpoint
   {
      int fd;
      sockaddr_in addr;

      endpoint() : fd(INVALID_SOCKET)
      {
         memset(&addr, 0, sizeof(addr));
      }

      endpoint(int sock) : fd(sock)
      {
         INSPIRE_ASSERT(INVALID_SOCKET != fd, "endpoint init with invalid socket");
         memset(&addr, 0, sizeof(addr));
         getpeername(fd, (struct sockaddr*)&addr, &len);
      }

      void toServerEndpoint(int port)
      {
         memset(&addr, 0, sizeof(sockaddr_in));
         addr.sin_family = AF_INET;
         addr.sin_addr.s_addr = htonl(INADDR_ANY);
         addr.sin_port = htons(port);
      }

      std::string toString()
      {
         INSPIRE_ASSERT(INVALID_SOCKET != fd, "try to get ip with invalid socket");
         std::string str;
         str = ntohl(addr.sin_addr.s_addr);
         str += ":";
         str += ntohs(addr.sin_port);

         return str;
      }
   };

   void toEndpoint(int sock, endpoint& end)
   {
      INSPIRE_ASSERT(INVALID_SOCKET != sock, "endpoint init with invalid socket");
      memset(&end.addr, 0, sizeof(end.addr));
   }

   void toEndpoint(uint port, endpoint& end)
   {
      memset(&end.addr, 0, sizeof(sockaddr_in));
      end.addr.sin_family = AF_INET;
      end.addr.sin_addr.s_addr = htonl(INADDR_ANY);
      end.addr.sin_port = htons(port);
   }
}
#endif
