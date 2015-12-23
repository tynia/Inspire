#include "util/inspire.h"
#include "util/assert.h"
#include "net.h"
#include "thread/threads.h"
#include "util/system/condition.h"

struct msgClient
{
   int64 id;
   char data[100];
};

class Session
{
public:
   Session(int fd) {}
   ~Session() {}



private:
   int _fd;
};

class TaskServer : inspire::thdTask
{
public:
   TaskServer() : thdTask(SERVER_TASK_ID, "server")
   {}

   ~TaskServer() {}

   virtual const int run()
   {
      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      STRONG_ASSERT(SOCKET_ERROR != _fd, "Failed to initialize socket");

      int port = 50000;
      sockaddr_in addr;
      memset(&addr, 0, sizeof(sockaddr_in));
      addr.sin_family = AF_INET;
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      addr.sin_port = htons(port);

      int rc = ::bind(_fd, (sockaddr*)&addr, 0);
      STRONG_ASSERT(SOCKET_ERROR != rc, "Failed to bind socket");

      rc = ::listen(_fd, 1000000);
      STRONG_ASSERT(SOCKET_ERROR != rc, "Failed to listen");

      _stop = false;
      while (!_stop)
      {
         int remote;
         sockaddr_in raddr;
         int len = sizeof(sockaddr);
         remote = ::accept(_fd, (sockaddr*)&raddr, &len);
         if (SOCKET_ERROR != remote)
         {
            
         }
      }

      int port = 5000;
   }

private:
   bool _stop;
   int _fd;
   const int64 SERVER_TASK_ID = 65536;
   std::map<int64, int> _sessions;
};