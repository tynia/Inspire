#include "ostream.h"
#include "endian/endian.h"

namespace inspire {

   OStream::OStream(allocator* al, const uint blockSize)
      : baseStream(al, blockSize)
   {
   }

   OStream::OStream(OStream& rhs) : baseStream(rhs)
   {
   }

   OStream::~OStream()
   {
   }

   OStream OStream::operator=(OStream& rhs)
   {
      OStream os(rhs);
      return os;
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
      ushort tmp = ENDIAN::H2N(us);
      _write((void*)&tmp, sizeof(ushort));
   }

   OStream& OStream::operator<<(const float f)
   {
      float tmp = ENDIAN::H2N(f);
      _write((void*)&tmp, sizeof(float));
   }

   OStream& OStream::operator<<(const double d)
   {
      double tmp = ENDIAN::H2N(d);
      _write((void*)&tmp, sizeof(double));
   }

   OStream& OStream::operator<<(const int i)
   {
      int tmp = ENDIAN::H2N(i);
      _write((void*)&tmp, sizeof(int));
   }

   OStream& OStream::operator<<(const uint ui)
   {
      uint tmp = ENDIAN::H2N(ui);
      _write((void*)&tmp, sizeof(uint));
   }

   OStream& OStream::operator<<(const int64& i64)
   {
      int64 tmp = ENDIAN::H2N(i64);
      _write((void*)&tmp, sizeof(int64));
   }

   OStream& OStream::operator<<(const uint64& ui64)
   {
      uint64 tmp = ENDIAN::H2N(ui64);
      _write((void*)&tmp, sizeof(uint64));
   }

   OStream& OStream::operator<<(const binData& bin)
   {
      uint tmp = ENDIAN::H2N(bin.len);
      _write((void*)&tmp, sizeof(uint));
      _write((void*)&bin.data, bin.len);
   }

   OStream& OStream::operator<<(const std::string& str)
   {
      uint len = ENDIAN::H2N(str.length());
      _write((void*)&len, sizeof(uint));
      _write((void*)str.c_str(), str.length());
   }

}