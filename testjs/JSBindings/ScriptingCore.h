//
//  ScriptingCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef cocos2dx_ScriptingCore_h
#define cocos2dx_ScriptingCore_h

#include "jsapi.h"
#include "cocos2d.h"

class ScriptingCore
{
	JSRuntime *rt;
	JSContext *cx;
	JSObject  *global;

	ScriptingCore();
public:
	~ScriptingCore();

	static ScriptingCore & getInstance() {
		static ScriptingCore instance;
		return instance;
	};

	/**
	 * will eval the specified string
	 * @param string The string with the javascript code to be evaluated
	 */
	void evalString(const char *string);

	/**
	 * will run the specified string
	 * @param string The path of the script to be run
	 */
	void runScript(const char *path);

	/**
	 * @return the global context
	 */
	JSContext* getGlobalContext() {
		return cx;
	};

	/**
	 * @param cx
	 * @param message
	 * @param report
	 */
	static void reportError(JSContext *cx, const char *message, JSErrorReport *report)
	{
		fprintf(stderr, "%s:%u:%s\n",  
				report->filename ? report->filename : "<no filename=\"filename\">",  
				(unsigned int) report->lineno,  
				message);
	};

	/**
	 * Log something using CCLog
	 * @param cx
	 * @param argc
	 * @param vp
	 */
	static JSBool log(JSContext *cx, uint32_t argc, jsval *vp)
	{
		if (argc > 0) {
			JSString *string = NULL;
			JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string);
			if (string) {
				char *cstr = JS_EncodeString(cx, string);
				cocos2d::CCLog(cstr);
			}
		}
		return JS_TRUE;
	};

	/**
	 * Register an object as a member of the GC's root set, preventing
	 * them from being GC'ed
	 */
	static JSBool addRootJS(JSContext *cx, uint32_t argc, jsval *vp)
	{
		if (argc == 1) {
			JSObject *o = NULL;
			if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == JS_TRUE) {
				if (JS_AddObjectRoot(cx, &o) == JS_FALSE) {
					cocos2d::CCLog("something went wrong when setting an object to the root");
				}
			}
		}
		return JS_TRUE;
	};

	/**
	 * removes an object from the GC's root, allowing them to be GC'ed if no
	 * longer referenced.
	 */
	static JSBool removeRootJS(JSContext *cx, uint32_t argc, jsval *vp)
	{
		if (argc == 1) {
			JSObject *o = NULL;
			if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == JS_TRUE) {
				JS_RemoveObjectRoot(cx, &o);
			}
		}
		return JS_TRUE;
	};

	/**
	 * Force a cycle of GC
	 * @param cx
	 * @param argc
	 * @param vp
	 */
	static JSBool forceGC(JSContext *cx, uint32_t argc, jsval *vp)
	{
		JS_GC(cx);
		return JS_TRUE;
	};
};

#endif
