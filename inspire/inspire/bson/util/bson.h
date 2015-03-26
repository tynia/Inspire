#ifndef _INSPIRE_BSON_H_
#define _INSPIRE_BSON_H_

typedef unsigned int size_t;
// int64
#ifdef _WIN32
typedef __int64 int64;
#else
typedef long long int64;
#endif

#ifdef _WIN32
#include <iostream>
#include <cstring>
#endif

#endif