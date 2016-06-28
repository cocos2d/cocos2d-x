#include "scripting/lua-bindings/manual/cocos2d/lua_cocos2dx_experimental_manual.hpp"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "2d/CCFastTMXLayer.h"

static int lua_cocos2dx_experimental_TMXLayer_getTileGIDAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getTileGIDAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccexp.TMXLayer:getTileGIDAt");
        if(!ok)
            return 0;
        int ret = cobj->getTileGIDAt(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        tolua_pushnumber(tolua_S,(lua_Number)0);
        return 2;
    }
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        int arg1 = 0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccexp.TMXLayer:getTileGIDAt");
        ok &= luaval_to_int32(tolua_S, 3, &arg1, "ccexp.TMXLayer:getTileGIDAt");

        if(!ok)
            return 0;

        unsigned int ret = cobj->getTileGIDAt(arg0, (cocos2d::TMXTileFlags*)&arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        tolua_pushnumber(tolua_S,(lua_Number)arg1);
        return 2;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getTileGIDAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getTileGIDAt'.",&tolua_err);
#endif

    return 0;
}

static void extendExperimentalTMXLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ccexp.TMXLayer");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "getTileGIDAt", lua_cocos2dx_experimental_TMXLayer_getTileGIDAt);
    }
    lua_pop(tolua_S, 1);
}

bool isVectorV3FC4BT2F(lua_State* tolua_S, int lo)
{
    if (!lua_istable(tolua_S, lo))
        return false;

    lua_pushnumber(tolua_S, 1);
    lua_gettable(tolua_S,lo);
    if (!lua_istable(tolua_S, -1))
        return false;

    lua_pushstring(tolua_S, "vertices");
    lua_gettable(tolua_S, -2);
    if (lua_isnil(tolua_S, -1))
        return  false;
    lua_pop(tolua_S, 1);

    lua_pushstring(tolua_S, "colors");
    lua_gettable(tolua_S, -2);
    if (lua_isnil(tolua_S, -1))
        return  false;
    lua_pop(tolua_S, 1);

    lua_pushstring(tolua_S, "texCoords");
    lua_gettable(tolua_S, -2);
    if (lua_isnil(tolua_S, -1))
        return  false;
    lua_pop(tolua_S, 1);

    return true;
}

int register_all_cocos2dx_experimental_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;

    extendExperimentalTMXLayer(L);

    return 0;
}
