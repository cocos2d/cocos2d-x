/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Implementations of runtime and static assertion macros for C and C++. */

#ifndef mozilla_Assertions_h
#define mozilla_Assertions_h

#include "mozilla/Attributes.h"
#include "mozilla/Compiler.h"
#include "mozilla/Likely.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
   /*
    * TerminateProcess and GetCurrentProcess are defined in <winbase.h>, which
    * further depends on <windef.h>.  We hardcode these few definitions manually
    * because those headers clutter the global namespace with a significant
    * number of undesired macros and symbols.
    */
#  ifdef __cplusplus
   extern "C" {
#  endif
   __declspec(dllimport) int __stdcall
   TerminateProcess(void* hProcess, unsigned int uExitCode);
   __declspec(dllimport) void* __stdcall GetCurrentProcess(void);
#  ifdef __cplusplus
   }
#  endif
#else
#  include <signal.h>
#endif
#ifdef ANDROID
#  include <android/log.h>
#endif

/*
 * MOZ_STATIC_ASSERT may be used to assert a condition *at compile time* in C.
 * In C++11, static_assert is provided by the compiler to the same effect.
 * This can be useful when you make certain assumptions about what must hold for
 * optimal, or even correct, behavior.  For example, you might assert that the
 * size of a struct is a multiple of the target architecture's word size:
 *
 *   struct S { ... };
 *   // C
 *   MOZ_STATIC_ASSERT(sizeof(S) % sizeof(size_t) == 0,
 *                     "S should be a multiple of word size for efficiency");
 *   // C++11
 *   static_assert(sizeof(S) % sizeof(size_t) == 0,
 *                 "S should be a multiple of word size for efficiency");
 *
 * This macro can be used in any location where both an extern declaration and a
 * typedef could be used.
 */
#ifndef __cplusplus
   /*
    * Some of the definitions below create an otherwise-unused typedef.  This
    * triggers compiler warnings with some versions of gcc, so mark the typedefs
    * as permissibly-unused to disable the warnings.
    */
#  if defined(__GNUC__)
#    define MOZ_STATIC_ASSERT_UNUSED_ATTRIBUTE __attribute__((unused))
#  else
#    define MOZ_STATIC_ASSERT_UNUSED_ATTRIBUTE /* nothing */
#  endif
#  define MOZ_STATIC_ASSERT_GLUE1(x, y)          x##y
#  define MOZ_STATIC_ASSERT_GLUE(x, y)           MOZ_STATIC_ASSERT_GLUE1(x, y)
#  if defined(__SUNPRO_CC)
     /*
      * The Sun Studio C++ compiler is buggy when declaring, inside a function,
      * another extern'd function with an array argument whose length contains a
      * sizeof, triggering the error message "sizeof expression not accepted as
      * size of array parameter".  This bug (6688515, not public yet) would hit
      * defining moz_static_assert as a function, so we always define an extern
      * array for Sun Studio.
      *
      * We include the line number in the symbol name in a best-effort attempt
      * to avoid conflicts (see below).
      */
#    define MOZ_STATIC_ASSERT(cond, reason) \
       extern char MOZ_STATIC_ASSERT_GLUE(moz_static_assert, __LINE__)[(cond) ? 1 : -1]
#  elif defined(__COUNTER__)
     /*
      * If there was no preferred alternative, use a compiler-agnostic version.
      *
      * Note that the non-__COUNTER__ version has a bug in C++: it can't be used
      * in both |extern "C"| and normal C++ in the same translation unit.  (Alas
      * |extern "C"| isn't allowed in a function.)  The only affected compiler
      * we really care about is gcc 4.2.  For that compiler and others like it,
      * we include the line number in the function name to do the best we can to
      * avoid conflicts.  These should be rare: a conflict would require use of
      * MOZ_STATIC_ASSERT on the same line in separate files in the same
      * translation unit, *and* the uses would have to be in code with
      * different linkage, *and* the first observed use must be in C++-linkage
      * code.
      */
#    define MOZ_STATIC_ASSERT(cond, reason) \
       typedef int MOZ_STATIC_ASSERT_GLUE(moz_static_assert, __COUNTER__)[(cond) ? 1 : -1] MOZ_STATIC_ASSERT_UNUSED_ATTRIBUTE
#  else
#    define MOZ_STATIC_ASSERT(cond, reason) \
       extern void MOZ_STATIC_ASSERT_GLUE(moz_static_assert, __LINE__)(int arg[(cond) ? 1 : -1]) MOZ_STATIC_ASSERT_UNUSED_ATTRIBUTE
#  endif

#define MOZ_STATIC_ASSERT_IF(cond, expr, reason)  MOZ_STATIC_ASSERT(!(cond) || (expr), reason)
#else
#define MOZ_STATIC_ASSERT_IF(cond, expr, reason)  static_assert(!(cond) || (expr), reason)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Prints |s| as an assertion failure (using file and ln as the location of the
 * assertion) to the standard debug-output channel.
 *
 * Usually you should use MOZ_ASSERT or MOZ_CRASH instead of this method.  This
 * method is primarily for internal use in this header, and only secondarily
 * for use in implementing release-build assertions.
 */
static MOZ_ALWAYS_INLINE void
MOZ_ReportAssertionFailure(const char* s, const char* file, int ln)
{
#ifdef ANDROID
  __android_log_print(ANDROID_LOG_FATAL, "MOZ_Assert",
                      "Assertion failure: %s, at %s:%d\n", s, file, ln);
#else
  fprintf(stderr, "Assertion failure: %s, at %s:%d\n", s, file, ln);
  fflush(stderr);
#endif
}

static MOZ_ALWAYS_INLINE void
MOZ_ReportCrash(const char* s, const char* file, int ln)
{
#ifdef ANDROID
    __android_log_print(ANDROID_LOG_FATAL, "MOZ_CRASH",
                        "Hit MOZ_CRASH(%s) at %s:%d\n", s, file, ln);
#else
  fprintf(stderr, "Hit MOZ_CRASH(%s) at %s:%d\n", s, file, ln);
  fflush(stderr);
#endif
}

/**
 * MOZ_REALLY_CRASH is used in the implementation of MOZ_CRASH().  You should
 * call MOZ_CRASH instead.
 */
#if defined(_MSC_VER)
   /*
    * On MSVC use the __debugbreak compiler intrinsic, which produces an inline
    * (not nested in a system function) breakpoint.  This distinctively invokes
    * Breakpad without requiring system library symbols on all stack-processing
    * machines, as a nested breakpoint would require.
    *
    * We use TerminateProcess with the exit code aborting would generate
    * because we don't want to invoke atexit handlers, destructors, library
    * unload handlers, and so on when our process might be in a compromised
    * state.
    *
    * We don't use abort() because it'd cause Windows to annoyingly pop up the
    * process error dialog multiple times.  See bug 345118 and bug 426163.
    *
    * We follow TerminateProcess() with a call to MOZ_NoReturn() so that the
    * compiler doesn't hassle us to provide a return statement after a
    * MOZ_REALLY_CRASH() call.
    *
    * (Technically these are Windows requirements, not MSVC requirements.  But
    * practically you need MSVC for debugging, and we only ship builds created
    * by MSVC, so doing it this way reduces complexity.)
    */

__declspec(noreturn) __inline void MOZ_NoReturn() {}

#  ifdef __cplusplus
#    define MOZ_REALLY_CRASH() \
       do { \
         ::__debugbreak(); \
         *((volatile int*) NULL) = 123; \
         ::TerminateProcess(::GetCurrentProcess(), 3); \
         ::MOZ_NoReturn(); \
       } while (0)
#  else
#    define MOZ_REALLY_CRASH() \
       do { \
         __debugbreak(); \
         *((volatile int*) NULL) = 123; \
         TerminateProcess(GetCurrentProcess(), 3); \
         MOZ_NoReturn(); \
       } while (0)
#  endif
#else
#  ifdef __cplusplus
#    define MOZ_REALLY_CRASH() \
       do { \
         *((volatile int*) NULL) = 123; \
         ::abort(); \
       } while (0)
#  else
#    define MOZ_REALLY_CRASH() \
       do { \
         *((volatile int*) NULL) = 123; \
         abort(); \
       } while (0)
#  endif
#endif

/*
 * MOZ_CRASH([explanation-string]) crashes the program, plain and simple, in a
 * Breakpad-compatible way, in both debug and release builds.
 *
 * MOZ_CRASH is a good solution for "handling" failure cases when you're
 * unwilling or unable to handle them more cleanly -- for OOM, for likely memory
 * corruption, and so on.  It's also a good solution if you need safe behavior
 * in release builds as well as debug builds.  But if the failure is one that
 * should be debugged and fixed, MOZ_ASSERT is generally preferable.
 *
 * The optional explanation-string, if provided, must be a string literal
 * explaining why we're crashing.  This argument is intended for use with
 * MOZ_CRASH() calls whose rationale is non-obvious; don't use it if it's
 * obvious why we're crashing.
 *
 * If we're a DEBUG build and we crash at a MOZ_CRASH which provides an
 * explanation-string, we print the string to stderr.  Otherwise, we don't
 * print anything; this is because we want MOZ_CRASH to be 100% safe in release
 * builds, and it's hard to print to stderr safely when memory might have been
 * corrupted.
 */
#ifndef DEBUG
#  define MOZ_CRASH(...) MOZ_REALLY_CRASH()
#else
#  define MOZ_CRASH(...) \
     do { \
       MOZ_ReportCrash("" __VA_ARGS__, __FILE__, __LINE__); \
       MOZ_REALLY_CRASH(); \
     } while(0)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/*
 * MOZ_ASSERT(expr [, explanation-string]) asserts that |expr| must be truthy in
 * debug builds.  If it is, execution continues.  Otherwise, an error message
 * including the expression and the explanation-string (if provided) is printed,
 * an attempt is made to invoke any existing debugger, and execution halts.
 * MOZ_ASSERT is fatal: no recovery is possible.  Do not assert a condition
 * which can correctly be falsy.
 *
 * The optional explanation-string, if provided, must be a string literal
 * explaining the assertion.  It is intended for use with assertions whose
 * correctness or rationale is non-obvious, and for assertions where the "real"
 * condition being tested is best described prosaically.  Don't provide an
 * explanation if it's not actually helpful.
 *
 *   // No explanation needed: pointer arguments often must not be NULL.
 *   MOZ_ASSERT(arg);
 *
 *   // An explanation can be helpful to explain exactly how we know an
 *   // assertion is valid.
 *   MOZ_ASSERT(state == WAITING_FOR_RESPONSE,
 *              "given that <thingA> and <thingB>, we must have...");
 *
 *   // Or it might disambiguate multiple identical (save for their location)
 *   // assertions of the same expression.
 *   MOZ_ASSERT(getSlot(PRIMITIVE_THIS_SLOT).isUndefined(),
 *              "we already set [[PrimitiveThis]] for this Boolean object");
 *   MOZ_ASSERT(getSlot(PRIMITIVE_THIS_SLOT).isUndefined(),
 *              "we already set [[PrimitiveThis]] for this String object");
 *
 * MOZ_ASSERT has no effect in non-debug builds.  It is designed to catch bugs
 * *only* during debugging, not "in the field".
 */
#ifdef DEBUG
   /* First the single-argument form. */
#  define MOZ_ASSERT_HELPER1(expr) \
     do { \
       if (MOZ_UNLIKELY(!(expr))) { \
         MOZ_ReportAssertionFailure(#expr, __FILE__, __LINE__); \
         MOZ_REALLY_CRASH(); \
       } \
     } while (0)
   /* Now the two-argument form. */
#  define MOZ_ASSERT_HELPER2(expr, explain) \
     do { \
       if (MOZ_UNLIKELY(!(expr))) { \
         MOZ_ReportAssertionFailure(#expr " (" explain ")", __FILE__, __LINE__); \
         MOZ_REALLY_CRASH(); \
       } \
     } while (0)
   /* And now, helper macrology up the wazoo. */
   /*
    * Count the number of arguments passed to MOZ_ASSERT, very carefully
    * tiptoeing around an MSVC bug where it improperly expands __VA_ARGS__ as a
    * single token in argument lists.  See these URLs for details:
    *
    *   http://connect.microsoft.com/VisualStudio/feedback/details/380090/variadic-macro-replacement
    *   http://cplusplus.co.il/2010/07/17/variadic-macro-to-count-number-of-arguments/#comment-644
    */
#  define MOZ_COUNT_ASSERT_ARGS_IMPL2(_1, _2, count, ...) \
     count
#  define MOZ_COUNT_ASSERT_ARGS_IMPL(args) \
	 MOZ_COUNT_ASSERT_ARGS_IMPL2 args
#  define MOZ_COUNT_ASSERT_ARGS(...) \
     MOZ_COUNT_ASSERT_ARGS_IMPL((__VA_ARGS__, 2, 1, 0))
   /* Pick the right helper macro to invoke. */
#  define MOZ_ASSERT_CHOOSE_HELPER2(count) MOZ_ASSERT_HELPER##count
#  define MOZ_ASSERT_CHOOSE_HELPER1(count) MOZ_ASSERT_CHOOSE_HELPER2(count)
#  define MOZ_ASSERT_CHOOSE_HELPER(count) MOZ_ASSERT_CHOOSE_HELPER1(count)
   /* The actual macro. */
#  define MOZ_ASSERT_GLUE(x, y) x y
#  define MOZ_ASSERT(...) \
     MOZ_ASSERT_GLUE(MOZ_ASSERT_CHOOSE_HELPER(MOZ_COUNT_ASSERT_ARGS(__VA_ARGS__)), \
                     (__VA_ARGS__))
#else
#  define MOZ_ASSERT(...) do { } while(0)
#endif /* DEBUG */

/*
 * MOZ_ASSERT_IF(cond1, cond2) is equivalent to MOZ_ASSERT(cond2) if cond1 is
 * true.
 *
 *   MOZ_ASSERT_IF(isPrime(num), num == 2 || isOdd(num));
 *
 * As with MOZ_ASSERT, MOZ_ASSERT_IF has effect only in debug builds.  It is
 * designed to catch bugs during debugging, not "in the field".
 */
#ifdef DEBUG
#  define MOZ_ASSERT_IF(cond, expr) \
     do { \
       if (cond) \
         MOZ_ASSERT(expr); \
     } while (0)
#else
#  define MOZ_ASSERT_IF(cond, expr)  do { } while (0)
#endif

/*
 * MOZ_ASSUME_UNREACHABLE_MARKER() expands to an expression which states that it is
 * undefined behavior for execution to reach this point.  No guarantees are made
 * about what will happen if this is reached at runtime.  Most code should
 * probably use the higher level MOZ_ASSUME_UNREACHABLE, which uses this when
 * appropriate.
 */
#if defined(__clang__)
#  define MOZ_ASSUME_UNREACHABLE_MARKER() __builtin_unreachable()
#elif defined(__GNUC__)
   /*
    * __builtin_unreachable() was implemented in gcc 4.5.  If we don't have
    * that, call a noreturn function; abort() will do nicely.  Qualify the call
    * in C++ in case there's another abort() visible in local scope.
    */
#  if MOZ_GCC_VERSION_AT_LEAST(4, 5, 0)
#    define MOZ_ASSUME_UNREACHABLE_MARKER() __builtin_unreachable()
#  else
#    ifdef __cplusplus
#      define MOZ_ASSUME_UNREACHABLE_MARKER() ::abort()
#    else
#      define MOZ_ASSUME_UNREACHABLE_MARKER() abort()
#    endif
#  endif
#elif defined(_MSC_VER)
#  define MOZ_ASSUME_UNREACHABLE_MARKER() __assume(0)
#else
#  ifdef __cplusplus
#    define MOZ_ASSUME_UNREACHABLE_MARKER() ::abort()
#  else
#    define MOZ_ASSUME_UNREACHABLE_MARKER() abort()
#  endif
#endif

/*
 * MOZ_ASSUME_UNREACHABLE([reason]) tells the compiler that it can assume that
 * the macro call cannot be reached during execution.  This lets the compiler
 * generate better-optimized code under some circumstances, at the expense of
 * the program's behavior being undefined if control reaches the
 * MOZ_ASSUME_UNREACHABLE.
 *
 * In Gecko, you probably should not use this macro outside of performance- or
 * size-critical code, because it's unsafe.  If you don't care about code size
 * or performance, you should probably use MOZ_ASSERT or MOZ_CRASH.
 *
 * SpiderMonkey is a different beast, and there it's acceptable to use
 * MOZ_ASSUME_UNREACHABLE more widely.
 *
 * Note that MOZ_ASSUME_UNREACHABLE is noreturn, so it's valid not to return a
 * value following a MOZ_ASSUME_UNREACHABLE call.
 *
 * Example usage:
 *
 *   enum ValueType {
 *     VALUE_STRING,
 *     VALUE_INT,
 *     VALUE_FLOAT
 *   };
 *
 *   int ptrToInt(ValueType type, void* value) {
 *   {
 *     // We know for sure that type is either INT or FLOAT, and we want this
 *     // code to run as quickly as possible.
 *     switch (type) {
 *     case VALUE_INT:
 *       return *(int*) value;
 *     case VALUE_FLOAT:
 *       return (int) *(float*) value;
 *     default:
 *       MOZ_ASSUME_UNREACHABLE("can only handle VALUE_INT and VALUE_FLOAT");
 *     }
 *   }
 */
#if defined(DEBUG)
#  define MOZ_ASSUME_UNREACHABLE(...) \
     do { \
       MOZ_ASSERT(false, "MOZ_ASSUME_UNREACHABLE(" __VA_ARGS__ ")"); \
       MOZ_ASSUME_UNREACHABLE_MARKER(); \
     } while (0)
#else
#  define MOZ_ASSUME_UNREACHABLE(reason)  MOZ_ASSUME_UNREACHABLE_MARKER()
#endif

/*
 * MOZ_ALWAYS_TRUE(expr) and MOZ_ALWAYS_FALSE(expr) always evaluate the provided
 * expression, in debug builds and in release builds both.  Then, in debug
 * builds only, the value of the expression is asserted either true or false
 * using MOZ_ASSERT.
 */
#ifdef DEBUG
#  define MOZ_ALWAYS_TRUE(expr)      MOZ_ASSERT((expr))
#  define MOZ_ALWAYS_FALSE(expr)     MOZ_ASSERT(!(expr))
#else
#  define MOZ_ALWAYS_TRUE(expr)      ((void)(expr))
#  define MOZ_ALWAYS_FALSE(expr)     ((void)(expr))
#endif

#endif /* mozilla_Assertions_h */
