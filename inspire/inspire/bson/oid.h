#ifndef _INSPIRE_BSON_OID_H_
#define _INSPIRE_BSON_OID_H_

namespace inspire {

   namespace bson {

      class ObjectId
      {
      public:
         ObjectId();
         ObjectId(const char* oid);
         virtual ~ObjectId();

         static ObjectId genOid();

         const char* toString();

         bool operator ==(const ObjectId& rhs);
         bool operator <(const ObjectId& rhs);
         bool operator >(const ObjectId& rhs);
         bool operator <=(const ObjectId& rhs);
         bool operator >=(const ObjectId& rhs);
         ObjectId operator =(const ObjectId& rhs);

      private:
         void _generate();

      private:
         unsigned char _data[12];
      };
   }
}
#endif
