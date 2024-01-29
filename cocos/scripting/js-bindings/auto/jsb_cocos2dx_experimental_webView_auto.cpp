#include "scripting/js-bindings/auto/jsb_cocos2dx_experimental_webView_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "ui/UIWebView.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
JSClass  *jsb_cocos2d_experimental_ui_WebView_class;
JSObject *jsb_cocos2d_experimental_ui_WebView_prototype;

bool js_cocos2dx_experimental_webView_WebView_setOpacityWebView(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_setOpacityWebView : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_setOpacityWebView : Error processing arguments");
        cobj->setOpacityWebView(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_setOpacityWebView : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_canGoBack(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_canGoBack : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->canGoBack();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_canGoBack : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_loadHTMLString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_loadHTMLString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_loadHTMLString : Error processing arguments");
        cobj->loadHTMLString(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_loadHTMLString : Error processing arguments");
        cobj->loadHTMLString(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_loadHTMLString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_goForward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_goForward : Invalid Native Object");
    if (argc == 0) {
        cobj->goForward();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_goForward : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_goBack(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_goBack : Invalid Native Object");
    if (argc == 0) {
        cobj->goBack();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_goBack : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_setScalesPageToFit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_setScalesPageToFit : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_setScalesPageToFit : Error processing arguments");
        cobj->setScalesPageToFit(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_setScalesPageToFit : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_getOnDidFailLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_getOnDidFailLoading : Invalid Native Object");
    if (argc == 0) {
        cocos2d::experimental::ui::WebView::ccWebViewCallback ret = cobj->getOnDidFailLoading();
        JS::RootedValue jsret(cx);
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_getOnDidFailLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_loadFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_loadFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_loadFile : Error processing arguments");
        cobj->loadFile(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_loadFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_loadURL(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::experimental::ui::WebView* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_loadURL : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->loadURL(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->loadURL(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_loadURL : wrong number of arguments");
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_setBounces(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_setBounces : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_setBounces : Error processing arguments");
        cobj->setBounces(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_setBounces : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_evaluateJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_evaluateJS : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_evaluateJS : Error processing arguments");
        cobj->evaluateJS(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_evaluateJS : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_setBackgroundTransparent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_setBackgroundTransparent : Invalid Native Object");
    if (argc == 0) {
        cobj->setBackgroundTransparent();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_setBackgroundTransparent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_getOnJSCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_getOnJSCallback : Invalid Native Object");
    if (argc == 0) {
        cocos2d::experimental::ui::WebView::ccWebViewCallback ret = cobj->getOnJSCallback();
        JS::RootedValue jsret(cx);
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_getOnJSCallback : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_canGoForward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_canGoForward : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->canGoForward();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_canGoForward : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_getOnShouldStartLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_getOnShouldStartLoading : Invalid Native Object");
    if (argc == 0) {
        std::function<bool (cocos2d::experimental::ui::WebView *, const std::string&)> ret = cobj->getOnShouldStartLoading();
        JS::RootedValue jsret(cx);
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_getOnShouldStartLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_stopLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_stopLoading : Invalid Native Object");
    if (argc == 0) {
        cobj->stopLoading();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_stopLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_getOpacityWebView(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_getOpacityWebView : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getOpacityWebView();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_getOpacityWebView : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_reload(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_reload : Invalid Native Object");
    if (argc == 0) {
        cobj->reload();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_reload : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_setJavascriptInterfaceScheme(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_setJavascriptInterfaceScheme : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_webView_WebView_setJavascriptInterfaceScheme : Error processing arguments");
        cobj->setJavascriptInterfaceScheme(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_setJavascriptInterfaceScheme : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_getOnDidFinishLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::WebView* cobj = (cocos2d::experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_webView_WebView_getOnDidFinishLoading : Invalid Native Object");
    if (argc == 0) {
        cocos2d::experimental::ui::WebView::ccWebViewCallback ret = cobj->getOnDidFinishLoading();
        JS::RootedValue jsret(cx);
        #pragma warning NO CONVERSION FROM NATIVE FOR std::function;
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_getOnDidFinishLoading : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_webView_WebView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocos2d::experimental::ui::WebView::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::experimental::ui::WebView>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::experimental::ui::WebView"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_experimental_webView_WebView_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_experimental_webView_WebView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::experimental::ui::WebView* cobj = new (std::nothrow) cocos2d::experimental::ui::WebView();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::experimental::ui::WebView>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::experimental::ui::WebView"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_register_cocos2dx_experimental_webView_WebView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_experimental_ui_WebView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_experimental_ui_WebView_class->name = "WebView";
    jsb_cocos2d_experimental_ui_WebView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_ui_WebView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_experimental_ui_WebView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_ui_WebView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_experimental_ui_WebView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_experimental_ui_WebView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_experimental_ui_WebView_class->convert = JS_ConvertStub;
    jsb_cocos2d_experimental_ui_WebView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setOpacityWebView", js_cocos2dx_experimental_webView_WebView_setOpacityWebView, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("canGoBack", js_cocos2dx_experimental_webView_WebView_canGoBack, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadHTMLString", js_cocos2dx_experimental_webView_WebView_loadHTMLString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("goForward", js_cocos2dx_experimental_webView_WebView_goForward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("goBack", js_cocos2dx_experimental_webView_WebView_goBack, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScalesPageToFit", js_cocos2dx_experimental_webView_WebView_setScalesPageToFit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOnDidFailLoading", js_cocos2dx_experimental_webView_WebView_getOnDidFailLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadFile", js_cocos2dx_experimental_webView_WebView_loadFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadURL", js_cocos2dx_experimental_webView_WebView_loadURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBounces", js_cocos2dx_experimental_webView_WebView_setBounces, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("evaluateJS", js_cocos2dx_experimental_webView_WebView_evaluateJS, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundTransparent", js_cocos2dx_experimental_webView_WebView_setBackgroundTransparent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOnJSCallback", js_cocos2dx_experimental_webView_WebView_getOnJSCallback, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("canGoForward", js_cocos2dx_experimental_webView_WebView_canGoForward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOnShouldStartLoading", js_cocos2dx_experimental_webView_WebView_getOnShouldStartLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopLoading", js_cocos2dx_experimental_webView_WebView_stopLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOpacityWebView", js_cocos2dx_experimental_webView_WebView_getOpacityWebView, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reload", js_cocos2dx_experimental_webView_WebView_reload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setJavascriptInterfaceScheme", js_cocos2dx_experimental_webView_WebView_setJavascriptInterfaceScheme, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOnDidFinishLoading", js_cocos2dx_experimental_webView_WebView_getOnDidFinishLoading, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_experimental_webView_WebView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_ui_Widget_prototype);
    jsb_cocos2d_experimental_ui_WebView_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_experimental_ui_WebView_class,
        js_cocos2dx_experimental_webView_WebView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_experimental_ui_WebView_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "WebView"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::experimental::ui::WebView>(cx, jsb_cocos2d_experimental_ui_WebView_class, proto, parent_proto);
}

void register_all_cocos2dx_experimental_webView(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccui", &ns);

    js_register_cocos2dx_experimental_webView_WebView(cx, ns);
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
