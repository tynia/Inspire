#include "ostream.h"
#include "bindata.h"

COStream::COStream() : bstr(), _wOffset(0)
{
}

COStream::COStream(const COStream& os) : bstr(os), _wOffset(0)
{
}

COStream::COStream(const char* src, const uint64 len) : bstr(src, len), _wOffset(0)
{
}

COStream& COStream::operator<< (bool b)
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

COStream& COStream::operator<< (char c)
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

COStream& COStream::operator<< (uchar uc)
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

COStream& COStream::operator<< (short s)
{
   int64 n = write(_wOffset, (void*)&s, sizeof(short));
   if (n <= 0 || n < sizeof(short))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(short), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (ushort us)
{
   int64 n = write(_wOffset, (void*)&us, sizeof(ushort));
   if (n <= 0 || n < sizeof(ushort))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(ushort), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (float f)
{
   int64 n = write(_wOffset, (void*)&f, sizeof(float));
   if (n <= 0 || n < sizeof(float))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(float), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (double d)
{
   int64 n = write(_wOffset, (void*)&d, sizeof(double));
   if (n <= 0 || n < sizeof(double))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(double), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (int i)
{
   int64 n = write(_wOffset, (void*)&i, sizeof(int));
   if (n <= 0 || n < sizeof(int))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(int), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (uint ui)
{
   int64 n = write(_wOffset, (void*)&ui, sizeof(uint));
   if (n <= 0 || n < sizeof(uint))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(uint), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (int64 i64)
{
   int64 n = write(_wOffset, (void*)&i64, sizeof(int64));
   if (n <= 0 || n < sizeof(int64))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(int64), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (uint64 ui64)
{
   int64 n = write(_wOffset, (void*)&ui64, sizeof(uint64));
   if (n <= 0 || n < sizeof(uint64))
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", sizeof(uint64), _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

COStream& COStream::operator<< (const char* str)
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

COStream& COStream::operator<< (std::string& str)
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

COStream& COStream::operator<< (binData& bin)
{
   int64 n = write(_wOffset, (void*)&bin.len, sizeof(bin.len));
   n += write(_wOffset + n, (void*)bin.pData, bin.len);
   if (n <= 0 || n < sizeof(bin.len) + bin.len + 1)
   {
      // LogError("Failed to write data[size: %lld] into stream[capacity:%lld, target offset: %p], returns: %lld", bin.len, _capacity, (_data + _wOffset), n);
      return *this;
   }
   _wOffset += n;
   return *this;
}

// COStream& COStream::Proposal()
// {
//    // step 1
//    // send her a song named <<let's get married<<
//    // step 2
//    // TODO:  
//    // step 3
//    // TODO:  
//    // step 4
//    // TODO:  
//    // ....
//    // step n
//    // it's the real ceremony, to be continued
//    // done.
// }