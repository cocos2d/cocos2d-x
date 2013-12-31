#ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H
#define COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "LuaScriptHandlerMgr.h"

NS_CC_BEGIN
class LuaEventListenerCustom
{
public:
    static EventListenerCustom* create(const std::string& eventName);
};

class LuaEventListenerAcceleration
{
public:
    static EventListenerAcceleration* create();
};
NS_CC_END

USING_NS_CC;

TOLUA_API int register_all_cocos2dx_manual(lua_State* tolua_S);

TOLUA_API int register_cocos2dx_event_releated(lua_State* tolua_S);

struct LuaEventAccelerationData
{
    void* acc;
    Event* event;
    
    LuaEventAccelerationData(void* inAcc,Event* inEvent)
    :acc(inAcc),event(inEvent)
    {
    }
};

struct LuaEventKeyboarData
{
    int keyCode;
    Event* event;
    
    LuaEventKeyboarData(int inKeyCode,Event* inEvent)
    :keyCode(inKeyCode),event(inEvent)
    {
    }
};

struct LuaEventTouchData
{
    Touch* touch;
    Event* event;
    
    LuaEventTouchData(Touch* inTouch, Event* inEvent)
    :touch(inTouch),
    event(inEvent)
    {
    }
};

struct LuaEventTouchesData
{
    std::vector<Touch*> touches;
    Event* event;
    
    LuaEventTouchesData(std::vector<Touch*> inTouches, Event* inEvent)
    :touches(inTouches),
    event(inEvent)
    {
    }
};

struct LuaEventMouseData
{
    Event* event;
    
    LuaEventMouseData(Event* inEvent)
    :event(inEvent)
    {
    }
};

#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H
