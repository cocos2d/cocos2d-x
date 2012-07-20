/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=79 ft=cpp:
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
 * The Original Code is SpiderMonkey JavaScript engine.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

class SpecialId {
    uintptr_t bits;

    /* Needs access to raw bits. */
    friend JS_ALWAYS_INLINE jsid SPECIALID_TO_JSID(const SpecialId &sid);

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

/* js::Class operation signatures. */

typedef JSBool
(* LookupGenericOp)(JSContext *cx, JSObject *obj, jsid id, JSObject **objp,
                    JSProperty **propp);
typedef JSBool
(* LookupPropOp)(JSContext *cx, JSObject *obj, PropertyName *name, JSObject **objp,
                 JSProperty **propp);
typedef JSBool
(* LookupElementOp)(JSContext *cx, JSObject *obj, uint32_t index, JSObject **objp,
                    JSProperty **propp);
typedef JSBool
(* LookupSpecialOp)(JSContext *cx, JSObject *obj, SpecialId sid, JSObject **objp,
                    JSProperty **propp);
typedef JSBool
(* DefineGenericOp)(JSContext *cx, JSObject *obj, jsid id, const Value *value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* DefinePropOp)(JSContext *cx, JSObject *obj, PropertyName *name, const Value *value,
                 PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* DefineElementOp)(JSContext *cx, JSObject *obj, uint32_t index, const Value *value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* DefineSpecialOp)(JSContext *cx, JSObject *obj, SpecialId sid, const Value *value,
                    PropertyOp getter, StrictPropertyOp setter, unsigned attrs);
typedef JSBool
(* GenericIdOp)(JSContext *cx, JSObject *obj, JSObject *receiver, jsid id, Value *vp);
typedef JSBool
(* PropertyIdOp)(JSContext *cx, JSObject *obj, JSObject *receiver, PropertyName *name, Value *vp);
typedef JSBool
(* ElementIdOp)(JSContext *cx, JSObject *obj, JSObject *receiver, uint32_t index, Value *vp);
typedef JSBool
(* ElementIfPresentOp)(JSContext *cx, JSObject *obj, JSObject *receiver, uint32_t index, Value *vp, bool* present);
typedef JSBool
(* SpecialIdOp)(JSContext *cx, JSObject *obj, JSObject *receiver, SpecialId sid, Value *vp);
typedef JSBool
(* StrictGenericIdOp)(JSContext *cx, JSObject *obj, jsid id, Value *vp, JSBool strict);
typedef JSBool
(* StrictPropertyIdOp)(JSContext *cx, JSObject *obj, PropertyName *name, Value *vp, JSBool strict);
typedef JSBool
(* StrictElementIdOp)(JSContext *cx, JSObject *obj, uint32_t index, Value *vp, JSBool strict);
typedef JSBool
(* StrictSpecialIdOp)(JSContext *cx, JSObject *obj, SpecialId sid, Value *vp, JSBool strict);
typedef JSBool
(* GenericAttributesOp)(JSContext *cx, JSObject *obj, jsid id, unsigned *attrsp);
typedef JSBool
(* PropertyAttributesOp)(JSContext *cx, JSObject *obj, PropertyName *name, unsigned *attrsp);
typedef JSBool
(* ElementAttributesOp)(JSContext *cx, JSObject *obj, uint32_t index, unsigned *attrsp);
typedef JSBool
(* SpecialAttributesOp)(JSContext *cx, JSObject *obj, SpecialId sid, unsigned *attrsp);
typedef JSBool
(* DeletePropertyOp)(JSContext *cx, JSObject *obj, PropertyName *name, Value *vp, JSBool strict);
typedef JSBool
(* DeleteElementOp)(JSContext *cx, JSObject *obj, uint32_t index, Value *vp, JSBool strict);
typedef JSBool
(* DeleteSpecialOp)(JSContext *cx, JSObject *obj, SpecialId sid, Value *vp, JSBool strict);
typedef JSType
(* TypeOfOp)(JSContext *cx, JSObject *obj);

/*
 * Prepare to make |obj| non-extensible; in particular, fully resolve its properties.
 * On error, return false.
 * If |obj| is now ready to become non-extensible, set |*fixed| to true and return true.
 * If |obj| refuses to become non-extensible, set |*fixed| to false and return true; the
 * caller will throw an appropriate error.
 */
typedef JSBool
(* FixOp)(JSContext *cx, JSObject *obj, bool *fixed, AutoIdVector *props);

typedef JSObject *
(* ObjectOp)(JSContext *cx, JSObject *obj);
typedef void
(* FinalizeOp)(JSContext *cx, JSObject *obj);

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
    JSFinalizeOp        finalize;                                             \
                                                                              \
    /* Optionally non-null members start here. */                             \
    JSCheckAccessOp     checkAccess;                                          \
    JSNative            call;                                                 \
    JSNative            construct;                                            \
    JSHasInstanceOp     hasInstance;                                          \
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
    FixOp               fix;
    ObjectOp            thisObject;
    FinalizeOp          clear;
};

#define JS_NULL_OBJECT_OPS                                                    \
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,   \
     NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,        \
     NULL,NULL,NULL,NULL,NULL,NULL}

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
    ESClass_Array, ESClass_Number, ESClass_String, ESClass_Boolean, ESClass_RegExp
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

#endif  /* __cplusplus */

#endif  /* jsclass_h__ */
