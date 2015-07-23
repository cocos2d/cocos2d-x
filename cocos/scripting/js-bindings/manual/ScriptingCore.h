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

#include <assert.h>
#include <memory>

#define ENGINE_VERSION "Cocos2d-JS v3.7"

void js_log(const char *format, ...);

typedef void (*sc_register_sth)(JSContext* cx, JS::HandleObject global);

void registerDefaultClasses(JSContext* cx, JS::HandleObject global);


class SimpleRunLoop : public cocos2d::Ref
{
public:
    void update(float d);
};

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

    static ScriptingCore *getInstance() {
        static ScriptingCore* pInstance = NULL;
        if (pInstance == NULL) {
            pInstance = new ScriptingCore();
        }
        return pInstance;
    };

    virtual cocos2d::ccScriptType getScriptType() { return cocos2d::kScriptTypeJavascript; };

    /**
     @brief Remove Object from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByObject(cocos2d::Ref* obj);

    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes) { return 0; }
    void pauseSchedulesAndActions(js_proxy_t* p);
    void resumeSchedulesAndActions(js_proxy_t* p);
    void cleanupSchedulesAndActions(js_proxy_t* p);

    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual  int executeScriptFile(const char* filename) { return 0; }

    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName) { return 0; }

    virtual int sendEvent(cocos2d::ScriptEvent* message) override;
    
    virtual bool parseConfig(ConfigType type, const std::string& str) override;

    virtual bool handleAssert(const char *msg) { return false; }

    virtual void setCalledFromScript(bool callFromScript) { _callFromScript = callFromScript; };
    virtual bool isCalledFromScript() { return _callFromScript; };
    
    bool executeFunctionWithObjectData(void* nativeObj, const char *name, JSObject *obj);

    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp);
    bool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp, JS::MutableHandleValue retVal);
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args);
    bool executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args, JS::MutableHandleValue retVal);

    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback);
    void executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback, const JS::HandleValueArray& vp, JS::MutableHandleValue retVal);

    /**
     * will eval the specified string
     * @param string The string with the javascript code to be evaluated
     * @param outVal The jsval that will hold the return value of the evaluation.
     * Can be NULL.
     */
    bool evalString(const char *string, jsval *outVal, const char *filename = NULL, JSContext* cx = NULL, JSObject* global = NULL);
    
    /**
     @brief get script object for the given path
     @param given script path
     @return script object
     */
    JSScript* getScript(const char *path);

    /**
     * will compile the specified string
     * @param string The path of the script to be run
     */
    void compileScript(const char *path, JSObject* global = NULL, JSContext* cx = NULL);

    /**
     * will run the specified string
     * @param string The path of the script to be run
     */
    bool runScript(const char *path);
    bool runScript(const char *path, JS::HandleObject global, JSContext* cx = NULL);

    /**
     * will clean script object the specified string
     */
    void cleanScript(const char *path);
    
    std::unordered_map<std::string, JSScript*> &getFileScript();
     /**
     * will clean all script object
     */
    void cleanAllScript();
    
    /**
     * initialize everything
     */
    void start();

    /**
     * cleanup everything
     */
    void cleanup();

    /**
     * cleanup everything then initialize everything
     */
    void reset();

    /**
     * will add the register_sth callback to the list of functions that need to be called
     * after the creation of the context
     */
    void addRegisterCallback(sc_register_sth callback);

    /**
     * Will create a new context. If one is already there, it will destroy the old context
     * and create a new one.
     */
    void createGlobalContext();

    static void removeAllRoots(JSContext *cx);


    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj, JS::MutableHandleValue retval);
    int executeCustomTouchEvent(cocos2d::EventTouch::EventCode eventType,
                                cocos2d::Touch *pTouch, JSObject *obj);
    int executeCustomTouchesEvent(cocos2d::EventTouch::EventCode eventType,
                                  const std::vector<cocos2d::Touch*>& touches, JSObject *obj);
    /**
     * @return the global context
     */
    JSContext* getGlobalContext() {
        return _cx;
    };

    /**
     * @param cx
     * @param message
     * @param report
     */
    static void reportError(JSContext *cx, const char *message, JSErrorReport *report);

    /**
     * Log something using CCLog
     * @param cx
     * @param argc
     * @param vp
     */
    static bool log(JSContext *cx, uint32_t argc, jsval *vp);

    bool setReservedSpot(uint32_t i, JSObject *obj, jsval value);

    /**
     * run a script from script :)
     */
    static bool executeScript(JSContext *cx, uint32_t argc, jsval *vp);

    /**
     * Force a cycle of GC
     * @param cx
     * @param argc
     * @param vp
     */
    static bool forceGC(JSContext *cx, uint32_t argc, jsval *vp);
    static bool dumpRoot(JSContext *cx, uint32_t argc, jsval *vp);
    static bool addRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    static bool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp);
    
    static bool isObjectValid(JSContext *cx, uint32_t argc, jsval *vp);

    /**
     * enable the debug environment
     */
    void debugProcessInput(const std::string& str);
    void enableDebugger(unsigned int port = 5086);
    JSObject* getDebugGlobal() { return _debugGlobal.ref().get(); }
    JSObject* getGlobalObject() { return _global.ref().get(); }

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

#endif /* __SCRIPTING_CORE_H__ */
