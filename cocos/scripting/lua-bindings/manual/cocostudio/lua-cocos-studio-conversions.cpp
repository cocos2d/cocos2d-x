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

#include "lua-cocos-studio-conversions.h"
#include "ActionTimeline/CCActionTimeline.h"

#if COCOS2D_DEBUG >=1
extern void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName);
#endif

bool luaval_to_animationInfo(lua_State* L, int lo, cocostudio::timeline::AnimationInfo* outValue , const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "name");                 /* L: paramStack key */
        lua_gettable(L,lo);                        /* L: paramStack paramStack[lo][key] */
        outValue->name = lua_isstring(L, -1)? lua_tostring(L, -1) : "";
        lua_pop(L,1);                              /* L: paramStack*/
        
        lua_pushstring(L, "startIndex");
        lua_gettable(L,lo);
        outValue->startIndex = lua_isnumber(L, -1)?(int)lua_tonumber(L, -1) : 0;
        lua_pop(L,1);
        
        lua_pushstring(L, "endIndex");
        lua_gettable(L, lo);
        outValue->endIndex = lua_isnumber(L, -1)?(int)lua_tonumber(L, -1) : 0;
        lua_pop(L, 1);
        
        return true;
    }
    
    return false;
}

void animationInfo_to_luaval(lua_State* L,const cocostudio::timeline::AnimationInfo& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    lua_pushstring(L, "name");
    lua_pushstring(L, inValue.name.c_str());
    lua_rawset(L, -3);
    
    lua_pushstring(L, "startIndex");
    lua_pushnumber(L, (lua_Number)inValue.startIndex);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "endIndex");
    lua_pushnumber(L, (lua_Number)inValue.endIndex);
    lua_rawset(L, -3);
}
