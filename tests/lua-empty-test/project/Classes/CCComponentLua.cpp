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
#include "lua_cocos2dx_luacomponent_auto.hpp"
#include "LuaBasicConversions.h"

NS_CC_BEGIN

ComponentLua* ComponentLua::create(const std::string& scriptFileName)
{
    CC_ASSERT(!scriptFileName.empty());
    
    auto componentLua = new(std::nothrow) ComponentLua(scriptFileName);
    if (componentLua)
    {
        componentLua->autorelease();
    }
    
    return componentLua;
}

ComponentLua::ComponentLua(const std::string& scriptFileName)
{
    _scriptFileName = scriptFileName;
    loadAndExecuteScript();
}

void ComponentLua::update(float delta)
{
    lua_State *l = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    lua_getglobal(l, "LuaComponent");
    lua_getfield(l, -1, "update");
    getUserData();
    LuaEngine::getInstance()->getLuaStack()->executeFunction(1);
}

void ComponentLua::loadAndExecuteScript()
{
    // register lua engine
    LuaEngine* engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    
    // register native functions
    lua_State *l = engine->getLuaStack()->getLuaState();
    register_all_cocos2dx_luacomponent(l);
    
    // execute script
    char command[100];
    snprintf(command, 100, "require '%s'", _scriptFileName.c_str());
    int result = engine->executeString(command);
    if (result != 0)
    {
        CCLOG("there is something wrong with the script %s", _scriptFileName.c_str());
    }
    
    // set lua class's metatable to registered table
    
    tolua_open(l);
    lua_pushstring(l,"cc.ComponentLua"); // string
    lua_gettable(l, LUA_REGISTRYINDEX);  // table
    if (!lua_istable(l, -1))
    {
        CCLOG("can not find table cc.ComponentLua");
        return;
    }
    
    
    lua_getglobal(l, "LuaComponent"); // table LuaComponent
    if (lua_istable(l,-1))
    {
        lua_pushvalue(l, -2); // table LuaComponent table
        lua_setmetatable(l, -2); // table LuaComponent
    }
    
    // generate userdata and set its metatable to LuaComponent
    
    object_to_luaval<cocos2d::ComponentLua>(l, "cc.ComponentLua",this); // table LuaComponent userdata
    // set userdata's meta table to LuaComponent
    lua_pushvalue(l, -2); // table LuaComponent userdata LuaComponent
    lua_setmetatable(l, -2); // table LuaComponent userdata
    
    lua_settop(l, 0);
}

void ComponentLua::getUserData()
{
    lua_State *L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    
    luaL_getmetatable(L, "cc.ComponentLua");                                 /* stack: mt */
    if (lua_isnil(L, -1)) { /* NOT FOUND metatable */
        lua_pop(L, 1);
        return;
    }
    lua_pushstring(L,"tolua_ubox");
    lua_rawget(L,-2);                                           /* stack: mt ubox */
    if (lua_isnil(L, -1))
    {
        lua_pop(L, 1);
        lua_pushstring(L, "tolua_ubox");
        lua_rawget(L, LUA_REGISTRYINDEX);
    }
    
    lua_pushlightuserdata(L,this);                             /* stack: mt ubox key<value> */
    lua_rawget(L,-2);                                          /* stack: mt ubox ubox[value] */
    if (lua_isnil(L,-1))
    {
        CCLOG("cant not get userdata");
        lua_pop(L, 2);
        return;
    }
    lua_remove(L, -2);
    lua_remove(L, -2);
}

NS_CC_END
