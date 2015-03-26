#ifndef _INSPIRE_BSON_ELEMENT_H_
#define _INSPIRE_BSON_ELEMENT_H_

#include "util/bson.h"

namespace inspire {

   class BSONElement
   {
   public:
      BSONElement();
      BSONElement(const char* data);
      ~BSONElement();

   public:
      const int type() const;
      const char* fieldName() const;
      const char* value() const;

      std::string toDocument();
      std::string toString();

   private:
      bool _check() const;
      const size_t _fieldNameSize() const;

   private:
      const char* _data;
   };
}
#endif