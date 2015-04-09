#ifndef _INSPIRE_UTIL_LOCK_H_
#define _INSPIRE_UTIL_LOCK_H_

namespace inspire {

   class ossMutex;

   class scopeLock
   {
   public:
      scopeLock(ossMutex* mx);
      ~scopeLock();

   private:
      ossMutex* _mutex;
   };
}
#endif