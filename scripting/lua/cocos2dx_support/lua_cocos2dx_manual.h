#ifndef COCOS2DX_SCRIPTING_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_MANUAL_H
#define COCOS2DX_SCRIPTING_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

LUA_API int register_all_cocos2dx_manual(lua_State* tolua_S);

#endif //#ifndef COCOS2DX_SCRIPTING_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_MANUAL_H
