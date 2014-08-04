#ifndef __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__
#define __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

#include "network/lua_cocos2dx_network_manual.h"
#include "lua_cocos2dx_cocosdenshion_auto.hpp"


int lua_module_register(lua_State* L)
{
    register_network_module(L);
    register_all_cocos2dx_cocosdenshion(L);
    return 1;
}

#endif  // __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

