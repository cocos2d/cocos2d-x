#ifndef COCOS2DX_SCRIPTING_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_COCOSTUDIO_MANUAL_H
#define COCOS2DX_SCRIPTING_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_COCOSTUDIO_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "cocoa/CCObject.h"

LUA_API int register_all_cocos2dx_studio_manual(lua_State* tolua_S);

struct LuaCocoStudioEventListenerData
{
    cocos2d::CCObject* objTarget;
    int eventType;
    
    LuaCocoStudioEventListenerData(cocos2d::CCObject* _objTarget, int _eventType):objTarget(_objTarget),eventType(_eventType)
    {
    }
};

enum LuaArmatureWrapperEventType
{
    MOVEMENT_EVENT,
    FRAME_EVENT,
    FILE_ASYNC,
};

struct LuaArmatureWrapperEventData
{    
    LuaArmatureWrapperEventType eventType;
    void* eventData;
    
    LuaArmatureWrapperEventData(LuaArmatureWrapperEventType _eventType, void* _eventData):eventType(_eventType),eventData(_eventData)
    {
    }
};

struct LuaArmatureMovementEventData
{
    cocos2d::CCObject* objTarget;
    int movementType;
    std::string movementID;
    
    LuaArmatureMovementEventData(cocos2d::CCObject* _objTarget, int _movementType,const std::string& _movementID):objTarget(_objTarget),movementType(_movementType),movementID(_movementID)
    {
    }
};

struct LuaArmatureFrameEventData
{
    cocos2d::CCObject* objTarget;
    std::string  frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
    
    LuaArmatureFrameEventData( cocos2d::CCObject* _objTarget, const std::string& _frameEventName, int _originFrameIndex, int _currentFrameIndex):objTarget(_objTarget), frameEventName(_frameEventName),originFrameIndex(_originFrameIndex), currentFrameIndex(_currentFrameIndex)
    {
    }
};
#endif //#define COCOS2DX_SCRIPTING_LUA_COCOS2DX_SUPPORT_LUA_COCOS2DX_COCOSTUDIO_MANUAL_H
