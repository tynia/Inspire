#include "basestream.h"
#include <cstring>

bstr::bstr() : _data(NULL), _len(0), _capacity(0)
{
}

bstr::bstr(const char* src, const uint64 len) : _data(NULL), _len(0), _capacity(0)
{
   write(0, src, len);
}

bstr::bstr(const bstr& rhs)
{
    write(0, rhs._data, rhs._len);
}

bstr::~bstr()
{
    if (NULL != _data)
    {
        delete [] _data;
        _data = NULL;
        _len = 0;
        _capacity = 0;
    }
}

int64 bstr::write(const uint64 offset, const void* toWrite, const uint64 wLen)
{
   if (NULL == toWrite)
   {
      // LogError("Invalid data to write");
      return 0;
   }

   if (0 == wLen)
   {
      // LogError("try to write 0 byte");
      return 0;
   }

   if (offset > _capacity)
   {
      //LogError("offset is out of buffer size")
      return 0;
   }

   if (_capacity - offset < wLen)
   {
      uint64 newSize = _len + wLen;//_capacity - offset + wLen;
      // extent buffer
      _extent(newSize);
   }

   memcpy(_data + offset, toWrite, wLen);
   _len += wLen;

   return wLen;
}

int64 bstr::read (const uint64 offset, void* toRead, const uint64 bufSize, const uint64 rLen)
{
   if (NULL == toRead)
   {
      // LogError("Invalid buffer to store data");
      return 0;
   }

   if (0 == bufSize)
   {
      // LogError("Invalid buffer size")
      return 0;
   }

   if (rLen == 0)
   {
      // LogError("Try to read 0 byte into buffer")
      return 0;
   }

   uint64 readLen = rLen;

   if (offset > _capacity)
   {
      // LogWarning("offset is beyond end of buffer")
      return 0;
   }

   if (offset + rLen > _capacity)
   {
      // LogWarning("read will beyond end of buffer, read less data")
      readLen = _capacity - offset;
   }

   if (rLen > bufSize)
   {
      // LogWarning("length to read is greater than buffer size")
      readLen = bufSize;
   }

   memcpy(toRead, _data + offset, readLen);

   return readLen;
}

bstr& bstr::operator=  (const bstr& rhs)
{
   if (_data == rhs._data)
   {
      return *this;
   }

   if (NULL != _data)
   {
      delete [] _data;
      _data = NULL;
      _len = 0;
      _capacity = 0;
   }
   write(0, rhs._data, rhs._len);
}

bstr& bstr::operator+= (const bstr& rhs)
{
   write(_len, rhs._data, rhs._len);
   return *this;
}

bstr& bstr::operator+= (const char* str)
{
   write(_len, str, strlen(str) + 1);
   return *this;
}

bool bstr::operator== (const bstr& rhs)
{
   if (_len != rhs._len)
   {
      return false;
   }

   if (0 != strncmp(_data, rhs._data, _len))
   {
      return false;
   }

   return true;
}

bool bstr::operator== (const char* str)
{
   if (_len != strlen(str))
   {
      return false;
   }

   if (0 != strncmp(_data, str, _len))
   {
      return false;
   }

   return true;
}

char* bstr::_extent(const uint64 size, uint bytes)
{
   uint64 newSize = ((size + (bytes - 1)) - ((size + (bytes - 1)) % bytes));
   char* ptr = new char[newSize];
   if (NULL == ptr)
   {
    //    LogError("system error: out of memory");
       return NULL;
   }

   char* old = _data;
   memcpy(ptr, _data, _len);
   _data = ptr;
   _capacity = newSize;

   delete [] old;
}