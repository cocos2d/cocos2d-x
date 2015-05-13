/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Implementations of various class and method modifier attributes. */

#ifndef mozilla_Attributes_h_
#define mozilla_Attributes_h_

#include "mozilla/Compiler.h"

/*
 * MOZ_INLINE is a macro which expands to tell the compiler that the method
 * decorated with it should be inlined.  This macro is usable from C and C++
 * code, even though C89 does not support the |inline| keyword.  The compiler
 * may ignore this directive if it chooses.
 */
#if defined(__cplusplus)
#  define MOZ_INLINE            inline
#elif defined(_MSC_VER)
#  define MOZ_INLINE            __inline
#elif defined(__GNUC__)
#  define MOZ_INLINE            __inline__
#else
#  define MOZ_INLINE            inline
#endif

/*
 * MOZ_ALWAYS_INLINE is a macro which expands to tell the compiler that the
 * method decorated with it must be inlined, even if the compiler thinks
 * otherwise.  This is only a (much) stronger version of the MOZ_INLINE hint:
 * compilers are not guaranteed to respect it (although they're much more likely
 * to do so).
 */
#if defined(_MSC_VER)
#  define MOZ_ALWAYS_INLINE     __forceinline
#elif defined(__GNUC__)
#  define MOZ_ALWAYS_INLINE     __attribute__((always_inline)) MOZ_INLINE
#else
#  define MOZ_ALWAYS_INLINE     MOZ_INLINE
#endif

/*
 * g++ requires -std=c++0x or -std=gnu++0x to support C++11 functionality
 * without warnings (functionality used by the macros below).  These modes are
 * detectable by checking whether __GXX_EXPERIMENTAL_CXX0X__ is defined or, more
 * standardly, by checking whether __cplusplus has a C++11 or greater value.
 * Current versions of g++ do not correctly set __cplusplus, so we check both
 * for forward compatibility.
 */
#if defined(__clang__)
   /*
    * Per Clang documentation, "Note that marketing version numbers should not
    * be used to check for language features, as different vendors use different
    * numbering schemes. Instead, use the feature checking macros."
    */
#  ifndef __has_extension
#    define __has_extension __has_feature /* compatibility, for older versions of clang */
#  endif
#  if __has_extension(cxx_constexpr)
#    define MOZ_HAVE_CXX11_CONSTEXPR
#  endif
#  if __has_extension(cxx_deleted_functions)
#    define MOZ_HAVE_CXX11_DELETE
#  endif
#  if __has_extension(cxx_override_control)
#    define MOZ_HAVE_CXX11_OVERRIDE
#    define MOZ_HAVE_CXX11_FINAL         final
#  endif
#  if __has_attribute(noinline)
#    define MOZ_HAVE_NEVER_INLINE        __attribute__((noinline))
#  endif
#  if __has_attribute(noreturn)
#    define MOZ_HAVE_NORETURN            __attribute__((noreturn))
#  endif
#elif defined(__GNUC__)
#  if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#    if MOZ_GCC_VERSION_AT_LEAST(4, 7, 0)
#      define MOZ_HAVE_CXX11_OVERRIDE
#      define MOZ_HAVE_CXX11_FINAL       final
#    endif
#    if MOZ_GCC_VERSION_AT_LEAST(4, 6, 0)
#      define MOZ_HAVE_CXX11_CONSTEXPR
#    endif
#    define MOZ_HAVE_CXX11_DELETE
#  else
     /* __final is a non-C++11 GCC synonym for 'final', per GCC r176655. */
#    if MOZ_GCC_VERSION_AT_LEAST(4, 7, 0)
#      define MOZ_HAVE_CXX11_FINAL       __final
#    endif
#  endif
#  define MOZ_HAVE_NEVER_INLINE          __attribute__((noinline))
#  define MOZ_HAVE_NORETURN              __attribute__((noreturn))
#elif defined(_MSC_VER)
#  if _MSC_VER >= 1700
#    define MOZ_HAVE_CXX11_FINAL         final
#  else
     /* MSVC <= 10 used to spell "final" as "sealed". */
#    define MOZ_HAVE_CXX11_FINAL         sealed
#  endif
#  define MOZ_HAVE_CXX11_OVERRIDE
#  define MOZ_HAVE_NEVER_INLINE          __declspec(noinline)
#  define MOZ_HAVE_NORETURN              __declspec(noreturn)
#endif

/*
 * The MOZ_CONSTEXPR specifier declares that a C++11 compiler can evaluate a
 * function at compile time. A constexpr function cannot examine any values
 * except its arguments and can have no side effects except its return value.
 */
#ifdef MOZ_HAVE_CXX11_CONSTEXPR
#  define MOZ_CONSTEXPR         constexpr
#else
#  define MOZ_CONSTEXPR         /* no support */
#endif

/*
 * MOZ_NEVER_INLINE is a macro which expands to tell the compiler that the
 * method decorated with it must never be inlined, even if the compiler would
 * otherwise choose to inline the method.  Compilers aren't absolutely
 * guaranteed to support this, but most do.
 */
#if defined(MOZ_HAVE_NEVER_INLINE)
#  define MOZ_NEVER_INLINE      MOZ_HAVE_NEVER_INLINE
#else
#  define MOZ_NEVER_INLINE      /* no support */
#endif

/*
 * MOZ_NORETURN, specified at the start of a function declaration, indicates
 * that the given function does not return.  (The function definition does not
 * need to be annotated.)
 *
 *   MOZ_NORETURN void abort(const char* msg);
 *
 * This modifier permits the compiler to optimize code assuming a call to such a
 * function will never return.  It also enables the compiler to avoid spurious
 * warnings about not initializing variables, or about any other seemingly-dodgy
 * operations performed after the function returns.
 *
 * This modifier does not affect the corresponding function's linking behavior.
 */
#if defined(MOZ_HAVE_NORETURN)
#  define MOZ_NORETURN          MOZ_HAVE_NORETURN
#else
#  define MOZ_NORETURN          /* no support */
#endif

/*
 * MOZ_ASAN_BLACKLIST is a macro to tell AddressSanitizer (a compile-time
 * instrumentation shipped with Clang) to not instrument the annotated function.
 * Furthermore, it will prevent the compiler from inlining the function because
 * inlining currently breaks the blacklisting mechanism of AddressSanitizer.
 */
#if defined(MOZ_ASAN)
#  define MOZ_ASAN_BLACKLIST MOZ_NEVER_INLINE __attribute__((no_address_safety_analysis))
# else
#  define MOZ_ASAN_BLACKLIST
#endif


#ifdef __cplusplus

/*
 * MOZ_DELETE, specified immediately prior to the ';' terminating an undefined-
 * method declaration, attempts to delete that method from the corresponding
 * class.  An attempt to use the method will always produce an error *at compile
 * time* (instead of sometimes as late as link time) when this macro can be
 * implemented.  For example, you can use MOZ_DELETE to produce classes with no
 * implicit copy constructor or assignment operator:
 *
 *   struct NonCopyable
 *   {
 *     private:
 *       NonCopyable(const NonCopyable& other) MOZ_DELETE;
 *       void operator=(const NonCopyable& other) MOZ_DELETE;
 *   };
 *
 * If MOZ_DELETE can't be implemented for the current compiler, use of the
 * annotated method will still cause an error, but the error might occur at link
 * time in some cases rather than at compile time.
 *
 * MOZ_DELETE relies on C++11 functionality not universally implemented.  As a
 * backstop, method declarations using MOZ_DELETE should be private.
 */
#if defined(MOZ_HAVE_CXX11_DELETE)
#  define MOZ_DELETE            = delete
#else
#  define MOZ_DELETE            /* no support */
#endif

/*
 * MOZ_OVERRIDE explicitly indicates that a virtual member function in a class
 * overrides a member function of a base class, rather than potentially being a
 * new member function.  MOZ_OVERRIDE should be placed immediately before the
 * ';' terminating the member function's declaration, or before '= 0;' if the
 * member function is pure.  If the member function is defined in the class
 * definition, it should appear before the opening brace of the function body.
 *
 *   class Base
 *   {
 *     public:
 *       virtual void f() = 0;
 *   };
 *   class Derived1 : public Base
 *   {
 *     public:
 *       virtual void f() MOZ_OVERRIDE;
 *   };
 *   class Derived2 : public Base
 *   {
 *     public:
 *       virtual void f() MOZ_OVERRIDE = 0;
 *   };
 *   class Derived3 : public Base
 *   {
 *     public:
 *       virtual void f() MOZ_OVERRIDE { }
 *   };
 *
 * In compilers supporting C++11 override controls, MOZ_OVERRIDE *requires* that
 * the function marked with it override a member function of a base class: it
 * is a compile error if it does not.  Otherwise MOZ_OVERRIDE does not affect
 * semantics and merely documents the override relationship to the reader (but
 * of course must still be used correctly to not break C++11 compilers).
 */
#if defined(MOZ_HAVE_CXX11_OVERRIDE)
#  define MOZ_OVERRIDE          override
#else
#  define MOZ_OVERRIDE          /* no support */
#endif

/*
 * MOZ_FINAL indicates that some functionality cannot be overridden through
 * inheritance.  It can be used to annotate either classes/structs or virtual
 * member functions.
 *
 * To annotate a class/struct with MOZ_FINAL, place MOZ_FINAL immediately after
 * the name of the class, before the list of classes from which it derives (if
 * any) and before its opening brace.  MOZ_FINAL must not be used to annotate
 * unnamed classes or structs.  (With some compilers, and with C++11 proper, the
 * underlying expansion is ambiguous with specifying a class name.)
 *
 *   class Base MOZ_FINAL
 *   {
 *     public:
 *       Base();
 *       ~Base();
 *       virtual void f() { }
 *   };
 *   // This will be an error in some compilers:
 *   class Derived : public Base
 *   {
 *     public:
 *       ~Derived() { }
 *   };
 *
 * One particularly common reason to specify MOZ_FINAL upon a class is to tell
 * the compiler that it's not dangerous for it to have a non-virtual destructor
 * yet have one or more virtual functions, silencing the warning it might emit
 * in this case.  Suppose Base above weren't annotated with MOZ_FINAL.  Because
 * ~Base() is non-virtual, an attempt to delete a Derived* through a Base*
 * wouldn't call ~Derived(), so any cleanup ~Derived() might do wouldn't happen.
 * (Formally C++ says behavior is undefined, but compilers will likely just call
 * ~Base() and not ~Derived().)  Specifying MOZ_FINAL tells the compiler that
 * it's safe for the destructor to be non-virtual.
 *
 * In compilers implementing final controls, it is an error to inherit from a
 * class annotated with MOZ_FINAL.  In other compilers it serves only as
 * documentation.
 *
 * To annotate a virtual member function with MOZ_FINAL, place MOZ_FINAL
 * immediately before the ';' terminating the member function's declaration, or
 * before '= 0;' if the member function is pure.  If the member function is
 * defined in the class definition, it should appear before the opening brace of
 * the function body.  (This placement is identical to that for MOZ_OVERRIDE.
 * If both are used, they should appear in the order 'MOZ_FINAL MOZ_OVERRIDE'
 * for consistency.)
 *
 *   class Base
 *   {
 *     public:
 *       virtual void f() MOZ_FINAL;
 *   };
 *   class Derived
 *   {
 *     public:
 *       // This will be an error in some compilers:
 *       virtual void f();
 *   };
 *
 * In compilers implementing final controls, it is an error for a derived class
 * to override a method annotated with MOZ_FINAL.  In other compilers it serves
 * only as documentation.
 */
#if defined(MOZ_HAVE_CXX11_FINAL)
#  define MOZ_FINAL             MOZ_HAVE_CXX11_FINAL
#else
#  define MOZ_FINAL             /* no support */
#endif

/**
 * MOZ_WARN_UNUSED_RESULT tells the compiler to emit a warning if a function's
 * return value is not used by the caller.
 *
 * Place this attribute at the very beginning of a function definition. For
 * example, write
 *
 *   MOZ_WARN_UNUSED_RESULT int foo();
 *
 * or
 *
 *   MOZ_WARN_UNUSED_RESULT int foo() { return 42; }
 */
#if defined(__GNUC__) || defined(__clang__)
#  define MOZ_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#else
#  define MOZ_WARN_UNUSED_RESULT
#endif

#endif /* __cplusplus */

#endif  /* mozilla_Attributes_h_ */
