#ifndef __pluginx_umeng_h__
#define __pluginx_umeng_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_AnalyticsUmeng_class;
extern JSObject *jsb_AnalyticsUmeng_prototype;

JSBool js_pluginx_umeng_AnalyticsUmeng_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_umeng_AnalyticsUmeng_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_umeng_AnalyticsUmeng(JSContext *cx, JSObject *global);
void register_all_pluginx_umeng(JSContext* cx, JSObject* obj);
JSBool js_pluginx_umeng_AnalyticsUmeng_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_startSession(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_stopSession(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_updateOnlineConfig(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logError(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logEventWithDuration(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_setDefaultReportPolicy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logTimedKVEventEnd(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logTimedKVEventBegin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_getConfigParams(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logTimedEventWithLabelBegin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logTimedEventWithLabelEnd(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logEvent(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_logEventWithLabel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_umeng_AnalyticsUmeng_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

