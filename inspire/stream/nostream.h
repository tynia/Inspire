#ifndef _STREAM_NET_OSTREAM_H_
#define _STREAM_NET_OSTREAM_H_

#include "basestream.h"
#include "endian.h"

class binData;

class NOStream : public bstr
{
public:
   NOStream(ENDIAN endian = ENDIAN_LITTLE);
   NOStream(const NOStream& os);
   NOStream(const char* src, const uint64 len, ENDIAN endian = ENDIAN_LITTLE);
   ~NOStream() {}

   const char* c_str() const { return _data; }

   void skip(uint64 w)
   {
      _wOffset += w;
   }

   NOStream& operator<< (bool b);
   NOStream& operator<< (char c);
   NOStream& operator<< (uchar uc);
   NOStream& operator<< (short s);
   NOStream& operator<< (ushort us);
   NOStream& operator<< (float f);
   NOStream& operator<< (double d);
   NOStream& operator<< (int i);
   NOStream& operator<< (uint ui);
   NOStream& operator<< (int64 i64);
   NOStream& operator<< (uint64 ui64);
   NOStream& operator<< (const char* str);
   NOStream& operator<< (std::string& str);
   NOStream& operator<< (binData& bin);

private:
   ENDIAN _endian;
   uint64 _wOffset;
};

#endif // _STREAM_NET_OSTREAM_H_