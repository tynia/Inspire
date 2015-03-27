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

   LogManager::LogManager() : _path(NULL)
   {
      _path = LOG_PATH;
      init();
   }

   LogManager::~LogManager()
   {
      _path = NULL;
   }

   LogManager* LogManager::Instance()
   {
      static LogManager _LogManager;
      return &_LogManager;
   }

   void LogManager::init()
   {
      XMLDocument doc;
      bool ret = doc.LoadXML("config.xml");
      if (!ret)
      {
         __asm int 3;
         return;
      }

      IXMLNode* root = doc.FirstChild("config");
      if (root)
      {
         IXMLNode* node = root->FirstChild("logs");
         if (node)
         {
            IXMLNode* child = node->FirstChild("item");
            while (child)
            {
               const char* category = child->GetAttributeValue("category");
               const char* filename = child->GetAttributeValue("filename");
               const char* priority = child->GetAttributeValue("priority");
               int prio = atoi(priority);
               if (category)
               {
                  LogFile* log = new LogFile(filename, prio);
                  //_categorys.push_back(log);
               }
               child = node->NextSibling("item");
            }
         }
      }
   }

}