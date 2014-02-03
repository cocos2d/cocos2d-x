/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* A compile-time constant-length array with bounds-checking assertions. */

#ifndef mozilla_Array_h
#define mozilla_Array_h

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"

#include <stddef.h>

namespace mozilla {

template<typename T, size_t Length>
class Array
{
    T arr[Length];

  public:
    T& operator[](size_t i) {
      MOZ_ASSERT(i < Length);
      return arr[i];
    }

    const T& operator[](size_t i) const {
      MOZ_ASSERT(i < Length);
      return arr[i];
    }
};

template<typename T>
class Array<T, 0>
{
  public:
    T& operator[](size_t i) {
      MOZ_ASSUME_UNREACHABLE("indexing into zero-length array");
    }

    const T& operator[](size_t i) const {
      MOZ_ASSUME_UNREACHABLE("indexing into zero-length array");
    }
};

}  /* namespace mozilla */

#endif /* mozilla_Array_h */
