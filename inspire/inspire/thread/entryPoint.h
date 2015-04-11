#ifndef _INSPIRE_THREAD_ENTRY_POINT_H_
#define _INSPIRE_THREAD_ENTRY_POINT_H_

namespace inspire {

   bool registerEntryPoint(bool system, THREAD_ENTRY_TYPES t, THREAD_ENTRY entry, const char* desc);

   threadEntryPoint* getEntryPoint(THREAD_ENTRY_TYPES t);

   const char* getEntryPointName(THREAD_ENTRY_TYPES t);
}
#endif