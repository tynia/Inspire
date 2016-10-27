#include "nistream.h"
#include "bindata.h"

CIStream::CIStream(ENDIAN endian) : bstr(), _endian(endian), _rOffset(0)
{
}

CIStream::CIStream(const CIStream& rhs) : bstr(rhs), _rOffset(0)
{
}

CIStream::CIStream(const char* src, const uint64 len, ENDIAN endian) : bstr(src, len), _endian(endian), _rOffset(0)
{
}

CIStream& CIStream::operator>> (bool& b)
{
   int64 n = read(_rOffset, (void*)&b, sizeof(bool), sizeof(bool));
   if (n <= 0 || n < sizeof(bool))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(bool), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (char& c)
{
   int64 n = read(_rOffset, (void*)&c, sizeof(char), sizeof(char));
   if (n <= 0 || n < sizeof(char))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(char), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (uchar& uc)
{
   int64 n = read(_rOffset, (void*)&uc, sizeof(uchar), sizeof(uchar));
   if (n <= 0 || n < sizeof(uchar))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(uchar), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (short& s)
{
   short tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(short), sizeof(short));
   if (n <= 0 || n < sizeof(short))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(short), _capacity, (_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN_2(tmp, s, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (ushort& us)
{
   ushort tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(ushort), sizeof(ushort));
   if (n <= 0 || n < sizeof(ushort))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(ushort), _capacity, (_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN_2(tmp, us, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (float& f)
{
   float tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(float), sizeof(float));
   if (n <= 0 || n < sizeof(float))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(float), _capacity, (_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN(tmp, f, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (double& d)
{
   double tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(double), sizeof(double));
   if (n <= 0 || n < sizeof(double))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(double), _capacity, (_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN(tmp, d, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (int& i)
{
   int tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(int), sizeof(int));
   if (n <= 0 || n < sizeof(int))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(int), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN(tmp, i, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (uint& ui)
{
   uint tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(int), sizeof(uint));
   if (n <= 0 || n < sizeof(uint))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(uint), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN(tmp, ui, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (int64& i64)
{
   int64 tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(int64), sizeof(int64));
   if (n <= 0 || n < sizeof(int64))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(int64), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN(tmp, i64, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (uint64& ui64)
{
   uint64 tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(uint64), sizeof(uint64));
   if (n <= 0 || n < sizeof(uint64))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(uint64), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   CONVERT_ENDIAN(tmp, ui64, _endian);
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (std::string& str)
{
   std::string s(_data + _rOffset);
   int64 n = s.length() + 1;
   str = s;
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (binData& bin)
{
   uint64 tmp;
   int64 n = read(_rOffset, (void*)&tmp, sizeof(uint64), sizeof(uint64));
   CONVERT_ENDIAN(tmp, bin.len, _endian);
   char *ptr = new char[bin.len];
   n += read(_rOffset + n, (void*)ptr, bin.len, bin.len);
   if (n <= 0 || n < sizeof(bin.len) + bin.len)
   {
     // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", bin.len, _capacity, (uint64)(_data + _rOffset), n);
     return *this;
   }
   _rOffset += n;
   bin.pData = ptr;
   return *this;
}