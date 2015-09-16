#include "refStream.h"
#include "refCounter.h"

namespace inspire {

   refOStream::refOStream() : _refCounter(NULL), _capacity(0), _refData(NULL)
   {
      _refCounter = new refCounter();
      _refCounter->_inc();
   }

   refOStream::refOStream(const refOStream& rhs)
   {
      _capacity = rhs._capacity;
      _refData  = rhs._refData;
      _refCounter = rhs._refCounter;
      _refCounter->_inc();
   }

   refOStream::~refOStream()
   {
      _release();
   }

   bool refOStream::shared() const
   {
      return (_refCounter->retain() > 0);
   }

   char* refOStream::data() const
   {
      return _refData;
   }

   const size_t refOStream::capacity() const
   {
      return _capacity;
   }

   void refOStream::_release()
   {
      _refCounter->_dec();
      if (0 == _refCounter->retain())
      {
         if (_refData)
         {
            ::free(_refData);
            _refData = NULL;
         }
         delete _refCounter;
         _refCounter = NULL;
      }
   }

   void refOStream::reverse(const size_t size)
   {
      if (size <= _capacity)
      {
         return;
      }

      if (0 == _capacity && NULL == _refData)
      {
         _alloc(size);
      }
      else
      {
         _realloc(size);
      }
   }

   refOStream& refOStream::operator= (const refOStream& rhs)
   {
      _release();
      _capacity = rhs._capacity;
      _refData = rhs._refData;
      _refCounter = rhs._refCounter;
      _refCounter->_inc();

      return *this;
   }

   void refOStream::_alloc(const size_t size)
   {
      char* ptr = (char*)::malloc(size);
      if (NULL == ptr)
      {
         //LogError
      }
      _refData = ptr;
   }

   void refOStream::_realloc(const size_t size)
   {
      char* ptr = (char*)::realloc(_refData, size);
      if (NULL == ptr)
      {
         //LogError
      }
      _refData = ptr;
      _capacity = size;
   }
}