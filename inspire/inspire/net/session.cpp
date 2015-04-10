#include "session.h"

namespace inspire {

   Session::Session(const int sock) : _conn(NULL)
   {
      _conn = new AsyncConnection(sock);
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
      _conn->close();
   }
}