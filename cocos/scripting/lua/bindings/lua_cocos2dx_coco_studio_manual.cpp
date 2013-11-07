#include "lua_cocos2dx_coco_studio_manual.hpp"

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
#include "CocosGUI.h"

using namespace gui;

class LuaCocoStudioEventListener:public Object
{
public:
    LuaCocoStudioEventListener();
    virtual ~LuaCocoStudioEventListener();
    
    virtual void setObjToLua(Object* obj);
    
    static LuaCocoStudioEventListener* create();
    
    virtual void eventCallbackFunc(Object* sender,int eventType)
    {
        if (nullptr == sender)
            return;
        
        int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        if (0 != handler)
        {
            //call lua funtion
        }
    }
    
    
    
private:
    Object* _objToLua;
};

LuaCocoStudioEventListener::LuaCocoStudioEventListener():_objToLua(nullptr)
{
    
}

LuaCocoStudioEventListener::~LuaCocoStudioEventListener()
{
    if (nullptr != _objToLua)
        _objToLua->release();
}

LuaCocoStudioEventListener* LuaCocoStudioEventListener::create()
{
    LuaCocoStudioEventListener* listener = new LuaCocoStudioEventListener();
    if (nullptr == listener)
        return nullptr;
    
    listener->autorelease();
    
    return listener;
}

void LuaCocoStudioEventListener::setObjToLua(Object* obj)
{
    if (nullptr != _objToLua)
        _objToLua->release();
    
    _objToLua = obj;
    _objToLua->retain();
}

static int lua_cocos2dx_UICheckBox_addEventListener(lua_State* L)
{
    if (NULL == L)
        return 0;
    
    int argc = 0;
    UICheckBox* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UICheckBox",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UICheckBox*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UICheckBox_addEventListener'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isusertype(L, 3, "Object", 0, &tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LuaCocoStudioEventListener* listern = LuaCocoStudioEventListener::create();
        if (nullptr == listern)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        Object* obj  = static_cast<Object*>(tolua_tousertype(L, 3, nullptr));
        
        listern->setObjToLua(obj);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listern, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->addEventListener(listern, checkboxselectedeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListener' function of UICheckBox has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendUICheckBox(lua_State* L)
{
    lua_pushstring(L, "UICheckBox");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_UICheckBox_addEventListener);
    }
}

int register_all_cocos2dx_coco_studio_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendUICheckBox(L);
    
    return 0;
}