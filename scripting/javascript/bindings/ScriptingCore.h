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

void js_log(const char *format, ...);

using namespace cocos2d;
using namespace std;

typedef void (*sc_register_sth)(JSContext* cx, JSObject* global);

void registerDefaultClasses(JSContext* cx, JSObject* global);


class SimpleRunLoop : public Object
{
public:
	void update(float d);
};

class ScriptingCore : public ScriptEngineProtocol
{
	JSRuntime *rt_;
	JSContext *cx_;
	JSObject  *global_;
	JSObject  *debugGlobal_;
	SimpleRunLoop* runLoop;

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
     @brief Remove Object from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByObject(Object* pObj);

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

    virtual int sendEvent(ScriptEvent* message) override;

    virtual bool handleAssert(const char *msg) { return false; }

    bool executeFunctionWithObjectData(Node *self, const char *name, JSObject *obj);
    JSBool executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc = 0, jsval* vp = NULL, jsval* retVal = NULL);

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


    int executeCustomTouchEvent(int eventType,
                                Touch *pTouch, JSObject *obj, jsval &retval);
    int executeCustomTouchEvent(int eventType,
                                Touch *pTouch, JSObject *obj);
    int executeCustomTouchesEvent(int eventType,
                                  Set *pTouches, JSObject *obj);
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

	/**
	 * enable the debug environment
	 */
	void debugProcessInput(string str);
	void enableDebugger();
	JSObject* getDebugGlobal() { return debugGlobal_; }
    JSObject* getGlobalObject() { return global_; }
    
 private:
    void string_report(jsval val);
    
    int handleTouchesEvent(void* data);
    int handleTouchEvent(void* data);
    int handleNodeEvent(void* data);
    int handleMenuClickedEvent(void* data);
    int handleAccelerometerEvent(void* data);
    int handleKeypadEvent(void* data);
};

// some utility functions
// to native
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *ret );
JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *ret );
JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *ret );
JSBool jsval_to_long_long(JSContext *cx, jsval v, long long* ret);
JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret);
JSBool jsval_to_ccpoint(JSContext *cx, jsval v, Point* ret);
JSBool jsval_to_ccrect(JSContext *cx, jsval v, Rect* ret);
JSBool jsval_to_ccsize(JSContext *cx, jsval v, Size* ret);
JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, Color4B* ret);
JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, Color4F* ret);
JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, Color3B* ret);
JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, Point **points, int *numPoints);
JSBool jsval_to_ccarray(JSContext* cx, jsval v, Array** ret);
JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, Dictionary** ret);
JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, Acceleration* ret);
JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, Array** ret);
JSBool jsval_to_ccaffinetransform(JSContext* cx, jsval v, AffineTransform* ret);
JSBool jsval_to_FontDefinition( JSContext *cx, jsval vp, FontDefinition* ret );

// from native
jsval int32_to_jsval( JSContext *cx, int32_t l);
jsval uint32_to_jsval( JSContext *cx, uint32_t number );
jsval long_long_to_jsval(JSContext* cx, long long v);
jsval std_string_to_jsval(JSContext* cx, const string& v);
jsval c_string_to_jsval(JSContext* cx, const char* v, size_t length = -1);
jsval ccpoint_to_jsval(JSContext* cx, const Point& v);
jsval ccrect_to_jsval(JSContext* cx, const Rect& v);
jsval ccsize_to_jsval(JSContext* cx, const Size& v);
jsval cccolor4b_to_jsval(JSContext* cx, const Color4B& v);
jsval cccolor4f_to_jsval(JSContext* cx, const Color4F& v);
jsval cccolor3b_to_jsval(JSContext* cx, const Color3B& v);
jsval ccdictionary_to_jsval(JSContext* cx, Dictionary *dict);
jsval ccarray_to_jsval(JSContext* cx, Array *arr);
jsval ccacceleration_to_jsval(JSContext* cx, const Acceleration& v);
jsval ccaffinetransform_to_jsval(JSContext* cx, const AffineTransform& t);
jsval FontDefinition_to_jsval(JSContext* cx, const FontDefinition& t);

JSObject* NewGlobalObject(JSContext* cx, bool debug = false);
JSBool jsStartDebugger(JSContext* cx, unsigned argc, jsval* vp);
JSBool jsGetScript(JSContext* cx, unsigned argc, jsval* vp);

JSBool JSBDebug_StartDebugger(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_BufferRead(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_BufferWrite(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_LockExecution(JSContext* cx, unsigned argc, jsval* vp);
JSBool JSBDebug_UnlockExecution(JSContext* cx, unsigned argc, jsval* vp);

// just a simple utility to avoid mem leaking when using JSString
class JSStringWrapper
{
	JSString*	string;
	const char*	buffer;
public:
	JSStringWrapper() {
		buffer = NULL;
	}
	JSStringWrapper(JSString* str, JSContext* cx = NULL) {
		set(str, cx);
	}
	JSStringWrapper(jsval val, JSContext* cx = NULL) {
		set(val, cx);
	}
	~JSStringWrapper() {
		if (buffer) {
			//JS_free(ScriptingCore::getInstance()->getGlobalContext(), (void*)buffer);
            delete[] buffer;
		}
	}
	void set(jsval val, JSContext* cx) {
		if (val.isString()) {
			this->set(val.toString(), cx);
		} else {
			buffer = NULL;
		}
	}
	void set(JSString* str, JSContext* cx) {
		string = str;
		if (!cx) {
			cx = ScriptingCore::getInstance()->getGlobalContext();
            
		}
        // JS_EncodeString isn't supported in SpiderMonkey ff19.0.
        //buffer = JS_EncodeString(cx, string);
        unsigned short* pStrUTF16 = (unsigned short*)JS_GetStringCharsZ(cx, str);
        buffer = cc_utf16_to_utf8(pStrUTF16, -1, NULL, NULL);
	}
	std::string get() {
        return buffer;
    }

	operator std::string() {
		return std::string(buffer);
	}
	operator char*() {
		return (char*)buffer;
	}
private:
	/* Copy and assignment are not supported. */
    JSStringWrapper(const JSStringWrapper &another);
    JSStringWrapper &operator=(const JSStringWrapper &another);
};

// wraps a function and "this" object
class JSFunctionWrapper
{
    JSContext *_cx;
    JSObject *_jsthis;
    jsval _fval;
public:
    JSFunctionWrapper(JSContext* cx, JSObject *jsthis, jsval fval)
    : _cx(cx)
    , _jsthis(jsthis)
    , _fval(fval)
    {
        JS_AddNamedValueRoot(cx, &this->_fval, "JSFunctionWrapper");
        JS_AddNamedObjectRoot(cx, &this->_jsthis, "JSFunctionWrapper");
    }
    ~JSFunctionWrapper() {
        JS_RemoveValueRoot(this->_cx, &this->_fval);
        JS_RemoveObjectRoot(this->_cx, &this->_jsthis);
    }
    JSBool invoke(unsigned int argc, jsval *argv, jsval &rval) {
        return JS_CallFunctionValue(this->_cx, this->_jsthis, this->_fval, argc, argv, &rval);
    }
private:
    /* Copy and assignment are not supported. */
    JSFunctionWrapper(const JSFunctionWrapper &another);
    JSFunctionWrapper &operator=(const JSFunctionWrapper &another);
};

JSBool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value);
JSBool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret);

js_proxy_t* jsb_new_proxy(void* nativeObj, JSObject* jsObj);
js_proxy_t* jsb_get_native_proxy(void* nativeObj);
js_proxy_t* jsb_get_js_proxy(JSObject* jsObj);
void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy);


#endif /* __SCRIPTING_CORE_H__ */
