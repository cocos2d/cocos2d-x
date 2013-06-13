#include "jsb_pluginx_extension_registration.h"
#include "jsb_pluginx_manual_callback.h"
#include "jsb_pluginx_manual_protocols.h"

static jsval anonEvaluate(JSContext *cx, JSObject *thisObj, const char* string) {
    jsval out;
    if (JS_EvaluateScript(cx, thisObj, string, strlen(string), "(string)", 1, &out) == JS_TRUE) {
        return out;
    }
    return JSVAL_VOID;
}

extern JSObject *jsb_ProtocolIAP_prototype;
extern JSObject *jsb_ProtocolAds_prototype;
extern JSObject *jsb_ProtocolSocial_prototype;
extern JSObject *jsb_PluginProtocol_prototype;

void register_pluginx_js_extensions(JSContext* cx, JSObject* global)
{
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, global, "plugin", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, global, "plugin", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }

    JS_DefineFunction(cx, jsb_ProtocolIAP_prototype, "setResultListener", js_pluginx_ProtocolIAP_setResultListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_ProtocolAds_prototype, "setAdsListener", js_pluginx_ProtocolAds_setAdsListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_ProtocolSocial_prototype, "setResultListener", js_pluginx_ProtocolSocial_setResultListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callFuncWithParam", js_pluginx_PluginProtocol_callFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callStringFuncWithParam", js_pluginx_PluginProtocol_callStringFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callIntFuncWithParam", js_pluginx_PluginProtocol_callIntFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callFloatFuncWithParam", js_pluginx_PluginProtocol_callFloatFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callBoolFuncWithParam", js_pluginx_PluginProtocol_callBoolFuncWithParam, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    global = ns;
    js_register_pluginx_protocols_PluginParam(cx, global);
}
