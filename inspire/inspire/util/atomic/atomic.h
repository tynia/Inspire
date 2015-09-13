#ifndef _INSPIRE_UTIL_ATOMIC_H_
#define _INSPIRE_UTIL_ATOMIC_H_

#include "inspire.h"

namespace inspire {

   template<class T>
   class predicatedGreater
   {
   public:
      bool op( const T& lhs, const T& rhs) const
      {
         return lhs > rhs;
      }
   };

   template<class T>
   class predicatedLess
   {
   public:
      bool op( const T& lhs, const T& rhs) const
      {
         return lhs < rhs;
      }
   };

   //////////////////////////////////////////////////////////////////////////
   inline int ossFetchAndAdd32(volatile int* pVal, int addVal)
   {
#ifdef _WIN32
      return InterlockedExchangeAdd((long*)pVal, (long)addVal);
#else
      return __sync_fetch_and_add((volatile int*)pVal, addVal);
#endif
   }

   inline int ossFetchAndAND32(volatile int* pVal, int andVal)
   {
#ifdef _WIN32
      return _InterlockedAnd((long*)pVal, (long)andVal);
#else
      return __sync_fetch_and_and((volatile int*)pVal, andVal);
#endif
   }

   inline int ossFetchAndOR32(volatile int* pVal, int orVal)
   {
#ifdef _WIN32
      return _InterlockedOr((long*)pVal, (long)orVal);
#else
      return __sync_fetch_and_or((volatile int*)pVal, orVal);
#endif
   }

   inline int ossFetchAndXOR32(volatile int* pVal, int xorVal)
   {
#ifdef _WIN32
      return _InterlockedXor((long*)pVal, (long)xorVal);
#else
      return __sync_fetch_and_xor((volatile int*)pVal, xorVal);
#endif
   }

   inline int ossCompareAndSwap32(volatile int* pVal, int comVal, int newVal)
   {
#ifdef _WIN32
      return (uint)comVal == InterlockedCompareExchange((long*)pVal, (long)newVal, (long)comVal);
#else
      return comVal == __sync_val_compare_and_swap((volatile int*)pVal, comVal, newVal);
#endif
   }

   inline int ossCompareAndSwap32WithReturn(volatile int* pVal, int comVal, int newVal)
   {
#ifdef _WIN32
      return InterlockedCompareExchange((long*)pVal, (long)newVal, (long)comVal);
#else
      return __sync_val_compare_and_swap((volatile int*)pVal, comVal, newVal);
#endif
   }

   inline int ossAtomicExchange32(volatile int* pVal, int newVal)
   {
#ifdef _WIN32
      return InterlockedExchange((long*)pVal, (long)newVal);
#else
      return __sync_lock_test_and_set((volatile int64*)pVal, comVal, newVal);
#endif
   }

   inline int ossAtomicPeek32(volatile int* pVal)
   {
      return *(int*)pVal;
   }
   
#define ossAtomicFetch32(pVal)   \
   ossFetchAndAdd32((volatile int*)pVal, 0)

#define ossFetchAndIncrement32(pVal)   \
   ossFetchAndAdd32((volatile int*)pVal, 1)

#define ossFetchAndDecrement32(pVal)   \
   ossFetchAndAdd32((volatile int*)pVal, -1)

   //////////////////////////////////////////////////////////////////////////
   inline int64 ossFetchAndAdd64(volatile int64* pVal, int64 addVal)
   {
#ifdef _WIN32
      return InterlockedExchangeAdd64((int64*)pVal, addVal);
#else
      return __sync_fetch_and_add((volatile int64*)pVal, addVal);
#endif
   }

   inline int64 ossFetchAndAND64(volatile int64* pVal, int64 andVal)
   {
#ifdef _WIN32
      return InterlockedAnd64((int64*)pVal, (int64)andVal);
#else
      return __sync_fetch_and_and((volatile int64*)pVal, andVal);
#endif
   }

   inline int64 ossFetchAndOR64(volatile int64* pVal, int64 orVal)
   {
#ifdef _WIN32
      return InterlockedOr64((int64*)pVal, orVal);
#else
      return __sync_fetch_and_or((volatile int64*)pVal, orVal);
#endif
   }

   inline int64 ossFetchAndXOR64(volatile int64* pVal, int64 xorVal)
   {
#ifdef _WIN32
      return InterlockedXor64((int64*)pVal, (int64)xorVal);
#else
      return __sync_fetch_and_xor((volatile int64*)pVal, xorVal);
#endif
   }

   inline int64 ossCompareAndSwap64(volatile int64* pVal, int64 comVal, int64 newVal)
   {
#ifdef _WIN32
      return (uint)comVal == InterlockedCompareExchange64((int64*)pVal, newVal, comVal);
#else
      return comVal == __sync_val_compare_and_swap((volatile int64*)pVal, comVal, newVal);
#endif
   }

   inline int64 ossCompareAndSwap64WithReturn(volatile int64* pVal, int64 comVal, int64 newVal)
   {
#ifdef _WIN32
      return InterlockedCompareExchange64((int64*)pVal, newVal, comVal);
#else
      return __sync_val_compare_and_swap((volatile int64*)pVal, comVal, newVal);
#endif
   }

   inline int64 ossAtomicExchange64(volatile int64* pVal, int64 newVal)
   {
#ifdef _WIN32
      return InterlockedExchange64((int64*)pVal, newVal);
#else
      return __sync_lock_test_and_set((volatile int64*)pVal, comVal, newVal);
#endif
   }

   inline int64 ossAtomicPeek64(volatile int64* pVal)
   {
      return *(int64*)pVal;
   }

#define ossAtomicFetch64(pVal)   \
   ossFetchAndAdd64((volatile int64*)pVal, 0)

#define ossFetchAndIncrement64(pVal)   \
   ossFetchAndAdd64((volatile int64*)pVal, 1)

#define ossFetchAndDecrement64(pVal)   \
   ossFetchAndAdd64((volatile int64*)pVal, -1)
}
#endif