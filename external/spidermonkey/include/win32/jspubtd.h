/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jspubtd_h
#define jspubtd_h

/*
 * JS public API typedefs.
 */

#include "mozilla/PodOperations.h"

#include "jsprototypes.h"
#include "jstypes.h"

#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING) || (defined(DEBUG) && !defined(_WIN32))
# define JSGC_TRACK_EXACT_ROOTS
#endif

namespace JS {

/*
 * Allow headers to reference JS::Value without #including the whole jsapi.h.
 * Unfortunately, typedefs (hence jsval) cannot be declared.
 */
class Value;

template <typename T>
class Rooted;

class JS_PUBLIC_API(AutoGCRooter);

struct Zone;

} /* namespace JS */

/*
 * In release builds, jsid is defined to be an integral type. This
 * prevents many bugs from being caught at compile time. E.g.:
 *
 *  jsid id = ...
 *  if (id == JS_TRUE)  // error
 *    ...
 *
 *  size_t n = id;      // error
 *
 * To catch more errors, jsid is given a struct type in C++ debug builds.
 * Struct assignment and (in C++) operator== allow correct code to be mostly
 * oblivious to the change. This feature can be explicitly disabled in debug
 * builds by defining JS_NO_JSVAL_JSID_STRUCT_TYPES.
 */
// Needed for cocos2d-js
#define JS_NO_JSVAL_JSID_STRUCT_TYPES
# if defined(DEBUG) && !defined(JS_NO_JSVAL_JSID_STRUCT_TYPES)
#  define JS_USE_JSID_STRUCT_TYPES
# endif

# ifdef JS_USE_JSID_STRUCT_TYPES
struct jsid
{
    size_t asBits;
    bool operator==(jsid rhs) const { return asBits == rhs.asBits; }
    bool operator!=(jsid rhs) const { return asBits != rhs.asBits; }
};
#  define JSID_BITS(id) (id.asBits)
# else  /* defined(JS_USE_JSID_STRUCT_TYPES) */
typedef ptrdiff_t jsid;
#  define JSID_BITS(id) (id)
# endif  /* defined(JS_USE_JSID_STRUCT_TYPES) */

#ifdef WIN32
typedef wchar_t   jschar;
#else
typedef uint16_t  jschar;
#endif

/*
 * Run-time version enumeration.  For compile-time version checking, please use
 * the JS_HAS_* macros in jsversion.h, or use MOZJS_MAJOR_VERSION,
 * MOZJS_MINOR_VERSION, MOZJS_PATCH_VERSION, and MOZJS_ALPHA definitions.
 */
typedef enum JSVersion {
    JSVERSION_ECMA_3  = 148,
    JSVERSION_1_6     = 160,
    JSVERSION_1_7     = 170,
    JSVERSION_1_8     = 180,
    JSVERSION_ECMA_5  = 185,
    JSVERSION_DEFAULT = 0,
    JSVERSION_UNKNOWN = -1,
    JSVERSION_LATEST  = JSVERSION_ECMA_5
} JSVersion;

/* Result of typeof operator enumeration. */
typedef enum JSType {
    JSTYPE_VOID,                /* undefined */
    JSTYPE_OBJECT,              /* object */
    JSTYPE_FUNCTION,            /* function */
    JSTYPE_STRING,              /* string */
    JSTYPE_NUMBER,              /* number */
    JSTYPE_BOOLEAN,             /* boolean */
    JSTYPE_NULL,                /* null */
    JSTYPE_LIMIT
} JSType;

/* Dense index into cached prototypes and class atoms for standard objects. */
typedef enum JSProtoKey {
#define PROTOKEY_AND_INITIALIZER(name,code,init) JSProto_##name = code,
    JS_FOR_EACH_PROTOTYPE(PROTOKEY_AND_INITIALIZER)
#undef JS_PROTO
    JSProto_LIMIT
} JSProtoKey;

/* js_CheckAccess mode enumeration. */
typedef enum JSAccessMode {
    JSACC_PROTO  = 0,           /* XXXbe redundant w.r.t. id */

                                /*
                                 * enum value #1 formerly called JSACC_PARENT,
                                 * gap preserved for ABI compatibility.
                                 */

                                /*
                                 * enum value #2 formerly called JSACC_IMPORT,
                                 * gap preserved for ABI compatibility.
                                 */

    JSACC_WATCH  = 3,           /* a watchpoint on object foo for id 'bar' */
    JSACC_READ   = 4,           /* a "get" of foo.bar */
    JSACC_WRITE  = 8,           /* a "set" of foo.bar = baz */
    JSACC_LIMIT
} JSAccessMode;

#define JSACC_TYPEMASK          (JSACC_WRITE - 1)

/*
 * This enum type is used to control the behavior of a JSObject property
 * iterator function that has type JSNewEnumerate.
 */
typedef enum JSIterateOp {
    /* Create new iterator state over enumerable properties. */
    JSENUMERATE_INIT,

    /* Create new iterator state over all properties. */
    JSENUMERATE_INIT_ALL,

    /* Iterate once. */
    JSENUMERATE_NEXT,

    /* Destroy iterator state. */
    JSENUMERATE_DESTROY
} JSIterateOp;

/* See JSVAL_TRACE_KIND and JSTraceCallback in jsapi.h. */
typedef enum {
    JSTRACE_OBJECT,
    JSTRACE_STRING,
    JSTRACE_SCRIPT,

    /*
     * Trace kinds internal to the engine. The embedding can only see them if
     * it implements JSTraceCallback.
     */
    JSTRACE_LAZY_SCRIPT,
    JSTRACE_IONCODE,
    JSTRACE_SHAPE,
    JSTRACE_BASE_SHAPE,
    JSTRACE_TYPE_OBJECT,
    JSTRACE_LAST = JSTRACE_TYPE_OBJECT
} JSGCTraceKind;

/* Struct typedefs and class forward declarations. */
typedef struct JSClass                      JSClass;
typedef struct JSCompartment                JSCompartment;
typedef struct JSConstDoubleSpec            JSConstDoubleSpec;
typedef struct JSContext                    JSContext;
typedef struct JSCrossCompartmentCall       JSCrossCompartmentCall;
typedef struct JSErrorReport                JSErrorReport;
typedef struct JSExceptionState             JSExceptionState;
typedef struct JSFunctionSpec               JSFunctionSpec;
typedef struct JSIdArray                    JSIdArray;
typedef struct JSLocaleCallbacks            JSLocaleCallbacks;
typedef struct JSObjectMap                  JSObjectMap;
typedef struct JSPrincipals                 JSPrincipals;
typedef struct JSPropertyDescriptor         JSPropertyDescriptor;
typedef struct JSPropertyName               JSPropertyName;
typedef struct JSPropertySpec               JSPropertySpec;
typedef struct JSRuntime                    JSRuntime;
typedef struct JSSecurityCallbacks          JSSecurityCallbacks;
typedef struct JSStructuredCloneCallbacks   JSStructuredCloneCallbacks;
typedef struct JSStructuredCloneReader      JSStructuredCloneReader;
typedef struct JSStructuredCloneWriter      JSStructuredCloneWriter;
typedef struct JSTracer                     JSTracer;

class                                       JSFlatString;
class                                       JSFunction;
class                                       JSObject;
class                                       JSScript;
class                                       JSStableString;  // long story
class                                       JSString;

#ifdef JS_THREADSAFE
typedef struct PRCallOnceType    JSCallOnceType;
#else
typedef JSBool                   JSCallOnceType;
#endif
typedef JSBool                 (*JSInitCallback)(void);

namespace JS {
namespace shadow {

struct Runtime
{
    /* Restrict zone access during Minor GC. */
    bool needsBarrier_;

#ifdef JSGC_GENERATIONAL
    /* Allow inlining of Nursery::isInside. */
    uintptr_t gcNurseryStart_;
    uintptr_t gcNurseryEnd_;
#endif

    Runtime()
      : needsBarrier_(false)
#ifdef JSGC_GENERATIONAL
      , gcNurseryStart_(0)
      , gcNurseryEnd_(0)
#endif
    {}
};

} /* namespace shadow */
} /* namespace JS */

namespace js {

/*
 * Parallel operations in general can have one of three states. They may
 * succeed, fail, or "bail", where bail indicates that the code encountered an
 * unexpected condition and should be re-run sequentially. Different
 * subcategories of the "bail" state are encoded as variants of TP_RETRY_*.
 */
enum ParallelResult { TP_SUCCESS, TP_RETRY_SEQUENTIALLY, TP_RETRY_AFTER_GC, TP_FATAL };

struct ThreadSafeContext;
struct ForkJoinSlice;
class ExclusiveContext;

class Allocator;

class SkipRoot;

enum ThingRootKind
{
    THING_ROOT_OBJECT,
    THING_ROOT_SHAPE,
    THING_ROOT_BASE_SHAPE,
    THING_ROOT_TYPE_OBJECT,
    THING_ROOT_STRING,
    THING_ROOT_ION_CODE,
    THING_ROOT_SCRIPT,
    THING_ROOT_ID,
    THING_ROOT_PROPERTY_ID,
    THING_ROOT_VALUE,
    THING_ROOT_TYPE,
    THING_ROOT_BINDINGS,
    THING_ROOT_PROPERTY_DESCRIPTOR,
    THING_ROOT_LIMIT
};

template <typename T>
struct RootKind;

/*
 * Specifically mark the ThingRootKind of externally visible types, so that
 * JSAPI users may use JSRooted... types without having the class definition
 * available.
 */
template<typename T, ThingRootKind Kind>
struct SpecificRootKind
{
    static ThingRootKind rootKind() { return Kind; }
};

template <> struct RootKind<JSObject *> : SpecificRootKind<JSObject *, THING_ROOT_OBJECT> {};
template <> struct RootKind<JSFlatString *> : SpecificRootKind<JSFlatString *, THING_ROOT_STRING> {};
template <> struct RootKind<JSFunction *> : SpecificRootKind<JSFunction *, THING_ROOT_OBJECT> {};
template <> struct RootKind<JSString *> : SpecificRootKind<JSString *, THING_ROOT_STRING> {};
template <> struct RootKind<JSScript *> : SpecificRootKind<JSScript *, THING_ROOT_SCRIPT> {};
template <> struct RootKind<jsid> : SpecificRootKind<jsid, THING_ROOT_ID> {};
template <> struct RootKind<JS::Value> : SpecificRootKind<JS::Value, THING_ROOT_VALUE> {};

struct ContextFriendFields
{
  protected:
    JSRuntime *const     runtime_;

    /* The current compartment. */
    JSCompartment       *compartment_;

    /* The current zone. */
    JS::Zone            *zone_;

  public:
    explicit ContextFriendFields(JSRuntime *rt)
      : runtime_(rt), compartment_(NULL), zone_(NULL), autoGCRooters(NULL)
    {
#ifdef JSGC_TRACK_EXACT_ROOTS
        mozilla::PodArrayZero(thingGCRooters);
#endif
#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
        skipGCRooters = NULL;
#endif
    }

    static const ContextFriendFields *get(const JSContext *cx) {
        return reinterpret_cast<const ContextFriendFields *>(cx);
    }

    static ContextFriendFields *get(JSContext *cx) {
        return reinterpret_cast<ContextFriendFields *>(cx);
    }

#ifdef JSGC_TRACK_EXACT_ROOTS
    /*
     * Stack allocated GC roots for stack GC heap pointers, which may be
     * overwritten if moved during a GC.
     */
    JS::Rooted<void*> *thingGCRooters[THING_ROOT_LIMIT];
#endif

#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
    /*
     * Stack allocated list of stack locations which hold non-relocatable
     * GC heap pointers (where the target is rooted somewhere else) or integer
     * values which may be confused for GC heap pointers. These are used to
     * suppress false positives which occur when a rooting analysis treats the
     * location as holding a relocatable pointer, but have no other effect on
     * GC behavior.
     */
    SkipRoot *skipGCRooters;
#endif

    /* Stack of thread-stack-allocated GC roots. */
    JS::AutoGCRooter   *autoGCRooters;

    friend JSRuntime *GetRuntime(const JSContext *cx);
    friend JSCompartment *GetContextCompartment(const JSContext *cx);
    friend JS::Zone *GetContextZone(const JSContext *cx);
};

class PerThreadData;

struct PerThreadDataFriendFields
{
  private:
    // Note: this type only exists to permit us to derive the offset of
    // the perThread data within the real JSRuntime* type in a portable
    // way.
    struct RuntimeDummy : JS::shadow::Runtime
    {
        struct PerThreadDummy {
            void *field1;
            uintptr_t field2;
#ifdef DEBUG
            uint64_t field3;
#endif
        } mainThread;
    };

  public:

    PerThreadDataFriendFields();

#ifdef JSGC_TRACK_EXACT_ROOTS
    /*
     * Stack allocated GC roots for stack GC heap pointers, which may be
     * overwritten if moved during a GC.
     */
    JS::Rooted<void*> *thingGCRooters[THING_ROOT_LIMIT];
#endif

#if defined(DEBUG) && defined(JS_GC_ZEAL) && defined(JSGC_ROOT_ANALYSIS) && !defined(JS_THREADSAFE)
    /*
     * Stack allocated list of stack locations which hold non-relocatable
     * GC heap pointers (where the target is rooted somewhere else) or integer
     * values which may be confused for GC heap pointers. These are used to
     * suppress false positives which occur when a rooting analysis treats the
     * location as holding a relocatable pointer, but have no other effect on
     * GC behavior.
     */
    SkipRoot *skipGCRooters;
#endif

    /* Limit pointer for checking native stack consumption. */
    uintptr_t nativeStackLimit;

    static const size_t RuntimeMainThreadOffset = offsetof(RuntimeDummy, mainThread);

    static inline PerThreadDataFriendFields *get(js::PerThreadData *pt) {
        return reinterpret_cast<PerThreadDataFriendFields *>(pt);
    }

    static inline PerThreadDataFriendFields *getMainThread(JSRuntime *rt) {
        // mainThread must always appear directly after |JS::shadow::Runtime|.
        // Tested by a JS_STATIC_ASSERT in |jsfriendapi.cpp|
        return reinterpret_cast<PerThreadDataFriendFields *>(
            reinterpret_cast<char*>(rt) + RuntimeMainThreadOffset);
    }

    static inline const PerThreadDataFriendFields *getMainThread(const JSRuntime *rt) {
        // mainThread must always appear directly after |JS::shadow::Runtime|.
        // Tested by a JS_STATIC_ASSERT in |jsfriendapi.cpp|
        return reinterpret_cast<const PerThreadDataFriendFields *>(
            reinterpret_cast<const char*>(rt) + RuntimeMainThreadOffset);
    }
};

} /* namespace js */

#endif /* jspubtd_h */
