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
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"
#include "CCBProxy.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocostudio;

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
        LuaScrollViewDelegate* delegate = new LuaScrollViewDelegate();
        if (nullptr == delegate)
            return 0;
        
        self->setUserObject(delegate);
        self->setDelegate(delegate);
        
        delegate->release();
        
        return 0;
    }
    
    CCLOG("'setDelegate' function of ScrollView wrong number of arguments: %d, was expecting %d\n", argc, 0);
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
    
    CCLOG("'registerScriptHandler' function of ScrollView has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
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
    
    CCLOG("'unregisterScriptHandler' function of ScrollView  has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
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
    
    CCLOG("'registerControlEventHandler' function of Control has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerControlEventHandler'.",&tolua_err);
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
    
    CCLOG("'unregisterControlEventHandler' function of Control  has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterControlEventHandler'.",&tolua_err);
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

static int tolua_cocos2d_EditBox_registerScriptEditBoxHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    EditBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<EditBox*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_EditBox_registerScriptEditBoxHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        self->registerScriptEditBoxHandler(handler);
        return 0;
    }
    
    CCLOG("'registerScriptEditBoxHandler' function of EditBox  has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptEditBoxHandler'.",&tolua_err);
    return 0;
#endif

}

static int tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler(lua_State* tolua_S)
{
    
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    EditBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.EditBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<EditBox*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        self->unregisterScriptEditBoxHandler();
        return 0;
    }
    
    CCLOG("'unregisterScriptEditBoxHandler' function of EditBox  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptEditBoxHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendEditBox(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.EditBox");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"registerScriptEditBoxHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_EditBox_registerScriptEditBoxHandler );
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"unregisterScriptEditBoxHandler");
        lua_pushcfunction(tolua_S,tolua_cocos2d_EditBox_unregisterScriptEditBoxHandler );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_cocos2d_CCBProxy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        CCBProxy* tolua_ret = (CCBProxy*)CCBProxy::create();        
        int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int *pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CCBProxy");
        return 1;
    }
    
    CCLOG("'create' function of CCBProxy has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_CCBProxy_createCCBReader(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_createCCBReader'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        CCBReader* tolua_ret = (CCBReader*) self->createCCBReader();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"cc.CCBReader");
        return 1;
    }
    
    CCLOG("'createCCBReader' function of CCBProxy  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'createCCBReader'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_CCBProxy_readCCBFromFile(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    const char* ccbFilePath = nullptr;
    CCBReader*  ccbReader   = nullptr;
    bool        setOwner    = false;
    Node*       tolua_ret    = nullptr;
    int         ID          = 0;
    int*        luaID       = nullptr;
    
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_readCCBFromFile'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (2 == argc || 3 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(tolua_S, 2, 0, &tolua_err)||
            !tolua_isusertype(tolua_S,3,"cc.CCBReader",0,&tolua_err)||
            !tolua_isboolean(tolua_S,4,1,&tolua_err )
            )
            goto tolua_lerror;
#endif
        ccbFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
        ccbReader   = ((CCBReader*)  tolua_tousertype(tolua_S,3,0));
        setOwner = (bool)  tolua_toboolean(tolua_S,4,-1);
        tolua_ret = (Node*) self->readCCBFromFile(ccbFilePath, ccbReader, setOwner);
        ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
        return 1;
    }
    
    CCLOG("'readCCBFromFile' function of CCBProxy  has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'readCCBFromFile'.",&tolua_err);
    return 0;
#endif
}


static int tolua_cocos2d_CCBProxy_getNodeTypeName(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
  
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_getNodeTypeName'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,1,"cc.Node",0,&tolua_err)) goto tolua_lerror;
#endif
        
        Node* node = static_cast<Node*>(tolua_tousertype(tolua_S,2,0));
        const char* tolua_ret = (const char*)self->getNodeTypeName(node);
        tolua_pushstring(tolua_S,(const char*)tolua_ret);
        return 1;
    }
    
    CCLOG("'getNodeTypeName' function of CCBProxy  has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getNodeTypeName'.",&tolua_err);
    return 0;
#endif
}

static int tolua_cocos2d_CCBProxy_setCallback(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBProxy* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBProxy*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBProxy_setCallback'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if ( argc >= 2 && argc <= 3 )
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2,"cc.Node",0,&tolua_err) ||
            !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) ||
            !tolua_isnumber(tolua_S, 4, 1, &tolua_err)
            )
            goto tolua_lerror;
#endif
        
        Node* node = ((Node*)tolua_tousertype(tolua_S,2,0));
        LUA_FUNCTION funID = (  toluafix_ref_function(tolua_S,3,0));
        int   controlEvents = (int)tolua_tonumber(tolua_S, 4, 1);
        self->setCallback(node, funID, controlEvents);
        return 0;
    }
    
    CCLOG("'setCallback' function of CCBProxy  has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setCallback'.",&tolua_err);
    return 0;
#endif
}

int register_cocos2dx_extension_CCBProxy(lua_State* tolua_S)
{
    tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");
    tolua_usertype(tolua_S,"cc.CCBProxy");
    tolua_cclass(tolua_S,"CCBProxy","cc.CCBProxy","cc.Layer",NULL);
    tolua_beginmodule(tolua_S,"CCBProxy");
    tolua_function(tolua_S, "create", tolua_cocos2d_CCBProxy_create);
    tolua_function(tolua_S, "createCCBReader", tolua_cocos2d_CCBProxy_createCCBReader);
    tolua_function(tolua_S, "readCCBFromFile", tolua_cocos2d_CCBProxy_readCCBFromFile);
    tolua_function(tolua_S, "getNodeTypeName", tolua_cocos2d_CCBProxy_getNodeTypeName);
    tolua_function(tolua_S, "setCallback", tolua_cocos2d_CCBProxy_setCallback);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    
    std::string typeName = typeid(CCBProxy).name();
    g_luaType[typeName] = "cc.CCBProxy";
    return 1;
}

static int tolua_cocos2d_CCBReader_load(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBReader* self = nullptr;
    bool ok = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBReader",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBReader*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBReader_load'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc >= 1 && argc <= 3)
    {
        const char* fileName = nullptr;
        std::string fileName_tmp = "";
        ok &= luaval_to_std_string(tolua_S, 2, &fileName_tmp);
        fileName = fileName_tmp.c_str();
        if (!ok)
            return 0;
        
        if (1 == argc)
        {
            Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName);
            int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
            return 1;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S, 3, "cc.Ref", 0, &tolua_err))
            goto tolua_lerror;
#endif
        Ref* owner = static_cast<Ref*>(tolua_tousertype(tolua_S, 3, 0));
        //In lua owner always define in lua script by table, so owner is always nullptr
        if (2 == argc)
        {
            Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName,owner);
            int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
            return 1;
        }
        
        Size size;
        ok &= luaval_to_size(tolua_S, 4, &size);
        if (!ok)
            return 0;
        
        Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName,owner,size);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"cc.Node");
        return 1;
        
    }
    
    CCLOG("'load' function of CCBReader  has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
    return 0;
#endif
}

static void extendCCBReader(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CCBReader");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"load");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CCBReader_load );
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}


static int tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBAnimationManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"cc.CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<CCBAnimationManager*>(tolua_tousertype(tolua_S,1,0));
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (2 == argc)
    {
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S,2, "cc.CallFunc", 0, &tolua_err) ||
            !tolua_isstring(tolua_S, 3, 0, &tolua_err) )
            goto tolua_lerror;
#endif
        
        CallFunc* pCallFunc = static_cast<CallFunc*>(tolua_tousertype(tolua_S,2,0));
        const char* keyframeCallback = ((const char*)  tolua_tostring(tolua_S,3,0));
        std::string strKey = "";
        if (NULL != keyframeCallback) {
            strKey = keyframeCallback;
        }
        self->setCallFunc(pCallFunc, strKey);
        
        return 0;
    }
    
    CCLOG("'setCallFuncForLuaCallbackNamed' function of CCBAnimationManager  has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setCallFuncForLuaCallbackNamed'.",&tolua_err);
    return 0;
#endif
}

static void extendCCBAnimationManager(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.CCBAnimationManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setCallFuncForLuaCallbackNamed");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed );
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
            delegate = new LuaAssetsManagerDelegateProtocol();
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
    
    CCLOG("'setDelegate' function of AssetsManager has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setDelegate'.",&tolua_err);
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
        LUA_TableViewDelegate* delegate = new LUA_TableViewDelegate();
        if (nullptr == delegate)
            return 0;
        
        Dictionary* userDict = static_cast<Dictionary*>(self->getUserObject());
        if (nullptr == userDict)
        {
            userDict = new Dictionary();
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
    
    CCLOG("'setDelegate' function of TableView wrong number of arguments: %d, was expecting %d\n", argc, 0);
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
        LUA_TableViewDataSource* dataSource = new LUA_TableViewDataSource();
        if (nullptr == dataSource)
            return 0;
        
        Dictionary* userDict = static_cast<Dictionary*>(self->getUserObject());
        if (nullptr == userDict)
        {
            userDict = new Dictionary();
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
    
    CCLOG("'setDataSource' function of TableView wrong number of arguments: %d, was expecting %d\n", argc, 0);
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
        LUA_TableViewDataSource* dataSource = new LUA_TableViewDataSource();
        Size size;
        ok &= luaval_to_size(L, 2, &size);
        
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
        
        Dictionary* userDict = new Dictionary();
        userDict->setObject(dataSource, KEY_TABLEVIEW_DATA_SOURCE);
        ret->setUserObject(userDict);
        userDict->release();
        
        dataSource->release();
        
        
        int  nID = (int)ret->_ID;
        int* pLuaID =  &ret->_luaID;
        toluafix_pushusertype_ccobject(L, nID, pLuaID, (void*)ret,"cc.TableView");
        
        return 1;
    }
    CCLOG("'create' function of TableView wrong number of arguments: %d, was expecting %d\n", argc, 1);
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
	if (!tolua_isusertype(L,1,"cc.TableView",0,&tolua_err)) goto tolua_lerror;
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
    
    CCLOG("'registerScriptHandler' function of TableView has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'registerScriptHandler'.",&tolua_err);
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
    
    CCLOG("'unregisterScriptHandler' function of TableView  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
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

int register_all_cocos2dx_extension_manual(lua_State* tolua_S)
{
    extendControl(tolua_S);
    extendEditBox(tolua_S);
    extendCCBReader(tolua_S);
    extendCCBAnimationManager(tolua_S);
    extendAssetsManager(tolua_S);
    extendScrollView(tolua_S);
    extendTableView(tolua_S);
    return 0;
}
