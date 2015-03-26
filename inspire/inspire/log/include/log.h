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
#ifndef _INSPIRE_LOG_H_
#define _INSPIRE_LOG_H_

#include "inspire.h"

#define LOG_BUFFER_SIZE 4096
#define MAX_LOG_FILE_NAME 255

namespace inspire {

   const static char *formatLog = "%04d-%02d-%02d-%02d.%02d.%02d"NEWLINE
                                  "Level: %s"NEWLINE
                                  "PID: %-37lldTID: %lld"NEWLINE
                                  "Function: %-32s"NEWLINE
                                  "File: %s"NEWLINE"Line: %d"NEWLINE
                                  "Message:"NEWLINE"%s"NEWLINE NEWLINE ;

   inline void Panic()
   {
#ifdef _DEBUG
      __asm int 3;
#else
      int *p = NULL;
      *p = 1;
#endif
   }

   /*
   * the bigger of value, the more logs
   **/
   enum PRIORITY
   {
      PRIO_ALWAYS   = 0,   // print always
      PRIO_EMERG    = 100,
      PRIO_FATAL    = 200,
      PRIO_CRITICAL = 300,
      PRIO_ERROR    = 400,
      PRIO_WARNING  = 500,
      PRIO_DEBUG    = 600,
      PRIO_NOTICE   = 700, // for expected
      PRIO_INFO     = 800,

      PRIO_DEFAULT  = PRIO_DEBUG,
      PRIO_LOG      = PRIO_CRITICAL,
   };

   inline const char* GetLevelString(const int level)
   {
      const char *str = NULL ;
      switch (level)
      {
      case PRIO_ALWAYS :
         str = "Always";
         break;
      case PRIO_FATAL :
         str = "Fatal" ;
         break;
      case PRIO_EMERG :
         str = "Emergency";
         break;
      case PRIO_CRITICAL:
         str = "Critical";
         break;
      case PRIO_ERROR :
         str = "Error" ;
         break;
      case PRIO_DEBUG :
         str = "Debug" ;
         break;
      case PRIO_WARNING :
         str = "Warning" ;
         break;
      case PRIO_INFO :
         str = "Info" ;
         break;
      default:
         break;
      }
      return str;
   }

   inline void Log(const int level, const char* func,
                   const char* file, const int line,
                   const char* fmt, ...)
   {
      struct tm otm;
      GetLocalTime(&otm);

      char userInfo[LOG_BUFFER_SIZE] = { 0 };
      va_list ap;
      va_start(ap, fmt);
      vsprintf_s(userInfo, LOG_BUFFER_SIZE, fmt, ap);
      va_end(ap);

      char buffer[LOG_BUFFER_SIZE] = { 0 };
      sprintf_s(buffer, LOG_BUFFER_SIZE, formatLog,
                otm.tm_year + 1900,
                otm.tm_mon + 1,
                otm.tm_mday,
                otm.tm_hour,
                otm.tm_min,
                otm.tm_sec,
                GetLevelString(level),
                GetProcessID(),
                GetThreadID(),
                func, file, line, userInfo);
      //   LogManager::Instance()->WriteLog(level, buffer) ;
   }
}
#endif