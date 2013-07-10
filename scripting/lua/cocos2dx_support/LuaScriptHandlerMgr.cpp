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

using namespace cocos2d;
using namespace cocos2d::extension;


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
    int handler = ScriptHandlerMgr::getInstance()->getObjecHandlerByEvent((void*)this,ScriptHandlerMgr::kScheduleHandler);
    if (0 !=  handler)
    {
        SchedulerScriptData data(handler,elapse);
        ScriptEvent event(kScheduleEvent,(void*)&data);
		ScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
    }
}

void ScheduleHandlerDelegate::update(float elapse)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjecHandlerByEvent((void*)this,ScriptHandlerMgr::kScheduleHandler);
    
    if (0 != handler)
    {
        SchedulerScriptData data(handler,elapse);
        ScriptEvent event(kScheduleEvent,(void*)&data);
		ScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
    }
}

CallFuncHandlerDelegate* CallFuncHandlerDelegate::create()
{
    CallFuncHandlerDelegate *ret = new CallFuncHandlerDelegate();
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

void CallFuncHandlerDelegate::callFunc(Node* node)
{
    if (NULL == _callFunc)
        return;
    
    int handler = ScriptHandlerMgr::getInstance()->getObjecHandlerByEvent((void*)_callFunc,ScriptHandlerMgr::kCallFuncHandler);
    
    if (0 != handler)
    {
        BasicScriptData data((void*)this,(void*)_callFunc->getTarget());
        ScriptEvent event(kCallFuncEvent,(void*)&data);
		ScriptEngineManager::sharedManager()->getScriptEngine()->sendEvent(&event);
    }
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
    _mapNodeScehdules.clear();
}

void ScriptHandlerMgr::registerObjectHandler(void* object,int handler,int eventType)
{
    if (NULL == object)
        return;
    
    //may be not need
    unregisterObjectHandler(object,eventType);
    
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
void ScriptHandlerMgr::unregisterObjectHandler(void* object,int eventType)
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

int  ScriptHandlerMgr::getObjecHandlerByEvent(void* object,int eventType)
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

ScheduleHandlerDelegate* ScriptHandlerMgr::registerScheduleHandler(int handler,float interval, unsigned int repeat, float delay, bool paused)
{
    if ( 0 == handler || NULL == Director::sharedDirector()->getScheduler() )
        return NULL;
    
    ScheduleHandlerDelegate* scheduleDelegate = ScheduleHandlerDelegate::create();
    if (NULL == scheduleDelegate)
        return NULL;
    //repeat = -1:repeateForever
    Director::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(ScheduleHandlerDelegate::scheduleFunc),scheduleDelegate,interval,repeat,delay,paused);
    
    registerObjectHandler(scheduleDelegate, handler, ScriptHandlerMgr::kScheduleHandler);
    return scheduleDelegate;
}

void ScriptHandlerMgr::unregisterScheduleHandler(ScheduleHandlerDelegate* scheduleDelegate)
{
     if( NULL == scheduleDelegate)
         return;
    
    unregisterObjectHandler((void*)scheduleDelegate,kScheduleHandler);
    Director::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(ScheduleHandlerDelegate::scheduleFunc), (Object*)scheduleDelegate);
}

void ScriptHandlerMgr::registerNotificationHandler(Object* target,int handler,const char* name)
{
    if (NotificationCenter::sharedNotificationCenter()->observerExisted(target, name))
        return;
    
    NotificationObserver* observer = new NotificationObserver(target, NULL, name, NULL);
    if (NULL  == observer)
        return;
    observer->autorelease();
    NotificationCenter::sharedNotificationCenter()->_observers->addObject(observer);
    
    registerObjectHandler(observer, handler, kNotificationHandler);
}

void ScriptHandlerMgr::unregisterNotificationHandler(Object* target,const char* name)
{
    Object* obj = NULL;
    CCARRAY_FOREACH(NotificationCenter::sharedNotificationCenter()->_observers, obj)
    {
        NotificationObserver* observer = (NotificationObserver*) obj;
        if (!observer)
            continue;
        
        if ( !strcmp(observer->getName(),name) && observer->getTarget() == target)
        {
            unregisterObjectHandler(observer, kNotificationHandler);
            NotificationCenter::sharedNotificationCenter()->_observers->removeObject(observer);
        }
    }
}


cocos2d::CallFuncN* ScriptHandlerMgr::registerCallFuncHandler(int handler)
{
    if (0 == handler)
        return NULL;
    
    CallFuncHandlerDelegate* callFuncDelegate = CallFuncHandlerDelegate::create();
    if (NULL == callFuncDelegate)
        return NULL;
    
    cocos2d::CallFuncN* callFunc = cocos2d::CallFuncN::create(callFuncDelegate, callfuncN_selector(CallFuncHandlerDelegate::callFunc));
    
    if (NULL == callFunc)
        return NULL;
    
    callFuncDelegate->setCallFunc(callFunc);
    
    registerObjectHandler(callFunc, handler, kCallFuncHandler);
    return callFunc;
}

void ScriptHandlerMgr::registerTouchesHandler(void* object,int objectType,int handler,bool isMultiTouches ,int priority ,bool swallowsTouches)
{
    if (NULL == object || 0 == handler)
        return;
    
    switch (objectType)
    {
        case kLayerTouches:
        {
            unregisterObjectHandler(object, kTouchesHandler);
            Layer* layer = (Layer*)object;
            if (isMultiTouches)
            {
                layer->setTouchMode(kTouchesAllAtOnce);
            }
            else
            {
                layer->setTouchMode(kTouchesOneByOne);
            }
            
            layer->setTouchPriority(priority);
            //layer swallowsTouches default true
            registerObjectHandler(object, handler, kTouchesHandler);
        }
        break;
            
        default:
            break;
    }
}

void ScriptHandlerMgr::registerKeypadHandler(void* object,int objectType,int handler)
{
    if (NULL == object || 0 == handler)
        return;
    
    switch (objectType) {
        case kLayerKeypad:
        {
            unregisterObjectHandler(object, kKeypadHandler);
            registerObjectHandler(object, handler, kKeypadHandler);
        }
        break;
            
        default:
            break;
    }
}

ScheduleHandlerDelegate* ScriptHandlerMgr::registerNodeSchedule(cocos2d::Node* node,int handler,float interval,unsigned int repeat,float delay)
{
    
    if (NULL == node || 0 == handler)
        return NULL;
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return NULL;
    
    ScheduleHandlerDelegate* scheduleDelegate = ScheduleHandlerDelegate::create();
    if (NULL == scheduleDelegate)
        return NULL;
        
    scheduler->scheduleSelector(schedule_selector(ScheduleHandlerDelegate::scheduleFunc),scheduleDelegate,interval,repeat,delay,!node->isRunning());
    
    registerObjectHandler(scheduleDelegate, handler, kScheduleHandler);
    
    addNodeSchedule(node, scheduleDelegate);

    return scheduleDelegate;
}

ScheduleHandlerDelegate* ScriptHandlerMgr::registerNodeScheduleOnce(cocos2d::Node* node,int handler,float delay)
{
    if (NULL == node || 0 == handler )
        return NULL;
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return NULL;
    
    ScheduleHandlerDelegate* scheduleDelegate = ScheduleHandlerDelegate::create();
    if (NULL == scheduleDelegate)
        return NULL;
    
    scheduler->scheduleSelector(schedule_selector(ScheduleHandlerDelegate::scheduleFunc), scheduleDelegate, 0, 0, delay, !node->isRunning());
    
    addNodeSchedule(node, scheduleDelegate);
    
    registerObjectHandler(scheduleDelegate, handler, kScheduleHandler);
    
    return scheduleDelegate;
}

void ScriptHandlerMgr::unregisterNodeSchedule(cocos2d::Node* node,ScheduleHandlerDelegate* scheduleDelegate)
{
    if ( NULL == node || NULL ==  scheduleDelegate)
        return;
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return ;
    
    unregisterObjectHandler(scheduleDelegate,kScheduleHandler);
    removeNodeSchedule(node, scheduleDelegate);
    
    scheduler->unscheduleSelector(schedule_selector(ScheduleHandlerDelegate::scheduleFunc), (Object*)scheduleDelegate);
    
    return;
}

ScheduleHandlerDelegate* ScriptHandlerMgr::registerNodeScheduleUpdateWithPriority(cocos2d::Node* node,int handler,int priority)
{
    if ( NULL == node || 0 == handler)
        return NULL;
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return NULL;
    
    unregisterNodeScheduleUpdateWithPriority(node);
    
    ScheduleHandlerDelegate* scheduleDelegate = ScheduleHandlerDelegate::create();
    if (NULL == scheduleDelegate)
        return NULL;
    
    scheduleDelegate->setUpdateSchedule(true);
    
    scheduler->scheduleUpdateForTarget(scheduleDelegate, priority, node->isRunning());
    
    addNodeSchedule(node, scheduleDelegate);
    
    registerObjectHandler(scheduleDelegate, handler, ScriptHandlerMgr::kScheduleHandler);
    
    return scheduleDelegate;
}

void ScriptHandlerMgr::unregisterNodeScheduleUpdateWithPriority(cocos2d::Node* node,ScheduleHandlerDelegate* scheduleDelegate)
{
    if (NULL == node )
        return;
    
    ScheduleHandlerDelegate* tmpScheduleDelegate = scheduleDelegate;
    if (NULL == tmpScheduleDelegate)
    {
        tmpScheduleDelegate = getNodeScheduleUpdateWithPriority(node);
    }
    
    if (NULL == tmpScheduleDelegate)
        return;
    
    unregisterObjectHandler(tmpScheduleDelegate,kScheduleHandler);
    
    removeNodeSchedule(node,tmpScheduleDelegate);
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return ;
    
    scheduler->unscheduleUpdateForTarget(scheduleDelegate);
}

ScheduleHandlerDelegate* ScriptHandlerMgr::getNodeScheduleUpdateWithPriority(cocos2d::Node* node)
{
    if (NULL == node || _mapNodeScehdules.empty() )
        return NULL;
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return NULL;
    
    auto iterMap = _mapNodeScehdules.find(node);
    if (_mapNodeScehdules.end() == iterMap)
        return NULL;
    
    if (iterMap->second.empty())
        return NULL;
    
    auto iterVec = iterMap->second.begin();
    for (; iterVec != iterMap->second.end(); iterVec++)
    {
        ScheduleHandlerDelegate* scheduleDelegate = *iterVec;
        if (NULL != scheduleDelegate && scheduleDelegate->isUpdateSchedule())
        {
            return scheduleDelegate;
        }
    }

    return NULL;
}

void ScriptHandlerMgr::unregisterNodeAllSchedule(cocos2d::Node* node)
{
    if ( NULL == node || _mapNodeScehdules.empty() )
        return;
    
    Scheduler* scheduler = node->getScheduler();
    if( NULL == scheduler)
        return ;

    
    auto iterMap = _mapNodeScehdules.find(node);
    if (_mapNodeScehdules.end() == iterMap)
        return;
    
    if (iterMap->second.empty())
        return;
    
    auto iterVec = iterMap->second.begin();
    for (; iterVec != iterMap->second.end(); iterVec++)
    {
        ScheduleHandlerDelegate* scheduleDelegate = *iterVec;
        if (NULL != scheduleDelegate)
        {
            if (scheduleDelegate->isUpdateSchedule())
            {
                scheduler->unscheduleUpdateForTarget(scheduleDelegate);
            }
            else
            {
                scheduler->unscheduleSelector(schedule_selector(ScheduleHandlerDelegate::scheduleFunc), (Object*)scheduleDelegate);
            }
        }
    }
    
    iterMap->second.clear();
    _mapNodeScehdules.erase(iterMap);
}

void ScriptHandlerMgr::addNodeSchedule(cocos2d::Node* node,ScheduleHandlerDelegate* schedule)
{
    if (NULL == node || NULL == schedule)
        return;
    
    auto iter = _mapNodeScehdules.find(node);
    VecShedule vecSchedule;
    vecSchedule.clear();
    if (_mapNodeScehdules.end() != iter)
    {
        vecSchedule = iter->second;
    }
    vecSchedule.push_back(schedule);
    _mapNodeScehdules[node] = vecSchedule;
}

void ScriptHandlerMgr::removeNodeSchedule(cocos2d::Node* node,ScheduleHandlerDelegate* schedule)
{
    if (NULL == node || NULL == schedule || _mapNodeScehdules.empty())
        return;
    
    auto iterMap = _mapNodeScehdules.find(node);
    if (_mapNodeScehdules.end() == iterMap)
        return;
    
    if (iterMap->second.empty())
        return;
    
    auto iterVec = iterMap->second.begin();
    bool exist  = false;
    for (; iterVec != iterMap->second.end(); iterVec++)
    {
        if ((*iterVec) == schedule)
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


static void tolua_reg_script_handler_mgr_type(lua_State* tolua_S)
{
    tolua_usertype(tolua_S, "ScheduleHandlerDelegate");
    tolua_usertype(tolua_S, "ScriptHandlerMgr");
}

static int tolua_collect_ScheduleHandlerDelegate(lua_State* tolua_S)
{
    ScheduleHandlerDelegate* self = (ScheduleHandlerDelegate*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

/* method: create of class ScheduleHandlerDelegate */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScheduleHandlerDelegate_create00
static int tolua_Cocos2d_ScheduleHandlerDelegate_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"ScheduleHandlerDelegate",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScheduleHandlerDelegate* tolua_ret = ScheduleHandlerDelegate::create();
        int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
        int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
        toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"ScheduleHandlerDelegate");
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

/* method: registerObjectHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerObjectHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_registerObjectHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        void* object = ((void*)  tolua_touserdata(tolua_S,2,0));
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
        int eventType = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerObjectHandler'", NULL);
#endif
        {
            self->registerObjectHandler(object,handler,eventType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerObjectHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterObjectHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_unregisterObjectHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterObjectHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        void* object = ((void*)  tolua_touserdata(tolua_S,2,0));
        int eventType = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterObjectHandler'", NULL);
#endif
        {
            self->unregisterObjectHandler(object,eventType);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterObjectHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerNotificationHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerNotificationHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_registerNotificationHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err)         ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isstring(tolua_S,4,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Object* target = (Object*)  tolua_tousertype(tolua_S,2,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
        const char* name = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerNotificationHandler'", NULL);
#endif
        {
            self->registerNotificationHandler(target,handler,name);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerNotificationHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterNotificationHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_unregisterNotificationHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterNotificationHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
        !tolua_isstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Object* target = (Object*)  tolua_tousertype(tolua_S,2,0);
        const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterNotificationHandler'", NULL);
#endif
        {
            self->unregisterNotificationHandler(target,name);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterNotificationHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCallFuncHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerCallFuncHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_registerCallFuncHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err)    ||
        !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCallFuncHandler'", NULL);
#endif
        {
            CallFuncN* tolua_ret = (CallFuncN*)  self->registerCallFuncHandler(handler);
            int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
            int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
            toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCCallFuncN");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerCallFuncHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerTouchesHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerTouchesHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_registerTouchesHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 4, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
        !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
        !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
        !tolua_isnoobj(tolua_S,8,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        void* object = ((void*)  tolua_touserdata(tolua_S,2,0));
        int objectType = ((int)  tolua_tonumber(tolua_S,3,0));
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,4,0));
        bool isMultiTouches = ((bool)  tolua_toboolean(tolua_S,5,false));
        int priority = ((int)  tolua_tonumber(tolua_S,6,INT_MIN));
        bool swallowsTouches = ((bool)  tolua_toboolean(tolua_S,7,false));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerTouchesHandler'", NULL);
#endif
        {
            self->registerTouchesHandler(object,objectType,handler,isMultiTouches,priority,swallowsTouches);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerTouchesHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerKeypadHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerKeypadHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_registerKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
        !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 4, "LUA_FUNCTION", 0, &tolua_err) ||
        !tolua_isnoobj(tolua_S,5,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        void* object = ((void*)  tolua_touserdata(tolua_S,2,0));
        int objectType = ((int)  tolua_tonumber(tolua_S,3,0));
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,4,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerKeypadHandler'", NULL);
#endif
        {
            self->registerKeypadHandler(object,objectType,handler);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerKeypadHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScheduleHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerScheduleHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_registerScheduleHandler00(lua_State* tolua_S)
{
    int argNums = lua_gettop(tolua_S);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (argNums < 2)
    {
        tolua_err.index = 0;
        tolua_err.array = 0;
        tolua_err.type = "argNums";
        goto tolua_lerror;
    }
    if (!tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        float interval = 0.0f;
        if (argNums >= 3)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,3,1,&tolua_err))
                goto tolua_lerror;
            else
#endif 
            {
                 interval = ((float)  tolua_tonumber(tolua_S,3,0.0f));
            }
        }
        unsigned int repeat = kRepeatForever;
        if (argNums >= 4)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,4,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                repeat = (unsigned int)tolua_tonumber(tolua_S,4,kRepeatForever);
            }
        }
        
        float delay = 0.0f;
        if (argNums >= 5)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,5,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                delay = ((float)  tolua_tonumber(tolua_S,5,0.0f));
            }
        }
        
        bool paused = false;
        if (argNums >= 6)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isboolean(tolua_S,6,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                paused = ((bool)  tolua_toboolean(tolua_S,6,false));
            }
        }
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScheduleHandler'", NULL);
#endif
        {
            ScheduleHandlerDelegate* tolua_ret = (ScheduleHandlerDelegate*)  self->registerScheduleHandler(handler,interval,repeat,delay,paused);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScheduleHandlerDelegate");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScheduleHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScheduleHandler of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_unregisterScheduleHandler00
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterScheduleHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"ScheduleHandlerDelegate",0,&tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        ScheduleHandlerDelegate* object = ((ScheduleHandlerDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScheduleHandler'", NULL);
#endif
        {
            self->unregisterScheduleHandler(object);
        }
        return 0;
    }
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScheduleHandler'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerNodeSchedule of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerNodeSchedule00
static int tolua_Cocos2d_ScriptHandlerMgr_registerNodeSchedule00(lua_State* tolua_S)
{
    int argNums = lua_gettop(tolua_S);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (argNums < 3)
    {
        tolua_err.index = 0;
        tolua_err.array = 0;
        tolua_err.type = "argNums";
        goto tolua_lerror;
    }
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        cocos2d::Node* node = ((cocos2d::Node*)  tolua_tousertype(tolua_S,2,0));
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
        
        float interval = 0.0f;
        if (argNums >= 4)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,4,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                interval = ((float)  tolua_tonumber(tolua_S,4,0.0f));
            }
        }
        unsigned int repeat = kRepeatForever;
        if (argNums >= 5)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,5,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                repeat = (unsigned int)tolua_tonumber(tolua_S,5,kRepeatForever);
            }
        }
        
        float delay = 0.0f;
        if (argNums >= 6)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,6,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                delay = ((float)  tolua_tonumber(tolua_S,6,0.0f));
            }
        }
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerNodeSchedule'", NULL);
#endif
        {
            ScheduleHandlerDelegate* tolua_ret = (ScheduleHandlerDelegate*)  self->registerNodeSchedule(node,handler,interval,repeat,delay);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScheduleHandlerDelegate");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerNodeSchedule'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterNodeSchedule of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeSchedule00
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"ScheduleHandlerDelegate",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Node* node = (Node*)  tolua_tousertype(tolua_S,2,0);
        ScheduleHandlerDelegate* scheduleDelegate = ((ScheduleHandlerDelegate*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterNodeSchedule'", NULL);
#endif
        {
            self->unregisterNodeSchedule(node,scheduleDelegate);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterNodeSchedule'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerNodeScheduleOnce of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerNodeScheduleOnce00
static int tolua_Cocos2d_ScriptHandlerMgr_registerNodeScheduleOnce00(lua_State* tolua_S)
{
    int argNums = lua_gettop(tolua_S);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Node* node = (Node*)  tolua_tousertype(tolua_S,2,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
        
        float delay = 0.0f;
        if (argNums >= 4)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,4,1,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                delay = ((float)  tolua_tonumber(tolua_S,4,0.0f));
            }
        }
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerNodeScheduleOnce'", NULL);
#endif
        {
            ScheduleHandlerDelegate* tolua_ret = (ScheduleHandlerDelegate*)  self->registerNodeScheduleOnce(node,handler,delay);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScheduleHandlerDelegate");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerNodeScheduleOnce'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerNodeScheduleUpdateWithPriority of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_registerNodeScheduleUpdateWithPriority00
static int tolua_Cocos2d_ScriptHandlerMgr_registerNodeScheduleUpdateWithPriority00(lua_State* tolua_S)
{
    int argNums = lua_gettop(tolua_S);
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err) )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Node* node = (Node*)  tolua_tousertype(tolua_S,2,0);
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
        
        int priority = 0;
        if (argNums >= 4)
        {
#ifndef TOLUA_RELEASE
            if(!tolua_isnumber(tolua_S,4,0,&tolua_err))
                goto tolua_lerror;
            else
#endif
            {
                priority = (int)tolua_tonumber(tolua_S,4,0);
            }
        }
        
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerNodeScheduleUpdateWithPriority'", NULL);
#endif
        {
            ScheduleHandlerDelegate* tolua_ret = (ScheduleHandlerDelegate*)  self->registerNodeScheduleUpdateWithPriority(node,handler,priority);
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScheduleHandlerDelegate");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerNodeScheduleUpdateWithPriority'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterNodeScheduleUpdateWithPriority of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeScheduleUpdateWithPriority00
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeScheduleUpdateWithPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,3,"ScheduleHandlerDelegate",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Node* node = (Node*)  tolua_tousertype(tolua_S,2,0);
        ScheduleHandlerDelegate* scheduleDelegate = ((ScheduleHandlerDelegate*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterNodeScheduleUpdateWithPriority'", NULL);
#endif
        {
            self->unregisterNodeScheduleUpdateWithPriority(node,scheduleDelegate);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterNodeScheduleUpdateWithPriority'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterNodeAllSchedule of class  ScriptHandlerMgr */
#ifndef TOLUA_DISABLE_tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeAllSchedule00
static int tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeAllSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"ScriptHandlerMgr",0,&tolua_err) ||
        !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        ScriptHandlerMgr* self = (ScriptHandlerMgr*)  tolua_tousertype(tolua_S,1,0);
        Node* node = (Node*)  tolua_tousertype(tolua_S,2,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterNodeAllSchedule'", NULL);
#endif
        {
            self->unregisterNodeAllSchedule(node);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterNodeAllSchedule'.",&tolua_err);
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
      tolua_cclass(tolua_S, "ScheduleHandlerDelegate", "ScheduleHandlerDelegate", "CCObject", tolua_collect_ScheduleHandlerDelegate);
      tolua_beginmodule(tolua_S, "ScheduleHandlerDelegate");
        tolua_function(tolua_S, "create", tolua_Cocos2d_ScheduleHandlerDelegate_create00);
      tolua_endmodule(tolua_S);
      tolua_cclass(tolua_S,"ScriptHandlerMgr","ScriptHandlerMgr","",NULL);
      tolua_beginmodule(tolua_S, "ScriptHandlerMgr");
        tolua_constant(tolua_S,"kNormalHandler",ScriptHandlerMgr::kNormalHandler);
        tolua_constant(tolua_S,"kScheduleHandler",ScriptHandlerMgr::kScheduleHandler);
        tolua_constant(tolua_S,"kNotificationHandler",ScriptHandlerMgr::kNotificationHandler);
        tolua_constant(tolua_S,"kCallFuncHandler",ScriptHandlerMgr::kCallFuncHandler);
        tolua_constant(tolua_S,"kTouchesHandler",ScriptHandlerMgr::kTouchesHandler);
        tolua_constant(tolua_S,"kKeypadHandler",ScriptHandlerMgr::kKeypadHandler);
        tolua_function(tolua_S,"getInstance",tolua_Cocos2d_ScriptHandlerMgr_getInstance00);
        tolua_function(tolua_S,"registerObjectHandler",tolua_Cocos2d_ScriptHandlerMgr_registerObjectHandler00);
        tolua_function(tolua_S,"unregisterObjectHandler",tolua_Cocos2d_ScriptHandlerMgr_unregisterObjectHandler00);
        tolua_function(tolua_S,"registerNotificationHandler",tolua_Cocos2d_ScriptHandlerMgr_registerNotificationHandler00);
        tolua_function(tolua_S,"unregisterNotificationHandler",tolua_Cocos2d_ScriptHandlerMgr_unregisterNotificationHandler00);
        tolua_function(tolua_S,"registerCallFuncHandler",tolua_Cocos2d_ScriptHandlerMgr_registerCallFuncHandler00);
        tolua_function(tolua_S,"registerTouchesHandler",tolua_Cocos2d_ScriptHandlerMgr_registerTouchesHandler00);
        tolua_function(tolua_S,"registerKeypadHandler",tolua_Cocos2d_ScriptHandlerMgr_registerKeypadHandler00);
        tolua_function(tolua_S,"registerScheduleHandler",tolua_Cocos2d_ScriptHandlerMgr_registerScheduleHandler00);
        tolua_function(tolua_S, "unregisterScheduleHandler", tolua_Cocos2d_ScriptHandlerMgr_unregisterScheduleHandler00);
        tolua_function(tolua_S, "registerNodeSchedule", tolua_Cocos2d_ScriptHandlerMgr_registerNodeSchedule00);
        tolua_function(tolua_S, "unregisterNodeSchedule", tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeSchedule00);
        tolua_function(tolua_S, "registerNodeScheduleOnce", tolua_Cocos2d_ScriptHandlerMgr_registerNodeScheduleOnce00);
        tolua_function(tolua_S, "registerNodeScheduleUpdateWithPriority", tolua_Cocos2d_ScriptHandlerMgr_registerNodeScheduleUpdateWithPriority00);
        tolua_function(tolua_S, "unregisterNodeScheduleUpdateWithPriority", tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeScheduleUpdateWithPriority00);
        tolua_function(tolua_S, "unregisterNodeAllSchedule", tolua_Cocos2d_ScriptHandlerMgr_unregisterNodeAllSchedule00);   
    
      tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
   return 1; 
}
