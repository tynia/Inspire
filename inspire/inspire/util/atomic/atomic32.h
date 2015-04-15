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
      explicit atomic32(unsigned int val);
      ~atomic32();

   public:
      void initialize(unsigned int val);
      size_t size() const;
      unsigned int peek();
      unsigned int add(unsigned int val);
      unsigned int sub(unsigned int val);
      unsigned int bitOR(unsigned int val);
      unsigned int bitAND(unsigned int val);
      unsigned int fetch();
      unsigned int inc();
      unsigned int dec();
      unsigned int swap(unsigned int val);
      bool compareAndSwap(unsigned int comVal, unsigned int val);
      unsigned int compareAndSwapWithReturn(unsigned int comVal, unsigned int val);
      unsigned int swapGreater(unsigned int val);
      unsigned int swapLess(unsigned int val);
      bool compare(unsigned int val);
      void poke(unsigned int val);

   private:
      atomicSigned32 _value;
   };
}
#endif