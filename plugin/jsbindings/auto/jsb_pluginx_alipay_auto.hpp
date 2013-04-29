#ifndef __pluginx_alipay_h__
#define __pluginx_alipay_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_IAPAlipay_class;
extern JSObject *jsb_IAPAlipay_prototype;

JSBool js_pluginx_alipay_IAPAlipay_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_alipay_IAPAlipay_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_alipay_IAPAlipay(JSContext *cx, JSObject *global);
void register_all_pluginx_alipay(JSContext* cx, JSObject* obj);
JSBool js_pluginx_alipay_IAPAlipay_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_alipay_IAPAlipay_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_alipay_IAPAlipay_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_alipay_IAPAlipay_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_alipay_IAPAlipay_payForProduct(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_alipay_IAPAlipay_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_alipay_IAPAlipay_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

