//
//  js_bindings_ccbreader.cpp
//  watermelon
//
//  Created by Rohan Kuruvilla on 14/08/2012.
//
//

#include "js_bindings_ccbreader.h"
#include "ScriptingCore.h"
#include "js_bindings_config.h"

USING_NS_CC;
USING_NS_CC_EXT;

static void removeSelector(std::string &str) {
    size_t found;
    found = str.find(":");
    while (found!=std::string::npos){
        str.replace(found, found+1, "");
        found = str.find(":");
    }
}

SEL_MenuHandler CCBScriptCallbackProxy::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget,
                                                                       const char * pSelectorName) {
    this->callBackProp = pSelectorName;
    removeSelector(this->callBackProp);
    return menu_selector(CCBScriptCallbackProxy::menuItemCallback);
}

SEL_CCControlHandler CCBScriptCallbackProxy::onResolveCCBCCControlSelector(CCObject * pTarget,
                                                                           const char * pSelectorName) {
    
    this->callBackProp = pSelectorName;
    removeSelector(this->callBackProp);
    return cccontrol_selector(CCBScriptCallbackProxy::controlCallback);
}

bool CCBScriptCallbackProxy::onAssignCCBMemberVariable(CCObject * pTarget,
                                                       const char * pMemberVariableName,
                                                       CCNode * pNode) {
    return true;
}

void CCBScriptCallbackProxy::onNodeLoaded(CCNode * pNode,
                                          CCNodeLoader * pNodeLoader) {}

CCBSelectorResolver * CCBScriptCallbackProxy::createNew() {
    CCBScriptCallbackProxy * ret = new CCBScriptCallbackProxy();
    ret->setJSOwner(this->owner);
    return dynamic_cast<CCBSelectorResolver *>(ret);
}

void CCBScriptCallbackProxy::menuItemCallback(CCObject *pSender) {
    ScriptingCore::getInstance()->executeFunctionWithOwner(owner, callBackProp.c_str() );
}

void CCBScriptCallbackProxy::controlCallback(CCObject *pSender, CCControlEvent event) {
    ScriptingCore::getInstance()->executeFunctionWithOwner(owner, callBackProp.c_str() );
}

void CCBScriptCallbackProxy::setCallbackProperty(const char *prop) {
    callBackProp = prop;
}

void CCBScriptCallbackProxy::setJSOwner(jsval ownr) {
    owner = ownr;
}

jsval CCBScriptCallbackProxy::getJSOwner() {
    return owner;
}

JSBool js_cocos2dx_CCBAnimationManager_animationCompleteCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSObject *obj = JS_THIS_OBJECT(cx, vp);
		js_proxy_t *proxy = jsb_get_js_proxy(obj);
		cocos2d::extension::CCBAnimationManager *node = (cocos2d::extension::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
        
        JSCCBAnimationWrapper *tmpCobj = new JSCCBAnimationWrapper();
        tmpCobj->autorelease();
        
        tmpCobj->setJSCallbackThis(argv[0]);
        if(argc >= 2) {
            tmpCobj->setJSCallbackFunc(argv[1]);
        }
        
        node->setAnimationCompletedCallback(tmpCobj, callfunc_selector(JSCCBAnimationWrapper::animationCompleteCallback));
        
        JS_SetReservedSlot(proxy->obj, 0, argv[0]);
        JS_SetReservedSlot(proxy->obj, 1, argv[1]);
        return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool js_cocos2dx_CCBReader_readNodeGraphFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj;
    cocos2d::extension::CCBReader* cobj;
    obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::extension::CCBReader *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 2) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::CCObject* arg1;
        do {
            js_proxy_t *proxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
            proxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::CCObject*)(proxy ? proxy->ptr : NULL);
            TEST_NATIVE_OBJECT(cx, arg1)
        } while (0);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

        cocos2d::CCNode* ret = cobj->readNodeGraphFromFile(arg0, arg1);
        jsval jsret; do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    if (argc == 1) {
        const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        cocos2d::CCNode* ret = cobj->readNodeGraphFromFile(arg0);
        jsval jsret; do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    if (argc == 3) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::CCObject* arg1;
        do {
            js_proxy_t *proxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
            proxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::CCObject*)(proxy ? proxy->ptr : NULL);
            TEST_NATIVE_OBJECT(cx, arg1)
        } while (0);
        cocos2d::CCSize arg2;
        ok &= jsval_to_ccsize(cx, argv[2], &arg2);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
        cocos2d::CCNode* ret = cobj->readNodeGraphFromFile(arg0, arg1, arg2);
        jsval jsret; do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool js_cocos2dx_CCBReader_createSceneWithNodeGraphFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
	JSObject *obj;
	cocos2d::extension::CCBReader* cobj;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (cocos2d::extension::CCBReader *)(proxy ? proxy->ptr : NULL);
	TEST_NATIVE_OBJECT(cx, cobj)
    
	if (argc == 2) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		cocos2d::CCObject* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::CCObject*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, arg1)
		} while (0);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		cocos2d::CCScene* ret = cobj->createSceneWithNodeGraphFromFile(arg0, arg1);
		jsval jsret; do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCScene>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		cocos2d::CCScene* ret = cobj->createSceneWithNodeGraphFromFile(arg0);
		jsval jsret; do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCScene>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 3) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		cocos2d::CCObject* arg1;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
			proxy = jsb_get_js_proxy(tmpObj);
			arg1 = (cocos2d::CCObject*)(proxy ? proxy->ptr : NULL);
			TEST_NATIVE_OBJECT(cx, arg1)
		} while (0);
		cocos2d::CCSize arg2;
        ok &= jsval_to_ccsize(cx, argv[2], &arg2);
        
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        
		cocos2d::CCScene* ret = cobj->createSceneWithNodeGraphFromFile(arg0, arg1, arg2);
		jsval jsret; do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCScene>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
    
    return JS_FALSE;
}


JSBool js_CocosBuilder_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("", JSLayerLoader::loader());
    
    cocos2d::extension::CCBReader * ret = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ret->autorelease();
    
    jsval jsret;
    if (ret) {
        js_proxy_t *proxy = jsb_get_native_proxy(ret);
        if (proxy) {
            jsret = OBJECT_TO_JSVAL(proxy->obj);
        } else {
            // create a new js obj of that class
            proxy = js_get_or_create_proxy<cocos2d::extension::CCBReader>(cx, ret);
            jsret = OBJECT_TO_JSVAL(proxy->obj);
        }
    } else {
        jsret = JSVAL_NULL;
    }
    JS_SET_RVAL(cx, vp, jsret);
    return JS_TRUE;
    
}

extern JSObject* jsb_CCBReader_prototype;
extern JSObject* jsb_CCBAnimationManager_prototype;

void register_CCBuilderReader(JSContext *cx, JSObject *obj) {
    jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "cc", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "cc", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

    JSObject  *tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, obj, "(function () { return cc._Reader; })()"));
    JS_DefineFunction(cx, tmpObj, "create", js_CocosBuilder_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "loadScene", js_cocos2dx_CCBReader_createSceneWithNodeGraphFromFile, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCBReader_prototype, "load", js_cocos2dx_CCBReader_readNodeGraphFromFile, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCBAnimationManager_prototype, "setCompletedAnimationCallback", js_cocos2dx_CCBAnimationManager_animationCompleteCallback, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}
