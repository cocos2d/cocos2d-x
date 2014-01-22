/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
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
