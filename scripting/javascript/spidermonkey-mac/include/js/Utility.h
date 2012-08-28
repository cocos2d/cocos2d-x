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

#ifndef js_utility_h__
#define js_utility_h__

#include "mozilla/Assertions.h"

#include <stdlib.h>
#include <string.h>

#ifdef JS_OOM_DO_BACKTRACES
#include <stdio.h>
#include <execinfo.h>
#endif

#include "jstypes.h"

#ifdef __cplusplus

/* The public JS engine namespace. */
namespace JS {}

/* The mozilla-shared reusable template/utility namespace. */
namespace mozilla {}

/* The private JS engine namespace. */
namespace js {

/* The private namespace is a superset of the public/shared namespaces. */
using namespace JS;
using namespace mozilla;

}  /* namespace js */
#endif  /* __cplusplus */

JS_BEGIN_EXTERN_C

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

#define JS_STATIC_ASSERT(cond)           MOZ_STATIC_ASSERT(cond, "JS_STATIC_ASSERT")
#define JS_STATIC_ASSERT_IF(cond, expr)  MOZ_STATIC_ASSERT_IF(cond, expr, "JS_STATIC_ASSERT_IF")

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

# else
#  define JS_OOM_POSSIBLY_FAIL() do {} while(0)
# endif

/*
 * SpiderMonkey code should not be calling these allocation functions directly.
 * Instead, all calls should go through JSRuntime, JSContext or OffTheBooks.
 * However, js_free() can be called directly.
 */
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
#define JS_FLOOR_LOG2W(n) (JS_ASSERT((n) != 0), js_FloorLog2wImpl(n))

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

#ifdef __cplusplus
#include <new>

/*
 * User guide to memory management within SpiderMonkey:
 *
 * Quick tips:
 *
 *   Allocation:
 *   - Prefer to allocate using JSContext:
 *       cx->{malloc_,realloc_,calloc_,new_,array_new}
 *
 *   - If no JSContext is available, use a JSRuntime:
 *       rt->{malloc_,realloc_,calloc_,new_,array_new}
 *
 *   - As a last resort, use unaccounted allocation ("OffTheBooks"):
 *       js::OffTheBooks::{malloc_,realloc_,calloc_,new_,array_new}
 *
 *   Deallocation:
 *   - When the deallocation occurs on a slow path, use:
 *       Foreground::{free_,delete_,array_delete}
 *
 *   - Otherwise deallocate on a background thread using a JSContext:
 *       cx->{free_,delete_,array_delete}
 *
 *   - If no JSContext is available, use a JSRuntime:
 *       rt->{free_,delete_,array_delete}
 *
 *   - As a last resort, use UnwantedForeground deallocation:
 *       js::UnwantedForeground::{free_,delete_,array_delete}
 *
 * General tips:
 *
 *   - Mixing and matching these allocators is allowed (you may free memory
 *     allocated by any allocator, with any deallocator).
 *
 *   - Never, ever use normal C/C++ memory management:
 *       malloc, free, new, new[], delete, operator new, etc.
 *
 *   - Never, ever use low-level SpiderMonkey allocators:
 *       js_malloc(), js_free(), js_calloc(), js_realloc()
 *     Their use is reserved for the other memory managers.
 *
 *   - Classes which have private constructors or destructors should have
 *     JS_DECLARE_ALLOCATION_FRIENDS_FOR_PRIVATE_CONSTRUCTOR added to their
 *     declaration.
 *
 * Details:
 *
 *   Using vanilla new/new[] is unsafe in SpiderMonkey because they throw on
 *   failure instead of returning NULL, which is what SpiderMonkey expects.
 *   (Even overriding them is unsafe, as the system's C++ runtime library may
 *   throw, which we do not support. We also can't just use the 'nothrow'
 *   variant of new/new[], because we want to mediate *all* allocations
 *   within SpiderMonkey, to satisfy any embedders using
 *   JS_USE_CUSTOM_ALLOCATOR.)
 *
 *   JSContexts and JSRuntimes keep track of memory allocated, and use this
 *   accounting to schedule GC. OffTheBooks does not. We'd like to remove
 *   OffTheBooks allocations as much as possible (bug 636558).
 *
 *   On allocation failure, a JSContext correctly reports an error, which a
 *   JSRuntime and OffTheBooks does not.
 *
 *   A JSContext deallocates in a background thread. A JSRuntime might
 *   deallocate in the background in the future, but does not now. Foreground
 *   deallocation is preferable on slow paths. UnwantedForeground deallocations
 *   occur where we have no JSContext or JSRuntime, and the deallocation is not
 *   on a slow path. We want to remove UnwantedForeground deallocations (bug
 *   636561).
 *
 *   JS_DECLARE_ALLOCATION_FRIENDS_FOR_PRIVATE_CONSTRUCTOR makes the allocation
 *   classes friends with your class, giving them access to private
 *   constructors and destructors.
 *
 *   |make check| does a source level check on the number of uses OffTheBooks,
 *   UnwantedForeground, js_malloc, js_free etc, to prevent regressions. If you
 *   really must add one, update Makefile.in, and run |make check|.
 *
 *   |make check| also statically prevents the use of vanilla new/new[].
 */

#define JS_NEW_BODY(allocator, t, parms)                                       \
    void *memory = allocator(sizeof(t));                                       \
    return memory ? new(memory) t parms : NULL;

/*
 * Given a class which should provide new_() methods, add
 * JS_DECLARE_NEW_METHODS (see JSContext for a usage example). This
 * adds new_()s with up to 12 parameters. Add more versions of new_ below if
 * you need more than 12 parameters.
 *
 * Note: Do not add a ; at the end of a use of JS_DECLARE_NEW_METHODS,
 * or the build will break.
 */
#define JS_DECLARE_NEW_METHODS(ALLOCATOR, QUALIFIERS)\
    template <class T>\
    QUALIFIERS T *new_() {\
        JS_NEW_BODY(ALLOCATOR, T, ())\
    }\
\
    template <class T, class P1>\
    QUALIFIERS T *new_(P1 p1) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1))\
    }\
\
    template <class T, class P1, class P2>\
    QUALIFIERS T *new_(P1 p1, P2 p2) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2))\
    }\
\
    template <class T, class P1, class P2, class P3>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11))\
    }\
\
    template <class T, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10, class P11, class P12>\
    QUALIFIERS T *new_(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, P9 p9, P10 p10, P11 p11, P12 p12) {\
        JS_NEW_BODY(ALLOCATOR, T, (p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12))\
    }\
    static const int JSMinAlignment = 8;\
    template <class T>\
    QUALIFIERS T *array_new(size_t n) {\
        /* The length is stored just before the vector memory. */\
        uint64_t numBytes64 = uint64_t(JSMinAlignment) + uint64_t(sizeof(T)) * uint64_t(n);\
        size_t numBytes = size_t(numBytes64);\
        if (numBytes64 != numBytes) {\
            JS_ASSERT(0);   /* we want to know if this happens in debug builds */\
            return NULL;\
        }\
        void *memory = ALLOCATOR(numBytes);\
        if (!memory)\
            return NULL;\
        *(size_t *)memory = n;\
        memory = (void*)(uintptr_t(memory) + JSMinAlignment);\
        return new(memory) T[n];\
    }\


#define JS_DECLARE_DELETE_METHODS(DEALLOCATOR, QUALIFIERS)\
    template <class T>\
    QUALIFIERS void delete_(T *p) {\
        if (p) {\
            p->~T();\
            DEALLOCATOR(p);\
        }\
    }\
\
    template <class T>\
    QUALIFIERS void array_delete(T *p) {\
        if (p) {\
            void* p0 = (void *)(uintptr_t(p) - js::OffTheBooks::JSMinAlignment);\
            size_t n = *(size_t *)p0;\
            for (size_t i = 0; i < n; i++)\
                (p + i)->~T();\
            DEALLOCATOR(p0);\
        }\
    }


/*
 * In general, all allocations should go through a JSContext or JSRuntime, so
 * that the garbage collector knows how much memory has been allocated. In
 * cases where it is difficult to use a JSContext or JSRuntime, OffTheBooks can
 * be used, though this is undesirable.
 */
namespace js {

class OffTheBooks {
public:
    JS_DECLARE_NEW_METHODS(::js_malloc, JS_ALWAYS_INLINE static)

    static JS_INLINE void* malloc_(size_t bytes) {
        return ::js_malloc(bytes);
    }

    static JS_INLINE void* calloc_(size_t bytes) {
        return ::js_calloc(bytes);
    }

    static JS_INLINE void* realloc_(void* p, size_t bytes) {
        return ::js_realloc(p, bytes);
    }
};

/*
 * We generally prefer deallocating using JSContext because it can happen in
 * the background. On slow paths, we may prefer foreground allocation.
 */
class Foreground {
public:
    /* See parentheses comment above. */
    static JS_ALWAYS_INLINE void free_(void* p) {
        ::js_free(p);
    }

    JS_DECLARE_DELETE_METHODS(::js_free, JS_ALWAYS_INLINE static)
};

class UnwantedForeground : public Foreground {
};

} /* namespace js */

/*
 * Note lack of ; in JSRuntime below. This is intentional so "calling" this
 * looks "normal".
 */
#define JS_DECLARE_ALLOCATION_FRIENDS_FOR_PRIVATE_CONSTRUCTOR \
    friend class js::OffTheBooks;\
    friend class js::Foreground;\
    friend class js::UnwantedForeground;\
    friend struct ::JSContext;\
    friend struct ::JSRuntime

/*
 * The following classes are designed to cause assertions to detect
 * inadvertent use of guard objects as temporaries.  In other words,
 * when we have a guard object whose only purpose is its constructor and
 * destructor (and is never otherwise referenced), the intended use
 * might be:
 *     JSAutoTempValueRooter tvr(cx, 1, &val);
 * but is is easy to accidentally write:
 *     JSAutoTempValueRooter(cx, 1, &val);
 * which compiles just fine, but runs the destructor well before the
 * intended time.
 *
 * They work by adding (#ifdef DEBUG) an additional parameter to the
 * guard object's constructor, with a default value, so that users of
 * the guard object's API do not need to do anything.  The default value
 * of this parameter is a temporary object.  C++ (ISO/IEC 14882:1998),
 * section 12.2 [class.temporary], clauses 4 and 5 seem to assume a
 * guarantee that temporaries are destroyed in the reverse of their
 * construction order, but I actually can't find a statement that that
 * is true in the general case (beyond the two specific cases mentioned
 * there).  However, it seems to be true.
 *
 * These classes are intended to be used only via the macros immediately
 * below them:
 *   JS_DECL_USE_GUARD_OBJECT_NOTIFIER declares (ifdef DEBUG) a member
 *     variable, and should be put where a declaration of a private
 *     member variable would be placed.
 *   JS_GUARD_OBJECT_NOTIFIER_PARAM should be placed at the end of the
 *     parameters to each constructor of the guard object; it declares
 *     (ifdef DEBUG) an additional parameter.
 *   JS_GUARD_OBJECT_NOTIFIER_INIT is a statement that belongs in each
 *     constructor.  It uses the parameter declared by
 *     JS_GUARD_OBJECT_NOTIFIER_PARAM.
 */
#ifdef DEBUG
class JS_FRIEND_API(JSGuardObjectNotifier)
{
private:
    bool* mStatementDone;
public:
    JSGuardObjectNotifier() : mStatementDone(NULL) {}

    ~JSGuardObjectNotifier() {
        *mStatementDone = true;
    }

    void setStatementDone(bool *aStatementDone) {
        mStatementDone = aStatementDone;
    }
};

class JS_FRIEND_API(JSGuardObjectNotificationReceiver)
{
private:
    bool mStatementDone;
public:
    JSGuardObjectNotificationReceiver() : mStatementDone(false) {}

    ~JSGuardObjectNotificationReceiver() {
        /*
         * Assert that the guard object was not used as a temporary.
         * (Note that this assert might also fire if Init is not called
         * because the guard object's implementation is not using the
         * above macros correctly.)
         */
        JS_ASSERT(mStatementDone);
    }

    void Init(const JSGuardObjectNotifier &aNotifier) {
        /*
         * aNotifier is passed as a const reference so that we can pass a
         * temporary, but we really intend it as non-const
         */
        const_cast<JSGuardObjectNotifier&>(aNotifier).
            setStatementDone(&mStatementDone);
    }
};

#define JS_DECL_USE_GUARD_OBJECT_NOTIFIER \
    JSGuardObjectNotificationReceiver _mCheckNotUsedAsTemporary;
#define JS_GUARD_OBJECT_NOTIFIER_PARAM \
    , const JSGuardObjectNotifier& _notifier = JSGuardObjectNotifier()
#define JS_GUARD_OBJECT_NOTIFIER_PARAM_NO_INIT \
    , const JSGuardObjectNotifier& _notifier
#define JS_GUARD_OBJECT_NOTIFIER_PARAM0 \
    const JSGuardObjectNotifier& _notifier = JSGuardObjectNotifier()
#define JS_GUARD_OBJECT_NOTIFIER_INIT \
    JS_BEGIN_MACRO _mCheckNotUsedAsTemporary.Init(_notifier); JS_END_MACRO

#else /* defined(DEBUG) */

#define JS_DECL_USE_GUARD_OBJECT_NOTIFIER
#define JS_GUARD_OBJECT_NOTIFIER_PARAM
#define JS_GUARD_OBJECT_NOTIFIER_PARAM_NO_INIT
#define JS_GUARD_OBJECT_NOTIFIER_PARAM0
#define JS_GUARD_OBJECT_NOTIFIER_INIT JS_BEGIN_MACRO JS_END_MACRO

#endif /* !defined(DEBUG) */

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
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    /*
     * If MoveRef is used in a rvalue position (which is expected), we can
     * end up in a situation where, without this ifdef, we would try to pass
     * a T& to a move constructor, which fails. It is not clear if the compiler
     * should instead use the copy constructor, but for now this lets us build
     * with clang. See bug 689066 and llvm.org/pr11003 for the details.
     * Note: We can probably remove MoveRef completely once we are comfortable
     * using c++11.
     */
    operator T&& ()  const { return static_cast<T&&>(*pointer); }
#else
    operator T& ()   const { return *pointer; }
#endif
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

/*
 * Round x up to the nearest power of 2.  This function assumes that the most
 * significant bit of x is not set, which would lead to overflow.
 */
JS_ALWAYS_INLINE size_t
RoundUpPow2(size_t x)
{
    return size_t(1) << JS_CEILING_LOG2W(x);
}

} /* namespace js */

#endif /* defined(__cplusplus) */

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
