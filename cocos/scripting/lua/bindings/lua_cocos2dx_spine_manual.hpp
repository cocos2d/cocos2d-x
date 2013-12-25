#ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_SPINE_MANUAL_H
#define COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_SPINE_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "CCObject.h"

TOLUA_API int register_all_cocos2dx_spine_manual(lua_State* L);


#endif // #ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_SPINE_MANUAL_H
