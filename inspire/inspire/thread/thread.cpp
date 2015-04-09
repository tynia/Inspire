#include "thread.h"

namespace inspire {

   threadEntity::threadEntity(const int64 type) : _type(type), _id(0), _hThread(NULL)
   {}

   threadEntity::~threadEntity()
   {
      if (_hThread)
      {
         CloseHandle(_hThread);
      }
   }
}