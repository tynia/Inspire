#ifndef _INSPIRE_ASSERT_H_
#define _INSPIRE_ASSERT_H_

#include <iostream>
#include "util.h"
#include "insLog.h"

#ifdef _DEBUG
#define INSPIRE_ASSERT(condition, fmt, ...)                 \
do                                                          \
{                                                           \
   if (!(condition))                                        \
   {                                                        \
      LogError(fmt, __VA_ARGS__);                           \
      inspire::Panic();                                     \
   }                                                        \
   else                                                     \
   {}                                                       \
}while(false)
#else
#define INSPIRE_ASSERT(condition, fmt, ...)                 \
do                                                          \
{                                                           \
   if (condition)                                           \
   {}                                                       \
}while(false)
#endif

#endif