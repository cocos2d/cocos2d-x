#ifndef __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__
#define __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

#include "audioengine/lua_cocos2dx_audioengine_manual.h"


int lua_module_register(lua_State* L)
{
    register_audioengine_module(L);
    return 1;
}

#endif  // __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

