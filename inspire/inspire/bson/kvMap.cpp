#include "kvMap.h"
#include "bson.h"
#include "allocator.h"

namespace inspire {

   namespace bson {

      inspire::allocator* _allocator = GetAllocator();

      const char* kvMap::toString()
      {
         if (_vtype == VT_EOO)
         {
            return "{}";
         }

         std::string fmt("{");
         fmt = _key;
         fmt += ":";
         switch (_vtype)
         {
         case inspire::bson::VT_DOUBLE:
            //TODO:
            break;
         case inspire::bson::VT_STRING:
            break;
         case inspire::bson::VT_OBJECT:
            break;
         case inspire::bson::VT_ARRAY:
            break;
         case inspire::bson::VT_BINDATA:
            break;
         case inspire::bson::VT_UNDEFINED:
            break;
         case inspire::bson::VT_OID:
            break;
         case inspire::bson::VT_BOOL:
            break;
         case inspire::bson::VT_DATE:
            break;
         case inspire::bson::VT_NULL:
            break;
         case inspire::bson::VT_REGEX:
            break;
         case inspire::bson::VT_DBREF_DEPRECATED:
            break;
         case inspire::bson::VT_CODE_DEPRECATED:
            break;
         case inspire::bson::VT_SYMBOL:
            break;
         case inspire::bson::VT_CODE:
            break;
         case inspire::bson::VT_INT:
            break;
         case inspire::bson::VT_TIMESTAMP:
            break;
         case inspire::bson::VT_LONG:
            break;
         default:
            break;
         }
      }

      kvMap::kvMap() : _vtype(VT_EOO)
      {}

      kvMap::~kvMap()
      {}

      void kvMap::put(const char* k, bool v)
      {
         _value = _allocator->alloc(sizeof(v));
         Writer writer(_value, sizeof(v));
         writer.appendChar(VT_BOOL);
         writer.appendBin(k, strlen(k));
         writer.appendBool(v);
      }

      void kvMap::put(const char* k, int v)
      {
         _value = _allocator->alloc(sizeof(v));
         Writer writer(_value, sizeof(v));
         writer.appendInt(VT_INT);
         writer.appendBin(k, strlen(k));
         writer.appendInt(v);
      }

      void kvMap::put(const char* k, int64 v)
      {
         _value = _allocator->alloc(sizeof(v));
         Writer writer(_value, sizeof(v));
         writer.appendInt64(VT_LONG);
         writer.appendBin(k, strlen(k));
         writer.appendInt64(v);
      }

      void kvMap::put(const char* k, double v)
      {
         _value = _allocator->alloc(sizeof(v));
         Writer writer(_value, sizeof(v));
         writer.appendInt64(VT_DOUBLE);
         writer.appendBin(k, strlen(k));
         writer.appendDouble(v);
      }

      void kvMap::put(const char* k, const char* v)
      {
         _value = _allocator->alloc(sizeof(v));
         Writer writer(_value, sizeof(v));
         writer.appendInt64(VT_STRING);
         writer.appendBin(k, strlen(k));
         writer.appendInt(strlen(v) + 1);
         writer.appendBin(v, strlen(v) + 1);
      }

      void kvMap::put(const char* k, const std::string& v)
      {
         _value = _allocator->alloc(sizeof(v));
         Writer writer(_value, sizeof(v));
         writer.appendInt64(VT_STRING);
         writer.appendBin(k, strlen(k));
         writer.appendInt(v.length());
         writer.appendBin(v.c_str(), v.length() + 1);
      }

      void kvMap::put(const char type, const char* k, const char* pValue, unsigned len)
      {
         unsigned keyLen = strlen(k);
         unsigned total = sizeof(char) + (keyLen + 1) + sizeof(int) + len;

         _value = _allocator->alloc(total);
         Writer writer(_value, total);

         writer.appendInt64(type);
         writer.appendBin(k, strlen(k));
         writer.appendInt(len);
         writer.appendBin(pValue, len);
      }
   }
}