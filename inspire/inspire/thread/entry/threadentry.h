#ifndef _INSPIRE_NET_THREAD_ENTRY_H_
#define _INSPIRE_NET_THREAD_ENTRY_H_

#include "inspire.h"
#include "async/async.h"
#include "thread.h"

namespace inspire {
   /*
    * define 2 callback function
    */
   class threadEntity;

   typedef void (*IOSERVICE_ACCEPTOR_FUNC)(void *);
   typedef void (*IOSERVICE_HANDLER_FUNC) (void *);
   typedef unsigned int (__stdcall *THREAD_ENTRY)(void*);

   class threadEntryPoint
   {
   public:
      bool _system;
      THREAD_TYPES _type;
      THREAD_ENTRY _entry;
      const char*  _desc;

   public:
      threadEntryPoint(bool system, THREAD_TYPES t, THREAD_ENTRY entry, const char* desc);
      ~threadEntryPoint();
   };

   static std::map<THREAD_TYPES, threadEntryPoint*> mapEntryPoint;

   void registerEntryPoint(bool system, THREAD_TYPES t, THREAD_ENTRY entry, const char* desc);
   threadEntryPoint* getEntryPoint(THREAD_TYPES t);

#define ON_THREAD_ENTRY_POINT(system, type, entry, desc) \
   registerEntryPoint(system, type, entry, desc)
}
#endif