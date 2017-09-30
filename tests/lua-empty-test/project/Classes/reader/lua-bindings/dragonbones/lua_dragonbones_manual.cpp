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
        tolua_error(L,"'Slot::displayController=' is not executed with Slot\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Slot*>(tolua_tousertype(L,1,0));
    
    int argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
        if (!lua_isstring(L, 2))
        {
            luaL_error(L, "'Slot::displayController=' first parameter is not a string\n");
            return 0;
        }
        
        const char* value = lua_tostring(L, 2);
        self->displayController = value;
        
        return 1;
    }
    else
    {
        luaL_error(L, "'Slot::displayController=' has wrong number of arguments: %d, was expecting 1\n", argc);
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
        tolua_error(L,"'addEvent' is not executed with Slot\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Armature*>(tolua_tousertype(L,1,0));
    object_to_luaval<dragonBones::Animation>(L, "ccdb.Slot", self->_animation);
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
        tolua_error(L,"'addEvent' is not executed with Armature\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::Armature*>(tolua_tousertype(L,1,0));
    object_to_luaval<dragonBones::Animation>(L, "ccdb.Animation", self->_animation);
    return 1;
}

static void extendArmature(lua_State* L)
{
    lua_pushstring(L, "ccdb.Armature");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "getAnimation", lua_Armature_getAnimation);
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
        tolua_error(L,"'addEvent' is not executed with EventObject\n", NULL);
        return 0;
    }
    
    auto self = static_cast<dragonBones::EventObject*>(tolua_tousertype(L,1,0));
    lua_pushstring(L, self->type.c_str());
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
            //stack->pushObject(event, "dragonbones.EventObject");
            tolua_pushusertype_and_addtoroot(L, event, "ccdb.EventObject");
            stack->executeFunctionByHandler(handler, 1);
            stack->clean();
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        
        return 1;
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

int register_all_creator_dragonbones_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendCCArmatureDisplay(L);
    extendEventObject(L);
    extendArmature(L);
    extendSlot(L);

    return 0;
}
