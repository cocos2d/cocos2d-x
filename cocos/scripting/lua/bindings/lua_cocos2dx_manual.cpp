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

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

static int tolua_cocos2d_MenuItemImage_create(lua_State* tolua_S)
{
    if (NULL == tolua_S) 
        return 0;

    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"MenuItemImage",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    do {
        if (argc == 0)
        {
            MenuItemImage* tolua_ret = (MenuItemImage*)MenuItemImage::create();
            //Uncheck
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
            return 1;
        }
    } while (0);
    do {
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
        
    } while (0);
    do {
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemImage");
        return 1;
        
    } while (0);

	CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
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
	if (!tolua_isusertable(tolua_S,1,"MenuItemLabel",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(1 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        Node* label = ((Node*)  tolua_tousertype(tolua_S,2,0));
        MenuItemLabel* tolua_ret = (MenuItemLabel*)  MenuItemLabel::create(label);
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemLabel");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
	if (!tolua_isusertable(tolua_S,1,"MenuItemFont",0,&tolua_err)) goto tolua_lerror;
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemFont");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
	if (!tolua_isusertable(tolua_S,1,"MenuItemSprite",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(argc >= 2 && argc <= 3)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
            !tolua_isusertype(tolua_S,3,"Node",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
        
        if (3 == argc && !tolua_isusertype(tolua_S,4,"Node",0,&tolua_err))
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemSprite");
        return 1;
    }
    
    CCLOG("create has wrong number of arguments: %d, was expecting %d\n", argc, 3);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
	if (!tolua_isusertable(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if (argc > 0 )
    {
        Vector<MenuItem*> items;
        uint32_t i = 1;
        while (i <= argc)
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(tolua_S, 1 + i, "MenuItem", 0, &tolua_err))
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Menu");
        return 1;
    }
    else if(argc == 0)
    {
        cocos2d::Menu* tolua_ret = cocos2d::Menu::create();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Menu");
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
	if (!tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
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
	if (!tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err)) goto tolua_lerror;
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
	tolua_error(tolua_S,"#ferror in function 'alignItemsInColumns'.\n",&tolua_err);
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
	if (!tolua_isusertable(tolua_S,1,"MenuItemToggle",0,&tolua_err)) goto tolua_lerror;
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
            if (!tolua_isusertype(tolua_S, i + 2,"MenuItem",0,&tolua_err) )
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"MenuItemToggle");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"MenuItem",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'registerScriptTapHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTapHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"MenuItem",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'unregisterScriptTapHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptTapHandler'.",&tolua_err);
    return 0;
#endif
}


static int executeScriptTouchHandler(Layer* layer, EventTouch::EventCode eventType, Touch* touch)
{
    TouchScriptData data(eventType, layer, touch);
    ScriptEvent event(kTouchEvent, &data);
    return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
}

static int executeScriptTouchesHandler(Layer* layer, EventTouch::EventCode eventType, const std::vector<Touch*>& touches)
{
    TouchesScriptData data(eventType, layer, touches);
    ScriptEvent event(kTouchesEvent, &data);
    return ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
}

static void setTouchEnabledForLayer(Layer* layer, bool enabled)
{
    if (nullptr == layer)
        return;
    
    auto dict = static_cast<Dictionary*>(layer->getUserObject());
    if (dict == nullptr)
    {
        dict = Dictionary::create();
        layer->setUserObject(dict);
    }
    
    dict->setObject(Bool::create(enabled), "touchEnabled");
    
    auto touchListenerAllAtOnce = static_cast<EventListenerTouchAllAtOnce*>(dict->objectForKey("touchListenerAllAtOnce"));
    auto touchListenerOneByOne = static_cast<EventListenerTouchOneByOne*>(dict->objectForKey("touchListenerOneByOne"));
    auto touchMode = static_cast<Integer*>(dict->objectForKey("touchMode"));
    auto swallowTouches = static_cast<Bool*>(dict->objectForKey("swallowTouches"));
    auto priority  = static_cast<Integer*>(dict->objectForKey("priority"));
    
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
                executeScriptTouchesHandler(layer, EventTouch::EventCode::BEGAN, touches);
            };
            listener->onTouchesMoved = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::MOVED, touches);
            };
            listener->onTouchesEnded = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::ENDED, touches);
            };
            listener->onTouchesCancelled = [layer](const std::vector<Touch*>& touches, Event* event){
                executeScriptTouchesHandler(layer, EventTouch::EventCode::CANCELLED, touches);
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
                return executeScriptTouchHandler(layer, EventTouch::EventCode::BEGAN, touch) == 0 ? false : true;
            };
            listener->onTouchMoved = [layer](Touch* touch, Event* event){
                executeScriptTouchHandler(layer, EventTouch::EventCode::MOVED, touch);
            };
            listener->onTouchEnded = [layer](Touch* touch, Event* event){
                executeScriptTouchHandler(layer, EventTouch::EventCode::ENDED, touch);
            };
            listener->onTouchCancelled = [layer](Touch* touch, Event* event){
                executeScriptTouchHandler(layer, EventTouch::EventCode::CANCELLED, touch);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'setTouchEnabled' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setTouchEnabled'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("touchEnabled"));
            bool ret = enabled ? enabled->getValue() : false;
            tolua_pushboolean(L, ret);
            return 1;
        }
        
        return 0;
    }
    
    CCLOG("'isTouchEnabled' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'isTouchEnabled'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if ( nullptr == dict)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        
        Integer* touchModeObj = static_cast<Integer*>(dict->objectForKey("touchMode"));
        int32_t touchMode = touchModeObj ? touchModeObj->getValue() : 0;
        if (touchMode != mode)
        {
            dict->setObject(Integer::create(mode), "touchMode");
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
        return 0;
    }
    
    CCLOG("'setTouchMode' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setTouchMode'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            Integer* mode = static_cast<Integer*>(dict->objectForKey("touchMode"));
            ret = mode ? mode->getValue() : 0;
            tolua_pushnumber(L, (lua_Number)ret);
            return 1;
        }
        
        return 0;
    }
    
    CCLOG("'getTouchMode' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'getTouchMode'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        Bool* swallowsTouchesObj = nullptr;
        
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        
        swallowsTouchesObj = static_cast<Bool*>(dict->objectForKey("swallowTouches"));
        bool oldSwallowsTouches = swallowsTouchesObj ? swallowsTouchesObj->getValue() : false;
        
        if (oldSwallowsTouches != swallowsTouches)
        {
            dict->setObject(Integer::create(swallowsTouches), "swallowTouches");
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
        
        return 0;
    }
    
    CCLOG("'setSwallowsTouches' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setSwallowsTouches'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            Bool* swallowTouches = static_cast<Bool*>(dict->objectForKey("swallowTouches"));
            bool ret = swallowTouches ? swallowTouches->getValue() : false;
            lua_pushboolean(L, ret);
            return 1;
        }
        return 0;
    }
    
    CCLOG("'isSwallowsTouches' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'isSwallowsTouches'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = Dictionary::create();
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
    
    CCLOG("'setKeyboardEnabled' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setKeyboardEnabled'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("keyboardEnabled"));
            bool ret = enabled ? enabled->getValue() : false;
            tolua_pushboolean(L, ret);
            return 1;
        }
        return 0;
    }
    
    CCLOG("'isKeyboardEnabled' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'isKeyboardEnabled'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
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
    
    CCLOG("'setAccelerometerEnabled' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setAccelerometerEnabled'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict != nullptr)
        {
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("accelerometerEnabled"));
            bool ret = enabled ? enabled->getValue() : false;
            tolua_pushboolean(L, ret);
            return 1;
        }
        
        return 0;
    }
    
    
    CCLOG("'isAccelerometerEnabled' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'isAccelerometerEnabled'.",&tolua_err);
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
	if (!tolua_isusertype(L,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        Device::setAccelerometerEnabled(interval);
        return 0;
    }
    
    CCLOG("'setAccelerometerInterval' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setAccelerometerInterval'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        
        auto dict = static_cast<Dictionary*>(self->getUserObject());
        if (dict == nullptr)
        {
            dict = Dictionary::create();
            self->setUserObject(dict);
        }
        
        auto touchModeValue = static_cast<Integer*>(dict->objectForKey("touchMode"));
        auto swallowTouchesValue = static_cast<Bool*>(dict->objectForKey("swallowTouches"));
        auto priorityValue = static_cast<Integer*>(dict->objectForKey("priority"));
        
        //touch model
        int32_t mode = touchModeValue?touchModeValue->getValue() : 0;
        if (mode != (int)touchesMode)
        {
            dict->setObject(Integer::create((int)touchesMode), "touchMode");
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("touchEnabled"));
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
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("touchEnabled"));
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
            Bool* enabled = static_cast<Bool*>(dict->objectForKey("touchEnabled"));
            if (enabled && enabled->getValue())
            {
                setTouchEnabledForLayer(self, false);
                setTouchEnabledForLayer(self, true);
            }
        }
		
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::HandlerType::TOUCHES);
        return 0;
    }
    
    CCLOG("'registerScriptTouchHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTouchHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
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
    
    CCLOG("'unregisterScriptTouchHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptTapHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'registerScriptKeypadHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptKeypadHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
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

    CCLOG("'unregisterScriptKeypadHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptKeypadHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'registerScriptAccelerateHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptAccelerateHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Layer",0,&tolua_err)) goto tolua_lerror;
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
        auto dict = static_cast<Dictionary*>(self->getUserObject());
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
    
    CCLOG("'unregisterScriptAccelerateHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptAccelerateHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Scheduler",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'scheduleScriptFunc' has wrong number of arguments: %d, was expecting %d\n", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'scheduleScriptFunc'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Scheduler",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'unscheduleScriptEntry' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unscheduleScriptEntry'.",&tolua_err);
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
	if (!tolua_isusertable(tolua_S,1,"Sequence",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    if(argc > 0)
    {
        Vector<FiniteTimeAction*> array;

        if (1 == argc && tolua_istable(tolua_S, 2, 0, &tolua_err))
        {
            luaval_to_ccvector(tolua_S, 2, &array);
        }
        else
        {
            uint32_t i = 1;
            while (i <= argc)
            {
#if COCOS2D_DEBUG >= 1
                if (!tolua_isusertype(tolua_S, 1 + i, "FiniteTimeAction", 0, &tolua_err))
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
        
        cocos2d::Sequence* tolua_ret = cocos2d::Sequence::create(array);
        //issue 2433 uncheck
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Sequence");
        return 1;
    }
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
	if (!tolua_isusertable(tolua_S,1,"CallFunc",0,&tolua_err)) goto tolua_lerror;
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
                    stack->pushObject(target, "Node");
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CallFunc");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'unregisterScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
        if (luaval_to_int32(tolua_S, 3, &priority))
        {
           self->scheduleUpdateWithPriorityLua(handler,priority);
        }
        return 0;
    }
    
    CCLOG("'scheduleUpdateWithPriorityLua' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'scheduleUpdateWithPriorityLua'.",&tolua_err);
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
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'unscheduleUpdate' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unscheduleUpdate'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
        ok &= luaval_to_size(tolua_S, 2, &size);
        if (!ok)
            return 0;
        
        cobj->setContentSize(size);
        return 0;
    }
    else if(2 == argc)
    {
        double width;
        ok &= luaval_to_number(tolua_S, 2,&width);
        
        if (!ok)
            return 0;
        
        double height;
        ok &= luaval_to_number(tolua_S, 3,&height);
        
        if (!ok)
            return 0;
        
        cobj->setContentSize(Size(width, height));
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setContentSize",argc, 1);
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
    if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
        cocos2d::Point pt;
        ok &= luaval_to_point(tolua_S, 2, &pt);
        if (!ok)
            return 0;
        
        cobj->setAnchorPoint(pt);
        return 0;
    }
    else if(2 == argc)
    {
        double x;
        ok &= luaval_to_number(tolua_S, 2,&x);
        
        if (!ok)
            return 0;
        
        double y;
        ok &= luaval_to_number(tolua_S, 3,&y);
        
        if (!ok)
            return 0;
        
        cobj->setAnchorPoint(Point(x,y));
        return 0;
    }
    
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAnchorPoint",argc, 1);
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
	if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'getPosition' function in Node has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_Spawn_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
    tolua_Error tolua_err;
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Spawn",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc > 0)
    {
        Vector<FiniteTimeAction*> array;        
        uint32_t i = 1;
        
        if (1 == argc && tolua_istable(tolua_S, 2, 0, &tolua_err))
        {
            luaval_to_ccvector(tolua_S, 2, &array);
        }
        else
        {
            while (i <= argc)
            {
#if COCOS2D_DEBUG >= 1
                if (!tolua_isusertype(tolua_S, 1 + i, "FiniteTimeAction", 0, &tolua_err))
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"Spawn");
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"CardinalSplineBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 3)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        double ten = 0.0;
        ok &= luaval_to_number(tolua_S, 4, &ten);
        if (!ok)
            return false;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                free(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            free(arr);
            CardinalSplineBy* tolua_ret = CardinalSplineBy::create(dur, points, ten);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CardinalSplineBy");
                return 1;
            }
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"CatmullRomBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                free(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            free(arr);
            CatmullRomBy* tolua_ret = CatmullRomBy::create(dur, points);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CatmullRomBy");
                return 1;
            }
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"CatmullRomTo",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double dur = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &dur);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num > 0)
        {
            PointArray* points = PointArray::create(num);
            
            if (NULL == points)
            {
                free(arr);
                return 0;
            }
            
            for( int i = 0; i < num; i++) {
                points->addControlPoint(arr[i]);
            }
            
            free(arr);
            CatmullRomTo* tolua_ret = CatmullRomTo::create(dur, points);
            if (NULL != tolua_ret)
            {
                int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
                int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
                toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CatmullRomTo");
                return 1;
            }
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"BezierBy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double t = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &t);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num < 3)
        {
            free(arr);
            return false;
        }
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        free(arr);
        
        BezierBy* tolua_ret = BezierBy::create(t, config);
        if (NULL != tolua_ret)
        {
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"BezierBy");
            return 1;
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"BezierTo",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 2)
    {
        double t = 0.0;
        ok &= luaval_to_number(tolua_S, 2, &t);
        if (!ok)
            return false;
        
        int num = 0;
        Point *arr = NULL;
        ok &= luaval_to_array_of_Point(tolua_S, 3, &arr, &num);
        if (!ok)
            return false;
        
        if (num < 3)
        {
            free(arr);
            return false;
        }
        
        ccBezierConfig config;
        config.controlPoint_1 = arr[0];
        config.controlPoint_2 = arr[1];
        config.endPosition = arr[2];
        free(arr);
        
        BezierTo* tolua_ret = BezierTo::create(t, config);
        if (NULL != tolua_ret)
        {
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"BezierTo");
            return 1;
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"DrawNode",0,&tolua_err)) goto tolua_lerror;
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
            Point* points = new Point[size];
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
                
                if(!luaval_to_point(tolua_S, lua_gettop(tolua_S), &points[i]))
                {
                    lua_pop(tolua_S, 1);
                    CC_SAFE_DELETE_ARRAY(points);
                    return 0;
                }
                lua_pop(tolua_S, 1);
            }
            
            Color4F fillColor;
            if (!luaval_to_color4f(tolua_S, 4, &fillColor))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }
            
            float borderWidth  = (float)tolua_tonumber(tolua_S, 5, 0);
            
            Color4F borderColor;
            if (!luaval_to_color4f(tolua_S, 6, &borderColor))
            {
                CC_SAFE_DELETE_ARRAY(points);
                return 0;
            }
            
            self->drawPolygon(points, size, fillColor, borderWidth, borderColor);
            CC_SAFE_DELETE_ARRAY(points);
            return 0;
        }        
    }
    
    CCLOG("'drawPolygon' has wrong number of arguments: %d, was expecting %d\n", argc, 5);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'drawPolygon'.",&tolua_err);
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
        if (!luaval_to_int32(tolua_S, 2, (int32_t*)&src))
            return 0;
        
        if (!luaval_to_int32(tolua_S, 3, (int32_t*)&dst))
            return 0;
        
        BlendFunc blendFunc = {src, dst};
        self->setBlendFunc(blendFunc);
        return 0;
    }

    
    CCLOG("'setBlendFunc' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2dx_Sprite_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<Sprite>(tolua_S,"Sprite");
}

static int tolua_cocos2dx_SpriteBatchNode_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<SpriteBatchNode>(tolua_S,"SpriteBatchNode");
}

static int tolua_cocos2dx_MotionStreak_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<MotionStreak>(tolua_S,"MotionStreak");
}

static int tolua_cocos2dx_AtlasNode_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<AtlasNode>(tolua_S,"AtlasNode");
}

static int tolua_cocos2dx_ParticleBatchNode_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<ParticleBatchNode>(tolua_S,"ParticleBatchNode");
}

static int tolua_cocos2dx_LayerColor_setBlendFunc(lua_State* tolua_S)
{
    return tolua_cocos2dx_setBlendFunc<LayerColor>(tolua_S,"LayerColor");
}

static int tolua_cocos2dx_ParticleSystem_setBlendFunc(lua_State* tolua_S) 
{
    return tolua_cocos2dx_setBlendFunc<ParticleSystem>(tolua_S,"ParticleSystem");
}

static int tolua_cocos2dx_DrawNode_setBlendFunc(lua_State* tolua_S) 
{
    return tolua_cocos2dx_setBlendFunc<DrawNode>(tolua_S,"DrawNode");
}

static int tolua_cocos2dx_LayerMultiplex_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    Vector<Layer*> arg0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "LayerMultiplex", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
 
    if (argc > 0)
    {
        if (luavals_variadic_to_ccvector(tolua_S, argc, &arg0))
        {
            LayerMultiplex* tolua_ret =  LayerMultiplex::createWithArray(arg0);
            int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"LayerMultiplex");
            return 1;
        }
        else
        {
            CCLOG("error in tolua_cocos2dx_LayerMultiplex_create \n");
            return 0;
        }
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"FileUtils",0,&tolua_err)) goto tolua_lerror;
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
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if (ok)
        {
            std::string fullPathName = FileUtils::getInstance()->fullPathForFilename(arg0);
            String* contentsOfFile = String::createWithContentsOfFile(fullPathName.c_str());
            if (nullptr != contentsOfFile)
            {
                const char* tolua_ret = contentsOfFile->getCString();
                tolua_pushstring(tolua_S, tolua_ret);
            }
            return 1;
        }
    }
    
    CCLOG("'getStringFromFile' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getStringFromFile'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"UserDefault",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(0 == argc)
    {
        UserDefault* tolua_ret = (UserDefault*)  UserDefault::getInstance();
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"UserDefault");
        return 1;
    }
    
    CCLOG("'getInstance' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S,1,"GLProgram",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if(2 == argc)
    {
        const char *arg0, *arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        
        GLProgram* tolua_ret = new GLProgram();
        if (nullptr == tolua_ret)
            return 0;        

        tolua_ret->autorelease();
        tolua_ret->initWithVertexShaderFilename(arg0, arg1);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"GLProgram");
        return 1;
        
    }
    
    CCLOG("'create' function of GLProgram wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"GLProgram",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'getProgram' function of GLProgram wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getProgram'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S,1,"GLProgram",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'setUniformLocationF32' function of GLProgram wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setUniformLocationF32'.",&tolua_err);
    return 0;
#endif    
    
}

static void extendGLProgram(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "GLProgram");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"create");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_GLProgram_create );
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"getProgram");
        lua_pushcfunction(tolua_S,tolua_cocos2d_GLProgram_getProgram );
        lua_rawset(tolua_S,-3);
        
        lua_pushstring(tolua_S,"setUniformLocationF32");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_GLProgram_setUniformLocationF32 );
        lua_rawset(tolua_S,-3);
    }
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
    if (!tolua_isusertype(tolua_S,1,"Texture2D",0,&tolua_err)) goto tolua_lerror;
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
    if (!tolua_isusertype(tolua_S,1,"SpriteBatchNode",0,&tolua_err)) goto tolua_lerror;
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
            toluafix_pushusertype_ccobject(tolua_S, (*iter)->_ID, &((*iter)->_luaID), (void*)(*iter),"Sprite");
            lua_rawset(tolua_S, -3);
            (*iter)->retain();
            ++indexTable;
        }
        
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDescendants",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_SpriteBatchNode_getDescendants'.",&tolua_err);
#endif
    return 0;
}

static void extendTexture2D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "Texture2D");
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
    lua_pushstring(tolua_S,"MenuItem");
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
    lua_pushstring(tolua_S,"MenuItemImage");
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
    lua_pushstring(tolua_S, "MenuItemLabel");
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
    lua_pushstring(tolua_S, "MenuItemFont");
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
    lua_pushstring(tolua_S, "MenuItemSprite");
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
    lua_pushstring(tolua_S, "MenuItemToggle");
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
    lua_pushstring(tolua_S, "Menu");
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
    lua_pushstring(tolua_S,"Node");
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
    }
    lua_pop(tolua_S, 1);
}

static void extendLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S,"Layer");
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
    lua_pushstring(tolua_S,"Scheduler");
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
    lua_pushstring(tolua_S,"Sequence");
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
    lua_pushstring(tolua_S,"CallFunc");
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
    lua_pushstring(tolua_S,"Spawn");
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
    lua_pushstring(tolua_S,"CardinalSplineBy");
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
    lua_pushstring(tolua_S,"CatmullRomBy");
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
    lua_pushstring(tolua_S,"CatmullRomTo");
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
    lua_pushstring(tolua_S,"BezierBy");
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
    lua_pushstring(tolua_S,"BezierTo");
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
    lua_pushstring(tolua_S,"DrawNode");
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
    lua_pushstring(tolua_S,"Sprite");
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
    lua_pushstring(tolua_S,"LayerColor");
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
    lua_pushstring(tolua_S,"LayerMultiplex");
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
    lua_pushstring(tolua_S,"ParticleSystem");
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
    lua_pushstring(tolua_S, "FileUtils");
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
    lua_pushstring(tolua_S, "UserDefault");
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
    lua_pushstring(tolua_S, "SpriteBatchNode");
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
    lua_pushstring(tolua_S, "MotionStreak");
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
    lua_pushstring(tolua_S, "AtlasNode");
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
    lua_pushstring(tolua_S, "ParticleBatchNode");
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
    if (!tolua_isusertable(tolua_S, 1, "EventListenerAcceleration", 0, &tolua_err))  goto tolua_lerror;
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
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"EventListenerAcceleration");
        
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertable(tolua_S, 1, "EventListenerCustom", 0, &tolua_err))  goto tolua_lerror;
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
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"EventListenerCustom");
        
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

int register_cocos2dx_event_releated(lua_State* tolua_S)
{
    tolua_module(tolua_S,"cc",0);
    tolua_beginmodule(tolua_S,"cc");
      tolua_usertype(tolua_S,"EventListenerCustom");
      tolua_cclass(tolua_S,"EventListenerCustom","EventListenerCustom","",NULL);
      tolua_beginmodule(tolua_S,"EventListenerCustom");
        tolua_function(tolua_S, "create", tolua_cocos2d_LuaEventListenerCustom_create);
      tolua_endmodule(tolua_S);
    
      tolua_usertype(tolua_S, "EventListenerAcceleration");
      tolua_cclass(tolua_S,"EventListenerAcceleration","EventListenerAcceleration","",NULL);
      tolua_beginmodule(tolua_S,"EventListenerAcceleration");
        tolua_function(tolua_S, "create", tolua_cocos2dx_LuaEventListenerAcceleration_create);
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    
    std::string typeEventCustomName = typeid(LuaEventListenerCustom).name();
    g_luaType[typeEventCustomName] = "EventListenerCustom";
    
    std::string typeEventAccelerationName = typeid(LuaEventListenerAcceleration).name();
    g_luaType[typeEventAccelerationName] = "EventListenerAcceleration";
    
    return 1;
}

static int tolua_cocos2dx_EventListenerKeyboard_create(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "EventListenerKeyboard", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerKeyboard* tolua_ret = cocos2d::EventListenerKeyboard::create();
        if(nullptr == tolua_ret)
            return 0;
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"EventListenerKeyboard");
        
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S, 1, "EventListenerKeyboard", 0, &tolua_err))  goto tolua_lerror;
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
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerKeyboard(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "EventListenerKeyboard");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create",tolua_cocos2dx_EventListenerKeyboard_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerKeyboard_registerScriptHandler);
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
    if (!tolua_isusertable(tolua_S, 1, "EventListenerTouchOneByOne", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerTouchOneByOne* tolua_ret = cocos2d::EventListenerTouchOneByOne::create();
        if(nullptr == tolua_ret)
            return 0;
        
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"EventListenerTouchOneByOne");
        
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S, 1, "EventListenerTouchOneByOne", 0, &tolua_err))  goto tolua_lerror;
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
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerTouchOneByOne(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "EventListenerTouchOneByOne");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerTouchOneByOne_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerTouchOneByOne_registerScriptHandler);
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
    if (!tolua_isusertable(tolua_S, 1, "EventListenerTouchAllAtOnce", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        cocos2d::EventListenerTouchAllAtOnce* tolua_ret = cocos2d::EventListenerTouchAllAtOnce::create();
        if(nullptr == tolua_ret)
            return 0;

        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"EventListenerTouchAllAtOnce");
        
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S, 1, "EventListenerTouchAllAtOnce", 0, &tolua_err))  goto tolua_lerror;
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
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerTouchAllAtOnce(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "EventListenerTouchAllAtOnce");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerTouchAllAtOnce_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerTouchAllAtOnce_registerScriptHandler);
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
    if (!tolua_isusertable(tolua_S, 1, "EventListenerMouse", 0, &tolua_err))  goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        cocos2d::EventListenerMouse* tolua_ret = cocos2d::EventListenerMouse::create();
        if(nullptr == tolua_ret)
            return 0;

        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"EventListenerMouse");
        
        return 1;
    }
    
    CCLOG("'create' has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
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
    if (!tolua_isusertype(tolua_S, 1, "EventListenerMouse", 0, &tolua_err))  goto tolua_lerror;
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
    
    CCLOG("'registerScriptHandler' has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerMouse(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "EventListenerMouse");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_cocos2dx_EventListenerMouse_create);
        tolua_function(tolua_S, "registerScriptHandler", tolua_cocos2dx_EventListenerMouse_registerScriptHandler);
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
    if (!tolua_isusertype(tolua_S,1,"ActionCamera",0,&tolua_err)) goto tolua_lerror;
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
        toluafix_pushusertype_ccobject(tolua_S, reverse->_ID, &(reverse->_luaID), (void*)(reverse),"ActionCamera");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "reverse",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_ActionCamera_reverse'.",&tolua_err);
#endif
    return 0;
}

static void extendActionCamera(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ActionCamera");
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
    if (!tolua_isusertype(tolua_S,1,"GridAction",0,&tolua_err)) goto tolua_lerror;
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
        toluafix_pushusertype_ccobject(tolua_S, reverse->_ID, &(reverse->_luaID), (void*)(reverse),"GridAction");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "reverse",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2dx_GridAction_reverse'.",&tolua_err);
#endif
    return 0;
}

static void extendGridAction(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "GridAction");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "reverse", tolua_cocos2dx_GridAction_reverse);
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
    extendActionCamera(tolua_S);
    extendGridAction(tolua_S);
    
    extendMotionStreak(tolua_S);
    extendAtlasNode(tolua_S);
    extendParticleBatchNode(tolua_S);
    return 0;
}
