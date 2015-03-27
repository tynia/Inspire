/*******************************************************************************
   Copyright (C) 2015 tynia.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.
   
   Any problem, please ping xduilib@gmail.com, free service may be supported.
*******************************************************************************/
#include "include/insLogManager.h"
#include "include/insLogFile.h"

namespace inspire {

   insLogManager::insLogManager() : IControl(MOD_LOG), _path(NULL)
   {
   }

   insLogManager::~insLogManager()
   {
      _path = NULL;
   }

   void insLogManager::initialize()
   {
      _path = LOG_PATH;
   }

   void insLogManager::active()
   {
      // init member
   }

   void insLogManager::destroy()
   {
      // destroy member
      _path = NULL;
   }

   void insLogManager::writeLog(const int priority, const char* data)
   {
      IWriteable* inst = _logMap[priority];
      if (NULL != inst)
      {
         inst->writeLog(priority, data);
      }
   }

   insLogManager extLogMgr;

   IWriteable* getLogMgr()
   {
      return &extLogMgr;
   }
}