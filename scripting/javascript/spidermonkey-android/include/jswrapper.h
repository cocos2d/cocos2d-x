/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=4 sw=4 et tw=99:
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
 * The Original Code is Mozilla SpiderMonkey JavaScript 1.9 code, released
 * May 28, 2008.
 *
 * The Initial Developer of the Original Code is
 *   Mozilla Foundation
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Andreas Gal <gal@mozilla.com>
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

#ifndef jswrapper_h___
#define jswrapper_h___

#include "mozilla/Attributes.h"

#include "jsapi.h"
#include "jsproxy.h"

namespace js {

class DummyFrameGuard;

/* Base class that just implements no-op forwarding methods for fundamental
 * traps. This is meant to be used as a base class for ProxyHandlers that
 * want transparent forwarding behavior but don't want to use the derived
 * traps and other baggage of js::Wrapper.
 */
class JS_FRIEND_API(AbstractWrapper) : public ProxyHandler
{
    unsigned mFlags;
  public:
    unsigned flags() const { return mFlags; }

    explicit AbstractWrapper(unsigned flags);

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
    virtual bool fix(JSContext *cx, JSObject *wrapper, Value *vp) MOZ_OVERRIDE;

    /* Policy enforcement traps.
     *
     * enter() allows the policy to specify whether the caller may perform |act|
     * on the underlying object's |id| property. In the case when |act| is CALL,
     * |id| is generally JSID_VOID.
     *
     * leave() allows the policy to undo various scoped state changes taken in
     * enter(). If enter() succeeds, leave() must be called upon completion of
     * the approved action.
     *
     * The |act| parameter to enter() specifies the action being performed. GET,
     * SET, and CALL are self-explanatory, but PUNCTURE requires more explanation:
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
     * */
    enum Action { GET, SET, CALL, PUNCTURE };
    virtual bool enter(JSContext *cx, JSObject *wrapper, jsid id, Action act, bool *bp);
    virtual void leave(JSContext *cx, JSObject *wrapper);

    static JSObject *wrappedObject(const JSObject *wrapper);
    static AbstractWrapper *wrapperHandler(const JSObject *wrapper);
};

/* No-op wrapper handler base class. */
class JS_FRIEND_API(Wrapper) : public AbstractWrapper
{
  public:
    explicit Wrapper(unsigned flags);

    typedef enum { PermitObjectAccess, PermitPropertyAccess, DenyAccess } Permission;

    virtual ~Wrapper();

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
    virtual bool nativeCall(JSContext *cx, JSObject *wrapper, Class *clasp, Native native, CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, JSObject *wrapper, const Value *vp, bool *bp) MOZ_OVERRIDE;
    virtual JSType typeOf(JSContext *cx, JSObject *proxy) MOZ_OVERRIDE;
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx) MOZ_OVERRIDE;
    virtual JSString *obj_toString(JSContext *cx, JSObject *wrapper) MOZ_OVERRIDE;
    virtual JSString *fun_toString(JSContext *cx, JSObject *wrapper, unsigned indent) MOZ_OVERRIDE;
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g) MOZ_OVERRIDE;
    virtual bool defaultValue(JSContext *cx, JSObject *wrapper, JSType hint, Value *vp) MOZ_OVERRIDE;
    virtual bool iteratorNext(JSContext *cx, JSObject *wrapper, Value *vp) MOZ_OVERRIDE;

    virtual void trace(JSTracer *trc, JSObject *wrapper) MOZ_OVERRIDE;

    using AbstractWrapper::Action;

    static Wrapper singleton;

    static JSObject *New(JSContext *cx, JSObject *obj, JSObject *proto, JSObject *parent,
                         Wrapper *handler);

    using AbstractWrapper::wrappedObject;
    using AbstractWrapper::wrapperHandler;

    enum {
        CROSS_COMPARTMENT = 1 << 0,
        LAST_USED_FLAG = CROSS_COMPARTMENT
    };

    static void *getWrapperFamily();
};

/* Base class for all cross compartment wrapper handlers. */
class JS_FRIEND_API(CrossCompartmentWrapper) : public Wrapper
{
  public:
    CrossCompartmentWrapper(unsigned flags);

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
    virtual bool nativeCall(JSContext *cx, JSObject *wrapper, Class *clasp, Native native, CallArgs args) MOZ_OVERRIDE;
    virtual bool hasInstance(JSContext *cx, JSObject *wrapper, const Value *vp, bool *bp) MOZ_OVERRIDE;
    virtual JSString *obj_toString(JSContext *cx, JSObject *wrapper) MOZ_OVERRIDE;
    virtual JSString *fun_toString(JSContext *cx, JSObject *wrapper, unsigned indent) MOZ_OVERRIDE;
    virtual bool defaultValue(JSContext *cx, JSObject *wrapper, JSType hint, Value *vp) MOZ_OVERRIDE;
    virtual bool iteratorNext(JSContext *cx, JSObject *wrapper, Value *vp);

    virtual void trace(JSTracer *trc, JSObject *wrapper) MOZ_OVERRIDE;

    static CrossCompartmentWrapper singleton;
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

    virtual bool nativeCall(JSContext *cx, JSObject *wrapper, Class *clasp, Native native, CallArgs args) MOZ_OVERRIDE;
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx) MOZ_OVERRIDE;
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g) MOZ_OVERRIDE;
};

typedef SecurityWrapper<Wrapper> SameCompartmentSecurityWrapper;
typedef SecurityWrapper<CrossCompartmentWrapper> CrossCompartmentSecurityWrapper;

/*
 * A hacky class that lets a friend force a fake frame. We must already be
 * in the compartment of |target| when we enter the forced frame.
 */
class JS_FRIEND_API(ForceFrame)
{
  public:
    JSContext * const context;
    JSObject * const target;
  private:
    DummyFrameGuard *frame;

  public:
    ForceFrame(JSContext *cx, JSObject *target);
    ~ForceFrame();
    bool enter();
};

extern JSObject *
TransparentObjectWrapper(JSContext *cx, JSObject *obj, JSObject *wrappedProto, JSObject *parent,
                         unsigned flags);

// Proxy family for wrappers. Public so that IsWrapper() can be fully inlined by
// jsfriendapi users.
extern JS_FRIEND_DATA(int) sWrapperFamily;

inline bool
IsWrapper(const JSObject *obj)
{
    return IsProxy(obj) && GetProxyHandler(obj)->family() == &sWrapperFamily;
}

// Given a JSObject, returns that object stripped of wrappers. If
// stopAtOuter is true, then this returns the outer window if it was
// previously wrapped. Otherwise, this returns the first object for
// which JSObject::isWrapper returns false.
JS_FRIEND_API(JSObject *) UnwrapObject(JSObject *obj, bool stopAtOuter = true,
                                       unsigned *flagsp = NULL);

// Given a JSObject, returns that object stripped of wrappers. At each stage,
// the security wrapper has the opportunity to veto the unwrap. Since checked
// code should never be unwrapping outer window wrappers, we always stop at
// outer windows.
JS_FRIEND_API(JSObject *) UnwrapObjectChecked(JSContext *cx, JSObject *obj);

bool IsCrossCompartmentWrapper(const JSObject *obj);

void
NukeCrossCompartmentWrapper(JSObject *wrapper);

} /* namespace js */

#endif
