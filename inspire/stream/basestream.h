#ifndef _STREAM_BASE_STREAM_H_
#define _STREAM_BASE_STREAM_H_

#include "inspire.h"

class bstr
{
public:
   bstr();
   bstr(const char* src, const uint64 len);
   bstr(const bstr& rhs);
   virtual ~bstr();

   int64 write(const uint64 offset, const void* toWrite, const uint64 wLen);
   int64 read (const uint64 offset, void* toRead, const uint64 bufSize, const uint64 rLen);

   uint64 capacity() const { return _capacity; }
   uint64 length() const { return _len; }
   const char* c_str() const { return _data; }
   const char* data() const { return _data; }
   char* data() { return _data; }

public:
   bstr& operator=  (const bstr& rhs);
   bstr& operator+= (const bstr& rhs);
   bstr& operator+= (const char* str);
   bool  operator== (const bstr& rhs);
   bool  operator== (const char* str);

protected:
   char* _extent(const uint64 newSize, uint bytes = 8);

protected:
   char*  _data;
   uint64 _len;
   uint64 _capacity;
};

#endif // _STREAM_BASE_STREAM_H_