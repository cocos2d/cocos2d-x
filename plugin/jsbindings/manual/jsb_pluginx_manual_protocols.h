#ifndef __JS_MANUAL_PROTOCOLS_H__
#define __JS_MANUAL_PROTOCOLS_H__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_PluginParam_class;
extern JSObject *jsb_PluginParam_prototype;

bool js_pluginx_protocols_PluginParam_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_PluginParam_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_PluginParam(JSContext *cx, JS::HandleObject global);
void register_all_pluginx_protocols(JSContext* cx, JS::HandleObject obj);
bool js_pluginx_protocols_PluginParam_PluginParam(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_MANUAL_PROTOCOLS_H__ */
