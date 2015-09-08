#include "mutex.h"

namespace inspire {

   insMutex::insMutex()
   {
#ifdef _WIN32
      _mutex = ::CreateMutex(NULL, FALSE, NULL);
      if (INVALID_HANDLE_VALUE == _mutex)
      {
         LogError("Failed to create sync mutex");
         return;
      }
#else
      int ret = pthread_mutex_init(&_mutex, NULL);
      if (ret)
      {
         LogError("Failed to create sync mutex");
         return;
      }
#endif
      LogEvent("Create sync mutex success");
   }

   insMutex::~insMutex()
   {
#ifdef _WIN32
      ::WaitForSingleObject(_mutex, INFINITE);
      ::CloseHandle(_mutex);
#else
      int ret = 0;
      do
      {
         ret = pthread_mutex_destroy(&_mutex);
      }while (ret)
#endif
      LogEvent("Destroy sync mutex success");
   }

   void insMutex::lock()
   {
#ifdef _WIN32
      ::WaitForSingleObject(_mutex, INFINITE);
#else
      int ret = 0;
      do
      {
         ret = pthread_mutex_lock(&_mutex);
      }while (ret)
#endif
   }

   void insMutex::unlock()
   {
#ifdef _WIN32
      ::SetEvent(_mutex);
#else
      int ret = pthread_mutex_unlock(&_mutex);
      if (ret)
      {
         LogError("Failed to release sync mutex");
      }
#endif
   }

   bool insMutex::tryLock()
   {
#ifdef _WIN32
      DWORD dwRet = ::WaitForSingleObject(_mutex, 1000);
      if (WAIT_OBJECT_0 != dwRet)
      {
         return false;
      }
#else
      int ret = pthread_mutex_trylock(&_mutex);
      if (ret)
      {
         return false;
      }
#endif
      return true;
   }
}