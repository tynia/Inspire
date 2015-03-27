/*******************************************************************************
   Copyright (C) 2015 tynia.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.
   
   Any problem, please ping xduilib@gmail.com, free service may be supported.
*******************************************************************************/
#ifndef _INSPIRE_LOG_HELPER_H_
#define _INSPIRE_LOG_HELPER_H_

#include "inspire.h"
#include "include/log.h"

inline void Panic()
{
#ifdef _DEBUG
   __asm int 3;
#else
   int *p = NULL;
   *p = 1;
#endif
}

#define __LOG_WRAPPER(LEVEL, fmt, ...)                      \
do                                                          \
{                                                           \
   inspire::Log(LEVEL, __FUNCTION__,                        \
                 __FILE__, __LINE__, fmt, __VA_ARGS__) ;    \
}while(false)

#ifdef _DEBUG
#define LIGHT_ASSERT(condition)                             \
do                                                          \
{                                                           \
   if (!condition)                                          \
   {                                                        \
      Panic();                                              \
   }                                                        \
}while(false)
#else
#define LIGHT_ASSERT(condition)                             \
do                                                          \
{                                                           \
   if (condition)                                           \
   {}                                                       \
}while(false)
#endif

#ifdef _DEBUG
#define INSPIRE_ASSERT(condition, fmt, ...)                 \
do                                                          \
{                                                           \
   if (!condition)                                          \
   {                                                        \
      inspire::Log(inspire::PRIO_ERROR, __FUNCTION__,       \
                    __FILE__, __LINE__, fmt, __VA_ARGS__) ; \
      Panic() ;                                             \
   }                                                        \
}while(false)
#else
#define INSPIRE_ASSERT(condition, fmt, ...)                 \
do                                                          \
{                                                           \
   if (!condition)                                          \
   {}                                                       \
}while(false)
#endif

/*
 *@brief useful macro when log
 **/
#define LogError(fmt, ...)                                  \
   __LOG_WRAPPER(inspire::PRIO_ERROR, fmt, __VA_ARGS__)

#define LogDebug(fmt, ...)                                  \
   __LOG_WRAPPER(inspire::PRIO_DEBUG, fmt, __VA_ARGS__)

#define LogWarning(fmt, ...)                                \
   __LOG_WRAPPER(inspire::PRIO_WARNING, fmt, __VA_ARGS__)

#define LogNotice(fmt, ...)                                 \
   __LOG_WRAPPER(inspire::PRIO_NOTICE, fmt, __VA_ARGS__)

#define LogInfo(fmt, ...)                                   \
   __LOG_WRAPPER(inspire::PRIO_INFO, fmt, __VA_ARGS__)

#endif