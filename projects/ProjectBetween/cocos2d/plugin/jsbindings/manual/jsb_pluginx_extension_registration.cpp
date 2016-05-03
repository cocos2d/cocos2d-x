#include "jsb_pluginx_extension_registration.h"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "jsb_pluginx_manual_callback.h"
#include "jsb_pluginx_manual_protocols.h"

static jsval anonEvaluate(JSContext *cx, JS::HandleObject thisObj, const char* string) {
    JS::RootedValue out(cx);
//    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    if (JS_EvaluateScript(cx, thisObj, string, strlen(string), "(string)", 1, &out) == true) {
        return out.get();
    }
    return JSVAL_VOID;
}

extern JSObject *jsb_cocos2d_plugin_ProtocolIAP_prototype;
extern JSObject *jsb_cocos2d_plugin_ProtocolAds_prototype;
extern JSObject *jsb_cocos2d_plugin_ProtocolShare_prototype;
extern JSObject *jsb_cocos2d_plugin_PluginProtocol_prototype;
extern JSObject *jsb_cocos2d_plugin_ProtocolSocial_prototype;
extern JSObject *jsb_cocos2d_plugin_ProtocolUser_prototype;
extern JSObject *jsb_cocos2d_plugin_FacebookAgent_prototype;

void register_pluginx_js_extensions(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject ns(cx);
    pluginx::get_or_create_js_obj(cx, global, "plugin", &ns);

    JS::RootedObject iap(cx, jsb_cocos2d_plugin_ProtocolIAP_prototype);
    JS_DefineFunction(cx, iap, "setListener", js_pluginx_ProtocolIAP_setResultListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, iap, "getListener", js_pluginx_ProtocolIAP_getResultListener, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, iap, "payForProduct", js_pluginx_ProtocolIAP_payForProduct, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject ads(cx, jsb_cocos2d_plugin_ProtocolAds_prototype);
    JS_DefineFunction(cx, ads, "setListener", js_pluginx_ProtocolAds_setAdsListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ads, "getListener", js_pluginx_ProtocolAds_getAdsListener, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject share(cx, jsb_cocos2d_plugin_ProtocolShare_prototype);
    JS_DefineFunction(cx, share, "setListener", js_pluginx_ProtocolShare_setResultListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, share, "getListener", js_pluginx_ProtocolShare_getResultListener, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, share, "share", js_pluginx_ProtocolShare_share, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject social(cx, jsb_cocos2d_plugin_ProtocolSocial_prototype);
    JS_DefineFunction(cx, social, "setListener", js_pluginx_ProtocolSocial_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, social, "getListener", js_pluginx_ProtocolSocial_getListener, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, social, "submitScore", js_pluginx_ProtocolSocial_submitScore, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, social, "unlockAchievement", js_pluginx_ProtocolSocial_unlockAchievement, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject user(cx, jsb_cocos2d_plugin_ProtocolUser_prototype);
    JS_DefineFunction(cx, user, "setActionListener", js_pluginx_ProtocolUser_setActionListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, user, "getActionListener", js_pluginx_ProtocolUser_getActionListener, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, user, "login", js_pluginx_ProtocolUser_login, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, user, "logout", js_pluginx_ProtocolUser_logout, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject protocol(cx, jsb_cocos2d_plugin_PluginProtocol_prototype);
    JS_DefineFunction(cx, protocol, "callFuncWithParam", js_pluginx_PluginProtocol_callFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, protocol, "callStringFuncWithParam", js_pluginx_PluginProtocol_callStringFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, protocol, "callIntFuncWithParam", js_pluginx_PluginProtocol_callIntFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, protocol, "callFloatFuncWithParam", js_pluginx_PluginProtocol_callFloatFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, protocol, "callBoolFuncWithParam", js_pluginx_PluginProtocol_callBoolFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject facebook(cx, jsb_cocos2d_plugin_FacebookAgent_prototype);
    JS_DefineFunction(cx, facebook, "login", js_pluginx_FacebookAgent_login, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, facebook, "_api", js_pluginx_FacebookAgent_api, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, facebook, "appRequest", js_pluginx_FacebookAgent_appRequest, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, facebook, "dialog", js_pluginx_FacebookAgent_dialog, 0, JSPROP_READONLY | JSPROP_PERMANENT);

    js_register_pluginx_protocols_PluginParam(cx, ns);
}
