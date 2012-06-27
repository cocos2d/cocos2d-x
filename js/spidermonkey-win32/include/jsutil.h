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

#include "jstypes.h"
#include <stdlib.h>
#include <string.h>

JS_BEGIN_EXTERN_C

/*
 * JS_Assert is present even in release builds, for the benefit of applications
 * that build DEBUG and link against a non-DEBUG SpiderMonkey library.
 */
extern JS_PUBLIC_API(void)
JS_Assert(const char *s, const char *file, JSIntn ln);

#define JS_CRASH_UNLESS(__cond)                                                 \
    JS_BEGIN_MACRO                                                              \
        if (!(__cond)) {                                                        \
            *(int *)(uintptr_t)0xccadbeef = 0;                                  \
            ((void(*)())0)(); /* More reliable, but doesn't say CCADBEEF */     \
        }                                                                       \
    JS_END_MACRO

#ifdef DEBUG

#define JS_ASSERT(expr)                                                       \
    ((expr) ? (void)0 : JS_Assert(#expr, __FILE__, __LINE__))

#define JS_ASSERT_IF(cond, expr)                                              \
    ((!(cond) || (expr)) ? (void)0 : JS_Assert(#expr, __FILE__, __LINE__))

#define JS_NOT_REACHED(reason)                                                \
    JS_Assert(reason, __FILE__, __LINE__)

#define JS_ALWAYS_TRUE(expr) JS_ASSERT(expr)

#define JS_ALWAYS_FALSE(expr) JS_ASSERT(!(expr))

# ifdef JS_THREADSAFE
# define JS_THREADSAFE_ASSERT(expr) JS_ASSERT(expr) 
# else
# define JS_THREADSAFE_ASSERT(expr) ((void) 0)
# endif

#else

#define JS_ASSERT(expr)         ((void) 0)
#define JS_ASSERT_IF(cond,expr) ((void) 0)
#define JS_NOT_REACHED(reason)
#define JS_ALWAYS_TRUE(expr)    ((void) (expr))
#define JS_ALWAYS_FALSE(expr)    ((void) (expr))
#define JS_THREADSAFE_ASSERT(expr) ((void) 0)

#endif /* defined(DEBUG) */

/*
 * Compile-time assert. "cond" must be a constant expression.
 * The macro can be used only in places where an "extern" declaration is
 * allowed.
 */

#ifdef __SUNPRO_CC
/*
 * Sun Studio C++ compiler has a bug
 * "sizeof expression not accepted as size of array parameter"
 * It happens when js_static_assert() function is declared inside functions.
 * The bug number is 6688515. It is not public yet.
 * Therefore, for Sun Studio, declare js_static_assert as an array instead.
 */
#define JS_STATIC_ASSERT(cond) extern char js_static_assert[(cond) ? 1 : -1]
#else
#ifdef __COUNTER__
    #define JS_STATIC_ASSERT_GLUE1(x,y) x##y
    #define JS_STATIC_ASSERT_GLUE(x,y) JS_STATIC_ASSERT_GLUE1(x,y)
    #define JS_STATIC_ASSERT(cond)                                            \
        typedef int JS_STATIC_ASSERT_GLUE(js_static_assert, __COUNTER__)[(cond) ? 1 : -1]
#else
    #define JS_STATIC_ASSERT(cond) extern void js_static_assert(int arg[(cond) ? 1 : -1])
#endif
#endif

#define JS_STATIC_ASSERT_IF(cond, expr) JS_STATIC_ASSERT(!(cond) || (expr))

/*
 * Abort the process in a non-graceful manner. This will cause a core file,
 * call to the debugger or other moral equivalent as well as causing the
 * entire process to stop.
 */
extern JS_PUBLIC_API(void) JS_Abort(void);

#ifdef DEBUG
# define JS_BASIC_STATS 1
#endif

#ifdef DEBUG_brendan
# define JS_SCOPE_DEPTH_METER 1
#endif

#ifdef JS_BASIC_STATS

#include <stdio.h>

typedef struct JSBasicStats {
    uint32      num;
    uint32      max;
    double      sum;
    double      sqsum;
    uint32      logscale;           /* logarithmic scale: 0 (linear), 2, 10 */
    uint32      hist[11];
} JSBasicStats;

#define JS_INIT_STATIC_BASIC_STATS  {0,0,0,0,0,{0,0,0,0,0,0,0,0,0,0,0}}
#define JS_BASIC_STATS_INIT(bs)     memset((bs), 0, sizeof(JSBasicStats))

#define JS_BASIC_STATS_ACCUM(bs,val)                                          \
    JS_BasicStatsAccum(bs, val)

#define JS_MeanAndStdDevBS(bs,sigma)                                          \
    JS_MeanAndStdDev((bs)->num, (bs)->sum, (bs)->sqsum, sigma)

extern void
JS_BasicStatsAccum(JSBasicStats *bs, uint32 val);

extern double
JS_MeanAndStdDev(uint32 num, double sum, double sqsum, double *sigma);

extern void
JS_DumpBasicStats(JSBasicStats *bs, const char *title, FILE *fp);

extern void
JS_DumpHistogram(JSBasicStats *bs, FILE *fp);

#else

#define JS_BASIC_STATS_ACCUM(bs,val) /* nothing */

#endif /* JS_BASIC_STATS */


#if defined(DEBUG_notme) && defined(XP_UNIX)

typedef struct JSCallsite JSCallsite;

struct JSCallsite {
    uint32      pc;
    char        *name;
    const char  *library;
    int         offset;
    JSCallsite  *parent;
    JSCallsite  *siblings;
    JSCallsite  *kids;
    void        *handy;
};

extern JS_FRIEND_API(JSCallsite *)
JS_Backtrace(int skip);

extern JS_FRIEND_API(void)
JS_DumpBacktrace(JSCallsite *trace);
#endif

#if defined JS_USE_CUSTOM_ALLOCATOR

#include "jscustomallocator.h"

#else

static JS_INLINE void* js_malloc(size_t bytes) {
    return malloc(bytes);
}

static JS_INLINE void* js_calloc(size_t bytes) {
    return calloc(bytes, 1);
}

static JS_INLINE void* js_realloc(void* p, size_t bytes) {
    return realloc(p, bytes);
}

static JS_INLINE void js_free(void* p) {
    free(p);
}
#endif/* JS_USE_CUSTOM_ALLOCATOR */

JS_END_EXTERN_C

#ifdef __cplusplus

/* 
 * Using vanilla new/new[] is unsafe in SpiderMonkey because they throw on
 * failure instead of returning NULL, which is what SpiderMonkey expects.
 * js_new()/js_array_new() should be used instead, and memory allocated with
 * them should be deallocated with js_delete()/js_array_delete().
 *
 * If you have a class with a private constructor or destructor, you can
 * make js_new/js_delete a friend.  This can be fiddly, and the interaction of
 * template functions, friend functions and namespaces can overwhelm even
 * modern compilers.  Manual inlining is probably easier.
 *
 * (If you're wondering why we can't just use the 'nothrow' variant of
 * new/new[], it's because we want to mediate *all* allocations within
 * SpiderMonkey, to satisfy any embedders using JS_USE_CUSTOM_ALLOCATOR.)
 */

#define JS_NEW_BODY(t, parms)                                                 \
    void *memory = js_malloc(sizeof(t));                                      \
    return memory ? new(memory) t parms : NULL;

template <class T>
JS_ALWAYS_INLINE T *js_new() {
    JS_NEW_BODY(T, ())
}

template <class T, class P1>
JS_ALWAYS_INLINE T *js_new(const P1 &p1) {
    JS_NEW_BODY(T, (p1))
}

template <class T, class P1, class P2>
JS_ALWAYS_INLINE T *js_new(const P1 &p1, const P2 &p2) {
    JS_NEW_BODY(T, (p1, p2))
}

template <class T, class P1, class P2, class P3>
JS_ALWAYS_INLINE T *js_new(const P1 &p1, const P2 &p2, const P3 &p3) {
    JS_NEW_BODY(T, (p1, p2, p3))
}

template <class T, class P1, class P2, class P3, class P4>
JS_ALWAYS_INLINE T *js_new(const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4) {
    JS_NEW_BODY(T, (p1, p2, p3, p4))
}

/* ...add additional js_new()s as necessary... */

#undef JS_NEW_BODY

template <class T>
JS_ALWAYS_INLINE void js_delete(T *p) {
    if (p) {
        p->~T();
        js_free(p);
    }
}

static const int JSMinAlignment = 8;

template <class T>
JS_ALWAYS_INLINE T *js_array_new(size_t n) {
	/* The length is stored just before the vector memory. */
    uint64 numBytes64 = uint64(JSMinAlignment) + uint64(sizeof(T)) * uint64(n);
    size_t numBytes = size_t(numBytes64);
    if (numBytes64 != numBytes) {
        JS_ASSERT(0);   /* we want to know if this happens in debug builds */
        return NULL;
    }
    void *memory = js_malloc(numBytes);
    if (!memory)
        return NULL;
	*(size_t *)memory = n;
	memory = (void*)(uintptr_t(memory) + JSMinAlignment);
    return new(memory) T[n];
}

template <class T>
JS_ALWAYS_INLINE void js_array_delete(T *p) {
    if (p) {
		void* p0 = (void *)(uintptr_t(p) - JSMinAlignment);
		size_t n = *(size_t *)p0;
		for (size_t i = 0; i < n; i++)
			(p + i)->~T();
		js_free(p0);
    }
}

/**
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
class JSGuardObjectNotifier
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

class JSGuardObjectNotificationReceiver
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
#define JS_GUARD_OBJECT_NOTIFIER_PARAM0 \
    const JSGuardObjectNotifier& _notifier = JSGuardObjectNotifier()
#define JS_GUARD_OBJECT_NOTIFIER_INIT \
    JS_BEGIN_MACRO _mCheckNotUsedAsTemporary.Init(_notifier); JS_END_MACRO

#else /* defined(DEBUG) */

#define JS_DECL_USE_GUARD_OBJECT_NOTIFIER
#define JS_GUARD_OBJECT_NOTIFIER_PARAM
#define JS_GUARD_OBJECT_NOTIFIER_PARAM0
#define JS_GUARD_OBJECT_NOTIFIER_INIT JS_BEGIN_MACRO JS_END_MACRO

#endif /* !defined(DEBUG) */

namespace js {

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
    memset(t, 0, nelem * sizeof(T));
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
PodCopy(T *dst, const T *src, size_t nelem)
{
    /* Cannot find portable word-sized abs(). */
    JS_ASSERT_IF(dst >= src, size_t(dst - src) >= nelem);
    JS_ASSERT_IF(src >= dst, size_t(src - dst) >= nelem);

    if (nelem < 128) {
        for (const T *srcend = src + nelem; src != srcend; ++src, ++dst)
            *dst = *src;
    } else {
        memcpy(dst, src, nelem * sizeof(T));
    }
}

} /* namespace js */

#endif /* defined(__cplusplus) */

#endif /* jsutil_h___ */
