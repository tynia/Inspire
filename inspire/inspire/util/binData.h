#ifndef _INSPIRE_UTIL_BIN_DATA_H_
#define _INSPIRE_UTIL_BIN_DATA_H_

#include "inspire.h"
#include "allocator.h"

namespace inspire {

   static allocator* _allocator = allocator::instance();

   struct binData
   {
      binData() : owned(true), data(NULL), len(0)
      {}
      binData(const char *data, const uint len)
         : owned(false), data(const_cast<char*>(data)), len(len)
      {}

      ~binData()
      {
         if (owned)
         {
            delete[] data;
            owned = false;
         }
         data = NULL;
         len = 0;
      }

      void reverse(const uint size)
      {
         if (len > size)
         {
            return;
         }
         else
         {
            if (owned)
            {
               delete[] data;
               data = NULL;
            }
            else
            {
               data = NULL;
            }

            owned = true;
            data = new char[size + 1];
            data[size] = '\0';
         }
      }

      bool  owned;
      uint  len;
      char *data;
   };
}
#endif
