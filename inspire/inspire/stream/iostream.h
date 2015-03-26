#ifndef _INSPIRE_NET_IO_STREAM_H_
#define _INSPIRE_NET_IO_STREAM_H_

#include "basestream.h"
#include "endian/endian.h"

namespace inspire {

   // define ENDIAN
#ifdef _INSPIRE_SERVER_
   typedef Endian ENDIAN;
#else
   typedef FixedEndian ENDIAN;
#endif

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
      CIStream& operator>> (context& ctx);

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
      COStream& operator<< (const context& ctx);
   };
}
#endif