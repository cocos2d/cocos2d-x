#ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_GUI_MANUAL_H
#define COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_GUI_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "CCObject.h"

TOLUA_API int register_all_cocos2dx_gui_manual(lua_State* L);

struct LuaStudioEventListenerData
{
    cocos2d::Object* objTarget;
    int eventType;
    
    LuaStudioEventListenerData(cocos2d::Object* _objTarget, int _eventType):objTarget(_objTarget),eventType(_eventType)
    {
    }
};
#endif // #ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_GUI_MANUAL_H
