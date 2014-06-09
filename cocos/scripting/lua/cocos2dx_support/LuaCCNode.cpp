//
//  LuaCCNode.cpp
//  quickcocos2dx
//
//  Created by ZhuJunfeng on 14-5-19.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "LuaCCNode.h"
#include "lua_binder.h"
#include "cocos2d.h"

using namespace cocos2d;

static int ltest(lua_State *L)
{
	const char *str = luaL_checklstring(L, 1, NULL);
	printf("entry ccnode.test ---- string: %s\n", str);

	lua_pushstring(L, "test ok!");
	return 1;
}

static int cclass_lua_Cocos2d_CCNode_create00(lua_State* L)
{
	printf("entry ccnode.create ---- \n");
    CCNode* cclua_ret = (CCNode*)  CCNode::create();
    if (!cclua_ret) return 0;
    lua_pushlightuserdata(L , cclua_ret);
    // get metatable for class
    // set metatable for obj

    return 1;
}

static int cclass_lua_Cocos2d_CCNode_setPosition00(lua_State* L)
{
    {
        luaL_checktype(L , 1, LUA_TTABLE);
        lua_pushliteral(L, "udata_");
        lua_gettable(L , 1);
        luaL_checktype(L , -1, LUA_TLIGHTUSERDATA);
        CCNode* self = (CCNode*)  lua_touserdata(L , -1);
        lua_pop(L, 1);
        
//        luaL_checktype(L , 1, LUA_TLIGHTUSERDATA);
//        CCNode* self = (CCNode*)  lua_touserdata(L , 1);
        float x = (float)  luaL_checknumber(L , 2);
        float y = (float)  luaL_checknumber(L,  3);
//        printf("entry ccnode.setPosition ---- %f, %f\n", x, y);
        {
            self->setPosition(x,y);
        }
    }
    return 0;
}

static cclass_method_Reg reg[] = {
    {"test", ltest, "I", "T"},
    {"create", cclass_lua_Cocos2d_CCNode_create00, "CCNodeTest", NULL},
    {"setPosition", cclass_lua_Cocos2d_CCNode_setPosition00, NULL, "CCNodeTest|F|F"},
    {NULL,NULL, NULL, NULL},
};

static const char *super[] = {
    NULL
};

int lua_ccnode_open(lua_State *L)
{
    cclass_runtime_reg(L, reg, super);
	return 1;
}
