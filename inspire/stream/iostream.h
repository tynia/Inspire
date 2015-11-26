#ifndef _INSPIRE_NET_IO_STREAM_H_
#define _INSPIRE_NET_IO_STREAM_H_

#include "endian/endian.h"
#include "istream.h"
#include "ostream.h"

namespace inspire {

   class IOStream : public IStream, public OStream
   {
   public:
      IOStream() : OStream(), IStream() {}
      IOStream(IOStream& rhs) {}
      virtual ~IOStream();

      IOStream operator= (IOStream& rhs);
      // istream
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

      // ostream
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

   class FixedStream : public baseStream
   {
   public:
      virtual ~FixedStream() {}

      FixedStream() : baseStream()
      {}
      FixedStream(const char* in, const int len) : baseStream(in, len)
      {}
      FixedStream(const baseStream* bs) : baseStream(bs)
      {}
      FixedStream(const baseStream& bs) : baseStream(bs)
      {}
   };

   class CIStream : virtual public FixedStream
   {
   public:
      virtual ~CIStream() {}

      CIStream() : FixedStream()
      {}
      CIStream(const char* data, const int len) : FixedStream(data, len)
      {}
      CIStream(const baseStream* bs) : FixedStream(bs)
      {}
      CIStream(const baseStream& bs) : FixedStream(bs)
      {}

      void skip(const size_t size);
      const size_t seekTo(const size_t size);

      //////////////////////////////////////////////////////////////////////////
      CIStream& operator>> (bool& var);
      CIStream& operator>> (char& var);
      CIStream& operator>> (unsigned char& var);
      CIStream& operator>> (float& var);
      CIStream& operator>> (double& var);
      CIStream& operator>> (int& var);
      CIStream& operator>> (unsigned int& var);
      CIStream& operator>> (int64& var);
      CIStream& operator>> (binData& ctx);
   };

   class COStream : virtual public FixedStream
   {
   public:
      virtual ~COStream() {}

      COStream() : FixedStream()
      {}
      COStream(const char* data, const int len) : FixedStream(data, len)
      {}
      COStream(const baseStream* bs) : FixedStream(bs)
      {}
      COStream(const baseStream& bs) : FixedStream(bs)
      {}

      void skip(const size_t size);
      const size_t seekTo(const size_t size);
      //////////////////////////////////////////////////////////////////////////
      COStream& operator<< (const bool& val);
      COStream& operator<< (const char& val);
      COStream& operator<< (const unsigned char& val);
      COStream& operator<< (const float& val);
      COStream& operator<< (const double& val);
      COStream& operator<< (const int& val);
      COStream& operator<< (const unsigned int& val);
      COStream& operator<< (const int64& val);
      COStream& operator<< (const binData& ctx);
   };
}
#endif