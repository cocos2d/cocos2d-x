#ifndef __LUA_TEMPLATE_RUNTIME_FRAMEWORKS_RUNTIME_SRC_CLASSES_LUA_MODULE_REGISTER_H__
#define __LUA_TEMPLATE_RUNTIME_FRAMEWORKS_RUNTIME_SRC_CLASSES_LUA_MODULE_REGISTER_H__

#include "cocosdenshion/lua_cocos2dx_cocosdenshion_manual.h"


int lua_module_register(lua_State* L)
{
    register_cocosdenshion_module(L);
    return 1;
}

#endif  // __LUA_TEMPLATE_RUNTIME_FRAMEWORKS_RUNTIME_SRC_CLASSES_LUA_MODULE_REGISTER_H__

