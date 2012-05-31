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
 * Portions created by the Initial Developer are Copyright (C) 2009
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

#ifndef jsproxy_h___
#define jsproxy_h___

#include "jsapi.h"
#include "jsfriendapi.h"

namespace js {

/* Base class for all C++ proxy handlers. */
class JS_FRIEND_API(ProxyHandler) {
    void *mFamily;
  public:
    explicit ProxyHandler(void *family);
    virtual ~ProxyHandler();

    /* ES5 Harmony fundamental proxy traps. */
    virtual bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id, bool set,
                                       PropertyDescriptor *desc) = 0;
    virtual bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id, bool set,
                                          PropertyDescriptor *desc) = 0;
    virtual bool defineProperty(JSContext *cx, JSObject *proxy, jsid id,
                                PropertyDescriptor *desc) = 0;
    virtual bool getOwnPropertyNames(JSContext *cx, JSObject *proxy, AutoIdVector &props) = 0;
    virtual bool delete_(JSContext *cx, JSObject *proxy, jsid id, bool *bp) = 0;
    virtual bool enumerate(JSContext *cx, JSObject *proxy, AutoIdVector &props) = 0;
    virtual bool fix(JSContext *cx, JSObject *proxy, Value *vp) = 0;

    /* ES5 Harmony derived proxy traps. */
    virtual bool has(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    virtual bool hasOwn(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    virtual bool get(JSContext *cx, JSObject *proxy, JSObject *receiver, jsid id, Value *vp);
    virtual bool set(JSContext *cx, JSObject *proxy, JSObject *receiver, jsid id, bool strict,
                     Value *vp);
    virtual bool keys(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    virtual bool iterate(JSContext *cx, JSObject *proxy, unsigned flags, Value *vp);

    /* Spidermonkey extensions. */
    virtual bool call(JSContext *cx, JSObject *proxy, unsigned argc, Value *vp);
    virtual bool construct(JSContext *cx, JSObject *proxy, unsigned argc, Value *argv, Value *rval);
    virtual bool nativeCall(JSContext *cx, JSObject *proxy, Class *clasp, Native native, CallArgs args);
    virtual bool hasInstance(JSContext *cx, JSObject *proxy, const Value *vp, bool *bp);
    virtual JSType typeOf(JSContext *cx, JSObject *proxy);
    virtual bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx);
    virtual JSString *obj_toString(JSContext *cx, JSObject *proxy);
    virtual JSString *fun_toString(JSContext *cx, JSObject *proxy, unsigned indent);
    virtual bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g);
    virtual bool defaultValue(JSContext *cx, JSObject *obj, JSType hint, Value *vp);
    virtual bool iteratorNext(JSContext *cx, JSObject *proxy, Value *vp);
    virtual void finalize(JSContext *cx, JSObject *proxy);
    virtual void trace(JSTracer *trc, JSObject *proxy);
    virtual bool getElementIfPresent(JSContext *cx, JSObject *obj, JSObject *receiver,
                                     uint32_t index, Value *vp, bool *present);

    virtual bool isOuterWindow() {
        return false;
    }

    inline void *family() {
        return mFamily;
    }
};

/* Dispatch point for handlers that executes the appropriate C++ or scripted traps. */
class Proxy {
  public:
    /* ES5 Harmony fundamental proxy traps. */
    static bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id, bool set,
                                      PropertyDescriptor *desc);
    static bool getPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id, bool set, Value *vp);
    static bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id, bool set,
                                         PropertyDescriptor *desc);
    static bool getOwnPropertyDescriptor(JSContext *cx, JSObject *proxy, jsid id, bool set,
                                         Value *vp);
    static bool defineProperty(JSContext *cx, JSObject *proxy, jsid id, PropertyDescriptor *desc);
    static bool defineProperty(JSContext *cx, JSObject *proxy, jsid id, const Value &v);
    static bool getOwnPropertyNames(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    static bool delete_(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    static bool enumerate(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    static bool fix(JSContext *cx, JSObject *proxy, Value *vp);

    /* ES5 Harmony derived proxy traps. */
    static bool has(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    static bool hasOwn(JSContext *cx, JSObject *proxy, jsid id, bool *bp);
    static bool get(JSContext *cx, JSObject *proxy, JSObject *receiver, jsid id, Value *vp);
    static bool getElementIfPresent(JSContext *cx, JSObject *proxy, JSObject *receiver,
                                    uint32_t index, Value *vp, bool *present);
    static bool set(JSContext *cx, JSObject *proxy, JSObject *receiver, jsid id, bool strict,
                    Value *vp);
    static bool keys(JSContext *cx, JSObject *proxy, AutoIdVector &props);
    static bool iterate(JSContext *cx, JSObject *proxy, unsigned flags, Value *vp);

    /* Spidermonkey extensions. */
    static bool call(JSContext *cx, JSObject *proxy, unsigned argc, Value *vp);
    static bool construct(JSContext *cx, JSObject *proxy, unsigned argc, Value *argv, Value *rval);
    static bool nativeCall(JSContext *cx, JSObject *proxy, Class *clasp, Native native, CallArgs args);
    static bool hasInstance(JSContext *cx, JSObject *proxy, const Value *vp, bool *bp);
    static JSType typeOf(JSContext *cx, JSObject *proxy);
    static bool objectClassIs(JSObject *obj, ESClassValue classValue, JSContext *cx);
    static JSString *obj_toString(JSContext *cx, JSObject *proxy);
    static JSString *fun_toString(JSContext *cx, JSObject *proxy, unsigned indent);
    static bool regexp_toShared(JSContext *cx, JSObject *proxy, RegExpGuard *g);
    static bool defaultValue(JSContext *cx, JSObject *obj, JSType hint, Value *vp);
    static bool iteratorNext(JSContext *cx, JSObject *proxy, Value *vp);
};

inline bool IsObjectProxyClass(const Class *clasp)
{
    return clasp == &js::ObjectProxyClass || clasp == &js::OuterWindowProxyClass;
}

inline bool IsFunctionProxyClass(const Class *clasp)
{
    return clasp == &js::FunctionProxyClass;
}

inline bool IsObjectProxy(const JSObject *obj)
{
    return IsObjectProxyClass(GetObjectClass(obj));
}

inline bool IsFunctionProxy(const JSObject *obj)
{
    return IsFunctionProxyClass(GetObjectClass(obj));
}

inline bool IsProxy(const JSObject *obj)
{
    Class *clasp = GetObjectClass(obj);
    return IsObjectProxyClass(clasp) || IsFunctionProxyClass(clasp);
}

/* Shared between object and function proxies. */
const uint32_t JSSLOT_PROXY_HANDLER = 0;
const uint32_t JSSLOT_PROXY_PRIVATE = 1;
const uint32_t JSSLOT_PROXY_EXTRA   = 2;
/* Function proxies only. */
const uint32_t JSSLOT_PROXY_CALL = 4;
const uint32_t JSSLOT_PROXY_CONSTRUCT = 5;

inline ProxyHandler *
GetProxyHandler(const JSObject *obj)
{
    JS_ASSERT(IsProxy(obj));
    return (ProxyHandler *) GetReservedSlot(obj, JSSLOT_PROXY_HANDLER).toPrivate();
}

inline const Value &
GetProxyPrivate(const JSObject *obj)
{
    JS_ASSERT(IsProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_PRIVATE);
}

inline const Value &
GetProxyExtra(const JSObject *obj, size_t n)
{
    JS_ASSERT(IsProxy(obj));
    return GetReservedSlot(obj, JSSLOT_PROXY_EXTRA + n);
}

inline void
SetProxyExtra(JSObject *obj, size_t n, const Value &extra)
{
    JS_ASSERT(IsProxy(obj));
    JS_ASSERT(n <= 1);
    SetReservedSlot(obj, JSSLOT_PROXY_EXTRA + n, extra);
}

JS_FRIEND_API(JSObject *)
NewProxyObject(JSContext *cx, ProxyHandler *handler, const Value &priv,
               JSObject *proto, JSObject *parent,
               JSObject *call = NULL, JSObject *construct = NULL);

} /* namespace js */

JS_BEGIN_EXTERN_C

extern JS_FRIEND_API(JSObject *)
js_InitProxyClass(JSContext *cx, JSObject *obj);

JS_END_EXTERN_C

#endif
