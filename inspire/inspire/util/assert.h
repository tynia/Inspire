#ifndef _INSPIRE_ASSERT_H_
#define _INSPIRE_ASSERT_H_

#include <iostream>
#include "util.h"

#ifdef _DEBUG
#define INSPIRE_ASSERT(condition, str)                      \
do                                                          \
{                                                           \
   if (!(condition))                                        \
   {                                                        \
      std::cout << " Assert Failed: " << str << std::endl;  \
      inspire::Panic();                                     \
   }                                                        \
   else                                                     \
   {}                                                       \
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