/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "lua_cocos2dx_3d_manual.h"
#include "lua_cocos2dx_3d_auto.hpp"
#include "LuaBasicConversions.h"
#include "CCLuaEngine.h"

int lua_cocos2dx_3d_Sprite3D_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Sprite3D*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        GLenum src, dst;
        if (!luaval_to_int32(tolua_S, 2, (int32_t*)&src, "cc.Sprite3D:setBlendFunc"))
            return 0;
        
        if (!luaval_to_int32(tolua_S, 3, (int32_t*)&dst, "cc.Sprite3D:setBlendFunc"))
            return 0;
        
        BlendFunc blendFunc = {src, dst};
        cobj->setBlendFunc(blendFunc);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:setBlendFunc",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_setBlendFunc'.",&tolua_err);
#endif
    return 0;
}

static void extendSprite3D(lua_State* L)
{
    lua_pushstring(L, "cc.Sprite3D");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setBlendFunc", lua_cocos2dx_3d_Sprite3D_setBlendFunc);
    }
    lua_pop(L, 1);
}

static int register_all_cocos2dx_3d_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendSprite3D(L);
    
    return 0;
}

int register_cocos3d_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        register_all_cocos2dx_3d(L);
        register_all_cocos2dx_3d_manual(L);
    }
    lua_pop(L, 1);
    
    return 1;
}
