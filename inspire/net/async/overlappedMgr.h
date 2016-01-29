#ifndef _INSPIRE_NET_ASYNC_OVERLAPPED_MGR_H_
#define _INSPIRE_NET_ASYNC_OVERLAPPED_MGR_H_

#include "util/container/deque.h"
#include "util/container/set.h"

namespace inspire {

   class overlappedContext;
   class overlappedMgr
   {
   public:
      overlappedMgr();
      virtual ~overlappedMgr();

   public:
      overlappedContext* create();
      void release(overlappedContext* ctx);

   private:
      void recycle(overlappedContext* ctx);

   private:
      set<overlappedContext*> _ctxQueue;
      deque<overlappedContext*> _ctxIdle;
   };

   extern overlappedMgr* GetOverlappedMgr();
}
#endif