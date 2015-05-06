#ifndef _INSPIRE_ASSERT_H_
#define _INSPIRE_ASSERT_H_

#include "util.h"

#ifdef _DEBUG
#define INSPIRE_ASSERT(condition)                           \
do                                                          \
{                                                           \
   if (condition)                                           \
   {}                                                       \
   else                                                     \
   {                                                        \
      inspire::Panic();                                     \
   }                                                        \
}while(false)
#else
#define INSPIRE_ASSERT(condition)                           \
do                                                          \
{                                                           \
   if (condition)                                           \
   {}                                                       \
}while(false)
#endif

#endif