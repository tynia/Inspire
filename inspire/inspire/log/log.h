#ifndef _INSPIRE_LOG_H_
#define _INSPIRE_LOG_H_

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
// include windows.h
#include <windows.h>
// include STL
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <map>
#else
// header in Linux
#endif

// macros
#define LOG_BUFFER_SIZE 4096
#define MAX_LOG_FILE_NAME 255

#endif