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
#include "lua_cocos2dx_extension_manual.h"
#include "lua_cocos2dx_extension_auto.hpp"
#include "lua_cocos2dx_assetsmanager_auto.hpp"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"
#include "CCLuaEngine.h"
#include "LuaScriptHandlerMgr.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LuaScrollViewDelegate:public Ref, public ScrollViewDelegate
{
public:
    virtual ~LuaScrollViewDelegate()
    {}
    
    virtual void scrollViewDidScroll(ScrollView* view) override
    {
        if (nullptr != view)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)view, ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL);
            if (0 != handler)
            {
                CommonScriptData data(handler,"");
                ScriptEvent event(kCommonEvent,(void*)&data);
                LuaEngine::getInstance()->sendEvent(&event);
            }
            
        }
    }
    
    virtual void scrollViewDidZoom(ScrollView* view) override
    {
        if (nullptr != view)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)view, ScriptHandlerMgr::HandlerType::SCROLLVIEW_ZOOM);
            if (0 != handler)
            {
                CommonScriptData data(handler,"");
                ScriptEvent event(kCommonEvent,(void*)&data);
                LuaEngine::getInstance()->sendEvent(&event);
            }
        }
    }
};

static int tolua_cocos2dx_ScrollView_setDelegate(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    ScrollView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2dx_ScrollView_setDelegate'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        LuaScrollViewDelegate* delegate = new (std::nothrow) LuaScrollViewDelegate();
        if (nullptr == delegate)
            return 0;
        
        self->setUserObject(delegate);
        self->setDelegate(delegate);
        
        delegate->release();
        
        return 0;
    }
    
    luaL_error(tolua_S, "'setDelegate' function of ScrollView wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_ScrollView_registerScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    ScrollView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ScrollView*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_ScrollView_registerScriptHandler'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(tolua_S) - 1;
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(tolua_S,3,0) + (int)ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);
        return 0;
    }
    
    luaL_error(tolua_S, "%s function of ScrollView has wrong number of arguments: %d, was expecting %d\n", "cc.ScrollView:registerScriptHandler",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_ScrollView_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_ScrollView_unregisterScriptHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    ScrollView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.ScrollView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ScrollView*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_ScrollView_unregisterScriptHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(tolua_S,2,0) + (int)ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
        return 0;
    }
    
    luaL_error(tolua_S, "%s function of ScrollView  has wrong number of arguments: %d, was expecting %d\n", "cc.ScrollView:unregisterScriptHandler", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_ScrollView_unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendScrollView(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ScrollView");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setDelegate");
        lua_pushcfunction(tolua_S,tolua_cocos2dx_ScrollView_setDelegate );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"registerScriptHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_ScrollView_registerScriptHandler );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"unregisterScriptHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_ScrollView_unregisterScriptHandler );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}


static int tolua_cocos2d_Control_registerControlEventHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Control* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Control*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_Control_registerControlEventHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S, 3, 0, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        int controlevent = (int)tolua_tonumber(tolua_S,3,0);
        for (int i = 0; i < kControlEventTotalNumber; i++)
        {
            if ((controlevent & (1 << i)))
            {
                ScriptHandlerMgr::HandlerType handlerevent  = ScriptHandlerMgr::HandlerType((int)ScriptHandlerMgr::HandlerType::CONTROL_TOUCH_DOWN + i);
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerevent);
            }
        }
        return 0;
    }
    
    luaL_error(tolua_S, "%s function of Control has wrong number of arguments: %d, was expecting %d\n", "cc.Control:registerControlEventHandler", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_Control_registerControlEventHandler'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_control_unregisterControlEventHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Control* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.Control",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<Control*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_control_unregisterControlEventHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err))
            goto tolua_lerror;
#endif
        int controlevent = (int)tolua_tonumber(tolua_S,2,0);
        for (int i = 0; i < kControlEventTotalNumber; i++)
        {
            if ((controlevent & (1 << i)))
            {
                ScriptHandlerMgr::HandlerType handlerevent  = ScriptHandlerMgr::HandlerType((int)ScriptHandlerMgr::HandlerType::CONTROL_TOUCH_DOWN + i);
                ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerevent);
                break;
            }
        }
        return 0;
    }
    
    luaL_error(tolua_S, "%s function of Control  has wrong number of arguments: %d, was expecting %d\n", "cc.Control:unregisterControlEventHandler", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'tolua_cocos2d_control_unregisterControlEventHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendControl(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.Control");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerControlEventHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_Control_registerControlEventHandler );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"unregisterControlEventHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_control_unregisterControlEventHandler );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}



class LuaAssetsManagerDelegateProtocol:public Ref, public AssetsManagerDelegateProtocol
{
public:
    virtual ~LuaAssetsManagerDelegateProtocol()
    {}
    
    virtual void onProgress(int percent) override
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS);
        if (0 != handler)
        {
            LuaAssetsManagerEventData eventData(percent);
            BasicScriptData data((void*)this,&eventData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS, (void*)&data);
        }
    }
    
    virtual void onSuccess() override
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ASSETSMANAGER_SUCCESS);
        if (0 != handler)
        {
            LuaAssetsManagerEventData eventData;
            BasicScriptData data((void*)this,&eventData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ASSETSMANAGER_SUCCESS, (void*)&data);
        }
    }
    
    virtual void onError(AssetsManager::ErrorCode errorCode) override
    {
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR);
        if (0 != handler)
        {
            LuaAssetsManagerEventData eventData((int)errorCode);
            BasicScriptData data((void*)this,&eventData);
            LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::ASSETSMANAGER_ERROR, (void*)&data);
        }
    }
};

#if CC_USE_CURL
static int lua_cocos2dx_AssetsManager_setDelegate(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    AssetsManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.AssetsManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (AssetsManager*)  tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_AssetsManager_setDelegate'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (2 == argc)
    {        
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L, 2, "LUA_FUNCTION", 0, &tolua_err) ||
                !tolua_isnumber(L, 3, 0, &tolua_err) )
        {
                goto tolua_lerror;
        }
#endif
        LuaAssetsManagerDelegateProtocol* delegate = dynamic_cast<LuaAssetsManagerDelegateProtocol*>( self->getDelegate());
        if (nullptr == delegate)
        {
            delegate = new (std::nothrow) LuaAssetsManagerDelegateProtocol();
            if (nullptr == delegate)
                return 0;
            
            self->setUserObject(delegate);
            self->setDelegate(delegate);
            delegate->release();
        }
        
        LUA_FUNCTION handler = toluafix_ref_function(L, 2, 0);
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L,3,0) + (int)ScriptHandlerMgr::HandlerType::ASSETSMANAGER_PROGRESS);
            
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)delegate, handler, handlerType);
        return 0;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.AssetsManager:setDelegate", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_AssetsManager_setDelegate'.",&tolua_err);
    return 0;
#endif
}

static void extendAssetsManager(lua_State* L)
{
    lua_pushstring(L, "cc.AssetsManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setDelegate", lua_cocos2dx_AssetsManager_setDelegate);
    }
    lua_pop(L, 1);
}
#endif  //CC_USE_CURL

#define KEY_TABLEVIEW_DATA_SOURCE  "TableViewDataSource"
#define KEY_TABLEVIEW_DELEGATE     "TableViewDelegate"

class LUA_TableViewDelegate:public Ref, public TableViewDelegate
{
public:
    LUA_TableViewDelegate(){}
    
    virtual ~LUA_TableViewDelegate(){}
    
    
    virtual void scrollViewDidScroll(ScrollView* view) override
    {
        if (nullptr != view)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)view, ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL);
            if (0 != handler)
            {
                LuaTableViewEventData eventData;
                BasicScriptData data(view,&eventData);
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL, (void*)&data);
            }
        }
    }
    
    virtual void scrollViewDidZoom(ScrollView* view) override
    {
        if (nullptr != view)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)view, ScriptHandlerMgr::HandlerType::SCROLLVIEW_ZOOM);
            if (0 != handler)
            {
                LuaTableViewEventData eventData;
                BasicScriptData data(view,&eventData);
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::SCROLLVIEW_ZOOM, (void*)&data);
            }
        }
    }
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override
    {
        if (nullptr != table && nullptr != cell)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLECELL_TOUCHED);
            if (0 != handler)
            {
                LuaTableViewEventData eventData(cell);
                BasicScriptData data(table,&eventData);
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLECELL_TOUCHED,(void*)&data);
            }
        }
    }
    
    virtual void tableCellHighlight(TableView* table, TableViewCell* cell) override
    {
        if (nullptr != table && nullptr != cell)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLECELL_HIGHLIGHT);
            if (0 != handler)
            {
                LuaTableViewEventData eventData(cell);
                BasicScriptData data(table,&eventData);
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLECELL_HIGHLIGHT,(void*)&data);
            }
        }
    }
    
    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell) override
    {
        if (nullptr != table && nullptr != cell)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLECELL_UNHIGHLIGHT);
            if (0 != handler)
            {
                LuaTableViewEventData eventData(cell);
                BasicScriptData data(table,&eventData);
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLECELL_UNHIGHLIGHT,(void*)&data);
            }
        }
    }
    
    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell) override
    {
        if (nullptr != table && nullptr != cell)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLECELL_WILL_RECYCLE);
            if (0 != handler)
            {
                LuaTableViewEventData eventData(cell);
                BasicScriptData data(table,&eventData);
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLECELL_WILL_RECYCLE,(void*)&data);
            }
        }
    }
};

static int lua_cocos2dx_TableView_setDelegate(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    TableView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (TableView*)  tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_TableView_setDelegate'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {
        LUA_TableViewDelegate* delegate = new (std::nothrow) LUA_TableViewDelegate();
        if (nullptr == delegate)
            return 0;
        
        __Dictionary* userDict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == userDict)
        {
            userDict = new __Dictionary();
            if (NULL == userDict)
                return 0;
            
            self->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->setObject(delegate, KEY_TABLEVIEW_DELEGATE);
        self->setDelegate(delegate);
        delegate->release();
        
        return 0;
    }
    
    luaL_error(L, "'setDelegate' function of TableView wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setDelegate'.",&tolua_err);
    return 0;
#endif
}

class LUA_TableViewDataSource:public Ref,public TableViewDataSource
{
public:
    LUA_TableViewDataSource(){}
    virtual ~LUA_TableViewDataSource(){}
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) override
    {
        if (nullptr != table )
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLECELL_SIZE_FOR_INDEX);
            if (0 != handler)
            {
                LuaTableViewEventData eventData(&idx);
                BasicScriptData data(table,&eventData);
                float width = 0.0;
                float height = 0.0;
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLECELL_SIZE_FOR_INDEX, (void*)&data,2,[&](lua_State* L,int numReturn){
                    CCASSERT(numReturn == 2, "tableCellSizeForIndex return count error");
                    ValueVector vec;
                    width  = (float)tolua_tonumber(L, -1, 0);
                    lua_pop(L, 1);
                    height = (float)tolua_tonumber(L, -1, 0);
                    lua_pop(L, 1);
                });
                
                return Size(width, height);
            }
        }
        
        return Size::ZERO;
    }
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override
    {
        if (nullptr != table )
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLECELL_AT_INDEX);
            if (0 != handler)
            {
                LuaTableViewEventData eventData(&idx);
                BasicScriptData data(table,&eventData);
                TableViewCell* viewCell = nullptr;
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLECELL_AT_INDEX, (void*)&data, 1, [&](lua_State* L, int numReturn){
                    CCASSERT(numReturn == 1, "tableCellAtIndex return count error");
                    viewCell = static_cast<TableViewCell*>(tolua_tousertype(L, -1, nullptr));
                    lua_pop(L, 1);
                });
                
                return viewCell;
            }
        }
        
        return NULL;
    }
    
    virtual ssize_t numberOfCellsInTableView(TableView *table) override
    {
        if (nullptr != table )
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)table, ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS);
            if (0 != handler)
            {
                LuaTableViewEventData eventData;
                BasicScriptData data(table,&eventData);
                ssize_t counts = 0;
                LuaEngine::getInstance()->handleEvent(ScriptHandlerMgr::HandlerType::TABLEVIEW_NUMS_OF_CELLS, (void*)&data,1, [&](lua_State* L, int numReturn){
                    CCASSERT(numReturn == 1, "numberOfCellsInTableView return count error");
                    counts = (ssize_t)tolua_tonumber(L, -1, 0);
                    lua_pop(L, 1);
                });
                return counts;
            }
        }
        return 0;
    }
};

static int lua_cocos2dx_TableView_setDataSource(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    TableView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = (TableView*)  tolua_tousertype(L,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self)
    {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_TableView_setDataSource'\n", nullptr);
		return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {
        LUA_TableViewDataSource* dataSource = new (std::nothrow) LUA_TableViewDataSource();
        if (nullptr == dataSource)
            return 0;
        
        __Dictionary* userDict = static_cast<__Dictionary*>(self->getUserObject());
        if (nullptr == userDict)
        {
            userDict = new __Dictionary();
            if (NULL == userDict)
                return 0;
            
            self->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->setObject(dataSource, KEY_TABLEVIEW_DATA_SOURCE);
        
        self->setDataSource(dataSource);
        
        dataSource->release();
        
        return 0;
    }
    
    luaL_error(L, "'setDataSource' function of TableView wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setDataSource'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_TableView_create(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (2 == argc || 1 == argc)
    {
        LUA_TableViewDataSource* dataSource = new (std::nothrow) LUA_TableViewDataSource();
        Size size;
        ok &= luaval_to_size(L, 2, &size, "cc.TableView:create");
        
        TableView* ret = nullptr;
        
        if (1 == argc)
        {
            ret = TableView::create(dataSource, size);
        }
        else
        {
#if COCOS2D_DEBUG >= 1
            if (!tolua_isusertype(L,3,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
            Node* node = static_cast<Node*>(tolua_tousertype(L, 3, nullptr));
            ret = TableView::create(dataSource, size, node);
        }
        
        if (nullptr ==  ret)
            return 0;
        
        ret->reloadData();
        
        __Dictionary* userDict = new __Dictionary();
        userDict->setObject(dataSource, KEY_TABLEVIEW_DATA_SOURCE);
        ret->setUserObject(userDict);
        userDict->release();
        
        dataSource->release();
        
        
        int  nID = (int)ret->_ID;
        int* pLuaID =  &ret->_luaID;
        toluafix_pushusertype_ccobject(L, nID, pLuaID, (void*)ret,"cc.TableView");
        
        return 1;
    }
    luaL_error(L, "'create' function of TableView wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2d_TableView_registerScriptHandler(lua_State* L)
{
    if (NULL == L)
        return 0;
    
    int argc = 0;
    TableView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<TableView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'tolua_cocos2d_TableView_registerScriptHandler'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(L, 3, 0, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L,3,0) + (int)ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL);
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);
        return 0;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.TableView:registerScriptHandler",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'tolua_cocos2d_TableView_registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2d_TableView_unregisterScriptHandler(lua_State* L)
{
    if (NULL == L)
        return 0;
    
    int argc = 0;
    TableView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<TableView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2d_TableView_unregisterScriptHandler'\n", NULL);
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
        ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType) ((int)tolua_tonumber(L,2,0) + (int)ScriptHandlerMgr::HandlerType::SCROLLVIEW_SCROLL);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
        return 0;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n", "cc.TableView:unregisterScriptHandler", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2d_TableView_unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendTableView(lua_State* L)
{
    lua_pushstring(L, "cc.TableView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setDelegate", lua_cocos2dx_TableView_setDelegate);
        tolua_function(L, "setDataSource", lua_cocos2dx_TableView_setDataSource);
        tolua_function(L, "create", lua_cocos2dx_TableView_create);
        tolua_function(L, "registerScriptHandler", lua_cocos2d_TableView_registerScriptHandler);
        tolua_function(L, "unregisterScriptHandler", lua_cocos2d_TableView_unregisterScriptHandler);
    }
    lua_pop(L, 1);
}

static void extendManifest(lua_State* L)
{
    lua_pushstring(L, "cc.Manifest");
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pop(L, 1);
}

#if CC_USE_CURL
static int lua_cocos2dx_Extension_EventListenerAssetsManagerEx_create(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(L,1,"cc.EventListenerAssetsManagerEx",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(L)-1;
    
    if (argc == 2)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(L, 2, "cc.AssetsManagerEx", 0, &tolua_err) ||
            !toluafix_isfunction(L,3,"LUA_FUNCTION",0,&tolua_err))
            goto tolua_lerror;
#endif
        cocos2d::extension::AssetsManagerEx* assetManager =  static_cast<cocos2d::extension::AssetsManagerEx*>(tolua_tousertype(L,2,nullptr));
        
        LUA_FUNCTION handler = toluafix_ref_function(L,3,0);
        
        cocos2d::extension::EventListenerAssetsManagerEx* ret = cocos2d::extension::EventListenerAssetsManagerEx::create(assetManager, [=](EventAssetsManagerEx* event){
            int id = event? (int)event->_ID : -1;
            int* luaID = event? &event->_luaID : nullptr;
            toluafix_pushusertype_ccobject(L, id, luaID, (void*)event,"cc.EventAssetsManagerEx");
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
        });
        
        int  id = (ret) ? (int)ret->_ID : -1;
        int* luaID = (ret) ? &ret->_luaID : nullptr;
        toluafix_pushusertype_ccobject(L, id, luaID, (void*)ret,"cc.EventListenerAssetsManagerEx");
        return 1;
    }
    
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d \n", "create",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'lua_cocos2dx_Extension_EventListenerAssetsManagerEx_create'.",&tolua_err);
    return 0;
#endif
}

static void extendEventListenerAssetsManagerEx(lua_State* L)
{
    lua_pushstring(L, "cc.EventListenerAssetsManagerEx");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "create", lua_cocos2dx_Extension_EventListenerAssetsManagerEx_create);
    }
    lua_pop(L, 1);
}
#endif  //CC_USE_CURL

int register_all_cocos2dx_extension_manual(lua_State* tolua_S)
{
    extendControl(tolua_S);
    extendScrollView(tolua_S);
    extendTableView(tolua_S);
    extendManifest(tolua_S);
#if CC_USE_CURL
    extendAssetsManager(tolua_S);
    extendEventListenerAssetsManagerEx(tolua_S);
#endif
    return 0;
}

int register_extension_module(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        register_all_cocos2dx_extension(tolua_S);
#if CC_USE_CURL
        register_all_cocos2dx_assetsmanager(tolua_S);
#endif
        register_all_cocos2dx_extension_manual(tolua_S);
    }
    lua_pop(tolua_S, 1);
    return 1;
}
