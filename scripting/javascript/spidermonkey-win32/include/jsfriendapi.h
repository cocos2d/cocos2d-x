/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
 *
 * The Original Code is SpiderMonkey code.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2010
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

#ifndef jsfriendapi_h___
#define jsfriendapi_h___

#include "jsclass.h"
#include "jspubtd.h"
#include "jsprvtd.h"

#include "mozilla/GuardObjects.h"

JS_BEGIN_EXTERN_C

extern JS_FRIEND_API(void)
JS_SetGrayGCRootsTracer(JSRuntime *rt, JSTraceDataOp traceOp, void *data);

extern JS_FRIEND_API(JSString *)
JS_GetAnonymousString(JSRuntime *rt);

extern JS_FRIEND_API(JSObject *)
JS_FindCompilationScope(JSContext *cx, JSObject *obj);

extern JS_FRIEND_API(JSFunction *)
JS_GetObjectFunction(JSObject *obj);

extern JS_FRIEND_API(JSObject *)
JS_GetGlobalForFrame(JSStackFrame *fp);

extern JS_FRIEND_API(JSBool)
JS_SplicePrototype(JSContext *cx, JSObject *obj, JSObject *proto);

extern JS_FRIEND_API(JSObject *)
JS_NewObjectWithUniqueType(JSContext *cx, JSClass *clasp, JSObject *proto, JSObject *parent);

extern JS_FRIEND_API(uint32_t)
JS_ObjectCountDynamicSlots(JSObject *obj);

extern JS_FRIEND_API(void)
JS_ShrinkGCBuffers(JSRuntime *rt);

extern JS_FRIEND_API(size_t)
JS_GetE4XObjectsCreated(JSContext *cx);

extern JS_FRIEND_API(size_t)
JS_SetProtoCalled(JSContext *cx);

extern JS_FRIEND_API(size_t)
JS_GetCustomIteratorCount(JSContext *cx);

extern JS_FRIEND_API(JSBool)
JS_NondeterministicGetWeakMapKeys(JSContext *cx, JSObject *obj, JSObject **ret);

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
    JS_TELEMETRY_GC_MARK_MS,
    JS_TELEMETRY_GC_SWEEP_MS,
    JS_TELEMETRY_GC_SLICE_MS,
    JS_TELEMETRY_GC_MMU_50,
    JS_TELEMETRY_GC_RESET,
    JS_TELEMETRY_GC_INCREMENTAL_DISABLED,
    JS_TELEMETRY_GC_NON_INCREMENTAL
};

typedef void
(* JSAccumulateTelemetryDataCallback)(int id, uint32_t sample);

extern JS_FRIEND_API(void)
JS_SetAccumulateTelemetryCallback(JSRuntime *rt, JSAccumulateTelemetryDataCallback callback);

extern JS_FRIEND_API(JSPrincipals *)
JS_GetCompartmentPrincipals(JSCompartment *compartment);

/* Safe to call with input obj == NULL. Returns non-NULL iff obj != NULL. */
extern JS_FRIEND_API(JSObject *)
JS_ObjectToInnerObject(JSContext *cx, JSObject *obj);

/* Requires obj != NULL. */
extern JS_FRIEND_API(JSObject *)
JS_ObjectToOuterObject(JSContext *cx, JSObject *obj);

extern JS_FRIEND_API(JSObject *)
JS_CloneObject(JSContext *cx, JSObject *obj, JSObject *proto, JSObject *parent);

extern JS_FRIEND_API(JSBool)
js_GetterOnlyPropertyStub(JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp);

JS_FRIEND_API(void)
js_ReportOverRecursed(JSContext *maybecx);

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

#ifdef __cplusplus

extern JS_FRIEND_API(bool)
JS_CopyPropertiesFrom(JSContext *cx, JSObject *target, JSObject *obj);

extern JS_FRIEND_API(JSBool)
JS_WrapPropertyDescriptor(JSContext *cx, js::PropertyDescriptor *desc);

extern JS_FRIEND_API(JSBool)
JS_EnumerateState(JSContext *cx, JSObject *obj, JSIterateOp enum_op, js::Value *statep, jsid *idp);

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

extern JS_FRIEND_API(bool)
JS_DefineFunctionsWithHelp(JSContext *cx, JSObject *obj, const JSFunctionSpecWithHelp *fs);

#endif

JS_END_EXTERN_C

#ifdef __cplusplus

namespace js {

struct RuntimeFriendFields {
    /*
     * If non-zero, we were been asked to call the operation callback as soon
     * as possible.
     */
    volatile int32_t    interrupt;

    /* Limit pointer for checking native stack consumption. */
    uintptr_t           nativeStackLimit;

    RuntimeFriendFields()
      : interrupt(0),
        nativeStackLimit(0) { }

    static const RuntimeFriendFields *get(const JSRuntime *rt) {
        return reinterpret_cast<const RuntimeFriendFields *>(rt);
    }
};

inline JSRuntime *
GetRuntime(const JSContext *cx)
{
    return ContextFriendFields::get(cx)->runtime;
}

typedef bool
(* PreserveWrapperCallback)(JSContext *cx, JSObject *obj);

#ifdef DEBUG
 /*
  * DEBUG-only method to dump the complete object graph of heap-allocated things.
  * fp is the file for the dump output.
  */
extern JS_FRIEND_API(void)
DumpHeapComplete(JSRuntime *rt, FILE *fp);

#endif

class JS_FRIEND_API(AutoPreserveCompartment) {
  private:
    JSContext *cx;
    JSCompartment *oldCompartment;
  public:
    AutoPreserveCompartment(JSContext *cx JS_GUARD_OBJECT_NOTIFIER_PARAM);
    ~AutoPreserveCompartment();
    JS_DECL_USE_GUARD_OBJECT_NOTIFIER
};

class JS_FRIEND_API(AutoSwitchCompartment) {
  private:
    JSContext *cx;
    JSCompartment *oldCompartment;
  public:
    AutoSwitchCompartment(JSContext *cx, JSCompartment *newCompartment
                          JS_GUARD_OBJECT_NOTIFIER_PARAM);
    AutoSwitchCompartment(JSContext *cx, JSObject *target JS_GUARD_OBJECT_NOTIFIER_PARAM);
    ~AutoSwitchCompartment();
    JS_DECL_USE_GUARD_OBJECT_NOTIFIER
};

#ifdef OLD_GETTER_SETTER_METHODS
JS_FRIEND_API(JSBool) obj_defineGetter(JSContext *cx, unsigned argc, js::Value *vp);
JS_FRIEND_API(JSBool) obj_defineSetter(JSContext *cx, unsigned argc, js::Value *vp);
#endif

extern JS_FRIEND_API(bool)
IsSystemCompartment(const JSCompartment *compartment);

extern JS_FRIEND_API(bool)
IsAtomsCompartment(const JSCompartment *c);

/*
 * Check whether it is OK to assign an undeclared property with name
 * propname of the global object in the current script on cx.  Reports
 * an error if one needs to be reported (in particular in all cases
 * when it returns false).
 */
extern JS_FRIEND_API(bool)
CheckUndeclaredVarAssignment(JSContext *cx, JSString *propname);

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
GCThingIsMarkedGray(void *thing);

/*
 * Shadow declarations of JS internal structures, for access by inline access
 * functions below. Do not use these structures in any other way. When adding
 * new fields for access by inline methods, make sure to add static asserts to
 * the original header file to ensure that offsets are consistent.
 */
namespace shadow {

struct TypeObject {
    JSObject    *proto;
};

struct BaseShape {
    js::Class   *clasp;
    JSObject    *parent;
};

struct Shape {
    BaseShape   *base;
    jsid        _1;
    uint32_t    slotInfo;

    static const uint32_t FIXED_SLOTS_SHIFT = 27;
};

struct Object {
    Shape       *shape;
    TypeObject  *type;
    js::Value   *slots;
    js::Value   *_1;

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

struct Atom {
    size_t _;
    const jschar *chars;
};

} /* namespace shadow */

extern JS_FRIEND_DATA(js::Class) AnyNameClass;
extern JS_FRIEND_DATA(js::Class) AttributeNameClass;
extern JS_FRIEND_DATA(js::Class) CallClass;
extern JS_FRIEND_DATA(js::Class) DeclEnvClass;
extern JS_FRIEND_DATA(js::Class) FunctionClass;
extern JS_FRIEND_DATA(js::Class) FunctionProxyClass;
extern JS_FRIEND_DATA(js::Class) NamespaceClass;
extern JS_FRIEND_DATA(js::Class) OuterWindowProxyClass;
extern JS_FRIEND_DATA(js::Class) ObjectProxyClass;
extern JS_FRIEND_DATA(js::Class) QNameClass;
extern JS_FRIEND_DATA(js::Class) XMLClass;
extern JS_FRIEND_DATA(js::Class) ObjectClass;

inline js::Class *
GetObjectClass(const JSObject *obj)
{
    return reinterpret_cast<const shadow::Object*>(obj)->shape->base->clasp;
}

inline JSClass *
GetObjectJSClass(const JSObject *obj)
{
    return js::Jsvalify(GetObjectClass(obj));
}

JS_FRIEND_API(bool)
IsScopeObject(JSObject *obj);

inline JSObject *
GetObjectParent(JSObject *obj)
{
    JS_ASSERT(!IsScopeObject(obj));
    return reinterpret_cast<shadow::Object*>(obj)->shape->base->parent;
}

JS_FRIEND_API(JSObject *)
GetObjectParentMaybeScope(JSObject *obj);

JS_FRIEND_API(JSObject *)
GetGlobalForObjectCrossCompartment(JSObject *obj);

JS_FRIEND_API(bool)
IsOriginalScriptFunction(JSFunction *fun);

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
                      JSPropertySpec *ps, JSFunctionSpec *fs,
                      JSPropertySpec *static_ps, JSFunctionSpec *static_fs);

JS_FRIEND_API(const Value &)
GetFunctionNativeReserved(JSObject *fun, size_t which);

JS_FRIEND_API(void)
SetFunctionNativeReserved(JSObject *fun, size_t which, const Value &val);

inline JSObject *
GetObjectProto(JSObject *obj)
{
    return reinterpret_cast<const shadow::Object*>(obj)->type->proto;
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
GetReservedSlot(const JSObject *obj, size_t slot)
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
    if (sobj->slotRef(slot).isMarkable())
        SetReservedSlotWithBarrier(obj, slot, value);
    else
        sobj->slotRef(slot) = value;
}

JS_FRIEND_API(uint32_t)
GetObjectSlotSpan(JSObject *obj);

inline const Value &
GetObjectSlot(JSObject *obj, size_t slot)
{
    JS_ASSERT(slot < GetObjectSlotSpan(obj));
    return reinterpret_cast<const shadow::Object *>(obj)->slotRef(slot);
}

inline Shape *
GetObjectShape(JSObject *obj)
{
    shadow::Shape *shape = reinterpret_cast<const shadow::Object*>(obj)->shape;
    return reinterpret_cast<Shape *>(shape);
}

inline const jschar *
GetAtomChars(JSAtom *atom)
{
    return reinterpret_cast<shadow::Atom *>(atom)->chars;
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
StringIsArrayIndex(JSLinearString *str, uint32_t *indexp);

JS_FRIEND_API(void)
SetPreserveWrapperCallback(JSRuntime *rt, PreserveWrapperCallback callback);

JS_FRIEND_API(bool)
IsObjectInContextCompartment(const JSObject *obj, const JSContext *cx);

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
    return RuntimeFriendFields::get(rt)->nativeStackLimit;
}

#define JS_CHECK_RECURSION(cx, onerror)                                         \
    JS_BEGIN_MACRO                                                              \
        int stackDummy_;                                                        \
        if (!JS_CHECK_STACK_SIZE(js::GetNativeStackLimit(js::GetRuntime(cx)), &stackDummy_)) { \
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

#ifdef JS_THREADSAFE
JS_FRIEND_API(void *)
GetOwnerThread(const JSContext *cx);

JS_FRIEND_API(unsigned)
GetContextOutstandingRequests(const JSContext *cx);
#endif

JS_FRIEND_API(JSCompartment *)
GetContextCompartment(const JSContext *cx);

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

extern JS_FRIEND_API(JSVersion)
VersionSetXML(JSVersion version, bool enable);

extern JS_FRIEND_API(bool)
CanCallContextDebugHandler(JSContext *cx);

extern JS_FRIEND_API(JSTrapStatus)
CallContextDebugHandler(JSContext *cx, JSScript *script, jsbytecode *bc, Value *rval);

extern JS_FRIEND_API(bool)
IsContextRunningJS(JSContext *cx);

class SystemAllocPolicy;
typedef Vector<JSCompartment*, 0, SystemAllocPolicy> CompartmentVector;
extern JS_FRIEND_API(const CompartmentVector&)
GetRuntimeCompartments(JSRuntime *rt);

extern JS_FRIEND_API(size_t)
SizeOfJSContext();

#define GCREASONS(D)                            \
    /* Reasons internal to the JS engine */     \
    D(API)                                      \
    D(MAYBEGC)                                  \
    D(LAST_CONTEXT)                             \
    D(DESTROY_CONTEXT)                          \
    D(LAST_DITCH)                               \
    D(TOO_MUCH_MALLOC)                          \
    D(ALLOC_TRIGGER)                            \
    D(DEBUG_GC)                                 \
    D(UNUSED2) /* was SHAPE */                  \
    D(UNUSED3) /* was REFILL */                 \
                                                \
    /* Reasons from Firefox */                  \
    D(DOM_WINDOW_UTILS)                         \
    D(COMPONENT_UTILS)                          \
    D(MEM_PRESSURE)                             \
    D(CC_WAITING)                               \
    D(CC_FORCED)                                \
    D(LOAD_END)                                 \
    D(POST_COMPARTMENT)                         \
    D(PAGE_HIDE)                                \
    D(NSJSCONTEXT_DESTROY)                      \
    D(SET_NEW_DOCUMENT)                         \
    D(SET_DOC_SHELL)                            \
    D(DOM_UTILS)                                \
    D(DOM_IPC)                                  \
    D(DOM_WORKER)                               \
    D(INTER_SLICE_GC)                           \
    D(REFRESH_FRAME)

namespace gcreason {

/* GCReasons will end up looking like JSGC_MAYBEGC */
enum Reason {
#define MAKE_REASON(name) name,
    GCREASONS(MAKE_REASON)
#undef MAKE_REASON
    NO_REASON,
    NUM_REASONS
};

} /* namespace gcreason */

extern JS_FRIEND_API(void)
PrepareCompartmentForGC(JSCompartment *comp);

extern JS_FRIEND_API(void)
PrepareForFullGC(JSRuntime *rt);

/*
 * When triggering a GC using one of the functions below, it is first necessary
 * to select the compartments to be collected. To do this, you can call
 * PrepareCompartmentForGC on each compartment, or you can call PrepareForFullGC
 * to select all compartments. Failing to select any compartment is an error.
 */

extern JS_FRIEND_API(void)
GCForReason(JSRuntime *rt, gcreason::Reason reason);

extern JS_FRIEND_API(void)
ShrinkingGC(JSRuntime *rt, gcreason::Reason reason);

extern JS_FRIEND_API(void)
IncrementalGC(JSRuntime *rt, gcreason::Reason reason);

extern JS_FRIEND_API(void)
SetGCSliceTimeBudget(JSContext *cx, int64_t millis);

enum GCProgress {
    /*
     * During non-incremental GC, the GC is bracketed by JSGC_CYCLE_BEGIN/END
     * callbacks. During an incremental GC, the sequence of callbacks is as
     * follows:
     *   JSGC_CYCLE_BEGIN, JSGC_SLICE_END  (first slice)
     *   JSGC_SLICE_BEGIN, JSGC_SLICE_END  (second slice)
     *   ...
     *   JSGC_SLICE_BEGIN, JSGC_CYCLE_END  (last slice)
     */

    GC_CYCLE_BEGIN,
    GC_SLICE_BEGIN,
    GC_SLICE_END,
    GC_CYCLE_END
};

struct JS_FRIEND_API(GCDescription) {
    bool isCompartment;

    GCDescription(bool isCompartment)
      : isCompartment(isCompartment) {}

    jschar *formatMessage(JSRuntime *rt) const;
    jschar *formatJSON(JSRuntime *rt, uint64_t timestamp) const;
};

typedef void
(* GCSliceCallback)(JSRuntime *rt, GCProgress progress, const GCDescription &desc);

extern JS_FRIEND_API(GCSliceCallback)
SetGCSliceCallback(JSRuntime *rt, GCSliceCallback callback);

/*
 * Signals a good place to do an incremental slice, because the browser is
 * drawing a frame.
 */
extern JS_FRIEND_API(void)
NotifyDidPaint(JSRuntime *rt);

extern JS_FRIEND_API(bool)
IsIncrementalGCEnabled(JSRuntime *rt);

extern JS_FRIEND_API(void)
DisableIncrementalGC(JSRuntime *rt);

extern JS_FRIEND_API(bool)
IsIncrementalBarrierNeeded(JSRuntime *rt);

extern JS_FRIEND_API(bool)
IsIncrementalBarrierNeeded(JSContext *cx);

extern JS_FRIEND_API(bool)
IsIncrementalBarrierNeededOnObject(JSObject *obj);

extern JS_FRIEND_API(void)
IncrementalReferenceBarrier(void *ptr);

extern JS_FRIEND_API(void)
IncrementalValueBarrier(const Value &v);

class ObjectPtr
{
    JSObject *value;

  public:
    ObjectPtr() : value(NULL) {}

    ObjectPtr(JSObject *obj) : value(obj) {}

    /* Always call finalize before the destructor. */
    ~ObjectPtr() { JS_ASSERT(!value); }

    void finalize(JSRuntime *rt) {
        if (IsIncrementalBarrierNeeded(rt))
            IncrementalReferenceBarrier(value);
        value = NULL;
    }

    void init(JSObject *obj) { value = obj; }

    JSObject *get() const { return value; }

    void writeBarrierPre(JSRuntime *rt) {
        IncrementalReferenceBarrier(value);
    }

    ObjectPtr &operator=(JSObject *obj) {
        IncrementalReferenceBarrier(value);
        value = obj;
        return *this;
    }

    JSObject &operator*() const { return *value; }
    JSObject *operator->() const { return value; }
    operator JSObject *() const { return value; }
};

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
 * Get an error type name from a number.
 * If no exception is associated, return NULL.
 */
extern JS_FRIEND_API(const jschar*)
GetErrorTypeNameFromNumber(JSContext* cx, const unsigned errorNumber);

} /* namespace js */

#endif

/* Implemented in jsdate.cpp. */

/*
 * Detect whether the internal date value is NaN.  (Because failure is
 * out-of-band for js_DateGet*)
 */
extern JS_FRIEND_API(JSBool)
js_DateIsValid(JSContext *cx, JSObject* obj);

extern JS_FRIEND_API(double)
js_DateGetMsecSinceEpoch(JSContext *cx, JSObject *obj);

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

#ifdef __cplusplus

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

    TYPE_MAX
};

} /* namespace ArrayBufferView */
} /* namespace js */

typedef js::ArrayBufferView::ViewType JSArrayBufferViewType;
#else
typedef uint32_t JSArrayBufferViewType;
#endif /* __cplusplus */

/*
 * Create a new typed array with nelements elements.
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
 * Create a new typed array using the given ArrayBuffer for storage. byteOffset
 * must not exceed (signed) INT32_MAX. The length value is optional; if -1 is
 * passed, enough elements to use up the remainder of the byte array is used as
 * the default value.
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
JS_IsTypedArrayObject(JSObject *obj, JSContext *cx);

/*
 * Test for specific typed array types (ArrayBufferView subtypes)
 */

extern JS_FRIEND_API(JSBool)
JS_IsInt8Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsUint8Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsUint8ClampedArray(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsInt16Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsUint16Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsInt32Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsUint32Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsFloat32Array(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(JSBool)
JS_IsFloat64Array(JSObject *obj, JSContext *cx);

/*
 * Get the type of elements in a typed array.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed. If cx is NULL, then DEBUG
 * builds may be unable to assert when unwrapping should be disallowed.
 */
extern JS_FRIEND_API(JSArrayBufferViewType)
JS_GetTypedArrayType(JSObject *obj, JSContext *cx);

/*
 * Check whether obj supports the JS_GetArrayBuffer* APIs. Note that this may
 * return false if a security wrapper is encountered that denies the
 * unwrapping. If this test succeeds, then it is safe to call the various
 * accessor JSAPI calls defined below.
 */
extern JS_FRIEND_API(JSBool)
JS_IsArrayBufferObject(JSObject *obj, JSContext *cx);

/*
 * Return the available byte length of an array buffer.
 *
 * |obj| must have passed a JS_IsArrayBufferObject test, or somehow be known
 * that it would pass such a test: it is an ArrayBuffer or a wrapper of an
 * ArrayBuffer, and the unwrapping will succeed. If cx is NULL, then DEBUG
 * builds may be unable to assert when unwrapping should be disallowed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetArrayBufferByteLength(JSObject *obj, JSContext *cx);

/*
 * Return a pointer to an array buffer's data. The buffer is still owned by the
 * array buffer object, and should not be modified on another thread.
 *
 * |obj| must have passed a JS_IsArrayBufferObject test, or somehow be known
 * that it would pass such a test: it is an ArrayBuffer or a wrapper of an
 * ArrayBuffer, and the unwrapping will succeed. If cx is NULL, then DEBUG
 * builds may be unable to assert when unwrapping should be disallowed.
 */
extern JS_FRIEND_API(uint8_t *)
JS_GetArrayBufferData(JSObject *obj, JSContext *cx);

/*
 * Return the number of elements in a typed array.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed. If cx is NULL, then DEBUG
 * builds may be unable to assert when unwrapping should be disallowed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetTypedArrayLength(JSObject *obj, JSContext *cx);

/*
 * Return the byte offset from the start of an array buffer to the start of a
 * typed array view.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed. If cx is NULL, then DEBUG
 * builds may be unable to assert when unwrapping should be disallowed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetTypedArrayByteOffset(JSObject *obj, JSContext *cx);

/*
 * Return the byte length of a typed array.
 *
 * |obj| must have passed a JS_IsTypedArrayObject/JS_Is*Array test, or somehow
 * be known that it would pass such a test: it is a typed array or a wrapper of
 * a typed array, and the unwrapping will succeed. If cx is NULL, then DEBUG
 * builds may be unable to assert when unwrapping should be disallowed.
 */
extern JS_FRIEND_API(uint32_t)
JS_GetTypedArrayByteLength(JSObject *obj, JSContext *cx);

/*
 * More generic name for JS_GetTypedArrayByteLength to cover DataViews as well
 */
extern JS_FRIEND_API(uint32_t)
JS_GetArrayBufferViewByteLength(JSObject *obj, JSContext *cx);

/*
 * Return a pointer to the start of the data referenced by a typed array. The
 * data is still owned by the typed array, and should not be modified on
 * another thread.
 *
 * |obj| must have passed a JS_Is*Array test, or somehow be known that it would
 * pass such a test: it is a typed array or a wrapper of a typed array, and the
 * unwrapping will succeed. If cx is NULL, then DEBUG builds may be unable to
 * assert when unwrapping should be disallowed.
 */

extern JS_FRIEND_API(int8_t *)
JS_GetInt8ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(uint8_t *)
JS_GetUint8ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(uint8_t *)
JS_GetUint8ClampedArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(int16_t *)
JS_GetInt16ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(uint16_t *)
JS_GetUint16ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(int32_t *)
JS_GetInt32ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(uint32_t *)
JS_GetUint32ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(float *)
JS_GetFloat32ArrayData(JSObject *obj, JSContext *cx);
extern JS_FRIEND_API(double *)
JS_GetFloat64ArrayData(JSObject *obj, JSContext *cx);

/*
 * Same as above, but for any kind of ArrayBufferView. Prefer the type-specific
 * versions when possible.
 */
extern JS_FRIEND_API(void *)
JS_GetArrayBufferViewData(JSObject *obj, JSContext *cx);

#endif /* jsfriendapi_h___ */
