/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jspubtd_h___
#define jspubtd_h___

/*
 * JS public API typedefs.
 */
#include "jstypes.h"

/*
 * Allow headers to reference JS::Value without #including the whole jsapi.h.
 * Unfortunately, typedefs (hence jsval) cannot be declared.
 */
#ifdef __cplusplus
namespace JS { class Value; }
#endif

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
#ifdef __cplusplus

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
#else  /* defined(__cplusplus) */
typedef ptrdiff_t jsid;
# define JSID_BITS(id) (id)
#endif

JS_BEGIN_EXTERN_C

#ifdef WIN32
typedef wchar_t   jschar;
#else
typedef uint16_t  jschar;
#endif

/*
 * Run-time version enumeration.  See jsversion.h for compile-time counterparts
 * to these values that may be selected by the JS_VERSION macro, and tested by
 * #if expressions.
 */
typedef enum JSVersion {
    JSVERSION_1_0     = 100,
    JSVERSION_1_1     = 110,
    JSVERSION_1_2     = 120,
    JSVERSION_1_3     = 130,
    JSVERSION_1_4     = 140,
    JSVERSION_ECMA_3  = 148,
    JSVERSION_1_5     = 150,
    JSVERSION_1_6     = 160,
    JSVERSION_1_7     = 170,
    JSVERSION_1_8     = 180,
    JSVERSION_ECMA_5  = 185,
    JSVERSION_DEFAULT = 0,
    JSVERSION_UNKNOWN = -1,
    JSVERSION_LATEST  = JSVERSION_ECMA_5
} JSVersion;

#define JSVERSION_IS_ECMA(version) \
    ((version) == JSVERSION_DEFAULT || (version) >= JSVERSION_1_3)

/* Result of typeof operator enumeration. */
typedef enum JSType {
    JSTYPE_VOID,                /* undefined */
    JSTYPE_OBJECT,              /* object */
    JSTYPE_FUNCTION,            /* function */
    JSTYPE_STRING,              /* string */
    JSTYPE_NUMBER,              /* number */
    JSTYPE_BOOLEAN,             /* boolean */
    JSTYPE_NULL,                /* null */
    JSTYPE_XML,                 /* xml object */
    JSTYPE_LIMIT
} JSType;

/* Dense index into cached prototypes and class atoms for standard objects. */
typedef enum JSProtoKey {
#define JS_PROTO(name,code,init) JSProto_##name = code,
#include "jsproto.tbl"
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
     * Trace kinds internal to the engine. The embedding can only them if it
     * implements JSTraceCallback.
     */
#if JS_HAS_XML_SUPPORT
    JSTRACE_XML,
#endif
    JSTRACE_SHAPE,
    JSTRACE_BASE_SHAPE,
    JSTRACE_TYPE_OBJECT,
    JSTRACE_LAST = JSTRACE_TYPE_OBJECT
} JSGCTraceKind;

/* Struct typedefs. */
typedef struct JSClass                      JSClass;
typedef struct JSCompartment                JSCompartment;
typedef struct JSConstDoubleSpec            JSConstDoubleSpec;
typedef struct JSContext                    JSContext;
typedef struct JSCrossCompartmentCall       JSCrossCompartmentCall;
typedef struct JSErrorReport                JSErrorReport;
typedef struct JSExceptionState             JSExceptionState;
typedef struct JSFunction                   JSFunction;
typedef struct JSFunctionSpec               JSFunctionSpec;
typedef struct JSIdArray                    JSIdArray;
typedef struct JSLocaleCallbacks            JSLocaleCallbacks;
typedef struct JSObject                     JSObject;
typedef struct JSObjectMap                  JSObjectMap;
typedef struct JSPrincipals                 JSPrincipals;
typedef struct JSPropertyDescriptor         JSPropertyDescriptor;
typedef struct JSPropertyName               JSPropertyName;
typedef struct JSPropertySpec               JSPropertySpec;
typedef struct JSRuntime                    JSRuntime;
typedef struct JSSecurityCallbacks          JSSecurityCallbacks;
typedef struct JSStackFrame                 JSStackFrame;
typedef struct JSScript          JSScript;
typedef struct JSStructuredCloneCallbacks   JSStructuredCloneCallbacks;
typedef struct JSStructuredCloneReader      JSStructuredCloneReader;
typedef struct JSStructuredCloneWriter      JSStructuredCloneWriter;
typedef struct JSTracer                     JSTracer;

#ifdef __cplusplus
class                                       JSFlatString;
class                                       JSString;
#else
typedef struct JSFlatString                 JSFlatString;
typedef struct JSString                     JSString;
#endif /* !__cplusplus */

#ifdef JS_THREADSAFE
typedef struct PRCallOnceType    JSCallOnceType;
#else
typedef JSBool                   JSCallOnceType;
#endif
typedef JSBool                 (*JSInitCallback)(void);

JS_END_EXTERN_C

#ifdef __cplusplus

namespace JS {

template <typename T>
class Rooted;

class SkipRoot;

enum ThingRootKind
{
    THING_ROOT_OBJECT,
    THING_ROOT_SHAPE,
    THING_ROOT_BASE_SHAPE,
    THING_ROOT_TYPE_OBJECT,
    THING_ROOT_STRING,
    THING_ROOT_SCRIPT,
    THING_ROOT_XML,
    THING_ROOT_ID,
    THING_ROOT_PROPERTY_ID,
    THING_ROOT_VALUE,
    THING_ROOT_TYPE,
    THING_ROOT_LIMIT
};

struct ContextFriendFields {
    JSRuntime *const    runtime;

    ContextFriendFields(JSRuntime *rt)
      : runtime(rt) { }

    static const ContextFriendFields *get(const JSContext *cx) {
        return reinterpret_cast<const ContextFriendFields *>(cx);
    }

    static ContextFriendFields *get(JSContext *cx) {
        return reinterpret_cast<ContextFriendFields *>(cx);
    }

#if defined(JSGC_ROOT_ANALYSIS) || defined(JSGC_USE_EXACT_ROOTING)
    /*
     * Stack allocated GC roots for stack GC heap pointers, which may be
     * overwritten if moved during a GC.
     */
    Rooted<void*> *thingGCRooters[THING_ROOT_LIMIT];
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
};

} /* namespace JS */

#endif /* __cplusplus */

#endif /* jspubtd_h___ */
