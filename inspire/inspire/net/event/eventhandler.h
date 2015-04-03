#ifndef _INSPIRE_EVENT_HANDLER_INTERFACE_H_
#define _INSPIRE_EVENT_HANDLER_INTERFACE_H_

namespace inspire {

   class CEvent;

   class INetEventHandler
   {
   public:
      virtual ~INetEventHandler() {}

      virtual void sendEvent(CEvent& ev) = 0;

      virtual void onEvent(CEvent& ev) = 0;
   };
}
#endif