#include "util/inspire.h"
#include "util/assert.h"
#include "net.h"
#include "thread/threads.h"
#include "util/system/condition.h"

struct atomic_id
{
   int64 id_sequeue;
   inspire::mutex_t _mtx;
};

const int64 inc(atomic_id& aid)
{
   inspire::condition_t cond(&aid._mtx);
   ++aid.id_sequeue;
   return aid.id_sequeue;
}

atomic_id taskId;

class TaskConnnection : public inspire::thdTask
{
public:
   TaskConnnection() : thdTask(inc(taskId), "client") : _stop(false)
   {}

   ~TaskConnnection() {}

   void stop()
   {
      _stop = false;
   }

   virtual const int run()
   {
      int rc = 0;
      LogEvent("client [%lld] connect to server", id());
      const char* host = "localhost";
      const uint  port = 50000;

      _fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      STRONG_ASSERT(SOCKET_ERROR != _fd, "Failed to init socket");
      sockaddr_in serv;
      serv.sin_family = AF_INET;
      serv.sin_addr.s_addr = inet_addr(host);
      serv.sin_port = htons(port);
      rc = ::connect(_fd, (struct sockaddr*)&serv, sizeof(sockaddr_in));
      STRONG_ASSERT(SOCKET_ERROR != rc, "Failed to connect to server: %s:%d", host, port);

      char data[100] = { 0 };
      utilSnprintf(data, 100, "hello, this is client %lld", id());

      ::send(_fd, data, strlen(data), 0);
      _stop = true;
      while (_stop)
      {
         utilSleep(1000);
      }
      return 0;
   }
private:
   int _fd;
   bool _stop;
};

int main(int argc, char** argb)
{
   STRONG_ASSERT(!inspire::netok(), "Failed initialize net environment");

   taskId.id_sequeue = 0;

   inspire::thdMgr* mgr = inspire::thdMgr::instance();
   STRONG_ASSERT(NULL != mgr, "Failed to init thread manager");

   uint idx = 0;
   while ( idx < 1000000)
   {
      TaskConnnection* task = INSPIRE_NEW TaskConnnection();
      mgr->postEvent(task);
   }

   idx = 0;
   while (idx < 1000000)
   {
      mgr->destroy();
   }

   return 0;
}