/****************************************************************************
 Copyright (c) 2015 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "jsapi.h"
#include "mozilla/Maybe.h"
#include "scripting/js-bindings/manual/component/CCComponentJS.h"
#include "base/CCScriptSupport.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"

NS_CC_BEGIN

const std::string ComponentJS::ON_ENTER = "onEnter";
const std::string ComponentJS::ON_EXIT = "onExit";
const std::string ComponentJS::UPDATE = "update";

ComponentJS* ComponentJS::create(const std::string& scriptFileName)
{
    CC_ASSERT(!scriptFileName.empty());
    
    auto componentJS = new(std::nothrow) ComponentJS(scriptFileName);
    if (componentJS)
    {
        componentJS->autorelease();
    }
    
    return componentJS;
}

ComponentJS::ComponentJS(const std::string& scriptFileName)
: _scriptFileName(scriptFileName)
, _jsObj(nullptr)
{
    ScriptingCore* engine = ScriptingCore::getInstance();
    JSContext* cx = engine->getGlobalContext();
    // Require script
    JS::RootedValue classValue(cx);
    _succeedLoadingScript = engine->requireScript(_scriptFileName.c_str(), &classValue);
    
    if (_succeedLoadingScript)
    {
        JS::RootedObject classObj(cx, classValue.toObjectOrNull());
        const JSClass* theClass = JS_GetClass(classObj);
        JS::RootedValue protoValue(cx);
        JS_GetProperty(cx, classObj, "prototype", &protoValue);
        
        mozilla::Maybe<JS::PersistentRootedObject> *jsObj = new (std::nothrow) mozilla::Maybe<JS::PersistentRootedObject>();
        
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::ComponentJS>(this);
        JS::RootedObject proto(cx, protoValue.toObjectOrNull());
        JS::RootedObject parent(cx, typeClass->proto.ref());
        jsObj->construct(cx);
        JS::RootedObject obj(cx, JS_NewObject(cx, theClass, proto, parent));
        jsObj->ref() = obj;
        
        // Unbind current proxy binding
        js_proxy_t* nproxy = jsb_get_native_proxy(this);
        if (nproxy)
        {
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
            JS::RemoveObjectRoot(cx, &nproxy->obj);
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
            JS::RootedObject nobj(cx, nproxy->obj);
            jsb_remove_proxy(nproxy, jsb_get_js_proxy(nobj));
        }
        // link the native object with the javascript object
        jsb_new_proxy(this, jsObj->ref());
        
        _jsObj = jsObj;
    }
}

ComponentJS::~ComponentJS()
{
    mozilla::Maybe<JS::PersistentRootedObject>* jsObj = static_cast<mozilla::Maybe<JS::PersistentRootedObject>*>(_jsObj);
    if (jsObj && !jsObj->empty())
    {
        // Remove proxy
        js_proxy_t* proxy = jsb_get_js_proxy(jsObj->ref());
        if (proxy)
            jsb_remove_proxy(proxy);
    }
    // Delete rooted object
    if (jsObj != nullptr)
    {
        delete jsObj;
    }
}

void* ComponentJS::getScriptObject() const
{
    mozilla::Maybe<JS::PersistentRootedObject>* jsObj = static_cast<mozilla::Maybe<JS::PersistentRootedObject>*>(_jsObj);
    if (jsObj && !jsObj->empty())
    {
        return jsObj->ref().get();
    }
    else
    {
        return nullptr;
    }
}

void ComponentJS::update(float delta)
{
    if (_succeedLoadingScript)
    {
        mozilla::Maybe<JS::PersistentRootedObject>* jsObj = static_cast<mozilla::Maybe<JS::PersistentRootedObject>*>(_jsObj);
        jsval dataVal = DOUBLE_TO_JSVAL(delta);
        JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsObj->ref().get()), ComponentJS::UPDATE.c_str(), 1, &dataVal, &retval);
    }
}

void ComponentJS::onEnter()
{
    if (_succeedLoadingScript)
    {
        mozilla::Maybe<JS::PersistentRootedObject>* jsObj = static_cast<mozilla::Maybe<JS::PersistentRootedObject>*>(_jsObj);
        jsval dataVal = INT_TO_JSVAL(1);
        JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsObj->ref().get()), ComponentJS::ON_ENTER.c_str(), 1, &dataVal, &retval);
    }
}

void ComponentJS::onExit()
{
    if (_succeedLoadingScript)
    {
        mozilla::Maybe<JS::PersistentRootedObject>* jsObj = static_cast<mozilla::Maybe<JS::PersistentRootedObject>*>(_jsObj);
        jsval dataVal = INT_TO_JSVAL(1);
        JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsObj->ref().get()), ComponentJS::ON_EXIT.c_str(), 1, &dataVal, &retval);
    }
}

NS_CC_END
