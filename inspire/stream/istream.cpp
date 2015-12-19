#include "istream.h"
#include "util/assert.h"

namespace inspire {

   IStream& IStream::operator>>(bool& b)
   {
      _read(&b, sizeof(bool), sizeof(bool));
      return *this;
   }

   IStream& IStream::operator>>(char& c)
   {
      _read(&c, sizeof(char), sizeof(char));
      return *this;
   }

   IStream& IStream::operator>>(uchar& uc)
   {
      _read(&uc, sizeof(uchar), sizeof(uchar));
      return *this;
   }

   IStream& IStream::operator>>(short& s)
   {
      _read(&s, sizeof(short), sizeof(short));
      return *this;
   }

   IStream& IStream::operator>>(ushort& us)
   {
      _read(&us, sizeof(ushort), sizeof(ushort));
      return *this;
   }

   IStream& IStream::operator>>(float& f)
   {
      _read(&f, sizeof(float), sizeof(float));
      return *this;
   }

   IStream& IStream::operator>>(double& d)
   {
      _read(&d, sizeof(double), sizeof(double));
      return *this;
   }

   IStream& IStream::operator>>(int& i)
   {
      _read(&i, sizeof(int), sizeof(int));
      return *this;
   }

   IStream& IStream::operator>>(uint& ui)
   {
      _read(&ui, sizeof(uint), sizeof(uint));
      return *this;
   }

   IStream& IStream::operator>>(int64& i64)
   {
      _read(&i64, sizeof(int64), sizeof(int64));
      return *this;
   }

   IStream& IStream::operator>>(uint64& ui64)
   {
      _read(&ui64, sizeof(uint64), sizeof(uint64));
      return *this;
   }

   IStream& IStream::operator>>(binData& bin)
   {
      _read(&bin.len, sizeof(uint), sizeof(uint));
      bin.reverse(bin.len);
      _read(&bin.str, bin.len, bin.len);
      return *this;
   }

   uint IStream::_read(void* buffer, const uint len, const uint toRead)
   {
      INSPIRE_ASSERT(NULL != buffer, "buffer can not be NULL");
      uint bytes = 0;
      if (toRead > (_size - _rOffset))
      {
         bytes = _size - _rOffset;
      }

      if (bytes > len)
      {
         bytes = len;
      }
      ::memmove(buffer, _data + _rOffset, bytes);
      _rOffset += bytes;

      return bytes;
   }

}