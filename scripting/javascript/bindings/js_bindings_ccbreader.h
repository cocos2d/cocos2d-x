//
//  js_bindings_ccbreader.h
//  watermelon
//
//  Created by Rohan Kuruvilla on 14/08/2012.
//
//
#ifndef __JS_BINDINGS_CCBREADER_H__
#define __JS_BINDINGS_CCBREADER_H__

#include "jsapi.h"
#include "cocos-ext.h"
#include "cocos2d_specifics.hpp"


class CCBScriptCallbackProxy:  public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner {
    
    std::string callBackProp;
    jsval owner;

public:


    CCBScriptCallbackProxy () {}
    virtual ~CCBScriptCallbackProxy() {}

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBScriptCallbackProxy, create);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget,
                                                                    const char * pSelectorName);

    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget,
                                                                                   const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName,
                                           cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode,
                              cocos2d::extension::CCNodeLoader * pNodeLoader);
        
    virtual CCBSelectorResolver * createNew();
    void menuItemCallback(CCObject *pSender);
    void controlCallback(CCObject *pSender, cocos2d::extension::CCControlEvent event);
    void setCallbackProperty(const char *prop);
    void setJSOwner(jsval ownr);
    jsval getJSOwner();
};


class JSLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(JSLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBScriptCallbackProxy);
};

void register_CCBuilderReader(JSContext *cx, JSObject *global);
JSBool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_BINDINGS_CCBREADER_H__ */

