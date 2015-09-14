#include "nistream.h"
#include "endian/endian.h"

namespace inspire {

   NIStream::NIStream(const char* buffer, uint64 len)
      : baseStream(buffer, len), _rOffset(0)
   {}

   NIStream::~NIStream()
   {
      _rOffset = 0;
   }

   char NIStream::get()
   {
      char c;
      _readBuffer(&c, sizeof(char), sizeof(char));
      return c;
   }

   NIStream& NIStream::operator>>(bool& b)
   {
      _readBuffer(&b, sizeof(bool), sizeof(bool));
      return *this;
   }

   NIStream& NIStream::operator>>(char& c)
   {
      _readBuffer(&c, sizeof(char), sizeof(char));
      return *this;
   }

   NIStream& NIStream::operator>>(uchar& uc)
   {
      _readBuffer(&uc, sizeof(uchar), sizeof(uchar));
      return *this;
   }

   NIStream& NIStream::operator>>(short& s)
   {
      short tmp = 0;
      _readBuffer(&tmp, sizeof(short), sizeof(short));
      s = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(ushort& us)
   {
      ushort tmp = 0;
      _readBuffer(&tmp, sizeof(ushort), sizeof(ushort));
      us = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(float& f)
   {
      float tmp = 0.0f;
      _readBuffer(&tmp, sizeof(float), sizeof(float));
      f = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(double& d)
   {
      double tmp = 0.0f;
      _readBuffer(&tmp, sizeof(double), sizeof(double));
      d = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(int& i)
   {
      int tmp = 0;
      _readBuffer(&tmp, sizeof(int), sizeof(int));
      i = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(uint& ui)
   {
      uint tmp = 0;
      _readBuffer(&tmp, sizeof(uint), sizeof(uint));
      ui = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(int64& i64)
   {
      uint64 tmp = 0;
      _readBuffer(&tmp, sizeof(int64), sizeof(int64));
      i64 = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(uint64& ui64)
   {
      uint64 tmp = 0;
      _readBuffer(&tmp, sizeof(uint64), sizeof(uint64));
      ui64 = ENDIAN::N2H(tmp);
      return *this;
   }

   NIStream& NIStream::operator>>(binData& bin)
   {
      uint tmp = 0;
      _readBuffer(&tmp, sizeof(uint), sizeof(uint));
      bin.len = ENDIAN::N2H(tmp);
      bin.reverse(bin.len);
      _readBuffer(&bin.data, bin.len, bin.len);
      return *this;
   }

   void NIStream::_readBuffer(void* buffer, const uint len, const uint toRead)
   {
      uint64 r = _read(_rOffset, toRead, buffer, len);
      if (r < toRead)
      {
         LogEvent("Reach end of stream, no more data to read");
      }
      _rOffset += r;
   }

}