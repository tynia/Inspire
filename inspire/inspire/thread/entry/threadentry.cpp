#include "threadentry.h"

namespace inspire {

   //////////////////////////////////////////////////////////////////////////
   threadEntryPoint::threadEntryPoint(bool system, THREAD_TYPES t,
                                      THREAD_ENTRY entry, const char* desc)
   : _system(system), _type(t), _entry(entry), _desc(desc)
   {
   }

   threadEntryPoint::~threadEntryPoint()
   {}

   void registerEntryPoint(bool system, THREAD_TYPES t, THREAD_ENTRY entry, const char* desc)
   {
      std::map<THREAD_TYPES, threadEntryPoint*>::iterator it = mapEntryPoint.find(t);
      if (mapEntryPoint.end() != it)
      {
         LogError("thread entry conflict, type:%d, name:%s", t, desc);
         return;
      }

      threadEntryPoint* pt = new threadEntryPoint(system, t, entry, desc);
      if (NULL == pt)
      {
         LogError("Out of memory when register entry point");
         return;
      }
      mapEntryPoint[t] = pt;
   }

   threadEntryPoint* getEntryPoint(THREAD_TYPES t)
   {
      std::map<THREAD_TYPES, threadEntryPoint*>::iterator it = mapEntryPoint.find(t);
      if (mapEntryPoint.end() != it)
      {
         return it->second;
      }
      // shouldn't hit here
      return NULL;
   }

   unsigned int __stdcall serviceEntry(void* argv)
   {
      return 0;
   }
}