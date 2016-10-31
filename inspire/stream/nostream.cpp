#include "nostream.h"
#include "bindata.h"
#include "endian.h"

NOStream::NOStream(ENDIAN endian) : bstr(), _endian(endian), _wOffset(0)
{
}

NOStream::NOStream(const NOStream& os) : bstr(os), _endian(os._endian), _wOffset(0)
{
}

NOStream::NOStream(const char* src, const uint64 len, ENDIAN endian) : bstr(src, len), _endian(endian), _wOffset(0)
{
}

NOStream& NOStream::operator<< (bool b)
{
   int64 n = write(_wOffset, (void*)&b, sizeof(bool));
   if (n <= 0 || n < sizeof(bool))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(bool), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (char c)
{
   int64 n = write(_wOffset, (void*)&c, sizeof(char));
   if (n <= 0 || n < sizeof(char))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(char), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (uchar uc)
{
   int64 n = write(_wOffset, (void*)&uc, sizeof(uchar));
   if (n <= 0 || n < sizeof(uchar))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(uchar), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (short s)
{
   short tmp;
   CONVERT_ENDIAN(s, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(short));
   if (n <= 0 || n < sizeof(short))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(short), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (ushort us)
{
   ushort tmp;
   CONVERT_ENDIAN(us, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(ushort));
   if (n <= 0 || n < sizeof(ushort))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(ushort), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (float f)
{
   float tmp;
   CONVERT_ENDIAN(f, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(float));
   if (n <= 0 || n < sizeof(float))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(float), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (double d)
{
   double tmp;
   CONVERT_ENDIAN(d, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(double));
   if (n <= 0 || n < sizeof(double))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(double), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (int i)
{
   int tmp;
   CONVERT_ENDIAN(i, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(int));
   if (n <= 0 || n < sizeof(int))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(int), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (uint ui)
{
   uint tmp;
   CONVERT_ENDIAN(ui, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(uint));
   if (n <= 0 || n < sizeof(uint))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(uint), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (int64 i64)
{
   int64 tmp;
   CONVERT_ENDIAN(i64, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(int64));
   if (n <= 0 || n < sizeof(int64))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(int64), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (uint64 ui64)
{
   uint64 tmp;
   CONVERT_ENDIAN(ui64, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(uint64));
   if (n <= 0 || n < sizeof(uint64))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(uint64), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (const char* str)
{
   uint64 l = strlen(str) + 1;
   int64 n = write(_wOffset, str, l);
   if (n <= 0 || n < l)
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", l, _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this; 
}

NOStream& NOStream::operator<< (std::string& str)
{
   uint64 l = str.length() + 1;
   int64 n = write(_wOffset, str.c_str(), l);
   if (n <= 0 || n < l)
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", l, _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

NOStream& NOStream::operator<< (binData& bin)
{
   int64 tmp;
   CONVERT_ENDIAN(bin.len, tmp, _endian);
   int64 n = write(_wOffset, (void*)&tmp, sizeof(bin.len));
   n += write(_wOffset + n, (void*)bin.pData, bin.len);
   if (n <= 0 || n < sizeof(bin.len) + bin.len + 1)
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", bin.len, _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}