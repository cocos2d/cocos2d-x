/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Miscellaneous uncategorized functionality.  Please add new functionality to
 * new headers, or to other appropriate existing headers, not here.
 */

#ifndef mozilla_Util_h_
#define mozilla_Util_h_

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Types.h"

#ifdef __cplusplus

namespace mozilla {

/*
 * This class, and the corresponding macro MOZ_ALIGNOF, figure out how many 
 * bytes of alignment a given type needs.
 */
template<class T>
class AlignmentFinder
{
    struct Aligner
    {
        char c;
        T t;
    };

  public:
    static const size_t alignment = sizeof(Aligner) - sizeof(T);
};

#define MOZ_ALIGNOF(T) mozilla::AlignmentFinder<T>::alignment

/*
 * Declare the MOZ_ALIGNED_DECL macro for declaring aligned types.
 *
 * For instance,
 *
 *   MOZ_ALIGNED_DECL(char arr[2], 8);
 *
 * will declare a two-character array |arr| aligned to 8 bytes.
 */

#if defined(__GNUC__)
#  define MOZ_ALIGNED_DECL(_type, _align) \
     _type __attribute__((aligned(_align)))
#elif defined(_MSC_VER)
#  define MOZ_ALIGNED_DECL(_type, _align) \
     __declspec(align(_align)) _type
#else
#  warning "We don't know how to align variables on this compiler."
#  define MOZ_ALIGNED_DECL(_type, _align) _type
#endif

/*
 * AlignedElem<N> is a structure whose alignment is guaranteed to be at least N
 * bytes.
 *
 * We support 1, 2, 4, 8, and 16-bit alignment.
 */
template<size_t align>
struct AlignedElem;

/*
 * We have to specialize this template because GCC doesn't like __attribute__((aligned(foo))) where
 * foo is a template parameter.
 */

template<>
struct AlignedElem<1>
{
    MOZ_ALIGNED_DECL(uint8_t elem, 1);
};

template<>
struct AlignedElem<2>
{
    MOZ_ALIGNED_DECL(uint8_t elem, 2);
};

template<>
struct AlignedElem<4>
{
    MOZ_ALIGNED_DECL(uint8_t elem, 4);
};

template<>
struct AlignedElem<8>
{
    MOZ_ALIGNED_DECL(uint8_t elem, 8);
};

template<>
struct AlignedElem<16>
{
    MOZ_ALIGNED_DECL(uint8_t elem, 16);
};

/*
 * This utility pales in comparison to Boost's aligned_storage. The utility
 * simply assumes that uint64_t is enough alignment for anyone. This may need
 * to be extended one day...
 *
 * As an important side effect, pulling the storage into this template is
 * enough obfuscation to confuse gcc's strict-aliasing analysis into not giving
 * false negatives when we cast from the char buffer to whatever type we've
 * constructed using the bytes.
 */
template<size_t nbytes>
struct AlignedStorage
{
    union U {
      char bytes[nbytes];
      uint64_t _;
    } u;

    const void* addr() const { return u.bytes; }
    void* addr() { return u.bytes; }
};

template<class T>
struct AlignedStorage2
{
    union U {
      char bytes[sizeof(T)];
      uint64_t _;
    } u;

    const T* addr() const { return reinterpret_cast<const T*>(u.bytes); }
    T* addr() { return static_cast<T*>(static_cast<void*>(u.bytes)); }
};

/*
 * Small utility for lazily constructing objects without using dynamic storage.
 * When a Maybe<T> is constructed, it is |empty()|, i.e., no value of T has
 * been constructed and no T destructor will be called when the Maybe<T> is
 * destroyed. Upon calling |construct|, a T object will be constructed with the
 * given arguments and that object will be destroyed when the owning Maybe<T>
 * is destroyed.
 *
 * N.B. GCC seems to miss some optimizations with Maybe and may generate extra
 * branches/loads/stores. Use with caution on hot paths.
 */
template<class T>
class Maybe
{
    AlignedStorage2<T> storage;
    bool constructed;

    T& asT() { return *storage.addr(); }

  public:
    Maybe() { constructed = false; }
    ~Maybe() { if (constructed) asT().~T(); }

    bool empty() const { return !constructed; }

    void construct() {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T();
      constructed = true;
    }

    template<class T1>
    void construct(const T1& t1) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1);
      constructed = true;
    }

    template<class T1, class T2>
    void construct(const T1& t1, const T2& t2) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2);
      constructed = true;
    }

    template<class T1, class T2, class T3>
    void construct(const T1& t1, const T2& t2, const T3& t3) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3);
      constructed = true;
    }

    template<class T1, class T2, class T3, class T4>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4);
      constructed = true;
    }

    T* addr() {
      MOZ_ASSERT(constructed);
      return &asT();
    }

    T& ref() {
      MOZ_ASSERT(constructed);
      return asT();
    }

    const T& ref() const {
      MOZ_ASSERT(constructed);
      return const_cast<Maybe*>(this)->asT();
    }

    void destroy() {
      ref().~T();
      constructed = false;
    }

    void destroyIfConstructed() {
      if (!empty())
        destroy();
    }

  private:
    Maybe(const Maybe& other) MOZ_DELETE;
    const Maybe& operator=(const Maybe& other) MOZ_DELETE;
};

/*
 * Safely subtract two pointers when it is known that end >= begin.  This avoids
 * the common compiler bug that if (size_t(end) - size_t(begin)) has the MSB
 * set, the unsigned subtraction followed by right shift will produce -1, or
 * size_t(-1), instead of the real difference.
 */
template<class T>
MOZ_ALWAYS_INLINE size_t
PointerRangeSize(T* begin, T* end)
{
  MOZ_ASSERT(end >= begin);
  return (size_t(end) - size_t(begin)) / sizeof(T);
}

/*
 * Compute the length of an array with constant length.  (Use of this method
 * with a non-array pointer will not compile.)
 *
 * Beware of the implicit trailing '\0' when using this with string constants.
 */
template<typename T, size_t N>
MOZ_CONSTEXPR size_t
ArrayLength(T (&arr)[N])
{
  return N;
}

/*
 * Compute the address one past the last element of a constant-length array.
 *
 * Beware of the implicit trailing '\0' when using this with string constants.
 */
template<typename T, size_t N>
MOZ_CONSTEXPR T*
ArrayEnd(T (&arr)[N])
{
  return arr + ArrayLength(arr);
}

} /* namespace mozilla */

#endif /* __cplusplus */

/*
 * MOZ_ARRAY_LENGTH() is an alternative to mozilla::ArrayLength() for C files
 * that can't use C++ template functions and for MOZ_STATIC_ASSERT() calls that
 * can't call ArrayLength() when it is not a C++11 constexpr function.
 */
#ifdef MOZ_HAVE_CXX11_CONSTEXPR
#  define MOZ_ARRAY_LENGTH(array)   mozilla::ArrayLength(array)
#else
#  define MOZ_ARRAY_LENGTH(array)   (sizeof(array)/sizeof((array)[0]))
#endif

#endif  /* mozilla_Util_h_ */
