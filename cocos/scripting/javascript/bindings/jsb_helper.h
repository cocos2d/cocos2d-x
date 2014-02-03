#ifndef __XMLHTTPHELPER_H__
#define __XMLHTTPHELPER_H__

#include <typeinfo>
#include <string>
#include <memory>
#include "jsapi.h"

//#pragma mark - Helpful Macros

#define JS_BINDED_CLASS_GLUE(klass) \
static JSClass js_class; \
static JSObject* js_proto; \
static JSObject* js_parent; \
static void _js_register(JSContext* cx, JSObject* global);

#define JS_BINDED_CLASS_GLUE_IMPL(klass) \
JSClass klass::js_class = {}; \
JSObject* klass::js_proto = NULL; \
JSObject* klass::js_parent = NULL; \

#define JS_BINDED_FUNC(klass, name) \
JSBool name(JSContext *cx, unsigned argc, jsval *vp)

#define JS_BINDED_CONSTRUCTOR(klass) \
static JSBool _js_constructor(JSContext *cx, unsigned argc, jsval *vp)

#define JS_BINDED_CONSTRUCTOR_IMPL(klass) \
JSBool klass::_js_constructor(JSContext *cx, unsigned argc, jsval *vp)

#define JS_BINDED_FUNC_IMPL(klass, name) \
static JSBool klass##_func_##name(JSContext *cx, unsigned argc, jsval *vp) { \
JSObject* thisObj = JS_THIS_OBJECT(cx, vp); \
klass* obj = (klass*)JS_GetPrivate(thisObj); \
if (obj) { \
return obj->name(cx, argc, vp); \
} \
JS_ReportError(cx, "Invalid object call for function %s", #name); \
return JS_FALSE; \
} \
JSBool klass::name(JSContext *cx, unsigned argc, jsval *vp)

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
JSBool _js_get_##propName(JSContext *cx, JS::HandleId id, JS::MutableHandleValue vp)

#define JS_BINDED_PROP_GET_IMPL(klass, propName) \
static JSBool _js_get_##klass##_##propName(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) { \
klass* cobj = (klass*)JS_GetPrivate(obj); \
if (cobj) { \
return cobj->_js_get_##propName(cx, id, vp); \
} \
JS_ReportError(cx, "Invalid getter call for property %s", #propName); \
return JS_FALSE; \
} \
JSBool klass::_js_get_##propName(JSContext *cx, JS::HandleId id, JS::MutableHandleValue vp)

#define JS_BINDED_PROP_SET(klass, propName) \
JSBool _js_set_##propName(JSContext *cx, JS::HandleId id, JSBool strict, JS::MutableHandleValue vp)

#define JS_BINDED_PROP_SET_IMPL(klass, propName) \
static JSBool _js_set_##klass##_##propName(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JSBool strict, JS::MutableHandleValue vp) { \
klass* cobj = (klass*)JS_GetPrivate(obj); \
if (cobj) { \
return cobj->_js_set_##propName(cx, id, strict, vp); \
} \
JS_ReportError(cx, "Invalid setter call for property %s", #propName); \
return JS_FALSE; \
} \
JSBool klass::_js_set_##propName(JSContext *cx, JS::HandleId id, JSBool strict, JS::MutableHandleValue vp)

#define JS_BINDED_PROP_ACCESSOR(klass, propName) \
JS_BINDED_PROP_GET(klass, propName); \
JS_BINDED_PROP_SET(klass, propName);

#define JS_BINDED_PROP_DEF_GETTER(klass, propName) \
{#propName, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(_js_get_##klass##_##propName), NULL}

#define JS_BINDED_PROP_DEF_ACCESSOR(klass, propName) \
{#propName, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(_js_get_##klass##_##propName), JSOP_WRAPPER(_js_set_##klass##_##propName)}

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
