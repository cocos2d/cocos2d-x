//
//  ScriptingCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include "ScriptingCore.h"

// Removed in Firefox v27, use 'js/OldDebugAPI.h' instead
//#include "jsdbgapi.h"
#include "js/OldDebugAPI.h"

#include "cocos2d.h"
#include "local-storage/LocalStorage.h"
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

#include <thread>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <map>

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

#if COCOS2D_DEBUG
#define TRACE_DEBUGGER_SERVER(...) CCLOG(__VA_ARGS__)
#else
#define TRACE_DEBUGGER_SERVER(...)
#endif // #if DEBUG

#define BYTE_CODE_FILE_EXT ".jsc"

using namespace cocos2d;

static std::string inData;
static std::string outData;
static std::vector<std::string> g_queue;
static std::mutex g_qMutex;
static std::mutex g_rwMutex;
static int clientSocket = -1;
static uint32_t s_nestedLoopLevel = 0;

// server entry point for the bg thread
static void serverEntryPoint(void);

js_proxy_t *_native_js_global_ht = NULL;
js_proxy_t *_js_native_global_ht = NULL;
std::unordered_map<std::string, js_type_class_t*> _js_global_type_map;

static char *_js_log_buf = NULL;

static std::vector<sc_register_sth> registrationList;

// name ~> JSScript map
static std::unordered_map<std::string, JSScript*> filename_script;
// port ~> socket map
static std::unordered_map<int,int> ports_sockets;
// name ~> globals
static std::unordered_map<std::string, JS::RootedObject*> globals;

static void ReportException(JSContext *cx)
{
    if (JS_IsExceptionPending(cx)) {
        if (!JS_ReportPendingException(cx)) {
            JS_ClearPendingException(cx);
        }
    }
}

static void executeJSFunctionFromReservedSpot(JSContext *cx, JSObject *obj,
                                              jsval &dataVal, jsval &retval) {

    jsval func = JS_GetReservedSlot(obj, 0);

    if (func == JSVAL_VOID) { return; }
    jsval thisObj = JS_GetReservedSlot(obj, 1);
    JSAutoCompartment ac(cx, obj);
    
    if (thisObj == JSVAL_VOID) {
        JS_CallFunctionValue(cx, obj, func, 1, &dataVal, &retval);
    } else {
        assert(!JSVAL_IS_PRIMITIVE(thisObj));
        JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(thisObj), func, 1, &dataVal, &retval);
    }
}

static void getTouchesFuncName(EventTouch::EventCode eventCode, std::string &funcName)
{
    switch(eventCode)
    {
        case EventTouch::EventCode::BEGAN:
            funcName = "onTouchesBegan";
            break;
        case EventTouch::EventCode::ENDED:
            funcName = "onTouchesEnded";
            break;
        case EventTouch::EventCode::MOVED:
            funcName = "onTouchesMoved";
            break;
        case EventTouch::EventCode::CANCELLED:
            funcName = "onTouchesCancelled";
            break;
    }
}

static void getTouchFuncName(EventTouch::EventCode eventCode, std::string &funcName)
{
    switch(eventCode) {
        case EventTouch::EventCode::BEGAN:
            funcName = "onTouchBegan";
            break;
        case EventTouch::EventCode::ENDED:
            funcName = "onTouchEnded";
            break;
        case EventTouch::EventCode::MOVED:
            funcName = "onTouchMoved";
            break;
        case EventTouch::EventCode::CANCELLED:
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

static void getJSTouchObject(JSContext *cx, Touch *x, jsval &jsret) {
    js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Touch>(cx, x);
    jsret = OBJECT_TO_JSVAL(proxy->obj);
}

static void removeJSTouchObject(JSContext *cx, Touch *x, jsval &jsret) {
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    void *ptr = (void*)x;
    nproxy = jsb_get_native_proxy(ptr);
    if (nproxy) {
        jsproxy = jsb_get_js_proxy(nproxy->obj);
        JS_RemoveObjectRoot(cx, &jsproxy->obj);
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void ScriptingCore::executeJSFunctionWithThisObj(jsval thisObj,
                                                 jsval callback,
                                                 uint32_t argc/* = 0*/,
                                                 jsval* vp/* = NULL*/,
                                                 jsval* retVal/* = NULL*/)
{
    if (callback != JSVAL_VOID || thisObj != JSVAL_VOID)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        // Very important: The last parameter 'retVal' passed to 'JS_CallFunctionValue' should not be a NULL pointer.
        // If it's a NULL pointer, crash will be triggered in 'JS_CallFunctionValue'. To find out the reason of this crash is very difficult.
        // So we have to check the availability of 'retVal'.
        if (retVal)
        {
            JS_CallFunctionValue(_cx, JSVAL_TO_OBJECT(thisObj), callback, argc, vp, retVal);
        }
        else
        {
            jsval jsRet;
            JS_CallFunctionValue(_cx, JSVAL_TO_OBJECT(thisObj), callback, argc, vp, &jsRet);
        }
    }
}

void js_log(const char *format, ...) {

    if (_js_log_buf == NULL)
    {
        _js_log_buf = (char *)calloc(sizeof(char), MAX_LOG_LENGTH+1);
        _js_log_buf[MAX_LOG_LENGTH] = '\0';
    }
    va_list vl;
    va_start(vl, format);
    int len = vsnprintf(_js_log_buf, MAX_LOG_LENGTH, format, vl);
    va_end(vl);
    if (len > 0)
    {
        CCLOG("JS: %s\n", _js_log_buf);
    }
}

#define JSB_COMPATIBLE_WITH_COCOS2D_HTML5_BASIC_TYPES 1

bool JSBCore_platform(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getPlatform");
        return false;
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

    return true;
};

bool JSBCore_version(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getVersion");
        return false;
    }

    char version[256];
    snprintf(version, sizeof(version)-1, "%s", cocos2dVersion());
    JSString * js_version = JS_InternString(cx, version);

    jsval ret = STRING_TO_JSVAL(js_version);
    JS_SET_RVAL(cx, vp, ret);

    return true;
};

bool JSBCore_os(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getOS");
        return false;
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

    return true;
};

bool JSB_core_restartVM(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments in executeScript");
    ScriptingCore::getInstance()->reset();
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
	return true;
};

void registerDefaultClasses(JSContext* cx, JSObject* global) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, global, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, global, "cc", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }

    //
    // Javascript controller (__jsc__)
    //
    JSObject *jsc = JS_NewObject(cx, NULL, NULL, NULL);
    JS::RootedValue jscVal(cx);
    jscVal = OBJECT_TO_JSVAL(jsc);
    JS_SetProperty(cx, global, "__jsc__", jscVal);

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
    JS_DefineFunction(cx, global, "__restartVM", JSB_core_restartVM, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}

static void sc_finalize(JSFreeOp *freeOp, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (global class)", obj);
}

static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, sc_finalize,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

ScriptingCore::ScriptingCore()
: _rt(nullptr)
, _cx(nullptr)
, _global(nullptr)
, _debugGlobal(nullptr)
{
    // set utf8 strings internally (we don't need utf16)
    // XXX: Removed in SpiderMonkey 19.0
    //JS_SetCStringsAreUTF8();
    this->addRegisterCallback(registerDefaultClasses);
    this->_runLoop = new SimpleRunLoop();
}

void ScriptingCore::string_report(jsval val) {
    if (JSVAL_IS_NULL(val)) {
        LOGD("val : (JSVAL_IS_NULL(val)");
        // return 1;
    } else if ((JSVAL_IS_BOOLEAN(val)) &&
               (false == (JSVAL_TO_BOOLEAN(val)))) {
        LOGD("val : (return value is false");
        // return 1;
    } else if (JSVAL_IS_STRING(val)) {
        JSString *str = JS_ValueToString(this->getGlobalContext(), val);
        if (NULL == str) {
            LOGD("val : return string is NULL");
        } else {
            JSStringWrapper wrapper(str);
            LOGD("val : return string =\n%s\n", wrapper.get());
        }
    } else if (JSVAL_IS_NUMBER(val)) {
        double number;
        if (false ==
            JS::ToNumber(this->getGlobalContext(), JS::RootedValue(_cx, val), &number)) {
            LOGD("val : return number could not be converted");
        } else {
            LOGD("val : return number =\n%f", number);
        }
    }
}

bool ScriptingCore::evalString(const char *string, jsval *outVal, const char *filename, JSContext* cx, JSObject* global)
{
    if (cx == NULL)
        cx = _cx;
    if (global == NULL)
        global = _global;
    
    JSAutoCompartment ac(cx, global);
    
    JSScript* script = JS_CompileScript(cx, global, string, strlen(string), filename, 1);
    if (script)
    {
        bool evaluatedOK = JS_ExecuteScript(cx, global, script, outVal);
        if (false == evaluatedOK)
        {
            fprintf(stderr, "(evaluatedOK == false)\n");
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

static JSPrincipals shellTrustedPrincipals = { 1 };

static bool
CheckObjectAccess(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JSAccessMode mode,
                  JS::MutableHandleValue vp)
{
    return true;
}

static JSSecurityCallbacks securityCallbacks = {
    CheckObjectAccess,
    NULL
};

void ScriptingCore::createGlobalContext() {
    if (this->_cx && this->_rt) {
        ScriptingCore::removeAllRoots(this->_cx);
        JS_DestroyContext(this->_cx);
        JS_DestroyRuntime(this->_rt);
        this->_cx = NULL;
        this->_rt = NULL;
    }
    
    // Start the engine. Added in SpiderMonkey v25
    if (!JS_Init())
        return;
    
    // Removed from Spidermonkey 19.
    //JS_SetCStringsAreUTF8();
    this->_rt = JS_NewRuntime(8L * 1024L * 1024L, JS_USE_HELPER_THREADS);
    JS_SetGCParameter(_rt, JSGC_MAX_BYTES, 0xffffffff);
	
    JS_SetTrustedPrincipals(_rt, &shellTrustedPrincipals);
    JS_SetSecurityCallbacks(_rt, &securityCallbacks);
	JS_SetNativeStackQuota(_rt, JSB_MAX_STACK_QUOTA);
    
    this->_cx = JS_NewContext(_rt, 8192);
    
    // Removed in Firefox v27
//    JS_SetOptions(this->_cx, JSOPTION_TYPE_INFERENCE);
    JS::ContextOptionsRef(_cx).setTypeInference(true);
    
//    JS_SetVersion(this->_cx, JSVERSION_LATEST);
    
    // Only disable METHODJIT on iOS.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    JS_SetOptions(this->_cx, JS_GetOptions(this->_cx) & ~JSOPTION_METHODJIT);
//    JS_SetOptions(this->_cx, JS_GetOptions(this->_cx) & ~JSOPTION_METHODJIT_ALWAYS);
#endif
    
    JS_SetErrorReporter(this->_cx, ScriptingCore::reportError);
#if defined(JS_GC_ZEAL) && defined(DEBUG)
    //JS_SetGCZeal(this->_cx, 2, JS_DEFAULT_ZEAL_FREQ);
#endif
    this->_global = NewGlobalObject(_cx);

    JSAutoCompartment ac(_cx, _global);
    js::SetDefaultObjectForContext(_cx, _global);
    
    for (std::vector<sc_register_sth>::iterator it = registrationList.begin(); it != registrationList.end(); it++) {
        sc_register_sth callback = *it;
        callback(this->_cx, this->_global);
    }
}

static std::string RemoveFileExt(const std::string& filePath) {
    size_t pos = filePath.rfind('.');
    if (0 < pos) {
        return filePath.substr(0, pos);
    }
    else {
        return filePath;
    }
}

void ScriptingCore::compileScript(const char *path, JSObject* global, JSContext* cx)
{
	if (!path) {
		return ;
	}

	cocos2d::FileUtils *futil = cocos2d::FileUtils::getInstance();

	if (global == NULL) {
		global = _global;
	}
	if (cx == NULL) {
		cx = _cx;
	}

	JSAutoCompartment ac(cx, global);

	JS::RootedScript script(cx);
	JS::RootedObject obj(cx, global);

	// a) check jsc file first
	std::string byteCodePath = RemoveFileExt(std::string(path)) + BYTE_CODE_FILE_EXT;

	Data data = futil->getDataFromFile(byteCodePath);

	if (!data.isNull())
	{
		script = JS_DecodeScript(cx, data.getBytes(), static_cast<uint32_t>(data.getSize()), nullptr, nullptr);
	}

	// b) no jsc file, check js file
	if (!script)
	{
		/* Clear any pending exception from previous failed decoding.  */
		ReportException(cx);

		std::string fullPath = futil->fullPathForFilename(path);
		JS::CompileOptions options(cx);
		options.setUTF8(true).setFileAndLine(fullPath.c_str(), 1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		std::string jsFileContent = futil->getStringFromFile(fullPath);
		if (!jsFileContent.empty())
		{
			script = JS::Compile(cx, obj, options, jsFileContent.c_str(), jsFileContent.size());
		}
#else
		script = JS::Compile(cx, obj, options, fullPath.c_str());
#endif
	}
	if (script) {
		filename_script[path] = script;
	}
}

bool ScriptingCore::runScript(const char *path, JSObject* global, JSContext* cx)
{
	if (global == NULL) {
		global = _global;
	}
	if (cx == NULL) {
		cx = _cx;
	}
	if (!filename_script[path])
	{
		compileScript(path,global,cx );
	}
	JSScript * script = filename_script[path];
	bool evaluatedOK = false;
	if (script) {
		jsval rval;
		JSAutoCompartment ac(cx, global);
		evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
		if (false == evaluatedOK) {
			cocos2d::log("(evaluatedOK == JS_FALSE)");
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
    removeAllRoots(_cx);
    if (_cx)
    {
        JS_DestroyContext(_cx);
        _cx = NULL;
    }
    if (_rt)
    {
        JS_DestroyRuntime(_rt);
        _rt = NULL;
    }
    JS_ShutDown();
    if (_js_log_buf) {
        free(_js_log_buf);
        _js_log_buf = NULL;
    }

    for (auto iter = _js_global_type_map.begin(); iter != _js_global_type_map.end(); ++iter)
    {
        free(iter->second->jsclass);
        free(iter->second);
    }
    
    _js_global_type_map.clear();
}

void ScriptingCore::reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    js_log("%s:%u:%s\n",
            report->filename ? report->filename : "<no filename=\"filename\">",
            (unsigned int) report->lineno,
            message);
};


bool ScriptingCore::log(JSContext* cx, uint32_t argc, jsval *vp)
{
    if (argc > 0) {
        JSString *string = NULL;
        JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string);
        if (string) {
            JSStringWrapper wrapper(string);
            js_log("%s", wrapper.get());
        }
    }
    return true;
}


void ScriptingCore::removeScriptObjectByObject(Ref* pObj)
{
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    void *ptr = (void*)pObj;
    nproxy = jsb_get_native_proxy(ptr);
    if (nproxy) {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        jsproxy = jsb_get_js_proxy(nproxy->obj);
        JS_RemoveObjectRoot(cx, &jsproxy->obj);
        jsb_remove_proxy(nproxy, jsproxy);
    }
}


bool ScriptingCore::setReservedSpot(uint32_t i, JSObject *obj, jsval value) {
    JS_SetReservedSlot(obj, i, value);
    return true;
}

bool ScriptingCore::executeScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSString* str = JS_ValueToString(cx, argv[0]);
        JSStringWrapper path(str);
        bool res = false;
        if (argc == 2 && argv[1].isString()) {
            JSString* globalName = JSVAL_TO_STRING(argv[1]);
            JSStringWrapper name(globalName);
//            JS::RootedObject* rootedGlobal = globals[name];
            JSObject* debugObj = ScriptingCore::getInstance()->getDebugGlobal();
            if (debugObj) {
                res = ScriptingCore::getInstance()->runScript(path.get(), debugObj);
            } else {
                JS_ReportError(cx, "Invalid global object: %s", name.get());
                return false;
            }
        } else {
            JSObject* glob = JS::CurrentGlobalOrNull(cx);
            res = ScriptingCore::getInstance()->runScript(path.get(), glob);
        }
        return res;
    }
    return true;
}

bool ScriptingCore::forceGC(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSRuntime *rt = JS_GetRuntime(cx);
    JS_GC(rt);
    return true;
}

//static void dumpNamedRoot(const char *name, void *addr,  JSGCRootType type, void *data)
//{
//    CCLOG("Root: '%s' at %p", name, addr);
//}

bool ScriptingCore::dumpRoot(JSContext *cx, uint32_t argc, jsval *vp)
{
    // JS_DumpNamedRoots is only available on DEBUG versions of SpiderMonkey.
    // Mac and Simulator versions were compiled with DEBUG.
#if COCOS2D_DEBUG
//    JSContext *_cx = ScriptingCore::getInstance()->getGlobalContext();
//    JSRuntime *rt = JS_GetRuntime(_cx);
//    JS_DumpNamedRoots(rt, dumpNamedRoot, NULL);
//    JS_DumpHeap(rt, stdout, NULL, JSTRACE_OBJECT, NULL, 2, NULL);
#endif
    return true;
}

bool ScriptingCore::addRootJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSObject *o = NULL;
        if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == true) {
            if (JS_AddNamedObjectRoot(cx, &o, "from-js") == false) {
                LOGD("something went wrong when setting an object to the root");
            }
        }
        return true;
    }
    return false;
}

bool ScriptingCore::removeRootJS(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JSObject *o = NULL;
        if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "o", &o) == true) {
            JS_RemoveObjectRoot(cx, &o);
        }
        return true;
    }
    return false;
}

void ScriptingCore::pauseSchedulesAndActions(js_proxy_t* p)
{
    Array * arr = JSScheduleWrapper::getTargetForJSObject(p->obj);
    if (! arr) return;
    
    Node* node = (Node*)p->ptr;
    for(unsigned int i = 0; i < arr->count(); ++i) {
        if (arr->getObjectAtIndex(i)) {
            node->getScheduler()->pauseTarget(arr->getObjectAtIndex(i));
        }
    }
}


void ScriptingCore::resumeSchedulesAndActions(js_proxy_t* p)
{
    Array * arr = JSScheduleWrapper::getTargetForJSObject(p->obj);
    if (!arr) return;
    
    Node* node = (Node*)p->ptr;
    for(unsigned int i = 0; i < arr->count(); ++i) {
        if (!arr->getObjectAtIndex(i)) continue;
        node->getScheduler()->resumeTarget(arr->getObjectAtIndex(i));
    }
}

void ScriptingCore::cleanupSchedulesAndActions(js_proxy_t* p)
{
    Array* arr = JSScheduleWrapper::getTargetForJSObject(p->obj);
    if (arr) {
        Scheduler* pScheduler = Director::getInstance()->getScheduler();
        Ref* pObj = NULL;
        CCARRAY_FOREACH(arr, pObj)
        {
            pScheduler->unscheduleAllForTarget(pObj);
        }

        JSScheduleWrapper::removeAllTargetsForJSObject(p->obj);
    }
}

int ScriptingCore::handleNodeEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject || NULL == basicScriptData->value)
        return 0;
    
    Node* node = static_cast<Node*>(basicScriptData->nativeObject);
    int action = *((int*)(basicScriptData->value));
                                                         
    js_proxy_t * p = jsb_get_native_proxy(node);
    if (!p) return 0;

    jsval retval;
    jsval dataVal = INT_TO_JSVAL(1);

    if (action == kNodeOnEnter)
    {
        executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onEnter", 1, &dataVal, &retval);
        resumeSchedulesAndActions(p);
    }
    else if (action == kNodeOnExit)
    {
        executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onExit", 1, &dataVal, &retval);
        pauseSchedulesAndActions(p);
    }
    else if (action == kNodeOnEnterTransitionDidFinish)
    {
        executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onEnterTransitionDidFinish", 1, &dataVal, &retval);
    }
    else if (action == kNodeOnExitTransitionDidStart)
    {
        executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onExitTransitionDidStart", 1, &dataVal, &retval);
    }
    else if (action == kNodeOnCleanup) {
        cleanupSchedulesAndActions(p);
    }

    return 1;
}

int ScriptingCore::handleMenuClickedEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject)
        return 0;
    
    MenuItem* menuItem = static_cast<MenuItem*>(basicScriptData->nativeObject);
    
    js_proxy_t * p = jsb_get_native_proxy(menuItem);
    if (!p) return 0;

    jsval retval;
    jsval dataVal;
    js_proxy_t *proxy = jsb_get_native_proxy(menuItem);
    dataVal = (proxy ? OBJECT_TO_JSVAL(proxy->obj) : JSVAL_NULL);

    executeJSFunctionFromReservedSpot(this->_cx, p->obj, dataVal, retval);

    return 1;
}

int ScriptingCore::handleTouchesEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    TouchesScriptData* touchesScriptData = static_cast<TouchesScriptData*>(data);
    if (NULL == touchesScriptData->nativeObject || touchesScriptData->touches.empty())
        return 0;
    
    Layer* pLayer = static_cast<Layer*>(touchesScriptData->nativeObject);
    EventTouch::EventCode eventType = touchesScriptData->actionType;
    const std::vector<Touch*>& touches = touchesScriptData->touches;
    
    std::string funcName = "";
    getTouchesFuncName(eventType, funcName);

    JSObject *jsretArr = JS_NewArrayObject(this->_cx, 0, NULL);

    JS_AddNamedObjectRoot(this->_cx, &jsretArr, "touchArray");
    int count = 0;
    
    for (auto& touch : touches)
    {
        jsval jsval;
        getJSTouchObject(this->_cx, touch, jsval);
        JS::RootedValue jsret(_cx, jsval);
        if (!JS_SetElement(this->_cx, jsretArr, count, &jsret))
        {
            break;
        }
        ++count;
    }

    executeFunctionWithObjectData(pLayer,  funcName.c_str(), jsretArr);

    JS_RemoveObjectRoot(this->_cx, &jsretArr);

    for (auto& touch : touches)
    {
        jsval jsret;
        removeJSTouchObject(this->_cx, touch, jsret);
    }

    return 1;
}

int ScriptingCore::handleTouchEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    TouchScriptData* touchScriptData = static_cast<TouchScriptData*>(data);
    if (NULL == touchScriptData->nativeObject || NULL == touchScriptData->touch)
        return 0;
    
    Layer* pLayer = static_cast<Layer*>(touchScriptData->nativeObject);
    EventTouch::EventCode eventType = touchScriptData->actionType;
    Touch *pTouch = touchScriptData->touch;

    
    std::string funcName = "";
    getTouchFuncName(eventType, funcName);

    jsval jsret;
    getJSTouchObject(this->getGlobalContext(), pTouch, jsret);
    JSObject *jsObj = JSVAL_TO_OBJECT(jsret);
    bool retval = executeFunctionWithObjectData(pLayer,  funcName.c_str(), jsObj);

    removeJSTouchObject(this->getGlobalContext(), pTouch, jsret);

    return retval;
}

bool ScriptingCore::executeFunctionWithObjectData(Node *self, const char *name, JSObject *obj) {

    js_proxy_t * p = jsb_get_native_proxy(self);
    if (!p) return false;

    jsval retval;
    jsval dataVal = OBJECT_TO_JSVAL(obj);

    executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), name, 1, &dataVal, &retval);
    if (JSVAL_IS_NULL(retval)) {
        return false;
    }
    else if (JSVAL_IS_BOOLEAN(retval)) {
        return JSVAL_TO_BOOLEAN(retval);
    }
    return false;
}

bool ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc /* = 0 */, jsval *vp /* = NULL */, jsval* retVal /* = NULL */)
{
    bool bRet = false;
    bool hasAction;
    JSContext* cx = this->_cx;
    JS::RootedValue temp_retval(cx);
    JSObject* obj = JSVAL_TO_OBJECT(owner);
    
    do
    {
        JSAutoCompartment ac(cx, obj);
        
        if (JS_HasProperty(cx, obj, name, &hasAction) && hasAction) {
            if (!JS_GetProperty(cx, obj, name, &temp_retval)) {
                break;
            }
            if (temp_retval == JSVAL_VOID) {
                break;
            }            
            
            if (retVal) {
                bRet = JS_CallFunctionName(cx, obj, name, argc, vp, retVal);
            }
            else {
                jsval jsret;
                bRet = JS_CallFunctionName(cx, obj, name, argc, vp, &jsret);
            }
        }
    }while(0);
    return bRet;
}

int ScriptingCore::handleAccelerometerEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject || NULL == basicScriptData->value)
        return 0;
    
    Acceleration* accelerationValue = static_cast<Acceleration*>(basicScriptData->value);
    Layer* layer = static_cast<Layer*>(basicScriptData->nativeObject);
    
    jsval value = ccacceleration_to_jsval(this->getGlobalContext(), *accelerationValue);
    JS_AddValueRoot(this->getGlobalContext(), &value);

    executeFunctionWithObjectData(layer, "onAccelerometer", JSVAL_TO_OBJECT(value));

    JS_RemoveValueRoot(this->getGlobalContext(), &value);
    return 1;
}

int ScriptingCore::handleKeypadEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    KeypadScriptData* keypadScriptData = static_cast<KeypadScriptData*>(data);
    if (NULL == keypadScriptData->nativeObject)
        return 0;
    
    EventKeyboard::KeyCode action = keypadScriptData->actionType;
    
	js_proxy_t * p = jsb_get_native_proxy(keypadScriptData->nativeObject);

	if (p)
    {
        bool ret = false;
        switch(action)
        {
        case EventKeyboard::KeyCode::KEY_BACKSPACE:
			ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onBackClicked");
            if (!ret)
            {
                ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "backClicked");
                if (ret)
                {
                    CCLOG("backClicked will be deprecated, please use onBackClicked instead.");
                }
            }
			break;
		case EventKeyboard::KeyCode::KEY_MENU:
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onMenuClicked");
            if (!ret)
            {
                ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "menuClicked");
                if (ret)
                {
                    CCLOG("menuClicked will be deprecated, please use onMenuClicked instead.");
                }
            }
			break;
		default:
			break;
		}
		return 1;
	}

	return 0;
}


int ScriptingCore::executeCustomTouchesEvent(EventTouch::EventCode eventType,
                                       const std::vector<Touch*>& touches, JSObject *obj)
{
    jsval retval;
    std::string funcName;
    getTouchesFuncName(eventType, funcName);

    JSObject *jsretArr = JS_NewArrayObject(this->_cx, 0, NULL);
    JS_AddNamedObjectRoot(this->_cx, &jsretArr, "touchArray");
    int count = 0;
    for (auto& touch : touches)
    {
        jsval jsret;
        getJSTouchObject(this->_cx, touch, jsret);
        JS::RootedValue jsval(_cx, jsret);
        if (!JS_SetElement(this->_cx, jsretArr, count, &jsval)) {
            break;
        }
        ++count;
    }

    jsval jsretArrVal = OBJECT_TO_JSVAL(jsretArr);
    executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), funcName.c_str(), 1, &jsretArrVal, &retval);
    JS_RemoveObjectRoot(this->_cx, &jsretArr);

    for (auto& touch : touches)
    {
        jsval jsret;
        removeJSTouchObject(this->_cx, touch, jsret);
    }

    return 1;
}


int ScriptingCore::executeCustomTouchEvent(EventTouch::EventCode eventType,
                                           Touch *pTouch, JSObject *obj)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    jsval retval;
    std::string funcName;
    getTouchFuncName(eventType, funcName);

    jsval jsTouch;
    getJSTouchObject(this->_cx, pTouch, jsTouch);

    executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), funcName.c_str(), 1, &jsTouch, &retval);

    // Remove touch object from global hash table and unroot it.
    removeJSTouchObject(this->_cx, pTouch, jsTouch);
    return 1;

}


int ScriptingCore::executeCustomTouchEvent(EventTouch::EventCode eventType,
                                           Touch *pTouch, JSObject *obj,
                                           jsval &retval)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    std::string funcName;
    getTouchFuncName(eventType, funcName);

    jsval jsTouch;
    getJSTouchObject(this->_cx, pTouch, jsTouch);

    executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), funcName.c_str(), 1, &jsTouch, &retval);

    // Remove touch object from global hash table and unroot it.
    removeJSTouchObject(this->_cx, pTouch, jsTouch);

    return 1;

}

int ScriptingCore::sendEvent(ScriptEvent* evt)
{
    if (NULL == evt)
        return 0;
 
    JSAutoCompartment ac(_cx, _global);
    
    switch (evt->type)
    {
        case kNodeEvent:
            {
                return handleNodeEvent(evt->data);
            }
            break;
        case kMenuClickedEvent:
            {
                return handleMenuClickedEvent(evt->data);
            }
            break;
        case kTouchEvent:
            {
                return handleTouchEvent(evt->data);
            }
            break;
        case kTouchesEvent:
            {
                return handleTouchesEvent(evt->data);
            }
            break;
        case kKeypadEvent:
            {
                return handleKeypadEvent(evt->data);
            }
            break;
        case kAccelerometerEvent:
            {
                return handleAccelerometerEvent(evt->data);
            }
            break;
        default:
            break;
    }
    
    return 0;
}

bool ScriptingCore::parseConfig(ConfigType type, const std::string &str)
{
    jsval args[2];
    args[0] = int32_to_jsval(_cx, static_cast<int>(type));
    args[1] = std_string_to_jsval(_cx, str);
    return (true == executeFunctionWithOwner(OBJECT_TO_JSVAL(_global), "__onParseConfig", 2, args));
}

#pragma mark - Debug

void SimpleRunLoop::update(float dt)
{
    g_qMutex.lock();
    size_t size = g_queue.size();
    g_qMutex.unlock();
    
    while (size > 0)
    {
        g_qMutex.lock();
        auto first = g_queue.begin();
        std::string str = *first;
        g_queue.erase(first);
        size = g_queue.size();
        g_qMutex.unlock();
        
        ScriptingCore::getInstance()->debugProcessInput(str);
    }
}

void ScriptingCore::debugProcessInput(const std::string& str)
{
    JSAutoCompartment ac(_cx, _debugGlobal);
    
    JSString* jsstr = JS_NewStringCopyZ(_cx, str.c_str());
    jsval argv = STRING_TO_JSVAL(jsstr);
    jsval outval;
    
    JS_CallFunctionName(_cx, _debugGlobal, "processInput", 1, &argv, &outval);
}

static bool NS_ProcessNextEvent()
{
    g_qMutex.lock();
    size_t size = g_queue.size();
    g_qMutex.unlock();
    
    while (size > 0)
    {
        g_qMutex.lock();
        auto first = g_queue.begin();
        std::string str = *first;
        g_queue.erase(first);
        size = g_queue.size();
        g_qMutex.unlock();
        
        ScriptingCore::getInstance()->debugProcessInput(str);
    }
//    std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    return true;
}

bool JSBDebug_enterNestedEventLoop(JSContext* cx, unsigned argc, jsval* vp)
{
    enum {
        NS_OK = 0,
        NS_ERROR_UNEXPECTED
    };
    
#define NS_SUCCEEDED(v) ((v) == NS_OK)
    
    int rv = NS_OK;
    
    uint32_t nestLevel = ++s_nestedLoopLevel;

    while (NS_SUCCEEDED(rv) && s_nestedLoopLevel >= nestLevel) {
        if (!NS_ProcessNextEvent())
            rv = NS_ERROR_UNEXPECTED;
    }
    
    CCASSERT(s_nestedLoopLevel <= nestLevel,
             "nested event didn't unwind properly");
    
    JS_SET_RVAL(cx, vp, UINT_TO_JSVAL(s_nestedLoopLevel));
    return true;
}

bool JSBDebug_exitNestedEventLoop(JSContext* cx, unsigned argc, jsval* vp)
{
    if (s_nestedLoopLevel > 0) {
        --s_nestedLoopLevel;
    } else {
        JS_SET_RVAL(cx, vp, UINT_TO_JSVAL(0));
        return true;
    }
    
    JS_SET_RVAL(cx, vp, UINT_TO_JSVAL(s_nestedLoopLevel));
    return true;
}

bool JSBDebug_getEventLoopNestLevel(JSContext* cx, unsigned argc, jsval* vp)
{
    JS_SET_RVAL(cx, vp, UINT_TO_JSVAL(s_nestedLoopLevel));
    return true;
}

//#pragma mark - Debugger

static void _clientSocketWriteAndClearString(std::string& s)
{
    ::send(clientSocket, s.c_str(), s.length(), 0);
    s.clear();
}

static void processInput(const std::string& data) {
    std::lock_guard<std::mutex> lk(g_qMutex);
    g_queue.push_back(data);
}

static void clearBuffers() {
    std::lock_guard<std::mutex> lk(g_rwMutex);
    // only process input if there's something and we're not locked
    if (inData.length() > 0) {
        processInput(inData);
        inData.clear();
    }
    if (outData.length() > 0) {
        _clientSocketWriteAndClearString(outData);
    }
}

static void serverEntryPoint(void)
{
    // start a server, accept the connection and keep reading data from it
    struct addrinfo hints, *result = nullptr, *rp = nullptr;
    int s = 0;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    
    std::stringstream portstr;
    portstr << JSB_DEBUGGER_PORT;
    
    int err = 0;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    WSADATA wsaData;
    err = WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif
    
    if ((err = getaddrinfo(NULL, portstr.str().c_str(), &hints, &result)) != 0) {
        LOGD("getaddrinfo error : %s\n", gai_strerror(err));
    }
    
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        if ((s = socket(rp->ai_family, rp->ai_socktype, 0)) < 0) {
            continue;
        }
        int optval = 1;
        if ((setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval))) < 0) {
            close(s);
			TRACE_DEBUGGER_SERVER("debug server : error setting socket option SO_REUSEADDR");
            return;
        }
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		if ((setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval))) < 0) {
			close(s);
			TRACE_DEBUGGER_SERVER("debug server : error setting socket option SO_NOSIGPIPE");
			return;
		}
#endif //(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        
        if ((::bind(s, rp->ai_addr, rp->ai_addrlen)) == 0) {
            break;
        }
        close(s);
        s = -1;
    }
    if (s < 0 || rp == NULL) {
		TRACE_DEBUGGER_SERVER("debug server : error creating/binding socket");
        return;
    }
    
    freeaddrinfo(result);
    
    listen(s, 1);
    
	while (true) {
        clientSocket = accept(s, NULL, NULL);
        
        if (clientSocket < 0)
        {
            TRACE_DEBUGGER_SERVER("debug server : error on accept");
            return;
        }
        else
        {
            // read/write data
            TRACE_DEBUGGER_SERVER("debug server : client connected");
            
            inData = "connected";
            // process any input, send any output
            clearBuffers();
            
            char buf[1024] = {0};
            int readBytes = 0;
            while ((readBytes = ::recv(clientSocket, buf, sizeof(buf), 0)) > 0)
            {
                buf[readBytes] = '\0';
                // TRACE_DEBUGGER_SERVER("debug server : received command >%s", buf);
                
                // no other thread is using this
                inData.append(buf);
                // process any input, send any output
                clearBuffers();
            } // while(read)
            
            close(clientSocket);
        }
	} // while(true)
}

bool JSBDebug_BufferWrite(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 1) {
        jsval* argv = JS_ARGV(cx, vp);
        JSStringWrapper strWrapper(argv[0]);
        // this is safe because we're already inside a lock (from clearBuffers)
        outData.append(strWrapper.get());
        _clientSocketWriteAndClearString(outData);
    }
    return true;
}

void ScriptingCore::enableDebugger()
{
    if (_debugGlobal == NULL)
    {
        JSAutoCompartment ac0(_cx, _global);
        
        JS_SetDebugMode(_cx, true);
        
        _debugGlobal = NewGlobalObject(_cx, true);
        // Adds the debugger object to root, otherwise it may be collected by GC.
        JS_AddObjectRoot(_cx, &_debugGlobal);
        JS::RootedObject rootedDebugObj(_cx, _debugGlobal);
        JS_WrapObject(_cx, &rootedDebugObj);
        JSAutoCompartment ac(_cx, _debugGlobal);
        // these are used in the debug program
        JS_DefineFunction(_cx, _debugGlobal, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, _debugGlobal, "_bufferWrite", JSBDebug_BufferWrite, 1, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, _debugGlobal, "_enterNestedEventLoop", JSBDebug_enterNestedEventLoop, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, _debugGlobal, "_exitNestedEventLoop", JSBDebug_exitNestedEventLoop, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, _debugGlobal, "_getEventLoopNestLevel", JSBDebug_getEventLoopNestLevel, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        
        
        runScript("jsb_debugger.js", _debugGlobal);
        
        // prepare the debugger
        jsval argv = OBJECT_TO_JSVAL(_global);
        jsval outval;
        bool ok = JS_CallFunctionName(_cx, _debugGlobal, "_prepareDebugger", 1, &argv, &outval);
        if (!ok) {
            JS_ReportPendingException(_cx);
        }
        
        // start bg thread
        auto t = std::thread(&serverEntryPoint);
        t.detach();

        Scheduler* scheduler = Director::getInstance()->getScheduler();
        scheduler->scheduleUpdate(CC_CALLBACK_1(SimpleRunLoop::update, this->_runLoop), this->_runLoop, 0, false);
    }
}

JSObject* NewGlobalObject(JSContext* cx, bool debug)
{
    JS::CompartmentOptions options;
    options.setVersion(JSVERSION_LATEST);
    
    JS::RootedObject glob(cx, JS_NewGlobalObject(cx, &global_class, NULL, JS::DontFireOnNewGlobalHook, options));
    if (!glob) {
        return NULL;
    }
    JSAutoCompartment ac(cx, glob);
    bool ok = true;
    ok = JS_InitStandardClasses(cx, glob);
    if (ok)
        JS_InitReflect(cx, glob);
    if (ok && debug)
        ok = JS_DefineDebuggerObject(cx, glob);
    if (!ok)
        return NULL;

    JS_FireOnNewGlobalObject(cx, glob);
    
    return glob;
}

bool jsb_set_reserved_slot(JSObject *obj, uint32_t idx, jsval value)
{
    const JSClass *klass = JS_GetClass(obj);
    unsigned int slots = JSCLASS_RESERVED_SLOTS(klass);
    if ( idx >= slots )
        return false;

    JS_SetReservedSlot(obj, idx, value);

    return true;
}

bool jsb_get_reserved_slot(JSObject *obj, uint32_t idx, jsval& ret)
{
    const JSClass *klass = JS_GetClass(obj);
    unsigned int slots = JSCLASS_RESERVED_SLOTS(klass);
    if ( idx >= slots )
        return false;

    ret = JS_GetReservedSlot(obj, idx);

    return true;
}

js_proxy_t* jsb_new_proxy(void* nativeObj, JSObject* jsObj)
{
    js_proxy_t* p = nullptr;
    JS_NEW_PROXY(p, nativeObj, jsObj);
    return p;
}

js_proxy_t* jsb_get_native_proxy(void* nativeObj)
{
    js_proxy_t* p = nullptr;
    JS_GET_PROXY(p, nativeObj);
    return p;
}

js_proxy_t* jsb_get_js_proxy(JSObject* jsObj)
{
    js_proxy_t* p = nullptr;
    JS_GET_NATIVE_PROXY(p, jsObj);
    return p;
}

void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy)
{
    JS_REMOVE_PROXY(nativeProxy, jsProxy);
}


