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
#include "CocoStudio.h"

using namespace gui;
using namespace cocostudio;

class LuaCocoStudioEventListener:public Object
{
public:
    LuaCocoStudioEventListener();
    virtual ~LuaCocoStudioEventListener();
    
    static LuaCocoStudioEventListener* create();
    
    virtual void eventCallbackFunc(Object* sender,int eventType);
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

void LuaCocoStudioEventListener::eventCallbackFunc(Object* sender,int eventType)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
    
    if (0 != handler)
    {
        LuaCocoStudioEventListenerData eventData(sender,eventType);
        BasicScriptData data(this,(void*)&eventData);
        ScriptEvent scriptEvent(kCocoStudioEventListener,(void*)&data);
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

static int lua_cocos2dx_UIWidget_addTouchEventListener(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UIWidget* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UIWidget",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UIWidget*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UIWidget_addTouchEventListener'\n", NULL);
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
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->setUserObject(listener);
        self->addTouchEventListener(listener, toucheventselector(LuaCocoStudioEventListener::eventCallbackFunc));
                
        return 0;
    }
    
    CCLOG("'addTouchEventListener' function of UIWidget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addTouchEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendUIWidget(lua_State* L)
{
    lua_pushstring(L, "UIWidget");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addTouchEventListener", lua_cocos2dx_UIWidget_addTouchEventListener);
    }
}

static int lua_cocos2dx_UICheckBox_addEventListenerCheckBox(lua_State* L)
{
    if (nullptr == L)
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
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UICheckBox_addEventListenerCheckBox'\n", NULL);
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
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->setUserObject(listener);        
        self->addEventListenerCheckBox(listener, checkboxselectedeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerCheckBox' function of UICheckBox has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerCheckBox'.",&tolua_err);
    return 0;
#endif
}


static void extendUICheckBox(lua_State* L)
{
    lua_pushstring(L, "UICheckBox");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerCheckBox", lua_cocos2dx_UICheckBox_addEventListenerCheckBox);
    }
}

static int lua_cocos2dx_UISlider_addEventListenerSlider(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UISlider* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UISlider",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UISlider*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UISlider_addEventListenerSlider'\n", NULL);
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

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->setUserObject(listener);        
        self->addEventListenerSlider(listener, sliderpercentchangedselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerSlider' function of UISlider has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerSlider'.",&tolua_err);
    return 0;
#endif
}

static void extendUISlider(lua_State* L)
{
    lua_pushstring(L, "UISlider");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerSlider", lua_cocos2dx_UISlider_addEventListenerSlider);
    }
}

static int lua_cocos2dx_UITextField_addEventListenerTextField(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UITextField* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UITextField",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UITextField*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UITextField_addEventListenerTextField'\n", NULL);
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

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->setUserObject(listener);        
        self->addEventListenerTextField(listener, textfieldeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerTextField' function of UITextField has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerTextField'.",&tolua_err);
    return 0;
#endif
}

static void extendUITextField(lua_State* L)
{
    lua_pushstring(L, "UITextField");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerTextField", lua_cocos2dx_UITextField_addEventListenerTextField);
    }
}

static int lua_cocos2dx_UIPageView_addEventListenerPageView(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UIPageView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UIPageView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UIPageView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UIPageView_addEventListenerPageView'\n", NULL);
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

        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listener, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->setUserObject(listener);        
        self->addEventListenerPageView(listener, pagevieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerPageView' function of UIPageView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerPageView'.",&tolua_err);
    return 0;
#endif
}

static void extendUIPageView(lua_State* L)
{
    lua_pushstring(L, "UIPageView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerPageView", lua_cocos2dx_UIPageView_addEventListenerPageView);
    }
}

static int lua_cocos2dx_UIListView_addEventListenerListView(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UIListView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UIListView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UIListView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UIListView_addEventListenerListView'\n", NULL);
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
        LuaCocoStudioEventListener* listern = LuaCocoStudioEventListener::create();
        if (nullptr == listern)
        {
            tolua_error(L,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)listern, handler, ScriptHandlerMgr::HandlerType::EVENT_LISTENER);
        
        self->setUserObject(listern);
        self->addEventListenerListView(listern, listvieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
        
        return 0;
    }
    
    CCLOG("'addEventListenerListView' function of UIListView has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addEventListenerListView'.",&tolua_err);
    return 0;
#endif
}

static void extendUIListView(lua_State* L)
{
    lua_pushstring(L, "UIListView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListenerListView", lua_cocos2dx_UIListView_addEventListenerListView);
    }
}

static int lua_cocos2dx_UILayoutParameter_setMargin(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UILayoutParameter* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"UILayoutParameter",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UILayoutParameter*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_UILayoutParameter_setMargin'\n", NULL);
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
        
        UIMargin margin;
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
    
    CCLOG("'setMargin' function of UILayoutParameter has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setMargin'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_UILayoutParameter_getMargin(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    UILayoutParameter* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"LayoutParameter",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<UILayoutParameter*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_LayoutParameter_getMargin'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (0 == argc)
    {
        UIMargin margin = self->getMargin();
        
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
    lua_pushstring(L, "UILayoutParameter");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setMargin", lua_cocos2dx_UILayoutParameter_setMargin);
        tolua_function(L, "getMargin", lua_cocos2dx_UILayoutParameter_getMargin);
    }
}

class LuaArmatureWrapper:public Object
{
public:
    LuaArmatureWrapper();
    virtual ~LuaArmatureWrapper();
    
    virtual void movementEventCallback(Armature* armature, MovementEventType type,const char* movementID);
    virtual void frameEventCallback(Bone* bone, const char* frameEventName, int orginFrameIndex, int currentFrameIndex);
    virtual void addArmatureFileInfoAsyncCallback(float percent);
};

LuaArmatureWrapper::LuaArmatureWrapper()
{
    
}

LuaArmatureWrapper::~LuaArmatureWrapper()
{
    
}

void LuaArmatureWrapper::movementEventCallback(Armature* armature, MovementEventType type,const char* movementID)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
    
    if (0 != handler)
    {
        std::string strMovementID = movementID;
        LuaArmatureMovementEventData movementData(armature,(int)type, strMovementID);
        
        LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::MOVEMENT_EVENT , (void*)&movementData);
        
        BasicScriptData data(this,(void*)&wrapperData);
        
        ScriptEvent scriptEvent(kArmatureWrapper,(void*)&data);
        
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

void LuaArmatureWrapper::frameEventCallback(Bone* bone, const char* frameEventName, int orginFrameIndex, int currentFrameIndex)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
    
    if (0 != handler)
    {
        std::string strFrameEventName(frameEventName);
        
        LuaArmatureFrameEventData frameData(bone,strFrameEventName,orginFrameIndex,currentFrameIndex);
        
        LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FRAME_EVENT , (void*)&frameData);
        
        BasicScriptData data(this,(void*)&wrapperData);
        
        ScriptEvent scriptEvent(kArmatureWrapper,(void*)&data);
        
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

void LuaArmatureWrapper::addArmatureFileInfoAsyncCallback(float percent)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
    
    if (0 != handler)
    {
        LuaArmatureWrapperEventData wrapperData(LuaArmatureWrapperEventData::LuaArmatureWrapperEventType::FILE_ASYNC , (void*)&percent);
        
        BasicScriptData data(this,(void*)&wrapperData);
        
        ScriptEvent scriptEvent(kArmatureWrapper,(void*)&data);
        
        ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&scriptEvent);
    }
}

static int lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ArmatureAnimation* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureAnimation*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc'\n", NULL);
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
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->setUserObject(wrapper);
        self->setMovementEventCallFunc(wrapper, movementEvent_selector(LuaArmatureWrapper::movementEventCallback));
        
        return 0;
    }
    
    CCLOG("'setMovementEventCallFunc' function of ArmatureAnimation has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setMovementEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static int lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    int argc = 0;
    ArmatureAnimation* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ArmatureAnimation",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureAnimation*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc'\n", NULL);
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
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->setUserObject(wrapper);
        self->setFrameEventCallFunc(wrapper, frameEvent_selector(LuaArmatureWrapper::frameEventCallback));
        
        return 0;
    }
    
    
    CCLOG("'setFrameEventCallFunc' function of ArmatureAnimation has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setFrameEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static void extendArmatureAnimation(lua_State* L)
{
    lua_pushstring(L, "ArmatureAnimation");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setMovementEventCallFunc", lua_cocos2dx_ArmatureAnimation_setMovementEventCallFunc);
        tolua_function(L, "setFrameEventCallFunc", lua_cocos2dx_ArmatureAnimation_setFrameEventCallFunc);
    }
}

static int lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc(lua_State* L)
{
    if (nullptr == L)
        return 0 ;
    
    int argc = 0;
    ArmatureDataManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"ArmatureDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ArmatureDataManager*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc'\n", NULL);
		return 0;
	}
#endif
    argc = lua_gettop(L) - 1;
    
    if (2 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!tolua_isstring(L, 2, 0, &tolua_err)  ||
            !toluafix_isfunction(L,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        const char* configFilePath = tolua_tostring(L, 2, "");
        LUA_FUNCTION handler = (  toluafix_ref_function(L, 3, 0));
    
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->addArmatureFileInfoAsync(configFilePath, wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    else if (4 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if ( !tolua_isstring(L, 2, 0, &tolua_err)  ||
             !tolua_isstring(L, 3, 0, &tolua_err)  ||
             !tolua_isstring(L, 4, 0, &tolua_err)  ||
             !toluafix_isfunction(L,5,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif        
        const char* imagePath = tolua_tostring(L, 2, "");
        const char* plistPath = tolua_tostring(L, 3, "");
        const char* configFilePath = tolua_tostring(L, 4, "");
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,5,0));
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)wrapper, handler, ScriptHandlerMgr::HandlerType::ARMATURE_EVENT);
        
        self->addArmatureFileInfoAsync(imagePath, plistPath,configFilePath,wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    
    CCLOG("'addArmatureFileInfoAsync' function of ArmatureDataManager has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addArmatureFileInfoAsync'.",&tolua_err);
    return 0;
#endif
}

static void extendArmatureDataManager(lua_State* L)
{
    lua_pushstring(L, "ArmatureDataManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addArmatureFileInfoAsync", lua_cocos2dx_ArmatureDataManager_addArmatureFileInfoAsyncCallFunc);
    }
}

int register_all_cocos2dx_coco_studio_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendUIWidget(L);
    extendUICheckBox(L);
    extendUISlider(L);
    extendUITextField(L);
    extendUIPageView(L);
    extendUIListView(L);
    extendLayoutParameter(L);
    extendArmatureAnimation(L);
    extendArmatureDataManager(L);
    
    return 0;
}