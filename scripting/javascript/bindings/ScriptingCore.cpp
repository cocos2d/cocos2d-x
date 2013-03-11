//
//  ScriptingCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include "ScriptingCore.h"
#include "jsdbgapi.h"
#include "cocos2d.h"
#include "LocalStorage.h"
#include "cocos2d_specifics.hpp"
#include "js_bindings_config.h"
// for debug socket
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#endif
#include <pthread.h>

#ifdef ANDROID
#include <android/log.h>
#include <jni/JniHelper.h>
#include <netinet/in.h>
#endif

#ifdef ANDROID
#define  LOG_TAG    "ScriptingCore.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) js_log(__VA_ARGS__)
#endif

#include "js_bindings_config.h"



pthread_t debugThread;
string inData;
string outData;
vector<string> queue;
pthread_mutex_t g_qMutex;
pthread_mutex_t g_rwMutex;
bool vmLock = false;
jsval frame = JSVAL_NULL, script = JSVAL_NULL;
int clientSocket;

// server entry point for the bg thread
void* serverEntryPoint(void*);

js_proxy_t *_native_js_global_ht = NULL;
js_proxy_t *_js_native_global_ht = NULL;
js_type_class_t *_js_global_type_ht = NULL;
char *_js_log_buf = NULL;

std::vector<sc_register_sth> registrationList;

// name ~> JSScript map
std::map<std::string, JSScript*> filename_script;
// port ~> socket map
std::map<int,int> ports_sockets;
// name ~> globals
std::map<std::string, js::RootedObject*> globals;

static void executeJSFunctionFromReservedSpot(JSContext *cx, JSObject *obj,
                                              jsval &dataVal, jsval &retval) {

    jsval func = JS_GetReservedSlot(obj, 0);

    if(func == JSVAL_VOID) { return; }
    jsval thisObj = JS_GetReservedSlot(obj, 1);
    JSAutoCompartment ac(cx, obj);
    if(thisObj == JSVAL_VOID) {
        JS_CallFunctionValue(cx, obj, func, 1, &dataVal, &retval);
    } else {
        assert(!JSVAL_IS_PRIMITIVE(thisObj));
        JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(thisObj), func, 1, &dataVal, &retval);
    }
}

static void getTouchesFuncName(int eventType, std::string &funcName) {
    switch(eventType) {
        case CCTOUCHBEGAN:
            funcName = "onTouchesBegan";
            break;
        case CCTOUCHENDED:
            funcName = "onTouchesEnded";
            break;
        case CCTOUCHMOVED:
            funcName = "onTouchesMoved";
            break;
        case CCTOUCHCANCELLED:
            funcName = "onTouchesCancelled";
            break;
    }

}

static void getTouchFuncName(int eventType, std::string &funcName) {
    switch(eventType) {
        case CCTOUCHBEGAN:
            funcName = "onTouchBegan";
            break;
        case CCTOUCHENDED:
            funcName = "onTouchEnded";
            break;
        case CCTOUCHMOVED:
            funcName = "onTouchMoved";
            break;
        case CCTOUCHCANCELLED:
            funcName = "onTouchCancelled";
            break;
    }

}

static void rootObject(JSContext *cx, JSObject *obj) {
    JS_AddNamedObjectRoot(cx, &obj, "unnamed");
}


static void unRootObject(JSContext *cx, JSObject *obj) {
    JS_RemoveObjectRoot(cx, &obj);
}

static void getJSTouchObject(JSContext *cx, CCTouch *x, jsval &jsret) {
    js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCTouch>(cx, x);
    jsret = OBJECT_TO_JSVAL(proxy->obj);
}

static void removeJSTouchObject(JSContext *cx, CCTouch *x, jsval &jsret) {
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    void *ptr = (void*)x;
    JS_GET_PROXY(nproxy, ptr);
    if (nproxy) {
        JS_GET_NATIVE_PROXY(jsproxy, nproxy->obj);
        JS_RemoveObjectRoot(cx, &jsproxy->obj);
        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}

void ScriptingCore::executeJSFunctionWithThisObj(jsval thisObj, jsval callback,
                                                 jsval *data) {
    jsval retval;
    if(callback != JSVAL_VOID || thisObj != JSVAL_VOID) {
        JS_CallFunctionValue(cx_, JSVAL_TO_OBJECT(thisObj), callback, 1, data, &retval);
    }
}


static void executeJSFunctionWithName(JSContext *cx, JSObject *obj,
                                      const char *funcName, jsval &dataVal,
                                      jsval &retval) {
    JSBool hasAction;
    jsval temp_retval;

    if (JS_HasProperty(cx, obj, funcName, &hasAction) && hasAction) {
        if(!JS_GetProperty(cx, obj, funcName, &temp_retval)) {
            return;
        }
        if(temp_retval == JSVAL_VOID) {
            return;
        }
        JSAutoCompartment ac(cx, obj);
        JS_CallFunctionName(cx, obj, funcName,
                            1, &dataVal, &retval);
    }

}

void js_log(const char *format, ...) {
    if (_js_log_buf == NULL) {
        _js_log_buf = (char *)calloc(sizeof(char), 257);
    }
    va_list vl;
    va_start(vl, format);
    int len = vsnprintf(_js_log_buf, 256, format, vl);
    va_end(vl);
    if (len) {
        CCLOG("JS: %s\n", _js_log_buf);
    }
}

#define JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES 1

JSBool JSBCore_platform(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getPlatform");
        return JS_FALSE;
    }

    JSString * platform;

    // config.deviceType: Device Type
    // 'mobile' for any kind of mobile devices, 'desktop' for PCs, 'browser' for Web Browsers
    // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    //     platform = JS_InternString(_cx, "desktop");
    // #else
    platform = JS_InternString(cx, "mobile");
    // #endif

    jsval ret = STRING_TO_JSVAL(platform);

    JS_SET_RVAL(cx, vp, ret);

    return JS_TRUE;
};

JSBool JSBCore_version(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getVersion");
        return JS_FALSE;
    }

    char version[256];
    snprintf(version, sizeof(version)-1, "%s - %s", cocos2dVersion(), JSB_version);
    JSString * js_version = JS_InternString(cx, version);

    jsval ret = STRING_TO_JSVAL(js_version);
    JS_SET_RVAL(cx, vp, ret);

    return JS_TRUE;
};

JSBool JSBCore_os(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getOS");
        return JS_FALSE;
    }

    JSString * os;

    // osx, ios, android, windows, linux, etc..
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    os = JS_InternString(cx, "ios");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    os = JS_InternString(cx, "android");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    os = JS_InternString(cx, "windows");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    os = JS_InternString(cx, "marmalade");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    os = JS_InternString(cx, "linux");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
    os = JS_InternString(cx, "bada");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    os = JS_InternString(cx, "blackberry");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    os = JS_InternString(cx, "osx");
#else
    os = JS_InternString(cx, "unknown");
#endif

    jsval ret = STRING_TO_JSVAL(os);
    JS_SET_RVAL(cx, vp, ret);

    return JS_TRUE;
};


void registerDefaultClasses(JSContext* cx, JSObject* global) {
    // first, try to get the ns
    jsval nsval;
    JSObject *ns;
    JS_GetProperty(cx, global, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, global, "cc", &nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }

    //
    // Javascript controller (__jsc__)
    //
    JSObject *jsc = JS_NewObject(cx, NULL, NULL, NULL);
    jsval jscVal = OBJECT_TO_JSVAL(jsc);
    JS_SetProperty(cx, global, "__jsc__", &jscVal);

    JS_DefineFunction(cx, jsc, "garbageCollect", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, jsc, "dumpRoot", ScriptingCore::dumpRoot, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, jsc, "addGCRootObject", ScriptingCore::addRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, jsc, "removeGCRootObject", ScriptingCore::removeRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, jsc, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );

    // register some global functions
    JS_DefineFunction(cx, global, "require", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "forceGC", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, global, "__getPlatform", JSBCore_platform, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__getOS", JSBCore_os, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__getVersion", JSBCore_version, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

void sc_finalize(JSFreeOp *freeOp, JSObject *obj) {
    return;
}

static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, sc_finalize,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

ScriptingCore::ScriptingCore()
: rt_(NULL)
, cx_(NULL)
, global_(NULL)
, debugGlobal_(NULL)
{
    // set utf8 strings internally (we don't need utf16)
    // XXX: Removed in SpiderMonkey 19.0
    //JS_SetCStringsAreUTF8();
    this->addRegisterCallback(registerDefaultClasses);
    this->runLoop = new SimpleRunLoop();
}

void ScriptingCore::string_report(jsval val) {
    if (JSVAL_IS_NULL(val)) {
        LOGD("val : (JSVAL_IS_NULL(val)");
        // return 1;
    } else if ((JSVAL_IS_BOOLEAN(val)) &&
               (JS_FALSE == (JSVAL_TO_BOOLEAN(val)))) {
        LOGD("val : (return value is JS_FALSE");
        // return 1;
    } else if (JSVAL_IS_STRING(val)) {
        JSString *str = JS_ValueToString(this->getGlobalContext(), val);
        if (NULL == str) {
            LOGD("val : return string is NULL");
        } else {
            JSStringWrapper wrapper(str);
            LOGD("val : return string =\n%s\n", (char *)wrapper);
        }
    } else if (JSVAL_IS_NUMBER(val)) {
        double number;
        if (JS_FALSE ==
            JS_ValueToNumber(this->getGlobalContext(), val, &number)) {
            LOGD("val : return number could not be converted");
        } else {
            LOGD("val : return number =\n%f", number);
        }
    }
}

JSBool ScriptingCore::evalString(const char *string, jsval *outVal, const char *filename, JSContext* cx, JSObject* global)
{
    jsval rval;
    if (cx == NULL)
        cx = cx_;
    if (global == NULL)
        global = global_;
    JSScript* script = JS_CompileScript(cx, global, string, strlen(string), filename, 1);
    if (script) {
        // JSAutoCompartment ac(cx, global);
        JSAutoCompartment ac(cx, global);
        JSBool evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
        if (JS_FALSE == evaluatedOK) {
            fprintf(stderr, "(evaluatedOK == JS_FALSE)\n");
        }
        return evaluatedOK;
    }
    return false;
}

void ScriptingCore::start() {
    // for now just this
    this->createGlobalContext();
}

void ScriptingCore::addRegisterCallback(sc_register_sth callback) {
    registrationList.push_back(callback);
}

void ScriptingCore::removeAllRoots(JSContext *cx) {
    js_proxy_t *current, *tmp;
    HASH_ITER(hh, _js_native_global_ht, current, tmp) {
        JS_RemoveObjectRoot(cx, &current->obj);
        HASH_DEL(_js_native_global_ht, current);
        free(current);
    }
    HASH_ITER(hh, _native_js_global_ht, current, tmp) {
        HASH_DEL(_native_js_global_ht, current);
        free(current);
    }
    HASH_CLEAR(hh, _js_native_global_ht);
    HASH_CLEAR(hh, _native_js_global_ht);
}

void ScriptingCore::createGlobalContext() {
    if (this->cx_ && this->rt_) {
        ScriptingCore::removeAllRoots(this->cx_);
        JS_DestroyContext(this->cx_);
        JS_DestroyRuntime(this->rt_);
        this->cx_ = NULL;
        this->rt_ = NULL;
    }
    //JS_SetCStringsAreUTF8();
    this->rt_ = JS_NewRuntime(10 * 1024 * 1024, JS_NO_HELPER_THREADS);
    this->cx_ = JS_NewContext(rt_, 10240);
    JS_SetOptions(this->cx_, JSOPTION_TYPE_INFERENCE);
    JS_SetVersion(this->cx_, JSVERSION_LATEST);
    JS_SetOptions(this->cx_, JS_GetOptions(this->cx_) & ~JSOPTION_METHODJIT);
    JS_SetOptions(this->cx_, JS_GetOptions(this->cx_) & ~JSOPTION_METHODJIT_ALWAYS);
    JS_SetErrorReporter(this->cx_, ScriptingCore::reportError);
#if defined(JS_GC_ZEAL) && defined(DEBUG)
    //JS_SetGCZeal(this->cx_, 2, JS_DEFAULT_ZEAL_FREQ);
#endif
    this->global_ = NewGlobalObject(cx_);
#if JSB_ENABLE_DEBUGGER
    JS_SetDebugMode(cx_, JS_TRUE);
#endif
    for (std::vector<sc_register_sth>::iterator it = registrationList.begin(); it != registrationList.end(); it++) {
        sc_register_sth callback = *it;
        callback(this->cx_, this->global_);
    }
}

JSBool ScriptingCore::runScript(const char *path, JSObject* global, JSContext* cx)
{
    if (!path) {
        return false;
    }
    cocos2d::CCFileUtils *futil = cocos2d::CCFileUtils::sharedFileUtils();
    std::string rpath;
    if (path[0] == '/') {
        rpath = path;
    } else {
        rpath = futil->fullPathForFilename(path);
    }
    if (global == NULL) {
        global = global_;
    }
    if (cx == NULL) {
        cx = cx_;
    }

    js::RootedObject obj(cx, global);
	JS::CompileOptions options(cx);
    options.setFileAndLine(rpath.c_str(), 1);
    // Don't setUTF8 since it will cause messy string output by cc.log .
//	options.setUTF8(true).setFileAndLine(rpath.c_str(), 1);
    
    // this will always compile the script, we can actually check if the script
    // was compiled before, because it can be in the global map
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    unsigned char *content = NULL;
    unsigned long contentSize = 0;

    content = (unsigned char*)CCString::createWithContentsOfFile(rpath.c_str())->getCString();
    contentSize = strlen((char*)content);
    // Not supported in SpiderMonkey 19.0
    //JSScript* script = JS_CompileScript(cx, global, (char*)content, contentSize, path, 1);
    JSScript *script = JS::Compile(cx, obj, options, (char*)content, contentSize);
#else
    // Removed in SpiderMonkey 19.0
    //JSScript* script = JS_CompileUTF8File(cx, global, rpath.c_str());
	JSScript *script = JS::Compile(cx, obj, options, rpath.c_str());
#endif
    JSBool evaluatedOK = false;
    if (script) {
        jsval rval;
        filename_script[path] = script;
        JSAutoCompartment ac(cx, global);
        evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
        if (JS_FALSE == evaluatedOK) {
            CCLog("(evaluatedOK == JS_FALSE)");
            JS_ReportPendingException(cx);
        }
    }
    return evaluatedOK;
}

void ScriptingCore::reset()
{
    cleanup();
    start();
}

ScriptingCore::~ScriptingCore()
{
    cleanup();
}

void ScriptingCore::cleanup()
{
    localStorageFree();
    removeAllRoots(cx_);
    if (cx_)
    {
        JS_DestroyContext(cx_);
        cx_ = NULL;
    }
    if (rt_)
    {
        JS_DestroyRuntime(rt_);
        rt_ = NULL;
    }
    JS_ShutDown();
    if (_js_log_buf) {
        free(_js_log_buf);
        _js_log_buf = NULL;
    }

    js_type_class_t* current, *tmp;
    HASH_ITER(hh, _js_global_type_ht, current, tmp)
    {
        HASH_DEL(_js_global_type_ht, current);
        free(current->jsclass);
        free(current);
    }
    HASH_CLEAR(hh, _js_global_type_ht);
}

void ScriptingCore::reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    js_log("%s:%u:%s\n",
            report->filename ? report->filename : "<no filename=\"filename\">",
            (unsigned int) report->lineno,
            message);
};


JSBool ScriptingCore::log(JSContext* cx, uint32_t argc, jsval *vp)
{
    if (argc > 0) {
        JSString *string = NULL;
        JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string);
        if (string) {
            JSStringWrapper wrapper(string);
            js_log((char *)wrapper);
        }
    }
    return JS_TRUE;
}


void ScriptingCore::removeScriptObjectByCCObject(CCObject* pObj)
{
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    void *ptr = (void*)pObj;
    JS_GET_PROXY(nproxy, ptr);
    if (nproxy) {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_GET_NATIVE_PROXY(jsproxy, nproxy->obj);
        JS_RemoveObjectRoot(cx, &jsproxy->obj);
        JS_REMOVE_PROXY(nproxy, jsproxy);
    }
}


JSBool ScriptingCore::setReservedSpot(uint32_t i, JSObject *obj, jsval value) {
    JS_SetReservedSlot(obj, i, value);
    return JS_TRUE;
}

JSBool ScriptingCore::executeScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSString* str = JS_ValueToString(cx, argv[0]);
        JSStringWrapper path(str);
        JSBool res = false;
        if (argc == 2 && argv[1].isString()) {
            JSString* globalName = JSVAL_TO_STRING(argv[1]);
            JSStringWrapper name(globalName);
            js::RootedObject* rootedGlobal = globals[name];
            if (rootedGlobal) {
                res = ScriptingCore::getInstance()->runScript(path, rootedGlobal->get());
            } else {
                JS_ReportError(cx, "Invalid global object: %s", (char*)name);
                return JS_FALSE;
            }
        } else {
            JSObject* glob = JS_GetGlobalForScopeChain(cx);
            res = ScriptingCore::getInstance()->runScript(path, glob);
        }
        return res;
    }
    return JS_TRUE;
}

JSBool ScriptingCore::forceGC(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSRuntime *rt = JS_GetRuntime(cx);
    JS_GC(rt);
    return JS_TRUE;
}

static void dumpNamedRoot(const char *name, void *addr,  JSGCRootType type, void *data)
{
    CCLOG("Root: '%s' at %p", name, addr);
}

JSBool ScriptingCore::dumpRoot(JSContext *cx, uint32_t argc, jsval *vp)
{
    // JS_DumpNamedRoots is only available on DEBUG versions of SpiderMonkey.
    // Mac and Simulator versions were compiled with DEBUG.
#if DEBUG
//    JSContext *_cx = ScriptingCore::getInstance()->getGlobalContext();
//    JSRuntime *rt = JS_GetRuntime(_cx);
//    JS_DumpNamedRoots(rt, dumpNamedRoot, NULL);
#endif
    return JS_TRUE;
}

JSBool ScriptingCore::addRootJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSObject *o = NULL;
        if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == JS_TRUE) {
            if (JS_AddNamedObjectRoot(cx, &o, "from-js") == JS_FALSE) {
                LOGD("something went wrong when setting an object to the root");
            }
        }
        return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool ScriptingCore::removeRootJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSObject *o = NULL;
        if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == JS_TRUE) {
            JS_RemoveObjectRoot(cx, &o);
        }
        return JS_TRUE;
    }
    return JS_FALSE;
}

void ScriptingCore::pauseSchedulesAndActions(CCNode *node) {

    CCArray * arr = JSScheduleWrapper::getTargetForNativeNode(node);
    if(! arr) return;
    for(unsigned int i = 0; i < arr->count(); ++i) {
        if(arr->objectAtIndex(i)) {
            node->getScheduler()->pauseTarget(arr->objectAtIndex(i));
        }
    }
}


void ScriptingCore::resumeSchedulesAndActions(CCNode *node) {

    CCArray * arr = JSScheduleWrapper::getTargetForNativeNode(node);
    if(!arr) return;
    for(unsigned int i = 0; i < arr->count(); ++i) {
        if(!arr->objectAtIndex(i)) continue;
        node->getScheduler()->resumeTarget(arr->objectAtIndex(i));
    }
}

void ScriptingCore::cleanupSchedulesAndActions(CCNode *node) {

    CCArray * arr = JSCallFuncWrapper::getTargetForNativeNode(node);
    if(arr) {
        arr->removeAllObjects();
    }

    arr = JSScheduleWrapper::getTargetForNativeNode(node);
    if(arr) {
        CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(arr, pObj)
        {
            pScheduler->unscheduleAllForTarget(pObj);
        }

        JSScheduleWrapper::removeAllTargetsForNatiaveNode(node);
    }
}

int ScriptingCore::executeNodeEvent(CCNode* pNode, int nAction)
{
    js_proxy_t * p;
    JS_GET_PROXY(p, pNode);

    if (!p) return 0;

    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);
    js_proxy_t *proxy;
    JS_GET_PROXY(proxy, pNode);

    if(nAction == kCCNodeOnEnter)
    {
        executeJSFunctionWithName(this->cx_, p->obj, "onEnter", dataVal, retval);
        resumeSchedulesAndActions(pNode);
    }
    else if(nAction == kCCNodeOnExit)
    {
        executeJSFunctionWithName(this->cx_, p->obj, "onExit", dataVal, retval);
        pauseSchedulesAndActions(pNode);
    }
    else if(nAction == kCCNodeOnEnterTransitionDidFinish)
    {
        executeJSFunctionWithName(this->cx_, p->obj, "onEnterTransitionDidFinish", dataVal, retval);
    }
    else if(nAction == kCCNodeOnExitTransitionDidStart)
    {
        executeJSFunctionWithName(this->cx_, p->obj, "onExitTransitionDidStart", dataVal, retval);
    }
    else if(nAction == kCCNodeOnCleanup) {
        cleanupSchedulesAndActions(pNode);
    }

    return 1;
}

int ScriptingCore::executeMenuItemEvent(CCMenuItem* pMenuItem)
{
    js_proxy_t * p;
    JS_GET_PROXY(p, pMenuItem);

    if (!p) return 0;

    jsval retval;
    jsval dataVal;
    js_proxy_t *proxy;
    JS_GET_PROXY(proxy, pMenuItem);
    dataVal = (proxy ? OBJECT_TO_JSVAL(proxy->obj) : JSVAL_NULL);

    executeJSFunctionFromReservedSpot(this->cx_, p->obj, dataVal, retval);

    return 1;
}

int ScriptingCore::executeNotificationEvent(CCNotificationCenter* pNotificationCenter, const char* pszName)
{
    return 1;
}

int ScriptingCore::executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget/* = NULL*/)
{
    return 1;
}

int ScriptingCore::executeSchedule(int nHandler, float dt, CCNode* pNode/* = NULL*/)
{
    js_proxy_t * p;
    JS_GET_PROXY(p, pNode);

    if (!p) return 0;

    jsval retval;
    jsval dataVal = DOUBLE_TO_JSVAL(dt);

    executeJSFunctionWithName(this->cx_, p->obj, "update", dataVal, retval);

    return 1;
}

int ScriptingCore::executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches)
{
    std::string funcName = "";
    getTouchesFuncName(eventType, funcName);

    JSObject *jsretArr = JS_NewArrayObject(this->cx_, 0, NULL);

    JS_AddNamedObjectRoot(this->cx_, &jsretArr, "touchArray");
    int count = 0;
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        getJSTouchObject(this->cx_, (CCTouch *) *it, jsret);
        if(!JS_SetElement(this->cx_, jsretArr, count, &jsret)) {
            break;
        }
    }

    executeFunctionWithObjectData(pLayer,  funcName.c_str(), jsretArr);

    JS_RemoveObjectRoot(this->cx_, &jsretArr);

    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        removeJSTouchObject(this->cx_, (CCTouch *) *it, jsret);
    }

    return 1;
}

int ScriptingCore::executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch)
{
    std::string funcName = "";
    getTouchFuncName(eventType, funcName);

    jsval jsret;
    getJSTouchObject(this->getGlobalContext(), pTouch, jsret);
    JSObject *jsObj = JSVAL_TO_OBJECT(jsret);
    bool retval = executeFunctionWithObjectData(pLayer,  funcName.c_str(), jsObj);

    removeJSTouchObject(this->getGlobalContext(), pTouch, jsret);

    return retval;
}

bool ScriptingCore::executeFunctionWithObjectData(CCNode *self, const char *name, JSObject *obj) {

    js_proxy_t * p;
    JS_GET_PROXY(p, self);
    if (!p) return false;

    jsval retval;
    jsval dataVal = OBJECT_TO_JSVAL(obj);

    executeJSFunctionWithName(this->cx_, p->obj, name, dataVal, retval);
    if(JSVAL_IS_NULL(retval)) {
        return false;
    }
    else if(JSVAL_IS_BOOLEAN(retval)) {
        return JSVAL_TO_BOOLEAN(retval);
    }
    return false;
}

int ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, jsval data) {
    jsval retval;

    executeJSFunctionWithName(this->cx_, JSVAL_TO_OBJECT(owner), name, data, retval);

    return 1;
}

int ScriptingCore::executeAccelerometerEvent(CCLayer *pLayer, CCAcceleration *pAccelerationValue) {

    jsval value = ccacceleration_to_jsval(this->getGlobalContext(), *pAccelerationValue);
    JS_AddValueRoot(this->getGlobalContext(), &value);

    executeFunctionWithObjectData(pLayer, "onAccelerometer", JSVAL_TO_OBJECT(value));

    JS_RemoveValueRoot(this->getGlobalContext(), &value);
    return 1;
}

int ScriptingCore::executeLayerKeypadEvent(CCLayer* pLayer, int eventType)
{
    return 0;
}


int ScriptingCore::executeCustomTouchesEvent(int eventType,
                                       CCSet *pTouches, JSObject *obj)
{
    jsval retval;
    std::string funcName;
    getTouchesFuncName(eventType, funcName);

    JSObject *jsretArr = JS_NewArrayObject(this->cx_, 0, NULL);
    JS_AddNamedObjectRoot(this->cx_, &jsretArr, "touchArray");
    int count = 0;
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        getJSTouchObject(this->cx_, (CCTouch *) *it, jsret);
        if(!JS_SetElement(this->cx_, jsretArr, count, &jsret)) {
            break;
        }
    }

    jsval jsretArrVal = OBJECT_TO_JSVAL(jsretArr);
    executeJSFunctionWithName(this->cx_, obj, funcName.c_str(), jsretArrVal, retval);
    JS_RemoveObjectRoot(this->cx_, &jsretArr);

    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        removeJSTouchObject(this->cx_, (CCTouch *) *it, jsret);
    }

    return 1;
}


int ScriptingCore::executeCustomTouchEvent(int eventType,
                                           CCTouch *pTouch, JSObject *obj) {
    jsval retval;
    std::string funcName;
    getTouchFuncName(eventType, funcName);

    jsval jsTouch;
    getJSTouchObject(this->cx_, pTouch, jsTouch);

    executeJSFunctionWithName(this->cx_, obj, funcName.c_str(), jsTouch, retval);

    // Remove touch object from global hash table and unroot it.
    removeJSTouchObject(this->cx_, pTouch, jsTouch);
    return 1;

}


int ScriptingCore::executeCustomTouchEvent(int eventType,
                                           CCTouch *pTouch, JSObject *obj,
                                           jsval &retval) {

    std::string funcName;
    getTouchFuncName(eventType, funcName);

    jsval jsTouch;
    getJSTouchObject(this->cx_, pTouch, jsTouch);

    executeJSFunctionWithName(this->cx_, obj, funcName.c_str(), jsTouch, retval);

    // Remove touch object from global hash table and unroot it.
    removeJSTouchObject(this->cx_, pTouch, jsTouch);

    return 1;

}

#pragma mark - Conversion Routines
JSBool jsval_to_int32( JSContext *cx, jsval vp, int32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (int32_t)dp;

    return ok;
}

JSBool jsval_to_uint32( JSContext *cx, jsval vp, uint32_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (uint32_t)dp;

    return ok;
}

JSBool jsval_to_uint16( JSContext *cx, jsval vp, uint16_t *outval )
{
    JSBool ok = JS_TRUE;
    double dp;
    ok &= JS_ValueToNumber(cx, vp, &dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ok &= !isnan(dp);
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    *outval = (uint16_t)dp;

    return ok;
}

JSBool jsval_to_long_long(JSContext *cx, jsval vp, long long* r) {
	JSObject *tmp_arg;
	JSBool ok = JS_ValueToObject( cx, vp, &tmp_arg );
	JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
	JSB_PRECONDITION2( tmp_arg && JS_IsTypedArrayObject( tmp_arg ), cx, JS_FALSE, "Not a TypedArray object");
	JSB_PRECONDITION2( JS_GetTypedArrayByteLength( tmp_arg ) == sizeof(long long), cx, JS_FALSE, "Invalid Typed Array length");
	
	uint32_t* arg_array = (uint32_t*)JS_GetArrayBufferViewData( tmp_arg );
	long long ret =  arg_array[0];
	ret = ret << 32;
	ret |= arg_array[1];
	
	*r = ret;
	return JS_TRUE;
}

JSBool jsval_to_std_string(JSContext *cx, jsval v, std::string* ret) {
    JSString *tmp = JS_ValueToString(cx, v);
    JSB_PRECONDITION2(tmp, cx, JS_FALSE, "Error processing arguments");

    JSStringWrapper str(tmp);
    *ret = str.get();
    return JS_TRUE;
}

JSBool jsval_to_ccpoint(JSContext *cx, jsval v, CCPoint* ret) {
    JSObject *tmp;
    jsval jsx, jsy;
    double x, y;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "x", &jsx) &&
        JS_GetProperty(cx, tmp, "y", &jsy) &&
        JS_ValueToNumber(cx, jsx, &x) &&
        JS_ValueToNumber(cx, jsy, &y);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    ret->x = (float)x;
    ret->y = (float)y;
    return JS_TRUE;
}

JSBool jsval_to_ccacceleration(JSContext* cx,jsval v, CCAcceleration* ret) {
    JSObject *tmp;
    jsval jsx, jsy, jsz, jstimestamp;
    double x, y, timestamp, z;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
    JS_GetProperty(cx, tmp, "x", &jsx) &&
    JS_GetProperty(cx, tmp, "y", &jsy) &&
    JS_GetProperty(cx, tmp, "z", &jsz) &&
    JS_GetProperty(cx, tmp, "timestamp", &jstimestamp) &&
    JS_ValueToNumber(cx, jsx, &x) &&
    JS_ValueToNumber(cx, jsy, &y) &&
    JS_ValueToNumber(cx, jsz, &z) &&
    JS_ValueToNumber(cx, jstimestamp, &timestamp);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    ret->x = x;
    ret->y = y;
    ret->z = z;
    ret->timestamp = timestamp;
    return JS_TRUE;
}

JSBool jsvals_variadic_to_ccarray( JSContext *cx, jsval *vp, int argc, CCArray** ret)
{
    JSBool ok = JS_TRUE;
    CCArray* pArray = CCArray::create();
    for( int i=0; i < argc; i++ )
    {
        double num = 0.0;
        // optimization: JS_ValueToNumber is expensive. And can convert an string like "12" to a number
        if( JSVAL_IS_NUMBER(*vp)) {
            ok &= JS_ValueToNumber(cx, *vp, &num );
            if (!ok) {
                break;
            }
            pArray->addObject(CCInteger::create((int)num));
        }
        else if (JSVAL_IS_STRING(*vp))
        {
            JSStringWrapper str(JSVAL_TO_STRING(*vp), cx);
            pArray->addObject(CCString::create(str));
        }
        else
        {
            js_proxy_t* p;
            JSObject* obj = JSVAL_TO_OBJECT(*vp);
            JS_GET_NATIVE_PROXY(p, obj);
            if (p) {
                pArray->addObject((CCObject*)p->ptr);
            }
        }
        // next
        vp++;
    }
    *ret = pArray;
    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    return ok;
}

JSBool jsval_to_ccrect(JSContext *cx, jsval v, CCRect* ret) {
    JSObject *tmp;
    jsval jsx, jsy, jswidth, jsheight;
    double x, y, width, height;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "x", &jsx) &&
        JS_GetProperty(cx, tmp, "y", &jsy) &&
        JS_GetProperty(cx, tmp, "width", &jswidth) &&
        JS_GetProperty(cx, tmp, "height", &jsheight) &&
        JS_ValueToNumber(cx, jsx, &x) &&
        JS_ValueToNumber(cx, jsy, &y) &&
        JS_ValueToNumber(cx, jswidth, &width) &&
        JS_ValueToNumber(cx, jsheight, &height);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    ret->origin.x = x;
    ret->origin.y = y;
    ret->size.width = width;
    ret->size.height = height;
    return JS_TRUE;
}

JSBool jsval_to_ccsize(JSContext *cx, jsval v, CCSize* ret) {
    JSObject *tmp;
    jsval jsw, jsh;
    double w, h;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "width", &jsw) &&
        JS_GetProperty(cx, tmp, "height", &jsh) &&
        JS_ValueToNumber(cx, jsw, &w) &&
        JS_ValueToNumber(cx, jsh, &h);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ret->width = w;
    ret->height = h;
    return JS_TRUE;
}

JSBool jsval_to_cccolor4b(JSContext *cx, jsval v, ccColor4B* ret) {
    JSObject *tmp;
    jsval jsr, jsg, jsb, jsa;
    double r, g, b, a;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "r", &jsr) &&
        JS_GetProperty(cx, tmp, "g", &jsg) &&
        JS_GetProperty(cx, tmp, "b", &jsb) &&
        JS_GetProperty(cx, tmp, "a", &jsa) &&
        JS_ValueToNumber(cx, jsr, &r) &&
        JS_ValueToNumber(cx, jsg, &g) &&
        JS_ValueToNumber(cx, jsb, &b) &&
        JS_ValueToNumber(cx, jsa, &a);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;
    return JS_TRUE;
}

JSBool jsval_to_cccolor4f(JSContext *cx, jsval v, ccColor4F* ret) {
    JSObject *tmp;
    jsval jsr, jsg, jsb, jsa;
    double r, g, b, a;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "r", &jsr) &&
        JS_GetProperty(cx, tmp, "g", &jsg) &&
        JS_GetProperty(cx, tmp, "b", &jsb) &&
        JS_GetProperty(cx, tmp, "a", &jsa) &&
        JS_ValueToNumber(cx, jsr, &r) &&
        JS_ValueToNumber(cx, jsg, &g) &&
        JS_ValueToNumber(cx, jsb, &b) &&
        JS_ValueToNumber(cx, jsa, &a);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    ret->r = r;
    ret->g = g;
    ret->b = b;
    ret->a = a;
    return JS_TRUE;
}

JSBool jsval_to_cccolor3b(JSContext *cx, jsval v, ccColor3B* ret) {
    JSObject *tmp;
    jsval jsr, jsg, jsb;
    double r, g, b;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "r", &jsr) &&
        JS_GetProperty(cx, tmp, "g", &jsg) &&
        JS_GetProperty(cx, tmp, "b", &jsb) &&
        JS_ValueToNumber(cx, jsr, &r) &&
        JS_ValueToNumber(cx, jsg, &g) &&
        JS_ValueToNumber(cx, jsb, &b);

    JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

    ret->r = r;
    ret->g = g;
    ret->b = b;
    return JS_TRUE;
}

JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, CCPoint **points, int *numPoints) {
    // Parsing sequence
    JSObject *jsobj;
    JSBool ok = JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj), cx, JS_FALSE, "Object must be an array");

    uint32_t len;
    JS_GetArrayLength(cx, jsobj, &len);

    CCPoint *array = (CCPoint*)malloc( sizeof(CCPoint) * len);

    for( uint32_t i=0; i< len;i++ ) {
        jsval valarg;
        JS_GetElement(cx, jsobj, i, &valarg);

        ok = jsval_to_ccpoint(cx, valarg, &array[i]);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
    }

    *numPoints = len;
    *points = array;

    return JS_TRUE;
}


JSBool jsval_to_ccarray(JSContext* cx, jsval v, CCArray** ret) {
    JSObject *jsobj;
    JSBool ok = JS_ValueToObject( cx, v, &jsobj );
    JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
    JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj),  cx, JS_FALSE, "Object must be an array");

    uint32_t len = 0;
    JS_GetArrayLength(cx, jsobj, &len);
    CCArray* arr = CCArray::createWithCapacity(len);
    for (uint32_t i=0; i < len; i++) {
        jsval elt;
        JSObject *elto;
        if (JS_GetElement(cx, jsobj, i, &elt) && JS_ValueToObject(cx, elt, &elto)) {
            js_proxy_t *proxy;
            JS_GET_NATIVE_PROXY(proxy, elto);
            JSB_PRECONDITION2( proxy, cx, JS_FALSE, "Error getting proxy.");

            arr->addObject((CCObject *)proxy->ptr);
        }
    }
    *ret = arr;
    return JS_TRUE;
}


jsval ccarray_to_jsval(JSContext* cx, CCArray *arr) {

    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);

    for(unsigned int i = 0; i < arr->count(); ++i) {
        jsval arrElement;
        CCObject *obj = arr->objectAtIndex(i);

        CCString *testString = dynamic_cast<cocos2d::CCString *>(obj);
        CCDictionary* testDict = NULL;
        CCArray* testArray = NULL;
        // XXX: Only supports string, since all data read from plist files will be stored as string in cocos2d-x
        // Do we need to convert string to js base type ?
        if(testString) {
            arrElement = c_string_to_jsval(cx, testString->getCString());
        } else if ((testDict = dynamic_cast<cocos2d::CCDictionary*>(obj))) {
            arrElement = ccdictionary_to_jsval(cx, testDict);
        } else if ((testArray = dynamic_cast<cocos2d::CCArray*>(obj))) {
            arrElement = ccarray_to_jsval(cx, testArray);
        } else {
            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCObject>(cx, obj);
            arrElement = OBJECT_TO_JSVAL(proxy->obj);
        }

        if(!JS_SetElement(cx, jsretArr, i, &arrElement)) {
            break;
        }
    }
    return OBJECT_TO_JSVAL(jsretArr);
}

jsval ccdictionary_to_jsval(JSContext* cx, CCDictionary* dict)
{
    JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(dict, pElement)
    {
        jsval dictElement;
        CCString* obj = dynamic_cast<CCString*>(pElement->getObject());

        CCString *testString = dynamic_cast<cocos2d::CCString *>(obj);
        CCDictionary* testDict = NULL;
        CCArray* testArray = NULL;
        // XXX: Only supports string, since all data read from plist files will be stored as string in cocos2d-x
        // Do we need to convert string to js base type ?
        if(testString) {
            dictElement = c_string_to_jsval(cx, testString->getCString());
        } else if ((testDict = dynamic_cast<cocos2d::CCDictionary*>(obj))) {
            dictElement = ccdictionary_to_jsval(cx, testDict);
        } else if ((testArray = dynamic_cast<cocos2d::CCArray*>(obj))) {
            dictElement = ccarray_to_jsval(cx, testArray);
        } else {
            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCObject>(cx, obj);
            dictElement = OBJECT_TO_JSVAL(proxy->obj);
        }

        const char* key = pElement->getStrKey();
        if (key && strlen(key) > 0)
        {
            JS_SetProperty(cx, jsRet, key, &dictElement);
        }
    }
    return OBJECT_TO_JSVAL(jsRet);
}

JSBool jsval_to_ccdictionary(JSContext* cx, jsval v, CCDictionary** ret) {

    if(JSVAL_IS_NULL(v) || JSVAL_IS_VOID(v))
    {
        *ret = NULL;
        return JS_TRUE;
    }
    
    JSObject *itEl = JS_NewPropertyIterator(cx, JSVAL_TO_OBJECT(v));
    JSBool ok = JS_TRUE;
    CCDictionary* dict = NULL;
    jsid propId;
    do {

        jsval prop;
        JS_GetPropertyById(cx, JSVAL_TO_OBJECT(v), propId, &prop);

        js_proxy_t *proxy;
        JSObject *tmp = JSVAL_TO_OBJECT(prop);
        JS_GET_NATIVE_PROXY(proxy, tmp);
        cocos2d::CCObject* cobj = (cocos2d::CCObject *)(proxy ? proxy->ptr : NULL);
        TEST_NATIVE_OBJECT(cx, cobj)

        jsval key;
        std::string keyStr;
        if(JSID_IS_STRING(propId)) {
            JS_IdToValue(cx, propId, &key);
            ok &= jsval_to_std_string(cx, key, &keyStr);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        }

        if(JSVAL_IS_NULL(key)) continue;

        if(!dict) {
            dict = CCDictionary::create();
        }
        dict->setObject(cobj, keyStr);

    } while(JS_NextProperty(cx, itEl, &propId));
    *ret = dict;
    return JS_TRUE;
}

// From native type to jsval
jsval int32_to_jsval( JSContext *cx, int32_t number )
{
    return INT_TO_JSVAL(number);
}

jsval uint32_to_jsval( JSContext *cx, uint32_t number )
{
    return UINT_TO_JSVAL(number);
}

jsval long_long_to_jsval(JSContext* cx, long long v) {
    JSObject *tmp = JS_NewUint32Array(cx, 2);
    uint32_t *data = (uint32_t *)JS_GetArrayBufferViewData(tmp);
    data[0] = ((uint32_t *)(&v))[0];
    data[1] = ((uint32_t *)(&v))[1];
    return OBJECT_TO_JSVAL(tmp);
}

jsval std_string_to_jsval(JSContext* cx, std::string& v) {
    JSString *str = JS_NewStringCopyZ(cx, v.c_str());
    return STRING_TO_JSVAL(str);
}

jsval c_string_to_jsval(JSContext* cx, const char* v) {
    JSString *str = JS_NewStringCopyZ(cx, v);
    return STRING_TO_JSVAL(str);
}

jsval ccpoint_to_jsval(JSContext* cx, CCPoint& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccacceleration_to_jsval(JSContext* cx, CCAcceleration& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "z", DOUBLE_TO_JSVAL(v.z), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
    JS_DefineProperty(cx, tmp, "timestamp", DOUBLE_TO_JSVAL(v.timestamp), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccrect_to_jsval(JSContext* cx, CCRect& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.origin.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.origin.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "width", DOUBLE_TO_JSVAL(v.size.width), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "height", DOUBLE_TO_JSVAL(v.size.height), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval ccsize_to_jsval(JSContext* cx, CCSize& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "width", DOUBLE_TO_JSVAL(v.width), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "height", DOUBLE_TO_JSVAL(v.height), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4b_to_jsval(JSContext* cx, ccColor4B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", INT_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "g", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "b", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "a", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor4f_to_jsval(JSContext* cx, ccColor4F& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", DOUBLE_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "g", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "b", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "a", DOUBLE_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

jsval cccolor3b_to_jsval(JSContext* cx, const ccColor3B& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "r", INT_TO_JSVAL(v.r), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "g", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "b", INT_TO_JSVAL(v.g), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    if (ok) {
        return OBJECT_TO_JSVAL(tmp);
    }
    return JSVAL_NULL;
}

#pragma mark - Debug

void SimpleRunLoop::update(float dt) {
    pthread_mutex_lock(&g_qMutex);
    while (queue.size() > 0) {
        vector<string>::iterator first = queue.begin();
        string str = *first;
        ScriptingCore::getInstance()->debugProcessInput(str);
        queue.erase(first);
    }
    pthread_mutex_unlock(&g_qMutex);
}

void ScriptingCore::debugProcessInput(string str) {
    JSString* jsstr = JS_NewStringCopyZ(cx_, str.c_str());
    jsval argv[3] = {
        STRING_TO_JSVAL(jsstr),
        frame,
        script
    };
    jsval outval;
    JSAutoCompartment ac(cx_, debugGlobal_);
    JS_CallFunctionName(cx_, debugGlobal_, "processInput", 3, argv, &outval);
}

void ScriptingCore::enableDebugger() {
    if (debugGlobal_ == NULL) {
        debugGlobal_ = NewGlobalObject(cx_, true);
        JS_WrapObject(cx_, &debugGlobal_);
        JSAutoCompartment ac(cx_, debugGlobal_);
        // these are used in the debug program
        JS_DefineFunction(cx_, debugGlobal_, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(cx_, debugGlobal_, "_bufferWrite", JSBDebug_BufferWrite, 1, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(cx_, debugGlobal_, "_bufferRead", JSBDebug_BufferRead, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(cx_, debugGlobal_, "_lockVM", JSBDebug_LockExecution, 2, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(cx_, debugGlobal_, "_unlockVM", JSBDebug_UnlockExecution, 0, JSPROP_READONLY | JSPROP_PERMANENT);

        runScript("jsb_debugger.js", debugGlobal_);

        // prepare the debugger
        jsval argv = OBJECT_TO_JSVAL(global_);
        jsval outval;
        JSBool ok = JS_CallFunctionName(cx_, debugGlobal_, "_prepareDebugger", 1, &argv, &outval);
        if (!ok) {
            JS_ReportPendingException(cx_);
        }
        // define the start debugger function
        JS_DefineFunction(cx_, global_, "startDebugger", JSBDebug_StartDebugger, 3, JSPROP_READONLY | JSPROP_PERMANENT);
        // start bg thread
        pthread_create(&debugThread, NULL, serverEntryPoint, NULL);

        CCScheduler* scheduler = CCDirector::sharedDirector()->getScheduler();
        scheduler->scheduleUpdateForTarget(this->runLoop, 0, false);
    }
}

JSBool jsStartDebugger(JSContext* cx, unsigned argc, jsval* vp)
{
    JSObject* debugGlobal = ScriptingCore::getInstance()->getDebugGlobal();
    if (argc >= 2) {
        jsval* argv = JS_ARGV(cx, vp);
        jsval out;
        JS_WrapObject(cx, &debugGlobal);
        JSAutoCompartment ac(cx, debugGlobal);
        JS_CallFunctionName(cx, debugGlobal, "_startDebugger", argc, argv, &out);
        return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool jsGetScript(JSContext* cx, unsigned argc, jsval* vp)
{
    jsval* argv = JS_ARGV(cx, vp);
    if (argc == 1 && argv[0].isString()) {
        JSString* str = argv[0].toString();
        JSStringWrapper wrapper(str);
        JSScript* script = filename_script[(char *)wrapper];
        if (script) {
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL((JSObject*)script));
        } else {
            JS_SET_RVAL(cx, vp, JSVAL_NULL);
        }
    }
    return JS_TRUE;
}

JSObject* NewGlobalObject(JSContext* cx, bool debug)
{
    JSObject* glob = JS_NewGlobalObject(cx, &global_class, NULL);
    if (!glob) {
        return NULL;
    }
    JSAutoCompartment ac(cx, glob);
    JSBool ok = JS_TRUE;
    ok = JS_InitStandardClasses(cx, glob);
    if (ok)
        JS_InitReflect(cx, glob);
    if (ok && debug)
        ok = JS_DefineDebuggerObject(cx, glob);
    if (!ok)
        return NULL;

    return glob;
}

JSBool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value)
{
    JSClass *klass = JS_GetClass(obj);
    unsigned int slots = JSCLASS_RESERVED_SLOTS(klass);
    if( idx >= slots )
        return JS_FALSE;

    JS_SetReservedSlot(obj, idx, value);

    return JS_TRUE;
}

JSBool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret)
{
    JSClass *klass = JS_GetClass(obj);
    unsigned int slots = JSCLASS_RESERVED_SLOTS(klass);
    if( idx >= slots )
        return JS_FALSE;

    ret = JS_GetReservedSlot(obj, idx);

    return JS_TRUE;
}

#pragma mark - Debugger

JSBool JSBDebug_StartDebugger(JSContext* cx, unsigned argc, jsval* vp)
{
    JSObject* debugGlobal = ScriptingCore::getInstance()->getDebugGlobal();
    if (argc >= 2) {
        jsval* argv = JS_ARGV(cx, vp);
        jsval out;
        JS_WrapObject(cx, &debugGlobal);
        JSAutoCompartment ac(cx, debugGlobal);
        JS_CallFunctionName(cx, debugGlobal, "_startDebugger", argc, argv, &out);
        return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool JSBDebug_BufferRead(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 0) {
        JSString* str;
        // this is safe because we're already inside a lock (from clearBuffers)
        if (vmLock) {
            pthread_mutex_lock(&g_rwMutex);
        }
        str = JS_NewStringCopyZ(cx, inData.c_str());
        inData.clear();
        if (vmLock) {
            pthread_mutex_unlock(&g_rwMutex);
        }
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(str));
    } else {
        JS_SET_RVAL(cx, vp, JSVAL_NULL);
    }
    return JS_TRUE;
}

JSBool JSBDebug_BufferWrite(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSStringWrapper strWrapper(argv[0]);
        // this is safe because we're already inside a lock (from clearBuffers)
        outData.append(strWrapper.get());
    }
    return JS_TRUE;
}

// this should lock the execution of the running thread, waiting for a signal
JSBool JSBDebug_LockExecution(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 2) {
        printf("locking vm\n");
        jsval* argv = JS_ARGV(cx, vp);
        frame = argv[0];
        script = argv[1];
        vmLock = true;
        while (vmLock) {
            // try to read the input, if there's anything
            pthread_mutex_lock(&g_qMutex);
            while (queue.size() > 0) {
                vector<string>::iterator first = queue.begin();
                string str = *first;
                ScriptingCore::getInstance()->debugProcessInput(str);
                queue.erase(first);
            }
            pthread_mutex_unlock(&g_qMutex);
            sched_yield();
        }
        printf("vm unlocked\n");
        frame = JSVAL_NULL;
        script = JSVAL_NULL;
        return JS_TRUE;
    }
    JS_ReportError(cx, "invalid call to _lockVM");
    return JS_FALSE;
}

JSBool JSBDebug_UnlockExecution(JSContext* cx, unsigned argc, jsval* vp)
{
    vmLock = false;
    return JS_TRUE;
}

bool serverAlive = true;

void processInput(string data) {
    pthread_mutex_lock(&g_qMutex);
    queue.push_back(string(data));
    pthread_mutex_unlock(&g_qMutex);
}

void clearBuffers() {
    pthread_mutex_lock(&g_rwMutex);
    {
        // only process input if there's something and we're not locked
        if (inData.length() > 0) {
            processInput(inData);
            inData.clear();
        }
        if (outData.length() > 0) {
            write(clientSocket, outData.c_str(), outData.length());
            outData.clear();
        }
    }
    pthread_mutex_unlock(&g_rwMutex);
}

void* serverEntryPoint(void*)
{
    // init the mutex
    assert(pthread_mutex_init(&g_rwMutex, NULL) == 0);
    assert(pthread_mutex_init(&g_qMutex, NULL) == 0);
    // start a server, accept the connection and keep reading data from it
    struct addrinfo hints, *result, *rp;
    int s;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; // TCP

    int err;
    stringstream portstr;
    portstr << JSB_DEBUGGER_PORT;
    const char* tmp = portstr.str().c_str();
    if ((err = getaddrinfo(NULL, tmp, &hints, &result)) != 0) {
        printf("error: %s\n", gai_strerror(err));
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        if ((s = socket(rp->ai_family, rp->ai_socktype, 0)) < 0) {
            continue;
        }
        int optval = 1;
        if ((setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval))) < 0) {
            close(s);
            LOGD("error setting socket options");
            return NULL;
        }
        if ((::bind(s, rp->ai_addr, rp->ai_addrlen)) == 0) {
            break;
        }
        close(s);
        s = -1;
    }
    if (s < 0 || rp == NULL) {
        LOGD("error creating/binding socket");
        return NULL;
    }

    freeaddrinfo(result);

    listen(s, 1);
    while (serverAlive && (clientSocket = accept(s, NULL, NULL)) > 0) {
        // read/write data
        LOGD("debug client connected");
        while (serverAlive) {
            char buf[256];
            int readBytes;
            while ((readBytes = read(clientSocket, buf, 256)) > 0) {
                buf[readBytes] = '\0';
                // no other thread is using this
                inData.append(buf);
                // process any input, send any output
                clearBuffers();
            } // while(read)
        } // while(serverAlive)
    }
    // we're done, destroy the mutex
    pthread_mutex_destroy(&g_rwMutex);
    pthread_mutex_destroy(&g_qMutex);
    return NULL;
}
