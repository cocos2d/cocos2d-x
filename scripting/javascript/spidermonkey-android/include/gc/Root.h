/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
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
 * The Original Code is SpiderMonkey global object code.
 *
 * The Initial Developer of the Original Code is
 * the Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2012
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

#ifndef jsgc_root_h__
#define jsgc_root_h__

#include "jspubtd.h"

#include "js/Utility.h"

#ifdef __cplusplus

namespace JS {

/*
 * Moving GC Stack Rooting
 *
 * A moving GC may change the physical location of GC allocated things, even
 * when they are rooted, updating all pointers to the thing to refer to its new
 * location. The GC must therefore know about all live pointers to a thing,
 * not just one of them, in order to behave correctly.
 *
 * The classes below are used to root stack locations whose value may be held
 * live across a call that can trigger GC (i.e. a call which might allocate any
 * GC things). For a code fragment such as:
 *
 * Foo();
 * ... = obj->lastProperty();
 *
 * If Foo() can trigger a GC, the stack location of obj must be rooted to
 * ensure that the GC does not move the JSObject referred to by obj without
 * updating obj's location itself. This rooting must happen regardless of
 * whether there are other roots which ensure that the object itself will not
 * be collected.
 *
 * If Foo() cannot trigger a GC, and the same holds for all other calls made
 * between obj's definitions and its last uses, then no rooting is required.
 *
 * Several classes are available for rooting stack locations. All are templated
 * on the type T of the value being rooted, for which RootMethods<T> must
 * have an instantiation.
 *
 * - Root<T> roots an existing stack allocated variable or other location of
 *   type T. This is typically used either when a variable only needs to be
 *   rooted on certain rare paths, or when a function takes a bare GC thing
 *   pointer as an argument and needs to root it. In the latter case a
 *   Handle<T> is generally preferred, see below.
 *
 * - RootedVar<T> declares a variable of type T, whose value is always rooted.
 *
 * - Handle<T> is a const reference to a Root<T> or RootedVar<T>. Handles are
 *   coerced automatically from such a Root<T> or RootedVar<T>. Functions which
 *   take GC things or values as arguments and need to root those arguments
 *   should generally replace those arguments with handles and avoid any
 *   explicit rooting. This has two benefits. First, when several such
 *   functions call each other then redundant rooting of multiple copies of the
 *   GC thing can be avoided. Second, if the caller does not pass a rooted
 *   value a compile error will be generated, which is quicker and easier to
 *   fix than when relying on a separate rooting analysis.
 */

template <typename T> class Root;
template <typename T> class RootedVar;

template <typename T>
struct RootMethods { };

/*
 * Reference to a stack location rooted for GC. See the "Moving GC Stack
 * Rooting" comment above.
 */
template <typename T>
class Handle
{
  public:
    /* Copy handles of different types, with implicit coercion. */
    template <typename S> Handle(Handle<S> handle) {
        testAssign<S>();
        ptr = reinterpret_cast<const T *>(handle.address());
    }

    /* Get a handle from a rooted stack location, with implicit coercion. */
    template <typename S> inline Handle(const Root<S> &root);
    template <typename S> inline Handle(const RootedVar<S> &root);

    const T *address() { return ptr; }

    operator T () { return value(); }
    T operator ->() { return value(); }

  private:
    const T *ptr;
    T value() { return *ptr; }

    template <typename S>
    void testAssign() {
#ifdef DEBUG
        T a = RootMethods<T>::initial();
        S b = RootMethods<S>::initial();
        a = b;
        (void)a;
#endif
    }
};

typedef Handle<JSObject*>    HandleObject;
typedef Handle<JSFunction*>  HandleFunction;
typedef Handle<JSString*>    HandleString;
typedef Handle<jsid>         HandleId;
typedef Handle<Value>        HandleValue;

template <typename T>
struct RootMethods<T *>
{
    static T *initial() { return NULL; }
    static ThingRootKind kind() { return T::rootKind(); }
    static bool poisoned(T *v) { return IsPoisonedPtr(v); }
};

/*
 * Root a stack location holding a GC thing. This takes a stack pointer
 * and ensures that throughout its lifetime the referenced variable
 * will remain pinned against a moving GC.
 *
 * It is important to ensure that the location referenced by a Root is
 * initialized, as otherwise the GC may try to use the the uninitialized value.
 * It is generally preferable to use either RootedVar for local variables, or
 * Handle for arguments.
 */
template <typename T>
class Root
{
  public:
    Root(JSContext *cx_, const T *ptr
         JS_GUARD_OBJECT_NOTIFIER_PARAM)
    {
#ifdef JSGC_ROOT_ANALYSIS
        ContextFriendFields *cx = ContextFriendFields::get(cx_);

        ThingRootKind kind = RootMethods<T>::kind();
        this->stack = reinterpret_cast<Root<T>**>(&cx->thingGCRooters[kind]);
        this->prev = *stack;
        *stack = this;
#endif

        JS_ASSERT(!RootMethods<T>::poisoned(*ptr));

        this->ptr = ptr;

        JS_GUARD_OBJECT_NOTIFIER_INIT;
    }

    ~Root()
    {
#ifdef JSGC_ROOT_ANALYSIS
        JS_ASSERT(*stack == this);
        *stack = prev;
#endif
    }

#ifdef JSGC_ROOT_ANALYSIS
    Root<T> *previous() { return prev; }
#endif

    const T *address() const { return ptr; }

  private:

#ifdef JSGC_ROOT_ANALYSIS
    Root<T> **stack, *prev;
#endif
    const T *ptr;

    JS_DECL_USE_GUARD_OBJECT_NOTIFIER
};

template<typename T> template <typename S>
inline
Handle<T>::Handle(const Root<S> &root)
{
    testAssign<S>();
    ptr = reinterpret_cast<const T *>(root.address());
}

typedef Root<JSObject*>    RootObject;
typedef Root<JSFunction*>  RootFunction;
typedef Root<JSString*>    RootString;
typedef Root<jsid>         RootId;
typedef Root<Value>        RootValue;

/*
 * Mark a stack location as a root for the rooting analysis, without actually
 * rooting it in release builds. This should only be used for stack locations
 * of GC things that cannot be relocated by a garbage collection, and that
 * are definitely reachable via another path.
 */
class SkipRoot
{
#if defined(DEBUG) && defined(JSGC_ROOT_ANALYSIS)

    SkipRoot **stack, *prev;
    const uint8_t *start;
    const uint8_t *end;

  public:
    template <typename T>
    SkipRoot(JSContext *cx_, const T *ptr
              JS_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        ContextFriendFields *cx = ContextFriendFields::get(cx_);

        this->stack = &cx->skipGCRooters;
        this->prev = *stack;
        *stack = this;
        this->start = (const uint8_t *) ptr;
        this->end = this->start + sizeof(T);
        JS_GUARD_OBJECT_NOTIFIER_INIT;
    }

    ~SkipRoot()
    {
        JS_ASSERT(*stack == this);
        *stack = prev;
    }

    SkipRoot *previous() { return prev; }

    bool contains(const uint8_t *v, size_t len) {
        return v >= start && v + len <= end;
    }

#else /* DEBUG && JSGC_ROOT_ANALYSIS */

  public:
    template <typename T>
    SkipRoot(JSContext *cx, const T *ptr
              JS_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        JS_GUARD_OBJECT_NOTIFIER_INIT;
    }

#endif /* DEBUG && JSGC_ROOT_ANALYSIS */

    JS_DECL_USE_GUARD_OBJECT_NOTIFIER
};

/* Make a local variable which stays rooted throughout its lifetime. */
template <typename T>
class RootedVar
{
  public:
    RootedVar(JSContext *cx)
      : ptr(RootMethods<T>::initial()), root(cx, &ptr)
    {}

    RootedVar(JSContext *cx, T initial)
      : ptr(initial), root(cx, &ptr)
    {}

    operator T () const { return ptr; }
    T operator ->() const { return ptr; }
    T * address() { return &ptr; }
    const T * address() const { return &ptr; }
    T & reference() { return ptr; }
    T raw() { return ptr; }

    /*
     * This method is only necessary due to an obscure C++98 requirement (that
     * there be an accessible, usable copy constructor when passing a temporary
     * to an implicitly-called constructor for use with a const-ref parameter).
     * (Head spinning yet?)  We can remove this when we build the JS engine
     * with -std=c++11.
     */
    operator Handle<T> () const { return Handle<T>(*this); }

    T & operator =(T value)
    {
        JS_ASSERT(!RootMethods<T>::poisoned(value));
        ptr = value;
        return ptr;
    }

    T & operator =(const RootedVar &value)
    {
        ptr = value;
        return ptr;
    }

  private:
    T ptr;
    Root<T> root;

    RootedVar() MOZ_DELETE;
    RootedVar(const RootedVar &) MOZ_DELETE;
};

template <typename T> template <typename S>
inline
Handle<T>::Handle(const RootedVar<S> &root)
{
    testAssign<S>();
    ptr = reinterpret_cast<const T *>(root.address());
}

typedef RootedVar<JSObject*>    RootedVarObject;
typedef RootedVar<JSFunction*>  RootedVarFunction;
typedef RootedVar<JSString*>    RootedVarString;
typedef RootedVar<jsid>         RootedVarId;
typedef RootedVar<Value>        RootedVarValue;

}  /* namespace JS */

#endif  /* __cplusplus */

#endif  /* jsgc_root_h___ */
