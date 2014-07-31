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
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of CheckBox has wrong number of arguments: %d, was expecting %d\n", argc, 1);
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
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of Slider has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of TextField has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of PageView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of ScrollView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of ListView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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
        
        return 0;
    }
    
    CCLOG("'addScrollViewEventListener' function of ListView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
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

int lua_cocos2dx_ProtectedNode_addProtectedChild(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_addProtectedChild'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ProtectedNode:addProtectedChild");
            
            if (!ok) { break; }
            cobj->addProtectedChild(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            
            if (!ok) { break; }
            cobj->addProtectedChild(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            cocos2d::Node* arg0;
            ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
            
            if (!ok) { break; }
            int arg1;
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ProtectedNode:addProtectedChild");
            
            if (!ok) { break; }
            int arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "cc.ProtectedNode:addProtectedChild");
            
            if (!ok) { break; }
            cobj->addProtectedChild(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ProtectedNode:addProtectedChild",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_addProtectedChild'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_disableCascadeColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_disableCascadeColor'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->disableCascadeColor();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:disableCascadeColor",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_disableCascadeColor'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_removeProtectedChildByTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_removeProtectedChildByTag'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        int arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ProtectedNode:removeProtectedChildByTag");
        if(!ok)
            return 0;
        cobj->removeProtectedChildByTag(arg0);
        return 0;
    }
    if (argc == 2)
    {
        int arg0;
        bool arg1;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ProtectedNode:removeProtectedChildByTag");
        
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.ProtectedNode:removeProtectedChildByTag");
        if(!ok)
            return 0;
        cobj->removeProtectedChildByTag(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeProtectedChildByTag",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_removeProtectedChildByTag'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_reorderProtectedChild(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_reorderProtectedChild'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::Node* arg0;
        int arg1;
        
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.ProtectedNode:reorderProtectedChild");
        if(!ok)
            return 0;
        cobj->reorderProtectedChild(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:reorderProtectedChild",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_reorderProtectedChild'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_removeAllProtectedChildrenWithCleanup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_removeAllProtectedChildrenWithCleanup'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ProtectedNode:removeAllProtectedChildrenWithCleanup");
        if(!ok)
            return 0;
        cobj->removeAllProtectedChildrenWithCleanup(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeAllProtectedChildrenWithCleanup",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_removeAllProtectedChildrenWithCleanup'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_sortAllProtectedChildren(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_sortAllProtectedChildren'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->sortAllProtectedChildren();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:sortAllProtectedChildren",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_sortAllProtectedChildren'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_getProtectedChildByTag(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_getProtectedChildByTag'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        int arg0;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ProtectedNode:getProtectedChildByTag");
        if(!ok)
            return 0;
        cocos2d::Node* ret = cobj->getProtectedChildByTag(arg0);
        object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:getProtectedChildByTag",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_getProtectedChildByTag'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_removeProtectedChild(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_removeProtectedChild'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Node* arg0;
        
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        if(!ok)
            return 0;
        cobj->removeProtectedChild(arg0);
        return 0;
    }
    if (argc == 2)
    {
        cocos2d::Node* arg0;
        bool arg1;
        
        ok &= luaval_to_object<cocos2d::Node>(tolua_S, 2, "cc.Node",&arg0);
        
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.ProtectedNode:removeProtectedChild");
        if(!ok)
            return 0;
        cobj->removeProtectedChild(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeProtectedChild",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_removeProtectedChild'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_removeAllProtectedChildren(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ProtectedNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ProtectedNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ProtectedNode_removeAllProtectedChildren'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cobj->removeAllProtectedChildren();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ProtectedNode:removeAllProtectedChildren",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_removeAllProtectedChildren'.",&tolua_err);
#endif
    
    return 0;
}
int lua_cocos2dx_ProtectedNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ProtectedNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::ProtectedNode* ret = cocos2d::ProtectedNode::create();
        object_to_luaval<cocos2d::ProtectedNode>(tolua_S, "cc.ProtectedNode",(cocos2d::ProtectedNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ProtectedNode:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ProtectedNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_ProtectedNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtectedNode)");
    return 0;
}

int lua_register_cocos2dx_ProtectedNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ProtectedNode");
    tolua_cclass(tolua_S,"ProtectedNode","cc.ProtectedNode","cc.Node",nullptr);
    
    tolua_beginmodule(tolua_S,"ProtectedNode");
    tolua_function(tolua_S,"addProtectedChild",lua_cocos2dx_ProtectedNode_addProtectedChild);
    tolua_function(tolua_S,"disableCascadeColor",lua_cocos2dx_ProtectedNode_disableCascadeColor);
    tolua_function(tolua_S,"removeProtectedChildByTag",lua_cocos2dx_ProtectedNode_removeProtectedChildByTag);
    tolua_function(tolua_S,"reorderProtectedChild",lua_cocos2dx_ProtectedNode_reorderProtectedChild);
    tolua_function(tolua_S,"removeAllProtectedChildrenWithCleanup",lua_cocos2dx_ProtectedNode_removeAllProtectedChildrenWithCleanup);
    tolua_function(tolua_S,"sortAllProtectedChildren",lua_cocos2dx_ProtectedNode_sortAllProtectedChildren);
    tolua_function(tolua_S,"getProtectedChildByTag",lua_cocos2dx_ProtectedNode_getProtectedChildByTag);
    tolua_function(tolua_S,"removeProtectedChild",lua_cocos2dx_ProtectedNode_removeProtectedChild);
    tolua_function(tolua_S,"removeAllProtectedChildren",lua_cocos2dx_ProtectedNode_removeAllProtectedChildren);
    tolua_function(tolua_S,"create", lua_cocos2dx_ProtectedNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ProtectedNode).name();
    g_luaType[typeName] = "cc.ProtectedNode";
    g_typeCast["ProtectedNode"] = "cc.ProtectedNode";
    return 1;
}

int register_cocos2dx_protectedNode(lua_State* L)
{
    tolua_module(L,"cc",0);
    tolua_beginmodule(L,"cc");
    lua_register_cocos2dx_ProtectedNode(L);
    tolua_endmodule(L);
    return 1;
}
