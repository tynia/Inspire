#ifndef _INSPIRE_PLATFORM_H_
#define _INSPIRE_PLATFORM_H_

// defined NULL
#ifdef _CXX_11
#define NULL nullptr
#else
#define NULL 0
#endif // _CXX_11

// defined int64
#ifdef _WIN32
typedef __int64 int64;
#define NEWLINE "\r\n"
#else
typedef long long int int64;
#define NEWLINE "\n"
#endif

#ifdef _WIN32
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#else
#endif

#endif