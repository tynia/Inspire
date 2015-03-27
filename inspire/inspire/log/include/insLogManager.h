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
#ifndef _INSPIRE_LOG_MANAGER_H_
#define _INSPIRE_LOG_MANAGER_H_

#include "noncopyable.h"

namespace inspire {

static const char* LOG_PATH = "./Logs/";

class LogManager : public noncopyable
{
public:
   virtual ~LogManager();
   static LogManager* Instance();

private:
   LogManager() ;
   void init();

private:
   const char* _path;
};

}

#endif