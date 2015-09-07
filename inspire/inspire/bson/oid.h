#ifndef _INSPIRE_BSON_OID_H_
#define _INSPIRE_BSON_OID_H_

namespace inspire {

   namespace bson {

      class ObjectId
      {
      public:
         ObjectId();
         virtual ~ObjectId();

         static ObjectId genOid();
      };
   }
}
#endif
