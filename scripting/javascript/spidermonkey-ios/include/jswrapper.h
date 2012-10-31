/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99:
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef jswrapper_h___
#define jswrapper_h___

#include "mozilla/Attributes.h"

#include "jsapi.h"
#include "jsproxy.h"

namespace js {

class DummyFrameGuard;

/*
 * A wrapper is essentially a proxy that restricts access to certain traps. The
 * way in which a wrapper restricts access to its traps depends on the
 * particular policy for that wrapper. To allow a wrapper's policy to be
 * customized, the Wrapper base class contains two functions, enter/leave, which
 * are called as a policy enforcement check before/after each trap is forwarded.
 *
 * To minimize code duplication, a set of abstract wrapper classes is
 * provided, from which other wrappers may inherit. These abstract classes are
 * organized in the following hierarchy:
 *
 * BaseProxyHandler Wrapper
 * |                    | |
 * IndirectProxyHandler | |
 * |                  | | |
 * |      IndirectWrapper |
 * |                      |
 * DirectProxyHandler     |
 *                  |     |
 *            DirectWrapper
 */
class JS_FRIEND_API(Wrapper)
{
    unsigned mFlags;

  public:
    enum Action {
        GET,
        SET,
        CALL,
        PUNCTURE
    };

    enum Flags {
        CROSS_COMPARTMENT = 1 << 0,
        LAST_USED_FLAG = CROSS_COMPARTMENT
    };

    typedef enum {
        PermitObjectAccess,
        PermitPropertyAccess,
        DenyAccess
    } Permission;

    static JSObject *New(JSContext *cx, JSObject *obj, JSObject *proto,
                         JSObject *parent, Wrapper *handler);

    static Wrapper *wrapperHandler(RawObject wrapper);

    static JSObject *wrappedObject(RawObject wrapper);

    explicit Wrapper(unsigned flags);

    unsigned flags() const {
        return mFlags;
    }

    /*
     * The function Wrapper::New takes a pointer to a Wrapper as the handler
     * object. It then passes it on to the function NewProxyObject, which
     * expects a pointer to a BaseProxyHandler as the handler object. We don't
     * want to change Wrapper::New to take a pointer to a BaseProxyHandler,
     * because that would allow the creation of wrappers with non-wrapper
     * handlers. Unfortunately, we can't inherit Wrapper from BaseProxyHandler,
     * since that would create a dreaded diamond, and we can't use dynamic_cast
     * to cast Wrapper to BaseProxyHandler, since that would require us to
     * compile with run time type information. Hence the need for this virtual
     * function.
     */
    virtual BaseProxyHandler *toBaseProxyHandler() = 0;

    /* Policy enforcement traps.
     *
     * enter() allows the policy to specify whether the caller may perform |act|
     * on the underlying object's |id| property. In the case when |act| is CALL,
     * |id| is generally JSID_VOID.
     *
     * The |act| parameter to enter() specifies the action being performed. GET,
     * SET, and CALL are self-explanatory, but PUNCTURE requires more
     * explanation:
     *
     * GET and SET allow for a very fine-grained security membrane, through
     * which access can be granted or denied on a per-property, per-object, and
     * per-action basis. Sometimes though, we just want to asks if we can access
     * _everything_ behind the wrapper barrier. For example, when the structured
     * clone algorithm runs up against a cross-compartment wrapper, it needs to
     * know whether it can enter the compartment and keep cloning, or whether it
     * should throw. This is the role of PUNCTURE.
     *
     * PUNCTURE allows the policy to specify whether the wrapper barrier may
     * be lifted - that is to say, whether the caller is allowed to access
     * anything that the wrapped object could access. This is a very powerful
     * permission, and thus should generally be denied for security wrappers
     * except under very special circumstances. When |act| is PUNCTURE, |id|
     * should be JSID_VOID.
     */
    virtual bool enter(JSContext *cx, JSObject *wrapper, jsid id, Action act,
                       bool *bp);
};

/*
 * IndirectWrapper forwards its traps by forwarding them to
 * IndirectProxyHandler. In effect, IndirectWrapper behaves the same as
 * IndirectProxyHandler, except that it adds policy enforcement checks to each
 * fundamental trap.
 */
class JS_FRIEND_API(IndirectWrapper) : public Wrapper,
                                       public IndirectProxyHandler
{
  public:
    explicit IndirectWrapper(unsigned flags);

    virtual BaseProxyHandler* toBaseProxyHandler() {
        return this;
    }

    virtual Wrapper *toWrapper() {
        return this;
    }

    /* ES5 Harmony fundamental wrapper traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *wrapper,
                                       jsid id, bool set,
                                       PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *wrapper,
                                          jsid id, bool set,
                                          PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool defineProperty(JSContext *cx, JSObject *wrapper, jsid id,
                                PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *wrapper,
                                     AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool delete_(JSContext *cx, JSObject *wrapper, jsid id,
                         bool *bp) MOZ_OVERRIDE;
    virtual bool enumerate(JSContext *cx, JSObject *wrapper,
                           AutoIdVector &props) MOZ_OVERRIDE;

    /* Spidermonkey extensions. */
    virtual bool defaultValue(JSContext *cx, JSObject *wrapper_, JSType hint,
                              Value *vp) MOZ_OVERRIDE;
};

/*
 * DirectWrapper forwards its traps by forwarding them to DirectProxyHandler.
 * In effect, DirectWrapper behaves the same as DirectProxyHandler, except that
 * it adds policy enforcement checks to each trap.
 */
class JS_FRIEND_API(DirectWrapper) : public Wrapper, public DirectProxyHandler
{
  public:
    explicit DirectWrapper(unsigned flags, bool hasPrototype = false);

    virtual ~DirectWrapper();

    virtual BaseProxyHandler* toBaseProxyHandler() {
        return this;
    }

    virtual Wrapper *toWrapper() {
        return this;
    }

    /* ES5 Harmony fundamental wrapper traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *wrapper,
                                       jsid id, bool set,
                                       PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *wrapper,
                                          jsid id, bool set,
                                          PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool defineProperty(JSContext *cx, JSObject *wrapper, jsid id,
                                PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *wrapper,
                                     AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool delete_(JSContext *cx, JSObject *wrapper, jsid id,
                         bool *bp) MOZ_OVERRIDE;
    virtual bool enumerate(JSContext *cx, JSObject *wrapper,
                           AutoIdVector &props) MOZ_OVERRIDE;

    /* ES5 Harmony derived wrapper traps. */
    virtual bool has(JSContext *cx, JSObject *wrapper, jsid id, bool *bp) MOZ_OVERRIDE;
    virtual bool hasOwn(JSContext *cx, JSObject *wrapper, jsid id, bool *bp) MOZ_OVERRIDE;
    virtual bool get(JSContext *cx, JSObject *wrapper, JSObject *receiver, jsid id, Value *vp) MOZ_OVERRIDE;
    virtual bool set(JSContext *cx, JSObject *wrapper, JSObject *receiver, jsid id, bool strict,
                     Value *vp) MOZ_OVERRIDE;
    virtual bool keys(JSContext *cx, JSObject *wrapper, AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool iterate(JSContext *cx, JSObject *wrapper, unsigned flags, Value *vp) MOZ_OVERRIDE;

    /* Spidermonkey extensions. */
    virtual bool call(JSContext *cx, JSObject *wrapper, unsigned argc, Value *vp) MOZ_OVERRIDE;
    virtual bool construct(JSContext *cx, JSObject *wrapper, unsigned argc, Value *argv, Value *rval) MOZ_OVERRIDE;
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl,
                            CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, JSObject *wrapper, const Value *vp, bool *bp) MOZ_OVERRIDE;
    virtual JSString *obj_toString(JSContext *cx, JSObject *wrapper) MOZ_OVERRIDE;
    virtual JSString *fun_toString(JSContext *cx, JSObject *wrapper, unsigned indent) MOZ_OVERRIDE;
    virtual bool defaultValue(JSContext *cx, JSObject *wrapper_, JSType hint,
                              Value *vp) MOZ_OVERRIDE;

    static DirectWrapper singleton;
    static DirectWrapper singletonWithPrototype;

    static void *getWrapperFamily();
};

/* Base class for all cross compartment wrapper handlers. */
class JS_FRIEND_API(CrossCompartmentWrapper) : public DirectWrapper
{
  public:
    CrossCompartmentWrapper(unsigned flags, bool hasPrototype = false);

    virtual ~CrossCompartmentWrapper();

    /* ES5 Harmony fundamental wrapper traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *wrapper, jsid id, bool set,
                                       PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *wrapper, jsid id, bool set,
                                          PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool defineProperty(JSContext *cx, JSObject *wrapper, jsid id,
                                PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *wrapper, AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool delete_(JSContext *cx, JSObject *wrapper, jsid id, bool *bp) MOZ_OVERRIDE;
    virtual bool enumerate(JSContext *cx, JSObject *wrapper, AutoIdVector &props) MOZ_OVERRIDE;

    /* ES5 Harmony derived wrapper traps. */
    virtual bool has(JSContext *cx, JSObject *wrapper, jsid id, bool *bp) MOZ_OVERRIDE;
    virtual bool hasOwn(JSContext *cx, JSObject *wrapper, jsid id, bool *bp) MOZ_OVERRIDE;
    virtual bool get(JSContext *cx, JSObject *wrapper, JSObject *receiver, jsid id, Value *vp) MOZ_OVERRIDE;
    virtual bool set(JSContext *cx, JSObject *wrapper, JSObject *receiver, jsid id, bool strict,
                     Value *vp) MOZ_OVERRIDE;
    virtual bool keys(JSContext *cx, JSObject *wrapper, AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool iterate(JSContext *cx, JSObject *wrapper, unsigned flags, Value *vp) MOZ_OVERRIDE;

    /* Spidermonkey extensions. */
    virtual bool call(JSContext *cx, JSObject *wrapper, unsigned argc, Value *vp) MOZ_OVERRIDE;
    virtual bool construct(JSContext *cx, JSObject *wrapper, unsigned argc, Value *argv, Value *rval) MOZ_OVERRIDE;
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl,
                            CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, JSObject *wrapper, const Value *vp, bool *bp) MOZ_OVERRIDE;
    virtual JSString *obj_toString(JSContext *cx, JSObject *wrapper) MOZ_OVERRIDE;
    virtual JSString *fun_toString(JSContext *cx, JSObject *wrapper, unsigned indent) MOZ_OVERRIDE;
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g) MOZ_OVERRIDE;
    virtual bool defaultValue(JSContext *cx, JSObject *wrapper, JSType hint, Value *vp) MOZ_OVERRIDE;
    virtual bool iteratorNext(JSContext *cx, JSObject *wrapper, Value *vp);

    static CrossCompartmentWrapper singleton;
    static CrossCompartmentWrapper singletonWithPrototype;
};

/*
 * Base class for security wrappers. A security wrapper is potentially hiding
 * all or part of some wrapped object thus SecurityWrapper defaults to denying
 * access to the wrappee. This is the opposite of Wrapper which tries to be
 * completely transparent.
 *
 * NB: Currently, only a few ProxyHandler operations are overridden to deny
 * access, relying on derived SecurityWrapper to block access when necessary.
 */
template <class Base>
class JS_FRIEND_API(SecurityWrapper) : public Base
{
  public:
    SecurityWrapper(unsigned flags);

    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl,
                            CallArgs args) MOZ_OVERRIDE;
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx) MOZ_OVERRIDE;
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g) MOZ_OVERRIDE;
};

typedef SecurityWrapper<DirectWrapper> SameCompartmentSecurityWrapper;
typedef SecurityWrapper<CrossCompartmentWrapper> CrossCompartmentSecurityWrapper;

class JS_FRIEND_API(DeadObjectProxy) : public BaseProxyHandler
{
  public:
    static int sDeadObjectFamily;

    explicit DeadObjectProxy();

    /* ES5 Harmony fundamental wrapper traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *wrapper, jsid id, bool set,
                                       PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *wrapper, jsid id, bool set,
                                          PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool defineProperty(JSContext *cx, JSObject *wrapper, jsid id,
                                PropertyDescriptor *desc) MOZ_OVERRIDE;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *wrapper, AutoIdVector &props) MOZ_OVERRIDE;
    virtual bool delete_(JSContext *cx, JSObject *wrapper, jsid id, bool *bp) MOZ_OVERRIDE;
    virtual bool enumerate(JSContext *cx, JSObject *wrapper, AutoIdVector &props) MOZ_OVERRIDE;

    /* Spidermonkey extensions. */
    virtual bool call(JSContext *cx, JSObject *proxy, unsigned argc, Value *vp);
    virtual bool construct(JSContext *cx, JSObject *proxy, unsigned argc, Value *argv, Value *rval);
    virtual bool nativeCall(JSContext *cx, IsAcceptableThis test, NativeImpl impl,
                            CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, JSObject *proxy, const Value *vp, bool *bp);
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx);
    virtual JSString *obj_toString(JSContext *cx, JSObject *proxy);
    virtual JSString *fun_toString(JSContext *cx, JSObject *proxy, unsigned indent);
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g);
    virtual bool defaultValue(JSContext *cx, JSObject *obj, JSType hint, Value *vp);
    virtual bool iteratorNext(JSContext *cx, JSObject *proxy, Value *vp);
    virtual bool getElementIfPresent(JSContext *cx, JSObject *obj, JSObject *receiver,
                                     uint32_t index, Value *vp, bool *present);


    static DeadObjectProxy singleton;
};

extern JSObject *
TransparentObjectWrapper(JSContext *cx, JSObject *obj, JSObject *wrappedProto, JSObject *parent,
                         unsigned flags);

// Proxy family for wrappers. Public so that IsWrapper() can be fully inlined by
// jsfriendapi users.
extern JS_FRIEND_DATA(int) sWrapperFamily;

inline bool
IsWrapper(RawObject obj)
{
    return IsProxy(obj) && GetProxyHandler(obj)->family() == &sWrapperFamily;
}

// Given a JSObject, returns that object stripped of wrappers. If
// stopAtOuter is true, then this returns the outer window if it was
// previously wrapped. Otherwise, this returns the first object for
// which JSObject::isWrapper returns false.
JS_FRIEND_API(JSObject *)
UnwrapObject(JSObject *obj, bool stopAtOuter = true, unsigned *flagsp = NULL);

// Given a JSObject, returns that object stripped of wrappers. At each stage,
// the security wrapper has the opportunity to veto the unwrap. Since checked
// code should never be unwrapping outer window wrappers, we always stop at
// outer windows.
JS_FRIEND_API(JSObject *)
UnwrapObjectChecked(JSContext *cx, JSObject *obj);

// Unwrap only the outermost security wrapper, with the same semantics as
// above. This is the checked version of Wrapper::wrappedObject.
JS_FRIEND_API(JSObject *)
UnwrapOneChecked(JSContext *cx, JSObject *obj);

JS_FRIEND_API(bool)
IsCrossCompartmentWrapper(RawObject obj);

JSObject *
NewDeadProxyObject(JSContext *cx, JSObject *parent);

void
NukeCrossCompartmentWrapper(JSObject *wrapper);

bool
RemapWrapper(JSContext *cx, JSObject *wobj, JSObject *newTarget);

JS_FRIEND_API(bool)
RemapAllWrappersForObject(JSContext *cx, JSObject *oldTarget,
                          JSObject *newTarget);

// API to recompute all cross-compartment wrappers whose source and target
// match the given filters.
JS_FRIEND_API(bool)
RecomputeWrappers(JSContext *cx, const CompartmentFilter &sourceFilter,
                  const CompartmentFilter &targetFilter);

} /* namespace js */

#endif
