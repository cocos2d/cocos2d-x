/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Weak pointer functionality, implemented as a mixin for use with any class. */

/**
 * SupportsWeakPtr lets you have a pointer to an object 'Foo' without affecting
 * its lifetime. It works by creating a single shared reference counted object
 * (WeakReference) that each WeakPtr will access 'Foo' through. This lets 'Foo'
 * clear the pointer in the WeakReference without having to know about all of
 * the WeakPtrs to it and allows the WeakReference to live beyond the lifetime
 * of 'Foo'.
 *
 * The overhead of WeakPtr is that accesses to 'Foo' becomes an additional
 * dereference, and an additional heap allocated pointer sized object shared
 * between all of the WeakPtrs.
 *
 * Example of usage:
 *
 *   // To have a class C support weak pointers, inherit from SupportsWeakPtr<C>.
 *   class C : public SupportsWeakPtr<C>
 *   {
 *    public:
 *      int num;
 *      void act();
 *   };
 *
 *   C* ptr =  new C();
 *
 *   // Get weak pointers to ptr. The first time asWeakPtr is called
 *   // a reference counted WeakReference object is created that
 *   // can live beyond the lifetime of 'ptr'. The WeakReference
 *   // object will be notified of 'ptr's destruction.
 *   WeakPtr<C> weak = ptr->asWeakPtr();
 *   WeakPtr<C> other = ptr->asWeakPtr();
 *
 *   // Test a weak pointer for validity before using it.
 *   if (weak) {
 *     weak->num = 17;
 *     weak->act();
 *   }
 *
 *   // Destroying the underlying object clears weak pointers to it.
 *   delete ptr;
 *
 *   MOZ_ASSERT(!weak, "Deleting |ptr| clears weak pointers to it.");
 *   MOZ_ASSERT(!other, "Deleting |ptr| clears all weak pointers to it.");
 *
 * WeakPtr is typesafe and may be used with any class. It is not required that
 * the class be reference-counted or allocated in any particular way.
 *
 * The API was loosely inspired by Chromium's weak_ptr.h:
 * http://src.chromium.org/svn/trunk/src/base/memory/weak_ptr.h
 */

#ifndef mozilla_WeakPtr_h_
#define mozilla_WeakPtr_h_

#include "mozilla/Assertions.h"
#include "mozilla/NullPtr.h"
#include "mozilla/RefPtr.h"
#include "mozilla/TypeTraits.h"

namespace mozilla {

template <typename T> class WeakPtr;

template <typename T>
class SupportsWeakPtr
{
  public:
    WeakPtr<T> asWeakPtr() {
      if (!weakRef)
        weakRef = new WeakReference(static_cast<T*>(this));
      return WeakPtr<T>(weakRef);
    }

  protected:
    ~SupportsWeakPtr() {
      MOZ_STATIC_ASSERT((IsBaseOf<SupportsWeakPtr<T>, T>::value), "T must derive from SupportsWeakPtr<T>");
      if (weakRef)
        weakRef->detach();
    }

  private:
    friend class WeakPtr<T>;

    // This can live beyond the lifetime of the class derived from SupportsWeakPtr.
    class WeakReference : public RefCounted<WeakReference>
    {
      public:
        explicit WeakReference(T* p) : ptr(p) {}
        T* get() const {
          return ptr;
        }

      private:
        friend class WeakPtr<T>;
        friend class SupportsWeakPtr<T>;
        void detach() {
          ptr = nullptr;
        }
        T* ptr;
    };

    RefPtr<WeakReference> weakRef;
};

template <typename T>
class WeakPtr
{
  public:
    WeakPtr(const WeakPtr<T>& o) : ref(o.ref) {}
    // Ensure that ref is dereferenceable in the uninitialized state
    WeakPtr() : ref(new typename SupportsWeakPtr<T>::WeakReference(nullptr)) {}

    operator T*() const {
      return ref->get();
    }
    T& operator*() const {
      return *ref->get();
    }

    T* operator->() const {
      return ref->get();
    }

    T* get() const {
      return ref->get();
    }

  private:
    friend class SupportsWeakPtr<T>;

    explicit WeakPtr(const RefPtr<typename SupportsWeakPtr<T>::WeakReference> &o) : ref(o) {}

    RefPtr<typename SupportsWeakPtr<T>::WeakReference> ref;
};

} // namespace mozilla

#endif /* ifdef mozilla_WeakPtr_h_ */
