/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Cross-platform lightweight thread local data wrappers. */

#ifndef mozilla_ThreadLocal_h
#define mozilla_ThreadLocal_h

#if defined(XP_WIN)
// This file will get included in any file that wants to add a profiler mark.
// In order to not bring <windows.h> together we could include windef.h and
// winbase.h which are sufficient to get the prototypes for the Tls* functions.
// # include <windef.h>
// # include <winbase.h>
// Unfortunately, even including these headers causes us to add a bunch of ugly
// stuff to our namespace e.g #define CreateEvent CreateEventW
extern "C" {
__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
__declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
__declspec(dllimport) unsigned long __stdcall TlsAlloc();
}
#else
#  include <pthread.h>
#  include <signal.h>
#endif

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/NullPtr.h"

namespace mozilla {

// sig_safe_t denotes an atomic type which can be read or stored in a single
// instruction.  This means that data of this type is safe to be manipulated
// from a signal handler, or other similar asynchronous execution contexts.
#if defined(XP_WIN)
typedef unsigned long sig_safe_t;
#else
typedef sig_atomic_t sig_safe_t;
#endif

/*
 * Thread Local Storage helpers.
 *
 * Usage:
 *
 * Only static-storage-duration (e.g. global variables, or static class members)
 * objects of this class should be instantiated. This class relies on
 * zero-initialization, which is implicit for static-storage-duration objects.
 * It doesn't have a custom default constructor, to avoid static initializers.
 *
 * API usage:
 *
 * // Create a TLS item
 * mozilla::ThreadLocal<int> tlsKey;
 * if (!tlsKey.init()) {
 *   // deal with the error
 * }
 *
 * // Set the TLS value
 * tlsKey.set(123);
 *
 * // Get the TLS value
 * int value = tlsKey.get();
 */
template<typename T>
class ThreadLocal
{
#if defined(XP_WIN)
    typedef unsigned long key_t;
#else
    typedef pthread_key_t key_t;
#endif

    union Helper {
      void* ptr;
      T value;
    };

  public:
    MOZ_WARN_UNUSED_RESULT inline bool init();

    inline T get() const;

    inline void set(const T value);

    bool initialized() const {
      return inited;
    }

  private:
    key_t key;
    bool inited;
};

template<typename T>
inline bool
ThreadLocal<T>::init()
{
  static_assert(sizeof(T) <= sizeof(void*),
                "mozilla::ThreadLocal can't be used for types larger than "
                "a pointer");
  MOZ_ASSERT(!initialized());
#ifdef XP_WIN
  key = TlsAlloc();
  inited = key != 0xFFFFFFFFUL; // TLS_OUT_OF_INDEXES
#else
  inited = !pthread_key_create(&key, nullptr);
#endif
  return inited;
}

template<typename T>
inline T
ThreadLocal<T>::get() const
{
  MOZ_ASSERT(initialized());
  Helper h;
#ifdef XP_WIN
  h.ptr = TlsGetValue(key);
#else
  h.ptr = pthread_getspecific(key);
#endif
  return h.value;
}

template<typename T>
inline void
ThreadLocal<T>::set(const T value)
{
  MOZ_ASSERT(initialized());
  Helper h;
  h.value = value;
  bool succeeded;
#ifdef XP_WIN
  succeeded = TlsSetValue(key, h.ptr);
#else
  succeeded = !pthread_setspecific(key, h.ptr);
#endif
  if (!succeeded)
    MOZ_CRASH();
}

} // namespace mozilla

#endif /* mozilla_ThreadLocal_h */
