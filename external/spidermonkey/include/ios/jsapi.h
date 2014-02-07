/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/* JavaScript API. */

#ifndef jsapi_h
#define jsapi_h

#include "mozilla/FloatingPoint.h"
#include "mozilla/MemoryReporting.h"
#include "mozilla/RangedPtr.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "jsalloc.h"
#include "jspubtd.h"

#include "js/CallArgs.h"
#include "js/Class.h"
#include "js/HashTable.h"
#include "js/Id.h"
#include "js/RootingAPI.h"
#include "js/Utility.h"
#include "js/Value.h"
#include "js/Vector.h"

/************************************************************************/

struct JSTracer;

namespace JS {

class Latin1CharsZ;
class TwoByteChars;

typedef mozilla::RangedPtr<const jschar> CharPtr;

class StableCharPtr : public CharPtr {
  public:
    StableCharPtr(const StableCharPtr &s) : CharPtr(s) {}
    StableCharPtr(const mozilla::RangedPtr<const jschar> &s) : CharPtr(s) {}
    StableCharPtr(const jschar *s, size_t len) : CharPtr(s, len) {}
    StableCharPtr(const jschar *pos, const jschar *start, size_t len)
      : CharPtr(pos, start, len)
    {}
};

#if defined JS_THREADSAFE && defined DEBUG

class JS_PUBLIC_API(AutoCheckRequestDepth)
{
    JSContext *cx;
  public:
    AutoCheckRequestDepth(JSContext *cx);
    AutoCheckRequestDepth(js::ContextFriendFields *cx);
    ~AutoCheckRequestDepth();
};

# define CHECK_REQUEST(cx) \
    JS::AutoCheckRequestDepth _autoCheckRequestDepth(cx)

#else

# define CHECK_REQUEST(cx) \
    ((void) 0)

#endif /* JS_THREADSAFE && DEBUG */

#ifdef DEBUG
/*
 * Assert that we're not doing GC on cx, that we're in a request as
 * needed, and that the compartments for cx and v are correct.
 * Also check that GC would be safe at this point.
 */
JS_PUBLIC_API(void)
AssertArgumentsAreSane(JSContext *cx, JS::Handle<JS::Value> v);
#else
inline void AssertArgumentsAreSane(JSContext *cx, JS::Handle<JS::Value> v) {
    /* Do nothing */
}
#endif /* DEBUG */

class JS_PUBLIC_API(AutoGCRooter) {
  public:
    AutoGCRooter(JSContext *cx, ptrdiff_t tag);
    AutoGCRooter(js::ContextFriendFields *cx, ptrdiff_t tag);

    ~AutoGCRooter() {
        JS_ASSERT(this == *stackTop);
        *stackTop = down;
    }

    /* Implemented in gc/RootMarking.cpp. */
    inline void trace(JSTracer *trc);
    static void traceAll(JSTracer *trc);
    static void traceAllWrappers(JSTracer *trc);

  protected:
    AutoGCRooter * const down;

    /*
     * Discriminates actual subclass of this being used.  If non-negative, the
     * subclass roots an array of values of the length stored in this field.
     * If negative, meaning is indicated by the corresponding value in the enum
     * below.  Any other negative value indicates some deeper problem such as
     * memory corruption.
     */
    ptrdiff_t tag_;

    enum {
        VALARRAY =     -2, /* js::AutoValueArray */
        PARSER =       -3, /* js::frontend::Parser */
        SHAPEVECTOR =  -4, /* js::AutoShapeVector */
        IDARRAY =      -6, /* js::AutoIdArray */
        DESCRIPTORS =  -7, /* js::AutoPropDescArrayRooter */
        ID =           -9, /* js::AutoIdRooter */
        VALVECTOR =   -10, /* js::AutoValueVector */
        STRING =      -12, /* js::AutoStringRooter */
        IDVECTOR =    -13, /* js::AutoIdVector */
        OBJVECTOR =   -14, /* js::AutoObjectVector */
        STRINGVECTOR =-15, /* js::AutoStringVector */
        SCRIPTVECTOR =-16, /* js::AutoScriptVector */
        NAMEVECTOR =  -17, /* js::AutoNameVector */
        HASHABLEVALUE=-18, /* js::HashableValue */
        IONMASM =     -19, /* js::jit::MacroAssembler */
        IONALLOC =    -20, /* js::jit::AutoTempAllocatorRooter */
        WRAPVECTOR =  -21, /* js::AutoWrapperVector */
        WRAPPER =     -22, /* js::AutoWrapperRooter */
        OBJOBJHASHMAP=-23, /* js::AutoObjectObjectHashMap */
        OBJU32HASHMAP=-24, /* js::AutoObjectUnsigned32HashMap */
        OBJHASHSET =  -25, /* js::AutoObjectHashSet */
        JSONPARSER =  -26, /* js::JSONParser */
        CUSTOM =      -27, /* js::CustomAutoRooter */
        FUNVECTOR =   -28  /* js::AutoFunctionVector */
    };

  private:
    AutoGCRooter ** const stackTop;

    /* No copy or assignment semantics. */
    AutoGCRooter(AutoGCRooter &ida) MOZ_DELETE;
    void operator=(AutoGCRooter &ida) MOZ_DELETE;
};

class AutoStringRooter : private AutoGCRooter {
  public:
    AutoStringRooter(JSContext *cx, JSString *str = nullptr
                     MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, STRING), str_(str)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    void setString(JSString *str) {
        str_ = str;
    }

    JSString * string() const {
        return str_;
    }

    JSString ** addr() {
        return &str_;
    }

    JSString * const * addr() const {
        return &str_;
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

  private:
    JSString *str_;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class AutoArrayRooter : private AutoGCRooter {
  public:
    AutoArrayRooter(JSContext *cx, size_t len, Value *vec
                    MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, len), array(vec), skip(cx, array, len)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        JS_ASSERT(tag_ >= 0);
    }

    void changeLength(size_t newLength) {
        tag_ = ptrdiff_t(newLength);
        JS_ASSERT(tag_ >= 0);
    }

    void changeArray(Value *newArray, size_t newLength) {
        changeLength(newLength);
        array = newArray;
    }

    Value *array;

    MutableHandle<Value> handleAt(size_t i)
    {
        JS_ASSERT(i < size_t(tag_));
        return MutableHandle<Value>::fromMarkedLocation(&array[i]);
    }
    Handle<Value> handleAt(size_t i) const
    {
        JS_ASSERT(i < size_t(tag_));
        return Handle<Value>::fromMarkedLocation(&array[i]);
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

  private:
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

    js::SkipRoot skip;
};

template<class T>
class AutoVectorRooter : protected AutoGCRooter
{
    typedef js::Vector<T, 8> VectorImpl;
    VectorImpl vector;

    /* Prevent overwriting of inline elements in vector. */
    js::SkipRoot vectorRoot;

  public:
    explicit AutoVectorRooter(JSContext *cx, ptrdiff_t tag
                              MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, tag), vector(cx), vectorRoot(cx, &vector)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    explicit AutoVectorRooter(js::ContextFriendFields *cx, ptrdiff_t tag
                              MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, tag), vector(cx), vectorRoot(cx, &vector)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    typedef T ElementType;
    typedef typename VectorImpl::Range Range;

    size_t length() const { return vector.length(); }
    bool empty() const { return vector.empty(); }

    bool append(const T &v) { return vector.append(v); }
    bool appendAll(const AutoVectorRooter<T> &other) {
        return vector.appendAll(other.vector);
    }

    bool insert(T *p, const T &val) { return vector.insert(p, val); }

    /* For use when space has already been reserved. */
    void infallibleAppend(const T &v) { vector.infallibleAppend(v); }

    void popBack() { vector.popBack(); }
    T popCopy() { return vector.popCopy(); }

    bool growBy(size_t inc) {
        size_t oldLength = vector.length();
        if (!vector.growByUninitialized(inc))
            return false;
        makeRangeGCSafe(oldLength);
        return true;
    }

    bool resize(size_t newLength) {
        size_t oldLength = vector.length();
        if (newLength <= oldLength) {
            vector.shrinkBy(oldLength - newLength);
            return true;
        }
        if (!vector.growByUninitialized(newLength - oldLength))
            return false;
        makeRangeGCSafe(oldLength);
        return true;
    }

    void clear() { vector.clear(); }

    bool reserve(size_t newLength) {
        return vector.reserve(newLength);
    }

    T &operator[](size_t i) { return vector[i]; }
    const T &operator[](size_t i) const { return vector[i]; }

    JS::MutableHandle<T> handleAt(size_t i) {
        return JS::MutableHandle<T>::fromMarkedLocation(&vector[i]);
    }
    JS::Handle<T> handleAt(size_t i) const {
        return JS::Handle<T>::fromMarkedLocation(&vector[i]);
    }

    const T *begin() const { return vector.begin(); }
    T *begin() { return vector.begin(); }

    const T *end() const { return vector.end(); }
    T *end() { return vector.end(); }

    Range all() { return vector.all(); }

    const T &back() const { return vector.back(); }

    friend void AutoGCRooter::trace(JSTracer *trc);

  private:
    void makeRangeGCSafe(size_t oldLength) {
        T *t = vector.begin() + oldLength;
        for (size_t i = oldLength; i < vector.length(); ++i, ++t)
            memset(t, 0, sizeof(T));
    }

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

template<class Key, class Value>
class AutoHashMapRooter : protected AutoGCRooter
{
  private:
    typedef js::HashMap<Key, Value> HashMapImpl;

  public:
    explicit AutoHashMapRooter(JSContext *cx, ptrdiff_t tag
                               MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, tag), map(cx)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    typedef Key KeyType;
    typedef Value ValueType;
    typedef typename HashMapImpl::Entry Entry;
    typedef typename HashMapImpl::Lookup Lookup;
    typedef typename HashMapImpl::Ptr Ptr;
    typedef typename HashMapImpl::AddPtr AddPtr;

    bool init(uint32_t len = 16) {
        return map.init(len);
    }
    bool initialized() const {
        return map.initialized();
    }
    Ptr lookup(const Lookup &l) const {
        return map.lookup(l);
    }
    void remove(Ptr p) {
        map.remove(p);
    }
    AddPtr lookupForAdd(const Lookup &l) const {
        return map.lookupForAdd(l);
    }

    template<typename KeyInput, typename ValueInput>
    bool add(AddPtr &p, const KeyInput &k, const ValueInput &v) {
        return map.add(p, k, v);
    }

    bool add(AddPtr &p, const Key &k) {
        return map.add(p, k);
    }

    template<typename KeyInput, typename ValueInput>
    bool relookupOrAdd(AddPtr &p, const KeyInput &k, const ValueInput &v) {
        return map.relookupOrAdd(p, k, v);
    }

    typedef typename HashMapImpl::Range Range;
    Range all() const {
        return map.all();
    }

    typedef typename HashMapImpl::Enum Enum;

    void clear() {
        map.clear();
    }

    void finish() {
        map.finish();
    }

    bool empty() const {
        return map.empty();
    }

    uint32_t count() const {
        return map.count();
    }

    size_t capacity() const {
        return map.capacity();
    }

    size_t sizeOfExcludingThis(mozilla::MallocSizeOf mallocSizeOf) const {
        return map.sizeOfExcludingThis(mallocSizeOf);
    }
    size_t sizeOfIncludingThis(mozilla::MallocSizeOf mallocSizeOf) const {
        return map.sizeOfIncludingThis(mallocSizeOf);
    }

    unsigned generation() const {
        return map.generation();
    }

    /************************************************** Shorthand operations */

    bool has(const Lookup &l) const {
        return map.has(l);
    }

    template<typename KeyInput, typename ValueInput>
    bool put(const KeyInput &k, const ValueInput &v) {
        return map.put(k, v);
    }

    template<typename KeyInput, typename ValueInput>
    bool putNew(const KeyInput &k, const ValueInput &v) {
        return map.putNew(k, v);
    }

    Ptr lookupWithDefault(const Key &k, const Value &defaultValue) {
        return map.lookupWithDefault(k, defaultValue);
    }

    void remove(const Lookup &l) {
        map.remove(l);
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

  private:
    AutoHashMapRooter(const AutoHashMapRooter &hmr) MOZ_DELETE;
    AutoHashMapRooter &operator=(const AutoHashMapRooter &hmr) MOZ_DELETE;

    HashMapImpl map;

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

template<class T>
class AutoHashSetRooter : protected AutoGCRooter
{
  private:
    typedef js::HashSet<T> HashSetImpl;

  public:
    explicit AutoHashSetRooter(JSContext *cx, ptrdiff_t tag
                               MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, tag), set(cx)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    typedef typename HashSetImpl::Lookup Lookup;
    typedef typename HashSetImpl::Ptr Ptr;
    typedef typename HashSetImpl::AddPtr AddPtr;

    bool init(uint32_t len = 16) {
        return set.init(len);
    }
    bool initialized() const {
        return set.initialized();
    }
    Ptr lookup(const Lookup &l) const {
        return set.lookup(l);
    }
    void remove(Ptr p) {
        set.remove(p);
    }
    AddPtr lookupForAdd(const Lookup &l) const {
        return set.lookupForAdd(l);
    }

    bool add(AddPtr &p, const T &t) {
        return set.add(p, t);
    }

    bool relookupOrAdd(AddPtr &p, const Lookup &l, const T &t) {
        return set.relookupOrAdd(p, l, t);
    }

    typedef typename HashSetImpl::Range Range;
    Range all() const {
        return set.all();
    }

    typedef typename HashSetImpl::Enum Enum;

    void clear() {
        set.clear();
    }

    void finish() {
        set.finish();
    }

    bool empty() const {
        return set.empty();
    }

    uint32_t count() const {
        return set.count();
    }

    size_t capacity() const {
        return set.capacity();
    }

    size_t sizeOfExcludingThis(mozilla::MallocSizeOf mallocSizeOf) const {
        return set.sizeOfExcludingThis(mallocSizeOf);
    }
    size_t sizeOfIncludingThis(mozilla::MallocSizeOf mallocSizeOf) const {
        return set.sizeOfIncludingThis(mallocSizeOf);
    }

    unsigned generation() const {
        return set.generation();
    }

    /************************************************** Shorthand operations */

    bool has(const Lookup &l) const {
        return set.has(l);
    }

    bool put(const T &t) {
        return set.put(t);
    }

    bool putNew(const T &t) {
        return set.putNew(t);
    }

    void remove(const Lookup &l) {
        set.remove(l);
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

  private:
    AutoHashSetRooter(const AutoHashSetRooter &hmr) MOZ_DELETE;
    AutoHashSetRooter &operator=(const AutoHashSetRooter &hmr) MOZ_DELETE;

    HashSetImpl set;

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class MOZ_STACK_CLASS AutoValueVector : public AutoVectorRooter<Value>
{
  public:
    explicit AutoValueVector(JSContext *cx
                             MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
        : AutoVectorRooter<Value>(cx, VALVECTOR)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class AutoIdVector : public AutoVectorRooter<jsid>
{
  public:
    explicit AutoIdVector(JSContext *cx
                          MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
        : AutoVectorRooter<jsid>(cx, IDVECTOR)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class AutoObjectVector : public AutoVectorRooter<JSObject *>
{
  public:
    explicit AutoObjectVector(JSContext *cx
                              MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
        : AutoVectorRooter<JSObject *>(cx, OBJVECTOR)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class AutoFunctionVector : public AutoVectorRooter<JSFunction *>
{
  public:
    explicit AutoFunctionVector(JSContext *cx
                                MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
        : AutoVectorRooter<JSFunction *>(cx, FUNVECTOR)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    explicit AutoFunctionVector(js::ContextFriendFields *cx
                                MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
        : AutoVectorRooter<JSFunction *>(cx, FUNVECTOR)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class AutoScriptVector : public AutoVectorRooter<JSScript *>
{
  public:
    explicit AutoScriptVector(JSContext *cx
                              MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
        : AutoVectorRooter<JSScript *>(cx, SCRIPTVECTOR)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

/*
 * Cutsom rooting behavior for internal and external clients.
 */
class JS_PUBLIC_API(CustomAutoRooter) : private AutoGCRooter
{
  public:
    template <typename CX>
    explicit CustomAutoRooter(CX *cx MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, CUSTOM)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

  protected:
    /* Supplied by derived class to trace roots. */
    virtual void trace(JSTracer *trc) = 0;

  private:
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

}  /* namespace JS */

/************************************************************************/

struct JSFreeOp {
  private:
    JSRuntime   *runtime_;

  protected:
    JSFreeOp(JSRuntime *rt)
      : runtime_(rt) { }

  public:
    JSRuntime *runtime() const {
        return runtime_;
    }
};

/* Callbacks and their arguments. */

/************************************************************************/

typedef enum JSContextOp {
    JSCONTEXT_NEW,
    JSCONTEXT_DESTROY
} JSContextOp;

/*
 * The possible values for contextOp when the runtime calls the callback are:
 *   JSCONTEXT_NEW      JS_NewContext successfully created a new JSContext
 *                      instance. The callback can initialize the instance as
 *                      required. If the callback returns false, the instance
 *                      will be destroyed and JS_NewContext returns null. In
 *                      this case the callback is not called again.
 *   JSCONTEXT_DESTROY  One of JS_DestroyContext* methods is called. The
 *                      callback may perform its own cleanup and must always
 *                      return true.
 *   Any other value    For future compatibility the callback must do nothing
 *                      and return true in this case.
 */
typedef bool
(* JSContextCallback)(JSContext *cx, unsigned contextOp, void *data);

typedef enum JSGCStatus {
    JSGC_BEGIN,
    JSGC_END
} JSGCStatus;

typedef void
(* JSGCCallback)(JSRuntime *rt, JSGCStatus status, void *data);

typedef enum JSFinalizeStatus {
    /*
     * Called when preparing to sweep a group of compartments, before anything
     * has been swept.  The collector will not yield to the mutator before
     * calling the callback with JSFINALIZE_GROUP_END status.
     */
    JSFINALIZE_GROUP_START,

    /*
     * Called when preparing to sweep a group of compartments. Weak references
     * to unmarked things have been removed and things that are not swept
     * incrementally have been finalized at this point.  The collector may yield
     * to the mutator after this point.
     */
    JSFINALIZE_GROUP_END,

    /*
     * Called at the end of collection when everything has been swept.
     */
    JSFINALIZE_COLLECTION_END
} JSFinalizeStatus;

typedef void
(* JSFinalizeCallback)(JSFreeOp *fop, JSFinalizeStatus status, bool isCompartment);

typedef bool
(* JSOperationCallback)(JSContext *cx);

typedef void
(* JSErrorReporter)(JSContext *cx, const char *message, JSErrorReport *report);

#ifdef MOZ_TRACE_JSCALLS
typedef void
(* JSFunctionCallback)(const JSFunction *fun,
                       const JSScript *scr,
                       const JSContext *cx,
                       int entering);
#endif

/*
 * Possible exception types. These types are part of a JSErrorFormatString
 * structure. They define which error to throw in case of a runtime error.
 * JSEXN_NONE marks an unthrowable error.
 */
typedef enum JSExnType {
    JSEXN_NONE = -1,
      JSEXN_ERR,
        JSEXN_INTERNALERR,
        JSEXN_EVALERR,
        JSEXN_RANGEERR,
        JSEXN_REFERENCEERR,
        JSEXN_SYNTAXERR,
        JSEXN_TYPEERR,
        JSEXN_URIERR,
        JSEXN_LIMIT
} JSExnType;

typedef struct JSErrorFormatString {
    /* The error format string in ASCII. */
    const char *format;

    /* The number of arguments to expand in the formatted error message. */
    uint16_t argCount;

    /* One of the JSExnType constants above. */
    int16_t exnType;
} JSErrorFormatString;

typedef const JSErrorFormatString *
(* JSErrorCallback)(void *userRef, const char *locale,
                    const unsigned errorNumber);

typedef bool
(* JSLocaleToUpperCase)(JSContext *cx, JS::Handle<JSString*> src,
                        JS::MutableHandle<JS::Value> rval);

typedef bool
(* JSLocaleToLowerCase)(JSContext *cx, JS::Handle<JSString*> src,
                        JS::MutableHandle<JS::Value> rval);

typedef bool
(* JSLocaleCompare)(JSContext *cx, JS::Handle<JSString*> src1, JS::Handle<JSString*> src2,
                    JS::MutableHandle<JS::Value> rval);

typedef bool
(* JSLocaleToUnicode)(JSContext *cx, const char *src, JS::MutableHandle<JS::Value> rval);

/*
 * Security protocol types.
 */

typedef void
(* JSDestroyPrincipalsOp)(JSPrincipals *principals);

/*
 * Used to check if a CSP instance wants to disable eval() and friends.
 * See js_CheckCSPPermitsJSAction() in jsobj.
 */
typedef bool
(* JSCSPEvalChecker)(JSContext *cx);

/*
 * Callback used to ask the embedding for the cross compartment wrapper handler
 * that implements the desired prolicy for this kind of object in the
 * destination compartment. |obj| is the object to be wrapped. If |existing| is
 * non-nullptr, it will point to an existing wrapper object that should be
 * re-used if possible. |existing| is guaranteed to be a cross-compartment
 * wrapper with a lazily-defined prototype and the correct global. It is
 * guaranteed not to wrap a function.
 */
typedef JSObject *
(* JSWrapObjectCallback)(JSContext *cx, JS::Handle<JSObject*> existing, JS::Handle<JSObject*> obj,
                         JS::Handle<JSObject*> proto, JS::Handle<JSObject*> parent,
                         unsigned flags);

/*
 * Callback used by the wrap hook to ask the embedding to prepare an object
 * for wrapping in a context. This might include unwrapping other wrappers
 * or even finding a more suitable object for the new compartment.
 */
typedef JSObject *
(* JSPreWrapCallback)(JSContext *cx, JS::Handle<JSObject*> scope, JS::Handle<JSObject*> obj,
                      unsigned flags);

/*
 * Callback used when wrapping determines that the underlying object is already
 * in the compartment for which it is being wrapped. This allows consumers to
 * maintain same-compartment wrapping invariants.
 *
 * |obj| is guaranteed to be same-compartment as |cx|, but it may (or may not)
 * be a security or cross-compartment wrapper. This is an unfortunate contract,
 * but is important for to avoid unnecessarily recomputing every cross-
 * compartment wrapper that gets passed to wrap.
 */
typedef JSObject *
(* JSSameCompartmentWrapObjectCallback)(JSContext *cx, JS::Handle<JSObject*> obj);

typedef void
(* JSDestroyCompartmentCallback)(JSFreeOp *fop, JSCompartment *compartment);

typedef void
(* JSZoneCallback)(JS::Zone *zone);

typedef void
(* JSCompartmentNameCallback)(JSRuntime *rt, JSCompartment *compartment,
                              char *buf, size_t bufsize);

/************************************************************************/

static JS_ALWAYS_INLINE jsval
JS_NumberValue(double d)
{
    int32_t i;
    d = JS::CanonicalizeNaN(d);
    if (mozilla::DoubleIsInt32(d, &i))
        return INT_TO_JSVAL(i);
    return DOUBLE_TO_JSVAL(d);
}

/************************************************************************/

JS_PUBLIC_API(bool)
JS_StringHasBeenInterned(JSContext *cx, JSString *str);

/*
 * Only JSStrings that have been interned via the JSAPI can be turned into
 * jsids by API clients.
 *
 * N.B. if a jsid is backed by a string which has not been interned, that
 * string must be appropriately rooted to avoid being collected by the GC.
 */
JS_PUBLIC_API(jsid)
INTERNED_STRING_TO_JSID(JSContext *cx, JSString *str);

/*
 * Returns true iff the given jsval is immune to GC and can be used across
 * multiple JSRuntimes without requiring any conversion API.
 */
static JS_ALWAYS_INLINE bool
JSVAL_IS_UNIVERSAL(jsval v)
{
    return !JSVAL_IS_GCTHING(v);
}

namespace JS {

class AutoIdRooter : private AutoGCRooter
{
  public:
    explicit AutoIdRooter(JSContext *cx, jsid aId = INT_TO_JSID(0)
                          MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, ID), id_(aId)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    jsid id() {
        return id_;
    }

    jsid * addr() {
        return &id_;
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

  private:
    jsid id_;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

} /* namespace JS */

/************************************************************************/

/* Property attributes, set in JSPropertySpec and passed to API functions. */
#define JSPROP_ENUMERATE        0x01    /* property is visible to for/in loop */
#define JSPROP_READONLY         0x02    /* not settable: assignment is no-op.
                                           This flag is only valid when neither
                                           JSPROP_GETTER nor JSPROP_SETTER is
                                           set. */
#define JSPROP_PERMANENT        0x04    /* property cannot be deleted */
#define JSPROP_NATIVE_ACCESSORS 0x08    /* set in JSPropertyDescriptor.flags
                                           if getters/setters are JSNatives */
#define JSPROP_GETTER           0x10    /* property holds getter function */
#define JSPROP_SETTER           0x20    /* property holds setter function */
#define JSPROP_SHARED           0x40    /* don't allocate a value slot for this
                                           property; don't copy the property on
                                           set of the same-named property in an
                                           object that delegates to a prototype
                                           containing this property */
#define JSPROP_INDEX            0x80    /* name is actually (int) index */
#define JSPROP_SHORTID         0x100    /* set in JS_DefineProperty attrs
                                           if getters/setters use a shortid */

#define JSFUN_STUB_GSOPS       0x200    /* use JS_PropertyStub getter/setter
                                           instead of defaulting to class gsops
                                           for property holding function */

#define JSFUN_CONSTRUCTOR      0x400    /* native that can be called as a ctor */


/*
 * Specify a generic native prototype methods, i.e., methods of a class
 * prototype that are exposed as static methods taking an extra leading
 * argument: the generic |this| parameter.
 *
 * If you set this flag in a JSFunctionSpec struct's flags initializer, then
 * that struct must live at least as long as the native static method object
 * created due to this flag by JS_DefineFunctions or JS_InitClass.  Typically
 * JSFunctionSpec structs are allocated in static arrays.
 */
#define JSFUN_GENERIC_NATIVE   0x800

#define JSFUN_FLAGS_MASK       0xe00    /* | of all the JSFUN_* flags */

/*
 * The first call to JS_CallOnce by any thread in a process will call 'func'.
 * Later calls to JS_CallOnce with the same JSCallOnceType object will be
 * suppressed.
 *
 * Equivalently: each distinct JSCallOnceType object will allow one JS_CallOnce
 * to invoke its JSInitCallback.
 */
extern JS_PUBLIC_API(bool)
JS_CallOnce(JSCallOnceType *once, JSInitCallback func);

/* Microseconds since the epoch, midnight, January 1, 1970 UTC. */
extern JS_PUBLIC_API(int64_t)
JS_Now(void);

/* Don't want to export data, so provide accessors for non-inline jsvals. */
extern JS_PUBLIC_API(jsval)
JS_GetNaNValue(JSContext *cx);

extern JS_PUBLIC_API(jsval)
JS_GetNegativeInfinityValue(JSContext *cx);

extern JS_PUBLIC_API(jsval)
JS_GetPositiveInfinityValue(JSContext *cx);

extern JS_PUBLIC_API(jsval)
JS_GetEmptyStringValue(JSContext *cx);

extern JS_PUBLIC_API(JSString *)
JS_GetEmptyString(JSRuntime *rt);

/*
 * Format is a string of the following characters (spaces are insignificant),
 * specifying the tabulated type conversions:
 *
 *   b      bool            Boolean
 *   c      uint16_t/jschar ECMA uint16_t, Unicode char
 *   i      int32_t         ECMA int32_t
 *   u      uint32_t        ECMA uint32_t
 *   j      int32_t         Rounded int32_t (coordinate)
 *   d      double          IEEE double
 *   I      double          Integral IEEE double
 *   S      JSString *      Unicode string, accessed by a JSString pointer
 *   W      jschar *        Unicode character vector, 0-terminated (W for wide)
 *   o      JSObject *      Object reference
 *   f      JSFunction *    Function private
 *   v      jsval           Argument value (no conversion)
 *   *      N/A             Skip this argument (no vararg)
 *   /      N/A             End of required arguments
 *
 * The variable argument list after format must consist of &b, &c, &s, e.g.,
 * where those variables have the types given above.  For the pointer types
 * char *, JSString *, and JSObject *, the pointed-at memory returned belongs
 * to the JS runtime, not to the calling native code.  The runtime promises
 * to keep this memory valid so long as argv refers to allocated stack space
 * (so long as the native function is active).
 *
 * Fewer arguments than format specifies may be passed only if there is a /
 * in format after the last required argument specifier and argc is at least
 * the number of required arguments.  More arguments than format specifies
 * may be passed without error; it is up to the caller to deal with trailing
 * unconverted arguments.
 */
extern JS_PUBLIC_API(bool)
JS_ConvertArguments(JSContext *cx, unsigned argc, jsval *argv, const char *format,
                    ...);

#ifdef va_start
extern JS_PUBLIC_API(bool)
JS_ConvertArgumentsVA(JSContext *cx, unsigned argc, jsval *argv,
                      const char *format, va_list ap);
#endif

extern JS_PUBLIC_API(bool)
JS_ConvertValue(JSContext *cx, JS::HandleValue v, JSType type, JS::MutableHandleValue vp);

extern JS_PUBLIC_API(bool)
JS_ValueToObject(JSContext *cx, JS::HandleValue v, JS::MutableHandleObject objp);

extern JS_PUBLIC_API(JSFunction *)
JS_ValueToFunction(JSContext *cx, JS::HandleValue v);

extern JS_PUBLIC_API(JSFunction *)
JS_ValueToConstructor(JSContext *cx, JS::HandleValue v);

extern JS_PUBLIC_API(JSString *)
JS_ValueToString(JSContext *cx, jsval v);

extern JS_PUBLIC_API(JSString *)
JS_ValueToSource(JSContext *cx, jsval v);

namespace js {
/*
 * DO NOT CALL THIS.  Use JS::ToNumber
 */
extern JS_PUBLIC_API(bool)
ToNumberSlow(JSContext *cx, JS::Value v, double *dp);

/*
 * DO NOT CALL THIS. Use JS::ToBoolean
 */
extern JS_PUBLIC_API(bool)
ToBooleanSlow(const JS::Value &v);
} /* namespace js */

namespace JS {

/* ES5 9.3 ToNumber. */
JS_ALWAYS_INLINE bool
ToNumber(JSContext *cx, Handle<Value> v, double *out)
{
    AssertArgumentsAreSane(cx, v);
    {
        js::SkipRoot root(cx, &v);
        js::MaybeCheckStackRoots(cx);
    }

    if (v.isNumber()) {
        *out = v.toNumber();
        return true;
    }
    return js::ToNumberSlow(cx, v, out);
}

JS_ALWAYS_INLINE bool
ToBoolean(const Value &v)
{
    if (v.isBoolean())
        return v.toBoolean();
    if (v.isInt32())
        return v.toInt32() != 0;
    if (v.isNullOrUndefined())
        return false;
    if (v.isDouble()) {
        double d = v.toDouble();
        return !mozilla::IsNaN(d) && d != 0;
    }

    /* The slow path handles strings and objects. */
    return js::ToBooleanSlow(v);
}

} /* namespace JS */

extern JS_PUBLIC_API(bool)
JS_DoubleIsInt32(double d, int32_t *ip);

extern JS_PUBLIC_API(int32_t)
JS_DoubleToInt32(double d);

extern JS_PUBLIC_API(uint32_t)
JS_DoubleToUint32(double d);

/*
 * Convert a value to a number, then to an int32_t, according to the ECMA rules
 * for ToInt32.
 */
extern JS_PUBLIC_API(bool)
JS_ValueToECMAInt32(JSContext *cx, jsval v, int32_t *ip);

/*
 * Convert a value to a number, then to an int64_t, according to the WebIDL
 * rules for ToInt64: http://dev.w3.org/2006/webapi/WebIDL/#es-long-long
 */
extern JS_PUBLIC_API(bool)
JS_ValueToInt64(JSContext *cx, jsval v, int64_t *ip);

/*
 * Convert a value to a number, then to an uint64_t, according to the WebIDL
 * rules for ToUint64: http://dev.w3.org/2006/webapi/WebIDL/#es-unsigned-long-long
 */
extern JS_PUBLIC_API(bool)
JS_ValueToUint64(JSContext *cx, jsval v, uint64_t *ip);

namespace js {
/* DO NOT CALL THIS.  Use JS::ToInt16. */
extern JS_PUBLIC_API(bool)
ToUint16Slow(JSContext *cx, JS::Handle<JS::Value> v, uint16_t *out);

/* DO NOT CALL THIS.  Use JS::ToInt32. */
extern JS_PUBLIC_API(bool)
ToInt32Slow(JSContext *cx, JS::Handle<JS::Value> v, int32_t *out);

/* DO NOT CALL THIS.  Use JS::ToUint32. */
extern JS_PUBLIC_API(bool)
ToUint32Slow(JSContext *cx, JS::Handle<JS::Value> v, uint32_t *out);

/* DO NOT CALL THIS. Use JS::ToInt64. */
extern JS_PUBLIC_API(bool)
ToInt64Slow(JSContext *cx, JS::Handle<JS::Value> v, int64_t *out);

/* DO NOT CALL THIS. Use JS::ToUint64. */
extern JS_PUBLIC_API(bool)
ToUint64Slow(JSContext *cx, JS::Handle<JS::Value> v, uint64_t *out);
} /* namespace js */

namespace JS {

JS_ALWAYS_INLINE bool
ToUint16(JSContext *cx, JS::Handle<JS::Value> v, uint16_t *out)
{
    AssertArgumentsAreSane(cx, v);
    js::MaybeCheckStackRoots(cx);

    if (v.isInt32()) {
        *out = uint16_t(v.toInt32());
        return true;
    }
    return js::ToUint16Slow(cx, v, out);
}

JS_ALWAYS_INLINE bool
ToInt32(JSContext *cx, JS::Handle<JS::Value> v, int32_t *out)
{
    AssertArgumentsAreSane(cx, v);
    js::MaybeCheckStackRoots(cx);

    if (v.isInt32()) {
        *out = v.toInt32();
        return true;
    }
    return js::ToInt32Slow(cx, v, out);
}

JS_ALWAYS_INLINE bool
ToUint32(JSContext *cx, JS::Handle<JS::Value> v, uint32_t *out)
{
    AssertArgumentsAreSane(cx, v);
    js::MaybeCheckStackRoots(cx);

    if (v.isInt32()) {
        *out = uint32_t(v.toInt32());
        return true;
    }
    return js::ToUint32Slow(cx, v, out);
}

JS_ALWAYS_INLINE bool
ToInt64(JSContext *cx, JS::Handle<JS::Value> v, int64_t *out)
{
    AssertArgumentsAreSane(cx, v);
    js::MaybeCheckStackRoots(cx);

    if (v.isInt32()) {
        *out = int64_t(v.toInt32());
        return true;
    }

    return js::ToInt64Slow(cx, v, out);
}

JS_ALWAYS_INLINE bool
ToUint64(JSContext *cx, JS::Handle<JS::Value> v, uint64_t *out)
{
    AssertArgumentsAreSane(cx, v);
    js::MaybeCheckStackRoots(cx);

    if (v.isInt32()) {
        /* Account for sign extension of negatives into the longer 64bit space. */
        *out = uint64_t(int64_t(v.toInt32()));
        return true;
    }

    return js::ToUint64Slow(cx, v, out);
}


} /* namespace JS */

/*
 * Convert a value to a number, then to a uint32_t, according to the ECMA rules
 * for ToUint32.
 */
extern JS_PUBLIC_API(bool)
JS_ValueToECMAUint32(JSContext *cx, jsval v, uint32_t *ip);

/*
 * Convert a value to a number, then to an int32_t if it fits by rounding to
 * nearest; but failing with an error report if the double is out of range
 * or unordered.
 */
extern JS_PUBLIC_API(bool)
JS_ValueToInt32(JSContext *cx, jsval v, int32_t *ip);

/*
 * ECMA ToUint16, for mapping a jsval to a Unicode point.
 */
extern JS_PUBLIC_API(bool)
JS_ValueToUint16(JSContext *cx, jsval v, uint16_t *ip);

extern JS_PUBLIC_API(bool)
JS_ValueToBoolean(JSContext *cx, jsval v, bool *bp);

extern JS_PUBLIC_API(JSType)
JS_TypeOfValue(JSContext *cx, jsval v);

extern JS_PUBLIC_API(const char *)
JS_GetTypeName(JSContext *cx, JSType type);

extern JS_PUBLIC_API(bool)
JS_StrictlyEqual(JSContext *cx, jsval v1, jsval v2, bool *equal);

extern JS_PUBLIC_API(bool)
JS_LooselyEqual(JSContext *cx, jsval v1, jsval v2, bool *equal);

extern JS_PUBLIC_API(bool)
JS_SameValue(JSContext *cx, jsval v1, jsval v2, bool *same);

/* True iff fun is the global eval function. */
extern JS_PUBLIC_API(bool)
JS_IsBuiltinEvalFunction(JSFunction *fun);

/* True iff fun is the Function constructor. */
extern JS_PUBLIC_API(bool)
JS_IsBuiltinFunctionConstructor(JSFunction *fun);

/************************************************************************/

/*
 * Initialization, locking, contexts, and memory allocation.
 *
 * It is important that the first runtime and first context be created in a
 * single-threaded fashion, otherwise the behavior of the library is undefined.
 * See: http://developer.mozilla.org/en/docs/Category:JSAPI_Reference
 */

typedef enum JSUseHelperThreads
{
    JS_NO_HELPER_THREADS,
    JS_USE_HELPER_THREADS
} JSUseHelperThreads;

/**
 * Initialize SpiderMonkey, returning true only if initialization succeeded.
 * Once this method has succeeded, it is safe to call JS_NewRuntime and other
 * JSAPI methods.
 *
 * This method must be called before any other JSAPI method is used on any
 * thread.  Once it has been used, it is safe to call any JSAPI method, and it
 * remains safe to do so until JS_ShutDown is correctly called.
 *
 * It is currently not possible to initialize SpiderMonkey multiple times (that
 * is, calling JS_Init/JSAPI methods/JS_ShutDown in that order, then doing so
 * again).  This restriction may eventually be lifted.
 */
extern JS_PUBLIC_API(bool)
JS_Init(void);

/**
 * Destroy free-standing resources allocated by SpiderMonkey, not associated
 * with any runtime, context, or other structure.
 *
 * This method should be called after all other JSAPI data has been properly
 * cleaned up: every new runtime must have been destroyed, every new context
 * must have been destroyed, and so on.  Calling this method before all other
 * resources have been destroyed has undefined behavior.
 *
 * Failure to call this method, at present, has no adverse effects other than
 * leaking memory.  This may not always be the case; it's recommended that all
 * embedders call this method when all other JSAPI operations have completed.
 *
 * It is currently not possible to initialize SpiderMonkey multiple times (that
 * is, calling JS_Init/JSAPI methods/JS_ShutDown in that order, then doing so
 * again).  This restriction may eventually be lifted.
 */
extern JS_PUBLIC_API(void)
JS_ShutDown(void);

extern JS_PUBLIC_API(JSRuntime *)
JS_NewRuntime(uint32_t maxbytes, JSUseHelperThreads useHelperThreads);

extern JS_PUBLIC_API(void)
JS_DestroyRuntime(JSRuntime *rt);

// These are equivalent to ICU's |UMemAllocFn|, |UMemReallocFn|, and
// |UMemFreeFn| types.  The first argument (called |context| in the ICU docs)
// will always be nullptr, and should be ignored.
typedef void *(*JS_ICUAllocFn)(const void *, size_t size);
typedef void *(*JS_ICUReallocFn)(const void *, void *p, size_t size);
typedef void (*JS_ICUFreeFn)(const void *, void *p);

// This function can be used to track memory used by ICU.
// Do not use it unless you know what you are doing!
extern JS_PUBLIC_API(bool)
JS_SetICUMemoryFunctions(JS_ICUAllocFn allocFn, JS_ICUReallocFn reallocFn, JS_ICUFreeFn freeFn);

JS_PUBLIC_API(void *)
JS_GetRuntimePrivate(JSRuntime *rt);

extern JS_PUBLIC_API(JSRuntime *)
JS_GetRuntime(JSContext *cx);

JS_PUBLIC_API(void)
JS_SetRuntimePrivate(JSRuntime *rt, void *data);

extern JS_PUBLIC_API(void)
JS_BeginRequest(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_EndRequest(JSContext *cx);

extern JS_PUBLIC_API(bool)
JS_IsInRequest(JSRuntime *rt);

namespace js {

void
AssertHeapIsIdle(JSRuntime *rt);

void
AssertHeapIsIdle(JSContext *cx);

} /* namespace js */

class JSAutoRequest
{
  public:
    JSAutoRequest(JSContext *cx
                  MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : mContext(cx)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
        JS_BeginRequest(mContext);
    }
    ~JSAutoRequest() {
        JS_EndRequest(mContext);
    }

  protected:
    JSContext *mContext;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

#if 0
  private:
    static void *operator new(size_t) CPP_THROW_NEW { return 0; };
    static void operator delete(void *, size_t) { };
#endif
};

class JSAutoCheckRequest
{
  public:
    JSAutoCheckRequest(JSContext *cx
                       MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
    {
#if defined JS_THREADSAFE && defined DEBUG
        mContext = cx;
        JS_ASSERT(JS_IsInRequest(JS_GetRuntime(cx)));
#endif
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    ~JSAutoCheckRequest() {
#if defined JS_THREADSAFE && defined DEBUG
        JS_ASSERT(JS_IsInRequest(JS_GetRuntime(mContext)));
#endif
    }


  private:
#if defined JS_THREADSAFE && defined DEBUG
    JSContext *mContext;
#endif
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER
};

extern JS_PUBLIC_API(void)
JS_SetContextCallback(JSRuntime *rt, JSContextCallback cxCallback, void *data);

extern JS_PUBLIC_API(JSContext *)
JS_NewContext(JSRuntime *rt, size_t stackChunkSize);

extern JS_PUBLIC_API(void)
JS_DestroyContext(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_DestroyContextNoGC(JSContext *cx);

extern JS_PUBLIC_API(void *)
JS_GetContextPrivate(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_SetContextPrivate(JSContext *cx, void *data);

extern JS_PUBLIC_API(void *)
JS_GetSecondContextPrivate(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_SetSecondContextPrivate(JSContext *cx, void *data);

extern JS_PUBLIC_API(JSRuntime *)
JS_GetRuntime(JSContext *cx);

extern JS_PUBLIC_API(JSContext *)
JS_ContextIterator(JSRuntime *rt, JSContext **iterp);

extern JS_PUBLIC_API(JSVersion)
JS_GetVersion(JSContext *cx);

// Mutate the version on the compartment. This is generally discouraged, but
// necessary to support the version mutation in the js and xpc shell command
// set.
//
// It would be nice to put this in jsfriendapi, but the linkage requirements
// of the shells make that impossible.
JS_PUBLIC_API(void)
JS_SetVersionForCompartment(JSCompartment *compartment, JSVersion version);

extern JS_PUBLIC_API(const char *)
JS_VersionToString(JSVersion version);

extern JS_PUBLIC_API(JSVersion)
JS_StringToVersion(const char *string);

namespace JS {

class JS_PUBLIC_API(ContextOptions) {
  public:
    ContextOptions()
      : extraWarnings_(false),
        werror_(false),
        varObjFix_(false),
        privateIsNSISupports_(false),
        compileAndGo_(false),
        dontReportUncaught_(false),
        noDefaultCompartmentObject_(false),
        noScriptRval_(false),
        baseline_(false),
        typeInference_(false),
        strictMode_(false),
        ion_(false),
        asmJS_(false)
    {
    }

    bool extraWarnings() const { return extraWarnings_; }
    ContextOptions &setExtraWarnings(bool flag) {
        extraWarnings_ = flag;
        return *this;
    }
    ContextOptions &toggleExtraWarnings() {
        extraWarnings_ = !extraWarnings_;
        return *this;
    }

    bool werror() const { return werror_; }
    ContextOptions &setWerror(bool flag) {
        werror_ = flag;
        return *this;
    }
    ContextOptions &toggleWerror() {
        werror_ = !werror_;
        return *this;
    }

    bool varObjFix() const { return varObjFix_; }
    ContextOptions &setVarObjFix(bool flag) {
        varObjFix_ = flag;
        return *this;
    }
    ContextOptions &toggleVarObjFix() {
        varObjFix_ = !varObjFix_;
        return *this;
    }

    bool privateIsNSISupports() const { return privateIsNSISupports_; }
    ContextOptions &setPrivateIsNSISupports(bool flag) {
        privateIsNSISupports_ = flag;
        return *this;
    }
    ContextOptions &togglePrivateIsNSISupports() {
        privateIsNSISupports_ = !privateIsNSISupports_;
        return *this;
    }

    bool compileAndGo() const { return compileAndGo_; }
    ContextOptions &setCompileAndGo(bool flag) {
        compileAndGo_ = flag;
        return *this;
    }
    ContextOptions &toggleCompileAndGo() {
        compileAndGo_ = !compileAndGo_;
        return *this;
    }

    bool dontReportUncaught() const { return dontReportUncaught_; }
    ContextOptions &setDontReportUncaught(bool flag) {
        dontReportUncaught_ = flag;
        return *this;
    }
    ContextOptions &toggleDontReportUncaught() {
        dontReportUncaught_ = !dontReportUncaught_;
        return *this;
    }

    bool noDefaultCompartmentObject() const { return noDefaultCompartmentObject_; }
    ContextOptions &setNoDefaultCompartmentObject(bool flag) {
        noDefaultCompartmentObject_ = flag;
        return *this;
    }
    ContextOptions &toggleNoDefaultCompartmentObject() {
        noDefaultCompartmentObject_ = !noDefaultCompartmentObject_;
        return *this;
    }

    bool noScriptRval() const { return noScriptRval_; }
    ContextOptions &setNoScriptRval(bool flag) {
        noScriptRval_ = flag;
        return *this;
    }
    ContextOptions &toggleNoScriptRval() {
        noScriptRval_ = !noScriptRval_;
        return *this;
    }

    bool baseline() const { return baseline_; }
    ContextOptions &setBaseline(bool flag) {
        baseline_ = flag;
        return *this;
    }
    ContextOptions &toggleBaseline() {
        baseline_ = !baseline_;
        return *this;
    }

    bool typeInference() const { return typeInference_; }
    ContextOptions &setTypeInference(bool flag) {
        typeInference_ = flag;
        return *this;
    }
    ContextOptions &toggleTypeInference() {
        typeInference_ = !typeInference_;
        return *this;
    }

    bool strictMode() const { return strictMode_; }
    ContextOptions &setStrictMode(bool flag) {
        strictMode_ = flag;
        return *this;
    }
    ContextOptions &toggleStrictMode() {
        strictMode_ = !strictMode_;
        return *this;
    }

    bool ion() const { return ion_; }
    ContextOptions &setIon(bool flag) {
        ion_ = flag;
        return *this;
    }
    ContextOptions &toggleIon() {
        ion_ = !ion_;
        return *this;
    }

    bool asmJS() const { return asmJS_; }
    ContextOptions &setAsmJS(bool flag) {
        asmJS_ = flag;
        return *this;
    }
    ContextOptions &toggleAsmJS() {
        asmJS_ = !asmJS_;
        return *this;
    }

  private:
    bool extraWarnings_ : 1;
    bool werror_ : 1;
    bool varObjFix_ : 1;
    bool privateIsNSISupports_ : 1;
    bool compileAndGo_ : 1;
    bool dontReportUncaught_ : 1;
    bool noDefaultCompartmentObject_ : 1;
    bool noScriptRval_ : 1;
    bool baseline_ : 1;
    bool typeInference_ : 1;
    bool strictMode_ : 1;
    bool ion_ : 1;
    bool asmJS_ : 1;
};

JS_PUBLIC_API(ContextOptions &)
ContextOptionsRef(JSContext *cx);

class JS_PUBLIC_API(AutoSaveContextOptions) {
  public:
    AutoSaveContextOptions(JSContext *cx)
      : cx_(cx),
        oldOptions_(ContextOptionsRef(cx_))
    {
    }

    ~AutoSaveContextOptions()
    {
        ContextOptionsRef(cx_) = oldOptions_;
    }

  private:
    JSContext *cx_;
    JS::ContextOptions oldOptions_;
};

} /* namespace JS */

extern JS_PUBLIC_API(void)
JS_SetJitHardening(JSRuntime *rt, bool enabled);

extern JS_PUBLIC_API(const char *)
JS_GetImplementationVersion(void);

extern JS_PUBLIC_API(void)
JS_SetDestroyCompartmentCallback(JSRuntime *rt, JSDestroyCompartmentCallback callback);

extern JS_PUBLIC_API(void)
JS_SetDestroyZoneCallback(JSRuntime *rt, JSZoneCallback callback);

extern JS_PUBLIC_API(void)
JS_SetSweepZoneCallback(JSRuntime *rt, JSZoneCallback callback);

extern JS_PUBLIC_API(void)
JS_SetCompartmentNameCallback(JSRuntime *rt, JSCompartmentNameCallback callback);

extern JS_PUBLIC_API(JSWrapObjectCallback)
JS_SetWrapObjectCallbacks(JSRuntime *rt,
                          JSWrapObjectCallback callback,
                          JSSameCompartmentWrapObjectCallback sccallback,
                          JSPreWrapCallback precallback);

extern JS_PUBLIC_API(void)
JS_SetCompartmentPrivate(JSCompartment *compartment, void *data);

extern JS_PUBLIC_API(void *)
JS_GetCompartmentPrivate(JSCompartment *compartment);

extern JS_PUBLIC_API(void)
JS_SetZoneUserData(JS::Zone *zone, void *data);

extern JS_PUBLIC_API(void *)
JS_GetZoneUserData(JS::Zone *zone);

extern JS_PUBLIC_API(bool)
JS_WrapObject(JSContext *cx, JS::MutableHandleObject objp);

extern JS_PUBLIC_API(bool)
JS_WrapValue(JSContext *cx, JS::MutableHandleValue vp);

extern JS_PUBLIC_API(bool)
JS_WrapId(JSContext *cx, jsid *idp);

extern JS_PUBLIC_API(JSObject *)
JS_TransplantObject(JSContext *cx, JS::Handle<JSObject*> origobj, JS::Handle<JSObject*> target);

extern JS_PUBLIC_API(bool)
JS_RefreshCrossCompartmentWrappers(JSContext *cx, JSObject *ob);

/*
 * At any time, a JSContext has a current (possibly-nullptr) compartment.
 * Compartments are described in:
 *
 *   developer.mozilla.org/en-US/docs/SpiderMonkey/SpiderMonkey_compartments
 *
 * The current compartment of a context may be changed. The preferred way to do
 * this is with JSAutoCompartment:
 *
 *   void foo(JSContext *cx, JSObject *obj) {
 *     // in some compartment 'c'
 *     {
 *       JSAutoCompartment ac(cx, obj);  // constructor enters
 *       // in the compartment of 'obj'
 *     }                                 // destructor leaves
 *     // back in compartment 'c'
 *   }
 *
 * For more complicated uses that don't neatly fit in a C++ stack frame, the
 * compartment can entered and left using separate function calls:
 *
 *   void foo(JSContext *cx, JSObject *obj) {
 *     // in 'oldCompartment'
 *     JSCompartment *oldCompartment = JS_EnterCompartment(cx, obj);
 *     // in the compartment of 'obj'
 *     JS_LeaveCompartment(cx, oldCompartment);
 *     // back in 'oldCompartment'
 *   }
 *
 * Note: these calls must still execute in a LIFO manner w.r.t all other
 * enter/leave calls on the context. Furthermore, only the return value of a
 * JS_EnterCompartment call may be passed as the 'oldCompartment' argument of
 * the corresponding JS_LeaveCompartment call.
 */

class JS_PUBLIC_API(JSAutoCompartment)
{
    JSContext *cx_;
    JSCompartment *oldCompartment_;
  public:
    JSAutoCompartment(JSContext *cx, JSObject *target);
    JSAutoCompartment(JSContext *cx, JSScript *target);
    ~JSAutoCompartment();
};

/* NB: This API is infallible; a nullptr return value does not indicate error. */
extern JS_PUBLIC_API(JSCompartment *)
JS_EnterCompartment(JSContext *cx, JSObject *target);

extern JS_PUBLIC_API(void)
JS_LeaveCompartment(JSContext *cx, JSCompartment *oldCompartment);

typedef void (*JSIterateCompartmentCallback)(JSRuntime *rt, void *data, JSCompartment *compartment);

/*
 * This function calls |compartmentCallback| on every compartment.  Beware that
 * there is no guarantee that the compartment will survive after the callback
 * returns.
 */
extern JS_PUBLIC_API(void)
JS_IterateCompartments(JSRuntime *rt, void *data,
                       JSIterateCompartmentCallback compartmentCallback);

/*
 * Initialize standard JS class constructors, prototypes, and any top-level
 * functions and constants associated with the standard classes (e.g. isNaN
 * for Number).
 *
 * NB: This sets cx's global object to obj if it was null.
 */
extern JS_PUBLIC_API(bool)
JS_InitStandardClasses(JSContext *cx, JSObject *obj);

/*
 * Resolve id, which must contain either a string or an int, to a standard
 * class name in obj if possible, defining the class's constructor and/or
 * prototype and storing true in *resolved.  If id does not name a standard
 * class or a top-level property induced by initializing a standard class,
 * store false in *resolved and just return true.  Return false on error,
 * as usual for bool result-typed API entry points.
 *
 * This API can be called directly from a global object class's resolve op,
 * to define standard classes lazily.  The class's enumerate op should call
 * JS_EnumerateStandardClasses(cx, obj), to define eagerly during for..in
 * loops any classes not yet resolved lazily.
 */
extern JS_PUBLIC_API(bool)
JS_ResolveStandardClass(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                        bool *resolved);

extern JS_PUBLIC_API(bool)
JS_EnumerateStandardClasses(JSContext *cx, JS::Handle<JSObject*> obj);

extern JS_PUBLIC_API(bool)
JS_GetClassObject(JSContext *cx, JSObject *obj, JSProtoKey key, JSObject **objp);

extern JS_PUBLIC_API(bool)
JS_GetClassPrototype(JSContext *cx, JSProtoKey key, JSObject **objp);

extern JS_PUBLIC_API(JSProtoKey)
JS_IdentifyClassPrototype(JSContext *cx, JSObject *obj);

/*
 * Returns the original value of |Function.prototype| from the global object in
 * which |forObj| was created.
 */
extern JS_PUBLIC_API(JSObject *)
JS_GetFunctionPrototype(JSContext *cx, JSObject *forObj);

/*
 * Returns the original value of |Object.prototype| from the global object in
 * which |forObj| was created.
 */
extern JS_PUBLIC_API(JSObject *)
JS_GetObjectPrototype(JSContext *cx, JSObject *forObj);

/*
 * Returns the original value of |Array.prototype| from the global object in
 * which |forObj| was created.
 */
extern JS_PUBLIC_API(JSObject *)
JS_GetArrayPrototype(JSContext *cx, JSObject *forObj);

extern JS_PUBLIC_API(JSObject *)
JS_GetGlobalForObject(JSContext *cx, JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_IsGlobalObject(JSObject *obj);

/*
 * May return nullptr, if |c| never had a global (e.g. the atoms compartment),
 * or if |c|'s global has been collected.
 */
extern JS_PUBLIC_API(JSObject *)
JS_GetGlobalForCompartmentOrNull(JSContext *cx, JSCompartment *c);

namespace JS {

extern JS_PUBLIC_API(JSObject *)
CurrentGlobalOrNull(JSContext *cx);

}

/*
 * This method returns the global corresponding to the most recent scripted
 * frame, which may not match the cx's current compartment. This is extremely
 * dangerous, because it can bypass compartment security invariants in subtle
 * ways. To use it safely, the caller must perform a subsequent security
 * check. There is currently only one consumer of this function in Gecko, and
 * it should probably stay that way. If you'd like to use it, please consult
 * the XPConnect module owner first.
 */
extern JS_PUBLIC_API(JSObject *)
JS_GetScriptedGlobal(JSContext *cx);

/*
 * Initialize the 'Reflect' object on a global object.
 */
extern JS_PUBLIC_API(JSObject *)
JS_InitReflect(JSContext *cx, JSObject *global);

#ifdef JS_HAS_CTYPES
/*
 * Initialize the 'ctypes' object on a global variable 'obj'. The 'ctypes'
 * object will be sealed.
 */
extern JS_PUBLIC_API(bool)
JS_InitCTypesClass(JSContext *cx, JSObject *global);

/*
 * Convert a unicode string 'source' of length 'slen' to the platform native
 * charset, returning a null-terminated string allocated with JS_malloc. On
 * failure, this function should report an error.
 */
typedef char *
(* JSCTypesUnicodeToNativeFun)(JSContext *cx, const jschar *source, size_t slen);

/*
 * Set of function pointers that ctypes can use for various internal functions.
 * See JS_SetCTypesCallbacks below. Providing nullptr for a function is safe,
 * and will result in the applicable ctypes functionality not being available.
 */
struct JSCTypesCallbacks {
    JSCTypesUnicodeToNativeFun unicodeToNative;
};

typedef struct JSCTypesCallbacks JSCTypesCallbacks;

/*
 * Set the callbacks on the provided 'ctypesObj' object. 'callbacks' should be a
 * pointer to static data that exists for the lifetime of 'ctypesObj', but it
 * may safely be altered after calling this function and without having
 * to call this function again.
 */
extern JS_PUBLIC_API(void)
JS_SetCTypesCallbacks(JSObject *ctypesObj, JSCTypesCallbacks *callbacks);
#endif

typedef bool
(* JSEnumerateDiagnosticMemoryCallback)(void *ptr, size_t length);

/*
 * Enumerate memory regions that contain diagnostic information
 * intended to be included in crash report minidumps.
 */
extern JS_PUBLIC_API(void)
JS_EnumerateDiagnosticMemoryRegions(JSEnumerateDiagnosticMemoryCallback callback);

extern JS_PUBLIC_API(void *)
JS_malloc(JSContext *cx, size_t nbytes);

extern JS_PUBLIC_API(void *)
JS_realloc(JSContext *cx, void *p, size_t nbytes);

/*
 * A wrapper for js_free(p) that may delay js_free(p) invocation as a
 * performance optimization.
 * cx may be nullptr.
 */
extern JS_PUBLIC_API(void)
JS_free(JSContext *cx, void *p);

/*
 * A wrapper for js_free(p) that may delay js_free(p) invocation as a
 * performance optimization as specified by the given JSFreeOp instance.
 */
extern JS_PUBLIC_API(void)
JS_freeop(JSFreeOp *fop, void *p);

extern JS_PUBLIC_API(JSFreeOp *)
JS_GetDefaultFreeOp(JSRuntime *rt);

extern JS_PUBLIC_API(void)
JS_updateMallocCounter(JSContext *cx, size_t nbytes);

extern JS_PUBLIC_API(char *)
JS_strdup(JSContext *cx, const char *s);

/* Duplicate a string.  Does not report an error on failure. */
extern JS_PUBLIC_API(char *)
JS_strdup(JSRuntime *rt, const char *s);


/*
 * A GC root is a pointer to a jsval, JSObject * or JSString * that itself
 * points into the GC heap. JS_AddValueRoot takes a pointer to a jsval and
 * JS_AddGCThingRoot takes a pointer to a JSObject * or JString *.
 *
 * Note that, since JS_Add*Root stores the address of a variable (of type
 * jsval, JSString *, or JSObject *), that variable must live until
 * JS_Remove*Root is called to remove that variable. For example, after:
 *
 *   void some_function() {
 *     jsval v;
 *     JS_AddNamedValueRoot(cx, &v, "name");
 *
 * the caller must perform
 *
 *     JS_RemoveValueRoot(cx, &v);
 *
 * before some_function() returns.
 *
 * Also, use JS_AddNamed*Root(cx, &structPtr->memberObj, "structPtr->memberObj")
 * in preference to JS_Add*Root(cx, &structPtr->memberObj), in order to identify
 * roots by their source callsites.  This way, you can find the callsite while
 * debugging if you should fail to do JS_Remove*Root(cx, &structPtr->memberObj)
 * before freeing structPtr's memory.
 */
extern JS_PUBLIC_API(bool)
JS_AddValueRoot(JSContext *cx, jsval *vp);

extern JS_PUBLIC_API(bool)
JS_AddStringRoot(JSContext *cx, JSString **rp);

extern JS_PUBLIC_API(bool)
JS_AddObjectRoot(JSContext *cx, JSObject **rp);

#ifdef NAME_ALL_GC_ROOTS
#define JS_DEFINE_TO_TOKEN(def) #def
#define JS_DEFINE_TO_STRING(def) JS_DEFINE_TO_TOKEN(def)
#define JS_AddValueRoot(cx,vp) JS_AddNamedValueRoot((cx), (vp), (__FILE__ ":" JS_TOKEN_TO_STRING(__LINE__))
#define JS_AddStringRoot(cx,rp) JS_AddNamedStringRoot((cx), (rp), (__FILE__ ":" JS_TOKEN_TO_STRING(__LINE__))
#define JS_AddObjectRoot(cx,rp) JS_AddNamedObjectRoot((cx), (rp), (__FILE__ ":" JS_TOKEN_TO_STRING(__LINE__))
#endif

extern JS_PUBLIC_API(bool)
JS_AddNamedValueRoot(JSContext *cx, jsval *vp, const char *name);

extern JS_PUBLIC_API(bool)
JS_AddNamedValueRootRT(JSRuntime *rt, jsval *vp, const char *name);

extern JS_PUBLIC_API(bool)
JS_AddNamedStringRoot(JSContext *cx, JSString **rp, const char *name);

extern JS_PUBLIC_API(bool)
JS_AddNamedObjectRoot(JSContext *cx, JSObject **rp, const char *name);

extern JS_PUBLIC_API(bool)
JS_AddNamedScriptRoot(JSContext *cx, JSScript **rp, const char *name);

extern JS_PUBLIC_API(void)
JS_RemoveValueRoot(JSContext *cx, jsval *vp);

extern JS_PUBLIC_API(void)
JS_RemoveStringRoot(JSContext *cx, JSString **rp);

extern JS_PUBLIC_API(void)
JS_RemoveObjectRoot(JSContext *cx, JSObject **rp);

extern JS_PUBLIC_API(void)
JS_RemoveScriptRoot(JSContext *cx, JSScript **rp);

extern JS_PUBLIC_API(void)
JS_RemoveValueRootRT(JSRuntime *rt, jsval *vp);

extern JS_PUBLIC_API(void)
JS_RemoveStringRootRT(JSRuntime *rt, JSString **rp);

extern JS_PUBLIC_API(void)
JS_RemoveObjectRootRT(JSRuntime *rt, JSObject **rp);

extern JS_PUBLIC_API(void)
JS_RemoveScriptRootRT(JSRuntime *rt, JSScript **rp);

/* TODO: remove these APIs */

extern JS_FRIEND_API(void)
js_RemoveRoot(JSRuntime *rt, void *rp);

/*
 * C-compatible version of the Anchor class. It should be called after the last
 * use of the variable it protects.
 */
extern JS_NEVER_INLINE JS_PUBLIC_API(void)
JS_AnchorPtr(void *p);

/*
 * Register externally maintained GC roots.
 *
 * traceOp: the trace operation. For each root the implementation should call
 *          JS_CallTracer whenever the root contains a traceable thing.
 * data:    the data argument to pass to each invocation of traceOp.
 */
extern JS_PUBLIC_API(bool)
JS_AddExtraGCRootsTracer(JSRuntime *rt, JSTraceDataOp traceOp, void *data);

/* Undo a call to JS_AddExtraGCRootsTracer. */
extern JS_PUBLIC_API(void)
JS_RemoveExtraGCRootsTracer(JSRuntime *rt, JSTraceDataOp traceOp, void *data);

/*
 * JS_CallTracer API and related macros for implementors of JSTraceOp, to
 * enumerate all references to traceable things reachable via a property or
 * other strong ref identified for debugging purposes by name or index or
 * a naming callback.
 *
 * See the JSTraceOp typedef.
 */

/*
 * Use the following macros to check if a particular jsval is a traceable
 * thing and to extract the thing and its kind to pass to JS_CallTracer.
 */
static JS_ALWAYS_INLINE bool
JSVAL_IS_TRACEABLE(jsval v)
{
    return JSVAL_IS_TRACEABLE_IMPL(JSVAL_TO_IMPL(v));
}

static JS_ALWAYS_INLINE void *
JSVAL_TO_TRACEABLE(jsval v)
{
    return JSVAL_TO_GCTHING(v);
}

static JS_ALWAYS_INLINE JSGCTraceKind
JSVAL_TRACE_KIND(jsval v)
{
    JS_ASSERT(JSVAL_IS_GCTHING(v));
    return (JSGCTraceKind) JSVAL_TRACE_KIND_IMPL(JSVAL_TO_IMPL(v));
}

#ifdef DEBUG

/*
 * DEBUG-only method to dump the object graph of heap-allocated things.
 *
 * fp:              file for the dump output.
 * start:           when non-null, dump only things reachable from start
 *                  thing. Otherwise dump all things reachable from the
 *                  runtime roots.
 * startKind:       trace kind of start if start is not null. Must be
 *                  JSTRACE_OBJECT when start is null.
 * thingToFind:     dump only paths in the object graph leading to thingToFind
 *                  when non-null.
 * maxDepth:        the upper bound on the number of edges to descend from the
 *                  graph roots.
 * thingToIgnore:   thing to ignore during the graph traversal when non-null.
 */
extern JS_PUBLIC_API(bool)
JS_DumpHeap(JSRuntime *rt, FILE *fp, void* startThing, JSGCTraceKind kind,
            void *thingToFind, size_t maxDepth, void *thingToIgnore);

#endif

/*
 * Garbage collector API.
 */
extern JS_PUBLIC_API(void)
JS_GC(JSRuntime *rt);

extern JS_PUBLIC_API(void)
JS_MaybeGC(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_SetGCCallback(JSRuntime *rt, JSGCCallback cb, void *data);

extern JS_PUBLIC_API(void)
JS_SetFinalizeCallback(JSRuntime *rt, JSFinalizeCallback cb);

extern JS_PUBLIC_API(bool)
JS_IsGCMarkingTracer(JSTracer *trc);

/* For assertions only. */
#ifdef DEBUG
extern JS_PUBLIC_API(bool)
JS_IsMarkingGray(JSTracer *trc);
#endif

/*
 * JS_IsAboutToBeFinalized checks if the given object is going to be finalized
 * at the end of the current GC. When called outside of the context of a GC,
 * this function will return false. Typically this function is used on weak
 * references, where the reference should be nulled out or destroyed if the
 * given object is about to be finalized.
 *
 * The argument to JS_IsAboutToBeFinalized is an in-out param: when the
 * function returns false, the object being referenced is still alive, but the
 * garbage collector might have moved it. In this case, the reference passed
 * to JS_IsAboutToBeFinalized will be updated to the object's new location.
 * Callers of this method are responsible for updating any state that is
 * dependent on the object's address. For example, if the object's address is
 * used as a key in a hashtable, then the object must be removed and
 * re-inserted with the correct hash.
 */
extern JS_PUBLIC_API(bool)
JS_IsAboutToBeFinalized(JS::Heap<JSObject *> *objp);

extern JS_PUBLIC_API(bool)
JS_IsAboutToBeFinalizedUnbarriered(JSObject **objp);

typedef enum JSGCParamKey {
    /* Maximum nominal heap before last ditch GC. */
    JSGC_MAX_BYTES          = 0,

    /* Number of JS_malloc bytes before last ditch GC. */
    JSGC_MAX_MALLOC_BYTES   = 1,

    /* Amount of bytes allocated by the GC. */
    JSGC_BYTES = 3,

    /* Number of times when GC was invoked. */
    JSGC_NUMBER = 4,

    /* Max size of the code cache in bytes. */
    JSGC_MAX_CODE_CACHE_BYTES = 5,

    /* Select GC mode. */
    JSGC_MODE = 6,

    /* Number of cached empty GC chunks. */
    JSGC_UNUSED_CHUNKS = 7,

    /* Total number of allocated GC chunks. */
    JSGC_TOTAL_CHUNKS = 8,

    /* Max milliseconds to spend in an incremental GC slice. */
    JSGC_SLICE_TIME_BUDGET = 9,

    /* Maximum size the GC mark stack can grow to. */
    JSGC_MARK_STACK_LIMIT = 10,

    /*
     * GCs less than this far apart in time will be considered 'high-frequency GCs'.
     * See setGCLastBytes in jsgc.cpp.
     */
    JSGC_HIGH_FREQUENCY_TIME_LIMIT = 11,

    /* Start of dynamic heap growth. */
    JSGC_HIGH_FREQUENCY_LOW_LIMIT = 12,

    /* End of dynamic heap growth. */
    JSGC_HIGH_FREQUENCY_HIGH_LIMIT = 13,

    /* Upper bound of heap growth. */
    JSGC_HIGH_FREQUENCY_HEAP_GROWTH_MAX = 14,

    /* Lower bound of heap growth. */
    JSGC_HIGH_FREQUENCY_HEAP_GROWTH_MIN = 15,

    /* Heap growth for low frequency GCs. */
    JSGC_LOW_FREQUENCY_HEAP_GROWTH = 16,

    /*
     * If false, the heap growth factor is fixed at 3. If true, it is determined
     * based on whether GCs are high- or low- frequency.
     */
    JSGC_DYNAMIC_HEAP_GROWTH = 17,

    /* If true, high-frequency GCs will use a longer mark slice. */
    JSGC_DYNAMIC_MARK_SLICE = 18,

    /* Lower limit after which we limit the heap growth. */
    JSGC_ALLOCATION_THRESHOLD = 19,

    /*
     * We decommit memory lazily. If more than this number of megabytes is
     * available to be decommitted, then JS_MaybeGC will trigger a shrinking GC
     * to decommit it.
     */
    JSGC_DECOMMIT_THRESHOLD = 20
} JSGCParamKey;

typedef enum JSGCMode {
    /* Perform only global GCs. */
    JSGC_MODE_GLOBAL = 0,

    /* Perform per-compartment GCs until too much garbage has accumulated. */
    JSGC_MODE_COMPARTMENT = 1,

    /*
     * Collect in short time slices rather than all at once. Implies
     * JSGC_MODE_COMPARTMENT.
     */
    JSGC_MODE_INCREMENTAL = 2
} JSGCMode;

extern JS_PUBLIC_API(void)
JS_SetGCParameter(JSRuntime *rt, JSGCParamKey key, uint32_t value);

extern JS_PUBLIC_API(uint32_t)
JS_GetGCParameter(JSRuntime *rt, JSGCParamKey key);

extern JS_PUBLIC_API(void)
JS_SetGCParameterForThread(JSContext *cx, JSGCParamKey key, uint32_t value);

extern JS_PUBLIC_API(uint32_t)
JS_GetGCParameterForThread(JSContext *cx, JSGCParamKey key);

/*
 * Create a new JSString whose chars member refers to external memory, i.e.,
 * memory requiring application-specific finalization.
 */
extern JS_PUBLIC_API(JSString *)
JS_NewExternalString(JSContext *cx, const jschar *chars, size_t length,
                     const JSStringFinalizer *fin);

/*
 * Return whether 'str' was created with JS_NewExternalString or
 * JS_NewExternalStringWithClosure.
 */
extern JS_PUBLIC_API(bool)
JS_IsExternalString(JSString *str);

/*
 * Return the 'closure' arg passed to JS_NewExternalStringWithClosure or
 * nullptr if the external string was created via JS_NewExternalString.
 */
extern JS_PUBLIC_API(const JSStringFinalizer *)
JS_GetExternalStringFinalizer(JSString *str);

/*
 * Set the size of the native stack that should not be exceed. To disable
 * stack size checking pass 0.
 *
 * SpiderMonkey allows for a distinction between system code (such as GCs, which
 * may incidentally be triggered by script but are not strictly performed on
 * behalf of such script), trusted script (as determined by JS_SetTrustedPrincipals),
 * and untrusted script. Each kind of code may have a different stack quota,
 * allowing embedders to keep higher-priority machinery running in the face of
 * scripted stack exhaustion by something else.
 *
 * The stack quotas for each kind of code should be monotonically descending,
 * and may be specified with this function. If 0 is passed for a given kind
 * of code, it defaults to the value of the next-highest-priority kind.
 */
extern JS_PUBLIC_API(void)
JS_SetNativeStackQuota(JSRuntime *cx, size_t systemCodeStackSize,
                       size_t trustedScriptStackSize = 0,
                       size_t untrustedScriptStackSize = 0);

/************************************************************************/

extern JS_PUBLIC_API(int)
JS_IdArrayLength(JSContext *cx, JSIdArray *ida);

extern JS_PUBLIC_API(jsid)
JS_IdArrayGet(JSContext *cx, JSIdArray *ida, int index);

extern JS_PUBLIC_API(void)
JS_DestroyIdArray(JSContext *cx, JSIdArray *ida);

namespace JS {

class AutoIdArray : private AutoGCRooter
{
  public:
    AutoIdArray(JSContext *cx, JSIdArray *ida
                MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : AutoGCRooter(cx, IDARRAY), context(cx), idArray(ida)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }
    ~AutoIdArray() {
        if (idArray)
            JS_DestroyIdArray(context, idArray);
    }
    bool operator!() {
        return !idArray;
    }
    jsid operator[](size_t i) const {
        JS_ASSERT(idArray);
        JS_ASSERT(i < length());
        return JS_IdArrayGet(context, idArray, i);
    }
    size_t length() const {
        return JS_IdArrayLength(context, idArray);
    }

    friend void AutoGCRooter::trace(JSTracer *trc);

    JSIdArray *steal() {
        JSIdArray *copy = idArray;
        idArray = nullptr;
        return copy;
    }

  protected:
    inline void trace(JSTracer *trc);

  private:
    JSContext *context;
    JSIdArray *idArray;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

    /* No copy or assignment semantics. */
    AutoIdArray(AutoIdArray &ida) MOZ_DELETE;
    void operator=(AutoIdArray &ida) MOZ_DELETE;
};

} /* namespace JS */

extern JS_PUBLIC_API(bool)
JS_ValueToId(JSContext *cx, jsval v, jsid *idp);

extern JS_PUBLIC_API(bool)
JS_IdToValue(JSContext *cx, jsid id, jsval *vp);

/*
 * JSNewResolveOp flag bits.
 */
#define JSRESOLVE_ASSIGNING     0x01    /* resolve on the left of assignment */

/*
 * Invoke the [[DefaultValue]] hook (see ES5 8.6.2) with the provided hint on
 * the specified object, computing a primitive default value for the object.
 * The hint must be JSTYPE_STRING, JSTYPE_NUMBER, or JSTYPE_VOID (no hint).  On
 * success the resulting value is stored in *vp.
 */
extern JS_PUBLIC_API(bool)
JS_DefaultValue(JSContext *cx, JSObject *obj, JSType hint, jsval *vp);

extern JS_PUBLIC_API(bool)
JS_PropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_StrictPropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id, bool strict,
                      JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_DeletePropertyStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id,
                      bool *succeeded);

extern JS_PUBLIC_API(bool)
JS_EnumerateStub(JSContext *cx, JS::Handle<JSObject*> obj);

extern JS_PUBLIC_API(bool)
JS_ResolveStub(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id);

extern JS_PUBLIC_API(bool)
JS_ConvertStub(JSContext *cx, JS::Handle<JSObject*> obj, JSType type,
               JS::MutableHandle<JS::Value> vp);

struct JSConstDoubleSpec {
    double          dval;
    const char      *name;
    uint8_t         flags;
    uint8_t         spare[3];
};

struct JSJitInfo;

/*
 * Wrappers to replace {Strict,}PropertyOp for JSPropertySpecs. This will allow
 * us to pass one JSJitInfo per function with the property spec, without
 * additional field overhead.
 */
typedef struct JSStrictPropertyOpWrapper {
    JSStrictPropertyOp  op;
    const JSJitInfo     *info;
} JSStrictPropertyOpWrapper;

typedef struct JSPropertyOpWrapper {
    JSPropertyOp        op;
    const JSJitInfo     *info;
} JSPropertyOpWrapper;

/*
 * Wrapper to do as above, but for JSNatives for JSFunctionSpecs.
 */
typedef struct JSNativeWrapper {
    JSNative        op;
    const JSJitInfo *info;
} JSNativeWrapper;

/*
 * Macro static initializers which make it easy to pass no JSJitInfo as part of a
 * JSPropertySpec or JSFunctionSpec.
 */
#define JSOP_WRAPPER(op) {op, nullptr}
#define JSOP_NULLWRAPPER JSOP_WRAPPER(nullptr)

/*
 * To define an array element rather than a named property member, cast the
 * element's index to (const char *) and initialize name with it, and set the
 * JSPROP_INDEX bit in flags.
 */
struct JSPropertySpec {
    const char                  *name;
    int8_t                      tinyid;
    uint8_t                     flags;
    JSPropertyOpWrapper         getter;
    JSStrictPropertyOpWrapper   setter;
};

namespace JS {
namespace detail {

/* NEVER DEFINED, DON'T USE.  For use by JS_CAST_NATIVE_TO only. */
inline int CheckIsNative(JSNative native);

} // namespace detail
} // namespace JS

#define JS_CAST_NATIVE_TO(v, To) \
  (static_cast<void>(sizeof(JS::detail::CheckIsNative(v))), \
   reinterpret_cast<To>(v))

#define JS_CHECK_ACCESSOR_FLAGS(flags) \
  (static_cast<mozilla::EnableIf<!((flags) & (JSPROP_READONLY | JSPROP_SHARED | JSPROP_NATIVE_ACCESSORS))>::Type>(0), \
   (flags))

/*
 * JSPropertySpec uses JSAPI JSPropertyOp and JSStrictPropertyOp in function
 * signatures.  These macros encapsulate the definition of JSNative-backed
 * JSPropertySpecs, performing type-safe casts on the getter/setter functions
 * and adding the necessary property flags to trigger interpretation as
 * JSNatives.
 */
#define JS_PSG(name, getter, flags) \
    {name, 0, \
     uint8_t(JS_CHECK_ACCESSOR_FLAGS(flags) | JSPROP_SHARED | JSPROP_NATIVE_ACCESSORS), \
     JSOP_WRAPPER(JS_CAST_NATIVE_TO(getter, JSPropertyOp)), \
     JSOP_NULLWRAPPER}
#define JS_PSGS(name, getter, setter, flags) \
    {name, 0, \
     uint8_t(JS_CHECK_ACCESSOR_FLAGS(flags) | JSPROP_SHARED | JSPROP_NATIVE_ACCESSORS), \
     JSOP_WRAPPER(JS_CAST_NATIVE_TO(getter, JSPropertyOp)), \
     JSOP_WRAPPER(JS_CAST_NATIVE_TO(setter, JSStrictPropertyOp))}
#define JS_PS_END {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}

/*
 * To define a native function, set call to a JSNativeWrapper. To define a
 * self-hosted function, set selfHostedName to the name of a function
 * compiled during JSRuntime::initSelfHosting.
 */
struct JSFunctionSpec {
    const char      *name;
    JSNativeWrapper call;
    uint16_t        nargs;
    uint16_t        flags;
    const char      *selfHostedName;
};

/*
 * Terminating sentinel initializer to put at the end of a JSFunctionSpec array
 * that's passed to JS_DefineFunctions or JS_InitClass.
 */
#define JS_FS_END JS_FS(nullptr,nullptr,0,0)

/*
 * Initializer macros for a JSFunctionSpec array element. JS_FN (whose name pays
 * homage to the old JSNative/JSFastNative split) simply adds the flag
 * JSFUN_STUB_GSOPS. JS_FNINFO allows the simple adding of
 * JSJitInfos. JS_SELF_HOSTED_FN declares a self-hosted function. Finally
 * JS_FNSPEC has slots for all the fields.
 */
#define JS_FS(name,call,nargs,flags)                                          \
    JS_FNSPEC(name, call, nullptr, nargs, flags, nullptr)
#define JS_FN(name,call,nargs,flags)                                          \
    JS_FNSPEC(name, call, nullptr, nargs, (flags) | JSFUN_STUB_GSOPS, nullptr)
#define JS_FNINFO(name,call,info,nargs,flags)                                 \
    JS_FNSPEC(name, call, info, nargs, flags, nullptr)
#define JS_SELF_HOSTED_FN(name,selfHostedName,nargs,flags)                    \
    JS_FNSPEC(name, nullptr, nullptr, nargs, flags, selfHostedName)
#define JS_FNSPEC(name,call,info,nargs,flags,selfHostedName)                  \
    {name, {call, info}, nargs, flags, selfHostedName}

extern JS_PUBLIC_API(JSObject *)
JS_InitClass(JSContext *cx, JSObject *obj, JSObject *parent_proto,
             const JSClass *clasp, JSNative constructor, unsigned nargs,
             const JSPropertySpec *ps, const JSFunctionSpec *fs,
             const JSPropertySpec *static_ps, const JSFunctionSpec *static_fs);

/*
 * Set up ctor.prototype = proto and proto.constructor = ctor with the
 * right property flags.
 */
extern JS_PUBLIC_API(bool)
JS_LinkConstructorAndPrototype(JSContext *cx, JSObject *ctor, JSObject *proto);

extern JS_PUBLIC_API(const JSClass *)
JS_GetClass(JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_InstanceOf(JSContext *cx, JSObject *obj, const JSClass *clasp, jsval *argv);

extern JS_PUBLIC_API(bool)
JS_HasInstance(JSContext *cx, JSObject *obj, jsval v, bool *bp);

extern JS_PUBLIC_API(void *)
JS_GetPrivate(JSObject *obj);

extern JS_PUBLIC_API(void)
JS_SetPrivate(JSObject *obj, void *data);

extern JS_PUBLIC_API(void *)
JS_GetInstancePrivate(JSContext *cx, JSObject *obj, const JSClass *clasp,
                      jsval *argv);

extern JS_PUBLIC_API(bool)
JS_GetPrototype(JSContext *cx, JS::Handle<JSObject*> obj, JS::MutableHandle<JSObject*> protop);

extern JS_PUBLIC_API(bool)
JS_SetPrototype(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<JSObject*> proto);

extern JS_PUBLIC_API(JSObject *)
JS_GetParent(JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_SetParent(JSContext *cx, JSObject *obj, JSObject *parent);

extern JS_PUBLIC_API(JSObject *)
JS_GetConstructor(JSContext *cx, JSObject *proto);

/*
 * Get a unique identifier for obj, good for the lifetime of obj (even if it
 * is moved by a copying GC).  Return false on failure (likely out of memory),
 * and true with *idp containing the unique id on success.
 */
extern JS_PUBLIC_API(bool)
JS_GetObjectId(JSContext *cx, JSObject *obj, jsid *idp);

namespace JS {

enum ZoneSpecifier {
    FreshZone = 0,
    SystemZone = 1
};

class JS_PUBLIC_API(CompartmentOptions)
{
    union {
        ZoneSpecifier spec;
        void *pointer; // js::Zone* is not exposed in the API.
    } zone_;
    JSVersion version_;

  public:
    bool invisibleToDebugger;

    explicit CompartmentOptions()
      : version_(JSVERSION_UNKNOWN)
      , invisibleToDebugger(false)
    {
        zone_.spec = JS::FreshZone;
    }

    CompartmentOptions &setZone(ZoneSpecifier spec);

    CompartmentOptions &setSameZoneAs(JSObject *obj);

    CompartmentOptions &setVersion(JSVersion aVersion) {
        MOZ_ASSERT(aVersion != JSVERSION_UNKNOWN);
        version_ = aVersion;
        return *this;
    }

    // Certain scopes (i.e. XBL compilation scopes) are implementation details
    // of the embedding, and references to them should never leak out to script.
    // This flag causes the this compartment to skip firing onNewGlobalObject
    // and makes addDebuggee a no-op for this global.
    CompartmentOptions &setInvisibleToDebugger(bool invisible) {
        invisibleToDebugger = invisible;
        return *this;
    }

    ZoneSpecifier zoneSpecifier() const { return zone_.spec; }

    JSVersion version() const { return version_; }

    void *zonePointer() const {
        JS_ASSERT(uintptr_t(zone_.pointer) > uintptr_t(JS::SystemZone));
        return zone_.pointer;
    }
};

// During global creation, we fire notifications to callbacks registered
// via the Debugger API. These callbacks are arbitrary script, and can touch
// the global in arbitrary ways. When that happens, the global should not be
// in a half-baked state. But this creates a problem for consumers that need
// to set slots on the global to put it in a consistent state.
//
// This API provides a way for consumers to set slots atomically (immediately
// after the global is created), before any debugger hooks are fired. It's
// unfortunately on the clunky side, but that's the way the cookie crumbles.
//
// If callers have no additional state on the global to set up, they may pass
// |FireOnNewGlobalHook| to JS_NewGlobalObject, which causes that function to
// fire the hook as its final act before returning. Otherwise, callers should
// pass |DontFireOnNewGlobalHook|, which means that they are responsible for
// invoking JS_FireOnNewGlobalObject upon successfully creating the global. If
// an error occurs and the operation aborts, callers should skip firing the
// hook. But otherwise, callers must take care to fire the hook exactly once
// before compiling any script in the global's scope (we have assertions in
// place to enforce this). This lets us be sure that debugger clients never miss
// breakpoints.
enum OnNewGlobalHookOption {
    FireOnNewGlobalHook,
    DontFireOnNewGlobalHook
};

} /* namespace JS */

extern JS_PUBLIC_API(JSObject *)
JS_NewGlobalObject(JSContext *cx, const JSClass *clasp, JSPrincipals *principals,
                   JS::OnNewGlobalHookOption hookOption,
                   const JS::CompartmentOptions &options = JS::CompartmentOptions());

extern JS_PUBLIC_API(void)
JS_FireOnNewGlobalObject(JSContext *cx, JS::HandleObject global);

extern JS_PUBLIC_API(JSObject *)
JS_NewObject(JSContext *cx, const JSClass *clasp, JSObject *proto, JSObject *parent);

/* Queries the [[Extensible]] property of the object. */
extern JS_PUBLIC_API(bool)
JS_IsExtensible(JSContext *cx, JS::Handle<JSObject*> obj, bool *extensible);

extern JS_PUBLIC_API(bool)
JS_IsNative(JSObject *obj);

extern JS_PUBLIC_API(JSRuntime *)
JS_GetObjectRuntime(JSObject *obj);

/*
 * Unlike JS_NewObject, JS_NewObjectWithGivenProto does not compute a default
 * proto if proto's actual parameter value is null.
 */
extern JS_PUBLIC_API(JSObject *)
JS_NewObjectWithGivenProto(JSContext *cx, const JSClass *clasp, JSObject *proto,
                           JSObject *parent);

/*
 * Freeze obj, and all objects it refers to, recursively. This will not recurse
 * through non-extensible objects, on the assumption that those are already
 * deep-frozen.
 */
extern JS_PUBLIC_API(bool)
JS_DeepFreezeObject(JSContext *cx, JSObject *obj);

/*
 * Freezes an object; see ES5's Object.freeze(obj) method.
 */
extern JS_PUBLIC_API(bool)
JS_FreezeObject(JSContext *cx, JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_PreventExtensions(JSContext *cx, JS::Handle<JSObject*> obj);

extern JS_PUBLIC_API(JSObject *)
JS_New(JSContext *cx, JSObject *ctor, unsigned argc, jsval *argv);

extern JS_PUBLIC_API(JSObject *)
JS_DefineObject(JSContext *cx, JSObject *obj, const char *name, const JSClass *clasp,
                JSObject *proto, unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_DefineConstDoubles(JSContext *cx, JSObject *obj, const JSConstDoubleSpec *cds);

extern JS_PUBLIC_API(bool)
JS_DefineProperties(JSContext *cx, JSObject *obj, const JSPropertySpec *ps);

extern JS_PUBLIC_API(bool)
JS_DefineProperty(JSContext *cx, JSObject *obj, const char *name, jsval value,
                  JSPropertyOp getter, JSStrictPropertyOp setter, unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_DefinePropertyById(JSContext *cx, JSObject *obj, jsid id, jsval value,
                      JSPropertyOp getter, JSStrictPropertyOp setter, unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_DefineOwnProperty(JSContext *cx, JSObject *obj, jsid id, jsval descriptor, bool *bp);

extern JS_PUBLIC_API(bool)
JS_DefinePropertyWithTinyId(JSContext *cx, JSObject *obj, const char *name,
                            int8_t tinyid, jsval value,
                            JSPropertyOp getter, JSStrictPropertyOp setter,
                            unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_AlreadyHasOwnProperty(JSContext *cx, JSObject *obj, const char *name,
                         bool *foundp);

extern JS_PUBLIC_API(bool)
JS_AlreadyHasOwnPropertyById(JSContext *cx, JSObject *obj, jsid id,
                             bool *foundp);

extern JS_PUBLIC_API(bool)
JS_HasProperty(JSContext *cx, JSObject *obj, const char *name, bool *foundp);

extern JS_PUBLIC_API(bool)
JS_HasPropertyById(JSContext *cx, JSObject *obj, jsid id, bool *foundp);

extern JS_PUBLIC_API(bool)
JS_LookupProperty(JSContext *cx, JSObject *obj, const char *name, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_LookupPropertyById(JSContext *cx, JSObject *obj, jsid id, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_LookupPropertyWithFlags(JSContext *cx, JSObject *obj, const char *name,
                           unsigned flags, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_LookupPropertyWithFlagsById(JSContext *cx, JSObject *obj, jsid id,
                               unsigned flags, JSObject **objp, JS::MutableHandle<JS::Value> vp);

struct JSPropertyDescriptor {
    JSObject           *obj;
    unsigned           attrs;
    unsigned           shortid;
    JSPropertyOp       getter;
    JSStrictPropertyOp setter;
    JS::Value          value;

    JSPropertyDescriptor() : obj(nullptr), attrs(0), shortid(0), getter(nullptr),
                             setter(nullptr), value(JSVAL_VOID)
    {}

    void trace(JSTracer *trc);
};

namespace JS {

template <typename Outer>
class PropertyDescriptorOperations
{
    const JSPropertyDescriptor * desc() const { return static_cast<const Outer*>(this)->extract(); }

  public:
    bool isEnumerable() const { return desc()->attrs & JSPROP_ENUMERATE; }
    bool isReadonly() const { return desc()->attrs & JSPROP_READONLY; }
    bool isPermanent() const { return desc()->attrs & JSPROP_PERMANENT; }
    bool hasNativeAccessors() const { return desc()->attrs & JSPROP_NATIVE_ACCESSORS; }
    bool hasGetterObject() const { return desc()->attrs & JSPROP_GETTER; }
    bool hasSetterObject() const { return desc()->attrs & JSPROP_SETTER; }
    bool hasGetterOrSetterObject() const { return desc()->attrs & (JSPROP_GETTER | JSPROP_SETTER); }
    bool isShared() const { return desc()->attrs & JSPROP_SHARED; }
    bool isIndex() const { return desc()->attrs & JSPROP_INDEX; }
    bool hasShortId() const { return desc()->attrs & JSPROP_SHORTID; }
    bool hasAttributes(unsigned attrs) const { return desc()->attrs & attrs; }

    JS::Handle<JSObject*> object() const {
        return JS::Handle<JSObject*>::fromMarkedLocation(&desc()->obj);
    }
    unsigned attributes() const { return desc()->attrs; }
    unsigned shortid() const { return desc()->shortid; }
    JSPropertyOp getter() const { return desc()->getter; }
    JSStrictPropertyOp setter() const { return desc()->setter; }
    JS::Handle<JSObject*> getterObject() const {
        MOZ_ASSERT(hasGetterObject());
        return JS::Handle<JSObject*>::fromMarkedLocation(
                reinterpret_cast<JSObject *const *>(&desc()->getter));
    }
    JS::Handle<JSObject*> setterObject() const {
        MOZ_ASSERT(hasSetterObject());
        return JS::Handle<JSObject*>::fromMarkedLocation(
                reinterpret_cast<JSObject *const *>(&desc()->setter));
    }
    JS::Handle<Value> value() const {
        return JS::Handle<Value>::fromMarkedLocation(&desc()->value);
    }
};

template <typename Outer>
class MutablePropertyDescriptorOperations : public PropertyDescriptorOperations<Outer>
{
    JSPropertyDescriptor * desc() { return static_cast<Outer*>(this)->extractMutable(); }

  public:

    void clear() {
        object().set(nullptr);
        setAttributes(0);
        setShortId(0);
        setGetter(nullptr);
        setSetter(nullptr);
        value().setUndefined();
    }

    JS::MutableHandle<JSObject*> object() {
        return JS::MutableHandle<JSObject*>::fromMarkedLocation(&desc()->obj);
    }
    unsigned &attributesRef() { return desc()->attrs; }
    JSPropertyOp &getter() { return desc()->getter; }
    JSStrictPropertyOp &setter() { return desc()->setter; }
    JS::MutableHandle<Value> value() {
        return JS::MutableHandle<Value>::fromMarkedLocation(&desc()->value);
    }

    void setEnumerable() { desc()->attrs |= JSPROP_ENUMERATE; }
    void setAttributes(unsigned attrs) { desc()->attrs = attrs; }

    void setShortId(unsigned id) { desc()->shortid = id; }
    void setGetter(JSPropertyOp op) { desc()->getter = op; }
    void setSetter(JSStrictPropertyOp op) { desc()->setter = op; }
    void setGetterObject(JSObject *obj) { desc()->getter = reinterpret_cast<JSPropertyOp>(obj); }
    void setSetterObject(JSObject *obj) { desc()->setter = reinterpret_cast<JSStrictPropertyOp>(obj); }
};

} /* namespace JS */

namespace js {

template <>
struct GCMethods<JSPropertyDescriptor> {
    static JSPropertyDescriptor initial() { return JSPropertyDescriptor(); }
    static ThingRootKind kind() { return THING_ROOT_PROPERTY_DESCRIPTOR; }
    static bool poisoned(const JSPropertyDescriptor &desc) {
        return (desc.obj && JS::IsPoisonedPtr(desc.obj)) ||
               (desc.attrs & JSPROP_GETTER && desc.getter && JS::IsPoisonedPtr(desc.getter)) ||
               (desc.attrs & JSPROP_SETTER && desc.setter && JS::IsPoisonedPtr(desc.setter)) ||
               (desc.value.isGCThing() && JS::IsPoisonedPtr(desc.value.toGCThing()));
    }
};

template <>
class RootedBase<JSPropertyDescriptor>
  : public JS::MutablePropertyDescriptorOperations<JS::Rooted<JSPropertyDescriptor> >
{
    friend class JS::PropertyDescriptorOperations<JS::Rooted<JSPropertyDescriptor> >;
    friend class JS::MutablePropertyDescriptorOperations<JS::Rooted<JSPropertyDescriptor> >;
    const JSPropertyDescriptor *extract() const {
        return static_cast<const JS::Rooted<JSPropertyDescriptor>*>(this)->address();
    }
    JSPropertyDescriptor *extractMutable() {
        return static_cast<JS::Rooted<JSPropertyDescriptor>*>(this)->address();
    }
};

template <>
class HandleBase<JSPropertyDescriptor>
  : public JS::PropertyDescriptorOperations<JS::Handle<JSPropertyDescriptor> >
{
    friend class JS::PropertyDescriptorOperations<JS::Handle<JSPropertyDescriptor> >;
    const JSPropertyDescriptor *extract() const {
        return static_cast<const JS::Handle<JSPropertyDescriptor>*>(this)->address();
    }
};

template <>
class MutableHandleBase<JSPropertyDescriptor>
  : public JS::MutablePropertyDescriptorOperations<JS::MutableHandle<JSPropertyDescriptor> >
{
    friend class JS::PropertyDescriptorOperations<JS::MutableHandle<JSPropertyDescriptor> >;
    friend class JS::MutablePropertyDescriptorOperations<JS::MutableHandle<JSPropertyDescriptor> >;
    const JSPropertyDescriptor *extract() const {
        return static_cast<const JS::MutableHandle<JSPropertyDescriptor>*>(this)->address();
    }
    JSPropertyDescriptor *extractMutable() {
        return static_cast<JS::MutableHandle<JSPropertyDescriptor>*>(this)->address();
    }
};

} /* namespace js */

extern JS_PUBLIC_API(bool)
JS_GetOwnPropertyDescriptorById(JSContext *cx, JSObject *objArg, jsid id, unsigned flags,
                                JS::MutableHandle<JSPropertyDescriptor> desc);

extern JS_PUBLIC_API(bool)
JS_GetOwnPropertyDescriptor(JSContext *cx, JSObject *objArg, const char *name, unsigned flags,
                            JS::MutableHandle<JSPropertyDescriptor> desc);

/*
 * Like JS_GetOwnPropertyDescriptorById but will return a property on
 * an object on the prototype chain (returned in desc->obj). If desc->obj is null,
 * then this property was not found on the prototype chain.
 */
extern JS_PUBLIC_API(bool)
JS_GetPropertyDescriptorById(JSContext *cx, JSObject *obj, jsid id, unsigned flags,
                             JS::MutableHandle<JSPropertyDescriptor> desc);

extern JS_PUBLIC_API(bool)
JS_GetPropertyDescriptor(JSContext *cx, JSObject *obj, const char *name, unsigned flags,
                         JS::MutableHandle<JSPropertyDescriptor> desc);

extern JS_PUBLIC_API(bool)
JS_GetProperty(JSContext *cx, JSObject *obj, const char *name, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_GetPropertyById(JSContext *cx, JSObject *obj, jsid id, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_ForwardGetPropertyTo(JSContext *cx, JSObject *obj, jsid id, JSObject *onBehalfOf,
                        JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_SetProperty(JSContext *cx, JSObject *obj, const char *name, JS::Handle<JS::Value> v);

extern JS_PUBLIC_API(bool)
JS_SetPropertyById(JSContext *cx, JSObject *obj, jsid id, JS::Handle<JS::Value> v);

extern JS_PUBLIC_API(bool)
JS_DeleteProperty(JSContext *cx, JSObject *obj, const char *name);

extern JS_PUBLIC_API(bool)
JS_DeleteProperty2(JSContext *cx, JSObject *obj, const char *name, bool *succeeded);

extern JS_PUBLIC_API(bool)
JS_DeletePropertyById(JSContext *cx, JSObject *obj, jsid id);

extern JS_PUBLIC_API(bool)
JS_DeletePropertyById2(JSContext *cx, JSObject *obj, jsid id, bool *succeeded);

extern JS_PUBLIC_API(bool)
JS_DefineUCProperty(JSContext *cx, JSObject *obj,
                    const jschar *name, size_t namelen, jsval value,
                    JSPropertyOp getter, JSStrictPropertyOp setter,
                    unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_DefineUCPropertyWithTinyId(JSContext *cx, JSObject *obj,
                              const jschar *name, size_t namelen,
                              int8_t tinyid, jsval value,
                              JSPropertyOp getter, JSStrictPropertyOp setter,
                              unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_AlreadyHasOwnUCProperty(JSContext *cx, JSObject *obj, const jschar *name,
                           size_t namelen, bool *foundp);

extern JS_PUBLIC_API(bool)
JS_HasUCProperty(JSContext *cx, JSObject *obj,
                 const jschar *name, size_t namelen,
                 bool *vp);

extern JS_PUBLIC_API(bool)
JS_LookupUCProperty(JSContext *cx, JSObject *obj,
                    const jschar *name, size_t namelen,
                    JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_GetUCProperty(JSContext *cx, JSObject *obj,
                 const jschar *name, size_t namelen,
                 JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_SetUCProperty(JSContext *cx, JSObject *obj,
                 const jschar *name, size_t namelen,
                 JS::Handle<JS::Value> v);

extern JS_PUBLIC_API(bool)
JS_DeleteUCProperty2(JSContext *cx, JSObject *obj, const jschar *name, size_t namelen,
                     bool *succeeded);

extern JS_PUBLIC_API(JSObject *)
JS_NewArrayObject(JSContext *cx, int length, jsval *vector);

extern JS_PUBLIC_API(bool)
JS_IsArrayObject(JSContext *cx, JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_GetArrayLength(JSContext *cx, JSObject *obj, uint32_t *lengthp);

extern JS_PUBLIC_API(bool)
JS_SetArrayLength(JSContext *cx, JSObject *obj, uint32_t length);

extern JS_PUBLIC_API(bool)
JS_DefineElement(JSContext *cx, JSObject *obj, uint32_t index, jsval value,
                 JSPropertyOp getter, JSStrictPropertyOp setter, unsigned attrs);

extern JS_PUBLIC_API(bool)
JS_AlreadyHasOwnElement(JSContext *cx, JSObject *obj, uint32_t index, bool *foundp);

extern JS_PUBLIC_API(bool)
JS_HasElement(JSContext *cx, JSObject *obj, uint32_t index, bool *foundp);

extern JS_PUBLIC_API(bool)
JS_LookupElement(JSContext *cx, JSObject *obj, uint32_t index, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_GetElement(JSContext *cx, JSObject *obj, uint32_t index, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_ForwardGetElementTo(JSContext *cx, JSObject *obj, uint32_t index, JSObject *onBehalfOf,
                       JS::MutableHandle<JS::Value> vp);

/*
 * Get the property with name given by |index|, if it has one.  If
 * not, |*present| will be set to false and the value of |vp| must not
 * be relied on.
 */
extern JS_PUBLIC_API(bool)
JS_GetElementIfPresent(JSContext *cx, JSObject *obj, uint32_t index, JSObject *onBehalfOf,
                       JS::MutableHandle<JS::Value> vp, bool* present);

extern JS_PUBLIC_API(bool)
JS_SetElement(JSContext *cx, JSObject *obj, uint32_t index, JS::MutableHandle<JS::Value> vp);

extern JS_PUBLIC_API(bool)
JS_DeleteElement(JSContext *cx, JSObject *obj, uint32_t index);

extern JS_PUBLIC_API(bool)
JS_DeleteElement2(JSContext *cx, JSObject *obj, uint32_t index, bool *succeeded);

/*
 * Remove all configurable properties from the given (non-global) object and
 * assign undefined to all writable data properties.
 */
JS_PUBLIC_API(void)
JS_ClearNonGlobalObject(JSContext *cx, JSObject *objArg);

/*
 * Assign 'undefined' to all of the object's non-reserved slots. Note: this is
 * done for all slots, regardless of the associated property descriptor.
 */
JS_PUBLIC_API(void)
JS_SetAllNonReservedSlotsToUndefined(JSContext *cx, JSObject *objArg);

/*
 * Create a new array buffer with the given contents, which must have been
 * returned by JS_AllocateArrayBufferContents or JS_StealArrayBufferContents.
 * The new array buffer takes ownership. After calling this function, do not
 * free |contents| or use |contents| from another thread.
 */
extern JS_PUBLIC_API(JSObject *)
JS_NewArrayBufferWithContents(JSContext *cx, void *contents);

/*
 * Steal the contents of the given array buffer. The array buffer has its
 * length set to 0 and its contents array cleared. The caller takes ownership
 * of |*contents| and must free it or transfer ownership via
 * JS_NewArrayBufferWithContents when done using it.
 * To free |*contents|, call free().
 * A pointer to the buffer's data is returned in |*data|. This pointer can
 * be used until |*contents| is freed or has its ownership transferred.
 */
extern JS_PUBLIC_API(bool)
JS_StealArrayBufferContents(JSContext *cx, JSObject *obj, void **contents,
                            uint8_t **data);

/*
 * Allocate memory that may be eventually passed to
 * JS_NewArrayBufferWithContents. |nbytes| is the number of payload bytes
 * required. The pointer to pass to JS_NewArrayBufferWithContents is returned
 * in |contents|. The pointer to the |nbytes| of usable memory is returned in
 * |data|. (*|contents| will contain a header before |data|.) The only legal
 * operations on *|contents| is to free it, or pass it to
 * JS_NewArrayBufferWithContents or JS_ReallocateArrayBufferContents.
 */
extern JS_PUBLIC_API(bool)
JS_AllocateArrayBufferContents(JSContext *cx, uint32_t nbytes, void **contents, uint8_t **data);

/*
 * Reallocate memory allocated by JS_AllocateArrayBufferContents, growing or
 * shrinking it as appropriate.  The new data pointer will be returned in data.
 * If *contents is nullptr, behaves like JS_AllocateArrayBufferContents.
 */
extern JS_PUBLIC_API(bool)
JS_ReallocateArrayBufferContents(JSContext *cx, uint32_t nbytes, void **contents, uint8_t **data);

extern JS_PUBLIC_API(JSIdArray *)
JS_Enumerate(JSContext *cx, JSObject *obj);

/*
 * Create an object to iterate over enumerable properties of obj, in arbitrary
 * property definition order.  NB: This differs from longstanding for..in loop
 * order, which uses order of property definition in obj.
 */
extern JS_PUBLIC_API(JSObject *)
JS_NewPropertyIterator(JSContext *cx, JSObject *obj);

/*
 * Return true on success with *idp containing the id of the next enumerable
 * property to visit using iterobj, or JSID_IS_VOID if there is no such property
 * left to visit.  Return false on error.
 */
extern JS_PUBLIC_API(bool)
JS_NextProperty(JSContext *cx, JSObject *iterobj, jsid *idp);

extern JS_PUBLIC_API(bool)
JS_CheckAccess(JSContext *cx, JSObject *obj, jsid id, JSAccessMode mode,
               jsval *vp, unsigned *attrsp);

extern JS_PUBLIC_API(jsval)
JS_GetReservedSlot(JSObject *obj, uint32_t index);

extern JS_PUBLIC_API(void)
JS_SetReservedSlot(JSObject *obj, uint32_t index, jsval v);

/************************************************************************/

/*
 * Security protocol.
 */
struct JSPrincipals {
    /* Don't call "destroy"; use reference counting macros below. */
    int refcount;

#ifdef DEBUG
    /* A helper to facilitate principals debugging. */
    uint32_t    debugToken;
#endif

    void setDebugToken(uint32_t token) {
# ifdef DEBUG
        debugToken = token;
# endif
    }

    /*
     * This is not defined by the JS engine but should be provided by the
     * embedding.
     */
    JS_PUBLIC_API(void) dump();
};

extern JS_PUBLIC_API(void)
JS_HoldPrincipals(JSPrincipals *principals);

extern JS_PUBLIC_API(void)
JS_DropPrincipals(JSRuntime *rt, JSPrincipals *principals);

struct JSSecurityCallbacks {
    JSCheckAccessOp            checkObjectAccess;
    JSCSPEvalChecker           contentSecurityPolicyAllows;
    JSSubsumesOp               subsumes;
};

extern JS_PUBLIC_API(void)
JS_SetSecurityCallbacks(JSRuntime *rt, const JSSecurityCallbacks *callbacks);

extern JS_PUBLIC_API(const JSSecurityCallbacks *)
JS_GetSecurityCallbacks(JSRuntime *rt);

/*
 * Code running with "trusted" principals will be given a deeper stack
 * allocation than ordinary scripts. This allows trusted script to run after
 * untrusted script has exhausted the stack. This function sets the
 * runtime-wide trusted principal.
 *
 * This principals is not held (via JS_HoldPrincipals/JS_DropPrincipals) since
 * there is no available JSContext. Instead, the caller must ensure that the
 * given principals stays valid for as long as 'rt' may point to it. If the
 * principals would be destroyed before 'rt', JS_SetTrustedPrincipals must be
 * called again, passing nullptr for 'prin'.
 */
extern JS_PUBLIC_API(void)
JS_SetTrustedPrincipals(JSRuntime *rt, const JSPrincipals *prin);

/*
 * Initialize the callback that is called to destroy JSPrincipals instance
 * when its reference counter drops to zero. The initialization can be done
 * only once per JS runtime.
 */
extern JS_PUBLIC_API(void)
JS_InitDestroyPrincipalsCallback(JSRuntime *rt, JSDestroyPrincipalsOp destroyPrincipals);

/************************************************************************/

/*
 * Functions and scripts.
 */
extern JS_PUBLIC_API(JSFunction *)
JS_NewFunction(JSContext *cx, JSNative call, unsigned nargs, unsigned flags,
               JSObject *parent, const char *name);

/*
 * Create the function with the name given by the id. JSID_IS_STRING(id) must
 * be true.
 */
extern JS_PUBLIC_API(JSFunction *)
JS_NewFunctionById(JSContext *cx, JSNative call, unsigned nargs, unsigned flags,
                   JSObject *parent, jsid id);

namespace JS {

extern JS_PUBLIC_API(JSFunction *)
GetSelfHostedFunction(JSContext *cx, const char *selfHostedName, jsid id, unsigned nargs);

} /* namespace JS */

extern JS_PUBLIC_API(JSObject *)
JS_GetFunctionObject(JSFunction *fun);

/*
 * Return the function's identifier as a JSString, or null if fun is unnamed.
 * The returned string lives as long as fun, so you don't need to root a saved
 * reference to it if fun is well-connected or rooted, and provided you bound
 * the use of the saved reference by fun's lifetime.
 */
extern JS_PUBLIC_API(JSString *)
JS_GetFunctionId(JSFunction *fun);

/*
 * Return a function's display name. This is the defined name if one was given
 * where the function was defined, or it could be an inferred name by the JS
 * engine in the case that the function was defined to be anonymous. This can
 * still return nullptr if a useful display name could not be inferred. The
 * same restrictions on rooting as those in JS_GetFunctionId apply.
 */
extern JS_PUBLIC_API(JSString *)
JS_GetFunctionDisplayId(JSFunction *fun);

/*
 * Return the arity (length) of fun.
 */
extern JS_PUBLIC_API(uint16_t)
JS_GetFunctionArity(JSFunction *fun);

/*
 * Infallible predicate to test whether obj is a function object (faster than
 * comparing obj's class name to "Function", but equivalent unless someone has
 * overwritten the "Function" identifier with a different constructor and then
 * created instances using that constructor that might be passed in as obj).
 */
extern JS_PUBLIC_API(bool)
JS_ObjectIsFunction(JSContext *cx, JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_ObjectIsCallable(JSContext *cx, JSObject *obj);

extern JS_PUBLIC_API(bool)
JS_IsNativeFunction(JSObject *funobj, JSNative call);

/* Return whether the given function is a valid constructor. */
extern JS_PUBLIC_API(bool)
JS_IsConstructor(JSFunction *fun);

/*
 * Bind the given callable to use the given object as "this".
 *
 * If |callable| is not callable, will throw and return nullptr.
 */
extern JS_PUBLIC_API(JSObject*)
JS_BindCallable(JSContext *cx, JSObject *callable, JSObject *newThis);

extern JS_PUBLIC_API(bool)
JS_DefineFunctions(JSContext *cx, JSObject *obj, const JSFunctionSpec *fs);

extern JS_PUBLIC_API(JSFunction *)
JS_DefineFunction(JSContext *cx, JSObject *obj, const char *name, JSNative call,
                  unsigned nargs, unsigned attrs);

extern JS_PUBLIC_API(JSFunction *)
JS_DefineUCFunction(JSContext *cx, JSObject *obj,
                    const jschar *name, size_t namelen, JSNative call,
                    unsigned nargs, unsigned attrs);

extern JS_PUBLIC_API(JSFunction *)
JS_DefineFunctionById(JSContext *cx, JSObject *obj, jsid id, JSNative call,
                      unsigned nargs, unsigned attrs);

/*
 * Clone a top-level function into a new scope. This function will dynamically
 * fail if funobj was lexically nested inside some other function.
 */
extern JS_PUBLIC_API(JSObject *)
JS_CloneFunctionObject(JSContext *cx, JSObject *funobj, JSObject *parent);

/*
 * Given a buffer, return false if the buffer might become a valid
 * javascript statement with the addition of more lines.  Otherwise return
 * true.  The intent is to support interactive compilation - accumulate
 * lines in a buffer until JS_BufferIsCompilableUnit is true, then pass it to
 * the compiler.
 */
extern JS_PUBLIC_API(bool)
JS_BufferIsCompilableUnit(JSContext *cx, JSObject *obj, const char *utf8, size_t length);

extern JS_PUBLIC_API(JSScript *)
JS_CompileScript(JSContext *cx, JSObject *obj,
                 const char *ascii, size_t length,
                 const char *filename, unsigned lineno);

extern JS_PUBLIC_API(JSScript *)
JS_CompileScriptForPrincipals(JSContext *cx, JSObject *obj,
                              JSPrincipals *principals,
                              const char *ascii, size_t length,
                              const char *filename, unsigned lineno);

extern JS_PUBLIC_API(JSScript *)
JS_CompileUCScript(JSContext *cx, JSObject *obj,
                   const jschar *chars, size_t length,
                   const char *filename, unsigned lineno);

extern JS_PUBLIC_API(JSScript *)
JS_CompileUCScriptForPrincipals(JSContext *cx, JSObject *obj,
                                JSPrincipals *principals,
                                const jschar *chars, size_t length,
                                const char *filename, unsigned lineno);

extern JS_PUBLIC_API(JSObject *)
JS_GetGlobalFromScript(JSScript *script);

extern JS_PUBLIC_API(JSFunction *)
JS_CompileFunction(JSContext *cx, JSObject *obj, const char *name,
                   unsigned nargs, const char *const *argnames,
                   const char *bytes, size_t length,
                   const char *filename, unsigned lineno);

extern JS_PUBLIC_API(JSFunction *)
JS_CompileFunctionForPrincipals(JSContext *cx, JSObject *obj,
                                JSPrincipals *principals, const char *name,
                                unsigned nargs, const char *const *argnames,
                                const char *bytes, size_t length,
                                const char *filename, unsigned lineno);

extern JS_PUBLIC_API(JSFunction *)
JS_CompileUCFunction(JSContext *cx, JSObject *obj, const char *name,
                     unsigned nargs, const char *const *argnames,
                     const jschar *chars, size_t length,
                     const char *filename, unsigned lineno);

namespace JS {

/* Options for JavaScript compilation. */
class JS_PUBLIC_API(CompileOptions)
{
    JSPrincipals *principals_;
    JSPrincipals *originPrincipals_;

  public:
    JSPrincipals *principals() const { return principals_; }
    JSPrincipals *originPrincipals() const;

    JSVersion version;
    bool versionSet;
    bool utf8;
    const char *filename;
    const jschar *sourceMapURL;
    unsigned lineno;
    unsigned column;
    Handle<JSObject*> element;
    bool compileAndGo;
    bool forEval;
    bool noScriptRval;
    bool selfHostingMode;
    bool canLazilyParse;
    bool strictOption;
    bool extraWarningsOption;
    bool werrorOption;
    bool asmJSOption;
    enum SourcePolicy {
        NO_SOURCE,
        LAZY_SOURCE,
        SAVE_SOURCE
    } sourcePolicy;

    explicit CompileOptions(JSContext *cx, JSVersion version = JSVERSION_UNKNOWN);
    CompileOptions &setPrincipals(JSPrincipals *p) { principals_ = p; return *this; }
    CompileOptions &setOriginPrincipals(JSPrincipals *p) { originPrincipals_ = p; return *this; }
    CompileOptions &setVersion(JSVersion v) { version = v; versionSet = true; return *this; }
    CompileOptions &setUTF8(bool u) { utf8 = u; return *this; }
    CompileOptions &setFileAndLine(const char *f, unsigned l) {
        filename = f; lineno = l; return *this;
    }
    CompileOptions &setSourceMapURL(const jschar *s) { sourceMapURL = s; return *this; }
    CompileOptions &setColumn(unsigned c) { column = c; return *this; }
    CompileOptions &setElement(Handle<JSObject*> e) { element.repoint(e); return *this; }
    CompileOptions &setCompileAndGo(bool cng) { compileAndGo = cng; return *this; }
    CompileOptions &setForEval(bool eval) { forEval = eval; return *this; }
    CompileOptions &setNoScriptRval(bool nsr) { noScriptRval = nsr; return *this; }
    CompileOptions &setSelfHostingMode(bool shm) { selfHostingMode = shm; return *this; }
    CompileOptions &setCanLazilyParse(bool clp) { canLazilyParse = clp; return *this; }
    CompileOptions &setSourcePolicy(SourcePolicy sp) { sourcePolicy = sp; return *this; }
};

extern JS_PUBLIC_API(JSScript *)
Compile(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
        const char *bytes, size_t length);

extern JS_PUBLIC_API(JSScript *)
Compile(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
        const jschar *chars, size_t length);

extern JS_PUBLIC_API(JSScript *)
Compile(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options, FILE *file);

extern JS_PUBLIC_API(JSScript *)
Compile(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options, const char *filename);

extern JS_PUBLIC_API(bool)
CanCompileOffThread(JSContext *cx, const CompileOptions &options);

/*
 * Off thread compilation control flow.
 *
 * After successfully triggering an off thread compile of a script, the
 * callback will eventually be invoked with the specified data and a token
 * for the compilation. The callback will be invoked while off the main thread,
 * so must ensure that its operations are thread safe. Afterwards,
 * FinishOffThreadScript must be invoked on the main thread to get the result
 * script or nullptr. If maybecx is specified, this method will also report
 * any error or warnings generated during the parse.
 *
 * The characters passed in to CompileOffThread must remain live until the
 * callback is invoked, and the resulting script will be rooted until the call
 * to FinishOffThreadScript.
 */

extern JS_PUBLIC_API(bool)
CompileOffThread(JSContext *cx, Handle<JSObject*> obj, CompileOptions options,
                 const jschar *chars, size_t length,
                 OffThreadCompileCallback callback, void *callbackData);

extern JS_PUBLIC_API(JSScript *)
FinishOffThreadScript(JSContext *maybecx, JSRuntime *rt, void *token);

extern JS_PUBLIC_API(JSFunction *)
CompileFunction(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
                const char *name, unsigned nargs, const char *const *argnames,
                const char *bytes, size_t length);

extern JS_PUBLIC_API(JSFunction *)
CompileFunction(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
                const char *name, unsigned nargs, const char *const *argnames,
                const jschar *chars, size_t length);

} /* namespace JS */

extern JS_PUBLIC_API(JSString *)
JS_DecompileScript(JSContext *cx, JSScript *script, const char *name, unsigned indent);

/*
 * API extension: OR this into indent to avoid pretty-printing the decompiled
 * source resulting from JS_DecompileFunction{,Body}.
 */
#define JS_DONT_PRETTY_PRINT    ((unsigned)0x8000)

extern JS_PUBLIC_API(JSString *)
JS_DecompileFunction(JSContext *cx, JSFunction *fun, unsigned indent);

extern JS_PUBLIC_API(JSString *)
JS_DecompileFunctionBody(JSContext *cx, JSFunction *fun, unsigned indent);

/*
 * NB: JS_ExecuteScript and the JS_Evaluate*Script* quadruplets use the obj
 * parameter as the initial scope chain header, the 'this' keyword value, and
 * the variables object (ECMA parlance for where 'var' and 'function' bind
 * names) of the execution context for script.
 *
 * Using obj as the variables object is problematic if obj's parent (which is
 * the scope chain link; see JS_SetParent and JS_NewObject) is not null: in
 * this case, variables created by 'var x = 0', e.g., go in obj, but variables
 * created by assignment to an unbound id, 'x = 0', go in the last object on
 * the scope chain linked by parent.
 *
 * ECMA calls that last scoping object the "global object", but note that many
 * embeddings have several such objects.  ECMA requires that "global code" be
 * executed with the variables object equal to this global object.  But these
 * JS API entry points provide freedom to execute code against a "sub-global",
 * i.e., a parented or scoped object, in which case the variables object will
 * differ from the last object on the scope chain, resulting in confusing and
 * non-ECMA explicit vs. implicit variable creation.
 *
 * Caveat embedders: unless you already depend on this buggy variables object
 * binding behavior, you should call ContextOptionsRef(cx).setVarObjFix(true)
 * for each context in the application, if you pass parented objects as the obj
 * parameter, or may ever pass such objects in the future.
 *
 * Why a runtime option?  The alternative is to add six or so new API entry
 * points with signatures matching the following six, and that doesn't seem
 * worth the code bloat cost.  Such new entry points would probably have less
 * obvious names, too, so would not tend to be used.  The JS_SetOption call,
 * OTOH, can be more easily hacked into existing code that does not depend on
 * the bug; such code can continue to use the familiar JS_EvaluateScript,
 * etc., entry points.
 */
extern JS_PUBLIC_API(bool)
JS_ExecuteScript(JSContext *cx, JSObject *obj, JSScript *script, jsval *rval);

extern JS_PUBLIC_API(bool)
JS_ExecuteScriptVersion(JSContext *cx, JSObject *obj, JSScript *script, jsval *rval,
                        JSVersion version);

/*
 * Execute either the function-defining prolog of a script, or the script's
 * main body, but not both.
 */
typedef enum JSExecPart { JSEXEC_PROLOG, JSEXEC_MAIN } JSExecPart;

extern JS_PUBLIC_API(bool)
JS_EvaluateScript(JSContext *cx, JSObject *obj,
                  const char *bytes, unsigned length,
                  const char *filename, unsigned lineno,
                  jsval *rval);

extern JS_PUBLIC_API(bool)
JS_EvaluateScriptForPrincipals(JSContext *cx, JSObject *obj,
                               JSPrincipals *principals,
                               const char *bytes, unsigned length,
                               const char *filename, unsigned lineno,
                               jsval *rval);

extern JS_PUBLIC_API(bool)
JS_EvaluateScriptForPrincipalsVersion(JSContext *cx, JSObject *obj,
                                      JSPrincipals *principals,
                                      const char *bytes, unsigned length,
                                      const char *filename, unsigned lineno,
                                      jsval *rval, JSVersion version);

extern JS_PUBLIC_API(bool)
JS_EvaluateUCScript(JSContext *cx, JSObject *obj,
                    const jschar *chars, unsigned length,
                    const char *filename, unsigned lineno,
                    jsval *rval);

extern JS_PUBLIC_API(bool)
JS_EvaluateUCScriptForPrincipals(JSContext *cx, JSObject *obj,
                                 JSPrincipals *principals,
                                 const jschar *chars, unsigned length,
                                 const char *filename, unsigned lineno,
                                 jsval *rval);

extern JS_PUBLIC_API(bool)
JS_EvaluateUCScriptForPrincipalsVersion(JSContext *cx, JSObject *obj,
                                        JSPrincipals *principals,
                                        const jschar *chars, unsigned length,
                                        const char *filename, unsigned lineno,
                                        jsval *rval, JSVersion version);

/*
 * JSAPI clients may optionally specify the 'originPrincipals' of a script.
 * A script's originPrincipals may be retrieved through the debug API (via
 * JS_GetScriptOriginPrincipals) and the originPrincipals are transitively
 * assigned to any nested scripts (including scripts dynamically created via
 * eval and the Function constructor). If originPrincipals is null, then the
 * value of principals is used as origin principals for the script.
 */
extern JS_PUBLIC_API(bool)
JS_EvaluateUCScriptForPrincipalsVersionOrigin(JSContext *cx, JSObject *obj,
                                              JSPrincipals *principals,
                                              JSPrincipals *originPrincipals,
                                              const jschar *chars, unsigned length,
                                              const char *filename, unsigned lineno,
                                              jsval *rval, JSVersion version);

namespace JS {

extern JS_PUBLIC_API(bool)
Evaluate(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
         const jschar *chars, size_t length, jsval *rval);

extern JS_PUBLIC_API(bool)
Evaluate(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
         const char *bytes, size_t length, jsval *rval);

extern JS_PUBLIC_API(bool)
Evaluate(JSContext *cx, JS::Handle<JSObject*> obj, CompileOptions options,
         const char *filename, jsval *rval);

} /* namespace JS */

extern JS_PUBLIC_API(bool)
JS_CallFunction(JSContext *cx, JSObject *obj, JSFunction *fun, unsigned argc,
                jsval *argv, jsval *rval);

extern JS_PUBLIC_API(bool)
JS_CallFunctionName(JSContext *cx, JSObject *obj, const char *name, unsigned argc,
                    jsval *argv, jsval *rval);

extern JS_PUBLIC_API(bool)
JS_CallFunctionValue(JSContext *cx, JSObject *obj, jsval fval, unsigned argc,
                     jsval *argv, jsval *rval);

namespace JS {

static inline bool
Call(JSContext *cx, JSObject *thisObj, JSFunction *fun, unsigned argc, jsval *argv,
     MutableHandle<Value> rval)
{
    return !!JS_CallFunction(cx, thisObj, fun, argc, argv, rval.address());
}

static inline bool
Call(JSContext *cx, JSObject *thisObj, const char *name, unsigned argc, jsval *argv,
     MutableHandle<Value> rval)
{
    return !!JS_CallFunctionName(cx, thisObj, name, argc, argv, rval.address());
}

static inline bool
Call(JSContext *cx, JSObject *thisObj, jsval fun, unsigned argc, jsval *argv,
     MutableHandle<Value> rval)
{
    return !!JS_CallFunctionValue(cx, thisObj, fun, argc, argv, rval.address());
}

extern JS_PUBLIC_API(bool)
Call(JSContext *cx, jsval thisv, jsval fun, unsigned argc, jsval *argv, MutableHandle<Value> rval);

static inline bool
Call(JSContext *cx, jsval thisv, JSObject *funObj, unsigned argc, jsval *argv,
     MutableHandle<Value> rval)
{
    return Call(cx, thisv, OBJECT_TO_JSVAL(funObj), argc, argv, rval);
}

} /* namespace JS */

/*
 * These functions allow setting an operation callback that will be called
 * from the JS thread some time after any thread triggered the callback using
 * JS_TriggerOperationCallback(rt).
 *
 * To schedule the GC and for other activities the engine internally triggers
 * operation callbacks. The embedding should thus not rely on callbacks being
 * triggered through the external API only.
 *
 * Important note: Additional callbacks can occur inside the callback handler
 * if it re-enters the JS engine. The embedding must ensure that the callback
 * is disconnected before attempting such re-entry.
 */
extern JS_PUBLIC_API(JSOperationCallback)
JS_SetOperationCallback(JSRuntime *rt, JSOperationCallback callback);

extern JS_PUBLIC_API(JSOperationCallback)
JS_GetOperationCallback(JSRuntime *rt);

extern JS_PUBLIC_API(void)
JS_TriggerOperationCallback(JSRuntime *rt);

extern JS_PUBLIC_API(bool)
JS_IsRunning(JSContext *cx);

/*
 * Saving and restoring frame chains.
 *
 * These two functions are used to set aside cx's call stack while that stack
 * is inactive. After a call to JS_SaveFrameChain, it looks as if there is no
 * code running on cx. Before calling JS_RestoreFrameChain, cx's call stack
 * must be balanced and all nested calls to JS_SaveFrameChain must have had
 * matching JS_RestoreFrameChain calls.
 *
 * JS_SaveFrameChain deals with cx not having any code running on it.
 */
extern JS_PUBLIC_API(bool)
JS_SaveFrameChain(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_RestoreFrameChain(JSContext *cx);

#ifdef MOZ_TRACE_JSCALLS
/*
 * The callback is expected to be quick and noninvasive. It should not
 * trigger interrupts, turn on debugging, or produce uncaught JS
 * exceptions. The state of the stack and registers in the context
 * cannot be relied upon, since this callback may be invoked directly
 * from either JIT. The 'entering' field means we are entering a
 * function if it is positive, leaving a function if it is zero or
 * negative.
 */
extern JS_PUBLIC_API(void)
JS_SetFunctionCallback(JSContext *cx, JSFunctionCallback fcb);

extern JS_PUBLIC_API(JSFunctionCallback)
JS_GetFunctionCallback(JSContext *cx);
#endif /* MOZ_TRACE_JSCALLS */

/************************************************************************/

/*
 * Strings.
 *
 * NB: JS_NewUCString takes ownership of bytes on success, avoiding a copy;
 * but on error (signified by null return), it leaves chars owned by the
 * caller. So the caller must free bytes in the error case, if it has no use
 * for them. In contrast, all the JS_New*StringCopy* functions do not take
 * ownership of the character memory passed to them -- they copy it.
 */
extern JS_PUBLIC_API(JSString *)
JS_NewStringCopyN(JSContext *cx, const char *s, size_t n);

extern JS_PUBLIC_API(JSString *)
JS_NewStringCopyZ(JSContext *cx, const char *s);

extern JS_PUBLIC_API(JSString *)
JS_InternJSString(JSContext *cx, JS::HandleString str);

extern JS_PUBLIC_API(JSString *)
JS_InternStringN(JSContext *cx, const char *s, size_t length);

extern JS_PUBLIC_API(JSString *)
JS_InternString(JSContext *cx, const char *s);

extern JS_PUBLIC_API(JSString *)
JS_NewUCString(JSContext *cx, jschar *chars, size_t length);

extern JS_PUBLIC_API(JSString *)
JS_NewUCStringCopyN(JSContext *cx, const jschar *s, size_t n);

extern JS_PUBLIC_API(JSString *)
JS_NewUCStringCopyZ(JSContext *cx, const jschar *s);

extern JS_PUBLIC_API(JSString *)
JS_InternUCStringN(JSContext *cx, const jschar *s, size_t length);

extern JS_PUBLIC_API(JSString *)
JS_InternUCString(JSContext *cx, const jschar *s);

extern JS_PUBLIC_API(bool)
JS_CompareStrings(JSContext *cx, JSString *str1, JSString *str2, int32_t *result);

extern JS_PUBLIC_API(bool)
JS_StringEqualsAscii(JSContext *cx, JSString *str, const char *asciiBytes, bool *match);

extern JS_PUBLIC_API(size_t)
JS_PutEscapedString(JSContext *cx, char *buffer, size_t size, JSString *str, char quote);

extern JS_PUBLIC_API(bool)
JS_FileEscapedString(FILE *fp, JSString *str, char quote);

/*
 * Extracting string characters and length.
 *
 * While getting the length of a string is infallible, getting the chars can
 * fail. As indicated by the lack of a JSContext parameter, there are two
 * special cases where getting the chars is infallible:
 *
 * The first case is interned strings, i.e., strings from JS_InternString or
 * JSID_TO_STRING(id), using JS_GetInternedStringChars*.
 *
 * The second case is "flat" strings that have been explicitly prepared in a
 * fallible context by JS_FlattenString. To catch errors, a separate opaque
 * JSFlatString type is returned by JS_FlattenString and expected by
 * JS_GetFlatStringChars. Note, though, that this is purely a syntactic
 * distinction: the input and output of JS_FlattenString are the same actual
 * GC-thing so only one needs to be rooted. If a JSString is known to be flat,
 * JS_ASSERT_STRING_IS_FLAT can be used to make a debug-checked cast. Example:
 *
 *   // in a fallible context
 *   JSFlatString *fstr = JS_FlattenString(cx, str);
 *   if (!fstr)
 *     return false;
 *   JS_ASSERT(fstr == JS_ASSERT_STRING_IS_FLAT(str));
 *
 *   // in an infallible context, for the same 'str'
 *   const jschar *chars = JS_GetFlatStringChars(fstr)
 *   JS_ASSERT(chars);
 *
 * The CharsZ APIs guarantee that the returned array has a null character at
 * chars[length]. This can require additional copying so clients should prefer
 * APIs without CharsZ if possible. The infallible functions also return
 * null-terminated arrays. (There is no additional cost or non-Z alternative
 * for the infallible functions, so 'Z' is left out of the identifier.)
 */

extern JS_PUBLIC_API(size_t)
JS_GetStringLength(JSString *str);

extern JS_PUBLIC_API(const jschar *)
JS_GetStringCharsAndLength(JSContext *cx, JSString *str, size_t *length);

extern JS_PUBLIC_API(const jschar *)
JS_GetInternedStringChars(JSString *str);

extern JS_PUBLIC_API(const jschar *)
JS_GetInternedStringCharsAndLength(JSString *str, size_t *length);

extern JS_PUBLIC_API(const jschar *)
JS_GetStringCharsZ(JSContext *cx, JSString *str);

extern JS_PUBLIC_API(const jschar *)
JS_GetStringCharsZAndLength(JSContext *cx, JSString *str, size_t *length);

extern JS_PUBLIC_API(JSFlatString *)
JS_FlattenString(JSContext *cx, JSString *str);

extern JS_PUBLIC_API(const jschar *)
JS_GetFlatStringChars(JSFlatString *str);

static JS_ALWAYS_INLINE JSFlatString *
JSID_TO_FLAT_STRING(jsid id)
{
    JS_ASSERT(JSID_IS_STRING(id));
    return (JSFlatString *)(JSID_BITS(id));
}

static JS_ALWAYS_INLINE JSFlatString *
JS_ASSERT_STRING_IS_FLAT(JSString *str)
{
    JS_ASSERT(JS_GetFlatStringChars((JSFlatString *)str));
    return (JSFlatString *)str;
}

static JS_ALWAYS_INLINE JSString *
JS_FORGET_STRING_FLATNESS(JSFlatString *fstr)
{
    return (JSString *)fstr;
}

/*
 * Additional APIs that avoid fallibility when given a flat string.
 */

extern JS_PUBLIC_API(bool)
JS_FlatStringEqualsAscii(JSFlatString *str, const char *asciiBytes);

extern JS_PUBLIC_API(size_t)
JS_PutEscapedFlatString(char *buffer, size_t size, JSFlatString *str, char quote);

/*
 * Create a dependent string, i.e., a string that owns no character storage,
 * but that refers to a slice of another string's chars.  Dependent strings
 * are mutable by definition, so the thread safety comments above apply.
 */
extern JS_PUBLIC_API(JSString *)
JS_NewDependentString(JSContext *cx, JS::HandleString str, size_t start,
                      size_t length);

/*
 * Concatenate two strings, possibly resulting in a rope.
 * See above for thread safety comments.
 */
extern JS_PUBLIC_API(JSString *)
JS_ConcatStrings(JSContext *cx, JS::HandleString left, JS::HandleString right);

/*
 * For JS_DecodeBytes, set *dstlenp to the size of the destination buffer before
 * the call; on return, *dstlenp contains the number of jschars actually stored.
 * To determine the necessary destination buffer size, make a sizing call that
 * passes nullptr for dst.
 *
 * On errors, the functions report the error. In that case, *dstlenp contains
 * the number of characters or bytes transferred so far.  If cx is nullptr, no
 * error is reported on failure, and the functions simply return false.
 *
 * NB: This function does not store an additional zero byte or jschar after the
 * transcoded string.
 */
JS_PUBLIC_API(bool)
JS_DecodeBytes(JSContext *cx, const char *src, size_t srclen, jschar *dst,
               size_t *dstlenp);

/*
 * A variation on JS_EncodeCharacters where a null terminated string is
 * returned that you are expected to call JS_free on when done.
 */
JS_PUBLIC_API(char *)
JS_EncodeString(JSContext *cx, JSString *str);

/*
 * Same behavior as JS_EncodeString(), but encode into UTF-8 string
 */
JS_PUBLIC_API(char *)
JS_EncodeStringToUTF8(JSContext *cx, JSString *str);

/*
 * Get number of bytes in the string encoding (without accounting for a
 * terminating zero bytes. The function returns (size_t) -1 if the string
 * can not be encoded into bytes and reports an error using cx accordingly.
 */
JS_PUBLIC_API(size_t)
JS_GetStringEncodingLength(JSContext *cx, JSString *str);

/*
 * Encode string into a buffer. The function does not stores an additional
 * zero byte. The function returns (size_t) -1 if the string can not be
 * encoded into bytes with no error reported. Otherwise it returns the number
 * of bytes that are necessary to encode the string. If that exceeds the
 * length parameter, the string will be cut and only length bytes will be
 * written into the buffer.
 */
JS_PUBLIC_API(size_t)
JS_EncodeStringToBuffer(JSContext *cx, JSString *str, char *buffer, size_t length);

class JSAutoByteString
{
  public:
    JSAutoByteString(JSContext *cx, JSString *str
                     MOZ_GUARD_OBJECT_NOTIFIER_PARAM)
      : mBytes(JS_EncodeString(cx, str))
    {
        JS_ASSERT(cx);
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    JSAutoByteString(MOZ_GUARD_OBJECT_NOTIFIER_ONLY_PARAM)
      : mBytes(nullptr)
    {
        MOZ_GUARD_OBJECT_NOTIFIER_INIT;
    }

    ~JSAutoByteString() {
        js_free(mBytes);
    }

    /* Take ownership of the given byte array. */
    void initBytes(char *bytes) {
        JS_ASSERT(!mBytes);
        mBytes = bytes;
    }

    char *encodeLatin1(JSContext *cx, JSString *str) {
        JS_ASSERT(!mBytes);
        JS_ASSERT(cx);
        mBytes = JS_EncodeString(cx, str);
        return mBytes;
    }

    char *encodeLatin1(js::ExclusiveContext *cx, JSString *str);

    char *encodeUtf8(JSContext *cx, JSString *str) {
        JS_ASSERT(!mBytes);
        JS_ASSERT(cx);
        mBytes = JS_EncodeStringToUTF8(cx, str);
        return mBytes;
    }

    void clear() {
        js_free(mBytes);
        mBytes = nullptr;
    }

    char *ptr() const {
        return mBytes;
    }

    bool operator!() const {
        return !mBytes;
    }

    size_t length() const {
        if (!mBytes)
            return 0;
        return strlen(mBytes);
    }

  private:
    char        *mBytes;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

    /* Copy and assignment are not supported. */
    JSAutoByteString(const JSAutoByteString &another);
    JSAutoByteString &operator=(const JSAutoByteString &another);
};

/************************************************************************/
/*
 * JSON functions
 */
typedef bool (* JSONWriteCallback)(const jschar *buf, uint32_t len, void *data);

/*
 * JSON.stringify as specified by ES5.
 */
JS_PUBLIC_API(bool)
JS_Stringify(JSContext *cx, JS::MutableHandleValue value, JS::HandleObject replacer,
             JS::HandleValue space, JSONWriteCallback callback, void *data);

/*
 * JSON.parse as specified by ES5.
 */
JS_PUBLIC_API(bool)
JS_ParseJSON(JSContext *cx, const jschar *chars, uint32_t len, JS::MutableHandleValue vp);

JS_PUBLIC_API(bool)
JS_ParseJSONWithReviver(JSContext *cx, const jschar *chars, uint32_t len, JS::HandleValue reviver,
                        JS::MutableHandleValue vp);

/************************************************************************/

/*
 * The default locale for the ECMAScript Internationalization API
 * (Intl.Collator, Intl.NumberFormat, Intl.DateTimeFormat).
 * Note that the Internationalization API encourages clients to
 * specify their own locales.
 * The locale string remains owned by the caller.
 */
extern JS_PUBLIC_API(bool)
JS_SetDefaultLocale(JSRuntime *rt, const char *locale);

/*
 * Reset the default locale to OS defaults.
 */
extern JS_PUBLIC_API(void)
JS_ResetDefaultLocale(JSRuntime *rt);

/*
 * Locale specific string conversion and error message callbacks.
 */
struct JSLocaleCallbacks {
    JSLocaleToUpperCase     localeToUpperCase;
    JSLocaleToLowerCase     localeToLowerCase;
    JSLocaleCompare         localeCompare; // not used #if EXPOSE_INTL_API
    JSLocaleToUnicode       localeToUnicode;
    JSErrorCallback         localeGetErrorMessage;
};

/*
 * Establish locale callbacks. The pointer must persist as long as the
 * JSRuntime.  Passing nullptr restores the default behaviour.
 */
extern JS_PUBLIC_API(void)
JS_SetLocaleCallbacks(JSRuntime *rt, JSLocaleCallbacks *callbacks);

/*
 * Return the address of the current locale callbacks struct, which may
 * be nullptr.
 */
extern JS_PUBLIC_API(JSLocaleCallbacks *)
JS_GetLocaleCallbacks(JSRuntime *rt);

/************************************************************************/

/*
 * Error reporting.
 */

/*
 * Report an exception represented by the sprintf-like conversion of format
 * and its arguments.  This exception message string is passed to a pre-set
 * JSErrorReporter function (set by JS_SetErrorReporter).
 */
extern JS_PUBLIC_API(void)
JS_ReportError(JSContext *cx, const char *format, ...);

/*
 * Use an errorNumber to retrieve the format string, args are char *
 */
extern JS_PUBLIC_API(void)
JS_ReportErrorNumber(JSContext *cx, JSErrorCallback errorCallback,
                     void *userRef, const unsigned errorNumber, ...);

#ifdef va_start
extern JS_PUBLIC_API(void)
JS_ReportErrorNumberVA(JSContext *cx, JSErrorCallback errorCallback,
                       void *userRef, const unsigned errorNumber, va_list ap);
#endif

/*
 * Use an errorNumber to retrieve the format string, args are jschar *
 */
extern JS_PUBLIC_API(void)
JS_ReportErrorNumberUC(JSContext *cx, JSErrorCallback errorCallback,
                     void *userRef, const unsigned errorNumber, ...);

extern JS_PUBLIC_API(void)
JS_ReportErrorNumberUCArray(JSContext *cx, JSErrorCallback errorCallback,
                            void *userRef, const unsigned errorNumber,
                            const jschar **args);

/*
 * As above, but report a warning instead (JSREPORT_IS_WARNING(report.flags)).
 * Return true if there was no error trying to issue the warning, and if the
 * warning was not converted into an error due to the JSOPTION_WERROR option
 * being set, false otherwise.
 */
extern JS_PUBLIC_API(bool)
JS_ReportWarning(JSContext *cx, const char *format, ...);

extern JS_PUBLIC_API(bool)
JS_ReportErrorFlagsAndNumber(JSContext *cx, unsigned flags,
                             JSErrorCallback errorCallback, void *userRef,
                             const unsigned errorNumber, ...);

extern JS_PUBLIC_API(bool)
JS_ReportErrorFlagsAndNumberUC(JSContext *cx, unsigned flags,
                               JSErrorCallback errorCallback, void *userRef,
                               const unsigned errorNumber, ...);

/*
 * Complain when out of memory.
 */
extern JS_PUBLIC_API(void)
JS_ReportOutOfMemory(JSContext *cx);

/*
 * Complain when an allocation size overflows the maximum supported limit.
 */
extern JS_PUBLIC_API(void)
JS_ReportAllocationOverflow(JSContext *cx);

struct JSErrorReport {
    const char      *filename;      /* source file name, URL, etc., or null */
    JSPrincipals    *originPrincipals; /* see 'originPrincipals' comment above */
    unsigned        lineno;         /* source line number */
    const char      *linebuf;       /* offending source line without final \n */
    const char      *tokenptr;      /* pointer to error token in linebuf */
    const jschar    *uclinebuf;     /* unicode (original) line buffer */
    const jschar    *uctokenptr;    /* unicode (original) token pointer */
    unsigned        flags;          /* error/warning, etc. */
    unsigned        errorNumber;    /* the error number, e.g. see js.msg */
    const jschar    *ucmessage;     /* the (default) error message */
    const jschar    **messageArgs;  /* arguments for the error message */
    int16_t         exnType;        /* One of the JSExnType constants */
    unsigned        column;         /* zero-based column index in line */
};

/*
 * JSErrorReport flag values.  These may be freely composed.
 */
#define JSREPORT_ERROR      0x0     /* pseudo-flag for default case */
#define JSREPORT_WARNING    0x1     /* reported via JS_ReportWarning */
#define JSREPORT_EXCEPTION  0x2     /* exception was thrown */
#define JSREPORT_STRICT     0x4     /* error or warning due to strict option */

/*
 * This condition is an error in strict mode code, a warning if
 * JS_HAS_STRICT_OPTION(cx), and otherwise should not be reported at
 * all.  We check the strictness of the context's top frame's script;
 * where that isn't appropriate, the caller should do the right checks
 * itself instead of using this flag.
 */
#define JSREPORT_STRICT_MODE_ERROR 0x8

/*
 * If JSREPORT_EXCEPTION is set, then a JavaScript-catchable exception
 * has been thrown for this runtime error, and the host should ignore it.
 * Exception-aware hosts should also check for JS_IsExceptionPending if
 * JS_ExecuteScript returns failure, and signal or propagate the exception, as
 * appropriate.
 */
#define JSREPORT_IS_WARNING(flags)      (((flags) & JSREPORT_WARNING) != 0)
#define JSREPORT_IS_EXCEPTION(flags)    (((flags) & JSREPORT_EXCEPTION) != 0)
#define JSREPORT_IS_STRICT(flags)       (((flags) & JSREPORT_STRICT) != 0)
#define JSREPORT_IS_STRICT_MODE_ERROR(flags) (((flags) &                      \
                                              JSREPORT_STRICT_MODE_ERROR) != 0)
extern JS_PUBLIC_API(JSErrorReporter)
JS_GetErrorReporter(JSContext *cx);

extern JS_PUBLIC_API(JSErrorReporter)
JS_SetErrorReporter(JSContext *cx, JSErrorReporter er);

/************************************************************************/

/*
 * Dates.
 */

extern JS_PUBLIC_API(JSObject *)
JS_NewDateObject(JSContext *cx, int year, int mon, int mday, int hour, int min, int sec);

extern JS_PUBLIC_API(JSObject *)
JS_NewDateObjectMsec(JSContext *cx, double msec);

/*
 * Infallible predicate to test whether obj is a date object.
 */
extern JS_PUBLIC_API(bool)
JS_ObjectIsDate(JSContext *cx, JS::HandleObject obj);

/*
 * Clears the cache of calculated local time from each Date object.
 * Call to propagate a system timezone change.
 */
extern JS_PUBLIC_API(void)
JS_ClearDateCaches(JSContext *cx);

/************************************************************************/

/*
 * Regular Expressions.
 */
#define JSREG_FOLD      0x01    /* fold uppercase to lowercase */
#define JSREG_GLOB      0x02    /* global exec, creates array of matches */
#define JSREG_MULTILINE 0x04    /* treat ^ and $ as begin and end of line */
#define JSREG_STICKY    0x08    /* only match starting at lastIndex */

extern JS_PUBLIC_API(JSObject *)
JS_NewRegExpObject(JSContext *cx, JS::HandleObject obj, char *bytes, size_t length,
                   unsigned flags);

extern JS_PUBLIC_API(JSObject *)
JS_NewUCRegExpObject(JSContext *cx, JS::HandleObject obj, jschar *chars, size_t length,
                     unsigned flags);

extern JS_PUBLIC_API(void)
JS_SetRegExpInput(JSContext *cx, JS::HandleObject obj, JS::HandleString input,
                  bool multiline);

extern JS_PUBLIC_API(void)
JS_ClearRegExpStatics(JSContext *cx, JS::HandleObject obj);

extern JS_PUBLIC_API(bool)
JS_ExecuteRegExp(JSContext *cx, JS::HandleObject obj, JS::HandleObject reobj,
                 jschar *chars, size_t length, size_t *indexp, bool test,
                 JS::MutableHandleValue rval);

/* RegExp interface for clients without a global object. */

extern JS_PUBLIC_API(JSObject *)
JS_NewRegExpObjectNoStatics(JSContext *cx, char *bytes, size_t length, unsigned flags);

extern JS_PUBLIC_API(JSObject *)
JS_NewUCRegExpObjectNoStatics(JSContext *cx, jschar *chars, size_t length, unsigned flags);

extern JS_PUBLIC_API(bool)
JS_ExecuteRegExpNoStatics(JSContext *cx, JS::HandleObject reobj, jschar *chars, size_t length,
                          size_t *indexp, bool test, JS::MutableHandleValue rval);

extern JS_PUBLIC_API(bool)
JS_ObjectIsRegExp(JSContext *cx, JS::HandleObject obj);

extern JS_PUBLIC_API(unsigned)
JS_GetRegExpFlags(JSContext *cx, JS::HandleObject obj);

extern JS_PUBLIC_API(JSString *)
JS_GetRegExpSource(JSContext *cx, JS::HandleObject obj);

/************************************************************************/

extern JS_PUBLIC_API(bool)
JS_IsExceptionPending(JSContext *cx);

extern JS_PUBLIC_API(bool)
JS_GetPendingException(JSContext *cx, JS::MutableHandleValue vp);

extern JS_PUBLIC_API(void)
JS_SetPendingException(JSContext *cx, JS::HandleValue v);

extern JS_PUBLIC_API(void)
JS_ClearPendingException(JSContext *cx);

extern JS_PUBLIC_API(bool)
JS_ReportPendingException(JSContext *cx);

/*
 * Save the current exception state.  This takes a snapshot of cx's current
 * exception state without making any change to that state.
 *
 * The returned state pointer MUST be passed later to JS_RestoreExceptionState
 * (to restore that saved state, overriding any more recent state) or else to
 * JS_DropExceptionState (to free the state struct in case it is not correct
 * or desirable to restore it).  Both Restore and Drop free the state struct,
 * so callers must stop using the pointer returned from Save after calling the
 * Release or Drop API.
 */
extern JS_PUBLIC_API(JSExceptionState *)
JS_SaveExceptionState(JSContext *cx);

extern JS_PUBLIC_API(void)
JS_RestoreExceptionState(JSContext *cx, JSExceptionState *state);

extern JS_PUBLIC_API(void)
JS_DropExceptionState(JSContext *cx, JSExceptionState *state);

/*
 * If the given value is an exception object that originated from an error,
 * the exception will contain an error report struct, and this API will return
 * the address of that struct.  Otherwise, it returns nullptr.  The lifetime
 * of the error report struct that might be returned is the same as the
 * lifetime of the exception object.
 */
extern JS_PUBLIC_API(JSErrorReport *)
JS_ErrorFromException(JSContext *cx, JS::HandleValue v);

/*
 * Given a reported error's message and JSErrorReport struct pointer, throw
 * the corresponding exception on cx.
 */
extern JS_PUBLIC_API(bool)
JS_ThrowReportedError(JSContext *cx, const char *message,
                      JSErrorReport *reportp);

/*
 * Throws a StopIteration exception on cx.
 */
extern JS_PUBLIC_API(bool)
JS_ThrowStopIteration(JSContext *cx);

extern JS_PUBLIC_API(bool)
JS_IsStopIteration(jsval v);

extern JS_PUBLIC_API(intptr_t)
JS_GetCurrentThread();

/*
 * A JS runtime always has an "owner thread". The owner thread is set when the
 * runtime is created (to the current thread) and practically all entry points
 * into the JS engine check that a runtime (or anything contained in the
 * runtime: context, compartment, object, etc) is only touched by its owner
 * thread. Embeddings may check this invariant outside the JS engine by calling
 * JS_AbortIfWrongThread (which will abort if not on the owner thread, even for
 * non-debug builds).
 */

extern JS_PUBLIC_API(void)
JS_AbortIfWrongThread(JSRuntime *rt);

/************************************************************************/

/*
 * A constructor can request that the JS engine create a default new 'this'
 * object of the given class, using the callee to determine parentage and
 * [[Prototype]].
 */
extern JS_PUBLIC_API(JSObject *)
JS_NewObjectForConstructor(JSContext *cx, const JSClass *clasp, const jsval *vp);

/************************************************************************/

#ifdef JS_GC_ZEAL
#define JS_DEFAULT_ZEAL_FREQ 100

extern JS_PUBLIC_API(void)
JS_SetGCZeal(JSContext *cx, uint8_t zeal, uint32_t frequency);

extern JS_PUBLIC_API(void)
JS_ScheduleGC(JSContext *cx, uint32_t count);
#endif

extern JS_PUBLIC_API(void)
JS_SetParallelParsingEnabled(JSContext *cx, bool enabled);

extern JS_PUBLIC_API(void)
JS_SetParallelIonCompilationEnabled(JSContext *cx, bool enabled);

#define JIT_COMPILER_OPTIONS(Register)                             \
  Register(BASELINE_USECOUNT_TRIGGER, "baseline.usecount.trigger") \
  Register(ION_USECOUNT_TRIGGER, "ion.usecount.trigger")           \
  Register(ION_ENABLE, "ion.enable")                               \
  Register(BASELINE_ENABLE, "baseline.enable")

typedef enum JSJitCompilerOption {
#define JIT_COMPILER_DECLARE(key, str) \
    JSJITCOMPILER_ ## key,

    JIT_COMPILER_OPTIONS(JIT_COMPILER_DECLARE)
#undef JIT_COMPILER_DECLARE

    JSJITCOMPILER_NOT_AN_OPTION
} JSJitCompilerOption;

extern JS_PUBLIC_API(void)
JS_SetGlobalJitCompilerOption(JSContext *cx, JSJitCompilerOption opt, uint32_t value);

/*
 * Convert a uint32_t index into a jsid.
 */
extern JS_PUBLIC_API(bool)
JS_IndexToId(JSContext *cx, uint32_t index, JS::MutableHandleId);

/*
 * Convert chars into a jsid.
 *
 * |chars| may not be an index.
 */
extern JS_PUBLIC_API(bool)
JS_CharsToId(JSContext* cx, JS::TwoByteChars chars, JS::MutableHandleId);

/*
 *  Test if the given string is a valid ECMAScript identifier
 */
extern JS_PUBLIC_API(bool)
JS_IsIdentifier(JSContext *cx, JS::HandleString str, bool *isIdentifier);

/*
 * Return the current script and line number of the most currently running
 * frame. Returns true if a scripted frame was found, false otherwise.
 */
extern JS_PUBLIC_API(bool)
JS_DescribeScriptedCaller(JSContext *cx, JS::MutableHandleScript script, unsigned *lineno);


/*
 * Encode/Decode interpreted scripts and functions to/from memory.
 */

extern JS_PUBLIC_API(void *)
JS_EncodeScript(JSContext *cx, JS::HandleScript script, uint32_t *lengthp);

extern JS_PUBLIC_API(void *)
JS_EncodeInterpretedFunction(JSContext *cx, JS::HandleObject funobj, uint32_t *lengthp);

extern JS_PUBLIC_API(JSScript *)
JS_DecodeScript(JSContext *cx, const void *data, uint32_t length,
                JSPrincipals *principals, JSPrincipals *originPrincipals);

extern JS_PUBLIC_API(JSObject *)
JS_DecodeInterpretedFunction(JSContext *cx, const void *data, uint32_t length,
                             JSPrincipals *principals, JSPrincipals *originPrincipals);

namespace JS {

/*
 * This callback represents a request by the JS engine to open for reading the
 * existing cache entry for the given global. If a cache entry exists, the
 * callback shall return 'true' and return the size, base address and an opaque
 * file handle as outparams. If the callback returns 'true', the JS engine
 * guarantees a call to CloseAsmJSCacheEntryForReadOp, passing the same base
 * address, size and handle.
 */
typedef bool
(* OpenAsmJSCacheEntryForReadOp)(HandleObject global, size_t *size, const uint8_t **memory,
                                 intptr_t *handle);
typedef void
(* CloseAsmJSCacheEntryForReadOp)(HandleObject global, size_t size, const uint8_t *memory,
                                  intptr_t handle);

/*
 * This callback represents a request by the JS engine to open for writing a
 * cache entry of the given size for the given global. If cache entry space is
 * available, the callback shall return 'true' and return the base address and
 * an opaque file handle as outparams. If the callback returns 'true', the JS
 * engine guarantees a call to CloseAsmJSCacheEntryForWriteOp passing the same
 * base address, size and handle.
 */
typedef bool
(* OpenAsmJSCacheEntryForWriteOp)(HandleObject global, size_t size, uint8_t **memory,
                                  intptr_t *handle);
typedef void
(* CloseAsmJSCacheEntryForWriteOp)(HandleObject global, size_t size, uint8_t *memory,
                                   intptr_t handle);

// Return the buildId (represented as a sequence of characters) associated with
// the currently-executing build. If the JS engine is embedded such that a
// single cache entry can be observed by different compiled versions of the JS
// engine, it is critical that the buildId shall change for each new build of
// the JS engine.
typedef bool
(* BuildIdOp)(mozilla::Vector<char> *buildId);

struct AsmJSCacheOps
{
    OpenAsmJSCacheEntryForReadOp openEntryForRead;
    CloseAsmJSCacheEntryForReadOp closeEntryForRead;
    OpenAsmJSCacheEntryForWriteOp openEntryForWrite;
    CloseAsmJSCacheEntryForWriteOp closeEntryForWrite;
    BuildIdOp buildId;
};

extern JS_PUBLIC_API(void)
SetAsmJSCacheOps(JSRuntime *rt, const AsmJSCacheOps *callbacks);

} /* namespace JS */

#endif /* jsapi_h */
