#include "thread.h"
#include "assert.h"

namespace inspire {

   thread::thread(THREAD_ENTRY entry, void* argv) : _entryFunc(entry), _entryParam(argv)
   {
   }

   thread::~thread()
   {
      _entryFunc = NULL;
      _entryParam = NULL;
   }

   uint thread::run()
   {
      return this->_entryFunc(_entryParam);
   }

   const int64 thread::id() const
   {
      return _id;
   }

   HANDLE thread::create()
   {
      INSPIRE_ASSERT(NULL != _hThread, "Thread handle is NULL");

#ifdef _WIN32
      _hThread = (HANDLE)::_beginthreadex(NULL, 0, _entryFunc, _entryParam, CREATE_SUSPENDED, NULL);
      _id = (int64)GetThreadId(_hThread);
#else
      pthread_t thdl;
      _hThread = pthread_create(&thdl, NULL, _entryFunc, _entryParam);
      _id = (int64)pthread_self();
#endif
   }
}