/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Provides DebugOnly, a type for variables used only in debug builds (i.e. by
 * assertions).
 */

#ifndef mozilla_DebugOnly_h_
#define mozilla_DebugOnly_h_

namespace mozilla {

/**
 * DebugOnly contains a value of type T, but only in debug builds.  In release
 * builds, it does not contain a value.  This helper is intended to be used with
 * MOZ_ASSERT()-style macros, allowing one to write:
 *
 *   DebugOnly<bool> check = func();
 *   MOZ_ASSERT(check);
 *
 * more concisely than declaring |check| conditional on #ifdef DEBUG, but also
 * without allocating storage space for |check| in release builds.
 *
 * DebugOnly instances can only be coerced to T in debug builds.  In release
 * builds they don't have a value, so type coercion is not well defined.
 */
template<typename T>
class DebugOnly
{
  public:
#ifdef DEBUG
    T value;

    DebugOnly() { }
    DebugOnly(const T& other) : value(other) { }
    DebugOnly(const DebugOnly& other) : value(other.value) { }
    DebugOnly& operator=(const T& rhs) {
      value = rhs;
      return *this;
    }
    void operator++(int) {
      value++;
    }
    void operator--(int) {
      value--;
    }

    T* operator&() { return &value; }

    operator T&() { return value; }
    operator const T&() const { return value; }

    T& operator->() { return value; }

#else
    DebugOnly() { }
    DebugOnly(const T&) { }
    DebugOnly(const DebugOnly&) { }
    DebugOnly& operator=(const T&) { return *this; }
    void operator++(int) { }
    void operator--(int) { }
#endif

    /*
     * DebugOnly must always have a destructor or else it will
     * generate "unused variable" warnings, exactly what it's intended
     * to avoid!
     */
    ~DebugOnly() {}
};

}

#endif  /* mozilla_DebugOnly_h_ */
