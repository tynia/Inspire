#ifndef _INSPIRE_NET_BASE_STREAM_H_
#define _INSPIRE_NET_BASE_STREAM_H_

#include "inspire.h"

namespace inspire {

   class baseStream
   {
   public:
      const char* data() const { return _data; }
      const uint64 capacity() const { return _capacity; }

   protected:
      baseStream();
      virtual ~baseStream();

      void _zero();

      uint64 _read(const uint64 offset, const uint64 toRead,
                   const char* buffer, const uint64 bufferLen);
      void   _write(const uint64 offset, const char* buffer, const uint64 toWrite);
      
   private:
      void _reverse();

   protected:
      const char* _data;
      const char* _cur;
      uint64      _capacity;
   };

   /*
   class baseStream : virtual public refStream
   {
   public:
      baseStream();
      baseStream(const char* data, const size_t len);
      baseStream(const baseStream* bs);
      baseStream(const baseStream& bs);
      virtual ~baseStream();

      baseStream& operator= (const baseStream& rhs);
      const size_t size() const;
      bool empty() const;
      bool readable() const;
      bool writeable() const;

   protected:
      void _skipRead(const size_t size);
      const size_t _seekToRead(const size_t size);
      void _read(char* data, const size_t size, bool align = false, const int bytes = 4);

      void _skipWrite(const size_t size);
      const size_t _seekToWrite(const size_t size);
      void _write(const char* data, const size_t size, bool align = false, const int bytes = 4);

   private:
      bool   _writeable;
      size_t _wOffset;
      size_t _rOffset;
   };*/

}
#endif