#ifndef __JS_MANUAL_IAP_H__
#define __JS_MANUAL_IAP_H__

#include "jsapi.h"
#include "jsfriendapi.h"

JSBool js_pluginx_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_ProtocolSocial_setResultListener(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_MANUAL_IAP_H__ */
