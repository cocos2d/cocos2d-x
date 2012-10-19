/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=79 ft=cpp:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsclass_h__
#define jsclass_h__
/*
 * A JSClass acts as a vtable for JS objects that allows JSAPI clients to
 * control various aspects of the behavior of an object like property lookup.
 * js::Class is an engine-private extension that allows more control over
 * object behavior and, e.g., allows custom slow layout.
 */
#include "jsapi.h"
#include "jsprvtd.h"

#ifdef __cplusplus

namespace js {

class PropertyName;
class SpecialId;
class PropertyId;

static JS_ALWAYS_INLINE jsid
SPECIALID_TO_JSID(const SpecialId &sid);

/*
 * We partition the ways to refer to a property into three: by an index
 * (uint32_t); by a string whose characters do not represent an index
 * (PropertyName, see vm/String.h); and by various special values.
 *
 * Special values are encoded using SpecialId, which is layout-compatible but
 * non-interconvertible with jsid.  A SpecialId may be: an object (used by E4X
 * and perhaps eventually by Harmony-proposed private names); JSID_VOID, which
 * does not occur in JS scripts but may be used to indicate the absence of a
 * valid identifier; or JS_DEFAULT_XML_NAMESPACE_ID, if E4X is enabled.
 */
class SpecialId
{
    uintptr_t bits;

    /* Needs access to raw bits. */
    friend JS_ALWAYS_INLINE jsid SPECIALID_TO_JSID(const SpecialId &sid);
    friend class PropertyId;

    static const uintptr_t TYPE_VOID = JSID_TYPE_VOID;
    static const uintptr_t TYPE_OBJECT = JSID_TYPE_OBJECT;
    static const uintptr_t TYPE_DEFAULT_XML_NAMESPACE = JSID_TYPE_DEFAULT_XML_NAMESPACE;
    static const uintptr_t TYPE_MASK = JSID_TYPE_MASK;

    SpecialId(uintptr_t bits) : bits(bits) { }

  public:
    SpecialId() : bits(TYPE_VOID) { }

    /* Object-valued */

    SpecialId(JSObject &obj)
      : bits(uintptr_t(&obj) | TYPE_OBJECT)
    {
        JS_ASSERT(&obj != NULL);
        JS_ASSERT((uintptr_t(&obj) & TYPE_MASK) == 0);
    }

    bool isObject() const {
        return (bits & TYPE_MASK) == TYPE_OBJECT && bits != TYPE_OBJECT;
    }

    JSObject *toObject() const {
        JS_ASSERT(isObject());
        return reinterpret_cast<JSObject *>(bits & ~TYPE_MASK);
    }

    /* Empty */

    static SpecialId empty() {
        SpecialId sid(TYPE_OBJECT);
        JS_ASSERT(sid.isEmpty());
        return sid;
    }

    bool isEmpty() const {
        return bits == TYPE_OBJECT;
    }

    /* Void */

    static SpecialId voidId() {
        SpecialId sid(TYPE_VOID);
        JS_ASSERT(sid.isVoid());
        return sid;
    }

    bool isVoid() const {
        return bits == TYPE_VOID;
    }

    /* Default XML namespace */

    static SpecialId defaultXMLNamespace() {
        SpecialId sid(TYPE_DEFAULT_XML_NAMESPACE);
        JS_ASSERT(sid.isDefaultXMLNamespace());
        return sid;
    }

    bool isDefaultXMLNamespace() const {
        return bits == TYPE_DEFAULT_XML_NAMESPACE;
    }
};

static JS_ALWAYS_INLINE jsid
SPECIALID_TO_JSID(const SpecialId &sid)
{
    jsid id;
    JSID_BITS(id) = sid.bits;
    JS_ASSERT_IF(sid.isObject(), JSID_IS_OBJECT(id) && JSID_TO_OBJECT(id) == sid.toObject());
    JS_ASSERT_IF(sid.isVoid(), JSID_IS_VOID(id));
    JS_ASSERT_IF(sid.isEmpty(), JSID_IS_EMPTY(id));
    JS_ASSERT_IF(sid.isDefaultXMLNamespace(), JSID_IS_DEFAULT_XML_NAMESPACE(id));
    return id;
}

static JS_ALWAYS_INLINE bool
JSID_IS_SPECIAL(jsid id)
{
    return JSID_IS_OBJECT(id) || JSID_IS_EMPTY(id) || JSID_IS_VOID(id) ||
           JSID_IS_DEFAULT_XML_NAMESPACE(id);
}

static JS_ALWAYS_INLINE SpecialId
JSID_TO_SPECIALID(jsid id)
{
    JS_ASSERT(JSID_IS_SPECIAL(id));
    if (JSID_IS_OBJECT(id))
        return SpecialId(*JSID_TO_OBJECT(id));
    if (JSID_IS_EMPTY(id))
        return SpecialId::empty();
    if (JSID_IS_VOID(id))
        return SpecialId::voidId();
    JS_ASSERT(JSID_IS_DEFAULT_XML_NAMESPACE(id));
    return SpecialId::defaultXMLNamespace();
}

typedef JS::Handle<SpecialId> HandleSpecialId;

/* js::Class operation signatures. */

typedef JSBool
(* LookupGenericOp)(JSContext *cx, HandleObject obj, HandleId id,
                    MutableHandleObject objp, MutableHandleShape propp);
typedef JSBool
(* LookupPropOp)(JSContext *cx, HandleObject obj, HandlePropertyName name,
                 MutableHandleObject objp, MutableHandleShape propp);
typedef JSBool
(* LookupElementOp)(JSContext *cx, HandleObject obj, uint32_t index,
                    MutableHandleObject objp, MutableHandleShape propp);
typedef JSBool
(* LookupSpecialOp)(JSContext *cx, HandleObject obj, HandleSpecialId sid,
                    MutableHandleObject objp, MutableHandleShape propp);
typedef JSBool
(* DefineGenericOp)(JSContext *cx, HandleObject obj, HandleId id, const Value *value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* DefinePropOp)(JSContext *cx, HandleObject obj, HandlePropertyName name, const Value *value,
                 PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* DefineElementOp)(JSContext *cx, HandleObject obj, uint32_t index, const Value *value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* DefineSpecialOp)(JSContext *cx, HandleObject obj, HandleSpecialId sid, const Value *value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* GenericIdOp)(JSContext *cx, HandleObject obj, HandleObject receiver, HandleId id, Value *vp);
typedef JSBool
(* PropertyIdOp)(JSContext *cx, HandleObject obj, HandleObject receiver, HandlePropertyName name, Value *vp);
typedef JSBool
(* ElementIdOp)(JSContext *cx, HandleObject obj, HandleObject receiver, uint32_t index, Value *vp);
typedef JSBool
(* ElementIfPresentOp)(JSContext *cx, HandleObject obj, HandleObject receiver, uint32_t index, Value *vp, bool* present);
typedef JSBool
(* SpecialIdOp)(JSContext *cx, HandleObject obj, HandleObject receiver, HandleSpecialId sid, Value *vp);
typedef JSBool
(* StrictGenericIdOp)(JSContext *cx, HandleObject obj, HandleId id, Value *vp, JSBool strict);
typedef JSBool
(* StrictPropertyIdOp)(JSContext *cx, HandleObject obj, HandlePropertyName name, Value *vp, JSBool strict);
typedef JSBool
(* StrictElementIdOp)(JSContext *cx, HandleObject obj, uint32_t index, Value *vp, JSBool strict);
typedef JSBool
(* StrictSpecialIdOp)(JSContext *cx, HandleObject obj, HandleSpecialId sid, Value *vp, JSBool strict);
typedef JSBool
(* GenericAttributesOp)(JSContext *cx, HandleObject obj, HandleId id, unsigned *attrsp);
typedef JSBool
(* PropertyAttributesOp)(JSContext *cx, HandleObject obj, HandlePropertyName name, unsigned *attrsp);
typedef JSBool
(* ElementAttributesOp)(JSContext *cx, HandleObject obj, uint32_t index, unsigned *attrsp);
typedef JSBool
(* SpecialAttributesOp)(JSContext *cx, HandleObject obj, HandleSpecialId sid, unsigned *attrsp);
typedef JSBool
(* DeletePropertyOp)(JSContext *cx, HandleObject obj, HandlePropertyName name, Value *vp, JSBool strict);
typedef JSBool
(* DeleteElementOp)(JSContext *cx, HandleObject obj, uint32_t index, Value *vp, JSBool strict);
typedef JSBool
(* DeleteSpecialOp)(JSContext *cx, HandleObject obj, HandleSpecialId sid, Value *vp, JSBool strict);
typedef JSType
(* TypeOfOp)(JSContext *cx, HandleObject obj);

typedef JSObject *
(* ObjectOp)(JSContext *cx, HandleObject obj);
typedef void
(* ClearOp)(JSContext *cx, HandleObject obj);
typedef void
(* FinalizeOp)(FreeOp *fop, JSObject *obj);

#define JS_CLASS_MEMBERS                                                      \
    const char          *name;                                                \
    uint32_t            flags;                                                \
                                                                              \
    /* Mandatory non-null function pointer members. */                        \
    JSPropertyOp        addProperty;                                          \
    JSPropertyOp        delProperty;                                          \
    JSPropertyOp        getProperty;                                          \
    JSStrictPropertyOp  setProperty;                                          \
    JSEnumerateOp       enumerate;                                            \
    JSResolveOp         resolve;                                              \
    JSConvertOp         convert;                                              \
    FinalizeOp          finalize;                                             \
                                                                              \
    /* Optionally non-null members start here. */                             \
    JSCheckAccessOp     checkAccess;                                          \
    JSNative            call;                                                 \
    JSHasInstanceOp     hasInstance;                                          \
    JSNative            construct;                                            \
    JSTraceOp           trace

/*
 * The helper struct to measure the size of JS_CLASS_MEMBERS to know how much
 * we have to padd js::Class to match the size of JSClass;
 */
struct ClassSizeMeasurement
{
    JS_CLASS_MEMBERS;
};

struct ClassExtension
{
    JSEqualityOp        equality;
    JSObjectOp          outerObject;
    JSObjectOp          innerObject;
    JSIteratorOp        iteratorObject;
    void               *unused;

    /*
     * isWrappedNative is true only if the class is an XPCWrappedNative.
     * WeakMaps use this to override the wrapper disposal optimization.
     */
    bool                isWrappedNative;
};

#define JS_NULL_CLASS_EXT   {NULL,NULL,NULL,NULL,NULL,false}

struct ObjectOps
{
    LookupGenericOp     lookupGeneric;
    LookupPropOp        lookupProperty;
    LookupElementOp     lookupElement;
    LookupSpecialOp     lookupSpecial;
    DefineGenericOp     defineGeneric;
    DefinePropOp        defineProperty;
    DefineElementOp     defineElement;
    DefineSpecialOp     defineSpecial;
    GenericIdOp         getGeneric;
    PropertyIdOp        getProperty;
    ElementIdOp         getElement;
    ElementIfPresentOp  getElementIfPresent; /* can be null */
    SpecialIdOp         getSpecial;
    StrictGenericIdOp   setGeneric;
    StrictPropertyIdOp  setProperty;
    StrictElementIdOp   setElement;
    StrictSpecialIdOp   setSpecial;
    GenericAttributesOp getGenericAttributes;
    PropertyAttributesOp getPropertyAttributes;
    ElementAttributesOp getElementAttributes;
    SpecialAttributesOp getSpecialAttributes;
    GenericAttributesOp setGenericAttributes;
    PropertyAttributesOp setPropertyAttributes;
    ElementAttributesOp setElementAttributes;
    SpecialAttributesOp setSpecialAttributes;
    DeletePropertyOp    deleteProperty;
    DeleteElementOp     deleteElement;
    DeleteSpecialOp     deleteSpecial;

    JSNewEnumerateOp    enumerate;
    TypeOfOp            typeOf;
    ObjectOp            thisObject;
    ClearOp             clear;
};

#define JS_NULL_OBJECT_OPS                                                    \
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,   \
     NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,        \
     NULL,NULL,NULL,NULL,NULL}

struct Class
{
    JS_CLASS_MEMBERS;
    ClassExtension      ext;
    ObjectOps           ops;
    uint8_t             pad[sizeof(JSClass) - sizeof(ClassSizeMeasurement) -
                            sizeof(ClassExtension) - sizeof(ObjectOps)];

    /* Class is not native and its map is not a scope. */
    static const uint32_t NON_NATIVE = JSCLASS_INTERNAL_FLAG2;

    bool isNative() const {
        return !(flags & NON_NATIVE);
    }

    bool hasPrivate() const {
        return !!(flags & JSCLASS_HAS_PRIVATE);
    }
};

JS_STATIC_ASSERT(offsetof(JSClass, name) == offsetof(Class, name));
JS_STATIC_ASSERT(offsetof(JSClass, flags) == offsetof(Class, flags));
JS_STATIC_ASSERT(offsetof(JSClass, addProperty) == offsetof(Class, addProperty));
JS_STATIC_ASSERT(offsetof(JSClass, delProperty) == offsetof(Class, delProperty));
JS_STATIC_ASSERT(offsetof(JSClass, getProperty) == offsetof(Class, getProperty));
JS_STATIC_ASSERT(offsetof(JSClass, setProperty) == offsetof(Class, setProperty));
JS_STATIC_ASSERT(offsetof(JSClass, enumerate) == offsetof(Class, enumerate));
JS_STATIC_ASSERT(offsetof(JSClass, resolve) == offsetof(Class, resolve));
JS_STATIC_ASSERT(offsetof(JSClass, convert) == offsetof(Class, convert));
JS_STATIC_ASSERT(offsetof(JSClass, finalize) == offsetof(Class, finalize));
JS_STATIC_ASSERT(offsetof(JSClass, checkAccess) == offsetof(Class, checkAccess));
JS_STATIC_ASSERT(offsetof(JSClass, call) == offsetof(Class, call));
JS_STATIC_ASSERT(offsetof(JSClass, construct) == offsetof(Class, construct));
JS_STATIC_ASSERT(offsetof(JSClass, hasInstance) == offsetof(Class, hasInstance));
JS_STATIC_ASSERT(offsetof(JSClass, trace) == offsetof(Class, trace));
JS_STATIC_ASSERT(sizeof(JSClass) == sizeof(Class));

static JS_ALWAYS_INLINE JSClass *
Jsvalify(Class *c)
{
    return (JSClass *)c;
}
static JS_ALWAYS_INLINE const JSClass *
Jsvalify(const Class *c)
{
    return (const JSClass *)c;
}

static JS_ALWAYS_INLINE Class *
Valueify(JSClass *c)
{
    return (Class *)c;
}
static JS_ALWAYS_INLINE const Class *
Valueify(const JSClass *c)
{
    return (const Class *)c;
}

/*
 * Enumeration describing possible values of the [[Class]] internal property
 * value of objects.
 */
enum ESClassValue {
    ESClass_Array, ESClass_Number, ESClass_String, ESClass_Boolean,
    ESClass_RegExp, ESClass_ArrayBuffer
};

/*
 * Return whether the given object has the given [[Class]] internal property
 * value. Beware, this query says nothing about the js::Class of the JSObject
 * so the caller must not assume anything about obj's representation (e.g., obj
 * may be a proxy).
 */
inline bool
ObjectClassIs(JSObject &obj, ESClassValue classValue, JSContext *cx);

/* Just a helper that checks v.isObject before calling ObjectClassIs. */
inline bool
IsObjectWithClass(const Value &v, ESClassValue classValue, JSContext *cx);

}  /* namespace js */

namespace JS {

inline bool
IsPoisonedSpecialId(js::SpecialId iden)
{
    if (iden.isObject())
        return IsPoisonedPtr(iden.toObject());
    return false;
}

template <> struct RootMethods<js::SpecialId>
{
    static js::SpecialId initial() { return js::SpecialId(); }
    static ThingRootKind kind() { return THING_ROOT_ID; }
    static bool poisoned(js::SpecialId id) { return IsPoisonedSpecialId(id); }
};

} /* namespace JS */

#endif  /* __cplusplus */

#endif  /* jsclass_h__ */
