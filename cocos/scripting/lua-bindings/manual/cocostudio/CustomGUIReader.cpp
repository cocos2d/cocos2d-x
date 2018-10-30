/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "scripting/lua-bindings/manual/cocostudio/CustomGUIReader.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

namespace cocostudio
{

    CustomGUIReader* CustomGUIReader::create(std::string &className, int createFunc, int setPropsFunc)
    {
        auto reader = new (std::nothrow) CustomGUIReader();
        reader->init(className, createFunc, setPropsFunc);
        return reader;
    }
   
    Ref* CustomGUIReader::createInstance()
    {
        Ref* result = nullptr;
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->executeFunction(_createFunc, 0, 1, [&result](lua_State* L,int numReturn){
            result = static_cast<Ref*>(tolua_tousertype(L, -1, nullptr));
            lua_pop(L, 1);
        });
        return result;
    }

    CustomGUIReader::CustomGUIReader()
    :_className()
    ,_createFunc(0)
    ,_setPropsFunc(0)
    {

    }

    CustomGUIReader::~CustomGUIReader()
    {
        if (_createFunc)
        {
            LuaEngine::getInstance()->removeScriptHandler(_createFunc);
            _createFunc = 0;
        }
        if (_setPropsFunc)
        {
            LuaEngine::getInstance()->removeScriptHandler(_setPropsFunc);
            _setPropsFunc = 0;
        }
    }

    void CustomGUIReader::init(std::string &className, int createFunc, int setPropsFunc)
    {
        _className = className;
        _createFunc = createFunc;
        _setPropsFunc = setPropsFunc;

        ObjectFactory* factoryCreate = ObjectFactory::getInstance();
        ObjectFactory::TInfo t;
        t._class = className;
        t._func = CC_CALLBACK_0(CustomGUIReader::createInstance, this);
        factoryCreate->registerType(t);

        auto guiReader = GUIReader::getInstance();
        auto objMap = guiReader->getParseObjectMap();
        (*objMap)[className] = this;
        auto callbackMap = guiReader->getParseCallBackMap();
        (*callbackMap)[className] = parseselector(CustomGUIReader::setCustomProps);
    }

	void CustomGUIReader::setCustomProps(const std::string &classType, cocos2d::Ref *widget, const rapidjson::Value &customOptions)
	{
        if (_setPropsFunc != 0)
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            customOptions.Accept(writer);

            auto stack = LuaEngine::getInstance()->getLuaStack();
            stack->pushString(classType.c_str(), static_cast<int>(classType.size()));
            stack->pushObject(widget, "cc.Ref");
            stack->pushString(buffer.GetString(), static_cast<int>(buffer.GetSize()));
            stack->executeFunctionByHandler(_setPropsFunc, 3);
        }
	}
}
