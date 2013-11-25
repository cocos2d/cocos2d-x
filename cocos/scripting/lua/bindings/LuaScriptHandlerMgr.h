#ifndef __LUA_SCRIPT_HANDLER_MGR_H__
#define __LUA_SCRIPT_HANDLER_MGR_H__


extern "C" {
#include "tolua++.h"
}


#include "CCObject.h"
#include "ccMacros.h"
#include "CCActionInstant.h"
#include <vector>
#include <map>

NS_CC_BEGIN

class ScheduleHandlerDelegate;


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
    enum class HandlerType: int
    {
        NODE = 0,
        MENU_CLICKED,
        NOTIFICATION,
        CALLFUNC,
        SCHEDULE,
        TOUCHES,
        KEYPAD,
        ACCELEROMETER,
        
        CONTROL_TOUCH_DOWN,
        CONTROL_TOUCH_DRAG_INSIDE,
        CONTROL_TOUCH_DRAG_OUTSIDE,
        CONTROL_TOUCH_DRAG_ENTER,
        CONTROL_TOUCH_DRAG_EXIT,
        CONTROL_TOUCH_UP_INSIDE,
        CONTROL_TOUCH_UP_OUTSIDE,
        CONTROL_TOUCH_UP_CANCEL,
        CONTROL_VALUE_CHANGED,
        
        WEBSOCKET_OPEN,
        WEBSOCKET_MESSAGE,
        WEBSOCKET_CLOSE,
        WEBSOCKET_ERROR,
        
        GL_NODE_DRAW,
        
        SCROLLVIEW_SCROLL,
        SCROLLVIEW_ZOOM,
        
        TABLECELL_TOUCHED,
        TABLECELL_HIGHLIGHT,
        TABLECELL_UNHIGHLIGHT,
        TABLECELL_WILL_RECYCLE,
        TABLECELL_SIZE_FOR_INDEX,
        TABLECELL_AT_INDEX,
        TABLEVIEW_NUMS_OF_CELLS,
        
        XMLHTTPREQUEST_READY_STATE_CHANGE,
        
        ASSETSMANAGER_PROGRESS,
        ASSETSMANAGER_SUCCESS,
        ASSETSMANAGER_ERROR,
        
        EVENT_LISTENER,
        ARMATURE_EVENT,
    };
    
    typedef int Handler;
    typedef std::pair<HandlerType, Handler> HandlerPair;
    typedef std::vector<HandlerPair> VecHandlerPairs;
    typedef std::map<void*,VecHandlerPairs> MapObjectHandlers;
    
    ScriptHandlerMgr(void);
    virtual ~ScriptHandlerMgr(void);
    static ScriptHandlerMgr* getInstance(void);
        
    void addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType);
    void removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    int  getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    void removeObjectAllHandlers(void* object);
    
private:
    void init(void);
    static ScriptHandlerMgr* _scriptHandlerMgr;
    MapObjectHandlers _mapObjectHandlers;
};

NS_CC_END

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
TOLUA_API int tolua_Cocos2d_WebSocket_registerScriptHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_WebSocket_unregisterScriptHandler00(lua_State* tolua_S);
#endif

TOLUA_API int tolua_Cocos2d_GLNode_registerScriptDrawHandler00(lua_State* tolua_S);
TOLUA_API int tolua_Cocos2d_GLNode_unregisterScriptDrawHandler00(lua_State* tolua_S);

TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
