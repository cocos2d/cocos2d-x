#include "lua_cocos2dx_extension_manual.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "cocos-ext.h"
#include "CCBProxy.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LuaScrollViewDelegate:public Object, public ScrollViewDelegate
{
public:
    virtual ~LuaScrollViewDelegate()
    {}
    
    virtual void scrollViewDidScroll(ScrollView* view)
    {
        if (nullptr != view)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)view, ScriptHandlerMgr::kScrollViewScrollHandler);
            if (0 != handler)
            {
                CommonScriptData data(handler,"");
                ScriptEvent event(kCommonEvent,(void*)&data);
                ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
            }

        }
    }
    
    virtual void scrollViewDidZoom(ScrollView* view)
    {
        if (nullptr != view)
        {
            int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)view, ScriptHandlerMgr::kScrollViewZoomHandler);
            if (0 != handler)
            {
                CommonScriptData data(handler,"");
                ScriptEvent event(kCommonEvent,(void*)&data);
                ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
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
    if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
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
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
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
        ScriptHandlerMgr::HandlerEventType handlerType = (ScriptHandlerMgr::HandlerEventType) ((int)tolua_tonumber(tolua_S,3,0) + ScriptHandlerMgr::kScrollViewScrollHandler);
        
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
	if (!tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err)) goto tolua_lerror;
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
        ScriptHandlerMgr::HandlerEventType handlerType = (ScriptHandlerMgr::HandlerEventType) ((int)tolua_tonumber(tolua_S,2,0) + ScriptHandlerMgr::kScrollViewScrollHandler);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
        return 0;
    }
    
    CCLOG("'unregisterScriptHandler' function of ScrollView  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendScrollView(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ScrollView");
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
}

static int tolua_cocos2d_Control_registerControlEventHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    Control* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
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
                int handlerevent  = ScriptHandlerMgr::kControlTouchDownHandler + i;
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
	if (!tolua_isusertype(tolua_S,1,"Control",0,&tolua_err)) goto tolua_lerror;
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
                int handlerevent  = ScriptHandlerMgr::kControlTouchDownHandler + i;
                ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerevent);
                break;
            }
        }
        return 0;
    }
    
    CCLOG("'unregisterControlEventHandler' function of Control  has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterControlEventHandler'.",&tolua_err);
    return 0;
#endif
}

static void extendControl(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "Control");
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
}

static int tolua_cocos2d_EditBox_registerScriptEditBoxHandler(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    EditBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
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
	if (!tolua_isusertype(tolua_S,1,"EditBox",0,&tolua_err)) goto tolua_lerror;
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
    lua_pushstring(tolua_S, "EditBox");
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
}

static int tolua_cocos2d_CCBProxy_create(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertable(tolua_S,1,"CCBProxy",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
        CCBProxy* tolua_ret = (CCBProxy*)CCBProxy::create();        
        int  nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int *pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBProxy");
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
	if (!tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err)) goto tolua_lerror;
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
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCBReader");
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
	if (!tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err)) goto tolua_lerror;
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
            !tolua_isusertype(tolua_S,3,"CCBReader",0,&tolua_err)||
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
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"Node");
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
	if (!tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err)) goto tolua_lerror;
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
        if (!tolua_isusertype(tolua_S,1,"Node",0,&tolua_err)) goto tolua_lerror;
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
	if (!tolua_isusertype(tolua_S,1,"CCBProxy",0,&tolua_err)) goto tolua_lerror;
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
        if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
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
    tolua_usertype(tolua_S,"CCBProxy");
    tolua_cclass(tolua_S,"CCBProxy","CCBProxy","Layer",NULL);
    tolua_beginmodule(tolua_S,"CCBProxy");
    tolua_function(tolua_S, "create", tolua_cocos2d_CCBProxy_create);
    tolua_function(tolua_S, "createCCBReader", tolua_cocos2d_CCBProxy_createCCBReader);
    tolua_function(tolua_S, "readCCBFromFile", tolua_cocos2d_CCBProxy_readCCBFromFile);
    tolua_function(tolua_S, "getNodeTypeName", tolua_cocos2d_CCBProxy_getNodeTypeName);
    tolua_function(tolua_S, "setCallback", tolua_cocos2d_CCBProxy_setCallback);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    
    uint32_t typeId = typeid(CCBProxy).hash_code();
    g_luaType[typeId] = "CCBProxy";
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
	if (!tolua_isusertype(tolua_S,1,"CCBReader",0,&tolua_err)) goto tolua_lerror;
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
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"Node");
            return 1;
        }
        
#if COCOS2D_DEBUG >= 1
        if (!tolua_isusertype(tolua_S, 3, "Object", 0, &tolua_err))
            goto tolua_lerror;
#endif
        Object* owner = static_cast<Object*>(tolua_tousertype(tolua_S, 3, 0));
        //In lua owner always define in lua script by table, so owner is always nullptr
        if (2 == argc)
        {
            Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName,owner);
            int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"Node");
            return 1;
        }
        
        Size size;
        ok &= luaval_to_size(tolua_S, 4, &size);
        if (!ok)
            return 0;
        
        Node* tolua_ret = (Node*) self->readNodeGraphFromFile(fileName,owner,size);
        int ID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* luaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)tolua_ret,"Node");
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
    lua_pushstring(tolua_S, "CCBReader");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"load");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CCBReader_load );
        lua_rawset(tolua_S,-3);
    }
}


static int tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed(lua_State* tolua_S)
{
    if (nullptr == tolua_S)
        return 0;
    
    int argc = 0;
    CCBAnimationManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"CCBAnimationManager",0,&tolua_err)) goto tolua_lerror;
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
        if (!tolua_isusertype(tolua_S,2, "CallFunc", 0, &tolua_err) ||
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
    lua_pushstring(tolua_S, "CCBAnimationManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"setCallFuncForLuaCallbackNamed");
        lua_pushcfunction(tolua_S,tolua_cocos2d_CCBAnimationManager_setCallFuncForLuaCallbackNamed );
        lua_rawset(tolua_S,-3);
    }
}

int register_all_cocos2dx_extension_manual(lua_State* tolua_S)
{
    extendScrollView(tolua_S);
    extendControl(tolua_S);
    extendEditBox(tolua_S);
    extendCCBReader(tolua_S);
    extendCCBAnimationManager(tolua_S);
    return 0;
}
