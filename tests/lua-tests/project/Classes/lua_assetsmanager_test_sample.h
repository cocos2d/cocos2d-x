#ifndef COCOS2DX_COCOS_SCRIPTING_LUA_BINDINGS_LUA_ASSETSMANAGER_TEST_SAMPLE_H
#define COCOS2DX_COCOS_SCRIPTING_LUA_BINDINGS_LUA_ASSETSMANAGER_TEST_SAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

/**
 * The apis which are bound in this file are temporary for the assetsmanager test sample.After the completion of some systems like fileutils,these apis will be deprecated
 */
TOLUA_API int register_assetsmanager_test_sample(lua_State* tolua_S);

#endif // #ifndef COCOS2DX_COCOS_SCRIPTING_LUA_BINDINGS_LUA_ASSETSMANAGER_TEST_SAMPLE_H
