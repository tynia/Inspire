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

   void ossSleep(unsigned int ms)
   {
#ifdef _WIN32
      ::Sleep(ms);
#else
      usleep(ms * 1000);
#endif
   }

   inline unsigned int ossGetLastError()
   {
#ifdef _WIN32
      return (unsigned int)GetLastError();
#else
      return errno;
#endif
   }
}
#endif