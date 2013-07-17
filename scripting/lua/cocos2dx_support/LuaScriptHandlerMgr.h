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

class LuaCallFunc:public cocos2d::CallFuncN
{
public:
    LuaCallFunc()
    {}
    virtual ~LuaCallFunc()
    {}
    
    static LuaCallFunc * create(int nHandler);
    virtual void execute();
    virtual LuaCallFunc* clone() const;
};

class ScriptHandlerMgr
{
public:
    ScriptHandlerMgr(void);
    virtual ~ScriptHandlerMgr(void);
    static ScriptHandlerMgr* getInstance(void);
        
    void addObjectHandler(void* object,int handler,int eventType);
    void removeObjectHandler(void* object,int eventType);
    int  getObjectHandler(void* object,int eventType);
    void removeObjectAllHandlers(void* object);
            
    enum HandlerEventType
    {
       kNodeHandler = 0,
       kMenuClickHandler,
       kNotificationHandler,
       kCallFuncHandler,
       kScheduleHandler,
       kTouchesHandler,
       kKeypadHandler,
       kAccelerometerHandler,
       
       kControlTouchDownHandler,
       kControlTouchDragInsideHandler,
       kControlTouchDragOutsideHandler,
       kControlTouchDragEnterHandler,
       kControlTouchDragExitHandler,
       kControlTouchUpInsideHandler,
       kControlTouchUpOutsideHandler,
       kControlTouchCancelHandler,
       kControlValueChangedHandler,
       
       kWebSocketScriptHandlerOpen,
       kWebSocketScriptHandlerMessage,
       kWebSocketScriptHandlerClose,
       kWebSocketScriptHandlerError,
        
       kGLNodeDrawHandler,
        
       kScrollViewScrollHandler,
       kScrollViewZoomHandler,
    };
    
    
private:
    void init(void);
    static ScriptHandlerMgr* _scriptHandlerMgr;
    MapObjectHandlers _mapObjectHandlers;
};

NS_CC_END

TOLUA_API int tolua_Cocos2d_registerScriptHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_unregisterScriptHandler00(lua_State* tolua_S);

TOLUA_API int tolua_Cocos2d_registerScriptTapHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_unregisterScriptTapHandler00(lua_State* tolua_S);

TOLUA_API int tolua_Cocos2d_registerScriptTouchHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_unregisterScriptTouchHandler00(lua_State* tolua_S);

TOLUA_API int tolua_Cocos2d_registerScriptKeypadHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_unregisterScriptKeypadHandler00(lua_State* tolua_S);

TOLUA_API int tolua_Cocos2d_registerScriptAccelerateHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_unregisterScriptAccelerateHandler00(lua_State* tolua_S);

TOLUA_API int tolua_Cocos2d_registerControlEventHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_unregisterControlEventHandler00(lua_State* tolua_S);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
TOLUA_API int tolua_Cocos2d_WebSocket_registerScriptHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_WebSocket_unregisterScriptHandler00(lua_State* tolua_S);
#endif

TOLUA_API int tolua_Cocos2d_GLNode_registerScriptDrawHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00(lua_State* tolua_S);

TOLUA_API int tolua_Cocos2d_ScrollView_registerScriptHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_ScrollView_unregisterScriptHandler00(lua_State* tolua_S);

TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
