#ifndef _INSPIRE_NET_NIStream_H_
#define _INSPIRE_NET_NIStream_H_

#include "baseStream.h"
#include "binData.h"

namespace inspire {

   class NIStream : virtual public baseStream
   {
   public:
      NIStream(const char* buffer, uint64 len);
      virtual ~NIStream();

      virtual void skip(uint64 w) { _rOffset += w; }
   public:
      const char* data() const
      {
         return _data;
      }

      void skip(uint64 r)
      {
         _rOffset += r;
      }

      char get();

      NIStream& operator>> (bool& b);
      NIStream& operator>> (char& c);
      NIStream& operator>> (uchar& uc);
      NIStream& operator>> (short& s);
      NIStream& operator>> (ushort& us);
      NIStream& operator>> (float& f);
      NIStream& operator>> (double& d);
      NIStream& operator>> (int& i);
      NIStream& operator>> (uint& ui);
      NIStream& operator>> (int64& i64);
      NIStream& operator>> (uint64& ui64);
      NIStream& operator>> (binData& bin);

   private:
      void _readBuffer(void* buffer, const uint len, const uint toRead);

   protected:
      uint64 _rOffset;
   };
}
#endif
