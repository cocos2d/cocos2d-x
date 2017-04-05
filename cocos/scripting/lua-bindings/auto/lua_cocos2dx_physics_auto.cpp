#include "scripting/lua-bindings/auto/lua_cocos2dx_physics_auto.hpp"
#if CC_USE_PHYSICS
#include "cocos2d.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_physics_PhysicsShape_getFriction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getFriction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getFriction'", nullptr);
            return 0;
        }
        double ret = cobj->getFriction();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getFriction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getFriction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setGroup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsShape:setGroup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setGroup'", nullptr);
            return 0;
        }
        cobj->setGroup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setGroup",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setGroup'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setDensity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setDensity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShape:setDensity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setDensity'", nullptr);
            return 0;
        }
        cobj->setDensity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setDensity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setDensity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getMass(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getMass'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getMass'", nullptr);
            return 0;
        }
        double ret = cobj->getMass();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getMass",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getMass'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getMaterial(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getMaterial'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getMaterial'", nullptr);
            return 0;
        }
        const cocos2d::PhysicsMaterial& ret = cobj->getMaterial();
        physics_material_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getMaterial",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getMaterial'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setSensor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setSensor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsShape:setSensor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setSensor'", nullptr);
            return 0;
        }
        cobj->setSensor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setSensor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setSensor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getCollisionBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getCollisionBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getCollisionBitmask'", nullptr);
            return 0;
        }
        int ret = cobj->getCollisionBitmask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getCollisionBitmask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getCollisionBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getArea(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getArea'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getArea'", nullptr);
            return 0;
        }
        double ret = cobj->getArea();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getArea",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getArea'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setCategoryBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setCategoryBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsShape:setCategoryBitmask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setCategoryBitmask'", nullptr);
            return 0;
        }
        cobj->setCategoryBitmask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setCategoryBitmask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setCategoryBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getGroup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getGroup'", nullptr);
            return 0;
        }
        int ret = cobj->getGroup();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getGroup",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getGroup'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setMoment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setMoment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShape:setMoment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setMoment'", nullptr);
            return 0;
        }
        cobj->setMoment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setMoment",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setMoment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_containsPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_containsPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsShape:containsPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_containsPoint'", nullptr);
            return 0;
        }
        bool ret = cobj->containsPoint(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:containsPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_containsPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getCategoryBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getCategoryBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getCategoryBitmask'", nullptr);
            return 0;
        }
        int ret = cobj->getCategoryBitmask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getCategoryBitmask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getCategoryBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_isSensor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_isSensor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_isSensor'", nullptr);
            return 0;
        }
        bool ret = cobj->isSensor();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:isSensor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_isSensor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getType(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getType'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getContactTestBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getContactTestBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getContactTestBitmask'", nullptr);
            return 0;
        }
        int ret = cobj->getContactTestBitmask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getContactTestBitmask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getContactTestBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getCenter(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getCenter'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getCenter'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getCenter();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getCenter",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getCenter'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getDensity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getDensity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getDensity'", nullptr);
            return 0;
        }
        double ret = cobj->getDensity();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getDensity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getDensity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setMass(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setMass'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShape:setMass");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setMass'", nullptr);
            return 0;
        }
        cobj->setMass(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setMass",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setMass'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getTag'", nullptr);
            return 0;
        }
        int ret = cobj->getTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_calculateDefaultMoment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_calculateDefaultMoment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_calculateDefaultMoment'", nullptr);
            return 0;
        }
        double ret = cobj->calculateDefaultMoment();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:calculateDefaultMoment",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_calculateDefaultMoment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setCollisionBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setCollisionBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsShape:setCollisionBitmask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setCollisionBitmask'", nullptr);
            return 0;
        }
        cobj->setCollisionBitmask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setCollisionBitmask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setCollisionBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getMoment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getMoment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getMoment'", nullptr);
            return 0;
        }
        double ret = cobj->getMoment();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getMoment",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getMoment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getOffset'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getRestitution(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getRestitution'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getRestitution'", nullptr);
            return 0;
        }
        double ret = cobj->getRestitution();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getRestitution",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getRestitution'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setFriction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setFriction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShape:setFriction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setFriction'", nullptr);
            return 0;
        }
        cobj->setFriction(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setFriction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setFriction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setMaterial(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setMaterial'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::PhysicsMaterial arg0;

        ok &= luaval_to_physics_material(tolua_S, 2, &arg0, "cc.PhysicsShape:setMaterial");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setMaterial'", nullptr);
            return 0;
        }
        cobj->setMaterial(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setMaterial",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setMaterial'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsShape:setTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setTag'", nullptr);
            return 0;
        }
        cobj->setTag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setContactTestBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setContactTestBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsShape:setContactTestBitmask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setContactTestBitmask'", nullptr);
            return 0;
        }
        cobj->setContactTestBitmask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setContactTestBitmask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setContactTestBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_setRestitution(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_setRestitution'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShape:setRestitution");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_setRestitution'", nullptr);
            return 0;
        }
        cobj->setRestitution(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:setRestitution",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_setRestitution'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShape_getBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShape* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShape",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShape*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShape_getBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShape_getBody'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cobj->getBody();
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShape:getBody",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShape_getBody'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsShape_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShape)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShape(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShape");
    tolua_cclass(tolua_S,"PhysicsShape","cc.PhysicsShape","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShape");
        tolua_function(tolua_S,"getFriction",lua_cocos2dx_physics_PhysicsShape_getFriction);
        tolua_function(tolua_S,"setGroup",lua_cocos2dx_physics_PhysicsShape_setGroup);
        tolua_function(tolua_S,"setDensity",lua_cocos2dx_physics_PhysicsShape_setDensity);
        tolua_function(tolua_S,"getMass",lua_cocos2dx_physics_PhysicsShape_getMass);
        tolua_function(tolua_S,"getMaterial",lua_cocos2dx_physics_PhysicsShape_getMaterial);
        tolua_function(tolua_S,"setSensor",lua_cocos2dx_physics_PhysicsShape_setSensor);
        tolua_function(tolua_S,"getCollisionBitmask",lua_cocos2dx_physics_PhysicsShape_getCollisionBitmask);
        tolua_function(tolua_S,"getArea",lua_cocos2dx_physics_PhysicsShape_getArea);
        tolua_function(tolua_S,"setCategoryBitmask",lua_cocos2dx_physics_PhysicsShape_setCategoryBitmask);
        tolua_function(tolua_S,"getGroup",lua_cocos2dx_physics_PhysicsShape_getGroup);
        tolua_function(tolua_S,"setMoment",lua_cocos2dx_physics_PhysicsShape_setMoment);
        tolua_function(tolua_S,"containsPoint",lua_cocos2dx_physics_PhysicsShape_containsPoint);
        tolua_function(tolua_S,"getCategoryBitmask",lua_cocos2dx_physics_PhysicsShape_getCategoryBitmask);
        tolua_function(tolua_S,"isSensor",lua_cocos2dx_physics_PhysicsShape_isSensor);
        tolua_function(tolua_S,"getType",lua_cocos2dx_physics_PhysicsShape_getType);
        tolua_function(tolua_S,"getContactTestBitmask",lua_cocos2dx_physics_PhysicsShape_getContactTestBitmask);
        tolua_function(tolua_S,"getCenter",lua_cocos2dx_physics_PhysicsShape_getCenter);
        tolua_function(tolua_S,"getDensity",lua_cocos2dx_physics_PhysicsShape_getDensity);
        tolua_function(tolua_S,"setMass",lua_cocos2dx_physics_PhysicsShape_setMass);
        tolua_function(tolua_S,"getTag",lua_cocos2dx_physics_PhysicsShape_getTag);
        tolua_function(tolua_S,"calculateDefaultMoment",lua_cocos2dx_physics_PhysicsShape_calculateDefaultMoment);
        tolua_function(tolua_S,"setCollisionBitmask",lua_cocos2dx_physics_PhysicsShape_setCollisionBitmask);
        tolua_function(tolua_S,"getMoment",lua_cocos2dx_physics_PhysicsShape_getMoment);
        tolua_function(tolua_S,"getOffset",lua_cocos2dx_physics_PhysicsShape_getOffset);
        tolua_function(tolua_S,"getRestitution",lua_cocos2dx_physics_PhysicsShape_getRestitution);
        tolua_function(tolua_S,"setFriction",lua_cocos2dx_physics_PhysicsShape_setFriction);
        tolua_function(tolua_S,"setMaterial",lua_cocos2dx_physics_PhysicsShape_setMaterial);
        tolua_function(tolua_S,"setTag",lua_cocos2dx_physics_PhysicsShape_setTag);
        tolua_function(tolua_S,"setContactTestBitmask",lua_cocos2dx_physics_PhysicsShape_setContactTestBitmask);
        tolua_function(tolua_S,"setRestitution",lua_cocos2dx_physics_PhysicsShape_setRestitution);
        tolua_function(tolua_S,"getBody",lua_cocos2dx_physics_PhysicsShape_getBody);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShape).name();
    g_luaType[typeName] = "cc.PhysicsShape";
    g_typeCast["PhysicsShape"] = "cc.PhysicsShape";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapeCircle_getRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeCircle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeCircle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapeCircle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeCircle_getRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_getRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapeCircle:getRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeCircle_getRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShapeCircle_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShapeCircle",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShapeCircle:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeCircle* ret = cocos2d::PhysicsShapeCircle::create(arg0);
        object_to_luaval<cocos2d::PhysicsShapeCircle>(tolua_S, "cc.PhysicsShapeCircle",(cocos2d::PhysicsShapeCircle*)ret);
        return 1;
    }
    if (argc == 2)
    {
        double arg0;
        cocos2d::PhysicsMaterial arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShapeCircle:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeCircle:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeCircle* ret = cocos2d::PhysicsShapeCircle::create(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsShapeCircle>(tolua_S, "cc.PhysicsShapeCircle",(cocos2d::PhysicsShapeCircle*)ret);
        return 1;
    }
    if (argc == 3)
    {
        double arg0;
        cocos2d::PhysicsMaterial arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShapeCircle:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeCircle:create");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsShapeCircle:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeCircle* ret = cocos2d::PhysicsShapeCircle::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsShapeCircle>(tolua_S, "cc.PhysicsShapeCircle",(cocos2d::PhysicsShapeCircle*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsShapeCircle:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeCircle_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_physics_PhysicsShapeCircle_calculateArea(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShapeCircle",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShapeCircle:calculateArea");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_calculateArea'", nullptr);
            return 0;
        }
        double ret = cocos2d::PhysicsShapeCircle::calculateArea(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsShapeCircle:calculateArea",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeCircle_calculateArea'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_physics_PhysicsShapeCircle_calculateMoment(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShapeCircle",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        double arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShapeCircle:calculateMoment");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.PhysicsShapeCircle:calculateMoment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_calculateMoment'", nullptr);
            return 0;
        }
        double ret = cocos2d::PhysicsShapeCircle::calculateMoment(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 3)
    {
        double arg0;
        double arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsShapeCircle:calculateMoment");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.PhysicsShapeCircle:calculateMoment");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsShapeCircle:calculateMoment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeCircle_calculateMoment'", nullptr);
            return 0;
        }
        double ret = cocos2d::PhysicsShapeCircle::calculateMoment(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsShapeCircle:calculateMoment",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeCircle_calculateMoment'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapeCircle_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapeCircle)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapeCircle(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapeCircle");
    tolua_cclass(tolua_S,"PhysicsShapeCircle","cc.PhysicsShapeCircle","cc.PhysicsShape",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapeCircle");
        tolua_function(tolua_S,"getRadius",lua_cocos2dx_physics_PhysicsShapeCircle_getRadius);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_PhysicsShapeCircle_create);
        tolua_function(tolua_S,"calculateArea", lua_cocos2dx_physics_PhysicsShapeCircle_calculateArea);
        tolua_function(tolua_S,"calculateMoment", lua_cocos2dx_physics_PhysicsShapeCircle_calculateMoment);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapeCircle).name();
    g_luaType[typeName] = "cc.PhysicsShapeCircle";
    g_typeCast["PhysicsShapeCircle"] = "cc.PhysicsShapeCircle";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapePolygon_getPointsCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapePolygon* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapePolygon",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapePolygon*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPointsCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPointsCount'", nullptr);
            return 0;
        }
        int ret = cobj->getPointsCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapePolygon:getPointsCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPointsCount'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShapePolygon_getPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapePolygon* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapePolygon",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapePolygon*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsShapePolygon:getPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPoint'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getPoint(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapePolygon:getPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapePolygon_getPoint'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapePolygon_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapePolygon)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapePolygon(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapePolygon");
    tolua_cclass(tolua_S,"PhysicsShapePolygon","cc.PhysicsShapePolygon","cc.PhysicsShape",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapePolygon");
        tolua_function(tolua_S,"getPointsCount",lua_cocos2dx_physics_PhysicsShapePolygon_getPointsCount);
        tolua_function(tolua_S,"getPoint",lua_cocos2dx_physics_PhysicsShapePolygon_getPoint);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapePolygon).name();
    g_luaType[typeName] = "cc.PhysicsShapePolygon";
    g_typeCast["PhysicsShapePolygon"] = "cc.PhysicsShapePolygon";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapeBox_getSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeBox* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeBox",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapeBox*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeBox_getSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeBox_getSize'", nullptr);
            return 0;
        }
        cocos2d::Size ret = cobj->getSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapeBox:getSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeBox_getSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShapeBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShapeBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Size arg0;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeBox* ret = cocos2d::PhysicsShapeBox::create(arg0);
        object_to_luaval<cocos2d::PhysicsShapeBox>(tolua_S, "cc.PhysicsShapeBox",(cocos2d::PhysicsShapeBox*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeBox:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeBox* ret = cocos2d::PhysicsShapeBox::create(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsShapeBox>(tolua_S, "cc.PhysicsShapeBox",(cocos2d::PhysicsShapeBox*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeBox:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeBox:create");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsShapeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeBox* ret = cocos2d::PhysicsShapeBox::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsShapeBox>(tolua_S, "cc.PhysicsShapeBox",(cocos2d::PhysicsShapeBox*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        cocos2d::Vec2 arg2;
        double arg3;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeBox:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeBox:create");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsShapeBox:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsShapeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeBox* ret = cocos2d::PhysicsShapeBox::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsShapeBox>(tolua_S, "cc.PhysicsShapeBox",(cocos2d::PhysicsShapeBox*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsShapeBox:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeBox_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapeBox_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapeBox)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapeBox(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapeBox");
    tolua_cclass(tolua_S,"PhysicsShapeBox","cc.PhysicsShapeBox","cc.PhysicsShapePolygon",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapeBox");
        tolua_function(tolua_S,"getSize",lua_cocos2dx_physics_PhysicsShapeBox_getSize);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_PhysicsShapeBox_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapeBox).name();
    g_luaType[typeName] = "cc.PhysicsShapeBox";
    g_typeCast["PhysicsShapeBox"] = "cc.PhysicsShapeBox";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgeSegment* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgeSegment",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapeEdgeSegment*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointB'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getPointB();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapeEdgeSegment:getPointB",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointB'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointA(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgeSegment* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgeSegment",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapeEdgeSegment*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointA'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointA'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getPointA();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapeEdgeSegment:getPointA",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointA'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsShapeEdgeSegment_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShapeEdgeSegment",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeSegment:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsShapeEdgeSegment:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeSegment* ret = cocos2d::PhysicsShapeEdgeSegment::create(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsShapeEdgeSegment>(tolua_S, "cc.PhysicsShapeEdgeSegment",(cocos2d::PhysicsShapeEdgeSegment*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::PhysicsMaterial arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeSegment:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsShapeEdgeSegment:create");
        ok &= luaval_to_physics_material(tolua_S, 4, &arg2, "cc.PhysicsShapeEdgeSegment:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeSegment* ret = cocos2d::PhysicsShapeEdgeSegment::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsShapeEdgeSegment>(tolua_S, "cc.PhysicsShapeEdgeSegment",(cocos2d::PhysicsShapeEdgeSegment*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::PhysicsMaterial arg2;
        double arg3;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeSegment:create");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsShapeEdgeSegment:create");
        ok &= luaval_to_physics_material(tolua_S, 4, &arg2, "cc.PhysicsShapeEdgeSegment:create");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsShapeEdgeSegment:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeSegment* ret = cocos2d::PhysicsShapeEdgeSegment::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsShapeEdgeSegment>(tolua_S, "cc.PhysicsShapeEdgeSegment",(cocos2d::PhysicsShapeEdgeSegment*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsShapeEdgeSegment:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeSegment_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapeEdgeSegment_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapeEdgeSegment)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapeEdgeSegment(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapeEdgeSegment");
    tolua_cclass(tolua_S,"PhysicsShapeEdgeSegment","cc.PhysicsShapeEdgeSegment","cc.PhysicsShape",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapeEdgeSegment");
        tolua_function(tolua_S,"getPointB",lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointB);
        tolua_function(tolua_S,"getPointA",lua_cocos2dx_physics_PhysicsShapeEdgeSegment_getPointA);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_PhysicsShapeEdgeSegment_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapeEdgeSegment).name();
    g_luaType[typeName] = "cc.PhysicsShapeEdgeSegment";
    g_typeCast["PhysicsShapeEdgeSegment"] = "cc.PhysicsShapeEdgeSegment";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPointsCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgePolygon* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgePolygon",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapeEdgePolygon*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPointsCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPointsCount'", nullptr);
            return 0;
        }
        int ret = cobj->getPointsCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapeEdgePolygon:getPointsCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPointsCount'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapeEdgePolygon_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapeEdgePolygon)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapeEdgePolygon(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapeEdgePolygon");
    tolua_cclass(tolua_S,"PhysicsShapeEdgePolygon","cc.PhysicsShapeEdgePolygon","cc.PhysicsShape",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapeEdgePolygon");
        tolua_function(tolua_S,"getPointsCount",lua_cocos2dx_physics_PhysicsShapeEdgePolygon_getPointsCount);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapeEdgePolygon).name();
    g_luaType[typeName] = "cc.PhysicsShapeEdgePolygon";
    g_typeCast["PhysicsShapeEdgePolygon"] = "cc.PhysicsShapeEdgePolygon";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapeEdgeBox_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsShapeEdgeBox",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Size arg0;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeBox* ret = cocos2d::PhysicsShapeEdgeBox::create(arg0);
        object_to_luaval<cocos2d::PhysicsShapeEdgeBox>(tolua_S, "cc.PhysicsShapeEdgeBox",(cocos2d::PhysicsShapeEdgeBox*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeBox:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeEdgeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeBox* ret = cocos2d::PhysicsShapeEdgeBox::create(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsShapeEdgeBox>(tolua_S, "cc.PhysicsShapeEdgeBox",(cocos2d::PhysicsShapeEdgeBox*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        double arg2;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeBox:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeEdgeBox:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsShapeEdgeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeBox* ret = cocos2d::PhysicsShapeEdgeBox::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsShapeEdgeBox>(tolua_S, "cc.PhysicsShapeEdgeBox",(cocos2d::PhysicsShapeEdgeBox*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        double arg2;
        cocos2d::Vec2 arg3;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsShapeEdgeBox:create");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsShapeEdgeBox:create");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsShapeEdgeBox:create");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsShapeEdgeBox:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_create'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShapeEdgeBox* ret = cocos2d::PhysicsShapeEdgeBox::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsShapeEdgeBox>(tolua_S, "cc.PhysicsShapeEdgeBox",(cocos2d::PhysicsShapeEdgeBox*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsShapeEdgeBox:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeBox_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapeEdgeBox_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapeEdgeBox)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapeEdgeBox(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapeEdgeBox");
    tolua_cclass(tolua_S,"PhysicsShapeEdgeBox","cc.PhysicsShapeEdgeBox","cc.PhysicsShapeEdgePolygon",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapeEdgeBox");
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_PhysicsShapeEdgeBox_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapeEdgeBox).name();
    g_luaType[typeName] = "cc.PhysicsShapeEdgeBox";
    g_typeCast["PhysicsShapeEdgeBox"] = "cc.PhysicsShapeEdgeBox";
    return 1;
}

int lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPointsCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsShapeEdgeChain* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsShapeEdgeChain",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsShapeEdgeChain*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPointsCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPointsCount'", nullptr);
            return 0;
        }
        int ret = cobj->getPointsCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsShapeEdgeChain:getPointsCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPointsCount'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsShapeEdgeChain_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsShapeEdgeChain)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsShapeEdgeChain(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsShapeEdgeChain");
    tolua_cclass(tolua_S,"PhysicsShapeEdgeChain","cc.PhysicsShapeEdgeChain","cc.PhysicsShape",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsShapeEdgeChain");
        tolua_function(tolua_S,"getPointsCount",lua_cocos2dx_physics_PhysicsShapeEdgeChain_getPointsCount);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsShapeEdgeChain).name();
    g_luaType[typeName] = "cc.PhysicsShapeEdgeChain";
    g_typeCast["PhysicsShapeEdgeChain"] = "cc.PhysicsShapeEdgeChain";
    return 1;
}

int lua_cocos2dx_physics_PhysicsBody_isGravityEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_isGravityEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_isGravityEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isGravityEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:isGravityEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_isGravityEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_resetForces(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_resetForces'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_resetForces'", nullptr);
            return 0;
        }
        cobj->resetForces();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:resetForces",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_resetForces'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getVelocityLimit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityLimit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityLimit'", nullptr);
            return 0;
        }
        double ret = cobj->getVelocityLimit();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getVelocityLimit",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityLimit'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setGroup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:setGroup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setGroup'", nullptr);
            return 0;
        }
        cobj->setGroup(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setGroup",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setGroup'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getMass(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getMass'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getMass'", nullptr);
            return 0;
        }
        double ret = cobj->getMass();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getMass",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getMass'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getCollisionBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getCollisionBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getCollisionBitmask'", nullptr);
            return 0;
        }
        int ret = cobj->getCollisionBitmask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getCollisionBitmask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getCollisionBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getRotationOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getRotationOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getRotationOffset'", nullptr);
            return 0;
        }
        double ret = cobj->getRotationOffset();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getRotationOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getRotationOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getRotation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getRotation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getRotation'", nullptr);
            return 0;
        }
        double ret = cobj->getRotation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getRotation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getRotation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getMoment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getMoment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getMoment'", nullptr);
            return 0;
        }
        double ret = cobj->getMoment();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getMoment",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getMoment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_applyImpulse(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_applyImpulse'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:applyImpulse");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_applyImpulse'", nullptr);
            return 0;
        }
        cobj->applyImpulse(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:applyImpulse");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsBody:applyImpulse");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_applyImpulse'", nullptr);
            return 0;
        }
        cobj->applyImpulse(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:applyImpulse",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_applyImpulse'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setRotationOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setRotationOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setRotationOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setRotationOffset'", nullptr);
            return 0;
        }
        cobj->setRotationOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setRotationOffset",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setRotationOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_applyForce(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_applyForce'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:applyForce");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_applyForce'", nullptr);
            return 0;
        }
        cobj->applyForce(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:applyForce");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsBody:applyForce");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_applyForce'", nullptr);
            return 0;
        }
        cobj->applyForce(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:applyForce",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_applyForce'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_addShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_addShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::PhysicsShape* arg0;

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.PhysicsBody:addShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_addShape'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->addShape(arg0);
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::PhysicsShape* arg0;
        bool arg1;

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.PhysicsBody:addShape");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.PhysicsBody:addShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_addShape'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->addShape(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:addShape",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_addShape'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_applyTorque(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_applyTorque'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:applyTorque");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_applyTorque'", nullptr);
            return 0;
        }
        cobj->applyTorque(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:applyTorque",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_applyTorque'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getAngularVelocityLimit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getAngularVelocityLimit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getAngularVelocityLimit'", nullptr);
            return 0;
        }
        double ret = cobj->getAngularVelocityLimit();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getAngularVelocityLimit",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getAngularVelocityLimit'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setAngularVelocityLimit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setAngularVelocityLimit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setAngularVelocityLimit");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setAngularVelocityLimit'", nullptr);
            return 0;
        }
        cobj->setAngularVelocityLimit(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setAngularVelocityLimit",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setAngularVelocityLimit'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getVelocity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getLinearDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getLinearDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getLinearDamping'", nullptr);
            return 0;
        }
        double ret = cobj->getLinearDamping();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getLinearDamping",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getLinearDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_removeAllShapes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_removeAllShapes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_removeAllShapes'", nullptr);
            return 0;
        }
        cobj->removeAllShapes();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsBody:removeAllShapes");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_removeAllShapes'", nullptr);
            return 0;
        }
        cobj->removeAllShapes(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:removeAllShapes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_removeAllShapes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setAngularDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setAngularDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setAngularDamping");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setAngularDamping'", nullptr);
            return 0;
        }
        cobj->setAngularDamping(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setAngularDamping",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setAngularDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setVelocityLimit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setVelocityLimit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setVelocityLimit");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setVelocityLimit'", nullptr);
            return 0;
        }
        cobj->setVelocityLimit(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setVelocityLimit",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setVelocityLimit'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setResting(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setResting'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsBody:setResting");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setResting'", nullptr);
            return 0;
        }
        cobj->setResting(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setResting",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setResting'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getPositionOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getPositionOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getPositionOffset'", nullptr);
            return 0;
        }
        const cocos2d::Vec2& ret = cobj->getPositionOffset();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getPositionOffset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getPositionOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setCategoryBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setCategoryBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:setCategoryBitmask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setCategoryBitmask'", nullptr);
            return 0;
        }
        cobj->setCategoryBitmask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setCategoryBitmask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setCategoryBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getWorld'", nullptr);
            return 0;
        }
        cocos2d::PhysicsWorld* ret = cobj->getWorld();
        object_to_luaval<cocos2d::PhysicsWorld>(tolua_S, "cc.PhysicsWorld",(cocos2d::PhysicsWorld*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getWorld",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getWorld'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getAngularVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getAngularVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getAngularVelocity'", nullptr);
            return 0;
        }
        double ret = cobj->getAngularVelocity();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getAngularVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getAngularVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getPosition(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getPosition'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getPosition'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getPosition();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getPosition",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getPosition'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setGravityEnable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setGravityEnable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsBody:setGravityEnable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setGravityEnable'", nullptr);
            return 0;
        }
        cobj->setGravityEnable(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setGravityEnable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setGravityEnable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getGroup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getGroup'", nullptr);
            return 0;
        }
        int ret = cobj->getGroup();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getGroup",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getGroup'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setMoment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setMoment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setMoment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setMoment'", nullptr);
            return 0;
        }
        cobj->setMoment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setMoment",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setMoment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getTag'", nullptr);
            return 0;
        }
        int ret = cobj->getTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_local2World(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_local2World'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:local2World");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_local2World'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->local2World(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:local2World",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_local2World'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getCategoryBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getCategoryBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getCategoryBitmask'", nullptr);
            return 0;
        }
        int ret = cobj->getCategoryBitmask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getCategoryBitmask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getCategoryBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setDynamic(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setDynamic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsBody:setDynamic");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setDynamic'", nullptr);
            return 0;
        }
        cobj->setDynamic(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setDynamic",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setDynamic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getFirstShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getFirstShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getFirstShape'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->getFirstShape();
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getFirstShape",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getFirstShape'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getShapes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getShapes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getShapes'", nullptr);
            return 0;
        }
        const cocos2d::Vector<cocos2d::PhysicsShape *>& ret = cobj->getShapes();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getShapes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getShapes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getContactTestBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getContactTestBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getContactTestBitmask'", nullptr);
            return 0;
        }
        int ret = cobj->getContactTestBitmask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getContactTestBitmask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getContactTestBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setAngularVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setAngularVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setAngularVelocity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setAngularVelocity'", nullptr);
            return 0;
        }
        cobj->setAngularVelocity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setAngularVelocity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setAngularVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_world2Local(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_world2Local'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:world2Local");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_world2Local'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->world2Local(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:world2Local",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_world2Local'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_removeShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_removeShape'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:removeShape");

            if (!ok) { break; }
            cobj->removeShape(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:removeShape");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.PhysicsBody:removeShape");

            if (!ok) { break; }
            cobj->removeShape(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::PhysicsShape* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.PhysicsBody:removeShape");

            if (!ok) { break; }
            cobj->removeShape(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            cocos2d::PhysicsShape* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.PhysicsBody:removeShape");

            if (!ok) { break; }
            bool arg1;
            ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.PhysicsBody:removeShape");

            if (!ok) { break; }
            cobj->removeShape(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.PhysicsBody:removeShape",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_removeShape'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setMass(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setMass'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setMass");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setMass'", nullptr);
            return 0;
        }
        cobj->setMass(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setMass",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setMass'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_addMoment(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_addMoment'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:addMoment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_addMoment'", nullptr);
            return 0;
        }
        cobj->addMoment(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:addMoment",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_addMoment'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:setVelocity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setVelocity'", nullptr);
            return 0;
        }
        cobj->setVelocity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setVelocity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setLinearDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setLinearDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:setLinearDamping");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setLinearDamping'", nullptr);
            return 0;
        }
        cobj->setLinearDamping(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setLinearDamping",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setLinearDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setCollisionBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setCollisionBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:setCollisionBitmask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setCollisionBitmask'", nullptr);
            return 0;
        }
        cobj->setCollisionBitmask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setCollisionBitmask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setCollisionBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setPositionOffset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setPositionOffset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:setPositionOffset");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setPositionOffset'", nullptr);
            return 0;
        }
        cobj->setPositionOffset(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setPositionOffset",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setPositionOffset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setRotationEnable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setRotationEnable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsBody:setRotationEnable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setRotationEnable'", nullptr);
            return 0;
        }
        cobj->setRotationEnable(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setRotationEnable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setRotationEnable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_isRotationEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_isRotationEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_isRotationEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isRotationEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:isRotationEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_isRotationEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getCPBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getCPBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getCPBody'", nullptr);
            return 0;
        }
        cpBody* ret = cobj->getCPBody();
        #pragma warning NO CONVERSION FROM NATIVE FOR cpBody*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getCPBody",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getCPBody'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getAngularDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getAngularDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getAngularDamping'", nullptr);
            return 0;
        }
        double ret = cobj->getAngularDamping();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getAngularDamping",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getAngularDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getVelocityAtLocalPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityAtLocalPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:getVelocityAtLocalPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityAtLocalPoint'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getVelocityAtLocalPoint(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getVelocityAtLocalPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityAtLocalPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_isResting(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_isResting'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_isResting'", nullptr);
            return 0;
        }
        bool ret = cobj->isResting();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:isResting",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_isResting'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_addMass(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_addMass'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:addMass");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_addMass'", nullptr);
            return 0;
        }
        cobj->addMass(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:addMass",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_addMass'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:getShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getShape'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->getShape(arg0);
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getShape",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getShape'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:setTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setTag'", nullptr);
            return 0;
        }
        cobj->setTag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getVelocityAtWorldPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityAtWorldPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:getVelocityAtWorldPoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityAtWorldPoint'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getVelocityAtWorldPoint(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getVelocityAtWorldPoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getVelocityAtWorldPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_setContactTestBitmask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_setContactTestBitmask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsBody:setContactTestBitmask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_setContactTestBitmask'", nullptr);
            return 0;
        }
        cobj->setContactTestBitmask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:setContactTestBitmask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_setContactTestBitmask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_removeFromWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_removeFromWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_removeFromWorld'", nullptr);
            return 0;
        }
        cobj->removeFromWorld();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:removeFromWorld",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_removeFromWorld'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_isDynamic(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_isDynamic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_isDynamic'", nullptr);
            return 0;
        }
        bool ret = cobj->isDynamic();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:isDynamic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_isDynamic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_getNode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsBody* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsBody*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsBody_getNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_getNode'", nullptr);
            return 0;
        }
        cocos2d::Node* ret = cobj->getNode();
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsBody:getNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_getNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_createBox(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Size arg0;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createBox(arg0);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createBox");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createBox(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createBox");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createBox");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsBody:createBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createBox(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsBody:createBox",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createBox'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_createEdgeSegment(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeSegment");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsBody:createEdgeSegment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeSegment'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeSegment(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::PhysicsMaterial arg2;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeSegment");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsBody:createEdgeSegment");
        ok &= luaval_to_physics_material(tolua_S, 4, &arg2, "cc.PhysicsBody:createEdgeSegment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeSegment'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeSegment(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::PhysicsMaterial arg2;
        double arg3;
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeSegment");
        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "cc.PhysicsBody:createEdgeSegment");
        ok &= luaval_to_physics_material(tolua_S, 4, &arg2, "cc.PhysicsBody:createEdgeSegment");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsBody:createEdgeSegment");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeSegment'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeSegment(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsBody:createEdgeSegment",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeSegment'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:create");
            if (!ok) { break; }
            cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::create(arg0);
            object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 0)
        {
            cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::create();
            object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:create");
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.PhysicsBody:create");
            if (!ok) { break; }
            cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::create(arg0, arg1);
            object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.PhysicsBody:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_createEdgeBox(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::Size arg0;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeBox(arg0);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 2)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeBox");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createEdgeBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeBox(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 3)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        double arg2;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeBox");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createEdgeBox");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsBody:createEdgeBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeBox(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 4)
    {
        cocos2d::Size arg0;
        cocos2d::PhysicsMaterial arg1;
        double arg2;
        cocos2d::Vec2 arg3;
        ok &= luaval_to_size(tolua_S, 2, &arg0, "cc.PhysicsBody:createEdgeBox");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createEdgeBox");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsBody:createEdgeBox");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsBody:createEdgeBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeBox'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createEdgeBox(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsBody:createEdgeBox",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createEdgeBox'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_physics_PhysicsBody_createCircle(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsBody",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:createCircle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createCircle'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createCircle(arg0);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 2)
    {
        double arg0;
        cocos2d::PhysicsMaterial arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:createCircle");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createCircle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createCircle'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createCircle(arg0, arg1);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    if (argc == 3)
    {
        double arg0;
        cocos2d::PhysicsMaterial arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsBody:createCircle");
        ok &= luaval_to_physics_material(tolua_S, 3, &arg1, "cc.PhysicsBody:createCircle");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsBody:createCircle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsBody_createCircle'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cocos2d::PhysicsBody::createCircle(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsBody:createCircle",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsBody_createCircle'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsBody_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsBody)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsBody(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsBody");
    tolua_cclass(tolua_S,"PhysicsBody","cc.PhysicsBody","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsBody");
        tolua_function(tolua_S,"isGravityEnabled",lua_cocos2dx_physics_PhysicsBody_isGravityEnabled);
        tolua_function(tolua_S,"resetForces",lua_cocos2dx_physics_PhysicsBody_resetForces);
        tolua_function(tolua_S,"getVelocityLimit",lua_cocos2dx_physics_PhysicsBody_getVelocityLimit);
        tolua_function(tolua_S,"setGroup",lua_cocos2dx_physics_PhysicsBody_setGroup);
        tolua_function(tolua_S,"getMass",lua_cocos2dx_physics_PhysicsBody_getMass);
        tolua_function(tolua_S,"getCollisionBitmask",lua_cocos2dx_physics_PhysicsBody_getCollisionBitmask);
        tolua_function(tolua_S,"getRotationOffset",lua_cocos2dx_physics_PhysicsBody_getRotationOffset);
        tolua_function(tolua_S,"getRotation",lua_cocos2dx_physics_PhysicsBody_getRotation);
        tolua_function(tolua_S,"getMoment",lua_cocos2dx_physics_PhysicsBody_getMoment);
        tolua_function(tolua_S,"applyImpulse",lua_cocos2dx_physics_PhysicsBody_applyImpulse);
        tolua_function(tolua_S,"setRotationOffset",lua_cocos2dx_physics_PhysicsBody_setRotationOffset);
        tolua_function(tolua_S,"applyForce",lua_cocos2dx_physics_PhysicsBody_applyForce);
        tolua_function(tolua_S,"addShape",lua_cocos2dx_physics_PhysicsBody_addShape);
        tolua_function(tolua_S,"applyTorque",lua_cocos2dx_physics_PhysicsBody_applyTorque);
        tolua_function(tolua_S,"getAngularVelocityLimit",lua_cocos2dx_physics_PhysicsBody_getAngularVelocityLimit);
        tolua_function(tolua_S,"setAngularVelocityLimit",lua_cocos2dx_physics_PhysicsBody_setAngularVelocityLimit);
        tolua_function(tolua_S,"getVelocity",lua_cocos2dx_physics_PhysicsBody_getVelocity);
        tolua_function(tolua_S,"getLinearDamping",lua_cocos2dx_physics_PhysicsBody_getLinearDamping);
        tolua_function(tolua_S,"removeAllShapes",lua_cocos2dx_physics_PhysicsBody_removeAllShapes);
        tolua_function(tolua_S,"setAngularDamping",lua_cocos2dx_physics_PhysicsBody_setAngularDamping);
        tolua_function(tolua_S,"setVelocityLimit",lua_cocos2dx_physics_PhysicsBody_setVelocityLimit);
        tolua_function(tolua_S,"setResting",lua_cocos2dx_physics_PhysicsBody_setResting);
        tolua_function(tolua_S,"getPositionOffset",lua_cocos2dx_physics_PhysicsBody_getPositionOffset);
        tolua_function(tolua_S,"setCategoryBitmask",lua_cocos2dx_physics_PhysicsBody_setCategoryBitmask);
        tolua_function(tolua_S,"getWorld",lua_cocos2dx_physics_PhysicsBody_getWorld);
        tolua_function(tolua_S,"getAngularVelocity",lua_cocos2dx_physics_PhysicsBody_getAngularVelocity);
        tolua_function(tolua_S,"getPosition",lua_cocos2dx_physics_PhysicsBody_getPosition);
        tolua_function(tolua_S,"setGravityEnable",lua_cocos2dx_physics_PhysicsBody_setGravityEnable);
        tolua_function(tolua_S,"getGroup",lua_cocos2dx_physics_PhysicsBody_getGroup);
        tolua_function(tolua_S,"setMoment",lua_cocos2dx_physics_PhysicsBody_setMoment);
        tolua_function(tolua_S,"getTag",lua_cocos2dx_physics_PhysicsBody_getTag);
        tolua_function(tolua_S,"local2World",lua_cocos2dx_physics_PhysicsBody_local2World);
        tolua_function(tolua_S,"getCategoryBitmask",lua_cocos2dx_physics_PhysicsBody_getCategoryBitmask);
        tolua_function(tolua_S,"setDynamic",lua_cocos2dx_physics_PhysicsBody_setDynamic);
        tolua_function(tolua_S,"getFirstShape",lua_cocos2dx_physics_PhysicsBody_getFirstShape);
        tolua_function(tolua_S,"getShapes",lua_cocos2dx_physics_PhysicsBody_getShapes);
        tolua_function(tolua_S,"getContactTestBitmask",lua_cocos2dx_physics_PhysicsBody_getContactTestBitmask);
        tolua_function(tolua_S,"setAngularVelocity",lua_cocos2dx_physics_PhysicsBody_setAngularVelocity);
        tolua_function(tolua_S,"world2Local",lua_cocos2dx_physics_PhysicsBody_world2Local);
        tolua_function(tolua_S,"removeShape",lua_cocos2dx_physics_PhysicsBody_removeShape);
        tolua_function(tolua_S,"setMass",lua_cocos2dx_physics_PhysicsBody_setMass);
        tolua_function(tolua_S,"addMoment",lua_cocos2dx_physics_PhysicsBody_addMoment);
        tolua_function(tolua_S,"setVelocity",lua_cocos2dx_physics_PhysicsBody_setVelocity);
        tolua_function(tolua_S,"setLinearDamping",lua_cocos2dx_physics_PhysicsBody_setLinearDamping);
        tolua_function(tolua_S,"setCollisionBitmask",lua_cocos2dx_physics_PhysicsBody_setCollisionBitmask);
        tolua_function(tolua_S,"setPositionOffset",lua_cocos2dx_physics_PhysicsBody_setPositionOffset);
        tolua_function(tolua_S,"setRotationEnable",lua_cocos2dx_physics_PhysicsBody_setRotationEnable);
        tolua_function(tolua_S,"isRotationEnabled",lua_cocos2dx_physics_PhysicsBody_isRotationEnabled);
        tolua_function(tolua_S,"getCPBody",lua_cocos2dx_physics_PhysicsBody_getCPBody);
        tolua_function(tolua_S,"getAngularDamping",lua_cocos2dx_physics_PhysicsBody_getAngularDamping);
        tolua_function(tolua_S,"getVelocityAtLocalPoint",lua_cocos2dx_physics_PhysicsBody_getVelocityAtLocalPoint);
        tolua_function(tolua_S,"isResting",lua_cocos2dx_physics_PhysicsBody_isResting);
        tolua_function(tolua_S,"addMass",lua_cocos2dx_physics_PhysicsBody_addMass);
        tolua_function(tolua_S,"getShape",lua_cocos2dx_physics_PhysicsBody_getShape);
        tolua_function(tolua_S,"setTag",lua_cocos2dx_physics_PhysicsBody_setTag);
        tolua_function(tolua_S,"getVelocityAtWorldPoint",lua_cocos2dx_physics_PhysicsBody_getVelocityAtWorldPoint);
        tolua_function(tolua_S,"setContactTestBitmask",lua_cocos2dx_physics_PhysicsBody_setContactTestBitmask);
        tolua_function(tolua_S,"removeFromWorld",lua_cocos2dx_physics_PhysicsBody_removeFromWorld);
        tolua_function(tolua_S,"isDynamic",lua_cocos2dx_physics_PhysicsBody_isDynamic);
        tolua_function(tolua_S,"getNode",lua_cocos2dx_physics_PhysicsBody_getNode);
        tolua_function(tolua_S,"createBox", lua_cocos2dx_physics_PhysicsBody_createBox);
        tolua_function(tolua_S,"createEdgeSegment", lua_cocos2dx_physics_PhysicsBody_createEdgeSegment);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_PhysicsBody_create);
        tolua_function(tolua_S,"createEdgeBox", lua_cocos2dx_physics_PhysicsBody_createEdgeBox);
        tolua_function(tolua_S,"createCircle", lua_cocos2dx_physics_PhysicsBody_createCircle);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsBody).name();
    g_luaType[typeName] = "cc.PhysicsBody";
    g_typeCast["PhysicsBody"] = "cc.PhysicsBody";
    return 1;
}

int lua_cocos2dx_physics_PhysicsContact_getContactData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContact* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContact",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContact*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContact_getContactData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContact_getContactData'", nullptr);
            return 0;
        }
        const cocos2d::PhysicsContactData* ret = cobj->getContactData();
        physics_contactdata_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContact:getContactData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContact_getContactData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContact_getEventCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContact* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContact",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContact*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContact_getEventCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContact_getEventCode'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getEventCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContact:getEventCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContact_getEventCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContact_getPreContactData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContact* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContact",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContact*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContact_getPreContactData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContact_getPreContactData'", nullptr);
            return 0;
        }
        const cocos2d::PhysicsContactData* ret = cobj->getPreContactData();
        physics_contactdata_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContact:getPreContactData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContact_getPreContactData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContact_getShapeA(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContact* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContact",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContact*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContact_getShapeA'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContact_getShapeA'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->getShapeA();
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContact:getShapeA",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContact_getShapeA'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContact_getShapeB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContact* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContact",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContact*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContact_getShapeB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContact_getShapeB'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->getShapeB();
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContact:getShapeB",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContact_getShapeB'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsContact_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsContact)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsContact(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsContact");
    tolua_cclass(tolua_S,"PhysicsContact","cc.PhysicsContact","cc.EventCustom",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsContact");
        tolua_function(tolua_S,"getContactData",lua_cocos2dx_physics_PhysicsContact_getContactData);
        tolua_function(tolua_S,"getEventCode",lua_cocos2dx_physics_PhysicsContact_getEventCode);
        tolua_function(tolua_S,"getPreContactData",lua_cocos2dx_physics_PhysicsContact_getPreContactData);
        tolua_function(tolua_S,"getShapeA",lua_cocos2dx_physics_PhysicsContact_getShapeA);
        tolua_function(tolua_S,"getShapeB",lua_cocos2dx_physics_PhysicsContact_getShapeB);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsContact).name();
    g_luaType[typeName] = "cc.PhysicsContact";
    g_typeCast["PhysicsContact"] = "cc.PhysicsContact";
    return 1;
}

int lua_cocos2dx_physics_PhysicsContactPreSolve_getFriction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getFriction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getFriction'", nullptr);
            return 0;
        }
        double ret = cobj->getFriction();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:getFriction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getFriction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPreSolve_getRestitution(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getRestitution'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getRestitution'", nullptr);
            return 0;
        }
        double ret = cobj->getRestitution();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:getRestitution",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getRestitution'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPreSolve_setFriction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setFriction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsContactPreSolve:setFriction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setFriction'", nullptr);
            return 0;
        }
        cobj->setFriction(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:setFriction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setFriction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPreSolve_ignore(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_ignore'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_ignore'", nullptr);
            return 0;
        }
        cobj->ignore();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:ignore",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_ignore'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPreSolve_getSurfaceVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getSurfaceVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getSurfaceVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getSurfaceVelocity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:getSurfaceVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_getSurfaceVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPreSolve_setSurfaceVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setSurfaceVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsContactPreSolve:setSurfaceVelocity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setSurfaceVelocity'", nullptr);
            return 0;
        }
        cobj->setSurfaceVelocity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:setSurfaceVelocity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setSurfaceVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPreSolve_setRestitution(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPreSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPreSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPreSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setRestitution'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsContactPreSolve:setRestitution");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setRestitution'", nullptr);
            return 0;
        }
        cobj->setRestitution(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPreSolve:setRestitution",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPreSolve_setRestitution'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsContactPreSolve_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsContactPreSolve)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsContactPreSolve(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsContactPreSolve");
    tolua_cclass(tolua_S,"PhysicsContactPreSolve","cc.PhysicsContactPreSolve","",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsContactPreSolve");
        tolua_function(tolua_S,"getFriction",lua_cocos2dx_physics_PhysicsContactPreSolve_getFriction);
        tolua_function(tolua_S,"getRestitution",lua_cocos2dx_physics_PhysicsContactPreSolve_getRestitution);
        tolua_function(tolua_S,"setFriction",lua_cocos2dx_physics_PhysicsContactPreSolve_setFriction);
        tolua_function(tolua_S,"ignore",lua_cocos2dx_physics_PhysicsContactPreSolve_ignore);
        tolua_function(tolua_S,"getSurfaceVelocity",lua_cocos2dx_physics_PhysicsContactPreSolve_getSurfaceVelocity);
        tolua_function(tolua_S,"setSurfaceVelocity",lua_cocos2dx_physics_PhysicsContactPreSolve_setSurfaceVelocity);
        tolua_function(tolua_S,"setRestitution",lua_cocos2dx_physics_PhysicsContactPreSolve_setRestitution);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsContactPreSolve).name();
    g_luaType[typeName] = "cc.PhysicsContactPreSolve";
    g_typeCast["PhysicsContactPreSolve"] = "cc.PhysicsContactPreSolve";
    return 1;
}

int lua_cocos2dx_physics_PhysicsContactPostSolve_getFriction(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPostSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPostSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPostSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getFriction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getFriction'", nullptr);
            return 0;
        }
        double ret = cobj->getFriction();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPostSolve:getFriction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getFriction'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPostSolve_getSurfaceVelocity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPostSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPostSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPostSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getSurfaceVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getSurfaceVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getSurfaceVelocity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPostSolve:getSurfaceVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getSurfaceVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsContactPostSolve_getRestitution(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsContactPostSolve* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsContactPostSolve",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsContactPostSolve*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getRestitution'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getRestitution'", nullptr);
            return 0;
        }
        double ret = cobj->getRestitution();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsContactPostSolve:getRestitution",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsContactPostSolve_getRestitution'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsContactPostSolve_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsContactPostSolve)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsContactPostSolve(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsContactPostSolve");
    tolua_cclass(tolua_S,"PhysicsContactPostSolve","cc.PhysicsContactPostSolve","",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsContactPostSolve");
        tolua_function(tolua_S,"getFriction",lua_cocos2dx_physics_PhysicsContactPostSolve_getFriction);
        tolua_function(tolua_S,"getSurfaceVelocity",lua_cocos2dx_physics_PhysicsContactPostSolve_getSurfaceVelocity);
        tolua_function(tolua_S,"getRestitution",lua_cocos2dx_physics_PhysicsContactPostSolve_getRestitution);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsContactPostSolve).name();
    g_luaType[typeName] = "cc.PhysicsContactPostSolve";
    g_typeCast["PhysicsContactPostSolve"] = "cc.PhysicsContactPostSolve";
    return 1;
}

int lua_cocos2dx_physics_EventListenerPhysicsContact_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EventListenerPhysicsContact",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContact_create'", nullptr);
            return 0;
        }
        cocos2d::EventListenerPhysicsContact* ret = cocos2d::EventListenerPhysicsContact::create();
        object_to_luaval<cocos2d::EventListenerPhysicsContact>(tolua_S, "cc.EventListenerPhysicsContact",(cocos2d::EventListenerPhysicsContact*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EventListenerPhysicsContact:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContact_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_EventListenerPhysicsContact_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventListenerPhysicsContact)");
    return 0;
}

int lua_register_cocos2dx_physics_EventListenerPhysicsContact(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerPhysicsContact");
    tolua_cclass(tolua_S,"EventListenerPhysicsContact","cc.EventListenerPhysicsContact","cc.EventListenerCustom",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerPhysicsContact");
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_EventListenerPhysicsContact_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EventListenerPhysicsContact).name();
    g_luaType[typeName] = "cc.EventListenerPhysicsContact";
    g_typeCast["EventListenerPhysicsContact"] = "cc.EventListenerPhysicsContact";
    return 1;
}

int lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_hitTest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerPhysicsContactWithBodies* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventListenerPhysicsContactWithBodies",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventListenerPhysicsContactWithBodies*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_hitTest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::PhysicsShape* arg0;
        cocos2d::PhysicsShape* arg1;

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.EventListenerPhysicsContactWithBodies:hitTest");

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 3, "cc.PhysicsShape",&arg1, "cc.EventListenerPhysicsContactWithBodies:hitTest");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_hitTest'", nullptr);
            return 0;
        }
        bool ret = cobj->hitTest(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerPhysicsContactWithBodies:hitTest",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_hitTest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EventListenerPhysicsContactWithBodies",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.EventListenerPhysicsContactWithBodies:create");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.EventListenerPhysicsContactWithBodies:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_create'", nullptr);
            return 0;
        }
        cocos2d::EventListenerPhysicsContactWithBodies* ret = cocos2d::EventListenerPhysicsContactWithBodies::create(arg0, arg1);
        object_to_luaval<cocos2d::EventListenerPhysicsContactWithBodies>(tolua_S, "cc.EventListenerPhysicsContactWithBodies",(cocos2d::EventListenerPhysicsContactWithBodies*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EventListenerPhysicsContactWithBodies:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventListenerPhysicsContactWithBodies)");
    return 0;
}

int lua_register_cocos2dx_physics_EventListenerPhysicsContactWithBodies(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerPhysicsContactWithBodies");
    tolua_cclass(tolua_S,"EventListenerPhysicsContactWithBodies","cc.EventListenerPhysicsContactWithBodies","cc.EventListenerPhysicsContact",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerPhysicsContactWithBodies");
        tolua_function(tolua_S,"hitTest",lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_hitTest);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_EventListenerPhysicsContactWithBodies_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EventListenerPhysicsContactWithBodies).name();
    g_luaType[typeName] = "cc.EventListenerPhysicsContactWithBodies";
    g_typeCast["EventListenerPhysicsContactWithBodies"] = "cc.EventListenerPhysicsContactWithBodies";
    return 1;
}

int lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_hitTest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerPhysicsContactWithShapes* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventListenerPhysicsContactWithShapes",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventListenerPhysicsContactWithShapes*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_hitTest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::PhysicsShape* arg0;
        cocos2d::PhysicsShape* arg1;

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.EventListenerPhysicsContactWithShapes:hitTest");

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 3, "cc.PhysicsShape",&arg1, "cc.EventListenerPhysicsContactWithShapes:hitTest");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_hitTest'", nullptr);
            return 0;
        }
        bool ret = cobj->hitTest(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerPhysicsContactWithShapes:hitTest",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_hitTest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EventListenerPhysicsContactWithShapes",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        cocos2d::PhysicsShape* arg0;
        cocos2d::PhysicsShape* arg1;
        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.EventListenerPhysicsContactWithShapes:create");
        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 3, "cc.PhysicsShape",&arg1, "cc.EventListenerPhysicsContactWithShapes:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_create'", nullptr);
            return 0;
        }
        cocos2d::EventListenerPhysicsContactWithShapes* ret = cocos2d::EventListenerPhysicsContactWithShapes::create(arg0, arg1);
        object_to_luaval<cocos2d::EventListenerPhysicsContactWithShapes>(tolua_S, "cc.EventListenerPhysicsContactWithShapes",(cocos2d::EventListenerPhysicsContactWithShapes*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EventListenerPhysicsContactWithShapes:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventListenerPhysicsContactWithShapes)");
    return 0;
}

int lua_register_cocos2dx_physics_EventListenerPhysicsContactWithShapes(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerPhysicsContactWithShapes");
    tolua_cclass(tolua_S,"EventListenerPhysicsContactWithShapes","cc.EventListenerPhysicsContactWithShapes","cc.EventListenerPhysicsContact",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerPhysicsContactWithShapes");
        tolua_function(tolua_S,"hitTest",lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_hitTest);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_EventListenerPhysicsContactWithShapes_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EventListenerPhysicsContactWithShapes).name();
    g_luaType[typeName] = "cc.EventListenerPhysicsContactWithShapes";
    g_typeCast["EventListenerPhysicsContactWithShapes"] = "cc.EventListenerPhysicsContactWithShapes";
    return 1;
}

int lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_hitTest(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::EventListenerPhysicsContactWithGroup* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.EventListenerPhysicsContactWithGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::EventListenerPhysicsContactWithGroup*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_hitTest'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::PhysicsShape* arg0;
        cocos2d::PhysicsShape* arg1;

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 2, "cc.PhysicsShape",&arg0, "cc.EventListenerPhysicsContactWithGroup:hitTest");

        ok &= luaval_to_object<cocos2d::PhysicsShape>(tolua_S, 3, "cc.PhysicsShape",&arg1, "cc.EventListenerPhysicsContactWithGroup:hitTest");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_hitTest'", nullptr);
            return 0;
        }
        bool ret = cobj->hitTest(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.EventListenerPhysicsContactWithGroup:hitTest",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_hitTest'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.EventListenerPhysicsContactWithGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.EventListenerPhysicsContactWithGroup:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_create'", nullptr);
            return 0;
        }
        cocos2d::EventListenerPhysicsContactWithGroup* ret = cocos2d::EventListenerPhysicsContactWithGroup::create(arg0);
        object_to_luaval<cocos2d::EventListenerPhysicsContactWithGroup>(tolua_S, "cc.EventListenerPhysicsContactWithGroup",(cocos2d::EventListenerPhysicsContactWithGroup*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.EventListenerPhysicsContactWithGroup:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EventListenerPhysicsContactWithGroup)");
    return 0;
}

int lua_register_cocos2dx_physics_EventListenerPhysicsContactWithGroup(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.EventListenerPhysicsContactWithGroup");
    tolua_cclass(tolua_S,"EventListenerPhysicsContactWithGroup","cc.EventListenerPhysicsContactWithGroup","cc.EventListenerPhysicsContact",nullptr);

    tolua_beginmodule(tolua_S,"EventListenerPhysicsContactWithGroup");
        tolua_function(tolua_S,"hitTest",lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_hitTest);
        tolua_function(tolua_S,"create", lua_cocos2dx_physics_EventListenerPhysicsContactWithGroup_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::EventListenerPhysicsContactWithGroup).name();
    g_luaType[typeName] = "cc.EventListenerPhysicsContactWithGroup";
    g_typeCast["EventListenerPhysicsContactWithGroup"] = "cc.EventListenerPhysicsContactWithGroup";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJoint_getBodyA(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_getBodyA'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_getBodyA'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cobj->getBodyA();
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:getBodyA",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_getBodyA'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_getBodyB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_getBodyB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_getBodyB'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cobj->getBodyB();
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:getBodyB",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_getBodyB'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_getMaxForce(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_getMaxForce'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_getMaxForce'", nullptr);
            return 0;
        }
        double ret = cobj->getMaxForce();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:getMaxForce",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_getMaxForce'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_setMaxForce(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_setMaxForce'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJoint:setMaxForce");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_setMaxForce'", nullptr);
            return 0;
        }
        cobj->setMaxForce(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:setMaxForce",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_setMaxForce'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_isEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_isEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:isEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_isEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_setEnable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_setEnable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsJoint:setEnable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_setEnable'", nullptr);
            return 0;
        }
        cobj->setEnable(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:setEnable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_setEnable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_setCollisionEnable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_setCollisionEnable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsJoint:setCollisionEnable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_setCollisionEnable'", nullptr);
            return 0;
        }
        cobj->setCollisionEnable(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:setCollisionEnable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_setCollisionEnable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_getWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_getWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_getWorld'", nullptr);
            return 0;
        }
        cocos2d::PhysicsWorld* ret = cobj->getWorld();
        object_to_luaval<cocos2d::PhysicsWorld>(tolua_S, "cc.PhysicsWorld",(cocos2d::PhysicsWorld*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:getWorld",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_getWorld'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_setTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_setTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsJoint:setTag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_setTag'", nullptr);
            return 0;
        }
        cobj->setTag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:setTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_setTag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_removeFormWorld(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_removeFormWorld'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_removeFormWorld'", nullptr);
            return 0;
        }
        cobj->removeFormWorld();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:removeFormWorld",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_removeFormWorld'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_isCollisionEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_isCollisionEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_isCollisionEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isCollisionEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:isCollisionEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_isCollisionEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJoint_getTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJoint* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJoint",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJoint*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJoint_getTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJoint_getTag'", nullptr);
            return 0;
        }
        int ret = cobj->getTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJoint:getTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJoint_getTag'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsJoint_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJoint)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJoint(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJoint");
    tolua_cclass(tolua_S,"PhysicsJoint","cc.PhysicsJoint","",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJoint");
        tolua_function(tolua_S,"getBodyA",lua_cocos2dx_physics_PhysicsJoint_getBodyA);
        tolua_function(tolua_S,"getBodyB",lua_cocos2dx_physics_PhysicsJoint_getBodyB);
        tolua_function(tolua_S,"getMaxForce",lua_cocos2dx_physics_PhysicsJoint_getMaxForce);
        tolua_function(tolua_S,"setMaxForce",lua_cocos2dx_physics_PhysicsJoint_setMaxForce);
        tolua_function(tolua_S,"isEnabled",lua_cocos2dx_physics_PhysicsJoint_isEnabled);
        tolua_function(tolua_S,"setEnable",lua_cocos2dx_physics_PhysicsJoint_setEnable);
        tolua_function(tolua_S,"setCollisionEnable",lua_cocos2dx_physics_PhysicsJoint_setCollisionEnable);
        tolua_function(tolua_S,"getWorld",lua_cocos2dx_physics_PhysicsJoint_getWorld);
        tolua_function(tolua_S,"setTag",lua_cocos2dx_physics_PhysicsJoint_setTag);
        tolua_function(tolua_S,"removeFormWorld",lua_cocos2dx_physics_PhysicsJoint_removeFormWorld);
        tolua_function(tolua_S,"isCollisionEnabled",lua_cocos2dx_physics_PhysicsJoint_isCollisionEnabled);
        tolua_function(tolua_S,"getTag",lua_cocos2dx_physics_PhysicsJoint_getTag);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJoint).name();
    g_luaType[typeName] = "cc.PhysicsJoint";
    g_typeCast["PhysicsJoint"] = "cc.PhysicsJoint";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointFixed_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointFixed* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointFixed",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointFixed*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointFixed_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointFixed_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointFixed:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointFixed_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointFixed_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointFixed",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        cocos2d::Vec2 arg2;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointFixed:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointFixed:construct");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointFixed:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointFixed_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointFixed* ret = cocos2d::PhysicsJointFixed::construct(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsJointFixed>(tolua_S, "cc.PhysicsJointFixed",(cocos2d::PhysicsJointFixed*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointFixed:construct",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointFixed_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointFixed_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointFixed)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointFixed(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointFixed");
    tolua_cclass(tolua_S,"PhysicsJointFixed","cc.PhysicsJointFixed","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointFixed");
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointFixed_createConstraints);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointFixed_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointFixed).name();
    g_luaType[typeName] = "cc.PhysicsJointFixed";
    g_typeCast["PhysicsJointFixed"] = "cc.PhysicsJointFixed";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointLimit_setAnchr2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_setAnchr2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointLimit:setAnchr2");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_setAnchr2'", nullptr);
            return 0;
        }
        cobj->setAnchr2(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:setAnchr2",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_setAnchr2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_setAnchr1(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_setAnchr1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointLimit:setAnchr1");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_setAnchr1'", nullptr);
            return 0;
        }
        cobj->setAnchr1(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:setAnchr1",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_setAnchr1'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_setMax(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_setMax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointLimit:setMax");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_setMax'", nullptr);
            return 0;
        }
        cobj->setMax(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:setMax",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_setMax'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_getAnchr2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_getAnchr2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_getAnchr2'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getAnchr2();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:getAnchr2",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_getAnchr2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_getAnchr1(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_getAnchr1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_getAnchr1'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getAnchr1();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:getAnchr1",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_getAnchr1'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_getMin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_getMin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_getMin'", nullptr);
            return 0;
        }
        double ret = cobj->getMin();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:getMin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_getMin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_getMax(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_getMax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_getMax'", nullptr);
            return 0;
        }
        double ret = cobj->getMax();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:getMax",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_getMax'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_setMin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointLimit_setMin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointLimit:setMin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointLimit_setMin'", nullptr);
            return 0;
        }
        cobj->setMin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointLimit:setMin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_setMin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointLimit_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 6)
        {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsBody* arg1;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            double arg4;
            ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            double arg5;
            ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsJointLimit* ret = cocos2d::PhysicsJointLimit::construct(arg0, arg1, arg2, arg3, arg4, arg5);
            object_to_luaval<cocos2d::PhysicsJointLimit>(tolua_S, "cc.PhysicsJointLimit",(cocos2d::PhysicsJointLimit*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsBody* arg1;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsJointLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsJointLimit* ret = cocos2d::PhysicsJointLimit::construct(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::PhysicsJointLimit>(tolua_S, "cc.PhysicsJointLimit",(cocos2d::PhysicsJointLimit*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.PhysicsJointLimit:construct",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointLimit_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointLimit_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointLimit)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointLimit(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointLimit");
    tolua_cclass(tolua_S,"PhysicsJointLimit","cc.PhysicsJointLimit","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointLimit");
        tolua_function(tolua_S,"setAnchr2",lua_cocos2dx_physics_PhysicsJointLimit_setAnchr2);
        tolua_function(tolua_S,"setAnchr1",lua_cocos2dx_physics_PhysicsJointLimit_setAnchr1);
        tolua_function(tolua_S,"setMax",lua_cocos2dx_physics_PhysicsJointLimit_setMax);
        tolua_function(tolua_S,"getAnchr2",lua_cocos2dx_physics_PhysicsJointLimit_getAnchr2);
        tolua_function(tolua_S,"getAnchr1",lua_cocos2dx_physics_PhysicsJointLimit_getAnchr1);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointLimit_createConstraints);
        tolua_function(tolua_S,"getMin",lua_cocos2dx_physics_PhysicsJointLimit_getMin);
        tolua_function(tolua_S,"getMax",lua_cocos2dx_physics_PhysicsJointLimit_getMax);
        tolua_function(tolua_S,"setMin",lua_cocos2dx_physics_PhysicsJointLimit_setMin);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointLimit_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointLimit).name();
    g_luaType[typeName] = "cc.PhysicsJointLimit";
    g_typeCast["PhysicsJointLimit"] = "cc.PhysicsJointLimit";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointPin_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointPin* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointPin",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointPin*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointPin_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointPin_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointPin:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointPin_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointPin_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointPin",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 4)
        {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::PhysicsBody* arg1;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg3;
            ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::PhysicsJointPin* ret = cocos2d::PhysicsJointPin::construct(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::PhysicsJointPin>(tolua_S, "cc.PhysicsJointPin",(cocos2d::PhysicsJointPin*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::PhysicsBody* arg1;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::Vec2 arg2;
            ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointPin:construct");
            if (!ok) { break; }
            cocos2d::PhysicsJointPin* ret = cocos2d::PhysicsJointPin::construct(arg0, arg1, arg2);
            object_to_luaval<cocos2d::PhysicsJointPin>(tolua_S, "cc.PhysicsJointPin",(cocos2d::PhysicsJointPin*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.PhysicsJointPin:construct",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointPin_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointPin_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointPin)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointPin(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointPin");
    tolua_cclass(tolua_S,"PhysicsJointPin","cc.PhysicsJointPin","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointPin");
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointPin_createConstraints);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointPin_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointPin).name();
    g_luaType[typeName] = "cc.PhysicsJointPin";
    g_typeCast["PhysicsJointPin"] = "cc.PhysicsJointPin";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointDistance_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointDistance* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointDistance",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointDistance*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointDistance_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointDistance_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointDistance:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointDistance_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointDistance_setDistance(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointDistance* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointDistance",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointDistance*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointDistance_setDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointDistance:setDistance");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointDistance_setDistance'", nullptr);
            return 0;
        }
        cobj->setDistance(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointDistance:setDistance",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointDistance_setDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointDistance_getDistance(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointDistance* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointDistance",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointDistance*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointDistance_getDistance'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointDistance_getDistance'", nullptr);
            return 0;
        }
        double ret = cobj->getDistance();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointDistance:getDistance",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointDistance_getDistance'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointDistance_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointDistance",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointDistance:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointDistance:construct");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointDistance:construct");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsJointDistance:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointDistance_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointDistance* ret = cocos2d::PhysicsJointDistance::construct(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsJointDistance>(tolua_S, "cc.PhysicsJointDistance",(cocos2d::PhysicsJointDistance*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointDistance:construct",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointDistance_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointDistance_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointDistance)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointDistance(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointDistance");
    tolua_cclass(tolua_S,"PhysicsJointDistance","cc.PhysicsJointDistance","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointDistance");
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointDistance_createConstraints);
        tolua_function(tolua_S,"setDistance",lua_cocos2dx_physics_PhysicsJointDistance_setDistance);
        tolua_function(tolua_S,"getDistance",lua_cocos2dx_physics_PhysicsJointDistance_getDistance);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointDistance_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointDistance).name();
    g_luaType[typeName] = "cc.PhysicsJointDistance";
    g_typeCast["PhysicsJointDistance"] = "cc.PhysicsJointDistance";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointSpring_setAnchr2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_setAnchr2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointSpring:setAnchr2");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_setAnchr2'", nullptr);
            return 0;
        }
        cobj->setAnchr2(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:setAnchr2",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_setAnchr2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_setAnchr1(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_setAnchr1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointSpring:setAnchr1");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_setAnchr1'", nullptr);
            return 0;
        }
        cobj->setAnchr1(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:setAnchr1",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_setAnchr1'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_getDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_getDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_getDamping'", nullptr);
            return 0;
        }
        double ret = cobj->getDamping();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:getDamping",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_getDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_setStiffness(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_setStiffness'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointSpring:setStiffness");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_setStiffness'", nullptr);
            return 0;
        }
        cobj->setStiffness(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:setStiffness",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_setStiffness'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_getRestLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_getRestLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_getRestLength'", nullptr);
            return 0;
        }
        double ret = cobj->getRestLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:getRestLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_getRestLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_getAnchr2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_getAnchr2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_getAnchr2'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getAnchr2();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:getAnchr2",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_getAnchr2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_getAnchr1(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_getAnchr1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_getAnchr1'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getAnchr1();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:getAnchr1",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_getAnchr1'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_getStiffness(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_getStiffness'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_getStiffness'", nullptr);
            return 0;
        }
        double ret = cobj->getStiffness();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:getStiffness",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_getStiffness'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_setRestLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_setRestLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointSpring:setRestLength");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_setRestLength'", nullptr);
            return 0;
        }
        cobj->setRestLength(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:setRestLength",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_setRestLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_setDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointSpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointSpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointSpring_setDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointSpring:setDamping");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_setDamping'", nullptr);
            return 0;
        }
        cobj->setDamping(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointSpring:setDamping",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_setDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointSpring_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointSpring",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 6)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        double arg4;
        double arg5;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointSpring:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointSpring:construct");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointSpring:construct");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsJointSpring:construct");
        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.PhysicsJointSpring:construct");
        ok &= luaval_to_number(tolua_S, 7,&arg5, "cc.PhysicsJointSpring:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointSpring_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointSpring* ret = cocos2d::PhysicsJointSpring::construct(arg0, arg1, arg2, arg3, arg4, arg5);
        object_to_luaval<cocos2d::PhysicsJointSpring>(tolua_S, "cc.PhysicsJointSpring",(cocos2d::PhysicsJointSpring*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointSpring:construct",argc, 6);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointSpring_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointSpring_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointSpring)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointSpring(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointSpring");
    tolua_cclass(tolua_S,"PhysicsJointSpring","cc.PhysicsJointSpring","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointSpring");
        tolua_function(tolua_S,"setAnchr2",lua_cocos2dx_physics_PhysicsJointSpring_setAnchr2);
        tolua_function(tolua_S,"setAnchr1",lua_cocos2dx_physics_PhysicsJointSpring_setAnchr1);
        tolua_function(tolua_S,"getDamping",lua_cocos2dx_physics_PhysicsJointSpring_getDamping);
        tolua_function(tolua_S,"setStiffness",lua_cocos2dx_physics_PhysicsJointSpring_setStiffness);
        tolua_function(tolua_S,"getRestLength",lua_cocos2dx_physics_PhysicsJointSpring_getRestLength);
        tolua_function(tolua_S,"getAnchr2",lua_cocos2dx_physics_PhysicsJointSpring_getAnchr2);
        tolua_function(tolua_S,"getAnchr1",lua_cocos2dx_physics_PhysicsJointSpring_getAnchr1);
        tolua_function(tolua_S,"getStiffness",lua_cocos2dx_physics_PhysicsJointSpring_getStiffness);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointSpring_createConstraints);
        tolua_function(tolua_S,"setRestLength",lua_cocos2dx_physics_PhysicsJointSpring_setRestLength);
        tolua_function(tolua_S,"setDamping",lua_cocos2dx_physics_PhysicsJointSpring_setDamping);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointSpring_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointSpring).name();
    g_luaType[typeName] = "cc.PhysicsJointSpring";
    g_typeCast["PhysicsJointSpring"] = "cc.PhysicsJointSpring";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointGroove_setAnchr2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_setAnchr2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointGroove:setAnchr2");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_setAnchr2'", nullptr);
            return 0;
        }
        cobj->setAnchr2(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:setAnchr2",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_setAnchr2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_setGrooveA(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_setGrooveA'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointGroove:setGrooveA");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_setGrooveA'", nullptr);
            return 0;
        }
        cobj->setGrooveA(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:setGrooveA",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_setGrooveA'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_setGrooveB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_setGrooveB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsJointGroove:setGrooveB");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_setGrooveB'", nullptr);
            return 0;
        }
        cobj->setGrooveB(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:setGrooveB",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_setGrooveB'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_getGrooveA(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_getGrooveA'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_getGrooveA'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getGrooveA();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:getGrooveA",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_getGrooveA'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_getGrooveB(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_getGrooveB'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_getGrooveB'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getGrooveB();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:getGrooveB",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_getGrooveB'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_getAnchr2(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_getAnchr2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_getAnchr2'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getAnchr2();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:getAnchr2",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_getAnchr2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGroove* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGroove*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGroove_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGroove:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGroove_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointGroove",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 5)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        cocos2d::Vec2 arg4;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointGroove:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointGroove:construct");
        ok &= luaval_to_vec2(tolua_S, 4, &arg2, "cc.PhysicsJointGroove:construct");
        ok &= luaval_to_vec2(tolua_S, 5, &arg3, "cc.PhysicsJointGroove:construct");
        ok &= luaval_to_vec2(tolua_S, 6, &arg4, "cc.PhysicsJointGroove:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGroove_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointGroove* ret = cocos2d::PhysicsJointGroove::construct(arg0, arg1, arg2, arg3, arg4);
        object_to_luaval<cocos2d::PhysicsJointGroove>(tolua_S, "cc.PhysicsJointGroove",(cocos2d::PhysicsJointGroove*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointGroove:construct",argc, 5);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGroove_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointGroove_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointGroove)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointGroove(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointGroove");
    tolua_cclass(tolua_S,"PhysicsJointGroove","cc.PhysicsJointGroove","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointGroove");
        tolua_function(tolua_S,"setAnchr2",lua_cocos2dx_physics_PhysicsJointGroove_setAnchr2);
        tolua_function(tolua_S,"setGrooveA",lua_cocos2dx_physics_PhysicsJointGroove_setGrooveA);
        tolua_function(tolua_S,"setGrooveB",lua_cocos2dx_physics_PhysicsJointGroove_setGrooveB);
        tolua_function(tolua_S,"getGrooveA",lua_cocos2dx_physics_PhysicsJointGroove_getGrooveA);
        tolua_function(tolua_S,"getGrooveB",lua_cocos2dx_physics_PhysicsJointGroove_getGrooveB);
        tolua_function(tolua_S,"getAnchr2",lua_cocos2dx_physics_PhysicsJointGroove_getAnchr2);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointGroove_createConstraints);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointGroove_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointGroove).name();
    g_luaType[typeName] = "cc.PhysicsJointGroove";
    g_typeCast["PhysicsJointGroove"] = "cc.PhysicsJointGroove";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointRotarySpring_getDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getDamping'", nullptr);
            return 0;
        }
        double ret = cobj->getDamping();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:getDamping",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_setRestAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setRestAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRotarySpring:setRestAngle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setRestAngle'", nullptr);
            return 0;
        }
        cobj->setRestAngle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:setRestAngle",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setRestAngle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_getStiffness(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getStiffness'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getStiffness'", nullptr);
            return 0;
        }
        double ret = cobj->getStiffness();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:getStiffness",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getStiffness'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_setStiffness(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setStiffness'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRotarySpring:setStiffness");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setStiffness'", nullptr);
            return 0;
        }
        cobj->setStiffness(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:setStiffness",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setStiffness'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_setDamping(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setDamping'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRotarySpring:setDamping");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setDamping'", nullptr);
            return 0;
        }
        cobj->setDamping(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:setDamping",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_setDamping'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_getRestAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotarySpring* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotarySpring*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getRestAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getRestAngle'", nullptr);
            return 0;
        }
        double ret = cobj->getRestAngle();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotarySpring:getRestAngle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_getRestAngle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotarySpring_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointRotarySpring",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointRotarySpring:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointRotarySpring:construct");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsJointRotarySpring:construct");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsJointRotarySpring:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointRotarySpring* ret = cocos2d::PhysicsJointRotarySpring::construct(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsJointRotarySpring>(tolua_S, "cc.PhysicsJointRotarySpring",(cocos2d::PhysicsJointRotarySpring*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointRotarySpring:construct",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotarySpring_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointRotarySpring_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointRotarySpring)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointRotarySpring(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointRotarySpring");
    tolua_cclass(tolua_S,"PhysicsJointRotarySpring","cc.PhysicsJointRotarySpring","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointRotarySpring");
        tolua_function(tolua_S,"getDamping",lua_cocos2dx_physics_PhysicsJointRotarySpring_getDamping);
        tolua_function(tolua_S,"setRestAngle",lua_cocos2dx_physics_PhysicsJointRotarySpring_setRestAngle);
        tolua_function(tolua_S,"getStiffness",lua_cocos2dx_physics_PhysicsJointRotarySpring_getStiffness);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointRotarySpring_createConstraints);
        tolua_function(tolua_S,"setStiffness",lua_cocos2dx_physics_PhysicsJointRotarySpring_setStiffness);
        tolua_function(tolua_S,"setDamping",lua_cocos2dx_physics_PhysicsJointRotarySpring_setDamping);
        tolua_function(tolua_S,"getRestAngle",lua_cocos2dx_physics_PhysicsJointRotarySpring_getRestAngle);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointRotarySpring_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointRotarySpring).name();
    g_luaType[typeName] = "cc.PhysicsJointRotarySpring";
    g_typeCast["PhysicsJointRotarySpring"] = "cc.PhysicsJointRotarySpring";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMax(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotaryLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotaryLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotaryLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMax'", nullptr);
            return 0;
        }
        double ret = cobj->getMax();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotaryLimit:getMax",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMax'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotaryLimit_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotaryLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotaryLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotaryLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotaryLimit:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotaryLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotaryLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotaryLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRotaryLimit:setMin");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMin'", nullptr);
            return 0;
        }
        cobj->setMin(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotaryLimit:setMin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMax(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotaryLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotaryLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotaryLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRotaryLimit:setMax");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMax'", nullptr);
            return 0;
        }
        cobj->setMax(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotaryLimit:setMax",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMax'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRotaryLimit* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRotaryLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRotaryLimit*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMin'", nullptr);
            return 0;
        }
        double ret = cobj->getMin();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRotaryLimit:getMin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMin'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRotaryLimit_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointRotaryLimit",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointRotaryLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsBody* arg1;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointRotaryLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsJointRotaryLimit* ret = cocos2d::PhysicsJointRotaryLimit::construct(arg0, arg1);
            object_to_luaval<cocos2d::PhysicsJointRotaryLimit>(tolua_S, "cc.PhysicsJointRotaryLimit",(cocos2d::PhysicsJointRotaryLimit*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointRotaryLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsBody* arg1;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointRotaryLimit:construct");
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsJointRotaryLimit:construct");
            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsJointRotaryLimit:construct");
            if (!ok) { break; }
            cocos2d::PhysicsJointRotaryLimit* ret = cocos2d::PhysicsJointRotaryLimit::construct(arg0, arg1, arg2, arg3);
            object_to_luaval<cocos2d::PhysicsJointRotaryLimit>(tolua_S, "cc.PhysicsJointRotaryLimit",(cocos2d::PhysicsJointRotaryLimit*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.PhysicsJointRotaryLimit:construct",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRotaryLimit_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointRotaryLimit_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointRotaryLimit)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointRotaryLimit(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointRotaryLimit");
    tolua_cclass(tolua_S,"PhysicsJointRotaryLimit","cc.PhysicsJointRotaryLimit","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointRotaryLimit");
        tolua_function(tolua_S,"getMax",lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMax);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointRotaryLimit_createConstraints);
        tolua_function(tolua_S,"setMin",lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMin);
        tolua_function(tolua_S,"setMax",lua_cocos2dx_physics_PhysicsJointRotaryLimit_setMax);
        tolua_function(tolua_S,"getMin",lua_cocos2dx_physics_PhysicsJointRotaryLimit_getMin);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointRotaryLimit_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointRotaryLimit).name();
    g_luaType[typeName] = "cc.PhysicsJointRotaryLimit";
    g_typeCast["PhysicsJointRotaryLimit"] = "cc.PhysicsJointRotaryLimit";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointRatchet_getAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getAngle'", nullptr);
            return 0;
        }
        double ret = cobj->getAngle();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:getAngle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getAngle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_setAngle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setAngle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRatchet:setAngle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setAngle'", nullptr);
            return 0;
        }
        cobj->setAngle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:setAngle",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setAngle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_setPhase(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setPhase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRatchet:setPhase");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setPhase'", nullptr);
            return 0;
        }
        cobj->setPhase(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:setPhase",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setPhase'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_getPhase(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getPhase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getPhase'", nullptr);
            return 0;
        }
        double ret = cobj->getPhase();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:getPhase",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getPhase'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_setRatchet(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setRatchet'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointRatchet:setRatchet");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setRatchet'", nullptr);
            return 0;
        }
        cobj->setRatchet(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:setRatchet",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_setRatchet'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_getRatchet(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointRatchet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointRatchet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getRatchet'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getRatchet'", nullptr);
            return 0;
        }
        double ret = cobj->getRatchet();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointRatchet:getRatchet",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_getRatchet'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointRatchet_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointRatchet",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointRatchet:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointRatchet:construct");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsJointRatchet:construct");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsJointRatchet:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointRatchet_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointRatchet* ret = cocos2d::PhysicsJointRatchet::construct(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsJointRatchet>(tolua_S, "cc.PhysicsJointRatchet",(cocos2d::PhysicsJointRatchet*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointRatchet:construct",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointRatchet_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointRatchet_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointRatchet)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointRatchet(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointRatchet");
    tolua_cclass(tolua_S,"PhysicsJointRatchet","cc.PhysicsJointRatchet","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointRatchet");
        tolua_function(tolua_S,"getAngle",lua_cocos2dx_physics_PhysicsJointRatchet_getAngle);
        tolua_function(tolua_S,"setAngle",lua_cocos2dx_physics_PhysicsJointRatchet_setAngle);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointRatchet_createConstraints);
        tolua_function(tolua_S,"setPhase",lua_cocos2dx_physics_PhysicsJointRatchet_setPhase);
        tolua_function(tolua_S,"getPhase",lua_cocos2dx_physics_PhysicsJointRatchet_getPhase);
        tolua_function(tolua_S,"setRatchet",lua_cocos2dx_physics_PhysicsJointRatchet_setRatchet);
        tolua_function(tolua_S,"getRatchet",lua_cocos2dx_physics_PhysicsJointRatchet_getRatchet);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointRatchet_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointRatchet).name();
    g_luaType[typeName] = "cc.PhysicsJointRatchet";
    g_typeCast["PhysicsJointRatchet"] = "cc.PhysicsJointRatchet";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointGear_setRatio(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGear* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGear",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGear*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGear_setRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointGear:setRatio");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGear_setRatio'", nullptr);
            return 0;
        }
        cobj->setRatio(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGear:setRatio",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGear_setRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGear_getPhase(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGear* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGear",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGear*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGear_getPhase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGear_getPhase'", nullptr);
            return 0;
        }
        double ret = cobj->getPhase();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGear:getPhase",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGear_getPhase'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGear_setPhase(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGear* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGear",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGear*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGear_setPhase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointGear:setPhase");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGear_setPhase'", nullptr);
            return 0;
        }
        cobj->setPhase(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGear:setPhase",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGear_setPhase'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGear_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGear* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGear",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGear*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGear_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGear_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGear:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGear_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGear_getRatio(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointGear* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointGear",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointGear*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointGear_getRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGear_getRatio'", nullptr);
            return 0;
        }
        double ret = cobj->getRatio();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointGear:getRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGear_getRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointGear_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointGear",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        double arg2;
        double arg3;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointGear:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointGear:construct");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsJointGear:construct");
        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.PhysicsJointGear:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointGear_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointGear* ret = cocos2d::PhysicsJointGear::construct(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::PhysicsJointGear>(tolua_S, "cc.PhysicsJointGear",(cocos2d::PhysicsJointGear*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointGear:construct",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointGear_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointGear_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointGear)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointGear(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointGear");
    tolua_cclass(tolua_S,"PhysicsJointGear","cc.PhysicsJointGear","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointGear");
        tolua_function(tolua_S,"setRatio",lua_cocos2dx_physics_PhysicsJointGear_setRatio);
        tolua_function(tolua_S,"getPhase",lua_cocos2dx_physics_PhysicsJointGear_getPhase);
        tolua_function(tolua_S,"setPhase",lua_cocos2dx_physics_PhysicsJointGear_setPhase);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointGear_createConstraints);
        tolua_function(tolua_S,"getRatio",lua_cocos2dx_physics_PhysicsJointGear_getRatio);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointGear_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointGear).name();
    g_luaType[typeName] = "cc.PhysicsJointGear";
    g_typeCast["PhysicsJointGear"] = "cc.PhysicsJointGear";
    return 1;
}

int lua_cocos2dx_physics_PhysicsJointMotor_setRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointMotor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointMotor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointMotor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointMotor_setRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsJointMotor:setRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointMotor_setRate'", nullptr);
            return 0;
        }
        cobj->setRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointMotor:setRate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointMotor_setRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointMotor_getRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointMotor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointMotor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointMotor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointMotor_getRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointMotor_getRate'", nullptr);
            return 0;
        }
        double ret = cobj->getRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointMotor:getRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointMotor_getRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointMotor_createConstraints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsJointMotor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsJointMotor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsJointMotor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsJointMotor_createConstraints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointMotor_createConstraints'", nullptr);
            return 0;
        }
        bool ret = cobj->createConstraints();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsJointMotor:createConstraints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointMotor_createConstraints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsJointMotor_construct(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.PhysicsJointMotor",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::PhysicsBody* arg0;
        cocos2d::PhysicsBody* arg1;
        double arg2;
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsJointMotor:construct");
        ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 3, "cc.PhysicsBody",&arg1, "cc.PhysicsJointMotor:construct");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.PhysicsJointMotor:construct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsJointMotor_construct'", nullptr);
            return 0;
        }
        cocos2d::PhysicsJointMotor* ret = cocos2d::PhysicsJointMotor::construct(arg0, arg1, arg2);
        object_to_luaval<cocos2d::PhysicsJointMotor>(tolua_S, "cc.PhysicsJointMotor",(cocos2d::PhysicsJointMotor*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.PhysicsJointMotor:construct",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsJointMotor_construct'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_physics_PhysicsJointMotor_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsJointMotor)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsJointMotor(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsJointMotor");
    tolua_cclass(tolua_S,"PhysicsJointMotor","cc.PhysicsJointMotor","cc.PhysicsJoint",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsJointMotor");
        tolua_function(tolua_S,"setRate",lua_cocos2dx_physics_PhysicsJointMotor_setRate);
        tolua_function(tolua_S,"getRate",lua_cocos2dx_physics_PhysicsJointMotor_getRate);
        tolua_function(tolua_S,"createConstraints",lua_cocos2dx_physics_PhysicsJointMotor_createConstraints);
        tolua_function(tolua_S,"construct", lua_cocos2dx_physics_PhysicsJointMotor_construct);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsJointMotor).name();
    g_luaType[typeName] = "cc.PhysicsJointMotor";
    g_typeCast["PhysicsJointMotor"] = "cc.PhysicsJointMotor";
    return 1;
}

int lua_cocos2dx_physics_PhysicsWorld_setGravity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setGravity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsWorld:setGravity");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setGravity'", nullptr);
            return 0;
        }
        cobj->setGravity(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setGravity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setGravity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getAllBodies(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getAllBodies'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getAllBodies'", nullptr);
            return 0;
        }
        const cocos2d::Vector<cocos2d::PhysicsBody *>& ret = cobj->getAllBodies();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getAllBodies",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getAllBodies'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_setFixedUpdateRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setFixedUpdateRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsWorld:setFixedUpdateRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setFixedUpdateRate'", nullptr);
            return 0;
        }
        cobj->setFixedUpdateRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setFixedUpdateRate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setFixedUpdateRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_setSubsteps(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setSubsteps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsWorld:setSubsteps");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setSubsteps'", nullptr);
            return 0;
        }
        cobj->setSubsteps(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setSubsteps",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setSubsteps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_setAutoStep(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setAutoStep'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsWorld:setAutoStep");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setAutoStep'", nullptr);
            return 0;
        }
        cobj->setAutoStep(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setAutoStep",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setAutoStep'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_addJoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_addJoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::PhysicsJoint* arg0;

        ok &= luaval_to_object<cocos2d::PhysicsJoint>(tolua_S, 2, "cc.PhysicsJoint",&arg0, "cc.PhysicsWorld:addJoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_addJoint'", nullptr);
            return 0;
        }
        cobj->addJoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:addJoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_addJoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_removeAllJoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllJoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllJoints'", nullptr);
            return 0;
        }
        cobj->removeAllJoints();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.PhysicsWorld:removeAllJoints");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllJoints'", nullptr);
            return 0;
        }
        cobj->removeAllJoints(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:removeAllJoints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllJoints'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getDebugDrawMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getDebugDrawMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getDebugDrawMask'", nullptr);
            return 0;
        }
        int ret = cobj->getDebugDrawMask();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getDebugDrawMask",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getDebugDrawMask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_isAutoStep(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_isAutoStep'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_isAutoStep'", nullptr);
            return 0;
        }
        bool ret = cobj->isAutoStep();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:isAutoStep",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_isAutoStep'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_removeBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_removeBody'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsWorld:removeBody");

            if (!ok) { break; }
            cobj->removeBody(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::PhysicsBody* arg0;
            ok &= luaval_to_object<cocos2d::PhysicsBody>(tolua_S, 2, "cc.PhysicsBody",&arg0, "cc.PhysicsWorld:removeBody");

            if (!ok) { break; }
            cobj->removeBody(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.PhysicsWorld:removeBody",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_removeBody'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_removeJoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_removeJoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::PhysicsJoint* arg0;

        ok &= luaval_to_object<cocos2d::PhysicsJoint>(tolua_S, 2, "cc.PhysicsJoint",&arg0, "cc.PhysicsWorld:removeJoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_removeJoint'", nullptr);
            return 0;
        }
        cobj->removeJoint(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        cocos2d::PhysicsJoint* arg0;
        bool arg1;

        ok &= luaval_to_object<cocos2d::PhysicsJoint>(tolua_S, 2, "cc.PhysicsJoint",&arg0, "cc.PhysicsWorld:removeJoint");

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.PhysicsWorld:removeJoint");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_removeJoint'", nullptr);
            return 0;
        }
        cobj->removeJoint(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:removeJoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_removeJoint'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getShapes(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getShapes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsWorld:getShapes");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getShapes'", nullptr);
            return 0;
        }
        cocos2d::Vector<cocos2d::PhysicsShape *> ret = cobj->getShapes(arg0);
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getShapes",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getShapes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_step(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_step'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsWorld:step");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_step'", nullptr);
            return 0;
        }
        cobj->step(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:step",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_step'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_setDebugDrawMask(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setDebugDrawMask'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsWorld:setDebugDrawMask");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setDebugDrawMask'", nullptr);
            return 0;
        }
        cobj->setDebugDrawMask(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setDebugDrawMask",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setDebugDrawMask'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getGravity(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getGravity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getGravity'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getGravity();
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getGravity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getGravity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_setUpdateRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setUpdateRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsWorld:setUpdateRate");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setUpdateRate'", nullptr);
            return 0;
        }
        cobj->setUpdateRate(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setUpdateRate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setUpdateRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getFixedUpdateRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getFixedUpdateRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getFixedUpdateRate'", nullptr);
            return 0;
        }
        int ret = cobj->getFixedUpdateRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getFixedUpdateRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getFixedUpdateRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getSubsteps(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getSubsteps'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getSubsteps'", nullptr);
            return 0;
        }
        int ret = cobj->getSubsteps();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getSubsteps",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getSubsteps'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getSpeed'", nullptr);
            return 0;
        }
        double ret = cobj->getSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getUpdateRate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getUpdateRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getUpdateRate'", nullptr);
            return 0;
        }
        int ret = cobj->getUpdateRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getUpdateRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getUpdateRate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_removeAllBodies(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllBodies'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllBodies'", nullptr);
            return 0;
        }
        cobj->removeAllBodies();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:removeAllBodies",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_removeAllBodies'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_setSpeed(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_setSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.PhysicsWorld:setSpeed");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_setSpeed'", nullptr);
            return 0;
        }
        cobj->setSpeed(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:setSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_setSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getShape(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getShape'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.PhysicsWorld:getShape");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getShape'", nullptr);
            return 0;
        }
        cocos2d::PhysicsShape* ret = cobj->getShape(arg0);
        object_to_luaval<cocos2d::PhysicsShape>(tolua_S, "cc.PhysicsShape",(cocos2d::PhysicsShape*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getShape",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getShape'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_physics_PhysicsWorld_getBody(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::PhysicsWorld* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.PhysicsWorld",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::PhysicsWorld*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_physics_PhysicsWorld_getBody'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.PhysicsWorld:getBody");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_physics_PhysicsWorld_getBody'", nullptr);
            return 0;
        }
        cocos2d::PhysicsBody* ret = cobj->getBody(arg0);
        object_to_luaval<cocos2d::PhysicsBody>(tolua_S, "cc.PhysicsBody",(cocos2d::PhysicsBody*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.PhysicsWorld:getBody",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_physics_PhysicsWorld_getBody'.",&tolua_err);
#endif

    return 0;
}
static int lua_cocos2dx_physics_PhysicsWorld_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PhysicsWorld)");
    return 0;
}

int lua_register_cocos2dx_physics_PhysicsWorld(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.PhysicsWorld");
    tolua_cclass(tolua_S,"PhysicsWorld","cc.PhysicsWorld","",nullptr);

    tolua_beginmodule(tolua_S,"PhysicsWorld");
        tolua_function(tolua_S,"setGravity",lua_cocos2dx_physics_PhysicsWorld_setGravity);
        tolua_function(tolua_S,"getAllBodies",lua_cocos2dx_physics_PhysicsWorld_getAllBodies);
        tolua_function(tolua_S,"setFixedUpdateRate",lua_cocos2dx_physics_PhysicsWorld_setFixedUpdateRate);
        tolua_function(tolua_S,"setSubsteps",lua_cocos2dx_physics_PhysicsWorld_setSubsteps);
        tolua_function(tolua_S,"setAutoStep",lua_cocos2dx_physics_PhysicsWorld_setAutoStep);
        tolua_function(tolua_S,"addJoint",lua_cocos2dx_physics_PhysicsWorld_addJoint);
        tolua_function(tolua_S,"removeAllJoints",lua_cocos2dx_physics_PhysicsWorld_removeAllJoints);
        tolua_function(tolua_S,"getDebugDrawMask",lua_cocos2dx_physics_PhysicsWorld_getDebugDrawMask);
        tolua_function(tolua_S,"isAutoStep",lua_cocos2dx_physics_PhysicsWorld_isAutoStep);
        tolua_function(tolua_S,"removeBody",lua_cocos2dx_physics_PhysicsWorld_removeBody);
        tolua_function(tolua_S,"removeJoint",lua_cocos2dx_physics_PhysicsWorld_removeJoint);
        tolua_function(tolua_S,"getShapes",lua_cocos2dx_physics_PhysicsWorld_getShapes);
        tolua_function(tolua_S,"step",lua_cocos2dx_physics_PhysicsWorld_step);
        tolua_function(tolua_S,"setDebugDrawMask",lua_cocos2dx_physics_PhysicsWorld_setDebugDrawMask);
        tolua_function(tolua_S,"getGravity",lua_cocos2dx_physics_PhysicsWorld_getGravity);
        tolua_function(tolua_S,"setUpdateRate",lua_cocos2dx_physics_PhysicsWorld_setUpdateRate);
        tolua_function(tolua_S,"getFixedUpdateRate",lua_cocos2dx_physics_PhysicsWorld_getFixedUpdateRate);
        tolua_function(tolua_S,"getSubsteps",lua_cocos2dx_physics_PhysicsWorld_getSubsteps);
        tolua_function(tolua_S,"getSpeed",lua_cocos2dx_physics_PhysicsWorld_getSpeed);
        tolua_function(tolua_S,"getUpdateRate",lua_cocos2dx_physics_PhysicsWorld_getUpdateRate);
        tolua_function(tolua_S,"removeAllBodies",lua_cocos2dx_physics_PhysicsWorld_removeAllBodies);
        tolua_function(tolua_S,"setSpeed",lua_cocos2dx_physics_PhysicsWorld_setSpeed);
        tolua_function(tolua_S,"getShape",lua_cocos2dx_physics_PhysicsWorld_getShape);
        tolua_function(tolua_S,"getBody",lua_cocos2dx_physics_PhysicsWorld_getBody);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::PhysicsWorld).name();
    g_luaType[typeName] = "cc.PhysicsWorld";
    g_typeCast["PhysicsWorld"] = "cc.PhysicsWorld";
    return 1;
}
TOLUA_API int register_all_cocos2dx_physics(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_physics_PhysicsBody(tolua_S);
	lua_register_cocos2dx_physics_PhysicsWorld(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJoint(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointLimit(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointFixed(tolua_S);
	lua_register_cocos2dx_physics_EventListenerPhysicsContact(tolua_S);
	lua_register_cocos2dx_physics_EventListenerPhysicsContactWithGroup(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShape(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapePolygon(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapeBox(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointMotor(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointRatchet(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointDistance(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapeCircle(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapeEdgePolygon(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointPin(tolua_S);
	lua_register_cocos2dx_physics_PhysicsContactPreSolve(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapeEdgeChain(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapeEdgeSegment(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointGear(tolua_S);
	lua_register_cocos2dx_physics_PhysicsContact(tolua_S);
	lua_register_cocos2dx_physics_EventListenerPhysicsContactWithBodies(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointRotarySpring(tolua_S);
	lua_register_cocos2dx_physics_PhysicsContactPostSolve(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointGroove(tolua_S);
	lua_register_cocos2dx_physics_PhysicsShapeEdgeBox(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointRotaryLimit(tolua_S);
	lua_register_cocos2dx_physics_PhysicsJointSpring(tolua_S);
	lua_register_cocos2dx_physics_EventListenerPhysicsContactWithShapes(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

#endif
