#ifndef _INSPIRE_NET_FRAMEWORK_H_
#define _INSPIRE_NET_FRAMEWORK_H_

#ifdef _WIN32
typedef __int64 int64;
#else
typedef long long int64;
#endif

#ifdef _WIN32
#include <Winsock2.h>
#include <ws2tcpip.h>

#include <cstdlib>
#include <cstring>
#include <map>

#pragma comment(lib, "Ws2_32.lib")

#else
#endif

#endif