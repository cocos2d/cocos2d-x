/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A class for lazily constructing an object without sticking it on the heap. */

#ifndef mozilla_Maybe_h
#define mozilla_Maybe_h

#include "mozilla/Alignment.h"
#include "mozilla/Assertions.h"

// For placement new
#include <new>

namespace mozilla {

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

    template<class T1, class T2, class T3, class T4, class T5>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4, t5);
      constructed = true;
    }

    template<class T1, class T2, class T3, class T4, class T5,
             class T6>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5,
                   const T6& t6) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4, t5, t6);
      constructed = true;
    }

    template<class T1, class T2, class T3, class T4, class T5,
             class T6, class T7>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5,
                   const T6& t6, const T7& t7) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4, t5, t6, t7);
      constructed = true;
    }

    template<class T1, class T2, class T3, class T4, class T5,
             class T6, class T7, class T8>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5,
                   const T6& t6, const T7& t7, const T8& t8) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4, t5, t6, t7, t8);
      constructed = true;
    }

    template<class T1, class T2, class T3, class T4, class T5,
             class T6, class T7, class T8, class T9>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5,
                   const T6& t6, const T7& t7, const T8& t8, const T9& t9) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4, t5, t6, t7, t8, t9);
      constructed = true;
    }

    template<class T1, class T2, class T3, class T4, class T5,
             class T6, class T7, class T8, class T9, class T10>
    void construct(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5,
                   const T6& t6, const T7& t7, const T8& t8, const T9& t9, const T10& t10) {
      MOZ_ASSERT(!constructed);
      ::new (storage.addr()) T(t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
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

} // namespace mozilla

#endif /* mozilla_Maybe_h */
