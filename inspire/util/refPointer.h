#ifndef _INSPIRE_UTIL_REFERENCE_POINTER_H_
#define _INSPIRE_UTIL_REFERENCE_POINTER_H_

namespace inspire {

   template<class T>
   class refPointer
   {
      refPointer(T* ptr) : _ptr(ptr)
      {
         _ptrCounter = new refCounter();
         _ptrCounter->_inc();
      }

      refPointer(const refPointer& rhs) : _ptr(rhs._ptr), _ptrCounter(rhs._ptrCounter)
      {
         _ptrCounter->_inc();
      }

      ~refPointer()
      {
         _ptrCounter->_dec();
         if (0 == _ptrCounter->_referCount)
         {
            delete _ptr;
            _ptr = NULL;

            delete _ptrCounter;
            _ptrCounter = NULL;
         }
      }

      refPointer<T>& operator= (const refPointer<T>& rhs)
      {
         if (_ptr != rhs._ptr)
         {
            _ptrCounter->_dec();
            _ptr = rhs._ptr;
            _ptrCounter = rhs._ptrCounter;
            _ptrCounter->_inc();
         }

         return *this;
      }

      T& operator* ()
      {
         return *_ptr;
      }

      T* operator-> ()
      {
         return _ptr;
      }

   private:
      T* _ptr;
      refCounter* _ptrCounter;
   };
}
#endif