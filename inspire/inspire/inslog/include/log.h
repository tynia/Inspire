#ifndef _INSPIRE_LOG_H_
#define _INSPIRE_LOG_H_

#include "control.h"
#include "platform.h"

namespace inspire {

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
      LOG_WARNING  = 500,
      LOG_DEBUG    = 600,
      LOG_NOTICE   = 700, // for expected
      LOG_INFO     = 800,
      LOG_DEFAULT  = LOG_DEBUG,
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