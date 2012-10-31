//
//  js_bindings_ccbreader.cpp
//  watermelon
//
//  Created by Rohan Kuruvilla on 14/08/2012.
//
//

#include "js_bindings_ccbreader.h"
#include "ScriptingCore.h"

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
                                                                       cocos2d::CCString * pSelectorName) {
    this->callBackProp = pSelectorName->getCString();
    removeSelector(this->callBackProp);
    return menu_selector(CCBScriptCallbackProxy::menuItemCallback);
}

SEL_CCControlHandler CCBScriptCallbackProxy::onResolveCCBCCControlSelector(CCObject * pTarget,
                                                                           CCString * pSelectorName) {
    
    this->callBackProp = pSelectorName->getCString();
    removeSelector(this->callBackProp);
    return cccontrol_selector(CCBScriptCallbackProxy::controlCallback);
}

bool CCBScriptCallbackProxy::onAssignCCBMemberVariable(CCObject * pTarget,
                                                       CCString * pMemberVariableName,
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
    ScriptingCore::getInstance()->executeFunctionWithOwner(owner, callBackProp.c_str() , JSVAL_NULL);
}

void CCBScriptCallbackProxy::controlCallback(CCObject *pSender, CCControlEvent event) {
    ScriptingCore::getInstance()->executeFunctionWithOwner(owner, callBackProp.c_str() , JSVAL_NULL);
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


static CCNode* loadReader(const char *file, jsval owner) {
    /* Create an autorelease CCNodeLoaderLibrary. */
    
    /* Create an autorelease CCBReader. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("", JSLayerLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    ccbReader->hasScriptingOwner = true;
    
    CCBScriptCallbackProxy *ccBCallbackProxy = new CCBScriptCallbackProxy();
    ccBCallbackProxy->setJSOwner(owner);
    //ccbReader->setOwner(dynamic_cast<CCObject *>(ccBCallbackProxy));
    
    //CCBSelectorResolver * targetAsCCBSelectorResolver = dynamic_cast<CCBSelectorResolver *>(ccBCallbackProxy);
    
    CCNode * node = ccbReader->readNodeGraphFromFile(file, dynamic_cast<CCObject *>(ccBCallbackProxy));
    
    return node;
}


JSBool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
		jsval *argv = JS_ARGV(cx, vp);
		const char *arg0;
        do {
            JSString *tmp = JS_ValueToString(cx, argv[0]);
            arg0 = JS_EncodeString(cx, tmp);
        }
        while (0);
      
        jsval obj =  argc >= 2 ? argv[1] : JSVAL_NULL;
		if (obj.isObject()) {
			CCLOG("%p: + ", JSVAL_TO_OBJECT(obj));
		}
        CCNode * ret = loadReader(arg0, obj);
        jsval jsret;
		if (ret) {
			js_proxy_t *proxy;
			JS_GET_PROXY(proxy, ret);
			if (proxy) {
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				// create a new js obj of that class
				proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			}
		} else {
			jsret = JSVAL_NULL;
		}
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;

    }
    return JS_FALSE;
}


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

	JSObject *ccReader = JS_NewObject(cx, NULL, NULL, NULL);
	jsval valObj = OBJECT_TO_JSVAL(ccReader);
	JS_SetProperty(cx, ns, "Reader", &valObj);

	JS_DefineFunction(cx, ccReader, "load", js_CocosBuilder_Run, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}
