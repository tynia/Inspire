#ifndef _INSPIRE_LOG_H_
#define _INSPIRE_LOG_H_

#include "control.h"

namespace inspire {

   // macros
   #define LOG_BUFFER_SIZE 4096
   #define MAX_LOG_FILE_NAME 255
   /*
   * the bigger of value, the more logs
   **/
   enum PRIORITY
   {
      LOG_ALWAYS   = 0,   // print always
      LOG_EMERG    = 100,
      LOG_FATAL    = 200,
      LOG_CRITICAL = 300,
      LOG_ERROR    = 400,
      LOG_EVENT    = 500,
      LOG_WARNING  = 600,
      LOG_DEBUG    = 700,
      LOG_NOTICE   = 800, // for expected
      LOG_INFO     = 900,
      LOG_DEFAULT  = LOG_WARNING,
   };

   class ILog
   {
   public:
      virtual ~ILog() {}

      virtual void writeLog(const int priority, const char* data) = 0;
   };

   const char* typeString(const int type);
   void flushToFile(const int level, const char* func,
                    const char* file, const int line,
                    const char* fmt, ...);

   extern ILog* getLogMgr();
}
#endif