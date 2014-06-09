#include <lua.h>
#include <lauxlib.h>

#include "lua_binder.h"
#include <stdio.h>

#define CCLASS_REG_TABLE_NAME "QUICKX_CCLASS_REG_FUNC"

static lua_State* m_LuaState = NULL;

#ifndef WIN32
#include <dlfcn.h>
static void *mh_main_sym = NULL;

static int lopensym (lua_State *L)
{
	printf("entry lua_binder.lopensym ---- \n");
    if (mh_main_sym) {
        return 0;
    }
    mh_main_sym = dlopen(NULL, RTLD_NOW);
    if (!mh_main_sym) {
        lua_pushstring(L , dlerror());
        return 1;
    }
	printf("lua_binder.lopensym ---- return ok\n");
    return 0;
}

static int lclosesym (lua_State *L)
{
    if (mh_main_sym) {
        dlclose(mh_main_sym);
        mh_main_sym = NULL;
    }
    return 0;
}

static int lgetsym(lua_State *L)
{
    void *symbol = NULL;
	const char *symbol_name = luaL_checklstring(L, 1, NULL);
    
    if (!mh_main_sym) {
        lua_pushnil(L);
        lua_pushstring(L , "symbol handle had been closed");
        return 2;
    }
    symbol = dlsym(mh_main_sym, symbol_name);
    if (!symbol) {
        lua_pushnil(L);
        lua_pushstring(L , dlerror());
        return 2;
    }
    lua_pushlightuserdata(L , symbol);
    return 1;
}
#endif //WIN32

static int lload(lua_State *L)
{
    int rn;
    lua_CFunction func;
	int top = lua_gettop(L);
	//check classname
	const char *classname = luaL_checklstring(L, 1, NULL);
	printf("entry lua_binder.load ---- classname: %s\n", classname);
	//check table
    // luaL_checktype(L, 2, LUA_TTABLE);
    
    //get registered function of classname
	lua_getglobal(L, CCLASS_REG_TABLE_NAME);
	lua_pushstring(L, classname);
    lua_gettable(L, -2);
    if (!lua_iscfunction(L, -1)) {
    	//return error msg
        lua_settop(L,top);
        lua_pushnil(L);
        lua_pushstring(L, "class not found");
        return 2;
    }
    func = lua_tocfunction(L, -1);
    lua_settop(L,top);
    
    // lua_pushvalue(L, 2);
    // call registered function of classname
    rn = func(L);
    // if ok, return a table
    if (1==rn) {
        // lua_remove(L, -2);
        return 1;
    }
    else{
        lua_settop(L,top);
        lua_pushnil(L);
        lua_pushstring(L, "class load error");
        return 2;
    }
}

int luabinderload(const char * classname)
{
    printf("lua_binder_load(%s)\n", classname);
    if (!m_LuaState || !classname) {
        return -1;
    }
	lua_pushstring(m_LuaState, classname);
    lload(m_LuaState);
    
    return 1;
}

int lua_binder_open(lua_State *L)
{
	luaL_Reg l[] = {
		{"load", lload},
#ifndef WIN32
		{"opensym", lopensym},
		{"closesym", lclosesym},
		{"getsym", lgetsym},
#endif //WIN32
//        {"ffi_load", lua_binder_load},
		{NULL,NULL},
	};
	luaL_openlib(L, "lua_binder", l, 0);
    m_LuaState = L;
	return 1;
}

void cclass_open(lua_State *L)
{
	int top = lua_gettop(L);

	lua_getglobal(L, CCLASS_REG_TABLE_NAME);
	if (!lua_istable(L, -1)) {
		lua_newtable(L);
		lua_setglobal(L, CCLASS_REG_TABLE_NAME);
	}

	lua_settop(L,top);
}

int cclass_reg(lua_State *L, const char *classname, lua_CFunction regfunc)
{
	cclass_open(L);
	lua_getglobal(L, CCLASS_REG_TABLE_NAME);
	lua_pushstring(L, classname);
//	lua_pushlightuserdata(L, regfunc);
	lua_pushcfunction(L, regfunc);
	lua_settable(L, -3);
	lua_pop(L, 1);

	return 1;
}

void cclass_runtime_reg(lua_State *L, cclass_method_Reg reg[], const char *super[])
{
    int n;
	lua_newtable(L);
    // register methods
	n = 0;
	while (reg[n].name && reg[n].func) {
		lua_pushstring(L, reg[n].name);
		lua_newtable(L);
		lua_pushstring(L, "cfunc");
		lua_pushcfunction(L, reg[n].func);
		lua_settable(L, -3);
        if (reg[n].retType) {
            lua_pushstring(L, "retType");
            lua_pushstring(L , reg[n].retType);
            lua_settable(L, -3);
        }
        if (reg[n].methodSign) {
            lua_pushstring(L , "methodSign");
            lua_pushstring(L , reg[n].methodSign);
            lua_settable(L, -3);
        }
		lua_settable(L, -3);
		n++;
	}
    // register super class
    if (super) {
        lua_pushstring(L, "cclass_super");
        lua_newtable(L);
        n = 0;
        while (super[n]) {
            lua_pushinteger(L , n+1 );
            lua_pushstring(L, super[n]);
            lua_settable(L, -3);
            n++;
        }
        lua_settable(L, -3);
    }
}