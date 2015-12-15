#ifndef _INSPIRE_COM_CONTROL_H_
#define _INSPIRE_COM_CONTROL_H_

#include "util/inspire.h"

namespace inspire {

   enum ctrlType
   {
      CTRL_MEMORY,
      CTRL_THREAD,
      CTRL_TASK,
   };

   class IControl
   {
   public:
      virtual ~IControl() {}
      virtual IControl* queryInterface(uint type) = 0;
   };

   class IMgr : public IControl
   {
   public:
      virtual ~IMgr() {}
      virtual uint64 id() = 0;
      virtual const char* name() = 0;
      virtual int init() = 0;
      virtual int active() = 0;
      virtual int deactive() = 0;
      virtual int destroy() = 0;

   protected:
      uint64 _id;
      const char* _name;
   };
}
#endif