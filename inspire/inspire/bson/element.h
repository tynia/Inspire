#ifndef _INSPIRE_BSON_ELEMENT_H_
#define _INSPIRE_BSON_ELEMENT_H_

#include "bson.h"
#include "kvMap.h"

namespace inspire {

   class refCounter;
   namespace bson {

      class Object;
      class Element : public kvMap
      {
      public:
         Element();
         Element(const Element& rhs);
         virtual ~Element();

         Element& operator= (const Element& rhs);

         void replace(const Element& e);

         template <class T>
         void replace(const char* k, T& v);

         void putNull(const char* k);

         const char* valuestr();

         Object toObject();

      protected:
         bool _checkValid();

         void _release();

         void put(const Element& e);

         template <class T>
         void put(const char* k, T& v);

      protected:
         bool        _owned;
         refCounter* _counter;
         Element*    _next;
      };

      template <class T>
      void inspire::bson::Element::put(const char* k, T& v)
      {
         put(k, v);
      }

      template <class T>
      void inspire::bson::Element::replace(const char* k, T& v)
      {
         _release();
         put(k, v);
      }

   }
}
#endif