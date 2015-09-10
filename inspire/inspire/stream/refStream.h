#ifndef _INSPIRE_REF_STREAM_H_
#define _INSPIRE_REF_STREAM_H_

#include "inspire.h"

namespace inspire {

   static const int BLOCK_SIZE = 1024;

   class refCounter;

   class refStream
   {
   protected:
      refStream();
      refStream(const char* data, const unsigned len);
      refStream(const refStream& rhs);
      ~refStream();
      void _release();

      // when call operator=, please check it is shared first
      // operator may release its buffer
      refStream& operator= (const refStream& rhs);

      bool  shared() const;
      void  reverse(const unsigned size);
      char* data() const;
      const unsigned capacity() const;

   private:
      void  _inc();
      void  _dec();
      void  _alloc(const unsigned size);
      void  _realloc(const unsigned size);

   protected:
      unsigned    _capacity;
      char*       _refData;
      refCounter* _refCount;
   };
}
#endif