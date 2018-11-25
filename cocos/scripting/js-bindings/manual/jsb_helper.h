/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __XMLHTTPHELPER_H__
#define __XMLHTTPHELPER_H__

#include "jsapi.h"
#include "jsfriendapi.h"

#include <typeinfo>
#include <string>
#include <memory>

//#pragma mark - Helpful Macros

#define JS_BINDED_CLASS_GLUE(klass) \
static JSClass js_class; \
static JSObject* js_proto; \
static JSObject* js_parent; \
static void _js_register(JSContext* cx, JS::HandleObject global);

#define JS_BINDED_CLASS_GLUE_IMPL(klass) \
JSClass klass::js_class = {}; \
JSObject* klass::js_proto = NULL; \
JSObject* klass::js_parent = NULL; \

#define JS_BINDED_FUNC(klass, name) \
bool name(JSContext *cx, unsigned argc, jsval *vp)

#define JS_BINDED_CONSTRUCTOR(klass) \
static bool _js_constructor(JSContext *cx, unsigned argc, jsval *vp)

#define JS_BINDED_CONSTRUCTOR_IMPL(klass) \
bool klass::_js_constructor(JSContext *cx, unsigned argc, jsval *vp)

#define JS_BINDED_FUNC_IMPL(klass, name) \
static bool klass##_func_##name(JSContext *cx, unsigned argc, jsval *vp) { \
JS::CallArgs args = JS::CallArgsFromVp(argc, vp); \
JS::RootedObject thisObj(cx, args.thisv().toObjectOrNull()); \
klass* obj = (klass*)JS_GetPrivate(thisObj); \
if (obj) { \
return obj->name(cx, argc, vp); \
} \
JS_ReportError(cx, "Invalid object call for function %s", #name); \
return false; \
} \
bool klass::name(JSContext *cx, unsigned argc, jsval *vp)

#define JS_WRAP_OBJECT_IN_VAL(klass, cobj, out) \
do { \
JSObject *obj = JS_NewObject(cx, &klass::js_class, klass::js_proto, klass::js_parent); \
if (obj) { \
JS_SetPrivate(obj, cobj); \
out = OBJECT_TO_JSVAL(obj); \
} \
} while(0) \

#define JS_BINDED_FUNC_FOR_DEF(klass, name) \
JS_FN(#name, klass##_func_##name, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT)

#define JS_BINDED_PROP_GET(klass, propName) \
bool _js_get_##propName(JSContext *cx, const JS::CallArgs& args)

#define JS_BINDED_PROP_GET_IMPL(klass, propName) \
static bool _js_get_##klass##_##propName(JSContext *cx, unsigned argc, jsval *vp) { \
JS::CallArgs args = JS::CallArgsFromVp(argc, vp); \
JS::RootedObject obj(cx, args.thisv().toObjectOrNull()); \
klass* cobj = (klass*)JS_GetPrivate(obj); \
if (cobj) { \
return cobj->_js_get_##propName(cx, args); \
} \
JS_ReportError(cx, "Invalid getter call for property %s", #propName); \
return false; \
} \
bool klass::_js_get_##propName(JSContext *cx, const JS::CallArgs& args)

#define JS_BINDED_PROP_SET(klass, propName) \
bool _js_set_##propName(JSContext *cx, const JS::CallArgs& args)

#define JS_BINDED_PROP_SET_IMPL(klass, propName) \
static bool _js_set_##klass##_##propName(JSContext *cx, unsigned argc, jsval *vp) { \
JS::CallArgs args = JS::CallArgsFromVp(argc, vp); \
JS::RootedObject obj(cx, args.thisv().toObjectOrNull()); \
klass* cobj = (klass*)JS_GetPrivate(obj); \
if (cobj) { \
return cobj->_js_set_##propName(cx, args); \
} \
JS_ReportError(cx, "Invalid setter call for property %s", #propName); \
return false; \
} \
bool klass::_js_set_##propName(JSContext *cx, const JS::CallArgs& args)

#define JS_BINDED_PROP_ACCESSOR(klass, propName) \
JS_BINDED_PROP_GET(klass, propName); \
JS_BINDED_PROP_SET(klass, propName);

#define JS_BINDED_PROP_DEF_GETTER(klass, propName) \
JS_PSG(#propName, _js_get_##klass##_##propName, JSPROP_ENUMERATE | JSPROP_PERMANENT)

#define JS_BINDED_PROP_DEF_ACCESSOR(klass, propName) \
JS_PSGS(#propName, _js_get_##klass##_##propName, _js_set_##klass##_##propName, JSPROP_ENUMERATE | JSPROP_PERMANENT)

#define JS_CREATE_UINT_WRAPPED(valOut, propName, val) \
do { \
JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL); \
jsval propVal = UINT_TO_JSVAL(val); \
JS_SetProperty(cx, jsobj, "__" propName, &propVal); \
valOut = OBJECT_TO_JSVAL(jsobj); \
} while(0)

#define JS_GET_UINT_WRAPPED(inVal, propName, out) \
do { \
if (inVal.isObject()) {\
JSObject* jsobj = JSVAL_TO_OBJECT(inVal); \
jsval outVal; \
JS_GetProperty(cx, jsobj, "__" propName, &outVal); \
JS_ValueToECMAUint32(cx, outVal, &out); \
} else { \
int32_t tmp; \
JS_ValueToInt32(cx, inVal, &tmp); \
out = (uint32_t)tmp; \
} \
} while (0)

#endif /* __XMLHTTPHELPER_H__ */
