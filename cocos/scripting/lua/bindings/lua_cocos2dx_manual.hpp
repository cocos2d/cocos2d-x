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
    ScriptHandlerMgr::HandlerType type;
    
    LuaEventListenerKeyboarData(int inKeyCode,Event* inEvent,ScriptHandlerMgr::HandlerType inType)
    :keyCode(inKeyCode),event(inEvent),type(inType)
    {
    }
};

struct LuaEventListenerTouchData
{
    ScriptHandlerMgr::HandlerType type;
    void* nativeObject;
    Touch* touch;
    Event* event;
    
    LuaEventListenerTouchData(ScriptHandlerMgr::HandlerType inType, void* inNativeObject, Touch* inTouch, Event* inEvent)
    : type(inType),
    nativeObject(inNativeObject),
    touch(inTouch),
    event(inEvent)
    {
    }
};

struct LuaEventListenerTouchesData
{
    ScriptHandlerMgr::HandlerType type;
    void* nativeObject;
    std::vector<Touch*> touches;
    Event* event;
    
    LuaEventListenerTouchesData(ScriptHandlerMgr::HandlerType inType, void* inNativeObject, std::vector<Touch*> inTouches, Event* inEvent)
    : type(inType),
    nativeObject(inNativeObject),
    touches(inTouches),
    event(inEvent)
    {
    }
};

struct LuaEventListenerMouseData
{
    ScriptHandlerMgr::HandlerType type;
    void* nativeObject;
    Event* event;
    
    LuaEventListenerMouseData(ScriptHandlerMgr::HandlerType inType, void* inNativeObject, Event* inEvent)
    : type(inType),
    nativeObject(inNativeObject),
    event(inEvent)
    {
    }
};

#endif // #ifndef COCOS2DX_SCRIPT_LUA_COCOS2DX_SUPPORT_GENERATED_LUA_COCOS2DX_MANUAL_H
