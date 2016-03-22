#include "scripting/lua-bindings/auto/lua_cocos2dx_navmesh_auto.hpp"
#if CC_USE_NAVMESH
#include "navmesh/CCNavMesh.h"
#include "scripting/lua-bindings/manual/navmesh/lua_cocos2dx_navmesh_conversions.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshAgent:setMaxSpeed");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed'", nullptr);
            return 0;
        }
        cobj->setMaxSpeed(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setMaxSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_syncToNode(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_syncToNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_syncToNode'", nullptr);
            return 0;
        }
        cobj->syncToNode();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:syncToNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_syncToNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink'", nullptr);
            return 0;
        }
        cobj->completeOffMeshLink();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:completeOffMeshLink",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight'", nullptr);
            return 0;
        }
        double ret = cobj->getSeparationWeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getSeparationWeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.NavMeshAgent:setAutoTraverseOffMeshLink");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink'", nullptr);
            return 0;
        }
        cobj->setAutoTraverseOffMeshLink(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setAutoTraverseOffMeshLink",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = cobj->getCurrentVelocity();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getCurrentVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_syncToAgent(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_syncToAgent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_syncToAgent'", nullptr);
            return 0;
        }
        cobj->syncToAgent();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:syncToAgent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_syncToAgent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink'", nullptr);
            return 0;
        }
        bool ret = cobj->isOnOffMeshLink();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:isOnOffMeshLink",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshAgent:setSeparationWeight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight'", nullptr);
            return 0;
        }
        cobj->setSeparationWeight(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setSeparationWeight",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_pause(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_pause'", nullptr);
            return 0;
        }
        cobj->pause();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getUserData(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getUserData'", nullptr);
            return 0;
        }
        void* ret = cobj->getUserData();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getUserData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getUserData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.NavMeshAgent:setAutoOrientation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation'", nullptr);
            return 0;
        }
        cobj->setAutoOrientation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setAutoOrientation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getHeight(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getHeight'", nullptr);
            return 0;
        }
        double ret = cobj->getHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getHeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed'", nullptr);
            return 0;
        }
        double ret = cobj->getMaxSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getMaxSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData'", nullptr);
            return 0;
        }
        cocos2d::OffMeshLinkData ret = cobj->getCurrentOffMeshLinkData();
        offmeshlinkdata_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getCurrentOffMeshLinkData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getRadius(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setSyncFlag(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setSyncFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NavMeshAgent::NavMeshAgentSyncFlag arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.NavMeshAgent:setSyncFlag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setSyncFlag'", nullptr);
            return 0;
        }
        cobj->setSyncFlag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setSyncFlag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setSyncFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getSyncFlag(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getSyncFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getSyncFlag'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getSyncFlag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getSyncFlag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getSyncFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_resume(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_resume'", nullptr);
            return 0;
        }
        cobj->resume();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:resume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_resume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_stop(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_stop'", nullptr);
            return 0;
        }
        cobj->stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshAgent:setMaxAcceleration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration'", nullptr);
            return 0;
        }
        cobj->setMaxAcceleration(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setMaxAcceleration",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec3 arg0;

        ok &= luaval_to_vec3(tolua_S, 2, &arg0, "cc.NavMeshAgent:setOrientationRefAxes");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes'", nullptr);
            return 0;
        }
        cobj->setOrientationRefAxes(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setOrientationRefAxes",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration'", nullptr);
            return 0;
        }
        double ret = cobj->getMaxAcceleration();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getMaxAcceleration",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setHeight(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshAgent:setHeight");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setHeight'", nullptr);
            return 0;
        }
        cobj->setHeight(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setHeight",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setUserData(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setUserData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setUserData'", nullptr);
            return 0;
        }
        cobj->setUserData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setUserData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setUserData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType'", nullptr);
            return 0;
        }
        uint16_t ret = cobj->getObstacleAvoidanceType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getObstacleAvoidanceType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getVelocity(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_getVelocity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getVelocity'", nullptr);
            return 0;
        }
        cocos2d::Vec3 ret = cobj->getVelocity();
        vec3_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:getVelocity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getVelocity'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setRadius(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshAgent:setRadius");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setRadius'", nullptr);
            return 0;
        }
        cobj->setRadius(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setRadius",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        uint16_t arg0;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "cc.NavMeshAgent:setObstacleAvoidanceType");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType'", nullptr);
            return 0;
        }
        cobj->setObstacleAvoidanceType(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:setObstacleAvoidanceType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NavMeshAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName'", nullptr);
            return 0;
        }
        const std::string& ret = cocos2d::NavMeshAgent::getNavMeshAgentComponentName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.NavMeshAgent:getNavMeshAgentComponentName",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NavMeshAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::NavMeshAgentParam arg0;
        ok &= luaval_to_navmeshagentparam(tolua_S, 2, &arg0, "cc.NavMeshAgent:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_create'", nullptr);
            return 0;
        }
        cocos2d::NavMeshAgent* ret = cocos2d::NavMeshAgent::create(arg0);
        object_to_luaval<cocos2d::NavMeshAgent>(tolua_S, "cc.NavMeshAgent",(cocos2d::NavMeshAgent*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.NavMeshAgent:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_navmesh_NavMeshAgent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshAgent_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NavMeshAgent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMeshAgent");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshAgent:NavMeshAgent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshAgent_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_navmesh_NavMeshAgent_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NavMeshAgent)");
    return 0;
}

int lua_register_cocos2dx_navmesh_NavMeshAgent(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.NavMeshAgent");
    tolua_cclass(tolua_S,"NavMeshAgent","cc.NavMeshAgent","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"NavMeshAgent");
        tolua_function(tolua_S,"new",lua_cocos2dx_navmesh_NavMeshAgent_constructor);
        tolua_function(tolua_S,"setMaxSpeed",lua_cocos2dx_navmesh_NavMeshAgent_setMaxSpeed);
        tolua_function(tolua_S,"syncToNode",lua_cocos2dx_navmesh_NavMeshAgent_syncToNode);
        tolua_function(tolua_S,"completeOffMeshLink",lua_cocos2dx_navmesh_NavMeshAgent_completeOffMeshLink);
        tolua_function(tolua_S,"getSeparationWeight",lua_cocos2dx_navmesh_NavMeshAgent_getSeparationWeight);
        tolua_function(tolua_S,"setAutoTraverseOffMeshLink",lua_cocos2dx_navmesh_NavMeshAgent_setAutoTraverseOffMeshLink);
        tolua_function(tolua_S,"getCurrentVelocity",lua_cocos2dx_navmesh_NavMeshAgent_getCurrentVelocity);
        tolua_function(tolua_S,"syncToAgent",lua_cocos2dx_navmesh_NavMeshAgent_syncToAgent);
        tolua_function(tolua_S,"isOnOffMeshLink",lua_cocos2dx_navmesh_NavMeshAgent_isOnOffMeshLink);
        tolua_function(tolua_S,"setSeparationWeight",lua_cocos2dx_navmesh_NavMeshAgent_setSeparationWeight);
        tolua_function(tolua_S,"pause",lua_cocos2dx_navmesh_NavMeshAgent_pause);
        tolua_function(tolua_S,"getUserData",lua_cocos2dx_navmesh_NavMeshAgent_getUserData);
        tolua_function(tolua_S,"setAutoOrientation",lua_cocos2dx_navmesh_NavMeshAgent_setAutoOrientation);
        tolua_function(tolua_S,"getHeight",lua_cocos2dx_navmesh_NavMeshAgent_getHeight);
        tolua_function(tolua_S,"getMaxSpeed",lua_cocos2dx_navmesh_NavMeshAgent_getMaxSpeed);
        tolua_function(tolua_S,"getCurrentOffMeshLinkData",lua_cocos2dx_navmesh_NavMeshAgent_getCurrentOffMeshLinkData);
        tolua_function(tolua_S,"getRadius",lua_cocos2dx_navmesh_NavMeshAgent_getRadius);
        tolua_function(tolua_S,"setSyncFlag",lua_cocos2dx_navmesh_NavMeshAgent_setSyncFlag);
        tolua_function(tolua_S,"getSyncFlag",lua_cocos2dx_navmesh_NavMeshAgent_getSyncFlag);
        tolua_function(tolua_S,"resume",lua_cocos2dx_navmesh_NavMeshAgent_resume);
        tolua_function(tolua_S,"stop",lua_cocos2dx_navmesh_NavMeshAgent_stop);
        tolua_function(tolua_S,"setMaxAcceleration",lua_cocos2dx_navmesh_NavMeshAgent_setMaxAcceleration);
        tolua_function(tolua_S,"setOrientationRefAxes",lua_cocos2dx_navmesh_NavMeshAgent_setOrientationRefAxes);
        tolua_function(tolua_S,"getMaxAcceleration",lua_cocos2dx_navmesh_NavMeshAgent_getMaxAcceleration);
        tolua_function(tolua_S,"setHeight",lua_cocos2dx_navmesh_NavMeshAgent_setHeight);
        tolua_function(tolua_S,"setUserData",lua_cocos2dx_navmesh_NavMeshAgent_setUserData);
        tolua_function(tolua_S,"getObstacleAvoidanceType",lua_cocos2dx_navmesh_NavMeshAgent_getObstacleAvoidanceType);
        tolua_function(tolua_S,"getVelocity",lua_cocos2dx_navmesh_NavMeshAgent_getVelocity);
        tolua_function(tolua_S,"setRadius",lua_cocos2dx_navmesh_NavMeshAgent_setRadius);
        tolua_function(tolua_S,"setObstacleAvoidanceType",lua_cocos2dx_navmesh_NavMeshAgent_setObstacleAvoidanceType);
        tolua_function(tolua_S,"getNavMeshAgentComponentName", lua_cocos2dx_navmesh_NavMeshAgent_getNavMeshAgentComponentName);
        tolua_function(tolua_S,"create", lua_cocos2dx_navmesh_NavMeshAgent_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::NavMeshAgent).name();
    g_luaType[typeName] = "cc.NavMeshAgent";
    g_typeCast["NavMeshAgent"] = "cc.NavMeshAgent";
    return 1;
}

int lua_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag'", nullptr);
            return 0;
        }
        int ret = (int)cobj->getSyncFlag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:getSyncFlag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_initWith(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_initWith'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        double arg0;
        double arg1;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshObstacle:initWith");

        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NavMeshObstacle:initWith");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_initWith'", nullptr);
            return 0;
        }
        bool ret = cobj->initWith(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:initWith",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_initWith'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle'", nullptr);
            return 0;
        }
        cobj->syncToObstacle();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:syncToObstacle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_syncToNode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_syncToNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_syncToNode'", nullptr);
            return 0;
        }
        cobj->syncToNode();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:syncToNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_syncToNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_getHeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getHeight'", nullptr);
            return 0;
        }
        double ret = cobj->getHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:getHeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NavMeshObstacle::NavMeshObstacleSyncFlag arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.NavMeshObstacle:setSyncFlag");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag'", nullptr);
            return 0;
        }
        cobj->setSyncFlag(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:setSyncFlag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_getRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMeshObstacle*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getRadius'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getRadius'", nullptr);
            return 0;
        }
        double ret = cobj->getRadius();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:getRadius",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getRadius'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        double arg0;
        double arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMeshObstacle:create");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "cc.NavMeshObstacle:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_create'", nullptr);
            return 0;
        }
        cocos2d::NavMeshObstacle* ret = cocos2d::NavMeshObstacle::create(arg0, arg1);
        object_to_luaval<cocos2d::NavMeshObstacle>(tolua_S, "cc.NavMeshObstacle",(cocos2d::NavMeshObstacle*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.NavMeshObstacle:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NavMeshObstacle",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName'", nullptr);
            return 0;
        }
        const std::string& ret = cocos2d::NavMeshObstacle::getNavMeshObstacleComponentName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.NavMeshObstacle:getNavMeshObstacleComponentName",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_navmesh_NavMeshObstacle_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMeshObstacle* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMeshObstacle_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NavMeshObstacle();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMeshObstacle");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMeshObstacle:NavMeshObstacle",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMeshObstacle_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_navmesh_NavMeshObstacle_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NavMeshObstacle)");
    return 0;
}

int lua_register_cocos2dx_navmesh_NavMeshObstacle(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.NavMeshObstacle");
    tolua_cclass(tolua_S,"NavMeshObstacle","cc.NavMeshObstacle","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"NavMeshObstacle");
        tolua_function(tolua_S,"new",lua_cocos2dx_navmesh_NavMeshObstacle_constructor);
        tolua_function(tolua_S,"getSyncFlag",lua_cocos2dx_navmesh_NavMeshObstacle_getSyncFlag);
        tolua_function(tolua_S,"initWith",lua_cocos2dx_navmesh_NavMeshObstacle_initWith);
        tolua_function(tolua_S,"syncToObstacle",lua_cocos2dx_navmesh_NavMeshObstacle_syncToObstacle);
        tolua_function(tolua_S,"syncToNode",lua_cocos2dx_navmesh_NavMeshObstacle_syncToNode);
        tolua_function(tolua_S,"getHeight",lua_cocos2dx_navmesh_NavMeshObstacle_getHeight);
        tolua_function(tolua_S,"setSyncFlag",lua_cocos2dx_navmesh_NavMeshObstacle_setSyncFlag);
        tolua_function(tolua_S,"getRadius",lua_cocos2dx_navmesh_NavMeshObstacle_getRadius);
        tolua_function(tolua_S,"create", lua_cocos2dx_navmesh_NavMeshObstacle_create);
        tolua_function(tolua_S,"getNavMeshObstacleComponentName", lua_cocos2dx_navmesh_NavMeshObstacle_getNavMeshObstacleComponentName);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::NavMeshObstacle).name();
    g_luaType[typeName] = "cc.NavMeshObstacle";
    g_typeCast["NavMeshObstacle"] = "cc.NavMeshObstacle";
    return 1;
}

int lua_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NavMeshObstacle* arg0;

        ok &= luaval_to_object<cocos2d::NavMeshObstacle>(tolua_S, 2, "cc.NavMeshObstacle",&arg0, "cc.NavMesh:removeNavMeshObstacle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle'", nullptr);
            return 0;
        }
        cobj->removeNavMeshObstacle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:removeNavMeshObstacle",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_removeNavMeshAgent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_removeNavMeshAgent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NavMeshAgent* arg0;

        ok &= luaval_to_object<cocos2d::NavMeshAgent>(tolua_S, 2, "cc.NavMeshAgent",&arg0, "cc.NavMesh:removeNavMeshAgent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_removeNavMeshAgent'", nullptr);
            return 0;
        }
        cobj->removeNavMeshAgent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:removeNavMeshAgent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_removeNavMeshAgent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.NavMesh:update");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_update'", nullptr);
            return 0;
        }
        cobj->update(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled'", nullptr);
            return 0;
        }
        bool ret = cobj->isDebugDrawEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:isDebugDrawEnabled",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_addNavMeshAgent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_addNavMeshAgent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NavMeshAgent* arg0;

        ok &= luaval_to_object<cocos2d::NavMeshAgent>(tolua_S, 2, "cc.NavMeshAgent",&arg0, "cc.NavMesh:addNavMeshAgent");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_addNavMeshAgent'", nullptr);
            return 0;
        }
        cobj->addNavMeshAgent(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:addNavMeshAgent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_addNavMeshAgent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_addNavMeshObstacle(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_addNavMeshObstacle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::NavMeshObstacle* arg0;

        ok &= luaval_to_object<cocos2d::NavMeshObstacle>(tolua_S, 2, "cc.NavMeshObstacle",&arg0, "cc.NavMesh:addNavMeshObstacle");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_addNavMeshObstacle'", nullptr);
            return 0;
        }
        cobj->addNavMeshObstacle(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:addNavMeshObstacle",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_addNavMeshObstacle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_setDebugDrawEnable(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_setDebugDrawEnable'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.NavMesh:setDebugDrawEnable");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_setDebugDrawEnable'", nullptr);
            return 0;
        }
        cobj->setDebugDrawEnable(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:setDebugDrawEnable",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_setDebugDrawEnable'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_debugDraw(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::NavMesh*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_navmesh_NavMesh_debugDraw'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Renderer* arg0;

        ok &= luaval_to_object<cocos2d::Renderer>(tolua_S, 2, "cc.Renderer",&arg0, "cc.NavMesh:debugDraw");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_debugDraw'", nullptr);
            return 0;
        }
        cobj->debugDraw(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:debugDraw",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_debugDraw'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.NavMesh",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.NavMesh:create");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.NavMesh:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_create'", nullptr);
            return 0;
        }
        cocos2d::NavMesh* ret = cocos2d::NavMesh::create(arg0, arg1);
        object_to_luaval<cocos2d::NavMesh>(tolua_S, "cc.NavMesh",(cocos2d::NavMesh*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.NavMesh:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_navmesh_NavMesh_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::NavMesh* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::NavMesh();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMesh");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:NavMesh",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_navmesh_NavMesh_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NavMesh)");
    return 0;
}

int lua_register_cocos2dx_navmesh_NavMesh(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.NavMesh");
    tolua_cclass(tolua_S,"NavMesh","cc.NavMesh","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"NavMesh");
        tolua_function(tolua_S,"new",lua_cocos2dx_navmesh_NavMesh_constructor);
        tolua_function(tolua_S,"removeNavMeshObstacle",lua_cocos2dx_navmesh_NavMesh_removeNavMeshObstacle);
        tolua_function(tolua_S,"removeNavMeshAgent",lua_cocos2dx_navmesh_NavMesh_removeNavMeshAgent);
        tolua_function(tolua_S,"update",lua_cocos2dx_navmesh_NavMesh_update);
        tolua_function(tolua_S,"isDebugDrawEnabled",lua_cocos2dx_navmesh_NavMesh_isDebugDrawEnabled);
        tolua_function(tolua_S,"addNavMeshAgent",lua_cocos2dx_navmesh_NavMesh_addNavMeshAgent);
        tolua_function(tolua_S,"addNavMeshObstacle",lua_cocos2dx_navmesh_NavMesh_addNavMeshObstacle);
        tolua_function(tolua_S,"setDebugDrawEnable",lua_cocos2dx_navmesh_NavMesh_setDebugDrawEnable);
        tolua_function(tolua_S,"debugDraw",lua_cocos2dx_navmesh_NavMesh_debugDraw);
        tolua_function(tolua_S,"create", lua_cocos2dx_navmesh_NavMesh_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::NavMesh).name();
    g_luaType[typeName] = "cc.NavMesh";
    g_typeCast["NavMesh"] = "cc.NavMesh";
    return 1;
}
TOLUA_API int register_all_cocos2dx_navmesh(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_navmesh_NavMeshObstacle(tolua_S);
	lua_register_cocos2dx_navmesh_NavMeshAgent(tolua_S);
	lua_register_cocos2dx_navmesh_NavMesh(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

#endif
