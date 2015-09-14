#include "nostream.h"
#include "endian/endian.h"

namespace inspire {

   NOStream::NOStream(allocator* al, const uint blockSize)
      : baseStream(al, blockSize)
   {
   }

   NOStream::~NOStream()
   {
   }

   void NOStream::put(const char c)
   {
      _write((void*)&c, sizeof(char));
   }

   NOStream& NOStream::operator<<(const bool b)
   {
      _write((void*)&b, sizeof(bool));
   }

   NOStream& NOStream::operator<<(const char c)
   {
      _write((void*)&c, sizeof(char));
   }

   NOStream& NOStream::operator<<(const uchar uc)
   {
      _write((void*)&uc, sizeof(uchar));
   }

   NOStream& NOStream::operator<<(const short s)
   {
      short tmp = ENDIAN::H2N(s);
      _write((void*)&tmp, sizeof(short));
   }

   NOStream& NOStream::operator<<(const ushort us)
   {
      ushort tmp = ENDIAN::H2N(us);
      _write((void*)&tmp, sizeof(ushort));
   }

   NOStream& NOStream::operator<<(const float f)
   {
      float tmp = ENDIAN::H2N(f);
      _write((void*)&tmp, sizeof(float));
   }

   NOStream& NOStream::operator<<(const double d)
   {
      double tmp = ENDIAN::H2N(d);
      _write((void*)&tmp, sizeof(double));
   }

   NOStream& NOStream::operator<<(const int i)
   {
      int tmp = ENDIAN::H2N(i);
      _write((void*)&tmp, sizeof(int));
   }

   NOStream& NOStream::operator<<(const uint ui)
   {
      uint tmp = ENDIAN::H2N(ui);
      _write((void*)&tmp, sizeof(uint));
   }

   NOStream& NOStream::operator<<(const int64& i64)
   {
      int64 tmp = ENDIAN::H2N(i64);
      _write((void*)&tmp, sizeof(int64));
   }

   NOStream& NOStream::operator<<(const uint64& ui64)
   {
      uint64 tmp = ENDIAN::H2N(ui64);
      _write((void*)&tmp, sizeof(uint64));
   }

   NOStream& NOStream::operator<<(const binData& bin)
   {
      uint tmp = ENDIAN::H2N(bin.len);
      _write((void*)&tmp, sizeof(uint));
      _write((void*)&bin.data, bin.len);
   }

   NOStream& NOStream::operator<<(const std::string& str)
   {
      uint len = ENDIAN::H2N(str.length());
      _write((void*)&len, sizeof(uint));
      _write((void*)str.c_str(), str.length());
   }

}