#ifndef _INSPIRE_NET_EVENT_H_
#define _INSPIRE_NET_EVENT_H_

#include "iostream.h"

namespace inspire {

   // base event
   class CEvent
   {
   public:
      CEvent(const int64 id) : msgLen(0), _eventId(id)
      {}
      virtual ~CEvent() {}

      const int64 getEventID()
      {
         return _eventId;
      }

      virtual void loadStream(CIStream& is)
      {
         is >> msgLen >> _eventId;
      }

      virtual void saveStream(COStream& os)
      {
         os << msgLen << _eventId;
      }

   public:
      uint msgLen;
   private:
      int64 _eventId;
   };
}
#endif