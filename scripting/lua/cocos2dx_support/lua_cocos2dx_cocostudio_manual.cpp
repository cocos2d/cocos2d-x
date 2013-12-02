#include "lua_cocos2dx_cocostudio_manual.h"

#ifdef __cplusplus
extern "C" {
#endif
#include  "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"


USING_NS_CC;
USING_NS_CC_EXT;

class LuaCocoStudioEventListener:public CCObject
{
public:
    LuaCocoStudioEventListener();
    virtual ~LuaCocoStudioEventListener();
    
    static LuaCocoStudioEventListener* create();
    
    virtual void eventCallbackFunc(CCObject* sender,int eventType);
    
    void setHandler(int handler){ m_lHandler = handler; }
    int  getHandler() { return m_lHandler; }
private:
    long m_lHandler;
};

LuaCocoStudioEventListener::LuaCocoStudioEventListener():m_lHandler(0)
{
    
}

LuaCocoStudioEventListener::~LuaCocoStudioEventListener()
{
    
}

LuaCocoStudioEventListener* LuaCocoStudioEventListener::create()
{
    LuaCocoStudioEventListener* listener = new LuaCocoStudioEventListener();
    if (NULL == listener)
        return NULL;
    
    listener->autorelease();
    
    return listener;
}

void LuaCocoStudioEventListener::eventCallbackFunc(CCObject* sender,int eventType)
{
    if (0 != m_lHandler)
    {
        CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();        
        CCLuaStack* pStack = pEngine->getLuaStack();
        pStack->pushCCObject(sender, "CCObject");
        pStack->pushInt(eventType);
        pStack->executeFunctionByHandler(m_lHandler, 2);
        pStack->clean();
    }
}

static int tolua_Cocos2dx_UIWidget_addTouchEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UIWidget",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UIWidget* self = (UIWidget*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTouchEventListener'", NULL);
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (NULL == listener)
        {
            tolua_error(tolua_S,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        listener->setHandler(handler);
        self->setUserObject(listener);
        self->addTouchEventListener(listener, toucheventselector(LuaCocoStudioEventListener::eventCallbackFunc));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addTouchEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendUIWidget(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UIWidget");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addTouchEventListener", tolua_Cocos2dx_UIWidget_addTouchEventListener00);
    }
}

static int tolua_Cocos2dx_UICheckBox_addEventListenerCheckBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UICheckBox",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UICheckBox* self = (UICheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListenerCheckBox'", NULL);
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (NULL == listener)
        {
            tolua_error(tolua_S,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        listener->setHandler(handler);
        self->setUserObject(listener);
        self->addEventListenerCheckBox(listener, checkboxselectedeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addEventListenerCheckBox'.",&tolua_err);
    return 0;
#endif
}

static void extendUICheckBox(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UICheckBox");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addEventListenerCheckBox", tolua_Cocos2dx_UICheckBox_addEventListenerCheckBox00);
    }
}

static int tolua_Cocos2dx_UISlider_addEventListenerSlider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UISlider",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UISlider* self = (UISlider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListenerSlider'", NULL);
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (NULL == listener)
        {
            tolua_error(tolua_S,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        listener->setHandler(handler);
        self->setUserObject(listener);
        self->addEventListenerSlider(listener, sliderpercentchangedselector(LuaCocoStudioEventListener::eventCallbackFunc));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addEventListenerSlider'.",&tolua_err);
    return 0;
#endif
}

static void extendUISlider(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UISlider");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addEventListenerSlider", tolua_Cocos2dx_UISlider_addEventListenerSlider00);
    }
}

static int tolua_Cocos2dx_UITextField_addEventListenerTextField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UITextField",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UITextField* self = (UITextField*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListenerTextField'", NULL);
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (NULL == listener)
        {
            tolua_error(tolua_S,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        listener->setHandler(handler);
        self->setUserObject(listener);
        self->addEventListenerTextField(listener, textfieldeventselector(LuaCocoStudioEventListener::eventCallbackFunc));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addEventListenerTextField'.",&tolua_err);
    return 0;
#endif
}

static void extendUITextFieldr(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UITextField");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addEventListenerTextField", tolua_Cocos2dx_UITextField_addEventListenerTextField00);
    }
}

static int tolua_Cocos2dx_UIPageView_addEventListenerPageView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UIPageView",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UIPageView* self = (UIPageView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListenerPageView'", NULL);
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (NULL == listener)
        {
            tolua_error(tolua_S,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        listener->setHandler(handler);
        self->setUserObject(listener);
        self->addEventListenerPageView(listener, pagevieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addEventListenerPageView'.",&tolua_err);
    return 0;
#endif
}

static void extendUIPageView(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UIPageView");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addEventListenerPageView", tolua_Cocos2dx_UIPageView_addEventListenerPageView00);
    }
}

static int tolua_Cocos2dx_UIListView_addEventListenerListView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UIListView",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UIListView* self = (UIListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addEventListenerListView'", NULL);
#endif
        LuaCocoStudioEventListener* listener = LuaCocoStudioEventListener::create();
        if (NULL == listener)
        {
            tolua_error(tolua_S,"LuaCocoStudioEventListener create fail\n", NULL);
            return 0;
        }
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        listener->setHandler(handler);
        self->setUserObject(listener);
        self->addEventListenerListView(listener, listvieweventselector(LuaCocoStudioEventListener::eventCallbackFunc));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addEventListenerListView'.",&tolua_err);
    return 0;
#endif
}

static void extendUIListView(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UIListView");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addEventListenerListView", tolua_Cocos2dx_UIListView_addEventListenerListView00);
    }
}

static int tolua_Cocos2dx_UILayoutParameter_setMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UILayoutParameter",0,&tolua_err) ||
        !tolua_istable(tolua_S, 2, 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UILayoutParameter* self = (UILayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMargin'", NULL);
#endif
        UIMargin margin;
        lua_pushstring(tolua_S, "left");
        lua_gettable(tolua_S,2);
        margin.left = lua_isnil(tolua_S,-1) ? 0 : lua_tonumber(tolua_S,-1);
        lua_pop(tolua_S,1);
        
        lua_pushstring(tolua_S, "top");
        lua_gettable(tolua_S,2);
        margin.top = lua_isnil(tolua_S,-1) ? 0 : lua_tonumber(tolua_S,-1);
        lua_pop(tolua_S,1);
        
        lua_pushstring(tolua_S, "right");
        lua_gettable(tolua_S,2);
        margin.right = lua_isnil(tolua_S,-1) ? 0 : lua_tonumber(tolua_S,-1);
        lua_pop(tolua_S,1);
        
        lua_pushstring(tolua_S, "bottom");
        lua_gettable(tolua_S,2);
        margin.bottom = lua_isnil(tolua_S,-1) ? 0 : lua_tonumber(tolua_S,-1);
        lua_pop(tolua_S,1);
        
        self->setMargin(margin);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setMargin'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2dx_UILayoutParameter_getMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"UILayoutParameter",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        UILayoutParameter* self = (UILayoutParameter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMargin'", NULL);
#endif
        UIMargin margin = self->getMargin();
        
        lua_newtable(tolua_S);
        
        lua_pushstring(tolua_S, "left");
        lua_pushnumber(tolua_S, (lua_Number) margin.left);
        lua_rawset(tolua_S, -3);
        
        lua_pushstring(tolua_S, "top");
        lua_pushnumber(tolua_S, (lua_Number) margin.top);
        lua_rawset(tolua_S, -3);
        
        lua_pushstring(tolua_S, "right");
        lua_pushnumber(tolua_S, (lua_Number) margin.right);
        lua_rawset(tolua_S, -3);
        
        lua_pushstring(tolua_S, "bottom");
        lua_pushnumber(tolua_S, (lua_Number) margin.bottom);
        lua_rawset(tolua_S, -3);
        
        return 1;
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getMargin'.",&tolua_err);
    return 0;
#endif
}

static void extendUILayoutParameter(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "UILayoutParameter");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setMargin", tolua_Cocos2dx_UILayoutParameter_setMargin00);
        tolua_function(tolua_S, "getMargin", tolua_Cocos2dx_UILayoutParameter_getMargin00);
    }
}

class LuaArmatureWrapper:public CCObject
{
public:
    LuaArmatureWrapper();
    virtual ~LuaArmatureWrapper();
    
    virtual void movementEventCallback(CCArmature* armature, MovementEventType type,const char* movementID);
    virtual void frameEventCallback(CCBone* bone, const char* frameEventName, int orginFrameIndex, int currentFrameIndex);
    virtual void addArmatureFileInfoAsyncCallback(float percent);
    
    void setHandler(int handler){ m_lHandler = handler; }
    int  getHandler() { return m_lHandler; }
private:
    long m_lHandler;
};

LuaArmatureWrapper::LuaArmatureWrapper():m_lHandler(0)
{
    
}

LuaArmatureWrapper::~LuaArmatureWrapper()
{
    
}

void LuaArmatureWrapper::movementEventCallback(CCArmature* armature, MovementEventType type,const char* movementID)
{
    if (0 != m_lHandler)
    {
        CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
        CCLuaStack* pStack = pEngine->getLuaStack();
        
        pStack->pushCCObject(armature, "CCArmature");
        pStack->pushInt(type);
        pStack->pushString(movementID);
        pStack->executeFunctionByHandler(m_lHandler, 3);
        pStack->clean();
    }
}

void LuaArmatureWrapper::frameEventCallback(CCBone* bone, const char* frameEventName, int orginFrameIndex, int currentFrameIndex)
{
    if (0 != m_lHandler)
    {
        CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
        CCLuaStack* pStack = pEngine->getLuaStack();
        
        pStack->pushCCObject(bone, "CCBone");
        pStack->pushString(frameEventName);
        pStack->pushInt(orginFrameIndex);
        pStack->pushInt(currentFrameIndex);
        pStack->executeFunctionByHandler(m_lHandler, 4);
        pStack->clean();
    }
}

void LuaArmatureWrapper::addArmatureFileInfoAsyncCallback(float percent)
{
    if (0 != m_lHandler)
    {
        CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
        CCLuaStack* pStack = pEngine->getLuaStack();
        
        pStack->pushFloat(percent);
        pStack->executeFunctionByHandler(m_lHandler, 1);
        pStack->clean();
    }
}

static int tolua_Cocos2dx_CCArmatureAnimation_setMovementEventCallFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMovementEventCallFunc'", NULL);
#endif
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        if (NULL == wrapper)
        {
            tolua_error(tolua_S,"LuaArmatureWrapper create fail\n", NULL);
            return 0;
        }
        
        wrapper->autorelease();
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        wrapper->setHandler(handler);
        self->setUserObject(wrapper);
        self->setMovementEventCallFunc(wrapper, movementEvent_selector(LuaArmatureWrapper::movementEventCallback));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setMovementEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2dx_CCArmatureAnimation_setFrameEventCallFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArmatureAnimation",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCArmatureAnimation* self = (CCArmatureAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFrameEventCallFunc'", NULL);
#endif
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        if (NULL == wrapper)
        {
            tolua_error(tolua_S,"LuaArmatureWrapper create fail\n", NULL);
            return 0;
        }
        
        wrapper->autorelease();
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        wrapper->setHandler(handler);
        self->setUserObject(wrapper);
        self->setFrameEventCallFunc(wrapper, frameEvent_selector(LuaArmatureWrapper::frameEventCallback));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setFrameEventCallFunc'.",&tolua_err);
    return 0;
#endif
}

static void extendCCArmatureAnimation(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCArmatureAnimation");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setMovementEventCallFunc", tolua_Cocos2dx_CCArmatureAnimation_setMovementEventCallFunc00);
        tolua_function(tolua_S, "setFrameEventCallFunc", tolua_Cocos2dx_CCArmatureAnimation_setFrameEventCallFunc00);
    }
}

static int tolua_Cocos2dx_CCArmatureDataManager_addArmatureFileInfoAsyncCallFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)   ||
        !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfoAsyncCallFunc'", NULL);
#endif
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        if (NULL == wrapper)
        {
            tolua_error(tolua_S,"LuaArmatureWrapper create fail\n", NULL);
            return 0;
        }
        
        wrapper->autorelease();
        const char* configFilePath = tolua_tostring(tolua_S, 2, "");
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
        
        wrapper->setHandler(handler);
        self->addArmatureFileInfoAsync(configFilePath, wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'addArmatureFileInfoAsyncCallFunc'.",&tolua_err);
    return 0;
#endif
}

static int tolua_Cocos2dx_CCArmatureDataManager_addArmatureFileInfoAsyncCallFunc01(lua_State* tolua_S)
{
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCArmatureDataManager",0,&tolua_err) ||
        !tolua_isstring(tolua_S, 2, 0, &tolua_err)  ||
        !tolua_isstring(tolua_S, 3, 0, &tolua_err)  ||
        !tolua_isstring(tolua_S, 4, 0, &tolua_err)  ||
        !toluafix_isfunction(tolua_S,5,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
    {
        
        CCArmatureDataManager* self = (CCArmatureDataManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addArmatureFileInfoAsyncCallFunc'", NULL);
#endif
        
        const char* imagePath = tolua_tostring(tolua_S, 2, "");
        const char* plistPath = tolua_tostring(tolua_S, 3, "");
        const char* configFilePath = tolua_tostring(tolua_S, 4, "");
        
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,5,0));
        
        LuaArmatureWrapper* wrapper = new LuaArmatureWrapper();
        wrapper->autorelease();
        wrapper->setHandler(handler);
        
        self->addArmatureFileInfoAsync(imagePath, plistPath,configFilePath,wrapper, schedule_selector(LuaArmatureWrapper::addArmatureFileInfoAsyncCallback));
        
        return 0;
    }
    return 0;
tolua_lerror:
    return tolua_Cocos2dx_CCArmatureDataManager_addArmatureFileInfoAsyncCallFunc00(tolua_S);
}

static void extendCCArmatureDataManager(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "CCArmatureDataManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "addArmatureFileInfoAsync", tolua_Cocos2dx_CCArmatureDataManager_addArmatureFileInfoAsyncCallFunc00);
        tolua_function(tolua_S, "addArmatureFileInfoAsync", tolua_Cocos2dx_CCArmatureDataManager_addArmatureFileInfoAsyncCallFunc01);
    }
}

int register_all_cocos2dx_studio_manual(lua_State* tolua_S)
{
    extendUIWidget(tolua_S);
    extendUICheckBox(tolua_S);
    extendUISlider(tolua_S);
    extendUITextFieldr(tolua_S);
    extendUIPageView(tolua_S);
    extendUIListView(tolua_S);
    extendUILayoutParameter(tolua_S);
    extendCCArmatureAnimation(tolua_S);
    extendCCArmatureDataManager(tolua_S);
    return 0;
}
