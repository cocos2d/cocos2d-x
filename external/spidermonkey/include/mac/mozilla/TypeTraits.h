/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Template-based metaprogramming and type-testing facilities. */

#ifndef mozilla_TypeTraits_h
#define mozilla_TypeTraits_h

/*
 * These traits are approximate copies of the traits and semantics from C++11's
 * <type_traits> header.  Don't add traits not in that header!  When all
 * platforms provide that header, we can convert all users and remove this one.
 */

#include <wchar.h>

namespace mozilla {

/* Forward declarations. */

template<typename> struct RemoveCV;

/* 20.9.3 Helper classes [meta.help] */

/**
 * Helper class used as a base for various type traits, exposed publicly
 * because <type_traits> exposes it as well.
 */
template<typename T, T Value>
struct IntegralConstant
{
    static const T value = Value;
    typedef T ValueType;
    typedef IntegralConstant<T, Value> Type;
};

/** Convenient aliases. */
typedef IntegralConstant<bool, true> TrueType;
typedef IntegralConstant<bool, false> FalseType;

/* 20.9.4 Unary type traits [meta.unary] */

/* 20.9.4.1 Primary type categories [meta.unary.cat] */

namespace detail {

template <typename T>
struct IsIntegralHelper : FalseType {};

template<> struct IsIntegralHelper<char>               : TrueType {};
template<> struct IsIntegralHelper<signed char>        : TrueType {};
template<> struct IsIntegralHelper<unsigned char>      : TrueType {};
template<> struct IsIntegralHelper<short>              : TrueType {};
template<> struct IsIntegralHelper<unsigned short>     : TrueType {};
template<> struct IsIntegralHelper<int>                : TrueType {};
template<> struct IsIntegralHelper<unsigned int>       : TrueType {};
template<> struct IsIntegralHelper<long>               : TrueType {};
template<> struct IsIntegralHelper<unsigned long>      : TrueType {};
template<> struct IsIntegralHelper<long long>          : TrueType {};
template<> struct IsIntegralHelper<unsigned long long> : TrueType {};
template<> struct IsIntegralHelper<bool>               : TrueType {};
template<> struct IsIntegralHelper<wchar_t>            : TrueType {};
#ifdef MOZ_CHAR16_IS_NOT_WCHAR
template<> struct IsIntegralHelper<char16_t>           : TrueType {};
#endif

} /* namespace detail */

/**
 * IsIntegral determines whether a type is an integral type.
 *
 * mozilla::IsIntegral<int>::value is true;
 * mozilla::IsIntegral<unsigned short>::value is true;
 * mozilla::IsIntegral<const long>::value is true;
 * mozilla::IsIntegral<int*>::value is false;
 * mozilla::IsIntegral<double>::value is false;
 *
 * Note that the behavior of IsIntegral on char16_t and char32_t is
 * unspecified.
 */
template<typename T>
struct IsIntegral : detail::IsIntegralHelper<typename RemoveCV<T>::Type>
{};

template<typename T, typename U>
struct IsSame;

namespace detail {

template<typename T>
struct IsFloatingPointHelper
  : IntegralConstant<bool,
                     IsSame<T, float>::value ||
                     IsSame<T, double>::value ||
                     IsSame<T, long double>::value>
{};

} // namespace detail

/**
 * IsFloatingPoint determines whether a type is a floating point type (float,
 * double, long double).
 *
 * mozilla::IsFloatingPoint<int>::value is false;
 * mozilla::IsFloatingPoint<const float>::value is true;
 * mozilla::IsFloatingPoint<long double>::value is true;
 * mozilla::IsFloatingPoint<double*>::value is false.
 */
template<typename T>
struct IsFloatingPoint
  : detail::IsFloatingPointHelper<typename RemoveCV<T>::Type>
{};

/**
 * IsPointer determines whether a type is a pointer type (but not a pointer-to-
 * member type).
 *
 * mozilla::IsPointer<struct S*>::value is true;
 * mozilla::IsPointer<int**>::value is true;
 * mozilla::IsPointer<void (*)(void)>::value is true;
 * mozilla::IsPointer<int>::value is false;
 * mozilla::IsPointer<struct S>::value is false.
 */
template<typename T>
struct IsPointer : FalseType {};

template<typename T>
struct IsPointer<T*> : TrueType {};

namespace detail {

// __is_enum is a supported extension across all of our supported compilers.
template<typename T>
struct IsEnumHelper
  : IntegralConstant<bool, __is_enum(T)>
{};

} // namespace detail

/**
 * IsEnum determines whether a type is an enum type.
 *
 * mozilla::IsEnum<enum S>::value is true;
 * mozilla::IsEnum<enum S*>::value is false;
 * mozilla::IsEnum<int>::value is false;
 */
template<typename T>
struct IsEnum
  : detail::IsEnumHelper<typename RemoveCV<T>::Type>
{};

/* 20.9.4.2 Composite type traits [meta.unary.comp] */

/**
 * IsArithmetic determines whether a type is arithmetic.  A type is arithmetic
 * iff it is an integral type or a floating point type.
 *
 * mozilla::IsArithmetic<int>::value is true;
 * mozilla::IsArithmetic<double>::value is true;
 * mozilla::IsArithmetic<long double*>::value is false.
 */
template<typename T>
struct IsArithmetic
  : IntegralConstant<bool, IsIntegral<T>::value || IsFloatingPoint<T>::value>
{};

/* 20.9.4.3 Type properties [meta.unary.prop] */

/**
 * IsConst determines whether a type is const or not.
 *
 * mozilla::IsConst<int>::value is false;
 * mozilla::IsConst<void* const>::value is true;
 * mozilla::IsConst<const char*>::value is false.
 */
template<typename T>
struct IsConst : FalseType {};

template<typename T>
struct IsConst<const T> : TrueType {};

/**
 * IsVolatile determines whether a type is volatile or not.
 *
 * mozilla::IsVolatile<int>::value is false;
 * mozilla::IsVolatile<void* volatile>::value is true;
 * mozilla::IsVolatile<volatile char*>::value is false.
 */
template<typename T>
struct IsVolatile : FalseType {};

template<typename T>
struct IsVolatile<volatile T> : TrueType {};

/**
 * Traits class for identifying POD types.  Until C++11 there's no automatic
 * way to detect PODs, so for the moment this is done manually.  Users may
 * define specializations of this class that inherit from mozilla::TrueType and
 * mozilla::FalseType (or equivalently mozilla::IntegralConstant<bool, true or
 * false>, or conveniently from mozilla::IsPod for composite types) as needed to
 * ensure correct IsPod behavior.
 */
template<typename T>
struct IsPod : public FalseType {};

template<> struct IsPod<char>               : TrueType {};
template<> struct IsPod<signed char>        : TrueType {};
template<> struct IsPod<unsigned char>      : TrueType {};
template<> struct IsPod<short>              : TrueType {};
template<> struct IsPod<unsigned short>     : TrueType {};
template<> struct IsPod<int>                : TrueType {};
template<> struct IsPod<unsigned int>       : TrueType {};
template<> struct IsPod<long>               : TrueType {};
template<> struct IsPod<unsigned long>      : TrueType {};
template<> struct IsPod<long long>          : TrueType {};
template<> struct IsPod<unsigned long long> : TrueType {};
template<> struct IsPod<bool>               : TrueType {};
template<> struct IsPod<float>              : TrueType {};
template<> struct IsPod<double>             : TrueType {};
template<> struct IsPod<wchar_t>            : TrueType {};
#ifdef MOZ_CHAR16_IS_NOT_WCHAR
template<> struct IsPod<char16_t>           : TrueType {};
#endif
template<typename T> struct IsPod<T*>       : TrueType {};

namespace detail {

template<typename T, bool = IsFloatingPoint<T>::value>
struct IsSignedHelper;

template<typename T>
struct IsSignedHelper<T, true> : TrueType {};

template<typename T>
struct IsSignedHelper<T, false>
  : IntegralConstant<bool, IsArithmetic<T>::value && T(-1) < T(1)>
{};

} // namespace detail

/**
 * IsSigned determines whether a type is a signed arithmetic type.  |char| is
 * considered a signed type if it has the same representation as |signed char|.
 *
 * Don't use this if the type might be user-defined!  You might or might not get
 * a compile error, depending.
 *
 * mozilla::IsSigned<int>::value is true;
 * mozilla::IsSigned<const unsigned int>::value is false;
 * mozilla::IsSigned<unsigned char>::value is false;
 * mozilla::IsSigned<float>::value is true.
 */
template<typename T>
struct IsSigned : detail::IsSignedHelper<T> {};

namespace detail {

template<typename T, bool = IsFloatingPoint<T>::value>
struct IsUnsignedHelper;

template<typename T>
struct IsUnsignedHelper<T, true> : FalseType {};

template<typename T>
struct IsUnsignedHelper<T, false>
  : IntegralConstant<bool,
                     IsArithmetic<T>::value &&
                     (IsSame<typename RemoveCV<T>::Type, bool>::value ||
                      T(1) < T(-1))>
{};

} // namespace detail

/**
 * IsUnsigned determines whether a type is an unsigned arithmetic type.
 *
 * Don't use this if the type might be user-defined!  You might or might not get
 * a compile error, depending.
 *
 * mozilla::IsUnsigned<int>::value is false;
 * mozilla::IsUnsigned<const unsigned int>::value is true;
 * mozilla::IsUnsigned<unsigned char>::value is true;
 * mozilla::IsUnsigned<float>::value is false.
 */
template<typename T>
struct IsUnsigned : detail::IsUnsignedHelper<T> {};

/* 20.9.5 Type property queries [meta.unary.prop.query] */

/* 20.9.6 Relationships between types [meta.rel] */

/**
 * IsSame tests whether two types are the same type.
 *
 * mozilla::IsSame<int, int>::value is true;
 * mozilla::IsSame<int*, int*>::value is true;
 * mozilla::IsSame<int, unsigned int>::value is false;
 * mozilla::IsSame<void, void>::value is true;
 * mozilla::IsSame<const int, int>::value is false;
 * mozilla::IsSame<struct S, struct S>::value is true.
 */
template<typename T, typename U>
struct IsSame : FalseType {};

template<typename T>
struct IsSame<T, T> : TrueType {};

namespace detail {

// The trickery used to implement IsBaseOf here makes it possible to use it for
// the cases of private and multiple inheritance.  This code was inspired by the
// sample code here:
//
// http://stackoverflow.com/questions/2910979/how-is-base-of-works
template<class Base, class Derived>
struct BaseOfHelper
{
  public:
    operator Base*() const;
    operator Derived*();
};

template<class Base, class Derived>
struct BaseOfTester
{
  private:
    template<class T>
    static char test(Derived*, T);
    static int test(Base*, int);

  public:
    static const bool value =
      sizeof(test(BaseOfHelper<Base, Derived>(), int())) == sizeof(char);
};

template<class Base, class Derived>
struct BaseOfTester<Base, const Derived>
{
  private:
    template<class T>
    static char test(Derived*, T);
    static int test(Base*, int);

  public:
    static const bool value =
      sizeof(test(BaseOfHelper<Base, Derived>(), int())) == sizeof(char);
};

template<class Base, class Derived>
struct BaseOfTester<Base&, Derived&> : FalseType {};

template<class Type>
struct BaseOfTester<Type, Type> : TrueType {};

template<class Type>
struct BaseOfTester<Type, const Type> : TrueType {};

} /* namespace detail */

/*
 * IsBaseOf allows to know whether a given class is derived from another.
 *
 * Consider the following class definitions:
 *
 *   class A {};
 *   class B : public A {};
 *   class C {};
 *
 * mozilla::IsBaseOf<A, B>::value is true;
 * mozilla::IsBaseOf<A, C>::value is false;
 */
template<class Base, class Derived>
struct IsBaseOf
  : IntegralConstant<bool, detail::BaseOfTester<Base, Derived>::value>
{};

namespace detail {

template<typename From, typename To>
struct ConvertibleTester
{
  private:
    static From create();

    template<typename From1, typename To1>
    static char test(To to);

    template<typename From1, typename To1>
    static int test(...);

  public:
    static const bool value =
      sizeof(test<From, To>(create())) == sizeof(char);
};

} // namespace detail

/**
 * IsConvertible determines whether a value of type From will implicitly convert
 * to a value of type To.  For example:
 *
 *   struct A {};
 *   struct B : public A {};
 *   struct C {};
 *
 * mozilla::IsConvertible<A, A>::value is true;
 * mozilla::IsConvertible<A*, A*>::value is true;
 * mozilla::IsConvertible<B, A>::value is true;
 * mozilla::IsConvertible<B*, A*>::value is true;
 * mozilla::IsConvertible<C, A>::value is false;
 * mozilla::IsConvertible<A, C>::value is false;
 * mozilla::IsConvertible<A*, C*>::value is false;
 * mozilla::IsConvertible<C*, A*>::value is false.
 *
 * For obscure reasons, you can't use IsConvertible when the types being tested
 * are related through private inheritance, and you'll get a compile error if
 * you try.  Just don't do it!
 */
template<typename From, typename To>
struct IsConvertible
  : IntegralConstant<bool, detail::ConvertibleTester<From, To>::value>
{};

/**
 * Is IsLvalueReference<T> is true if its template param is T& and is false if
 * its type is T or T&&.
 */
template<typename T>
struct IsLvalueReference : FalseType {};

template<typename T>
struct IsLvalueReference<T&> : TrueType {};

/* 20.9.7 Transformations between types [meta.trans] */

/* 20.9.7.1 Const-volatile modifications [meta.trans.cv] */

/**
 * RemoveConst removes top-level const qualifications on a type.
 *
 * mozilla::RemoveConst<int>::Type is int;
 * mozilla::RemoveConst<const int>::Type is int;
 * mozilla::RemoveConst<const int*>::Type is const int*;
 * mozilla::RemoveConst<int* const>::Type is int*.
 */
template<typename T>
struct RemoveConst
{
    typedef T Type;
};

template<typename T>
struct RemoveConst<const T>
{
    typedef T Type;
};

/**
 * RemoveVolatile removes top-level volatile qualifications on a type.
 *
 * mozilla::RemoveVolatile<int>::Type is int;
 * mozilla::RemoveVolatile<volatile int>::Type is int;
 * mozilla::RemoveVolatile<volatile int*>::Type is volatile int*;
 * mozilla::RemoveVolatile<int* volatile>::Type is int*.
 */
template<typename T>
struct RemoveVolatile
{
    typedef T Type;
};

template<typename T>
struct RemoveVolatile<volatile T>
{
    typedef T Type;
};

/**
 * RemoveCV removes top-level const and volatile qualifications on a type.
 *
 * mozilla::RemoveCV<int>::Type is int;
 * mozilla::RemoveCV<const int>::Type is int;
 * mozilla::RemoveCV<volatile int>::Type is int;
 * mozilla::RemoveCV<int* const volatile>::Type is int*.
 */
template<typename T>
struct RemoveCV
{
    typedef typename RemoveConst<typename RemoveVolatile<T>::Type>::Type Type;
};

/* 20.9.7.2 Reference modifications [meta.trans.ref] */

/**
 * Converts reference types to the underlying types.
 *
 * mozilla::RemoveReference<T>::Type is T;
 * mozilla::RemoveReference<T&>::Type is T;
 * mozilla::RemoveReference<T&&>::Type is T;
 */

template<typename T>
struct RemoveReference
{
    typedef T Type;
};

template<typename T>
struct RemoveReference<T&>
{
    typedef T Type;
};

template<typename T>
struct RemoveReference<T&&>
{
    typedef T Type;
};

/* 20.9.7.3 Sign modifications [meta.trans.sign] */

template<bool B, typename T = void>
struct EnableIf;

template<bool Condition, typename A, typename B>
struct Conditional;

namespace detail {

template<bool MakeConst, typename T>
struct WithC : Conditional<MakeConst, const T, T>
{};

template<bool MakeVolatile, typename T>
struct WithV : Conditional<MakeVolatile, volatile T, T>
{};


template<bool MakeConst, bool MakeVolatile, typename T>
struct WithCV : WithC<MakeConst, typename WithV<MakeVolatile, T>::Type>
{};

template<typename T>
struct CorrespondingSigned;

template<>
struct CorrespondingSigned<char> { typedef signed char Type; };
template<>
struct CorrespondingSigned<unsigned char> { typedef signed char Type; };
template<>
struct CorrespondingSigned<unsigned short> { typedef short Type; };
template<>
struct CorrespondingSigned<unsigned int> { typedef int Type; };
template<>
struct CorrespondingSigned<unsigned long> { typedef long Type; };
template<>
struct CorrespondingSigned<unsigned long long> { typedef long long Type; };

template<typename T,
         typename CVRemoved = typename RemoveCV<T>::Type,
         bool IsSignedIntegerType = IsSigned<CVRemoved>::value &&
                                    !IsSame<char, CVRemoved>::value>
struct MakeSigned;

template<typename T, typename CVRemoved>
struct MakeSigned<T, CVRemoved, true>
{
    typedef T Type;
};

template<typename T, typename CVRemoved>
struct MakeSigned<T, CVRemoved, false>
  : WithCV<IsConst<T>::value, IsVolatile<T>::value,
           typename CorrespondingSigned<CVRemoved>::Type>
{};

} // namespace detail

/**
 * MakeSigned produces the corresponding signed integer type for a given
 * integral type T, with the const/volatile qualifiers of T.  T must be a
 * possibly-const/volatile-qualified integral type that isn't bool.
 *
 * If T is already a signed integer type (not including char!), then T is
 * produced.
 *
 * Otherwise, if T is an unsigned integer type, the signed variety of T, with
 * T's const/volatile qualifiers, is produced.
 *
 * Otherwise, the integral type of the same size as T, with the lowest rank,
 * with T's const/volatile qualifiers, is produced.  (This basically only acts
 * to produce signed char when T = char.)
 *
 * mozilla::MakeSigned<unsigned long>::Type is signed long;
 * mozilla::MakeSigned<volatile int>::Type is volatile int;
 * mozilla::MakeSigned<const unsigned short>::Type is const signed short;
 * mozilla::MakeSigned<const char>::Type is const signed char;
 * mozilla::MakeSigned<bool> is an error;
 * mozilla::MakeSigned<void*> is an error.
 */
template<typename T>
struct MakeSigned
  : EnableIf<IsIntegral<T>::value && !IsSame<bool, typename RemoveCV<T>::Type>::value,
             typename detail::MakeSigned<T>
            >::Type
{};

namespace detail {

template<typename T>
struct CorrespondingUnsigned;

template<>
struct CorrespondingUnsigned<char> { typedef unsigned char Type; };
template<>
struct CorrespondingUnsigned<signed char> { typedef unsigned char Type; };
template<>
struct CorrespondingUnsigned<short> { typedef unsigned short Type; };
template<>
struct CorrespondingUnsigned<int> { typedef unsigned int Type; };
template<>
struct CorrespondingUnsigned<long> { typedef unsigned long Type; };
template<>
struct CorrespondingUnsigned<long long> { typedef unsigned long long Type; };


template<typename T,
         typename CVRemoved = typename RemoveCV<T>::Type,
         bool IsUnsignedIntegerType = IsUnsigned<CVRemoved>::value &&
                                      !IsSame<char, CVRemoved>::value>
struct MakeUnsigned;

template<typename T, typename CVRemoved>
struct MakeUnsigned<T, CVRemoved, true>
{
    typedef T Type;
};

template<typename T, typename CVRemoved>
struct MakeUnsigned<T, CVRemoved, false>
  : WithCV<IsConst<T>::value, IsVolatile<T>::value,
           typename CorrespondingUnsigned<CVRemoved>::Type>
{};

} // namespace detail

/**
 * MakeUnsigned produces the corresponding unsigned integer type for a given
 * integral type T, with the const/volatile qualifiers of T.  T must be a
 * possibly-const/volatile-qualified integral type that isn't bool.
 *
 * If T is already an unsigned integer type (not including char!), then T is
 * produced.
 *
 * Otherwise, if T is an signed integer type, the unsigned variety of T, with
 * T's const/volatile qualifiers, is produced.
 *
 * Otherwise, the unsigned integral type of the same size as T, with the lowest
 * rank, with T's const/volatile qualifiers, is produced.  (This basically only
 * acts to produce unsigned char when T = char.)
 *
 * mozilla::MakeUnsigned<signed long>::Type is unsigned long;
 * mozilla::MakeUnsigned<volatile unsigned int>::Type is volatile unsigned int;
 * mozilla::MakeUnsigned<const signed short>::Type is const unsigned short;
 * mozilla::MakeUnsigned<const char>::Type is const unsigned char;
 * mozilla::MakeUnsigned<bool> is an error;
 * mozilla::MakeUnsigned<void*> is an error.
 */
template<typename T>
struct MakeUnsigned
  : EnableIf<IsIntegral<T>::value && !IsSame<bool, typename RemoveCV<T>::Type>::value,
             typename detail::MakeUnsigned<T>
            >::Type
{};

/* 20.9.7.4 Array modifications [meta.trans.arr] */

/* 20.9.7.5 Pointer modifications [meta.trans.ptr] */

/* 20.9.7.6 Other transformations [meta.trans.other] */

/**
 * EnableIf is a struct containing a typedef of T if and only if B is true.
 *
 * mozilla::EnableIf<true, int>::Type is int;
 * mozilla::EnableIf<false, int>::Type is a compile-time error.
 *
 * Use this template to implement SFINAE-style (Substitution Failure Is not An
 * Error) requirements.  For example, you might use it to impose a restriction
 * on a template parameter:
 *
 *   template<typename T>
 *   class PodVector // vector optimized to store POD (memcpy-able) types
 *   {
 *      EnableIf<IsPod<T>::value, T>::Type* vector;
 *      size_t length;
 *      ...
 *   };
 */
template<bool B, typename T>
struct EnableIf
{};

template<typename T>
struct EnableIf<true, T>
{
    typedef T Type;
};

/**
 * Conditional selects a class between two, depending on a given boolean value.
 *
 * mozilla::Conditional<true, A, B>::Type is A;
 * mozilla::Conditional<false, A, B>::Type is B;
 */
template<bool Condition, typename A, typename B>
struct Conditional
{
    typedef A Type;
};

template<class A, class B>
struct Conditional<false, A, B>
{
    typedef B Type;
};

} /* namespace mozilla */

#endif /* mozilla_TypeTraits_h */
