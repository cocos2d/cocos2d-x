#include "base/ccConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#ifndef __cocos2dx_experimental_webView_h__
#define __cocos2dx_experimental_webView_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_cocos2d_experimental_ui_WebView_class;
extern JSObject *jsb_cocos2d_experimental_ui_WebView_prototype;

bool js_cocos2dx_experimental_webView_WebView_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_experimental_webView_WebView_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_experimental_webView_WebView(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_experimental_webView(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_experimental_webView_WebView_canGoBack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_loadHTMLString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_goForward(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_goBack(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_setScalesPageToFit(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_getOnDidFailLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_loadFile(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_loadURL(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_setBounces(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_evaluateJS(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_getOnJSCallback(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_canGoForward(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_getOnShouldStartLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_stopLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_reload(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_setJavascriptInterfaceScheme(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_getOnDidFinishLoading(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_experimental_webView_WebView_WebView(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_experimental_webView_h__
#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
