#include "kernel.h"

namespace inspire {

   krControl::krControl()
   {}

   krControl::~krControl()
   {
      
   }
   //////////////////////////////////////////////////////////////////////////
   // !!!@ a global kernel control instance
   krControl _krCTRL;
}