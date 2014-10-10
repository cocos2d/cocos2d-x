#ifndef COCOS2DX_TEST_LUA_TESTS_PROJECT_CLASSES_LUA_TEST_BINDINGS_H
#define COCOS2DX_TEST_LUA_TESTS_PROJECT_CLASSES_LUA_TEST_BINDINGS_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int register_test_binding(lua_State* tolua_S);

#endif // #ifndef COCOS2DX_TEST_LUA_TESTS_PROJECT_CLASSES_LUA_TEST_BINDINGS_H
