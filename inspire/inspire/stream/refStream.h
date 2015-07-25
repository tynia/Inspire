#ifndef _INSPIRE_REF_STREAM_H_
#define _INSPIRE_REF_STREAM_H_

#include "inspire.h"

namespace inspire {

   static const int BLOCK_SIZE = 1024;

   class refCounter;

   class refStream
   {
   public:
      refStream();
      refStream(const char* data, const unsigned len);
      refStream(const refStream& rhs);

   public:
      bool  shared() const;
      void  reverse(const unsigned size);
      char* data() const;
      const unsigned capacity() const;

   protected:
      ~refStream();
      void _release();
      refStream& operator= (const refStream& rhs);

   private:
      void  _inc();
      void  _dec();
      void  _alloc(const unsigned size);
      void  _realloc(const unsigned size);

   protected:
      unsigned _capacity;
      char*    _refData;
      refCounter* _refCount;
   };
}
#endif