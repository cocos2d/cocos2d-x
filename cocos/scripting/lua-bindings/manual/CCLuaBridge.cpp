/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "scripting/lua-bindings/manual/CCLuaBridge.h"

NS_CC_BEGIN

lua_State *LuaBridge::s_luaState = NULL;
int        LuaBridge::s_newFunctionId = 0;

LuaStack *LuaBridge::getStack()
{
    return LuaEngine::getInstance()->getLuaStack();
}

int LuaBridge::pushLuaFunctionById(int functionId)
{
    lua_State *L = s_luaState;
    int top = lua_gettop(L);
    /* L: */
    lua_pushstring(L, LUA_BRIDGE_REGISTRY_FUNCTION);            /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 0;
    }
    
    lua_pushnil(L);                                             /* L: f_id nil */
    while (lua_next(L, -2) != 0)                                /* L: f_id f id */
    {
        int value = lua_tointeger(L, -1);
        lua_pop(L, 1);                                          /* L: f_id f */
        if (value == functionId)
        {
            return -1;
        }
    }                                                           /* L: f_id */
    
    lua_settop(L, top);
    return 0;
}

int LuaBridge::retainLuaFunctionById(int functionId)
{
    lua_State *L = s_luaState;
    
    lua_pushstring(L, LUA_BRIDGE_REGISTRY_RETAIN);              /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 0;
    }
    
    // get counter
    lua_pushinteger(L, functionId);                             /* L: id_r id */
    lua_rawget(L, -2);                                          /* L: id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 2);
        return 0;
    }
    
    // increase counter
    int retainCount = lua_tointeger(L, -1);
    retainCount++;
    lua_pop(L, 1);                                              /* L: id_r */
    lua_pushinteger(L, functionId);                             /* L: id_r id */
    lua_pushinteger(L, retainCount);                            /* L: id_r id r */
    lua_rawset(L, -3);                            /* id_r[id] = r, L: id_r */
    lua_pop(L, 1);
    
    CCLOG("CCLuaBridge::retainLuaFunctionById(%d) - retain count = %d", functionId, retainCount);
    
    return retainCount;
    
}

int LuaBridge::releaseLuaFunctionById(int functionId)
{
    lua_State *L = s_luaState;
    /* L: */
    lua_pushstring(L, LUA_BRIDGE_REGISTRY_FUNCTION);            /* L: key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        CCLOG("CCLuaBridge::releaseLuaFunctionById() - LUA_BRIDGE_REGISTRY_FUNCTION not exists");
        return 0;
    }
    
    lua_pushstring(L, LUA_BRIDGE_REGISTRY_RETAIN);              /* L: f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 2);
        CCLOG("CCLuaBridge::releaseLuaFunctionById() - LUA_BRIDGE_REGISTRY_RETAIN not exists");
        return 0;
    }
    
    lua_pushinteger(L, functionId);                             /* L: f_id id_r id */
    lua_rawget(L, -2);                                          /* L: f_id id_r r */
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        lua_pop(L, 3);
        CCLOG("CCLuaBridge::releaseLuaFunctionById() - function id %d not found", functionId);
        return 0;
    }
    
    int retainCount = lua_tointeger(L, -1);
    retainCount--;
    
    if (retainCount > 0)
    {
        // update counter
        lua_pop(L, 1);                                          /* L: f_id id_r */
        lua_pushinteger(L, functionId);                         /* L: f_id id_r id */
        lua_pushinteger(L, retainCount);                        /* L: f_id id_r id r */
        lua_rawset(L, -3);                        /* id_r[id] = r, L: f_id id_r */
        lua_pop(L, 2);
        CCLOG("CCLuaBridge::releaseLuaFunctionById() - function id %d retain count = %d", functionId, retainCount);
        return retainCount;
    }
    
    // remove lua function reference
    lua_pop(L, 1);                                              /* L: f_id id_r */
    lua_pushinteger(L, functionId);                             /* L: f_id id_r id */
    lua_pushnil(L);                                             /* L: f_id id_r id nil */
    lua_rawset(L, -3);                          /* id_r[id] = nil, L: f_id id_r */
    
    lua_pop(L, 1);                                              /* L: f_id */
    lua_pushnil(L);                                             /* L: f_id nil */
    while (lua_next(L, -2) != 0)                                /* L: f_id f id */
    {
        int value = lua_tointeger(L, -1);
        lua_pop(L, 1);                                          /* L: f_id f */
        if (value == functionId)
        {
            lua_pushnil(L);                                     /* L: f_id f nil */
            lua_rawset(L, -3);                   /* f_id[f] = nil, L: f_id */
            break;
        }
    }                                                           /* L: f_id */
    
    lua_pop(L, 1);
    CCLOG("CCLuaBridge::releaseLuaFunctionById() - function id %d released", functionId);
    return 0;
}

int LuaBridge::retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn)
{
    /* L: f ... */
    lua_pushstring(L, LUA_BRIDGE_REGISTRY_FUNCTION);            /* L: f ... key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f ... f_id */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUA_BRIDGE_REGISTRY_FUNCTION);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }
    
    lua_pushstring(L, LUA_BRIDGE_REGISTRY_RETAIN);              /* L: f ... f_id key */
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* L: f ... f_id id_r */
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, LUA_BRIDGE_REGISTRY_RETAIN);
        lua_pushvalue(L, -2);
        lua_rawset(L, LUA_REGISTRYINDEX);
    }
    
    // get function id
    lua_pushvalue(L, functionIndex - 2);                        /* L: f ... f_id id_r f */
    lua_rawget(L, -3);                                          /* L: f ... f_id id_r id */
    
    int functionId;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, create new id
        lua_pop(L, 1);                                          /* L: f ... f_id id_r */
        s_newFunctionId++;
        functionId = s_newFunctionId;
        
        lua_pushvalue(L, functionIndex - 2);                    /* L: f ... f_id id_r f */
        lua_pushinteger(L, functionId);                         /* L: f ... f_id id_r f id */
        lua_rawset(L, -4);                        /* f_id[f] = id, L: f ... f_id id_r */
        lua_pushinteger(L, functionId);                         /* L: f ... f_id id_r id */
    }
    else
    {
        functionId = lua_tointeger(L, -1);
    }
    
    // get function retain
    lua_pushvalue(L, -1);                                       /* L: f ... f_id id_r id id */
    lua_rawget(L, -3);                                          /* L: f ... f_id id_r id r */
    int retainCount = 1;
    if (lua_type(L, -1) != LUA_TNUMBER)
    {
        // first retain, set retain count = 1
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }
    else
    {
        // add retain count
        retainCount = lua_tointeger(L, -1);
        retainCount++;
        lua_pop(L, 1);
        lua_pushinteger(L, retainCount);
    }
    
    lua_rawset(L, -3);                            /* id_r[id] = r, L: f ... f_id id_r */
    lua_pop(L, 2);                                              /* L: f ... */
    
    if (retainCountReturn) *retainCountReturn = retainCount;
    return functionId;
}

NS_CC_END
