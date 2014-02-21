/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* C++11-style, but C++98-usable, "move references" implementation. */

#ifndef mozilla_Move_h
#define mozilla_Move_h

#include "mozilla/TypeTraits.h"

namespace mozilla {

/*
 * "Move" References
 *
 * [Once upon a time, C++11 rvalue references were not implemented by all the
 * compilers we cared about, so we invented mozilla::Move() (now called
 * OldMove()), which does something similar.  We're in the process of
 * transitioning away from this to pure stl (bug 896100).  Until that bug is
 * completed, this header will provide both mozilla::OldMove() and
 * mozilla::Move().]
 *
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
 *    afterwards (although it must still be safe to destroy); and
 *
 * 2) a way for a type (like Vector) to announce that it can be moved more
 *    efficiently than it can be copied, and provide an implementation of that
 *    move operation.
 *
 * The OldMove(T&) function takes a reference to a T, and returns a MoveRef<T>
 * referring to the same value; that's (1). A MoveRef<T> is simply a reference
 * to a T, annotated to say that a copy constructor applied to it may move that
 * T, instead of copying it. Finally, a constructor that accepts an MoveRef<T>
 * should perform a more efficient move, instead of a copy, providing (2).
 *
 * The Move(T&) function takes a reference to a T and returns a T&&.  It acts
 * just like std::move(), which is not available on all our platforms.
 *
 * In new code, you should use Move(T&) and T&& instead of OldMove(T&) and
 * MoveRef<T>, where possible.
 *
 * Where we might define a copy constructor for a class C like this:
 *
 *   C(const C& rhs) { ... copy rhs to this ... }
 *
 * we would declare a move constructor like this:
 *
 *   C(C&& rhs) { .. move rhs to this ... }
 *
 * or, in the deprecated OldMove style:
 *
 *   C(MoveRef<C> rhs) { ... move rhs to this ... }
 *
 * And where we might perform a copy like this:
 *
 *   C c2(c1);
 *
 * we would perform a move like this:
 *
 *   C c2(Move(c1));
 *
 * or, in the deprecated OldMove style:
 *
 *   C c2(OldMove(c1));
 *
 * Note that MoveRef<T> implicitly converts to T&, so you can pass a MoveRef<T>
 * to an ordinary copy constructor for a type that doesn't support a special
 * move constructor, and you'll just get a copy.  This means that templates can
 * use Move whenever they know they won't use the original value any more, even
 * if they're not sure whether the type at hand has a specialized move
 * constructor.  If it doesn't, the MoveRef<T> will just convert to a T&, and
 * the ordinary copy constructor will apply.
 *
 * A class with a move constructor can also provide a move assignment operator,
 * which runs this's destructor, and then applies the move constructor to
 * *this's memory. A typical definition:
 *
 *   C& operator=(C&& rhs) {  // or |MoveRef<C> rhs|
 *     this->~C();
 *     new(this) C(rhs);
 *     return *this;
 *   }
 *
 * With that in place, one can write move assignments like this:
 *
 *   c2 = Move(c1); // or OldMove()
 *
 * This destroys c1, moves c1's value to c2, and leaves c1 in an undefined but
 * destructible state.
 *
 * This header file defines MoveRef, Move, and OldMove in the mozilla namespace.
 * It's up to individual containers to annotate moves as such, by calling Move
 * or OldMove; and it's up to individual types to define move constructors.
 *
 * One hint: if you're writing a move constructor where the type has members
 * that should be moved themselves, it's much nicer to write this:
 *
 *   C(MoveRef<C> c) : x(Move(c->x)), y(Move(c->y)) { }
 *
 * than the equivalent:
 *
 *   C(MoveRef<C> c) { new(&x) X(Move(c->x)); new(&y) Y(Move(c->y)); }
 *
 * especially since GNU C++ fails to notice that this does indeed initialize x
 * and y, which may matter if they're const.
 */
template<typename T>
class MoveRef
{
    T* pointer;

  public:
    explicit MoveRef(T& t) : pointer(&t) { }
    T& operator*() const { return *pointer; }
    T* operator->() const { return pointer; }
    operator T& () const { return *pointer; }
};

template<typename T>
inline MoveRef<T>
OldMove(T& t)
{
  return MoveRef<T>(t);
}

template<typename T>
inline MoveRef<T>
OldMove(const T& t)
{
  // With some versions of gcc, for a class C, there's an (incorrect) ambiguity
  // between the C(const C&) constructor and the default C(C&&) C++11 move
  // constructor, when the constructor is called with a const C& argument.
  //
  // This ambiguity manifests with the Move implementation above when Move is
  // passed const U& for some class U.  Calling Move(const U&) returns a
  // MoveRef<const U&>, which is then commonly passed to the U constructor,
  // triggering an implicit conversion to const U&.  gcc doesn't know whether to
  // call U(const U&) or U(U&&), so it wrongly reports a compile error.
  //
  // http://gcc.gnu.org/bugzilla/show_bug.cgi?id=50442 has since been fixed, so
  // this is no longer an issue for up-to-date compilers.  But there's no harm
  // in keeping it around for older compilers, so we might as well.  See also
  // bug 686280.
  return MoveRef<T>(const_cast<T&>(t));
}

/**
 * Identical to std::Move(); this is necessary until our stlport supports
 * std::move().
 */
template<typename T>
inline typename RemoveReference<T>::Type&&
Move(T&& a)
{
  return static_cast<typename RemoveReference<T>::Type&&>(a);
}

/**
 * These two overloads are identidal to std::Forward(); they are necessary until
 * our stlport supports std::forward().
 */
template<typename T>
inline T&&
Forward(typename RemoveReference<T>::Type& a)
{
  return static_cast<T&&>(a);
}

template<typename T>
inline T&&
Forward(typename RemoveReference<T>::Type&& t)
{
  static_assert(!IsLvalueReference<T>::value,
                "misuse of Forward detected!  try the other overload");
  return static_cast<T&&>(t);
}

/** Swap |t| and |u| using move-construction if possible. */
template<typename T>
inline void
Swap(T& t, T& u)
{
  T tmp(OldMove(t));
  t = OldMove(u);
  u = OldMove(tmp);
}

} // namespace mozilla

#endif /* mozilla_Move_h */
