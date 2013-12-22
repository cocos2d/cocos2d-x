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

struct LuaEventListenerAccelerationData
{
    void* acc;
    Event* event;
    
    LuaEventListenerAccelerationData(void* inAcc,Event* inEvent)
    :acc(inAcc),event(inEvent)
    {
    }
};

struct LuaEventListenerKeyboarData
{
    enum class KeyboardStatus :int
    {
        PRESSED = 0,
        RELEASE,
    };
    int keyCode;
    Event* event;
    KeyboardStatus status;
    
    LuaEventListenerKeyboarData(int inKeyCode,Event* inEvent,KeyboardStatus inStatus)
    :keyCode(inKeyCode),event(inEvent),status(inStatus)
    {
    }
};

struct LuaEventListenerTouchData
{
    EventTouch::EventCode eventCode;
    void* nativeObject;
    Touch* touch;
    Event* event;
    
    LuaEventListenerTouchData(EventTouch::EventCode inEventCode, void* inNativeObject, Touch* inTouch, Event* inEvent)
    : eventCode(inEventCode),
    nativeObject(inNativeObject),
    touch(inTouch),
    event(inEvent)
    {
    }
};

struct LuaEventListenerTouchesData
{
    EventTouch::EventCode eventCode;
    void* nativeObject;
    std::vector<Touch*> touches;
    Event* event;
    
    LuaEventListenerTouchesData(EventTouch::EventCode inEventCode, void* inNativeObject, std::vector<Touch*> inTouches, Event* inEvent)
    : eventCode(inEventCode),
    nativeObject(inNativeObject),
    touches(inTouches),
    event(inEvent)
    {
    }
};

struct LuaEventListenerMouseData
{
    EventMouse::MouseEventType eventType;
    void* nativeObject;
    Event* event;
    
    LuaEventListenerMouseData(EventMouse::MouseEventType inEventType, void* inNativeObject, Event* inEvent)
    : eventType(inEventType),
    nativeObject(inNativeObject),
    event(inEvent)
    {
    }
};

#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H
