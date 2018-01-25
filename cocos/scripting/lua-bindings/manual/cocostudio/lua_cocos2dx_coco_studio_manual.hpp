/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "base/CCRef.h"
#include <string>

TOLUA_API int  register_all_cocos2dx_coco_studio_manual(lua_State* L);

/**
 * @addtogroup lua
 * @{
 */

/**
 * Call this function can import the lua bindings for the coco studio module.
 * After registering, we could call the related coco studio code conveniently in the lua.
 * If you don't want to use the coco studio module in the lua, you only don't call this registering function.
 * If you don't register the coco studio module, the package size would become smaller .
 * The current mechanism,this registering function is called in the lua_module_register.h
 */
TOLUA_API int  register_cocostudio_module(lua_State* L);

// end group
/// @}

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
    cocos2d::Ref* objTarget;
    int movementType;
    std::string movementID;
    
    LuaArmatureMovementEventData(cocos2d::Ref* _objTarget, int _movementType,const std::string& _movementID):objTarget(_objTarget),movementType(_movementType),movementID(_movementID)
    {
    }
};

struct LuaArmatureFrameEventData
{
    cocos2d::Ref* objTarget;
    std::string  frameEventName;
    int originFrameIndex;
    int currentFrameIndex;
    
    LuaArmatureFrameEventData( cocos2d::Ref* _objTarget, const std::string& _frameEventName, int _originFrameIndex, int _currentFrameIndex):objTarget(_objTarget), frameEventName(_frameEventName),originFrameIndex(_originFrameIndex), currentFrameIndex(_currentFrameIndex)
    {
    }
};

#endif // #ifndef COCOS_SCRIPTING_LUA_BINDINGS_LUA_COCOS2DX_COCO_STUDIO_MANUAL_H
