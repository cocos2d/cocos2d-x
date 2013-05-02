#ifndef __pluginx_admob_h__
#define __pluginx_admob_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_AdsAdmob_class;
extern JSObject *jsb_AdsAdmob_prototype;

JSBool js_pluginx_admob_AdsAdmob_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_admob_AdsAdmob_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_admob_AdsAdmob(JSContext *cx, JSObject *global);
void register_all_pluginx_admob(JSContext* cx, JSObject* obj);
JSBool js_pluginx_admob_AdsAdmob_showAds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_hideAds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_addTestDevice(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_admob_AdsAdmob_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

