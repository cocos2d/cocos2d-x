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

#include "scripting/lua-bindings/manual/navmesh/lua_cocos2dx_navmesh_conversions.h"
#include "base/ccConfig.h"
#if CC_USE_NAVMESH

#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "navmesh/CCNavMeshAgent.h"

#if COCOS2D_DEBUG >=1
extern void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName);
#endif

bool luaval_to_navmeshagentparam(lua_State* L, int lo, cocos2d::NavMeshAgentParam* outValue , const char* funcName)
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
        lua_pushstring(L, "radius");
        lua_gettable(L,lo);
        outValue->radius = lua_isnumber(L, -1)? (float)lua_tonumber(L, -1) : 0.6;
        lua_pop(L,1);
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->height = lua_isnumber(L, -1)?(float)lua_tonumber(L, -1) : 2.0;
        lua_pop(L,1);
        
        lua_pushstring(L, "maxAcceleration");
        lua_gettable(L, lo);
        outValue->maxAcceleration = lua_isnumber(L, -1)?(float)lua_tonumber(L, -1) : 8.0;
        lua_pop(L, 1);
        

        lua_pushstring(L, "maxSpeed");
        lua_gettable(L, lo);
        outValue->maxSpeed = lua_isnumber(L, -1)?(float)lua_tonumber(L, -1) : 3.5;
        lua_pop(L, 1);

        lua_pushstring(L, "collisionQueryRange");
        lua_gettable(L, lo);
        outValue->collisionQueryRange = lua_isnumber(L, -1)?(float)lua_tonumber(L, -1) : outValue->radius * 12.0;
        lua_pop(L, 1);

        lua_pushstring(L, "pathOptimizationRange");
        lua_gettable(L, lo);
        outValue->pathOptimizationRange = lua_isnumber(L, -1)?(float)lua_tonumber(L, -1) :  outValue->radius * 30.0;
        lua_pop(L, 1);

        lua_pushstring(L, "separationWeight");
        lua_gettable(L, lo);
        outValue->separationWeight = lua_isnumber(L, -1)?(float)lua_tonumber(L, -1) : 2.0;
        lua_pop(L, 1);

        lua_pushstring(L, "updateFlags");
        lua_gettable(L, lo);
        outValue->updateFlags = lua_isnumber(L, -1)?(unsigned char)lua_tonumber(L, -1) : DT_CROWD_ANTICIPATE_TURNS | DT_CROWD_OPTIMIZE_VIS | DT_CROWD_OPTIMIZE_TOPO | DT_CROWD_OBSTACLE_AVOIDANCE;
        lua_pop(L, 1);

        lua_pushstring(L, "obstacleAvoidanceType");
        lua_gettable(L, lo);
        outValue->obstacleAvoidanceType = lua_isnumber(L, -1)?(unsigned char)lua_tonumber(L, -1) : 3;
        lua_pop(L, 1);

        lua_pushstring(L, "queryFilterType");
        lua_gettable(L, lo);
        outValue->queryFilterType = lua_isnumber(L, -1)?(unsigned char)lua_tonumber(L, -1) : 0;
        lua_pop(L, 1);

        return true;
    }
    
    return false;
}

bool luaval_to_offmeshlinkdata(lua_State* L, int lo, cocos2d::OffMeshLinkData* outValue , const char* funcName)
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
        lua_pushstring(L, "startPosition");
        lua_gettable(L,lo);
        ok &= luaval_to_vec3(L, lua_gettop(L), &outValue->startPosition);
        if(!ok)
        {
            lua_pop(L, 1);
            return false;
        }
        lua_pop(L,1);

        lua_pushstring(L, "endPosition");
        ok &= luaval_to_vec3(L, lua_gettop(L), &outValue->endPosition);
        if(!ok)
        {
            lua_pop(L, 1);
            return false;
        }
        lua_pop(L,1);
        return true;
    }
    
    return false;
}

void navmeshagentparam_to_luaval(lua_State* L,const cocos2d::NavMeshAgentParam& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    lua_pushstring(L, "radius");
    lua_pushnumber(L, (lua_Number)inValue.radius);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "height");
    lua_pushnumber(L, (lua_Number)inValue.height);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "maxAcceleration");
    lua_pushnumber(L, (lua_Number)inValue.maxAcceleration);
    lua_rawset(L, -3);

    lua_pushstring(L, "maxSpeed");
    lua_pushnumber(L, (lua_Number)inValue.maxSpeed);
    lua_rawset(L, -3);

    lua_pushstring(L, "collisionQueryRange");
    lua_pushnumber(L, (lua_Number)inValue.collisionQueryRange);
    lua_rawset(L, -3);

    lua_pushstring(L, "pathOptimizationRange");
    lua_pushnumber(L, (lua_Number)inValue.pathOptimizationRange);
    lua_rawset(L, -3);

    lua_pushstring(L, "separationWeight");
    lua_pushnumber(L, (lua_Number)inValue.separationWeight);
    lua_rawset(L, -3);

    lua_pushstring(L, "updateFlags");
    lua_pushnumber(L, (lua_Number)inValue.updateFlags);
    lua_rawset(L, -3);

    lua_pushstring(L, "obstacleAvoidanceType");
    lua_pushnumber(L, (lua_Number)inValue.obstacleAvoidanceType);
    lua_rawset(L, -3);

    lua_pushstring(L, "queryFilterType");
    lua_pushnumber(L, (lua_Number)inValue.queryFilterType);
    lua_rawset(L, -3);
}

void offmeshlinkdata_to_luaval(lua_State* L,const cocos2d::OffMeshLinkData& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    lua_pushstring(L, "startPosition");
    vec3_to_luaval(L, inValue.startPosition);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "endPosition");
    vec3_to_luaval(L, inValue.endPosition);
    lua_rawset(L, -3);
}

#endif