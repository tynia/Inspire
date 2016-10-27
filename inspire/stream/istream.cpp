#include "istream.h"
#include "bindata.h"

CIStream::CIStream() : bstr(), _rOffset(0)
{
}

CIStream::CIStream(const CIStream& rhs) : bstr(rhs), _rOffset(0)
{
}

CIStream::CIStream(const char* src, const uint64 len) : bstr(src, len), _rOffset(0)
{
}

CIStream& CIStream::operator>> (bool& b)
{
   int64 n = read(_rOffset, (void*)&b, sizeof(b), sizeof(bool));
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
   int64 n = read(_rOffset, (void*)&c, sizeof(c), sizeof(char));
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
   int64 n = read(_rOffset, (void*)&uc, sizeof(uc), sizeof(uchar));
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
   int64 n = read(_rOffset, (void*)&s, sizeof(s), sizeof(short));
   if (n <= 0 || n < sizeof(short))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(short), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (ushort& us)
{
   int64 n = read(_rOffset, (void*)&us, sizeof(us), sizeof(ushort));
   if (n <= 0 || n < sizeof(ushort))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(ushort), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (float& f)
{
   int64 n = read(_rOffset, (void*)&f, sizeof(f), sizeof(float));
   if (n <= 0 || n < sizeof(float))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(float), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (double& d)
{
   int64 n = read(_rOffset, (void*)&d, sizeof(d), sizeof(double));
   if (n <= 0 || n < sizeof(double))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(double), _capacity, (_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (int& i)
{
   int64 n = read(_rOffset, (void*)&i, sizeof(i), sizeof(int));
   if (n <= 0 || n < sizeof(int))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(int), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (uint& ui)
{
   int64 n = read(_rOffset, (void*)&ui, sizeof(ui), sizeof(uint));
   if (n <= 0 || n < sizeof(uint))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(uint), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (int64& i64)
{
   int64 n = read(_rOffset, (void*)&i64, sizeof(i64), sizeof(int64));
   if (n <= 0 || n < sizeof(int64))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(int64), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
   _rOffset += n;
   return *this;
}

CIStream& CIStream::operator>> (uint64& ui64)
{
   int64 n = read(_rOffset, (void*)&ui64, sizeof(ui64), sizeof(uint64));
   if (n <= 0 || n < sizeof(uint64))
   {
      // LogError("Failed to read data[size: %lld] from stream[capacity: %lld, offset: 0x%p], return %lld", sizeof(uint64), _capacity, (uint64)(_data + _rOffset), n);
      return *this;
   }
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
   int64 n = read(_rOffset, (void*)&bin.len, sizeof(bin.len), sizeof(bin.len));
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