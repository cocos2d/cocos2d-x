/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_Range_h_
#define mozilla_Range_h_

#include "mozilla/NullPtr.h"
#include "mozilla/RangedPtr.h"

#include <stddef.h>

namespace mozilla {

// Range<T> is a tuple containing a pointer and a length.
template <typename T>
class Range
{
    RangedPtr<T> mStart;
    RangedPtr<T> mEnd;

    typedef void (Range::* ConvertibleToBool)();
    void nonNull() {}

  public:
    Range() : mStart(nullptr, 0), mEnd(nullptr, 0) {}
    Range(T* p, size_t len)
      : mStart(p, p, p + len),
        mEnd(p + len, p, p + len)
    {}

    RangedPtr<T> start() const { return mStart; }
    RangedPtr<T> end() const { return mEnd; }
    size_t length() const { return mEnd - mStart; }

    T& operator[](size_t offset) {
      return mStart[offset];
    }

    operator ConvertibleToBool() const { return mStart ? &Range::nonNull : 0; }
};

} // namespace mozilla

#endif // mozilla_Range_h_

