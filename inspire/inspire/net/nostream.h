#ifndef _INSPIRE_NET_OSTREAM_H_
#define _INSPIRE_NET_OSTREAM_H_

#include "baseStream.h"
#include "binData.h"

namespace inspire {

   class OStream : virtual public baseStream
   {
      static const uint BLOCKSIZE = 1024;
   public:
      OStream(allocator* al = NULL, const uint blockSize = BLOCKSIZE);
      OStream(OStream& rhs);
      virtual ~OStream();

      OStream operator= (OStream& rhs);
   public:
      const char* data() const { return _data; }

      const uint64 capacity() const { return _capacity; }

      const uint64 size() const { return _wOffset; }

      void put(const char c);

      OStream& operator<< (const bool b);
      OStream& operator<< (const char c);
      OStream& operator<< (const uchar uc);
      OStream& operator<< (const short s);
      OStream& operator<< (const ushort us);
      OStream& operator<< (const float f);
      OStream& operator<< (const double d);
      OStream& operator<< (const int i);
      OStream& operator<< (const uint ui);
      OStream& operator<< (const int64& i64);
      OStream& operator<< (const uint64& ui64);
      OStream& operator<< (const binData& bin);
      OStream& operator<< (const std::string& str);
   };
}
#endif