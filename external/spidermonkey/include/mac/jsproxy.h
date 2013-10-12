/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
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
class JS_FRIEND_API(BaseProxyHandler)
{
    void *mFamily;
    bool mHasPrototype;
    bool mHasPolicy;
  protected:
    // Subclasses may set this in their constructor.
    void setHasPrototype(bool aHasPrototype) { mHasPrototype = aHasPrototype; }
    void setHasPolicy(bool aHasPolicy) { mHasPolicy = aHasPolicy; }

  public:
    explicit BaseProxyHandler(void *family);
    virtual ~BaseProxyHandler();

    bool hasPrototype() {
        return mHasPrototype;
    }

    bool hasPolicy() {
        return mHasPolicy;
    }

    inline void *family() {
        return mFamily;
    }

    virtual bool isOuterWindow() {
        return false;
    }

    virtual bool finalizeInBackground(Value priv) {
        /*
         * Called on creation of a proxy to determine whether its finalize
         * method can be finalized on the background thread.
         */
        return true;
    }

    /* Policy enforcement traps.
     *
     * enter() allows the policy to specify whether the caller may perform |act|
     * on the proxy's |id| property. In the case when |act| is CALL, |id| is
     * generally JSID_VOID.
     *
     * The |act| parameter to enter() specifies the action being performed.
     * If |bp| is false, the trap suggests that the caller throw (though it
     * may still decide to squelch the error).
     */
    enum Action {
        GET,
        SET,
        CALL
    };
    virtual bool enter(JSContext *cx, HandleObject wrapper, HandleId id, Action act,
                       bool *bp);

    /* ES5 Harmony fundamental proxy traps. */
    virtual bool preventExtensions(JSContext *cx, HandleObject proxy) = 0;
    virtual bool getPropertyDescriptor(JSContext *cx, HandleObject proxy, HandleId id,
                                       PropertyDescriptor *desc, unsigned flags) = 0;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, HandleObject proxy,
                                          HandleId id, PropertyDescriptor *desc,
                                          unsigned flags) = 0;
    virtual bool defineProperty(JSContext *cx, HandleObject proxy, HandleId id,
                                PropertyDescriptor *desc) = 0;
    virtual bool getOwnPropertyNames(JSContext *cx, HandleObject proxy,
                                     AutoIdVector &props) = 0;
    virtual bool delete_(JSContext *cx, HandleObject proxy, HandleId id, bool *bp) = 0;
    virtual bool enumerate(JSContext *cx, HandleObject proxy, AutoIdVector &props) = 0;

    /* ES5 Harmony derived proxy traps. */
    virtual bool has(JSContext *cx, HandleObject proxy, HandleId id, bool *bp);
    virtual bool hasOwn(JSContext *cx, HandleObject proxy, HandleId id, bool *bp);
    virtual bool get(JSContext *cx, HandleObject proxy, HandleObject receiver,
                     HandleId id, MutableHandleValue vp);
    virtual bool set(JSContext *cx, HandleObject proxy, HandleObject receiver,
                     HandleId id, bool strict, MutableHandleValue vp);
    virtual bool keys(JSContext *cx, HandleObject proxy, AutoIdVector &props);
    virtual bool iterate(JSContext *cx, HandleObject proxy, unsigned flags,
                         MutableHandleValue vp);

    /* Spidermonkey extensions. */
    virtual bool isExtensible(JSObject *proxy) = 0;
    virtual bool call(JSContext *cx, HandleObject proxy, const CallArgs &args);
    virtual bool construct(JSContext *cx, HandleObject proxy, const CallArgs &args);
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl, CallArgs args);
    virtual bool hasInstance(JSContext *cx, HandleObject proxy, MutableHandleValue v, bool *bp);
    virtual bool objectClassIs(HandleObject obj, ESClassValue classValue, JSContext *cx);
    virtual const char *className(JSContext *cx, HandleObject proxy);
    virtual JSString *fun_toString(JSContext *cx, HandleObject proxy, unsigned indent);
    virtual bool regexp_toShared(JSContext *cx, HandleObject proxy, RegExpGuard *g);
    virtual bool defaultValue(JSContext *cx, HandleObject obj, JSType hint, MutableHandleValue vp);
    virtual void finalize(JSFreeOp *fop, JSObject *proxy);
    virtual bool getElementIfPresent(JSContext *cx, HandleObject obj, HandleObject receiver,
                                     uint32_t index, MutableHandleValue vp, bool *present);
    virtual bool getPrototypeOf(JSContext *cx, HandleObject proxy, MutableHandleObject protop);

    /* See comment for weakmapKeyDelegateOp in jsclass.h. */
    virtual JSObject *weakmapKeyDelegate(JSObject *proxy);
};

/*
 * DirectProxyHandler includes a notion of a target object. All traps are
 * reimplemented such that they forward their behavior to the target. This
 * allows consumers of this class to forward to another object as transparently
 * and efficiently as possible.
 */
class JS_PUBLIC_API(DirectProxyHandler) : public BaseProxyHandler
{
  public:
    explicit DirectProxyHandler(void *family);

    /* ES5 Harmony fundamental proxy traps. */
    virtual bool preventExtensions(JSContext *cx, HandleObject proxy) MOZ_OVERRIDE;
    virtual bool getPropertyDescriptor(JSContext *cx, HandleObject proxy, HandleId id,
                                       PropertyDescriptor *desc, unsigned flags) MOZ_OVERRIDE;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, HandleObject proxy,
                                          HandleId id, PropertyDescriptor *desc,
                                          unsigned flags) MOZ_OVERRIDE;
    virtual bool defineProperty(JSContext *cx, HandleObject proxy, HandleId id,
                                PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyNames(JSContext *cx, HandleObject proxy,
                                     AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool delete_(JSContext *cx, HandleObject proxy, HandleId id,
                         bool *bp) MOZ_OVERRIDE;
    virtual bool enumerate(JSContext *cx, HandleObject proxy,
                           AutoIdVector &props) MOZ_OVERRIDE;

    /* ES5 Harmony derived proxy traps. */
    virtual bool has(JSContext *cx, HandleObject proxy, HandleId id,
                     bool *bp) MOZ_OVERRIDE;
    virtual bool hasOwn(JSContext *cx, HandleObject proxy, HandleId id,
                        bool *bp) MOZ_OVERRIDE;
    virtual bool get(JSContext *cx, HandleObject proxy, HandleObject receiver,
                     HandleId id, MutableHandleValue vp) MOZ_OVERRIDE;
    virtual bool set(JSContext *cx, HandleObject proxy, HandleObject receiver,
                     HandleId id, bool strict, MutableHandleValue vp) MOZ_OVERRIDE;
    virtual bool keys(JSContext *cx, HandleObject proxy,
                      AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool iterate(JSContext *cx, HandleObject proxy, unsigned flags,
                         MutableHandleValue vp) MOZ_OVERRIDE;

    /* Spidermonkey extensions. */
    virtual bool isExtensible(JSObject *proxy) MOZ_OVERRIDE;
    virtual bool call(JSContext *cx, HandleObject proxy, const CallArgs &args) MOZ_OVERRIDE;
    virtual bool construct(JSContext *cx, HandleObject proxy, const CallArgs &args) MOZ_OVERRIDE;
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl,
                            CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, HandleObject proxy, MutableHandleValue v,
                             bool *bp) MOZ_OVERRIDE;
    virtual bool objectClassIs(HandleObject obj, ESClassValue classValue,
                               JSContext *cx) MOZ_OVERRIDE;
    virtual const char *className(JSContext *cx, HandleObject proxy) MOZ_OVERRIDE;
    virtual JSString *fun_toString(JSContext *cx, HandleObject proxy,
                                   unsigned indent) MOZ_OVERRIDE;
    virtual bool regexp_toShared(JSContext *cx, HandleObject proxy,
                                 RegExpGuard *g) MOZ_OVERRIDE;
    virtual bool defaultValue(JSContext *cx, HandleObject obj, JSType hint,
                              MutableHandleValue vp) MOZ_OVERRIDE;
    virtual JSObject *weakmapKeyDelegate(JSObject *proxy);
};

/* Dispatch point for handlers that executes the appropriate C++ or scripted traps. */
class Proxy
{
  public:
    /* ES5 Harmony fundamental proxy traps. */
    static bool preventExtensions(JSContext *cx, HandleObject proxy);
    static bool getPropertyDescriptor(JSContext *cx, HandleObject proxy, HandleId id,
                                      PropertyDescriptor *desc, unsigned flags);
    static bool getPropertyDescriptor(JSContext *cx, HandleObject proxy, unsigned flags, HandleId id,
                                      MutableHandleValue vp);
    static bool getOwnPropertyDescriptor(JSContext *cx, HandleObject proxy, HandleId id,
                                         PropertyDescriptor *desc, unsigned flags);
    static bool getOwnPropertyDescriptor(JSContext *cx, HandleObject proxy, unsigned flags, HandleId id,
                                         MutableHandleValue vp);
    static bool defineProperty(JSContext *cx, HandleObject proxy, HandleId id, PropertyDescriptor *desc);
    static bool defineProperty(JSContext *cx, HandleObject proxy, HandleId id, HandleValue v);
    static bool getOwnPropertyNames(JSContext *cx, HandleObject proxy, AutoIdVector &props);
    static bool delete_(JSContext *cx, HandleObject proxy, HandleId id, bool *bp);
    static bool enumerate(JSContext *cx, HandleObject proxy, AutoIdVector &props);

    /* ES5 Harmony derived proxy traps. */
    static bool has(JSContext *cx, HandleObject proxy, HandleId id, bool *bp);
    static bool hasOwn(JSContext *cx, HandleObject proxy, HandleId id, bool *bp);
    static bool get(JSContext *cx, HandleObject proxy, HandleObject receiver, HandleId id,
                    MutableHandleValue vp);
    static bool getElementIfPresent(JSContext *cx, HandleObject proxy, HandleObject receiver,
                                    uint32_t index, MutableHandleValue vp, bool *present);
    static bool set(JSContext *cx, HandleObject proxy, HandleObject receiver, HandleId id,
                    bool strict, MutableHandleValue vp);
    static bool keys(JSContext *cx, HandleObject proxy, AutoIdVector &props);
    static bool iterate(JSContext *cx, HandleObject proxy, unsigned flags, MutableHandleValue vp);

    /* Spidermonkey extensions. */
    static bool isExtensible(JSObject *proxy);
    static bool call(JSContext *cx, HandleObject proxy, const CallArgs &args);
    static bool construct(JSContext *cx, HandleObject proxy, const CallArgs &args);
    static bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl, CallArgs args);
    static bool hasInstance(JSContext *cx, HandleObject proxy, MutableHandleValue v, bool *bp);
    static bool objectClassIs(HandleObject obj, ESClassValue classValue, JSContext *cx);
    static const char *className(JSContext *cx, HandleObject proxy);
    static JSString *fun_toString(JSContext *cx, HandleObject proxy, unsigned indent);
    static bool regexp_toShared(JSContext *cx, HandleObject proxy, RegExpGuard *g);
    static bool defaultValue(JSContext *cx, HandleObject obj, JSType hint, MutableHandleValue vp);
    static bool getPrototypeOf(JSContext *cx, HandleObject proxy, MutableHandleObject protop);

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

inline bool IsObjectProxy(JSObject *obj)
{
    return IsObjectProxyClass(GetObjectClass(obj));
}

inline bool IsFunctionProxy(JSObject *obj)
{
    return IsFunctionProxyClass(GetObjectClass(obj));
}

inline bool IsProxy(JSObject *obj)
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
GetProxyHandler(JSObject *obj)
{
    JS_ASSERT(IsProxy(obj));
    return (BaseProxyHandler *) GetReservedSlot(obj, JSSLOT_PROXY_HANDLER).toPrivate();
}

inline const Value &
GetProxyPrivate(JSObject *obj)
{
    JS_ASSERT(IsProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_PRIVATE);
}

inline JSObject *
GetProxyTargetObject(JSObject *obj)
{
    JS_ASSERT(IsProxy(obj));
    return GetProxyPrivate(obj).toObjectOrNull();
}

inline const Value &
GetProxyExtra(JSObject *obj, size_t n)
{
    JS_ASSERT(IsProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_EXTRA + n);
}

inline void
SetProxyHandler(JSObject *obj, BaseProxyHandler *handler)
{
    JS_ASSERT(IsProxy(obj));
    SetReservedSlot(obj, JSSLOT_PROXY_HANDLER, PrivateValue(handler));
}

inline void
SetProxyExtra(JSObject *obj, size_t n, const Value &extra)
{
    JS_ASSERT(IsProxy(obj));
    JS_ASSERT(n <= 1);
    SetReservedSlot(obj, JSSLOT_PROXY_EXTRA + n, extra);
}

enum ProxyCallable {
    ProxyNotCallable = false,
    ProxyIsCallable = true
};

JS_FRIEND_API(JSObject *)
NewProxyObject(JSContext *cx, BaseProxyHandler *handler, const Value &priv,
               JSObject *proto, JSObject *parent, ProxyCallable callable = ProxyNotCallable);

JSObject *
RenewProxyObject(JSContext *cx, JSObject *obj, BaseProxyHandler *handler, Value priv);

class JS_FRIEND_API(AutoEnterPolicy)
{
  public:
    typedef BaseProxyHandler::Action Action;
    AutoEnterPolicy(JSContext *cx, BaseProxyHandler *handler,
                    HandleObject wrapper, HandleId id, Action act, bool mayThrow)
#ifdef DEBUG
        : context(NULL)
#endif
    {
        allow = handler->hasPolicy() ? handler->enter(cx, wrapper, id, act, &rv)
                                     : true;
        recordEnter(cx, wrapper, id);
        // We want to throw an exception if all of the following are true:
        // * The policy disallowed access.
        // * The policy set rv to false, indicating that we should throw.
        // * The caller did not instruct us to ignore exceptions.
        // * The policy did not throw itself.
        if (!allow && !rv && mayThrow && !JS_IsExceptionPending(cx))
            reportError(cx, id);
    }

    virtual ~AutoEnterPolicy() { recordLeave(); }
    inline bool allowed() { return allow; }
    inline bool returnValue() { JS_ASSERT(!allowed()); return rv; }

  protected:
    // no-op constructor for subclass
    AutoEnterPolicy()
#ifdef DEBUG
        : context(NULL)
#endif
        {};
    void reportError(JSContext *cx, jsid id);
    bool allow;
    bool rv;

#ifdef DEBUG
    JSContext *context;
    mozilla::Maybe<HandleObject> enteredProxy;
    mozilla::Maybe<HandleId> enteredId;
    // NB: We explicitly don't track the entered action here, because sometimes
    // SET traps do an implicit GET during their implementation, leading to
    // spurious assertions.
    AutoEnterPolicy *prev;
    void recordEnter(JSContext *cx, HandleObject proxy, HandleId id);
    void recordLeave();

    friend JS_FRIEND_API(void) assertEnteredPolicy(JSContext *cx, JSObject *proxy, jsid id);
#else
    inline void recordEnter(JSContext *cx, JSObject *proxy, jsid id) {}
    inline void recordLeave() {}
#endif

};

#ifdef DEBUG
class JS_FRIEND_API(AutoWaivePolicy) : public AutoEnterPolicy {
public:
    AutoWaivePolicy(JSContext *cx, HandleObject proxy, HandleId id)
    {
        allow = true;
        recordEnter(cx, proxy, id);
    }
};
#else
class JS_FRIEND_API(AutoWaivePolicy) {
    public: AutoWaivePolicy(JSContext *cx, HandleObject proxy, HandleId id) {};
};
#endif

} /* namespace js */

extern JS_FRIEND_API(JSObject *)
js_InitProxyClass(JSContext *cx, JSHandleObject obj);

#endif
