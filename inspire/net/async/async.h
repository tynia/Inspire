#ifndef _INSPIRE_NET_ASYNC_H_
#define _INSPIRE_NET_ASYNC_H_

namespace inspire {

   class endpoint;
   class CEvent;

   class asyncConnection
   {
   public:
      virtual ~asyncConnection() {}

      virtual void asyncWrite(CEvent& ev) = 0;
      virtual void OnRead(const CEvent& ev) = 0;

      void close();

   protected:
      int initialize();
      int listenOn(const int port);
      int accept(asyncConnection& fd, endpoint& remote);
   };
}
#endif