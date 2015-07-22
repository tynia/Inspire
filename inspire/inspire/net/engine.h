#ifndef _INSPIRE_NET_ENGINE_H_
#define _INSPIRE_NET_ENGINE_H_

namespace inspire {

   /*
    * accept callback for service
    * @param fd: service for listening
    **/
   unsigned int (*SERVICE_ACCEPTOR)(int fd);

   class netEvent
   {
#ifndef _WIN32
      struct epoll_event event;
#endif
      IService* _svc;
   };

   enum NET_ENGINE
   {
      NET_ENGINE_REACTOR,
      NET_ENGINE_PROACTOR,
   };

   class INetEngine
   {
   public:
      virtual ~INetEngine() {}

      virtual int initailize();

      virtual int add();

      virtual int modify();

      virtual int remove();

      virtual int destroy();
   };
}
#endif