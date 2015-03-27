#ifndef _INSPIRE_LOG_UITL_H_
#define _INSPIRE_LOG_UITL_H_

#include "writeable.h"

namespace inspire {
   /*
   * the bigger of value, the more logs
   **/
   enum PRIORITY
   {
      LOG_ALWAYS = 0,   // print always
      LOG_EMERG = 100,
      LOG_FATAL = 200,
      LOG_CRITICAL = 300,
      LOG_ERROR = 400,
      LOG_WARNING = 500,
      LOG_DEBUG = 600,
      LOG_NOTICE = 700, // for expected
      LOG_INFO = 800,
      LOG_DEFAULT = LOG_DEBUG,
   };

   inline const char* typeString(const int type)
   {
      const char *str = NULL ;
      switch (type)
      {
      case LOG_ALWAYS :
         str = "Always";
         break;
      case LOG_FATAL :
         str = "Fatal" ;
         break;
      case LOG_EMERG :
         str = "Emergency";
         break;
      case LOG_CRITICAL:
         str = "Critical";
         break;
      case LOG_ERROR :
         str = "Error" ;
         break;
      case LOG_DEBUG :
         str = "Debug" ;
         break;
      case LOG_WARNING :
         str = "Warning" ;
         break;
      case LOG_INFO :
         str = "Info" ;
         break;
      default:
         break;
      }
      return str;
   }

   const static char *logFmt = "%04d-%02d-%02d-%02d.%02d.%02d"NEWLINE
                               "Level: %s"NEWLINE
                               "PID: %-37lldTID: %lld"NEWLINE
                               "Function: %-32s"NEWLINE
                               "File: %s"NEWLINE"Line: %d"NEWLINE
                               "Message:"NEWLINE"%s"NEWLINE NEWLINE;

   inline void flushToFile(const int level, const char* func,
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
      sprintf_s(buffer, LOG_BUFFER_SIZE, logFmt,
                otm.tm_year + 1900, otm.tm_mon + 1, otm.tm_mday,
                otm.tm_hour, otm.tm_min, otm.tm_sec,
                typeString(level), GetProcessID(), GetThreadID(),
                func, file, line, userInfo);
      getLogMgr()->writeLog(level, buffer);
   }
}
#endif