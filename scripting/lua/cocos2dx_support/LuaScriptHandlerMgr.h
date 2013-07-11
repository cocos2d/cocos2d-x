#ifndef __LUA_SCRIPT_HANDLER_MGR_H__
#define __LUA_SCRIPT_HANDLER_MGR_H__


extern "C" {
#include "tolua++.h"
}


#include "cocoa/CCObject.h"
#include "ccMacros.h"
#include "actions/CCActionInstant.h"
#include <vector>
#include <map>

NS_CC_BEGIN

class ScheduleHandlerDelegate;

typedef int EventType;
typedef int EventHandler;
typedef std::pair<EventType, EventHandler> PairEventHandler;
typedef std::vector<PairEventHandler> VecEventHandlers;
typedef std::map<void*,VecEventHandlers> MapObjectHandlers;
typedef std::vector<ScheduleHandlerDelegate*> VecShedule;
typedef std::map<cocos2d::Node*,VecShedule> MapNodeSchedules;

class ScheduleHandlerDelegate:public cocos2d::Object
{
public:
    ScheduleHandlerDelegate():_isUpdateSchedule(false)
    {}
    virtual ~ScheduleHandlerDelegate()
    {}
    
    static ScheduleHandlerDelegate* create();
    
    void scheduleFunc(float elapse);
    
    virtual void update(float elapse);
    
    void setUpdateSchedule(bool isUpdateSchedule){ _isUpdateSchedule = isUpdateSchedule; }
    bool isUpdateSchedule(){ return _isUpdateSchedule; }
private:
    bool _isUpdateSchedule;
};

class CallFuncHandlerDelegate:public cocos2d::Object
{
public:
    CallFuncHandlerDelegate():_callFunc(NULL)
    {}
    virtual ~CallFuncHandlerDelegate()
    {}
    
    static CallFuncHandlerDelegate* create();
    
    void callFunc(cocos2d::Node* node);
    
    void setCallFunc(cocos2d::CallFuncN* callFunc){ _callFunc = callFunc ;}
    cocos2d::CallFuncN* getCallFunc(){ return _callFunc ;}
private:
    cocos2d::CallFuncN* _callFunc;
};

class ScriptHandlerMgr
{
public:
    ScriptHandlerMgr(void);
    virtual ~ScriptHandlerMgr(void);
    static ScriptHandlerMgr* getInstance(void);
    
    void registerObjectHandler(void* object,int handler,int eventType);
    void unregisterObjectHandler(void* object,int eventType);
    int  getObjecHandlerByEvent(void* object,int eventType);
    void unregisterObjectAllHandlers(void* object);
        
    cocos2d::CallFuncN* registerCallFuncHandler(int handler);
    void registerTouchesHandler(void* object,int objectType,int handler,bool isMultiTouches = false,int priority = 0,bool swallowsTouches = false);
    void registerKeypadHandler(void* object,int objectType,int handler);
    
    ScheduleHandlerDelegate* registerScheduleHandler(int handler,float interval = 0.0f, unsigned int repeat = kRepeatForever, float delay = 0.0f, bool paused = false);
    void unregisterScheduleHandler(ScheduleHandlerDelegate* scheduleDelegate);
    
    ScheduleHandlerDelegate* registerNodeSchedule(cocos2d::Node* node,int handler,float interval = 0.0f,unsigned int repeat = kRepeatForever,float delay = 0.0f);
    
    void unregisterNodeSchedule(cocos2d::Node* node,ScheduleHandlerDelegate* scheduleDelegate);
    
    ScheduleHandlerDelegate* registerNodeScheduleOnce(cocos2d::Node* node,int handler,float delay = 0.0f);
    
    ScheduleHandlerDelegate* registerNodeScheduleUpdateWithPriority(cocos2d::Node* node,int handler,int priority);
    void unregisterNodeScheduleUpdateWithPriority(cocos2d::Node* node,ScheduleHandlerDelegate* scheduleDelegate = NULL);
    //one node only have one scheduleUpdate func
    ScheduleHandlerDelegate* getNodeScheduleUpdateWithPriority(cocos2d::Node* node);
    
    void unregisterNodeAllSchedule(cocos2d::Node* node);
    
    enum HandlerEventType
    {
       kNormalHandler = 0,
       kScheduleHandler,
       kNotificationHandler,
       kCallFuncHandler,
       kTouchesHandler,
       kKeypadHandler,
    };
    
    
private:
    void init(void);
    void addNodeSchedule(cocos2d::Node* node,ScheduleHandlerDelegate* schedule);
    void removeNodeSchedule(cocos2d::Node* node,ScheduleHandlerDelegate* schedule);
    static ScriptHandlerMgr* _scriptHandlerMgr;
    MapObjectHandlers _mapObjectHandlers;
    MapNodeSchedules   _mapNodeScehdules;
};

NS_CC_END

TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
