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
#include "lua_cocos2dx_ui_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "lua_cocos2dx_experimental_video_auto.hpp"
#include "lua_cocos2dx_experimental_video_manual.hpp"
#include "lua_cocos2dx_experimental_webview_auto.hpp"
#include "lua_cocos2dx_experimental_webview_manual.hpp"
#endif
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "ui/CocosGUI.h"
#include "CCLuaEngine.h"

using namespace ui;

static int handleUIEvent(int handler, cocos2d::Ref* sender, int eventType)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    
    stack->pushObject(sender, "cc.Ref");
    stack->pushInt(eventType);
    
    stack->executeFunctionByHandler(handler, 2);
    stack->clean();
    
    return 0;
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
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addTouchEventListener([=](cocos2d::Ref* ref,Widget::TouchEventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addTouchEventListener' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addTouchEventListener'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Widget_addClickEventListener(lua_State* L)
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
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Widget_addClickEventListener'\n", NULL);
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
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addClickEventListener([=](cocos2d::Ref* sender){
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            stack->pushObject(sender, "cc.Ref");
            stack->executeFunctionByHandler(handler, 1);
            stack->clean();
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addClickEventListener' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addClickEventListener'.",&tolua_err);
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
        tolua_function(L, "addClickEventListener", lua_cocos2dx_Widget_addClickEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_CheckBox_addEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_CheckBox_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addEventListener([=](cocos2d::Ref* ref,CheckBox::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addEventListener' function of CheckBox has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}


static void extendCheckBox(lua_State* L)
{
    lua_pushstring(L, "ccui.CheckBox");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_CheckBox_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_RadioButton_addEventListener(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc = 0;
    RadioButton* self = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
  if (!tolua_isusertype(L,1,"ccui.RadioButton",0,&tolua_err)) goto tolua_lerror;
#endif

    self = static_cast<RadioButton*>(tolua_tousertype(L,1,0));

#if COCOS2D_DEBUG >= 1
  if (nullptr == self) {
    tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_RadioButton_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));

        self->addEventListener([=](RadioButton* radioButton,RadioButton::EventType eventType){
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            stack->pushObject(radioButton, "ccui.RadioButton");
            stack->pushInt((int)eventType);

            stack->executeFunctionByHandler(handler, 2);
            stack->clean();
        });

        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }

    luaL_error(L, "'addEventListener' function of CheckBox has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendRadioButton(lua_State* L)
{
    lua_pushstring(L, "ccui.RadioButton");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_RadioButton_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_RadioButtonGroup_addEventListener(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc = 0;
    RadioButtonGroup* self = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
  if (!tolua_isusertype(L,1,"ccui.RadioButtonGroup",0,&tolua_err)) goto tolua_lerror;
#endif

    self = static_cast<RadioButtonGroup*>(tolua_tousertype(L,1,0));

#if COCOS2D_DEBUG >= 1
  if (nullptr == self) {
    tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_RadioButtonGroup_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));

        self->addEventListener([=](RadioButton* radioButton,int index,RadioButtonGroup::EventType eventType){
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();

            stack->pushObject(radioButton, "ccui.RadioButton");
            stack->pushInt(index);
            stack->pushInt((int)eventType);

            stack->executeFunctionByHandler(handler, 3);
            stack->clean();
        });

        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }

    luaL_error(L, "'addEventListener' function of RadioButtonGroup has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendRadioButtonGroup(lua_State* L)
{
    lua_pushstring(L, "ccui.RadioButtonGroup");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_RadioButtonGroup_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_Slider_addEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Slider_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addEventListener([=](cocos2d::Ref* ref,Slider::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addEventListener' function of Slider has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendSlider(lua_State* L)
{
    lua_pushstring(L, "ccui.Slider");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_Slider_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_TextField_addEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_TextField_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addEventListener([=](cocos2d::Ref* ref,TextField::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addEventListener' function of TextField has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendTextField(lua_State* L)
{
    lua_pushstring(L, "ccui.TextField");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_TextField_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_PageView_addEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_PageView_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addEventListener([=](cocos2d::Ref* ref,PageView::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addEventListener' function of PageView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendPageView(lua_State* L)
{
    lua_pushstring(L, "ccui.PageView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_PageView_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ScrollView_addEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ScrollView_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        self->addEventListener([=](cocos2d::Ref* ref,ScrollView::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        });
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addEventListener' function of ScrollView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendScrollView(lua_State* L)
{
    lua_pushstring(L, "ccui.ScrollView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_ScrollView_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_ListView_addEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ListView_addEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        auto listViewCallback = [=](cocos2d::Ref* ref,ListView::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        };
        self->addEventListener((ui::ListView::ccListViewCallback)listViewCallback);
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addEventListener' function of ListView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_ListView_addScrollViewEventListener(lua_State* L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ListView_addScrollViewEventListener'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        auto scrollViewCallback = [=](cocos2d::Ref* ref, ui::ScrollView::EventType eventType){
            handleUIEvent(handler, ref, (int)eventType);
        };
        self->addEventListener((ui::ScrollView::ccScrollViewCallback)scrollViewCallback);
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 0;
    }
    
    luaL_error(L, "'addScrollViewEventListener' function of ListView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addScrollViewEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendListView(lua_State* L)
{
    lua_pushstring(L, "ccui.ListView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_ListView_addEventListener);
        tolua_function(L, "addScrollViewEventListener", lua_cocos2dx_ListView_addScrollViewEventListener);
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
    
    luaL_error(L, "'setMargin' function of LayoutParameter has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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
    
    luaL_error(L, "'getMargin' function of LayoutParameter has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    
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


static int tolua_cocos2d_EditBox_registerScriptEditBoxHandler(lua_State* L)
{
    if (NULL == L)
        return 0;
    
    int argc = 0;
    EditBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<EditBox*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'tolua_cocos2d_EditBox_registerScriptEditBoxHandler'\n", NULL);
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
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        self->registerScriptEditBoxHandler(handler);
        return 0;
    }
    
    luaL_error(L, "%s function of EditBox  has wrong number of arguments: %d, was expecting %d\n", "ccui.EditBox:registerScriptEditBoxHandler", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'tolua_cocos2d_EditBox_registerScriptEditBoxHandler'.",&tolua_err);
    return 0;
#endif
    
}

static int tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler(lua_State* L)
{
    
    if (NULL == L)
        return 0;
    
    int argc = 0;
    EditBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ccui.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<EditBox*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {
        self->unregisterScriptEditBoxHandler();
        return 0;
    }
    
    luaL_error(L, "%s function of EditBox  has wrong number of arguments: %d, was expecting %d\n", "ccui.EditBox:unregisterScriptEditBoxHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEditBox(lua_State* L)
{
    lua_pushstring(L, "ccui.EditBox");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        lua_pushstring(L,"registerScriptEditBoxHandler");
        lua_pushcfunction(L,tolua_cocos2d_EditBox_registerScriptEditBoxHandler );
        lua_rawset(L,-3);
        lua_pushstring(L,"unregisterScriptEditBoxHandler");
        lua_pushcfunction(L,tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler );
        lua_rawset(L,-3);
    }
    lua_pop(L, 1);
}

int register_all_cocos2dx_ui_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendWidget(L);
    extendCheckBox(L);
    extendRadioButton(L);
    extendRadioButtonGroup(L);
    extendSlider(L);
    extendTextField(L);
    extendPageView(L);
    extendScrollView(L);
    extendListView(L);
    extendLayoutParameter(L);
    extendEditBox(L);

    return 0;
}

static int tolua_cocos2dx_EventListenerFocus_create(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L, 1, "cc.EventListenerFocus", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerFocus* tolua_ret = cocos2d::EventListenerFocus::create();
        if(nullptr == tolua_ret)
            return 0;
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(L, ID, luaID, (void*)tolua_ret,"cc.EventListenerFocus");
        
        return 1;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerFocus:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'tolua_cocos2dx_EventListenerFocus_create'.",&tolua_err);
    return 0;
#endif
}

static void cloneFocusHandler(const EventListenerFocus* src,EventListenerFocus* dst )
{
    if (nullptr == src || nullptr == dst)
        return;
    
    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, ScriptHandlerMgr::HandlerType::EVENT_FOCUS);
    if (0 != handler)
    {
        int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, ScriptHandlerMgr::HandlerType::EVENT_FOCUS);
        dst->onFocusChanged = [=](ui::Widget* widgetLostFocus, ui::Widget* widgetGetFocus){
            lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
            int id = (widgetLostFocus) ? (int)widgetLostFocus->_ID : -1;
            int* luaID = (widgetLostFocus) ? &widgetLostFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(L, id, luaID, (void*)widgetLostFocus,"ccui.Widget");
            id = (widgetGetFocus) ? (int)widgetGetFocus->_ID : -1;
            luaID = (widgetGetFocus) ? &widgetGetFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(L, id, luaID, (void*)widgetGetFocus,"ccui.Widget");
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
    }
}

static int tolua_cocos2dx_EventListenerFocus_clone(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    EventListenerFocus* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.EventListenerFocus", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerFocus*>(tolua_tousertype(L,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'tolua_cocos2dx_EventListenerFocus_clone'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerFocus* tolua_ret = cocos2d::EventListenerFocus::create();
        if(nullptr == tolua_ret)
            return 0;
        
        cloneFocusHandler(self, tolua_ret);
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(L, ID, luaID, (void*)tolua_ret,"cc.EventListenerFocus");
        
        return 1;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerFocus:clone", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'tolua_cocos2dx_EventListenerFocus_clone'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2dx_EventListenerFocus_registerScriptHandler(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    EventListenerFocus* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L, 1, "cc.EventListenerFocus", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerFocus*>(tolua_tousertype(L,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'tolua_cocos2dx_EventListenerFocus_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(L,2,0);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_FOCUS);
        
        self->onFocusChanged = [=](ui::Widget* widgetLostFocus, ui::Widget* widgetGetFocus){
            int id = (widgetLostFocus) ? (int)widgetLostFocus->_ID : -1;
            int* luaID = (widgetLostFocus) ? &widgetLostFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(L, id, luaID, (void*)widgetLostFocus,"ccui.Widget");
            id = (widgetGetFocus) ? (int)widgetGetFocus->_ID : -1;
            luaID = (widgetGetFocus) ? &widgetGetFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(L, id, luaID, (void*)widgetGetFocus,"ccui.Widget");
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
        return 0;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerFocus:registerScriptHandler", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'tolua_cocos2dx_EventListenerFocus_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerFocusEvent(lua_State* L)
{
    lua_pushstring(L, "cc.EventListenerFocus");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "create", tolua_cocos2dx_EventListenerFocus_create);
        tolua_function(L, "registerScriptHandler", tolua_cocos2dx_EventListenerFocus_registerScriptHandler);
        tolua_function(L, "clone", tolua_cocos2dx_EventListenerFocus_clone);
    }
    lua_pop(L, 1);
}

int register_ui_moudle(lua_State* L)
{
    lua_getglobal(L, "_G");
    if (lua_istable(L,-1))//stack:...,_G,
    {
        register_all_cocos2dx_ui(L);
        register_all_cocos2dx_ui_manual(L);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        register_all_cocos2dx_experimental_video(L);
        register_all_cocos2dx_experimental_video_manual(L);
		register_all_cocos2dx_experimental_webview(L);
		register_all_cocos2dx_experimental_webview_manual(L);
#endif
        extendEventListenerFocusEvent(L);
    }
    lua_pop(L, 1);
    
    return 1;
}
