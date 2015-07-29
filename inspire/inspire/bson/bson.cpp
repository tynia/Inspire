#include "bson.h"

namespace inspire {

   namespace bson {

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
         case inspire::bson::VT_MINKEY:
            fmt += "MinKey";
            break;
         case inspire::bson::VT_DOUBLE:
            //TODO:
            break;
         case inspire::bson::VT_STRING:
            fmt += _value.ptr;
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
         case inspire::bson::VT_MAXKEY:
            break;
         default:
            break;
         }
      }

      kvMap::kvMap()
      {

      }

      kvMap::~kvMap()
      {

      }

      void kvMap::put(const char* k, char v)
      {
         _key = k;
         _value.c1 = (unsigned char)v;
      }

      void kvMap::put(const char* k, unsigned char v)
      {
         _key = k;
         _value.c1 = v;
      }

      void kvMap::put(const char* k, bool v)
      {
         _key = k;
         _value.c1 = (char)(v ? 1 : 0);
      }

      void kvMap::put(const char* k, int v)
      {
         _key = k;
         _value.i4 = (unsigned int)v;
      }

      void kvMap::put(const char* k, unsigned v)
      {
         _key = k;
         _value.i4 = v;
      }

      void kvMap::put(const char* k, int64 v)
      {
         _key = k;
         _value.u8 = (uint64)v;
      }

      void kvMap::put(const char* k, uint64 v)
      {
         _key = k;
         _value.u8 = v;
      }

      void kvMap::put(const char* k, double v)
      {
         _key = k;
         _value.u8 = (double)v;
      }

      void kvMap::put(const char* k, const char* v)
      {
         _key = k;
         _value.ptr = v;
      }

      void kvMap::put(const char* k, const std::string& v)
      {
         put(k, v.c_str());
      }

      void kvMap::put(const char* k, const binData& v)
      {
         _key = k;
         _value.bin = &v;
      }

   }
}