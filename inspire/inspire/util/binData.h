#ifndef _INSPIRE_UTIL_BIN_DATA_H_
#define _INSPIRE_UTIL_BIN_DATA_H_

#include "inspire.h"
#include "allocator.h"

namespace inspire {

   static allocator* _allocator = allocator::instance();

   struct binData
   {
      binData() : owned(false), _data(NULL), _len(0)
      {}
      binData(const char *data, const unsigned len) : owned(false),
         _data(const_cast<char*>(data)),
         _len(len)
      {}

      ~binData()
      {
         if (owned)
         {
            delete[] _data;
            owned = false;
         }
         _data = NULL;
         _len = 0;
      }

      void reverse(const unsigned size)
      {
         if (_len > size)
         {
            return;
         }
         else
         {
            if (owned)
            {
               delete[] _data;
               _data = NULL;
            }
            else
            {
               _data = NULL;
            }

            owned = true;
            _data = new char[size + 1];
            _data[size] = '\0';
         }
      }

      bool     owned;
      unsigned _len;
      char    *_data;
   };
}
#endif
