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
   }

   //////////////////////////////////////////////////////////////////////////
   // !!!@ a global kernel control instance
   krControl _krCTRL;
}