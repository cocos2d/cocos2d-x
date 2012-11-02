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
#include "cocos2d_specifics.hpp"
// for debug socket
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#endif

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
    js_type_class_t *classType;
    TypeTest<cocos2d::CCTouch> t;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, classType);
    assert(classType);
    JSObject *_tmp = JS_NewObject(cx, classType->jsclass, classType->proto, classType->parentProto);
    js_proxy_t *proxy, *nproxy;
    JS_NEW_PROXY(proxy, x, _tmp);
    void *ptr = x;
    JS_GET_PROXY(nproxy, ptr);
    JS_AddNamedObjectRoot(cx, &nproxy->obj, "CCTouch");
    jsret = OBJECT_TO_JSVAL(_tmp);
}

static void removeJSTouchObject(JSContext *cx, CCTouch *x, jsval &jsret) {
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    void *ptr = x;
    JS_GET_PROXY(nproxy, ptr);
    if (nproxy) {
        JS_RemoveObjectRoot(cx, &nproxy->obj);
        JS_GET_NATIVE_PROXY(jsproxy, nproxy->obj);
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

void jsb_register_cocos2d_config( JSContext *_cx, JSObject *cocos2d)
{
    // Config Object
    JSObject *ccconfig = JS_NewObject(_cx, NULL, NULL, NULL);
    // config.os: The Operating system
    // osx, ios, android, windows, linux, etc..
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    JSString *str = JS_InternString(_cx, "ios");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JSString *str = JS_InternString(_cx, "android");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    JSString *str = JS_InternString(_cx, "windows");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    JSString *str = JS_InternString(_cx, "marmalade");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    JSString *str = JS_InternString(_cx, "linux");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
    JSString *str = JS_InternString(_cx, "bada");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    JSString *str = JS_InternString(_cx, "blackberry");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    JSString *str = JS_InternString(_cx, "osx");
#else
    JSString *str = JS_InternString(_cx, "unknown");
#endif
    JS_DefineProperty(_cx, ccconfig, "os", STRING_TO_JSVAL(str), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

    // config.deviceType: Device Type
    // 'mobile' for any kind of mobile devices, 'desktop' for PCs, 'browser' for Web Browsers
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
//     str = JS_InternString(_cx, "desktop");
// #else
    str = JS_InternString(_cx, "mobile");
// #endif
    JS_DefineProperty(_cx, ccconfig, "deviceType", STRING_TO_JSVAL(str), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

    // config.engine: Type of renderer
    // 'cocos2d', 'cocos2d-x', 'cocos2d-html5/canvas', 'cocos2d-html5/webgl', etc..
    str = JS_InternString(_cx, "cocos2d-x");
    JS_DefineProperty(_cx, ccconfig, "engine", STRING_TO_JSVAL(str), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

    // config.arch: CPU Architecture
    // i386, ARM, x86_64, web
#ifdef __LP64__
    str = JS_InternString(_cx, "x86_64");
#elif defined(__arm__) || defined(__ARM_NEON__)
    str = JS_InternString(_cx, "arm");
#else
    str = JS_InternString(_cx, "i386");
#endif
    JS_DefineProperty(_cx, ccconfig, "arch", STRING_TO_JSVAL(str), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

    // config.version: Version of cocos2d + renderer
    str = JS_InternString(_cx, cocos2dVersion() );
    JS_DefineProperty(_cx, ccconfig, "version", STRING_TO_JSVAL(str), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

    // config.usesTypedArrays
#if JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES
    JSBool b = JS_FALSE;
#else
    JSBool b = JS_TRUE;
#endif
    JS_DefineProperty(_cx, ccconfig, "usesTypedArrays", BOOLEAN_TO_JSVAL(b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

    // config.debug: Debug build ?
#if COCOS2D_DEBUG > 0
    b = JS_TRUE;
#else
    b = JS_FALSE;
#endif
    JS_DefineProperty(_cx, ccconfig, "debug", BOOLEAN_TO_JSVAL(b), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);


    // Add "config" to "cc"
    JS_DefineProperty(_cx, cocos2d, "config", OBJECT_TO_JSVAL(ccconfig), NULL, NULL, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);
}

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

    jsb_register_cocos2d_config(cx, ns);

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

    // these are used in the debug socket
    JS_DefineFunction(cx, global, "newGlobal", jsNewGlobal, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "_socketOpen", jsSocketOpen, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "_socketWrite", jsSocketWrite, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "_socketRead", jsSocketRead, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "_socketClose", jsSocketClose, 1, JSPROP_READONLY | JSPROP_PERMANENT);
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
{
    // set utf8 strings internally (we don't need utf16)
    JS_SetCStringsAreUTF8();
    this->addRegisterCallback(registerDefaultClasses);
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
            LOGD("val : return string =\n%s\n",
                 JS_EncodeString(this->getGlobalContext(), str));
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
    HASH_CLEAR(hh, _js_global_type_ht);
}

void ScriptingCore::createGlobalContext() {
    if (this->cx_ && this->rt_) {
        ScriptingCore::removeAllRoots(this->cx_);
        JS_DestroyContext(this->cx_);
        JS_DestroyRuntime(this->rt_);
        this->cx_ = NULL;
        this->rt_ = NULL;
    }
	JS_SetCStringsAreUTF8();
    this->rt_ = JS_NewRuntime(10 * 1024 * 1024);
    this->cx_ = JS_NewContext(rt_, 10240);
    JS_SetOptions(this->cx_, JSOPTION_TYPE_INFERENCE);
    JS_SetVersion(this->cx_, JSVERSION_LATEST);
    JS_SetOptions(this->cx_, JS_GetOptions(this->cx_) & ~JSOPTION_METHODJIT);
    JS_SetOptions(this->cx_, JS_GetOptions(this->cx_) & ~JSOPTION_METHODJIT_ALWAYS);
    JS_SetErrorReporter(this->cx_, ScriptingCore::reportError);
    this->global_ = NewGlobalObject(cx_);
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
        rpath = futil->fullPathFromRelativePath(path);
    }
    if (global == NULL) {
        global = global_;
    }
    if (cx == NULL) {
        cx = cx_;
    }

    // this will always compile the script, we can actually check if the script
    // was compiled before, because it can be in the global map
#ifdef ANDROID
    unsigned char *content = NULL;
    unsigned long contentSize = 0;

    content = (unsigned char*)CCString::createWithContentsOfFile(rpath.c_str())->getCString();
    contentSize = strlen((char*)content);
    JSScript* script = JS_CompileScript(cx, global, (char*)content, contentSize, path, 1);
#else
    JSScript* script = JS_CompileUTF8File(cx, global, rpath.c_str());
#endif
    JSBool evaluatedOK = false;
    if (script) {
        jsval rval;
        filename_script[path] = script;
		JSAutoCompartment ac(cx, global);
        evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
        if (JS_FALSE == evaluatedOK) {
            fprintf(stderr, "(evaluatedOK == JS_FALSE)\n");
        }
    }
    return evaluatedOK;
}

ScriptingCore::~ScriptingCore()
{
    JS_DestroyContext(cx_);
    JS_DestroyRuntime(rt_);
    JS_ShutDown();
    if (_js_log_buf) {
        free(_js_log_buf);
        _js_log_buf = NULL;
    }
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
            char *cstr = JS_EncodeString(cx, string);
            js_log(cstr);
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
        const char* path = JS_EncodeString(cx, str);
        JSBool res = false;
        if (argc == 2 && argv[1].isString()) {
            JSString* globalName = JSVAL_TO_STRING(argv[1]);
            const char* name = JS_EncodeString(cx, globalName);
            js::RootedObject* rootedGlobal = globals[name];
            if (rootedGlobal) {
                JS_free(cx, (void*)name);
                res = ScriptingCore::getInstance()->runScript(path, rootedGlobal->get());
            } else {
                JS_ReportError(cx, "Invalid global object: %s", name);
                return JS_FALSE;
            }
        } else {
            JSObject* glob = JS_GetGlobalForScopeChain(cx);
            res = ScriptingCore::getInstance()->runScript(path, glob);
        }
        JS_free(cx, (void*)path);
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
        arr->removeAllObjects();
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

int ScriptingCore::executeSchedule(CCTimer* pTimer, float dt, CCNode* pNode/* = NULL*/)
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
    executeFunctionWithObjectData(pLayer,  funcName.c_str(), jsObj);
    
    removeJSTouchObject(this->getGlobalContext(), pTouch, jsret);
    
    return 1;
}

int ScriptingCore::executeFunctionWithObjectData(CCNode *self, const char *name, JSObject *obj) {

    js_proxy_t * p;
    JS_GET_PROXY(p, self);
    if (!p) return 0;

    jsval retval;
    jsval dataVal = OBJECT_TO_JSVAL(obj);

    executeJSFunctionWithName(this->cx_, p->obj, name, dataVal, retval);

    return 1;
}

int ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, jsval data) {
    jsval retval;

    executeJSFunctionWithName(this->cx_, JSVAL_TO_OBJECT(owner), name, data, retval);

    return 1;
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
    return 1;

}

#pragma mark - Conversion Routines

long long jsval_to_long_long(JSContext *cx, jsval v) {
    JSObject *tmp = JSVAL_TO_OBJECT(v);
    if (JS_IsTypedArrayObject(tmp, cx) && JS_GetTypedArrayByteLength(tmp, cx) == 8) {
        uint32_t *data = (uint32_t *)JS_GetUint32ArrayData(tmp, cx);
        long long r = (long long)(*data);
        return r;
    }
    return 0;
}

std::string jsval_to_std_string(JSContext *cx, jsval v) {
    JSString *tmp = JS_ValueToString(cx, v);
    char *rawStr = JS_EncodeString(cx, tmp);
    std::string ret = std::string(rawStr);
    JS_free(cx, rawStr);
    return ret;
}

const char* jsval_to_c_string(JSContext *cx, jsval v) {
    JSString *tmp = JS_ValueToString(cx, v);
    return JS_EncodeString(cx, tmp);
}

CCPoint jsval_to_ccpoint(JSContext *cx, jsval v) {
    JSObject *tmp;
    jsval jsx, jsy;
    double x, y;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "x", &jsx) &&
        JS_GetProperty(cx, tmp, "y", &jsy) &&
        JS_ValueToNumber(cx, jsx, &x) &&
        JS_ValueToNumber(cx, jsy, &y);
    assert(ok == JS_TRUE);
    return cocos2d::CCPoint(x, y);
}

CCRect jsval_to_ccrect(JSContext *cx, jsval v) {
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
    assert(ok == JS_TRUE);
    return cocos2d::CCRect(x, y, width, height);
}

CCSize jsval_to_ccsize(JSContext *cx, jsval v) {
    JSObject *tmp;
    jsval jsw, jsh;
    double w, h;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "width", &jsw) &&
        JS_GetProperty(cx, tmp, "height", &jsh) &&
        JS_ValueToNumber(cx, jsw, &w) &&
        JS_ValueToNumber(cx, jsh, &h);
    assert(ok == JS_TRUE);
    return cocos2d::CCSize(w, h);
}

ccGridSize jsval_to_ccgridsize(JSContext *cx, jsval v) {
    JSObject *tmp;
    jsval jsx, jsy;
    double x, y;
    JSBool ok = JS_ValueToObject(cx, v, &tmp) &&
        JS_GetProperty(cx, tmp, "x", &jsx) &&
        JS_GetProperty(cx, tmp, "y", &jsy) &&
        JS_ValueToNumber(cx, jsx, &x) &&
        JS_ValueToNumber(cx, jsy, &y);
    assert(ok == JS_TRUE);
    return cocos2d::ccg(x, y);
}

ccColor4B jsval_to_cccolor4b(JSContext *cx, jsval v) {
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
    assert(ok == JS_TRUE);
    return cocos2d::ccc4(r, g, b, a);
}

ccColor4F jsval_to_cccolor4f(JSContext *cx, jsval v) {
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
    assert(ok == JS_TRUE);
    return cocos2d::ccc4f(r, g, b, a);
}

ccColor3B jsval_to_cccolor3b(JSContext *cx, jsval v) {
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
    assert(ok == JS_TRUE);
    return cocos2d::ccc3(r, g, b);
}

JSBool jsval_to_ccarray_of_CCPoint(JSContext* cx, jsval v, CCPoint **points, int *numPoints) {
    // Parsing sequence
    JSObject *jsobj;
    JSBool ok = JS_ValueToObject( cx, v, &jsobj );
    if(!jsobj || !JS_IsArrayObject( cx, jsobj)) return JS_FALSE;

    uint32_t len;
    JS_GetArrayLength(cx, jsobj, &len);

    CCPoint *array = (CCPoint*)malloc( sizeof(CCPoint) * len);

    for( uint32_t i=0; i< len;i++ ) {
        jsval valarg;
        JS_GetElement(cx, jsobj, i, &valarg);

        array[i] = jsval_to_ccpoint(cx, valarg);
    }

    *numPoints = len;
    *points = array;

    return JS_TRUE;
}


CCArray* jsval_to_ccarray(JSContext* cx, jsval v) {
    JSObject *arr;
    if (JS_ValueToObject(cx, v, &arr) && JS_IsArrayObject(cx, arr)) {
        uint32_t len = 0;
        JS_GetArrayLength(cx, arr, &len);
        CCArray* ret = CCArray::createWithCapacity(len);
        for (int i=0; i < len; i++) {
            jsval elt;
            JSObject *elto;
            if (JS_GetElement(cx, arr, i, &elt) && JS_ValueToObject(cx, elt, &elto)) {
                js_proxy_t *proxy;
                JS_GET_NATIVE_PROXY(proxy, elto);
                if (proxy) {
                    ret->addObject((CCObject *)proxy->ptr);
                }
            }
        }
        return ret;
    }
    return NULL;
}


jsval ccarray_to_jsval(JSContext* cx, CCArray *arr) {
    
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);
    
    for(int i = 0; i < arr->count(); ++i) {
        jsval arrElement;
        CCObject *obj = arr->objectAtIndex(i);
        
        CCString *testString = dynamic_cast<cocos2d::CCString *>(obj);
        if(testString) {
            arrElement = c_string_to_jsval(cx, testString->getCString());
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

jsval long_long_to_jsval(JSContext* cx, long long v) {
    JSObject *tmp = JS_NewUint32Array(cx, 2);
    uint32_t *data = (uint32_t *)JS_GetArrayBufferViewData(tmp, cx);
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

jsval ccgridsize_to_jsval(JSContext* cx, ccGridSize& v) {
    JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    if (!tmp) return JSVAL_NULL;
    JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(v.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(v.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
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

#pragma mark - Debug Socket

JSObject* NewGlobalObject(JSContext* cx)
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
	if (ok)
		ok = JS_DefineDebuggerObject(cx, glob);
	if (!ok)
		return NULL;

    return glob;
}

JSBool jsNewGlobal(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 1) {
        jsval *argv = JS_ARGV(cx, vp);
        JSString *jsstr = JS_ValueToString(cx, argv[0]);
        std::string key = JS_EncodeString(cx, jsstr);
        js::RootedObject *global = globals[key];
        if (!global) {
            JSObject* g = NewGlobalObject(cx);
            global = new js::RootedObject(cx, g);
            JS_WrapObject(cx, global->address());
            globals[key] = global;
            // register everything on the list on this new global object
			JSAutoCompartment ac(cx, g);
            for (std::vector<sc_register_sth>::iterator it = registrationList.begin(); it != registrationList.end(); it++) {
                sc_register_sth callback = *it;
                callback(cx, g);
            }
        }
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(*global));
        return JS_TRUE;
    }
    return JS_FALSE;
}

// open a socket, bind it to a port and start listening, all at once :)
JSBool jsSocketOpen(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 2) {
        jsval* argv = JS_ARGV(cx, vp);
        int port = JSVAL_TO_INT(argv[0]);
        JSObject* callback = JSVAL_TO_OBJECT(argv[1]);

        int s;
        s = ports_sockets[port];
        if (!s) {
            char myname[256];
            struct sockaddr_in sa;
            struct hostent *hp;
            memset(&sa, 0, sizeof(struct sockaddr_in));
            gethostname(myname, 256);
            hp = gethostbyname(myname);
            sa.sin_family = hp->h_addrtype;
            sa.sin_port = htons(port);
            if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
                JS_ReportError(cx, "error opening socket");
                return JS_FALSE;
            }
            int optval = 1;
            if ((setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval))) < 0) {
                close(s);
                JS_ReportError(cx, "error setting socket options");
                return JS_FALSE;
            }
            if ((bind(s, (const struct sockaddr *)&sa, sizeof(struct sockaddr_in))) < 0) {
                close(s);
                JS_ReportError(cx, "error binding socket");
                return JS_FALSE;
            }
            listen(s, 1);
            int clientSocket;
            if ((clientSocket = accept(s, NULL, NULL)) > 0) {
                ports_sockets[port] = clientSocket;
                jsval fval = OBJECT_TO_JSVAL(callback);
                jsval jsSocket = INT_TO_JSVAL(clientSocket);
                jsval outVal;
                JS_CallFunctionValue(cx, NULL, fval, 1, &jsSocket, &outVal);
            }
        } else {
            // just call the callback with the client socket
            jsval fval = OBJECT_TO_JSVAL(callback);
            jsval jsSocket = INT_TO_JSVAL(s);
            jsval outVal;
            JS_CallFunctionValue(cx, NULL, fval, 1, &jsSocket, &outVal);
        }
        JS_SET_RVAL(cx, vp, INT_TO_JSVAL(s));
    }
    return JS_TRUE;
}

JSBool jsSocketRead(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 1) {
        jsval* argv = JS_ARGV(cx, vp);
        int s = JSVAL_TO_INT(argv[0]);
        char buff[1024];
        JSString* outStr = JS_NewStringCopyZ(cx, "");

        size_t bytesRead;
        while ((bytesRead = read(s, buff, 1024)) > 0) {
            JSString* newStr = JS_NewStringCopyN(cx, buff, bytesRead);
            outStr = JS_ConcatStrings(cx, outStr, newStr);
            // break on new line
            if (buff[bytesRead-1] == '\n') {
                break;
            }
        }
        JS_SET_RVAL(cx, vp, STRING_TO_JSVAL(outStr));
    } else {
        JS_SET_RVAL(cx, vp, JSVAL_NULL);
    }
    return JS_TRUE;
}

JSBool jsSocketWrite(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 2) {
        jsval* argv = JS_ARGV(cx, vp);
        int s;
        const char* str;

        s = JSVAL_TO_INT(argv[0]);
        JSString* jsstr = JS_ValueToString(cx, argv[1]);
        str = JS_EncodeString(cx, jsstr);

        write(s, str, strlen(str));

        JS_free(cx, (void*)str);
    }
    return JS_TRUE;
}

JSBool jsSocketClose(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 1) {
        jsval* argv = JS_ARGV(cx, vp);
        int s = JSVAL_TO_INT(argv[0]);
        close(s);
    }
    return JS_TRUE;
}
