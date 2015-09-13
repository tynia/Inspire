#ifndef _INSPIRE_THREAD_H_
#define _INSPIRE_THREAD_H_

#include "inspire.h"
#include "noncopyable.h"

namespace inspire {

   typedef uint(__stdcall *THREAD_ENTRY)(void*);

   enum threadState
   {
      THREAD_CREATING,
      THREAD_RUNNING,
      THREAD_STOPPED,
      THREAD_DESTROY,
   };

   class thread : public noncopyable
   {
   public:
      thread(THREAD_ENTRY entry, void* argv);
      virtual ~thread();

   public:
      virtual uint run();

   public:
      const int64 id() const;

   private:
      HANDLE create();

   private:
      int64        _id;
      HANDLE       _hThread;
      void*        _entryParam;
      THREAD_ENTRY _entryFunc;
   };
}
#endif