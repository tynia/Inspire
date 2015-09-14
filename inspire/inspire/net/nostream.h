#ifndef _INSPIRE_NET_NOStream_H_
#define _INSPIRE_NET_NOStream_H_

#include "baseStream.h"
#include "binData.h"

namespace inspire {

   class NOStream : virtual public baseStream
   {
      static const uint BLOCKSIZE = 1024;
   public:
      NOStream(allocator* al = NULL, const uint blockSize = BLOCKSIZE);
      virtual ~NOStream();
   public:
      const char* data() const { return _data; }

      const uint64 capacity() const { return _capacity; }

      const uint64 size() const { return _wOffset; }

      void put(const char c);

      NOStream& operator<< (const bool b);
      NOStream& operator<< (const char c);
      NOStream& operator<< (const uchar uc);
      NOStream& operator<< (const short s);
      NOStream& operator<< (const ushort us);
      NOStream& operator<< (const float f);
      NOStream& operator<< (const double d);
      NOStream& operator<< (const int i);
      NOStream& operator<< (const uint ui);
      NOStream& operator<< (const int64& i64);
      NOStream& operator<< (const uint64& ui64);
      NOStream& operator<< (const binData& bin);
      NOStream& operator<< (const std::string& str);
   };
}
#endif