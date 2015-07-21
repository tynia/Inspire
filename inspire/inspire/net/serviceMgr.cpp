#include "serviceMgr.h"

namespace inspire {

   insServiceMgr::insServiceMgr()
   {

   }

   insServiceMgr::~insServiceMgr()
   {

   }

   insServiceMgr* insServiceMgr::instance()
   {
      static insServiceMgr svcMgr;
      return &svcMgr;
   }

   
}