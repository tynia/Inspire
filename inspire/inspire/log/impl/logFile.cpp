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
#include "logFile.h"

namespace inspire {

   LogFile::LogFile(const char* filename, int priority) : _priority(priority)
   {
      memset(_filename, 0, MAX_LOG_FILE_NAME + 1) ;
      memcpy(_filename, filename, MAX_LOG_FILE_NAME) ;
   }

   void LogFile::WriteLog(int priority, const char* str)
   {
      if (priority <= _priority)
      {
         return;
      }

      std::fstream file(_filename, std::ios::out | std::ios::app) ;
      if (file.is_open())
      {
         file.tellg();
         file.write(str, strlen(str)) ;
         file.close();
      }
   }

}