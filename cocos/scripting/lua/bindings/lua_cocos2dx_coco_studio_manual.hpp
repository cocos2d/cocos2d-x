#ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_COCO_STUDIO_MANUAL_H
#define COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_COCO_STUDIO_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "CCObject.h"

TOLUA_API int register_all_cocos2dx_coco_studio_manual(lua_State* L);

struct LuaCocoStudioEventListenerData
{
    cocos2d::Object* objTarget;
    int eventType;
    
    LuaCocoStudioEventListenerData(cocos2d::Object* _objTarget, int _eventType):objTarget(_objTarget),eventType(_eventType)
    {
    }
};

struct LuaArmatureWrapperEventData
{
    enum class LuaArmatureWrapperEventType
    {
        MOVEMENT_EVENT,
        FRAME_EVENT,
        FILE_ASYNC,
    };
    
    LuaArmatureWrapperEventType eventType;
    void* eventData;
    
    LuaArmatureWrapperEventData(LuaArmatureWrapperEventType _eventType, void* _eventData):eventType(_eventType),eventData(_eventData)
    {
    }
};

struct LuaArmatureMovementEventData
{
    cocos2d::Object* objTarget;
    int movementType;
    std::string movementID;
    
    LuaArmatureMovementEventData(cocos2d::Object* _objTarget, int _movementType,const std::string& _movementID):objTarget(_objTarget),movementType(_movementType),movementID(_movementID)
    {
    }
};

struct LuaArmatureFrameEventData
{
    cocos2d::Object* objTarget;
    std::string  frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
    
    LuaArmatureFrameEventData( cocos2d::Object* _objTarget, const std::string& _frameEventName, int _originFrameIndex, int _currentFrameIndex):objTarget(_objTarget), frameEventName(_frameEventName),originFrameIndex(_originFrameIndex), currentFrameIndex(_currentFrameIndex)
    {
    }
};

#endif // #ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_COCO_STUDIO_MANUAL_H
