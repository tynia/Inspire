#ifndef _INSPIRE_STREAM_ISTREAM_H_
#define _INSPIRE_STREAM_ISTREAM_H_

#include "baseStream.h"
#include "binData.h"

namespace inspire {

   class IStream : virtual public baseStream
   {
   public:
      IStream(const char* buffer, uint64 len);
      virtual ~IStream();

      const char* data() const
      {
         return _data;
      }

      void skip(uint64 r)
      {
         _rOffset += r;
      }

      char get();

      IStream& operator>> (bool& b);
      IStream& operator>> (char& c);
      IStream& operator>> (uchar& uc);
      IStream& operator>> (short& s);
      IStream& operator>> (ushort& us);
      IStream& operator>> (float& f);
      IStream& operator>> (double& d);
      IStream& operator>> (int& i);
      IStream& operator>> (uint& ui);
      IStream& operator>> (int64& i64);
      IStream& operator>> (uint64& ui64);
      IStream& operator>> (binData& bin);

   private:
      void _readBuffer(void* buffer, const uint len, const uint toRead);

   protected:
      uint64 _rOffset;
   };
}
#endif
