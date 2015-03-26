#ifndef _INSPIRE_NET_PROCESSOR_H_
#define _INSPIRE_NET_PROCESSOR_H_

namespace inspire {

   class CEvent;

   class IProcessor
   {
   public:
      virtual ~IProcessor() {}

      virtual void onRead (CEvent& ev) = 0;
   };
}
#endif