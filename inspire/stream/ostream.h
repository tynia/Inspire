#ifndef _STREAM_OSTREAM_H_
#define _STREAM_OSTREAM_H_

#include "basestream.h"
#include "bindata.h"

class CIStream;
class binData;

class COStream : public bstr
{
public:
   COStream();
   COStream(const COStream& os);
   COStream(const char* src, const uint64 len);
   ~COStream() {}

   const char* c_str() const { return _data; }

   void skip(uint64 w)
   {
      _wOffset += w;
   }

   COStream& operator<< (bool b);
   COStream& operator<< (char c);
   COStream& operator<< (uchar uc);
   COStream& operator<< (short s);
   COStream& operator<< (ushort us);
   COStream& operator<< (float f);
   COStream& operator<< (double d);
   COStream& operator<< (int i);
   COStream& operator<< (uint ui);
   COStream& operator<< (int64 i64);
   COStream& operator<< (uint64 ui64);
   COStream& operator<< (const char* str);
   COStream& operator<< (std::string& str);
   COStream& operator<< (binData& bin);

private:
   uint64 _wOffset;
};

#endif //_STREAM_OSTREAM_H_