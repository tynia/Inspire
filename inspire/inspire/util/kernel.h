#ifndef _INSPIRE_UTIL_KERNEL_H_
#define _INSPIRE_UTIL_KERNEL_H_

#include "noncopyable.h"
#include "inspire.h"

namespace inspire {

   class threadMgr;

   class krControl : public IControl
   {
   public:
      krControl();
      ~krControl();

      virtual void initialize();

      virtual void active();

      virtual void destroy();

      threadMgr* getThreadMgr() const
      {
         return _threadMgr;
      }

   private:
      threadMgr* _threadMgr;
      std::vector<IControl*> _mapCTRL;
   };

   extern krControl _krCTRL;
   inline krControl* getKernel()
   {
      return &_krCTRL;
   }
}
#endif