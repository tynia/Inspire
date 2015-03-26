#include "session.h"

namespace inspire {

   Session::Session(const int socket)
   {
      _conn = new TCPConnection(socket);
      if (NULL == _conn)
      {
         //LogError
      }
   }

   Session::~Session()
   {
      destroy();
   }

   void Session::init()
   {
      // 
   }

   void Session::run(IProcessor* processor)
   {

   }

   void Session::destroy()
   {
      if (NULL != _conn)
      {
         delete _conn;
         _conn = NULL ;
      }
   }

   void Session::onEventReceived(CEvent& ev)
   {
      // dispatch event
   }

}