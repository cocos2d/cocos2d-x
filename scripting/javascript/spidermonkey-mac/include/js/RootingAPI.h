/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sw=4 et tw=78:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsgc_root_h__
#define jsgc_root_h__

#include "mozilla/GuardObjects.h"
#include "mozilla/TypeTraits.h"

#include "js/Utility.h"
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
 * The |Root| and |Handle| classes below are used to root stack locations
 * whose value may be held live across a call that can trigger GC. For a
 * code fragment such as:
 *
 * JSObject *obj = NewObject(cx);
 * DoSomething(cx);
 * ... = obj->lastProperty();
 *
 * If |DoSomething()| can trigger a GC, the stack location of |obj| must be
 * rooted to ensure that the GC does not move the JSObject referred to by
 * |obj| without updating |obj|'s location itself. This rooting must happen
 * regardless of whether there are other roots which ensure that the object
 * itself will not be collected.
 *
 * If |DoSomething()| cannot trigger a GC, and the same holds for all other
 * calls made between |obj|'s definitions and its last uses, then no rooting
 * is required.
 *
 * SpiderMonkey can trigger a GC at almost any time and in ways that are not
 * always clear. For example, the following innocuous-looking actions can
 * cause a GC: allocation of any new GC thing; JSObject::hasProperty;
 * JS_ReportError and friends; and ToNumber, among many others. The following
 * dangerous-looking actions cannot trigger a GC: js_malloc, cx->malloc_,
 * rt->malloc_, and friends and JS_ReportOutOfMemory.
 *
 * The following family of four classes will exactly root a stack location.
 * Incorrect usage of these classes will result in a compile error in almost
 * all cases. Therefore, it is very hard to be incorrectly rooted if you use
 * these classes exclusively. These classes are all templated on the type T of
 * the value being rooted.
 *
 * - Rooted<T> declares a variable of type T, whose value is always rooted.
 *   Rooted<T> may be automatically coerced to a Handle<T>, below. Rooted<T>
 *   should be used whenever a local variable's value may be held live across a
 *   call which can trigger a GC. This is generally true of
 *
 * - Handle<T> is a const reference to a Rooted<T>. Functions which take GC
 *   things or values as arguments and need to root those arguments should
 *   generally use handles for those arguments and avoid any explicit rooting.
 *   This has two benefits. First, when several such functions call each other
 *   then redundant rooting of multiple copies of the GC thing can be avoided.
 *   Second, if the caller does not pass a rooted value a compile error will be
 *   generated, which is quicker and easier to fix than when relying on a
 *   separate rooting analysis.
 *
 * - MutableHandle<T> is a non-const reference to Rooted<T>. It is used in the
 *   same way as Handle<T> and includes a |set(const T &v)| method to allow
 *   updating the value of the referenced Rooted<T>. A MutableHandle<T> can be
 *   created from a Rooted<T> by using |Rooted<T>::operator&()|.
 *
 * In some cases the small performance overhead of exact rooting is too much.
 * In these cases, try the following:
 *
 * - Move all Rooted<T> above inner loops: this allows you to re-use the root
 *   on each iteration of the loop.
 *
 * - Pass Handle<T> through your hot call stack to avoid re-rooting costs at
 *   every invocation.
 *
 * There also exists a set of RawT typedefs for modules without rooting
 * concerns, such as the GC. Do not use these as they provide no rooting
 * protection whatsoever.
 *
 * The following diagram explains the list of supported, implicit type
 * conversions between classes of this family:
 *
 *  RawT -----> Rooted<T> ----> Handle<T>
 *                 |               ^
 *                 |               |
 *                 |               |
 *                 +---> MutableHandle<T>
 *                 (via &)
 *
 * Currently all of these types implicit conversion to RawT. These are present
 * only for the purpose of bootstrapping exact rooting and will be removed in
 * the future (Bug 817164).
 */

namespace js {

class Module;

template <typename T>
struct RootMethods {};

template <typename T>
class RootedBase {};

template <typename T>
class HandleBase {};

template <typename T>
class MutableHandleBase {};

/*
 * js::NullPtr acts like a NULL pointer in contexts that require a Handle.
 *
 * Handle provides an implicit constructor for js::NullPtr so that, given:
 *   foo(Handle<JSObject*> h);
 * callers can simply write:
 *   foo(js::NullPtr());
 * which avoids creating a Rooted<JSObject*> just to pass NULL.
 *
 * This is the SpiderMonkey internal variant. js::NullPtr should be used in
 * preference to JS::NullPtr to avoid the GOT access required for JS_PUBLIC_API
 * symbols.
 */
struct NullPtr
{
    static void * const constNullValue;
};

} /* namespace js */

namespace JS {

template <typename T> class Rooted;

template <typename T> class Handle;
template <typename T> class MutableHandle;

/* This is exposing internal state of the GC for inlining purposes. */
JS_FRIEND_API(bool) isGCEnabled();

#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
extern void
CheckStackRoots(JSContext *cx);
#endif

/*
 * JS::NullPtr acts like a NULL pointer in contexts that require a Handle.
 *
 * Handle provides an implicit constructor for JS::NullPtr so that, given:
 *   foo(Handle<JSObject*> h);
 * callers can simply write:
 *   foo(JS::NullPtr());
 * which avoids creating a Rooted<JSObject*> just to pass NULL.
 */
struct JS_PUBLIC_API(NullPtr)
{
    static void * const constNullValue;
};

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
    friend class MutableHandle<T>;

  public:
    /* Creates a handle from a handle of a type convertible to T. */
    template <typename S>
    Handle(Handle<S> handle,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0)
    {
        ptr = reinterpret_cast<const T *>(handle.address());
    }

    /* Create a handle for a NULL pointer. */
    Handle(js::NullPtr) {
        MOZ_STATIC_ASSERT(mozilla::IsPointer<T>::value,
                          "js::NullPtr overload not valid for non-pointer types");
        ptr = reinterpret_cast<const T *>(&js::NullPtr::constNullValue);
    }

    /* Create a handle for a NULL pointer. */
    Handle(JS::NullPtr) {
        MOZ_STATIC_ASSERT(mozilla::IsPointer<T>::value,
                          "JS::NullPtr overload not valid for non-pointer types");
        ptr = reinterpret_cast<const T *>(&JS::NullPtr::constNullValue);
    }

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
    Handle(Rooted<S> &root,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0);

    /* Construct a read only handle from a mutable handle. */
    template <typename S>
    inline
    Handle(MutableHandle<S> &root,
           typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy = 0);

    const T *address() const { return ptr; }
    T get() const { return *ptr; }

    operator T() const { return get(); }
    T operator->() const { return get(); }

    bool operator!=(const T &other) { return *ptr != other; }
    bool operator==(const T &other) { return *ptr == other; }

  private:
    Handle() {}

    const T *ptr;

    template <typename S>
    void operator=(S v) MOZ_DELETE;
};

typedef Handle<JSObject*>    HandleObject;
typedef Handle<js::Module*>  HandleModule;
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
    inline MutableHandle(Rooted<T> *root);

    void set(T v) {
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

    operator T() const { return get(); }
    T operator->() const { return get(); }

  private:
    MutableHandle() {}

    T *ptr;

    template <typename S>
    void operator=(S v) MOZ_DELETE;
};

typedef MutableHandle<JSObject*>   MutableHandleObject;
typedef MutableHandle<JSFunction*> MutableHandleFunction;
typedef MutableHandle<JSScript*>   MutableHandleScript;
typedef MutableHandle<JSString*>   MutableHandleString;
typedef MutableHandle<jsid>        MutableHandleId;
typedef MutableHandle<Value>       MutableHandleValue;

} /* namespace JS */

namespace js {

/*
 * Raw pointer used as documentation that a parameter does not need to be
 * rooted.
 */
typedef JSObject *                  RawObject;
typedef JSString *                  RawString;
typedef jsid                        RawId;
typedef JS::Value                   RawValue;

/*
 * InternalHandle is a handle to an internal pointer into a gcthing. Use
 * InternalHandle when you have a pointer to a direct field of a gcthing, or
 * when you need a parameter type for something that *may* be a pointer to a
 * direct field of a gcthing.
 */
template <typename T>
class InternalHandle {};

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
    {}

    /*
     * Create an InternalHandle to a field within a Rooted<>.
     */
    template<typename R>
    InternalHandle(const JS::Rooted<R> &root, T *field)
      : holder((void**)root.address()), offset(uintptr_t(field) - uintptr_t(root.get()))
    {}

    T *get() const { return reinterpret_cast<T*>(uintptr_t(*holder) + offset); }

    const T &operator*() const { return *get(); }
    T *operator->() const { return get(); }

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
      : holder(reinterpret_cast<void * const *>(&js::NullPtr::constNullValue)),
        offset(uintptr_t(field))
    {}
};

/*
 * This macro simplifies forward declaration of a class and its matching raw-pointer.
 */
# define ForwardDeclare(type)              \
    class type;                            \
    typedef type * Raw##type

# define ForwardDeclareJS(type)            \
    class JS##type;                        \
    namespace js {                         \
        typedef JS##type * Raw##type;      \
    }                                      \
    class JS##type

/*
 * By default, pointers should use the inheritance hierarchy to find their
 * ThingRootKind. Some pointer types are explicitly set in jspubtd.h so that
 * Rooted<T> may be used without the class definition being available.
 */
template <typename T>
struct RootKind<T *>
{
    static ThingRootKind rootKind() { return T::rootKind(); }
};

template <typename T>
struct RootMethods<T *>
{
    static T *initial() { return NULL; }
    static ThingRootKind kind() { return RootKind<T *>::rootKind(); }
    static bool poisoned(T *v) { return JS::IsPoisonedPtr(v); }
};

} /* namespace js */

namespace JS {

/*
 * Local variable of type T whose value is always rooted. This is typically
 * used for local variables, or for non-rooted values being passed to a
 * function that requires a handle, e.g. Foo(Root<T>(cx, x)).
 *
 * If you want to add additional methods to Rooted for a specific
 * specialization, define a RootedBase<T> specialization containing them.
 */
template <typename T>
class Rooted : public js::RootedBase<T>
{
    void init(JSContext *cxArg) {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        js::ContextFriendFields *cx = js::ContextFriendFields::get(cxArg);
        commonInit(cx->thingGCRooters);
#endif
    }

    void init(js::PerThreadData *ptArg) {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        js::PerThreadDataFriendFields *pt = js::PerThreadDataFriendFields::get(ptArg);
        commonInit(pt->thingGCRooters);
#endif
    }

  public:
    Rooted(JSContext *cx
           MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(js::RootMethods<T>::initial())
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
      : ptr(js::RootMethods<T>::initial())
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

    ~Rooted() {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        JS_ASSERT(*stack == reinterpret_cast<Rooted<void*>*>(this));
        *stack = prev;
#endif
    }

#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
    Rooted<T> *previous() { return prev; }
#endif

    operator T() const { return ptr; }
    T operator->() const { return ptr; }
    T *address() { return &ptr; }
    const T *address() const { return &ptr; }
    T &get() { return ptr; }
    const T &get() const { return ptr; }

    T &operator=(T value) {
        JS_ASSERT(!js::RootMethods<T>::poisoned(value));
        ptr = value;
        return ptr;
    }

    T &operator=(const Rooted &value) {
        ptr = value;
        return ptr;
    }

    bool operator!=(const T &other) { return ptr != other; }
    bool operator==(const T &other) { return ptr == other; }

  private:
    void commonInit(Rooted<void*> **thingGCRooters) {
#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
        js::ThingRootKind kind = js::RootMethods<T>::kind();
        this->stack = &thingGCRooters[kind];
        this->prev = *stack;
        *stack = reinterpret_cast<Rooted<void*>*>(this);

        JS_ASSERT(!js::RootMethods<T>::poisoned(ptr));
#endif
    }

#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
    Rooted<void*> **stack, *prev;
#endif

#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
    /* Has the rooting analysis ever scanned this Rooted's stack location? */
    friend void JS::CheckStackRoots(JSContext*);
    bool scanned;
#endif

    /*
     * |ptr| must be the last field in Rooted because the analysis treats all
     * Rooted as Rooted<void*> during the analysis. See bug 829372.
     */
    T ptr;

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

    Rooted(const Rooted &) MOZ_DELETE;
};

#if !(defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING))
// Defined in vm/String.h.
template <>
class Rooted<JSStableString *>;
#endif

typedef Rooted<JSObject*>    RootedObject;
typedef Rooted<js::Module*>  RootedModule;
typedef Rooted<JSFunction*>  RootedFunction;
typedef Rooted<JSScript*>    RootedScript;
typedef Rooted<JSString*>    RootedString;
typedef Rooted<jsid>         RootedId;
typedef Rooted<JS::Value>    RootedValue;

} /* namespace JS */

namespace js {

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
    void init(SkipRoot **head, const T *ptr, size_t count) {
        this->stack = head;
        this->prev = *stack;
        *stack = this;
        this->start = (const uint8_t *) ptr;
        this->end = this->start + (sizeof(T) * count);
    }

  public:
    template <typename T>
    SkipRoot(JSContext *cx, const T *ptr, size_t count = 1
             MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        init(&ContextFriendFields::get(cx)->skipGCRooters, ptr, count);
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    template <typename T>
    SkipRoot(js::PerThreadData *ptd, const T *ptr, size_t count = 1
             MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        PerThreadDataFriendFields *ptff = PerThreadDataFriendFields::get(ptd);
        init(&ptff->skipGCRooters, ptr, count);
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    ~SkipRoot() {
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
             MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    template <typename T>
    SkipRoot(PerThreadData *ptd, const T *ptr, size_t count = 1
             MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

#endif /* DEBUG && JSGC_ROOT_ANALYSIS */

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

/* Interface substitute for Rooted<T> which does not root the variable's memory. */
template <typename T>
class FakeRooted : public RootedBase<T>
{
  public:
    FakeRooted(JSContext *cx
                MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(RootMethods<T>::initial())
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    FakeRooted(JSContext *cx, T initial
                MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : ptr(initial)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    operator T() const { return ptr; }
    T operator->() const { return ptr; }
    T *address() { return &ptr; }
    const T *address() const { return &ptr; }
    T &get() { return ptr; }
    const T &get() const { return ptr; }

    T &operator=(T value) {
        JS_ASSERT(!RootMethods<T>::poisoned(value));
        ptr = value;
        return ptr;
    }

    bool operator!=(const T &other) { return ptr != other; }
    bool operator==(const T &other) { return ptr == other; }

  private:
    T ptr;

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

    FakeRooted(const FakeRooted &) MOZ_DELETE;
};

/* Interface substitute for MutableHandle<T> which is not required to point to rooted memory. */
template <typename T>
class FakeMutableHandle : public js::MutableHandleBase<T>
{
  public:
    FakeMutableHandle(T *t) {
        ptr = t;
    }

    FakeMutableHandle(FakeRooted<T> *root) {
        ptr = root->address();
    }

    void set(T v) {
        JS_ASSERT(!js::RootMethods<T>::poisoned(v));
        *ptr = v;
    }

    T *address() const { return ptr; }
    T get() const { return *ptr; }

    operator T() const { return get(); }
    T operator->() const { return get(); }

  private:
    FakeMutableHandle() {}

    T *ptr;

    template <typename S>
    void operator=(S v) MOZ_DELETE;
};

/*
 * Types for a variable that either should or shouldn't be rooted, depending on
 * the template parameter Rooted. Used for implementing functions that can
 * operate on either rooted or unrooted data.
 *
 * The toHandle() and toMutableHandle() functions are for calling functions
 * which require handle types and are only called in the CanGC case. These
 * allow the calling code to type check.
 */
enum AllowGC {
    NoGC = 0,
    CanGC = 1
};
template <typename T, AllowGC allowGC>
class MaybeRooted
{
};

template <typename T> class MaybeRooted<T, CanGC>
{
  public:
    typedef JS::Handle<T> HandleType;
    typedef JS::Rooted<T> RootType;
    typedef JS::MutableHandle<T> MutableHandleType;

    static inline JS::Handle<T> toHandle(HandleType v) {
        return v;
    }

    static inline JS::MutableHandle<T> toMutableHandle(MutableHandleType v) {
        return v;
    }
};

template <typename T> class MaybeRooted<T, NoGC>
{
  public:
    typedef T HandleType;
    typedef FakeRooted<T> RootType;
    typedef FakeMutableHandle<T> MutableHandleType;

    static inline JS::Handle<T> toHandle(HandleType v) {
        JS_NOT_REACHED("Bad conversion");
        return JS::Handle<T>::fromMarkedLocation(NULL);
    }

    static inline JS::MutableHandle<T> toMutableHandle(MutableHandleType v) {
        JS_NOT_REACHED("Bad conversion");
        return JS::MutableHandle<T>::fromMarkedLocation(NULL);
    }
};

} /* namespace js */

namespace JS {

template <typename T> template <typename S>
inline
Handle<T>::Handle(Rooted<S> &root,
                  typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy)
{
    ptr = reinterpret_cast<const T *>(root.address());
}

template <typename T> template <typename S>
inline
Handle<T>::Handle(MutableHandle<S> &root,
                  typename mozilla::EnableIf<mozilla::IsConvertible<S, T>::value, int>::Type dummy)
{
    ptr = reinterpret_cast<const T *>(root.address());
}

template <typename T>
inline
MutableHandle<T>::MutableHandle(Rooted<T> *root)
{
    ptr = root->address();
}

} /* namespace JS */

namespace js {

/*
 * Hook for dynamic root analysis. Checks the native stack and poisons
 * references to GC things which have not been rooted.
 */
inline void MaybeCheckStackRoots(JSContext *cx)
{
#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
    JS::CheckStackRoots(cx);
#endif
}

namespace gc {
struct Cell;
} /* namespace gc */

/* Base class for automatic read-only object rooting during compilation. */
class CompilerRootNode
{
  protected:
    CompilerRootNode(js::gc::Cell *ptr) : next(NULL), ptr_(ptr) {}

  public:
    void **address() { return (void **)&ptr_; }

  public:
    CompilerRootNode *next;

  protected:
    js::gc::Cell *ptr_;
};

}  /* namespace js */

ForwardDeclareJS(Script);
ForwardDeclareJS(Function);
ForwardDeclareJS(Object);

#endif  /* jsgc_root_h___ */
