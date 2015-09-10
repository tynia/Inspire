#include "basestream.h"
#include "stream.h"
#include "util.h"
#include "allocator.h"

namespace inspire {

   static allocator* _allocator = allocator::instance();

   baseStream::baseStream() : _data(NULL), _capacity(0)
   {

   }

   baseStream::baseStream()
   {
      _allocator->dealloc(_data);
      _data = NULL;
      _capacity = 0;
   }

   void baseStream::_zero()
   {
#ifdef DEBUG
      memset(_data, 0xfe, _capacity);
#else
      memset((void*)_data, 0x0, _capacity);
#endif // DEBUG
   }

   uint64 baseStream::_read(const uint64 offset, const uint64 toRead,
                            const char* buffer, const uint64 bufferLen)
   {
      INSPIRE_ASSERT(_capacity > offset, "read offset gt than capacity");
      INSPIRE_ASSERT(NULL != buffer, "read buffer cannot be NULL");

      if (toRead == 0)
      {
         return 0;
      }

      uint64 realSize = 0;
      const char* ptr = _data + offset;
      if (_cur < ptr + toRead)
      {
         uint64 readSize = _cur - ptr;
         realSize = readSize > bufferLen ? bufferLen : readSize;
         memcpy((void*)buffer, _data + offset, realSize);
      }
      else
      {
         realSize = toRead > bufferLen ? bufferLen : toRead;
         memcpy((void*)buffer, _data + offset, realSize);
      }
      return realSize;
   }

   void baseStream::_write(const uint64 offset, const char* buffer, const uint64 toWrite)
   {
      INSPIRE_ASSERT(_capacity > offset, "write offset gt than capacity");
      if (NULL == buffer)
      {
         return;
      }

      while (_cur + toWrite > _data + _capacity)
      {
         _reverse();
      }


   }

   void baseStream::_reverse()
   {
      uint64 oldSize = _capacity;
      uint64 allocSize = _capacity;
      char* ptr = NULL;
      bool  done = false;
      do
      {
         allocSize *= 2;
         char* ptr = _allocator->alloc(allocSize);
         if (NULL == ptr)
         {
            _allocator->pray();
            done = true;
         }
      } while (NULL == ptr && done);

      memmove(ptr, _data, oldSize);
      _capacity = allocSize;
      _cur = ptr + (_cur - _data);
      _allocator->dealloc(_data);
      _data = ptr;
   }

   /*
   baseStream::baseStream() : refStream(), _writeable(true), _wOffset(0), _rOffset(0)
   {
   }

   baseStream::baseStream(const char* data, const size_t len) : refStream(data, len), _writeable(false), _wOffset(0), _rOffset(0)
   {
   }

   baseStream::baseStream(const baseStream* rhs) : refStream(*rhs)
   {
      _writeable = rhs->_writeable;
      _wOffset = rhs->_wOffset;
      _rOffset = rhs->_rOffset;
   }

   baseStream::baseStream(const baseStream& rhs) : refStream(rhs)
   {
      _writeable = rhs._writeable;
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
      return (!_writeable) || (_rOffset < _wOffset);
   }

   bool baseStream::writeable() const
   {
      return _writeable;
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
   */
}
