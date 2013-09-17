#ifndef __JS_MANUAL_PROTOCOLS_H__
#define __JS_MANUAL_PROTOCOLS_H__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_PluginParam_class;
extern JSObject *jsb_PluginParam_prototype;

JSBool js_pluginx_protocols_PluginParam_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_PluginParam_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_PluginParam(JSContext *cx, JSObject *global);
void register_all_pluginx_protocols(JSContext* cx, JSObject* obj);
JSBool js_pluginx_protocols_PluginParam_PluginParam(JSContext *cx, uint32_t argc, jsval *vp);

JSBool js_pluginx_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_MANUAL_PROTOCOLS_H__ */
