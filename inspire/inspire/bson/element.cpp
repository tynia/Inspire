#include "element.h"

namespace inspire {

   namespace bson {

      Element::Element() : _counter(NULL), _e(NULL), _next(NULL)
      {}

      Element::Element(const Element& rhs)
      {
         _e = rhs._e;
         _counter = rhs._counter;
         _next = rhs._next;
         _counter->_inc();
      }

      Element::~Element()
      {
         _counter->_dec();
         if (0 == _counter->get())
         {
            if (NULL != _e)
            {
               delete _e;
               _e = NULL;
            }
            _next = NULL;
         }
      }

      Element& Element::operator=(const Element& rhs)
      {
         if (_e == rhs._e && _next == rhs._next && _counter == rhs._counter)
         {
            return *this;
         }

         _counter->_dec();

         _e = rhs._e;
         _next = rhs._next;
         _counter = rhs._counter;
         _counter->_inc();
      }

   }
}