
#ifndef COCOS2DX_SCRIPT_LUA_ANYSDK_MANUAL_H
#define COCOS2DX_SCRIPT_LUA_ANYSDK_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_anysdk_manual(lua_State* tolua_S);

#endif // #ifndef COCOS2DX_SCRIPT_LUA_ANYSDK_MANUAL_H
