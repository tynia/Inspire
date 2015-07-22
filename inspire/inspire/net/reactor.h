#ifndef _INSPIRE_NET_REACTOR_ENGINE_H_
#define _INSPIRE_NET_REACTOR_ENGINE_H_

#include "inspire.h"
#include "engine.h"

namespace inspire {

   class Reactor : public INetEngine
   {
   public:
      Reactor();
      virtual ~Reactor();

   public:
      virtual int initailize();
      virtual int add(netEvent& nev);
      virtual int modify(netEvent& nev);
      virtual int remove(netEvent& nev);
      virtual int destroy();

   private:
#ifdef _WIN32
      HANDLE _hIOCP; // IOCP handle
#else
      int _fd;       // epoll handle
#endif
   };
}
#endif