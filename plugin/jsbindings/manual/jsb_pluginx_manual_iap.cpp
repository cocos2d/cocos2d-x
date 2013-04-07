#include "jsb_pluginx_manual_iap.h"
#include "jsb_pluginx_basic_conversions.h"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "ProtocolIAPOnLine.h"

using namespace pluginx;

static JSContext* s_cx = NULL;

class Pluginx_PurchaseResult : public cocos2d::plugin::PayResultListener
{
public:
    virtual void payResult(cocos2d::plugin::EPayResult ret, const char* msg, cocos2d::plugin::TProductInfo info)
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
        
        JSObject* obj = m_pJSDelegate;
        
        if (JS_HasProperty(cx, obj, "payResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "payResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "payResult",
                                3, dataVal, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }

private:
    JSObject* m_pJSDelegate;
};

JSBool js_pluginx_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_PurchaseResult* nativeDelegate = new Pluginx_PurchaseResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cocos2d::plugin::ProtocolIAP::setResultListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class Pluginx_PurchaseLocalResult : public cocos2d::plugin::LocalResultListener
{
public:
    virtual void payFailedLocally(cocos2d::plugin::EPayResult ret, const char* msg)
    {
        JSContext* cx = s_cx;

        JSBool hasAction;
        jsval retval;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        JSObject* obj = m_pJSDelegate;
        JSBool bRet = JS_HasProperty(cx, obj, "payFailedLocally", &hasAction);
        if (bRet && hasAction) {
            if(!JS_GetProperty(cx, obj, "payFailedLocally", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, "payFailedLocally",
                                2, dataVal, &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }

private:
    JSObject* m_pJSDelegate;
};

JSBool js_pluginx_ProtocolIAPOnLine_setLocalResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        Pluginx_PurchaseLocalResult* nativeDelegate = new Pluginx_PurchaseLocalResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cocos2d::plugin::ProtocolIAPOnLine::setLocalResultListener(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}
