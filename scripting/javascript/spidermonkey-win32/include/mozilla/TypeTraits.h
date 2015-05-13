/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* Template-based metaprogramming and type-testing facilities. */

#ifndef mozilla_TypeTraits_h_
#define mozilla_TypeTraits_h_

/*
 * These traits are approximate copies of the traits and semantics from C++11's
 * <type_traits> header.  Don't add traits not in that header!  When all
 * platforms provide that header, we can convert all users and remove this one.
 */

#include <wchar.h>

namespace mozilla {

namespace detail {

/**
 * The trickery used to implement IsBaseOf here makes it possible to use it for
 * the cases of private and multiple inheritance.  This code was inspired by the
 * sample code here:
 *
 * http://stackoverflow.com/questions/2910979/how-is-base-of-works
 */
template<class Base, class Derived>
class IsBaseOfHelper
{
  public:
    operator Base*() const;
    operator Derived*();
};

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
class IsBaseOf
{
  private:
    template<class T>
    static char test(Derived*, T);
    static int test(Base*, int);

  public:
    static const bool value =
      sizeof(test(detail::IsBaseOfHelper<Base, Derived>(), int())) == sizeof(char);
};

template<class Base, class Derived>
class IsBaseOf<Base, const Derived>
{
  private:
    template<class T>
    static char test(Derived*, T);
    static int test(Base*, int);

  public:
    static const bool value =
      sizeof(test(detail::IsBaseOfHelper<Base, Derived>(), int())) == sizeof(char);
};

template<class Base, class Derived>
class IsBaseOf<Base&, Derived&>
{
  public:
    static const bool value = false;
};

template<class Type>
class IsBaseOf<Type, Type>
{
  public:
    static const bool value = true;
};

template<class Type>
class IsBaseOf<Type, const Type>
{
  public:
    static const bool value = true;
};

/*
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

/*
 * Conditional selects a class between two, depending on a given boolean value.
 *
 * mozilla::Conditional<true, A, B>::Type is A;
 * mozilla::Conditional<false, A, B>::Type is B;
 */
template<bool condition, class A, class B>
struct Conditional
{
    typedef A Type;
};

template<class A, class B>
struct Conditional<false, A, B>
{
    typedef B Type;
};

/*
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
 *      EnableIf<IsPod<T>, T>::Type* vector;
 *      size_t length;
 *      ...
 *   };
 */
template<bool B, typename T = void>
struct EnableIf
{};

template<typename T>
struct EnableIf<true, T>
{
    typedef T Type;
};

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
struct IsSame
{
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T>
{
    static const bool value = true;
};

/*
 * Traits class for identifying POD types. Until C++0x, there is no automatic
 * way to detect PODs, so for the moment it is done manually.
 */
template<typename T>
struct IsPod
{
    static const bool value = false;
};
template<> struct IsPod<char>               { static const bool value = true; };
template<> struct IsPod<signed char>        { static const bool value = true; };
template<> struct IsPod<unsigned char>      { static const bool value = true; };
template<> struct IsPod<short>              { static const bool value = true; };
template<> struct IsPod<unsigned short>     { static const bool value = true; };
template<> struct IsPod<int>                { static const bool value = true; };
template<> struct IsPod<unsigned int>       { static const bool value = true; };
template<> struct IsPod<long>               { static const bool value = true; };
template<> struct IsPod<unsigned long>      { static const bool value = true; };
template<> struct IsPod<long long>          { static const bool value = true; };
template<> struct IsPod<unsigned long long> { static const bool value = true; };
template<> struct IsPod<bool>               { static const bool value = true; };
template<> struct IsPod<float>              { static const bool value = true; };
template<> struct IsPod<double>             { static const bool value = true; };
template<> struct IsPod<wchar_t>            { static const bool value = true; };
template<typename T> struct IsPod<T*>       { static const bool value = true; };

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
struct IsPointer
{
    static const bool value = false;
};
template<typename T>
struct IsPointer<T*>
{
    static const bool value = true;
};

} /* namespace mozilla */

#endif  /* mozilla_TypeTraits_h_ */
