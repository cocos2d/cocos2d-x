/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
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

#ifndef __SCRIPT_SUPPORT_H__
#define __SCRIPT_SUPPORT_H__

#include "base/ccConfig.h"
#include "platform/CCCommon.h"
#include "base/CCTouch.h"
#include "base/CCEventTouch.h"
#include "base/CCEventKeyboard.h"
#include <map>
#include <string>
#include <list>

/**
 * @addtogroup base
 * @{
 */

#if CC_ENABLE_SCRIPT_BINDING

typedef struct lua_State lua_State;

NS_CC_BEGIN

class TimerScriptHandler;
class Layer;
class MenuItem;
class CallFunc;
class Acceleration;
class Action;

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

/**@~english
 * This classes is wrapped to store the handler corresponding to the Lua function pointer and assign the handler a unique id
 * @~chinese 
 * 这个类用于封装Lua函数指针对应的handler，每一个handler对应一个唯一id.
 * @lua NA
 * @js NA
 */
class ScriptHandlerEntry : public Ref
{
public:
    
    /**@~english
     * create a ScriptHandlerEntry instance by the handler.
     *
     * @~chinese 
     * 创根据handler创建一个ScriptHandlerEntry实例。
     * 
     * @param handler @~english corresponding to the Lua function pointer.
     * @~chinese Lua函数的引用id。
     * @return @~english ScriptHandlerEntry instance.
     * @~chinese ScriptHandlerEntry实例。
     * @js NA
     */
    static ScriptHandlerEntry* create(int handler);
    
    /**@~english
     * Destructor of ScriptHandlerEntry.
     * @~chinese 
     * ScriptHandlerEntry的析构函数。
     * @js NA
     */
    virtual ~ScriptHandlerEntry();
    
    /**@~english
     * Get the handler corresponding to the Lua function pointer.
     *
     * @~chinese 
     * 获取对应Lua函数的handler。
     * 
     * @return @~english the handler corresponding to the Lua function pointer.
     * @~chinese 对应Lua函数的handler。
     * @js NA
     */
    int getHandler(void) {
        return _handler;
    }
    
    /**@~english
     * Get the unique id corresponding to the handler.
     *
     * @~chinese 
     * 获取对应handler的唯一ID。
     * 
     * @return @~english the unique id corresponding to the handler.
     * @~chinese handler的唯一id。
     * @js NA
     */
    int getEntryId(void) {
        return _entryId;
    }
    
protected:
    ScriptHandlerEntry(int handler)
    : _handler(handler)
    {
        static int newEntryId = 0;
        newEntryId++;
        _entryId = newEntryId;
    }
    
    int _handler;
    int _entryId;
};

/**@~english
 * The SchedulerScriptHandlerEntry is used to store the handler corresponding to the Lua function pointer and assign the handler a unique id like ScriptHandlerEntry.
 * Meanwhile,create a timer that named TimerScriptHandler to execute the Lua function corresponding to the handler in the interval time if the SchedulerScriptHandlerEntry object isn't paused.
 * @~chinese 
 * SchedulerScriptHandlerEntry和ScriptHandlerEntry类似，将对应Lua函数的handler进行封装并且给这个handler分配一个唯一id.同时，它会创建一个TimerScriptHandler类型的定时器，如果SchedulerScriptHandlerEntry对象没有暂停，它将会按一定的间隔时间执行handler对应的Lua函数。
 * @lua NA
 * @js NA
 */
class SchedulerScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    /**@~english
     * create a SchedulerScriptHandlerEntry object.
     * 
     * @~chinese 
     * 创建一个SchedulerScriptHandlerEntry对象。
     * 
     * @param handler @~english the index corresponding to the Lua function pointer.
     * @~chinese 对应Lua函数的引用id。
     * @param interval @~english the interval to execute the Lua function. If the value is 0, then the lua function will be scheduled every frame.
     * @~chinese 执行Lua函数的时间间隔。如果值为0，那么Lua函数每帧会执行一次。
     * @param paused @~english if paused is true, then the timer won't be started until it is resumed.
     * @~chinese 如果paused值为true,那么定时器只有被恢复后才能开始运行。
     * @return @~english a SchedulerScriptHandlerEntry object.
     * @~chinese SchedulerScriptHandlerEntry对象。
     */
    static SchedulerScriptHandlerEntry* create(int handler, float interval, bool paused);
    
    /**@~english
     * Destructor of SchedulerScriptHandlerEntry.
     * @~chinese 
     * SchedulerScriptHandlerEntry的析构函数。
     */
    virtual ~SchedulerScriptHandlerEntry();
    
    /**@~english
     * Get the pointer of TimerScriptHandler object.
     *
     * @~chinese 
     * 获取TimerScriptHandler对象的指针。
     * 
     * @return @~english the pointer of TimerScriptHandler object.
     * @~chinese TimerScriptHandler对象指针。
     */
    TimerScriptHandler* getTimer(void) {
        return _timer;
    }
    
    /**@~english
     * Get the flag whether paused or not.
     *
     * @~chinese 
     * 获取是否paused的标记。
     * 
     * @return @~english the flag whether paused or not.
     * @~chinese 是否paused的标记。
     */
    bool isPaused(void) {
        return _paused;
    }
    /**@~english
     * Set the markedForDeletion flag true.
     * @~chinese 
     * 设置markedForDeletion标记为true。
     */
    void markedForDeletion(void) {
        _markedForDeletion = true;
    }
    /**@~english
     * Get the flag whether markedForDeletion or not.
     *
     * @~chinese 
     * 获取markedForDeletion标记。
     * 
     * @return @~english the flag whether markedForDeletion or not.
     * @~chinese markedForDeletion的标记。
     */
    bool isMarkedForDeletion(void) {
        return _markedForDeletion;
    }
    
private:
    SchedulerScriptHandlerEntry(int handler)
    : ScriptHandlerEntry(handler)
    , _timer(nullptr)
    , _paused(false)
    , _markedForDeletion(false)
    {
    }
    bool init(float interval, bool paused);
    
    TimerScriptHandler*   _timer;
    bool                _paused;
    bool                _markedForDeletion;
};


/**
 * @cond
 * @js NA
 */
class TouchScriptHandlerEntry : public ScriptHandlerEntry
{
public:

    static TouchScriptHandlerEntry* create(int handler, bool isMultiTouches, int priority, bool swallowsTouches);

    virtual ~TouchScriptHandlerEntry();

    bool isMultiTouches(void) {
        return _isMultiTouches;
    }

    int getPriority(void) {
        return _priority;
    }

    bool getSwallowsTouches(void) {
        return _swallowsTouches;
    }
    
private:
    TouchScriptHandlerEntry(int handler)
    : ScriptHandlerEntry(handler)
    , _isMultiTouches(false)
    , _priority(0)
    , _swallowsTouches(false)
    {
    }
    bool init(bool isMultiTouches, int priority, bool swallowsTouches);
    
    bool    _isMultiTouches;
    int     _priority;
    bool    _swallowsTouches;
};

/**
 * @endcond
 * @js NA
 */

/** @~english ScriptEventType enum @~chinese ScriptEventType枚举*/
enum ScriptEventType
{
    kNodeEvent = 0,
    kMenuClickedEvent,
    kCallFuncEvent,
    kScheduleEvent,
    kTouchEvent,
    kTouchesEvent,
    kKeypadEvent,
    kAccelerometerEvent,
    kControlEvent,
    kCommonEvent,
    kComponentEvent,
    kRestartGame,
    kScriptActionEvent
};

/**@~english
 * For Lua, Wrapper the script data that should be used to find the handler corresponding to the Lua function by the nativeobject pointer and store the value pointer which would be converted concretely by the different events,then the converted data would be passed into the Lua stack.
 * @~chinese 
 * 对于Lua,这是一个基础数据封装类。其中,nativeObject用于查找对于Lua函数的handler，value的值根据不同的事件类型转换成具体类型的数据，并且转换后的数据将会压入到Lua堆栈，做为Lua函数中的传入参数。
 * @js NA
 * @lua NA
 */
struct BasicScriptData
{
    /** @~english
     * For Lua, nativeobject is used to get handler corresponding to the Lua function.
     *
     * @~chinese 
     * 对于Lua, nativeobject用于获取对于Lua函数的handler。
     * 
     */
    void* nativeObject;
    
    /**@~english
     * A pointer point to the value data which would be converted by different events.
     *
     * @~chinese 
     * 一个需要根据不同事件进行具体转换的数据指针。
     */
    void* value;
    
    /**@~english
     * Constructor of BasicScriptData.
     *
     * @~chinese 
     * BasicScriptData的构造函数。
     */
    BasicScriptData(void* inObject,void* inValue = nullptr)
    : nativeObject(inObject),value(inValue)
    {
    }
};

/**@~english
 * For Lua, Wrapper the script data that should be used to find the handler corresponding to the Lua function by the nativeobject pointer and store the value pointer which would be converted concretely by the different events,then the converted data would be passed into the Lua stack.
 * @js NA
 */
struct ActionObjectScriptData
{
    /**
     * For Lua, nativeobject is used to get handler corresponding to the Lua function.
     *
     * @js NA
     * @lua NA
     */
    void* nativeObject;
    
    /**
     * A pointer point to the value data which event action
     *
     * @js NA
     * @lua NA
     */
    int* eventType;
    
    /**
     * A pointer point to the value data which would be converted by different events.
     *
     * @js NA
     * @lua NA
     */
    void* param;
    
    /**
     * Constructor of BasicScriptData.
     *
     * @js NA
     * @lua NA
     */
    ActionObjectScriptData(void* inObject,int* inValue = nullptr, void* inParam = nullptr)
    : nativeObject(inObject),eventType(inValue), param(inParam)
    {
    }
};

/**
 * For Lua, the SchedulerScriptData is used to find the Lua function pointer by the handler, then call the Lua function by push the elapse into the Lua stack as a parameter when scheduler update event is triggered.
 * @~chinese 
 * @~chinese 对于Lua, SchedulerScriptData也是一个数据封装类。当定时器update事件被触发时，它通过handler找到对应的Lua函数，然后将elpase压入Lua堆栈作为Lua函数的参数。
 * @js NA
 * @lua NA
 */
struct SchedulerScriptData
{
    /** @~english
     * the handler corresponding to the Lua function pointer, only use in the Lua.
     *
     * @~chinese 
     * 对应Lua函数的引用id,只用于Lua。
     */
    int handler;
    /** @~english
     * the parameter would be passed in to the Lua function, only use in the Lua.
     *
     * @~chinese 
     * 传入Lua函数的参数，只用于Lua
     */
    float elapse;
    // js use
    void* node;
    
    /**@~english
     * constructor of SchedulerScriptData.
     *
     * @~chinese 
     * SchedulerScriptData的构造函数。
     */
    SchedulerScriptData(int inHandler,float inElapse,void* inNode = nullptr)
    : handler(inHandler),
      elapse(inElapse),
      node(inNode)
    {
    }
};

/**@~english
 * For Lua, the TouchesScriptData is used to find the Lua function pointer by the nativeObject, then call the Lua function by push touches data and actionType into the Lua stack as the parameters when the touches event is triggered.
 * @~chinese 
 * 对于Lua, TouchesScriptData封装了touches相关数据。当touches事件被触发，它将通过nativeObject查找对于Lua函数的handler,然后将touches数据和actionType压入Lua堆栈作为Lua函数参数调用Lua函数。
 * @js NA
 * @lua NA
 */
struct TouchesScriptData
{
    /** @~english
     * The EventTouch::EventCode type. 
     *
     * @~chinese 
     * EventTouch::EventCode类型的值。
     */
    EventTouch::EventCode actionType;
    /** @~english
     * For Lua, it Used to find the Lua function pointer by the ScriptHandlerMgr.
     *
     * @~chinese 
     * 对于Lua，nativeObject用于查找对Lua函数的handler。
     */
    void* nativeObject;
    /** @~english
     * The vector of Touch.For Lua, it would be convert to the Lua table form to be pushed into the Lua stack. 
     *
     * @~chinese 
     * 关于Touch的std::vector。对于Lua, 这个vector会转成对应的Lua table压入对应的Lua stack。
     */
    const std::vector<Touch*>& touches;
    /** @~english
     * event information, it is useless for Lua.
     *
     * @~chinese 
     * 事件信息，Lua不需用到这个变量。
     */
    Event* event;
    
    /**@~english
     * Constructor of TouchesScriptData.
     *
     * @~chinese 
     * TouchesScriptData的构造函数。
     */
    TouchesScriptData(EventTouch::EventCode inActionType, void* inNativeObject, const std::vector<Touch*>& inTouches, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touches(inTouches),
      event(evt)
    {
    }
};

/**@~english
 * For Lua, the TouchScriptData is used to find the Lua function pointer by the nativeObject, then call the Lua function by push touch data and actionType converted to string type into the Lua stack as the parameters when the touch event is triggered.
 * @~chinese 
 * 对于Lua, TouchScriptData封装了touch相关数据。当touch事件被触发，它将通过nativeObject查找对于Lua函数的handler,然后将touch数据和actionType压入Lua堆栈作为Lua函数的参数调用Lua函数。
 * @js NA
 * @lua NA
 */
struct TouchScriptData
{
    /** @~english
     * The EventTouch::EventCode type.
     *
     * @~chinese 
     * EventTouch::EventCode类型的值。
     */
    EventTouch::EventCode actionType;
    /** @~english
     * For Lua, it Used to find the Lua function pointer by the ScriptHandlerMgr.
     *
     * @~chinese 
     * 对于Lua，nativeObject用于查找对Lua函数指针的handler。
     */
    void* nativeObject;
    /** @~english
     * touch information. it would be in x,y form to push into the Lua stack.
     *
     * @~chinese 
     * touch信息，它将以x,y形式压入Lua堆栈。
     */
    Touch* touch;
    /**@~english
     * event information,it is useless for Lua.
     *
     * @~chinese 
     * 事件信息，Lua不需用到这个变量。
     */
    Event* event;
    
    /** @~english
     * Constructor of TouchScriptData.
     *
     * @~chinese 
     * TouchScriptData的构造函数。
     */
    TouchScriptData(EventTouch::EventCode inActionType, void* inNativeObject, Touch* inTouch, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touch(inTouch),
      event(evt)
    {
    }
};


/**@~english
 * For Lua, the KeypadScriptData is used to find the Lua function pointer by the nativeObject, then call the Lua function by push the actionType converted to string type into the Lua stack as the parameters when the Keypad event is triggered.
 * @~chinese 
 * 对于Lua，KeypadScriptData封装了关于Keypad信息的相关数据。当Keypad事件被触发，它将通过nativeObject查找对应Lua函数的handler,然后将actionType转成对应的字符串压入Lua堆栈做为Lua函数的参数调用Lua函数。
 * @js NA
 * @lua NA
 */
struct KeypadScriptData
{
    /** @~english
     * The specific type of EventKeyboard::KeyCode
     *
     * @~chinese 
     * EventKeyboard::KeyCode类型的值。
     */
    EventKeyboard::KeyCode actionType;
    /** @~english
     * For Lua, it Used to find the Lua function pointer by the ScriptHandlerMgr.
     *
     * @~chinese 
     * 对于Lua，nativeObject用于查找对Lua函数指针的handler。
     */
    void* nativeObject;
    
    /**@~english
     * Constructor of KeypadScriptData.
     *
     * @~chinese 
     * KeypadScriptData的构造函数。
     */
    KeypadScriptData(EventKeyboard::KeyCode inActionType,void* inNativeObject)
    : actionType(inActionType),nativeObject(inNativeObject)
    {
    }
};


/**@~english
 * For Lua, the CommonScriptData is used to find the Lua function pointer by the handler, then call the Lua function by push the eventName, eventSource(if it not nullptr), eventSourceClassName(if it is nullptr or "", and the eventSource is not nullptr,would give the default string "cc.Ref") into the Lua stack as the parameter when the common event such as is triggered.
 * @~chinese
 * 对于Lua，CommonScriptData封装了一般数据。当一般事件触发时，它将通过handler找到对应的Lua函数指针，然后将eventName，eventSource(如果不为空)，eventSourceClassName(如果eventSourceClassName不为nullptr，并且eventSourceClassName为空或者""，它将会将默认地将"cc.Ref"压入到Lua栈中)压入Lua栈中作为Lua函数的参数调用Lua函数。
 * @js NA
 * @lua NA
 */
struct CommonScriptData
{
    /** @~english
     * The index to find the corresponding to the Lua function pointer.
     *
     * @~chinese 
     * 对应Lua函数的引用id,只用于Lua。
     */
    int handler;
    /** @~english
     * The string value to be pushed into the Lua stack.
     *
     * @~chinese 
     * 压入Lua栈的事件名。
     */
    char eventName[64];
    /** @~english
     * The source object trigger the event,could be nullptr.
     *
     * @~chinese 
     * 事件触发源对象的指针，可以为nullptr。
     */
    Ref* eventSource;
    /**@~english
     * The class name of source object trigger the event, could be 0.
     *
     * @~chinese 
     * 事件触发源对象的类名,可以为空。
     */
    char eventSourceClassName[64];
    
    /** @~english
     * Constructor of  CommonScriptData.
     *
     * @~chinese 
     * CommonScriptData的构造函数。
     */
    CommonScriptData(int inHandler,const char* inName, Ref* inSource = nullptr,const char* inClassName = nullptr)
    : handler(inHandler),
      eventSource(inSource)
    {
        strncpy(eventName, inName, 64);
        
        if (nullptr == inClassName)
        {
            memset(eventSourceClassName, 0, 64*sizeof(char));
        }
        else
        {
            strncpy(eventSourceClassName, inClassName, 64);
        }
    }
};

/**@~english
 * The ScriptEvent wrapper the different script data corresponding to the ScriptEventType in to the unified struct.
 * when the corresponding event is triggered, we could call the `sendEvent` of ScriptEngineProtocol to handle the event.
 * @~chinese 
 * ScriptEvent将不同类型的ScriptEventType对应的脚本数据封装到一个统一的结构里面。
 * 当对应的事件被触发, 将调用ScriptEngineProtocol的`sendEvent`来处理这个event。
 * @js NA
 * @lua NA
 */
struct ScriptEvent
{
    /** @~english
     * The specific type of ScriptEventType.
     *
     * @~chinese 
     * 特定ScriptEventType的值。
     */
    ScriptEventType type;
    /** @~english
     * Pointer point to the different data.
     *
     * @~chinese 
     * 指向不同数据的指针。
     */
    void* data;
    
    /**@~english
     * Constructor of ScriptEvent.
     *
     * @~chinese 
     * ScriptEvent的构造函数。
     */
    ScriptEvent(ScriptEventType inType,void* inData)
    : type(inType),
      data(inData)
    {
    }
};

/** @~english
 * Don't make ScriptEngineProtocol inherits from Ref since setScriptEngine is invoked only once in AppDelegate.cpp,
 * It will affect the lifecycle of ScriptEngine instance, the autorelease pool will be destroyed before destructing ScriptEngine.
 * So a crash will appear on Win32 if you click the close button.
 * @~chinese 
 * 由于ScriptEngineProtocol对象在AppDelegate.cpp中通过setScriptEngine设置后将一直存在，所以它不需要从Ref派生。
 * 并且它将会影响到脚本引擎实例的生命期，而autorelease pool会在脚本引擎被析构前调用。
 * 如果你点击关闭按钮，在win32平台上会出现崩溃。
 * @js NA
 * @lua NA
 */
class CC_DLL ScriptEngineProtocol
{
public:
    
    /** @~english
     * Constructor of ScriptEngineProtocol.
     *
     * @~chinese 
     * ScriptEngineProtocol的构造函数。
     */
    ScriptEngineProtocol()
    {};
    
    /**@~english
     * Destructor of ScriptEngineProtocol.
     *
     * @~chinese 
     * ScriptEngineProtocol的析构函数。
     */
    virtual ~ScriptEngineProtocol() {};
    
    /** @~english
     * Get the specific script type.
     *
     * @~chinese 
     * 获取脚本引擎的类型。
     * 
     * @return @~english the specific script type.
     *
     * @~chinese 获取脚本引擎的类型。
     */
    virtual ccScriptType getScriptType() { return kScriptTypeNone; };

    /** @~english
     * Remove script object,the specific meaning should refer to the ScriptType.
     * For Lua, @see removeScriptObjectByObject of LuaEngine
     * @~chinese 
     * 移除脚本对象，不同的ScriptType有不同的操作。
     * 对于Lua, @see removeScriptObjectByObject of LuaEngine.
     */
    virtual void removeScriptObjectByObject(Ref* obj) = 0;
    
    /** @~english
     * Remove script function handler, only LuaEngine class need to implement this function.
     * @~chinese 
     * 移除handler的引用,只有LuaEngine需要实现这个函数。
     * @see removeScriptHandler of LuaEngine.
     */
    virtual void removeScriptHandler(int handler) {};
    
    /** @~english
     * Reallocate script function handler, only LuaEngine class need to implement this function.
     * @~chinese 
     * 重新分配脚本函数的handler,只有LuaEngine类需要实现这个函数。
     * @see reallocateScriptHandler of LuaEngine.
     */
    virtual int reallocateScriptHandler(int handler) { return 0;}
    
    /**@~english
     * Execute script code contained in the given string.
     *
     * @~chinese 
     * 执行给定字符串中包含的脚本代码。
     * 
     * @param codes @~english holding the valid script code that should be executed.
     * @~chinese 将被执行的脚本字符串。
     * @return @~english 0 if the string is executed correctly,other if the string is executed wrongly.
     * @~chinese 执行正确返回0，否则返回其它值。
     */
    virtual int executeString(const char* codes) = 0;
    
    /**@~english
     * Execute a script file.
     * 
     * @~chinese 
     * 执行一个脚本文件。
     * 
     * @param filename @~english String object holding the filename of the script file that is to be executed.
     * @~chinese 脚本文件的文件名。
     * @return @~english 0 if it happen the error or it hasn't return value, otherwise it return the value by calling the lua function.
     * @~chinese 如果碰到错误或者调用的Lua函数没有返回值，返回0；否则返回调用Lua函数的返回值。
     */
    virtual int executeScriptFile(const char* filename) = 0;
    
    /**@~english
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer for Lua.
     *
     * @~chinese 
     * 执行全局的脚本函数。
     * 对于Lua,该全局函数不应该有函数参数并且它将返回一个整数值。
     * 
     * @param functionName @~english String object holding the name of the function, in the global script environment, that is to be executed.
     * @~chinese 全局脚本函数的字符串名称。
     * @return @~english The integer value returned from the script function.
     * @~chinese 从脚本函数返回的整数值。
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
    /**@~english
     * When some events triggered in the c++ also needs to pass into script ,call this func.The ScriptEvent contains the data need to passed into the script.
     *
     *
     * @~chinese 
     * 当c++中触发的一些事件需要传递到脚本层处理时,将会调用这个函数来处理。ScriptEvent中包含了要传到脚本层处理的数据。
     */
    virtual int sendEvent(ScriptEvent* evt) = 0;
    
    /** @~english
     * Handle the assert message.
     *
     * @~chinese 
     * 处理断言信息。
     * 
     * @return @~english return true if current _callFromLua of LuaStack is not equal to 0 otherwise return false for Lua.
     *
     * @~chinese 返回true,如果当前LuaStack的_callFromLua不等于0,否则返回假。
     */
    virtual bool handleAssert(const char *msg) = 0;
    
    /** @~english
     * Set whether the call comes from the script or not, only use for the js.
     *
     * @~chinese 
     * 设置这个调用是否是由脚本层触发的，只用于js。
     * @param callFromScript @~english whether the call comes from the script or not.
     * @~chinese 调用是否用脚本层触发。
     */
    virtual void setCalledFromScript(bool callFromScript) { CC_UNUSED_PARAM(callFromScript); };
    
    /** @~english
     * Get the flag that represents whether the call comes from the script or not,only use for the js.
     *
     * @~chinese 
     * 获取调用是否是由脚本层触发的标记，只用于js。
     * 
     * @return @~english false.
     * @~chinese false。
     * @lua NA
     * @js NA
     */
    virtual bool isCalledFromScript() { return false; };
    
    /** @~english ConfigType enum.  @~chinese ConfigType枚举类。*/
    enum class ConfigType
    {
        NONE,
        COCOSTUDIO
    };
    /** @~english
     * Parse configuration file.
     * 
     * @~chinese 
     * 解析配置文件。
     * 
     * @param type @~english the specific type value.
     * @~chinese 特定ConfigType的值。
     * @param str @~english the information data.
     *
     * @~chinese 数据信息。
     */
    virtual bool parseConfig(ConfigType type, const std::string& str) = 0;
};

class Node;
/**@~english
 * ScriptEngineManager is a singleton which manager an object instance of ScriptEngineProtocl, such as LuaEngine.
 *
 * @~chinese 
 * ScriptEngineManager是一个用来管理ScriptEngineProtocl实例对象的单例，例如LuaEngine实例对象。
 * 
 * @since v0.99.5-x-0.8.5
 * @js NA
 * @lua NA
 */
class CC_DLL ScriptEngineManager
{
public:
    /** @~english
     * Constructor of ScriptEngineManager.
     *
     * @~chinese 
     * ScriptEngineManager的构造函数。
     */
    ~ScriptEngineManager(void);
    /** @~english
     * Get the ScriptEngineProtocol object.
     *
     * @~chinese 
     * 获取ScriptEngineProtocol对象实例。
     * 
     * @return @~english the ScriptEngineProtocol object.
     *
     * @~chinese ScriptEngineProtocol对象实例。
     */
    ScriptEngineProtocol* getScriptEngine(void) {
        return _scriptEngine;
    }
    /**@~english
     * Set the ScriptEngineProtocol object should be managed.
     *
     * @~chinese 
     * 设置需要被管理的ScriptEngineProtocol对象。
     * 
     * @param scriptEngine @~english the ScriptEngineProtocol object should be managered.
     *
     * @~chinese 需要被管理的ScriptEngineProtocol对象。
     */
    void setScriptEngine(ScriptEngineProtocol *scriptEngine);
    
    /**@~english
     * Remove the ScriptEngineProtocol object managed.
     *
     *
     * @~chinese 
     * 删除被管理的ScriptEngineProtocol。
     */
    void removeScriptEngine(void);
    /**@~english
     * Get the instance of ScriptEngineManager object.
     *
     * @~chinese 
     * 获取ScriptEngineManager对象的实例。
     * 
     * @return @~english the instance of ScriptEngineManager object.
     *
     * @~chinese ScriptEngineManager对象的实例。
     */
    static ScriptEngineManager* getInstance();
    /**@~english
     * Destroy the singleton of ScriptEngineManager.
     *
     * @~chinese 
     * 销毁ScriptEngineManager的单例。
     */
    static void destroyInstance();
    /**@~english
     * send the node event to JS
     *
     * @~chinese 
     * 发送node事件到JS。
     * @param node @~english the pointer of node object.
     *
     * @~chinese
     * node对象指针。
     *
     * @param action @~english action.
     *
     * @~chinese
     * 事件类型。
     *
     * @return @~english true if execute successfully,otherwise false.
     *
     * @~chinese 执行成功返回true，否则返回false。
     */
    static bool sendActionEventToJS(Action* actionObject, int eventType, void* param);
    /**
     *
     *
     * @lua NA
     * @js NA
     */
    static bool sendNodeEventToJS(Node* node, int action);
    /**@~english
     * send the extended event of Node to JS
     *
     * @~chinese 
     * 发送扩展的node事件到JS。
     * @param node @~english the pointer of node object.
     *
     * @~chinese
     * node对象指针。
     *
     * @param action @~english action.
     *
     * @~chinese
     * 事件类型。
     *
     * @return @~english true if execute successfully,otherwise false.
     *
     * @~chinese 执行成功返回true，否则返回false。
     */
    static bool sendNodeEventToJSExtended(Node* node, int action);
    /**@~english
     * Call the Lua function when the event of node is triggered.
     * 
     * @~chinese 
     * 当node事件触发时回调Lua函数。
     * 
     * @param node @~english the nativeobject triggers the event.
     * @~chinese 触发事件的node对象。
     * @param action @~english the specific action type.
     *
     * @~chinese 事件类型。
     */
    static void sendNodeEventToLua(Node* node, int action);
    /**
     * @deprecated @~english Use getInstance() instead.
     * @~chinese 使用getInstance替代。
     */
    CC_DEPRECATED_ATTRIBUTE static ScriptEngineManager* sharedManager() { return ScriptEngineManager::getInstance(); };
    /**
     * @deprecated @~english Use destroyInstance() instead.
     * @~chinese 使用destroyInstance替代
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedManager() { ScriptEngineManager::destroyInstance(); };
    
private:
    ScriptEngineManager(void)
    : _scriptEngine(nullptr)
    {
    }
    
    ScriptEngineProtocol *_scriptEngine;
};

NS_CC_END



#endif // #if CC_ENABLE_SCRIPT_BINDING

// end group
/// @}

#endif // __SCRIPT_SUPPORT_H__
