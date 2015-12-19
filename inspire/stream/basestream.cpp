#include "basestream.h"
#include "util.h"
#include "allocator.h"
#include "refCounter.h"

namespace inspire {

   baseStream::baseStream(const uint unitSize) 
      : _data(NULL), _capacity(0), _refCounter(NULL)
   {
      _initialize();
      _refCounter = new refCounter();
      INSPIRE_ASSERT(NULL != _refCounter, "Failed to allocate refCounter");
   }

   baseStream::baseStream(const char* data, const uint64 len)
      : _data(data), _capacity(len), _refCounter(NULL)
   {
      _refCounter = new refCounter();
      INSPIRE_ASSERT(NULL != _refCounter, "Failed to allocate refCounter");
   }

   baseStream::baseStream(baseStream& rhs)
      : _data(rhs._data), _capacity(rhs._capacity), _wOffset(rhs._wOffset)
      , _blockSize(rhs._blockSize), _refCounter(rhs._refCounter), _allocator(rhs._allocator)
   {
      _refCounter->_inc();
   }

   baseStream::~baseStream()
   {
      _refCounter->_dec();
      if (0 == _refCounter->retain())
      {
         _allocator->dealloc(_data);
         _allocator = NULL;
         _blockSize = 0;
      }
      _data = NULL;
      _capacity = 0;
      _wOffset = 0;
   }

   void baseStream::_zero()
   {
#ifdef DEBUG
      memset((void*)_data, 0xfe, _capacity);
#else
      memset((void*)_data, 0x0, _capacity);
#endif // DEBUG
   }

   uint64 baseStream::_read(const uint64 offset, const uint64 toRead,
                            void* buffer, const uint64 bufferLen)
   {
      if (NULL == buffer || toRead == 0)
      {
         return 0;
      }

      if (offset > _wOffset)
      {
         LogEvent("Attempt to read invalid buffer");
         return 0;
      }

      uint64 realSize = 0;
      const char* ptr = _data + offset;
      if (_data + _wOffset < ptr + toRead)
      {
         uint64 readSize = _data + _wOffset - ptr;
         realSize = readSize > bufferLen ? bufferLen : readSize;
         memcpy((void*)buffer, _data + offset, realSize);
      }
      else
      {
         realSize = toRead > bufferLen ? bufferLen : toRead;
         memcpy(buffer, _data + offset, realSize);
      }
      return realSize;
   }

   void baseStream::_write(void* data, const uint64 toWrite)
   {
      // may be locked
      // TODO:

      if (NULL == data)
      {
         return;
      }

      if (_wOffset + toWrite > _capacity)
      {
         uint64 newCapacity = _capacity;
         do
         {
            newCapacity += _blockSize;
         } while (_wOffset + toWrite > newCapacity);

         _extCapacity(newCapacity);
      }

      memcpy((void*)(_data + _wOffset), data, toWrite);
      _wOffset += toWrite;
   }

   void baseStream::_initialize()
   {
      _extCapacity(_blockSize);
   }

   void baseStream::_extCapacity(const uint64 size)
   {
      bool  done = false;
      uint64 allocSize = 0;
      char* ptr = NULL;

      while (NULL == ptr)
      {
         allocSize = (0 == size ? 2 * _capacity : size);
         ptr = _allocator->alloc(allocSize);
         if (NULL == ptr)
         {
            if (done)
            {
               LogError("Out of memory although prayed");
               Panic();
            }
            _allocator->pray();
            done = true;
         }
      }

      // succeed to allocate memory,
      if (_data)
      {
         memmove(ptr, _data, _wOffset);
         _allocator->dealloc(_data);
      }
      _data = ptr;
      _capacity = allocSize;
   }
}
