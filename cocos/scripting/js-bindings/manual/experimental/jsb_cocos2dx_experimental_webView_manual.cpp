#include "jsb_cocos2dx_experimental_webView_manual.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "UIWebView.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

using namespace cocos2d;


static bool jsb_cocos2dx_experimental_webView_setOnShouldStartLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    experimental::ui::WebView* cobj = (experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(0)));
        cobj->setOnShouldStartLoading([=](experimental::ui::WebView *sender, const std::string &url)->bool{
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
            {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval arg[2];
                js_proxy_t *proxy = js_get_or_create_proxy(cx, sender);
                if(proxy)
                    arg[0] = OBJECT_TO_JSVAL(proxy->obj);
                else
                    arg[0] = JSVAL_NULL;
                arg[1] = std_string_to_jsval(cx, url);
                JS::RootedValue rval(cx);

                bool ok = func->invoke(2, arg, &rval);
                if (!ok && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            });
            return true;
        });
        return true;
    }
}

static bool jsb_cocos2dx_experimental_webView_setOnDidFinishLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    experimental::ui::WebView* cobj = (experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(0)));
        cobj->setOnDidFinishLoading([=](experimental::ui::WebView *sender, const std::string &url)->void{
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
            {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval arg[2];
                js_proxy_t *proxy = js_get_or_create_proxy(cx, sender);
                if(proxy)
                    arg[0] = OBJECT_TO_JSVAL(proxy->obj);
                else
                    arg[0] = JSVAL_NULL;
                arg[1] = std_string_to_jsval(cx, url);
                JS::RootedValue rval(cx);

                bool ok = func->invoke(2, arg, &rval);
                if (!ok && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            });
        });
        return true;
    }
}

static bool jsb_cocos2dx_experimental_webView_setOnDidFailLoading(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    experimental::ui::WebView* cobj = (experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(0)));
        cobj->setOnDidFailLoading([=](experimental::ui::WebView *sender, const std::string &url)->void{
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
            {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval arg[2];
                js_proxy_t *proxy = js_get_or_create_proxy(cx, sender);
                if(proxy)
                    arg[0] = OBJECT_TO_JSVAL(proxy->obj);
                else
                    arg[0] = JSVAL_NULL;
                arg[1] = std_string_to_jsval(cx, url);
                JS::RootedValue rval(cx);

                bool ok = func->invoke(2, arg, &rval);
                if (!ok && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            });
        });
        return true;
    }
}

static bool jsb_cocos2dx_experimental_webView_setOnJSCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    experimental::ui::WebView* cobj = (experimental::ui::WebView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if(argc == 1){
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, obj, args.get(0)));
        cobj->setOnJSCallback([=](experimental::ui::WebView *sender, const std::string &url)->void{
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
            {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval arg[2];
                js_proxy_t *proxy = js_get_or_create_proxy(cx, sender);
                if(proxy)
                    arg[0] = OBJECT_TO_JSVAL(proxy->obj);
                else
                    arg[0] = JSVAL_NULL;
                arg[1] = std_string_to_jsval(cx, url);
                JS::RootedValue rval(cx);

                bool ok = func->invoke(2, arg, &rval);
                if (!ok && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            });
        });
        return true;
    }
}
extern JSObject* jsb_cocos2d_experimental_ui_WebView_prototype;

void register_all_cocos2dx_experimental_webView_manual(JSContext* cx, JS::HandleObject global)
{
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_experimental_ui_WebView_prototype), "setOnShouldStartLoading", jsb_cocos2dx_experimental_webView_setOnShouldStartLoading, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_experimental_ui_WebView_prototype), "setOnDidFinishLoading", jsb_cocos2dx_experimental_webView_setOnDidFinishLoading, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_experimental_ui_WebView_prototype), "setOnDidFailLoading", jsb_cocos2dx_experimental_webView_setOnDidFailLoading, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_experimental_ui_WebView_prototype), "setOnJSCallback", jsb_cocos2dx_experimental_webView_setOnJSCallback, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}

#endif
