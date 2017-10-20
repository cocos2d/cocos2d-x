/****************************************************************************
 Copyright (c) 2017 Chukong Technologies Inc.
 
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
#include "lua_dragonbones_manual.hpp"

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "base/CCEventListenerFocus.h"

#include "dragonbones/cocos2dx/CCArmatureDisplay.h"
#include "dragonbones/cocos2dx/CCFactory.h"

/*************************************************
 extend AnimationState
 *************************************************/

static int lua_AnimationState_timeScale_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'timeScale' is accessed with AnimationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->timeScale);
    return 1;
}

static int lua_AnimationState_timeScale_set(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'timeScale' is not accessed with Slot\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isnumber(L, 2))
        {
            luaL_error(L, "set 'timeScale' without a number\n");
            return 0;
        }
        
        float value = lua_tonumber(L, 2);
        self->timeScale = value;
        
        return 0;
    }
    else
    {
        luaL_error(L, "set 'timeScale' without wrong number parameters, expected 1 parameter, recieved %d\n", argc);
        return 0;
    }
}

static int lua_AnimationState_weight_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'weight' is accessed with AnimationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->timeScale);
    return 1;
}

static int lua_AnimationState_weight_set(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'weight' is not accessed with AnmationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isnumber(L, 2))
        {
            luaL_error(L, "set 'weight' without a number\n");
            return 0;
        }
        
        float value = lua_tonumber(L, 2);
        self->weight = value;
        
        return 0;
    }
    else
    {
        luaL_error(L, "set 'weight' without wrong number parameters, expected 1 parameter, recieved %d\n", argc);
        return 0;
    }
}

static int lua_AnimationState_autoFadeOutTime_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'autoFadeOutTime' is accessed with AnimationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->autoFadeOutTime);
    return 1;
}

static int lua_AnimationState_autoFadeOutTime_set(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'autoFadeOutTime' is not accessed with AnimationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isnumber(L, 2))
        {
            luaL_error(L, "set 'autoFadeOutTime' without a number\n");
            return 0;
        }
        
        float value = lua_tonumber(L, 2);
        self->autoFadeOutTime = value;
        
        return 0;
    }
    else
    {
        luaL_error(L, "set 'autoFadeOutTime' without wrong number parameters, expected 1 parameter, recieved %d\n", argc);
        return 0;
    }
}

static int lua_AnimationState_fadeTotalTime_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'fadeTotalTime' is accessed with AnimationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->fadeTotalTime);
    return 1;
}

static int lua_AnimationState_fadeTotalTime_set(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.AnimationState",0,&tolua_err))
    {
        tolua_error(L,"'fadeTotalTime' is not accessed with AnimationState\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::AnimationState*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isnumber(L, 2))
        {
            luaL_error(L, "set 'fadeTotalTime' without a number\n");
            return 0;
        }
        
        float value = lua_tonumber(L, 2);
        self->fadeTotalTime = value;
        
        return 0;
    }
    else
    {
        luaL_error(L, "set 'fadeTotalTime' without wrong number parameters, expected 1 parameter, recieved %d\n", argc);
        return 0;
    }
}

static void extendAnimationState(lua_State* L)
{
    lua_pushstring(L, "ccdb.AnimationState");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_variable(L, "timeScale", lua_AnimationState_timeScale_get, lua_AnimationState_timeScale_set);
        tolua_variable(L, "weight", lua_AnimationState_weight_get, lua_AnimationState_weight_set);
        tolua_variable(L, "autoFadeOutTime", lua_AnimationState_autoFadeOutTime_get, lua_AnimationState_autoFadeOutTime_set);
        tolua_variable(L, "fadeTotalTime", lua_AnimationState_fadeTotalTime_get, lua_AnimationState_fadeTotalTime_set);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend Slot
 *************************************************/

static int lua_Slot_displayController_set(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Slot",0,&tolua_err))
    {
        tolua_error(L,"'displayController' is not accessed with Slot\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Slot*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isstring(L, 2))
        {
            luaL_error(L, "set 'displayController' without a string\n");
            return 0;
        }
        
        const char* value = lua_tostring(L, 2);
        self->displayController = value;
        
        return 0;
    }
    else
    {
        luaL_error(L, "set 'displayController' without wrong number parameters, expected 1 parameter, recieved %d\n", argc);
        return 0;
    }
}

static int lua_Slot_displayController_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Slot",0,&tolua_err))
    {
        tolua_error(L,"'displayController' is accessed with Slot\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Slot*>(tolua_tousertype(L,1,0));
    lua_pushstring(L, self->displayController.c_str());
    return 1;
}

static void extendSlot(lua_State* L)
{
    lua_pushstring(L, "ccdb.Slot");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_variable(L, "displayController", lua_Slot_displayController_get, lua_Slot_displayController_set);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend Armature
 *************************************************/

static int lua_Armature_getAnimation(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Armature",0,&tolua_err))
    {
        tolua_error(L,"'getAnimation' is not executed with Armature\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Armature*>(tolua_tousertype(L,1,0));
    object_to_luaval(L, "ccdb.Animation", self->_animation);
    return 1;
}

static int lua_Armature_getDisplay(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Armature",0,&tolua_err))
    {
        tolua_error(L,"'getDisplay' is not executed with Armature\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Armature*>(tolua_tousertype(L,1,0));
    object_to_luaval(L, "ccdb.CCArmatureDisplay", static_cast<dragonBones::CCArmatureDisplay*>(self->getDisplay()));
    
    return 1;
}

static void extendArmature(lua_State* L)
{
    lua_pushstring(L, "ccdb.Armature");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "getAnimation", lua_Armature_getAnimation);
        tolua_function(L, "getDisplay", lua_Armature_getDisplay);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend EventObject
 *************************************************/

static int lua_EventObject_START_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::START);
    return 1;
}

static int lua_EventObject_LOOP_COMPLETE_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::LOOP_COMPLETE);
    return 1;
}

static int lua_EventObject_COMPLETE_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::COMPLETE);
    return 1;
}

static int lua_EventObject_FADE_IN_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::FADE_IN);
    return 1;
}

static int lua_EventObject_FADE_IN_COMPLETE_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::FADE_IN_COMPLETE);
    return 1;
}

static int lua_EventObject_FADE_OUT_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::FADE_OUT);
    return 1;
}

static int lua_EventObject_FADE_OUT_COMPLETE_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::FADE_OUT_COMPLETE);
    return 1;
}

static int lua_EventObject_FRAME_EVENT_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::FRAME_EVENT);
    return 1;
}

static int lua_EventObject_SOUND_EVENT_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushstring(L, dragonBones::EventObject::SOUND_EVENT);
    return 1;
}

static int lua_EventObject_type_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.EventObject",0,&tolua_err))
    {
        tolua_error(L,"'type' is not executed with EventObject\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::EventObject*>(tolua_tousertype(L,1,0));
    lua_pushstring(L, self->type.c_str());
    return 1;
}

static int lua_EventObject_armature_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.EventObject",0,&tolua_err))
    {
        tolua_error(L,"'armature' is not executed with EventObject\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::EventObject*>(tolua_tousertype(L,1,0));
    object_to_luaval(L, "ccdb.Armature", self->armature);
    return 1;
}

static int lua_EventObject_animationState_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.EventObject",0,&tolua_err))
    {
        tolua_error(L,"'animationState' is not executed with EventObject\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::EventObject*>(tolua_tousertype(L,1,0));
    object_to_luaval(L, "ccdb.AnimationState", self->animationState);
    return 1;
}

static void extendEventObject(lua_State* L)
{
    lua_pushstring(L, "ccdb.EventObject");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        // class variables
        tolua_variable(L, "START", lua_EventObject_START_get, NULL);
        tolua_variable(L, "LOOP_COMPLETE", lua_EventObject_LOOP_COMPLETE_get, NULL);
        tolua_variable(L, "COMPLETE", lua_EventObject_COMPLETE_get, NULL);
        tolua_variable(L, "FADE_IN", lua_EventObject_FADE_IN_get, NULL);
        tolua_variable(L, "FADE_IN_COMPLETE", lua_EventObject_FADE_IN_COMPLETE_get, NULL);
        tolua_variable(L, "FADE_OUT", lua_EventObject_FADE_IN_COMPLETE_get, NULL);
        tolua_variable(L, "FADE_OUT_COMPLETE", lua_EventObject_FADE_OUT_COMPLETE_get, NULL);
        tolua_variable(L, "FRAME_EVENT", lua_EventObject_FRAME_EVENT_get, NULL);
        tolua_variable(L, "SOUND_EVENT", lua_EventObject_SOUND_EVENT_get, NULL);
        
        // member variables
        tolua_variable(L, "type", lua_EventObject_type_get, NULL);
        tolua_variable(L, "armature", lua_EventObject_armature_get, NULL);
        tolua_variable(L, "animationState", lua_EventObject_animationState_get, NULL);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend CCArmatureDisplay
 *************************************************/

static int lua_CCArmatureDisplay_addEvent(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.CCArmatureDisplay",0,&tolua_err))
    {
        tolua_error(L,"'addEvent' is not executed with CCArmatureDisplay\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::CCArmatureDisplay*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (2 == argc)
    {
        if (!lua_isstring(L, 2))
        {
            luaL_error(L, "'addEvent' second parameter is not a string\n");
            return 0;
        }
        
        if (!toluafix_isfunction(L,3,"LUA_FUNCTION",0,&tolua_err))
        {
            luaL_error(L, "'addEvent' first parameter is not a function\n");
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,3,0));
        const char* key = lua_tostring(L, 2);
        self->addEvent(key, [=](dragonBones::EventObject* event)
        {
            auto stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            object_to_luaval(L, "ccdb.EventObject", event);
            stack->executeFunctionByHandler(handler, 1);
            stack->clean();
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        
        return 0;
    }
    else
    {
        luaL_error(L, "'addEvent' function of CCArmatureDisplay has wrong number of arguments: %d, was expecting %d\n", argc, 1);
        return 0;
    }
}

static void extendCCArmatureDisplay(lua_State* L)
{
    lua_pushstring(L, "ccdb.CCArmatureDisplay");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEvent", lua_CCArmatureDisplay_addEvent);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend WorldClock
 *************************************************/

static int lua_WorldClock_clock_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    object_to_luaval(L, "ccdb.WorldClock", &dragonBones::WorldClock::clock);
    return 1;
}

static int lua_WorldClock_add(lua_State* L)
{
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "ccdb.WorldClock", 0, &tolua_err))
    {
        tolua_error(L, "invalid object in function 'lua_creator_dragonbones_WorldClock_add'.", &tolua_err);
        return 0;
    }
    
    auto cobj = (dragonBones::WorldClock*)tolua_tousertype(L, 1, 0);

    int argc = lua_gettop(L) - 1;
    if (argc == 1)
    {
        dragonBones::Armature* arg0;
        
        bool ok = luaval_to_object(L, 2, "ccdb.Armature",&arg0, "ccdb.WorldClock:add");
        if(!ok)
        {
            tolua_error(L, "invalid arguments in function 'lua_creator_dragonbones_WorldClock_add'", nullptr);
            return 0;
        }
        cobj->add(arg0);
        lua_settop(L, 1);
        return 0;
    }
    else
    {
        luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.WorldClock:add", argc, 1);
        return 0;
    }
}

static int lua_WorldClock_remove(lua_State* L)
{
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "ccdb.WorldClock", 0, &tolua_err))
    {
        tolua_error(L, "invalid object in function 'lua_creator_dragonbones_WorldClock_remove'.", &tolua_err);
        return 0;
    }
    
    auto cobj = (dragonBones::WorldClock*)tolua_tousertype(L, 1, 0);
    
    int argc = lua_gettop(L) - 1;
    if (argc == 1)
    {
        dragonBones::Armature* arg0;
        
        bool ok = luaval_to_object(L, 2, "ccdb.Armature",&arg0, "ccdb.WorldClock:remove");
        if(!ok)
        {
            tolua_error(L, "invalid arguments in function 'lua_creator_dragonbones_WorldClock_remove'", nullptr);
            return 0;
        }
        cobj->remove(arg0);
        lua_settop(L, 1);
        return 0;
    }
    else
    {
        luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "ccdb.WorldClock:remove", argc, 1);
        return 0;
    }
}

static void extendWorldClock(lua_State* L)
{
    lua_pushstring(L, "ccdb.WorldClock");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_variable(L, "clock", lua_WorldClock_clock_get, NULL);
        tolua_function(L, "add", lua_WorldClock_add);
        tolua_function(L, "remove", lua_WorldClock_remove);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend Bone
 *************************************************/

static int lua_Bone_global_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Bone",0,&tolua_err))
    {
        tolua_error(L,"'global' is accessed with Bone\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Bone*>(tolua_tousertype(L,1,0));
    object_to_luaval(L, "ccdb.Transform", &self->global);
    return 1;
}

static void extendBone(lua_State* L)
{
    lua_pushstring(L, "ccdb.Bone");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_variable(L, "global", lua_Bone_global_get, NULL);
    }
    lua_pop(L, 1);
}

/*************************************************
 extend Transform
 *************************************************/

static int lua_Transform_x_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Transform",0,&tolua_err))
    {
        tolua_error(L,"'x' is accessed with Transform\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Transform*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->x);
    return 1;
}

static int lua_Transform_y_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Transform",0,&tolua_err))
    {
        tolua_error(L,"'y' is accessed with Transform\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Transform*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->y);
    return 1;
}

static int lua_Transform_skewX_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Transform",0,&tolua_err))
    {
        tolua_error(L,"'skewX' is accessed with Transform\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Transform*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->skewX);
    return 1;
}

static int lua_Transform_skewY_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Transform",0,&tolua_err))
    {
        tolua_error(L,"'skewY' is accessed with Transform\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Transform*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->skewY);
    return 1;
}

static int lua_Transform_scaleX_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Transform",0,&tolua_err))
    {
        tolua_error(L,"'scaleX' is accessed with Transform\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Transform*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->scaleX);
    return 1;
}

static int lua_Transform_scaleY_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccdb.Transform",0,&tolua_err))
    {
        tolua_error(L,"'scaleY' is accessed with Transform\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Transform*>(tolua_tousertype(L,1,0));
    lua_pushnumber(L, self->scaleY);
    return 1;
}

static void extendTransform(lua_State* L)
{
    lua_pushstring(L, "ccdb.Transform");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_variable(L, "x", lua_Transform_x_get, NULL);
        tolua_variable(L, "y", lua_Transform_y_get, NULL);
        tolua_variable(L, "skewX", lua_Transform_skewX_get, NULL);
        tolua_variable(L, "skewY", lua_Transform_skewY_get, NULL);
        tolua_variable(L, "scaleX", lua_Transform_scaleX_get, NULL);
        tolua_variable(L, "scaleY", lua_Transform_scaleY_get, NULL);
    }
    lua_pop(L, 1);
}

/*************************************************
 register AnimationFadeOutMode
 *************************************************/
static int lua_AnimationFadeOutMode_None_get(lua_State* L)
{
    if (nullptr == L)
        return 0;

    lua_pushnumber(L, static_cast<int>(dragonBones::AnimationFadeOutMode::None));
    return 1;
}

static int lua_AnimationFadeOutMode_SameLayer_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushnumber(L, static_cast<int>(dragonBones::AnimationFadeOutMode::SameLayer));
    return 1;
}

static int lua_AnimationFadeOutMode_SameGroup_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushnumber(L, static_cast<int>(dragonBones::AnimationFadeOutMode::SameGroup));
    return 1;
}

static int lua_AnimationFadeOutMode_SameLayerAndGroup_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushnumber(L, static_cast<int>(dragonBones::AnimationFadeOutMode::SameLayerAndGroup));
    return 1;
}

static int lua_AnimationFadeOutMode_All_get(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    lua_pushnumber(L, static_cast<int>(dragonBones::AnimationFadeOutMode::All));
    return 1;
}


static void lua_register_creator_dragonbones_AnimationFadeOutMode(lua_State* L)
{
    tolua_open(L);
    tolua_module(L,"ccdb",0);
    tolua_beginmodule(L,"ccdb");
    
    tolua_usertype(L,"ccdb.AnimationFadeOutMode");
    tolua_cclass(L,"AnimationFadeOutMode","ccdb.AnimationFadeOutMode", "" ,nullptr);
    
    tolua_beginmodule(L,"AnimationFadeOutMode");
    tolua_variable(L, "None", lua_AnimationFadeOutMode_None_get, NULL);
    tolua_variable(L, "SameLayer", lua_AnimationFadeOutMode_SameLayer_get, NULL);
    tolua_variable(L, "SameGroup", lua_AnimationFadeOutMode_SameGroup_get, NULL);
    tolua_variable(L, "SameLayerAndGroup", lua_AnimationFadeOutMode_SameLayerAndGroup_get, NULL);
    tolua_variable(L, "All", lua_AnimationFadeOutMode_All_get, NULL);
    tolua_endmodule(L);
    
    std::string typeName = typeid(dragonBones::AnimationFadeOutMode).name();
    g_luaType[typeName] = "ccdb.AnimationFadeOutMode";
    g_typeCast["AnimationFadeOutMode"] = "ccdb.AnimationFadeOutMode";
    
    tolua_endmodule(L);
}

int register_all_creator_dragonbones_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendCCArmatureDisplay(L);
    extendEventObject(L);
    extendArmature(L);
    extendSlot(L);
    extendAnimationState(L);
    extendWorldClock(L);
    extendBone(L);
    extendTransform(L);
    
    lua_register_creator_dragonbones_AnimationFadeOutMode(L);

    return 0;
}
