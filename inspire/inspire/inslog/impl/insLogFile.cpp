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
#include "insLogFile.h"
#include "inspire.h"
#include "scopeLock.h"

namespace inspire {

   insLogFile::insLogFile(const char* name, const int priority) : _priority(priority)
   {
      memset(_filename, 0, MAX_LOG_FILE_NAME + 1);
      _init(name);
   }

   void insLogFile::writeLog(const int priority, const char* data)
   {
      if (priority <= _priority)
      {
         return;
      }

      scopeLock lock(&_mtx);
      std::fstream file;
      file.open(_filename, std::ios::out | std::ios::app) ;
      if (file.is_open())
      {
         file.tellg();
         file.write(data, strlen(data)) ;
         file.close();
      }
   }

   void insLogFile::_init(const char* name)
   {
      sprintf_s(_filename, "%s.%s.log", name, typeString(_priority));
   }
}