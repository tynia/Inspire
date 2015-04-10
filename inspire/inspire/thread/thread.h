#ifndef _INSPIRE_THREAD_H_
#define _INSPIRE_THREAD_H_

#include "inspire.h"

namespace inspire {

   enum THREAD_TYPES
   {
      THREAD_SERVICE_ACCEPTOR,
      THREAD_SERVICE_SESSION,
   };

   class threadEntryPoint;

   class threadEntity
   {
   public:
      threadEntity(THREAD_TYPES t, void* argv);
      virtual ~threadEntity() {}

      HANDLE handle() const
      {
         return _thdl;
      }

      const int64 id() const
      {
         return _id;
      }

      const THREAD_TYPES type() const
      {
         return _type;
      }

      void attach(threadEntryPoint* ep, void* argv);

      void init   ();
      void run    ();
      void stop   ();
      void pause  ();
      void resume ();
      void destroy();

   protected:
      bool         _stop;
      THREAD_TYPES _type;
      int64        _id;
      HANDLE       _thdl;
      threadEntryPoint* _entryPoint;
      void* _argv;
   };
}
#endif