/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Code.
 *
 * The Initial Developer of the Original Code is
 *   The Mozilla Foundation
 * Portions created by the Initial Developer are Copyright (C) 2011
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Jeff Walden <jwalden+code@mit.edu> (original author)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

/*
 * Implements a smart pointer asserted to remain within a range specified at
 * construction.
 */

#ifndef mozilla_RangedPtr_h_
#define mozilla_RangedPtr_h_

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Util.h"

namespace mozilla {

/*
 * RangedPtr is a smart pointer restricted to an address range specified at
 * creation.  The pointer (and any smart pointers derived from it) must remain
 * within the range [start, end] (inclusive of end to facilitate use as
 * sentinels).  Dereferencing or indexing into the pointer (or pointers derived
 * from it) must remain within the range [start, end).  All the standard pointer
 * operators are defined on it; in debug builds these operations assert that the
 * range specified at construction is respected.
 *
 * In theory passing a smart pointer instance as an argument can be slightly
 * slower than passing a T* (due to ABI requirements for passing structs versus
 * passing pointers), if the method being called isn't inlined.  If you are in
 * extremely performance-critical code, you may want to be careful using this
 * smart pointer as an argument type.
 *
 * RangedPtr<T> intentionally does not implicitly convert to T*.  Use get() to
 * explicitly convert to T*.  Keep in mind that the raw pointer of course won't
 * implement bounds checking in debug builds.
 */
template <typename T>
class RangedPtr
{
    T* ptr;

#ifdef DEBUG
    T* const rangeStart;
    T* const rangeEnd;
#endif

    void checkSanity() {
        MOZ_ASSERT(rangeStart <= ptr);
        MOZ_ASSERT(ptr <= rangeEnd);
    }

    /* Creates a new pointer for |ptr|, restricted to this pointer's range. */
    RangedPtr<T> create(T *ptr) const {
#ifdef DEBUG
        return RangedPtr<T>(ptr, rangeStart, rangeEnd);
#else
        return RangedPtr<T>(ptr, NULL, size_t(0));
#endif
    }

  public:
    RangedPtr(T* p, T* start, T* end)
      : ptr(p)
#ifdef DEBUG
      , rangeStart(start), rangeEnd(end)
#endif
    {
        MOZ_ASSERT(rangeStart <= rangeEnd);
        checkSanity();
    }
    RangedPtr(T* p, T* start, size_t length)
      : ptr(p)
#ifdef DEBUG
      , rangeStart(start), rangeEnd(start + length)
#endif
    {
        MOZ_ASSERT(length <= size_t(-1) / sizeof(T));
        MOZ_ASSERT(uintptr_t(rangeStart) + length * sizeof(T) >= uintptr_t(rangeStart));
        checkSanity();
    }

    /* Equivalent to RangedPtr(p, p, length). */
    RangedPtr(T* p, size_t length)
      : ptr(p)
#ifdef DEBUG
      , rangeStart(p), rangeEnd(p + length)
#endif
    {
        MOZ_ASSERT(length <= size_t(-1) / sizeof(T));
        MOZ_ASSERT(uintptr_t(rangeStart) + length * sizeof(T) >= uintptr_t(rangeStart));
        checkSanity();
    }

    /* Equivalent to RangedPtr(arr, arr, N). */
    template<size_t N>
    RangedPtr(T arr[N])
      : ptr(arr)
#ifdef DEBUG
      , rangeStart(arr), rangeEnd(arr + N)
#endif
    {
      checkSanity();
    }

    T* get() const {
        return ptr;
    }

    /*
     * You can only assign one RangedPtr into another if the two pointers have
     * the same valid range:
     *
     *   char arr1[] = "hi";
     *   char arr2[] = "bye";
     *   RangedPtr<char> p1(arr1, 2);
     *   p1 = RangedPtr<char>(arr1 + 1, arr1, arr1 + 2); // works
     *   p1 = RangedPtr<char>(arr2, 3);                  // asserts
     */
    RangedPtr<T>& operator=(const RangedPtr<T>& other) {
        MOZ_ASSERT(rangeStart == other.rangeStart);
        MOZ_ASSERT(rangeEnd == other.rangeEnd);
        ptr = other.ptr;
        checkSanity();
        return *this;
    }

    RangedPtr<T> operator+(size_t inc) {
        MOZ_ASSERT(inc <= size_t(-1) / sizeof(T));
        MOZ_ASSERT(ptr + inc > ptr);
        return create(ptr + inc);
    }

    RangedPtr<T> operator-(size_t dec) {
        MOZ_ASSERT(dec <= size_t(-1) / sizeof(T));
        MOZ_ASSERT(ptr - dec < ptr);
        return create(ptr - dec);
    }

    /*
     * You can assign a raw pointer into a RangedPtr if the raw pointer is
     * within the range specified at creation.
     */
    template <typename U>
    RangedPtr<T>& operator=(U* p) {
        *this = create(p);
        return *this;
    }

    template <typename U>
    RangedPtr<T>& operator=(const RangedPtr<U>& p) {
        MOZ_ASSERT(rangeStart <= p.ptr);
        MOZ_ASSERT(p.ptr <= rangeEnd);
        ptr = p.ptr;
        checkSanity();
        return *this;
    }

    RangedPtr<T>& operator++() {
        return (*this += 1);
    }

    RangedPtr<T> operator++(int) {
        RangedPtr<T> rcp = *this;
        ++*this;
        return rcp;
    }

    RangedPtr<T>& operator--() {
        return (*this -= 1);
    }

    RangedPtr<T> operator--(int) {
        RangedPtr<T> rcp = *this;
        --*this;
        return rcp;
    }

    RangedPtr<T>& operator+=(size_t inc) {
        this->operator=<T>(*this + inc);
        return *this;
    }

    RangedPtr<T>& operator-=(size_t dec) {
        this->operator=<T>(*this - dec);
        return *this;
    }

    T& operator[](int index) const {
        MOZ_ASSERT(size_t(index > 0 ? index : -index) <= size_t(-1) / sizeof(T));
        return *create(ptr + index);
    }

    T& operator*() const {
        return *ptr;
    }

    template <typename U>
    bool operator==(const RangedPtr<U>& other) const {
        return ptr == other.ptr;
    }
    template <typename U>
    bool operator!=(const RangedPtr<U>& other) const {
        return !(*this == other);
    }

    template<typename U>
    bool operator==(const U* u) const {
        return ptr == u;
    }
    template<typename U>
    bool operator!=(const U* u) const {
        return !(*this == u);
    }

    template <typename U>
    bool operator<(const RangedPtr<U>& other) const {
        return ptr < other.ptr;
    }
    template <typename U>
    bool operator<=(const RangedPtr<U>& other) const {
        return ptr <= other.ptr;
    }

    template <typename U>
    bool operator>(const RangedPtr<U>& other) const {
        return ptr > other.ptr;
    }
    template <typename U>
    bool operator>=(const RangedPtr<U>& other) const {
        return ptr >= other.ptr;
    }

    size_t operator-(const RangedPtr<T>& other) const {
        MOZ_ASSERT(ptr >= other.ptr);
        return PointerRangeSize(other.ptr, ptr);
    }

  private:
    RangedPtr() MOZ_DELETE;
    T* operator&() MOZ_DELETE;
    operator T*() const MOZ_DELETE;
};

} /* namespace mozilla */

#endif  /* mozilla_RangedPtr_h_ */
