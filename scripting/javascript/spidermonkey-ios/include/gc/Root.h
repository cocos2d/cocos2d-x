/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsgc_root_h__
#define jsgc_root_h__

#ifdef __cplusplus

#include "mozilla/TypeTraits.h"
#include "mozilla/GuardObjects.h"

#include "js/TemplateLib.h"

#include "jspubtd.h"

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
 * - Rooted<T> declares a variable of type T, whose value is always rooted.
 *   Rooted<T> may be automatically coerced to a Handle<T>, below. Rooted<T>
 *   should be used whenever a local variable's value may be held live across a
 *   call which can allocate GC things or otherwise trigger a GC.
 *
 * - Handle<T> is a const reference to a Rooted<T>. Functions which take GC
 *   things or values as arguments and need to root those arguments should
 *   generally use handles for those arguments and avoid any explicit rooting.
 *   This has two benefits. First, when several such functions call each other
 *   then redundant rooting of multiple copies of the GC thing can be avoided.
 *   Second, if the caller does not pass a rooted value a compile error will be
 *   generated, which is quicker and easier to fix than when relying on a
 *   separate rooting analysis.
 */

namespace js {

template <typename T> class Rooted;

template <typename T>
struct RootMethods {};

template <typename T>
class HandleBase {};

template <typename T>
class MutableHandleBase {};

} /* namespace js */

namespace JS {

class AutoAssertNoGC;

template <typename T> class MutableHandle;

JS_FRIEND_API(void) EnterAssertNoGCScope();
JS_FRIEND_API(void) LeaveAssertNoGCScope();
JS_FRIEND_API(bool) InNoGCScope();

/*
 * Handle provides an implicit constructor for NullPtr so that, given:
 *   foo(Handle<JSObject*> h);
 * callers can simply write:
 *   foo(NullPtr());
 * which avoids creating a Rooted<JSObject*> just to pass NULL.
 */
struct NullPtr
{
    static void * const constNullValue;
};

template <typename T>
class MutableHandle;

/*
 * Reference to a T that has been rooted elsewhere. This is most useful
 * as a parameter type, which guarantees that the T lvalue is properly
 * rooted. See "Move GC Stack Rooting" above.
 *
 * If you want to add additional methods to Handle for a specific
 * specialization, define a HandleBase<T> specialization containing them.
 */
template <typename T>
class Handle : public js::HandleBase<T>
{
  public:
    /* Creates a handle from a handle of a type convertible to T. */
    template <typename S>
    Handle(Handle<S> handle,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0)
    {
        ptr = reinterpret_cast<const T *>(handle.address());
    }

    /* Create a handle for a NULL pointer. */
    Handle(NullPtr) {
        typedef typename js::tl::StaticAssert<js::tl::IsPointerType<T>::result>::result _;
        ptr = reinterpret_cast<const T *>(&NullPtr::constNullValue);
    }

    friend class MutableHandle<T>;
    Handle(MutableHandle<T> handle) {
        ptr = handle.address();
    }

    /*
     * This may be called only if the location of the T is guaranteed
     * to be marked (for some reason other than being a Rooted),
     * e.g., if it is guaranteed to be reachable from an implicit root.
     *
     * Create a Handle from a raw location of a T.
     */
    static Handle fromMarkedLocation(const T *p) {
        Handle h;
        h.ptr = p;
        return h;
    }

    /*
     * Construct a handle from an explicitly rooted location. This is the
     * normal way to create a handle, and normally happens implicitly.
     */
    template <typename S>
    inline
    Handle(js::Rooted<S> &root,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0);

    /* Construct a read only handle from a mutable handle. */
    template <typename S>
    inline
    Handle(MutableHandle<S> &root,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0);

    const T *address() const { return ptr; }
    T get() const { return *ptr; }

    operator T () const { return get(); }
    T operator ->() const { return get(); }

  private:
    Handle() {}

    const T *ptr;

    template <typename S>
    void operator =(S v) MOZ_DELETE;
};

typedef Handle<JSObject*>    HandleObject;
typedef Handle<JSFunction*>  HandleFunction;
typedef Handle<JSScript*>    HandleScript;
typedef Handle<JSString*>    HandleString;
typedef Handle<jsid>         HandleId;
typedef Handle<Value>        HandleValue;

/*
 * Similar to a handle, but the underlying storage can be changed. This is
 * useful for outparams.
 *
 * If you want to add additional methods to MutableHandle for a specific
 * specialization, define a MutableHandleBase<T> specialization containing
 * them.
 */
template <typename T>
class MutableHandle : public js::MutableHandleBase<T>
{
  public:
    template <typename S>
    MutableHandle(MutableHandle<S> handle,
                  typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0)
    {
        this->ptr = reinterpret_cast<const T *>(handle.address());
    }

    template <typename S>
    inline
    MutableHandle(js::Rooted<S> *root,
                  typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0);

    void set(T v)
    {
        JS_ASSERT(!js::RootMethods<T>::poisoned(v));
        *ptr = v;
    }

    /*
     * This may be called only if the location of the T is guaranteed
     * to be marked (for some reason other than being a Rooted),
     * e.g., if it is guaranteed to be reachable from an implicit root.
     *
     * Create a MutableHandle from a raw location of a T.
     */
    static MutableHandle fromMarkedLocation(T *p) {
        MutableHandle h;
        h.ptr = p;
        return h;
    }

    T *address() const { return ptr; }
    T get() const { return *ptr; }

    operator T () const { return get(); }
    T operator ->() const { return get(); }

  private:
    MutableHandle() {}

    T *ptr;

    template <typename S>
    void operator =(S v) MOZ_DELETE;
};

typedef MutableHandle<JSObject*>   MutableHandleObject;
typedef MutableHandle<JSFunction*> MutableHandleFunction;
typedef MutableHandle<JSScript*>   MutableHandleScript;
typedef MutableHandle<JSString*>   MutableHandleString;
typedef MutableHandle<jsid>        MutableHandleId;
typedef MutableHandle<Value>       MutableHandleValue;

/*
 * Raw pointer used as documentation that a parameter does not need to be
 * rooted.
 */
typedef JSObject *                  RawObject;
typedef JSFunction *                RawFunction;
typedef JSScript *                  RawScript;
typedef JSString *                  RawString;
typedef jsid                        RawId;
typedef Value                       RawValue;

} /* namespace JS */

namespace js {

/*
 * InternalHandle is a handle to an internal pointer into a gcthing. Use
 * InternalHandle when you have a pointer to a direct field of a gcthing, or
 * when you need a parameter type for something that *may* be a pointer to a
 * direct field of a gcthing.
 */
template <typename T>
class InternalHandle { };

template <typename T>
class InternalHandle<T*>
{
    void * const *holder;
    size_t offset;

  public:
    /*
     * Create an InternalHandle using a Handle to the gcthing containing the
     * field in question, and a pointer to the field.
     */
    template<typename H>
    InternalHandle(const JS::Handle<H> &handle, T *field)
      : holder((void**)handle.address()), offset(uintptr_t(field) - uintptr_t(handle.get()))
    {
    }

    /*
     * Create an InternalHandle to a field within a Rooted<>.
     */
    template<typename R>
    InternalHandle(const Rooted<R> &root, T *field)
      : holder((void**)root.address()), offset(uintptr_t(field) - uintptr_t(root.get()))
    {
    }

    T *get() const { return reinterpret_cast<T*>(uintptr_t(*holder) + offset); }

    const T& operator *() const { return *get(); }
    T* operator ->() const { return get(); }

    static InternalHandle<T*> fromMarkedLocation(T *fieldPtr) {
        return InternalHandle(fieldPtr);
    }

  private:
    /*
     * Create an InternalHandle to something that is not a pointer to a
     * gcthing, and so does not need to be rooted in the first place. Use these
     * InternalHandles to pass pointers into functions that also need to accept
     * regular InternalHandles to gcthing fields.
     *
     * Make this private to prevent accidental misuse; this is only for
     * fromMarkedLocation().
     */
    InternalHandle(T *field)
      : holder(reinterpret_cast<void * const *>(&NullPtr::constNullValue)),
        offset(uintptr_t(field))
    {
    }
};

#ifdef DEBUG
template <typename T>
class IntermediateNoGC
{
    T t_;

  public:
    IntermediateNoGC(const T &t) : t_(t) {
        EnterAssertNoGCScope();
    }
    IntermediateNoGC(const IntermediateNoGC &) {
        EnterAssertNoGCScope();
    }
    ~IntermediateNoGC() {
        LeaveAssertNoGCScope();
    }

    const T &operator->() { return t_; }
    operator const T &() { return t_; }
};
#endif

/*
 * Return<T> wraps GC things that are returned from accessor methods.  The
 * wrapper helps to ensure correct rooting of the returned pointer and safe
 * access while unrooted.
 *
 * Example usage in a method declaration:
 *
 *     class Foo {
 *         HeapPtrScript script_;
 *         ...
 *       public:
 *          Return<JSScript*> script() { return script_; }
 *     };
 *
 * Example usage of method (1):
 *
 *     Foo foo(...);
 *     RootedScript script(cx, foo->script());
 *
 * Example usage of method (2):
 *
 *     Foo foo(...);
 *     foo->script()->needsArgsObj();
 *
 * The purpose of this class is to assert eagerly on incorrect use of GC thing
 * pointers. For example:
 *
 *    RootedShape shape(cx, ...);
 *    shape->parent.init(js_NewGCThing<Shape*>(cx, ...));
 *
 * In this expression, C++ is allowed to order these calls as follows:
 *
 *   Call                           Effect
 *   ----                           ------
 *   1) RootedShape::operator->     Stores shape::ptr_ to stack.
 *   2) js_NewGCThing<Shape*>       Triggers GC and compaction of shapes. This
 *                                  moves shape::ptr_ to a new location.
 *   3) HeapPtrObject::init         This call takes the relocated shape::ptr_
 *                                  as |this|, crashing or, worse, corrupting
 *                                  the program's state on the first access
 *                                  to a member variable.
 *
 * If Shape::parent were an accessor function returning a Return<Shape*>, this
 * could not happen: Return ensures either immediate rooting or no GC within
 * the same expression.
 */
template <typename T>
class Return
{
    friend class Rooted<T>;

    const T ptr_;

  public:
    template <typename S>
    Return(const S &ptr,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0)
      : ptr_(ptr)
    {}

    Return(NullPtr) : ptr_(NULL) {}

    /*
     * |get(AutoAssertNoGC &)| is the safest way to access a Return<T> without
     * rooting it first: it is impossible to call this method without an
     * AutoAssertNoGC in scope, so the compiler will automatically catch any
     * incorrect usage.
     *
     * Example:
     *     AutoAssertNoGC nogc;
     *     RawScript script = fun->script().get(nogc);
     */
    const T &get(AutoAssertNoGC &) const {
        return ptr_;
    }

    /*
     * |operator->|'s result cannot be stored in a local variable, so it is safe
     * to use in a CanGC context iff no GC can occur anywhere within the same
     * expression (generally from one |;| to the next). |operator->| uses a
     * temporary object as a guard and will assert if a CanGC context is
     * encountered before the next C++ Sequence Point.
     *
     * INCORRECT:
     *    fun->script()->bindings = myBindings->clone(cx, ...);
     *
     * The compiler is allowed to reorder |fun->script()::operator->()| above
     * the call to |clone(cx, ...)|. In this case, the RawScript C++ stores on
     * the stack may be corrupted by a GC under |clone|. The subsequent
     * dereference of this pointer to get |bindings| will result in an invalid
     * access. This wrapper ensures that such usage asserts in DEBUG builds when
     * it encounters this situation. Without this assertion, it is possible for
     * such access to corrupt program state instead of crashing immediately.
     *
     * CORRECT:
     *    RootedScript clone(cx, myBindings->clone(cx, ...));
     *    fun->script()->bindings = clone;
     */
#ifdef DEBUG
    IntermediateNoGC<T> operator->() const {
        return IntermediateNoGC<T>(ptr_);
    }
#else
    const T &operator->() const {
        return ptr_;
    }
#endif

    /*
     * |unsafeGet()| is unsafe for most uses.  Although it performs similar
     * checking to |operator->|, its result can be stored to a local variable.
     * For this reason, it should only be used when it would be incorrect or
     * absurd to create a new Rooted for its use: e.g. for assertions.
     */
#ifdef DEBUG
    IntermediateNoGC<T> unsafeGet() const {
        return IntermediateNoGC<T>(ptr_);
    }
#else
    const T &unsafeGet() const {
        return ptr_;
    }
#endif

    /*
     * |operator==| is safe to use in any context.  It is present to allow:
     *     JS_ASSERT(myScript == fun->script().unsafeGet());
     *
     * To be rewritten as:
     *     JS_ASSERT(fun->script() == myScript);
     *
     * Note: the new order tells C++ to use |Return<JSScript*>::operator=|
     *       instead of direct pointer comparison.
     */
    bool operator==(const T &other) { return ptr_ == other; }
    bool operator!=(const T &other) { return ptr_ != other; }
    bool operator==(const Return<T> &other) { return ptr_ == other.ptr_; }
    bool operator==(const JS::Handle<T> &other) { return ptr_ == other.get(); }
    inline bool operator==(const Rooted<T> &other);
};

/*
 * By default, pointers should use the inheritance hierarchy to find their
 * ThingRootKind. Some pointer types are explicitly set in jspubtd.h so that
 * Rooted<T> may be used without the class definition being available.
 */
template <typename T>
struct RootKind<T *> { static ThingRootKind rootKind() { return T::rootKind(); } };

template <typename T>
struct RootMethods<T *>
{
    static T *initial() { return NULL; }
    static ThingRootKind kind() { return RootKind<T *>::rootKind(); }
    static bool poisoned(T *v) { return IsPoisonedPtr(v); }
};

template <typename T>
class RootedBase {};

/*
 * Local variable of type T whose value is always rooted. This is typically
 * used for local variables, or for non-rooted values being passed to a
 * function that requires a handle, e.g. Foo(Root<T>(cx, x)).
 *
 * If you want to add additional methods to Rooted for a specific
 * specialization, define a RootedBase<T> specialization containing them.
 */
template <typename T>
class Rooted : public RootedBase<T>
{
    void init(JSContext *cxArg)
    {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        ContextFriendFields *cx = ContextFriendFields::get(cxArg);
        commonInit(cx->thingGCRooters);
#endif
    }

    void init(JSRuntime *rtArg)
    {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        PerThreadDataFriendFields *pt = PerThreadDataFriendFields::getMainThread(rtArg);
        commonInit(pt->thingGCRooters);
#endif
    }

    void init(js::PerThreadData *ptArg)
    {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        PerThreadDataFriendFields *pt = PerThreadDataFriendFields::get(ptArg);
        commonInit(pt->thingGCRooters);
#endif
    }

  public:
    Rooted(JSRuntime *rt
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(RootMethods<T>::initial())
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(rt);
    }

    Rooted(JSRuntime *rt, T initial
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(initial)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(rt);
    }

    Rooted(JSContext *cx
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(RootMethods<T>::initial())
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(cx);
    }

    Rooted(JSContext *cx, T initial
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(initial)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(cx);
    }

    Rooted(js::PerThreadData *pt
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(RootMethods<T>::initial())
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(pt);
    }

    Rooted(js::PerThreadData *pt, T initial
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(initial)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(pt);
    }

    template <typename S>
    Rooted(JSContext *cx, const Return<S> &initial
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(initial.ptr_)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(cx);
    }

    template <typename S>
    Rooted(js::PerThreadData *pt, const Return<S> &initial
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(initial.ptr_)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        init(pt);
    }

    ~Rooted()
    {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        JS_ASSERT(*stack == this);
        *stack = prev;
#endif
    }

#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
    Rooted<T> *previous() { return prev; }
#endif

    operator T () const { return ptr; }
    T operator ->() const { return ptr; }
    T * address() { return &ptr; }
    const T * address() const { return &ptr; }
    T & get() { return ptr; }
    const T & get() const { return ptr; }

    T & operator =(T value)
    {
        JS_ASSERT(!RootMethods<T>::poisoned(value));
        ptr = value;
        return ptr;
    }

    T & operator =(const Rooted &value)
    {
        ptr = value;
        return ptr;
    }

    template <typename S>
    T & operator =(const Return<S> &value)
    {
        ptr = value.ptr_;
        return ptr;
    }

  private:
    void commonInit(Rooted<void*> **thingGCRooters) {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        ThingRootKind kind = RootMethods<T>::kind();
        this->stack = reinterpret_cast<Rooted<T>**>(&thingGCRooters[kind]);
        this->prev = *stack;
        *stack = this;

        JS_ASSERT(!RootMethods<T>::poisoned(ptr));
#endif
    }

#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
    Rooted<T> **stack, *prev;
#endif
    T ptr;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

    Rooted(const Rooted &) MOZ_DELETE;
};

#if !(defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING))
// Defined in vm/String.h.
template <>
class Rooted<JSStableString *>;
#endif

template <typename T>
bool
Return<T>::operator==(const Rooted<T> &other)
{
    return ptr_ == other.get();
}

typedef Rooted<JSObject*>    RootedObject;
typedef Rooted<JSFunction*>  RootedFunction;
typedef Rooted<JSScript*>    RootedScript;
typedef Rooted<JSString*>    RootedString;
typedef Rooted<jsid>         RootedId;
typedef Rooted<Value>        RootedValue;

/*
 * Mark a stack location as a root for the rooting analysis, without actually
 * rooting it in release builds. This should only be used for stack locations
 * of GC things that cannot be relocated by a garbage collection, and that
 * are definitely reachable via another path.
 */
class SkipRoot
{
#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)

    SkipRoot **stack, *prev;
    const uint8_t *start;
    const uint8_t *end;

    template <typename T>
    void init(ContextFriendFields *cx, const T *ptr, size_t count)
    {
        this->stack = &cx->skipGCRooters;
        this->prev = *stack;
        *stack = this;
        this->start = (const uint8_t *) ptr;
        this->end = this->start + (sizeof(T) * count);
    }

  public:
    template <typename T>
    SkipRoot(JSContext *cx, const T *ptr, size_t count = 1
             JS_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        init(ContextFriendFields::get(cx), ptr, count);
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
    SkipRoot(JSContext *cx, const T *ptr, size_t count = 1
              JS_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        JS_GUARD_OBJECT_NOTIFIER_INIT;
    }

#endif /* DEBUG && JSGC_ROOT_ANALYSIS */

    JS_DECL_USE_GUARD_OBJECT_NOTIFIER
};

} /* namespace js */

namespace JS {

template<typename T> template <typename S>
inline
Handle<T>::Handle(js::Rooted<S> &root,
                  typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy)
{
    ptr = reinterpret_cast<const T *>(root.address());
}

template<typename T> template <typename S>
inline
Handle<T>::Handle(MutableHandle<S> &root,
                  typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy)
{
    ptr = reinterpret_cast<const T *>(root.address());
}

template<typename T> template <typename S>
inline
MutableHandle<T>::MutableHandle(js::Rooted<S> *root,
                                typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy)
{
    ptr = root->address();
}

/*
 * The scoped guard object AutoAssertNoGC forces the GC to assert if a GC is
 * attempted while the guard object is live.  If you have a GC-unsafe operation
 * to perform, use this guard object to protect your operation.
 */
class AutoAssertNoGC
{
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

public:
    AutoAssertNoGC(MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM) {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
#ifdef DEBUG
        EnterAssertNoGCScope();
#endif
    }

    ~AutoAssertNoGC() {
#ifdef DEBUG
        LeaveAssertNoGCScope();
#endif
    }
};

/*
 * AssertCanGC will assert if it is called inside of an AutoAssertNoGC region.
 */
JS_ALWAYS_INLINE void
AssertCanGC()
{
    JS_ASSERT(!InNoGCScope());
}

#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
extern void
CheckStackRoots(JSContext *cx);
#endif

JS_FRIEND_API(bool) NeedRelaxedRootChecks();

} /* namespace JS */

namespace js {

/*
 * Hook for dynamic root analysis. Checks the native stack and poisons
 * references to GC things which have not been rooted.
 */
inline void MaybeCheckStackRoots(JSContext *cx, bool relax = true)
{
    AssertCanGC();
#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
    if (relax && NeedRelaxedRootChecks())
        return;
    CheckStackRoots(cx);
#endif
}

namespace gc {
struct Cell;
} /* namespace gc */

/* Base class for automatic read-only object rooting during compilation. */
class CompilerRootNode
{
  protected:
    CompilerRootNode(js::gc::Cell *ptr)
      : next(NULL), ptr(ptr)
    { }

  public:
    void **address() { return (void **)&ptr; }

  public:
    CompilerRootNode *next;

  protected:
    js::gc::Cell *ptr;
};

}  /* namespace js */

#endif  /* __cplusplus */

#endif  /* jsgc_root_h___ */
