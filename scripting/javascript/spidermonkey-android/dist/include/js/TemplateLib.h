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
 * The Original Code is Mozilla SpiderMonkey JavaScript code.
 *
 * The Initial Developer of the Original Code is
 * the Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2011
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *  Luke Wagner <luke@mozilla.com>
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

#ifndef js_template_lib_h__
#define js_template_lib_h__

#include "jstypes.h"

/*
 * Library of reusable template meta-functions (that is, functions on types and
 * compile-time values). Meta-functions are placed inside the 'tl' namespace to
 * avoid conflict with non-meta functions that logically have the same name
 * (e.g., js::tl::Min vs. js::Min).
 */

namespace js {
namespace tl {

/* Compute min/max/clamp. */
template <size_t i, size_t j> struct Min {
    static const size_t result = i < j ? i : j;
};
template <size_t i, size_t j> struct Max {
    static const size_t result = i > j ? i : j;
};
template <size_t i, size_t min, size_t max> struct Clamp {
    static const size_t result = i < min ? min : (i > max ? max : i);
};

/* Compute x^y. */
template <size_t x, size_t y> struct Pow {
    static const size_t result = x * Pow<x, y - 1>::result;
};
template <size_t x> struct Pow<x,0> {
    static const size_t result = 1;
};

/* Compute floor(log2(i)). */
template <size_t i> struct FloorLog2 {
    static const size_t result = 1 + FloorLog2<i / 2>::result;
};
template <> struct FloorLog2<0> { /* Error */ };
template <> struct FloorLog2<1> { static const size_t result = 0; };

/* Compute ceiling(log2(i)). */
template <size_t i> struct CeilingLog2 {
    static const size_t result = FloorLog2<2 * i - 1>::result;
};

/* Round up to the nearest power of 2. */
template <size_t i> struct RoundUpPow2 {
    static const size_t result = size_t(1) << CeilingLog2<i>::result;
};
template <> struct RoundUpPow2<0> {
    static const size_t result = 1;
};

/* Compute the number of bits in the given unsigned type. */
template <class T> struct BitSize {
    static const size_t result = sizeof(T) * JS_BITS_PER_BYTE;
};

/* Allow Assertions by only including the 'result' typedef if 'true'. */
template <bool> struct StaticAssert {};
template <> struct StaticAssert<true> { typedef int result; };

/* Boolean test for whether two types are the same. */
template <class T, class U> struct IsSameType {
    static const bool result = false;
};
template <class T> struct IsSameType<T,T> {
    static const bool result = true;
};

/*
 * Produce an N-bit mask, where N <= BitSize<size_t>::result.  Handle the
 * language-undefined edge case when N = BitSize<size_t>::result.
 */
template <size_t N> struct NBitMask {
    typedef typename StaticAssert<N < BitSize<size_t>::result>::result _;
    static const size_t result = (size_t(1) << N) - 1;
};
template <> struct NBitMask<BitSize<size_t>::result> {
    static const size_t result = size_t(-1);
};

/*
 * For the unsigned integral type size_t, compute a mask M for N such that
 * for all X, !(X & M) implies X * N will not overflow (w.r.t size_t)
 */
template <size_t N> struct MulOverflowMask {
    static const size_t result =
        ~NBitMask<BitSize<size_t>::result - CeilingLog2<N>::result>::result;
};
template <> struct MulOverflowMask<0> { /* Error */ };
template <> struct MulOverflowMask<1> { static const size_t result = 0; };

/*
 * Generate a mask for T such that if (X & sUnsafeRangeSizeMask), an X-sized
 * array of T's is big enough to cause a ptrdiff_t overflow when subtracting
 * a pointer to the end of the array from the beginning.
 */
template <class T> struct UnsafeRangeSizeMask {
    /*
     * The '2' factor means the top bit is clear, sizeof(T) converts from
     * units of elements to bytes.
     */
    static const size_t result = MulOverflowMask<2 * sizeof(T)>::result;
};

/* Return T stripped of any const-ness. */
template <class T> struct StripConst          { typedef T result; };
template <class T> struct StripConst<const T> { typedef T result; };

/*
 * Traits class for identifying POD types. Until C++0x, there is no automatic
 * way to detect PODs, so for the moment it is done manually.
 */
template <class T> struct IsPodType                 { static const bool result = false; };
template <> struct IsPodType<char>                  { static const bool result = true; };
template <> struct IsPodType<signed char>           { static const bool result = true; };
template <> struct IsPodType<unsigned char>         { static const bool result = true; };
template <> struct IsPodType<short>                 { static const bool result = true; };
template <> struct IsPodType<unsigned short>        { static const bool result = true; };
template <> struct IsPodType<int>                   { static const bool result = true; };
template <> struct IsPodType<unsigned int>          { static const bool result = true; };
template <> struct IsPodType<long>                  { static const bool result = true; };
template <> struct IsPodType<unsigned long>         { static const bool result = true; };
template <> struct IsPodType<long long>             { static const bool result = true; };
template <> struct IsPodType<unsigned long long>    { static const bool result = true; };
template <> struct IsPodType<bool>                  { static const bool result = true; };
template <> struct IsPodType<float>                 { static const bool result = true; };
template <> struct IsPodType<double>                { static const bool result = true; };
template <> struct IsPodType<wchar_t>               { static const bool result = true; };
template <typename T> struct IsPodType<T *>         { static const bool result = true; };

template <bool cond, typename T, T v1, T v2> struct If        { static const T result = v1; };
template <typename T, T v1, T v2> struct If<false, T, v1, v2> { static const T result = v2; };

/*
 * Traits class for identifying types that are implicitly barriered.
 */
template <class T> struct IsPostBarrieredType { static const bool result = false; };

} /* namespace tl */
} /* namespace js */

#endif  /* js_template_lib_h__ */
