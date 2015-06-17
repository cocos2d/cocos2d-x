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

#include "CCComponentLua.h"
#include "base/CCScriptSupport.h"
#include "CCLuaEngine.h"

NS_CC_BEGIN

void ComponentLua::bindEvent(const std::string& event, const std::string& luaFunctionName)
{
    _eventFunctionMap[event] = luaFunctionName;
}

void ComponentLua::receiveEvent(const std::string& event)
{
    CC_ASSERT(!_scriptPath.empty());
    
    // register lua engine
    LuaEngine* engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);

    char command[100];
    snprintf(command, 100, "require '%s'", _scriptPath.c_str());
    engine->executeString(command);
    
    engine->getLuaStack()->executeGlobalFunction("update");
}

void ComponentLua::update(float delta)
{
    receiveEvent("update");
}

NS_CC_END