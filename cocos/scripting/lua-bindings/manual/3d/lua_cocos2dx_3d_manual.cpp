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

int lua_cocos2dx_3d_Sprite3D_setBlendFunc(lua_State* L)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Sprite3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_setBlendFunc'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 2)
    {
        GLenum src, dst;
        if (!luaval_to_int32(L, 2, (int32_t*)&src, "cc.Sprite3D:setBlendFunc"))
            return 0;
        
        if (!luaval_to_int32(L, 3, (int32_t*)&dst, "cc.Sprite3D:setBlendFunc"))
            return 0;
        
        BlendFunc blendFunc = {src, dst};
        cobj->setBlendFunc(blendFunc);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:setBlendFunc",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_setBlendFunc'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_3d_Sprite3D_getAABB(lua_State* L)
{
    int argc = 0;
    cocos2d::Sprite3D* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.Sprite3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Sprite3D*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_Sprite3D_getAABB'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        cocos2d::AABB* ret = const_cast<cocos2d::AABB*>(&(cobj->getAABB()));
        object_to_luaval<cocos2d::AABB>(L, "cc.AABB",(cocos2d::AABB*)ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Sprite3D:getAABB",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_Sprite3D_getAABB'.",&tolua_err);
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
        tolua_function(L, "getAABB", lua_cocos2dx_3d_Sprite3D_getAABB);
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

int lua_cocos2dx_3d_AABB_reset(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_reset'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->reset();
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:reset",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_reset'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_set(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_set'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 2)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        
        ok &= luaval_to_vec3(L, 2, &arg0, "cc.AABB:set");
        
        ok &= luaval_to_vec3(L, 3, &arg1, "cc.AABB:set");
        if(!ok)
            return 0;
        cobj->set(arg0, arg1);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:set",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_set'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_transform(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_transform'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Mat4 arg0;
        
        ok &= luaval_to_mat4(L, 2, &arg0, "cc.AABB:transform");
        if(!ok)
            return 0;
        cobj->transform(arg0);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:transform",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_transform'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_getCenter(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_getCenter'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::Vec3 ret = cobj->getCenter();
        vec3_to_luaval(L, ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:getCenter",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_getCenter'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_isEmpty(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_isEmpty'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        bool ret = cobj->isEmpty();
        tolua_pushboolean(L,(bool)ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:isEmpty",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_isEmpty'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_getCorners(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_getCorners'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Vec3* arg0;
        
        ok &= luaval_to_object<cocos2d::Vec3>(L, 2, "cc.Vec3",&arg0);
        if(!ok)
            return 0;
        cobj->getCorners(arg0);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:getCorners",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_getCorners'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_updateMinMax(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_updateMinMax'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 2)
    {
        const cocos2d::Vec3* arg0;
        ssize_t arg1;
        
        ok &= luaval_to_object<const cocos2d::Vec3>(L, 2, "cc.Vec3",&arg0);
        
        ok &= luaval_to_ssize(L, 3, &arg1, "cc.AABB:updateMinMax");
        if(!ok)
            return 0;
        cobj->updateMinMax(arg0, arg1);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:updateMinMax",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_updateMinMax'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_containPoint(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::AABB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_AABB_containPoint'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Vec3 arg0;
        
        ok &= luaval_to_vec3(L, 2, &arg0, "cc.AABB:containPoint");
        if(!ok)
            return 0;
        bool ret = cobj->containPoint(arg0);
        tolua_pushboolean(L,(bool)ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.AABB:containPoint",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_containPoint'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_AABB_constructor(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    argc = lua_gettop(L)-1;
    do{
        if (argc == 2) {
            cocos2d::Vec3 arg0;
            ok &= luaval_to_vec3(L, 2, &arg0, "cc.AABB:AABB");
            
            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(L, 3, &arg1, "cc.AABB:AABB");
            
            if (!ok) { break; }
            cobj = new cocos2d::AABB(arg0, arg1);
            tolua_pushusertype(L,(void*)cobj,"cc.AABB");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new cocos2d::AABB();
            tolua_pushusertype(L,(void*)cobj,"cc.AABB");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.AABB:AABB",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_AABB_constructor'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_get_AABB_min(lua_State* L)
{
    cocos2d::AABB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::AABB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_AABB_min'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_min);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_AABB_min'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_AABB_min(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::AABB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_AABB_min'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_min);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_AABB_min'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_AABB_max(lua_State* L)
{
    cocos2d::AABB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::AABB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_AABB_max'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_max);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_AABB_max'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_AABB_max(lua_State* L)
{
    int argc = 0;
    cocos2d::AABB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.AABB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::AABB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_AABB_max'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_max);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_Ray_direction'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_AABB_finalize(lua_State* L)
{
    cocos2d::AABB* self = (cocos2d::AABB*) tolua_tousertype(L,1,0);
    CC_SAFE_DELETE(self);
    return 0;
}

int lua_register_cocos2dx_3d_AABB(lua_State* L)
{
    tolua_usertype(L,"cc.AABB");
    tolua_cclass(L,"AABB","cc.AABB","",lua_cocos2dx_3d_AABB_finalize);
    
    tolua_beginmodule(L,"AABB");
        tolua_variable(L, "_min", lua_cocos2dx_3d_get_AABB_min, lua_cocos2dx_3d_set_AABB_min);
        tolua_variable(L, "_max", lua_cocos2dx_3d_get_AABB_max, lua_cocos2dx_3d_set_AABB_max);
        tolua_function(L,"new",lua_cocos2dx_3d_AABB_constructor);
        tolua_function(L,"reset",lua_cocos2dx_3d_AABB_reset);
        tolua_function(L,"set",lua_cocos2dx_3d_AABB_set);
        tolua_function(L,"transform",lua_cocos2dx_3d_AABB_transform);
        tolua_function(L,"getCenter",lua_cocos2dx_3d_AABB_getCenter);
        tolua_function(L,"isEmpty",lua_cocos2dx_3d_AABB_isEmpty);
        tolua_function(L,"getCorners",lua_cocos2dx_3d_AABB_getCorners);
        tolua_function(L,"updateMinMax",lua_cocos2dx_3d_AABB_updateMinMax);
        tolua_function(L,"containPoint",lua_cocos2dx_3d_AABB_containPoint);
    tolua_endmodule(L);
    std::string typeName = typeid(cocos2d::AABB).name();
    g_luaType[typeName] = "cc.AABB";
    g_typeCast["AABB"] = "cc.AABB";
    return 1;
}

int lua_cocos2dx_3d_OBB_reset(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::OBB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_OBB_reset'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->reset();
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OBB:reset",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_reset'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_OBB_set(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::OBB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_OBB_set'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 5)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Vec3 arg2;
        cocos2d::Vec3 arg3;
        cocos2d::Vec3 arg4;
        
        ok &= luaval_to_vec3(L, 2, &arg0, "cc.OBB:set");
        
        ok &= luaval_to_vec3(L, 3, &arg1, "cc.OBB:set");
        
        ok &= luaval_to_vec3(L, 4, &arg2, "cc.OBB:set");
        
        ok &= luaval_to_vec3(L, 5, &arg3, "cc.OBB:set");
        
        ok &= luaval_to_vec3(L, 6, &arg4, "cc.OBB:set");
        if(!ok)
            return 0;
        cobj->set(arg0, arg1, arg2, arg3, arg4);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OBB:set",argc, 5);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_set'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_OBB_transform(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::OBB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_OBB_transform'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Mat4 arg0;
        
        ok &= luaval_to_mat4(L, 2, &arg0, "cc.OBB:transform");
        if(!ok)
            return 0;
        cobj->transform(arg0);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OBB:transform",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_transform'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_OBB_containPoint(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::OBB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_OBB_containPoint'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Vec3 arg0;
        
        ok &= luaval_to_vec3(L, 2, &arg0, "cc.OBB:containPoint");
        if(!ok)
            return 0;
        bool ret = cobj->containPoint(arg0);
        tolua_pushboolean(L,(bool)ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OBB:containPoint",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_containPoint'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_OBB_constructor(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    argc = lua_gettop(L)-1;
    do{
        if (argc == 1) {
            cocos2d::AABB* arg0;
            ok &= luaval_to_object<cocos2d::AABB>(L, 2, "cc.AABB",&arg0);
            
            if (!ok) { break; }
            cobj = new cocos2d::OBB(*arg0);
            tolua_pushusertype(L,(void*)cobj,"cc.OBB");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new cocos2d::OBB();
            tolua_pushusertype(L,(void*)cobj,"cc.OBB");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const cocos2d::Vec3* arg0;
            ok &= luaval_to_object<const cocos2d::Vec3>(L, 2, "cc.Vec3",&arg0);
            
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(L, 3,(int *)&arg1, "cc.OBB:OBB");
            
            if (!ok) { break; }
            cobj = new cocos2d::OBB(arg0, arg1);
            tolua_pushusertype(L,(void*)cobj,"cc.OBB");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.OBB:OBB",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_constructor'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_OBB_intersects(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* self = nullptr;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_OBB_intersects'\n", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(L)-1;
    if(1 == argc)
    {
        cocos2d::OBB* arg0;
        ok &= luaval_to_object<cocos2d::OBB>(L, 2, "cc.OBB",&arg0);
        
        if (!ok)
            return 0;
        
        bool ret = self->intersects(*arg0);
        tolua_pushboolean(L, ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.OBB:intersects",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_intersects'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_OBB_center(lua_State* L)
{
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_OBB_center'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_center);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_OBB_center'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_OBB_center(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_OBB_center'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_center);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_OBB_center'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_OBB_xAxis(lua_State* L)
{
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_OBB_xAxis'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_xAxis);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_OBB_xAxis'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_OBB_xAxis(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_OBB_xAxis'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_xAxis);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_OBB_center'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_OBB_yAxis(lua_State* L)
{
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_OBB_yAxis'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_yAxis);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_OBB_yAxis'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_OBB_yAxis(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_OBB_yAxis'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_yAxis);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_OBB_yAxis'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_OBB_zAxis(lua_State* L)
{
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_OBB_zAxis'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_zAxis);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_OBB_zAxis'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_OBB_zAxis(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_OBB_zAxis'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_zAxis);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_OBB_zAxis'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_OBB_extents(lua_State* L)
{
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_OBB_extents'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_extents);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_OBB_extents'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_OBB_extents(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OBB*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_OBB_extents'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_extents);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_OBB_extents'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_OBB_getCorners(lua_State* L)
{
    int argc = 0;
    cocos2d::OBB* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.OBB",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::OBB*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_OBB_getCorners'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Vec3* arg0;
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        
        size_t len = lua_objlen(L, 2);
        if (len == 0 )
        {
            luaL_error(L, "Table's len equal 0");
            return 0;
        }
        
        arg0 = new cocos2d::Vec3[len];
        
        if (nullptr == arg0)
        {
            luaL_error(L, "Allocate cocos2d::Vec3 array in the lua_cocos2dx_3d_OBB_getCorners failed!");
            return 0;
        }
        
        for (int i = 1 ; i <= len; i++)
        {
            lua_pushnumber(L,i);
            lua_gettable(L,2);
            if (lua_isnil(L, -1))
            {
                arg0[i - 1] = cocos2d::Vec3(0,0,0);
            }
            else
            {
                luaval_to_vec3(L, -1, &arg0[i - 1], "cc.OBB:getCorners");
            }
            lua_pop(L,1);
        }
        
        cobj->getCorners(arg0);
        
        lua_newtable(L);
        
        for (int i = 1; i <= len; i++)
        {
            lua_pushnumber(L, i);
            vec3_to_luaval(L, arg0[i - 1]);
            lua_rawset(L, -3);
        }
        CC_SAFE_DELETE_ARRAY(arg0);
        
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.OBB:getCorners",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_OBB_getCorners'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_OBB_finalize(lua_State* L)
{
    cocos2d::OBB* self = (cocos2d::OBB*) tolua_tousertype(L,1,0);
    CC_SAFE_DELETE(self);
    return 0;
}

int lua_register_cocos2dx_3d_OBB(lua_State* L)
{
    tolua_usertype(L,"cc.OBB");
    tolua_cclass(L,"OBB","cc.OBB","",lua_cocos2dx_3d_OBB_finalize);
    
    tolua_beginmodule(L,"OBB");
        tolua_variable(L, "_center", lua_cocos2dx_3d_get_OBB_center, lua_cocos2dx_3d_set_OBB_center);
        tolua_variable(L, "_xAxis", lua_cocos2dx_3d_get_OBB_xAxis, lua_cocos2dx_3d_set_OBB_xAxis);
        tolua_variable(L, "_yAxis", lua_cocos2dx_3d_get_OBB_yAxis, lua_cocos2dx_3d_set_OBB_yAxis);
        tolua_variable(L, "_zAxis", lua_cocos2dx_3d_get_OBB_zAxis, lua_cocos2dx_3d_set_OBB_zAxis);
        tolua_variable(L, "_extents", lua_cocos2dx_3d_get_OBB_extents, lua_cocos2dx_3d_set_OBB_extents);
        tolua_function(L, "new", lua_cocos2dx_3d_OBB_constructor);
        tolua_function(L,"reset",lua_cocos2dx_3d_OBB_reset);
        tolua_function(L,"set",lua_cocos2dx_3d_OBB_set);
        tolua_function(L,"transform",lua_cocos2dx_3d_OBB_transform);
        tolua_function(L,"containPoint",lua_cocos2dx_3d_OBB_containPoint);
        tolua_function(L,"intersects", lua_cocos2dx_3d_OBB_intersects);
        tolua_function(L,"getCorners", lua_cocos2dx_3d_OBB_getCorners);
    tolua_endmodule(L);
    std::string typeName = typeid(cocos2d::OBB).name();
    g_luaType[typeName] = "cc.OBB";
    g_typeCast["OBB"] = "cc.OBB";
    return 1;
}

int lua_cocos2dx_3d_Ray_set(lua_State* L)
{
    int argc = 0;
    cocos2d::Ray* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Ray*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_Ray_set'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 2)
    {
        cocos2d::Vec3 arg0;
        cocos2d::Vec3 arg1;
        
        ok &= luaval_to_vec3(L, 2, &arg0, "cc.Ray:set");
        
        ok &= luaval_to_vec3(L, 3, &arg1, "cc.Ray:set");
        if(!ok)
            return 0;
        cobj->set(arg0, arg1);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ray:set",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_Ray_set'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_3d_Ray_transform(lua_State* L)
{
    int argc = 0;
    cocos2d::Ray* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Ray*)tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(L,"invalid 'cobj' in function 'lua_cocos2dx_3d_Ray_transform'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L)-1;
    if (argc == 1)
    {
        cocos2d::Mat4 arg0;
        
        ok &= luaval_to_mat4(L, 2, &arg0, "cc.Ray:transform");
        if(!ok)
            return 0;
        cobj->transform(arg0);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.Ray:transform",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_Ray_transform'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_Ray_intersects(lua_State* L)
{
    int argc = 0;
    cocos2d::Ray* self = nullptr;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::Ray*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_Ray_intersects'\n", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(L)-1;
    if(1 == argc)
    {
        cocos2d::OBB* arg0 = nullptr;
        ok &= luaval_to_object<cocos2d::OBB>(L, 2, "cc.OBB",&arg0);
        
        if (!ok)
            return 0;
        
        bool ret = self->intersects(*arg0);
        tolua_pushboolean(L, ret);
        return 1;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Ray:intersects",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_OBB_center'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_Ray_constructor(lua_State* L)
{
    int argc = 0;
    cocos2d::Ray* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    argc = lua_gettop(L)-1;
    do{
        if (argc == 2) {
            cocos2d::Vec3 arg0;
            ok &= luaval_to_vec3(L, 2, &arg0, "cc.Ray:Ray");
            
            if (!ok) { break; }
            cocos2d::Vec3 arg1;
            ok &= luaval_to_vec3(L, 3, &arg1, "cc.Ray:Ray");
            
            if (!ok) { break; }
            cobj = new cocos2d::Ray(arg0, arg1);
            tolua_pushusertype(L,(void*)cobj,"cc.Ray");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj = new cocos2d::Ray();
            tolua_pushusertype(L,(void*)cobj,"cc.Ray");
            tolua_register_gc(L,lua_gettop(L));
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.Ray:Ray",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_Ray_constructor'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_3d_get_Ray_origin(lua_State* L)
{
    cocos2d::Ray* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::Ray*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_Ray_origin'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_origin);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_Ray_origin'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_Ray_origin(lua_State* L)
{
    int argc = 0;
    cocos2d::Ray* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::Ray*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_Ray_origin'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_origin);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_Ray_origin'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_get_Ray_direction(lua_State* L)
{
    cocos2d::Ray* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::Ray*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_get_Ray_direction'\n", nullptr);
        return 0;
    }
#endif
    vec3_to_luaval(L, self->_direction);
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_get_Ray_direction'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_set_Ray_direction(lua_State* L)
{
    int argc = 0;
    cocos2d::Ray* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.Ray",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::Ray*)  tolua_tousertype(L,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_3d_set_Ray_direction'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        luaval_to_vec3(L, 2, &self->_direction);
        return 0;
    }
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_3d_set_Ray_direction'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_3d_Ray_finalize(lua_State* L)
{
    cocos2d::Ray* self = (cocos2d::Ray*) tolua_tousertype(L,1,0);
    CC_SAFE_DELETE(self);
    return 0;
}

int lua_register_cocos2dx_3d_Ray(lua_State* L)
{
    tolua_usertype(L,"cc.Ray");
    tolua_cclass(L,"Ray","cc.Ray","",lua_cocos2dx_3d_Ray_finalize);
    
    tolua_beginmodule(L,"Ray");
        tolua_variable(L, "_origin", lua_cocos2dx_3d_get_Ray_origin, lua_cocos2dx_3d_set_Ray_origin);
        tolua_variable(L, "_direction", lua_cocos2dx_3d_get_Ray_direction, lua_cocos2dx_3d_set_Ray_direction);
        tolua_function(L,"new",lua_cocos2dx_3d_Ray_constructor);
        tolua_function(L,"set",lua_cocos2dx_3d_Ray_set);
        tolua_function(L,"transform",lua_cocos2dx_3d_Ray_transform);
        tolua_function(L, "intersects", lua_cocos2dx_3d_Ray_intersects);
    tolua_endmodule(L);
    std::string typeName = typeid(cocos2d::Ray).name();
    g_luaType[typeName] = "cc.Ray";
    g_typeCast["Ray"] = "cc.Ray";
    return 1;
}

int register_all_cocos3d_manual_class(lua_State* L)
{
    tolua_module(L,"cc",0);
    tolua_beginmodule(L,"cc");
        lua_register_cocos2dx_3d_AABB(L);
        lua_register_cocos2dx_3d_OBB(L);
    	lua_register_cocos2dx_3d_Ray(L);
    tolua_endmodule(L);
    
    return 0;
}

int register_cocos3d_module(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        register_all_cocos2dx_3d(L);
        register_all_cocos2dx_3d_manual(L);
        register_all_cocos3d_manual_class(L);
    }
    lua_pop(L, 1);
    
    return 1;
}
