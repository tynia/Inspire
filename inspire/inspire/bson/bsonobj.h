#ifndef _INSPIRE_BSON_OBJ_H_
#define _INSPIRE_BSON_OBJ_H_

namespace inspire {

   class BSONElement;
   class BSONDocument
   {
   public:
      BSONDocument();
      BSONDocument(const char* data);
      BSONDocument(const BSONDocument& bson);
      ~BSONDocument();

      bool hasField(const char* field);
      const int getFieldType(const char* field);
      BSONElement getField(const char* field);
      binary getBinaryField(const char* field);
      const char* getStringField(const char* field);
      const double getFloatField(const char* field);
      const int getIntField(const char* field);
      const int64 getInt64Field(const char* field);
      const bool getBoolField(const char* field);

      void append(const char* field, const bool v);
      void append(const char* field, const int v);
      void append(const char* field, const int64 v);
      void append(const char* field, const std::string& v);
      void append(const char* field, const double v);
      void append(const char* field, const binary& v);
      //void append(const char* name, const) //datatime
      //void append(const char* name, const) //oid
      void appendNULL(const char* field);
      void append(const BSONElement& e);

      std::string toString();
      bool isValid();

   public:
      BSONDocument& operator= (const BSONDocument& rhs);
      BSONElement operator[] (const std::string& name);

   private:
      void _parse(const char* data);
      bool _check();
      bool _done();

   public:
      const char* data() const
      {
         return _data;
      }

      const size_t size() const
      {
         return *(size_t*)_data;
      }

   private:
      bool  _serialized;
      char* _data;
   };
}
#endif // !_INSPIRE_BSON_OBJ_H_
