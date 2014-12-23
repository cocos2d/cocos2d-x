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

#if CC_ENABLE_SCRIPT_BINDING

typedef struct lua_State lua_State;

NS_CC_BEGIN

class TimerScriptHandler;
class Layer;
class MenuItem;
class CallFunc;
class Acceleration;

enum ccScriptType {
    kScriptTypeNone = 0,
    kScriptTypeLua,
    kScriptTypeJavascript
};

class ScriptHandlerEntry : public Ref
{
public:
    static ScriptHandlerEntry* create(int handler);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScriptHandlerEntry();
    
    int getHandler(void) {
        return _handler;
    }
    
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

/**
 * @addtogroup script_support
 * @{
 */

class SchedulerScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    // nHandler return by tolua_ref_function(), called from LuaCocos2d.cpp
    /**
     * @js NA
     * @lua NA
     */
    static SchedulerScriptHandlerEntry* create(int handler, float interval, bool paused);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~SchedulerScriptHandlerEntry();
    /**
     * @js NA
     * @lua NA
     */
    TimerScriptHandler* getTimer(void) {
        return _timer;
    }
    /**
     * @js NA
     * @lua NA
     */
    bool isPaused(void) {
        return _paused;
    }
    /**
     * @js NA
     * @lua NA
     */
    void markedForDeletion(void) {
        _markedForDeletion = true;
    }
    /**
     * @js NA
     * @lua NA
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



class TouchScriptHandlerEntry : public ScriptHandlerEntry
{
public:
    /**
     * @js NA
     * @lua NA
     */
    static TouchScriptHandlerEntry* create(int handler, bool isMultiTouches, int priority, bool swallowsTouches);
    /**
     * @js NA
     * @lua NA
     */
    virtual ~TouchScriptHandlerEntry();
    /**
     * @js NA
     * @lua NA
     */
    bool isMultiTouches(void) {
        return _isMultiTouches;
    }
    /**
     * @js NA
     * @lua NA
     */
    int getPriority(void) {
        return _priority;
    }
    /**
     * @js NA
     * @lua NA
     */
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
    kComponentEvent
};

struct BasicScriptData
{
    // nativeobject:to get handler for lua or to get jsobject for js
    void* nativeObject;
    // value: a pointer to a object that already defined
    void* value;
    
    // Constructor
    /**
     * @js NA
     * @lua NA
     */
    BasicScriptData(void* inObject,void* inValue = nullptr)
    : nativeObject(inObject),value(inValue)
    {
    }
};

struct SchedulerScriptData
{
    // lua use
    int handler;
    float elapse;
    // js use
    void* node;
    
    // Constructor
    /**
     * @js NA
     * @lua NA
     */
    SchedulerScriptData(int inHandler,float inElapse,void* inNode = nullptr)
    : handler(inHandler),
      elapse(inElapse),
      node(inNode)
    {
    }
};

struct TouchesScriptData
{
    EventTouch::EventCode actionType;
    void* nativeObject;
    const std::vector<Touch*>& touches;
    Event* event;
    
    // Constructor
    /**
     * @js NA
     * @lua NA
     */
    TouchesScriptData(EventTouch::EventCode inActionType, void* inNativeObject, const std::vector<Touch*>& inTouches, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touches(inTouches),
      event(evt)
    {
    }
};

struct TouchScriptData
{
    EventTouch::EventCode actionType;
    void* nativeObject;
    Touch* touch;
    Event* event;
    
    // Constructor
    /**
     * @js NA
     * @lua NA
     */
    TouchScriptData(EventTouch::EventCode inActionType, void* inNativeObject, Touch* inTouch, Event* evt)
    : actionType(inActionType),
      nativeObject(inNativeObject),
      touch(inTouch),
      event(evt)
    {
    }
};

struct KeypadScriptData
{
    EventKeyboard::KeyCode actionType;
    void* nativeObject;
    
    // Constructor
    /**
     * @js NA
     * @lua NA
     */
    KeypadScriptData(EventKeyboard::KeyCode inActionType,void* inNativeObject)
    : actionType(inActionType),nativeObject(inNativeObject)
    {
    }
};

struct CommonScriptData
{
    // Now this struct is only used in LuaBinding.
    int handler;
    char eventName[64];
    Ref* eventSource;
    char eventSourceClassName[64];
    
    // Constructor
    /**
     * @js NA
     * @lua NA
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

struct ScriptEvent
{
    ScriptEventType type;
    void* data;
    
    // Constructor
    /**
     * @js NA
     * @lua NA
     */
    ScriptEvent(ScriptEventType inType,void* inData)
    : type(inType),
      data(inData)
    {
    }
};

// Don't make ScriptEngineProtocol inherits from Object since setScriptEngine is invoked only once in AppDelegate.cpp,
// It will affect the lifecycle of ScriptCore instance, the autorelease pool will be destroyed before destructing ScriptCore.
// So a crash will appear on Win32 if you click the close button.
class CC_DLL ScriptEngineProtocol
{
public:
    ScriptEngineProtocol()
    {};
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~ScriptEngineProtocol() {};
    
    /** Get script type 
     * @js NA
     * @lua NA
     */
    virtual ccScriptType getScriptType() { return kScriptTypeNone; };

    /** Remove script object. 
     * @js NA
     * @lua NA
     */
    virtual void removeScriptObjectByObject(Ref* obj) = 0;
    
    /** Remove script function handler, only LuaEngine class need to implement this function. 
     * @js NA
     * @lua NA
     */
    virtual void removeScriptHandler(int handler) {};
    
    /** Reallocate script function handler, only LuaEngine class need to implement this function. 
     * @js NA
     * @lua NA
     */
    virtual int reallocateScriptHandler(int handler) { return 0;}
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is executed correctly.
     @return other if the string is executed wrongly.
     * @js NA
     * @lua NA
     */
    virtual int executeString(const char* codes) = 0;
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     * @js NA
     * @lua NA
     */
    virtual int executeScriptFile(const char* filename) = 0;
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     * @js NA
     * @lua NA
     */
    virtual int executeGlobalFunction(const char* functionName) = 0;
    
    /**when trigger a script event ,call this func,add params needed into ScriptEvent object.nativeObject is object triggering the event, can be nullptr in lua
     * @js NA
     * @lua NA
     */
    virtual int sendEvent(ScriptEvent* evt) = 0;
    
    /** called by CCAssert to allow scripting engine to handle failed assertions
     * @return true if the assert was handled by the script engine, false otherwise.
     * @js NA
     * @lua NA
     */
    virtual bool handleAssert(const char *msg) = 0;
    
    virtual void setCalledFromScript(bool callFromScript) { CC_UNUSED_PARAM(callFromScript); };
    virtual bool isCalledFromScript() { return false; };
    
    enum class ConfigType
    {
        NONE,
        COCOSTUDIO
    };
    /** Parse configuration file */
    virtual bool parseConfig(ConfigType type, const std::string& str) = 0;
};

class Node;
/**
 ScriptEngineManager is a singleton which holds an object instance of ScriptEngineProtocl
 It helps cocos2d-x and the user code to find back LuaEngine object
 @since v0.99.5-x-0.8.5
 */
class CC_DLL ScriptEngineManager
{
public:
    /**
     * @js NA
     * @lua NA
     */
    ~ScriptEngineManager(void);
    /**
     * @js NA
     * @lua NA
     */
    ScriptEngineProtocol* getScriptEngine(void) {
        return _scriptEngine;
    }
    /**
     * @js NA
     * @lua NA
     */
    void setScriptEngine(ScriptEngineProtocol *scriptEngine);
    /**
     * @js NA
     * @lua NA
     */
    void removeScriptEngine(void);
    /**
     * @js NA
     * @lua NA
     */
    static ScriptEngineManager* getInstance();
    /**
     * @js NA
     * @lua NA
     */
    static void destroyInstance();
    /**
     * @js NA
     * @lua NA
     */
    static bool sendNodeEventToJS(Node* node, int action);
    /**
     * @js NA
     * @lua NA
     */
    static bool sendNodeEventToJSExtended(Node* node, int action);
    /**
     * @js NA
     * @lua NA
     */
    static void sendNodeEventToLua(Node* node, int action);
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static ScriptEngineManager* sharedManager() { return ScriptEngineManager::getInstance(); };
    /**
     * @js NA
     * @lua NA
     */
    CC_DEPRECATED_ATTRIBUTE static void purgeSharedManager() { ScriptEngineManager::destroyInstance(); };
    
private:
    ScriptEngineManager(void)
    : _scriptEngine(nullptr)
    {
    }
    
    ScriptEngineProtocol *_scriptEngine;
};

// end of script_support group
/// @}

NS_CC_END

#endif // #if CC_ENABLE_SCRIPT_BINDING

#endif // __SCRIPT_SUPPORT_H__
