#ifndef _STREAM_ISTREAM_H_
#define _STREAM_ISTREAM_H_

#include "basestream.h"

class COStream;
class binData;

class CIStream : public bstr
{
public:
   CIStream();
   CIStream(const CIStream& rhs);
   CIStream(const char* src, const uint64 len);
   ~CIStream() {}

   const char* c_str() const { return _data; }

   void skip(uint64 r)
   {
      _rOffset += r;
   }

   CIStream& operator>> (bool& b);
   CIStream& operator>> (char& c);
   CIStream& operator>> (uchar& uc);
   CIStream& operator>> (short& s);
   CIStream& operator>> (ushort& us);
   CIStream& operator>> (float& f);
   CIStream& operator>> (double& d);
   CIStream& operator>> (int& i);
   CIStream& operator>> (uint& ui);
   CIStream& operator>> (int64& i64);
   CIStream& operator>> (uint64& ui64);
   CIStream& operator>> (std::string& str);
   CIStream& operator>> (binData& bin);

private:
   uint64 _rOffset;
};

#endif // _STREAM_ISTREAM_H_