#ifndef _INSPIRE_BSON_ELEMENT_H_
#define _INSPIRE_BSON_ELEMENT_H_

#include "bson.h"

namespace inspire {

   namespace bson {

      class Object;
      class Element : virtual public kvMap
      {
      public:
         Element();
         Element(const Element& rhs);
         virtual ~Element();

         void replace(const Element& e);

         template <class T>
         void replace(const char* k, T& v);

         void putNull(const char* k);

         const char* valuestr();

         Object& toObject();

      protected:
         bool _checkValid();

         void put(const Element& e);

         template <class T>
         void put(const char* k, T& v);

      protected:
         Element* _next;
      };
   }
}
#endif