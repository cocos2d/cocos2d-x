/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A type/length-parametrized vector class. */

#ifndef mozilla_Vector_h
#define mozilla_Vector_h

#include "mozilla/AllocPolicy.h"
#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/MathAlgorithms.h"
#include "mozilla/MemoryReporting.h"
#include "mozilla/Move.h"
#include "mozilla/NullPtr.h"
#include "mozilla/ReentrancyGuard.h"
#include "mozilla/TemplateLib.h"
#include "mozilla/TypeTraits.h"
#include "mozilla/Util.h"

#include <new> // for placement new

/* Silence dire "bugs in previous versions of MSVC have been fixed" warnings */
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4345)
#endif

namespace mozilla {

template<typename T, size_t N, class AllocPolicy, class ThisVector>
class VectorBase;

namespace detail {

/*
 * Check that the given capacity wastes the minimal amount of space if
 * allocated on the heap.  This means that cap*sizeof(T) is as close to a
 * power-of-two as possible.  growStorageBy() is responsible for ensuring
 * this.
 */
template<typename T>
static bool CapacityHasExcessSpace(size_t cap)
{
  size_t size = cap * sizeof(T);
  return RoundUpPow2(size) - size >= sizeof(T);
}

/*
 * This template class provides a default implementation for vector operations
 * when the element type is not known to be a POD, as judged by IsPod.
 */
template<typename T, size_t N, class AP, class ThisVector, bool IsPod>
struct VectorImpl
{
    /* Destroys constructed objects in the range [begin, end). */
    static inline void destroy(T* begin, T* end) {
      for (T* p = begin; p < end; ++p)
        p->~T();
    }

    /* Constructs objects in the uninitialized range [begin, end). */
    static inline void initialize(T* begin, T* end) {
      for (T* p = begin; p < end; ++p)
        new(p) T();
    }

    /*
     * Copy-constructs objects in the uninitialized range
     * [dst, dst+(srcend-srcbeg)) from the range [srcbeg, srcend).
     */
    template<typename U>
    static inline void copyConstruct(T* dst, const U* srcbeg, const U* srcend) {
      for (const U* p = srcbeg; p < srcend; ++p, ++dst)
        new(dst) T(*p);
    }

    /*
     * Move-constructs objects in the uninitialized range
     * [dst, dst+(srcend-srcbeg)) from the range [srcbeg, srcend).
     */
    template<typename U>
    static inline void moveConstruct(T* dst, const U* srcbeg, const U* srcend) {
      for (const U* p = srcbeg; p < srcend; ++p, ++dst)
        new(dst) T(Move(*p));
    }

    /*
     * Copy-constructs objects in the uninitialized range [dst, dst+n) from the
     * same object u.
     */
    template<typename U>
    static inline void copyConstructN(T* dst, size_t n, const U& u) {
      for (T* end = dst + n; dst < end; ++dst)
        new(dst) T(u);
    }

    /*
     * Grows the given buffer to have capacity newCap, preserving the objects
     * constructed in the range [begin, end) and updating v. Assumes that (1)
     * newCap has not overflowed, and (2) multiplying newCap by sizeof(T) will
     * not overflow.
     */
    static inline bool
    growTo(VectorBase<T, N, AP, ThisVector>& v, size_t newCap) {
      MOZ_ASSERT(!v.usingInlineStorage());
      MOZ_ASSERT(!CapacityHasExcessSpace<T>(newCap));
      T* newbuf = reinterpret_cast<T*>(v.malloc_(newCap * sizeof(T)));
      if (!newbuf)
        return false;
      T* dst = newbuf;
      T* src = v.beginNoCheck();
      for (; src < v.endNoCheck(); ++dst, ++src)
        new(dst) T(Move(*src));
      VectorImpl::destroy(v.beginNoCheck(), v.endNoCheck());
      v.free_(v.mBegin);
      v.mBegin = newbuf;
      /* v.mLength is unchanged. */
      v.mCapacity = newCap;
      return true;
    }
};

/*
 * This partial template specialization provides a default implementation for
 * vector operations when the element type is known to be a POD, as judged by
 * IsPod.
 */
template<typename T, size_t N, class AP, class ThisVector>
struct VectorImpl<T, N, AP, ThisVector, true>
{
    static inline void destroy(T*, T*) {}

    static inline void initialize(T* begin, T* end) {
      /*
       * You would think that memset would be a big win (or even break even)
       * when we know T is a POD. But currently it's not. This is probably
       * because |append| tends to be given small ranges and memset requires
       * a function call that doesn't get inlined.
       *
       * memset(begin, 0, sizeof(T) * (end-begin));
       */
      for (T* p = begin; p < end; ++p)
        new(p) T();
    }

    template<typename U>
    static inline void copyConstruct(T* dst, const U* srcbeg, const U* srcend) {
      /*
       * See above memset comment. Also, notice that copyConstruct is
       * currently templated (T != U), so memcpy won't work without
       * requiring T == U.
       *
       * memcpy(dst, srcbeg, sizeof(T) * (srcend - srcbeg));
       */
      for (const U* p = srcbeg; p < srcend; ++p, ++dst)
        *dst = *p;
    }

    template<typename U>
    static inline void moveConstruct(T* dst, const U* srcbeg, const U* srcend) {
      copyConstruct(dst, srcbeg, srcend);
    }

    static inline void copyConstructN(T* dst, size_t n, const T& t) {
      for (T* end = dst + n; dst < end; ++dst)
        *dst = t;
    }

    static inline bool
    growTo(VectorBase<T, N, AP, ThisVector>& v, size_t newCap) {
      MOZ_ASSERT(!v.usingInlineStorage());
      MOZ_ASSERT(!CapacityHasExcessSpace<T>(newCap));
      size_t oldSize = sizeof(T) * v.mCapacity;
      size_t newSize = sizeof(T) * newCap;
      T* newbuf = reinterpret_cast<T*>(v.realloc_(v.mBegin, oldSize, newSize));
      if (!newbuf)
        return false;
      v.mBegin = newbuf;
      /* v.mLength is unchanged. */
      v.mCapacity = newCap;
      return true;
    }
};

} // namespace detail

/*
 * A CRTP base class for vector-like classes.  Unless you really really want
 * your own vector class -- and you almost certainly don't -- you should use
 * mozilla::Vector instead!
 *
 * See mozilla::Vector for interface requirements.
 */
template<typename T, size_t N, class AllocPolicy, class ThisVector>
class VectorBase : private AllocPolicy
{
    /* utilities */

    static const bool sElemIsPod = IsPod<T>::value;
    typedef detail::VectorImpl<T, N, AllocPolicy, ThisVector, sElemIsPod> Impl;
    friend struct detail::VectorImpl<T, N, AllocPolicy, ThisVector, sElemIsPod>;

    bool growStorageBy(size_t incr);
    bool convertToHeapStorage(size_t newCap);

    /* magic constants */

    static const int sMaxInlineBytes = 1024;

    /* compute constants */

    /*
     * Consider element size to be 1 for buffer sizing if there are 0 inline
     * elements.  This allows us to compile when the definition of the element
     * type is not visible here.
     *
     * Explicit specialization is only allowed at namespace scope, so in order
     * to keep everything here, we use a dummy template parameter with partial
     * specialization.
     */
    template<int M, int Dummy>
    struct ElemSize
    {
        static const size_t value = sizeof(T);
    };
    template<int Dummy>
    struct ElemSize<0, Dummy>
    {
        static const size_t value = 1;
    };

    static const size_t sInlineCapacity =
      tl::Min<N, sMaxInlineBytes / ElemSize<N, 0>::value>::value;

    /* Calculate inline buffer size; avoid 0-sized array. */
    static const size_t sInlineBytes =
      tl::Max<1, sInlineCapacity * ElemSize<N, 0>::value>::value;

    /* member data */

    /*
     * Pointer to the buffer, be it inline or heap-allocated. Only [mBegin,
     * mBegin + mLength) hold valid constructed T objects. The range [mBegin +
     * mLength, mBegin + mCapacity) holds uninitialized memory. The range
     * [mBegin + mLength, mBegin + mReserved) also holds uninitialized memory
     * previously allocated by a call to reserve().
     */
    T* mBegin;

    /* Number of elements in the vector. */
    size_t mLength;

    /* Max number of elements storable in the vector without resizing. */
    size_t mCapacity;

#ifdef DEBUG
    /* Max elements of reserved or used space in this vector. */
    size_t mReserved;
#endif

    /* Memory used for inline storage. */
    AlignedStorage<sInlineBytes> storage;

#ifdef DEBUG
    friend class ReentrancyGuard;
    bool entered;
#endif

    /* private accessors */

    bool usingInlineStorage() const {
      return mBegin == const_cast<VectorBase*>(this)->inlineStorage();
    }

    T* inlineStorage() {
      return static_cast<T*>(storage.addr());
    }

    T* beginNoCheck() const {
      return mBegin;
    }

    T* endNoCheck() {
      return mBegin + mLength;
    }

    const T* endNoCheck() const {
      return mBegin + mLength;
    }

#ifdef DEBUG
    size_t reserved() const {
      MOZ_ASSERT(mReserved <= mCapacity);
      MOZ_ASSERT(mLength <= mReserved);
      return mReserved;
    }
#endif

    /* Append operations guaranteed to succeed due to pre-reserved space. */
    template<typename U> void internalAppend(const U& u);
    template<typename U, size_t O, class BP, class UV>
    void internalAppendAll(const VectorBase<U, O, BP, UV>& u);
    void internalAppendN(const T& t, size_t n);
    template<typename U> void internalAppend(const U* begin, size_t length);

  public:
    static const size_t sMaxInlineStorage = N;

    typedef T ElementType;

    VectorBase(AllocPolicy = AllocPolicy());
    VectorBase(MoveRef<ThisVector>); /* Move constructor. */
    ThisVector& operator=(MoveRef<ThisVector>); /* Move assignment. */
    ~VectorBase();

    /* accessors */

    const AllocPolicy& allocPolicy() const {
      return *this;
    }

    AllocPolicy& allocPolicy() {
      return *this;
    }

    enum { InlineLength = N };

    size_t length() const {
      return mLength;
    }

    bool empty() const {
      return mLength == 0;
    }

    size_t capacity() const {
      return mCapacity;
    }

    T* begin() {
      MOZ_ASSERT(!entered);
      return mBegin;
    }

    const T* begin() const {
      MOZ_ASSERT(!entered);
      return mBegin;
    }

    T* end() {
      MOZ_ASSERT(!entered);
      return mBegin + mLength;
    }

    const T* end() const {
      MOZ_ASSERT(!entered);
      return mBegin + mLength;
    }

    T& operator[](size_t i) {
      MOZ_ASSERT(!entered);
      MOZ_ASSERT(i < mLength);
      return begin()[i];
    }

    const T& operator[](size_t i) const {
      MOZ_ASSERT(!entered);
      MOZ_ASSERT(i < mLength);
      return begin()[i];
    }

    T& back() {
      MOZ_ASSERT(!entered);
      MOZ_ASSERT(!empty());
      return *(end() - 1);
    }

    const T& back() const {
      MOZ_ASSERT(!entered);
      MOZ_ASSERT(!empty());
      return *(end() - 1);
    }

    class Range
    {
        friend class VectorBase;
        T* cur_;
        T* end_;
        Range(T* cur, T* end) : cur_(cur), end_(end) {}

      public:
        Range() {}
        bool empty() const { return cur_ == end_; }
        size_t remain() const { return end_ - cur_; }
        T& front() const { return *cur_; }
        void popFront() { MOZ_ASSERT(!empty()); ++cur_; }
        T popCopyFront() { MOZ_ASSERT(!empty()); return *cur_++; }
    };

    Range all() {
      return Range(begin(), end());
    }

    /* mutators */

    /**
     * Given that the vector is empty and has no inline storage, grow to
     * |capacity|.
     */
    bool initCapacity(size_t request);

    /**
     * If reserve(length() + N) succeeds, the N next appends are guaranteed to
     * succeed.
     */
    bool reserve(size_t request);

    /**
     * Destroy elements in the range [end() - incr, end()). Does not deallocate
     * or unreserve storage for those elements.
     */
    void shrinkBy(size_t incr);

    /** Grow the vector by incr elements. */
    bool growBy(size_t incr);

    /** Call shrinkBy or growBy based on whether newSize > length(). */
    bool resize(size_t newLength);

    /**
     * Increase the length of the vector, but don't initialize the new elements
     * -- leave them as uninitialized memory.
     */
    bool growByUninitialized(size_t incr);
    bool resizeUninitialized(size_t newLength);

    /** Shorthand for shrinkBy(length()). */
    void clear();

    /** Clears and releases any heap-allocated storage. */
    void clearAndFree();

    /**
     * If true, appending |needed| elements won't reallocate elements storage.
     * This *doesn't* mean that infallibleAppend may be used!  You still must
     * reserve the extra space, even if this method indicates that appends won't
     * need to reallocate elements storage.
     */
    bool canAppendWithoutRealloc(size_t needed) const;

    /**
     * Potentially fallible append operations.
     *
     * The function templates that take an unspecified type U require a const T&
     * or a MoveRef<T>.  The MoveRef<T> variants move their operands into the
     * vector, instead of copying them.  If they fail, the operand is left
     * unmoved.
     */
    template<typename U> bool append(const U& u);
    template<typename U, size_t O, class BP, class UV>
    bool appendAll(const VectorBase<U, O, BP, UV>& u);
    bool appendN(const T& t, size_t n);
    template<typename U> bool append(const U* begin, const U* end);
    template<typename U> bool append(const U* begin, size_t length);

    /*
     * Guaranteed-infallible append operations for use upon vectors whose
     * memory has been pre-reserved.  Don't use this if you haven't reserved the
     * memory!
     */
    template<typename U> void infallibleAppend(const U& u) {
      internalAppend(u);
    }
    void infallibleAppendN(const T& t, size_t n) {
      internalAppendN(t, n);
    }
    template<typename U> void infallibleAppend(const U* aBegin, const U* aEnd) {
      internalAppend(aBegin, PointerRangeSize(aBegin, aEnd));
    }
    template<typename U> void infallibleAppend(const U* aBegin, size_t aLength) {
      internalAppend(aBegin, aLength);
    }

    void popBack();

    T popCopy();

    /**
     * Transfers ownership of the internal buffer used by this vector to the
     * caller.  (It's the caller's responsibility to properly deallocate this
     * buffer, in accordance with this vector's AllocPolicy.)  After this call,
     * the vector is empty.  Since the returned buffer may need to be allocated
     * (if the elements are currently stored in-place), the call can fail,
     * returning nullptr.
     *
     * N.B. Although a T*, only the range [0, length()) is constructed.
     */
    T* extractRawBuffer();

    /**
     * Transfer ownership of an array of objects into the vector.  The caller
     * must have allocated the array in accordance with this vector's
     * AllocPolicy.
     *
     * N.B. This call assumes that there are no uninitialized elements in the
     *      passed array.
     */
    void replaceRawBuffer(T* p, size_t length);

    /**
     * Places |val| at position |p|, shifting existing elements from |p| onward
     * one position higher.  On success, |p| should not be reused because it'll
     * be a dangling pointer if reallocation of the vector storage occurred; the
     * return value should be used instead.  On failure, nullptr is returned.
     *
     * Example usage:
     *
     *   if (!(p = vec.insert(p, val)))
     *     <handle failure>
     *   <keep working with p>
     *
     * This is inherently a linear-time operation.  Be careful!
     */
    T* insert(T* p, const T& val);

    /**
     * Removes the element |t|, which must fall in the bounds [begin, end),
     * shifting existing elements from |t + 1| onward one position lower.
     */
    void erase(T* t);

    /**
     * Measure the size of the vector's heap-allocated storage.
     */
    size_t sizeOfExcludingThis(MallocSizeOf mallocSizeOf) const;

    /**
     * Like sizeOfExcludingThis, but also measures the size of the vector
     * object (which must be heap-allocated) itself.
     */
    size_t sizeOfIncludingThis(MallocSizeOf mallocSizeOf) const;

    void swap(ThisVector& other);

  private:
    VectorBase(const ThisVector&) MOZ_DELETE;
    void operator=(const ThisVector&) MOZ_DELETE;
};

/* This does the re-entrancy check plus several other sanity checks. */
#define MOZ_REENTRANCY_GUARD_ET_AL \
  ReentrancyGuard g(*this); \
  MOZ_ASSERT_IF(usingInlineStorage(), mCapacity == sInlineCapacity); \
  MOZ_ASSERT(reserved() <= mCapacity); \
  MOZ_ASSERT(mLength <= reserved()); \
  MOZ_ASSERT(mLength <= mCapacity)

/* Vector Implementation */

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE
VectorBase<T, N, AP, TV>::VectorBase(AP ap)
  : AP(ap),
    mBegin(static_cast<T*>(storage.addr())),
    mLength(0),
    mCapacity(sInlineCapacity)
#ifdef DEBUG
  , mReserved(sInlineCapacity),
    entered(false)
#endif
{}

/* Move constructor. */
template<typename T, size_t N, class AllocPolicy, class TV>
MOZ_ALWAYS_INLINE
VectorBase<T, N, AllocPolicy, TV>::VectorBase(MoveRef<TV> rhs)
  : AllocPolicy(rhs)
#ifdef DEBUG
    , entered(false)
#endif
{
  mLength = rhs->mLength;
  mCapacity = rhs->mCapacity;
#ifdef DEBUG
  mReserved = rhs->mReserved;
#endif

  if (rhs->usingInlineStorage()) {
    /* We can't move the buffer over in this case, so copy elements. */
    mBegin = static_cast<T*>(storage.addr());
    Impl::moveConstruct(mBegin, rhs->beginNoCheck(), rhs->endNoCheck());
    /*
     * Leave rhs's mLength, mBegin, mCapacity, and mReserved as they are.
     * The elements in its in-line storage still need to be destroyed.
     */
  } else {
    /*
     * Take src's buffer, and turn src into an empty vector using
     * in-line storage.
     */
    mBegin = rhs->mBegin;
    rhs->mBegin = static_cast<T*>(rhs->storage.addr());
    rhs->mCapacity = sInlineCapacity;
    rhs->mLength = 0;
#ifdef DEBUG
    rhs->mReserved = sInlineCapacity;
#endif
  }
}

/* Move assignment. */
template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE
TV&
VectorBase<T, N, AP, TV>::operator=(MoveRef<TV> rhs)
{
  TV* tv = static_cast<TV*>(this);
  tv->~TV();
  new(tv) TV(rhs);
  return *tv;
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE
VectorBase<T, N, AP, TV>::~VectorBase()
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  Impl::destroy(beginNoCheck(), endNoCheck());
  if (!usingInlineStorage())
    this->free_(beginNoCheck());
}

/*
 * This function will create a new heap buffer with capacity newCap,
 * move all elements in the inline buffer to this new buffer,
 * and fail on OOM.
 */
template<typename T, size_t N, class AP, class TV>
inline bool
VectorBase<T, N, AP, TV>::convertToHeapStorage(size_t newCap)
{
  MOZ_ASSERT(usingInlineStorage());

  /* Allocate buffer. */
  MOZ_ASSERT(!detail::CapacityHasExcessSpace<T>(newCap));
  T* newBuf = reinterpret_cast<T*>(this->malloc_(newCap * sizeof(T)));
  if (!newBuf)
    return false;

  /* Copy inline elements into heap buffer. */
  Impl::moveConstruct(newBuf, beginNoCheck(), endNoCheck());
  Impl::destroy(beginNoCheck(), endNoCheck());

  /* Switch in heap buffer. */
  mBegin = newBuf;
  /* mLength is unchanged. */
  mCapacity = newCap;
  return true;
}

template<typename T, size_t N, class AP, class TV>
MOZ_NEVER_INLINE bool
VectorBase<T, N, AP, TV>::growStorageBy(size_t incr)
{
  MOZ_ASSERT(mLength + incr > mCapacity);
  MOZ_ASSERT_IF(!usingInlineStorage(),
                !detail::CapacityHasExcessSpace<T>(mCapacity));

  /*
   * When choosing a new capacity, its size should is as close to 2**N bytes
   * as possible.  2**N-sized requests are best because they are unlikely to
   * be rounded up by the allocator.  Asking for a 2**N number of elements
   * isn't as good, because if sizeof(T) is not a power-of-two that would
   * result in a non-2**N request size.
   */

  size_t newCap;

  if (incr == 1) {
    if (usingInlineStorage()) {
      /* This case occurs in ~70--80% of the calls to this function. */
      size_t newSize =
        tl::RoundUpPow2<(sInlineCapacity + 1) * sizeof(T)>::value;
      newCap = newSize / sizeof(T);
      goto convert;
    }

    if (mLength == 0) {
      /* This case occurs in ~0--10% of the calls to this function. */
      newCap = 1;
      goto grow;
    }

    /* This case occurs in ~15--20% of the calls to this function. */

    /*
     * Will mLength * 4 *sizeof(T) overflow?  This condition limits a vector
     * to 1GB of memory on a 32-bit system, which is a reasonable limit.  It
     * also ensures that
     *
     *   static_cast<char*>(end()) - static_cast<char*>(begin())
     *
     * doesn't overflow ptrdiff_t (see bug 510319).
     */
    if (mLength & tl::MulOverflowMask<4 * sizeof(T)>::value) {
      this->reportAllocOverflow();
      return false;
    }

    /*
     * If we reach here, the existing capacity will have a size that is already
     * as close to 2^N as sizeof(T) will allow.  Just double the capacity, and
     * then there might be space for one more element.
     */
    newCap = mLength * 2;
    if (detail::CapacityHasExcessSpace<T>(newCap))
      newCap += 1;
  } else {
    /* This case occurs in ~2% of the calls to this function. */
    size_t newMinCap = mLength + incr;

    /* Did mLength + incr overflow?  Will newCap * sizeof(T) overflow? */
    if (newMinCap < mLength ||
        newMinCap & tl::MulOverflowMask<2 * sizeof(T)>::value)
    {
      this->reportAllocOverflow();
      return false;
    }

    size_t newMinSize = newMinCap * sizeof(T);
    size_t newSize = RoundUpPow2(newMinSize);
    newCap = newSize / sizeof(T);
  }

  if (usingInlineStorage()) {
  convert:
    return convertToHeapStorage(newCap);
  }

grow:
  return Impl::growTo(*this, newCap);
}

template<typename T, size_t N, class AP, class TV>
inline bool
VectorBase<T, N, AP, TV>::initCapacity(size_t request)
{
  MOZ_ASSERT(empty());
  MOZ_ASSERT(usingInlineStorage());
  if (request == 0)
    return true;
  T* newbuf = reinterpret_cast<T*>(this->malloc_(request * sizeof(T)));
  if (!newbuf)
    return false;
  mBegin = newbuf;
  mCapacity = request;
#ifdef DEBUG
  mReserved = request;
#endif
  return true;
}

template<typename T, size_t N, class AP, class TV>
inline bool
VectorBase<T, N, AP, TV>::reserve(size_t request)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  if (request > mCapacity && !growStorageBy(request - mLength))
    return false;

#ifdef DEBUG
  if (request > mReserved)
    mReserved = request;
  MOZ_ASSERT(mLength <= mReserved);
  MOZ_ASSERT(mReserved <= mCapacity);
#endif
  return true;
}

template<typename T, size_t N, class AP, class TV>
inline void
VectorBase<T, N, AP, TV>::shrinkBy(size_t incr)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  MOZ_ASSERT(incr <= mLength);
  Impl::destroy(endNoCheck() - incr, endNoCheck());
  mLength -= incr;
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::growBy(size_t incr)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  if (incr > mCapacity - mLength && !growStorageBy(incr))
    return false;

  MOZ_ASSERT(mLength + incr <= mCapacity);
  T* newend = endNoCheck() + incr;
  Impl::initialize(endNoCheck(), newend);
  mLength += incr;
#ifdef DEBUG
  if (mLength > mReserved)
    mReserved = mLength;
#endif
  return true;
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::growByUninitialized(size_t incr)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  if (incr > mCapacity - mLength && !growStorageBy(incr))
    return false;

  MOZ_ASSERT(mLength + incr <= mCapacity);
  mLength += incr;
#ifdef DEBUG
  if (mLength > mReserved)
    mReserved = mLength;
#endif
  return true;
}

template<typename T, size_t N, class AP, class TV>
inline bool
VectorBase<T, N, AP, TV>::resize(size_t newLength)
{
  size_t curLength = mLength;
  if (newLength > curLength)
    return growBy(newLength - curLength);
  shrinkBy(curLength - newLength);
  return true;
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::resizeUninitialized(size_t newLength)
{
  size_t curLength = mLength;
  if (newLength > curLength)
    return growByUninitialized(newLength - curLength);
  shrinkBy(curLength - newLength);
  return true;
}

template<typename T, size_t N, class AP, class TV>
inline void
VectorBase<T, N, AP, TV>::clear()
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  Impl::destroy(beginNoCheck(), endNoCheck());
  mLength = 0;
}

template<typename T, size_t N, class AP, class TV>
inline void
VectorBase<T, N, AP, TV>::clearAndFree()
{
  clear();

  if (usingInlineStorage())
    return;

  this->free_(beginNoCheck());
  mBegin = static_cast<T*>(storage.addr());
  mCapacity = sInlineCapacity;
#ifdef DEBUG
  mReserved = sInlineCapacity;
#endif
}

template<typename T, size_t N, class AP, class TV>
inline bool
VectorBase<T, N, AP, TV>::canAppendWithoutRealloc(size_t needed) const
{
  return mLength + needed <= mCapacity;
}

template<typename T, size_t N, class AP, class TV>
template<typename U, size_t O, class BP, class UV>
MOZ_ALWAYS_INLINE void
VectorBase<T, N, AP, TV>::internalAppendAll(const VectorBase<U, O, BP, UV>& other)
{
  internalAppend(other.begin(), other.length());
}

template<typename T, size_t N, class AP, class TV>
template<typename U>
MOZ_ALWAYS_INLINE void
VectorBase<T, N, AP, TV>::internalAppend(const U& u)
{
  MOZ_ASSERT(mLength + 1 <= mReserved);
  MOZ_ASSERT(mReserved <= mCapacity);
  new(endNoCheck()) T(u);
  ++mLength;
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::appendN(const T& t, size_t needed)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  if (mLength + needed > mCapacity && !growStorageBy(needed))
    return false;

#ifdef DEBUG
  if (mLength + needed > mReserved)
    mReserved = mLength + needed;
#endif
  internalAppendN(t, needed);
  return true;
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE void
VectorBase<T, N, AP, TV>::internalAppendN(const T& t, size_t needed)
{
  MOZ_ASSERT(mLength + needed <= mReserved);
  MOZ_ASSERT(mReserved <= mCapacity);
  Impl::copyConstructN(endNoCheck(), needed, t);
  mLength += needed;
}

template<typename T, size_t N, class AP, class TV>
inline T*
VectorBase<T, N, AP, TV>::insert(T* p, const T& val)
{
  MOZ_ASSERT(begin() <= p);
  MOZ_ASSERT(p <= end());
  size_t pos = p - begin();
  MOZ_ASSERT(pos <= mLength);
  size_t oldLength = mLength;
  if (pos == oldLength) {
    if (!append(val))
      return nullptr;
  } else {
    T oldBack = back();
    if (!append(oldBack)) /* Dup the last element. */
      return nullptr;
    for (size_t i = oldLength; i > pos; --i)
      (*this)[i] = (*this)[i - 1];
    (*this)[pos] = val;
  }
  return begin() + pos;
}

template<typename T, size_t N, class AP, class TV>
inline void
VectorBase<T, N, AP, TV>::erase(T* it)
{
  MOZ_ASSERT(begin() <= it);
  MOZ_ASSERT(it < end());
  while (it + 1 < end()) {
    *it = *(it + 1);
    ++it;
  }
  popBack();
}

template<typename T, size_t N, class AP, class TV>
template<typename U>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::append(const U* insBegin, const U* insEnd)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  size_t needed = PointerRangeSize(insBegin, insEnd);
  if (mLength + needed > mCapacity && !growStorageBy(needed))
    return false;

#ifdef DEBUG
  if (mLength + needed > mReserved)
    mReserved = mLength + needed;
#endif
  internalAppend(insBegin, needed);
  return true;
}

template<typename T, size_t N, class AP, class TV>
template<typename U>
MOZ_ALWAYS_INLINE void
VectorBase<T, N, AP, TV>::internalAppend(const U* insBegin, size_t insLength)
{
  MOZ_ASSERT(mLength + insLength <= mReserved);
  MOZ_ASSERT(mReserved <= mCapacity);
  Impl::copyConstruct(endNoCheck(), insBegin, insBegin + insLength);
  mLength += insLength;
}

template<typename T, size_t N, class AP, class TV>
template<typename U>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::append(const U& u)
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  if (mLength == mCapacity && !growStorageBy(1))
    return false;

#ifdef DEBUG
  if (mLength + 1 > mReserved)
    mReserved = mLength + 1;
#endif
  internalAppend(u);
  return true;
}

template<typename T, size_t N, class AP, class TV>
template<typename U, size_t O, class BP, class UV>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::appendAll(const VectorBase<U, O, BP, UV>& other)
{
  return append(other.begin(), other.length());
}

template<typename T, size_t N, class AP, class TV>
template<class U>
MOZ_ALWAYS_INLINE bool
VectorBase<T, N, AP, TV>::append(const U *insBegin, size_t insLength)
{
  return append(insBegin, insBegin + insLength);
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE void
VectorBase<T, N, AP, TV>::popBack()
{
  MOZ_REENTRANCY_GUARD_ET_AL;
  MOZ_ASSERT(!empty());
  --mLength;
  endNoCheck()->~T();
}

template<typename T, size_t N, class AP, class TV>
MOZ_ALWAYS_INLINE T
VectorBase<T, N, AP, TV>::popCopy()
{
  T ret = back();
  popBack();
  return ret;
}

template<typename T, size_t N, class AP, class TV>
inline T*
VectorBase<T, N, AP, TV>::extractRawBuffer()
{
  T* ret;
  if (usingInlineStorage()) {
    ret = reinterpret_cast<T*>(this->malloc_(mLength * sizeof(T)));
    if (!ret)
      return nullptr;
    Impl::copyConstruct(ret, beginNoCheck(), endNoCheck());
    Impl::destroy(beginNoCheck(), endNoCheck());
    /* mBegin, mCapacity are unchanged. */
    mLength = 0;
  } else {
    ret = mBegin;
    mBegin = static_cast<T*>(storage.addr());
    mLength = 0;
    mCapacity = sInlineCapacity;
#ifdef DEBUG
    mReserved = sInlineCapacity;
#endif
  }
  return ret;
}

template<typename T, size_t N, class AP, class TV>
inline void
VectorBase<T, N, AP, TV>::replaceRawBuffer(T* p, size_t aLength)
{
  MOZ_REENTRANCY_GUARD_ET_AL;

  /* Destroy what we have. */
  Impl::destroy(beginNoCheck(), endNoCheck());
  if (!usingInlineStorage())
    this->free_(beginNoCheck());

  /* Take in the new buffer. */
  if (aLength <= sInlineCapacity) {
    /*
     * We convert to inline storage if possible, even though p might
     * otherwise be acceptable.  Maybe this behaviour should be
     * specifiable with an argument to this function.
     */
    mBegin = static_cast<T*>(storage.addr());
    mLength = aLength;
    mCapacity = sInlineCapacity;
    Impl::moveConstruct(mBegin, p, p + aLength);
    Impl::destroy(p, p + aLength);
    this->free_(p);
  } else {
    mBegin = p;
    mLength = aLength;
    mCapacity = aLength;
  }
#ifdef DEBUG
  mReserved = aLength;
#endif
}

template<typename T, size_t N, class AP, class TV>
inline size_t
VectorBase<T, N, AP, TV>::sizeOfExcludingThis(MallocSizeOf mallocSizeOf) const
{
  return usingInlineStorage() ? 0 : mallocSizeOf(beginNoCheck());
}

template<typename T, size_t N, class AP, class TV>
inline size_t
VectorBase<T, N, AP, TV>::sizeOfIncludingThis(MallocSizeOf mallocSizeOf) const
{
  return mallocSizeOf(this) + sizeOfExcludingThis(mallocSizeOf);
}

template<typename T, size_t N, class AP, class TV>
inline void
VectorBase<T, N, AP, TV>::swap(TV& other)
{
  static_assert(N == 0,
                "still need to implement this for N != 0");

  // This only works when inline storage is always empty.
  if (!usingInlineStorage() && other.usingInlineStorage()) {
    other.mBegin = mBegin;
    mBegin = inlineStorage();
  } else if (usingInlineStorage() && !other.usingInlineStorage()) {
    mBegin = other.mBegin;
    other.mBegin = other.inlineStorage();
  } else if (!usingInlineStorage() && !other.usingInlineStorage()) {
    Swap(mBegin, other.mBegin);
  } else {
    // This case is a no-op, since we'd set both to use their inline storage.
  }

  Swap(mLength, other.mLength);
  Swap(mCapacity, other.mCapacity);
#ifdef DEBUG
  Swap(mReserved, other.mReserved);
#endif
}

/*
 * STL-like container providing a short-lived, dynamic buffer.  Vector calls the
 * constructors/destructors of all elements stored in its internal buffer, so
 * non-PODs may be safely used.  Additionally, Vector will store the first N
 * elements in-place before resorting to dynamic allocation.
 *
 * T requirements:
 *  - default and copy constructible, assignable, destructible
 *  - operations do not throw
 * N requirements:
 *  - any value, however, N is clamped to min/max values
 * AllocPolicy:
 *  - see "Allocation policies" in AllocPolicy.h (defaults to
 *    mozilla::MallocAllocPolicy)
 *
 * Vector is not reentrant: T member functions called during Vector member
 * functions must not call back into the same object!
 */
template<typename T,
         size_t MinInlineCapacity = 0,
         class AllocPolicy = MallocAllocPolicy>
class Vector
  : public VectorBase<T,
                      MinInlineCapacity,
                      AllocPolicy,
                      Vector<T, MinInlineCapacity, AllocPolicy> >
{
    typedef VectorBase<T, MinInlineCapacity, AllocPolicy, Vector> Base;

  public:
    Vector(AllocPolicy alloc = AllocPolicy()) : Base(alloc) {}
    Vector(mozilla::MoveRef<Vector> vec) : Base(vec) {}
    Vector& operator=(mozilla::MoveRef<Vector> vec) {
      return Base::operator=(vec);
    }
};

} // namespace mozilla

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* mozilla_Vector_h */
