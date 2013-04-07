#ifndef __pluginx_protocols_h__
#define __pluginx_protocols_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_PluginProtocol_class;
extern JSObject *jsb_PluginProtocol_prototype;

JSBool js_pluginx_protocols_PluginProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_PluginProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_PluginProtocol(JSContext *cx, JSObject *global);
void register_all_pluginx_protocols(JSContext* cx, JSObject* obj);
JSBool js_pluginx_protocols_PluginProtocol_setUserData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginProtocol_getUserData(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginProtocol_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_PluginManager_class;
extern JSObject *jsb_PluginManager_prototype;

JSBool js_pluginx_protocols_PluginManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_PluginManager_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_PluginManager(JSContext *cx, JSObject *global);
void register_all_pluginx_protocols(JSContext* cx, JSObject* obj);
JSBool js_pluginx_protocols_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolAnalytics_class;
extern JSObject *jsb_ProtocolAnalytics_prototype;

JSBool js_pluginx_protocols_ProtocolAnalytics_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_ProtocolAnalytics_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_ProtocolAnalytics(JSContext *cx, JSObject *global);
void register_all_pluginx_protocols(JSContext* cx, JSObject* obj);
JSBool js_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_logEvent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolAnalytics_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolIAP_class;
extern JSObject *jsb_ProtocolIAP_prototype;

JSBool js_pluginx_protocols_ProtocolIAP_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_ProtocolIAP_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_ProtocolIAP(JSContext *cx, JSObject *global);
void register_all_pluginx_protocols(JSContext* cx, JSObject* obj);
JSBool js_pluginx_protocols_ProtocolIAP_initDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAP_payResult(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolIAPOnLine_class;
extern JSObject *jsb_ProtocolIAPOnLine_prototype;

JSBool js_pluginx_protocols_ProtocolIAPOnLine_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_protocols_ProtocolIAPOnLine_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_protocols_ProtocolIAPOnLine(JSContext *cx, JSObject *global);
void register_all_pluginx_protocols(JSContext* cx, JSObject* obj);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_initDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_payForProduct(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_protocols_ProtocolIAPOnLine_payFailedLocally(JSContext *cx, uint32_t argc, jsval *vp);
#endif

