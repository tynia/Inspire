#include "ostream.h"
#include "endian/endian.h"

namespace inspire {

   OStream::OStream(allocator* al, const uint blockSize)
      : baseStream(al, blockSize)
   {
   }

   OStream::~OStream()
   {
   }

   void OStream::put(const char c)
   {
      _write((void*)&c, sizeof(char));
   }

   OStream& OStream::operator<<(const bool b)
   {
      _write((void*)&b, sizeof(bool));
   }

   OStream& OStream::operator<<(const char c)
   {
      _write((void*)&c, sizeof(char));
   }

   OStream& OStream::operator<<(const uchar uc)
   {
      _write((void*)&uc, sizeof(uchar));
   }

   OStream& OStream::operator<<(const short s)
   {
      short tmp = ENDIAN::H2N(s);
      _write((void*)&tmp, sizeof(short));
   }

   OStream& OStream::operator<<(const ushort us)
   {
      _write((void*)&us, sizeof(ushort));
   }

   OStream& OStream::operator<<(const float f)
   {
      _write((void*)&f, sizeof(float));
   }

   OStream& OStream::operator<<(const double d)
   {
      _write((void*)&d, sizeof(double));
   }

   OStream& OStream::operator<<(const int i)
   {
      _write((void*)&i, sizeof(int));
   }

   OStream& OStream::operator<<(const uint ui)
   {
      _write((void*)&ui, sizeof(uint));
   }

   OStream& OStream::operator<<(const int64& i64)
   {
      _write((void*)&i64, sizeof(int64));
   }

   OStream& OStream::operator<<(const uint64& ui64)
   {
      _write((void*)&ui64, sizeof(uint64));
   }

   OStream& OStream::operator<<(const binData& bin)
   {
      _write((void*)&bin.len, sizeof(uint));
      _write((void*)&bin.data, bin.len);
   }

   OStream& OStream::operator<<(const std::string& str)
   {
      uint len = ENDIAN::H2N(str.length());
      _write((void*)&len, sizeof(uint));
      _write((void*)str.c_str(), str.length());
   }

}