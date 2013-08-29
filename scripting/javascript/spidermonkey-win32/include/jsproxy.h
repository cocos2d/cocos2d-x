/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jsproxy_h___
#define jsproxy_h___

#include "jsapi.h"
#include "jsfriendapi.h"

namespace js {

class JS_FRIEND_API(Wrapper);

/*
 * A proxy is a JSObject that implements generic behavior by providing custom
 * implementations for each object trap. The implementation for each trap is
 * provided by a C++ object stored on the proxy, known as its handler.
 *
 * A major use case for proxies is to forward each trap to another object,
 * known as its target. The target can be an arbitrary C++ object. Not every
 * proxy has the notion of a target, however.
 *
 * Proxy traps are grouped into fundamental and derived traps. Every proxy has
 * to at least provide implementations for the fundamental traps, but the
 * derived traps can be implemented in terms of the fundamental ones
 * BaseProxyHandler provides implementations of the derived traps in terms of
 * the (pure virtual) fundamental traps.
 *
 * To minimize code duplication, a set of abstract proxy handler classes is
 * provided, from which other handlers may inherit. These abstract classes
 * are organized in the following hierarchy:
 *
 * BaseProxyHandler
 * |
 * DirectProxyHandler
 * |
 * Wrapper
 */

/*
 * BaseProxyHandler is the most generic kind of proxy handler. It does not make
 * any assumptions about the target. Consequently, it does not provide any
 * default implementation for the fundamental traps. It does, however, implement
 * the derived traps in terms of the fundamental ones. This allows consumers of
 * this class to define any custom behavior they want.
 */
class JS_FRIEND_API(BaseProxyHandler) {
    void *mFamily;
    bool mHasPrototype;
  protected:
    // Subclasses may set this in their constructor.
    void setHasPrototype(bool aHasPrototype) { mHasPrototype = aHasPrototype; }

  public:
    explicit BaseProxyHandler(void *family);
    virtual ~BaseProxyHandler();

    bool hasPrototype() {
        return mHasPrototype;
    }

    inline void *family() {
        return mFamily;
    }

    virtual bool isOuterWindow() {
        return false;
    }

    /* ES5 Harmony fundamental proxy traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id,
                                       PropertyDescriptor *desc, unsigned flags) = 0;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy,
                                          jsid id, PropertyDescriptor *desc, unsigned flags) = 0;
    virtual bool defineProperty(JSContext *cx, JSObject *proxy, jsid id,
                                PropertyDescriptor *desc) = 0;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *proxy,
                                     AutoIdVector &props) = 0;
    virtual bool delete_(JSContext *cx, JSObject *proxy, jsid id, bool *bp) = 0;
    virtual bool enumerate(JSContext *cx, JSObject *proxy,
                           AutoIdVector &props) = 0;

    /* ES5 Harmony derived proxy traps. */
    virtual bool has(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    virtual bool hasOwn(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    virtual bool get(JSContext *cx, JSObject *proxy, JSObject *receiver,
                     jsid id, Value *vp);
    virtual bool set(JSContext *cx, JSObject *proxy, JSObject *receiver,
                     jsid id, bool strict, Value *vp);
    virtual bool keys(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    virtual bool iterate(JSContext *cx, JSObject *proxy, unsigned flags,
                         Value *vp);

    /* Spidermonkey extensions. */
    virtual bool call(JSContext *cx, JSObject *proxy, unsigned argc, Value *vp);
    virtual bool construct(JSContext *cx, JSObject *proxy, unsigned argc, Value *argv, Value *rval);
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl, CallArgs args);
    virtual bool hasInstance(JSContext *cx, HandleObject proxy, MutableHandleValue v, bool *bp);
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx);
    virtual JSString *obj_toString(JSContext *cx, JSObject *proxy);
    virtual JSString *fun_toString(JSContext *cx, JSObject *proxy, unsigned indent);
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g);
    virtual bool defaultValue(JSContext *cx, JSObject *obj, JSType hint, Value *vp);
    virtual void finalize(JSFreeOp *fop, JSObject *proxy);
    virtual bool getElementIfPresent(JSContext *cx, JSObject *obj, JSObject *receiver,
                                     uint32_t index, Value *vp, bool *present);
    virtual bool getPrototypeOf(JSContext *cx, JSObject *proxy, JSObject **protop);

    /* See comment for weakmapKeyDelegateOp in jsclass.h. */
    virtual JSObject *weakmapKeyDelegate(JSObject *proxy);
};

/*
 * DirectProxyHandler includes a notion of a target object. All traps are
 * reimplemented such that they forward their behavior to the target. This
 * allows consumers of this class to forward to another object as transparently
 * and efficiently as possible.
 */
class JS_PUBLIC_API(DirectProxyHandler) : public BaseProxyHandler {
public:
    explicit DirectProxyHandler(void *family);

    /* ES5 Harmony fundamental proxy traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id,
                                       PropertyDescriptor *desc, unsigned flags) MOZ_OVERRIDE;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy,
                                          jsid id, PropertyDescriptor *desc,
                                          unsigned flags) MOZ_OVERRIDE;
    virtual bool defineProperty(JSContext *cx, JSObject *proxy, jsid id,
                                PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *proxy,
                                     AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool delete_(JSContext *cx, JSObject *proxy, jsid id,
                         bool *bp) MOZ_OVERRIDE;
    virtual bool enumerate(JSContext *cx, JSObject *proxy,
                           AutoIdVector &props) MOZ_OVERRIDE;

    /* ES5 Harmony derived proxy traps. */
    virtual bool has(JSContext *cx, JSObject *proxy, jsid id,
                     bool *bp) MOZ_OVERRIDE;
    virtual bool hasOwn(JSContext *cx, JSObject *proxy, jsid id,
                        bool *bp) MOZ_OVERRIDE;
    virtual bool get(JSContext *cx, JSObject *proxy, JSObject *receiver,
                     jsid id, Value *vp) MOZ_OVERRIDE;
    virtual bool set(JSContext *cx, JSObject *proxy, JSObject *receiver,
                     jsid id, bool strict, Value *vp) MOZ_OVERRIDE;
    virtual bool keys(JSContext *cx, JSObject *proxy,
                      AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool iterate(JSContext *cx, JSObject *proxy, unsigned flags,
                         Value *vp) MOZ_OVERRIDE;

    /* Spidermonkey extensions. */
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl,
                            CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, HandleObject proxy, MutableHandleValue v,
                             bool *bp) MOZ_OVERRIDE;
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue,
                               JSContext *cx) MOZ_OVERRIDE;
    virtual JSString *obj_toString(JSContext *cx, JSObject *proxy) MOZ_OVERRIDE;
    virtual JSString *fun_toString(JSContext *cx, JSObject *proxy,
                                   unsigned indent) MOZ_OVERRIDE;
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy,
                                 RegExpGuard *g) MOZ_OVERRIDE;
    virtual bool defaultValue(JSContext *cx, JSObject *obj, JSType hint,
                              Value *vp) MOZ_OVERRIDE;
    virtual JSObject *weakmapKeyDelegate(JSObject *proxy);
};

/* Dispatch point for handlers that executes the appropriate C++ or scripted traps. */
class Proxy {
  public:
    /* ES5 Harmony fundamental proxy traps. */
    static bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id,
                                      PropertyDescriptor *desc, unsigned flags);
    static bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, unsigned flags, jsid id,
                                      Value *vp);
    static bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id,
                                         PropertyDescriptor *desc, unsigned flags);
    static bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy, unsigned flags, jsid id,
                                         Value *vp);
    static bool defineProperty(JSContext *cx, JSObject *proxy, jsid id, PropertyDescriptor *desc);
    static bool defineProperty(JSContext *cx, JSObject *proxy, jsid id, const Value &v);
    static bool getOwnPropertyNames(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    static bool delete_(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    static bool enumerate(JSContext *cx, JSObject *proxy, AutoIdVector &props);

    /* ES5 Harmony derived proxy traps. */
    static bool has(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    static bool hasOwn(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    static bool get(JSContext *cx, HandleObject proxy, HandleObject receiver, HandleId id, MutableHandleValue vp);
    static bool getElementIfPresent(JSContext *cx, HandleObject proxy, HandleObject receiver,
                                    uint32_t index, MutableHandleValue vp, bool *present);
    static bool set(JSContext *cx, HandleObject proxy, HandleObject receiver, HandleId id, bool strict,
                    MutableHandleValue vp);
    static bool keys(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    static bool iterate(JSContext *cx, HandleObject proxy, unsigned flags, MutableHandleValue vp);

    /* Spidermonkey extensions. */
    static bool call(JSContext *cx, JSObject *proxy, unsigned argc, Value *vp);
    static bool construct(JSContext *cx, JSObject *proxy, unsigned argc, Value *argv, Value *rval);
    static bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl, CallArgs args);
    static bool hasInstance(JSContext *cx, HandleObject proxy, MutableHandleValue v, bool *bp);
    static bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx);
    static JSString *obj_toString(JSContext *cx, JSObject *proxy);
    static JSString *fun_toString(JSContext *cx, JSObject *proxy, unsigned indent);
    static bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g);
    static bool defaultValue(JSContext *cx, JSObject *obj, JSType hint, Value *vp);
    static bool getPrototypeOf(JSContext *cx, JSObject *proxy, JSObject **protop);

    static JSObject * const LazyProto;
};

inline bool IsObjectProxyClass(const Class *clasp)
{
    return clasp == &js::ObjectProxyClass || clasp == &js::OuterWindowProxyClass;
}

inline bool IsFunctionProxyClass(const Class *clasp)
{
    return clasp == &js::FunctionProxyClass;
}

inline bool IsObjectProxy(RawObject obj)
{
    return IsObjectProxyClass(GetObjectClass(obj));
}

inline bool IsFunctionProxy(RawObject obj)
{
    return IsFunctionProxyClass(GetObjectClass(obj));
}

inline bool IsProxy(RawObject obj)
{
    Class *clasp = GetObjectClass(obj);
    return IsObjectProxyClass(clasp) || IsFunctionProxyClass(clasp);
}

/* Shared between object and function proxies. */
/*
 * NOTE: JSSLOT_PROXY_PRIVATE is 0, because that way slot 0 is usable by API
 * clients for both proxy and non-proxy objects.  So an API client that only
 * needs to store one slot's worth of data doesn't need to branch on what sort
 * of object it has.
 */
const uint32_t JSSLOT_PROXY_PRIVATE = 0;
const uint32_t JSSLOT_PROXY_HANDLER = 1;
const uint32_t JSSLOT_PROXY_EXTRA   = 2;
/* Function proxies only. */
const uint32_t JSSLOT_PROXY_CALL = 4;
const uint32_t JSSLOT_PROXY_CONSTRUCT = 5;

inline BaseProxyHandler *
GetProxyHandler(RawObject obj)
{
    JS_ASSERT(IsProxy(obj));
    return (BaseProxyHandler *) GetReservedSlot(obj, JSSLOT_PROXY_HANDLER).toPrivate();
}

inline const Value &
GetProxyPrivate(RawObject obj)
{
    JS_ASSERT(IsProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_PRIVATE);
}

inline JSObject *
GetProxyTargetObject(RawObject obj)
{
    JS_ASSERT(IsProxy(obj));
    return GetProxyPrivate(obj).toObjectOrNull();
}

inline const Value &
GetProxyCall(RawObject obj)
{
    JS_ASSERT(IsFunctionProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_CALL);
}

inline const Value &
GetProxyExtra(RawObject obj, size_t n)
{
    JS_ASSERT(IsProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_EXTRA + n);
}

inline void
SetProxyHandler(RawObject obj, BaseProxyHandler *handler)
{
    JS_ASSERT(IsProxy(obj));
    SetReservedSlot(obj, JSSLOT_PROXY_HANDLER, PrivateValue(handler));
}

inline void
SetProxyPrivate(RawObject obj, const Value &value)
{
    JS_ASSERT(IsProxy(obj));
    SetReservedSlot(obj, JSSLOT_PROXY_PRIVATE, value);
}

inline void
SetProxyExtra(RawObject obj, size_t n, const Value &extra)
{
    JS_ASSERT(IsProxy(obj));
    JS_ASSERT(n <= 1);
    SetReservedSlot(obj, JSSLOT_PROXY_EXTRA + n, extra);
}

JS_FRIEND_API(JSObject *)
NewProxyObject(JSContext *cx, BaseProxyHandler *handler, const Value &priv,
               JSObject *proto, JSObject *parent,
               JSObject *call = NULL, JSObject *construct = NULL);

JSObject *
RenewProxyObject(JSContext *cx, JSObject *obj, BaseProxyHandler *handler, Value priv);

} /* namespace js */

extern JS_FRIEND_API(JSObject *)
js_InitProxyClass(JSContext *cx, JSHandleObject obj);

#endif
