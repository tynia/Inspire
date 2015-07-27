#include "reactor.h"

namespace inspire {

#ifdef _WIN32
   Reactor::Reactor() : _stop(false), _maxEventCount(EPOLL_MAX_EVENT_COUNT), _hIOCP(INVALID_HANDLE_VALUE)
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

   int Reactor::add(netEvent& nev)
   {
      return -1;
   }

#else
   Reactor::Reactor() : _stop(false), _maxEventCount(EPOLL_MAX_EVENT_COUNT), _fd(INVALID_FILE_DESCRIPTION)
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

   int Reactor::add(netEvent& nev)
   {

   }

   int Reactor::initailize(unsigned int evCount)
   {
      if (0 != evCount)
      {
         _maxEventCount = evCount;
      }

      return _createReactor();
   }

   int Reactor::_createReactor()
   {
      int rc = 0;
      _epoll = epoll_create(_maxEventCount);
      if (0 > _epoll)
      {
         rc = -1;
         LogError("Create epoll handle failed, errno = ", util::netError());
      }
      return rc;
   }

   int Reactor::active()
   {
      INSPIRE_ASSERT(_epoll > 0);
      int rc = 0;
      _events = ::calloc(_maxEventCount, sizeof(struct epoll_event));
      if (NULL == _epollEvents )
      {
         rc = -1;
         LogError("Failed to alloc memory space for epoll event");
         return;
      }

      int nfd = 0;
      int idx = 0;
      while(!_stop)
      {
         int nfd = epoll_wait(_epoll, _events, _maxEventCount, 500)
         if (nfd < 0)
         {
            LogEvent("No event occured in %dms", 500);
            continue;
         }
         for (idx = 0; idx < _maxEventCount, ++idx)
         {
            if ( (   (_events[idx].events & EPOLLERR)
                  || (_events[idx].events & EPOLLHUP) )
                  || !(_events[idx].events & EPOLLIN) )
            {
               LogError("Error occurred when wait epoll event");
               remove(_events[idx].data.fd);
               close(_events[idx].data.fd);
            }
            else
            {
               fdData* fdd = _fdDataList[_events[idx].data.fd];
               if (FD_SERVICE == fdd->type && _events[idx].events & EPOLLIN)
               {
                  sockaddr_in addr;
                  int len = sizeof(addr);
                  int conn = ::accept(fdd->fd, (sockaddr*)&addr, &len);
                  if (conn < 0)
                  {
                     LogError("Failed to accept remote connection, errno: %d", util::netError());
                     continue;
                  }
                  fdData* newFdd = new fdData(FD_CONNECTION, conn);
                  _fdDataList.insert(conn, newFdd);
               }
               else if (FD_CONNECTION == fdd->type && _events[idx].events & EPOLLIN)
               {
                  int msgLen = 0;
                  int readLen = 0;
                  int pos = 0;
                  readLen = ::read(fdd->_fd, (char*)&msgLen, sizeof(int), 0);
                  if (readLen < 0)
                  {
                     LogError("Failed to read msg length, errno: %d", util::netError());
                     //remove(fdd->_fd);
                  }
                  // need import memory pool to alloc buffer
                  char* buf = new char[msgLen];
                  *(int*)buf = msgLen;
                  pos += sizeof(int);
                  while (pos < msgLen)
                  {
                     readLen = ::read(fdd->_fd, buf + pos, msgLen - pos);
                     if (readLen < 0)
                     {
                        LogError("Failed to read msg context, errno: %d", util::netError());
                        //remove(fdd->_fd);
                        break;
                     }
                     pos += readLen;
                  }
                  // handle data
                  // thread join
               }
               else if (FD_CONNECTION == fdd->type && _events[idx].events & EPOLLOUT)
               {
                  // hit here it means send buffer of tcp is full
                  // and we should add it to epoll to send rest data
                  // TODO:
               }
            }
         }
      }
   }

#endif
}