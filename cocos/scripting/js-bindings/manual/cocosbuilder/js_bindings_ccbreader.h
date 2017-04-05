/*
 * Created by Rohan Kuruvilla on 14/08/2012.
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2017 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __JS_BINDINGS_CCBREADER_H__
#define __JS_BINDINGS_CCBREADER_H__

#include "scripting/js-bindings/manual/cocosbuilder/cocosbuilder_specifics.hpp"
#include "editor-support/cocosbuilder/CocosBuilder.h"

class CCBScriptCallbackProxy:  public cocos2d::Layer
, public cocosbuilder::CCBSelectorResolver
, public cocosbuilder::CCBMemberVariableAssigner {
    
    std::string callBackProp;
    jsval owner;

public:


    CCBScriptCallbackProxy () {}
    virtual ~CCBScriptCallbackProxy() {}

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CCBScriptCallbackProxy, create);
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget,
                                                                    const char * pSelectorName);

    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget,
                                                                                   const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref * pTarget, const char * pMemberVariableName,
                                           cocos2d::Node * pNode);
    virtual void onNodeLoaded(cocos2d::Node * pNode,
                              cocosbuilder::NodeLoader * pNodeLoader);
        
    virtual CCBSelectorResolver * createNew();
    void menuItemCallback(Ref *pSender);
    void controlCallback(Ref *pSender, cocos2d::extension::Control::EventType event);
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

void register_CCBuilderReader(JSContext *cx, JS::HandleObject global);
bool js_CocosBuilder_Run(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_BINDINGS_CCBREADER_H__ */

