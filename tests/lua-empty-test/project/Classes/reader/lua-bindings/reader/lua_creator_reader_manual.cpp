/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#include "lua_creator_reader_manual.hpp"

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "base/CCEventListenerFocus.h"

#include "collider/ColliderManager.h"


static int lua_ColliderManager_unregisterCollisionCallback(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"creator.ColliderManager",0,&tolua_err))
    {
        tolua_error(L,"'lua_ColliderManager_unregisterCollisionCallback' is not executed in ColliderManager\n", NULL);
        return 0;
    }

    creator::ColliderManager* self = static_cast<creator::ColliderManager*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isstring(L, 1))
        {
            tolua_error(L, "parameter 1 is not string\n", NULL);
            return 0;
        }
        
        const char* key = lua_tostring(L, 1);
        self->unregisterCollisionCallback(key);
    }
    else
        luaL_error(L, "'unregisterCollisionCallback' function of ColliderManager has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
}

static int lua_ColliderManager_registerCollitionCallback(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"creator.ColliderManager",0,&tolua_err))
    {
        tolua_error(L,"'registerCollitionCallback' is not executed with ColliderManager\n", NULL);
        return 0;
    }
    
    auto self = static_cast<creator::ColliderManager*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (2 == argc)
    {
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            luaL_error(L, "'registerCollitionCallback' first parameter is not a function\n");
            return 0;
        }
        if (!lua_isstring(L, 3))
        {
            luaL_error(L, "'registerCollitionCallback' second parameter is not a string\n");
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        const char* key = lua_tostring(L, 3);
        
        self->registerCollitionCallback([=](creator::Contract::CollisionType type, creator::Collider* collider1, creator::Collider* collider2)
        {
            auto stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            stack->pushInt(static_cast<int>(type));
            stack->pushObject(collider1, "creator.Collider");
            stack->pushObject(collider2, "creator.Collider");
            stack->executeFunctionByHandler(handler, 3);
            stack->clean();
        }, key);
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
    }
    else
        luaL_error(L, "'addClickEventListener' function of ColliderManager has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
}

static void extendColliderManager(lua_State* L)
{
    lua_pushstring(L, "creator.ColliderManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "registerCollitionCallback", lua_ColliderManager_registerCollitionCallback);
        tolua_function(L, "unregisterCollisionCallback", lua_ColliderManager_unregisterCollisionCallback);
    }
    lua_pop(L, 1);
}

int register_all_creator_reader_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendColliderManager(L);

    return 0;
}
