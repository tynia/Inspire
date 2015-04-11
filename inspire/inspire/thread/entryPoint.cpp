#include "entryPoint.h"
#include "entry/entry.h"
#include "async/ioservice.h"

namespace inspire {

   bool registerEntryPoint(bool system, THREAD_ENTRY_TYPES t, THREAD_ENTRY entry, const char* desc)
   {
      threadEntryPoint* entry = threadEntryPointMgr::instance()->createEntryPoint(system, t, entry, desc);
      if (NULL == entry)
      {
         return false;
      }
      return true;
   }

   threadEntryPoint* getEntryPoint(THREAD_ENTRY_TYPES t)
   {
      static threadEntryInfo entryInfo[] = {
         ON_THREAD_ENTRY_POINT(true, THREAD_SERVICE_ACCEPTOR, SERVICE_ACCEPTOR, "Service name"),
      };
      return threadEntryPointMgr::instance()->getEntryPonit(t);
   }

   const char* getEntryPointName(THREAD_ENTRY_TYPES t)
   {
      return threadEntryPointMgr::instance()->getEntryPonitName(t);
   }
}