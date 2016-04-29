#ifndef __JS_MANUAL_CALLBACK_H__
#define __JS_MANUAL_CALLBACK_H__

#include "jsapi.h"
#include "jsfriendapi.h"

bool js_pluginx_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolIAP_getResultListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolAds_getAdsListener(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_ProtocolShare_setResultListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolShare_getResultListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_ProtocolSocial_setListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolSocial_getListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_ProtocolUser_setActionListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolUser_getActionListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_ProtocolUser_logout(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_protocols_AgentManager_share(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_protocols_AgentManager_login(JSContext *cx, uint32_t argc, jsval *vp);

bool js_pluginx_FacebookAgent_login(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_FacebookAgent_api(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_FacebookAgent_appRequest(JSContext *cx, uint32_t argc, jsval *vp);
bool js_pluginx_FacebookAgent_dialog(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_MANUAL_CALLBACK_H__ */
