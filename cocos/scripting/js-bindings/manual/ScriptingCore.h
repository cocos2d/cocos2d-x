/*
 * Created by Rolando Abarca on 3/14/12.
 * Copyright (c) 2012 Zynga Inc. All rights reserved.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __SCRIPTING_CORE_H__
#define __SCRIPTING_CORE_H__


#include "jsapi.h"
#include "jsfriendapi.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "js_bindings_config.h"
#include "js_bindings_core.h"
#include "spidermonkey_specifics.h"
#include "js_manual_conversions.h"
#include "mozilla/Maybe.h"
#include "js-BindingsExport.h"

#include <assert.h>
#include <memory>

#define ENGINE_VERSION "Cocos2d-JS v3.10"

void js_log(const char *format, ...);

typedef void (*sc_register_sth)(JSContext* cx, JS::HandleObject global);

void registerDefaultClasses(JSContext* cx, JS::HandleObject global);


class SimpleRunLoop : public cocos2d::Ref
{
public:
    void update(float d);
};

/**
 * @addtogroup jsb
 * @{
 */

/**
 * @brief @~english ScriptingCore is the main class which manages interaction with JavaScript environment
 * @details @~english It creates the JavaScript context and its global object.
 * It also manages object bindings between C++ scope and JavaScript scope,
 * for most cocos2d classes, if you create an object in JavaScript scope, it will also create a C++ object,
 * ScriptingCore will manage a proxy between them and synchronize the life cycle.
 * It can:
 * - Execute JavaScript functions in different ways with different parameters
 * - Evaluate JavaScript commands or string
 * - Execute a JavaScript file
 * - Clean a JavaScript file cache
 * - Clean all JavaScript files
 * - Cleanup or reset the JavaScript context
 * - Invoke garbage collection of JavaScript context
 * - etc...
 */
class CC_JS_DLL ScriptingCore : public cocos2d::ScriptEngineProtocol
{
private:
    JSRuntime *_rt;
    JSContext *_cx;
    mozilla::Maybe<JS::PersistentRootedObject> _global;
    mozilla::Maybe<JS::PersistentRootedObject> _debugGlobal;
    SimpleRunLoop* _runLoop;

    bool _callFromScript;
    ScriptingCore();
public:
    ~ScriptingCore();

    /**@~english
     * ScriptingCore is a singleton class, you can retrieve its instance with this function.
     * @return @~english The ScriptingCore instance.
     */
    static ScriptingCore *getInstance();
    
    /**@~english
     * Gets the script type, for ScriptingCore, it will return `cocos2d::kScriptTypeJavascript`
     * @return `cocos2d::kScriptTypeJavascript`
     */
    virtual cocos2d::ccScriptType getScriptType() override { return cocos2d::kScriptTypeJavascript; };
    
    /**
     * @brief @~english Removes the C++ object's linked JavaScript proxy object from JavaScript context
     * @param obj @~english Object to be removed
     */
    virtual void removeScriptObjectByObject(cocos2d::Ref* obj) override;
    
    /**
     * @brief @~english Useless in ScriptingCore, please use evalString
     * @see evalString
     */
    virtual int executeString(const char* codes) override { return 0; }
    
    /**
     * @brief @~english Pause scheduled tasks and actions for an object proxy.
     * @param p @~english The object proxy
     */
    void pauseSchedulesAndActions(js_proxy_t* p);
    /**
     * @brief @~english Resume scheduled tasks and actions for an object proxy.
     * @param p @~english The object proxy
     */
    void resumeSchedulesAndActions(js_proxy_t* p);
    /**
     * @brief @~english Cleanup scheduled tasks and actions for an object proxy.
     * @param p @~english The object proxy
     */
    void cleanupSchedulesAndActions(js_proxy_t* p);

    /**
     @brief Useless in ScriptingCore, please use runScript
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual  int executeScriptFile(const char* filename) override { return 0; }

    /**
     @brief @~english Useless in ScriptingCore, please use executeFunctionWithOwner
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName) override { return 0; }

    virtual int sendEvent(cocos2d::ScriptEvent* message) override;
    
    virtual bool parseConfig(ConfigType type, const std::string& str) override;
    /**
     * @brief @~english Useless in ScriptingCore
     * @return @~english false
     */
    virtual bool handleAssert(const char *msg) override { return false; }

    virtual void setCalledFromScript(bool callFromScript) override { _callFromScript = callFromScript; };
    virtual bool isCalledFromScript() override { return _callFromScript; };
    
    /**
     * @brief @~english Execute a js function with a JavaScript object as parameter.
     * By passing a native object, ScriptingCore will found its JavaScript object with the proxy.
     * Then the function will be invoked with the native object's js proxy as caller.
     * @param nativeObj @~english The caller object's C++ proxy.
     * @param name      @~english The function name.
     * @param obj       @~english The JavaScript object as parameter.
     * @return @~english Return the js function's boolean result if successfully invoked, otherwise return false.
     */
    bool executeFunctionWithObjectData(void* nativeObj, const char *name, JSObject *obj);
    
    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments count and arguments.
     * @param owner     @~english The caller object.
     * @param name      @~english The function name.
     * @param argc      @~english The arguments count.
     * @param vp        @~english The arguments.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp);
    
    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments count, arguments and a return value.
     * @param owner     @~english The caller object.
     * @param name      @~english The function name.
     * @param argc      @~english The arguments count.
     * @param vp        @~english The arguments.
     * @param retVal    @~english The js object to save the return value.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp, JS::MutableHandleValue retVal);
    
    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments array.
     * This is more reliable in js memory management
     * @param owner     @~english The caller object.
     * @param name      @~english The function name.
     * @param args      @~english The arguments array.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args);
    
    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments array and a return value.
     * This is more reliable in js memory management
     * @param owner     @~english The caller object.
     * @param name      @~english The function name.
     * @param args      @~english The arguments array.
     * @param retVal    @~english The js object to save the return value.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args, JS::MutableHandleValue retVal);
    
    /**
     * @brief @~english Execute a js function with a js this object and the js function object.
     * @param thisObj   @~english The js this object.
     * @param callback  @~english The js function object.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback);
    /**
     * @brief @~english Execute a js function with a js this object, the js function object, arguments and a return value.
     * @param thisObj   @~english The js this object.
     * @param callback  @~english The js function object.
     * @param vp        @~english The arguments array.
     * @param retVal    @~english The js object to save the return value.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback, const JS::HandleValueArray& vp, JS::MutableHandleValue retVal);
    
    /**@~english
     * Evaluate the specified js code string
     * @param string    @~english The string with the javascript code to be evaluated
     * @param outVal    @~english The jsval that will hold the return value of the evaluation.
     * @param filename  @~english The filename
     * @param cx        @~english The js context
     * @param global    @~english The js global object
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool evalString(const char *string, JS::MutableHandleValue outVal, const char *filename, JSContext* cx, JS::HandleObject global);
    
    /**@~english
     * Evaluate the specified js code string
     * @param string    @~english The string with the javascript code to be evaluated
     * @param outVal    @~english The jsval that will hold the return value of the evaluation.
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool evalString(const char *string, JS::MutableHandleValue outVal);
    
    /**@~english
     * Evaluate the specified js code string
     * @param string    @~english The string with the javascript code to be evaluated
     * @return @~english Return true if successfully invoked, otherwise return false.
     */
    bool evalString(const char *string);
    
    /**
     @brief @~english Get script object for the given path
     @param path @~english The script file path
     @return @~english Script object
     */
    JSScript* getScript(const char *path);
    
    /**@~english
     * Compile the specified js file
     * @param path    @~english The path of the script to to compiled
     * @param global    @~english The js global object
     * @param cx        @~english The js context
     */
    void compileScript(const char *path, JS::HandleObject global, JSContext* cx = NULL);
    
    /**@~english
     * Run the specified js file
     * @param path @~english The path of the script to be executed
     * @return @~english Return true if succeed, otherwise return false.
     */
    bool runScript(const char *path);
    /**@~english
     * Run the specified js file
     * @param path @~english The path of the script to be executed
     * @param global @~english The global object to execute the script
     * @param global @~english The context to execute the script
     * @return @~english Return true if succeed, otherwise return false.
     */
    bool runScript(const char *path, JS::HandleObject global, JSContext* cx = NULL);
    
    /**@~english
     * Require the specified js file
     * The difference between run and require is that require returns the export object of the script
     * @param path @~english The path of the script to be executed
     * @param jsvalRet @~english On success, return the value from the last executed expression statement processed in the script
     * @return @~english Return true if succeed, otherwise return false.
     * @see https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey/JSAPI_reference/JS_ExecuteScript
     */
    bool requireScript(const char *path, JS::MutableHandleValue jsvalRet);
    /**@~english
     * Require the specified js file
     * The difference between run and require is that require returns the export object of the script
     * @param path @~english The path of the script to be executed
     * @param global @~english The global object to execute the script
     * @param global @~english The context to execute the script
     * @param jsvalRet @~english On success, return the value from the last executed expression statement processed in the script
     * @return @~english Return true if succeed, otherwise return false.
     * @see https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey/JSAPI_reference/JS_ExecuteScript
     */
    bool requireScript(const char *path, JS::HandleObject global, JSContext* cx, JS::MutableHandleValue jsvalRet);
    
    /**@~english
     * Clean script object for the specified js file
     * @param path @~english The path of the js file to be cleaned
     */
    void cleanScript(const char *path);
    
    /**@~english
     * Gets the cached script objects for all executed js file
     * @return @~english The cached script object map
     */
    std::unordered_map<std::string, JSScript*> &getFileScript();
    /**@~english
     * Clean all script objects
     */
    void cleanAllScript();
    
    /**@~english
     * Initialize everything, including the js context, js global object etc.
     */
    void start();
    
    /**@~english
     * Cleanup everything, including script cache, js context, global object etc.
     */
    void cleanup();
    
    /**@~english
     * Cleanup everything then initialize everything
     */
    void reset();
    
    /**@~english
     * Add the register_sth callback to the list of functions that need to be called after the creation of the context.
     * It's normally used to register script bindings in the js context for bound classes
     * @param callback @~english The callback to register something to the js context
     */
    void addRegisterCallback(sc_register_sth callback);
    
    /**@~english
     * Create a new context. If one is already there, it will destroy the old context and create a new one.
     */
    void createGlobalContext();
    
    /**@~english
     * Removes all rooted object in the given js context, rooted object won't be garbage collected.
     * @param cx @~english The js context
     */
    static void removeAllRoots(JSContext *cx);
    
    /**@~english
     * Simulate a touch event and dispatch it to a js object.
     * @param eventType @~english The touch event type
     * @param pTouch @~english The touch object
     * @param obj @~english The js object
     * @param retval @~english The return value of the touch event callback
     * @return @~english Return 1 if succeed, otherwise return 0.
     */
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj, JS::MutableHandleValue retval);
    /**@~english
     * Simulate a touch event and dispatch it to a js object.
     * @param eventType @~english The touch event type
     * @param pTouch @~english The touch object
     * @param obj @~english The js object
     * @return @~english Return 1 if succeed, otherwise return 0.
     */
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj);
    /**@~english
     * Simulate a multi touch event and dispatch it to a js object.
     * @param eventType @~english The touch event type
     * @param touches @~english Touchs list for multitouch
     * @param obj @~english The js object
     * @return @~english Return 1 if succeed, otherwise return 0.
     */
    int executeCustomTouchesEvent(cocos2d::EventTouch::EventCode eventType,
                                  const std::vector<cocos2d::Touch*>& touches, JSObject *obj);
    /**@~english
     * Gets the current global context.
     * @return @~english the global context
     */
    JSContext* getGlobalContext() {
        return _cx;
    };
    
    /**@~english
     * Report an error in the js context
     * @param cx @~english The js context
     * @param message @~english The error message
     * @param report @~english The js error report object
     */
    static void reportError(JSContext *cx, const char *message, JSErrorReport *report);
    
    /**@~english
     * Log something to the js context using CCLog.
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     * @return @~english Return true if succeed, otherwise return false.
     */
    static bool log(JSContext *cx, uint32_t argc, jsval *vp);
    
    /**@~english
     * Sets a js value to the targeted js obejct's reserved slot, which is not exposed to script environment.
     * @param i @~english The slot index
     * @param obj @~english The targeted object
     * @param value @~english The js value to set to the slot
     * @return @~english Return true if succeed, otherwise return false.
     */
    bool setReservedSpot(uint32_t i, JSObject *obj, jsval value);
    
    /**@~english
     * Runs a script from script environment, it should be invoked from script environment
     * Bound to `__jsc__.executeScript` and `window.executeScript`
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     * @return @~english Return true if succeed, otherwise return false.
     */
    static bool executeScript(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Forces a cycle of garbage collection, it should be invoked from script environment
     * Bound to `__jsc__.garbageCollect` and `window.garbageCollect`
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     */
    static bool forceGC(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Dump all named rooted objects, it should be invoked from script environment
     * Bound to `__jsc__.dumpRoot`
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     */
    static bool dumpRoot(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Adds a js object to root so that it won't be touched by the garbage collection, it should be invoked from script environment
     * Bound to `__jsc__.addGCRootObject`
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     */
    static bool addRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Removes a js object from root, it should be invoked from script environment
     * Bound to `__jsc__.removeGCRootObject`
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     */
    static bool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Check whether a js object's C++ proxy is still valid, it should be invoked from script environment
     * Bound to `window.__isObjectValid`
     * @param cx @~english The js context
     * @param argc @~english The arguments count
     * @param vp @~english The arguments
     */
    static bool isObjectValid(JSContext *cx, uint32_t argc, jsval *vp);
    
    /**@~english
     * Log a string to the debug environment.
     * Enable the debug environment so that it can be invoked.
     * @param str @~english The message to log
     */
    void debugProcessInput(const std::string& str);
    /**@~english
     * Enable the debug environment, mozilla Firefox's remote debugger or Code IDE can connect to it.
     * @param port @~english The port to connect with the debug environment, default value is 5086
     */
    void enableDebugger(unsigned int port = 5086);
    /**@~english
     * Gets the debug environment's global object
     * @return @~english The debug environment's global object
     */
    JSObject* getDebugGlobal() { return _debugGlobal.ref().get(); }
    /**@~english
     * Gets the global object
     * @return @~english The global object
     */
    JSObject* getGlobalObject() { return _global.ref().get(); }
    
    /**@~english
     * Checks whether a C++ function is overrided in js prototype chain
     * @param obj @~english The js object
     * @param name @~english The function name
     * @param native @~english The native function
     * @return @~english The global object
     */
    bool isFunctionOverridedInJS(JS::HandleObject obj, const std::string& name, JSNative native);

    /**
     * Roots the associated JSObj.
     * The GC won't collected rooted objects. This function is only called
     * when compiled with CC_ENABLE_GC_FOR_NATIVE_OBJECTS=1
     */
    virtual void rootObject(cocos2d::Ref* ref) override;
    /**
     * Unroots the associated JSObj.
     * The GC will collect this object the next time the GC
     * is called.
     * This function is only called when compiled with CC_ENABLE_GC_FOR_NATIVE_OBJECTS=1
     */
    virtual void unrootObject(cocos2d::Ref* ref) override;

private:
    void string_report(JS::HandleValue val);
    void initRegister();

public:
    int handleNodeEvent(void* data);
    int handleActionEvent(void* data);
    int handleComponentEvent(void* data);
    
    bool handleTouchesEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    bool handleTouchesEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event, JS::MutableHandleValue jsvalRet);

    bool handleTouchEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, cocos2d::Touch* touch, cocos2d::Event* event);
    bool handleTouchEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, cocos2d::Touch* touch, cocos2d::Event* event, JS::MutableHandleValue jsvalRet);

    bool handleMouseEvent(void* nativeObj, cocos2d::EventMouse::MouseEventType eventType, cocos2d::Event* event);
    bool handleMouseEvent(void* nativeObj, cocos2d::EventMouse::MouseEventType eventType, cocos2d::Event* event, JS::MutableHandleValue jsvalRet);

    bool handleKeybardEvent(void* nativeObj, cocos2d::EventKeyboard::KeyCode keyCode, bool isPressed, cocos2d::Event* event);
    bool handleFocusEvent(void* nativeObj, cocos2d::ui::Widget* widgetLoseFocus, cocos2d::ui::Widget* widgetGetFocus);

    void restartVM();
};

JSObject* NewGlobalObject(JSContext* cx, bool debug = false);

bool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value);
bool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret);

template <class T>
js_type_class_t *jsb_register_class(JSContext *cx, JSClass *jsClass, JS::HandleObject proto, JS::HandleObject parentProto)
{
    TypeTest<T> t;
    js_type_class_t *p = nullptr;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsClass;
        if (p->proto.empty())
        {
            p->proto.construct(cx);
        }
        p->proto.ref() = proto;
        if (p->parentProto.empty())
        {
            p->parentProto.construct(cx);
        }
        p->parentProto.ref() = parentProto ;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
    return p;
}

/** creates two new proxies: one associaged with the nativeObj,
 and another one associated with the JsObj */
js_proxy_t* jsb_new_proxy(void* nativeObj, JS::HandleObject jsObj);
/** returns the proxy associated with the Native* */
js_proxy_t* jsb_get_native_proxy(void* nativeObj);
/** returns the proxy associated with the JSObject* */
js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);
/** deprecated: use jsb_remove_proxy(js_proxy_t* proxy) instead */
void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy);
/** removes both the native and js proxies */
void jsb_remove_proxy(js_proxy_t* proxy);

/**
 * Generic initialization function for subclasses of Ref
 */
void jsb_ref_init(JSContext* cx, JS::Heap<JSObject*> *obj, cocos2d::Ref* ref, const char* debug);

/**
 * Generic initialization function for subclasses of Ref.
 * Similar to jsb_ref_init(), but call it if you know that Ref has been autoreleased
 * This function should never be called. It is only added as way to fix
 * an issue with the static auto-bindings with the "create" function
 */
void jsb_ref_autoreleased_init(JSContext* cx, JS::Heap<JSObject*> *obj, cocos2d::Ref* ref, const char* debug);

/**
 * Generic finalize used by objects that are subclass of Ref
 */
void jsb_ref_finalize(JSFreeOp* fop, JSObject* obj);

/**
 Disassociates oldRef from jsobj, and associates a new Ref.
 Useful for the EaseActions and others
 */
void jsb_ref_rebind(JSContext* cx, JS::HandleObject jsobj, js_proxy_t *js2native_proxy, cocos2d::Ref* oldRef, cocos2d::Ref* newRef, const char* debug);

/**
 Creates a new JSObject of a certain type (typeClass) and creates a proxy associated with and the Ref
 */
JSObject* jsb_ref_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug);

/**
 * Creates a new JSObject of a certain type (typeClass) and creates a proxy associated with and the Ref
 * Similar to jsb_ref_create_jsobject(), but call it if you know that Ref has been autoreleased
 * This function should never be called. It is only added as way to fix
 * an issue with the static auto-bindings with the "create" function
 */
JSObject* jsb_ref_autoreleased_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug);

/**
 It will try to get the associated JSObjct for ref.
 If it can't find it, it will create a new one associating it to Ref.
 Call this function for objects that were already created and initialized, when returning `getChild()`
 */
JSObject* jsb_ref_get_or_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug);

/**
 It will try to get the associated JSObjct for ref.
 If it can't find it, it will create a new one associating it to Ref
 Call this function for objects that might return an already existing copy when you create them. For example, `Animation3D::create()`;
 */
JSObject* jsb_ref_autoreleased_get_or_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug);

#endif /* __SCRIPTING_CORE_H__ */
