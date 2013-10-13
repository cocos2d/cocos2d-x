/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsprvtd_h___
#define jsprvtd_h___
/*
 * JS private typename definitions.
 *
 * This header is included only in other .h files, for convenience and for
 * simplicity of type naming.  The alternative for structures is to use tags,
 * which are named the same as their typedef names (legal in C/C++, and less
 * noisy than suffixing the typedef name with "Struct" or "Str").  Instead,
 * all .h files that include this file may use the same typedef name, whether
 * declaring a pointer to struct type, or defining a member of struct type.
 *
 * A few fundamental scalar types are defined here too.  Neither the scalar
 * nor the struct typedefs should change much, therefore the nearly-global
 * make dependency induced by this file should not prove painful.
 */

#include "jsapi.h"
#include "jsutil.h"

#include "js/HashTable.h"
#include "js/Vector.h"

/*
 * Convenience constants.
 */
#define JS_BITS_PER_UINT32_LOG2 5
#define JS_BITS_PER_UINT32      32

/* The alignment required of objects stored in GC arenas. */
static const unsigned JS_GCTHING_ALIGN = 8;
static const unsigned JS_GCTHING_ZEROBITS = 3;

/* Scalar typedefs. */
typedef uint8_t     jsbytecode;
typedef uint8_t     jssrcnote;
typedef uintptr_t   jsatomid;

/* Struct typedefs. */
typedef struct JSGCThing            JSGCThing;
typedef struct JSGenerator          JSGenerator;
typedef struct JSNativeEnumerator   JSNativeEnumerator;
typedef struct JSTryNote            JSTryNote;

/* Friend "Advanced API" typedefs. */
typedef struct JSAtomState          JSAtomState;
typedef struct JSCodeSpec           JSCodeSpec;
typedef struct JSPrinter            JSPrinter;
typedef struct JSStackHeader        JSStackHeader;
typedef struct JSSubString          JSSubString;
typedef struct JSSpecializedNative  JSSpecializedNative;

/*
 * Template declarations.
 *
 * jsprvtd.h can be included in both C and C++ translation units. For C++, it
 * may possibly be wrapped in an extern "C" block which does not agree with
 * templates.
 */
class JSDependentString;
class JSExtensibleString;
class JSExternalString;
class JSLinearString;
class JSRope;
class JSAtom;
class JSWrapper;

namespace js {

struct ArgumentsData;
struct Class;

class RegExpGuard;
class RegExpObject;
class RegExpObjectBuilder;
class RegExpShared;
class RegExpStatics;
class MatchPairs;
class PropertyName;

enum RegExpFlag
{
    IgnoreCaseFlag  = 0x01,
    GlobalFlag      = 0x02,
    MultilineFlag   = 0x04,
    StickyFlag      = 0x08,

    NoFlags         = 0x00,
    AllFlags        = 0x0f
};

class ExecuteArgsGuard;
class InvokeFrameGuard;
class InvokeArgsGuard;
class StringBuffer;

class FrameRegs;
class StackFrame;
class StackSegment;
class StackSpace;
class ContextStack;
class ScriptFrameIter;

class Proxy;
class JS_FRIEND_API(BaseProxyHandler);
class JS_FRIEND_API(Wrapper);
class JS_FRIEND_API(CrossCompartmentWrapper);

class TempAllocPolicy;
class RuntimeAllocPolicy;

class GlobalObject;

template <typename K,
          typename V,
          size_t InlineElems>
class InlineMap;

class LifoAlloc;

class Shape;

class Breakpoint;
class BreakpointSite;
class Debugger;
class WatchpointMap;

/*
 * Env is the type of what ES5 calls "lexical environments" (runtime
 * activations of lexical scopes). This is currently just JSObject, and is
 * implemented by Call, Block, With, and DeclEnv objects, among others--but
 * environments and objects are really two different concepts.
 */
typedef JSObject Env;

typedef JSNative             Native;
typedef JSPropertyOp         PropertyOp;
typedef JSStrictPropertyOp   StrictPropertyOp;
typedef JSPropertyDescriptor PropertyDescriptor;

namespace frontend {

struct BytecodeEmitter;
struct Definition;
class FunctionBox;
class ObjectBox;
struct Token;
struct TokenPos;
class TokenStream;
class ParseMapPool;
struct ParseNode;

template <typename ParseHandler>
struct Parser;

} /* namespace frontend */

namespace analyze {

struct LifetimeVariable;
class LoopAnalysis;
class ScriptAnalysis;
class SlotValue;
class SSAValue;
class SSAUseChain;

} /* namespace analyze */

namespace types {

class TypeSet;
struct TypeCallsite;
struct TypeObject;
struct TypeCompartment;

} /* namespace types */

typedef JS::Handle<Shape*>             HandleShape;
typedef JS::Handle<types::TypeObject*> HandleTypeObject;
typedef JS::Handle<JSAtom*>            HandleAtom;
typedef JS::Handle<PropertyName*>      HandlePropertyName;

typedef JS::MutableHandle<Shape*>      MutableHandleShape;
typedef JS::MutableHandle<JSAtom*>     MutableHandleAtom;

typedef JS::Rooted<Shape*>             RootedShape;
typedef JS::Rooted<types::TypeObject*> RootedTypeObject;
typedef JS::Rooted<JSAtom*>            RootedAtom;
typedef JS::Rooted<PropertyName*>      RootedPropertyName;

enum XDRMode {
    XDR_ENCODE,
    XDR_DECODE
};

template <XDRMode mode>
class XDRState;

class FreeOp;

struct IdValuePair
{
    jsid id;
    Value value;

    IdValuePair() {}
    IdValuePair(jsid idArg)
      : id(idArg), value(UndefinedValue())
    {}
};

} /* namespace js */

namespace JSC {

class ExecutableAllocator;

} /* namespace JSC */

namespace WTF {

class BumpPointerAllocator;

} /* namespace WTF */

/* "Friend" types used by jscntxt.h and jsdbgapi.h. */
typedef enum JSTrapStatus {
    JSTRAP_ERROR,
    JSTRAP_CONTINUE,
    JSTRAP_RETURN,
    JSTRAP_THROW,
    JSTRAP_LIMIT
} JSTrapStatus;

typedef JSTrapStatus
(* JSTrapHandler)(JSContext *cx, JSScript *script, jsbytecode *pc, jsval *rval,
                  jsval closure);

typedef JSTrapStatus
(* JSInterruptHook)(JSContext *cx, JSScript *script, jsbytecode *pc, jsval *rval,
                    void *closure);

typedef JSTrapStatus
(* JSDebuggerHandler)(JSContext *cx, JSScript *script, jsbytecode *pc, jsval *rval,
                      void *closure);

typedef JSTrapStatus
(* JSThrowHook)(JSContext *cx, JSScript *script, jsbytecode *pc, jsval *rval,
                void *closure);

typedef JSBool
(* JSWatchPointHandler)(JSContext *cx, JSObject *obj, jsid id, jsval old,
                        jsval *newp, void *closure);

/* called just after script creation */
typedef void
(* JSNewScriptHook)(JSContext  *cx,
                    const char *filename,  /* URL of script */
                    unsigned   lineno,     /* first line */
                    JSScript   *script,
                    JSFunction *fun,
                    void       *callerdata);

/* called just before script destruction */
typedef void
(* JSDestroyScriptHook)(JSFreeOp *fop,
                        JSScript *script,
                        void     *callerdata);

typedef void
(* JSSourceHandler)(const char *filename, unsigned lineno, const jschar *str,
                    size_t length, void **listenerTSData, void *closure);

/* js::ObjectOps function pointer typedefs. */

/*
 * A generic type for functions mapping an object to another object, or null
 * if an error or exception was thrown on cx.
 */
typedef JSObject *
(* JSObjectOp)(JSContext *cx, JSHandleObject obj);

/* Signature for class initialization ops. */
typedef JSObject *
(* JSClassInitializerOp)(JSContext *cx, JSHandleObject obj);

/*
 * Hook that creates an iterator object for a given object. Returns the
 * iterator object or null if an error or exception was thrown on cx.
 */
typedef JSObject *
(* JSIteratorOp)(JSContext *cx, JSHandleObject obj, JSBool keysonly);


#endif /* jsprvtd_h___ */
