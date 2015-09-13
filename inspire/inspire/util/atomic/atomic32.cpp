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
   // uint
   atomic32::atomic32(uint val) : _value((int)val)
   {
   }

   atomic32::~atomic32()
   {
   }

   void atomic32::initialize(uint val)
   {
      _value.initialize((int)val);
   }

   size_t atomic32::size() const
   {
      return _value.size();
   }

   uint atomic32::peek()
   {
      return (uint)_value.peek();
   }

   uint atomic32::add(uint val)
   {
      return (uint)_value.add((int)val);
   }

   uint atomic32::sub(uint val)
   {
      return (uint)_value.add((int)val);
   }

   uint atomic32::bitOR(uint val)
   {
      return (uint)_value.bitOR((int)val);
   }

   uint atomic32::bitAND(uint val)
   {
      return (uint)_value.bitAND((int)val);
   }

   uint atomic32::fetch()
   {
      return (uint)_value.fetch();
   }

   uint atomic32::inc()
   {
      return (uint)_value.inc();
   }

   uint atomic32::dec()
   {
      return (uint)_value.dec();
   }

   uint atomic32::swap(uint val)
   {
      return (uint)_value.swap((int)val);
   }

   bool atomic32::compareAndSwap(uint comVal, uint val)
   {
      return (uint)_value.compareAndSwap((int)comVal, (int)val);
   }

   uint atomic32::compareAndSwapWithReturn(uint comVal, uint val)
   {
      return (uint)_value.compareAndSwapWithReturn((int)comVal, (int)val);
   }

   uint atomic32::swapGreater(uint val)
   {
      return (uint)_value._swapPredicated((int)val, predicatedGreater<uint>());
   }

   uint atomic32::swapLess(uint val)
   {
      return (uint)_value._swapPredicated((int)val, predicatedLess<uint>());
   }

   bool atomic32::compare(uint comVal)
   {
      return (uint)_value.compare((int)comVal);
   }

   void atomic32::poke(uint val)
   {
      _value.poke((int)val);
   }
}