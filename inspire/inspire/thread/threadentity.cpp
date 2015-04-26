#include "threadentity.h"
#include "entry/entry.h"
#include "entryPoint.h"

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
         LogError("Cannot find entry point, type: %d", _type);
         return;
      }

      _thdl = (HANDLE)::_beginthreadex(NULL, 0, _entryPoint->_entry, _argv, CREATE_SUSPENDED, NULL);
      _id = (int64)::GetThreadId(_thdl);
      LogEvent("create a thread, type: %d, name: %s", _type, _entryPoint->_desc);
   }

   void threadEntity::run()
   {
      ::ResumeThread(_thdl);
   }

   void threadEntity::stop()
   {
      LogEvent("stop thread, type: %d, id: "fmt64", name: %s",
               _type, _id, _entryPoint->_desc);
      _stop = true;
      ::WaitForSingleObject(_thdl, WAIT_OBJECT_0);
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
      LogEvent("destroy thread, id: "fmt64", name: %s", _id, getEntryPointName(_type));
      if (!_stop)
      {
         stop();
      }
      if (_thdl)
      {
         ::CloseHandle(_thdl);
      }
   }

   void threadEntity::kill(int64& exitCode)
   {
      LogEvent("kill thread, id: "fmt64", name: %s", _id, getEntryPointName(_type));
      ::TerminateThread(_thdl, 0);
      ::WaitForSingleObject(_thdl, WAIT_OBJECT_0);
   }

   bool threadEntity::isStopped() const
   {
      return _stop;
   }

   bool threadEntity::isSystemThread() const
   {
      return _entryPoint->_system;
   }

   const char* threadEntity::desc() const
   {
      return _entryPoint->_desc;
   }
}