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

#include "include/log.h"

#define __LOG_WRAPPER(LEVEL, fmt, ...)                         \
do                                                             \
{                                                              \
   inspire::flushToFile(LEVEL, __FUNCTION__,                   \
                        __FILE__, __LINE__, fmt, __VA_ARGS__); \
}while(false)

/*
 *@brief useful macro when log
 **/
#define LogError(fmt, ...)                                  \
   __LOG_WRAPPER(inspire::LOG_ERROR, fmt, __VA_ARGS__)

#define LogDebug(fmt, ...)                                  \
   __LOG_WRAPPER(inspire::LOG_DEBUG, fmt, __VA_ARGS__)

#define LogEvent(fmt, ...)                                  \
   __LOG_WRAPPER(inspire::LOG_EVENT, fmt, __VA_ARGS__)

#define LogWarning(fmt, ...)                                \
   __LOG_WRAPPER(inspire::LOG_WARNING, fmt, __VA_ARGS__)

#define LogNotice(fmt, ...)                                 \
   __LOG_WRAPPER(inspire::LOG_NOTICE, fmt, __VA_ARGS__)

#define LogInfo(fmt, ...)                                   \
   __LOG_WRAPPER(inspire::LOG_INFO, fmt, __VA_ARGS__)

#endif