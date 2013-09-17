#include "jsb_pluginx_manual_callback.h"
#include "jsb_pluginx_basic_conversions.h"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "ProtocolAds.h"

using namespace pluginx;

static JSContext* s_cx = NULL;

class Pluginx_PurchaseResult : public cocos2d::plugin::PayResultListener
{
public:
    virtual void onPayResult(cocos2d::plugin::PayResultCode ret, const char* msg, cocos2d::plugin::TProductInfo info)
    {
        char goodInfo[1024] = { 0 };
        sprintf(goodInfo, "商品名称:%s\n商品价格:%s\n商品描述:%s",
                info.find("productName")->second.c_str(),
                info.find("productPrice")->second.c_str(),
                info.find("productDesc")->second.c_str());
        LOGD(goodInfo);
        
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;
        jsval dataVal[3];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        dataVal[2] = TProductInfo_to_jsval(cx, info);
        
        JSObject* obj = _JSDelegate;
        
        if (JS_HasProperty(cx, obj, "onPayResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onPayResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "onPayResult",
                                3, dataVal, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }

private:
    JSObject* _JSDelegate;
};

JSBool js_pluginx_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSBool ok = JS_TRUE;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_PurchaseResult* nativeDelegate = new Pluginx_PurchaseResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setResultListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class Pluginx_AdsListener : public cocos2d::plugin::AdsListener
{
public:

    virtual void onAdsResult(AdsResultCode code, const char* msg)
    {
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(code);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        JSObject* obj = _JSDelegate;
        JSBool bRet = JS_HasProperty(cx, obj, "onAdsResult", &hasAction);
        if (bRet && hasAction) {
            if(!JS_GetProperty(cx, obj, "onAdsResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "onAdsResult",
                                2, dataVal, &retval);
        }
    }

    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points)
    {
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;

        js_proxy_t * p;
        JS_GET_PROXY(p, pAdsPlugin);
        
        if (! p) return;
        jsval dataVal[2];
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        dataVal[0] = arg;
        dataVal[1] = INT_TO_JSVAL(points);
        
        JSObject* obj = _JSDelegate;
        JSBool bRet = JS_HasProperty(cx, obj, "onPlayerGetPoints", &hasAction);
        if (bRet && hasAction) {
            if(!JS_GetProperty(cx, obj, "onPlayerGetPoints", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "onPlayerGetPoints",
                                2, NULL, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }

private:
    JSObject* _JSDelegate;
};

JSBool js_pluginx_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_AdsListener* nativeDelegate = new Pluginx_AdsListener();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setAdsListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class Pluginx_ShareResult : public cocos2d::plugin::ShareResultListener
{
public:
    virtual void onShareResult(cocos2d::plugin::ShareResultCode ret, const char* msg)
    {
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        JSObject* obj = _JSDelegate;
        
        if (JS_HasProperty(cx, obj, "onShareResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onShareResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "onShareResult",
                                2, dataVal, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }

private:
    JSObject* _JSDelegate;
};

JSBool js_pluginx_ProtocolShare_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSBool ok = JS_TRUE;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_ShareResult* nativeDelegate = new Pluginx_ShareResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setResultListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class Pluginx_SocialResult : public cocos2d::plugin::SocialListener
{
public:
    virtual void onSocialResult(cocos2d::plugin::SocialRetCode ret, const char* msg)
    {
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        JSObject* obj = _JSDelegate;
        
        if (JS_HasProperty(cx, obj, "onSocialResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onSocialResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "onSocialResult",
                                2, dataVal, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }

private:
    JSObject* _JSDelegate;
};

JSBool js_pluginx_ProtocolSocial_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSBool ok = JS_TRUE;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_SocialResult* nativeDelegate = new Pluginx_SocialResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class Pluginx_UserActionListener : public cocos2d::plugin::UserActionListener
{
public:
    virtual void onActionResult(ProtocolUser* userPlugin, cocos2d::plugin::UserActionResultCode ret, const char* msg)
    {
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;

        js_proxy_t * p;
        JS_GET_PROXY(p, userPlugin);
        
        if (! p) return;
        jsval dataVal[3];
        jsval arg1 = OBJECT_TO_JSVAL(p->obj);
        dataVal[0] = arg1;
        dataVal[1] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[2] = std_string_to_jsval(cx, strMsgInfo);
        
        JSObject* obj = _JSDelegate;
        
        if (JS_HasProperty(cx, obj, "onActionResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onActionResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "onActionResult",
                                3, dataVal, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }

private:
    JSObject* _JSDelegate;
};

JSBool js_pluginx_ProtocolUser_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSBool ok = JS_TRUE;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_UserActionListener* nativeDelegate = new Pluginx_UserActionListener();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setActionListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

