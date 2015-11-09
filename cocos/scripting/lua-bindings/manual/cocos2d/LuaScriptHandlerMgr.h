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

/**@~english
 * The LuaCallFunc is wrapped to call the callback function in the Lua conveniently and don't insert useless code to processing the Lua in the CallFuncN.
 *
 * @~chinese 
 * LuaCallFunc是为了在Lua中能方便地调用回调函数而进行的封装。通过封装，不需要在CallFuncN插入一些特殊代码来处理Lua。
 * 
 * @lua NA
 * @js NA
 */
class LuaCallFunc:public cocos2d::CallFuncN
{
public:
    /**@~english
     * Default constructor.
     * @~chinese 
     * 默认构造函数。
     */
    LuaCallFunc():_functionLua(nullptr)
    {}
    
    /**@~english
     * Destructor.
     * @~chinese 
     * 析构函数。
     */
    virtual ~LuaCallFunc()
    {}
    
    /**@~english
     * Create a LuaCallFunc object by a function pointer for callback.
     *
     * @~chinese 
     * 通过一个指向回调函数的函数指针创建一个LuaCallFunc对象。
     * 
     * @param func @~english a function pointer for callback.
     * @~chinese 回调函数的函数指针。
     */
    static LuaCallFunc* create(const std::function<void(void* self,Node*)>& func);
    
    /**@~english
     * Init a LuaCallFunc object by a function pointer for callback.
     *
     * @~chinese 
     * 使用一个回调函数的函数指针来初始化LuaCallFunc对象。
     * 
     * @param func @~english a function pointer for callback.
     * @~chinese 回调函数的函数指针。
     */
    bool initWithFunction(const std::function<void(void* self,Node*)>& func);
    virtual LuaCallFunc* clone() const override;
    virtual void execute() override;
protected:
    std::function<void(void* self,Node*)> _functionLua;
    
};

/**@~english
 * In order to reduce the coupling of lua script engine and native c++ engine.
 * In the current mechanism, for the class derived frome the Ref, we constuct a mapping relationship among c++ Ref object ,HandlerType and the reference id corresponding to the pointer of Lua function.Then, using the ScriptHandlerMgr to manager uniformly.
 * By this mechanism,when native c++ Ref object wants to call the Lua function, we didn't insert the processing code in the native c++ class.
 * @~chinese 
 * 为了减少lua脚本引擎和c++引擎的耦合。
 * 在当前的机制,对于Ref派生类,我们会构建一个Ref对象，HandlerType以及指向Lua函数指针的引用id的映射关系表。然后,使用ScriptHandlerMgr进行统一管理。
 * 通过这种机制,当c++ Ref对象想调用Lua函数时,我们无需在原生c++类中插入处理脚本的代码。
 */
class ScriptHandlerMgr
{
public:
    
    /**@~english
     * HandlerType enum.
     * This enum class represent the processing event type for c++ calling the Lua function.
     *
     * @~chinese 
     * HandlerType枚举。
     * 这个枚举类表示c++回调处理Lua函数的事件类型。
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
    
    /**@~english
     * Default constructor.
     *
     * @~chinese 
     * 默认构造函数。
     * 
     * @lua NA
     * @js NA
     */
    ScriptHandlerMgr(void);
    
    /**@~english
     * Destructor.
     *
     * @~chinese 
     * 析构函数。
     * 
     * @lua NA
     * @js NA
     */
    virtual ~ScriptHandlerMgr(void);
    
    /**@~english
     * Get the instance of the ScriptHandlerMgr.
     *
     * @~chinese 
     * 获取ScriptHandlerMgr的实例对象。
     * 
     * @return @~english the instance of the ScriptHandlerMgr.
     * @~chinese ScriptHandlerMgr的实例对象。
     * @js NA
     */
    static ScriptHandlerMgr* getInstance(void);
    
    /**@~english
     * Destroy the instance of the ScriptHandlerMgr.
     *
     * @~chinese 
     * 消毁ScriptHandlerMgr的实例对象。
     * 
     * @lua NA
     * @js NA
     */
    static void destroyInstance(void);
    
    /**@~english
     * Construct or update the mapping relationship among c++ Ref object ,HandlerType and the reference id corresponding to the pointer of Lua function.
     *
     * @~chinese 
     * 构建或更新c++ Ref对象,HandlerType以及对应Lua函数的指针引用id的映射关系。
     * 
     * @param object @~english a Ref object.
     * @~chinese Ref对象。
     * @param handler @~english a reference id corresponding to the pointer of Lua function.
     * @~chinese 对应Lua函数指针的引用id。
     * @param handlerType @~english ScriptHandlerMgr::HandlerType.
     * @~chinese ScriptHandlerMgr::HandlerType。
     * @lua registerScriptHandler
     * @js NA
     */
    void addObjectHandler(void* object,int handler,ScriptHandlerMgr::HandlerType handlerType);
    
    /**@~english
     * By the handlerType and Ref object, find the correct reference id corresponding to the pointer of Lua function.
     * If found, remove the reference of Lua function corresponding to this id in the 'toluafix_refid_function_mapping' table.
     * 
     * @~chinese 
     * 通过handlerType和Ref对象，查找对于Lua函数指针的引用id。
     * 如果找到,则移除Lua函数toluafix_refid_function_mapping table中对应id的Lua函数的引用。
     * 
     * @param object @~english a Ref object.
     * @~chinese 一个Ref对象。
     * @param handlerType @~english ScriptHandlerMgr::HandlerType.
     * @~chinese ScriptHandlerMgr::HandlerType。
     * @lua unregisterScriptHandler
     * @js NA
     */
    void removeObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    
    /**@~english
     * By the handlerType and object, find the correct reference id corresponding to the pointer of Lua function.
     *
     * @~chinese 
     * 根据handlerType和Ref对象,找到对应Lua函数指针的引用id。
     * 
     * @param object @~english a Ref object.
     * @~chinese 一个Ref对象。
     * @param handlerType @~english ScriptHandlerMgr::HandlerType.
     * @~chinese ScriptHandlerMgr::HandlerType。
     * @return @~english reference id corresponding to the pointer of Lua function,otherwise 0.
     * @~chinese Lua函数指针的引用id或者0。
     * @lua NA
     * @js NA
     */
    int  getObjectHandler(void* object,ScriptHandlerMgr::HandlerType handlerType);
    
    /**@~english
     * Remove the all relationship among the object, HandlerType and the reference id corresponding to the pointer of Lua function.
     * Meanwhile, remove the reference of Lua function corresponding to the id the object has in the 'toluafix_refid_function_mapping' table.
     *
     * @~chinese 
     * 移除所有和object，HandlerType以及引用id相关的映射关系。
     * 同时,根据引用id, 移除`toluafix_refid_function_mapping`中Lua函数指针的引用。
     * 
     * @param object @~english the Ref object.
     * @~chinese 一个Ref对象
     * @js NA
     */
    void removeObjectAllHandlers(void* object);
    
    /**@~english
     * Add customizable relationship among c++ Ref object, HandlerType and the reference id corresponding to the pointer of Lua function.
     * In the customizable relationship, we don't pass the HandlerType, it will obtain the HandlerType by auto-increasing.
     * The HandlerTypes used to customizable relationship are between EVENT_CUSTOM_BEGAN(10000) and EVENT_CUSTOM_ENDED(11000).
     * If the HandlerType increased more than EVENT_CUSTOM_ENDED(110000),it would trigger assert.
     *
     * @~chinese
     * 添加自定义的c++ Ref对象,HandlerType和对应Lua函数指针的引用id的映射关系。
     * 在这种自定义映射关系中,我们不需传递HandlerType参数, 这个函数内部会通过自增加的方法儿取HandlerType。
     * 用于自定义映射关系的HandlerTypes的取值范围在EVENT_CUSTOM_BEGAN(10000)和EVENT_CUSTOM_ENDED(11000)之间。
     * 如果HandlerType增加超过EVENT_CUSTOM_ENDED(110000),它将触发断言。
     * 
     * @param object @~english the Ref object.
     * @~chinese Ref对象。
     * @param handler @~english a reference index corresponding to the pointer of Lua function.
     * @~chinese Lua函数指针的引用id。
     * @return @~english ScriptHandlerMgr::HandlerType the ScriptHandlerMgr::HandlerType value after adding.
     * @~chinese 添加自定义映射关系后的ScriptHandlerMgr::HandlerType值。
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
