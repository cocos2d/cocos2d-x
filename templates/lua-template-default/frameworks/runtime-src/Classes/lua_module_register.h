#ifndef __LUA_TEMPLATE_RUNTIME_FRAMEWORKS_RUNTIME_SRC_CLASSES_LUA_MODULE_REGISTER_H__
#define __LUA_TEMPLATE_RUNTIME_FRAMEWORKS_RUNTIME_SRC_CLASSES_LUA_MODULE_REGISTER_H__

#include "cocosdenshion/lua_cocos2dx_cocosdenshion_manual.h"
#include "network/lua_cocos2dx_network_manual.h"
#include "cocosbuilder/lua_cocos2dx_cocosbuilder_manual.h"
#include "cocostudio/lua_cocos2dx_coco_studio_manual.hpp"
#include "extension/lua_cocos2dx_extension_manual.h"
#include "ui/lua_cocos2dx_ui_manual.hpp"
#include "spine/lua_cocos2dx_spine_manual.hpp"
#include "3d/lua_cocos2dx_3d_manual.h"
#include "audioengine/lua_cocos2dx_audioengine_manual.h"

static int lua_module_register(lua_State* L)
{
    //Dont' change the module register order unless you know what your are doing
    register_cocosdenshion_module(L);
    register_network_module(L);
    register_cocosbuilder_module(L);
    register_cocostudio_module(L);
    register_ui_moudle(L);
    register_extension_module(L);
    register_spine_module(L);
    register_cocos3d_module(L);
    register_audioengine_module(L);
    return 1;
}

#endif  // __LUA_TEMPLATE_RUNTIME_FRAMEWORKS_RUNTIME_SRC_CLASSES_LUA_MODULE_REGISTER_H__

