#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_DEPRECATED_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_DEPRECATED_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int register_all_cocos2dx_deprecated(lua_State* tolua_S);
TOLUA_API int register_all_cocos2dx_manual_deprecated(lua_State* tolua_S);

#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_DEPRECATED_H
