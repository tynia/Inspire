#ifndef _INSPIRE_THREAD_H_
#define _INSPIRE_THREAD_H_

namespace inspire {

   typedef void (*THREAD_ENTRY)(void*);

   class IThread
   {
   public:
      virtual ~IThread() {}

      virtual void init   () = 0;
      virtual void run    () = 0;
      virtual void stop   () = 0;
      virtual void pause  () = 0;
      virtual void resume () = 0;
      virtual void destroy() = 0;
   };
}
#endif