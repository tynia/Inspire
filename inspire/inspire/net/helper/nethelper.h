#ifndef _INSPIRE_NET_HELPER_H_
#define _INSPIRE_NET_HELPER_H_

#include "net.h"

namespace inspire {

   inline int initNetModule()
   {
      int rc = NO_ERROR;
#ifdef _WIN32
      static bool initialized = false;
      // init
      WSADATA wsaData;
      rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
      if (NO_ERROR != rc)
      {
         return WSAGetLastError(); 
      }
      else
      {
         initialized = true;
      }
#endif
      return rc;
   }

   inline void check(int& mask, int key, bool enable = true)
   {
      if (enable)
      {
         mask |= key;
      }
      else
      {
         mask &= ~key;
      }
   }

   inline bool isCheck(const int mask, int key)
   {
      if (0 == key)
      {
         return false;
      }

      return ((mask & key) != 0) ? true : false;
   }

   inline void initNetAddr(const char* ip, int port, sockaddr_in& addr)
   {
      memset(&addr, 0, sizeof(sockaddr_in));
      if (NULL == ip)
      {
         return;
      }

      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = inet_addr(ip);
      addr.sin_port = htons(port);
   }

   inline void initNetAddr(int port, sockaddr_in& addr)
   {
      memset(&addr, 0, sizeof(sockaddr_in));

      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      addr.sin_port = htons(port);
   }

   inline bool getLocalAddr(SOCKET* sock, sockaddr_in& addr)
   {
      if (NULL == sock)
      {
         return false;
      }

      memset(&addr, 0, sizeof(sockaddr_in));
      int len = sizeof(addr);

      int rc = getsockname(*sock, (sockaddr*)&addr, &len);
      if (rc)
      {
         return false;
      }
      return true;
   }

   inline bool getPeerAddr(SOCKET* sock, sockaddr_in& addr)
   {
      if (NULL == sock)
      {
         return false;
      }
      memset(&addr, 0, sizeof(sockaddr_in));
      socklen_t len = sizeof(addr);

      int rc = getpeername(*sock, (sockaddr*)&addr, &len);
      if (rc)
      {
         return false;
      }
      return true;
   }

   inline int getPort(sockaddr_in* addr)
   {
      return ntohs(addr->sin_port);
   }

   inline int getIP(sockaddr_in* addr)
   {
      return ntohl(addr->sin_addr.s_addr);
   }

   inline void getAddress(sockaddr_in* addr, char* pAddrBuffer, int bufferLen)
   {
      int rc = 0;
      rc = getnameinfo((struct sockaddr*)addr, sizeof(sockaddr), pAddrBuffer,
         bufferLen, NULL, 0, NI_NUMERICHOST);
      if (rc)
      {
         //LogError("Failed to getnameinfo")
      }
   }

}
#endif