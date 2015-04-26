#include "kernel.h"
#include "threadMgr.h"

namespace inspire {

   krControl::krControl() : IControl(MOD_KERNEL)
   {
      
   }

   krControl::~krControl()
   {
      
   }

   void krControl::initialize()
   {
      _threadMgr = new threadMgr();
      if (NULL == _threadMgr)
      {
         LogError("Failed to allocate thread manager, out of memory");
         return;
      }
      LogEvent("Success to create thread manager");
   }

   //////////////////////////////////////////////////////////////////////////
   // !!!@ a global kernel control instance
   krControl _krCTRL;
}