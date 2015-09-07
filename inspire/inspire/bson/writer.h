#ifndef _INSPIRE_BSON_WRITER_H_
#define _INSPIRE_BSON_WRITER_H_

#include "inspire.h"
#include "noncopyable.h"

namespace inspire {

   namespace bson {

      class writer : public noncopyable
      {
      public:
         writer();
         ~writer();

      public:
         void init(const char* ptr, const unsigned len);
         const char* curPtr() const
         {
            return _cur;
         }

         void appendChar(char c);
         void appendUChar(unsigned char uc);
         void appendBool(bool b);
         void appendShort(short s);
         void appendInt(int i);
         void appendUInt(unsigned ui);
         void appendInt64(int64 i64);
         void appendUInt64(uint64 ui64);
         void appendDouble(double d);
         void appendString(const char* str, unsigned len);
         void appendBin(const char* bin, unsigned len);

      private:
         void _verify(unsigned toWriteSize);

      private:
         const char* _end;
         const char* _cur;
         const char* _ptr;
      };
   }
}
#endif