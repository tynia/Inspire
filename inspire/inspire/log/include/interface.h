#ifndef _INSPIRE_LOG_INTERFACE_H_
#define _INSPIRE_LOG_INTERFACE_H_

#include "log.h"

namespace inspire {

   const static char *formatLog =   "%04d-%02d-%02d-%02d.%02d.%02d"NEWLINE
                                    "Level: %s"NEWLINE
                                    "PID: %-37lldTID: %lld"NEWLINE
                                    "Function: %-32s"NEWLINE
                                    "File: %s"NEWLINE"Line: %d"NEWLINE
                                    "Message:"NEWLINE"%s"NEWLINE NEWLINE ;
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

   class IWriteable
   {
   public:
      virtual ~IWriteable() {}

      virtual void writeLog(const int priority, const char* data);
   };

}
#endif