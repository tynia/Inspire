#ifndef _INSPIRE_NET_EVENT_HANDLER_INTERFACE_H_
#define _INSPIRE_NET_EVENT_HANDLER_INTERFACE_H_

namespace inspire {

   class CEvent;

   class INetEventHandler
   {
   public:
      virtual ~INetEventHandler() {}

      virtual void sendEvent(CEvent& ev) = 0;

      virtual void recvEvent(CEvent& ev) = 0;
   };

   class INetAsyncEventHandler
   {
   public:
      virtual ~INetAsyncEventHandler() {}

      virtual void sendEvent(CEvent& ev) = 0;

      virtual void onEvent(CEvent& ev) = 0;
   };
}
#endif