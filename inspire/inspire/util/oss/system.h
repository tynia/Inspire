#ifndef _INSPIRE_UTIL_OSS_SYSTEM_H_
#define _INSPIRE_UTIL_OSS_SYSTEM_H_

namespace inspire {

#ifdef _WIN32
   const DWORD ossGetCurrentThreadId()
   {
      return GetCurrentThreadId();
   }

   const DWORD ossGetCurrentProcessId()
   {
      return GetCurrentProcessId();
   }
#else
   const pthread_t ossGetCurrentThreadId()
   {
      return syscall(SYS_gettid);
   }

   const pid_t ossGetCurrentProcessId()
   {
      return getpid();
   }
#endif

   void ossSleep(uint ms)
   {
#ifdef _WIN32
      ::Sleep(ms);
#else
      usleep(ms * 1000);
#endif
   }

   inline uint ossGetLastError()
   {
#ifdef _WIN32
      return (uint)GetLastError();
#else
      return errno;
#endif
   }

}
#endif