#include "basestream.h"
#include "stream.h"
#include "util.h"

namespace inspire {

   baseStream::baseStream() : refStream(), _wOffset(0), _rOffset(0)
   {
   }

   baseStream::baseStream(const char* data, const size_t len) : refStream(data, len), _wOffset(0), _rOffset(0)
   {
   }

   baseStream::baseStream(const baseStream* rhs) : refStream(*rhs)
   {
      _wOffset = rhs->_wOffset;
      _rOffset = rhs->_rOffset;
   }

   baseStream::baseStream(const baseStream& rhs) : refStream(rhs)
   {
      _wOffset = rhs._wOffset;
      _rOffset = rhs._rOffset;
   }

   baseStream::~baseStream()
   {
      _release();
      _wOffset = 0;
      _rOffset = 0;
   }

   baseStream& baseStream::operator= (const baseStream& rhs)
   {
      refStream::operator=(rhs);
      _wOffset = rhs._wOffset;
      _rOffset = rhs._rOffset;

      return *this;
   }

   const size_t baseStream::size() const
   {
      return _wOffset;
   }

   bool baseStream::empty() const
   {
      return (0 == _wOffset);
   }

   bool baseStream::readable() const
   {
      return _rOffset < _wOffset;
   }

   void baseStream::_skipRead(const size_t size)
   {
      if (_wOffset <= _rOffset + size)
      {
         return;
      }
      _rOffset += size;
   }

   const size_t baseStream::_seekToRead(const size_t size)
   {
      size_t seek = size > _wOffset ? _wOffset : size;
      _rOffset = seek;
      return seek;
   }

   void baseStream::_read(char* buffer, const size_t size, bool align, const int bytes)
   {
      if (size + _rOffset > _capacity)
      {
         //LogError
         return;
      }

      size_t pos = _rOffset;
      memcpy((void *)buffer, _refData + pos, size);
      if (align)
      {
         _rOffset += util::roundUp(size, bytes);
      }
      else
      {
         _rOffset += size;
      }
   }

   void baseStream::_skipWrite(const size_t size)
   {
      _wOffset += size;
   }

   const size_t baseStream::_seekToWrite(const size_t size)
   {
      size_t seek = size > _capacity ? _capacity : size;
      _wOffset = seek;
      return seek;
   }

   void baseStream::_write(const char* data, const size_t size, bool align, const int bytes)
   {
      size_t tmp = _capacity;
      while (tmp <= _wOffset + size)
      {
         tmp += BLOCK_SIZE;
      }

      reverse(tmp);
      memcpy(_refData + _wOffset, data, size);
      if (align)
      {
         _wOffset += util::roundUp(size, bytes);
      }
      else
      {
         _wOffset += size;
      }
   }
}
