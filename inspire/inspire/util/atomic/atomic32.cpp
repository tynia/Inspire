#include "atomic32.h"
#include "atomic.h"

namespace inspire {

   atomicSigned32::atomicSigned32(int val)
   {
      initialize(val);
   }

   atomicSigned32::~atomicSigned32()
   {}

   template<class T>
   int atomicSigned32::_swapPredicated(int val, const T& predVal)
   {
      int prev = peek();
      for (;;)
      {
         int newVal = prev;
         if (predVal.op(val, prev))
         {
            newVal = val;
         }
         int tmp = ossCompareAndSwap32WithReturn(&_value, prev, newVal);
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

   void atomicSigned32::initialize(int val)
   {
      _value = val;
   }

   size_t atomicSigned32::size() const
   {
      return sizeof(_value);
   }

   int atomicSigned32::peek()
   {
      return _value;
   }

   int atomicSigned32::add(int val)
   {
      return ossFetchAndAdd32(&_value, val);
   }

   int atomicSigned32::sub(int val)
   {
      return add(-val);
   }

   int atomicSigned32::bitOR(int val)
   {
      return ossFetchAndOR32(&_value, val);
   }

   int atomicSigned32::bitAND(int val)
   {
      return ossFetchAndAND32(&_value, val);
   }

   int atomicSigned32::fetch()
   {
      return ossAtomicFetch32(&_value);
   }

   int atomicSigned32::inc()
   {
      return ossFetchAndIncrement32(&_value);
   }

   int atomicSigned32::dec()
   {
      return ossFetchAndDecrement32(&_value);
   }

   int atomicSigned32::swap(int val)
   {
      return ossAtomicExchange32(&_value, val);
   }

   bool atomicSigned32::compareAndSwap(int comVal, int val)
   {
      return ossCompareAndSwap32(&_value, comVal, val);
   }

   int atomicSigned32::compareAndSwapWithReturn(int comVal, int val)
   {
      return ossCompareAndSwap32WithReturn(&_value, comVal, val);
   }

   int atomicSigned32::swapGreater(int val)
   {
      return _swapPredicated(val, predicatedGreater<int>());
   }

   int atomicSigned32::swapLess(int val)
   {
      return _swapPredicated(val, predicatedLess<int>());
   }

   bool atomicSigned32::compare(int comVal)
   {
      return ossCompareAndSwap32(&_value, comVal, comVal);
   }

   void atomicSigned32::poke(int val)
   {
      _value = val;
   }

   //////////////////////////////////////////////////////////////////////////
   // unsigned int
   atomic32::atomic32(unsigned int val) : _value((int)val)
   {
   }

   atomic32::~atomic32()
   {
   }

   void atomic32::initialize(unsigned int val)
   {
      _value.initialize((int)val);
   }

   size_t atomic32::size() const
   {
      return _value.size();
   }

   unsigned int atomic32::peek()
   {
      return (unsigned int)_value.peek();
   }

   unsigned int atomic32::add(unsigned int val)
   {
      return (unsigned int)_value.add((int)val);
   }

   unsigned int atomic32::sub(unsigned int val)
   {
      return (unsigned int)_value.add((int)val);
   }

   unsigned int atomic32::bitOR(unsigned int val)
   {
      return (unsigned int)_value.bitOR((int)val);
   }

   unsigned int atomic32::bitAND(unsigned int val)
   {
      return (unsigned int)_value.bitAND((int)val);
   }

   unsigned int atomic32::fetch()
   {
      return (unsigned int)_value.fetch();
   }

   unsigned int atomic32::inc()
   {
      return (unsigned int)_value.inc();
   }

   unsigned int atomic32::dec()
   {
      return (unsigned int)_value.dec();
   }

   unsigned int atomic32::swap(unsigned int val)
   {
      return (unsigned int)_value.swap((int)val);
   }

   bool atomic32::compareAndSwap(unsigned int comVal, unsigned int val)
   {
      return (unsigned int)_value.compareAndSwap((int)comVal, (int)val);
   }

   unsigned int atomic32::compareAndSwapWithReturn(unsigned int comVal, unsigned int val)
   {
      return (unsigned int)_value.compareAndSwapWithReturn((int)comVal, (int)val);
   }

   unsigned int atomic32::swapGreater(unsigned int val)
   {
      return (unsigned int)_value._swapPredicated((int)val, predicatedGreater<unsigned int>());
   }

   unsigned int atomic32::swapLess(unsigned int val)
   {
      return (unsigned int)_value._swapPredicated((int)val, predicatedLess<unsigned int>());
   }

   bool atomic32::compare(unsigned int comVal)
   {
      return (unsigned int)_value.compare((int)comVal);
   }

   void atomic32::poke(unsigned int val)
   {
      _value.poke((int)val);
   }
}