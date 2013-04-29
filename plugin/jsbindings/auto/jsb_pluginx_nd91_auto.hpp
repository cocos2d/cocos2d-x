#ifndef __pluginx_nd91_h__
#define __pluginx_nd91_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_IAPNd91_class;
extern JSObject *jsb_IAPNd91_prototype;

JSBool js_pluginx_nd91_IAPNd91_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_nd91_IAPNd91_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_nd91_IAPNd91(JSContext *cx, JSObject *global);
void register_all_pluginx_nd91(JSContext* cx, JSObject* obj);
JSBool js_pluginx_nd91_IAPNd91_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_nd91_IAPNd91_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_nd91_IAPNd91_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_nd91_IAPNd91_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_nd91_IAPNd91_payForProduct(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_nd91_IAPNd91_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_nd91_IAPNd91_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

