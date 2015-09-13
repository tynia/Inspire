#ifndef _INSPIRE_REF_STREAM_H_
#define _INSPIRE_REF_STREAM_H_

#include "inspire.h"
#include "ostream.h"

namespace inspire {

   class refCounter;

   class IReference
   {
   protected:
      IReference();
      virtual ~IReference(); 

   public:
      bool shared() const { return 0 != _refCounter->retain(); }
   protected:
      refCounter* _refCounter;
   };

   class refOStream : public OStream
   {
   protected:
      refOStream();
      refOStream(const char* data, const unsigned len);
      refOStream(const refOStream& rhs);
      ~refOStream();
      void _release();

      // when call operator=, please check it is shared first
      // operator may release its buffer
      refOStream& operator= (const refOStream& rhs);

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