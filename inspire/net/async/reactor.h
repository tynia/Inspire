#ifndef _INSPIRE_NET_REACTOR_ENGINE_H_
#define _INSPIRE_NET_REACTOR_ENGINE_H_

#include "util/inspire.h"
#include "overlapped.h"
#include "util/container/deque.h"

namespace inspire {

   class Reactor : public EventHandler
   {
   public:
      Reactor();
      virtual ~Reactor();

   public:
      int initailize();

      int bind(asyncConnection* conn);

      int run();

      void stop();

      void destroy();

      void associate(overlappedContext* overlapped);

      bool stopped() const;

      int  handle(overlappedContext* overlapped);

   private:
      bool _stop;
      uint _maxEventCount;
#ifdef _WIN32
      HANDLE _hIOCP; // IOCP handle
#else
      int _epoll;    // epoll handle
      struct epoll_event* _events;
#endif
      deque<overlappedContext*> _dequeOverlapped;
   };
}
#endif