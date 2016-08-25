/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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
#include "platform/CCPlatformConfig.h"
#include "base/ccConfig.h"
#if CC_USE_NAVMESH
#include "scripting/lua-bindings/manual/navmesh/lua_cocos2dx_navmesh_manual.h"
#include "scripting/lua-bindings/auto/lua_cocos2dx_navmesh_auto.hpp"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "navmesh/CCNavMesh.h"


int lua_cocos2dx_navmesh_NavMeshAgent_move(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshAgent* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshAgent",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::NavMeshAgent*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_move'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec3 arg0;
        
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.NavMeshAgent:move");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_move'", nullptr);
            return 0;
        }
        cobj->move(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Vec3 arg0;
        LUA_FUNCTION handler;
        
        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.NavMeshAgent:move");
        
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        handler = toluafix_ref_function(tolua_S, 3, 0);
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_move'", nullptr);
            return 0;
        }
        cobj->move(arg0, [=](cocos2d::NavMeshAgent *agent, float totalTimeAfterMove){
            object_to_luaval<cocos2d::NavMeshAgent>(tolua_S, "cc.NavMeshAgent",(cocos2d::NavMeshAgent*)agent);
            tolua_pushnumber(tolua_S, (lua_Number)totalTimeAfterMove);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        });
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)cobj, handler);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:move",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_move'.",&tolua_err);
#endif
    
    return 0;
}


static void extendNavMeshAgent(lua_State* L)
{
    lua_pushstring(L, "cc.NavMeshAgent");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "move", lua_cocos2dx_navmesh_NavMeshAgent_move);
    }
    lua_pop(L, 1);
}

static int register_all_navmesh_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendNavMeshAgent(L);
    
    return 1;
}

int register_navmesh_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
    	register_all_cocos2dx_navmesh(L);
        register_all_navmesh_manual(L);
    }
    lua_pop(L, 1);
    return 1;
}

#endif