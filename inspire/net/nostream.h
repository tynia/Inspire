#ifndef _INSPIRE_NET_NOStream_H_
#define _INSPIRE_NET_NOStream_H_

#include "stream/baseStream.h"
#include "binData.h"

namespace inspire {

   class NOStream : virtual public baseStream
   {
   public:
      NOStream();
      virtual ~NOStream();
   public:
      const char* data() const { return _data; }

      const uint capacity() const { return _capacity; }

      const uint size() const { return _wOffset; }

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