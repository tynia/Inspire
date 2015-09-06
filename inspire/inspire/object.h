#ifndef _INSPRE_BSON_JSON_H_
#define _INSPRE_BSON_JSON_H_

#include "inspire.h"
#include "basestream.h"

namespace inspire {
   namespace bson {

      class allocator;
      class Object
      {
      public:
         Object();
         Object(const char* str);
         virtual ~Object();

         const char* toString();

         void put(const Element& e);

         template <class T>
         void put(const char* k, T& v);

         void append(const Element& e);

         template <class T>
         void append(const char* k, T& v);

         Object& operator== (const Object& rhs);

      protected:
         bool        _done;
         Element*    _e;
         Element*    _end;
         allocator*  _pool;
         refCounter* _counter;
         const char* _serializedData;
      };
   }
}
#endif