#ifndef _INSPIRE_BSON_KVMAP_H_
#define _INSPIRE_BSON_KVMAP_H_

#include "inspire.h"
#include "writer.h"

namespace inspire {

   namespace bson {

      class binData;
      class kvMap
      {
      protected:
         kvMap();
         virtual ~kvMap();

         const char* toString();

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

      private:
         void _verify(unsigned toWriteSize);
         void _prepare(const char* k);

      protected:
         char _vtype;
         unsigned _totalSize;
         const char* _key;
         const char* _value;
      private:
         const char* _ptr;
         writer      _w;
      };
   }
}
#endif
