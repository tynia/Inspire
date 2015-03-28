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
#ifndef _INSPIRE_LOG_FILE_H_
#define _INSPIRE_LOG_FILE_H_

#include "include/log.h"

namespace inspire {

   class IWriteLog
   {
   public:
      virtual ~IWriteLog() {}

      virtual void writeLog(const int priority, const char* data) = 0;
   };

   class insLogFile : public IWriteLog
   {
   public:
      insLogFile(const char* name, const int priority = LOG_DEBUG);
      virtual ~insLogFile() {};

      virtual void writeLog(const int priority, const char* data);

   protected:
      void _init(const char* name);

   protected:
      int  _priority;
      // mutexLock
      char _filename[MAX_LOG_FILE_NAME + 1];
   };

}
#endif