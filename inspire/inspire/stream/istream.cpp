#include "istream.h"

namespace inspire {

   IStream::IStream(const char* buffer, uint64 len)
      : baseStream(buffer, len), _rOffset(0)
   {}

   IStream::~IStream()
   {
      _rOffset = 0;
   }

   char IStream::get()
   {
      char c;
      _readBuffer(&c, sizeof(char), sizeof(char));
      return c;
   }

   IStream& IStream::operator>>(bool& b)
   {
      _readBuffer(&b, sizeof(bool), sizeof(bool));
      return *this;
   }

   IStream& IStream::operator>>(char& c)
   {
      _readBuffer(&c, sizeof(char), sizeof(char));
      return *this;
   }

   IStream& IStream::operator>>(uchar& uc)
   {
      _readBuffer(&uc, sizeof(uchar), sizeof(uchar));
      return *this;
   }

   IStream& IStream::operator>>(short& s)
   {
      _readBuffer(&s, sizeof(short), sizeof(short));
      return *this;
   }

   IStream& IStream::operator>>(ushort& us)
   {
      _readBuffer(&us, sizeof(ushort), sizeof(ushort));
      return *this;
   }

   IStream& IStream::operator>>(float& f)
   {
      _readBuffer(&f, sizeof(float), sizeof(float));
      return *this;
   }

   IStream& IStream::operator>>(double& d)
   {
      _readBuffer(&d, sizeof(double), sizeof(double));
      return *this;
   }

   IStream& IStream::operator>>(int& i)
   {
      _readBuffer(&i, sizeof(int), sizeof(int));
      return *this;
   }

   IStream& IStream::operator>>(uint& ui)
   {
      _readBuffer(&ui, sizeof(uint), sizeof(uint));
      return *this;
   }

   IStream& IStream::operator>>(int64& i64)
   {
      _readBuffer(&i64, sizeof(int64), sizeof(int64));
      return *this;
   }

   IStream& IStream::operator>>(uint64& ui64)
   {
      _readBuffer(&ui64, sizeof(uint64), sizeof(uint64));
      return *this;
   }

   IStream& IStream::operator>>(binData& bin)
   {
      _readBuffer(&bin.len, sizeof(uint), sizeof(uint));
      bin.reverse(bin.len);
      _readBuffer(&bin.data, bin.len, bin.len);
      return *this;
   }

   void IStream::_readBuffer(void* buffer, const uint len, const uint toRead)
   {
      uint64 r = _read(_rOffset, toRead, buffer, len);
      if (r < toRead)
      {
         LogEvent("Reach end of stream, no more data to read");
      }
      _rOffset += r;
   }

}