#include "element.h"
#include "refCounter.h"

namespace inspire {

   namespace bson {

      Element::Element() : kvMap(), _owned(true), _refCounter(NULL), _next(NULL)
      {
         _refCounter = new refCounter();
      }

      Element::Element(const Element& rhs) : kvMap(), _owned(false)
      {
         _refCounter = rhs._refCounter;
         _next = rhs._next;
         _refCounter->_inc();
      }

      Element::~Element()
      {
         _release();
      }

      void Element::replace(const Element& e)
      {
         if (_next == e._next && _refCounter == e._refCounter)
         {
            return;
         }

         _release();

         _next = e._next;
         _refCounter = e._refCounter;
         _refCounter->_inc();
      }

      void Element::putNull(const char* k)
      {
         putNull(k);
      }

      const char* Element::valuestr()
      {
         return _value;
      }

      Object Element::toObject()
      {
         Object obj;
         obj.append(*this);
         return obj;
      }

      bool Element::_checkValid()
      {

      }

      void Element::_release()
      {
         _refCounter->_dec();

         if (_owned)
         {
            if (0 == _refCounter->retain())
            {
//             if (NULL != _e)
//             {
//                delete _e;
//                _e = NULL;
//             }
               _next = NULL;
            }
         }
      }

      void Element::put(const Element& e)
      {

      }

      Element Element::operator=(const Element& rhs)
      {
         if (_next == rhs._next && _refCounter == rhs._refCounter)
         {
            return *this;
         }

         _refCounter->_dec();

         _next = rhs._next;
         _refCounter = rhs._refCounter;
         _refCounter->_inc();
      }

   }
}