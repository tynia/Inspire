#ifndef _INSPIRE_NET_ENGINE_H_
#define _INSPIRE_NET_ENGINE_H_

namespace inspire {

   /*
    * accept callback for service
    * @param fd: service for listening
    **/
   unsigned int (*SERVICE_ACCEPTOR)(int fd);

   class IService;

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

   // socket type for epoll
   enum
   {
      FD_CONNECTION,    // fd for connection through accept
      FD_SERVICE,       // fd for listening by service
   };

   enum
   {
      EPOLL_MAX_EVENT_COUNT = 2048,
   };

   struct fdData
   {
      int _type;
      int _fd;
      IService* _owner;

      fdData(int type, int fd, IService* svc = NULL) : _type(type), _fd(fd), _owner(svc)
      {}

      ~fdData()
      {
         _owner = NULL;
      }
   };

#define MAKE_SERVICE_FD_DATA(var, fd)        \
   fdData *var = new fdData(FD_SERVICE, fd);

   class INetEngine
   {
   public:
      virtual ~INetEngine() {}

      virtual int add();

      virtual int modify();

      virtual int remove();
   };
}
#endif