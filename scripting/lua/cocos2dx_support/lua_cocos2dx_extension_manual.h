#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_EXTENSION_MANUAL_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_EXTENSION_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int register_all_cocos2dx_extension_manual(lua_State* tolua_S);
TOLUA_API int register_cocos2dx_extension_CCBProxy(lua_State* tolua_S);

struct LuaTableViewEventData
{
    int   eventType;
    void* value;
    
    // Constructor
    LuaTableViewEventData(int _eventType,void* _value = nullptr)
    : eventType(_eventType),value(_value)
    {
    }
};

#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_EXTENSION_MANUAL_H
