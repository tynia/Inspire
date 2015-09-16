#include "kvMap.h"
#include "bson.h"
#include "allocator.h"

namespace inspire {

   namespace bson {

      inspire::allocator* _allocator = memMgr();

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

      kvMap::kvMap() : _vtype(VT_EOO), _totalSize(0), _key(NULL), _value(NULL), _ptr(NULL)
      {}

      kvMap::~kvMap()
      {
         _vtype = VT_EOO;
         _totalSize = 0;
         _key = NULL;
         _value = NULL;

         // release memory to pool
         _allocator->dealloc(_ptr);
         _ptr = NULL;
      }

      void kvMap::put(const char* k, bool v)
      {
         _vtype = VT_BOOL;
         /* ----------|***type***|---|*key size*|---|*value size*| */
         _totalSize = sizeof(char) + strlen(k) + 1 + sizeof(bool);

         _ptr = _allocator->alloc(_totalSize);
         INSPIRE_ASSERT(NULL != _ptr, "Failed to allocate memory, size = %d", _totalSize);

         _prepare(k);

         _w.appendBool(v);
      }

      void kvMap::put(const char* k, int v)
      {
         _vtype = VT_INT;
         /* ----------|***type***|---|*key size*|---|*value size*| */
         _totalSize = sizeof(char) + strlen(k) + 1 + sizeof(int);

         _prepare(k);

         _w.appendInt(v);
      }

      void kvMap::put(const char* k, int64 v)
      {
         _vtype = VT_LONG;
         /* ----------|***type***|---|*key size*|---|*value size*| */
         _totalSize = sizeof(char) + strlen(k) + 1 + sizeof(int64);

         _prepare(k);

         _w.appendInt64(v);
      }

      void kvMap::put(const char* k, double v)
      {
         _vtype = VT_DOUBLE;
         /* ----------|***type***|---|*key size*|---|*value size*| */
         _totalSize = sizeof(char) + strlen(k) + 1 + sizeof(double);

         _prepare(k);

         _w.appendDouble(v);
      }

      void kvMap::put(const char* k, const char* v)
      {
         _vtype = VT_STRING;
         /* ----------|***type***|---|*key size*|---|*value size*| */
         _totalSize = sizeof(char) + strlen(k) + 1 + strlen(v) + 1;

         _prepare(k);

         _w.appendString(v, strlen(v));
      }

      void kvMap::put(const char* k, const std::string& v)
      {
         _vtype = VT_STRING;
         /* ----------|***type***|---|*key size*|---|**value size**| */
         _totalSize = sizeof(char) + strlen(k) + 1 + v.length() + 1;

         _prepare(k);

         _w.appendString(v.c_str(), v.length());
      }

      void kvMap::put(const char type, const char* k, const binData& bin)
      {
         _vtype = type;
         /* ----------|***type***|---|*key size*|---|**value size**| */
         _totalSize = sizeof(char) + strlen(k) + 1 + sizeof(int) + 1 + bin.len;

         _prepare(k);
         _w.appendInt(bin.len);
         _w.appendChar(type);
         _w.appendBin(bin.data, bin.len);
      }

      void kvMap::_verify(unsigned toWriteSize)
      {

      }

      void kvMap::_prepare(const char* k)
      {
         _ptr = _allocator->alloc(_totalSize);
         INSPIRE_ASSERT(NULL != _ptr, "Failed to allocate memory, size = %d", _totalSize);

         _w.init(_ptr, _totalSize);

         _w.appendChar(_vtype);

         _key = _w.curPtr();
         _w.appendString(k, strlen(k));

         _value = _w.curPtr();
      }

   }
}