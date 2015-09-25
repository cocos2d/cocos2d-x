#ifndef __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__
#define __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

#include "extension/lua_cocos2dx_extension_manual.h"
#include "cocosbuilder/lua_cocos2dx_cocosbuilder_manual.h"
#include "cocostudio/lua_cocos2dx_coco_studio_manual.hpp"
#include "ui/lua_cocos2dx_ui_manual.hpp"
#include "spine/lua_cocos2dx_spine_manual.hpp"
#include "network/lua_cocos2dx_network_manual.h"
#include "cocosdenshion/lua_cocos2dx_cocosdenshion_manual.h"
#include "3d/lua_cocos2dx_3d_manual.h"
#include "audioengine/lua_cocos2dx_audioengine_manual.h"
#include "physics3d/lua_cocos2dx_physics3d_manual.h"
#include "navmesh/lua_cocos2dx_navmesh_manual.h"


int lua_module_register(lua_State* L)
{
    register_ui_moudle(L);
    //extension module must be registed after ui module
    register_extension_module(L);
    register_cocostudio_module(L);
    register_cocosbuilder_module(L);
    register_spine_module(L);
    register_network_module(L);
    register_cocosdenshion_module(L);
    register_cocos3d_module(L);
    register_audioengine_module(L);
#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
    register_physics3d_module(L);
#endif
    
#if CC_USE_NAVMESH
    register_navmesh_module(L);
#endif
    return 1;
}

#endif  // __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

