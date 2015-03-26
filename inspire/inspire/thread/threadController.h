#ifndef _INSPIRE_THREAD_CONTROLLER_H_
#define _INSPIRE_THREAD_CONTROLLER_H_

#include "application.h"
#include <map>

namespace inspire {

   class IThread;
   typedef std::map<int64, IThread*> controlMap;

   class threadController : public IControl
   {
   public:
      static threadController* instance();

   private:
      threadController();
      ~threadController();
   };
}
#endif