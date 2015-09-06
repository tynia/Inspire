#ifndef _INSPIRE_BSON_KVMAP_H_
#define _INSPIRE_BSON_KVMAP_H_

#include "inspire.h"

namespace inspire {

   namespace bson {

      class binData;
      class kvMap
      {
      protected:
         kvMap();
         virtual ~kvMap();

         const char* toString();

         const unsigned vSize() const
         {
            return 0;
         }

         const unsigned kSize() const
         {
            return strlen(_key);
         }

         const int _type() const
         {
            return _vtype;
         }

         void put(const char* k, bool v);
         void put(const char* k, int v);
         void put(const char* k, int64 v);
         void put(const char* k, double v);
         void put(const char* k, const char* v);
         void put(const char* k, const std::string& v);

         // date
         // object id
         // array
         // null
         void put(const char type, const char* k,
                  const char* pValue, const unsigned len);

      protected:
         char _vtype;
         const char* _key;
         char* _value;
      };
   }
}
#endif
