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

/* Since there is an ugly bug in spiderMonkey-win32(cocos2d-2.0-rc0a), we updated spiderMonkey to v1.8.5 to resolve it.
    But the api is a little different from the old version, so we define two marco here.
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
typedef unsigned int uint32_t;
typedef int int32_t;

#define JS_GetPrivate(obj) JS_GetPrivate(cx, obj)
#define JS_SetPrivate(obj, data) JS_SetPrivate(cx, obj, data)

#endif

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
     * @param outVal The jsval that will hold the return value of the evaluation.
     * Can be NULL.
     */
    bool evalString(const char *string, jsval *outVal);

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
     * run a script from script :)
     */
    static JSBool executeScript(JSContext *cx, uint32_t argc, jsval *vp)
    {
        if (argc == 1) {
            JSString *string;
            if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string) == JS_TRUE) {
                ScriptingCore::getInstance().runScript(JS_EncodeString(cx, string));
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
