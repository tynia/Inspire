#include "include/bsonobj.h"

namespace inspire {

   BSONDocument::BSONDocument() : _serialized(false), _data(NULL)
   {

   }

   BSONDocument::BSONDocument(const char* data)
   {
      _parse(data);
   }

   BSONDocument::BSONDocument(const BSONDocument& rhs)
   {
      _serialized = rhs._serialized;
      _data = rhs._data;
   }

   BSONDocument::~BSONDocument()
   {
      if (_data)
      {
         delete [] _data;
      }
      _serialized = false;
   }
}