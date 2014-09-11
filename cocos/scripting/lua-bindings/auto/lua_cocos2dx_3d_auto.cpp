#include "lua_cocos2dx_3d_auto.hpp"
#include "cocos3d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


TOLUA_API int register_all_cocos2dx_3d(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");


	tolua_endmodule(tolua_S);
	return 1;
}

