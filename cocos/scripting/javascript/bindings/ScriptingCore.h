//
//  ScriptingCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef __SCRIPTING_CORE_H__
#define __SCRIPTING_CORE_H__

#include <assert.h>
#include <memory>
#include "cocos2d.h"
#include "js_bindings_config.h"
#include "js_bindings_core.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#include "spidermonkey_specifics.h"
#include "js_manual_conversions.h"

void js_log(const char *format, ...);

typedef void (*sc_register_sth)(JSContext* cx, JSObject* global);

void registerDefaultClasses(JSContext* cx, JSObject* global);


class SimpleRunLoop : public cocos2d::Object
{
public:
	void update(float d);
};

class ScriptingCore : public cocos2d::ScriptEngineProtocol
{
	JSRuntime *_rt;
	JSContext *_cx;
	JSObject  *_global;
	JSObject  *_debugGlobal;
	SimpleRunLoop* _runLoop;

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
    virtual void removeScriptObjectByObject(cocos2d::Object* pObj);

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

    bool executeFunctionWithObjectData(cocos2d::Node *self, const char *name, JSObject *obj);
    JSBool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc = 0, jsval* vp = NULL, jsval* retVal = NULL);

    void executeJSFunctionWithThisObj(jsval thisObj, jsval callback, uint32_t argc = 0, jsval* vp = NULL, jsval* retVal = NULL);

	/**
	 * will eval the specified string
	 * @param string The string with the javascript code to be evaluated
	 * @param outVal The jsval that will hold the return value of the evaluation.
	 * Can be NULL.
	 */
	JSBool evalString(const char *string, jsval *outVal, const char *filename = NULL, JSContext* cx = NULL, JSObject* global = NULL);

	/**
	 * will run the specified string
	 * @param string The path of the script to be run
	 */
	JSBool runScript(const char *path, JSObject* global = NULL, JSContext* cx = NULL);

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
                                cocos2d::Touch *pTouch, JSObject *obj, jsval &retval);
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
	static JSBool log(JSContext *cx, uint32_t argc, jsval *vp);

	JSBool setReservedSpot(uint32_t i, JSObject *obj, jsval value);

	/**
	 * run a script from script :)
	 */
	static JSBool executeScript(JSContext *cx, uint32_t argc, jsval *vp);

	/**
	 * Force a cycle of GC
	 * @param cx
	 * @param argc
	 * @param vp
	 */
	static JSBool forceGC(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool dumpRoot(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool addRootJS(JSContext *cx, uint32_t argc, jsval *vp);
	static JSBool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp);

	/**
	 * enable the debug environment
	 */
	void debugProcessInput(const std::string& str);
	void enableDebugger();
	JSObject* getDebugGlobal() { return _debugGlobal; }
    JSObject* getGlobalObject() { return _global; }
    
 private:
    void string_report(jsval val);
    
    int handleTouchesEvent(void* data);
    int handleTouchEvent(void* data);
    int handleNodeEvent(void* data);
    int handleMenuClickedEvent(void* data);
    int handleAccelerometerEvent(void* data);
    int handleKeypadEvent(void* data);
};

JSObject* NewGlobalObject(JSContext* cx, bool debug = false);

JSBool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value);
JSBool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret);

js_proxy_t* jsb_new_proxy(void* nativeObj, JSObject* jsObj);
js_proxy_t* jsb_get_native_proxy(void* nativeObj);
js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);
void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy);


#endif /* __SCRIPTING_CORE_H__ */
