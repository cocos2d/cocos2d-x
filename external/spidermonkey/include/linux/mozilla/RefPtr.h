/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Helpers for defining and using refcounted objects. */

#ifndef mozilla_RefPtr_h
#define mozilla_RefPtr_h

#include "mozilla/Assertions.h"
#include "mozilla/Atomics.h"
#include "mozilla/Attributes.h"
#include "mozilla/TypeTraits.h"

namespace mozilla {

template<typename T> class RefCounted;
template<typename T> class RefPtr;
template<typename T> class TemporaryRef;
template<typename T> class OutParamRef;
template<typename T> OutParamRef<T> byRef(RefPtr<T>&);

/**
 * RefCounted<T> is a sort of a "mixin" for a class T.  RefCounted
 * manages, well, refcounting for T, and because RefCounted is
 * parameterized on T, RefCounted<T> can call T's destructor directly.
 * This means T doesn't need to have a virtual dtor and so doesn't
 * need a vtable.
 *
 * RefCounted<T> is created with refcount == 0.  Newly-allocated
 * RefCounted<T> must immediately be assigned to a RefPtr to make the
 * refcount > 0.  It's an error to allocate and free a bare
 * RefCounted<T>, i.e. outside of the RefPtr machinery.  Attempts to
 * do so will abort DEBUG builds.
 *
 * Live RefCounted<T> have refcount > 0.  The lifetime (refcounts) of
 * live RefCounted<T> are controlled by RefPtr<T> and
 * RefPtr<super/subclass of T>.  Upon a transition from refcounted==1
 * to 0, the RefCounted<T> "dies" and is destroyed.  The "destroyed"
 * state is represented in DEBUG builds by refcount==0xffffdead.  This
 * state distinguishes use-before-ref (refcount==0) from
 * use-after-destroy (refcount==0xffffdead).
 */
namespace detail {
#ifdef DEBUG
static const int DEAD = 0xffffdead;
#endif

// This is used WeakPtr.h as well as this file.
enum RefCountAtomicity
{
  AtomicRefCount,
  NonAtomicRefCount
};

template<typename T, RefCountAtomicity Atomicity>
class RefCounted
{
    friend class RefPtr<T>;

  protected:
    RefCounted() : refCnt(0) { }
    ~RefCounted() {
      MOZ_ASSERT(refCnt == detail::DEAD);
    }

  public:
    // Compatibility with nsRefPtr.
    void AddRef() const {
      MOZ_ASSERT(refCnt >= 0);
      ++refCnt;
    }

    void Release() const {
      MOZ_ASSERT(refCnt > 0);
      if (0 == --refCnt) {
#ifdef DEBUG
        refCnt = detail::DEAD;
#endif
        delete static_cast<const T*>(this);
      }
    }

    // Compatibility with wtf::RefPtr.
    void ref() { AddRef(); }
    void deref() { Release(); }
    int refCount() const { return refCnt; }
    bool hasOneRef() const {
      MOZ_ASSERT(refCnt > 0);
      return refCnt == 1;
    }

  private:
    mutable typename Conditional<Atomicity == AtomicRefCount, Atomic<int>, int>::Type refCnt;
};

}

template<typename T>
class RefCounted : public detail::RefCounted<T, detail::NonAtomicRefCount>
{
  public:
    ~RefCounted() {
      static_assert(IsBaseOf<RefCounted, T>::value,
                    "T must derive from RefCounted<T>");
    }
};

/**
 * AtomicRefCounted<T> is like RefCounted<T>, with an atomically updated
 * reference counter.
 */
template<typename T>
class AtomicRefCounted : public detail::RefCounted<T, detail::AtomicRefCount>
{
  public:
    ~AtomicRefCounted() {
      static_assert(IsBaseOf<AtomicRefCounted, T>::value,
                    "T must derive from AtomicRefCounted<T>");
    }
};

/**
 * RefPtr points to a refcounted thing that has AddRef and Release
 * methods to increase/decrease the refcount, respectively.  After a
 * RefPtr<T> is assigned a T*, the T* can be used through the RefPtr
 * as if it were a T*.
 *
 * A RefPtr can forget its underlying T*, which results in the T*
 * being wrapped in a temporary object until the T* is either
 * re-adopted from or released by the temporary.
 */
template<typename T>
class RefPtr
{
    // To allow them to use unref()
    friend class TemporaryRef<T>;
    friend class OutParamRef<T>;

    struct DontRef {};

  public:
    RefPtr() : ptr(0) { }
    RefPtr(const RefPtr& o) : ptr(ref(o.ptr)) {}
    RefPtr(const TemporaryRef<T>& o) : ptr(o.drop()) {}
    RefPtr(T* t) : ptr(ref(t)) {}

    template<typename U>
    RefPtr(const RefPtr<U>& o) : ptr(ref(o.get())) {}

    ~RefPtr() { unref(ptr); }

    RefPtr& operator=(const RefPtr& o) {
      assign(ref(o.ptr));
      return *this;
    }
    RefPtr& operator=(const TemporaryRef<T>& o) {
      assign(o.drop());
      return *this;
    }
    RefPtr& operator=(T* t) {
      assign(ref(t));
      return *this;
    }

    template<typename U>
    RefPtr& operator=(const RefPtr<U>& o) {
      assign(ref(o.get()));
      return *this;
    }

    TemporaryRef<T> forget() {
      T* tmp = ptr;
      ptr = 0;
      return TemporaryRef<T>(tmp, DontRef());
    }

    T* get() const { return ptr; }
    operator T*() const { return ptr; }
    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }
    template<typename U>
    operator TemporaryRef<U>() { return TemporaryRef<U>(ptr); }

  private:
    void assign(T* t) {
      unref(ptr);
      ptr = t;
    }

    T* ptr;

    static MOZ_ALWAYS_INLINE T* ref(T* t) {
      if (t)
        t->AddRef();
      return t;
    }

    static MOZ_ALWAYS_INLINE void unref(T* t) {
      if (t)
        t->Release();
    }
};

/**
 * TemporaryRef<T> represents an object that holds a temporary
 * reference to a T.  TemporaryRef objects can't be manually ref'd or
 * unref'd (being temporaries, not lvalues), so can only relinquish
 * references to other objects, or unref on destruction.
 */
template<typename T>
class TemporaryRef
{
    // To allow it to construct TemporaryRef from a bare T*
    friend class RefPtr<T>;

    typedef typename RefPtr<T>::DontRef DontRef;

  public:
    TemporaryRef(T* t) : ptr(RefPtr<T>::ref(t)) {}
    TemporaryRef(const TemporaryRef& o) : ptr(o.drop()) {}

    template<typename U>
    TemporaryRef(const TemporaryRef<U>& o) : ptr(o.drop()) {}

    ~TemporaryRef() { RefPtr<T>::unref(ptr); }

    T* drop() const {
      T* tmp = ptr;
      ptr = 0;
      return tmp;
    }

  private:
    TemporaryRef(T* t, const DontRef&) : ptr(t) {}

    mutable T* ptr;

    TemporaryRef() MOZ_DELETE;
    void operator=(const TemporaryRef&) MOZ_DELETE;
};

/**
 * OutParamRef is a wrapper that tracks a refcounted pointer passed as
 * an outparam argument to a function.  OutParamRef implements COM T**
 * outparam semantics: this requires the callee to AddRef() the T*
 * returned through the T** outparam on behalf of the caller.  This
 * means the caller (through OutParamRef) must Release() the old
 * object contained in the tracked RefPtr.  It's OK if the callee
 * returns the same T* passed to it through the T** outparam, as long
 * as the callee obeys the COM discipline.
 *
 * Prefer returning TemporaryRef<T> from functions over creating T**
 * outparams and passing OutParamRef<T> to T**.  Prefer RefPtr<T>*
 * outparams over T** outparams.
 */
template<typename T>
class OutParamRef
{
    friend OutParamRef byRef<T>(RefPtr<T>&);

  public:
    ~OutParamRef() {
      RefPtr<T>::unref(refPtr.ptr);
      refPtr.ptr = tmp;
    }

    operator T**() { return &tmp; }

  private:
    OutParamRef(RefPtr<T>& p) : refPtr(p), tmp(p.get()) {}

    RefPtr<T>& refPtr;
    T* tmp;

    OutParamRef() MOZ_DELETE;
    OutParamRef& operator=(const OutParamRef&) MOZ_DELETE;
};

/**
 * byRef cooperates with OutParamRef to implement COM outparam semantics.
 */
template<typename T>
OutParamRef<T>
byRef(RefPtr<T>& ptr)
{
  return OutParamRef<T>(ptr);
}

} // namespace mozilla

#if 0

// Command line that builds these tests
//
//   cp RefPtr.h test.cc && g++ -g -Wall -pedantic -DDEBUG -o test test.cc && ./test

using namespace mozilla;

struct Foo : public RefCounted<Foo>
{
  Foo() : dead(false) { }
  ~Foo() {
    MOZ_ASSERT(!dead);
    dead = true;
    numDestroyed++;
  }

  bool dead;
  static int numDestroyed;
};
int Foo::numDestroyed;

struct Bar : public Foo { };

TemporaryRef<Foo>
NewFoo()
{
  return RefPtr<Foo>(new Foo());
}

TemporaryRef<Foo>
NewBar()
{
  return new Bar();
}

void
GetNewFoo(Foo** f)
{
  *f = new Bar();
  // Kids, don't try this at home
  (*f)->AddRef();
}

void
GetPassedFoo(Foo** f)
{
  // Kids, don't try this at home
  (*f)->AddRef();
}

void
GetNewFoo(RefPtr<Foo>* f)
{
  *f = new Bar();
}

void
GetPassedFoo(RefPtr<Foo>* f)
{}

TemporaryRef<Foo>
GetNullFoo()
{
  return 0;
}

int
main(int argc, char** argv)
{
  // This should blow up
//    Foo* f = new Foo(); delete f;

  MOZ_ASSERT(0 == Foo::numDestroyed);
  {
    RefPtr<Foo> f = new Foo();
    MOZ_ASSERT(f->refCount() == 1);
  }
  MOZ_ASSERT(1 == Foo::numDestroyed);

  {
    RefPtr<Foo> f1 = NewFoo();
    RefPtr<Foo> f2(NewFoo());
    MOZ_ASSERT(1 == Foo::numDestroyed);
  }
  MOZ_ASSERT(3 == Foo::numDestroyed);

  {
    RefPtr<Foo> b = NewBar();
    MOZ_ASSERT(3 == Foo::numDestroyed);
  }
  MOZ_ASSERT(4 == Foo::numDestroyed);

  {
    RefPtr<Foo> f1;
    {
      f1 = new Foo();
      RefPtr<Foo> f2(f1);
      RefPtr<Foo> f3 = f2;
      MOZ_ASSERT(4 == Foo::numDestroyed);
    }
    MOZ_ASSERT(4 == Foo::numDestroyed);
  }
  MOZ_ASSERT(5 == Foo::numDestroyed);

  {
    RefPtr<Foo> f = new Foo();
    f.forget();
    MOZ_ASSERT(6 == Foo::numDestroyed);
  }

  {
    RefPtr<Foo> f = new Foo();
    GetNewFoo(byRef(f));
    MOZ_ASSERT(7 == Foo::numDestroyed);
  }
  MOZ_ASSERT(8 == Foo::numDestroyed);

  {
    RefPtr<Foo> f = new Foo();
    GetPassedFoo(byRef(f));
    MOZ_ASSERT(8 == Foo::numDestroyed);
  }
  MOZ_ASSERT(9 == Foo::numDestroyed);

  {
    RefPtr<Foo> f = new Foo();
    GetNewFoo(&f);
    MOZ_ASSERT(10 == Foo::numDestroyed);
  }
  MOZ_ASSERT(11 == Foo::numDestroyed);

  {
    RefPtr<Foo> f = new Foo();
    GetPassedFoo(&f);
    MOZ_ASSERT(11 == Foo::numDestroyed);
  }
  MOZ_ASSERT(12 == Foo::numDestroyed);

  {
    RefPtr<Foo> f1 = new Bar();
  }
  MOZ_ASSERT(13 == Foo::numDestroyed);

  {
    RefPtr<Foo> f = GetNullFoo();
    MOZ_ASSERT(13 == Foo::numDestroyed);
  }
  MOZ_ASSERT(13 == Foo::numDestroyed);

  return 0;
}

#endif

#endif /* mozilla_RefPtr_h */
