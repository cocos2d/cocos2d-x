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
#include "cocosbuilder_specifics.hpp"
#include "cocosbuilder/CocosBuilder.h"

class CCBScriptCallbackProxy:  public cocos2d::Layer
, public cocosbuilder::CCBSelectorResolver
, public cocosbuilder::CCBMemberVariableAssigner {
    
    std::string callBackProp;
    jsval owner;

public:


    CCBScriptCallbackProxy () {}
    virtual ~CCBScriptCallbackProxy() {}

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBScriptCallbackProxy, create);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget,
                                                                    const char * pSelectorName);

    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget,
                                                                                   const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName,
                                           cocos2d::Node * pNode);
    virtual void onNodeLoaded(cocos2d::Node * pNode,
                              cocosbuilder::NodeLoader * pNodeLoader);
        
    virtual CCBSelectorResolver * createNew();
    void menuItemCallback(Object *pSender);
    void controlCallback(Object *pSender, cocos2d::extension::Control::EventType event);
    void setCallbackProperty(const char *prop);
    void setJSOwner(jsval ownr);
    jsval getJSOwner();
};


class JSLayerLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(JSLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBScriptCallbackProxy);
};

void register_CCBuilderReader(JSContext *cx, JSObject *global);
JSBool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_BINDINGS_CCBREADER_H__ */

