#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_EXTENSION_MANUAL_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_EXTENSION_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "LuaScriptHandlerMgr.h"

TOLUA_API int register_all_cocos2dx_extension_manual(lua_State* tolua_S);
TOLUA_API int register_cocos2dx_extension_CCBProxy(lua_State* tolua_S);

struct LuaTableViewEventData
{
    cocos2d::ScriptHandlerMgr::HandlerType  handlerType;
    void* value;
    
    // Constructor
    LuaTableViewEventData(cocos2d::ScriptHandlerMgr::HandlerType _handleType,void* _value = nullptr)
    : handlerType(_handleType),value(_value)
    {
    }
};

struct LuaAssetsManagerEventData
{
    cocos2d::ScriptHandlerMgr::HandlerType handlerType;
    int value;
    
    LuaAssetsManagerEventData(cocos2d::ScriptHandlerMgr::HandlerType _handleType, int _value = 0):handlerType(_handleType),value(_value)
    {
    }
};


#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_EXTENSION_MANUAL_H
