#include "mutex.h"

namespace inspire {

   mutex::mutex()
   {
#ifdef _WIN32
      ::InitializeCriticalSection(&_cs);
#else
      int ret = pthread_mutex_init(&_mtx, NULL);
      if (ret)
      {
         LogError("Failed to create mutex");
         return;
      }
#endif
      LogDebug("Create mutex success");
   }

   mutex::~mutex()
   {
#ifdef _WIN32
      ::DeleteCriticalSection(&_cs);
#else
      int ret = 0;
      do
      {
         ret = pthread_mutex_destroy(&_mtx);
      } while (ret);
#endif
      LogDebug("Destroy mutex");
   }

   void mutex::lock()
   {
#ifdef _WIN32
      ::EnterCriticalSection(&_cs);
#else
      int ret = 0;
      do
      {
         ret = pthread_mutex_lock(&_mtx);
      } while (ret);
#endif
      LogDebug("get lock");
   }

   void mutex::unlock()
   {
#ifdef _WIN32
      ::LeaveCriticalSection(&_cs);
#else
      int ret = 0;
      do
      {
         ret = pthread_mutex_unlock(&_mtx);
      } while (ret);
#endif
      LogDebug("release lock");
   }

   bool mutex::tryLock()
   {
#ifdef _WIN32
      return ::TryEnterCriticalSection(&_cs);
#else
      return EBUSY != pthread_mutex_trylock(&_mtx);
#endif
   }

}