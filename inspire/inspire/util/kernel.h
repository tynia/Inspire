#ifndef _INSPIRE_UTIL_KERNEL_H_
#define _INSPIRE_UTIL_KERNEL_H_

#include "noncopyable.h"
#include "inspire.h"

namespace inspire {

   class threadMgr;

   class krControl : public IControl, public noncopyable
   {
   public:
      krControl();
      ~krControl();

      // IControl
      virtual void initialize();
      virtual void active();
      virtual void destroy();

      void registerCTRL(modType t);

      threadMgr* getThreadMgr() const
      {
         return _threadMgr;
      }

   private:
      threadMgr* _threadMgr;
      std::vector<IControl*> _mapCTRL;
   };

   extern krControl _kernel;
   inline krControl* getKernel()
   {
      return &_kernel;
   }

   inline void regModule(modType t)
   {
      getKernel()->registerCTRL(t);
   }

#define REGISTER_MOD(type) \
do                         \
{                          \
   regModule(type);        \
} while (false)
   
}
#endif