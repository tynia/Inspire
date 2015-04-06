#ifndef _INSPIRE_NET_THREAD_ENTRY_H_
#define _INSPIRE_NET_THREAD_ENTRY_H_

#include "inspire.h"
#include "async/async.h"

namespace inspire {
   /*
    * define 2 callback function
    */
   typedef void (*IOSERVICE_ACCEPTOR_FUNC)(void *additonParam);
   typedef void (*IOSERVICE_HANDLER_FUNC) (void *additonParam);

   enum THREAD_TYPES
   {
      THREAD_SERVICE_ACCEPTOR,
      THREAD_SERVICE_SESSION,
   };
}
#endif