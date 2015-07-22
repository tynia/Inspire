#include "reactor.h"

namespace inspire {

#ifdef _WIN32
   Reactor::Reactor() : _hIOCP(INVALID_HANDLE_VALUE)
   {

   }

   Reactor::~Reactor()
   {
      if (INVALID_HANDLE_VALUE != _hIOCP)
      {
         ::CloseHandle(_hIOCP);
         _hIOCP = INVALID_HANDLE_VALUE;
      }
   }

   int Reactor::add()
   {
   }

#else
   Reactor::Reactor() : _fd(INVALID_FILE_DESCRIPTION)
   {

   }

   Reactor::~Reactor()
   {
      if (INVALID_FILE_DESCRIPTION != _fd)
      {
         close(_fd);
         _fd = INVALID_FILE_DESCRIPTION;
      }
   }

   int Reactor::add(netEvent nev)
   {

   }
#endif
}