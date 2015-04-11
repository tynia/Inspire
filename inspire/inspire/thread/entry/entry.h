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

   struct threadEntryInfo
   {
      bool bsystem;
      bool bregister;
      THREAD_ENTRY_TYPES t;
   };

   class threadEntryPoint
   {
   public:
      bool _system;
      THREAD_ENTRY_TYPES _type;
      THREAD_ENTRY _entry;
      const char*  _desc;

   public:
      threadEntryPoint(bool system, THREAD_ENTRY_TYPES t, THREAD_ENTRY entry, const char* desc);
      ~threadEntryPoint();
   };

   class threadEntryPointMgr
   {
   public:
      static threadEntryPointMgr* instance();

      threadEntryPoint* createEntryPoint(bool system, THREAD_ENTRY_TYPES t, THREAD_ENTRY entry, const char* desc);

      threadEntryPoint* getEntryPonit(THREAD_ENTRY_TYPES t);

      const char* getEntryPonitName(THREAD_ENTRY_TYPES t);

   protected:
      threadEntryPointMgr() ;
      ~threadEntryPointMgr();

      void _addEntryPoint(threadEntryPoint* pEntryPoint);

   private:
      std::map<THREAD_ENTRY_TYPES, threadEntryPoint*> _mapEntryPoint;
   };

#define ON_THREAD_ENTRY_POINT(system, type, entry, desc) \
   { system, registerEntryPoint(system, type, entry, desc), type }
}
#endif