#include "atomic64.h"
#include "atomic.h"

namespace inspire {

   atomicSigned64::atomicSigned64(int64 val)
   {
      initialize(val);
   }

   atomicSigned64::~atomicSigned64()
   {}

   template<class T>
   int64 atomicSigned64::_swapPredicated(int64 val, const T& predVal)
   {
      int prev = peek();
      for (;;)
      {
         int64 newVal = prev;
         if (predVal.op(val, prev))
         {
            newVal = val;
         }
         int64 tmp = ossCompareAndSwap64WithReturn(&_value, prev, newVal);
         if (prev == tmp)
         {
            break;
         }
         else
         {
            prev = tmp;
         }
      }
      return prev;
   }

   void atomicSigned64::initialize(int64 val)
   {
      _value = val;
   }

   size_t atomicSigned64::size() const
   {
      return sizeof(_value);
   }

   int64 atomicSigned64::peek()
   {
      return _value;
   }

   int64 atomicSigned64::add(int64 val)
   {
      return ossFetchAndAdd64(&_value, val);
   }

   int64 atomicSigned64::sub(int64 val)
   {
      return add(-val);
   }

   int64 atomicSigned64::bitOR(int64 val)
   {
      return ossFetchAndOR64(&_value, val);
   }

   int64 atomicSigned64::bitAND(int64 val)
   {
      return ossFetchAndAND64(&_value, val);
   }

   int64 atomicSigned64::fetch()
   {
      return ossAtomicFetch64(&_value);
   }

   int64 atomicSigned64::inc()
   {
      return ossFetchAndIncrement64(&_value);
   }

   int64 atomicSigned64::dec()
   {
      return ossFetchAndDecrement64(&_value);
   }

   int64 atomicSigned64::swap(int64 val)
   {
      return ossAtomicExchange64(&_value, val);
   }

   bool atomicSigned64::compareAndSwap(int64 comVal, int64 val)
   {
      return ossCompareAndSwap64(&_value, comVal, val);
   }

   int64 atomicSigned64::compareAndSwapWithReturn(int64 comVal, int64 val)
   {
      return ossCompareAndSwap64WithReturn(&_value, comVal, val);
   }

   int64 atomicSigned64::swapGreater(int64 val)
   {
      return _swapPredicated(val, predicatedGreater<int64>());
   }

   int64 atomicSigned64::swapLess(int64 val)
   {
      return _swapPredicated(val, predicatedLess<int64>());
   }

   bool atomicSigned64::compare(int64 comVal)
   {
      return ossCompareAndSwap64(&_value, comVal, comVal);
   }

   void atomicSigned64::poke(int64 val)
   {
      _value = val;
   }

   //////////////////////////////////////////////////////////////////////////
   // unsigned int
   atomic64::atomic64(unsigned int64 val) : _value((int64)val)
   {
   }

   atomic64::~atomic64()
   {
   }

   void atomic64::initialize(unsigned int64 val)
   {
      _value.initialize((int64)val);
   }

   size_t atomic64::size() const
   {
      return _value.size();
   }

   unsigned int64 atomic64::peek()
   {
      return (unsigned int64)_value.peek();
   }

   unsigned int64 atomic64::add(unsigned int64 val)
   {
      return (unsigned int64)_value.add((int64)val);
   }

   unsigned int64 atomic64::sub(unsigned int64 val)
   {
      return (unsigned int64)_value.add((int64)val);
   }

   unsigned int64 atomic64::bitOR(unsigned int64 val)
   {
      return (unsigned int64)_value.bitOR((int64)val);
   }

   unsigned int64 atomic64::bitAND(unsigned int64 val)
   {
      return (unsigned int64)_value.bitAND((int64)val);
   }

   unsigned int64 atomic64::fetch()
   {
      return (unsigned int64)_value.fetch();
   }

   unsigned int64 atomic64::inc()
   {
      return (unsigned int64)_value.inc();
   }

   unsigned int64 atomic64::dec()
   {
      return (unsigned int64)_value.dec();
   }

   unsigned int64 atomic64::swap(unsigned int64 val)
   {
      return (unsigned int64)_value.swap((int64)val);
   }

   bool atomic64::compareAndSwap(unsigned int64 comVal, unsigned int64 val)
   {
      return (unsigned int64)_value.compareAndSwap((int64)comVal, (int64)val);
   }

   unsigned int64 atomic64::compareAndSwapWithReturn(unsigned int64 comVal, unsigned int64 val)
   {
      return (unsigned int64)_value.compareAndSwapWithReturn((int64)comVal, (int64)val);
   }

   unsigned int64 atomic64::swapGreater(unsigned int64 val)
   {
      return (unsigned int64)_value._swapPredicated((int64)val, predicatedGreater<unsigned int64>());
   }

   unsigned int64 atomic64::swapLess(unsigned int64 val)
   {
      return (unsigned int64)_value._swapPredicated((int64)val, predicatedLess<unsigned int64>());
   }

   bool atomic64::compare(unsigned int64 comVal)
   {
      return (unsigned int64)_value.compare((int64)comVal);
   }

   void atomic64::poke(unsigned int64 val)
   {
      _value.poke((int64)val);
   }
}