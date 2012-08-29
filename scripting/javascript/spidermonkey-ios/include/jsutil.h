/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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
 * PR assertion checker.
 */

#ifndef jsutil_h___
#define jsutil_h___

#include "mozilla/Attributes.h"

#include "js/Utility.h"

/* Forward declarations. */
struct JSContext;

static JS_ALWAYS_INLINE void *
js_memcpy(void *dst_, const void *src_, size_t len)
{
    char *dst = (char *) dst_;
    const char *src = (const char *) src_;
    JS_ASSERT_IF(dst >= src, (size_t) (dst - src) >= len);
    JS_ASSERT_IF(src >= dst, (size_t) (src - dst) >= len);

    return memcpy(dst, src, len);
}

#ifdef __cplusplus
namespace js {

template <class T>
struct AlignmentTestStruct
{
    char c;
    T t;
};

/* This macro determines the alignment requirements of a type. */
#define JS_ALIGNMENT_OF(t_) \
  (sizeof(js::AlignmentTestStruct<t_>) - sizeof(t_))

template <class T>
class AlignedPtrAndFlag
{
    uintptr_t bits;

  public:
    AlignedPtrAndFlag(T *t, bool flag) {
        JS_ASSERT((uintptr_t(t) & 1) == 0);
        bits = uintptr_t(t) | uintptr_t(flag);
    }

    T *ptr() const {
        return (T *)(bits & ~uintptr_t(1));
    }

    bool flag() const {
        return (bits & 1) != 0;
    }

    void setPtr(T *t) {
        JS_ASSERT((uintptr_t(t) & 1) == 0);
        bits = uintptr_t(t) | uintptr_t(flag());
    }

    void setFlag() {
        bits |= 1;
    }

    void unsetFlag() {
        bits &= ~uintptr_t(1);
    }

    void set(T *t, bool flag) {
        JS_ASSERT((uintptr_t(t) & 1) == 0);
        bits = uintptr_t(t) | flag;
    }
};

template <class T>
static inline void
Reverse(T *beg, T *end)
{
    while (beg != end) {
        if (--end == beg)
            return;
        T tmp = *beg;
        *beg = *end;
        *end = tmp;
        ++beg;
    }
}

template <class T>
static inline T *
Find(T *beg, T *end, const T &v)
{
    for (T *p = beg; p != end; ++p) {
        if (*p == v)
            return p;
    }
    return end;
}

template <class Container>
static inline typename Container::ElementType *
Find(Container &c, const typename Container::ElementType &v)
{
    return Find(c.begin(), c.end(), v);
}

template <typename InputIterT, typename CallableT>
void
ForEach(InputIterT begin, InputIterT end, CallableT f)
{
    for (; begin != end; ++begin)
        f(*begin);
}

template <class T>
static inline T
Min(T t1, T t2)
{
    return t1 < t2 ? t1 : t2;
}

template <class T>
static inline T
Max(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
}

/* Allows a const variable to be initialized after its declaration. */
template <class T>
static T&
InitConst(const T &t)
{
    return const_cast<T &>(t);
}

template <class T, class U>
JS_ALWAYS_INLINE T &
ImplicitCast(U &u)
{
    T &t = u;
    return t;
}

template<typename T>
class AutoScopedAssign
{
  private:
    JS_DECL_USE_GUARD_OBJECT_NOTIFIER
    T *addr;
    T old;

  public:
    AutoScopedAssign(T *addr, const T &value JS_GUARD_OBJECT_NOTIFIER_PARAM)
        : addr(addr), old(*addr)
    {
        JS_GUARD_OBJECT_NOTIFIER_INIT;
        *addr = value;
    }

    ~AutoScopedAssign() { *addr = old; }
};

template <class T>
JS_ALWAYS_INLINE static void
PodZero(T *t)
{
    memset(t, 0, sizeof(T));
}

template <class T>
JS_ALWAYS_INLINE static void
PodZero(T *t, size_t nelem)
{
    /*
     * This function is often called with 'nelem' small; we use an
     * inline loop instead of calling 'memset' with a non-constant
     * length.  The compiler should inline the memset call with constant
     * size, though.
     */
    for (T *end = t + nelem; t != end; ++t)
        memset(t, 0, sizeof(T));
}

/*
 * Arrays implicitly convert to pointers to their first element, which is
 * dangerous when combined with the above PodZero definitions. Adding an
 * overload for arrays is ambiguous, so we need another identifier. The
 * ambiguous overload is left to catch mistaken uses of PodZero; if you get a
 * compile error involving PodZero and array types, use PodArrayZero instead.
 */
template <class T, size_t N> static void PodZero(T (&)[N]);          /* undefined */
template <class T, size_t N> static void PodZero(T (&)[N], size_t);  /* undefined */

template <class T, size_t N>
JS_ALWAYS_INLINE static void
PodArrayZero(T (&t)[N])
{
    memset(t, 0, N * sizeof(T));
}

template <class T>
JS_ALWAYS_INLINE static void
PodAssign(T *dst, const T *src)
{
    js_memcpy((char *) dst, (const char *) src, sizeof(T));
}

template <class T>
JS_ALWAYS_INLINE static void
PodCopy(T *dst, const T *src, size_t nelem)
{
    /* Cannot find portable word-sized abs(). */
    JS_ASSERT_IF(dst >= src, size_t(dst - src) >= nelem);
    JS_ASSERT_IF(src >= dst, size_t(src - dst) >= nelem);

    if (nelem < 128) {
        /*
         * Avoid using operator= in this loop, as it may have been
         * intentionally deleted by the POD type.
         */
        for (const T *srcend = src + nelem; src != srcend; ++src, ++dst)
            PodAssign(dst, src);
    } else {
        memcpy(dst, src, nelem * sizeof(T));
    }
}

template <class T>
JS_ALWAYS_INLINE static bool
PodEqual(T *one, T *two, size_t len)
{
    if (len < 128) {
        T *p1end = one + len;
        for (T *p1 = one, *p2 = two; p1 != p1end; ++p1, ++p2) {
            if (*p1 != *p2)
                return false;
        }
        return true;
    }

    return !memcmp(one, two, len * sizeof(T));
}

template <class T>
JS_ALWAYS_INLINE static void
Swap(T &t, T &u)
{
    T tmp(Move(t));
    t = Move(u);
    u = Move(tmp);
}

JS_ALWAYS_INLINE static size_t
UnsignedPtrDiff(const void *bigger, const void *smaller)
{
    return size_t(bigger) - size_t(smaller);
}

/*
 * Ordinarily, a function taking a JSContext* 'cx' parameter reports errors on
 * the context. In some cases, functions optionally report and indicate this by
 * taking a nullable 'maybecx' parameter. In some cases, though, a function
 * always needs a 'cx', but optionally reports. This option is presented by the
 * MaybeReportError.
 */
enum MaybeReportError { REPORT_ERROR = true, DONT_REPORT_ERROR = false };

/*****************************************************************************/

/* A bit array is an array of bits represented by an array of words (size_t). */

static inline unsigned
NumWordsForBitArrayOfLength(size_t length)
{
    return (length + (JS_BITS_PER_WORD - 1)) / JS_BITS_PER_WORD;
}

static inline unsigned
BitArrayIndexToWordIndex(size_t length, size_t bitIndex)
{
    unsigned wordIndex = bitIndex / JS_BITS_PER_WORD;
    JS_ASSERT(wordIndex < length);
    return wordIndex;
}

static inline size_t
BitArrayIndexToWordMask(size_t i)
{
    return size_t(1) << (i % JS_BITS_PER_WORD);
}

static inline bool
IsBitArrayElementSet(size_t *array, size_t length, size_t i)
{
    return array[BitArrayIndexToWordIndex(length, i)] & BitArrayIndexToWordMask(i);
}

static inline bool
IsAnyBitArrayElementSet(size_t *array, size_t length)
{
    unsigned numWords = NumWordsForBitArrayOfLength(length);
    for (unsigned i = 0; i < numWords; ++i) {
        if (array[i])
            return true;
    }
    return false;
}

static inline void
SetBitArrayElement(size_t *array, size_t length, size_t i)
{
    array[BitArrayIndexToWordIndex(length, i)] |= BitArrayIndexToWordMask(i);
}

static inline void
ClearBitArrayElement(size_t *array, size_t length, size_t i)
{
    array[BitArrayIndexToWordIndex(length, i)] &= ~BitArrayIndexToWordMask(i);
}

static inline void
ClearAllBitArrayElements(size_t *array, size_t length)
{
    for (unsigned i = 0; i < length; ++i)
        array[i] = 0;
}

}  /* namespace js */
#endif  /* __cplusplus */

/*
 * JS_ROTATE_LEFT32
 *
 * There is no rotate operation in the C Language so the construct (a << 4) |
 * (a >> 28) is used instead. Most compilers convert this to a rotate
 * instruction but some versions of MSVC don't without a little help.  To get
 * MSVC to generate a rotate instruction, we have to use the _rotl intrinsic
 * and use a pragma to make _rotl inline.
 *
 * MSVC in VS2005 will do an inline rotate instruction on the above construct.
 */
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || \
    defined(_M_X64))
#include <stdlib.h>
#pragma intrinsic(_rotl)
#define JS_ROTATE_LEFT32(a, bits) _rotl(a, bits)
#else
#define JS_ROTATE_LEFT32(a, bits) (((a) << (bits)) | ((a) >> (32 - (bits))))
#endif

/* Static control-flow checks. */
#ifdef NS_STATIC_CHECKING
/* Trigger a control flow check to make sure that code flows through label */
inline __attribute__ ((unused)) void MUST_FLOW_THROUGH(const char *label) {}

/* Avoid unused goto-label warnings. */
# define MUST_FLOW_LABEL(label) goto label; label:

#else
# define MUST_FLOW_THROUGH(label)            ((void) 0)
# define MUST_FLOW_LABEL(label)
#endif

/* Crash diagnostics */
#ifdef DEBUG
# define JS_CRASH_DIAGNOSTICS 1
#endif
#ifdef JS_CRASH_DIAGNOSTICS
# define JS_POISON(p, val, size) memset((p), (val), (size))
# define JS_OPT_ASSERT(expr)                                                  \
    ((expr) ? (void)0 : MOZ_Assert(#expr, __FILE__, __LINE__))
# define JS_OPT_ASSERT_IF(cond, expr)                                         \
    ((!(cond) || (expr)) ? (void)0 : MOZ_Assert(#expr, __FILE__, __LINE__))
#else
# define JS_POISON(p, val, size) ((void) 0)
# define JS_OPT_ASSERT(expr) ((void) 0)
# define JS_OPT_ASSERT_IF(cond, expr) ((void) 0)
#endif

/* Basic stats */
#ifdef DEBUG
# define JS_BASIC_STATS 1
#endif
#ifdef JS_BASIC_STATS
# include <stdio.h>
typedef struct JSBasicStats {
    uint32_t    num;
    uint32_t    max;
    double      sum;
    double      sqsum;
    uint32_t    logscale;           /* logarithmic scale: 0 (linear), 2, 10 */
    uint32_t    hist[11];
} JSBasicStats;
# define JS_INIT_STATIC_BASIC_STATS  {0,0,0,0,0,{0,0,0,0,0,0,0,0,0,0,0}}
# define JS_BASIC_STATS_INIT(bs)     memset((bs), 0, sizeof(JSBasicStats))
# define JS_BASIC_STATS_ACCUM(bs,val)                                         \
    JS_BasicStatsAccum(bs, val)
# define JS_MeanAndStdDevBS(bs,sigma)                                         \
    JS_MeanAndStdDev((bs)->num, (bs)->sum, (bs)->sqsum, sigma)
extern void
JS_BasicStatsAccum(JSBasicStats *bs, uint32_t val);
extern double
JS_MeanAndStdDev(uint32_t num, double sum, double sqsum, double *sigma);
extern void
JS_DumpBasicStats(JSBasicStats *bs, const char *title, FILE *fp);
extern void
JS_DumpHistogram(JSBasicStats *bs, FILE *fp);
#else
# define JS_BASIC_STATS_ACCUM(bs,val)
#endif

/* A jsbitmap_t is a long integer that can be used for bitmaps. */
typedef size_t jsbitmap;
#define JS_TEST_BIT(_map,_bit)  ((_map)[(_bit)>>JS_BITS_PER_WORD_LOG2] &      \
                                 ((jsbitmap)1<<((_bit)&(JS_BITS_PER_WORD-1))))
#define JS_SET_BIT(_map,_bit)   ((_map)[(_bit)>>JS_BITS_PER_WORD_LOG2] |=     \
                                 ((jsbitmap)1<<((_bit)&(JS_BITS_PER_WORD-1))))
#define JS_CLEAR_BIT(_map,_bit) ((_map)[(_bit)>>JS_BITS_PER_WORD_LOG2] &=     \
                                 ~((jsbitmap)1<<((_bit)&(JS_BITS_PER_WORD-1))))

/* Wrapper for various macros to stop warnings coming from their expansions. */
#if defined(__clang__)
# define JS_SILENCE_UNUSED_VALUE_IN_EXPR(expr)                                \
    JS_BEGIN_MACRO                                                            \
        _Pragma("clang diagnostic push")                                      \
        _Pragma("clang diagnostic ignored \"-Wunused-value\"")                \
        expr;                                                                 \
        _Pragma("clang diagnostic pop")                                       \
    JS_END_MACRO
#elif (__GNUC__ >= 5) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
# define JS_SILENCE_UNUSED_VALUE_IN_EXPR(expr)                                \
    JS_BEGIN_MACRO                                                            \
        _Pragma("GCC diagnostic push")                                        \
        _Pragma("GCC diagnostic ignored \"-Wunused-but-set-variable\"")       \
        expr;                                                                 \
        _Pragma("GCC diagnostic pop")                                         \
    JS_END_MACRO
#else
# define JS_SILENCE_UNUSED_VALUE_IN_EXPR(expr)                                \
    JS_BEGIN_MACRO                                                            \
        expr;                                                                 \
    JS_END_MACRO
#endif

#endif /* jsutil_h___ */
