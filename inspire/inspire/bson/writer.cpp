#include "writer.h"

namespace inspire {

   namespace bson {

      /// bson element writer
      writer::writer() : _ptr(NULL), _cur(NULL), _end(NULL)
      {}

      writer::~writer()
      {
         _ptr = NULL;
         _cur = NULL;
         _end = NULL;
      }

      void writer::init(const char* ptr, const unsigned len)
      {
         _ptr = ptr;
         _cur = ptr;
         _end = _ptr + len;
      }

      void writer::appendChar(char c)
      {
         _verify(sizeof(char));

         memcpy((void*)_cur, &c, sizeof(char));
         _cur += sizeof(char);
      }

      void writer::appendUChar(unsigned char uc)
      {
         _verify(sizeof(unsigned char));

         memcpy((void*)_cur, &uc, sizeof(unsigned char));
         _cur += sizeof(unsigned char);
      }

      void writer::appendBool(bool b)
      {
         appendChar((char)(b ? 1 : 0));
      }

      void writer::appendShort(short s)
      {
         _verify(sizeof(short));

         memcpy((void*)_cur, &s, sizeof(short));
         _cur += sizeof(short);
      }

      void writer::appendInt(int i)
      {
         _verify(sizeof(int));

         memcpy((void*)_cur, &i, sizeof(int));
         _cur += sizeof(int);
      }

      void writer::appendUInt(unsigned ui)
      {
         _verify(sizeof(unsigned));

         memcpy((void*)_cur, &ui, sizeof(unsigned));
         _cur += sizeof(unsigned);
      }

      void writer::appendInt64(int64 i64)
      {
         _verify(sizeof(int64));

         memcpy((void*)_cur, &i64, sizeof(int64));
         _cur += sizeof(int64);
      }

      void writer::appendUInt64(uint64 ui64)
      {
         _verify(sizeof(uint64));

         memcpy((void*)_cur, &ui64, sizeof(uint64));
         _cur += sizeof(uint64);
      }

      void writer::appendDouble(double d)
      {
         _verify(sizeof(double));

         memcpy((void*)_cur, &d, sizeof(double));
         _cur += sizeof(double);
      }

      void writer::appendString(const char* str, unsigned len)
      {
         _verify(len + 1);

         memcpy((void*)_cur, str, len);
         memset((void*)_cur, 0, 1);
         _cur += len + 1;
      }

      void writer::appendBin(const char* bin, unsigned len)
      {
         _verify(len);

         memcpy((void*)_cur, bin, len);
         _cur += len;
      }

      void writer::_verify(unsigned size)
      {
         if (_cur >= _end || _cur + size > _end)
         {
            LogError("Try to write out of buffer size, "
                     "begin: 0x%x, current: 0x%x, end: 0x%x. "
                     "Only [%d]bytes left, want to write [%d]bytes",
                     (uint64)_ptr, uint64(_cur), uint64(_end), _end - _cur, size);
            Panic();
         }
      }
   }
}