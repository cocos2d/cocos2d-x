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
#include "lua_cocos2dx_deprecated.h"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"

USING_NS_CC;

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif


#define deprecatedClassTip(className) CCLOG("%s will be not binded in lua,please use the lua's table instead",className)
#define deprecatedFunctionTip(oldFun,newFun) CCLOG("%s was deprecated please use %s instead ",oldFun, newFun)

static int lua_cocos2dx_LabelBMFont_setLineBreakWithoutSpace(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setLineBreakWithoutSpace'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.LabelBMFont:setLineBreakWithoutSpace");
        if(!ok)
            return 0;
        cobj->setLineBreakWithoutSpace(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setLineBreakWithoutSpace",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setLineBreakWithoutSpace'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_getBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:getBlendFunc",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_getBlendFunc'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_isOpacityModifyRGB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_isOpacityModifyRGB'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        bool ret = cobj->isOpacityModifyRGB();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:isOpacityModifyRGB",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_isOpacityModifyRGB'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_getLetter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_getLetter'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        int arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.LabelBMFont:getLetter");
        if(!ok)
            return 0;
        cocos2d::Sprite* ret = cobj->getLetter(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:getLetter",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_getLetter'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_getString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_getString'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:getString",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_getString'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    
    if (argc == 1)
    {
        cocos2d::BlendFunc arg0;
        
        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.LabelBMFont:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_LabelBMFont_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setBlendFunc",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setBlendFunc'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_setString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setString'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:setString");
        if(!ok)
            return 0;
        cobj->setString(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setString",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setString'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_initWithString'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1,"cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelBMFont:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        cocos2d::TextHAlignment arg3;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelBMFont:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        cocos2d::TextHAlignment arg3;
        cocos2d::Vec2 arg4;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelBMFont:initWithString");
        
        ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.LabelBMFont:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:initWithString",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_initWithString'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_setOpacityModifyRGB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setOpacityModifyRGB'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.LabelBMFont:setOpacityModifyRGB");
        if(!ok)
            return 0;
        cobj->setOpacityModifyRGB(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setOpacityModifyRGB",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setOpacityModifyRGB'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_getFntFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_getFntFile'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getFntFile();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:getFntFile",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_getFntFile'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_setFntFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setFntFile'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:setFntFile");
        if(!ok)
            return 0;
        cobj->setFntFile(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Vec2 arg1;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:setFntFile");
        
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.LabelBMFont:setFntFile");
        if(!ok)
            return 0;
        cobj->setFntFile(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setFntFile",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setFntFile'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_setAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setAlignment'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::TextHAlignment arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.LabelBMFont:setAlignment");
        if(!ok)
            return 0;
        cobj->setAlignment(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setAlignment",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setAlignment'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_setWidth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelBMFont*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelBMFont_setWidth'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        double arg0;
        
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.LabelBMFont:setWidth");
        if(!ok)
            return 0;
        cobj->setWidth(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:setWidth",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_setWidth'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelBMFont_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LabelBMFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S)-1;
    
    do
    {
        if (argc == 0)
        {
            cocos2d::LabelBMFont* ret = cocos2d::LabelBMFont::create();
            object_to_luaval<cocos2d::LabelBMFont>(tolua_S, "cc.LabelBMFont",(cocos2d::LabelBMFont*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::LabelBMFont* ret = cocos2d::LabelBMFont::create(arg0, arg1);
            object_to_luaval<cocos2d::LabelBMFont>(tolua_S, "cc.LabelBMFont",(cocos2d::LabelBMFont*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::LabelBMFont* ret = cocos2d::LabelBMFont::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::LabelBMFont>(tolua_S, "cc.LabelBMFont",(cocos2d::LabelBMFont*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 4)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::LabelBMFont* ret = cocos2d::LabelBMFont::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::LabelBMFont>(tolua_S, "cc.LabelBMFont",(cocos2d::LabelBMFont*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 5)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelBMFont:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelBMFont:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg3;
            ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::Vec2 arg4;
            ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.LabelBMFont:create");
            if (!ok) { break; }
            cocos2d::LabelBMFont* ret = cocos2d::LabelBMFont::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::LabelBMFont>(tolua_S, "cc.LabelBMFont",(cocos2d::LabelBMFont*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LabelBMFont:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_LabelBMFont_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelBMFont* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::LabelBMFont();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LabelBMFont");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelBMFont:new",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelBMFont_constructor'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_cocos2dx_LabelBMFont_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LabelBMFont)");
    return 0;
}

static int register_cocos2dx_deprecated_LabelBMFont(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.LabelBMFont");
    tolua_module(tolua_S,"cc",0);
    tolua_beginmodule(tolua_S,"cc");
        tolua_cclass(tolua_S,"LabelBMFont","cc.LabelBMFont","cc.Node",nullptr);
    
        tolua_beginmodule(tolua_S,"LabelBMFont");
            tolua_function(tolua_S,"new",lua_cocos2dx_LabelBMFont_constructor);
            tolua_function(tolua_S,"setLineBreakWithoutSpace",lua_cocos2dx_LabelBMFont_setLineBreakWithoutSpace);
            tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_LabelBMFont_getBlendFunc);
            tolua_function(tolua_S,"isOpacityModifyRGB",lua_cocos2dx_LabelBMFont_isOpacityModifyRGB);
            tolua_function(tolua_S,"getLetter",lua_cocos2dx_LabelBMFont_getLetter);
            tolua_function(tolua_S,"getString",lua_cocos2dx_LabelBMFont_getString);
            tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_LabelBMFont_setBlendFunc);
            tolua_function(tolua_S,"setString",lua_cocos2dx_LabelBMFont_setString);
            tolua_function(tolua_S,"initWithString",lua_cocos2dx_LabelBMFont_initWithString);
            tolua_function(tolua_S,"setOpacityModifyRGB",lua_cocos2dx_LabelBMFont_setOpacityModifyRGB);
            tolua_function(tolua_S,"getFntFile",lua_cocos2dx_LabelBMFont_getFntFile);
            tolua_function(tolua_S,"setFntFile",lua_cocos2dx_LabelBMFont_setFntFile);
            tolua_function(tolua_S,"setAlignment",lua_cocos2dx_LabelBMFont_setAlignment);
            tolua_function(tolua_S,"setWidth",lua_cocos2dx_LabelBMFont_setWidth);
            tolua_function(tolua_S,"create", lua_cocos2dx_LabelBMFont_create);
        tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::LabelBMFont).name();
    g_luaType[typeName] = "cc.LabelBMFont";
    g_typeCast["LabelBMFont"] = "cc.LabelBMFont";
    return 1;
}

static int lua_cocos2dx_LabelTTF_enableShadow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_enableShadow'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        cocos2d::Size arg0;
        double arg1;
        double arg2;
        
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.LabelTTF:enableShadow");
        
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.LabelTTF:enableShadow");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:enableShadow");
        if(!ok)
            return 0;
        cobj->enableShadow(arg0, arg1, arg2);
        return 0;
    }
    if (argc == 4)
    {
        cocos2d::Size arg0;
        double arg1;
        double arg2;
        bool arg3;
        
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.LabelTTF:enableShadow");
        
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.LabelTTF:enableShadow");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:enableShadow");
        
        ok &= luaval_to_boolean(tolua_S, 5,&arg3, "cc.LabelTTF:enableShadow");
        if(!ok)
            return 0;
        cobj->enableShadow(arg0, arg1, arg2, arg3);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:enableShadow",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_enableShadow'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setDimensions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setDimensions'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Size arg0;
        
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.LabelTTF:setDimensions");
        if(!ok)
            return 0;
        cobj->setDimensions(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setDimensions",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setDimensions'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getFontSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getFontSize'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        double ret = cobj->getFontSize();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getFontSize",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getFontSize'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getString'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getString",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getString'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setFlippedY(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setFlippedY'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.LabelTTF:setFlippedY");
        if(!ok)
            return 0;
        cobj->setFlippedY(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setFlippedY",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setFlippedY'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setFlippedX(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setFlippedX'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.LabelTTF:setFlippedX");
        if(!ok)
            return 0;
        cobj->setFlippedX(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setFlippedX",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setFlippedX'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setTextDefinition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setTextDefinition'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::FontDefinition arg0;
        
        ok &= luaval_to_fontdefinition(tolua_S, 2, &arg0, "cc.LabelTTF:setTextDefinition");
        if(!ok)
            return 0;
        cobj->setTextDefinition(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setTextDefinition",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setTextDefinition'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setFontName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setFontName'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:setFontName");
        if(!ok)
            return 0;
        cobj->setFontName(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setFontName",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setFontName'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getHorizontalAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getHorizontalAlignment'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getHorizontalAlignment();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getHorizontalAlignment",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getHorizontalAlignment'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_initWithStringAndTextDefinition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_initWithStringAndTextDefinition'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        std::string arg0;
        cocos2d::FontDefinition arg1;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:initWithStringAndTextDefinition");
        
        ok &= luaval_to_fontdefinition(tolua_S, 3, &arg1, "cc.LabelTTF:initWithStringAndTextDefinition");
        if(!ok)
            return 0;
        bool ret = cobj->initWithStringAndTextDefinition(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:initWithStringAndTextDefinition",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_initWithStringAndTextDefinition'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setString'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:setString");
        if(!ok)
            return 0;
        cobj->setString(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setString",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setString'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_initWithString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_initWithString'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        cocos2d::Size arg3;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.LabelTTF:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        cocos2d::Size arg3;
        cocos2d::TextHAlignment arg4;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelTTF:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 6)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        cocos2d::Size arg3;
        cocos2d::TextHAlignment arg4;
        cocos2d::TextVAlignment arg5;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelTTF:initWithString");
        
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.LabelTTF:initWithString");
        if(!ok)
            return 0;
        bool ret = cobj->initWithString(arg0, arg1, arg2, arg3, arg4, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:initWithString",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_initWithString'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setFontFillColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setFontFillColor'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Color3B arg0;
        
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LabelTTF:setFontFillColor");
        if(!ok)
            return 0;
        cobj->setFontFillColor(arg0);
        return 0;
    }
    if (argc == 2)
    {
        cocos2d::Color3B arg0;
        bool arg1;
        
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LabelTTF:setFontFillColor");
        
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.LabelTTF:setFontFillColor");
        if(!ok)
            return 0;
        cobj->setFontFillColor(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setFontFillColor",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setFontFillColor'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getBlendFunc",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getBlendFunc'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_enableStroke(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_enableStroke'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::Color3B arg0;
        double arg1;
        
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LabelTTF:enableStroke");
        
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.LabelTTF:enableStroke");
        if(!ok)
            return 0;
        cobj->enableStroke(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        cocos2d::Color3B arg0;
        double arg1;
        bool arg2;
        
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "cc.LabelTTF:enableStroke");
        
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.LabelTTF:enableStroke");
        
        ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.LabelTTF:enableStroke");
        if(!ok)
            return 0;
        cobj->enableStroke(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:enableStroke",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_enableStroke'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getDimensions(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getDimensions'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const cocos2d::Size& ret = cobj->getDimensions();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getDimensions",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getDimensions'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setVerticalAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setVerticalAlignment'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::TextVAlignment arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.LabelTTF:setVerticalAlignment");
        if(!ok)
            return 0;
        cobj->setVerticalAlignment(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setVerticalAlignment",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setVerticalAlignment'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setFontSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setFontSize'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        double arg0;
        
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.LabelTTF:setFontSize");
        if(!ok)
            return 0;
        cobj->setFontSize(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setFontSize",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setFontSize'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getVerticalAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getVerticalAlignment'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getVerticalAlignment();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getVerticalAlignment",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getVerticalAlignment'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getTextDefinition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getTextDefinition'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const cocos2d::FontDefinition& ret = cobj->getTextDefinition();
        fontdefinition_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getTextDefinition",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getTextDefinition'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::BlendFunc arg0;
        
        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.LabelTTF:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_LabelTTF_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setBlendFunc",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setBlendFunc'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_getFontName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_getFontName'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        const std::string& ret = cobj->getFontName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:getFontName",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_getFontName'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_setHorizontalAlignment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_setHorizontalAlignment'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::TextHAlignment arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.LabelTTF:setHorizontalAlignment");
        if(!ok)
            return 0;
        cobj->setHorizontalAlignment(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:setHorizontalAlignment",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_setHorizontalAlignment'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_disableShadow(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_disableShadow'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->disableShadow();
        return 0;
    }
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.LabelTTF:disableShadow");
        if(!ok)
            return 0;
        cobj->disableShadow(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:disableShadow",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_disableShadow'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_disableStroke(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::LabelTTF*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_LabelTTF_disableStroke'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->disableStroke();
        return 0;
    }
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.LabelTTF:disableStroke");
        if(!ok)
            return 0;
        cobj->disableStroke(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:disableStroke",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_disableStroke'.",&tolua_err);
#endif
    
    return 0;
}
static int lua_cocos2dx_LabelTTF_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S)-1;
    
    do
    {
        if (argc == 0)
        {
            cocos2d::LabelTTF* ret = cocos2d::LabelTTF::create();
            object_to_luaval<cocos2d::LabelTTF>(tolua_S, "cc.LabelTTF",(cocos2d::LabelTTF*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 3)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::LabelTTF* ret = cocos2d::LabelTTF::create(arg0, arg1, arg2);
            object_to_luaval<cocos2d::LabelTTF>(tolua_S, "cc.LabelTTF",(cocos2d::LabelTTF*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 4)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::Size arg3;
            ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::LabelTTF* ret = cocos2d::LabelTTF::create(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::LabelTTF>(tolua_S, "cc.LabelTTF",(cocos2d::LabelTTF*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 5)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::Size arg3;
            ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::LabelTTF* ret = cocos2d::LabelTTF::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<cocos2d::LabelTTF>(tolua_S, "cc.LabelTTF",(cocos2d::LabelTTF*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 6)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:create");
            if (!ok) { break; }
            std::string arg1;
            ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.LabelTTF:create");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::Size arg3;
            ok &= luaval_to_size(tolua_S, 5, &arg3, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::TextHAlignment arg4;
            ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::TextVAlignment arg5;
            ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "cc.LabelTTF:create");
            if (!ok) { break; }
            cocos2d::LabelTTF* ret = cocos2d::LabelTTF::create(arg0, arg1, arg2, arg3, arg4, arg5);
            object_to_luaval<cocos2d::LabelTTF>(tolua_S, "cc.LabelTTF",(cocos2d::LabelTTF*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.LabelTTF:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_LabelTTF_createWithFontDefinition(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.LabelTTF",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        std::string arg0;
        cocos2d::FontDefinition arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.LabelTTF:createWithFontDefinition");
        ok &= luaval_to_fontdefinition(tolua_S, 3, &arg1, "cc.LabelTTF:createWithFontDefinition");
        if(!ok)
            return 0;
        cocos2d::LabelTTF* ret = cocos2d::LabelTTF::createWithFontDefinition(arg0, arg1);
        object_to_luaval<cocos2d::LabelTTF>(tolua_S, "cc.LabelTTF",(cocos2d::LabelTTF*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.LabelTTF:createWithFontDefinition",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_createWithFontDefinition'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_LabelTTF_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::LabelTTF* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj = new cocos2d::LabelTTF();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.LabelTTF");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.LabelTTF:new",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_LabelTTF_constructor'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_cocos2dx_LabelTTF_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LabelTTF)");
    return 0;
}

static int register_cocos2dx_deprecated_LabelTTF(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.LabelTTF");
    tolua_module(tolua_S,"cc",0);
    tolua_beginmodule(tolua_S,"cc");
        tolua_cclass(tolua_S,"LabelTTF","cc.LabelTTF","cc.Node",nullptr);
    
        tolua_beginmodule(tolua_S,"LabelTTF");
            tolua_function(tolua_S,"new",lua_cocos2dx_LabelTTF_constructor);
            tolua_function(tolua_S,"enableShadow",lua_cocos2dx_LabelTTF_enableShadow);
            tolua_function(tolua_S,"setDimensions",lua_cocos2dx_LabelTTF_setDimensions);
            tolua_function(tolua_S,"getFontSize",lua_cocos2dx_LabelTTF_getFontSize);
            tolua_function(tolua_S,"getString",lua_cocos2dx_LabelTTF_getString);
            tolua_function(tolua_S,"setFlippedY",lua_cocos2dx_LabelTTF_setFlippedY);
            tolua_function(tolua_S,"setFlippedX",lua_cocos2dx_LabelTTF_setFlippedX);
            tolua_function(tolua_S,"setTextDefinition",lua_cocos2dx_LabelTTF_setTextDefinition);
            tolua_function(tolua_S,"setFontName",lua_cocos2dx_LabelTTF_setFontName);
            tolua_function(tolua_S,"getHorizontalAlignment",lua_cocos2dx_LabelTTF_getHorizontalAlignment);
            tolua_function(tolua_S,"initWithStringAndTextDefinition",lua_cocos2dx_LabelTTF_initWithStringAndTextDefinition);
            tolua_function(tolua_S,"setString",lua_cocos2dx_LabelTTF_setString);
            tolua_function(tolua_S,"initWithString",lua_cocos2dx_LabelTTF_initWithString);
            tolua_function(tolua_S,"setFontFillColor",lua_cocos2dx_LabelTTF_setFontFillColor);
            tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_LabelTTF_getBlendFunc);
            tolua_function(tolua_S,"enableStroke",lua_cocos2dx_LabelTTF_enableStroke);
            tolua_function(tolua_S,"getDimensions",lua_cocos2dx_LabelTTF_getDimensions);
            tolua_function(tolua_S,"setVerticalAlignment",lua_cocos2dx_LabelTTF_setVerticalAlignment);
            tolua_function(tolua_S,"setFontSize",lua_cocos2dx_LabelTTF_setFontSize);
            tolua_function(tolua_S,"getVerticalAlignment",lua_cocos2dx_LabelTTF_getVerticalAlignment);
            tolua_function(tolua_S,"getTextDefinition",lua_cocos2dx_LabelTTF_getTextDefinition);
            tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_LabelTTF_setBlendFunc);
            tolua_function(tolua_S,"getFontName",lua_cocos2dx_LabelTTF_getFontName);
            tolua_function(tolua_S,"setHorizontalAlignment",lua_cocos2dx_LabelTTF_setHorizontalAlignment);
            tolua_function(tolua_S,"disableShadow",lua_cocos2dx_LabelTTF_disableShadow);
            tolua_function(tolua_S,"disableStroke",lua_cocos2dx_LabelTTF_disableStroke);
            tolua_function(tolua_S,"create", lua_cocos2dx_LabelTTF_create);
            tolua_function(tolua_S,"createWithFontDefinition", lua_cocos2dx_LabelTTF_createWithFontDefinition);
        tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::LabelTTF).name();
    g_luaType[typeName] = "cc.LabelTTF";
    g_typeCast["LabelTTF"] = "cc.LabelTTF";
    return 1;
}


int register_all_cocos2dx_deprecated(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    register_cocos2dx_deprecated_LabelBMFont(tolua_S);
    register_cocos2dx_deprecated_LabelTTF(tolua_S);
    tolua_endmodule(tolua_S);
    
    return 0;
}

extern int lua_cocos2dx_Animation_createWithSpriteFrames(lua_State* tolua_S);

static int tolua_cocos2d_Sequence_createWithTwoActions(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        FiniteTimeAction* pActionOne = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
        FiniteTimeAction* pActionTwo = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,3,0));
        {
            Sequence* tolua_ret = (Sequence*)  Sequence::createWithTwoActions(pActionOne,pActionTwo);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Sequence");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithTwoActions'.",&tolua_err);
    return 0;
#endif
}

static int extendSequenceDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Sequence");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTwoActions",tolua_cocos2d_Sequence_createWithTwoActions);
    }
    lua_pop(tolua_S, 1);
    
    return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
extern int tolua_bnd_cast(lua_State* tolua_S);
#ifdef __cplusplus
}
#endif

static int tolua_bnd_cast_deprecated00(lua_State* tolua_S)
{
    void* v = nullptr;
    std::string strValue = "";
    strValue = tolua_tostring(tolua_S,2,NULL);
    size_t pos = strValue.find("CC");
    if (pos == 0 &&
        std::string::npos == strValue.find("CCBAnimationManager") &&
        std::string::npos == strValue.find("CCString") &&
        std::string::npos == strValue.find("CCPoint") &&
        std::string::npos == strValue.find("CCRect") &&
        std::string::npos == strValue.find("CCSize") &&
        std::string::npos == strValue.find("CCArray"))
    {
        strValue = strValue.substr(2);
        if (lua_islightuserdata(tolua_S, 1)) {
            v = tolua_touserdata(tolua_S, 1, NULL);
        } else {
            v = tolua_tousertype(tolua_S, 1, 0);
        };
        if (v && !strValue.empty())
            tolua_pushusertype(tolua_S,v,strValue.c_str());
        else
            lua_pushnil(tolua_S);
        return 1;        
    }
    else
    {
        std::string castName = tolua_tostring(tolua_S,2,NULL);
        auto iter = g_typeCast.find(castName);
        if (iter != g_typeCast.end() )
        {
            CCLOG("Cast name %s doesn't include modular name which it belongs to,please add the modular name",iter->first.c_str());
            tolua_pushstring(tolua_S, iter->second.c_str());
            lua_insert(tolua_S, 2);
            lua_pop(tolua_S, 1);
        }
        return tolua_bnd_cast(tolua_S);
    }
}

static int extendToluaDeprecated(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        lua_pushstring(tolua_S,"tolua");//stack:_G,keyValue
        lua_gettable(tolua_S, -2);//stack:_G,toluaModule
        if (lua_istable(tolua_S,-1))
        {
            tolua_function(tolua_S, "cast", tolua_bnd_cast_deprecated00);
        }
        lua_pop(tolua_S, 1);//statck:_G
    }
    lua_pop(tolua_S, 1);//statck:...
    
    return 1;
}

static int tolua_cocos2d_Spawn_createWithTwoActions_deprcated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"Spawn",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"FiniteTimeAction",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        FiniteTimeAction* pAction1 = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
        FiniteTimeAction* pAction2 = ((FiniteTimeAction*)  tolua_tousertype(tolua_S,3,0));
        {
            Spawn* tolua_ret = (Spawn*)  Spawn::createWithTwoActions(pAction1,pAction2);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Spawn");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createWithTwoActions'.",&tolua_err);
    return 0;
#endif
}

static int extendSpawnDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Spawn");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTwoActions", tolua_cocos2d_Spawn_createWithTwoActions_deprcated00);
    }
    lua_pop(tolua_S, 1);
    return 1;
}

extern int lua_cocos2dx_Label_create(lua_State* tolua_S);

static int lua_cocos2dx_Label_create_deprecated(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 3 && argc <= 6)
    {
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err)  ||
            !tolua_isstring(tolua_S, 3, 0, &tolua_err)  ||
            !tolua_isnumber(tolua_S, 4, 0, &tolua_err)  ||
            !tolua_istable(tolua_S, 5, 1, &tolua_err)   ||
            !tolua_isnumber(tolua_S, 6, 1, &tolua_err)  ||
            !tolua_isnumber(tolua_S, 7, 1, &tolua_err) )
        {
            goto tolua_lerror;
        }
        else
        {
            CCLOG("The create(text, ...) was deprecated,please use create createWithTTF(text, ...) instead");
            std::string text = tolua_tocppstring(tolua_S, 2, "");
            std::string fontFile = tolua_tocppstring(tolua_S, 3, "");
            float fontSize   = tolua_tonumber(tolua_S, 4, 0);
            cocos2d::Size dimensions = cocos2d::Size::ZERO;
            if (lua_istable(tolua_S, 5))
            {
                luaval_to_size(tolua_S, 5, &dimensions, "cc.Label:create");
            }
            TextHAlignment hAlignment = static_cast<TextHAlignment>((int)tolua_tonumber(tolua_S, 6, 0));
            TextVAlignment vAlignment = static_cast<TextVAlignment>((int)tolua_tonumber(tolua_S, 7, 0));
            
            cocos2d::Label* ret = cocos2d::Label::create(text, fontFile, fontSize, dimensions, hAlignment, vAlignment);
            
            int ID = ret ? (int)(ret->_ID) : -1;
            int* luaID = ret ? &(ret->_luaID) : nullptr;
            toluafix_pushusertype_ccobject(tolua_S,ID, luaID, (void*)ret,"cc.Label");
            return 1;
        }
    }
    
tolua_lerror:
    return lua_cocos2dx_Label_create(tolua_S);
}

static void extendLabelDeprecated(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Label");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", lua_cocos2dx_Label_create_deprecated);
    }
    lua_pop(tolua_S, 1);
}


int register_all_cocos2dx_manual_deprecated(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendSequenceDeprecated(tolua_S);
    extendToluaDeprecated(tolua_S);

    return 0;
}
