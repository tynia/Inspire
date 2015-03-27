#ifndef _INSPIRE_LOG_INTERFACE_H_
#define _INSPIRE_LOG_INTERFACE_H_

namespace inspire {

   class IWriteable
   {
   public:
      virtual ~IWriteable() {}

      virtual void writeLog(const int priority, const char* data) = 0;
   };

   extern IWriteable* getLogMgr();
}
#endif