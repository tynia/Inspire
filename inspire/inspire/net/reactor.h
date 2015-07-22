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
      virtual int initailize(unsigned int evCount);
      virtual int active();
      virtual int deactive();
      virtual int add(netEvent& nev);
      virtual int modify(netEvent& nev);
      virtual int remove(netEvent& nev);
      virtual void destroy();

   protected:
      int _createReactor();

   private:
      bool _stop;
      unsigned int _maxEventCount;
#ifdef _WIN32
      HANDLE _hIOCP; // IOCP handle
#else
      int _epoll;    // epoll handle
      struct epoll_event* _events;
#endif
      std::map<int, fdData*> _fdDataList;
   };
}
#endif