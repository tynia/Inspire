#include "element.h"
#include "refPointer.h"

namespace inspire {

   namespace bson {

      Element::Element() : kvMap(), _owned(true), _counter(NULL), _next(NULL)
      {
         _counter = new refCounter();
      }

      Element::Element(const Element& rhs) : kvMap(), _owned(false)
      {
         _counter = rhs._counter;
         _next = rhs._next;
         _counter->_inc();
      }

      Element::~Element()
      {
         _release();
      }

      void Element::replace(const Element& e)
      {
         if (_next == e._next && _counter == e._counter)
         {
            return;
         }

         _release();

         _next = e._next;
         _counter = e._counter;
         _counter->_inc();
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
         _counter->_dec();

         if (_owned)
         {
            if (0 == _counter->get())
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

      Element& Element::operator=(const Element& rhs)
      {
         if (_next == rhs._next && _counter == rhs._counter)
         {
            return *this;
         }

         _counter->_dec();

         _next = rhs._next;
         _counter = rhs._counter;
         _counter->_inc();
      }

   }
}