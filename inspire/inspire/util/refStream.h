#ifndef _INSPIRE_REF_STREAM_H_
#define _INSPIRE_REF_STREAM_H_

#include "inspire.h"

namespace inspire {

   static const int BLOCK_SIZE = 1024;

   typedef unsigned int size_t;

   class refStream
   {
   public:
      refStream();
      refStream(const char* data, const size_t len);
      refStream(const refStream& rhs);

   public:
      bool  shared() const;
      void  reverse(const size_t size);
      char* data() const;
      const size_t capacity() const;

   protected:
      ~refStream();
      void  _release();
      refStream& operator= (const refStream& rhs);

   private:
      void  _inc();
      void  _dec();
      void  _alloc(const size_t size);
      void  _realloc(const size_t size);

   protected:
      size_t  _capacity;
      size_t* _refCount;
      char*   _refData;
   };
}
#endif