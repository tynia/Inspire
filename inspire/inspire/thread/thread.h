#ifndef _INSPIRE_THREAD_H_
#define _INSPIRE_THREAD_H_

namespace inspire {

   class IService;
   typedef void (*THREAD_ENTRY)(IService*, void*);

   class IThread
   {
   public:
      virtual ~IThread() {}

      virtual void init() = 0;
      virtual void run () = 0;
      virtual void destroy() = 0;
   };
}
#endif