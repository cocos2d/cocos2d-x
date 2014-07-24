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
#include "lua_cocos2dx_manual.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#if defined(_MSC_VER) || defined(__MINGW32__)
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#endif
#include "ui/UIWidget.h"

static int tolua_cocos2d_MenuItemImage_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.MenuItemImage",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    do {
        if (argc == 0)
        {
            MenuItemImage* tolua_ret = (MenuItemImage*)MenuItemImage::create();
            //Uncheck
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemImage");
            return 1;
        }
    } while (0);
    do {
        if (argc == 2)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
                !tolua_isstring(tolua_S,3,0,&tolua_err))
            {
                ok = false;
            }
#endif
            if (!ok)
            {
                ok = true;
                break;
            }
            const std::string normalImage = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
            const std::string selectedImage = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
            MenuItemImage* tolua_ret = (MenuItemImage*)  MenuItemImage::create(normalImage,selectedImage);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemImage");
            return 1;
        }
    } while (0);
    do {
        if (argc == 3)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
                !tolua_isstring(tolua_S,3,0,&tolua_err) ||
                !tolua_isstring(tolua_S,4,0,&tolua_err) )
            {
                goto tolua_lerror;
                break;
            }
#endif
            const std::string normalImage = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
            const std::string selectedImage = ((const std::string)  tolua_tocppstring(tolua_S,3,0));
            const std::string disabledImage = ((const std::string)  tolua_tocppstring(tolua_S,4,0));
            
            MenuItemImage* tolua_ret = (MenuItemImage*)  MenuItemImage::create(normalImage,selectedImage,disabledImage);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemImage");
            return 1;
        }
    } while (0);
    
	CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItemImage:create",argc, 0);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItemImage_create'.\n",&tolua_err);
#endif
	return 0;
    
}

static int tolua_cocos2d_MenuItemLabel_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(1 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        Node* label = ((Node*)  tolua_tousertype(tolua_S,2,0));
        MenuItemLabel* tolua_ret = (MenuItemLabel*)  MenuItemLabel::create(label);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemLabel");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItemLabel:create", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItemImage_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItemFont_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.MenuItemFont",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(1 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const std::string value = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
        MenuItemFont* tolua_ret = (MenuItemFont*)  MenuItemFont::create(value);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemFont");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItemFont:create", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItemImage_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItemSprite_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(argc >= 2 && argc <= 3)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
            !tolua_isusertype(tolua_S,3,"cc.Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
        
        if (3 == argc && !tolua_isusertype(tolua_S,4,"cc.Node",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        Node* normalSprite = ((Node*)  tolua_tousertype(tolua_S,2,0));
        Node* selectedSprite = ((Node*)  tolua_tousertype(tolua_S,3,0));
        Node* disabledSprite = NULL;
        if (3 == argc)
        {
            disabledSprite = (Node*)  tolua_tousertype(tolua_S,4,0);
        }
        MenuItemSprite* tolua_ret = (MenuItemSprite*)  MenuItemSprite::create(normalSprite,selectedSprite,disabledSprite);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemSprite");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItemSprite:create",argc, 3);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItemImage_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Menu_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0 )
    {
        Vector<MenuItem*> items;
        uint32_t i = 1;
        while (i <= argc)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, 1 + i, "cc.MenuItem", 0, &tolua_err))
                goto tolua_lerror;
#endif
            
            cocos2d::MenuItem* item = static_cast<cocos2d::MenuItem*>(tolua_tousertype(tolua_S, 1 + i, NULL));
            if (NULL != item)
            {
                items.pushBack(item);
                ++i;
            }
            
        }
        cocos2d::Menu* tolua_ret = cocos2d::Menu::createWithArray(items);
        //UnCheck
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Menu");
        return 1;
    }
    else if(argc == 0)
    {
        cocos2d::Menu* tolua_ret = cocos2d::Menu::create();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Menu");
        return 1;
    }
    
    CCLOG("create wrong number of arguments: %d, was expecting %d\n", argc, 0);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Menu_create'.\n",&tolua_err);
#endif
	return 0;
}



static int tolua_cocos2dx_Menu_alignItemsInRows(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Menu* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Menu*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'lua_cocos2dx_Menu_alignItemsInRows'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0)
    {
        ValueVector items;
        if (luavals_variadic_to_ccvaluevector(tolua_S, argc, &items))
        {
            self->alignItemsInRowsWithArray(items);
        }
        return 0;
    }
    
    CCLOG("'alignItemsInRows' has wrong number of arguments in tolua_cocos2dx_Menu_alignItemsInRows: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'alignItemsInRows'.\n",&tolua_err);
#endif
	return 0;
}

static int tolua_cocos2dx_Menu_alignItemsInColumns(lua_State* tolua_S)
{
    
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Menu* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Menu*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Menu_alignItemsInColumns'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0)
    {
        ValueVector items;
        if (luavals_variadic_to_ccvaluevector(tolua_S, argc, &items))
        {
            self->alignItemsInColumnsWithArray(items);
        }
        return 0;
    }
    
    CCLOG("'alignItemsInColumns' has wrong number of arguments in tolua_cocos2dx_Menu_alignItemsInColumns: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_Menu_alignItemsInColumns'.\n",&tolua_err);
#endif
	return 0;
}

static int tolua_cocos2d_MenuItemToggle_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.MenuItemToggle",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(argc >= 1)
    {
        MenuItemToggle* tolua_ret = MenuItemToggle::create();
        if (NULL == tolua_ret)
        {
            return 0;
        }
        
        for (uint32_t i = 0; i < argc; ++i)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, i + 2,"cc.MenuItem",0,&tolua_err) )
            {
                goto tolua_lerror;
            }
#endif
            MenuItem* item = static_cast<MenuItem*>(tolua_tousertype(tolua_S, i + 2,0));
            tolua_ret->addSubItem(item);
        }
        tolua_ret->setSelectedIndex(0);
        
        int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.MenuItemToggle");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItemToggle:create",argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItemToggle_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItem_registerScriptTapHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    MenuItem* cobj = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2d_MenuItem_registerScriptTapHandler'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)cobj, handler, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItem:registerScriptTapHandler",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItem_registerScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_MenuItem_unregisterScriptTapHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    MenuItem* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.MenuItem",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = static_cast<cocos2d::MenuItemImage*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == cobj) {
		tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2d_MenuItem_unregisterScriptTapHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)cobj, ScriptHandlerMgr::HandlerType::MENU_CLICKED);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.MenuItem:unregisterScriptTapHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_MenuItem_unregisterScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}


static int executeScriptTouchHandler(Layer* layer, EventTouch::EventCode eventType, Touch* touch, Event* event)
{
    TouchScriptData data(eventType, layer, touch, event);
    ScriptEvent scriptEvent(kTouchEvent, &data);
    return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
}

static int executeScriptTouchesHandler(Layer* layer, EventTouch::EventCode eventType, const std::vector<Touch*>& touches, Event* event)
{
    TouchesScriptData data(eventType, layer, touches, event);
    ScriptEvent scriptEvent(kTouchesEvent, &data);
    return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
}

static void setTouchEnabledForLayer(Layer* layer, bool enabled)
{
    if (nullptr == layer)
        return;
    
    auto dict = static_cast<__Dictionary*>(layer->getUserObject());
    if (dict == nullptr)
    {
        dict = __Dictionary::create();
        layer->setUserObject(dict);
    }
    
    dict->setObject(Bool::create(enabled), "touchEnabled");
    
    auto touchListenerAllAtOnce = static_cast<EventListenerTouchAllAtOnce*>(dict->objectForKey("touchListenerAllAtOnce"));
    auto touchListenerOneByOne = static_cast<EventListenerTouchOneByOne*>(dict->objectForKey("touchListenerOneByOne"));
    auto touchMode = static_cast<__Integer*>(dict->objectForKey("touchMode"));
    auto swallowTouches = static_cast<__Bool*>(dict->objectForKey("swallowTouches"));
    auto priority  = static_cast<__Integer*>(dict->objectForKey("priority"));
    
    auto dispatcher = layer->getEventDispatcher();
    if (nullptr != dispatcher && (touchListenerAllAtOnce != nullptr || touchListenerOneByOne != nullptr))
    {
        dispatcher->removeEventListener(touchListenerAllAtOnce);
        dispatcher->removeEventListener(touchListenerOneByOne);
        dict->removeObjectForKey("touchListenerAllAtOnce");
        dict->removeObjectForKey("touchListenerOneByOne");
        touchListenerAllAtOnce = nullptr;
        touchListenerOneByOne = nullptr;
    }

    if (enabled)
    {
        if (touchMode == nullptr || touchMode->getValue() == (int)Touch::DispatchMode::ALL_AT_ONCE)
        {
            auto listener = EventListenerTouchAllAtOnce::create();
            listener->onTouchesBegan = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::BEGAN, touches, event);
            };
            listener->onTouchesMoved = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::MOVED, touches, event);
            };
            listener->onTouchesEnded = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::ENDED, touches, event);
            };
            listener->onTouchesCancelled = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::CANCELLED, touches, event);
            };
            
            if (nullptr != priority && 0 != priority->getValue())
            {
                dispatcher->addEventListenerWithFixedPriority(listener, priority->getValue());
            }
            else
            {
                dispatcher->addEventListenerWithSceneGraphPriority(listener, layer);
            }
            
            dict->setObject(listener, "touchListenerAllAtOnce");
        }
        else
        {
            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(swallowTouches ? swallowTouches->getValue() : false);
            listener->onTouchBegan = [layer](Touch* touch, Event* event) -> bool{
                return executeScriptTouchHandler(layer, EventTouch::EventCode::BEGAN, touch, event) == 0 ? false : true;
            };
            listener->onTouchMoved = [layer](Touch* touch, Event* event){
                executeScriptTouchHandler(layer, EventTouch::EventCode::MOVED, touch, event);
            };
            listener->onTouchEnded = [layer](Touch* touch, Event* event){
                executeScriptTouchHandler(layer, EventTouch::EventCode::ENDED, touch, event);
            };
            listener->onTouchCancelled = [layer](Touch* touch, Event* event){
                executeScriptTouchHandler(layer, EventTouch::EventCode::CANCELLED, touch,event);
            };
            
            if (nullptr != priority && 0 != priority->getValue())
            {
                dispatcher->addEventListenerWithFixedPriority(listener, priority->getValue());
            }
            else
            {
                dispatcher->addEventListenerWithSceneGraphPriority(listener, layer);
            }
            
            dict->setObject(listener, "touchListenerOneByOne");
        }
    }
    
}

//Only for v2.x lua compatibility
static int lua_cocos2dx_Layer_setTouchPriority(lua_State* L)
{
    return 0;
}

static int lua_cocos2dx_Layer_setTouchEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_setTouchEnabled'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        bool enabled = tolua_toboolean(L, 2, 0);
        setTouchEnabledForLayer(self, enabled);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setTouchEnabled", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_setTouchEnabled'.",&tolua_err);
    return 0;
#endif
    
}

static int lua_cocos2dx_Layer_isTouchEnabled(lua_State* L)
{
    if (nullptr == L)
    return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_isTouchEnabled'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("touchEnabled"));
            bool ret = enabled ? enabled->getValue() : false;
            tolua_pushboolean(L, ret);
            return 1;
        }
        
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isTouchEnabled", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_isTouchEnabled'.",&tolua_err);
    return 0;
#endif
    
    
}

static int lua_cocos2dx_Layer_setTouchMode(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_setTouchMode'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        int32_t mode = (int32_t)tolua_tonumber(L, 2, 0);
        
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if ( nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        
        __Integer* touchModeObj = static_cast<__Integer*>(dict->objectForKey("touchMode"));
        int32_t touchMode = touchModeObj ? touchModeObj->getValue() : 0;
        if (touchMode != mode)
        {
            dict->setObject(Integer::create(mode), "touchMode");
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setTouchMode", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_setTouchMode'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_getTouchMode(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_getTouchMode'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        int32_t ret = 0;
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            __Integer* mode = static_cast<__Integer*>(dict->objectForKey("touchMode"));
            ret = mode ? mode->getValue() : 0;
            tolua_pushnumber(L, (lua_Number)ret);
            return 1;
        }
        
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:getTouchMode", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_getTouchMode'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_setSwallowsTouches(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_setSwallowsTouches'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        
        bool swallowsTouches = tolua_toboolean(L, 2, 0);
        __Bool* swallowsTouchesObj = nullptr;
        
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        
        swallowsTouchesObj = static_cast<__Bool*>(dict->objectForKey("swallowTouches"));
        bool oldSwallowsTouches = swallowsTouchesObj ? swallowsTouchesObj->getValue() : false;
        
        if (oldSwallowsTouches != swallowsTouches)
        {
            dict->setObject(Integer::create(swallowsTouches), "swallowTouches");
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
        
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setSwallowsTouches", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_setSwallowsTouches'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_isSwallowsTouches(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_isSwallowsTouches'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            __Bool* swallowTouches = static_cast<__Bool*>(dict->objectForKey("swallowTouches"));
            bool ret = swallowTouches ? swallowTouches->getValue() : false;
            lua_pushboolean(L, ret);
            return 1;
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isSwallowsTouches", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_isSwallowsTouches'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_setKeyboardEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_setKeyboardEnabled'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        bool enabled = tolua_toboolean(L, 2, 0);
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = __Dictionary::create();
            self->setUserObject(dict);
        }
        
        dict->setObject(Bool::create(enabled), "keyboardEnabled");
        
        auto keyboardListener = static_cast<EventListenerKeyboard*>(dict->objectForKey("keyboardListener"));
        
        auto dispatcher = self->getEventDispatcher();
        dispatcher->removeEventListener(keyboardListener);
        if (enabled)
        {
            auto listener = EventListenerKeyboard::create();
            listener->onKeyPressed = [self](EventKeyboard::KeyCode keyCode, Event* event){
                
            };
            listener->onKeyReleased = [self](EventKeyboard::KeyCode keyCode, Event* event){
                KeypadScriptData data(keyCode, self);
                ScriptEvent scriptEvent(kKeypadEvent,&data);
                ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
            };
            CCLOG("come in the keyboardEnable");
            dispatcher->addEventListenerWithSceneGraphPriority(listener, self);
            
            dict->setObject(listener, "keyboardListener");
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setKeyboardEnabled", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_setKeyboardEnabled'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_isKeyboardEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_isKeyboardEnabled'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("keyboardEnabled"));
            bool ret = enabled ? enabled->getValue() : false;
            tolua_pushboolean(L, ret);
            return 1;
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isKeyboardEnabled", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_isKeyboardEnabled'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_setAccelerometerEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_setAccelerometerEnabled'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isboolean(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        bool enabled = tolua_toboolean(L, 2, 0);
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        
        dict->setObject(Bool::create(enabled), "accelerometerEnabled");
        
        auto accListener = static_cast<EventListenerAcceleration*>(dict->objectForKey("accListener"));
        
        auto dispatcher = self->getEventDispatcher();
        dispatcher->removeEventListener(accListener);
        
        Device::setAccelerometerEnabled(enabled);
        
        if (enabled)
        {
            auto listener = EventListenerAcceleration::create([self](Acceleration* acc, Event* event){
                BasicScriptData data(self,(void*)acc);
                ScriptEvent accEvent(kAccelerometerEvent,&data);
                ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&accEvent);
            });
            
            dispatcher->addEventListenerWithSceneGraphPriority(listener, self);
            
            dict->setObject(listener, "accListener");
        }
        
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setAccelerometerEnabled", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_setAccelerometerEnabled'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_isAccelerometerEnabled(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_isAccelerometerEnabled'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("accelerometerEnabled"));
            bool ret = enabled ? enabled->getValue() : false;
            tolua_pushboolean(L, ret);
            return 1;
        }
        
        return 0;
    }
    
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:isAccelerometerEnabled", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_isAccelerometerEnabled'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Layer_setAccelerometerInterval(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Layer_setAccelerometerInterval'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(L, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        double interval = tolua_tonumber(L, 2, 0);
        Device::setAccelerometerInterval(interval);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:setAccelerometerInterval",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Layer_setAccelerometerInterval'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Layer_registerScriptTouchHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptTouchHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >=1 && argc <= 4) {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        bool isMultiTouches  = false;
        int  priority        = 0;
        bool swallowTouches  = true;
        
        if (argc >= 2) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(tolua_S,3,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            isMultiTouches = (bool)tolua_toboolean(tolua_S,3,false);
        }
        
        if (argc >= 3) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,4,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            priority = (int)tolua_tonumber(tolua_S,4,0);
        }
        
        if (argc == 4) {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isboolean(tolua_S,5,0,&tolua_err)) {
                goto tolua_lerror;
            }
#endif
            swallowTouches = (bool)tolua_toboolean(tolua_S,5,true);
        }
        
        Touch::DispatchMode touchesMode = Touch::DispatchMode::ALL_AT_ONCE;
        if (!isMultiTouches)
            touchesMode = Touch::DispatchMode::ONE_BY_ONE;
        
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = __Dictionary::create();
            self->setUserObject(dict);
        }
        
        auto touchModeValue = static_cast<__Integer*>(dict->objectForKey("touchMode"));
        auto swallowTouchesValue = static_cast<__Bool*>(dict->objectForKey("swallowTouches"));
        auto priorityValue = static_cast<__Integer*>(dict->objectForKey("priority"));
        
        //touch model
        int32_t mode = touchModeValue?touchModeValue->getValue() : 0;
        if (mode != (int)touchesMode)
        {
            dict->setObject(Integer::create((int)touchesMode), "touchMode");
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
        
        int oldPriorityValue = priorityValue?priorityValue->getValue() : 0;
        if (priority != oldPriorityValue)
        {
            dict->setObject(Integer::create(priority), "priority");
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
        
        //swallowsTouches Obj
        bool oldSwallowTouchesValue = swallowTouchesValue?swallowTouchesValue->getValue():false;
        if (oldSwallowTouchesValue != swallowTouches)
        {
            dict->setObject(Integer::create(swallowTouches), "swallowTouches");
            __Bool* enabled = static_cast<__Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
		
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:registerScriptTouchHandler", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Layer_registerScriptTouchHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptTouchHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptTouchHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            auto touchListenerAllAtOnce = static_cast<EventListenerTouchAllAtOnce*>(dict->objectForKey("touchListenerAllAtOnce"));
            auto touchListenerOneByOne = static_cast<EventListenerTouchOneByOne*>(dict->objectForKey("touchListenerOneByOne"));
            auto dispatcher = self->getEventDispatcher();
            if (nullptr != dispatcher)
            {
                dispatcher->removeEventListener(touchListenerAllAtOnce);
                dispatcher->removeEventListener(touchListenerOneByOne);
            }
        }

        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:unregisterScriptTouchHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Layer_unregisterScriptTouchHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptKeypadHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptKeypadHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::KEYPAD);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:registerScriptKeypadHandler", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Layer_registerScriptKeypadHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptKeypadHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptKeypadHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            auto keyboardListener = static_cast<EventListenerKeyboard*>(dict->objectForKey("keyboardListener"));
            
            auto dispatcher = self->getEventDispatcher();
            if (dispatcher != nullptr)
            {
                dispatcher->removeEventListener(keyboardListener);
            }
        }
        
        ScriptHandlerMgr::getInstance()->removeObjectHandler(self, ScriptHandlerMgr::HandlerType::KEYPAD);
        return 0;
    }

    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:unregisterScriptKeypadHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Layer_unregisterScriptKeypadHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_registerScriptAccelerateHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_registerScriptAccelerateHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler =  toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::ACCELEROMETER);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:registerScriptAccelerateHandler", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Layer_registerScriptAccelerateHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Layer_unregisterScriptAccelerateHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Layer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Layer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Layer*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Layer_unregisterScriptAccelerateHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        auto dict = static_cast<__Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            auto accListener = static_cast<EventListenerAcceleration*>(dict->objectForKey("accListener"));
            
            auto dispatcher = self->getEventDispatcher();
            if (dispatcher != nullptr)
            {
                dispatcher->removeEventListener(accListener);
            }
        }
        
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::ACCELEROMETER);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Layer:unregisterScriptAccelerateHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Layer_unregisterScriptAccelerateHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Scheduler_scheduleScriptFunc(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Scheduler* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Scheduler_scheduleScriptFunc'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (3 == argc) {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
            !tolua_isboolean(tolua_S,4,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler =  toluafix_ref_function(tolua_S,2,0);
        float interval = (float)  tolua_tonumber(tolua_S,3,0);
        bool  paused   = (bool)  tolua_toboolean(tolua_S,4,0);
        unsigned int tolua_ret = (unsigned int)  self->scheduleScriptFunc(handler,interval,paused);
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Scheduler:scheduleScriptFunc",  argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Scheduler_scheduleScriptFunc'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_Scheduler_unscheduleScriptEntry(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Scheduler* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Scheduler",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Scheduler*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Scheduler_unscheduleScriptEntry'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (1 == argc) {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        unsigned int scheduleScriptEntryID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
        self->unscheduleScriptEntry(scheduleScriptEntryID);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Scheduler:unscheduleScriptEntry",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Scheduler_unscheduleScriptEntry'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Sequence_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
    tolua_Error tolua_err;
    
#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertable(tolua_S,1,"cc.Sequence",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(argc > 0)
    {
        Vector<FiniteTimeAction*> array;

        if (1 == argc && tolua_istable(tolua_S, 2, 0, &tolua_err))
        {
            luaval_to_ccvector(tolua_S, 2, &array, "cc.Sequence:create");
        }
        else
        {
            uint32_t i = 1;
            while (i <= argc)
            {
#if COCOS2D_DEBUG >= 1
                if (!tolua_isusertype(tolua_S, 1 + i, "cc.FiniteTimeAction", 0, &tolua_err))
                    goto tolua_lerror;
#endif
                
                cocos2d::FiniteTimeAction* item = static_cast<cocos2d::FiniteTimeAction*>(tolua_tousertype(tolua_S, 1 + i, nullptr));
                if (nullptr != item)
                {
                    array.pushBack(item);
                }
                ++i;
            }
        }
        
        cocos2d::Sequence* tolua_ret = cocos2d::Sequence::create(array);
        //issue 2433 uncheck
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : nullptr;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Sequence");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Sequence:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Sequence_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_CallFunc_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.CallFunc",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1 || argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if(!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        LUA_FUNCTION handler =  toluafix_ref_function(tolua_S,2,0);
        
        bool hasExtraData = false;
        int  ref  = 0;
        if (argc == 2)
        {
#if COCOS2D_DEBUG >= 1
            if(!tolua_istable(tolua_S, 3, 0, &tolua_err))
                goto tolua_lerror;
#endif
            lua_pushvalue(tolua_S, 3);
            ref = luaL_ref(tolua_S, LUA_REGISTRYINDEX);
            hasExtraData = true;
        }
        LuaCallFunc* tolua_ret = new LuaCallFunc();
        tolua_ret->initWithFunction([=](void* self,Node* target){
            int callbackHandler =  ScriptHandlerMgr::getInstance()->getObjectHandler((void*)tolua_ret, ScriptHandlerMgr::HandlerType::CALLFUNC);
            
            if (0 != callbackHandler)
            {
                LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
                int argNums = 1;
                if (nullptr != target)
                {
                    stack->pushObject(target, "cc.Node");
                }
                else
                {
                    stack->pushNil();
                }
                
                if (hasExtraData)
                {
                    lua_rawgeti(tolua_S, LUA_REGISTRYINDEX,ref);
                    if (lua_istable(tolua_S, -1))
                    {
                        argNums += 1;
                    }
                    else
                    {
                        lua_pop(tolua_S, 1);
                    }
                }
                stack->executeFunctionByHandler(callbackHandler, argNums);
                if (hasExtraData)
                {
                    luaL_unref(tolua_S, LUA_REGISTRYINDEX,ref);
                }
                stack->clean();
            }
        });
        tolua_ret->autorelease();
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)tolua_ret, handler, ScriptHandlerMgr::HandlerType::CALLFUNC);
        
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CallFunc");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.CallFunc:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CallFunc_create'.",&tolua_err);
    return 0;
#endif
    
}

static int tolua_cocos2d_Node_registerScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_registerScriptHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if(!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::NODE);

        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Node:registerScriptHandler",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Node_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_unregisterScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_unregisterScriptHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, ScriptHandlerMgr::HandlerType::NODE);
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Node:unregisterScriptHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Node_unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}


static int tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if(!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        
        LUA_FUNCTION handler =  toluafix_ref_function(tolua_S,2,0);
        int priority = 0;
        if (luaval_to_int32(tolua_S, 3, &priority, "cc.Node:scheduleUpdateWithPriorityLua"))
        {
           self->scheduleUpdateWithPriorityLua(handler,priority);
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n","cc.Node:scheduleUpdateWithPriorityLua",  argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Node_unscheduleUpdate(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_unscheduleUpdate'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        self->unscheduleUpdate();
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Node:unscheduleUpdate", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Node_unscheduleUpdate'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_Node_setContentSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Node_setContentSize'", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    
    if (1 == argc)
    {
        cocos2d::Size size;
        ok &= luaval_to_size(tolua_S, 2, &size, "cc.Node:setContentSize");
        if (!ok)
            return 0;
        
        cobj->setContentSize(size);
        return 0;
    }
    else if(2 == argc)
    {
        double width;
        ok &= luaval_to_number(tolua_S, 2,&width, "cc.Node:setContentSize");
        
        if (!ok)
            return 0;
        
        double height;
        ok &= luaval_to_number(tolua_S, 3,&height, "cc.Node:setContentSize");
        
        if (!ok)
            return 0;
        
        cobj->setContentSize(Size(width, height));
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setContentSize",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Node_setContentSize'.",&tolua_err);
#endif
    return 0;
}

int tolua_cocos2d_Node_setAnchorPoint(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Node_setAnchorPoint'", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    
    if (1 == argc)
    {
        cocos2d::Vec2 pt;
        ok &= luaval_to_vec2(tolua_S, 2, &pt, "cc.Node:setAnchorPoint");
        if (!ok)
            return 0;
        
        cobj->setAnchorPoint(pt);
        return 0;
    }
    else if(2 == argc)
    {
        double x;
        ok &= luaval_to_number(tolua_S, 2,&x, "cc.Node:setAnchorPoint");
        
        if (!ok)
            return 0;
        
        double y;
        ok &= luaval_to_number(tolua_S, 3,&y, "cc.Node:setAnchorPoint");
        
        if (!ok)
            return 0;
        
        cobj->setAnchorPoint(cocos2d::Vec2(x,y));
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Node:setAnchorPoint",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Node_setAnchorPoint'.",&tolua_err);
#endif
    return 0;
}

static int tolua_cocos2d_Node_getPosition(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Node* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::Node*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Node_getPosition'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 0 && argc <= 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,1,&tolua_err) || !tolua_isnumber(tolua_S,3,1,&tolua_err) )
            goto tolua_lerror;
#endif
        float x = (float)  tolua_tonumber(tolua_S,2,0);
        float y = (float)  tolua_tonumber(tolua_S,3,0);
        
        self->getPosition(&x,&y);
        
        tolua_pushnumber(tolua_S,(lua_Number)x);
        tolua_pushnumber(tolua_S,(lua_Number)y);
        
        return 2;
    }
    
    CCLOG("%s function in Node has wrong number of arguments: %d, was expecting %d\n", "cc.Node:getPosition",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Node_getPosition'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_Node_enumerateChildren(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Node* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Node*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Node_enumerateChildren'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
            !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        std::string name = (std::string)tolua_tocppstring(tolua_S,2,0);
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,3,0);
        
        cobj->enumerateChildren(name, [=](Node* node)->bool{
            int id = node ? (int)node->_ID : -1;
            int* luaID = node ? &node->_luaID : nullptr;
            toluafix_pushusertype_ccobject(tolua_S, id, luaID, (void*)node,"cc.Node");
            bool ret = LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
            LuaEngine::getInstance()->removeScriptHandler(handler);
            return ret;
        });
        
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "enumerateChildren",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Node_enumerateChildren'.",&tolua_err);
#endif
    
    return 0;
}

static int tolua_cocos2d_Spawn_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
    tolua_Error tolua_err;
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.Spawn",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc > 0)
    {
        Vector<FiniteTimeAction*> array;        
        uint32_t i = 1;
        
        if (1 == argc && tolua_istable(tolua_S, 2, 0, &tolua_err))
        {
            luaval_to_ccvector(tolua_S, 2, &array, "cc.Spawn:create");
        }
        else
        {
            while (i <= argc)
            {
#if COCOS2D_DEBUG >= 1
                if (!tolua_isusertype(tolua_S, 1 + i, "cc.FiniteTimeAction", 0, &tolua_err))
                    goto tolua_lerror;
#endif
                
                cocos2d::FiniteTimeAction* item = static_cast<cocos2d::FiniteTimeAction*>(tolua_tousertype(tolua_S, 1 + i, NULL));
                if (NULL != item)
                {
                    array.pushBack(item);
                    ++i;
                }
            }
        }
        
        cocos2d::Spawn * tolua_ret = cocos2d::Spawn::create(array);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.Spawn");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.Spawn:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Spawn_create'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2d_CardinalSplineBy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.CardinalSplineBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 3)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur, "cc.CardinalSplineBy:create");
        if (!ok)
            return 0;
        
        int num = 0;
        cocos2d::Vec2 *arr = NULL;
        ok &= luaval_to_array_of_vec2(tolua_S, 3, &arr, &num, "cc.CardinalSplineBy:create");
        if (!ok)
            return 0;
        
        double ten = 0.0;
        ok &= luaval_to_number(tolua_S, 4, &ten, "cc.CardinalSplineBy:create");
        if (!ok)
        {
            CC_SAFE_DELETE_ARRAY(arr);
            return 0;
        }
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                CC_SAFE_DELETE_ARRAY(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            CC_SAFE_DELETE_ARRAY(arr);
            CardinalSplineBy* tolua_ret = CardinalSplineBy::create(dur, points, ten);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CardinalSplineBy");
                return 1;
            }
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.CardinalSplineBy:create", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2d_CardinalSplineBy_create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_CatmullRomBy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.CatmullRomBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur, "cc.CatmullRomBy:create");
        if (!ok)
            return 0;
        
        int num = 0;
        cocos2d::Vec2 *arr = NULL;
        ok &= luaval_to_array_of_vec2(tolua_S, 3, &arr, &num, "cc.CatmullRomBy:create");
        if (!ok)
            return 0;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                CC_SAFE_DELETE_ARRAY(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            CC_SAFE_DELETE_ARRAY(arr);
            CatmullRomBy* tolua_ret = CatmullRomBy::create(dur, points);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CatmullRomBy");
                return 1;
            }
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.CatmullRomBy:create", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CatmullRomBy_create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_CatmullRomTo_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.CatmullRomTo",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur, "cc.CatmullRomTo:create");
        if (!ok)
            return 0;
        
        int num = 0;
        cocos2d::Vec2 *arr = NULL;
        ok &= luaval_to_array_of_vec2(tolua_S, 3, &arr, &num, "cc.CatmullRomTo:create");
        if (!ok)
            return 0;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                CC_SAFE_DELETE_ARRAY(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            CC_SAFE_DELETE_ARRAY(arr);
            CatmullRomTo* tolua_ret = CatmullRomTo::create(dur, points);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CatmullRomTo");
                return 1;
            }
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.CatmullRomTo:create", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_CatmullRomTo_create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_BezierBy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.BezierBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double t = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &t, "cc.BezierBy:create");
        if (!ok)
            return 0;
        
        int num = 0;
        cocos2d::Vec2 *arr = NULL;
        ok &= luaval_to_array_of_vec2(tolua_S, 3, &arr, &num, "cc.BezierBy:create");
        if (!ok)
            return 0;
        
        if (num < 3)
        {
            CC_SAFE_DELETE_ARRAY(arr);
            return 0;
        }
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        CC_SAFE_DELETE_ARRAY(arr);
        
        BezierBy* tolua_ret = BezierBy::create(t, config);
        if (NULL != tolua_ret)
        {
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.BezierBy");
            return 1;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.BezierBy:create",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_BezierBy_create'.",&tolua_err);
    return 0;
#endif
}

int tolua_cocos2d_BezierTo_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.BezierTo",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double t = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &t, "cc.BezierTo:create");
        if (!ok)
            return 0;
        
        int num = 0;
        cocos2d::Vec2 *arr = NULL;
        ok &= luaval_to_array_of_vec2(tolua_S, 3, &arr, &num, "cc.BezierTo:create");
        if (!ok)
            return 0;
        
        if (num < 3)
        {
            CC_SAFE_DELETE_ARRAY(arr);
            return 0;
        }
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        CC_SAFE_DELETE_ARRAY(arr);
        
        BezierTo* tolua_ret = BezierTo::create(t, config);
        if (NULL != tolua_ret)
        {
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.BezierTo");
            return 1;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.BezierTo:create", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_BezierTo_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_DrawNode_drawPolygon(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    DrawNode* self = nullptr;
  
    tolua_Error tolua_err;
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.DrawNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::DrawNode*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_DrawNode_drawPolygon'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (5 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if(
        !tolua_istable(tolua_S, 2, 0, &tolua_err)  ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
        !tolua_istable(tolua_S, 4, 0,&tolua_err)   ||
        !tolua_isnumber(tolua_S, 5, 0, &tolua_err) ||
        !tolua_istable(tolua_S,6, 0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        size_t size = lua_tonumber(tolua_S, 3);
        if ( size > 0 )
        {
            cocos2d::Vec2* points = new cocos2d::Vec2[size];
            if (NULL == points)
                return 0;
            
            for (int i = 0; i < size; i++)
            {
                lua_pushnumber(tolua_S,i + 1);
                lua_gettable(tolua_S,2);
                if (!tolua_istable(tolua_S,-1, 0, &tolua_err))
                {
                    CC_SAFE_DELETE_ARRAY(points);
#if COCOS2D_DEBUG >= 1
                    goto tolua_lerror;
#endif
                }
                
                if(!luaval_to_vec2(tolua_S, lua_gettop(tolua_S), &points[i], "cc.DrawNode:drawPolygon"))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }
            
            Color4F fillColor;
            if (!luaval_to_color4f(tolua_S, 4, &fillColor, "cc.DrawNode:drawPolygon"))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }
            
            float borderWidth  = (float)tolua_tonumber(tolua_S, 5, 0);
            
            Color4F borderColor;
            if (!luaval_to_color4f(tolua_S, 6, &borderColor, "cc.DrawNode:drawPolygon"))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }
            
            self->drawPolygon(points, (int)size, fillColor, borderWidth, borderColor);
            CC_SAFE_DELETE_ARRAY(points);
            return 0;
        }        
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.DrawNode:drawPolygon", argc, 5);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_DrawNode_drawPolygon'.",&tolua_err);
    return 0;
#endif
}

// setBlendFunc
template<class T>
static int tolua_cocos2dx_setBlendFunc(lua_State* tolua_S,const char* className)
{
    if (NULL == tolua_S || NULL == className || strlen(className) == 0)
        return 0;
    
    int argc = 0;
    T* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,className,0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<T*>(tolua_tousertype(tolua_S,1,0));
    
    argc = lua_gettop(tolua_S) - 1;
    if (2 == argc)
    {
        GLenum src, dst;
        if (!luaval_to_int32(tolua_S, 2, (int32_t*)&src, StringUtils::format("%s%s",className, ":setBlendFunc").c_str()))
            return 0;
        
        if (!luaval_to_int32(tolua_S, 3, (int32_t*)&dst, StringUtils::format("%s%s",className, ":setBlendFunc").c_str()))
            return 0;
        
        BlendFunc blendFunc = {src, dst};
        self->setBlendFunc(blendFunc);
        return 0;
    }

    
    CCLOG("'setBlendFunc' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_setBlendFunc'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_Sprite_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<Sprite>(tolua_S,"cc.Sprite");
}

static int tolua_cocos2dx_SpriteBatchNode_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<SpriteBatchNode>(tolua_S,"cc.SpriteBatchNode");
}

static int tolua_cocos2dx_MotionStreak_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<MotionStreak>(tolua_S,"cc.MotionStreak");
}

static int tolua_cocos2dx_AtlasNode_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<AtlasNode>(tolua_S,"cc.AtlasNode");
}

static int tolua_cocos2dx_ParticleBatchNode_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<ParticleBatchNode>(tolua_S,"cc.ParticleBatchNode");
}

static int tolua_cocos2dx_LayerColor_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<LayerColor>(tolua_S,"cc.LayerColor");
}

static int tolua_cocos2dx_ParticleSystem_setBlendFunc(lua_State* tolua_S) 
{
    return tolua_cocos2dx_setBlendFunc<ParticleSystem>(tolua_S,"cc.ParticleSystem");
}

static int tolua_cocos2dx_DrawNode_setBlendFunc(lua_State* tolua_S) 
{
    return tolua_cocos2dx_setBlendFunc<DrawNode>(tolua_S,"cc.DrawNode");
}

static int tolua_cocos2dx_LayerMultiplex_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Vector<Layer*> arg0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.LayerMultiplex", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
 
    if (argc > 0)
    {
        if (luavals_variadic_to_ccvector(tolua_S, argc, &arg0))
        {
            LayerMultiplex* tolua_ret =  LayerMultiplex::createWithArray(arg0);
            int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.LayerMultiplex");
            return 1;
        }
        else
        {
            CCLOG("error in tolua_cocos2dx_LayerMultiplex_create \n");
            return 0;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.LayerMultiplex:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_LayerMultiplex_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_FileUtils_getStringFromFile(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    FileUtils* self = nullptr;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<FileUtils *>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_FileUtils_getStringFromFile'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.FileUtils:getStringFromFile"); arg0 = arg0_tmp.c_str();
        if (ok)
        {
            std::string fullPathName = FileUtils::getInstance()->fullPathForFilename(arg0);
            __String* contentsOfFile = __String::createWithContentsOfFile(fullPathName.c_str());
            if (nullptr != contentsOfFile)
            {
                const char* tolua_ret = contentsOfFile->getCString();
                tolua_pushstring(tolua_S, tolua_ret);
            }
            return 1;
        }
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.FileUtils:getStringFromFile", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_FileUtils_getStringFromFile'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_UserDefault_getInstance(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.UserDefault",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(0 == argc)
    {
        UserDefault* tolua_ret = (UserDefault*)  UserDefault::getInstance();
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"cc.UserDefault");
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.UserDefault:getInstance",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_UserDefault_getInstance'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_GLProgram_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    bool ok = false;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(2 == argc)
    {
        const char *arg0, *arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.GLProgram:create"); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "cc.GLProgram:create"); arg1 = arg1_tmp.c_str();
        
        GLProgram* tolua_ret = new GLProgram();
        if (nullptr == tolua_ret)
            return 0;        

        tolua_ret->autorelease();
        tolua_ret->initWithFilenames(arg0, arg1);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.GLProgram");
        return 1;
        
    }
    
    CCLOG("%s wrong number of arguments: %d, was expecting %d\n", "cc.GLProgram:create", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_GLProgram_create'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_GLProgram_getProgram(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    GLProgram* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_GLProgram_getProgram'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (0 == argc)
    {
        unsigned const int tolua_ret = ( unsigned const int)  self->getProgram();
        tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.GLProgram:getProgram",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_GLProgram_getProgram'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_GLProgram_setUniformLocationF32(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    GLProgram* self = nullptr;
    int location = 0;
    double f1 = 0.0;
    double f2 = 0.0;
    double f3 = 0.0;
    double f4 = 0.0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (GLProgram*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_GLProgram_getProgram'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 2 && argc <= 5)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
            !tolua_isnumber(tolua_S,3,0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        location = (int)  tolua_tonumber(tolua_S,2,0);
        f1 = (float)  tolua_tonumber(tolua_S,3,0);
        
        if (2 == argc)
        {
            self->setUniformLocationWith1f(location,f1);
            return 0;
        }
        
        if (argc >= 3)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,4,0,&tolua_err))
                goto tolua_lerror;
#endif
            
            f2 = (float)  tolua_tonumber(tolua_S,3,0);
            if (3 == argc)
            {
                self->setUniformLocationWith2f(location, f1, f2);
                return 0;
            }
        }
        
        if (argc >= 4)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,5,0,&tolua_err))
                goto tolua_lerror;
#endif
            
            f3 = (float)  tolua_tonumber(tolua_S,3,0);
            if (4 == argc)
            {
                self->setUniformLocationWith3f(location, f1, f2, f3);
                return 0;
            }
        }
        
        if (argc == 5)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S,6,0,&tolua_err))
                goto tolua_lerror;
#endif
            
            f4 = (float)  tolua_tonumber(tolua_S,3,0);
            if (4 == argc)
            {
                self->setUniformLocationWith4f(location, f1, f2, f3, f4);
                return 0;
            }

        }
    }
    
    CCLOG(" %s has wrong number of arguments: %d, was expecting %d\n", "cc.GLProgram:setUniformLocationF32",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_GLProgram_getProgram'.",&tolua_err);
    return 0;
#endif
}


static int lua_cocos2dx_GLProgram_getUniform(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_getUniform'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.GLProgram:getUniform");
        if(!ok)
            return 0;
        cocos2d::Uniform* ret = cobj->getUniform(arg0);
        if (nullptr == ret)
        {
            lua_pushnil(tolua_S);
        }
        else
        {
            uniform_to_luaval(tolua_S, *ret);
        }
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:getUniform:getUniform",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_getUniform'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_GLProgram_setUniformLocationWithMatrix2fv(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_setUniformLocationWithMatrix2fv'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        GLint arg0;
        GLfloat* arg1;
        unsigned int arg2;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.GLProgram:setUniformLocationWithMatrix2fv");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgram:setUniformLocationWithMatrix2fv");
        
        if(!ok)
        {
            CCLOG("Parse params error in the lua_cocos2dx_GLProgram_setUniformLocationWithMatrix2fv");
            return 0;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        arg1 = new GLfloat[sizeof(GLfloat) * 4 * arg2];
        if (nullptr == arg1)
        {
            CCLOG("Allocate matrixArry in the lua_cocos2dx_GLProgram_setUniformLocationWithMatrix2fv failed!");
            return 0;
        }
        
        for (int i = 1; i <= arg2 * 4; i++)
        {
            arg1[i - 1] = (GLfloat)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        
        cobj->setUniformLocationWithMatrix2fv(arg0, arg1, arg2);
        CC_SAFE_DELETE_ARRAY(arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:setUniformLocationWithMatrix2fv",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_setUniformLocationWithMatrix2fv'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_GLProgram_setUniformLocationWithMatrix3fv(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_setUniformLocationWithMatrix3fv'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        GLint arg0;
        GLfloat* arg1;
        unsigned int arg2;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.GLProgram:setUniformLocationWithMatrix3fv");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgram:setUniformLocationWithMatrix3fv");
        
        if(!ok)
        {
            CCLOG("Parse params error in the lua_cocos2dx_GLProgram_setUniformLocationWithMatrix3fv");
            return 0;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        arg1 = new GLfloat[sizeof(GLfloat) * 9 * arg2];
        if (nullptr == arg1)
        {
            CCLOG("Allocate matrixArry in the lua_cocos2dx_GLProgram_setUniformLocationWithMatrix3fv failed!");
            return 0;
        }
        
        for (int i = 1; i <= arg2 * 9; i++)
        {
            arg1[i - 1] = (GLfloat)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }

        cobj->setUniformLocationWithMatrix3fv(arg0, arg1, arg2);
        CC_SAFE_DELETE_ARRAY(arg1);
        
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:setUniformLocationWithMatrix3fv",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_setUniformLocationWithMatrix3fv'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_GLProgram_setUniformLocationWithMatrix4fv(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_setUniformLocationWithMatrix4fv'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        GLint arg0;
        GLfloat* arg1;
        unsigned int arg2;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.GLProgram:setUniformLocationWithMatrix4fv");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgram:setUniformLocationWithMatrix4fv");
        
        if(!ok)
        {
            CCLOG("Parse params error in the lua_cocos2dx_GLProgram_setUniformLocationWithMatrix4fv");
            return 0;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        arg1 = new GLfloat[sizeof(GLfloat) * 16 * arg2];
        if (nullptr == arg1)
        {
            CCLOG("Allocate matrixArry in the lua_cocos2dx_GLProgram_setUniformLocationWithMatrix4fv failed!");
            return 0;
        }
        
        for (int i = 1; i <= arg2 * 16; i++)
        {
            arg1[i - 1] = (GLfloat)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
    
        cobj->setUniformLocationWithMatrix4fv(arg0, arg1, arg2);
        
        CC_SAFE_DELETE_ARRAY(arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:setUniformLocationWithMatrix4fv",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_setUniformLocationWithMatrix4fv'.",&tolua_err);
    return 0;
#endif
}

int lua_cocos2dx_GLProgram_setUniformLocationWith3iv(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_setUniformLocationWith3iv'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        GLint arg0;
        GLint* arg1;
        unsigned int arg2;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.GLProgram:setUniformLocationWith3iv");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgram:setUniformLocationWith3iv");
        if(!ok)
        {
            CCLOG("Parse params error in the lua_cocos2dx_GLProgram_setUniformLocationWith3iv");
            return 0;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        arg1 = new GLint[sizeof(GLint) * 3 * arg2];
        if (nullptr == arg1)
        {
            CCLOG("Allocate intArray in the lua_cocos2dx_GLProgram_setUniformLocationWith3iv failed!");
            return 0;
        }
        
        for (int i = 1; i <= arg2 * 3; i++)
        {
            arg1[i - 1] = (GLint)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        
        cobj->setUniformLocationWith3iv(arg0, arg1, arg2);
        
        CC_SAFE_DELETE_ARRAY(arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:setUniformLocationWith3iv",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_setUniformLocationWith3iv'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_GLProgram_setUniformLocationWith4iv(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_setUniformLocationWith4iv'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        GLint arg0;
        GLint* arg1;
        unsigned int arg2;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.GLProgram:setUniformLocationWith4iv");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgram:setUniformLocationWith4iv");
        
        if(!ok)
        {
            CCLOG("Parse params error in the lua_cocos2dx_GLProgram_setUniformLocationWith4iv");
            return 0;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        arg1 = new GLint[sizeof(GLint) * 4 * arg2];
        if (nullptr == arg1)
        {
            CCLOG("Allocate intArray in the lua_cocos2dx_GLProgram_setUniformLocationWith4iv failed!");
            return 0;
        }
        
        for (int i = 1; i <= arg2 * 4; i++)
        {
            arg1[i - 1] = (GLint)tolua_tofieldnumber(tolua_S, 3, i, 0);
        }
        cobj->setUniformLocationWith4iv(arg0, arg1, arg2);
        CC_SAFE_DELETE_ARRAY(arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:setUniformLocationWith4iv",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_setUniformLocationWith4iv'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_GLProgram_setUniformLocationWith2iv(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_setUniformLocationWith2iv'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
        GLint arg0;
        GLint* arg1;
        unsigned int arg2;
        
        ok &= luaval_to_int32(tolua_S, 2,(GLint *)&arg0, "cc.GLProgram:setUniformLocationWith2iv");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgram:setUniformLocationWith2iv");
        
        if(!ok)
        {
            CCLOG("Parse params error in the lua_cocos2dx_GLProgram_setUniformLocationWith2iv");
            return 0;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
            goto tolua_lerror;
#endif
        arg1 = new GLint[sizeof(GLint) * 2 * arg2];
        if (nullptr == arg1)
        {
            CCLOG("Allocate intArray in the lua_cocos2dx_GLProgram_setUniformLocationWith2iv failed!");
            return 0;
        }
        
        cobj->setUniformLocationWith2iv(arg0, arg1, arg2);
        
        CC_SAFE_DELETE_ARRAY(arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:setUniformLocationWith2iv",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_setUniformLocationWith2iv'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_GLProgram_getVertexAttrib(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgram* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgram*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgram_getVertexAttrib'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.GLProgram:getVertexAttrib");
        if(!ok)
            return 0;
        cocos2d::VertexAttrib* ret = cobj->getVertexAttrib(arg0);
        if (nullptr == ret)
        {
            lua_pushnil(tolua_S);
        }
        else
        {
            vertexattrib_to_luaval(tolua_S, *ret);
        }
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgram:getVertexAttrib",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgram_getVertexAttrib'.",&tolua_err);
#endif
    
    return 0;
}

static void extendGLProgram(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.GLProgram");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_GLProgram_create);
        tolua_function(tolua_S, "getProgram", tolua_cocos2d_GLProgram_getProgram);
        tolua_function(tolua_S, "setUniformLocationF32", tolua_cocos2dx_GLProgram_setUniformLocationF32);
        tolua_function(tolua_S, "getUniform", lua_cocos2dx_GLProgram_getUniform);
        tolua_function(tolua_S, "setUniformLocationWithMatrix2fv", lua_cocos2dx_GLProgram_setUniformLocationWithMatrix2fv);
        tolua_function(tolua_S, "setUniformLocationWithMatrix3fv", lua_cocos2dx_GLProgram_setUniformLocationWithMatrix3fv);
        tolua_function(tolua_S, "setUniformLocationWithMatrix4fv", lua_cocos2dx_GLProgram_setUniformLocationWithMatrix4fv);
        tolua_function(tolua_S, "setUniformLocationWith2iv", lua_cocos2dx_GLProgram_setUniformLocationWith2iv);
        tolua_function(tolua_S, "setUniformLocationWith3iv", lua_cocos2dx_GLProgram_setUniformLocationWith3iv);
        tolua_function(tolua_S, "setUniformLocationWith4iv", lua_cocos2dx_GLProgram_setUniformLocationWith4iv);
        tolua_function(tolua_S, "getVertexAttrib", lua_cocos2dx_GLProgram_getVertexAttrib);
    };
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_Texture2D_setTexParameters(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Texture2D* self = nullptr;
    GLuint arg1 = 0;
    GLuint arg2 = 0;
    GLuint arg3 = 0;
    GLuint arg4 = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"cc.Texture2D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (Texture2D*)  tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_Texture2D_setTexParameters'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (4 == argc)
    {        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 4, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 5, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        arg1 = (GLuint)tolua_tonumber(tolua_S, 2, 0);
        arg2 = (GLuint)tolua_tonumber(tolua_S, 3, 0);
        arg3 = (GLuint)tolua_tonumber(tolua_S, 4, 0);
        arg4 = (GLuint)tolua_tonumber(tolua_S, 5, 0);
        
        Texture2D::TexParams param = { arg1, arg2, arg3, arg4 };
        
        self->setTexParameters(param);
        
        return 0;
    }
    
    CCLOG("'setTexParameters' function of Texture2D wrong number of arguments: %d, was expecting %d\n", argc,4);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTexParameters'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_SpriteBatchNode_getDescendants(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::SpriteBatchNode* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::SpriteBatchNode*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2dx_SpriteBatchNode_getDescendants'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
            return 0;
        std::vector<Sprite*> ret = cobj->getDescendants();

        lua_newtable(tolua_S);
        
        if (ret.empty())
            return 1;
        
        auto iter = ret.begin();
        int  indexTable = 1;
        for (; iter != ret.end(); ++iter)
        {
            if (nullptr == *iter)
                continue;
            
            lua_pushnumber(tolua_S, (lua_Number)indexTable);
            toluafix_pushusertype_ccobject(tolua_S, (*iter)->_ID, &((*iter)->_luaID), (void*)(*iter),"cc.Sprite");
            lua_rawset(tolua_S, -3);
            (*iter)->retain();
            ++indexTable;
        }
        
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.SpriteBatchNode:getDescendants",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_SpriteBatchNode_getDescendants'.",&tolua_err);
#endif
    return 0;
}

static void extendTexture2D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Texture2D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setTexParameters");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Texture2D_setTexParameters );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItem(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.MenuItem");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptTapHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItem_registerScriptTapHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unregisterScriptTapHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItem_unregisterScriptTapHandler);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItemImage(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.MenuItemImage");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemImage_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItemLabel(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MenuItemLabel");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemLabel_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItemFont(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MenuItemFont");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemFont_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItemSprite(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MenuItemSprite");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemSprite_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenuItemToggle(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MenuItemToggle");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_MenuItemToggle_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMenu(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Menu");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S, -1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Menu_create);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"alignItemsInRows");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Menu_alignItemsInRows);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"alignItemsInColumns");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Menu_alignItemsInColumns);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Node");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_registerScriptHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"unregisterScriptHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_unregisterScriptHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S,"scheduleUpdateWithPriorityLua");
        lua_pushcfunction(tolua_S,tolua_Cocos2d_Node_scheduleUpdateWithPriorityLua);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S,"unscheduleUpdate");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_unscheduleUpdate);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S,"getPosition");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Node_getPosition);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setContentSize");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Node_setContentSize);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "setAnchorPoint");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Node_setAnchorPoint);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "enumerateChildren");
        lua_pushcfunction(tolua_S, lua_cocos2dx_Node_enumerateChildren);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Layer");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptTouchHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Layer_registerScriptTouchHandler);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unregisterScriptTouchHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Layer_unregisterScriptTouchHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "registerScriptKeypadHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptKeypadHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptKeypadHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptKeypadHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "registerScriptAccelerateHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_registerScriptAccelerateHandler);
        lua_rawset(tolua_S, -3);
        lua_pushstring(tolua_S, "unregisterScriptAccelerateHandler");
        lua_pushcfunction(tolua_S, tolua_cocos2d_Layer_unregisterScriptAccelerateHandler);
        lua_rawset(tolua_S, -3);
        
        tolua_function(tolua_S, "setTouchEnabled", lua_cocos2dx_Layer_setTouchEnabled);
        tolua_function(tolua_S, "isTouchEnabled", lua_cocos2dx_Layer_isTouchEnabled);
        tolua_function(tolua_S, "setTouchMode", lua_cocos2dx_Layer_setTouchMode);
        tolua_function(tolua_S, "getTouchMode", lua_cocos2dx_Layer_getTouchMode);
        tolua_function(tolua_S, "setSwallowsTouches", lua_cocos2dx_Layer_setSwallowsTouches);
        tolua_function(tolua_S, "isSwallowsTouches", lua_cocos2dx_Layer_isSwallowsTouches);
        tolua_function(tolua_S, "setKeyboardEnabled", lua_cocos2dx_Layer_setKeyboardEnabled);
        tolua_function(tolua_S, "isKeyboardEnabled", lua_cocos2dx_Layer_isKeyboardEnabled);
        tolua_function(tolua_S, "setAccelerometerEnabled", lua_cocos2dx_Layer_setAccelerometerEnabled);
        tolua_function(tolua_S, "isAccelerometerEnabled", lua_cocos2dx_Layer_isAccelerometerEnabled);
        tolua_function(tolua_S, "setAccelerometerInterval", lua_cocos2dx_Layer_setAccelerometerInterval);
    }
    lua_pop(tolua_S, 1);
}

static void extendScheduler(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Scheduler");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"scheduleScriptFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Scheduler_scheduleScriptFunc);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S, "unscheduleScriptEntry");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Scheduler_unscheduleScriptEntry);
        lua_rawset(tolua_S, -3);
    }
    lua_pop(tolua_S, 1);
}

static void extendSequence(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Sequence");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Sequence_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCallFunc(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.CallFunc");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CallFunc_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendSpawn(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Spawn");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Spawn_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCardinalSplineBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.CardinalSplineBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,lua_cocos2d_CardinalSplineBy_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCatmullRomBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.CatmullRomBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CatmullRomBy_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendCatmullRomTo(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.CatmullRomTo");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CatmullRomTo_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendBezierBy(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.BezierBy");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_BezierBy_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendBezierTo(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.BezierTo");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2d_BezierTo_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendDrawNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.DrawNode");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"drawPolygon");
        lua_pushcfunction(tolua_S,tolua_cocos2d_DrawNode_drawPolygon);
        lua_rawset(tolua_S,-3);

        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_DrawNode_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendSprite(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.Sprite");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_Sprite_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendLayerColor(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.LayerColor");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_LayerColor_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendLayerMultiplex(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.LayerMultiplex");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_LayerMultiplex_create);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendParticleSystem(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"cc.ParticleSystem");
    lua_rawget(tolua_S,LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_ParticleSystem_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendFileUtils(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.FileUtils");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getStringFromFile");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_FileUtils_getStringFromFile );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendUserDefault(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.UserDefault");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getInstance");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_UserDefault_getInstance );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendSpriteBatchNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.SpriteBatchNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getDescendants");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_SpriteBatchNode_getDescendants );
        lua_rawset(tolua_S,-3);

        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_SpriteBatchNode_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendMotionStreak(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.MotionStreak");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_MotionStreak_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendAtlasNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.AtlasNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_AtlasNode_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static void extendParticleBatchNode(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ParticleBatchNode");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setBlendFunc");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_ParticleBatchNode_setBlendFunc);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

NS_CC_BEGIN
EventListenerAcceleration* LuaEventListenerAcceleration::create()
{
    EventListenerAcceleration* eventAcceleration = new EventListenerAcceleration();
    if (nullptr == eventAcceleration)
        return nullptr;
    
    if ( eventAcceleration->init([=](Acceleration* acc, Event* event){
        LuaEventAccelerationData listenerData((void*)acc,event);
        BasicScriptData data(eventAcceleration,(void*)&listenerData);
        LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::EVENT_ACC, (void*)&data);
    }))
    {
        eventAcceleration->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(eventAcceleration);
    }
    return eventAcceleration;
}

EventListenerCustom* LuaEventListenerCustom::create(const std::string& eventName)
{
    EventListenerCustom* eventCustom = new EventListenerCustom();
    if (nullptr == eventCustom)
        return nullptr;
    
    if ( eventCustom->init(eventName, [=](EventCustom* event){
        BasicScriptData data((void*)eventCustom,(void*)event);
        LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::EVENT_CUSTIOM, (void*)&data );
    }))
    {
        eventCustom->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(eventCustom);
    }
    return eventCustom;
}
NS_CC_END

static int tolua_cocos2dx_LuaEventListenerAcceleration_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerAcceleration", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
 
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        cocos2d::EventListenerAcceleration* tolua_ret = cocos2d::LuaEventListenerAcceleration::create();
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)tolua_ret, handler, ScriptHandlerMgr::HandlerType::EVENT_ACC);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerAcceleration");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerAcceleration:create",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_LuaEventListenerAcceleration_create'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_LuaEventListenerCustom_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerCustom", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S,2,0,&tolua_err) ||
            !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const std::string eventName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,3,0);
        cocos2d::EventListenerCustom* tolua_ret = LuaEventListenerCustom::create(eventName);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)tolua_ret, handler, ScriptHandlerMgr::HandlerType::EVENT_CUSTIOM);
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerCustom");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerCustom:create", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_LuaEventListenerCustom_create'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerCustom(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerCustom");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create",tolua_cocos2d_LuaEventListenerCustom_create);
    }
    lua_pop(tolua_S, 1);
}

static void extendEventListenerAcceleration(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerAcceleration");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create",tolua_cocos2dx_LuaEventListenerAcceleration_create);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_EventListenerKeyboard_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerKeyboard", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerKeyboard* tolua_ret = cocos2d::EventListenerKeyboard::create();
        if(nullptr == tolua_ret)
            return 0;
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerKeyboard");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerKeyboard:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerKeyboard_create'.",&tolua_err);
    return 0;
#endif
}

static void cloneKeyboardHandler(const EventListenerKeyboard* src,EventListenerKeyboard* dst,  ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;
    
    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED:
                {
                    dst->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
                        LuaEventKeyboarData listenerData((int)keyCode, event);
                        BasicScriptData data((void*)dst,(void*)&listenerData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED:
                {
                    dst->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
                        LuaEventKeyboarData listenerData((int)keyCode, event);
                        BasicScriptData data((void*)dst,(void*)&listenerData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            default:
                break;
        }
    }
}

static int tolua_cocos2dx_EventListenerKeyboard_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerKeyboard* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerKeyboard", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerKeyboard*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerKeyboard_clone'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerKeyboard* tolua_ret = cocos2d::EventListenerKeyboard::create();
        if(nullptr == tolua_ret)
            return 0;
        
        cloneKeyboardHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED);
        cloneKeyboardHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED);
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerKeyboard");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerKeyboard:clone",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerKeyboard_clone'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_EventListenerKeyboard_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerKeyboard* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerKeyboard", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerKeyboard*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerKeyboard_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::HandlerType type = static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_PRESSED:
                {
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                    self->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
                        LuaEventKeyboarData listenerData((int)keyCode, event);
                        BasicScriptData data((void*)self,(void*)&listenerData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_KEYBOARD_RELEASED:
                {
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                    self->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
                        LuaEventKeyboarData listenerData((int)keyCode, event);
                        BasicScriptData data((void*)self,(void*)&listenerData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            default:
                break;
        }
        
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerKeyboard:registerScriptHandler", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerKeyboard_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerKeyboard(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerKeyboard");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create",tolua_cocos2dx_EventListenerKeyboard_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerKeyboard_registerScriptHandler);
        tolua_function(tolua_S, "clone", tolua_cocos2dx_EventListenerKeyboard_clone);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_EventListenerTouchOneByOne_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerTouchOneByOne", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerTouchOneByOne* tolua_ret = cocos2d::EventListenerTouchOneByOne::create();
        if(nullptr == tolua_ret)
            return 0;
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerTouchOneByOne");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerTouchOneByOne:create",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerTouchOneByOne_create'.",&tolua_err);
    return 0;
#endif
}

static void cloneTouchOneByOneHandler(const EventListenerTouchOneByOne* src,EventListenerTouchOneByOne* dst,  ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;
    
    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN:
                {
                    dst->onTouchBegan = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)dst,(void*)&touchData);
                        return LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED:
                {
                    dst->onTouchMoved = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)dst,(void*)&touchData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                        };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED:
                {
                    dst->onTouchEnded = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)dst,(void*)&touchData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED:
                {
                    dst->onTouchCancelled = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)dst,(void*)&touchData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            default:
                break;
        }
    }
}

static int tolua_cocos2dx_EventListenerTouchOneByOne_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerTouchOneByOne* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchOneByOne", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerTouchOneByOne*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerTouchOneByOne_clone'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerTouchOneByOne* tolua_ret = cocos2d::EventListenerTouchOneByOne::create();
        if(nullptr == tolua_ret)
            return 0;
        
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN);
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED);
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED);
        cloneTouchOneByOneHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED);
        tolua_ret->setSwallowTouches(self->isSwallowTouches());
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerTouchOneByOne");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerTouchOneByOne:create", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerTouchOneByOne_clone'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_EventListenerTouchOneByOne_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerTouchOneByOne* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchOneByOne", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerTouchOneByOne*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerTouchOneByOne_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::HandlerType type        = static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_BEGAN:
                {
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                    
                    self->onTouchBegan = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)self,(void*)&touchData);
                        return LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_MOVED:
                {
                    self->onTouchMoved = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)self,(void*)&touchData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                    
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_ENDED:
                {
                    self->onTouchEnded = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)self,(void*)&touchData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                    
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCH_CANCELLED:
                {
                    self->onTouchCancelled = [=](Touch* touch, Event* event){
                        LuaEventTouchData touchData(touch, event);
                        BasicScriptData data((void*)self,(void*)&touchData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                    
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                }
                break;
            default:
                break;
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerTouchOneByOne:registerScriptHandler", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerTouchOneByOne_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerTouchOneByOne(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerTouchOneByOne");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerTouchOneByOne_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerTouchOneByOne_registerScriptHandler);
        tolua_function(tolua_S, "clone", tolua_cocos2dx_EventListenerTouchOneByOne_clone);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_EventListenerTouchAllAtOnce_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerTouchAllAtOnce", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerTouchAllAtOnce* tolua_ret = cocos2d::EventListenerTouchAllAtOnce::create();
        if(nullptr == tolua_ret)
            return 0;

        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerTouchAllAtOnce");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerTouchAllAtOnce:registerScriptHandler",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerTouchAllAtOnce_create'.",&tolua_err);
    return 0;
#endif
}

static void cloneTouchAllAtOnceHandler(const EventListenerTouchAllAtOnce* src,EventListenerTouchAllAtOnce* dst,  ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;
    
    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN:
                {
                    dst->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
                        LuaEventTouchesData touchesData(touches, event);
                        BasicScriptData data((void*)dst,(void*)&touchesData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED:
                {
                    dst->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event){
                        LuaEventTouchesData touchesData(touches, event);
                        BasicScriptData data((void*)dst,(void*)&touchesData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED:
                {
                    dst->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
                        LuaEventTouchesData touchesData(touches, event);
                        BasicScriptData data((void*)dst,(void*)&touchesData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED:
                {
                    dst->onTouchesCancelled = [=](const std::vector<Touch*>& touches, Event* event){
                        LuaEventTouchesData touchesData(touches, event);
                        BasicScriptData data((void*)dst,(void*)&touchesData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            default:
                break;
        }
    }
}

static int tolua_cocos2dx_EventListenerTouchAllAtOnce_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerTouchAllAtOnce* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchAllAtOnce", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerTouchAllAtOnce*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerTouchAllAtOnce_clone'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerTouchAllAtOnce* tolua_ret = cocos2d::EventListenerTouchAllAtOnce::create();
        if(nullptr == tolua_ret)
            return 0;
        
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN);
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED);
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED);
        cloneTouchAllAtOnceHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED);
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerTouchAllAtOnce");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerTouchAllAtOnce:clone", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerTouchAllAtOnce_clone'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_EventListenerTouchAllAtOnce_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerTouchAllAtOnce* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerTouchAllAtOnce", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerTouchAllAtOnce*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerTouchAllAtOnce_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::HandlerType type        = static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0));
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_BEGAN:
                {
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                
                    self->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
                        LuaEventTouchesData touchesData(touches, event);
                        BasicScriptData data((void*)self,(void*)&touchesData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_MOVED:
            {
                self->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event){
                    LuaEventTouchesData touchesData(touches, event);
                    BasicScriptData data((void*)self,(void*)&touchesData);
                    LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                };
                
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
            }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_ENDED:
            {
                self->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
                    LuaEventTouchesData touchesData(touches, event);
                    BasicScriptData data((void*)self,(void*)&touchesData);
                    LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                };
                
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
            }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_TOUCHES_CANCELLED:
            {
                self->onTouchesCancelled = [=](const std::vector<Touch*>& touches, Event* event){
                    LuaEventTouchesData touchesData(touches, event);
                    BasicScriptData data((void*)self,(void*)&touchesData);
                    LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                };
                
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
            }
                break;
            default:
                break;
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerTouchAllAtOnce:registerScriptHandler",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerTouchAllAtOnce_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerTouchAllAtOnce(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerTouchAllAtOnce");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerTouchAllAtOnce_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerTouchAllAtOnce_registerScriptHandler);
        tolua_function(tolua_S, "clone", tolua_cocos2dx_EventListenerTouchAllAtOnce_clone);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_EventListenerMouse_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerMouse", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::EventListenerMouse* tolua_ret = cocos2d::EventListenerMouse::create();
        if(nullptr == tolua_ret)
            return 0;

        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerMouse");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerMouse:create",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerMouse_create'.",&tolua_err);
    return 0;
#endif
}

static void cloneMouseHandler(const EventListenerMouse* src,EventListenerMouse* dst,  ScriptHandlerMgr::HandlerType type)
{
    if (nullptr == src || nullptr == dst)
        return;
    
    LUA_FUNCTION handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)src, type);
    if (0 != handler)
    {
        int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)dst, newscriptHandler, type);
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN:
                {
                    dst->onMouseDown = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)dst,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP:
                {
                    dst->onMouseUp = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)dst,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE:
                {
                    dst->onMouseMove = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)dst,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL:
                {
                    dst->onMouseScroll = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)dst,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            default:
                break;
        }
    }
}

static int tolua_cocos2dx_EventListenerMouse_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerMouse* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerMouse", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerMouse*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerMouse_clone'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerMouse* tolua_ret = cocos2d::EventListenerMouse::create();
        if(nullptr == tolua_ret)
            return 0;
        
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN);
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE);
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL);
        cloneMouseHandler(self, tolua_ret, ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP);
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerMouse");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerMouse:clone", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerMouse_clone'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2dx_EventListenerMouse_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerMouse* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerMouse", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerMouse*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerMouse_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        ScriptHandlerMgr::HandlerType type = static_cast<ScriptHandlerMgr::HandlerType>((int)tolua_tonumber(tolua_S, 3, 0) ) ;
        
        switch (type)
        {
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_DOWN:
                {
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                
                    self->onMouseDown = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)self,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_UP:
                {
                    self->onMouseUp = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)self,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_MOVE:
                {
                    self->onMouseMove = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)self,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                }
                break;
            case ScriptHandlerMgr::HandlerType::EVENT_MOUSE_SCROLL:
                {
                    self->onMouseScroll = [=](Event* event){
                        LuaEventMouseData mouseData(event);
                        BasicScriptData data((void*)self,(void*)&mouseData);
                        LuaEngine::getInstance()->handleEvent(type, (void*)&data);
                    };
                
                    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
                }
                break;
            default:
                break;
        }
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerMouse:registerScriptHandler",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerMouse_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerMouse(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerMouse");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerMouse_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerMouse_registerScriptHandler);
        tolua_function(tolua_S, "clone", tolua_cocos2dx_EventListenerMouse_clone);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_ActionCamera_reverse(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::ActionCamera* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ActionCamera",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ActionCamera*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2dx_ActionCamera_reverse'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        cocos2d::ActionCamera* reverse = cobj->reverse();
        toluafix_pushusertype_ccobject(tolua_S, reverse->_ID, &(reverse->_luaID), (void*)(reverse),"cc.ActionCamera");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.ActionCamera:reverse",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_ActionCamera_reverse'.",&tolua_err);
#endif
    return 0;
}

static void extendActionCamera(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ActionCamera");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "reverse", tolua_cocos2dx_ActionCamera_reverse);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_GridAction_reverse(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    cocos2d::GridAction* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GridAction",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GridAction*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'tolua_cocos2dx_GridAction_reverse'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        cocos2d::GridAction* reverse = cobj->reverse();
        toluafix_pushusertype_ccobject(tolua_S, reverse->_ID, &(reverse->_luaID), (void*)(reverse),"cc.GridAction");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GridAction:reverse",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_GridAction_reverse'.",&tolua_err);
#endif
    return 0;
}

static void extendGridAction(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.GridAction");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "reverse", tolua_cocos2dx_GridAction_reverse);
    }
    lua_pop(tolua_S, 1);
}

static int lua_cocos2dx_Label_createWithTTF00(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc >= 2 && argc <= 4)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(L, 2, 0, &tolua_err)  ||
            !tolua_isstring(L, 3, 0, &tolua_err) ||
            !tolua_isnumber(L, 4, 1, &tolua_err) ||
            !tolua_isnumber(L, 5, 1, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        TTFConfig ttfConfig("");
        std::string text = "";

        ok &= luaval_to_ttfconfig(L, 2, &ttfConfig, "cc.Label:createWithTTF");
        if (!ok)
            return 0;
        
        ok &= luaval_to_std_string(L, 3, &text,  "cc.Label:createWithTTF");
        if (!ok)
            return 0;
        
        
        int alignment = tolua_tonumber(L, 4, 1);
        int lineSize  = tolua_tonumber(L, 5, 0);
        cocos2d::Label* ret = cocos2d::Label::createWithTTF(ttfConfig, text, static_cast<TextHAlignment>(alignment), lineSize);
        int ID = ret ? (int)(ret->_ID) : -1;
        int* luaID = ret ? &(ret->_luaID) : nullptr;
        toluafix_pushusertype_ccobject(L,ID, luaID, (void*)ret,"cc.Label");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cc.Label:createWithTTF",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Label_createWithTTF'.",&tolua_err);
#endif
    return 0;
}

static int lua_cocos2dx_Label_createWithTTF01(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    
    tolua_Error tolua_err;
    if (!tolua_isusertable(L,1,"cc.Label",0,&tolua_err)) goto tolua_lerror;
    
    argc = lua_gettop(L) - 1;
    
    if (argc >= 3 && argc <= 6)
    {
        if (!tolua_isstring(L, 2, 0, &tolua_err)  ||
            !tolua_isstring(L, 3, 0, &tolua_err)  ||
            !tolua_isnumber(L, 4, 0, &tolua_err)  ||
            !tolua_istable(L, 5, 1, &tolua_err)   ||
            !tolua_isnumber(L, 6, 1, &tolua_err)  ||
            !tolua_isnumber(L, 7, 1, &tolua_err) )
        {
            goto tolua_lerror;
        }
        else
        {
            std::string text = tolua_tostring(L, 2, "");
            std::string fontFile = tolua_tostring(L, 3, "");
            float fontSize   = tolua_tonumber(L, 4, 0);
            cocos2d::Size dimensions = cocos2d::Size::ZERO;
            if (lua_istable(L, 5))
            {
                luaval_to_size(L, 5, &dimensions,  "cc.Label:createWithTTF");
            }
            TextHAlignment hAlignment = static_cast<TextHAlignment>((int)tolua_tonumber(L, 6, 0));
            TextVAlignment vAlignment = static_cast<TextVAlignment>((int)tolua_tonumber(L, 7, 0));
            
            cocos2d::Label* ret = cocos2d::Label::createWithTTF(text, fontFile, fontSize, dimensions, hAlignment, vAlignment);
            
            int ID = ret ? (int)(ret->_ID) : -1;
            int* luaID = ret ? &(ret->_luaID) : nullptr;
            toluafix_pushusertype_ccobject(L,ID, luaID, (void*)ret,"cc.Label");
            return 1;
        }
    }
    
tolua_lerror:
    return lua_cocos2dx_Label_createWithTTF00(L);
}

static void extendLabel(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Label");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "createWithTTF", lua_cocos2dx_Label_createWithTTF00);
        tolua_function(tolua_S, "createWithTTF", lua_cocos2dx_Label_createWithTTF01);
    }
    lua_pop(tolua_S, 1);
}

static int lua_cocos2dx_TMXTiledMap_getPropertiesForGID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXTiledMap* cobj = NULL;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_TMXTiledMap_getPropertiesForGID'", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0,  "cc.TMXTiledMap:getPropertiesForGID");
            
        if (!ok)
            return 0;
        cocos2d::Value ret = cobj->getPropertiesForGID(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXTiledMap:getPropertiesForGID",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_TMXTiledMap_getPropertiesForGID'.",&tolua_err);
#endif
    
    return 0;
}

static void extendTMXTiledMap(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.TMXTiledMap");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "getPropertiesForGID", lua_cocos2dx_TMXTiledMap_getPropertiesForGID);
    }
    lua_pop(tolua_S, 1);
}

static int lua_cocos2dx_Console_send(lua_State* tolua_S)
{
    cocos2d::Console* cobj = nullptr;
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Console",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Console*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Console_send'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    
    if (argc == 2)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,&arg0, "cc.Console:send");
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "cc.Console:send");
        if(!ok)
            return 0;
        
        send(arg0, arg1.c_str(), arg1.length(), 0);
        return 0;
    }
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "cc.Console:send",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Console_send'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_cocos2dx_Console_wait(lua_State* tolua_S)
{
    cocos2d::Console* cobj = nullptr;
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Console",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::Console*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Console_wait'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    
    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,&arg0, "cc.Console:wait");
        if(!ok)
            return 0;
        
        std::chrono::milliseconds dura( arg0 * 1000 );
        std::this_thread::sleep_for( dura );
        return 0;
    }
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "cc.Console:wait",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Console_wait'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_cocos2dx_Console_addCommand(lua_State* tolua_S)
{
    cocos2d::Console* cobj = nullptr;
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Console",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Console*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Console_addCommand'", NULL);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (ok && argc == 2)
    {
        ValueMap arg0;
        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "cc.Console:addCommand");
        //
        std::string name = std::string(arg0["name"].asString());
        std::string help = std::string(arg0["help"].asString());
        
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = 0;
        if (ok) {
            handler = (  toluafix_ref_function(tolua_S,3,0));
            ScriptHandlerMgr::getInstance()->addCustomHandler((void*)cobj, handler);
            
            struct Console::Command outValue = {
                name,
                help,
                [=](int fd, const std::string& args)
                {
                    //lua-callback, the third param;
                    tolua_pushnumber(tolua_S, fd);
                    tolua_pushstring(tolua_S, args.c_str());
                    
                    LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
                }
            };
            cobj->addCommand(outValue);
        }
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "cc.Console:addCommand",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Console_addCommand'.",&tolua_err);
#endif
    
    return 0;
}

static void extendConsole(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Console");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S,"wait", lua_cocos2dx_Console_wait);
        tolua_function(tolua_S,"send", lua_cocos2dx_Console_send);
        tolua_function(tolua_S,"addCommand", lua_cocos2dx_Console_addCommand);
    }
    lua_pop(tolua_S, 1);
}

static int lua_cocos2dx_GLProgramState_setVertexAttribPointer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::GLProgramState* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.GLProgramState",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::GLProgramState*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_GLProgramState_setVertexAttribPointer'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 6)
    {
        std::string arg0;
        int arg1;
        unsigned int arg2;
        bool arg3;
        int arg4;
        int arg5;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_boolean(tolua_S, 5, &arg3, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_int32(tolua_S, 7, (int *)&arg5, "cc.GLProgramState:setVertexAttribPointer");
        
        if(!ok)
            return 0;
        cobj->setVertexAttribPointer(arg0, arg1, arg2, arg3, arg4, (void*)&arg5);
        return 0;
    }
    else if (argc == 7)
    {
        std::string arg0;
        int arg1;
        unsigned int arg2;
        bool arg3;
        int arg4;
        GLfloat* arg5;
        int arg6;
        
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_boolean(tolua_S, 5, &arg3, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "cc.GLProgramState:setVertexAttribPointer");
        
        ok &= luaval_to_int32(tolua_S, 8, (int *)&arg6, "cc.GLProgramState:setVertexAttribPointer");
        
        size_t len = lua_objlen(tolua_S, 7);
        
        if (len != arg6)
        {
            CCLOG("table size is  %zu,but input size is %d \n", len, arg6);
            return 0;
        }
        
        arg5 = new GLfloat[len];
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S,i + 1);
            lua_gettable(tolua_S,7);
            bool isnum = true;
#if COCOS2D_DEBUG >= 1
            if (!tolua_isnumber(tolua_S, -1, 0, &tolua_err))
            {
                isnum = false;
            }
#endif
            if (isnum)
            {
                arg5[i] = tolua_tonumber(tolua_S, -1, 0);
            }
            else
            {
                arg5[i] = 0;
            }
            lua_pop(tolua_S, 1);
        }
        
        cobj->setVertexAttribPointer(arg0, arg1, arg2, arg3, arg4, (void*)arg5);
        
        CC_SAFE_DELETE(arg5);
        
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.GLProgramState:setVertexAttribPointer",argc, 6);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_GLProgramState_setVertexAttribPointer'.",&tolua_err);
#endif
    
    return 0;
}

static void extendGLProgramState(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.GLProgramState");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S,"setVertexAttribPointer", lua_cocos2dx_GLProgramState_setVertexAttribPointer);
    }
    lua_pop(tolua_S, 1);
}

static int lua_cocos2dx_OrbitCamera_sphericalRadius(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::OrbitCamera* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.OrbitCamera",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (cocos2d::OrbitCamera*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!self)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_OrbitCamera_sphericalRadius'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 3)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 4, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        float newRadius = (float)tolua_tonumber(tolua_S, 2, 0);
        float zenith    = (float)tolua_tonumber(tolua_S, 3, 0);
        float azimuth   = (float)tolua_tonumber(tolua_S, 4, 0);
        
        self->sphericalRadius(&newRadius, &zenith, &azimuth);
        
        tolua_pushnumber(tolua_S, (lua_Number)newRadius);
        tolua_pushnumber(tolua_S, (lua_Number)zenith);
        tolua_pushnumber(tolua_S, (lua_Number)azimuth);
        
        return 3;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.OrbitCamera:sphericalRadius",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_OrbitCamera_sphericalRadius'.",&tolua_err);
#endif
    
    return 0;
}

static void extendOrbitCamera(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.OrbitCamera");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S,"sphericalRadius", lua_cocos2dx_OrbitCamera_sphericalRadius);
    }
    lua_pop(tolua_S, 1);
}

int lua_cocos2dx_TMXLayer_getTileGIDAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXLayer* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::TMXLayer*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_TMXLayer_getTileGIDAt'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;
        
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TMXLayer:getTileGIDAt");
        if(!ok)
            return 0;
        unsigned int ret = cobj->getTileGIDAt(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        tolua_pushnumber(tolua_S,(lua_Number)0);
        return 2;
    }
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        int arg1;
        
        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "cc.TMXLayer:getTileGIDAt");
        ok &= luaval_to_int32(tolua_S, 3, &arg1, "cc.TMXLayer:getTileGIDAt");
        
        if(!ok)
            return 0;
        
        unsigned int ret = cobj->getTileGIDAt(arg0, (cocos2d::TMXTileFlags*)&arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        tolua_pushnumber(tolua_S,(lua_Number)arg1);
        return 2;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayer:getTileGIDAt",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_TMXLayer_getTileGIDAt'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_TMXLayer_setTiles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::TMXLayer* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::TMXLayer*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_TMXLayer_setTiles'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        uint32_t* arg0 = nullptr;
#if COCOS2D_DEBUG >= 1
        if (!tolua_istable(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        
        size_t len = lua_objlen(tolua_S, 2);
        if (len == 0 )
        {
            CCLOG("Table's len equal 0");
            return 0;
        }
        arg0 = new uint32_t[len];
        
        if (nullptr == arg0)
        {
            CCLOG("Allocate uint32_t array in the lua_cocos2dx_TMXLayer_setTiles failed!");
            return 0;
        }
        
        for (int i = 1 ; i <= len; i++)
        {
            arg0[i - 1] = (uint32_t)tolua_tofieldnumber(tolua_S, 2, i, 0);
        }
        
        cobj->setTiles(arg0);
        
        CC_SAFE_DELETE_ARRAY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.TMXLayer:setTiles",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_TMXLayer_setTiles'.",&tolua_err);
#endif
    
    return 0;
}

static void extendTMXLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.TMXLayer");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S,"getTileGIDAt", lua_cocos2dx_TMXLayer_getTileGIDAt);
        tolua_function(tolua_S, "setTiles", lua_cocos2dx_TMXLayer_setTiles);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2dx_EventListenerFocus_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "cc.EventListenerFocus", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerFocus* tolua_ret = cocos2d::EventListenerFocus::create();
        if(nullptr == tolua_ret)
            return 0;
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerFocus");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerFocus:create", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerFocus_create'.",&tolua_err);
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
            lua_State* tolua_S = LuaEngine::getInstance()->getLuaStack()->getLuaState();
            int id = (widgetLostFocus) ? (int)widgetLostFocus->_ID : -1;
            int* luaID = (widgetLostFocus) ? &widgetLostFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(tolua_S, id, luaID, (void*)widgetLostFocus,"ccui.Widget");
            id = (widgetGetFocus) ? (int)widgetGetFocus->_ID : -1;
            luaID = (widgetGetFocus) ? &widgetGetFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(tolua_S, id, luaID, (void*)widgetGetFocus,"ccui.Widget");
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
    }
}

static int tolua_cocos2dx_EventListenerFocus_clone(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerFocus* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerFocus", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerFocus*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerFocus_clone'\n", nullptr);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerFocus* tolua_ret = cocos2d::EventListenerFocus::create();
        if(nullptr == tolua_ret)
            return 0;
        
        cloneFocusHandler(self, tolua_ret);
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.EventListenerFocus");
        
        return 1;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerFocus:clone", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerFocus_clone'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2dx_EventListenerFocus_registerScriptHandler(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    EventListenerFocus* self = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "cc.EventListenerFocus", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    self = static_cast<EventListenerFocus*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_EventListenerFocus_registerScriptHandler'\n", nullptr);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::EVENT_FOCUS);
        
        self->onFocusChanged = [=](ui::Widget* widgetLostFocus, ui::Widget* widgetGetFocus){
            int id = (widgetLostFocus) ? (int)widgetLostFocus->_ID : -1;
            int* luaID = (widgetLostFocus) ? &widgetLostFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(tolua_S, id, luaID, (void*)widgetLostFocus,"ccui.Widget");
            id = (widgetGetFocus) ? (int)widgetGetFocus->_ID : -1;
            luaID = (widgetGetFocus) ? &widgetGetFocus->_luaID : nullptr;
            toluafix_pushusertype_ccobject(tolua_S, id, luaID, (void*)widgetGetFocus,"ccui.Widget");
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n", "cc.EventListenerFocus:registerScriptHandler", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_EventListenerFocus_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerFocus(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EventListenerFocus");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerFocus_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerFocus_registerScriptHandler);
        tolua_function(tolua_S, "clone", tolua_cocos2dx_EventListenerFocus_clone);
    }
    lua_pop(tolua_S, 1);
}


int lua_cocos2dx_Application_isIOS64bit(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::Application* cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.Application",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::Application*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Application_isIOS64bit'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        bool isIOS64bit = false;
        Application::Platform platform = cocos2d::Application::getInstance()->getTargetPlatform();
        if (Application::Platform::OS_IPHONE == platform || Application::Platform::OS_IPAD == platform)
        {
#if defined(__LP64__)
            isIOS64bit = true;
#endif
        }

        tolua_pushboolean(tolua_S, isIOS64bit);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cc.Application:isIOS64bit",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Application_isIOS64bit'.",&tolua_err);
#endif
    
    return 0;
}

static void extendApplication(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Application");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "isIOS64bit", lua_cocos2dx_Application_isIOS64bit);
    }
    lua_pop(tolua_S, 1);
}

static int lua_cocos2dx_TextureCache_addImageAsync(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0 ;
    
    int argc = 0;
    TextureCache* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.TextureCache",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<TextureCache*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'lua_cocos2dx_TextureCache_addImageAsync'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err)  ||
            !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* configFilePath = tolua_tostring(tolua_S, 2, "");
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S, 3, 0));
        
        
        self->addImageAsync(configFilePath, [=](Texture2D* tex){
            int ID = (tex) ? (int)tex->_ID : -1;
            int* luaID = (tex) ? &tex->_luaID : nullptr;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tex, "cc.Texture2D");
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler,1);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        });
        
        return 0;
    }
    
    CCLOG("%s function of TextureCache has wrong number of arguments: %d, was expecting %d\n", "cc.TextureCache:addImageAsync", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_TextureCache_addImageAsync'.",&tolua_err);
#endif
    return 0;
}

static void extendTextureCache(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.TextureCache");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addImageAsync", lua_cocos2dx_TextureCache_addImageAsync);
    }
    lua_pop(tolua_S, 1);
}

int register_all_cocos2dx_manual(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    extendNode(tolua_S);
    extendLayer(tolua_S);
    extendMenuItem(tolua_S);
    extendMenuItemImage(tolua_S);
    extendMenuItemLabel(tolua_S);
    extendMenuItemFont(tolua_S);
    extendMenuItemSprite(tolua_S);
    extendMenuItemToggle(tolua_S);
    extendMenu(tolua_S);
    extendScheduler(tolua_S);
    extendSequence(tolua_S);
    extendCallFunc(tolua_S);
    extendSpawn(tolua_S);
    extendCardinalSplineBy(tolua_S);
    extendCatmullRomBy(tolua_S);
    extendCatmullRomTo(tolua_S);
    extendBezierBy(tolua_S);
    extendBezierTo(tolua_S);
    extendDrawNode(tolua_S);
    extendSprite(tolua_S);
    extendLayerColor(tolua_S);
    extendLayerMultiplex(tolua_S);
    extendParticleSystem(tolua_S);
    extendFileUtils(tolua_S);
    extendUserDefault(tolua_S);
    extendGLProgram(tolua_S);
    extendTexture2D(tolua_S);
    extendSpriteBatchNode(tolua_S);
    extendEventListenerKeyboard(tolua_S);
    extendEventListenerTouchOneByOne(tolua_S);
    extendEventListenerTouchAllAtOnce(tolua_S);
    extendEventListenerMouse(tolua_S);
    extendEventListenerCustom(tolua_S);
    extendEventListenerAcceleration(tolua_S);
    extendActionCamera(tolua_S);
    extendGridAction(tolua_S);
    
    extendMotionStreak(tolua_S);
    extendAtlasNode(tolua_S);
    extendParticleBatchNode(tolua_S);
    extendLabel(tolua_S);
    extendTMXTiledMap(tolua_S);
    extendConsole(tolua_S);
    extendGLProgramState(tolua_S);
    extendOrbitCamera(tolua_S);
    extendTMXLayer(tolua_S);
    extendEventListenerFocus(tolua_S);
    extendApplication(tolua_S);
    extendTextureCache(tolua_S);
    
    return 0;
}

static int tolua_cocos2d_utils_captureScreen(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_istable(tolua_S,1,0, &tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isstring(tolua_S, 3, 0, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S,2,0);
        std::string  fileName = tolua_tocppstring(tolua_S, 3, "");
        cocos2d::utils::captureScreen([=](bool succeed, const std::string& name ){
            
            tolua_pushboolean(tolua_S, succeed);
            tolua_pushstring(tolua_S, name.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        }, fileName);
        
        return 0;
    }
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_utils_captureScreen'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_utils_findChildren(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_istable(tolua_S,1,0, &tolua_err) ||
        !tolua_isusertype(tolua_S, 2, "cc.Node", 0, &tolua_err) ||
        !tolua_isstring(tolua_S, 3, 0, &tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        cocos2d::Node* node = static_cast<Node*>(tolua_tousertype(tolua_S, 2, nullptr));
        std::string  name = tolua_tocppstring(tolua_S, 3, "");
        std::vector<Node*> children = cocos2d::utils::findChildren(*node, name);
        lua_newtable(tolua_S);
        int index = 1;
        for (const auto& obj : children)
        {
            if (nullptr == obj)
                continue;
            
            lua_pushnumber(tolua_S, (lua_Number)index);
            int ID = (obj) ? (int)obj->_ID : -1;
            int* luaID = (obj) ? &obj->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)obj, "cc.Node");
            lua_rawset(tolua_S, -3);
            ++index;
        }
        return 1;
    }
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_utils_findChildren'.",&tolua_err);
    return 0;
#endif
}

int register_all_cocos2dx_module_manual(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    tolua_open(tolua_S);
    tolua_module(tolua_S, "cc", 0);
    tolua_beginmodule(tolua_S, "cc");
        tolua_module(tolua_S, "utils", 0);
        tolua_beginmodule(tolua_S,"utils");
            tolua_function(tolua_S, "captureScreen", tolua_cocos2d_utils_captureScreen);
            tolua_function(tolua_S, "findChildren", tolua_cocos2d_utils_findChildren);
        tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    
    return 0;
}
