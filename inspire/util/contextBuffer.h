#ifndef _INSPIRE_CONTEXT_BUFFER_H_
#define _INSPIRE_CONTEXT_BUFFER_H_

#include "refStream.h"

namespace inspire {

   class contextBuffer : virtual public refStream
   {
   public:
      contextBuffer();
      contextBuffer(const char* data, const size_t len);
      contextBuffer(const contextBuffer* rhs);
      contextBuffer(const contextBuffer& rhs);
      virtual ~contextBuffer();

      contextBuffer& operator= (const contextBuffer& rhs);
      const size_t size() const;
      bool empty() const;

      // read
      bool readable() const;
      void skipRead(const size_t size);
      const size_t seekToRead(const size_t size);
      void read(char* data, const size_t size, bool align = false, const int bytes = 4);

      // write
      void skipWrite(const size_t size);
      const size_t seekToWrite(const size_t size);
      void write(const char* data, const size_t size, bool align = false, const int bytes = 4);

   private:
      size_t _wOffset;
      size_t _rOffset;
   };

}
#endif