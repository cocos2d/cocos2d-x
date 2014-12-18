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
#include "lua_cocos2dx_extension_nanovg_manual.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "nanovg/nanonode/NVGDrawNode.h"


static int tolua_cocos2dx_NVGDrawNode_setPoints(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::extension::NVGDrawNode* self = nullptr;
    
    tolua_Error tolua_err;
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::extension::NVGDrawNode*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_NVGDrawNode_setPoints'\n", NULL);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S) - 1;
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if(
           !tolua_istable(tolua_S, 2, 0, &tolua_err)  ||
           !tolua_isnumber(tolua_S, 3, 0, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        size_t size = lua_tonumber(tolua_S, 3);
        if ( size > 0 )
        {
            cocos2d::Vec2* points = new cocos2d::Vec2[size];
            if (NULL == points)
                return 0;
            
            for (int i = 0; i < size; i++)
            {
                lua_pushnumber(tolua_S,i + 1);
                lua_gettable(tolua_S,2);
                if (!tolua_istable(tolua_S,-1, 0, &tolua_err))
                {
                    CC_SAFE_DELETE_ARRAY(points);
#if COCOS2D_DEBUG >= 1
                    goto tolua_lerror;
#endif
                }
                
                if(!luaval_to_vec2(tolua_S, lua_gettop(tolua_S), &points[i], "cc.NVGDrawNode:setPoints"))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }

            self->setPoints(points, (int)size);
            CC_SAFE_DELETE_ARRAY(points);
            return 0;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.NVGDrawNode:setPoints", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_NVGDrawNode_setPoints'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_NVGDrawNode_drawSolidPolygon(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::extension::NVGDrawNode* self = nullptr;
    
    tolua_Error tolua_err;
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::extension::NVGDrawNode*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_NVGDrawNode_drawSolidPolygon'\n", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (3 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if(
           !tolua_istable(tolua_S, 2, 0, &tolua_err)  ||
           !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
           !tolua_istable(tolua_S, 4, 0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        size_t size = lua_tonumber(tolua_S, 3);
        if ( size > 0 )
        {
            cocos2d::Vec2* points = new cocos2d::Vec2[size];
            if (NULL == points)
                return 0;
            
            for (int i = 0; i < size; i++)
            {
                lua_pushnumber(tolua_S,i + 1);
                lua_gettable(tolua_S,2);
                if (!tolua_istable(tolua_S,-1, 0, &tolua_err))
                {
                    CC_SAFE_DELETE_ARRAY(points);
#if COCOS2D_DEBUG >= 1
                    goto tolua_lerror;
#endif
                }
                
                if(!luaval_to_vec2(tolua_S, lua_gettop(tolua_S), &points[i], "cc.NVGDrawNode:drawSolidPolygon"))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }
            
            Color4F fillColor;
            if (!luaval_to_color4f(tolua_S, 4, &fillColor, "cc.NVGDrawNode:drawPolygon"))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }

            self->drawSolidPolygon(points, (int)size, fillColor);
            CC_SAFE_DELETE_ARRAY(points);
            return 0;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.NVGDrawNode:drawSolidPolygon", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_DrawNode_drawSolidPolygon'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2dx_NVGDrawNode_drawPolygon(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::extension::NVGDrawNode* self = nullptr;
    bool ok  = true;
    
    tolua_Error tolua_err;
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::extension::NVGDrawNode*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (!self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_NVGDrawNode_drawPolygon'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 4)
    {
        unsigned int size;
        luaval_to_uint32(tolua_S, 3, &size, "cc.NVGDrawNode:drawPolygon");
        if ( size > 0 )
        {
            cocos2d::Vec2* points = new cocos2d::Vec2[size];
            if (NULL == points)
                return 0;
            
            for (int i = 0; i < size; i++)
            {
                lua_pushnumber(tolua_S,i + 1);
                lua_gettable(tolua_S,2);
                if (!tolua_istable(tolua_S,-1, 0, &tolua_err))
                {
                    CC_SAFE_DELETE_ARRAY(points);
#if COCOS2D_DEBUG >= 1
                    goto tolua_lerror;
#endif
                }
                
                if(!luaval_to_vec2(tolua_S, lua_gettop(tolua_S), &points[i], "cc.NVGDrawNode:drawPolygon"))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }
            
            bool arg2;
            cocos2d::Color4F arg3;
            
            ok &= luaval_to_boolean(tolua_S, 4,&arg2, "cc.NVGDrawNode:drawPolygon");
            
            ok &= luaval_to_color4f(tolua_S, 5, &arg3, "cc.NVGDrawNode:drawPolygon");
            if(!ok)
                return 0;
            
            self->drawPolygon(points, size, arg2, arg3);
            CC_SAFE_DELETE_ARRAY(points);
            return 0;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawPolygon",argc, 4);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_NVGDrawNode_drawPolygon'.",&tolua_err);
#endif
    
    return 0;
}

int tolua_cocos2dx_NVGDrawNode_drawPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extension::NVGDrawNode* self = nullptr;
    bool ok  = true;
    
    tolua_Error tolua_err;
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NVGDrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::extension::NVGDrawNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_NVGDrawNode_drawPoints'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        unsigned int size;
        luaval_to_uint32(tolua_S, 3, &size, "cc.NVGDrawNode:drawPoints");
        if ( size > 0 )
        {
            cocos2d::Vec2* points = new cocos2d::Vec2[size];
            if (NULL == points)
                return 0;
            
            for (int i = 0; i < size; i++)
            {
                lua_pushnumber(tolua_S,i + 1);
                lua_gettable(tolua_S,2);
                if (!tolua_istable(tolua_S,-1, 0, &tolua_err))
                {
                    CC_SAFE_DELETE_ARRAY(points);
#if COCOS2D_DEBUG >= 1
                    goto tolua_lerror;
#endif
                }
                
                if(!luaval_to_vec2(tolua_S, lua_gettop(tolua_S), &points[i], "cc.NVGDrawNode:drawPoints"))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }
            
            cocos2d::Color4F arg2;
            
            ok &=luaval_to_color4f(tolua_S, 4, &arg2, "cc.NVGDrawNode:drawPoints");
            if(!ok)
                return 0;
            self->drawPoints(points, size, arg2);
            return 0;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.NVGDrawNode:drawPoints",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_NVGDrawNode_drawPoints'.",&tolua_err);
#endif
    
    return 0;
}


static void extendNVGDrawNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.NVGDrawNode");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {        
        lua_pushstring(tolua_S,"drawPoints");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_NVGDrawNode_drawPoints);
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"drawPolygon");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_NVGDrawNode_drawPolygon);
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"drawSolidPolygon");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_NVGDrawNode_drawSolidPolygon);
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"setPoints");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_NVGDrawNode_setPoints);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

int register_all_cocos2dx_extension_nanovg_manual(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;

    extendNVGDrawNode(tolua_S);

    return 0;
}

