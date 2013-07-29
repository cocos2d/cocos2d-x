#ifdef __cplusplus
extern "C" {
#endif
#include "tolua_fix.h"
#ifdef __cplusplus
}
#endif

#include <map>
#include <string>
#include "LuaScriptHandlerMgr.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "Lua_web_socket.h"
#include "LuaOpengl.h"
#include "LuaScrollView.h"

using namespace cocos2d;
using namespace cocos2d::extension;

NS_CC_BEGIN

ScheduleHandlerDelegate* ScheduleHandlerDelegate::create()
{
    ScheduleHandlerDelegate *ret = new ScheduleHandlerDelegate();
    if (NULL != ret )
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

void ScheduleHandlerDelegate::scheduleFunc(float elapse)
{

}

void ScheduleHandlerDelegate::update(float elapse)
{

}


LuaCallFunc * LuaCallFunc::create(int nHandler)
{
    LuaCallFunc *ret = new LuaCallFunc();
    if (NULL != ret )
    {
        ret->autorelease();
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)ret, nHandler, ScriptHandlerMgr::kCallFuncHandler);
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}
void LuaCallFunc::execute()
{
    int handler =  ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::    kCallFuncHandler);
    
    if (0 == handler)
        return ;
    
    BasicScriptData data((void*)this,(void*)_target);
    ScriptEvent event(kCallFuncEvent,(void*)&data);
    ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
}

LuaCallFunc* LuaCallFunc::clone() const
{
    int handler =  ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::    kCallFuncHandler);
    
    if (0 == handler)
        return NULL;
    
    auto ret = new LuaCallFunc();

    int newscriptHandler = cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->reallocateScriptHandler(handler);
    
    ScriptHandlerMgr::getInstance()->addObjectHandler((void*)ret, newscriptHandler, ScriptHandlerMgr::kCallFuncHandler);
    
    ret->autorelease();
    
    return ret;
}

ScriptHandlerMgr* ScriptHandlerMgr::_scriptHandlerMgr = NULL;

ScriptHandlerMgr::ScriptHandlerMgr()
{
    
}
ScriptHandlerMgr::~ScriptHandlerMgr()
{
    CC_SAFE_DELETE(_scriptHandlerMgr);
}
ScriptHandlerMgr* ScriptHandlerMgr::getInstance()
{
    if (NULL == _scriptHandlerMgr)
    {
        _scriptHandlerMgr = new ScriptHandlerMgr();
        _scriptHandlerMgr->init();
    }
    return _scriptHandlerMgr;
}

void ScriptHandlerMgr::init()
{
    _mapObjectHandlers.clear();
}

void ScriptHandlerMgr::addObjectHandler(void* object,int handler,int eventType)
{
    if (NULL == object)
        return;
    
    //may be not need
    removeObjectHandler(object,eventType);
    
    auto iter = _mapObjectHandlers.find(object);
    VecEventHandlers vecHandlers;
    vecHandlers.clear();
    if (_mapObjectHandlers.end() != iter)
    {
        vecHandlers = iter->second;
    }
    
    PairEventHandler eventHanler = std::make_pair(eventType, handler);
    vecHandlers.push_back(eventHanler);
    _mapObjectHandlers[object] = vecHandlers;
}
void ScriptHandlerMgr::removeObjectHandler(void* object,int eventType)
{
    if (NULL == object || _mapObjectHandlers.empty())
        return;
    
    auto iterMap = _mapObjectHandlers.find(object);
    if (_mapObjectHandlers.end() == iterMap)
        return;
    
    if (iterMap->second.empty())
        return;
    
    auto iterVec = iterMap->second.begin();
    bool exist  = false;
    for (; iterVec != iterMap->second.end(); iterVec++)
    {
        if (iterVec->first == eventType)
        {
            exist = true;
            break;
        }
    }
    
    if (exist)
    {
        iterMap->second.erase(iterVec);
    }

}
int  ScriptHandlerMgr::getObjectHandler(void* object,int eventType)
{
    if (NULL == object ||   _mapObjectHandlers.empty() )
        return 0;
    
    auto iter = _mapObjectHandlers.find(object);
    
    if (_mapObjectHandlers.end() != iter)
    {
        auto iterVec = (iter->second).begin();
        for (; iterVec != (iter->second).end(); iterVec++)
        {
            if (iterVec->first == eventType)
            {
                return iterVec->second;
            }
        }
    }
    
    return 0;
}
void ScriptHandlerMgr::removeObjectAllHandlers(void* object)
{
    if (NULL == object || _mapObjectHandlers.empty())
        return;
    
    auto iter = _mapObjectHandlers.find(object);
    
    if (_mapObjectHandlers.end() != iter)
    {
        (iter->second).clear();
        _mapObjectHandlers.erase(iter);
    }
}

NS_CC_END

int tolua_Cocos2d_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err)    ||
        !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* node = (Node*)tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)node, handler, ScriptHandlerMgr::kNodeHandler);
        return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err)    ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Node* node = (Node*)tolua_tousertype(tolua_S,1,0);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)node, ScriptHandlerMgr::kNodeHandler);
        return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_registerScriptTapHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCMenuItem",0,&tolua_err)    ||
        !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MenuItem* menuItem = (MenuItem*)tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)menuItem, handler, ScriptHandlerMgr::kMenuClickHandler);
        return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_unregisterScriptTapHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCMenuItem",0,&tolua_err)    ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        MenuItem* menuItem = (MenuItem*)tolua_tousertype(tolua_S,1,0);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)menuItem, ScriptHandlerMgr::kMenuClickHandler);
        return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_registerScriptTouchHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
        !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
        !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,6,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Layer* self = (Layer*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        bool isMultiTouches = ((bool)  tolua_toboolean(tolua_S,3,false));
        int priority = ((int)  tolua_tonumber(tolua_S,4,0));
        bool swallowTouches = (bool)tolua_toboolean(tolua_S, 5, 0);
        Touch::DispatchMode touchesMode = Touch::DispatchMode::ALL_AT_ONCE;
        if (!isMultiTouches)
            touchesMode = Touch::DispatchMode::ONE_BY_ONE;
        self->setTouchMode(touchesMode);
        self->setTouchPriority(priority);
		self->setSwallowsTouches(swallowTouches);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, ScriptHandlerMgr::kTouchesHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTouchHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_unregisterScriptTouchHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Layer* layer = (Layer*)  tolua_tousertype(tolua_S,1,0);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)layer, ScriptHandlerMgr::kTouchesHandler);
        return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptTouchHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_registerScriptKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Layer* layer = (Layer*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)layer, handler, ScriptHandlerMgr::kKeypadHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptKeypadHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_unregisterScriptKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Layer* layer = (Layer*)  tolua_tousertype(tolua_S,1,0);
        
        ScriptHandlerMgr::getInstance()->removeObjectHandler(layer, ScriptHandlerMgr::kKeypadHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptKeypadHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_registerScriptAccelerateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Layer* layer = (Layer*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)layer, handler, ScriptHandlerMgr::kAccelerometerHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptAccelerateHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_unregisterScriptAccelerateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Layer* layer = (Layer*)  tolua_tousertype(tolua_S,1,0);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)layer, ScriptHandlerMgr::kAccelerometerHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptAccelerateHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_registerControlEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnumber(tolua_S, 3, 0, &tolua_err)||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Control* control = (Control*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        int controlevent = (int)tolua_tonumber(tolua_S,3,0);
        for (int i = 0; i < kControlEventTotalNumber; i++)
        {
            if ((controlevent & (1 << i)))
            {
                int handlerevent  = ScriptHandlerMgr::kControlTouchDownHandler + i;
                ScriptHandlerMgr::getInstance()->addObjectHandler((void*)control, handler, handlerevent);
                break;
            }
        }        
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerControlEventHandler'.",&tolua_err);
    return 0;
#endif
}
int tolua_Cocos2d_unregisterControlEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCControl",0,&tolua_err) ||
        !tolua_isnumber(tolua_S, 2, 0, &tolua_err)||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        Control* control = (Control*)  tolua_tousertype(tolua_S,1,0);
        int controlevent = (int)tolua_tonumber(tolua_S,2,0);
        for (int i = 0; i < kControlEventTotalNumber; i++)
        {
            if ((controlevent & (1 << i)))
            {
                int handlerevent  = ScriptHandlerMgr::kControlTouchDownHandler + i;
                ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)control, handlerevent);
                break;
            }
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerControlEventHandler'.",&tolua_err);
    return 0;
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
int tolua_Cocos2d_WebSocket_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket* self    = (LuaWebSocket*)  tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            int handler = (  toluafix_ref_function(tolua_S,2,0));
            ScriptHandlerMgr::HandlerEventType handlerType = (ScriptHandlerMgr::HandlerEventType)((int)tolua_tonumber(tolua_S,3,0) + ScriptHandlerMgr::kWebSocketScriptHandlerOpen);
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_WebSocket_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"WebSocket",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket* self    = (LuaWebSocket*)  tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            ScriptHandlerMgr::HandlerEventType handlerType = (ScriptHandlerMgr::HandlerEventType)((int)tolua_tonumber(tolua_S,2,0) + ScriptHandlerMgr::kWebSocketScriptHandlerOpen);

            ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}
#endif

int tolua_Cocos2d_GLNode_registerScriptDrawHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"GLNode",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        GLNode* glNode = (GLNode*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)glNode, handler, ScriptHandlerMgr::kGLNodeDrawHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptDrawHandler'.",&tolua_err);
    return 0;
#endif
}


int tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"GLNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err))
        goto tolua_lerror;
    else
#endif
    {
        GLNode* glNode = (GLNode*)tolua_tousertype(tolua_S,1,0);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)glNode,ScriptHandlerMgr::kGLNodeDrawHandler);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptDrawHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_ScrollView_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self    = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        ScriptHandlerMgr::HandlerEventType handlerType = (ScriptHandlerMgr::HandlerEventType) ((int)tolua_tonumber(tolua_S,3,0) + ScriptHandlerMgr::kScrollViewScrollHandler);
        ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_ScrollView_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
        !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LuaScrollView* self    = (LuaScrollView*)  tolua_tousertype(tolua_S,1,0);
        ScriptHandlerMgr::HandlerEventType handlerType = (ScriptHandlerMgr::HandlerEventType) ((int)tolua_tonumber(tolua_S,2,0) + ScriptHandlerMgr::kScrollViewScrollHandler);
        ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}


static void tolua_reg_script_handler_mgr_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "CCCallFunc");
    tolua_usertype(tolua_S, "ScheduleHandlerDelegate");
    tolua_usertype(tolua_S, "ScriptHandlerMgr");
}

/* method: create of class  LuaCallFunc */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_LuaCallFunc_create00
static int tolua_Cocos2d_LuaCallFunc_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"CCCallFunc",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        LUA_FUNCTION funcID = (  toluafix_ref_function(tolua_S,2,0));
        {
            LuaCallFunc* tolua_ret = (LuaCallFunc*)  LuaCallFunc::create(funcID);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCCallFunc");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_getInstance00
static int tolua_Cocos2d_ScriptHandlerMgr_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* tolua_ret = (ScriptHandlerMgr*)  ScriptHandlerMgr::getInstance();
        tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScriptHandlerMgr");
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_script_handler_mgr_type(tolua_S);
    tolua_module(tolua_S, NULL,0);
    tolua_beginmodule(tolua_S, NULL);
      tolua_cclass(tolua_S, "CCCallFunc", "CCCallFunc","CCActionInstant",NULL);
      tolua_beginmodule(tolua_S, "CCCallFunc");
         tolua_function(tolua_S, "create", tolua_Cocos2d_LuaCallFunc_create00);
      tolua_endmodule(tolua_S);
      tolua_cclass(tolua_S,"ScriptHandlerMgr","ScriptHandlerMgr","",NULL);
      tolua_beginmodule(tolua_S, "ScriptHandlerMgr");
        tolua_constant(tolua_S,"kNormalHandler",ScriptHandlerMgr::kNodeHandler);
        tolua_constant(tolua_S,"kMenuClickHandler",ScriptHandlerMgr::kMenuClickHandler);
        tolua_constant(tolua_S,"kNotificationHandler",ScriptHandlerMgr::kNotificationHandler);
        tolua_constant(tolua_S,"kCallFuncHandler",ScriptHandlerMgr::kCallFuncHandler);
        tolua_constant(tolua_S,"kScheduleHandler",ScriptHandlerMgr::kScheduleHandler);
        tolua_constant(tolua_S,"kTouchesHandler",ScriptHandlerMgr::kTouchesHandler);
        tolua_constant(tolua_S,"kKeypadHandler",ScriptHandlerMgr::kKeypadHandler);
        tolua_constant(tolua_S,"kAccelerometerHandler",ScriptHandlerMgr::kAccelerometerHandler);
        tolua_constant(tolua_S,"kControlTouchDownHandler",ScriptHandlerMgr::kControlTouchDownHandler);
        tolua_constant(tolua_S,"kControlTouchDragInsideHandler",ScriptHandlerMgr::kControlTouchDragInsideHandler);
        tolua_constant(tolua_S,"kControlTouchDragOutsideHandler",ScriptHandlerMgr::kControlTouchDragOutsideHandler);
        tolua_constant(tolua_S,"kControlTouchDragEnterHandler",ScriptHandlerMgr::kControlTouchDragEnterHandler);
        tolua_constant(tolua_S,"kControlTouchDragExitHandler",ScriptHandlerMgr::kControlTouchDragExitHandler);
        tolua_constant(tolua_S,"kControlTouchUpInsideHandler",ScriptHandlerMgr::kControlTouchUpInsideHandler);
        tolua_constant(tolua_S,"kControlTouchUpOutsideHandler",ScriptHandlerMgr::kControlTouchUpOutsideHandler);
        tolua_constant(tolua_S,"kControlTouchCancelHandler",ScriptHandlerMgr::kControlTouchCancelHandler);
        tolua_constant(tolua_S,"kControlValueChangedHandler",ScriptHandlerMgr::kControlValueChangedHandler);
        tolua_constant(tolua_S,"kWebSocketScriptHandlerOpen",ScriptHandlerMgr::kWebSocketScriptHandlerOpen);
        tolua_constant(tolua_S,"kWebSocketScriptHandlerMessage",ScriptHandlerMgr::kWebSocketScriptHandlerMessage);
        tolua_constant(tolua_S,"kWebSocketScriptHandlerClose",ScriptHandlerMgr::kWebSocketScriptHandlerClose);
        tolua_constant(tolua_S,"kWebSocketScriptHandlerError",ScriptHandlerMgr::kWebSocketScriptHandlerError);
        tolua_constant(tolua_S,"kGLNodeDrawHandler",ScriptHandlerMgr::kGLNodeDrawHandler);
        tolua_constant(tolua_S,"kScrollViewScrollHandler",ScriptHandlerMgr::kScrollViewScrollHandler);
        tolua_constant(tolua_S,"kScrollViewZoomHandler",ScriptHandlerMgr::kScrollViewZoomHandler);
        tolua_function(tolua_S, "getInstance", tolua_Cocos2d_ScriptHandlerMgr_getInstance00);
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   return 1; 
}
