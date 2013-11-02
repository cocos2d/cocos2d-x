/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsfriendapi_h
#define jsfriendapi_h

#include "mozilla/MemoryReporting.h"

#include "jsclass.h"
#include "jsprvtd.h"
#include "jspubtd.h"

#include "js/CallArgs.h"

/*
 * This macro checks if the stack pointer has exceeded a given limit. If
 * |tolerance| is non-zero, it returns true only if the stack pointer has
 * exceeded the limit by more than |tolerance| bytes.
 */
#if JS_STACK_GROWTH_DIRECTION > 0
# define JS_CHECK_STACK_SIZE_WITH_TOLERANCE(limit, sp, tolerance)  \
    ((uintptr_t)(sp) < (limit)+(tolerance))
#else
# define JS_CHECK_STACK_SIZE_WITH_TOLERANCE(limit, sp, tolerance)  \
    ((uintptr_t)(sp) > (limit)-(tolerance))
#endif

#define JS_CHECK_STACK_SIZE(limit, lval) JS_CHECK_STACK_SIZE_WITH_TOLERANCE(limit, lval, 0)

namespace JS {
template <class T>
class Heap;
} /* namespace JS */

extern JS_FRIEND_API(void)
JS_SetGrayGCRootsTracer(JSRuntime *rt, JSTraceDataOp traceOp, void *data);

extern JS_FRIEND_API(JSString *)
JS_GetAnonymousString(JSRuntime *rt);

extern JS_FRIEND_API(JSObject *)
JS_FindCompilationScope(JSContext *cx, JSObject *obj);

extern JS_FRIEND_API(JSFunction *)
JS_GetObjectFunction(JSObject *obj);

extern JS_FRIEND_API(JSBool)
JS_SplicePrototype(JSContext *cx, JSObject *obj, JSObject *proto);

extern JS_FRIEND_API(JSObject *)
JS_NewObjectWithUniqueType(JSContext *cx, JSClass *clasp, JSObject *proto, JSObject *parent);

extern JS_FRIEND_API(uint32_t)
JS_ObjectCountDynamicSlots(JS::HandleObject obj);

extern JS_FRIEND_API(size_t)
JS_SetProtoCalled(JSContext *cx);

extern JS_FRIEND_API(size_t)
JS_GetCustomIteratorCount(JSContext *cx);

extern JS_FRIEND_API(JSBool)
JS_NondeterministicGetWeakMapKeys(JSContext *cx, JSObject *obj, JSObject **ret);

/*
 * Determine whether the given object is backed by a DeadObjectProxy.
 *
 * Such objects hold no other objects (they have no outgoing reference edges)
 * and will throw if you touch them (e.g. by reading/writing a property).
 */
extern JS_FRIEND_API(JSBool)
JS_IsDeadWrapper(JSObject *obj);

/*
 * Used by the cycle collector to trace through the shape and all
 * shapes it reaches, marking all non-shape children found in the
 * process. Uses bounded stack space.
 */
extern JS_FRIEND_API(void)
JS_TraceShapeCycleCollectorChildren(JSTracer *trc, void *shape);

enum {
    JS_TELEMETRY_GC_REASON,
    JS_TELEMETRY_GC_IS_COMPARTMENTAL,
    JS_TELEMETRY_GC_MS,
    JS_TELEMETRY_GC_MAX_PAUSE_MS,
    JS_TELEMETRY_GC_MARK_MS,
    JS_TELEMETRY_GC_SWEEP_MS,
    JS_TELEMETRY_GC_MARK_ROOTS_MS,
    JS_TELEMETRY_GC_MARK_GRAY_MS,
    JS_TELEMETRY_GC_SLICE_MS,
    JS_TELEMETRY_GC_MMU_50,
    JS_TELEMETRY_GC_RESET,
    JS_TELEMETRY_GC_INCREMENTAL_DISABLED,
    JS_TELEMETRY_GC_NON_INCREMENTAL,
    JS_TELEMETRY_GC_SCC_SWEEP_TOTAL_MS,
    JS_TELEMETRY_GC_SCC_SWEEP_MAX_PAUSE_MS
};

typedef void
(* JSAccumulateTelemetryDataCallback)(int id, uint32_t sample);

extern JS_FRIEND_API(void)
JS_SetAccumulateTelemetryCallback(JSRuntime *rt, JSAccumulateTelemetryDataCallback callback);

extern JS_FRIEND_API(JSPrincipals *)
JS_GetCompartmentPrincipals(JSCompartment *compartment);

extern JS_FRIEND_API(void)
JS_SetCompartmentPrincipals(JSCompartment *compartment, JSPrincipals *principals);

/* Safe to call with input obj == NULL. Returns non-NULL iff obj != NULL. */
extern JS_FRIEND_API(JSObject *)
JS_ObjectToInnerObject(JSContext *cx, JSObject *obj);

/* Requires obj != NULL. */
extern JS_FRIEND_API(JSObject *)
JS_ObjectToOuterObject(JSContext *cx, JSObject *obj);

extern JS_FRIEND_API(JSObject *)
JS_CloneObject(JSContext *cx, JSObject *obj, JSObject *proto, JSObject *parent);

extern JS_FRIEND_API(JSString *)
JS_BasicObjectToString(JSContext *cx, JS::HandleObject obj);

extern JS_FRIEND_API(JSBool)
js_GetterOnlyPropertyStub(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JSBool strict,
                          JS::MutableHandleValue vp);

JS_FRIEND_API(void)
js_ReportOverRecursed(JSContext *maybecx);

JS_FRIEND_API(bool)
js_ObjectClassIs(JSContext *cx, JS::HandleObject obj, js::ESClassValue classValue);

JS_FRIEND_API(const char *)
js_ObjectClassName(JSContext *cx, JS::HandleObject obj);

JS_FRIEND_API(bool)
js_AddObjectRoot(JSRuntime *rt, JSObject **objp);

JS_FRIEND_API(void)
js_RemoveObjectRoot(JSRuntime *rt, JSObject **objp);

#ifdef DEBUG

/*
 * Routines to print out values during debugging.  These are FRIEND_API to help
 * the debugger find them and to support temporarily hacking js_Dump* calls
 * into other code.
 */

extern JS_FRIEND_API(void)
js_DumpString(JSString *str);

extern JS_FRIEND_API(void)
js_DumpAtom(JSAtom *atom);

extern JS_FRIEND_API(void)
js_DumpObject(JSObject *obj);

extern JS_FRIEND_API(void)
js_DumpChars(const jschar *s, size_t n);
#endif

extern JS_FRIEND_API(bool)
JS_CopyPropertiesFrom(JSContext *cx, JSObject *target, JSObject *obj);

extern JS_FRIEND_API(JSBool)
JS_WrapPropertyDescriptor(JSContext *cx, js::PropertyDescriptor *desc);

extern JS_FRIEND_API(JSBool)
JS_WrapAutoIdVector(JSContext *cx, JS::AutoIdVector &props);

extern JS_FRIEND_API(JSBool)
JS_EnumerateState(JSContext *cx, JS::HandleObject obj, JSIterateOp enum_op,
                  js::MutableHandleValue statep, js::MutableHandleId idp);

struct JSFunctionSpecWithHelp {
    const char      *name;
    JSNative        call;
    uint16_t        nargs;
    uint16_t        flags;
    const char      *usage;
    const char      *help;
};

#define JS_FN_HELP(name,call,nargs,flags,usage,help)                          \
    {name, call, nargs, (flags) | JSPROP_ENUMERATE | JSFUN_STUB_GSOPS, usage, help}
#define JS_FS_HELP_END                                                        \
    {NULL, NULL, 0, 0, NULL, NULL}

extern JS_FRIEND_API(bool)
JS_DefineFunctionsWithHelp(JSContext *cx, JSObject *obj, const JSFunctionSpecWithHelp *fs);

typedef bool (* JS_SourceHook)(JSContext *cx, JS::Handle<JSScript*> script,
                               jschar **src, uint32_t *length);

extern JS_FRIEND_API(void)
JS_SetSourceHook(JSRuntime *rt, JS_SourceHook hook);

namespace js {

inline JSRuntime *
GetRuntime(const JSContext *cx)
{
    return ContextFriendFields::get(cx)->runtime_;
}

inline JSCompartment *
GetContextCompartment(const JSContext *cx)
{
    return ContextFriendFields::get(cx)->compartment_;
}

inline JS::Zone *
GetContextZone(const JSContext *cx)
{
    return ContextFriendFields::get(cx)->zone_;
}

extern JS_FRIEND_API(JS::Zone *)
GetCompartmentZone(JSCompartment *comp);

typedef bool
(* PreserveWrapperCallback)(JSContext *cx, JSObject *obj);

 /*
  * Dump the complete object graph of heap-allocated things.
  * fp is the file for the dump output.
  */
extern JS_FRIEND_API(void)
DumpHeapComplete(JSRuntime *rt, FILE *fp);

#ifdef OLD_GETTER_SETTER_METHODS
JS_FRIEND_API(JSBool) obj_defineGetter(JSContext *cx, unsigned argc, js::Value *vp);
JS_FRIEND_API(JSBool) obj_defineSetter(JSContext *cx, unsigned argc, js::Value *vp);
#endif

extern JS_FRIEND_API(bool)
IsSystemCompartment(JSCompartment *comp);

extern JS_FRIEND_API(bool)
IsSystemZone(JS::Zone *zone);

extern JS_FRIEND_API(bool)
IsAtomsCompartment(JSCompartment *comp);

/*
 * Check whether it is OK to assign an undeclared variable with the name
 * |propname| at the current location in script.  It is not an error if there is
 * no current script location, or if that location is not an assignment to an
 * undeclared variable.  Reports an error if one needs to be reported (and,
 * particularly, always reports when it returns false).
 */
extern JS_FRIEND_API(bool)
ReportIfUndeclaredVarAssignment(JSContext *cx, HandleString propname);

/*
 * Returns whether we're in a non-strict property set (in that we're in a
 * non-strict script and the bytecode we're on is a property set).  The return
 * value does NOT indicate any sort of exception was thrown: it's just a
 * boolean.
 */
extern JS_FRIEND_API(bool)
IsInNonStrictPropertySet(JSContext *cx);

struct WeakMapTracer;

/*
 * Weak map tracer callback, called once for every binding of every
 * weak map that was live at the time of the last garbage collection.
 *
 * m will be NULL if the weak map is not contained in a JS Object.
 */
typedef void
(* WeakMapTraceCallback)(WeakMapTracer *trc, JSObject *m,
                         void *k, JSGCTraceKind kkind,
                         void *v, JSGCTraceKind vkind);

struct WeakMapTracer {
    JSRuntime            *runtime;
    WeakMapTraceCallback callback;

    WeakMapTracer(JSRuntime *rt, WeakMapTraceCallback cb)
        : runtime(rt), callback(cb) {}
};

extern JS_FRIEND_API(void)
TraceWeakMaps(WeakMapTracer *trc);

extern JS_FRIEND_API(bool)
AreGCGrayBitsValid(JSRuntime *rt);

typedef void
(*GCThingCallback)(void *closure, void *gcthing);

extern JS_FRIEND_API(void)
VisitGrayWrapperTargets(JS::Zone *zone, GCThingCallback callback, void *closure);

extern JS_FRIEND_API(JSObject *)
GetWeakmapKeyDelegate(JSObject *key);

JS_FRIEND_API(JSGCTraceKind)
GCThingTraceKind(void *thing);

/*
 * Invoke cellCallback on every gray JS_OBJECT in the given zone.
 */
extern JS_FRIEND_API(void)
IterateGrayObjects(JS::Zone *zone, GCThingCallback cellCallback, void *data);

#ifdef JS_HAS_CTYPES
extern JS_FRIEND_API(size_t)
SizeOfDataIfCDataObject(mozilla::MallocSizeOf mallocSizeOf, JSObject *obj);
#endif

extern JS_FRIEND_API(JSCompartment *)
GetAnyCompartmentInZone(JS::Zone *zone);

/*
 * Shadow declarations of JS internal structures, for access by inline access
 * functions below. Do not use these structures in any other way. When adding
 * new fields for access by inline methods, make sure to add static asserts to
 * the original header file to ensure that offsets are consistent.
 */
namespace shadow {

struct TypeObject {
    Class       *clasp;
    JSObject    *proto;
};

struct BaseShape {
    js::Class *clasp;
    JSObject *parent;
    JSObject *_1;
    JSCompartment *compartment;
};

class Shape {
public:
    shadow::BaseShape *base;
    jsid              _1;
    uint32_t          slotInfo;

    static const uint32_t FIXED_SLOTS_SHIFT = 27;
};

struct Object {
    shadow::Shape      *shape;
    shadow::TypeObject *type;
    js::Value          *slots;
    js::Value          *_1;

    size_t numFixedSlots() const { return shape->slotInfo >> Shape::FIXED_SLOTS_SHIFT; }
    Value *fixedSlots() const {
        return (Value *)(uintptr_t(this) + sizeof(shadow::Object));
    }

    js::Value &slotRef(size_t slot) const {
        size_t nfixed = numFixedSlots();
        if (slot < nfixed)
            return fixedSlots()[slot];
        return slots[slot - nfixed];
    }
};

struct Function {
    Object base;
    uint16_t nargs;
    uint16_t flags;
    /* Used only for natives */
    Native native;
    const JSJitInfo *jitinfo;
    void *_1;
};

struct Atom {
    static const size_t LENGTH_SHIFT = 4;
    size_t lengthAndFlags;
    const jschar *chars;
};

} /* namespace shadow */

// These are equal to |&{Function,Object,OuterWindow}ProxyObject::class_|.  Use
// them in places where you don't want to #include vm/ProxyObject.h.
extern JS_FRIEND_DATA(js::Class* const) FunctionProxyClassPtr;
extern JS_FRIEND_DATA(js::Class* const) ObjectProxyClassPtr;
extern JS_FRIEND_DATA(js::Class* const) OuterWindowProxyClassPtr;

// This is equal to |&JSObject::class_|.  Use it in places where you don't want
// to #include jsobj.h.
extern JS_FRIEND_DATA(js::Class* const) ObjectClassPtr;

inline js::Class *
GetObjectClass(JSObject *obj)
{
    return reinterpret_cast<const shadow::Object*>(obj)->type->clasp;
}

inline JSClass *
GetObjectJSClass(JSObject *obj)
{
    return js::Jsvalify(GetObjectClass(obj));
}

inline bool
IsInnerObject(JSObject *obj) {
    return !!GetObjectClass(obj)->ext.outerObject;
}

inline bool
IsOuterObject(JSObject *obj) {
    return !!GetObjectClass(obj)->ext.innerObject;
}

JS_FRIEND_API(bool)
IsFunctionObject(JSObject *obj);

JS_FRIEND_API(bool)
IsScopeObject(JSObject *obj);

JS_FRIEND_API(bool)
IsCallObject(JSObject *obj);

inline JSObject *
GetObjectParent(JSObject *obj)
{
    JS_ASSERT(!IsScopeObject(obj));
    return reinterpret_cast<shadow::Object*>(obj)->shape->base->parent;
}

static JS_ALWAYS_INLINE JSCompartment *
GetObjectCompartment(JSObject *obj)
{
    return reinterpret_cast<shadow::Object*>(obj)->shape->base->compartment;
}

JS_FRIEND_API(JSObject *)
GetObjectParentMaybeScope(JSObject *obj);

JS_FRIEND_API(JSObject *)
GetGlobalForObjectCrossCompartment(JSObject *obj);

// For legacy consumers only. This whole concept is going away soon.
JS_FRIEND_API(JSObject *)
DefaultObjectForContextOrNull(JSContext *cx);

JS_FRIEND_API(void)
SetDefaultObjectForContext(JSContext *cx, JSObject *obj);

JS_FRIEND_API(void)
NotifyAnimationActivity(JSObject *obj);

JS_FRIEND_API(bool)
IsOriginalScriptFunction(JSFunction *fun);

/*
 * Return the outermost enclosing function (script) of the scripted caller.
 * This function returns NULL in several cases:
 *  - no script is running on the context
 *  - the caller is in global or eval code
 * In particular, this function will "stop" its outermost search at eval() and
 * thus it will really return the outermost enclosing function *since the
 * innermost eval*.
 */
JS_FRIEND_API(JSScript *)
GetOutermostEnclosingFunctionOfScriptedCaller(JSContext *cx);

JS_FRIEND_API(JSFunction *)
DefineFunctionWithReserved(JSContext *cx, JSObject *obj, const char *name, JSNative call,
                           unsigned nargs, unsigned attrs);

JS_FRIEND_API(JSFunction *)
NewFunctionWithReserved(JSContext *cx, JSNative call, unsigned nargs, unsigned flags,
                        JSObject *parent, const char *name);

JS_FRIEND_API(JSFunction *)
NewFunctionByIdWithReserved(JSContext *cx, JSNative native, unsigned nargs, unsigned flags,
                            JSObject *parent, jsid id);

JS_FRIEND_API(JSObject *)
InitClassWithReserved(JSContext *cx, JSObject *obj, JSObject *parent_proto,
                      JSClass *clasp, JSNative constructor, unsigned nargs,
                      const JSPropertySpec *ps, const JSFunctionSpec *fs,
                      const JSPropertySpec *static_ps, const JSFunctionSpec *static_fs);

JS_FRIEND_API(const Value &)
GetFunctionNativeReserved(JSObject *fun, size_t which);

JS_FRIEND_API(void)
SetFunctionNativeReserved(JSObject *fun, size_t which, const Value &val);

inline bool
GetObjectProto(JSContext *cx, JS::Handle<JSObject*> obj, JS::MutableHandle<JSObject*> proto)
{
    js::Class *clasp = GetObjectClass(obj);
    if (clasp == js::ObjectProxyClassPtr ||
        clasp == js::OuterWindowProxyClassPtr ||
        clasp == js::FunctionProxyClassPtr)
    {
        return JS_GetPrototype(cx, obj, proto);
    }

    proto.set(reinterpret_cast<const shadow::Object*>(obj.get())->type->proto);
    return true;
}

inline void *
GetObjectPrivate(JSObject *obj)
{
    const shadow::Object *nobj = reinterpret_cast<const shadow::Object*>(obj);
    void **addr = reinterpret_cast<void**>(&nobj->fixedSlots()[nobj->numFixedSlots()]);
    return *addr;
}

/*
 * Get a slot that is both reserved for object's clasp *and* is fixed (fits
 * within the maximum capacity for the object's fixed slots).
 */
inline const Value &
GetReservedSlot(JSObject *obj, size_t slot)
{
    JS_ASSERT(slot < JSCLASS_RESERVED_SLOTS(GetObjectClass(obj)));
    return reinterpret_cast<const shadow::Object *>(obj)->slotRef(slot);
}

JS_FRIEND_API(void)
SetReservedSlotWithBarrier(JSObject *obj, size_t slot, const Value &value);

inline void
SetReservedSlot(JSObject *obj, size_t slot, const Value &value)
{
    JS_ASSERT(slot < JSCLASS_RESERVED_SLOTS(GetObjectClass(obj)));
    shadow::Object *sobj = reinterpret_cast<shadow::Object *>(obj);
    if (sobj->slotRef(slot).isMarkable()
#ifdef JSGC_GENERATIONAL
        || value.isMarkable()
#endif
       )
    {
        SetReservedSlotWithBarrier(obj, slot, value);
    } else {
        sobj->slotRef(slot) = value;
    }
}

JS_FRIEND_API(uint32_t)
GetObjectSlotSpan(JSObject *obj);

inline const Value &
GetObjectSlot(JSObject *obj, size_t slot)
{
    JS_ASSERT(slot < GetObjectSlotSpan(obj));
    return reinterpret_cast<const shadow::Object *>(obj)->slotRef(slot);
}

inline const jschar *
GetAtomChars(JSAtom *atom)
{
    return reinterpret_cast<shadow::Atom *>(atom)->chars;
}

inline size_t
GetAtomLength(JSAtom *atom)
{
    using shadow::Atom;
    return reinterpret_cast<Atom*>(atom)->lengthAndFlags >> Atom::LENGTH_SHIFT;
}

inline JSLinearString *
AtomToLinearString(JSAtom *atom)
{
    return reinterpret_cast<JSLinearString *>(atom);
}

static inline js::PropertyOp
CastAsJSPropertyOp(JSObject *object)
{
    return JS_DATA_TO_FUNC_PTR(js::PropertyOp, object);
}

static inline js::StrictPropertyOp
CastAsJSStrictPropertyOp(JSObject *object)
{
    return JS_DATA_TO_FUNC_PTR(js::StrictPropertyOp, object);
}

JS_FRIEND_API(bool)
GetPropertyNames(JSContext *cx, JSObject *obj, unsigned flags, js::AutoIdVector *props);

JS_FRIEND_API(bool)
AppendUnique(JSContext *cx, AutoIdVector &base, AutoIdVector &others);

JS_FRIEND_API(bool)
GetGeneric(JSContext *cx, JSObject *obj, JSObject *receiver, jsid id, Value *vp);

JS_FRIEND_API(bool)
StringIsArrayIndex(JSLinearString *str, uint32_t *indexp);

JS_FRIEND_API(void)
SetPreserveWrapperCallback(JSRuntime *rt, PreserveWrapperCallback callback);

JS_FRIEND_API(bool)
IsObjectInContextCompartment(JSObject *obj, const JSContext *cx);

/*
 * NB: these flag bits are encoded into the bytecode stream in the immediate
 * operand of JSOP_ITER, so don't change them without advancing vm/Xdr.h's
 * XDR_BYTECODE_VERSION.
 */
#define JSITER_ENUMERATE  0x1   /* for-in compatible hidden default iterator */
#define JSITER_FOREACH    0x2   /* return [key, value] pair rather than key */
#define JSITER_KEYVALUE   0x4   /* destructuring for-in wants [key, value] */
#define JSITER_OWNONLY    0x8   /* iterate over obj's own properties only */
#define JSITER_HIDDEN     0x10  /* also enumerate non-enumerable properties */
#define JSITER_FOR_OF     0x20  /* harmony for-of loop */

inline uintptr_t
GetNativeStackLimit(const JSRuntime *rt)
{
    return PerThreadDataFriendFields::getMainThread(rt)->nativeStackLimit;
}

inline uintptr_t
GetNativeStackLimit(JSContext *cx)
{
    return GetNativeStackLimit(GetRuntime(cx));
}

/*
 * These macros report a stack overflow and run |onerror| if we are close to
 * using up the C stack. The JS_CHECK_CHROME_RECURSION variant gives us a little
 * extra space so that we can ensure that crucial code is able to run.
 */

#define JS_CHECK_RECURSION(cx, onerror)                              \
    JS_BEGIN_MACRO                                                              \
        int stackDummy_;                                                        \
        if (!JS_CHECK_STACK_SIZE(js::GetNativeStackLimit(cx), &stackDummy_)) {  \
            js_ReportOverRecursed(cx);                                          \
            onerror;                                                            \
        }                                                                       \
    JS_END_MACRO

#define JS_CHECK_RECURSION_WITH_SP_DONT_REPORT(cx, sp, onerror)                 \
    JS_BEGIN_MACRO                                                              \
        if (!JS_CHECK_STACK_SIZE(js::GetNativeStackLimit(cx), sp)) {            \
            onerror;                                                            \
        }                                                                       \
    JS_END_MACRO

#define JS_CHECK_CHROME_RECURSION(cx, onerror)                                  \
    JS_BEGIN_MACRO                                                              \
        int stackDummy_;                                                        \
        if (!JS_CHECK_STACK_SIZE_WITH_TOLERANCE(js::GetNativeStackLimit(cx),    \
                                                &stackDummy_,                   \
                                                1024 * sizeof(size_t)))         \
        {                                                                       \
            js_ReportOverRecursed(cx);                                          \
            onerror;                                                            \
        }                                                                       \
    JS_END_MACRO

JS_FRIEND_API(void)
StartPCCountProfiling(JSContext *cx);

JS_FRIEND_API(void)
StopPCCountProfiling(JSContext *cx);

JS_FRIEND_API(void)
PurgePCCounts(JSContext *cx);

JS_FRIEND_API(size_t)
GetPCCountScriptCount(JSContext *cx);

JS_FRIEND_API(JSString *)
GetPCCountScriptSummary(JSContext *cx, size_t script);

JS_FRIEND_API(JSString *)
GetPCCountScriptContents(JSContext *cx, size_t script);

/*
 * A call stack can be specified to the JS engine such that all JS entry/exits
 * to functions push/pop an entry to/from the specified stack.
 *
 * For more detailed information, see vm/SPSProfiler.h
 */
class ProfileEntry
{
    /*
     * All fields are marked volatile to prevent the compiler from re-ordering
     * instructions. Namely this sequence:
     *
     *    entry[size] = ...;
     *    size++;
     *
     * If the size modification were somehow reordered before the stores, then
     * if a sample were taken it would be examining bogus information.
     *
     * A ProfileEntry represents both a C++ profile entry and a JS one. Both use
     * the string as a description, but JS uses the sp as NULL to indicate that
     * it is a JS entry. The script_ is then only ever examined for a JS entry,
     * and the idx is used by both, but with different meanings.
     */
    const char * volatile string; // Descriptive string of this entry
    void * volatile sp;           // Relevant stack pointer for the entry
    JSScript * volatile script_;  // if js(), non-null script which is running
    int32_t volatile idx;         // if js(), idx of pc, otherwise line number

  public:
    /*
     * All of these methods are marked with the 'volatile' keyword because SPS's
     * representation of the stack is stored such that all ProfileEntry
     * instances are volatile. These methods would not be available unless they
     * were marked as volatile as well
     */

    bool js() volatile {
        JS_ASSERT_IF(sp == NULL, script_ != NULL);
        return sp == NULL;
    }

    uint32_t line() volatile { JS_ASSERT(!js()); return idx; }
    JSScript *script() volatile { JS_ASSERT(js()); return script_; }
    void *stackAddress() volatile { return sp; }
    const char *label() volatile { return string; }

    void setLine(uint32_t aLine) volatile { JS_ASSERT(!js()); idx = aLine; }
    void setLabel(const char *aString) volatile { string = aString; }
    void setStackAddress(void *aSp) volatile { sp = aSp; }
    void setScript(JSScript *aScript) volatile { script_ = aScript; }

    /* we can't know the layout of JSScript, so look in vm/SPSProfiler.cpp */
    JS_FRIEND_API(jsbytecode *) pc() volatile;
    JS_FRIEND_API(void) setPC(jsbytecode *pc) volatile;

    static size_t offsetOfString() { return offsetof(ProfileEntry, string); }
    static size_t offsetOfStackAddress() { return offsetof(ProfileEntry, sp); }
    static size_t offsetOfPCIdx() { return offsetof(ProfileEntry, idx); }
    static size_t offsetOfScript() { return offsetof(ProfileEntry, script_); }

    /*
     * The index used in the entry can either be a line number or the offset of
     * a pc into a script's code. To signify a NULL pc, use a -1 index. This is
     * checked against in pc() and setPC() to set/get the right pc.
     */
    static const int32_t NullPCIndex = -1;
};

JS_FRIEND_API(void)
SetRuntimeProfilingStack(JSRuntime *rt, ProfileEntry *stack, uint32_t *size,
                         uint32_t max);

JS_FRIEND_API(void)
EnableRuntimeProfilingStack(JSRuntime *rt, bool enabled);

JS_FRIEND_API(jsbytecode*)
ProfilingGetPC(JSRuntime *rt, JSScript *script, void *ip);

#ifdef JS_THREADSAFE
JS_FRIEND_API(bool)
ContextHasOutstandingRequests(const JSContext *cx);
#endif

JS_FRIEND_API(bool)
HasUnrootedGlobal(const JSContext *cx);

typedef void
(* ActivityCallback)(void *arg, JSBool active);

/*
 * Sets a callback that is run whenever the runtime goes idle - the
 * last active request ceases - and begins activity - when it was
 * idle and a request begins.
 */
JS_FRIEND_API(void)
SetActivityCallback(JSRuntime *rt, ActivityCallback cb, void *arg);

extern JS_FRIEND_API(const JSStructuredCloneCallbacks *)
GetContextStructuredCloneCallbacks(JSContext *cx);

extern JS_FRIEND_API(bool)
CanCallContextDebugHandler(JSContext *cx);

extern JS_FRIEND_API(JSTrapStatus)
CallContextDebugHandler(JSContext *cx, JSScript *script, jsbytecode *bc, Value *rval);

extern JS_FRIEND_API(bool)
IsContextRunningJS(JSContext *cx);

typedef void
(* AnalysisPurgeCallback)(JSRuntime *rt, JS::Handle<JSFlatString*> desc);

extern JS_FRIEND_API(AnalysisPurgeCallback)
SetAnalysisPurgeCallback(JSRuntime *rt, AnalysisPurgeCallback callback);

typedef JSBool
(* DOMInstanceClassMatchesProto)(JS::HandleObject protoObject, uint32_t protoID,
                                 uint32_t depth);
struct JSDOMCallbacks {
    DOMInstanceClassMatchesProto instanceClassMatchesProto;
};
typedef struct JSDOMCallbacks DOMCallbacks;

extern JS_FRIEND_API(void)
SetDOMCallbacks(JSRuntime *rt, const DOMCallbacks *callbacks);

extern JS_FRIEND_API(const DOMCallbacks *)
GetDOMCallbacks(JSRuntime *rt);

extern JS_FRIEND_API(JSObject *)
GetTestingFunctions(JSContext *cx);

/*
 * Helper to convert FreeOp to JSFreeOp when the definition of FreeOp is not
 * available and the compiler does not know that FreeOp inherits from
 * JSFreeOp.
 */
inline JSFreeOp *
CastToJSFreeOp(FreeOp *fop)
{
    return reinterpret_cast<JSFreeOp *>(fop);
}

/* Implemented in jsexn.cpp. */

/*
 * Get an error type name from a JSExnType constant.
 * Returns NULL for invalid arguments and JSEXN_INTERNALERR
 */
extern JS_FRIEND_API(const jschar*)
GetErrorTypeName(JSContext* cx, int16_t exnType);

#ifdef DEBUG
extern JS_FRIEND_API(unsigned)
GetEnterCompartmentDepth(JSContext* cx);
#endif

/* Implemented in jswrapper.cpp. */
typedef enum NukeReferencesToWindow {
    NukeWindowReferences,
    DontNukeWindowReferences
} NukeReferencesToWindow;

/*
 * These filters are designed to be ephemeral stack classes, and thus don't
 * do any rooting or holding of their members.
 */
struct CompartmentFilter {
    virtual bool match(JSCompartment *c) const = 0;
};

struct AllCompartments : public CompartmentFilter {
    virtual bool match(JSCompartment *c) const { return true; }
};

struct ContentCompartmentsOnly : public CompartmentFilter {
    virtual bool match(JSCompartment *c) const {
        return !IsSystemCompartment(c);
    }
};

struct ChromeCompartmentsOnly : public CompartmentFilter {
    virtual bool match(JSCompartment *c) const {
        return IsSystemCompartment(c);
    }
};

struct SingleCompartment : public CompartmentFilter {
    JSCompartment *ours;
    SingleCompartment(JSCompartment *c) : ours(c) {}
    virtual bool match(JSCompartment *c) const { return c == ours; }
};

struct CompartmentsWithPrincipals : public CompartmentFilter {
    JSPrincipals *principals;
    CompartmentsWithPrincipals(JSPrincipals *p) : principals(p) {}
    virtual bool match(JSCompartment *c) const {
        return JS_GetCompartmentPrincipals(c) == principals;
    }
};

extern JS_FRIEND_API(JSBool)
NukeCrossCompartmentWrappers(JSContext* cx,
                             const CompartmentFilter& sourceFilter,
                             const CompartmentFilter& targetFilter,
                             NukeReferencesToWindow nukeReferencesToWindow);

/* Specify information about DOMProxy proxies in the DOM, for use by ICs. */

/*
 * The DOMProxyShadowsCheck function will be called to check if the property for
 * id should be gotten from the prototype, or if there is an own property that
 * shadows it.
 * If DoesntShadow is returned then the slot at listBaseExpandoSlot should
 * either be undefined or point to an expando object that would contain the own
 * property.
 * If DoesntShadowUnique is returned then the slot at listBaseExpandoSlot should
 * contain a private pointer to a ExpandoAndGeneration, which contains a
 * JS::Value that should either be undefined or point to an expando object, and
 * a uint32 value. If that value changes then the IC for getting a property will
 * be invalidated.
 */

struct ExpandoAndGeneration {
  ExpandoAndGeneration()
    : expando(UndefinedValue()),
      generation(0)
  {}

  void Unlink()
  {
      ++generation;
      expando.setUndefined();
  }

  JS::Heap<JS::Value> expando;
  uint32_t generation;
};

typedef enum DOMProxyShadowsResult {
  ShadowCheckFailed,
  Shadows,
  DoesntShadow,
  DoesntShadowUnique
} DOMProxyShadowsResult;
typedef DOMProxyShadowsResult
(* DOMProxyShadowsCheck)(JSContext* cx, JS::HandleObject object, JS::HandleId id);
JS_FRIEND_API(void)
SetDOMProxyInformation(void *domProxyHandlerFamily, uint32_t domProxyExpandoSlot,
                       DOMProxyShadowsCheck domProxyShadowsCheck);

void *GetDOMProxyHandlerFamily();
uint32_t GetDOMProxyExpandoSlot();
DOMProxyShadowsCheck GetDOMProxyShadowsCheck();

} /* namespace js */

/* Implemented in jsdate.cpp. */

/*
 * Detect whether the internal date value is NaN.  (Because failure is
 * out-of-band for js_DateGet*)
 */
extern JS_FRIEND_API(JSBool)
js_DateIsValid(JSObject* obj);

extern JS_FRIEND_API(double)
js_DateGetMsecSinceEpoch(JSObject *obj);

/* Implemented in jscntxt.cpp. */

/*
 * Report an exception, which is currently realized as a printf-style format
 * string and its arguments.
 */
typedef enum JSErrNum {
#define MSG_DEF(name, number, count, exception, format) \
    name = number,
#include "js.msg"
#undef MSG_DEF
    JSErr_Limit
} JSErrNum;

extern JS_FRIEND_API(const JSErrorFormatString *)
js_GetErrorMessage(void *userRef, const char *locale, const unsigned errorNumber);

/* Implemented in jsclone.cpp. */

extern JS_FRIEND_API(uint64_t)
js_GetSCOffset(JSStructuredCloneWriter* writer);

/* Typed Array functions, implemented in jstypedarray.cpp */

namespace js {
namespace ArrayBufferView {

enum ViewType {
    TYPE_INT8 = 0,
    TYPE_UINT8,
    TYPE_INT16,
    TYPE_UINT16,
    TYPE_INT32,
    TYPE_UINT32,
    TYPE_FLOAT32,
    TYPE_FLOAT64,

    /*
     * Special type that is a uint8_t, but assignments are clamped to [0, 256).
     * Treat the raw data type as a uint8_t.
     */
    TYPE_UINT8_CLAMPED,

    /*
     * Type returned for a DataView. Note that there is no single element type
     * in this case.
     */
    TYPE_DATAVIEW,

    TYPE_MAX
};

} /* namespace ArrayBufferView */

/*
 * A helper for building up an ArrayBuffer object's data
 * before creating the ArrayBuffer itself.  Will do doubling
 * based reallocation, up to an optional maximum growth given.
 *
 * When all the data has been appended, call getArrayBuffer,
 * passing in the JSContext* for which the ArrayBuffer object
 * is to be created.  This also implicitly resets the builder,
 * or it can be reset explicitly at any point by calling reset().
 */
class ArrayBufferBuilder
{
    void *rawcontents_;
    uint8_t *dataptr_;
    uint32_t capacity_;
    uint32_t length_;
  public:
    ArrayBufferBuilder()
        : rawcontents_(NULL),
          dataptr_(NULL),
          capacity_(0),
          length_(0)
    {
    }

    ~ArrayBufferBuilder() {
        reset();
    }

    void reset() {
        if (rawcontents_)
            JS_free(NULL, rawcontents_);
        rawcontents_ = dataptr_ = NULL;
        capacity_ = length_ = 0;
    }

    // will truncate if newcap is < length()
    bool setCapacity(uint32_t newcap) {
        if (!JS_ReallocateArrayBufferContents(NULL, newcap, &rawcontents_, &dataptr_))
            return false;

        capacity_ = newcap;
        if (length_ > newcap)
            length_ = newcap;

        return true;
    }

    // Append datalen bytes from data to the current buffer.  If we
    // need to grow the buffer, grow by doubling the size up to a
    // maximum of maxgrowth (if given).  If datalen is greater than
    // what the new capacity would end up as, then grow by datalen.
    //
    // The data parameter must not overlap with anything beyond the
    // builder's current valid contents [0..length)
    bool append(const uint8_t *newdata, uint32_t datalen, uint32_t maxgrowth = 0) {
        if (length_ + datalen > capacity_) {
            uint32_t newcap;
            // double while under maxgrowth or if not specified
            if (!maxgrowth || capacity_ < maxgrowth)
                newcap = capacity_ * 2;
            else
                newcap = capacity_ + maxgrowth;

            // but make sure there's always enough to satisfy our request
            if (newcap < length_ + datalen)
                newcap = length_ + datalen;

            // did we overflow?
            if (newcap < capacity_)
                return false;

            if (!setCapacity(newcap))
                return false;
        }

        // assert that the region isn't overlapping so we can memcpy;
        JS_ASSERT(!areOverlappingRegions(newdata, datalen, dataptr_ + length_, datalen));

        memcpy(dataptr_ + length_, newdata, datalen);
        length_ += datalen;

        return true;
    }

    uint8_t *data() {
        return dataptr_;
    }

    uint32_t length() {
        return length_;
    }

    uint32_t capacity() {
        return capacity_;
    }

    JSObject* getArrayBuffer(JSContext *cx) {
        // we need to check for length_ == 0, because nothing may have been
        // added
        if (capacity_ > length_ || length_ == 0) {
            if (!setCapacity(length_))
                return NULL;
        }

        JSObject* obj = JS_NewArrayBufferWithContents(cx, rawcontents_);
        if (!obj)
            return NULL;

        rawcontents_ = dataptr_ = NULL;
        length_ = capacity_ = 0;

        return obj;
    }

protected:

    static bool areOverlappingRegions(const uint8_t *start1, uint32_t length1,
                                      const uint8_t *start2, uint32_t length2)
    {
        const uint8_t *end1 = start1 + length1;
        const uint8_t *end2 = start2 + length2;

        const uint8_t *max_start = start1 > start2 ? start1 : start2;
        const uint8_t *min_end   = end1 < end2 ? end1 : end2;

        return max_start < min_end;
    }
};

} /* namespace js */

typedef js::ArrayBufferView::ViewType JSArrayBufferViewType;

/*
 * Create a new typed array with nelements elements.
 *
 * These functions (except the WithBuffer variants) fill in the array with zeros.
 */

extern JS_FRIEND_API(JSObject *)
JS_NewInt8Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewUint8Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewUint8ClampedArray(JSContext *cx, uint32_t nelements);

extern JS_FRIEND_API(JSObject *)
JS_NewInt16Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewUint16Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewInt32Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewUint32Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewFloat32Array(JSContext *cx, uint32_t nelements);
extern JS_FRIEND_API(JSObject *)
JS_NewFloat64Array(JSContext *cx, uint32_t nelements);

/*
 * Create a new typed array and copy in values from the given object. The
 * object is used as if it were an array; that is, the new array (if
 * successfully created) will have length given by array.length, and its
 * elements will be those specified by array[0], array[1], and so on, after
 * conversion to the typed array element type.
 */

extern JS_FRIEND_API(JSObject *)
JS_NewInt8ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewUint8ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewUint8ClampedArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewInt16ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewUint16ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewInt32ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewUint32ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewFloat32ArrayFromArray(JSContext *cx, JSObject *array);
extern JS_FRIEND_API(JSObject *)
JS_NewFloat64ArrayFromArray(JSContext *cx, JSObject *array);

/*
 * Create a new typed array using the given ArrayBuffer for storage.  The
 * length value is optional; if -1 is passed, enough elements to use up the
 * remainder of the byte array is used as the default value.
 */

extern JS_FRIEND_API(JSObject *)
JS_NewInt8ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                          uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewUint8ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                           uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewUint8ClampedArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                                  uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewInt16ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                           uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewUint16ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                            uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewInt32ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                           uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewUint32ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                            uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewFloat32ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                             uint32_t byteOffset, int32_t length);
extern JS_FRIEND_API(JSObject *)
JS_NewFloat64ArrayWithBuffer(JSContext *cx, JSObject *arrayBuffer,
                             uint32_t byteOffset, int32_t length);

/*
 * Create a new ArrayBuffer with the given byte length.
 */
extern JS_FRIEND_API(JSObject *)
JS_NewArrayBuffer(JSContext *cx, uint32_t nbytes);

/*
 * Check whether obj supports JS_GetTypedArray* APIs. Note that this may return
 * false if a security wrapper is encountered that denies the unwrapping. If
 * this test or one of the JS_Is*Array tests succeeds, then it is safe to call
 * the various accessor JSAPI calls defined below.
 */
extern JS_FRIEND_API(JSBool)
JS_IsTypedArrayObject(JSObject *obj);

/*
 * Check whether obj supports JS_GetArrayBufferView* APIs. Note that this may
 * return false if a security wrapper is encountered that denies the
 * unwrapping. If this test or one of the more specific tests succeeds, then it
 * is safe to call the various ArrayBufferView accessor JSAPI calls defined
 * below.
 */
extern JS_FRIEND_API(JSBool)
JS_IsArrayBufferViewObject(JSObject *obj);

/*
 * Test for specific typed array types (ArrayBufferView subtypes)
 */

extern JS_FRIEND_API(JSBool)
JS_IsInt8Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsUint8Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsUint8ClampedArray(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsInt16Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsUint16Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsInt32Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsUint32Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsFloat32Array(JSObject *obj);
extern JS_FRIEND_API(JSBool)
JS_IsFloat64Array(JSObject *obj);

/*
 * Unwrap Typed arrays all at once. Return NULL without throwing if the object
 * cannot be viewed as the correct typed array, or the typed array object on
 * success, filling both outparameters.
 */
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsInt8Array(JSObject *obj, uint32_t *length, int8_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsUint8Array(JSObject *obj, uint32_t *length, uint8_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsUint8ClampedArray(JSObject *obj, uint32_t *length, uint8_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsInt16Array(JSObject *obj, uint32_t *length, int16_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsUint16Array(JSObject *obj, uint32_t *length, uint16_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsInt32Array(JSObject *obj, uint32_t *length, int32_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsUint32Array(JSObject *obj, uint32_t *length, uint32_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsFloat32Array(JSObject *obj, uint32_t *length, float **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsFloat64Array(JSObject *obj, uint32_t *length, double **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsArrayBufferView(JSObject *obj, uint32_t *length, uint8_t **data);
extern JS_FRIEND_API(JSObject *)
JS_GetObjectAsArrayBuffer(JSObject *obj, uint32_t *length, uint8_t **data);

/*
 * Get the type of elements in a typed array, or TYPE_DATAVIEW if a DataView.
 *
 * |obj| must have passed a JS_IsArrayBufferView/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is an ArrayBufferView or a
 * wrapper of an ArrayBufferView, and the unwrapping will succeed.
 */
extern JS_FRIEND_API(JSArrayBufferViewType)
JS_GetArrayBufferViewType(JSObject *obj);

/*
 * Check whether obj supports the JS_GetArrayBuffer* APIs. Note that this may
 * return false if a security wrapper is encountered that denies the
 * unwrapping. If this test succeeds, then it is safe to call the various
 * accessor JSAPI calls defined below.
 */
extern JS_FRIEND_API(JSBool)
JS_IsArrayBufferObject(JSObject *obj);

/*
 * Return the available byte length of an array buffer.
 *
 * |obj| must have passed a JS_IsArrayBufferObject test, or somehow be known
 * that it would pass such a test: it is an ArrayBuffer or a wrapper of an
 * ArrayBuffer, and the unwrapping will succeed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetArrayBufferByteLength(JSObject *obj);

/*
 * Return a pointer to an array buffer's data. The buffer is still owned by the
 * array buffer object, and should not be modified on another thread. The
 * returned pointer is stable across GCs.
 *
 * |obj| must have passed a JS_IsArrayBufferObject test, or somehow be known
 * that it would pass such a test: it is an ArrayBuffer or a wrapper of an
 * ArrayBuffer, and the unwrapping will succeed.
 */
extern JS_FRIEND_API(uint8_t *)
JS_GetArrayBufferData(JSObject *obj);

/*
 * Return the number of elements in a typed array.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetTypedArrayLength(JSObject *obj);

/*
 * Return the byte offset from the start of an array buffer to the start of a
 * typed array view.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetTypedArrayByteOffset(JSObject *obj);

/*
 * Return the byte length of a typed array.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetTypedArrayByteLength(JSObject *obj);

/*
 * Check whether obj supports JS_ArrayBufferView* APIs. Note that this may
 * return false if a security wrapper is encountered that denies the
 * unwrapping.
 */
extern JS_FRIEND_API(JSBool)
JS_IsArrayBufferViewObject(JSObject *obj);

/*
 * More generic name for JS_GetTypedArrayByteLength to cover DataViews as well
 */
extern JS_FRIEND_API(uint32_t)
JS_GetArrayBufferViewByteLength(JSObject *obj);

/*
 * Return a pointer to the start of the data referenced by a typed array. The
 * data is still owned by the typed array, and should not be modified on
 * another thread.
 *
 * |obj| must have passed a JS_Is*Array test, or somehow be known that it would
 * pass such a test: it is a typed array or a wrapper of a typed array, and the
 * unwrapping will succeed.
 */

extern JS_FRIEND_API(int8_t *)
JS_GetInt8ArrayData(JSObject *obj);
extern JS_FRIEND_API(uint8_t *)
JS_GetUint8ArrayData(JSObject *obj);
extern JS_FRIEND_API(uint8_t *)
JS_GetUint8ClampedArrayData(JSObject *obj);
extern JS_FRIEND_API(int16_t *)
JS_GetInt16ArrayData(JSObject *obj);
extern JS_FRIEND_API(uint16_t *)
JS_GetUint16ArrayData(JSObject *obj);
extern JS_FRIEND_API(int32_t *)
JS_GetInt32ArrayData(JSObject *obj);
extern JS_FRIEND_API(uint32_t *)
JS_GetUint32ArrayData(JSObject *obj);
extern JS_FRIEND_API(float *)
JS_GetFloat32ArrayData(JSObject *obj);
extern JS_FRIEND_API(double *)
JS_GetFloat64ArrayData(JSObject *obj);

/*
 * Same as above, but for any kind of ArrayBufferView. Prefer the type-specific
 * versions when possible.
 */
extern JS_FRIEND_API(void *)
JS_GetArrayBufferViewData(JSObject *obj);

/*
 * Return the ArrayBuffer underlying an ArrayBufferView. If the buffer has been
 * neutered, this will still return the neutered buffer. |obj| must be an
 * object that would return true for JS_IsArrayBufferViewObject().
 */
extern JS_FRIEND_API(JSObject *)
JS_GetArrayBufferViewBuffer(JSObject *obj);

/*
 * Check whether obj supports JS_GetDataView* APIs.
 */
JS_FRIEND_API(JSBool)
JS_IsDataViewObject(JSObject *obj);

/*
 * Return the byte offset of a data view into its array buffer. |obj| must be a
 * DataView.
 *
 * |obj| must have passed a JS_IsDataViewObject test, or somehow be known that
 * it would pass such a test: it is a data view or a wrapper of a data view,
 * and the unwrapping will succeed.
 */
JS_FRIEND_API(uint32_t)
JS_GetDataViewByteOffset(JSObject *obj);

/*
 * Return the byte length of a data view.
 *
 * |obj| must have passed a JS_IsDataViewObject test, or somehow be known that
 * it would pass such a test: it is a data view or a wrapper of a data view,
 * and the unwrapping will succeed. If cx is NULL, then DEBUG builds may be
 * unable to assert when unwrapping should be disallowed.
 */
JS_FRIEND_API(uint32_t)
JS_GetDataViewByteLength(JSObject *obj);

/*
 * Return a pointer to the beginning of the data referenced by a DataView.
 *
 * |obj| must have passed a JS_IsDataViewObject test, or somehow be known that
 * it would pass such a test: it is a data view or a wrapper of a data view,
 * and the unwrapping will succeed. If cx is NULL, then DEBUG builds may be
 * unable to assert when unwrapping should be disallowed.
 */
JS_FRIEND_API(void *)
JS_GetDataViewData(JSObject *obj);

/*
 * A class, expected to be passed by value, which represents the CallArgs for a
 * JSJitGetterOp.
 */
class JSJitGetterCallArgs : protected JS::MutableHandleValue
{
  public:
    explicit JSJitGetterCallArgs(const JS::CallArgs& args)
      : JS::MutableHandleValue(args.rval())
    {}

    explicit JSJitGetterCallArgs(JS::Rooted<JS::Value>* rooted)
      : JS::MutableHandleValue(rooted)
    {}

    JS::MutableHandleValue rval() {
        return *this;
    }
};

/*
 * A class, expected to be passed by value, which represents the CallArgs for a
 * JSJitSetterOp.
 */
class JSJitSetterCallArgs : protected JS::MutableHandleValue
{
  public:
    explicit JSJitSetterCallArgs(const JS::CallArgs& args)
      : JS::MutableHandleValue(args[0])
    {}

    JS::MutableHandleValue operator[](unsigned i) {
        MOZ_ASSERT(i == 0);
        return *this;
    }

    unsigned length() const { return 1; }

    // Add get() or maybe hasDefined() as needed
};

struct JSJitMethodCallArgsTraits;

/*
 * A class, expected to be passed by reference, which represents the CallArgs
 * for a JSJitMethodOp.
 */
class JSJitMethodCallArgs : protected JS::detail::CallArgsBase<JS::detail::NoUsedRval>
{
  private:
    typedef JS::detail::CallArgsBase<JS::detail::NoUsedRval> Base;
    friend struct JSJitMethodCallArgsTraits;

  public:
    explicit JSJitMethodCallArgs(const JS::CallArgs& args) {
        argv_ = args.array();
        argc_ = args.length();
    }

    JS::MutableHandleValue rval() const {
        return Base::rval();
    }

    unsigned length() const { return Base::length(); }

    JS::MutableHandleValue operator[](unsigned i) const {
        return Base::operator[](i);
    }

    bool hasDefined(unsigned i) const {
        return Base::hasDefined(i);
    }

    // Add get() as needed
};

struct JSJitMethodCallArgsTraits
{
    static const size_t offsetOfArgv = offsetof(JSJitMethodCallArgs, argv_);
    static const size_t offsetOfArgc = offsetof(JSJitMethodCallArgs, argc_);
};

/*
 * This struct contains metadata passed from the DOM to the JS Engine for JIT
 * optimizations on DOM property accessors. Eventually, this should be made
 * available to general JSAPI users, but we are not currently ready to do so.
 */
typedef bool
(* JSJitGetterOp)(JSContext *cx, JS::HandleObject thisObj,
                  void *specializedThis, JSJitGetterCallArgs args);
typedef bool
(* JSJitSetterOp)(JSContext *cx, JS::HandleObject thisObj,
                  void *specializedThis, JSJitSetterCallArgs args);
typedef bool
(* JSJitMethodOp)(JSContext *cx, JS::HandleObject thisObj,
                  void *specializedThis, const JSJitMethodCallArgs& args);

struct JSJitInfo {
    enum OpType {
        Getter,
        Setter,
        Method,
        OpType_None
    };

    union {
        JSJitGetterOp getter;
        JSJitSetterOp setter;
        JSJitMethodOp method;
    };
    uint32_t protoID;
    uint32_t depth;
    OpType type;
    bool isInfallible;      /* Is op fallible? False in setters. */
    bool isConstant;        /* Getting a construction-time constant? */
    bool isPure;            /* As long as no non-pure DOM things happen, will
                               keep returning the same value for the given
                               "this" object" */
    JSValueType returnType; /* The return type tag.  Might be JSVAL_TYPE_UNKNOWN */

    /* An alternative native that's safe to call in parallel mode. */
    JSParallelNative parallelNative;
};

#define JS_JITINFO_NATIVE_PARALLEL(op)                                         \
    {{NULL},0,0,JSJitInfo::OpType_None,false,false,false,JSVAL_TYPE_MISSING,op}

static JS_ALWAYS_INLINE const JSJitInfo *
FUNCTION_VALUE_TO_JITINFO(const JS::Value& v)
{
    JS_ASSERT(js::GetObjectClass(&v.toObject()) == js::FunctionClassPtr);
    return reinterpret_cast<js::shadow::Function *>(&v.toObject())->jitinfo;
}

/* Statically asserted in jsfun.h. */
static const unsigned JS_FUNCTION_INTERPRETED_BIT = 0x1;

static JS_ALWAYS_INLINE void
SET_JITINFO(JSFunction * func, const JSJitInfo *info)
{
    js::shadow::Function *fun = reinterpret_cast<js::shadow::Function *>(func);
    JS_ASSERT(!(fun->flags & JS_FUNCTION_INTERPRETED_BIT));
    fun->jitinfo = info;
}

/*
 * Engine-internal extensions of jsid.  This code is here only until we
 * eliminate Gecko's dependencies on it!
 */

static JS_ALWAYS_INLINE jsid
JSID_FROM_BITS(size_t bits)
{
    jsid id;
    JSID_BITS(id) = bits;
    return id;
}

/*
 * Must not be used on atoms that are representable as integer jsids.
 * Prefer NameToId or AtomToId over this function:
 *
 * A PropertyName is an atom that does not contain an integer in the range
 * [0, UINT32_MAX]. However, jsid can only hold an integer in the range
 * [0, JSID_INT_MAX] (where JSID_INT_MAX == 2^31-1).  Thus, for the range of
 * integers (JSID_INT_MAX, UINT32_MAX], to represent as a jsid 'id', it must be
 * the case JSID_IS_ATOM(id) and !JSID_TO_ATOM(id)->isPropertyName().  In most
 * cases when creating a jsid, code does not have to care about this corner
 * case because:
 *
 * - When given an arbitrary JSAtom*, AtomToId must be used, which checks for
 *   integer atoms representable as integer jsids, and does this conversion.
 *
 * - When given a PropertyName*, NameToId can be used which which does not need
 *   to do any dynamic checks.
 *
 * Thus, it is only the rare third case which needs this function, which
 * handles any JSAtom* that is known not to be representable with an int jsid.
 */
static JS_ALWAYS_INLINE jsid
NON_INTEGER_ATOM_TO_JSID(JSAtom *atom)
{
    JS_ASSERT(((size_t)atom & 0x7) == 0);
    jsid id = JSID_FROM_BITS((size_t)atom);
    JS_ASSERT(id == INTERNED_STRING_TO_JSID(NULL, (JSString*)atom));
    return id;
}

/* All strings stored in jsids are atomized, but are not necessarily property names. */
static JS_ALWAYS_INLINE JSBool
JSID_IS_ATOM(jsid id)
{
    return JSID_IS_STRING(id);
}

static JS_ALWAYS_INLINE JSBool
JSID_IS_ATOM(jsid id, JSAtom *atom)
{
    return id == JSID_FROM_BITS((size_t)atom);
}

static JS_ALWAYS_INLINE JSAtom *
JSID_TO_ATOM(jsid id)
{
    return (JSAtom *)JSID_TO_STRING(id);
}

JS_STATIC_ASSERT(sizeof(jsid) == JS_BYTES_PER_WORD);

namespace js {

static JS_ALWAYS_INLINE Value
IdToValue(jsid id)
{
    if (JSID_IS_STRING(id))
        return StringValue(JSID_TO_STRING(id));
    if (JS_LIKELY(JSID_IS_INT(id)))
        return Int32Value(JSID_TO_INT(id));
    if (JS_LIKELY(JSID_IS_OBJECT(id)))
        return ObjectValue(*JSID_TO_OBJECT(id));
    JS_ASSERT(JSID_IS_VOID(id));
    return UndefinedValue();
}

static JS_ALWAYS_INLINE jsval
IdToJsval(jsid id)
{
    return IdToValue(id);
}

extern JS_FRIEND_API(bool)
IsReadOnlyDateMethod(JS::IsAcceptableThis test, JS::NativeImpl method);

extern JS_FRIEND_API(bool)
IsTypedArrayThisCheck(JS::IsAcceptableThis test);

enum CTypesActivityType {
    CTYPES_CALL_BEGIN,
    CTYPES_CALL_END,
    CTYPES_CALLBACK_BEGIN,
    CTYPES_CALLBACK_END
};

typedef void
(* CTypesActivityCallback)(JSContext *cx, CTypesActivityType type);

/*
 * Sets a callback that is run whenever js-ctypes is about to be used when
 * calling into C.
 */
JS_FRIEND_API(void)
SetCTypesActivityCallback(JSRuntime *rt, CTypesActivityCallback cb);

class JS_FRIEND_API(AutoCTypesActivityCallback) {
  private:
    JSContext *cx;
    CTypesActivityCallback callback;
    CTypesActivityType endType;
    MOZ_DECL_USE_GUARD_OBJECT_NOTIFIER

  public:
    AutoCTypesActivityCallback(JSContext *cx, CTypesActivityType beginType,
                               CTypesActivityType endType
                               MOZ_GUARD_OBJECT_NOTIFIER_PARAM);
    ~AutoCTypesActivityCallback() {
        DoEndCallback();
    }
    void DoEndCallback() {
        if (callback) {
            callback(cx, endType);
            callback = NULL;
        }
    }
};

#ifdef DEBUG
extern JS_FRIEND_API(void)
assertEnteredPolicy(JSContext *cx, JSObject *obj, jsid id);
#else
inline void assertEnteredPolicy(JSContext *cx, JSObject *obj, jsid id) {};
#endif

typedef bool
(* ObjectMetadataCallback)(JSContext *cx, JSObject **pmetadata);

/*
 * Specify a callback to invoke when creating each JS object in the current
 * compartment, which may return a metadata object to associate with the
 * object. Objects with different metadata have different shape hierarchies,
 * so for efficiency, objects should generally try to share metadata objects.
 */
JS_FRIEND_API(void)
SetObjectMetadataCallback(JSContext *cx, ObjectMetadataCallback callback);

/* Manipulate the metadata associated with an object. */

JS_FRIEND_API(bool)
SetObjectMetadata(JSContext *cx, JS::HandleObject obj, JS::HandleObject metadata);

JS_FRIEND_API(JSObject *)
GetObjectMetadata(JSObject *obj);

/* ES5 8.12.8. */
extern JS_FRIEND_API(JSBool)
DefaultValue(JSContext *cx, JS::HandleObject obj, JSType hint, MutableHandleValue vp);

/*
 * Helper function. To approximate a call to the [[DefineOwnProperty]] internal
 * method described in ES5, first call this, then call JS_DefinePropertyById.
 *
 * JS_DefinePropertyById by itself does not enforce the invariants on
 * non-configurable properties when obj->isNative(). This function performs the
 * relevant checks (specified in ES5 8.12.9 [[DefineOwnProperty]] steps 1-11),
 * but only if obj is native.
 *
 * The reason for the messiness here is that ES5 uses [[DefineOwnProperty]] as
 * a sort of extension point, but there is no hook in js::Class,
 * js::ProxyHandler, or the JSAPI with precisely the right semantics for it.
 */
extern JS_FRIEND_API(bool)
CheckDefineProperty(JSContext *cx, HandleObject obj, HandleId id, HandleValue value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);

} /* namespace js */

extern JS_FRIEND_API(JSBool)
js_DefineOwnProperty(JSContext *cx, JSObject *objArg, jsid idArg,
                     const js::PropertyDescriptor& descriptor, JSBool *bp);

extern JS_FRIEND_API(JSBool)
js_ReportIsNotFunction(JSContext *cx, const JS::Value& v);

#ifdef JSGC_GENERATIONAL
extern JS_FRIEND_API(void)
JS_StoreObjectPostBarrierCallback(JSContext* cx,
                                  void (*callback)(JSTracer *trc, void *key, void *data),
                                  JSObject *key, void *data);

extern JS_FRIEND_API(void)
JS_StoreStringPostBarrierCallback(JSContext* cx,
                                  void (*callback)(JSTracer *trc, void *key, void *data),
                                  JSString *key, void *data);
#else
inline void
JS_StoreObjectPostBarrierCallback(JSContext* cx,
                                  void (*callback)(JSTracer *trc, void *key, void *data),
                                  JSObject *key, void *data) {}

inline void
JS_StoreStringPostBarrierCallback(JSContext* cx,
                                  void (*callback)(JSTracer *trc, void *key, void *data),
                                  JSString *key, void *data) {}
#endif /* JSGC_GENERATIONAL */

#endif /* jsfriendapi_h */
