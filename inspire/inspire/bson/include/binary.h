#ifndef _INSPIRE_BSON_BINARY_H_
#define _INSPIRE_BSON_BINARY_H_

#include "util/bson.h"

namespace inspire {

   class binary
   {
   public:
      binary(const char* data, const size_t len) : _data(data), _len(len)
      {}

      ~binary()
      {
         _data = NULL;
         _len = 0;
      }

      const size_t size() const
      {
         return _len;
      }

   private:
      const char* _data;
      size_t      _len;
   };
}
#endif