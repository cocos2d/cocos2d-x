/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla SpiderMonkey JavaScript 1.9 code, released
 * June 12, 2009.
 *
 * The Initial Developer of the Original Code is
 *   the Mozilla Corporation.
 *
 * Contributor(s):
 *   Luke Wagner <lw@mozilla.com>
 *   Nicholas Nethercote <nnethercote@mozilla.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef jsvector_h_
#define jsvector_h_

#include "mozilla/Attributes.h"

#include "TemplateLib.h"
#include "Utility.h"

/* Silence dire "bugs in previous versions of MSVC have been fixed" warnings */
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4345)
#endif

namespace js {

class TempAllocPolicy;

template <class T,
          size_t MinInlineCapacity = 0,
          class AllocPolicy = TempAllocPolicy>
class Vector;

/*
 * This template class provides a default implementation for vector operations
 * when the element type is not known to be a POD, as judged by IsPodType.
 */
template <class T, size_t N, class AP, bool IsPod>
struct VectorImpl
{
    /* Destroys constructed objects in the range [begin, end). */
    static inline void destroy(T *begin, T *end) {
        for (T *p = begin; p != end; ++p)
            p->~T();
    }

    /* Constructs objects in the uninitialized range [begin, end). */
    static inline void initialize(T *begin, T *end) {
        for (T *p = begin; p != end; ++p)
            new(p) T();
    }

    /*
     * Copy-constructs objects in the uninitialized range
     * [dst, dst+(srcend-srcbeg)) from the range [srcbeg, srcend).
     */
    template <class U>
    static inline void copyConstruct(T *dst, const U *srcbeg, const U *srcend) {
        for (const U *p = srcbeg; p != srcend; ++p, ++dst)
            new(dst) T(*p);
    }

    /*
     * Move-constructs objects in the uninitialized range
     * [dst, dst+(srcend-srcbeg)) from the range [srcbeg, srcend).
     */
    template <class U>
    static inline void moveConstruct(T *dst, const U *srcbeg, const U *srcend) {
        for (const U *p = srcbeg; p != srcend; ++p, ++dst)
            new(dst) T(Move(*p));
    }

    /*
     * Copy-constructs objects in the uninitialized range [dst, dst+n) from the
     * same object u.
     */
    template <class U>
    static inline void copyConstructN(T *dst, size_t n, const U &u) {
        for (T *end = dst + n; dst != end; ++dst)
            new(dst) T(u);
    }

    /*
     * Grows the given buffer to have capacity newcap, preserving the objects
     * constructed in the range [begin, end) and updating v. Assumes that (1)
     * newcap has not overflowed, and (2) multiplying newcap by sizeof(T) will
     * not overflow.
     */
    static inline bool growTo(Vector<T,N,AP> &v, size_t newcap) {
        JS_ASSERT(!v.usingInlineStorage());
        T *newbuf = reinterpret_cast<T *>(v.malloc_(newcap * sizeof(T)));
        if (!newbuf)
            return false;
        for (T *dst = newbuf, *src = v.beginNoCheck(); src != v.endNoCheck(); ++dst, ++src)
            new(dst) T(Move(*src));
        VectorImpl::destroy(v.beginNoCheck(), v.endNoCheck());
        v.free_(v.mBegin);
        v.mBegin = newbuf;
        /* v.mLength is unchanged. */
        v.mCapacity = newcap;
        return true;
    }
};

/*
 * This partial template specialization provides a default implementation for
 * vector operations when the element type is known to be a POD, as judged by
 * IsPodType.
 */
template <class T, size_t N, class AP>
struct VectorImpl<T, N, AP, true>
{
    static inline void destroy(T *, T *) {}

    static inline void initialize(T *begin, T *end) {
        /*
         * You would think that memset would be a big win (or even break even)
         * when we know T is a POD. But currently it's not. This is probably
         * because |append| tends to be given small ranges and memset requires
         * a function call that doesn't get inlined.
         *
         * memset(begin, 0, sizeof(T) * (end-begin));
         */
        for (T *p = begin; p != end; ++p)
            new(p) T();
    }

    template <class U>
    static inline void copyConstruct(T *dst, const U *srcbeg, const U *srcend) {
        /*
         * See above memset comment. Also, notice that copyConstruct is
         * currently templated (T != U), so memcpy won't work without
         * requiring T == U.
         *
         * memcpy(dst, srcbeg, sizeof(T) * (srcend - srcbeg));
         */
        for (const U *p = srcbeg; p != srcend; ++p, ++dst)
            *dst = *p;
    }

    template <class U>
    static inline void moveConstruct(T *dst, const U *srcbeg, const U *srcend) {
        copyConstruct(dst, srcbeg, srcend);
    }

    static inline void copyConstructN(T *dst, size_t n, const T &t) {
        for (T *p = dst, *end = dst + n; p != end; ++p)
            *p = t;
    }

    static inline bool growTo(Vector<T,N,AP> &v, size_t newcap) {
        JS_ASSERT(!v.usingInlineStorage());
        size_t bytes = sizeof(T) * newcap;
        size_t oldBytes = sizeof(T) * v.mCapacity;
        T *newbuf = reinterpret_cast<T *>(v.realloc_(v.mBegin, oldBytes, bytes));
        if (!newbuf)
            return false;
        v.mBegin = newbuf;
        /* v.mLength is unchanged. */
        v.mCapacity = newcap;
        return true;
    }
};

/*
 * JS-friendly, STL-like container providing a short-lived, dynamic buffer.
 * Vector calls the constructors/destructors of all elements stored in
 * its internal buffer, so non-PODs may be safely used. Additionally,
 * Vector will store the first N elements in-place before resorting to
 * dynamic allocation.
 *
 * T requirements:
 *  - default and copy constructible, assignable, destructible
 *  - operations do not throw
 * N requirements:
 *  - any value, however, N is clamped to min/max values
 * AllocPolicy:
 *  - see "Allocation policies" in jsalloc.h (default js::TempAllocPolicy)
 *
 * N.B: Vector is not reentrant: T member functions called during Vector member
 *      functions must not call back into the same object.
 */
template <class T, size_t N, class AllocPolicy>
class Vector : private AllocPolicy
{
    /* utilities */

    static const bool sElemIsPod = tl::IsPodType<T>::result;
    typedef VectorImpl<T, N, AllocPolicy, sElemIsPod> Impl;
    friend struct VectorImpl<T, N, AllocPolicy, sElemIsPod>;

    bool calculateNewCapacity(size_t curLength, size_t lengthInc, size_t &newCap);
    bool growStorageBy(size_t lengthInc);
    bool growHeapStorageBy(size_t lengthInc);
    bool convertToHeapStorage(size_t lengthInc);

    template <bool InitNewElems> inline bool growByImpl(size_t inc);

    /* magic constants */

    static const int sMaxInlineBytes = 1024;

    /* compute constants */

    /*
     * Consider element size to be 1 for buffer sizing if there are
     * 0 inline elements. This allows us to compile when the definition
     * of the element type is not visible here.
     *
     * Explicit specialization is only allowed at namespace scope, so
     * in order to keep everything here, we use a dummy template
     * parameter with partial specialization.
     */
    template <int M, int Dummy>
    struct ElemSize {
        static const size_t result = sizeof(T);
    };
    template <int Dummy>
    struct ElemSize<0, Dummy> {
        static const size_t result = 1;
    };

    static const size_t sInlineCapacity =
        tl::Min<N, sMaxInlineBytes / ElemSize<N, 0>::result>::result;

    /* Calculate inline buffer size; avoid 0-sized array. */
    static const size_t sInlineBytes =
        tl::Max<1, sInlineCapacity * ElemSize<N, 0>::result>::result;

    /* member data */

    /*
     * Pointer to the buffer, be it inline or heap-allocated. Only [mBegin,
     * mBegin + mLength) hold valid constructed T objects. The range [mBegin +
     * mLength, mBegin + mCapacity) holds uninitialized memory. The range
     * [mBegin + mLength, mBegin + mReserved) also holds uninitialized memory
     * previously allocated by a call to reserve().
     */
    T *mBegin;
    size_t mLength;     /* Number of elements in the Vector. */
    size_t mCapacity;   /* Max number of elements storable in the Vector without resizing. */
#ifdef DEBUG
    size_t mReserved;   /* Max elements of reserved or used space in this vector. */
#endif

    AlignedStorage<sInlineBytes> storage;

#ifdef DEBUG
    friend class ReentrancyGuard;
    bool entered;
#endif

    Vector(const Vector &) MOZ_DELETE;
    Vector &operator=(const Vector &) MOZ_DELETE;

    /* private accessors */

    bool usingInlineStorage() const {
        return mBegin == (T *)storage.addr();
    }

    T *beginNoCheck() const {
        return mBegin;
    }

    T *endNoCheck() {
        return mBegin + mLength;
    }

    const T *endNoCheck() const {
        return mBegin + mLength;
    }

#ifdef DEBUG
    size_t reserved() const {
        JS_ASSERT(mReserved <= mCapacity);
        JS_ASSERT(mLength <= mReserved);
        return mReserved;
    }
#endif

    /* Append operations guaranteed to succeed due to pre-reserved space. */
    template <class U> void internalAppend(U t);
    void internalAppendN(const T &t, size_t n);
    template <class U> void internalAppend(const U *begin, size_t length);
    template <class U, size_t O, class BP> void internalAppend(const Vector<U,O,BP> &other);

  public:
    static const size_t sMaxInlineStorage = N;

    typedef T ElementType;

    Vector(AllocPolicy = AllocPolicy());
    Vector(MoveRef<Vector>); /* Move constructor. */
    Vector &operator=(MoveRef<Vector>); /* Move assignment. */
    ~Vector();

    /* accessors */

    const AllocPolicy &allocPolicy() const {
        return *this;
    }

    AllocPolicy &allocPolicy() {
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

    T *begin() {
        JS_ASSERT(!entered);
        return mBegin;
    }

    const T *begin() const {
        JS_ASSERT(!entered);
        return mBegin;
    }

    T *end() {
        JS_ASSERT(!entered);
        return mBegin + mLength;
    }

    const T *end() const {
        JS_ASSERT(!entered);
        return mBegin + mLength;
    }

    T &operator[](size_t i) {
        JS_ASSERT(!entered && i < mLength);
        return begin()[i];
    }

    const T &operator[](size_t i) const {
        JS_ASSERT(!entered && i < mLength);
        return begin()[i];
    }

    T &back() {
        JS_ASSERT(!entered && !empty());
        return *(end() - 1);
    }

    const T &back() const {
        JS_ASSERT(!entered && !empty());
        return *(end() - 1);
    }

    class Range {
        friend class Vector;
        T *cur, *end;
        Range(T *cur, T *end) : cur(cur), end(end) {}
      public:
        Range() {}
        bool empty() const { return cur == end; }
        size_t remain() const { return end - cur; }
        T &front() const { return *cur; }
        void popFront() { JS_ASSERT(!empty()); ++cur; }
        T popCopyFront() { JS_ASSERT(!empty()); return *cur++; }
    };

    Range all() {
        return Range(begin(), end());
    }

    /* mutators */

    /* If reserve(length() + N) succeeds, the N next appends are guaranteed to succeed. */
    bool reserve(size_t capacity);

    /*
     * Destroy elements in the range [end() - incr, end()). Does not deallocate
     * or unreserve storage for those elements.
     */
    void shrinkBy(size_t incr);

    /* Grow the vector by incr elements. */
    bool growBy(size_t incr);

    /* Call shrinkBy or growBy based on whether newSize > length(). */
    bool resize(size_t newLength);

    /* Leave new elements as uninitialized memory. */
    bool growByUninitialized(size_t incr);
    bool resizeUninitialized(size_t newLength);

    /* Shorthand for shrinkBy(length()). */
    void clear();

    /* Clears and releases any heap-allocated storage. */
    void clearAndFree();

    /*
     * Potentially fallible append operations.
     *
     * The function templates that take an unspecified type U require a
     * const T & or a MoveRef<T>. The MoveRef<T> variants move their
     * operands into the vector, instead of copying them. If they fail, the
     * operand is left unmoved.
     */
    template <class U> bool append(U t);
    bool appendN(const T &t, size_t n);
    template <class U> bool append(const U *begin, const U *end);
    template <class U> bool append(const U *begin, size_t length);
    template <class U, size_t O, class BP> bool append(const Vector<U,O,BP> &other);

    /*
     * Guaranteed-infallible append operations for use upon vectors whose
     * memory has been pre-reserved.
     */
    void infallibleAppend(const T &t) {
        internalAppend(t);
    }
    void infallibleAppendN(const T &t, size_t n) {
        internalAppendN(t, n);
    }
    template <class U> void infallibleAppend(const U *begin, const U *end) {
        internalAppend(begin, PointerRangeSize(begin, end));
    }
    template <class U> void infallibleAppend(const U *begin, size_t length) {
        internalAppend(begin, length);
    }
    template <class U, size_t O, class BP> void infallibleAppend(const Vector<U,O,BP> &other) {
        internalAppend(other);
    }

    void popBack();

    T popCopy();

    /*
     * Transfers ownership of the internal buffer used by Vector to the caller.
     * After this call, the Vector is empty. Since the returned buffer may need
     * to be allocated (if the elements are currently stored in-place), the
     * call can fail, returning NULL.
     *
     * N.B. Although a T*, only the range [0, length()) is constructed.
     */
    T *extractRawBuffer();

    /*
     * Transfer ownership of an array of objects into the Vector.
     * N.B. This call assumes that there are no uninitialized elements in the
     *      passed array.
     */
    void replaceRawBuffer(T *p, size_t length);

    /*
     * Places |val| at position |p|, shifting existing elements
     * from |p| onward one position higher.
     */
    bool insert(T *p, const T &val);

    /*
     * Removes the element |t|, which must fall in the bounds [begin, end),
     * shifting existing elements from |t + 1| onward one position lower.
     */
    void erase(T *t);

    /*
     * Measure the size of the Vector's heap-allocated storage.
     */
    size_t sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const;

    /* 
     * Like sizeOfExcludingThis, but also measures the size of the Vector
     * object (which must be heap-allocated) itself.
     */
    size_t sizeOfIncludingThis(JSMallocSizeOfFun mallocSizeOf) const;
};

/* This does the re-entrancy check plus several other sanity checks. */
#define REENTRANCY_GUARD_ET_AL \
    ReentrancyGuard g(*this); \
    JS_ASSERT_IF(usingInlineStorage(), mCapacity == sInlineCapacity); \
    JS_ASSERT(reserved() <= mCapacity); \
    JS_ASSERT(mLength <= reserved()); \
    JS_ASSERT(mLength <= mCapacity)

/* Vector Implementation */

template <class T, size_t N, class AllocPolicy>
JS_ALWAYS_INLINE
Vector<T,N,AllocPolicy>::Vector(AllocPolicy ap)
  : AllocPolicy(ap), mBegin((T *)storage.addr()), mLength(0),
    mCapacity(sInlineCapacity)
#ifdef DEBUG
  , mReserved(0), entered(false)
#endif
{}

/* Move constructor. */
template <class T, size_t N, class AllocPolicy>
JS_ALWAYS_INLINE
Vector<T, N, AllocPolicy>::Vector(MoveRef<Vector> rhs)
    : AllocPolicy(rhs)
{
    mLength = rhs->mLength;
    mCapacity = rhs->mCapacity;
#ifdef DEBUG
    mReserved = rhs->mReserved;
#endif

    if (rhs->usingInlineStorage()) {
        /* We can't move the buffer over in this case, so copy elements. */
        mBegin = (T *)storage.addr();
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
        rhs->mBegin = (T *) rhs->storage.addr();
        rhs->mCapacity = sInlineCapacity;
        rhs->mLength = 0;
#ifdef DEBUG
        rhs->mReserved = 0;
#endif
    }
}

/* Move assignment. */
template <class T, size_t N, class AP>
JS_ALWAYS_INLINE
Vector<T, N, AP> &
Vector<T, N, AP>::operator=(MoveRef<Vector> rhs)
{
    this->~Vector();
    new(this) Vector(rhs);
    return *this;
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE
Vector<T,N,AP>::~Vector()
{
    REENTRANCY_GUARD_ET_AL;
    Impl::destroy(beginNoCheck(), endNoCheck());
    if (!usingInlineStorage())
        this->free_(beginNoCheck());
}

/*
 * Calculate a new capacity that is at least lengthInc greater than
 * curLength and check for overflow.
 */
template <class T, size_t N, class AP>
STATIC_POSTCONDITION(!return || newCap >= curLength + lengthInc)
inline bool
Vector<T,N,AP>::calculateNewCapacity(size_t curLength, size_t lengthInc,
                                     size_t &newCap)
{
    size_t newMinCap = curLength + lengthInc;

    /*
     * Check for overflow in the above addition, below CEILING_LOG2, and later
     * multiplication by sizeof(T).
     */
    if (newMinCap < curLength ||
        newMinCap & tl::MulOverflowMask<2 * sizeof(T)>::result) {
        this->reportAllocOverflow();
        return false;
    }

    /* Round up to next power of 2. */
    newCap = RoundUpPow2(newMinCap);

    /*
     * Do not allow a buffer large enough that the expression ((char *)end() -
     * (char *)begin()) overflows ptrdiff_t. See Bug 510319.
     */
    if (newCap & tl::UnsafeRangeSizeMask<T>::result) {
        this->reportAllocOverflow();
        return false;
    }
    return true;
}

/*
 * This function will grow the current heap capacity to have capacity
 * (mLength + lengthInc) and fail on OOM or integer overflow.
 */
template <class T, size_t N, class AP>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::growHeapStorageBy(size_t lengthInc)
{
    JS_ASSERT(!usingInlineStorage());
    size_t newCap;
    return calculateNewCapacity(mLength, lengthInc, newCap) &&
           Impl::growTo(*this, newCap);
}

/*
 * This function will create a new heap buffer with capacity (mLength +
 * lengthInc()), move all elements in the inline buffer to this new buffer,
 * and fail on OOM or integer overflow.
 */
template <class T, size_t N, class AP>
inline bool
Vector<T,N,AP>::convertToHeapStorage(size_t lengthInc)
{
    JS_ASSERT(usingInlineStorage());
    size_t newCap;
    if (!calculateNewCapacity(mLength, lengthInc, newCap))
        return false;

    /* Allocate buffer. */
    T *newBuf = reinterpret_cast<T *>(this->malloc_(newCap * sizeof(T)));
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

template <class T, size_t N, class AP>
JS_NEVER_INLINE bool
Vector<T,N,AP>::growStorageBy(size_t incr)
{
    JS_ASSERT(mLength + incr > mCapacity);
    return usingInlineStorage()
         ? convertToHeapStorage(incr)
         : growHeapStorageBy(incr);
}

template <class T, size_t N, class AP>
inline bool
Vector<T,N,AP>::reserve(size_t request)
{
    REENTRANCY_GUARD_ET_AL;
    if (request > mCapacity && !growStorageBy(request - mLength))
        return false;

#ifdef DEBUG
    if (request > mReserved)
        mReserved = request;
    JS_ASSERT(mLength <= mReserved);
    JS_ASSERT(mReserved <= mCapacity);
#endif
    return true;
}

template <class T, size_t N, class AP>
inline void
Vector<T,N,AP>::shrinkBy(size_t incr)
{
    REENTRANCY_GUARD_ET_AL;
    JS_ASSERT(incr <= mLength);
    Impl::destroy(endNoCheck() - incr, endNoCheck());
    mLength -= incr;
}

template <class T, size_t N, class AP>
template <bool InitNewElems>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::growByImpl(size_t incr)
{
    REENTRANCY_GUARD_ET_AL;
    if (incr > mCapacity - mLength && !growStorageBy(incr))
        return false;

    JS_ASSERT(mLength + incr <= mCapacity);
    T *newend = endNoCheck() + incr;
    if (InitNewElems)
        Impl::initialize(endNoCheck(), newend);
    mLength += incr;
#ifdef DEBUG
    if (mLength > mReserved)
        mReserved = mLength;
#endif
    return true;
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::growBy(size_t incr)
{
    return growByImpl<true>(incr);
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::growByUninitialized(size_t incr)
{
    return growByImpl<false>(incr);
}

template <class T, size_t N, class AP>
STATIC_POSTCONDITION(!return || ubound(this->begin()) >= newLength)
inline bool
Vector<T,N,AP>::resize(size_t newLength)
{
    size_t curLength = mLength;
    if (newLength > curLength)
        return growBy(newLength - curLength);
    shrinkBy(curLength - newLength);
    return true;
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::resizeUninitialized(size_t newLength)
{
    size_t curLength = mLength;
    if (newLength > curLength)
        return growByUninitialized(newLength - curLength);
    shrinkBy(curLength - newLength);
    return true;
}

template <class T, size_t N, class AP>
inline void
Vector<T,N,AP>::clear()
{
    REENTRANCY_GUARD_ET_AL;
    Impl::destroy(beginNoCheck(), endNoCheck());
    mLength = 0;
}

template <class T, size_t N, class AP>
inline void
Vector<T,N,AP>::clearAndFree()
{
    clear();

    if (usingInlineStorage())
        return;

    this->free_(beginNoCheck());
    mBegin = (T *)storage.addr();
    mCapacity = sInlineCapacity;
#ifdef DEBUG
    mReserved = 0;
#endif
}

template <class T, size_t N, class AP>
template <class U>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::append(U t)
{
    REENTRANCY_GUARD_ET_AL;
    if (mLength == mCapacity && !growStorageBy(1))
        return false;

#ifdef DEBUG
    if (mLength + 1 > mReserved)
        mReserved = mLength + 1;
#endif
    internalAppend(t);
    return true;
}

template <class T, size_t N, class AP>
template <class U>
JS_ALWAYS_INLINE void
Vector<T,N,AP>::internalAppend(U t)
{
    JS_ASSERT(mLength + 1 <= mReserved);
    JS_ASSERT(mReserved <= mCapacity);
    new(endNoCheck()) T(t);
    ++mLength;
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::appendN(const T &t, size_t needed)
{
    REENTRANCY_GUARD_ET_AL;
    if (mLength + needed > mCapacity && !growStorageBy(needed))
        return false;

#ifdef DEBUG
    if (mLength + needed > mReserved)
        mReserved = mLength + needed;
#endif
    internalAppendN(t, needed);
    return true;
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE void
Vector<T,N,AP>::internalAppendN(const T &t, size_t needed)
{
    JS_ASSERT(mLength + needed <= mReserved);
    JS_ASSERT(mReserved <= mCapacity);
    Impl::copyConstructN(endNoCheck(), needed, t);
    mLength += needed;
}

template <class T, size_t N, class AP>
inline bool
Vector<T,N,AP>::insert(T *p, const T &val)
{
    JS_ASSERT(begin() <= p && p <= end());
    size_t pos = p - begin();
    JS_ASSERT(pos <= mLength);
    size_t oldLength = mLength;
    if (pos == oldLength)
        return append(val);
    {
        T oldBack = back();
        if (!append(oldBack)) /* Dup the last element. */
            return false;
    }
    for (size_t i = oldLength; i > pos; --i)
        (*this)[i] = (*this)[i - 1];
    (*this)[pos] = val;
    return true;
}

template<typename T, size_t N, class AP>
inline void
Vector<T,N,AP>::erase(T *it)
{
    JS_ASSERT(begin() <= it && it < end());
    while (it + 1 != end()) {
        *it = *(it + 1);
        ++it;
    }
    popBack();
}

template <class T, size_t N, class AP>
template <class U>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::append(const U *insBegin, const U *insEnd)
{
    REENTRANCY_GUARD_ET_AL;
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

template <class T, size_t N, class AP>
template <class U>
JS_ALWAYS_INLINE void
Vector<T,N,AP>::internalAppend(const U *insBegin, size_t length)
{
    JS_ASSERT(mLength + length <= mReserved);
    JS_ASSERT(mReserved <= mCapacity);
    Impl::copyConstruct(endNoCheck(), insBegin, insBegin + length);
    mLength += length;
}

template <class T, size_t N, class AP>
template <class U, size_t O, class BP>
inline bool
Vector<T,N,AP>::append(const Vector<U,O,BP> &other)
{
    return append(other.begin(), other.end());
}

template <class T, size_t N, class AP>
template <class U, size_t O, class BP>
inline void
Vector<T,N,AP>::internalAppend(const Vector<U,O,BP> &other)
{
    internalAppend(other.begin(), other.length());
}

template <class T, size_t N, class AP>
template <class U>
JS_ALWAYS_INLINE bool
Vector<T,N,AP>::append(const U *insBegin, size_t length)
{
    return this->append(insBegin, insBegin + length);
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE void
Vector<T,N,AP>::popBack()
{
    REENTRANCY_GUARD_ET_AL;
    JS_ASSERT(!empty());
    --mLength;
    endNoCheck()->~T();
}

template <class T, size_t N, class AP>
JS_ALWAYS_INLINE T
Vector<T,N,AP>::popCopy()
{
    T ret = back();
    popBack();
    return ret;
}

template <class T, size_t N, class AP>
inline T *
Vector<T,N,AP>::extractRawBuffer()
{
    T *ret;
    if (usingInlineStorage()) {
        ret = reinterpret_cast<T *>(this->malloc_(mLength * sizeof(T)));
        if (!ret)
            return NULL;
        Impl::copyConstruct(ret, beginNoCheck(), endNoCheck());
        Impl::destroy(beginNoCheck(), endNoCheck());
        /* mBegin, mCapacity are unchanged. */
        mLength = 0;
    } else {
        ret = mBegin;
        mBegin = (T *)storage.addr();
        mLength = 0;
        mCapacity = sInlineCapacity;
#ifdef DEBUG
        mReserved = 0;
#endif
    }
    return ret;
}

template <class T, size_t N, class AP>
inline void
Vector<T,N,AP>::replaceRawBuffer(T *p, size_t length)
{
    REENTRANCY_GUARD_ET_AL;

    /* Destroy what we have. */
    Impl::destroy(beginNoCheck(), endNoCheck());
    if (!usingInlineStorage())
        this->free_(beginNoCheck());

    /* Take in the new buffer. */
    if (length <= sInlineCapacity) {
        /*
         * We convert to inline storage if possible, even though p might
         * otherwise be acceptable.  Maybe this behaviour should be
         * specifiable with an argument to this function.
         */
        mBegin = (T *)storage.addr();
        mLength = length;
        mCapacity = sInlineCapacity;
        Impl::moveConstruct(mBegin, p, p + length);
        Impl::destroy(p, p + length);
        this->free_(p);
    } else {
        mBegin = p;
        mLength = length;
        mCapacity = length;
    }
#ifdef DEBUG
    mReserved = length;
#endif
}

template <class T, size_t N, class AP>
inline size_t
Vector<T,N,AP>::sizeOfExcludingThis(JSMallocSizeOfFun mallocSizeOf) const
{
    return usingInlineStorage() ? 0 : mallocSizeOf(beginNoCheck());
}

template <class T, size_t N, class AP>
inline size_t
Vector<T,N,AP>::sizeOfIncludingThis(JSMallocSizeOfFun mallocSizeOf) const
{
    return mallocSizeOf(this) + sizeOfExcludingThis(mallocSizeOf);
}

}  /* namespace js */

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* jsvector_h_ */
