/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Implements (almost always) lock-free atomic operations. The operations here
 * are a subset of that which can be found in C++11's <atomic> header, with a
 * different API to enforce consistent memory ordering constraints.
 *
 * Anyone caught using |volatile| for inter-thread memory safety needs to be
 * sent a copy of this header and the C++11 standard.
 */

#ifndef mozilla_Atomics_h
#define mozilla_Atomics_h

#include "mozilla/Assertions.h"
#include "mozilla/TypeTraits.h"

#include <stdint.h>

/*
 * Our minimum deployment target on clang/OS X is OS X 10.6, whose SDK
 * does not have <atomic>.  So be sure to check for <atomic> support
 * along with C++0x support.
 */
#if defined(__clang__)
   /*
    * clang doesn't like libstdc++'s version of <atomic> before GCC 4.7,
    * due to the loose typing of the __sync_* family of functions done by
    * GCC.  We do not have a particularly good way to detect this sort of
    * case at this point, so just assume that if we're on a Linux system,
    * we can't use the system's <atomic>.
    *
    * OpenBSD uses an old libstdc++ 4.2.1 and thus doesnt have <atomic>.
    */
#  if !defined(__linux__) && !defined(__OpenBSD__) && \
      (__cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)) && \
      __has_include(<atomic>)
#    define MOZ_HAVE_CXX11_ATOMICS
#  endif
/*
 * Android uses a different C++ standard library that does not provide
 * support for <atomic>.
 *
 * GCC 4.5.x and 4.6.x's unspecialized std::atomic template doesn't include
 * inline definitions for the functions declared therein.  This oversight
 * leads to linking errors when using atomic enums.  We therefore require
 * GCC 4.7 or higher.
 */
#elif defined(__GNUC__) && !defined(__ANDROID__)
#  include "mozilla/Compiler.h"
#  if (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L) && \
      MOZ_GCC_VERSION_AT_LEAST(4, 7, 0)
#    define MOZ_HAVE_CXX11_ATOMICS
#  endif
#elif defined(_MSC_VER) && _MSC_VER >= 1700
#  define MOZ_HAVE_CXX11_ATOMICS
#endif

namespace mozilla {

/**
 * An enum of memory ordering possibilities for atomics.
 *
 * Memory ordering is the observable state of distinct values in memory.
 * (It's a separate concept from atomicity, which concerns whether an
 * operation can ever be observed in an intermediate state.  Don't
 * conflate the two!)  Given a sequence of operations in source code on
 * memory, it is *not* always the case that, at all times and on all
 * cores, those operations will appear to have occurred in that exact
 * sequence.  First, the compiler might reorder that sequence, if it
 * thinks another ordering will be more efficient.  Second, the CPU may
 * not expose so consistent a view of memory.  CPUs will often perform
 * their own instruction reordering, above and beyond that performed by
 * the compiler.  And each core has its own memory caches, and accesses
 * (reads and writes both) to "memory" may only resolve to out-of-date
 * cache entries -- not to the "most recently" performed operation in
 * some global sense.  Any access to a value that may be used by
 * multiple threads, potentially across multiple cores, must therefore
 * have a memory ordering imposed on it, for all code on all
 * threads/cores to have a sufficiently coherent worldview.
 *
 * http://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync and
 * http://en.cppreference.com/w/cpp/atomic/memory_order go into more
 * detail on all this, including examples of how each mode works.
 *
 * Note that for simplicity and practicality, not all of the modes in
 * C++11 are supported.  The missing C++11 modes are either subsumed by
 * the modes we provide below, or not relevant for the CPUs we support
 * in Gecko.  These three modes are confusing enough as it is!
 */
enum MemoryOrdering {
  /*
   * Relaxed ordering is the simplest memory ordering: none at all.
   * When the result of a write is observed, nothing may be inferred
   * about other memory.  Writes ostensibly performed "before" on the
   * writing thread may not yet be visible.  Writes performed "after" on
   * the writing thread may already be visible, if the compiler or CPU
   * reordered them.  (The latter can happen if reads and/or writes get
   * held up in per-processor caches.)  Relaxed ordering means
   * operations can always use cached values (as long as the actual
   * updates to atomic values actually occur, correctly, eventually), so
   * it's usually the fastest sort of atomic access.  For this reason,
   * *it's also the most dangerous kind of access*.
   *
   * Relaxed ordering is good for things like process-wide statistics
   * counters that don't need to be consistent with anything else, so
   * long as updates themselves are atomic.  (And so long as any
   * observations of that value can tolerate being out-of-date -- if you
   * need some sort of up-to-date value, you need some sort of other
   * synchronizing operation.)  It's *not* good for locks, mutexes,
   * reference counts, etc. that mediate access to other memory, or must
   * be observably consistent with other memory.
   *
   * x86 architectures don't take advantage of the optimization
   * opportunities that relaxed ordering permits.  Thus it's possible
   * that using relaxed ordering will "work" on x86 but fail elsewhere
   * (ARM, say, which *does* implement non-sequentially-consistent
   * relaxed ordering semantics).  Be extra-careful using relaxed
   * ordering if you can't easily test non-x86 architectures!
   */
  Relaxed,
  /*
   * When an atomic value is updated with ReleaseAcquire ordering, and
   * that new value is observed with ReleaseAcquire ordering, prior
   * writes (atomic or not) are also observable.  What ReleaseAcquire
   * *doesn't* give you is any observable ordering guarantees for
   * ReleaseAcquire-ordered operations on different objects.  For
   * example, if there are two cores that each perform ReleaseAcquire
   * operations on separate objects, each core may or may not observe
   * the operations made by the other core.  The only way the cores can
   * be synchronized with ReleaseAcquire is if they both
   * ReleaseAcquire-access the same object.  This implies that you can't
   * necessarily describe some global total ordering of ReleaseAcquire
   * operations.
   *
   * ReleaseAcquire ordering is good for (as the name implies) atomic
   * operations on values controlling ownership of things: reference
   * counts, mutexes, and the like.  However, if you are thinking about
   * using these to implement your own locks or mutexes, you should take
   * a good, hard look at actual lock or mutex primitives first.
   */
  ReleaseAcquire,
  /*
   * When an atomic value is updated with SequentiallyConsistent
   * ordering, all writes observable when the update is observed, just
   * as with ReleaseAcquire ordering.  But, furthermore, a global total
   * ordering of SequentiallyConsistent operations *can* be described.
   * For example, if two cores perform SequentiallyConsistent operations
   * on separate objects, one core will observably perform its update
   * (and all previous operations will have completed), then the other
   * core will observably perform its update (and all previous
   * operations will have completed).  (Although those previous
   * operations aren't themselves ordered -- they could be intermixed,
   * or ordered if they occur on atomic values with ordering
   * requirements.)  SequentiallyConsistent is the *simplest and safest*
   * ordering of atomic operations -- it's always as if one operation
   * happens, then another, then another, in some order -- and every
   * core observes updates to happen in that single order.  Because it
   * has the most synchronization requirements, operations ordered this
   * way also tend to be slowest.
   *
   * SequentiallyConsistent ordering can be desirable when multiple
   * threads observe objects, and they all have to agree on the
   * observable order of changes to them.  People expect
   * SequentiallyConsistent ordering, even if they shouldn't, when
   * writing code, atomic or otherwise.  SequentiallyConsistent is also
   * the ordering of choice when designing lockless data structures.  If
   * you don't know what order to use, use this one.
   */
  SequentiallyConsistent,
};

} // namespace mozilla

// Build up the underlying intrinsics.
#ifdef MOZ_HAVE_CXX11_ATOMICS

#  include <atomic>

namespace mozilla {
namespace detail {

/*
 * We provide CompareExchangeFailureOrder to work around a bug in some
 * versions of GCC's <atomic> header.  See bug 898491.
 */
template<MemoryOrdering Order> struct AtomicOrderConstraints;

template<>
struct AtomicOrderConstraints<Relaxed>
{
    static const std::memory_order AtomicRMWOrder = std::memory_order_relaxed;
    static const std::memory_order LoadOrder = std::memory_order_relaxed;
    static const std::memory_order StoreOrder = std::memory_order_relaxed;
    static const std::memory_order CompareExchangeFailureOrder =
      std::memory_order_relaxed;
};

template<>
struct AtomicOrderConstraints<ReleaseAcquire>
{
    static const std::memory_order AtomicRMWOrder = std::memory_order_acq_rel;
    static const std::memory_order LoadOrder = std::memory_order_acquire;
    static const std::memory_order StoreOrder = std::memory_order_release;
    static const std::memory_order CompareExchangeFailureOrder =
      std::memory_order_acquire;
};

template<>
struct AtomicOrderConstraints<SequentiallyConsistent>
{
    static const std::memory_order AtomicRMWOrder = std::memory_order_seq_cst;
    static const std::memory_order LoadOrder = std::memory_order_seq_cst;
    static const std::memory_order StoreOrder = std::memory_order_seq_cst;
    static const std::memory_order CompareExchangeFailureOrder =
      std::memory_order_seq_cst;
};

template<typename T, MemoryOrdering Order>
struct IntrinsicBase
{
    typedef std::atomic<T> ValueType;
    typedef AtomicOrderConstraints<Order> OrderedOp;
};

template<typename T, MemoryOrdering Order>
struct IntrinsicMemoryOps : public IntrinsicBase<T, Order>
{
    typedef IntrinsicBase<T, Order> Base;
    static T load(const typename Base::ValueType& ptr) {
      return ptr.load(Base::OrderedOp::LoadOrder);
    }
    static void store(typename Base::ValueType& ptr, T val) {
      ptr.store(val, Base::OrderedOp::StoreOrder);
    }
    static T exchange(typename Base::ValueType& ptr, T val) {
      return ptr.exchange(val, Base::OrderedOp::AtomicRMWOrder);
    }
    static bool compareExchange(typename Base::ValueType& ptr, T oldVal, T newVal) {
      return ptr.compare_exchange_strong(oldVal, newVal,
                                         Base::OrderedOp::AtomicRMWOrder,
                                         Base::OrderedOp::CompareExchangeFailureOrder);
    }
};

template<typename T, MemoryOrdering Order>
struct IntrinsicAddSub : public IntrinsicBase<T, Order>
{
    typedef IntrinsicBase<T, Order> Base;
    static T add(typename Base::ValueType& ptr, T val) {
      return ptr.fetch_add(val, Base::OrderedOp::AtomicRMWOrder);
    }
    static T sub(typename Base::ValueType& ptr, T val) {
      return ptr.fetch_sub(val, Base::OrderedOp::AtomicRMWOrder);
    }
};

template<typename T, MemoryOrdering Order>
struct IntrinsicAddSub<T*, Order> : public IntrinsicBase<T*, Order>
{
    typedef IntrinsicBase<T*, Order> Base;
    static T* add(typename Base::ValueType& ptr, ptrdiff_t val) {
      return ptr.fetch_add(fixupAddend(val), Base::OrderedOp::AtomicRMWOrder);
    }
    static T* sub(typename Base::ValueType& ptr, ptrdiff_t val) {
      return ptr.fetch_sub(fixupAddend(val), Base::OrderedOp::AtomicRMWOrder);
    }
  private:
    /*
     * GCC 4.6's <atomic> header has a bug where adding X to an
     * atomic<T*> is not the same as adding X to a T*.  Hence the need
     * for this function to provide the correct addend.
     */
    static ptrdiff_t fixupAddend(ptrdiff_t val) {
#if defined(__clang__) || defined(_MSC_VER)
      return val;
#elif defined(__GNUC__) && MOZ_GCC_VERSION_AT_LEAST(4, 6, 0) && \
      !MOZ_GCC_VERSION_AT_LEAST(4, 7, 0)
      return val * sizeof(T);
#else
      return val;
#endif
    }
};

template<typename T, MemoryOrdering Order>
struct IntrinsicIncDec : public IntrinsicAddSub<T, Order>
{
    typedef IntrinsicBase<T, Order> Base;
    static T inc(typename Base::ValueType& ptr) {
      return IntrinsicAddSub<T, Order>::add(ptr, 1);
    }
    static T dec(typename Base::ValueType& ptr) {
      return IntrinsicAddSub<T, Order>::sub(ptr, 1);
    }
};

template<typename T, MemoryOrdering Order>
struct AtomicIntrinsics : public IntrinsicMemoryOps<T, Order>,
                          public IntrinsicIncDec<T, Order>
{
    typedef IntrinsicBase<T, Order> Base;
    static T or_(typename Base::ValueType& ptr, T val) {
      return ptr.fetch_or(val, Base::OrderedOp::AtomicRMWOrder);
    }
    static T xor_(typename Base::ValueType& ptr, T val) {
      return ptr.fetch_xor(val, Base::OrderedOp::AtomicRMWOrder);
    }
    static T and_(typename Base::ValueType& ptr, T val) {
      return ptr.fetch_and(val, Base::OrderedOp::AtomicRMWOrder);
    }
};

template<typename T, MemoryOrdering Order>
struct AtomicIntrinsics<T*, Order>
  : public IntrinsicMemoryOps<T*, Order>, public IntrinsicIncDec<T*, Order>
{
};

} // namespace detail
} // namespace mozilla

#elif defined(__GNUC__)

namespace mozilla {
namespace detail {

/*
 * The __sync_* family of intrinsics is documented here:
 *
 * http://gcc.gnu.org/onlinedocs/gcc-4.6.4/gcc/Atomic-Builtins.html
 *
 * While these intrinsics are deprecated in favor of the newer __atomic_*
 * family of intrincs:
 *
 * http://gcc.gnu.org/onlinedocs/gcc-4.7.3/gcc/_005f_005fatomic-Builtins.html
 *
 * any GCC version that supports the __atomic_* intrinsics will also support
 * the <atomic> header and so will be handled above.  We provide a version of
 * atomics using the __sync_* intrinsics to support older versions of GCC.
 *
 * All __sync_* intrinsics that we use below act as full memory barriers, for
 * both compiler and hardware reordering, except for __sync_lock_test_and_set,
 * which is a only an acquire barrier.  When we call __sync_lock_test_and_set,
 * we add a barrier above it as appropriate.
 */

template<MemoryOrdering Order> struct Barrier;

/*
 * Some processors (in particular, x86) don't require quite so many calls to
 * __sync_sychronize as our specializations of Barrier produce.  If
 * performance turns out to be an issue, defining these specializations
 * on a per-processor basis would be a good first tuning step.
 */

template<>
struct Barrier<Relaxed>
{
    static void beforeLoad() {}
    static void afterLoad() {}
    static void beforeStore() {}
    static void afterStore() {}
};

template<>
struct Barrier<ReleaseAcquire>
{
    static void beforeLoad() {}
    static void afterLoad() { __sync_synchronize(); }
    static void beforeStore() { __sync_synchronize(); }
    static void afterStore() {}
};

template<>
struct Barrier<SequentiallyConsistent>
{
    static void beforeLoad() { __sync_synchronize(); }
    static void afterLoad() { __sync_synchronize(); }
    static void beforeStore() { __sync_synchronize(); }
    static void afterStore() { __sync_synchronize(); }
};

template<typename T, MemoryOrdering Order>
struct IntrinsicMemoryOps
{
    static T load(const T& ptr) {
      Barrier<Order>::beforeLoad();
      T val = ptr;
      Barrier<Order>::afterLoad();
      return val;
    }
    static void store(T& ptr, T val) {
      Barrier<Order>::beforeStore();
      ptr = val;
      Barrier<Order>::afterStore();
    }
    static T exchange(T& ptr, T val) {
      // __sync_lock_test_and_set is only an acquire barrier; loads and stores
      // can't be moved up from after to before it, but they can be moved down
      // from before to after it.  We may want a stricter ordering, so we need
      // an explicit barrier.

      Barrier<Order>::beforeStore();
      return __sync_lock_test_and_set(&ptr, val);
    }
    static bool compareExchange(T& ptr, T oldVal, T newVal) {
      return __sync_bool_compare_and_swap(&ptr, oldVal, newVal);
    }
};

template<typename T>
struct IntrinsicAddSub
{
    typedef T ValueType;
    static T add(T& ptr, T val) {
      return __sync_fetch_and_add(&ptr, val);
    }
    static T sub(T& ptr, T val) {
      return __sync_fetch_and_sub(&ptr, val);
    }
};

template<typename T>
struct IntrinsicAddSub<T*>
{
    typedef T* ValueType;
    /*
     * The reinterpret_casts are needed so that
     * __sync_fetch_and_{add,sub} will properly type-check.
     *
     * Also, these functions do not provide standard semantics for
     * pointer types, so we need to adjust the addend.
     */
    static ValueType add(ValueType& ptr, ptrdiff_t val) {
      ValueType amount = reinterpret_cast<ValueType>(val * sizeof(T));
      return __sync_fetch_and_add(&ptr, amount);
    }
    static ValueType sub(ValueType& ptr, ptrdiff_t val) {
      ValueType amount = reinterpret_cast<ValueType>(val * sizeof(T));
      return __sync_fetch_and_sub(&ptr, amount);
    }
};

template<typename T>
struct IntrinsicIncDec : public IntrinsicAddSub<T>
{
    static T inc(T& ptr) { return IntrinsicAddSub<T>::add(ptr, 1); }
    static T dec(T& ptr) { return IntrinsicAddSub<T>::sub(ptr, 1); }
};

template<typename T, MemoryOrdering Order>
struct AtomicIntrinsics : public IntrinsicMemoryOps<T, Order>,
                          public IntrinsicIncDec<T>
{
    static T or_(T& ptr, T val) {
      return __sync_fetch_and_or(&ptr, val);
    }
    static T xor_(T& ptr, T val) {
      return __sync_fetch_and_xor(&ptr, val);
    }
    static T and_(T& ptr, T val) {
      return __sync_fetch_and_and(&ptr, val);
    }
};

template<typename T, MemoryOrdering Order>
struct AtomicIntrinsics<T*, Order> : public IntrinsicMemoryOps<T*, Order>,
                                     public IntrinsicIncDec<T*>
{
};

} // namespace detail
} // namespace mozilla

#elif defined(_MSC_VER)

/*
 * Windows comes with a full complement of atomic operations.
 * Unfortunately, most of those aren't available for Windows XP (even if
 * the compiler supports intrinsics for them), which is the oldest
 * version of Windows we support.  Therefore, we only provide operations
 * on 32-bit datatypes for 32-bit Windows versions; for 64-bit Windows
 * versions, we support 64-bit datatypes as well.
 *
 * To avoid namespace pollution issues, we declare whatever functions we
 * need ourselves.
 */

extern "C" {
long __cdecl _InterlockedExchangeAdd(long volatile* dst, long value);
long __cdecl _InterlockedOr(long volatile* dst, long value);
long __cdecl _InterlockedXor(long volatile* dst, long value);
long __cdecl _InterlockedAnd(long volatile* dst, long value);
long __cdecl _InterlockedExchange(long volatile *dst, long value);
long __cdecl _InterlockedCompareExchange(long volatile *dst, long newVal, long oldVal);
}

#  pragma intrinsic(_InterlockedExchangeAdd)
#  pragma intrinsic(_InterlockedOr)
#  pragma intrinsic(_InterlockedXor)
#  pragma intrinsic(_InterlockedAnd)
#  pragma intrinsic(_InterlockedExchange)
#  pragma intrinsic(_InterlockedCompareExchange)

namespace mozilla {
namespace detail {

#  if !defined(_M_IX86) && !defined(_M_X64)
     /*
      * The implementations below are optimized for x86ish systems.  You
      * will have to modify them if you are porting to Windows on a
      * different architecture.
      */
#    error "Unknown CPU type"
#  endif

/*
 * The PrimitiveIntrinsics template should define |Type|, the datatype of size
 * DataSize upon which we operate, and the following eight functions.
 *
 * static Type add(Type* ptr, Type val);
 * static Type sub(Type* ptr, Type val);
 * static Type or_(Type* ptr, Type val);
 * static Type xor_(Type* ptr, Type val);
 * static Type and_(Type* ptr, Type val);
 *
 *   These functions perform the obvious operation on the value contained in
 *   |*ptr| combined with |val| and return the value previously stored in
 *   |*ptr|.
 *
 * static void store(Type* ptr, Type val);
 *
 *   This function atomically stores |val| into |*ptr| and must provide a full
 *   memory fence after the store to prevent compiler and hardware instruction
 *   reordering.  It should also act as a compiler barrier to prevent reads and
 *   writes from moving to after the store.
 *
 * static Type exchange(Type* ptr, Type val);
 *
 *   This function atomically stores |val| into |*ptr| and returns the previous
 *   contents of *ptr;
 *
 * static bool compareExchange(Type* ptr, Type oldVal, Type newVal);
 *
 *   This function atomically performs the following operation:
 *
 *     if (*ptr == oldVal) {
 *       *ptr = newVal;
 *       return true;
 *     } else {
 *       return false;
 *     }
 *
 */
template<size_t DataSize> struct PrimitiveIntrinsics;

template<>
struct PrimitiveIntrinsics<4>
{
    typedef long Type;

    static Type add(Type* ptr, Type val) {
      return _InterlockedExchangeAdd(ptr, val);
    }
    static Type sub(Type* ptr, Type val) {
      /*
       * _InterlockedExchangeSubtract isn't available before Windows 7,
       * and we must support Windows XP.
       */
      return _InterlockedExchangeAdd(ptr, -val);
    }
    static Type or_(Type* ptr, Type val) {
      return _InterlockedOr(ptr, val);
    }
    static Type xor_(Type* ptr, Type val) {
      return _InterlockedXor(ptr, val);
    }
    static Type and_(Type* ptr, Type val) {
      return _InterlockedAnd(ptr, val);
    }
    static void store(Type* ptr, Type val) {
      _InterlockedExchange(ptr, val);
    }
    static Type exchange(Type* ptr, Type val) {
      return _InterlockedExchange(ptr, val);
    }
    static bool compareExchange(Type* ptr, Type oldVal, Type newVal) {
      return _InterlockedCompareExchange(ptr, newVal, oldVal) == oldVal;
    }
};

#  if defined(_M_X64)

extern "C" {
long long __cdecl _InterlockedExchangeAdd64(long long volatile* dst,
                                            long long value);
long long __cdecl _InterlockedOr64(long long volatile* dst,
                                   long long value);
long long __cdecl _InterlockedXor64(long long volatile* dst,
                                    long long value);
long long __cdecl _InterlockedAnd64(long long volatile* dst,
                                    long long value);
long long __cdecl _InterlockedExchange64(long long volatile* dst,
                                         long long value);
long long __cdecl _InterlockedCompareExchange64(long long volatile* dst,
                                                long long newVal,
                                                long long oldVal);
}

#    pragma intrinsic(_InterlockedExchangeAdd64)
#    pragma intrinsic(_InterlockedOr64)
#    pragma intrinsic(_InterlockedXor64)
#    pragma intrinsic(_InterlockedAnd64)
#    pragma intrinsic(_InterlockedExchange64)
#    pragma intrinsic(_InterlockedCompareExchange64)

template <>
struct PrimitiveIntrinsics<8>
{
    typedef __int64 Type;

    static Type add(Type* ptr, Type val) {
      return _InterlockedExchangeAdd64(ptr, val);
    }
    static Type sub(Type* ptr, Type val) {
      /*
       * There is no _InterlockedExchangeSubtract64.
       */
      return _InterlockedExchangeAdd64(ptr, -val);
    }
    static Type or_(Type* ptr, Type val) {
      return _InterlockedOr64(ptr, val);
    }
    static Type xor_(Type* ptr, Type val) {
      return _InterlockedXor64(ptr, val);
    }
    static Type and_(Type* ptr, Type val) {
      return _InterlockedAnd64(ptr, val);
    }
    static void store(Type* ptr, Type val) {
      _InterlockedExchange64(ptr, val);
    }
    static Type exchange(Type* ptr, Type val) {
      return _InterlockedExchange64(ptr, val);
    }
    static bool compareExchange(Type* ptr, Type oldVal, Type newVal) {
      return _InterlockedCompareExchange64(ptr, newVal, oldVal) == oldVal;
    }
};

#  endif

extern "C" { void _ReadWriteBarrier(); }

#  pragma intrinsic(_ReadWriteBarrier)

template<MemoryOrdering Order> struct Barrier;

/*
 * We do not provide an afterStore method in Barrier, as Relaxed and
 * ReleaseAcquire orderings do not require one, and the required barrier
 * for SequentiallyConsistent is handled by PrimitiveIntrinsics.
 */

template<>
struct Barrier<Relaxed>
{
    static void beforeLoad() {}
    static void afterLoad() {}
    static void beforeStore() {}
};

template<>
struct Barrier<ReleaseAcquire>
{
    static void beforeLoad() {}
    static void afterLoad() { _ReadWriteBarrier(); }
    static void beforeStore() { _ReadWriteBarrier(); }
};

template<>
struct Barrier<SequentiallyConsistent>
{
    static void beforeLoad() { _ReadWriteBarrier(); }
    static void afterLoad() { _ReadWriteBarrier(); }
    static void beforeStore() { _ReadWriteBarrier(); }
};

template<typename PrimType, typename T>
struct CastHelper
{
  static PrimType toPrimType(T val) { return static_cast<PrimType>(val); }
  static T fromPrimType(PrimType val) { return static_cast<T>(val); }
};

template<typename PrimType, typename T>
struct CastHelper<PrimType, T*>
{
  static PrimType toPrimType(T* val) { return reinterpret_cast<PrimType>(val); }
  static T* fromPrimType(PrimType val) { return reinterpret_cast<T*>(val); }
};

template<typename T>
struct IntrinsicBase
{
    typedef T ValueType;
    typedef PrimitiveIntrinsics<sizeof(T)> Primitives;
    typedef typename Primitives::Type PrimType;
    static_assert(sizeof(PrimType) == sizeof(T),
                  "Selection of PrimitiveIntrinsics was wrong");
    typedef CastHelper<PrimType, T> Cast;
};

template<typename T, MemoryOrdering Order>
struct IntrinsicMemoryOps : public IntrinsicBase<T>
{
    static ValueType load(const ValueType& ptr) {
      Barrier<Order>::beforeLoad();
      ValueType val = ptr;
      Barrier<Order>::afterLoad();
      return val;
    }
    static void store(ValueType& ptr, ValueType val) {
      // For SequentiallyConsistent, Primitives::store() will generate the
      // proper memory fence.  Everything else just needs a barrier before
      // the store.
      if (Order == SequentiallyConsistent) {
        Primitives::store(reinterpret_cast<PrimType*>(&ptr),
                          Cast::toPrimType(val));
      } else {
        Barrier<Order>::beforeStore();
        ptr = val;
      }
    }
    static ValueType exchange(ValueType& ptr, ValueType val) {
      PrimType oldval =
        Primitives::exchange(reinterpret_cast<PrimType*>(&ptr),
                             Cast::toPrimType(val));
      return Cast::fromPrimType(oldval);
    }
    static bool compareExchange(ValueType& ptr, ValueType oldVal, ValueType newVal) {
      return Primitives::compareExchange(reinterpret_cast<PrimType*>(&ptr),
                                         Cast::toPrimType(oldVal),
                                         Cast::toPrimType(newVal));
    }
};

template<typename T>
struct IntrinsicApplyHelper : public IntrinsicBase<T>
{
    typedef PrimType (*BinaryOp)(PrimType*, PrimType);
    typedef PrimType (*UnaryOp)(PrimType*);

    static ValueType applyBinaryFunction(BinaryOp op, ValueType& ptr,
                                         ValueType val) {
      PrimType* primTypePtr = reinterpret_cast<PrimType*>(&ptr);
      PrimType primTypeVal = Cast::toPrimType(val);
      return Cast::fromPrimType(op(primTypePtr, primTypeVal));
    }

    static ValueType applyUnaryFunction(UnaryOp op, ValueType& ptr) {
      PrimType* primTypePtr = reinterpret_cast<PrimType*>(&ptr);
      return Cast::fromPrimType(op(primTypePtr));
    }
};

template<typename T>
struct IntrinsicAddSub : public IntrinsicApplyHelper<T>
{
    static ValueType add(ValueType& ptr, ValueType val) {
      return applyBinaryFunction(&Primitives::add, ptr, val);
    }
    static ValueType sub(ValueType& ptr, ValueType val) {
      return applyBinaryFunction(&Primitives::sub, ptr, val);
    }
};

template<typename T>
struct IntrinsicAddSub<T*> : public IntrinsicApplyHelper<T*>
{
    static ValueType add(ValueType& ptr, ptrdiff_t amount) {
      return applyBinaryFunction(&Primitives::add, ptr,
                                 (ValueType)(amount * sizeof(ValueType)));
    }
    static ValueType sub(ValueType& ptr, ptrdiff_t amount) {
      return applyBinaryFunction(&Primitives::sub, ptr,
                                 (ValueType)(amount * sizeof(ValueType)));
    }
};

template<typename T>
struct IntrinsicIncDec : public IntrinsicAddSub<T>
{
    static ValueType inc(ValueType& ptr) { return add(ptr, 1); }
    static ValueType dec(ValueType& ptr) { return sub(ptr, 1); }
};

template<typename T, MemoryOrdering Order>
struct AtomicIntrinsics : public IntrinsicMemoryOps<T, Order>,
                          public IntrinsicIncDec<T>
{
    static ValueType or_(ValueType& ptr, T val) {
      return applyBinaryFunction(&Primitives::or_, ptr, val);
    }
    static ValueType xor_(ValueType& ptr, T val) {
      return applyBinaryFunction(&Primitives::xor_, ptr, val);
    }
    static ValueType and_(ValueType& ptr, T val) {
      return applyBinaryFunction(&Primitives::and_, ptr, val);
    }
};

template<typename T, MemoryOrdering Order>
struct AtomicIntrinsics<T*, Order> : public IntrinsicMemoryOps<T*, Order>,
                                     public IntrinsicIncDec<T*>
{
};

} // namespace detail
} // namespace mozilla

#else
# error "Atomic compiler intrinsics are not supported on your platform"
#endif

namespace mozilla {

namespace detail {

template<typename T, MemoryOrdering Order>
class AtomicBase
{
    // We only support 32-bit types on 32-bit Windows, which constrains our
    // implementation elsewhere.  But we support pointer-sized types everywhere.
    static_assert(sizeof(T) == 4 || (sizeof(uintptr_t) == 8 && sizeof(T) == 8),
                  "mozilla/Atomics.h only supports 32-bit and pointer-sized types");

  protected:
    typedef typename detail::AtomicIntrinsics<T, Order> Intrinsics;
    typename Intrinsics::ValueType mValue;

  public:
    AtomicBase() : mValue() {}
    AtomicBase(T aInit) { Intrinsics::store(mValue, aInit); }

    operator T() const { return Intrinsics::load(mValue); }

    T operator=(T aValue) {
      Intrinsics::store(mValue, aValue);
      return aValue;
    }

    /**
     * Performs an atomic swap operation.  aValue is stored and the previous
     * value of this variable is returned.
     */
    T exchange(T aValue) {
      return Intrinsics::exchange(mValue, aValue);
    }

    /**
     * Performs an atomic compare-and-swap operation and returns true if it
     * succeeded. This is equivalent to atomically doing
     *
     *   if (mValue == aOldValue) {
     *     mValue = aNewValue;
     *     return true;
     *   } else {
     *     return false;
     *   }
     */
    bool compareExchange(T aOldValue, T aNewValue) {
      return Intrinsics::compareExchange(mValue, aOldValue, aNewValue);
    }

  private:
    template<MemoryOrdering AnyOrder>
    AtomicBase(const AtomicBase<T, AnyOrder>& aCopy) MOZ_DELETE;
};

template<typename T, MemoryOrdering Order>
class AtomicBaseIncDec : public AtomicBase<T, Order>
{
    typedef typename detail::AtomicBase<T, Order> Base;

  public:
    AtomicBaseIncDec() : Base() {}
    AtomicBaseIncDec(T aInit) : Base(aInit) {}

    using Base::operator=;

    T operator++(int) { return Base::Intrinsics::inc(Base::mValue); }
    T operator--(int) { return Base::Intrinsics::dec(Base::mValue); }
    T operator++() { return Base::Intrinsics::inc(Base::mValue) + 1; }
    T operator--() { return Base::Intrinsics::dec(Base::mValue) - 1; }

  private:
    template<MemoryOrdering AnyOrder>
    AtomicBaseIncDec(const AtomicBaseIncDec<T, AnyOrder>& aCopy) MOZ_DELETE;
};

} // namespace detail

/**
 * A wrapper for a type that enforces that all memory accesses are atomic.
 *
 * In general, where a variable |T foo| exists, |Atomic<T> foo| can be used in
 * its place.  Implementations for integral and pointer types are provided
 * below.
 *
 * Atomic accesses are sequentially consistent by default.  You should
 * use the default unless you are tall enough to ride the
 * memory-ordering roller coaster (if you're not sure, you aren't) and
 * you have a compelling reason to do otherwise.
 *
 * There is one exception to the case of atomic memory accesses: providing an
 * initial value of the atomic value is not guaranteed to be atomic.  This is a
 * deliberate design choice that enables static atomic variables to be declared
 * without introducing extra static constructors.
 */
template<typename T,
         MemoryOrdering Order = SequentiallyConsistent,
         typename Enable = void>
class Atomic;

/**
 * Atomic<T> implementation for integral types.
 *
 * In addition to atomic store and load operations, compound assignment and
 * increment/decrement operators are implemented which perform the
 * corresponding read-modify-write operation atomically.  Finally, an atomic
 * swap method is provided.
 */
template<typename T, MemoryOrdering Order>
class Atomic<T, Order, typename EnableIf<IsIntegral<T>::value>::Type>
  : public detail::AtomicBaseIncDec<T, Order>
{
    typedef typename detail::AtomicBaseIncDec<T, Order> Base;

  public:
    Atomic() : Base() {}
    Atomic(T aInit) : Base(aInit) {}

    using Base::operator=;

    T operator+=(T delta) { return Base::Intrinsics::add(Base::mValue, delta) + delta; }
    T operator-=(T delta) { return Base::Intrinsics::sub(Base::mValue, delta) - delta; }
    T operator|=(T val) { return Base::Intrinsics::or_(Base::mValue, val) | val; }
    T operator^=(T val) { return Base::Intrinsics::xor_(Base::mValue, val) ^ val; }
    T operator&=(T val) { return Base::Intrinsics::and_(Base::mValue, val) & val; }

  private:
    Atomic(Atomic<T, Order>& aOther) MOZ_DELETE;
};

/**
 * Atomic<T> implementation for pointer types.
 *
 * An atomic compare-and-swap primitive for pointer variables is provided, as
 * are atomic increment and decement operators.  Also provided are the compound
 * assignment operators for addition and subtraction. Atomic swap (via
 * exchange()) is included as well.
 */
template<typename T, MemoryOrdering Order>
class Atomic<T*, Order> : public detail::AtomicBaseIncDec<T*, Order>
{
    typedef typename detail::AtomicBaseIncDec<T*, Order> Base;

  public:
    Atomic() : Base() {}
    Atomic(T* aInit) : Base(aInit) {}

    using Base::operator=;

    T* operator+=(ptrdiff_t delta) {
      return Base::Intrinsics::add(Base::mValue, delta) + delta;
    }
    T* operator-=(ptrdiff_t delta) {
      return Base::Intrinsics::sub(Base::mValue, delta) - delta;
    }

  private:
    Atomic(Atomic<T*, Order>& aOther) MOZ_DELETE;
};

/**
 * Atomic<T> implementation for enum types.
 *
 * The atomic store and load operations and the atomic swap method is provided.
 */
template<typename T, MemoryOrdering Order>
class Atomic<T, Order, typename EnableIf<IsEnum<T>::value>::Type>
  : public detail::AtomicBase<T, Order>
{
    typedef typename detail::AtomicBase<T, Order> Base;

  public:
    Atomic() : Base() {}
    Atomic(T aInit) : Base(aInit) {}

    using Base::operator=;

  private:
    Atomic(Atomic<T, Order>& aOther) MOZ_DELETE;
};

} // namespace mozilla

#endif /* mozilla_Atomics_h */
