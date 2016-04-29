#include "jsb_pluginx_manual_callback.h"
#include "jsb_pluginx_basic_conversions.h"
#include "jsb_pluginx_spidermonkey_specifics.h"
#include "ProtocolAds.h"
#include "AgentManager.h"
#include "FacebookAgent.h"

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
        
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);
        
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);
        jsval dataVal[3];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        dataVal[2] = TProductInfo_to_jsval(cx, info);
        
        
        if (JS_HasProperty(cx, obj, "onPayResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onPayResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }

            JS_CallFunctionName(cx, obj, "onPayResult", JS::HandleValueArray::fromMarkedLocation(3, dataVal), &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    JSObject* getJSDelegate()
    {
        return _JSDelegate;
    }
    
    virtual void onRequestProductsResult(cocos2d::plugin::IAPProductRequest ret, cocos2d::plugin::TProductList info){
        JSContext* cx = s_cx;
        
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);
        
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(ret);
        if(info.size() > 0){
            dataVal[1] = TProductList_to_jsval(cx, info);
        }
        
        if (JS_HasProperty(cx, obj, "onRequestProductResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onRequestProductResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            
            JS_CallFunctionName(cx, obj, "onRequestProductResult", JS::HandleValueArray::fromMarkedLocation(2, dataVal), &retval);
        }

    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

bool js_pluginx_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    bool ok = true;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        Pluginx_PurchaseResult* nativeDelegate = new Pluginx_PurchaseResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setResultListener(nativeDelegate);
        
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_pluginx_ProtocolIAP_getResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_ProtocolIAP_getResultListener : Invalid Native Object");
	if (argc == 0) {
		Pluginx_PurchaseResult* listener = (Pluginx_PurchaseResult*)cobj->getResultListener();
        JSObject *ret = listener->getJSDelegate();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				jsret = OBJECT_TO_JSVAL(ret);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().setUndefined();
		return true;
	}
    
	JS_ReportError(cx, "js_pluginx_ProtocolIAP_getResultListener : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_pluginx_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolIAP* cobj = (cocos2d::plugin::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolIAP_payForProduct : Invalid Native Object");
    if (argc == 1) {
        cocos2d::plugin::TProductInfo arg0;
        ok &= pluginx::jsval_to_TProductInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolIAP_payForProduct : Error processing arguments");
        cobj->payForProduct(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    if(argc == 2){
        cocos2d::plugin::TProductInfo arg0;
        ok &= pluginx::jsval_to_TProductInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolIAP_payForProduct : Error processing arguments");
        
        std::function<void (int, std::string&)> arg1;
        do {
            std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(1)));
            auto lambda = [=](int larg0, std::string& larg1) -> void {
                JSAutoCompartment ac(cx, obj);
                jsval largv[2];
                largv[0] = int32_to_jsval(cx, larg0);
                largv[1] = std_string_to_jsval(cx, larg1);
                JS::RootedValue rval(cx);
                bool succeed = func->invoke(2, &largv[0], &rval);
                if (!succeed && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
            arg1 = lambda;
        } while(0);
        
        cobj->payForProduct(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_pluginx_protocols_ProtocolIAP_payForProduct : wrong number of arguments");
    return false;
}

class Pluginx_AdsListener : public cocos2d::plugin::AdsListener
{
public:

    virtual void onAdsResult(AdsResultCode code, const char* msg)
    {
        JSContext* cx = s_cx;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(code);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        bool bRet = JS_HasProperty(cx, obj, "onAdsResult", &hasAction);
        if (bRet && hasAction) {
            if(!JS_GetProperty(cx, obj, "onAdsResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JS_CallFunctionName(cx, obj, "onAdsResult", JS::HandleValueArray::fromMarkedLocation(2, dataVal), &retval);
        }
    }

    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points)
    {
        JSContext* cx = s_cx;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);

        js_proxy_t * p;
        JS_GET_PROXY(p, pAdsPlugin);
        
        if (! p) return;
        jsval dataVal[2];
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        dataVal[0] = arg;
        dataVal[1] = INT_TO_JSVAL(points);
        
        bool bRet = JS_HasProperty(cx, obj, "onPlayerGetPoints", &hasAction);
        if (bRet && hasAction) {
            if(!JS_GetProperty(cx, obj, "onPlayerGetPoints", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JS_CallFunctionName(cx, obj, "onPlayerGetPoints", JS::HandleValueArray::fromMarkedLocation(2, dataVal), &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    JSObject* getJSDelegate()
    {
        return _JSDelegate;
    }

private:
    JS::Heap<JSObject*> _JSDelegate;
};

bool js_pluginx_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    bool ok = true;
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        Pluginx_AdsListener* nativeDelegate = new Pluginx_AdsListener();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setAdsListener(nativeDelegate);
        
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_pluginx_ProtocolAds_getAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolAds* cobj = (cocos2d::plugin::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_ProtocolAds_getAdsListener : Invalid Native Object");
	if (argc == 0) {
		Pluginx_AdsListener* listener = (Pluginx_AdsListener*)cobj->getAdsListener();
        JSObject *ret = listener->getJSDelegate();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				jsret = OBJECT_TO_JSVAL(ret);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		args.rval().set(jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_pluginx_ProtocolAds_getAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

class Pluginx_ShareResult : public cocos2d::plugin::ShareResultListener
{
public:
    virtual void onShareResult(cocos2d::plugin::ShareResultCode ret, const char* msg)
    {
        JSContext* cx = s_cx;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        if (JS_HasProperty(cx, obj, "onShareResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onShareResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JS_CallFunctionName(cx, obj, "onShareResult", JS::HandleValueArray::fromMarkedLocation(2, dataVal), &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    
    JSObject* getJSDelegate()
    {
        return _JSDelegate;
    }

private:
    JS::Heap<JSObject*> _JSDelegate;
};

bool js_pluginx_ProtocolShare_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
    bool ok = true;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        Pluginx_ShareResult* nativeDelegate = new Pluginx_ShareResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setResultListener(nativeDelegate);
        
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_pluginx_ProtocolShare_getResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_ProtocolShare_getResultListener : Invalid Native Object");
	if (argc == 0) {
		Pluginx_ShareResult* listener = (Pluginx_ShareResult*)cobj->getResultListener();
        JSObject *ret = listener->getJSDelegate();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				jsret = OBJECT_TO_JSVAL(ret);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		args.rval().set(jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_pluginx_ProtocolShare_getResultListener : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_pluginx_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolShare* cobj = (cocos2d::plugin::ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolShare_share : Invalid Native Object");
    if (argc == 1) {
        cocos2d::plugin::TShareInfo arg0;
        ok &= pluginx::jsval_to_TShareInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolShare_share : Error processing arguments");
        cobj->share(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    if(argc == 2){
        cocos2d::plugin::TShareInfo arg0;
        ok &= pluginx::jsval_to_TShareInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolShare_share : Error processing arguments");
        
        std::function<void (int, std::string&)> arg1;
        do {
            std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(1)));
            auto lambda = [=](int larg0, std::string& larg1) -> void {
                JSAutoCompartment ac(cx, obj);
                jsval largv[2];
                largv[0] = int32_to_jsval(cx, larg0);
                largv[1] = std_string_to_jsval(cx, larg1);
                JS::RootedValue rval(cx);
                bool succeed = func->invoke(2, &largv[0], &rval);
                if (!succeed && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
            arg1 = lambda;
        } while(0);
        
        cobj->share(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_pluginx_protocols_ProtocolShare_share : wrong number of arguments");
    return false;
}

class Pluginx_SocialResult : public cocos2d::plugin::SocialListener
{
public:
    virtual void onSocialResult(cocos2d::plugin::SocialRetCode ret, const char* msg)
    {
        JSContext* cx = s_cx;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);
        jsval dataVal[2];
        dataVal[0] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[1] = std_string_to_jsval(cx, strMsgInfo);
        
        if (JS_HasProperty(cx, obj, "onSocialResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onSocialResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JS_CallFunctionName(cx, obj, "onSocialResult", JS::HandleValueArray::fromMarkedLocation(2, dataVal), &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    
    JSObject* getJSDelegate()
    {
        return _JSDelegate;
    }

private:
    JS::Heap<JSObject*> _JSDelegate;
};

bool js_pluginx_ProtocolSocial_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    bool ok = true;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        Pluginx_SocialResult* nativeDelegate = new Pluginx_SocialResult();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setListener(nativeDelegate);
        
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_pluginx_ProtocolSocial_getListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_ProtocolSocial_getListener : Invalid Native Object");
	if (argc == 0) {
		Pluginx_SocialResult* listener = (Pluginx_SocialResult*)cobj->getListener();
        JSObject *ret = listener->getJSDelegate();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				jsret = OBJECT_TO_JSVAL(ret);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		args.rval().set(jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_pluginx_ProtocolSocial_getListener : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_pluginx_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_submitScore : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        long arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_long(cx, args.get(1), (long *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_submitScore : Error processing arguments");
        cobj->submitScore(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    
    if(argc == 3){
        const char* arg0;
        long arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_long(cx, args.get(1), (long *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_submitScore : Error processing arguments");
        
        std::function<void (int, std::string&)> arg2;
        do {
            std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(2)));
            auto lambda = [=](int larg0, std::string& larg1) -> void {
                JSAutoCompartment ac(cx, obj);
                jsval largv[2];
                largv[0] = int32_to_jsval(cx, larg0);
                largv[1] = std_string_to_jsval(cx, larg1);
                JS::RootedValue rval(cx);
                bool succeed = func->invoke(2, &largv[0], &rval);
                if (!succeed && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
            arg2 = lambda;
        } while(0);
        
        cobj->submitScore(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_submitScore : wrong number of arguments");
    return false;
}

bool js_pluginx_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolSocial* cobj = (cocos2d::plugin::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : Invalid Native Object");
    if (argc == 1) {
        cocos2d::plugin::TAchievementInfo arg0;
        ok &= pluginx::jsval_to_TAchievementInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : Error processing arguments");
        cobj->unlockAchievement(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    if(argc ==2){
        cocos2d::plugin::TAchievementInfo arg0;
        ok &= pluginx::jsval_to_TAchievementInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : Error processing arguments");
        
        std::function<void (int, std::string&)> arg1;
        do {
            std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(1)));
            auto lambda = [=](int larg0, std::string& larg1) -> void {
                JSAutoCompartment ac(cx, obj);
                jsval largv[2];
                largv[0] = int32_to_jsval(cx, larg0);
                largv[1] = std_string_to_jsval(cx, larg1);
                JS::RootedValue rval(cx);
                bool succeed = func->invoke(2, &largv[0], &rval);
                if (!succeed && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
            arg1 = lambda;
        } while(0);
        
        cobj->unlockAchievement(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_pluginx_protocols_ProtocolSocial_unlockAchievement : wrong number of arguments");
    return false;
}

class Pluginx_UserActionListener : public cocos2d::plugin::UserActionListener
{
public:
    virtual void onActionResult(ProtocolUser* userPlugin, cocos2d::plugin::UserActionResultCode ret, const char* msg)
    {
        JSContext* cx = s_cx;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue temp_retval(cx);

        js_proxy_t * p;
        JS_GET_PROXY(p, userPlugin);
        
        if (! p) return;
        jsval dataVal[3];
        jsval arg1 = OBJECT_TO_JSVAL(p->obj);
        dataVal[0] = arg1;
        dataVal[1] = INT_TO_JSVAL(ret);
        std::string strMsgInfo = msg;
        dataVal[2] = std_string_to_jsval(cx, strMsgInfo);
        
        if (JS_HasProperty(cx, obj, "onActionResult", &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, "onActionResult", &temp_retval)) {
                return;
            }
            if(temp_retval == JSVAL_VOID) {
                return;
            }
            JS_CallFunctionName(cx, obj, "onActionResult", JS::HandleValueArray::fromMarkedLocation(3, dataVal), &retval);
        }
    }

    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    
    JSObject* getJSDelegate()
    {
        return _JSDelegate;
    }

private:
    JS::Heap<JSObject*> _JSDelegate;
};

bool js_pluginx_ProtocolUser_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    bool ok = true;

    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        Pluginx_UserActionListener* nativeDelegate = new Pluginx_UserActionListener();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setActionListener(nativeDelegate);
        
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_pluginx_ProtocolUser_getActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_ProtocolUser_getActionListener : Invalid Native Object");
	if (argc == 0) {
		Pluginx_UserActionListener* listener = (Pluginx_UserActionListener*)cobj->getActionListener();
        JSObject *ret = listener->getJSDelegate();
		jsval jsret = JSVAL_NULL;
		do {
			if (ret) {
				jsret = OBJECT_TO_JSVAL(ret);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		args.rval().set(jsret);
		return true;
	}
    
	JS_ReportError(cx, "js_pluginx_ProtocolUser_getActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}

bool js_pluginx_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_login : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->login();
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    do {
        if (argc == 1) {
            std::function<void (int, std::string&)> arg0;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(0)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    largv[1] = std_string_to_jsval(cx, larg1);
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg0 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->login(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_login : wrong number of arguments");
    return false;
}

bool js_pluginx_ProtocolUser_logout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::ProtocolUser* cobj = (cocos2d::plugin::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_ProtocolUser_logout : Invalid Native Object");
    if (argc == 0) {
        cobj->logout();
        args.rval().setUndefined();
        return true;
    }
    
    do {
        if (argc == 1) {
            std::function<void (int, std::string&)> arg0;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(0)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    largv[1] = std_string_to_jsval(cx, larg1);
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg0 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->logout(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_pluginx_protocols_ProtocolUser_logout : wrong number of arguments");
    return false;
}


bool js_pluginx_FacebookAgent_login(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::FacebookAgent* cobj = (cocos2d::plugin::FacebookAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_FacebookAgent_login : Invalid Native Object");
    
    do {
        if (argc == 1) {
            std::function<void (int, std::string&)> arg0;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(0)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    jsval temp = std_string_to_jsval(cx, larg1);
                    JS::RootedValue outVal(cx);
//                    size_t utf16Count = 0;
//                    const jschar* utf16Buf = JS_GetStringCharsZAndLength(cx, JSVAL_TO_STRING(temp), &utf16Count);
//                    JS_ParseJSON(cx, utf16Buf, static_cast<uint32_t>(utf16Count), &outVal);
                    JS_ParseJSON(cx, JS::RootedString(cx, temp.toString()), &outVal);
                    largv[1] = outVal.get();
                    
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg0 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->login(arg0);
            args.rval().setUndefined();
            return true;
        }
        
        if (argc == 2) {
            std::string arg0;
            ok &= pluginx::jsval_array_to_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_FacebookAgent_login : Error processing arguments");
            if (!ok) { ok = true; break; }
            
            std::function<void (int, std::string&)> arg1;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(1)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    jsval temp = std_string_to_jsval(cx, larg1);
                    JS::RootedValue outVal(cx);
//                    size_t utf16Count = 0;
//                    const jschar* utf16Buf = JS_GetStringCharsZAndLength(cx, JSVAL_TO_STRING(temp), &utf16Count);
//                    JS_ParseJSON(cx, utf16Buf, static_cast<uint32_t>(utf16Count), &outVal);
                    JS_ParseJSON(cx, JS::RootedString(cx, temp.toString()), &outVal);
                    largv[1] = outVal.get();
                    
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg1 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->login(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    
    JS_ReportError(cx, "js_pluginx_protocols_FacebookAgent_login : wrong number of arguments");
    return false;
}

bool js_pluginx_FacebookAgent_api(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::FacebookAgent* cobj = (cocos2d::plugin::FacebookAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_FacebookAgent_api : Invalid Native Object");
    
    do {
        if (argc == 4) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            int arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cocos2d::plugin::TShareInfo arg2;
            ok &= pluginx::jsval_to_FBInfo(cx, args.get(2), &arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_FacebookAgent_api : Error processing arguments");
            if (!ok) { ok = true; break; }
            
            std::function<void (int, std::string&)> arg3;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(3)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    largv[1] = std_string_to_jsval(cx, larg1);
                    
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg3 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->api(arg0, arg1, arg2, arg3);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_pluginx_protocols_FacebookAgent_api : wrong number of arguments");
    return false;
}

bool js_pluginx_FacebookAgent_appRequest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::FacebookAgent* cobj = (cocos2d::plugin::FacebookAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_FacebookAgent_appRequest : Invalid Native Object");
    
    do {
        if (argc == 2) {
            cocos2d::plugin::TShareInfo arg0;
            ok &= pluginx::jsval_to_TShareInfo(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_FacebookAgent_appRequest : Error processing arguments");
            if (!ok) { ok = true; break; }
            
            std::function<void (int, std::string&)> arg1;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(1)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    jsval temp = std_string_to_jsval(cx, larg1);
                    JS::RootedValue outVal(cx);
//                    size_t utf16Count = 0;
//                    const jschar* utf16Buf = JS_GetStringCharsZAndLength(cx, JSVAL_TO_STRING(temp), &utf16Count);
//                    JS_ParseJSON(cx, utf16Buf, static_cast<uint32_t>(utf16Count), &outVal);
                    JS_ParseJSON(cx, JS::RootedString(cx, temp.toString()), &outVal);
                    largv[1] = outVal.get();
                    
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg1 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->appRequest(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_pluginx_protocols_FacebookAgent_appRequest : wrong number of arguments");
    return false;
}

bool js_pluginx_FacebookAgent_dialog(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::plugin::FacebookAgent* cobj = (cocos2d::plugin::FacebookAgent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_pluginx_protocols_FacebookAgent_dialog : Invalid Native Object");
    
    do {
        if (argc == 2) {
            cocos2d::plugin::TShareInfo arg0;
            ok &= pluginx::jsval_to_TShareInfo(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_pluginx_protocols_FacebookAgent_dialog : Error processing arguments");
            if (!ok) { ok = true; break; }
            
            std::function<void (int, std::string&)> arg1;
            do {
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(1)));
                auto lambda = [=](int larg0, std::string& larg1) -> void {
                    JSAutoCompartment ac(cx, obj);
                    jsval largv[2];
                    largv[0] = int32_to_jsval(cx, larg0);
                    jsval temp = std_string_to_jsval(cx, larg1);
                    JS::RootedValue outVal(cx);
//                    size_t utf16Count = 0;
//                    const jschar* utf16Buf = JS_GetStringCharsZAndLength(cx, JSVAL_TO_STRING(temp), &utf16Count);
//                    JS_ParseJSON(cx, utf16Buf, static_cast<uint32_t>(utf16Count), &outVal);
                    JS_ParseJSON(cx, JS::RootedString(cx, temp.toString()), &outVal);
                    largv[1] = outVal.get();
                    
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(2, &largv[0], &rval);
                    if (!succeed && JS_IsExceptionPending(cx)) {
                        JS_ReportPendingException(cx);
                    }
                };
                arg1 = lambda;
            } while(0);
            
            if (!ok) { ok = true; break; }
            cobj->dialog(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_pluginx_protocols_FacebookAgent_dialog : wrong number of arguments");
    return false;
}