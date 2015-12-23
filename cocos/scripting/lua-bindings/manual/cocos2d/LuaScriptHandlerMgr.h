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


#include "base/CCRef.h"
#include "base/ccMacros.h"
#include "2d/CCActionInstant.h"
#include <vector>
#include <map>

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

class ScheduleHandlerDelegate;

/// @cond
typedef std::vector<ScheduleHandlerDelegate*> VecShedule;
typedef std::map<cocos2d::Node*,VecShedule> MapNodeSchedules;

class ScheduleHandlerDelegate:public cocos2d::Ref
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
/// @endcond

/**
 * The LuaCallFunc is wrapped to call the callback function in the Lua Conveniently and don't insert useless code to processing the lua in the CallFuncN.
 *
 * @lua NA
 * @js NA
 */
class LuaCallFunc:public cocos2d::CallFuncN
{
public:
    /**
     * Default constructor.
     */
    LuaCallFunc():_functionLua(nullptr)
    {}
    
    /**
     *  Destructor.
     */
    virtual ~LuaCallFunc()
    {}
    
    /**
     * Create a LuaCallFunc object by a function pointer for callback.
     *
     * @param func a function pointer for callback.
     */
    static LuaCallFunc* create(const std::function<void(void* self,Node*)>& func);
    
    /**
     * Init a LuaCallFunc object by a function pointer for callback.
     *
     * @param func a function pointer for callback.
     */
    bool initWithFunction(const std::function<void(void* self,Node*)>& func);
    virtual LuaCallFunc* clone() const override;
    virtual void execute() override;
protected:
    std::function<void(void* self,Node*)> _functionLua;
    
};

/**
 * In order to reduce the coupling of lua script engine and native c++ engine.
 * In the current mechanism, for the class derived from the Ref, we construct a mapping relationship among c++ Ref object, HandlerType and the reference index corresponding to the pointer of Lua function. Then, using the ScriptHandlerMgr to manager uniformly.
 * By this mechanism, when native c++ Ref object wants to call the Lua function, we didn't insert the processing code in the native c++ class.
 */
class ScriptHandlerMgr
{
public:
    
    /**
     * HandlerType enum.
     * This enum class represent the processing type for c++ call the Lua function.
     *
     * @js NA
     */
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
        EVENT_PHYSICS_CONTACT_SEPARATE,
        
        EVENT_FOCUS,
        
        EVENT_CONTROLLER_CONNECTED,
        EVENT_CONTROLLER_DISCONNECTED,
        EVENT_CONTROLLER_KEYDOWN,
        EVENT_CONTROLLER_KEYUP,
        EVENT_CONTROLLER_KEYREPEAT,
        EVENT_CONTROLLER_AXIS,
        
        EVENT_SPINE_ANIMATION_START,
        EVENT_SPINE_ANIMATION_END,
        EVENT_SPINE_ANIMATION_COMPLETE,
        EVENT_SPINE_ANIMATION_EVENT,
        
        EVENT_CUSTOM_BEGAN = 10000,
        EVENT_CUSTOM_ENDED = 11000,
    };
    
    ///! @cond
    typedef int Handler;
    typedef std::pair<HandlerType, Handler> HandlerPair;
    typedef std::vector<HandlerPair> VecHandlerPairs;
    typedef std::map<void*,VecHandlerPairs> MapObjectHandlers;
    /// @endcond
    
    /**
     * Default constructor.
     *
     * @lua NA
     * @js NA
     */
    ScriptHandlerMgr(void);
    
    /**
     * Destructor.
     *
     * @lua NA
     * @js NA
     */
    virtual ~ScriptHandlerMgr(void);
    
    /**
     * Get the instance of the ScriptHandlerMgr.
     *
     * @return the instance of the ScriptHandlerMgr.
     * @js NA
     */
    static ScriptHandlerMgr* getInstance(void);
    
    /**
     * Destroy the instance of the ScriptHandlerMgr.
     *
     * @lua NA
     * @js NA
     */
    static void destroyInstance(void);
    
    /**
     * Construct or update the mapping relationship among c++ Ref object ,HandlerType and the reference index corresponding to the pointer of Lua function.
     *
     * @param object a Ref object.
     * @param handler a reference index corresponding to the pointer of Lua function.
     * @param handlerType ScriptHandlerMgr::HandlerType.
     * @lua registerScriptHandler
     * @js NA
     */
    void addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType);
    
    /**
     * By the handlerType and object, find the correct reference index corresponding to the pointer of Lua function.
     * If found, remove the reference of Lua function corresponding to this index in the 'toluafix_refid_function_mapping' table.
     * 
     * @param object a Ref object.
     * @param handlerType ScriptHandlerMgr::HandlerType.
     * @lua unregisterScriptHandler
     * @js NA
     */
    void removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    
    /**
     * By the handlerType and object, find the correct reference index corresponding to the pointer of Lua function.
     *
     * @param object a Ref object.
     * @param handlerType ScriptHandlerMgr::HandlerType.
     * @return index corresponding to the pointer of Lua function,otherwise 0.
     * @lua NA
     * @js NA
     */
    int  getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    
    /**
     * Remove the all relationship among the object, HandlerType and the reference index corresponding to the pointer of Lua function.
     * Meanwhile, remove the reference of Lua function corresponding to the indexs the object has in the 'toluafix_refid_function_mapping' table.
     *
     * @param object the Ref object.
     * @js NA
     */
    void removeObjectAllHandlers(void* object);
    
    /**
     * Add customizable relationship among c++ Ref object, HandlerType and the reference index corresponding to the pointer of Lua function.
     * In the customizable relationship, we don't pass the HandlerType, it will obtain the HandlerType by auto-increasing.
     * The HandlerTypes used to customizable relationship are between EVENT_CUSTOM_BEGAN(10000) and EVENT_CUSTOM_ENDED(11000).
     * If the HandlerType increased more than 12,it would trigger assert.
     *
     * @param object the Ref object.
     * @param handler a reference index corresponding to the pointer of Lua function.
     * @return ScriptHandlerMgr::HandlerType the value of current ScriptHandlerMgr::HandlerType after adding.
     * @lua NA
     * @js NA
     */
    ScriptHandlerMgr::HandlerType addCustomHandler(void* object, int handler);
    
private:
    void init(void);
    static ScriptHandlerMgr* _scriptHandlerMgr;
    MapObjectHandlers _mapObjectHandlers;
};

NS_CC_END

// end group
/// @}

/// @cond
TOLUA_API int tolua_script_handler_mgr_open(lua_State* tolua_S);
/// @endcond

#endif //__LUA_SCRIPT_HANDLER_MGR_H__
