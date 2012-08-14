/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
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

#ifndef jspubtd_h___
#define jspubtd_h___
/*
 * JS public API typedefs.
 */
#include "jstypes.h"
#include "jscompat.h"
#include "jsval.h"

JS_BEGIN_EXTERN_C

/* Scalar typedefs. */
typedef JSInt32   jsint;
typedef JSUint32  jsuint;
typedef float64   jsdouble;
typedef JSInt32   jsrefcount;   /* PRInt32 if JS_THREADSAFE, see jslock.h */

#ifdef WIN32
typedef wchar_t   jschar;
#else
typedef JSUint16  jschar;
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
    JSACC_PARENT = 1,           /* XXXbe redundant w.r.t. id */

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

/* Struct typedefs. */
typedef struct JSClass           JSClass;
typedef struct JSConstDoubleSpec JSConstDoubleSpec;
typedef struct JSContext         JSContext;
typedef struct JSErrorReport     JSErrorReport;
typedef struct JSFunction        JSFunction;
typedef struct JSFunctionSpec    JSFunctionSpec;
typedef struct JSTracer          JSTracer;
typedef struct JSIdArray         JSIdArray;
typedef struct JSPropertyDescriptor JSPropertyDescriptor;
typedef struct JSPropertySpec    JSPropertySpec;
typedef struct JSObjectMap       JSObjectMap;
typedef struct JSRuntime         JSRuntime;
typedef struct JSStackFrame      JSStackFrame;
typedef struct JSXDRState        JSXDRState;
typedef struct JSExceptionState  JSExceptionState;
typedef struct JSLocaleCallbacks JSLocaleCallbacks;
typedef struct JSSecurityCallbacks JSSecurityCallbacks;
typedef struct JSONParser        JSONParser;
typedef struct JSCompartment     JSCompartment;
typedef struct JSCrossCompartmentCall JSCrossCompartmentCall;
typedef struct JSStructuredCloneWriter JSStructuredCloneWriter;
typedef struct JSStructuredCloneReader JSStructuredCloneReader;
typedef struct JSStructuredCloneCallbacks JSStructuredCloneCallbacks;

#ifdef __cplusplus
typedef class JSWrapper          JSWrapper;
typedef class JSCrossCompartmentWrapper JSCrossCompartmentWrapper;
#endif

/* JSClass (and js::ObjectOps where appropriate) function pointer typedefs. */

/*
 * Add, delete, or get a property named by id in obj.  Note the jsid id
 * type -- id may be a string (Unicode property identifier) or an int (element
 * index).  The *vp out parameter, on success, is the new property value after
 * an add or get.  After a successful delete, *vp is JSVAL_FALSE iff
 * obj[id] can't be deleted (because it's permanent).
 */
typedef JSBool
(* JSPropertyOp)(JSContext *cx, JSObject *obj, jsid id, jsval *vp);

/*
 * Set a property named by id in obj, treating the assignment as strict
 * mode code if strict is true. Note the jsid id type -- id may be a string
 * (Unicode property identifier) or an int (element index). The *vp out
 * parameter, on success, is the new property value after the
 * set.
 */
typedef JSBool
(* JSStrictPropertyOp)(JSContext *cx, JSObject *obj, jsid id, JSBool strict, jsval *vp);

/*
 * This function type is used for callbacks that enumerate the properties of
 * a JSObject.  The behavior depends on the value of enum_op:
 *
 *  JSENUMERATE_INIT
 *    A new, opaque iterator state should be allocated and stored in *statep.
 *    (You can use PRIVATE_TO_JSVAL() to tag the pointer to be stored).
 *
 *    The number of properties that will be enumerated should be returned as
 *    an integer jsval in *idp, if idp is non-null, and provided the number of
 *    enumerable properties is known.  If idp is non-null and the number of
 *    enumerable properties can't be computed in advance, *idp should be set
 *    to JSVAL_ZERO.
 *
 *  JSENUMERATE_INIT_ALL
 *    Used identically to JSENUMERATE_INIT, but exposes all properties of the
 *    object regardless of enumerability.
 *
 *  JSENUMERATE_NEXT
 *    A previously allocated opaque iterator state is passed in via statep.
 *    Return the next jsid in the iteration using *idp.  The opaque iterator
 *    state pointed at by statep is destroyed and *statep is set to JSVAL_NULL
 *    if there are no properties left to enumerate.
 *
 *  JSENUMERATE_DESTROY
 *    Destroy the opaque iterator state previously allocated in *statep by a
 *    call to this function when enum_op was JSENUMERATE_INIT or
 *    JSENUMERATE_INIT_ALL.
 *
 * The return value is used to indicate success, with a value of JS_FALSE
 * indicating failure.
 */
typedef JSBool
(* JSNewEnumerateOp)(JSContext *cx, JSObject *obj, JSIterateOp enum_op,
                     jsval *statep, jsid *idp);

/*
 * The old-style JSClass.enumerate op should define all lazy properties not
 * yet reflected in obj.
 */
typedef JSBool
(* JSEnumerateOp)(JSContext *cx, JSObject *obj);

/*
 * Resolve a lazy property named by id in obj by defining it directly in obj.
 * Lazy properties are those reflected from some peer native property space
 * (e.g., the DOM attributes for a given node reflected as obj) on demand.
 *
 * JS looks for a property in an object, and if not found, tries to resolve
 * the given id.  If resolve succeeds, the engine looks again in case resolve
 * defined obj[id].  If no such property exists directly in obj, the process
 * is repeated with obj's prototype, etc.
 *
 * NB: JSNewResolveOp provides a cheaper way to resolve lazy properties.
 */
typedef JSBool
(* JSResolveOp)(JSContext *cx, JSObject *obj, jsid id);

/*
 * Like JSResolveOp, but flags provide contextual information as follows:
 *
 *  JSRESOLVE_QUALIFIED   a qualified property id: obj.id or obj[id], not id
 *  JSRESOLVE_ASSIGNING   obj[id] is on the left-hand side of an assignment
 *  JSRESOLVE_DETECTING   'if (o.p)...' or similar detection opcode sequence
 *  JSRESOLVE_DECLARING   var, const, or function prolog declaration opcode
 *  JSRESOLVE_CLASSNAME   class name used when constructing
 *
 * The *objp out parameter, on success, should be null to indicate that id
 * was not resolved; and non-null, referring to obj or one of its prototypes,
 * if id was resolved.
 *
 * This hook instead of JSResolveOp is called via the JSClass.resolve member
 * if JSCLASS_NEW_RESOLVE is set in JSClass.flags.
 *
 * Setting JSCLASS_NEW_RESOLVE and JSCLASS_NEW_RESOLVE_GETS_START further
 * extends this hook by passing in the starting object on the prototype chain
 * via *objp.  Thus a resolve hook implementation may define the property id
 * being resolved in the object in which the id was first sought, rather than
 * in a prototype object whose class led to the resolve hook being called.
 *
 * When using JSCLASS_NEW_RESOLVE_GETS_START, the resolve hook must therefore
 * null *objp to signify "not resolved".  With only JSCLASS_NEW_RESOLVE and no
 * JSCLASS_NEW_RESOLVE_GETS_START, the hook can assume *objp is null on entry.
 * This is not good practice, but enough existing hook implementations count
 * on it that we can't break compatibility by passing the starting object in
 * *objp without a new JSClass flag.
 */
typedef JSBool
(* JSNewResolveOp)(JSContext *cx, JSObject *obj, jsid id, uintN flags,
                   JSObject **objp);

/*
 * Convert obj to the given type, returning true with the resulting value in
 * *vp on success, and returning false on error or exception.
 */
typedef JSBool
(* JSConvertOp)(JSContext *cx, JSObject *obj, JSType type, jsval *vp);

/*
 * Delegate typeof to an object so it can cloak a primitive or another object.
 */
typedef JSType
(* JSTypeOfOp)(JSContext *cx, JSObject *obj);

/*
 * Finalize obj, which the garbage collector has determined to be unreachable
 * from other live objects or from GC roots.  Obviously, finalizers must never
 * store a reference to obj.
 */
typedef void
(* JSFinalizeOp)(JSContext *cx, JSObject *obj);

/*
 * Used by JS_AddExternalStringFinalizer and JS_RemoveExternalStringFinalizer
 * to extend and reduce the set of string types finalized by the GC.
 */
typedef void
(* JSStringFinalizeOp)(JSContext *cx, JSString *str);

/*
 * JSClass.checkAccess type: check whether obj[id] may be accessed per mode,
 * returning false on error/exception, true on success with obj[id]'s last-got
 * value in *vp, and its attributes in *attrsp.  As for JSPropertyOp above, id
 * is either a string or an int jsval.
 */
typedef JSBool
(* JSCheckAccessOp)(JSContext *cx, JSObject *obj, jsid id, JSAccessMode mode,
                    jsval *vp);

/*
 * Encode or decode an object, given an XDR state record representing external
 * data.  See jsxdrapi.h.
 */
typedef JSBool
(* JSXDRObjectOp)(JSXDRState *xdr, JSObject **objp);

/*
 * Check whether v is an instance of obj.  Return false on error or exception,
 * true on success with JS_TRUE in *bp if v is an instance of obj, JS_FALSE in
 * *bp otherwise.
 */
typedef JSBool
(* JSHasInstanceOp)(JSContext *cx, JSObject *obj, const jsval *v, JSBool *bp);

/*
 * Deprecated function type for JSClass.mark. All new code should define
 * JSTraceOp instead to ensure the traversal of traceable things stored in
 * the native structures.
 */
typedef uint32
(* JSMarkOp)(JSContext *cx, JSObject *obj, void *arg);

/*
 * Function type for trace operation of the class called to enumerate all
 * traceable things reachable from obj's private data structure. For each such
 * thing, a trace implementation must call
 *
 *    JS_CallTracer(trc, thing, kind);
 *
 * or one of its convenience macros as described in jsapi.h.
 *
 * JSTraceOp implementation can assume that no other threads mutates object
 * state. It must not change state of the object or corresponding native
 * structures. The only exception for this rule is the case when the embedding
 * needs a tight integration with GC. In that case the embedding can check if
 * the traversal is a part of the marking phase through calling
 * JS_IsGCMarkingTracer and apply a special code like emptying caches or
 * marking its native structures.
 *
 * To define the tracer for a JSClass, the implementation must add
 * JSCLASS_MARK_IS_TRACE to class flags and use JS_CLASS_TRACE(method)
 * macro below to convert JSTraceOp to JSMarkOp when initializing or
 * assigning JSClass.mark field.
 */
typedef void
(* JSTraceOp)(JSTracer *trc, JSObject *obj);

#if defined __GNUC__ && __GNUC__ >= 4 && !defined __cplusplus
# define JS_CLASS_TRACE(method)                                               \
    (__builtin_types_compatible_p(JSTraceOp, __typeof(&(method)))             \
     ? (JSMarkOp)(method)                                                     \
     : js_WrongTypeForClassTracer)

extern JSMarkOp js_WrongTypeForClassTracer;

#else
# define JS_CLASS_TRACE(method) ((JSMarkOp)(method))
#endif

/*
 * Tracer callback, called for each traceable thing directly referenced by a
 * particular object or runtime structure. It is the callback responsibility
 * to ensure the traversal of the full object graph via calling eventually
 * JS_TraceChildren on the passed thing. In this case the callback must be
 * prepared to deal with cycles in the traversal graph.
 *
 * kind argument is one of JSTRACE_OBJECT, JSTRACE_STRING or a tag denoting
 * internal implementation-specific traversal kind. In the latter case the only
 * operations on thing that the callback can do is to call JS_TraceChildren or
 * DEBUG-only JS_PrintTraceThingInfo.
 */
typedef void
(* JSTraceCallback)(JSTracer *trc, void *thing, uint32 kind);

/*
 * DEBUG only callback that JSTraceOp implementation can provide to return
 * a string describing the reference traced with JS_CallTracer.
 */
typedef void
(* JSTraceNamePrinter)(JSTracer *trc, char *buf, size_t bufsize);

typedef JSBool
(* JSEqualityOp)(JSContext *cx, JSObject *obj, const jsval *v, JSBool *bp);

/*
 * Typedef for native functions called by the JS VM.
 *
 * See jsapi.h, the JS_CALLEE, JS_THIS, etc. macros.
 */

typedef JSBool
(* JSNative)(JSContext *cx, uintN argc, jsval *vp);

/* Callbacks and their arguments. */

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
typedef JSBool
(* JSContextCallback)(JSContext *cx, uintN contextOp);

#ifndef JS_THREADSAFE
typedef void
(* JSHeartbeatCallback)(JSRuntime *rt);
#endif

typedef enum JSGCStatus {
    JSGC_BEGIN,
    JSGC_END,
    JSGC_MARK_END,
    JSGC_FINALIZE_END
} JSGCStatus;

typedef JSBool
(* JSGCCallback)(JSContext *cx, JSGCStatus status);

/*
 * Generic trace operation that calls JS_CallTracer on each traceable thing
 * stored in data.
 */
typedef void
(* JSTraceDataOp)(JSTracer *trc, void *data);

typedef JSBool
(* JSOperationCallback)(JSContext *cx);

typedef void
(* JSErrorReporter)(JSContext *cx, const char *message, JSErrorReport *report);

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
    /* The error format string (UTF-8 if js_CStringsAreUTF8). */
    const char *format;

    /* The number of arguments to expand in the formatted error message. */
    uint16 argCount;

    /* One of the JSExnType constants above. */
    int16 exnType;
} JSErrorFormatString;

typedef const JSErrorFormatString *
(* JSErrorCallback)(void *userRef, const char *locale,
                    const uintN errorNumber);

#ifdef va_start
#define JS_ARGUMENT_FORMATTER_DEFINED 1

typedef JSBool
(* JSArgumentFormatter)(JSContext *cx, const char *format, JSBool fromJS,
                        jsval **vpp, va_list *app);
#endif

typedef JSBool
(* JSLocaleToUpperCase)(JSContext *cx, JSString *src, jsval *rval);

typedef JSBool
(* JSLocaleToLowerCase)(JSContext *cx, JSString *src, jsval *rval);

typedef JSBool
(* JSLocaleCompare)(JSContext *cx, JSString *src1, JSString *src2,
                    jsval *rval);

typedef JSBool
(* JSLocaleToUnicode)(JSContext *cx, const char *src, jsval *rval);

/*
 * Security protocol types.
 */
typedef struct JSPrincipals JSPrincipals;

/*
 * XDR-encode or -decode a principals instance, based on whether xdr->mode is
 * JSXDR_ENCODE, in which case *principalsp should be encoded; or JSXDR_DECODE,
 * in which case implementations must return a held (via JSPRINCIPALS_HOLD),
 * non-null *principalsp out parameter.  Return true on success, false on any
 * error, which the implementation must have reported.
 */
typedef JSBool
(* JSPrincipalsTranscoder)(JSXDRState *xdr, JSPrincipals **principalsp);

/*
 * Return a weak reference to the principals associated with obj, possibly via
 * the immutable parent chain leading from obj to a top-level container (e.g.,
 * a window object in the DOM level 0).  If there are no principals associated
 * with obj, return null.  Therefore null does not mean an error was reported;
 * in no event should an error be reported or an exception be thrown by this
 * callback's implementation.
 */
typedef JSPrincipals *
(* JSObjectPrincipalsFinder)(JSContext *cx, JSObject *obj);

/*
 * Used to check if a CSP instance wants to disable eval() and friends.
 * See js_CheckCSPPermitsJSAction() in jsobj.
 */
typedef JSBool
(* JSCSPEvalChecker)(JSContext *cx);

/*
 * Callback used to ask the embedding for the cross compartment wrapper handler
 * that implements the desired prolicy for this kind of object in the
 * destination compartment.
 */
typedef JSObject *
(* JSWrapObjectCallback)(JSContext *cx, JSObject *obj, JSObject *proto, JSObject *parent,
                         uintN flags);

/*
 * Callback used by the wrap hook to ask the embedding to prepare an object
 * for wrapping in a context. This might include unwrapping other wrappers
 * or even finding a more suitable object for the new compartment.
 */
typedef JSObject *
(* JSPreWrapCallback)(JSContext *cx, JSObject *scope, JSObject *obj, uintN flags);

typedef enum {
    JSCOMPARTMENT_NEW, /* XXX Does it make sense to have a NEW? */
    JSCOMPARTMENT_DESTROY
} JSCompartmentOp;

typedef JSBool
(* JSCompartmentCallback)(JSContext *cx, JSCompartment *compartment, uintN compartmentOp);

/*
 * Read structured data from the reader r. This hook is used to read a value
 * previously serialized by a call to the WriteStructuredCloneOp hook.
 *
 * tag and data are the pair of uint32 values from the header. The callback may
 * use the JS_Read* APIs to read any other relevant parts of the object from
 * the reader r. closure is any value passed to the JS_ReadStructuredClone
 * function. Return the new object on success, NULL on error/exception.
 */
typedef JSObject *(*ReadStructuredCloneOp)(JSContext *cx, JSStructuredCloneReader *r,
                                           uint32 tag, uint32 data, void *closure);

/*
 * Structured data serialization hook. The engine can write primitive values,
 * Objects, Arrays, Dates, RegExps, TypedArrays, and ArrayBuffers. Any other
 * type of object requires application support. This callback must first use
 * the JS_WriteUint32Pair API to write an object header, passing a value
 * greater than JS_SCTAG_USER to the tag parameter. Then it can use the
 * JS_Write* APIs to write any other relevant parts of the value v to the
 * writer w. closure is any value passed to the JS_WriteStructuredCLone function.
 *
 * Return true on success, false on error/exception.
 */
typedef JSBool (*WriteStructuredCloneOp)(JSContext *cx, JSStructuredCloneWriter *w,
                                         JSObject *obj, void *closure);

/*
 * This is called when JS_WriteStructuredClone finds that the object to be
 * written is recursive. To follow HTML5, the application must throw a
 * DATA_CLONE_ERR DOMException. errorid is always JS_SCERR_RECURSION.
 */
typedef void (*StructuredCloneErrorOp)(JSContext *cx, uint32 errorid);

JS_END_EXTERN_C

#endif /* jspubtd_h___ */
