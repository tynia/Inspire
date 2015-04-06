#ifndef _INSPIRE_THREAD_CONTROLLER_H_
#define _INSPIRE_THREAD_CONTROLLER_H_

#include "application.h"
#include "entry/threadentry.h"

#include <map>

namespace inspire {

   class threadEntity;
   typedef std::map<int64, threadEntity*> controlMap;

   class threadController : public IControl
   {
   public:
      threadController();
      ~threadController();

      void createEntity(THREAD_TYPES t, void* argv);

      void active(const int64 id);

      threadEntity* getThreadEntity(const int64 id);
   };
}
#endif