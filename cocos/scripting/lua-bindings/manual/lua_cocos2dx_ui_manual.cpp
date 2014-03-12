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
#include "lua_cocos2dx_ui_manual.hpp"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "ui/CocosGUI.h"
#include "CCLuaEngine.h"

using namespace ui;

class LuaCocoStudioEventListener:public Ref
{
public:
    LuaCocoStudioEventListener();
    virtual ~LuaCocoStudioEventListener();
    
    static LuaCocoStudioEventListener* create();
    
    virtual void eventCallbackFunc(Ref* sender,int eventType);
};

LuaCocoStudioEventListener::LuaCocoStudioEventListener()
{
    
}

LuaCocoStudioEventListener::~LuaCocoStudioEventListener()
{

}

LuaCocoStudioEventListener* LuaCocoStudioEventListener::create()
{
    LuaCocoStudioEventListener* listener = new LuaCocoStudioEventListener();
    if (nullptr == listener)
        return nullptr;
    
    listener->autorelease();
    
    return listener;
}

void LuaCocoStudioEventListener::eventCallbackFunc(Ref* sender,int eventType)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
    
    if (0 != handler)
    {
        LuaStudioEventListenerData eventData(sender,eventType);
        BasicScriptData data(this,(void*)&eventData);
        LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER, (void*)&data);
    }
}

static int lua_cocos2dx_Widget_addTouchEventListener(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Widget* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.Widget",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Widget*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Widget_addTouchEventListener'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "widgetTouchEvent");
        
        self->addTouchEventListener(listener, toucheventselector(LuaCocoStudioEventListener::eventCallbackFunc));
                
        return 0;
    }
    
    CCLOG("'addTouchEventListener' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addTouchEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendWidget(lua_State* L)
{
    lua_pushstring(L, "ccui.Widget");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addTouchEventListener", lua_cocos2dx_Widget_addTouchEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_CheckBox_addEventListenerCheckBox(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    CheckBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.CheckBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CheckBox*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_CheckBox_addEventListenerCheckBox'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "checkBoxEventListener");
        
        self->addEventListenerCheckBox(listener, checkboxselectedeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerCheckBox' function of CheckBox has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerCheckBox'.",&tolua_err);
    return 0;
#endif
}


static void extendCheckBox(lua_State* L)
{
    lua_pushstring(L, "ccui.CheckBox");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerCheckBox", lua_cocos2dx_CheckBox_addEventListenerCheckBox);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_Slider_addEventListenerSlider(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Slider* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.Slider",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Slider*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Slider_addEventListenerSlider'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "sliderEventListener");
        
        self->addEventListenerSlider(listener, sliderpercentchangedselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerSlider' function of Slider has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerSlider'.",&tolua_err);
    return 0;
#endif
}

static void extendSlider(lua_State* L)
{
    lua_pushstring(L, "ccui.Slider");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerSlider", lua_cocos2dx_Slider_addEventListenerSlider);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_TextField_addEventListenerTextField(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    TextField* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.TextField",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<TextField*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_TextField_addEventListenerTextField'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "textfieldEventListener");
        
        self->addEventListenerTextField(listener, textfieldeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerTextField' function of TextField has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerTextField'.",&tolua_err);
    return 0;
#endif
}

static void extendTextField(lua_State* L)
{
    lua_pushstring(L, "ccui.TextField");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerTextField", lua_cocos2dx_TextField_addEventListenerTextField);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_PageView_addEventListenerPageView(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    PageView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.PageView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<PageView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_PageView_addEventListenerPageView'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "pageViewEventListener");
        
        self->addEventListenerPageView(listener, pagevieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerPageView' function of PageView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerPageView'.",&tolua_err);
    return 0;
#endif
}

static void extendPageView(lua_State* L)
{
    lua_pushstring(L, "ccui.PageView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerPageView", lua_cocos2dx_PageView_addEventListenerPageView);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ScrollView_addEventListenerScrollView(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ScrollView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ScrollView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ScrollView_addEventListenerScrollView'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "scrollViewEventListener");
        
        self->addEventListenerScrollView(listener, scrollvieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerScrollView' function of ScrollView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerScrollView'.",&tolua_err);
    return 0;
#endif
}

static void extendScrollView(lua_State* L)
{
    lua_pushstring(L, "ccui.ScrollView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerScrollView", lua_cocos2dx_ScrollView_addEventListenerScrollView);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ListView_addEventListenerListView(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ListView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.ListView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ListView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ListView_addEventListenerListView'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (nullptr == listener)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::STUDIO_EVENT_LISTENER);
        
        __Dictionary* dict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        dict->setObject(listener, "listViewEventListener");
        
        self->addEventListenerListView(listener, listvieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerListView' function of ListView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerListView'.",&tolua_err);
    return 0;
#endif
}

static void extendListView(lua_State* L)
{
    lua_pushstring(L, "ccui.ListView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerListView", lua_cocos2dx_ListView_addEventListenerListView);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_LayoutParameter_setMargin(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    LayoutParameter* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.LayoutParameter",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<LayoutParameter*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_LayoutParameter_setMargin'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        Margin margin;
        lua_pushstring(L, "left");
        lua_gettable(L,2);
        margin.left = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
            
        lua_pushstring(L, "top");
        lua_gettable(L,2);
        margin.top = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
            
        lua_pushstring(L, "right");
        lua_gettable(L,2);
        margin.right = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
            
        lua_pushstring(L, "bottom");
        lua_gettable(L,2);
        margin.bottom = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        self->setMargin(margin);
        return 0;
    }
    
    CCLOG("'setMargin' function of LayoutParameter has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setMargin'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_LayoutParameter_getMargin(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    LayoutParameter* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.LayoutParameter",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<LayoutParameter*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_LayoutParameter_getMargin'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {
        Margin margin = self->getMargin();
        
        lua_newtable(L);
        
        lua_pushstring(L, "left");                             
        lua_pushnumber(L, (lua_Number) margin.left);
        lua_rawset(L, -3);
        
        lua_pushstring(L, "top");                             
        lua_pushnumber(L, (lua_Number) margin.top);
        lua_rawset(L, -3);
        
        lua_pushstring(L, "right");
        lua_pushnumber(L, (lua_Number) margin.right);
        lua_rawset(L, -3);
        
        lua_pushstring(L, "bottom");
        lua_pushnumber(L, (lua_Number) margin.bottom);
        lua_rawset(L, -3);
        
        return 1;
    }
    
    CCLOG("'getMargin' function of LayoutParameter has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'getMargin'.",&tolua_err);
    return 0;
#endif
}

static void extendLayoutParameter(lua_State* L)
{
    lua_pushstring(L, "ccui.LayoutParameter");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setMargin", lua_cocos2dx_LayoutParameter_setMargin);
        tolua_function(L, "getMargin", lua_cocos2dx_LayoutParameter_getMargin);
    }
    lua_pop(L, 1);
}

int register_all_cocos2dx_ui_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendWidget(L);
    extendCheckBox(L);
    extendSlider(L);
    extendTextField(L);
    extendPageView(L);
    extendScrollView(L);
    extendListView(L);
    extendLayoutParameter(L);
    
    return 0;
}
