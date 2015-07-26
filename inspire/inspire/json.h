#ifndef _INSPRE_BSON_JSON_H_
#define _INSPRE_BSON_JSON_H_

namespace inspire {
   namespace json {
      enum vType
      {
         VT_INT,
         VI_BOOL,
         VT_DOUBLE,
         VT_DATATIME,
         VT_STRING,
      };

      template <class T>
      class Value
      {
      public:
         virtual ~Value() {}

         virtual const char* toString();

         const char* key() const
         {
            return _key.operator->() ;
         }

      protected:
         vType _type;
         refPointer<char> _key;
         T _value;
      };

      
      class Element
      {
      public:
         Element();
         Element(const Element& rhs);
         virtual ~Element();

         void put(const Element& e);

         template <class T>
         void put(const char* k, T& v);

         void append(const Element& e);

         template <class T>
         void append(const char* k, T& v);

         void remove(const char* k);

         void replace(const Element& e);

         template <class T>
         void replace(const char* k, T& v);

         const char* valuestr();

         Object& toObject();

      protected:
         
         Element* _next;
         Element* _end;
      };

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

      protected:
         Element* _e;
         allocator *_pool;
      };
   }
}
#endif