#include "threadentry.h"

namespace inspire {

   unsigned int __stdcall serviceListener(void* data)
   {
      Service* service = (Service*)data;
      service->_ioservice->run();
   }
}