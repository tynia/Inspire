#ifndef _STREAM_NET_ISTREAM_H_
#define _STREAM_NET_ISTREAM_H_

#include "basestream.h"
#include "endian.h"

class NOStream;
class binData;

class NIStream : public bstr
{
public:
   NIStream(ENDIAN endian = ENDIAN_LITTLE);
   NIStream(const NIStream& rhs);
   NIStream(const char* src, const uint64 len, ENDIAN endian = ENDIAN_LITTLE);
   ~NIStream() {}

   const char* c_str() const { return _data; }

   void skip(uint64 r)
   {
      _rOffset += r;
   }

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
   NIStream& operator>> (std::string& str);
   NIStream& operator>> (binData& bin);

private:
   ENDIAN _endian;
   uint64 _rOffset;
};

#endif // _STREAM_NET_ISTREAM_H_