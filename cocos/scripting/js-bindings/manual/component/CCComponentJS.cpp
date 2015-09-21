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

#include "CCComponentJS.h"
#include "base/CCScriptSupport.h"
#include "ScriptingCore.h"
#include "js_manual_conversions.h"

NS_CC_BEGIN

ScriptComponent* ScriptComponent::create(const std::string& scriptFileName)
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
: ScriptComponent(scriptFileName)
{
    ScriptingCore* engine = ScriptingCore::getInstance();
    JSContext* cx = engine->getGlobalContext();
    // Require script
    JS::RootedValue classValue(cx);
    _succeedLoadingScript = engine->requireScript(_scriptFileName.c_str(), &classValue);
    
    if (_succeedLoadingScript)
    {
        JSObject* classObj = classValue.toObjectOrNull();
        const JSClass* theClass = JS_GetClass(classObj);
        JS::RootedValue protoValue(cx);
        JS_GetProperty(cx, JS::RootedObject(cx, classObj), "prototype", &protoValue);
        
        TypeTest<ScriptComponent> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        
        JS::RootedObject proto(cx, protoValue.toObjectOrNull());
        JS::RootedObject parent(cx, typeClass->proto.get());
        _jsObj.construct(cx);
        _jsObj.ref() = JS_NewObject(cx, theClass, proto, parent);
        
        // Unbind current proxy binding
        js_proxy_t* jsproxy = js_get_or_create_proxy<ScriptComponent>(cx, this);
        JS::RemoveObjectRoot(cx, &jsproxy->obj);
        jsb_remove_proxy(jsb_get_native_proxy(this), jsproxy);
        // link the native object with the javascript object
        jsb_new_proxy(this, _jsObj.ref().get());
    }
}

void* ComponentJS::getScriptObject() const
{
    return _jsObj.ref().get();
}

void ComponentJS::update(float delta)
{
    if (_succeedLoadingScript)
    {
        jsval dataVal = DOUBLE_TO_JSVAL(delta);
        JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_jsObj.ref().get()), ScriptComponent::UPDATE.c_str(), 1, &dataVal, &retval);
    }
}

void ComponentJS::onEnter()
{
    if (_succeedLoadingScript)
    {
        jsval dataVal = INT_TO_JSVAL(1);
        JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_jsObj.ref().get()), ScriptComponent::ON_ENTER.c_str(), 1, &dataVal, &retval);
    }
}

void ComponentJS::onExit()
{
    if (_succeedLoadingScript)
    {
        jsval dataVal = INT_TO_JSVAL(1);
        JS::RootedValue retval(ScriptingCore::getInstance()->getGlobalContext());
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_jsObj.ref().get()), ScriptComponent::ON_EXIT.c_str(), 1, &dataVal, &retval);
    }
}

NS_CC_END
