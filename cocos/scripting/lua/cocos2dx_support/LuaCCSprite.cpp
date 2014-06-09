//
//  LuaCCSprite.cpp
//  quickcocos2dx
//
//  Created by ZhuJunfeng on 14-5-20.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "lua_binder.h"
#include "LuaCCSprite.h"
#include "cocos2d.h"

using namespace cocos2d;

static int cclass_lua_Cocos2d_CCSprite_create01(lua_State* L)
{
    const char* pszFileName = ((const char*)  luaL_checkstring(L,1));
    {
        CCSprite* cclua_ret = (CCSprite*)  CCSprite::create(pszFileName);
        if (!cclua_ret) return 0;
        lua_pushlightuserdata(L , cclua_ret);
    }
    return 1;
}
static cclass_method_Reg reg[] = {
    {"create", cclass_lua_Cocos2d_CCSprite_create01, "CCSpriteTest", "T"},
    {NULL,NULL, NULL, NULL},
};

static const char *super[] = {
    "CCNodeTest",
    NULL
};

int lua_ccsprite_open(lua_State *L)
{
    cclass_runtime_reg(L, reg, super);
	return 1;
}
