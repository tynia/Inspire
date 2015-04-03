#ifndef _INSPIRE_NET_THREAD_ENTRY_H_
#define _INSPIRE_NET_THREAD_ENTRY_H_

#include "inspire.h"

namespace inspire {
   /*
    * define 3 callback function
    */
   typedef void (*IO_CONNECTOR_FUNC)(void *additonParam);
   typedef void (*IO_ACCEPTOR_FUNC) (void *additonParam);
   typedef void (*IO_HANDLER_FUNC)  (void *additonParam);
}
#endif