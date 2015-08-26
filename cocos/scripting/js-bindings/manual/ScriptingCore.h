/******************************************************************
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
 ******************************************************************/

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

#include <assert.h>
#include <memory>

#define ENGINE_VERSION "Cocos2d-JS v3.8 RC0"

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
 * @~chinese ScriptingCore是管理与JavaScript环境交互的核心类
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
 * @~chinese 它创建JavaScript上下文和全局对象。
 * 它还管理C++环境和JavaScript环境对象之间的绑定，
 * 对于大多数cocos2d类，如果在JavaScript环境内创建一个对象，它还将同时创建一个c++对象,
 * ScriptingCore将为不同环境下对象管理一个代理并同步不同环境下的生命周期。
 * 它可以:
 * - 以不同的方式与不同的参数执行JavaScript函数
 * - 执行JavaScript命令或字符串
 * - 执行一个JavaScript文件
 * - 清理一个JavaScript文件缓存
 * - 清理所有的JavaScript文件缓存
 * - 清理或重置JavaScript上下文
 * - 调用JavaScript上下文的垃圾收集
 * - 等等...
 */
class ScriptingCore : public cocos2d::ScriptEngineProtocol
{
private:
    JSRuntime *_rt;
    JSContext *_cx;
    mozilla::Maybe<JS::PersistentRootedObject> _global;
    mozilla::Maybe<JS::PersistentRootedObject> _debugGlobal;
    //JS::Heap<JSObject*> _global;
    //JS::Heap<JSObject*> _debugGlobal;
    SimpleRunLoop* _runLoop;

    bool _callFromScript;
    ScriptingCore();
public:
    ~ScriptingCore();

    /**@~english
     * ScriptingCore is a singleton class, you can retrieve its instance with this function.
     * @~chinese 
     * ScriptingCore是一个单例类，你可以用这个函数获取它的实例。
     * @return @~english The ScriptingCore instance.
     * @~chinese ScriptingCore实例。
     */
    static ScriptingCore *getInstance() {
        static ScriptingCore* pInstance = NULL;
        if (pInstance == NULL) {
            pInstance = new ScriptingCore();
        }
        return pInstance;
    };

    /**@~english
     * Gets the script type, for ScriptingCore, it will return `cocos2d::kScriptTypeJavascript`
     * @~chinese 
     * 获取脚本类型，它将返回`cocos2d::kScriptTypeJavascript`
     * @return `cocos2d::kScriptTypeJavascript`
     */
    virtual cocos2d::ccScriptType getScriptType() { return cocos2d::kScriptTypeJavascript; };

    /**
     * @brief @~english Removes the C++ object's linked JavaScript proxy object from JavaScript context
     * @~chinese 从JavaScript上下文中删除指定C++对象的JavaScript代理对象
     * @param obj @~english Object to be removed
     * @~chinese 需要被删除的对象
     */
    virtual void removeScriptObjectByObject(cocos2d::Ref* obj);

    /**
     * @brief @~english Useless in ScriptingCore, please use evalString
     * @~chinese 在ScriptingCore中无用，请使用evalString
     * @see evalString
     */
    virtual int executeString(const char* codes) { return 0; }

    /**
     * @brief @~english Pause scheduled tasks and actions for an object proxy.
     * @~chinese 暂停代理对象所指向的节点的所有任务和动作。
     * @param p @~english The object proxy
     * @~chinese 代理对象
     */
    void pauseSchedulesAndActions(js_proxy_t* p);
    /**
     * @brief @~english Resume scheduled tasks and actions for an object proxy.
     * @~chinese 恢复代理对象所指向的节点的所有任务和动作。
     * @param p @~english The object proxy
     * @~chinese 代理对象
     */
    void resumeSchedulesAndActions(js_proxy_t* p);
    /**
     * @brief @~english Cleanup scheduled tasks and actions for an object proxy.
     * @~chinese 清除代理对象所指向的节点的所有任务和动作。
     * @param p @~english The object proxy
     * @~chinese 代理对象
     */
    void cleanupSchedulesAndActions(js_proxy_t* p);

    /**
     * @brief @~english Useless in ScriptingCore, please use runScript
     * @~chinese 在ScriptingCore中无用,请使用runScript
     * @see runScript
     */
    virtual  int executeScriptFile(const char* filename) { return 0; }
    /**
     * @brief @~english Useless in ScriptingCore, please use executeFunctionWithOwner
     * @~chinese 在ScriptingCore中无用,请使用executeFunctionWithOwner
     * @see executeFunctionWithOwner
     */
    virtual int executeGlobalFunction(const char* functionName) { return 0; }

    virtual int sendEvent(cocos2d::ScriptEvent* message) override;
    virtual bool parseConfig(ConfigType type, const std::string& str) override;
    /**
     * @brief @~english Useless in ScriptingCore
     * @~chinese 在ScriptingCore中无用
     * @return @~english false
     * @~chinese false
     */
    virtual bool handleAssert(const char *msg) { return false; }

    virtual void setCalledFromScript(bool callFromScript) override { _callFromScript = callFromScript; };
    virtual bool isCalledFromScript() override { return _callFromScript; };
    
    /**
     * @brief @~english Execute a js function with a JavaScript object as parameter.
     * By passing a native object, ScriptingCore will found its JavaScript object with the proxy. 
     * Then the function will be invoked with the native object's js proxy as caller.
     * @~chinese 以一个JavaScript对象作为参数执行一个js函数。
     * 通过传递一个C++原生对象，ScriptingCore将会找到它的JavaScript代理对象。
     * 然后将使用代理对象作为js调用者调用指定的JS函数。
     * @param nativeObj @~english The caller object's C++ proxy.
     *                  @~chinese 调用者对象的c++代理对象。
     * @param name      @~english The function name.
     *                  @~chinese 函数的名字。
     * @param obj       @~english The JavaScript object as parameter.
     *                  @~chinese 作为参数的JavaScript对象。
     * @return @~english Return the js function's boolean result if successfully invoked, otherwise return false.
     * @~chinese 如果调用成功返回js函数的布尔结果，否则返回false。
     */
    bool executeFunctionWithObjectData(void* nativeObj, const char *name, JSObject *obj);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments count and arguments.
     * @~chinese 用一个JavaScript调用者，函数名，参数数量和参数执行一个js函数。
     * @param owner     @~english The caller object.
     *                  @~chinese 调用者对象。
     * @param name      @~english The function name.
     *                  @~chinese 函数的名字。
     * @param argc      @~english The arguments count.
     *                  @~chinese 参数数量。
     * @param vp        @~english The arguments.
     *                  @~chinese 参数。
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments count, arguments and a return value.
     * @~chinese 用一个JavaScript调用者，函数名，参数数量，参数和返回值执行一个js函数。
     * @param owner     @~english The caller object.
     *                  @~chinese 调用者对象。
     * @param name      @~english The function name.
     *                  @~chinese 函数的名字。
     * @param argc      @~english The arguments count.
     *                  @~chinese 参数数量。
     * @param vp        @~english The arguments.
     *                  @~chinese 参数。
     * @param retVal    @~english The js object to save the return value.
     *                  @~chinese 用来保存返回值的js对象。
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp, JS::MutableHandleValue retVal);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments array.
     * This is more reliable in js memory management
     * @~chinese 用一个JavaScript调用者，函数名和参数数组执行一个js函数。
     * 这对于js内存管理来说更加可靠
     * @param owner     @~english The caller object.
     *                  @~chinese 调用对象。
     * @param name      @~english The function name.
     *                  @~chinese 函数的名字。
     * @param args      @~english The arguments array.
     *                  @~chinese 参数数组。
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args);

    /**
     * @brief @~english Execute a js function with a JavaScript caller, function name, arguments array and a return value.
     * This is more reliable in js memory management
     * @~chinese 用一个JavaScript调用者，函数名，参数数组和一个返回值执行一个js函数。
     * 这对于js内存管理来说更加可靠
     * @param owner     @~english The caller object.
     *                  @~chinese 调用对象。
     * @param name      @~english The function name.
     *                  @~chinese 函数的名字。
     * @param args      @~english The arguments array.
     *                  @~chinese 参数数组。
     * @param retVal    @~english The js object to save the return value.
     *                  @~chinese 用来保存返回值的js对象。
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args, JS::MutableHandleValue retVal);

    /**
     * @brief @~english Execute a js function with a js this object and the js function object.
     * @~chinese 用js this对象和一个js函数对象执行这个js函数。
     * @param thisObj   @~english The js this object.
     *                  @~chinese js this对象。
     * @param callback  @~english The js function object.
     *                  @~chinese js函数对象。
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback);
    /**
     * @brief @~english Execute a js function with a js this object, the js function object, arguments and a return value.
     * @~chinese 用js this对象和一个js函数对象执行这个js函数。
     * @param thisObj   @~english The js this object.
     *                  @~chinese js this对象。
     * @param callback  @~english The js function object.
     *                  @~chinese js函数对象。
     * @param vp        @~english The arguments array.
     *                  @~chinese 参数数组。
     * @param retVal    @~english The js object to save the return value.
     *                  @~chinese 用来保存返回值的js对象。
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback, const JS::HandleValueArray& vp, JS::MutableHandleValue retVal);

    /**@~english
     * Evaluate the specified js code string
     * @~chinese 
     * 执行指定的JS代码字符串
     * @param string    @~english The string with the javascript code to be evaluated
     * @~chinese javascript代码的字符串
     * @param outVal    @~english The jsval that will hold the return value of the evaluation.
     * @~chinese 将用来保存返回值的jsval。
     * @param filename  @~english The filename
     * @~chinese 文件名
     * @param cx        @~english The js context
     * @~chinese js上下文对象
     * @param global    @~english The js global object
     * @~chinese js的全局对象
     * @return @~english Return true if successfully invoked, otherwise return false.
     * @~chinese 调用成功时返回true，否则返回false。
     */
    bool evalString(const char *string, jsval *outVal, const char *filename = NULL, JSContext* cx = NULL, JSObject* global = NULL);
    
    /**
     @brief @~english Get script object for the given path
     * @~chinese 为给定的js脚本路径获取脚本对象
     @param path @~english The script file path
     * @~chinese 脚本文件路径
     @return @~english Script object
     * @~chinese 脚本对象
     */
    JSScript* getScript(const char *path);

    /**@~english
     * Compile the specified js file
     * @~chinese 
     * 编译指定路径下的js文件
     * @param path    @~english The path of the script to to compiled
     * @~chinese 脚本文件的路径
     * @param global    @~english The js global object
     * @~chinese js的全局对象
     * @param cx        @~english The js context
     * @~chinese js上下文
     */
    void compileScript(const char *path, JSObject* global = NULL, JSContext* cx = NULL);

    /**@~english
     * Run the specified js file
     * @~chinese 
     * 执行指定的js文件
     * @param path @~english The path of the script to be executed
     * @~chinese 脚本文件的路径
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese 成功时返回true，否则返回false。
     */
    bool runScript(const char *path);
    /**@~english
     * Run the specified js file
     * @~chinese 
     * 执行指定的js文件
     * @param path @~english The path of the script to be executed
     * @~chinese 脚本文件的路径
     * @param global @~english The global object to execute the script
     * @~chinese 执行脚本的全局对象
     * @param global @~english The context to execute the script
     * @~chinese 执行脚本的js运行环境
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese 成功时返回true，否则返回false。
     */
    bool runScript(const char *path, JS::HandleObject global, JSContext* cx = NULL);

    /**@~english
     * Clean script object for the specified js file
     * @~chinese 
     * 清除js文件对应的脚本缓存对象
     * @param path @~english The path of the js file to be cleaned
     * @~chinese 脚本文件的路径
     */
    void cleanScript(const char *path);
    
    /**@~english
     * Gets the cached script objects for all executed js file
     * @~chinese 
     * 获取所有已执行的js文件的缓存脚本对象
     * @return @~english The cached script object map
     * @~chinese 缓存脚本对象表
     */
    std::unordered_map<std::string, JSScript*> &getFileScript();
    /**@~english
     * Clean all script objects
     * @~chinese 
     * 清除所有脚本对象缓存
     */
    void cleanAllScript();
    
    /**@~english
     * Initialize everything, including the js context, js global object etc.
     * @~chinese 
     * 初始化所有的东西，包括js上下文，js全局对象等。
     */
    void start();

    /**@~english
     * Cleanup everything, including script cache, js context, global object etc.
     * @~chinese 
     * 清除所有脚本对象缓存，js上下文，全局对象，等等。
     */
    void cleanup();

    /**@~english
     * Cleanup everything then initialize everything
     * @~chinese 
     * 清理然后重新初始化所有的一切
     */
    void reset();

    /**@~english
     * Add the register_sth callback to the list of functions that need to be called after the creation of the context.
     * It's normally used to register script bindings in the js context for bound classes
     * @~chinese 
     * 添加register_sth回调函数到列表中，列表中的所有回调都会在js上下文创建后被调用。
     * 它通常用于将已绑定的类注册到js上下文中。
     * @param callback @~english The callback to register something to the js context
     * @~chinese 用于注册绑定的回调函数
     */
    void addRegisterCallback(sc_register_sth callback);

    /**@~english
     * Create a new context. If one is already there, it will destroy the old context and create a new one.
     * @~chinese 
     * 创建一个新的js上下文。如果一个旧的上下文已经存在，它将摧毁旧的上下文并创建一个新的。
     */
    void createGlobalContext();

    /**@~english
     * Removes all rooted object in the given js context, rooted object won't be garbage collected.
     * @~chinese 
     * 在给定的js环境中删除所有的根对象，根对象不会被垃圾回收机制回收。
     * @param cx @~english The js context
     * @~chinese js上下文
     */
    static void removeAllRoots(JSContext *cx);

    /**@~english
     * Simulate a touch event and dispatch it to a js object.
     * @~chinese 
     * 模拟一个触摸事件，并将其分派到一个javascript对象。
     * @param eventType @~english The touch event type
     * @~chinese 触摸事件类型
     * @param pTouch @~english The touch object
     * @~chinese 触点对象
     * @param obj @~english The js object
     * @~chinese js对象
     * @param retval @~english The return value of the touch event callback
     * @~chinese 触摸事件回调的返回值
     * @return @~english Return 1 if succeed, otherwise return 0.
     * @~chinese 如果成功,返回1,否则返回0。
     */
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj, JS::MutableHandleValue retval);
    /**@~english
     * Simulate a touch event and dispatch it to a js object.
     * @~chinese 
     * 模拟一个触摸事件，并将其分派到一个javascript对象。
     * @param eventType @~english The touch event type
     * @~chinese 触摸事件类型
     * @param pTouch @~english The touch object
     * @~chinese 触点对象
     * @param obj @~english The js object
     * @~chinese js对象
     * @return @~english Return 1 if succeed, otherwise return 0.
     * @~chinese 如果成功,返回1,否则返回0。
     */
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj);
    /**@~english
     * Simulate a multi touch event and dispatch it to a js object.
     * @~chinese 
     * 模拟一个多点触摸事件，并将其分派到一个javascript对象。
     * @param eventType @~english The touch event type
     * @~chinese 触摸事件类型
     * @param touches @~english Touchs list for multitouch
     * @~chinese 多点触点对象
     * @param obj @~english The js object
     * @~chinese js对象
     * @return @~english Return 1 if succeed, otherwise return 0.
     * @~chinese 如果成功,返回1,否则返回0。
     */
    int executeCustomTouchesEvent(cocos2d::EventTouch::EventCode eventType,
                                  const std::vector<cocos2d::Touch*>& touches, JSObject *obj);
    /**@~english
     * Gets the current global context.
     * @~chinese 
     * 获取当前全局js上下文。
     * @return @~english the global context
     * @~chinese 全局js上下文
     */
    JSContext* getGlobalContext() {
        return _cx;
    };

    /**@~english
     * Report an error in the js context
     * @~chinese 
     * 在js上下文报告一个错误
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param message @~english The error message
     * @~chinese 错误消息
     * @param report @~english The js error report object
     * @~chinese js错误报告对象
     */
    static void reportError(JSContext *cx, const char *message, JSErrorReport *report);

    /**@~english
     * Log something to the js context using CCLog.
     * @~chinese 
     * 在js上下文打印一个log信息
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese 成功时返回true，否则返回false。
     */
    static bool log(JSContext *cx, uint32_t argc, jsval *vp);

    /**@~english
     * Sets a js value to the targeted js obejct's reserved slot, which is not exposed to script environment.
     * @~chinese 
     * 设置一个js值到目标js对象的预留存储槽，这些值将不会被暴露于脚本环境。
     * @param i @~english The slot index
     * @~chinese 存储槽位置索引
     * @param obj @~english The targeted object
     * @~chinese 目标对象
     * @param value @~english The js value to set to the slot
     * @~chinese 需要被存储的js值
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese 成功时返回true，否则返回false。
     */
    bool setReservedSpot(uint32_t i, JSObject *obj, jsval value);

    /**@~english
     * Runs a script from script environment, it should be invoked from script environment
     * Bound to `__jsc__.executeScript` and `window.executeScript`
     * @~chinese 
     * 从脚本环境中运行一个脚本，它应该从脚本中被调用
     * 被绑定到`__jsc__.executeScript`和`window.executeScript`
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     * @return @~english Return true if succeed, otherwise return false.
     * @~chinese 成功时返回true，否则返回false。
     */
    static bool executeScript(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Forces a cycle of garbage collection, it should be invoked from script environment
     * Bound to `__jsc__.garbageCollect` and `window.garbageCollect`
     * @~chinese 
     * 强制执行一次垃圾回收，它应该从脚本中被调用
     * 绑定到`__jsc__.garbageCollect`和`window.garbageCollect`
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     */
    static bool forceGC(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Dump all named rooted objects, it should be invoked from script environment
     * Bound to `__jsc__.dumpRoot`
     * @~chinese 
     * 打印所有有名根对象，它应该从脚本中被调用
     * 绑定到`__jsc__.dumpRoot`
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     */
    static bool dumpRoot(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Adds a js object to root so that it won't be touched by the garbage collection, it should be invoked from script environment
     * Bound to `__jsc__.addGCRootObject`
     * @~chinese 
     * 添加一个js对象到根内存中，这样它就不会被垃圾回收机制所影响。它应该从脚本中被调用
     * 绑定到`__jsc__.addGCRootObject`
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     */
    static bool addRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Removes a js object from root, it should be invoked from script environment
     * Bound to `__jsc__.removeGCRootObject`
     * @~chinese 
     * 从根内存中删除一个js，它应该从脚本中被调用
     * 绑定到`__jsc__.removeGCRootObject`
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     */
    static bool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    /**@~english
     * Check whether a js object's C++ proxy is still valid, it should be invoked from script environment
     * Bound to `window.__isObjectValid`
     * @~chinese 
     * 检查一个js对象的c++代理是否仍然有效，它应该从脚本中被调用
     * 绑定到`window.__isObjectValid`
     * @param cx @~english The js context
     * @~chinese js上下文
     * @param argc @~english The arguments count
     * @~chinese 参数数量
     * @param vp @~english The arguments
     * @~chinese 参数
     */
    static bool isObjectValid(JSContext *cx, uint32_t argc, jsval *vp);

    /**@~english
     * Log a string to the debug environment.
     * Enable the debug environment so that it can be invoked.
     * @~chinese 
     * 打印一个字符串到调试环境。
     * 启用调试环境，以便它可以被调用。
     * @param str @~english The message to log
     * @~chinese 消息日志
     */
    void debugProcessInput(const std::string& str);
    /**@~english
     * Enable the debug environment, mozilla Firefox's remote debugger or Code IDE can connect to it.
     * @~chinese 
     * 启用调试环境，mozilla Firefox的远程调试器或Code IDE可以连接它。
     * @param port @~english The port to connect with the debug enviroment, default value is 5086
     * @~chinese 调试环境连接端口，默认值是5086
     */
    void enableDebugger(unsigned int port = 5086);
    /**@~english
     * Gets the debug environment's global object
     * @~chinese 
     * 获取调试环境的全局对象
     * @return @~english The debug environment's global object
     * @~chinese 调试环境的全局对象
     */
    JSObject* getDebugGlobal() { return _debugGlobal.ref().get(); }
    /**@~english
     * Gets the global object
     * @~chinese 
     * 获取全局对象
     * @return @~english The global object
     * @~chinese 全局对象
     */
    JSObject* getGlobalObject() { return _global.ref().get(); }

    /**@~english
     * Checks whether a C++ function is overrided in js prototype chain
     * @~chinese 
     * 检查一个c++函数是否在js继承链中被覆盖
     * @param obj @~english The js object
     * @~chinese js对象
     * @param name @~english The function name
     * @~chinese 函数名
     * @param native @~english The native function
     * @~chinese 原生C++函数
     * @return @~english The global object
     * @~chinese 全局对象
     */
    bool isFunctionOverridedInJS(JS::HandleObject obj, const std::string& name, JSNative native);
    
private:
    void string_report(JS::HandleValue val);
    void initRegister();

public:
    int handleNodeEvent(void* data);
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

js_proxy_t* jsb_new_proxy(void* nativeObj, JSObject* jsObj);
js_proxy_t* jsb_get_native_proxy(void* nativeObj);
js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);
void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy);

template <class T>
jsval getJSObject(JSContext* cx, T* nativeObj)
{
    js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, nativeObj);
    return proxy ? OBJECT_TO_JSVAL(proxy->obj) : JSVAL_NULL;
}

void removeJSObject(JSContext* cx, void* nativeObj);

/**@~english
 * // JSB
 * @}
 * @~chinese 
 * / / JSB
 * @ }
 */

#endif /* __SCRIPTING_CORE_H__ */
