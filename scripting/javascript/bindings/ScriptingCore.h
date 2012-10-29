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
#include "cocos2d.h"
#include "uthash.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#include "spidermonkey_specifics.h"

void js_log(const char *format, ...);

using namespace cocos2d;

typedef void (*sc_register_sth)(JSContext* cx, JSObject* global);

void registerDefaultClasses(JSContext* cx, JSObject* global);

class ScriptingCore : public CCScriptEngineProtocol
{
	JSRuntime *rt_;
	JSContext *cx_;
	JSObject  *global_;
	
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

    virtual ccScriptType getScriptType() { return kScriptTypeJavascript; };
    
    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByCCObject(CCObject* pObj);

    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
	virtual int executeString(const char* codes) { return 0; }
    void pauseSchedulesAndActions(CCNode *node);
    void resumeSchedulesAndActions(CCNode *node);
    void cleanupSchedulesAndActions(CCNode *node);

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

    virtual int executeNodeEvent(CCNode* pNode, int nAction);
    virtual int executeMenuItemEvent(CCMenuItem* pMenuItem);
    virtual int executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName);
    virtual int executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget = NULL);
    virtual int executeSchedule(CCTimer* pTimer, float dt, CCNode* pNode = NULL);
    virtual int executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches);
    virtual int executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch);

    int executeFunctionWithObjectData(CCNode *self, const char *name, JSObject *obj);
    int executeFunctionWithOwner(jsval owner, const char *name, jsval data);
    
    void executeJSFunctionWithThisObj(jsval thisObj, jsval callback, jsval *data);

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
	
    
    int executeCustomTouchEvent(int eventType, 
                                CCTouch *pTouch, JSObject *obj, jsval &retval);
    int executeCustomTouchEvent(int eventType, 
                                CCTouch *pTouch, JSObject *obj);
    int executeCustomTouchesEvent(int eventType, 
                                  CCSet *pTouches, JSObject *obj);
	/**
	 * @return the global context
	 */
	JSContext* getGlobalContext() {
		return cx_;
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

 private:
    void string_report(jsval val);
};

// some utility functions
// to native
long long jsval_to_long_long(JSContext *cx, jsval v);
std::string jsval_to_std_string(JSContext *cx, jsval v);
// you should free this pointer after you're done with it
const char* jsval_to_c_string(JSContext *cx, jsval v);
CCPoint jsval_to_ccpoint(JSContext *cx, jsval v);
CCRect jsval_to_ccrect(JSContext *cx, jsval v);
CCSize jsval_to_ccsize(JSContext *cx, jsval v);
ccGridSize jsval_to_ccgridsize(JSContext *cx, jsval v);
ccColor4B jsval_to_cccolor4b(JSContext *cx, jsval v);
ccColor4F jsval_to_cccolor4f(JSContext *cx, jsval v);
ccColor3B jsval_to_cccolor3b(JSContext *cx, jsval v);
JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, CCPoint **points, int *numPoints);
CCArray* jsval_to_ccarray(JSContext* cx, jsval v);
jsval ccarray_to_jsval(JSContext* cx, CCArray *arr);
// from native
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval std_string_to_jsval(JSContext* cx, std::string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v);
jsval ccpoint_to_jsval(JSContext* cx, CCPoint& v);
jsval ccrect_to_jsval(JSContext* cx, CCRect& v);
jsval ccsize_to_jsval(JSContext* cx, CCSize& v);
jsval ccgridsize_to_jsval(JSContext* cx, ccGridSize& v);
jsval cccolor4b_to_jsval(JSContext* cx, ccColor4B& v);
jsval cccolor4f_to_jsval(JSContext* cx, ccColor4F& v);
jsval cccolor3b_to_jsval(JSContext* cx, const ccColor3B& v);

JSObject* NewGlobalObject(JSContext* cx);
JSBool jsNewGlobal(JSContext* cx, unsigned argc, jsval* vp);

JSBool jsSocketOpen(JSContext* cx, unsigned argc, jsval* vp);
JSBool jsSocketRead(JSContext* cx, unsigned argc, jsval* vp);
JSBool jsSocketWrite(JSContext* cx, unsigned argc, jsval* vp);
JSBool jsSocketClose(JSContext* cx, unsigned argc, jsval* vp);

#endif
