#ifndef __pluginx_weibo_h__
#define __pluginx_weibo_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_SocialWeibo_class;
extern JSObject *jsb_SocialWeibo_prototype;

JSBool js_pluginx_weibo_SocialWeibo_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_pluginx_weibo_SocialWeibo_finalize(JSContext *cx, JSObject *obj);
void js_register_pluginx_weibo_SocialWeibo(JSContext *cx, JSObject *global);
void register_all_pluginx_weibo(JSContext* cx, JSObject* obj);
JSBool js_pluginx_weibo_SocialWeibo_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_weibo_SocialWeibo_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_weibo_SocialWeibo_share(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_weibo_SocialWeibo_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_weibo_SocialWeibo_configDeveloperInfo(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_weibo_SocialWeibo_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_pluginx_weibo_SocialWeibo_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);
#endif

