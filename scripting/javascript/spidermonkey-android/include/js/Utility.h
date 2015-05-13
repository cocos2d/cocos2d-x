/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=99 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef js_utility_h__
#define js_utility_h__

#include "mozilla/Assertions.h"
#include "mozilla/Attributes.h"
#include "mozilla/Scoped.h"

#include <stdlib.h>
#include <string.h>

#ifdef JS_OOM_DO_BACKTRACES
#include <stdio.h>
#include <execinfo.h>
#endif

#include "jstypes.h"

#include "js/TemplateLib.h"

/* The public JS engine namespace. */
namespace JS {}

/* The mozilla-shared reusable template/utility namespace. */
namespace mozilla {}

/* The private JS engine namespace. */
namespace js {

/* The private namespace is a superset of the public/shared namespaces. */
using namespace JS;

}  /* namespace js */

/*
 * Pattern used to overwrite freed memory. If you are accessing an object with
 * this pattern, you probably have a dangling pointer.
 */
#define JS_FREE_PATTERN 0xDA

#define JS_ASSERT(expr)           MOZ_ASSERT(expr)
#define JS_ASSERT_IF(cond, expr)  MOZ_ASSERT_IF(cond, expr)
#define JS_NOT_REACHED(reason)    MOZ_NOT_REACHED(reason)
#define JS_ALWAYS_TRUE(expr)      MOZ_ALWAYS_TRUE(expr)
#define JS_ALWAYS_FALSE(expr)     MOZ_ALWAYS_FALSE(expr)

#ifdef DEBUG
# ifdef JS_THREADSAFE
#  define JS_THREADSAFE_ASSERT(expr) JS_ASSERT(expr)
# else
#  define JS_THREADSAFE_ASSERT(expr) ((void) 0)
# endif
#else
# define JS_THREADSAFE_ASSERT(expr) ((void) 0)
#endif

#if defined(DEBUG)
# define JS_DIAGNOSTICS_ASSERT(expr) MOZ_ASSERT(expr)
#elif defined(JS_CRASH_DIAGNOSTICS)
# define JS_DIAGNOSTICS_ASSERT(expr) do { if (!(expr)) MOZ_CRASH(); } while(0)
#else
# define JS_DIAGNOSTICS_ASSERT(expr) ((void) 0)
#endif

#define JS_STATIC_ASSERT(cond)           MOZ_STATIC_ASSERT(cond, "JS_STATIC_ASSERT")
#define JS_STATIC_ASSERT_IF(cond, expr)  MOZ_STATIC_ASSERT_IF(cond, expr, "JS_STATIC_ASSERT_IF")

extern MOZ_NORETURN JS_PUBLIC_API(void)
JS_Assert(const char *s, const char *file, int ln);

/*
 * Abort the process in a non-graceful manner. This will cause a core file,
 * call to the debugger or other moral equivalent as well as causing the
 * entire process to stop.
 */
extern JS_PUBLIC_API(void) JS_Abort(void);

/*
 * Custom allocator support for SpiderMonkey
 */
#if defined JS_USE_CUSTOM_ALLOCATOR
# include "jscustomallocator.h"
#else
# ifdef DEBUG
/*
 * In order to test OOM conditions, when the shell command-line option
 * |-A NUM| is passed, we fail continuously after the NUM'th allocation.
 */
extern JS_PUBLIC_DATA(uint32_t) OOM_maxAllocations; /* set from shell/js.cpp */
extern JS_PUBLIC_DATA(uint32_t) OOM_counter; /* data race, who cares. */

#ifdef JS_OOM_DO_BACKTRACES
#define JS_OOM_BACKTRACE_SIZE 32
static JS_ALWAYS_INLINE void
PrintBacktrace()
{
    void* OOM_trace[JS_OOM_BACKTRACE_SIZE];
    char** OOM_traceSymbols = NULL;
    int32_t OOM_traceSize = 0;
    int32_t OOM_traceIdx = 0;
    OOM_traceSize = backtrace(OOM_trace, JS_OOM_BACKTRACE_SIZE);
    OOM_traceSymbols = backtrace_symbols(OOM_trace, OOM_traceSize);

    if (!OOM_traceSymbols)
        return;

    for (OOM_traceIdx = 0; OOM_traceIdx < OOM_traceSize; ++OOM_traceIdx) {
        fprintf(stderr, "#%d %s\n", OOM_traceIdx, OOM_traceSymbols[OOM_traceIdx]);
    }

    free(OOM_traceSymbols);
}

#define JS_OOM_EMIT_BACKTRACE() \
    do {\
        fprintf(stderr, "Forcing artificial memory allocation function failure:\n");\
	PrintBacktrace();\
    } while (0)
# else
#  define JS_OOM_EMIT_BACKTRACE() do {} while(0)
#endif /* JS_OOM_DO_BACKTRACES */

#  define JS_OOM_POSSIBLY_FAIL() \
    do \
    { \
        if (++OOM_counter > OOM_maxAllocations) { \
            JS_OOM_EMIT_BACKTRACE();\
            return NULL; \
        } \
    } while (0)

#  define JS_OOM_POSSIBLY_FAIL_REPORT(cx) \
    do \
    { \
        if (++OOM_counter > OOM_maxAllocations) { \
            JS_OOM_EMIT_BACKTRACE();\
            js_ReportOutOfMemory(cx);\
            return NULL; \
        } \
    } while (0)

# else
#  define JS_OOM_POSSIBLY_FAIL() do {} while(0)
#  define JS_OOM_POSSIBLY_FAIL_REPORT(cx) do {} while(0)
# endif /* DEBUG */

static JS_INLINE void* js_malloc(size_t bytes)
{
    JS_OOM_POSSIBLY_FAIL();
    return malloc(bytes);
}

static JS_INLINE void* js_calloc(size_t bytes)
{
    JS_OOM_POSSIBLY_FAIL();
    return calloc(bytes, 1);
}

static JS_INLINE void* js_realloc(void* p, size_t bytes)
{
    JS_OOM_POSSIBLY_FAIL();
    return realloc(p, bytes);
}

static JS_INLINE void js_free(void* p)
{
    free(p);
}
#endif/* JS_USE_CUSTOM_ALLOCATOR */

JS_BEGIN_EXTERN_C

/*
 * Replace bit-scanning code sequences with CPU-specific instructions to
 * speedup calculations of ceiling/floor log2.
 *
 * With GCC 3.4 or later we can use __builtin_clz for that, see bug 327129.
 *
 * SWS: Added MSVC intrinsic bitscan support.  See bugs 349364 and 356856.
 */
#if defined(_WIN32) && (_MSC_VER >= 1300) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64))

unsigned char _BitScanForward(unsigned long * Index, unsigned long Mask);
unsigned char _BitScanReverse(unsigned long * Index, unsigned long Mask);
# pragma intrinsic(_BitScanForward,_BitScanReverse)

__forceinline static int
__BitScanForward32(unsigned int val)
{
    unsigned long idx;

    _BitScanForward(&idx, (unsigned long)val);
    return (int)idx;
}
__forceinline static int
__BitScanReverse32(unsigned int val)
{
    unsigned long idx;

    _BitScanReverse(&idx, (unsigned long)val);
    return (int)(31-idx);
}
# define js_bitscan_ctz32(val)  __BitScanForward32(val)
# define js_bitscan_clz32(val)  __BitScanReverse32(val)
# define JS_HAS_BUILTIN_BITSCAN32

#if defined(_M_AMD64) || defined(_M_X64)
unsigned char _BitScanForward64(unsigned long * Index, unsigned __int64 Mask);
unsigned char _BitScanReverse64(unsigned long * Index, unsigned __int64 Mask);
# pragma intrinsic(_BitScanForward64,_BitScanReverse64)

__forceinline static int
__BitScanForward64(unsigned __int64 val)
{
    unsigned long idx;

    _BitScanForward64(&idx, val);
    return (int)idx;
}
__forceinline static int
__BitScanReverse64(unsigned __int64 val)
{
    unsigned long idx;

    _BitScanReverse64(&idx, val);
    return (int)(63-idx);
}
# define js_bitscan_ctz64(val)  __BitScanForward64(val)
# define js_bitscan_clz64(val)  __BitScanReverse64(val)
# define JS_HAS_BUILTIN_BITSCAN64
#endif
#elif (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)

# define js_bitscan_ctz32(val)  __builtin_ctz(val)
# define js_bitscan_clz32(val)  __builtin_clz(val)
# define JS_HAS_BUILTIN_BITSCAN32
# if (JS_BYTES_PER_WORD == 8)
#  define js_bitscan_ctz64(val)  __builtin_ctzll(val)
#  define js_bitscan_clz64(val)  __builtin_clzll(val)
#  define JS_HAS_BUILTIN_BITSCAN64
# endif

#endif

/*
** Macro version of JS_CeilingLog2: Compute the log of the least power of
** 2 greater than or equal to _n. The result is returned in _log2.
*/
#ifdef JS_HAS_BUILTIN_BITSCAN32
/*
 * Use intrinsic function or count-leading-zeros to calculate ceil(log2(_n)).
 * The macro checks for "n <= 1" and not "n != 0" as js_bitscan_clz32(0) is
 * undefined.
 */
# define JS_CEILING_LOG2(_log2,_n)                                            \
    JS_BEGIN_MACRO                                                            \
        unsigned int j_ = (unsigned int)(_n);                                 \
        (_log2) = (j_ <= 1 ? 0 : 32 - js_bitscan_clz32(j_ - 1));              \
    JS_END_MACRO
#else
# define JS_CEILING_LOG2(_log2,_n)                                            \
    JS_BEGIN_MACRO                                                            \
        uint32_t j_ = (uint32_t)(_n);                                         \
        (_log2) = 0;                                                          \
        if ((j_) & ((j_)-1))                                                  \
            (_log2) += 1;                                                     \
        if ((j_) >> 16)                                                       \
            (_log2) += 16, (j_) >>= 16;                                       \
        if ((j_) >> 8)                                                        \
            (_log2) += 8, (j_) >>= 8;                                         \
        if ((j_) >> 4)                                                        \
            (_log2) += 4, (j_) >>= 4;                                         \
        if ((j_) >> 2)                                                        \
            (_log2) += 2, (j_) >>= 2;                                         \
        if ((j_) >> 1)                                                        \
            (_log2) += 1;                                                     \
    JS_END_MACRO
#endif

/*
** Macro version of JS_FloorLog2: Compute the log of the greatest power of
** 2 less than or equal to _n. The result is returned in _log2.
**
** This is equivalent to finding the highest set bit in the word.
*/
#ifdef JS_HAS_BUILTIN_BITSCAN32
/*
 * Use js_bitscan_clz32 or count-leading-zeros to calculate floor(log2(_n)).
 * Since js_bitscan_clz32(0) is undefined, the macro set the loweset bit to 1
 * to ensure 0 result when _n == 0.
 */
# define JS_FLOOR_LOG2(_log2,_n)                                              \
    JS_BEGIN_MACRO                                                            \
        (_log2) = 31 - js_bitscan_clz32(((unsigned int)(_n)) | 1);            \
    JS_END_MACRO
#else
# define JS_FLOOR_LOG2(_log2,_n)                                              \
    JS_BEGIN_MACRO                                                            \
        uint32_t j_ = (uint32_t)(_n);                                         \
        (_log2) = 0;                                                          \
        if ((j_) >> 16)                                                       \
            (_log2) += 16, (j_) >>= 16;                                       \
        if ((j_) >> 8)                                                        \
            (_log2) += 8, (j_) >>= 8;                                         \
        if ((j_) >> 4)                                                        \
            (_log2) += 4, (j_) >>= 4;                                         \
        if ((j_) >> 2)                                                        \
            (_log2) += 2, (j_) >>= 2;                                         \
        if ((j_) >> 1)                                                        \
            (_log2) += 1;                                                     \
    JS_END_MACRO
#endif

#if JS_BYTES_PER_WORD == 4
# ifdef JS_HAS_BUILTIN_BITSCAN32
#  define js_FloorLog2wImpl(n)                                                \
    ((size_t)(JS_BITS_PER_WORD - 1 - js_bitscan_clz32(n)))
# else
JS_PUBLIC_API(size_t) js_FloorLog2wImpl(size_t n);
# endif
#elif JS_BYTES_PER_WORD == 8
# ifdef JS_HAS_BUILTIN_BITSCAN64
#  define js_FloorLog2wImpl(n)                                                \
    ((size_t)(JS_BITS_PER_WORD - 1 - js_bitscan_clz64(n)))
# else
JS_PUBLIC_API(size_t) js_FloorLog2wImpl(size_t n);
# endif
#else
# error "NOT SUPPORTED"
#endif

JS_END_EXTERN_C

/*
 * Internal function.
 * Compute the log of the least power of 2 greater than or equal to n. This is
 * a version of JS_CeilingLog2 that operates on unsigned integers with
 * CPU-dependant size.
 */
#define JS_CEILING_LOG2W(n) ((n) <= 1 ? 0 : 1 + JS_FLOOR_LOG2W((n) - 1))

/*
 * Internal function.
 * Compute the log of the greatest power of 2 less than or equal to n.
 * This is a version of JS_FloorLog2 that operates on unsigned integers with
 * CPU-dependant size and requires that n != 0.
 */
static MOZ_ALWAYS_INLINE size_t
JS_FLOOR_LOG2W(size_t n)
{
    JS_ASSERT(n != 0);
    return js_FloorLog2wImpl(n);
}

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

#include <new>

/*
 * Low-level memory management in SpiderMonkey:
 *
 *  ** Do not use the standard malloc/free/realloc: SpiderMonkey allows these
 *     to be redefined (via JS_USE_CUSTOM_ALLOCATOR) and Gecko even #define's
 *     these symbols.
 *
 *  ** Do not use the builtin C++ operator new and delete: these throw on
 *     error and we cannot override them not to.
 *
 * Allocation:
 *
 * - If the lifetime of the allocation is tied to the lifetime of a GC-thing
 *   (that is, finalizing the GC-thing will free the allocation), call one of
 *   the following functions:
 *
 *     JSContext::{malloc_,realloc_,calloc_,new_}
 *     JSRuntime::{malloc_,realloc_,calloc_,new_}
 *
 *   These functions accumulate the number of bytes allocated which is used as
 *   part of the GC-triggering heuristic.
 *
 *   The difference between the JSContext and JSRuntime versions is that the
 *   cx version reports an out-of-memory error on OOM. (This follows from the
 *   general SpiderMonkey idiom that a JSContext-taking function reports its
 *   own errors.)
 *
 * - Otherwise, use js_malloc/js_realloc/js_calloc/js_free/js_new
 *
 * Deallocation:
 *
 * - Ordinarily, use js_free/js_delete.
 *
 * - For deallocations during GC finalization, use one of the following
 *   operations on the FreeOp provided to the finalizer:
 *
 *     FreeOp::{free_,delete_}
 *
 *   The advantage of these operations is that the memory is batched and freed
 *   on another thread.
 */

#define JS_NEW_BODY(allocator, t, parms)                                       \
    void *memory = allocator(sizeof(t));                                       \
    return memory ? new(memory) t parms : NULL;

/*
 * Given a class which should provide 'new' methods, add
 * JS_DECLARE_NEW_METHODS (see JSContext for a usage example). This
 * adds news with up to 12 parameters. Add more versions of new below if
 * you need more than 12 parameters.
 *
 * Note: Do not add a ; at the end of a use of JS_DECLARE_NEW_METHODS,
 * or the build will break.
 */
#define JS_DECLARE_NEW_METHODS(NEWNAME, ALLOCATOR, QUALIFIERS)\
    template <class T>\
    QUALIFIERS T *NEWNAME() {\
        JS_NEW_BODY(ALLOCATOR, T, ())\
    }\
\
    template <class T, class P1>\
    QUALIFIERS T *NEWNAME(P1 p1) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1))\
    }\
\
    template <class T, class P1, class P2>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2))\
    }\
\
    template <class T, class P1, class P2, class P3>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11, class P12>\
    QUALIFIERS T *NEWNAME(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12))\
    }\

JS_DECLARE_NEW_METHODS(js_new, js_malloc, static JS_ALWAYS_INLINE)

template <class T>
static JS_ALWAYS_INLINE void
js_delete(T *p)
{
    if (p) {
        p->~T();
        js_free(p);
    }
}

template <class T>
static JS_ALWAYS_INLINE T *
js_pod_malloc()
{
    return (T *)js_malloc(sizeof(T));
}

template <class T>
static JS_ALWAYS_INLINE T *
js_pod_calloc()
{
    return (T *)js_calloc(sizeof(T));
}

template <class T>
static JS_ALWAYS_INLINE T *
js_pod_malloc(size_t numElems)
{
    if (numElems & js::tl::MulOverflowMask<sizeof(T)>::result)
        return NULL;
    return (T *)js_malloc(numElems * sizeof(T));
}

template <class T>
static JS_ALWAYS_INLINE T *
js_pod_calloc(size_t numElems)
{
    if (numElems & js::tl::MulOverflowMask<sizeof(T)>::result)
        return NULL;
    return (T *)js_calloc(numElems * sizeof(T));
}

namespace js {

template<typename T>
struct ScopedFreePtrTraits
{
    typedef T* type;
    static T* empty() { return NULL; }
    static void release(T* ptr) { js_free(ptr); }
};
SCOPED_TEMPLATE(ScopedJSFreePtr, ScopedFreePtrTraits)

template <typename T>
struct ScopedDeletePtrTraits : public ScopedFreePtrTraits<T>
{
    static void release(T *ptr) { js_delete(ptr); }
};
SCOPED_TEMPLATE(ScopedJSDeletePtr, ScopedDeletePtrTraits)

} /* namespace js */

namespace js {

/*
 * "Move" References
 *
 * Some types can be copied much more efficiently if we know the original's
 * value need not be preserved --- that is, if we are doing a "move", not a
 * "copy". For example, if we have:
 *
 *   Vector<T> u;
 *   Vector<T> v(u);
 *
 * the constructor for v must apply a copy constructor to each element of u ---
 * taking time linear in the length of u. However, if we know we will not need u
 * any more once v has been initialized, then we could initialize v very
 * efficiently simply by stealing u's dynamically allocated buffer and giving it
 * to v --- a constant-time operation, regardless of the size of u.
 *
 * Moves often appear in container implementations. For example, when we append
 * to a vector, we may need to resize its buffer. This entails moving each of
 * its extant elements from the old, smaller buffer to the new, larger buffer.
 * But once the elements have been migrated, we're just going to throw away the
 * old buffer; we don't care if they still have their values. So if the vector's
 * element type can implement "move" more efficiently than "copy", the vector
 * resizing should by all means use a "move" operation. Hash tables also need to
 * be resized.
 *
 * The details of the optimization, and whether it's worth applying, vary from
 * one type to the next. And while some constructor calls are moves, many really
 * are copies, and can't be optimized this way. So we need:
 *
 * 1) a way for a particular invocation of a copy constructor to say that it's
 *    really a move, and that the value of the original isn't important
 *    afterwards (althought it must still be safe to destroy); and
 *
 * 2) a way for a type (like Vector) to announce that it can be moved more
 *    efficiently than it can be copied, and provide an implementation of that
 *    move operation.
 *
 * The Move(T &) function takes a reference to a T, and returns an MoveRef<T>
 * referring to the same value; that's 1). An MoveRef<T> is simply a reference
 * to a T, annotated to say that a copy constructor applied to it may move that
 * T, instead of copying it. Finally, a constructor that accepts an MoveRef<T>
 * should perform a more efficient move, instead of a copy, providing 2).
 *
 * So, where we might define a copy constructor for a class C like this:
 *
 *   C(const C &rhs) { ... copy rhs to this ... }
 *
 * we would declare a move constructor like this:
 *
 *   C(MoveRef<C> rhs) { ... move rhs to this ... }
 *
 * And where we might perform a copy like this:
 *
 *   C c2(c1);
 *
 * we would perform a move like this:
 *
 *   C c2(Move(c1))
 *
 * Note that MoveRef<T> implicitly converts to T &, so you can pass an
 * MoveRef<T> to an ordinary copy constructor for a type that doesn't support a
 * special move constructor, and you'll just get a copy. This means that
 * templates can use Move whenever they know they won't use the original value
 * any more, even if they're not sure whether the type at hand has a specialized
 * move constructor. If it doesn't, the MoveRef<T> will just convert to a T &,
 * and the ordinary copy constructor will apply.
 *
 * A class with a move constructor can also provide a move assignment operator,
 * which runs this's destructor, and then applies the move constructor to
 * *this's memory. A typical definition:
 *
 *   C &operator=(MoveRef<C> rhs) {
 *     this->~C();
 *     new(this) C(rhs);
 *     return *this;
 *   }
 *
 * With that in place, one can write move assignments like this:
 *
 *   c2 = Move(c1);
 *
 * This destroys c1, moves c1's value to c2, and leaves c1 in an undefined but
 * destructible state.
 *
 * This header file defines MoveRef and Move in the js namespace. It's up to
 * individual containers to annotate moves as such, by calling Move; and it's up
 * to individual types to define move constructors.
 *
 * One hint: if you're writing a move constructor where the type has members
 * that should be moved themselves, it's much nicer to write this:
 *
 *   C(MoveRef<C> c) : x(c->x), y(c->y) { }
 *
 * than the equivalent:
 *
 *   C(MoveRef<C> c) { new(&x) X(c->x); new(&y) Y(c->y); }
 *
 * especially since GNU C++ fails to notice that this does indeed initialize x
 * and y, which may matter if they're const.
 */
template<typename T>
class MoveRef {
  public:
    typedef T Referent;
    explicit MoveRef(T &t) : pointer(&t) { }
    T &operator*()  const { return *pointer; }
    T *operator->() const { return  pointer; }
    operator T& ()   const { return *pointer; }
  private:
    T *pointer;
};

template<typename T>
MoveRef<T> Move(T &t) { return MoveRef<T>(t); }

template<typename T>
MoveRef<T> Move(const T &t) { return MoveRef<T>(const_cast<T &>(t)); }

/* Useful for implementing containers that assert non-reentrancy */
class ReentrancyGuard
{
    /* ReentrancyGuard is not copyable. */
    ReentrancyGuard(const ReentrancyGuard &);
    void operator=(const ReentrancyGuard &);

#ifdef DEBUG
    bool &entered;
#endif
  public:
    template <class T>
#ifdef DEBUG
    ReentrancyGuard(T &obj)
      : entered(obj.entered)
#else
    ReentrancyGuard(T &/*obj*/)
#endif
    {
#ifdef DEBUG
        JS_ASSERT(!entered);
        entered = true;
#endif
    }
    ~ReentrancyGuard()
    {
#ifdef DEBUG
        entered = false;
#endif
    }
};

template <class T>
JS_ALWAYS_INLINE static void
Swap(T &t, T &u)
{
    T tmp(Move(t));
    t = Move(u);
    u = Move(tmp);
}

/*
 * Round x up to the nearest power of 2.  This function assumes that the most
 * significant bit of x is not set, which would lead to overflow.
 */
JS_ALWAYS_INLINE size_t
RoundUpPow2(size_t x)
{
    return size_t(1) << JS_CEILING_LOG2W(x);
}

/* Integral types for all hash functions. */
typedef uint32_t HashNumber;
const unsigned HashNumberSizeBits = 32;

namespace detail {

/*
 * Given a raw hash code, h, return a number that can be used to select a hash
 * bucket.
 *
 * This function aims to produce as uniform an output distribution as possible,
 * especially in the most significant (leftmost) bits, even though the input
 * distribution may be highly nonrandom, given the constraints that this must
 * be deterministic and quick to compute.
 *
 * Since the leftmost bits of the result are best, the hash bucket index is
 * computed by doing ScrambleHashCode(h) / (2^32/N) or the equivalent
 * right-shift, not ScrambleHashCode(h) % N or the equivalent bit-mask.
 *
 * FIXME: OrderedHashTable uses a bit-mask; see bug 775896.
 */
inline HashNumber
ScrambleHashCode(HashNumber h)
{
    /*
     * Simply returning h would not cause any hash tables to produce wrong
     * answers. But it can produce pathologically bad performance: The caller
     * right-shifts the result, keeping only the highest bits. The high bits of
     * hash codes are very often completely entropy-free. (So are the lowest
     * bits.)
     *
     * So we use Fibonacci hashing, as described in Knuth, The Art of Computer
     * Programming, 6.4. This mixes all the bits of the input hash code h.
     * 
     * The value of goldenRatio is taken from the hex
     * expansion of the golden ratio, which starts 1.9E3779B9....
     * This value is especially good if values with consecutive hash codes
     * are stored in a hash table; see Knuth for details.
     */
    static const HashNumber goldenRatio = 0x9E3779B9U;
    return h * goldenRatio;
}

} /* namespace detail */

} /* namespace js */

namespace JS {

/*
 * Methods for poisoning GC heap pointer words and checking for poisoned words.
 * These are in this file for use in Value methods and so forth.
 *
 * If the moving GC hazard analysis is in use and detects a non-rooted stack
 * pointer to a GC thing, one byte of that pointer is poisoned to refer to an
 * invalid location. For both 32 bit and 64 bit systems, the fourth byte of the
 * pointer is overwritten, to reduce the likelihood of accidentally changing
 * a live integer value.
 */

inline void PoisonPtr(void *v)
{
#if defined(JSGC_ROOT_ANALYSIS) && defined(DEBUG)
    uint8_t *ptr = (uint8_t *) v + 3;
    *ptr = JS_FREE_PATTERN;
#endif
}

template <typename T>
inline bool IsPoisonedPtr(T *v)
{
#if defined(JSGC_ROOT_ANALYSIS) && defined(DEBUG)
    uint32_t mask = uintptr_t(v) & 0xff000000;
    return mask == uint32_t(JS_FREE_PATTERN << 24);
#else
    return false;
#endif
}

}

/*
 * This is SpiderMonkey's equivalent to |nsMallocSizeOfFun|.
 */
typedef size_t(*JSMallocSizeOfFun)(const void *p);

/* sixgill annotation defines */
#ifndef HAVE_STATIC_ANNOTATIONS
# define HAVE_STATIC_ANNOTATIONS
# ifdef XGILL_PLUGIN
#  define STATIC_PRECONDITION(COND)         __attribute__((precondition(#COND)))
#  define STATIC_PRECONDITION_ASSUME(COND)  __attribute__((precondition_assume(#COND)))
#  define STATIC_POSTCONDITION(COND)        __attribute__((postcondition(#COND)))
#  define STATIC_POSTCONDITION_ASSUME(COND) __attribute__((postcondition_assume(#COND)))
#  define STATIC_INVARIANT(COND)            __attribute__((invariant(#COND)))
#  define STATIC_INVARIANT_ASSUME(COND)     __attribute__((invariant_assume(#COND)))
#  define STATIC_PASTE2(X,Y) X ## Y
#  define STATIC_PASTE1(X,Y) STATIC_PASTE2(X,Y)
#  define STATIC_ASSERT(COND)                        \
  JS_BEGIN_MACRO                                     \
    __attribute__((assert_static(#COND), unused))    \
    int STATIC_PASTE1(assert_static_, __COUNTER__);  \
  JS_END_MACRO
#  define STATIC_ASSUME(COND)                        \
  JS_BEGIN_MACRO                                     \
    __attribute__((assume_static(#COND), unused))    \
    int STATIC_PASTE1(assume_static_, __COUNTER__);  \
  JS_END_MACRO
#  define STATIC_ASSERT_RUNTIME(COND)                       \
  JS_BEGIN_MACRO                                            \
    __attribute__((assert_static_runtime(#COND), unused))   \
    int STATIC_PASTE1(assert_static_runtime_, __COUNTER__); \
  JS_END_MACRO
# else /* XGILL_PLUGIN */
#  define STATIC_PRECONDITION(COND)          /* nothing */
#  define STATIC_PRECONDITION_ASSUME(COND)   /* nothing */
#  define STATIC_POSTCONDITION(COND)         /* nothing */
#  define STATIC_POSTCONDITION_ASSUME(COND)  /* nothing */
#  define STATIC_INVARIANT(COND)             /* nothing */
#  define STATIC_INVARIANT_ASSUME(COND)      /* nothing */
#  define STATIC_ASSERT(COND)          JS_BEGIN_MACRO /* nothing */ JS_END_MACRO
#  define STATIC_ASSUME(COND)          JS_BEGIN_MACRO /* nothing */ JS_END_MACRO
#  define STATIC_ASSERT_RUNTIME(COND)  JS_BEGIN_MACRO /* nothing */ JS_END_MACRO
# endif /* XGILL_PLUGIN */
# define STATIC_SKIP_INFERENCE STATIC_INVARIANT(skip_inference())
#endif /* HAVE_STATIC_ANNOTATIONS */

#endif /* js_utility_h__ */
