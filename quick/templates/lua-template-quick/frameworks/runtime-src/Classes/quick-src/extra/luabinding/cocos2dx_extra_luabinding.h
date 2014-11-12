
#ifndef __COCOS2DX_EXTRA_LUABINDING_H_
#define __COCOS2DX_EXTRA_LUABINDING_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "tolua_fix.h"

TOLUA_API int luaopen_cocos2dx_extra_luabinding(lua_State* tolua_S);

#endif // __COCOS2DX_EXTRA_LUABINDING_H_
