#ifndef _INSPIRE_THREAD_H_
#define _INSPIRE_THREAD_H_

#include "inspire.h"

namespace inspire {

   typedef unsigned int(__stdcall *THREAD_ENTRY)(void*);

   enum threadState
   {
      THREAD_CREATING,
      THREAD_RUNNING,
      THREAD_STOPPED,
      THREAD_DESTROY,
   };

   class thread
   {
   public:
      thread(THREAD_ENTRY entry, void* argv);
      ~thread();

   public:
      int run();

      bool isRunning();

      const int stopped();

   private:
      HANDLE create();
      void stop();

   private:
      bool         _stop;
      void*        _entryParam;
      THREAD_ENTRY _entryFunc;
   };
}
#endif