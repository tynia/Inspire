#include "session.h"

namespace inspire {

   Session::Session(const int sock) : ISession(sock)
   {
   }

   Session::~Session()
   {
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
      close();
   }
}