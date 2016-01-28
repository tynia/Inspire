#include "overlappedMgr.h"
#include "overlapped.h"

namespace inspire {

   overlappedMgr::overlappedMgr()
   {
   }

   overlappedMgr::~overlappedMgr()
   {
      if (!_ctxQueue.empty())
      {
         std::set<overlappedContext*>& ctxQueue = _ctxQueue.raw();
         std::set<overlappedContext*>::iterator it = ctxQueue.begin();
         while (ctxQueue.end() != it)
         {
            overlappedContext* pOverlapped = (*it);
            delete pOverlapped;
            pOverlapped = NULL;
         }
      }
   }

   overlappedContext* overlappedMgr::create()
   {
      overlappedContext* ctx = NULL;
      if (!_ctxIdle.pop_front(ctx))
      {
         ctx = new overlappedContext();
         if (NULL == ctx)
         {
            LogError("Failed to create overlapped context, out of memory");
            return NULL;
         }
         _ctxQueue.insert(ctx);
      }
      LogDebug("fetch an overlapped context from idle queue");
      return ctx;
   }

   void overlappedMgr::release(overlappedContext* ctx)
   {
      recycle(ctx);
   }

   void overlappedMgr::recycle(overlappedContext* ctx)
   {
      overlappedContext* pctx = NULL;
      if (!_ctxQueue.find(ctx))
      {
         LogEvent("overlapped context is not owned");
         delete ctx;
      }

      ctx->zero();
      _ctxIdle.push_back(ctx);
   }

   overlappedMgr* GetOverlappedMgr()
   {
      static overlappedMgr mgr;
      return &mgr;
   }
}