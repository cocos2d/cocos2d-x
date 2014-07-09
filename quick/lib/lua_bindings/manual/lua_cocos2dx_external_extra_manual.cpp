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
#include "lua_cocos2dx_external_extra_manual.h"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"

#include "extra/cocos2dx_extra.h"
#include "extra/native/CCNative.h"

USING_NS_CC;
USING_NS_CC_EXTRA;

static int lua_cocos2dx_Native_addAlertButton(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err)) {
            goto tolua_lerror;
        }
#endif
        const char* title = ((const char*)  tolua_tostring(tolua_S, 2, 0));
        int ret = Native::addAlertButtonLua(title);
        //tolua_pushnumber(tolua_S, ret);
        
        return 0;
    }
    
    CCLOG("'addAlertButton' function of Native has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'addAlertButton'.", &tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Native_showAlert(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S, 1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        Native::showAlertLua(handler);

        return 0;
    }
    
    CCLOG("'showAlert' function of Native has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S, "#ferror in function 'showAlert'.", &tolua_err);
    return 0;
#endif
}

static void extendNative(lua_State* L)
{
    lua_pushstring(L, "cc.extra::Native");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addAlertButton", lua_cocos2dx_Native_addAlertButton);
        tolua_function(L, "showAlert", lua_cocos2dx_Native_showAlert);
    }
    lua_pop(L, 1);
}

int register_all_cocos2dx_external_extra_manual(lua_State* tolua_S)
{
    extendNative(tolua_S);
    return 0;
}
