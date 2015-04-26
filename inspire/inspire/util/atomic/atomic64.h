#ifndef _INSPIRE_UTIL_ATOMIC_64_H_
#define _INSPIRE_UTIL_ATOMIC_64_H_

#include "inspire.h"

namespace inspire {

   class atomic64;

   class atomicSigned64
   {
   public:
      typedef long long int64;
      atomicSigned64(int64 val);
      ~atomicSigned64();

      friend class atomic64;

   private:
      template<class T>
      int64  _swapPredicated(int64 val, const T& predVal);

   public:
      void initialize(int64 val);
      size_t size() const;
      int64 peek();
      int64 add(int64 val);
      int64 sub(int64 val);
      int64 bitOR(int64 val);
      int64 bitAND(int64 val);
      int64 fetch();
      int64 inc();
      int64 dec();
      int64 swap(int64 val);
      bool compareAndSwap(int64 comVal, int64 val);
      int64 compareAndSwapWithReturn(int64 comVal, int64 val);
      int64 swapGreater(int64 val);
      int64 swapLess(int64 val);
      bool compare(int64 val);
      void poke(int64 val);

   private:
      volatile int64 _value;
   };

   class atomic64
   {
   public:
      explicit atomic64(uint64 val);
      ~atomic64();

   public:
      void initialize(uint64 val);
      size_t size() const;
      uint64 peek();
      uint64 add(uint64 val);
      uint64 sub(uint64 val);
      uint64 bitOR(uint64 val);
      uint64 bitAND(uint64 val);
      uint64 fetch();
      uint64 inc();
      uint64 dec();
      uint64 swap(uint64 val);
      bool compareAndSwap(uint64 comVal, uint64 val);
      uint64 compareAndSwapWithReturn(uint64 comVal, uint64 val);
      uint64 swapGreater(uint64 val);
      uint64 swapLess(uint64 val);
      bool compare(uint64 val);
      void poke(uint64 val);

   private:
      atomicSigned64 _value;
   };
}
#endif