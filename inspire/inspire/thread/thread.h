#ifndef _INSPIRE_THREAD_H_
#define _INSPIRE_THREAD_H_

namespace inspire {

   typedef void (*THREAD_ENTRY)(void*);

   class threadEntity
   {
   public:
      virtual ~threadEntity() {}

      HANDLE handle() const
      {
         return _hThread;
      }

      const int64 id() const
      {
         return _id;
      }

      const int64 type() const
      {
         return _type;
      }

      virtual void init   () = 0;
      virtual void run    () = 0;
      virtual void stop   () = 0;
      virtual void pause  () = 0;
      virtual void resume () = 0;
      virtual void destroy() = 0;

   protected:
      int64  _type;
      int64  _id;
      HANDLE _hThread;
   };
}
#endif