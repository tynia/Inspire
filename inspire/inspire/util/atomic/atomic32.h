#ifndef _INSPIRE_UTIL_ATOMIC_32_H_
#define _INSPIRE_UTIL_ATOMIC_32_H_

namespace inspire {

   class atomic32;

   class atomicSigned32
   {
   public:
      explicit atomicSigned32(int val);
      ~atomicSigned32();

      friend class atomic32;
   private:
      template<class T>
      int  _swapPredicated(int val, const T& predVal);

   public:
      void initialize(int val);
      size_t size() const;
      int peek();
      int add(int val);
      int sub(int val);
      int bitOR(int val);
      int bitAND(int val);
      int fetch();
      int inc();
      int dec();
      int swap(int val);
      bool compareAndSwap(int comVal, int val);
      int compareAndSwapWithReturn(int comVal, int val);
      int swapGreater(int val);
      int swapLess(int val);
      bool compare(int val);
      void poke(int val);

   private:
      volatile int _value;
   };

   class atomic32
   {
   public:
      explicit atomic32(uint val);
      ~atomic32();

   public:
      void initialize(uint val);
      size_t size() const;
      uint peek();
      uint add(uint val);
      uint sub(uint val);
      uint bitOR(uint val);
      uint bitAND(uint val);
      uint fetch();
      uint inc();
      uint dec();
      uint swap(uint val);
      bool compareAndSwap(uint comVal, uint val);
      uint compareAndSwapWithReturn(uint comVal, uint val);
      uint swapGreater(uint val);
      uint swapLess(uint val);
      bool compare(uint val);
      void poke(uint val);

   private:
      atomicSigned32 _value;
   };
}
#endif