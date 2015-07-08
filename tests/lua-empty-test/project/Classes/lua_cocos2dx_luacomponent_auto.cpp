#include "lua_cocos2dx_luacomponent_auto.hpp"
#include "cocos2d.h"
#include "CCComponentLua.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_luacomponent_ComponentLua_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ComponentLua* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ComponentLua",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ComponentLua*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_luacomponent_ComponentLua_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ComponentLua:update");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_luacomponent_ComponentLua_update'", nullptr);
            return 0;
        }
        cobj->update(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ComponentLua:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_luacomponent_ComponentLua_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_luacomponent_ComponentLua_getScriptObject(lua_State* tolua_S)
{
    cocos2d::ComponentLua* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ComponentLua",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ComponentLua*)tolua_tousertype(tolua_S,1,0);
    cobj->getScriptObject();
    
    return 1;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_luacomponent_ComponentLua_getScriptObject'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_luacomponent_ComponentLua_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ComponentLua",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.ComponentLua:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_luacomponent_ComponentLua_create'", nullptr);
            return 0;
        }
        cocos2d::ComponentLua* ret = cocos2d::ComponentLua::create(arg0);
        object_to_luaval<cocos2d::ComponentLua>(tolua_S, "cc.ComponentLua",(cocos2d::ComponentLua*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ComponentLua:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_luacomponent_ComponentLua_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_luacomponent_ComponentLua_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ComponentLua)");
    return 0;
}

int lua_register_cocos2dx_luacomponent_ComponentLua(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ComponentLua");
    tolua_cclass(tolua_S,"ComponentLua","cc.ComponentLua","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"ComponentLua");
        tolua_function(tolua_S,"update",lua_cocos2dx_luacomponent_ComponentLua_update);
    tolua_function(tolua_S,"getScriptObject",lua_cocos2dx_luacomponent_ComponentLua_getScriptObject);
        tolua_function(tolua_S,"create", lua_cocos2dx_luacomponent_ComponentLua_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ComponentLua).name();
    g_luaType[typeName] = "cc.ComponentLua";
    g_typeCast["ComponentLua"] = "cc.ComponentLua";
    return 1;
}
TOLUA_API int register_all_cocos2dx_luacomponent(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_luacomponent_ComponentLua(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

