#ifndef __pluginx_twitter_h__
#define __pluginx_twitter_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_SocialTwitter_class;
extern JSObject *jsb_SocialTwitter_prototype;

JSBool js_pluginx_twitter_SocialTwitter_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_twitter_SocialTwitter_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_twitter_SocialTwitter(JSContext *cx, JSObject *global);
void register_all_pluginx_twitter(JSContext* cx, JSObject* obj);
JSBool js_pluginx_twitter_SocialTwitter_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_twitter_SocialTwitter_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_twitter_SocialTwitter_share(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_twitter_SocialTwitter_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_twitter_SocialTwitter_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_twitter_SocialTwitter_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_twitter_SocialTwitter_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

