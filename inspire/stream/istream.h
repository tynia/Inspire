#ifndef _INSPIRE_STREAM_ISTREAM_H_
#define _INSPIRE_STREAM_ISTREAM_H_

#include "baseStream.h"
#include "util/binData.h"

namespace inspire {

   class IStream
   {
   public:
      IStream(const char* src, uint64 len) : _data(src), _size(len) {}
      virtual ~IStream() { _data = NULL, _size = 0; }

   public:
      const char* data() const
      {
         return _data;
      }

      const uint64 size() const { return _size; }

      void skip(uint64 r)
      {
         _rOffset += r;
      }

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
      uint _read(void* buffer, const uint len, const uint toRead);

   protected:
      const char* _data;
      uint64      _size;
      uint64      _rOffset;
   };
}
#endif
