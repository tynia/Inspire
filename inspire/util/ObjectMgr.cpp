#include "ObjectMgr.h"
#include "assert.h"

namespace inspire {

   ObjectMgr::ObjectMgr(AllocatorMgr* mgr) : _alMgr(mgr)
   {
      STRONG_ASSERT(NULL != mgr, "AllocatorMgr cannot be NULL");
   }

   ObjectMgr::~ObjectMgr()
   {
      _alMgr = NULL;
   }

   ObjectMgr* ObjectMgr::instance()
   {
      static ObjectMgr objMgr(AllocatorMgr::instance());
      return &objMgr;
   }
}