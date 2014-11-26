
#ifndef __PLAYERLUACORE_H_
#define __PLAYERLUACORE_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "tolua_fix.h"

TOLUA_API int luaopen_PlayerLuaCore(lua_State* tolua_S);

#endif // __PLAYERLUACORE_H_
