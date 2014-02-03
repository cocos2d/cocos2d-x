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
    LuaCallFunc():_functionLua(nullptr)
    {}
    virtual ~LuaCallFunc()
    {}
    
    static LuaCallFunc* create(const std::function<void(void* self,Node*)>& func);
    bool initWithFunction(const std::function<void(void* self,Node*)>& func);
    virtual LuaCallFunc* clone() const;
    virtual void execute() override;
protected:
    /**
     */
    std::function<void(void* self,Node*)> _functionLua;
    
};

class ScriptHandlerMgr
{
public:
    enum class HandlerType: int
    {
        NODE = 0,
        MENU_CLICKED,
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
        
        STUDIO_EVENT_LISTENER,
        ARMATURE_EVENT,
        
        EVENT_ACC,
        EVENT_CUSTIOM,
        
        EVENT_KEYBOARD_PRESSED,
        EVENT_KEYBOARD_RELEASED,
        
        EVENT_TOUCH_BEGAN,
        EVENT_TOUCH_MOVED,
        EVENT_TOUCH_ENDED,
        EVENT_TOUCH_CANCELLED,
        
        EVENT_TOUCHES_BEGAN,
        EVENT_TOUCHES_MOVED,
        EVENT_TOUCHES_ENDED,
        EVENT_TOUCHES_CANCELLED,
        
        EVENT_MOUSE_DOWN,
        EVENT_MOUSE_UP,
        EVENT_MOUSE_MOVE,
        EVENT_MOUSE_SCROLL,
        
        EVENT_SPINE,
        
        EVENT_PHYSICS_CONTACT_BEGIN,
        EVENT_PHYSICS_CONTACT_PRESOLVE,
        EVENT_PHYSICS_CONTACT_POSTSOLVE,
        EVENT_PHYSICS_CONTACT_SEPERATE,
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

TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
