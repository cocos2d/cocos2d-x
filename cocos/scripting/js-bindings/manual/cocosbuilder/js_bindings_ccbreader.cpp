/*
 * Created by Rohan Kuruvilla on 14/08/2012.
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "scripting/js-bindings/manual/cocosbuilder/js_bindings_ccbreader.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/js_bindings_config.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocosbuilder;

static void removeSelector(std::string &str) {
    size_t found;
    found = str.find(":");
    while (found!=std::string::npos){
        str.replace(found, found+1, "");
        found = str.find(":");
    }
}

SEL_MenuHandler CCBScriptCallbackProxy::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget,
                                                                       const char * pSelectorName) {
    this->callBackProp = pSelectorName;
    removeSelector(this->callBackProp);
    return menu_selector(CCBScriptCallbackProxy::menuItemCallback);
}

Control::Handler CCBScriptCallbackProxy::onResolveCCBCCControlSelector(Ref * pTarget,
                                                                           const char * pSelectorName) {
    
    this->callBackProp = pSelectorName;
    removeSelector(this->callBackProp);
    return cccontrol_selector(CCBScriptCallbackProxy::controlCallback);
}

bool CCBScriptCallbackProxy::onAssignCCBMemberVariable(Ref * pTarget,
                                                       const char * pMemberVariableName,
                                                       Node * pNode) {
    return true;
}

void CCBScriptCallbackProxy::onNodeLoaded(Node * pNode,
                                          NodeLoader * pNodeLoader) {}

CCBSelectorResolver * CCBScriptCallbackProxy::createNew() {
    CCBScriptCallbackProxy * ret = new (std::nothrow) CCBScriptCallbackProxy();
    ret->setJSOwner(this->owner);
    return dynamic_cast<CCBSelectorResolver *>(ret);
}

void CCBScriptCallbackProxy::menuItemCallback(Ref *pSender) {
    jsval arg;
    ScriptingCore::getInstance()->executeFunctionWithOwner(owner, callBackProp.c_str(), 0, &arg);
}

void CCBScriptCallbackProxy::controlCallback(Ref *pSender, Control::EventType event) {
    jsval arg;
    ScriptingCore::getInstance()->executeFunctionWithOwner(owner, callBackProp.c_str(), 0, &arg);
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

bool js_cocos2dx_CCBAnimationManager_animationCompleteCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
        js_proxy_t *p = jsb_get_js_proxy(obj);
        cocosbuilder::CCBAnimationManager *node = (cocosbuilder::CCBAnimationManager *)(p ? p->ptr : NULL);
        
        JSCCBAnimationWrapper *tmpCobj = new (std::nothrow) JSCCBAnimationWrapper();
        tmpCobj->autorelease();
        
        tmpCobj->setJSCallbackThis(args.get(0));
        if(argc >= 2) {
            tmpCobj->setJSCallbackFunc(args.get(1));
        }
        
        node->setAnimationCompletedCallback(tmpCobj, callfunc_selector(JSCCBAnimationWrapper::animationCompleteCallback));
        return true;
    }
    return false;
}

bool js_cocos2dx_CCBReader_readNodeGraphFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *p = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(p ? p->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 2) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::Ref* arg1;
        do {
            js_proxy_t *proxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            proxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(proxy ? proxy->ptr : NULL);
        } while (0);
        
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

        cocos2d::Node* ret = cobj->readNodeGraphFromFile(arg0, arg1);
        jsval jsret; do {
            if (ret) {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Node>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        cocos2d::Node* ret = cobj->readNodeGraphFromFile(arg0);
        jsval jsret; do {
            if (ret) {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Node>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::Ref* arg1;
        do {
            js_proxy_t *proxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            proxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(proxy ? proxy->ptr : NULL);
        } while (0);
        cocos2d::Size arg2;
        ok &= jsval_to_ccsize(cx, args.get(2), &arg2);
        
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        cocos2d::Node* ret = cobj->readNodeGraphFromFile(arg0, arg1, arg2);
        jsval jsret; do {
            if (ret) {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Node>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    return false;
}

bool js_cocos2dx_CCBReader_createSceneWithNodeGraphFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *p = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(p ? p->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 2) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::Ref* arg1;
        do {
            js_proxy_t *proxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            proxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(proxy ? proxy->ptr : NULL);
            TEST_NATIVE_OBJECT(cx, arg1)
        } while (0);
        
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        cocos2d::Scene* ret = cobj->createSceneWithNodeGraphFromFile(arg0, arg1);
        jsval jsret; do {
            if (ret) {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Scene>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        cocos2d::Scene* ret = cobj->createSceneWithNodeGraphFromFile(arg0);
        jsval jsret; do {
            if (ret) {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Scene>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        cocos2d::Ref* arg1;
        do {
            js_proxy_t *proxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            proxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(proxy ? proxy->ptr : NULL);
            TEST_NATIVE_OBJECT(cx, arg1)
        } while (0);
        cocos2d::Size arg2;
        ok &= jsval_to_ccsize(cx, args.get(2), &arg2);
        
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        cocos2d::Scene* ret = cobj->createSceneWithNodeGraphFromFile(arg0, arg1, arg2);
        jsval jsret;
        do {
            if (ret) {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::Scene>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    
    return false;
}


bool js_CocosBuilder_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    
    ccNodeLoaderLibrary->registerNodeLoader("", JSLayerLoader::loader());
    
    CCBReader * ret = new (std::nothrow) CCBReader(ccNodeLoaderLibrary);
    ret->autorelease();
    
    jsval jsret;
    if (ret) {
        // create a new js obj of that class
        JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocosbuilder::CCBReader>(cx, ret));
        jsret = OBJECT_TO_JSVAL(jsobj);
    } else {
        jsret = JSVAL_NULL;
    }
    args.rval().set(jsret);
    return true;
    
}

extern JSObject* jsb_cocosbuilder_CCBReader_prototype;
extern JSObject* jsb_cocosbuilder_CCBAnimationManager_prototype;

void register_CCBuilderReader(JSContext *cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "cc", &ccObj);
    
    JS_GetProperty(cx, ccObj, "_Reader", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "create", js_CocosBuilder_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "loadScene", js_cocos2dx_CCBReader_createSceneWithNodeGraphFromFile, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_cocosbuilder_CCBReader_prototype);
    JS_DefineFunction(cx, tmpObj, "load", js_cocos2dx_CCBReader_readNodeGraphFromFile, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    tmpObj.set(jsb_cocosbuilder_CCBAnimationManager_prototype);
    JS_DefineFunction(cx, tmpObj, "setCompletedAnimationCallback", js_cocos2dx_CCBAnimationManager_animationCompleteCallback, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}
