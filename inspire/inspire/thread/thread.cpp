#include "thread.h"
#include "entry/entry.h"

namespace inspire {

   threadEntity::threadEntity(THREAD_ENTRY_TYPES t, void* argv)
      : _stop(false), _type(t), _id(0), _thdl(NULL), _entryPoint(NULL), _argv(argv)
   {}

   threadEntity::~threadEntity()
   {
   }

   void threadEntity::init()
   {
      _entryPoint = getEntryPoint(_type);
      if (NULL == _entryPoint)
      {
         LogError("Cannot find entry point, type:%d", _type);
         return;
      }

      _thdl = (HANDLE)::_beginthreadex(NULL, 0, _entryPoint->_entry, _argv, CREATE_SUSPENDED, NULL);
      _id = ::GetThreadId(_thdl);
   }

   void threadEntity::run()
   {
      ::ResumeThread(_thdl);
   }

   void threadEntity::stop()
   {
      _stop = true;
   }

   void threadEntity::pause()
   {
      ::SuspendThread(_thdl);
   }

   void threadEntity::resume()
   {
      ::ResumeThread(_thdl);
   }

   void threadEntity::destroy()
   {
      if (_thdl)
      {
         ::CloseHandle(_thdl);
      }
   }

}