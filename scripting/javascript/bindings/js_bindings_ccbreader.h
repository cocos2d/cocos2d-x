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


class CCBScriptCallbackProxy:  public cc::Layer
, public cc::extension::CCBSelectorResolver
, public cc::extension::CCBMemberVariableAssigner {
    
    std::string callBackProp;
    jsval owner;

public:


    CCBScriptCallbackProxy () {}
    virtual ~CCBScriptCallbackProxy() {}

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBScriptCallbackProxy, create);
    virtual cc::SEL_MenuHandler onResolveCCBMenuItemSelector(cc::Object * pTarget,
                                                                    const char * pSelectorName);

    virtual cc::extension::SEL_CCControlHandler onResolveCCBControlSelector(cc::Object * pTarget,
                                                                                   const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cc::Object * pTarget, const char * pMemberVariableName,
                                           cc::Node * pNode);
    virtual void onNodeLoaded(cc::Node * pNode,
                              cc::extension::NodeLoader * pNodeLoader);
        
    virtual CCBSelectorResolver * createNew();
    void menuItemCallback(Object *pSender);
    void controlCallback(Object *pSender, cc::extension::ControlEvent event);
    void setCallbackProperty(const char *prop);
    void setJSOwner(jsval ownr);
    jsval getJSOwner();
};


class JSLayerLoader : public cc::extension::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(JSLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCBScriptCallbackProxy);
};

void register_CCBuilderReader(JSContext *cx, JSObject *global);
JSBool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_BINDINGS_CCBREADER_H__ */

