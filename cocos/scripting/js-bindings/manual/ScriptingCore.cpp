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

#include "scripting/js-bindings/manual/ScriptingCore.h"

// Removed in Firefox v27, use 'js/OldDebugAPI.h' instead
//#include "jsdbgapi.h"
#include "js/OldDebugAPI.h"

#include "cocos2d.h"
#include "storage/local-storage/LocalStorage.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/auto/jsb_cocos2dx_auto.hpp"
#include "scripting/js-bindings/manual/js_bindings_config.h"

// for debug socket
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
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

#include "scripting/js-bindings/manual/js_bindings_config.h"

#if COCOS2D_DEBUG
#define TRACE_DEBUGGER_SERVER(...) CCLOG(__VA_ARGS__)
#else
#define TRACE_DEBUGGER_SERVER(...)
#endif // #if COCOS2D_DEBUG

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
static void serverEntryPoint(unsigned int port);

//js_proxy_t *_native_js_global_ht = NULL;
//js_proxy_t *_js_native_global_ht = NULL;
std::unordered_map<std::string, js_type_class_t*> _js_global_type_map;
static std::unordered_map<void*, js_proxy_t*> _native_js_global_map;
static std::unordered_map<JSObject*, js_proxy_t*> _js_native_global_map;
static std::unordered_map<JSObject*, JSObject*> _js_hook_owner_map;

static char *_js_log_buf = NULL;

static std::vector<sc_register_sth> registrationList;

// name ~> JSScript map
static std::unordered_map<std::string, JSScript*> filename_script;
// port ~> socket map
static std::unordered_map<int,int> ports_sockets;

static void cc_closesocket(int fd)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    closesocket(fd);
#else
    close(fd);
#endif
}

static void ReportException(JSContext *cx)
{
    if (JS_IsExceptionPending(cx)) {
        if (!JS_ReportPendingException(cx)) {
            JS_ClearPendingException(cx);
        }
    }
}

static void executeJSFunctionFromReservedSpot(JSContext *cx, JS::HandleObject obj,
                                              const JS::HandleValueArray& dataVal, JS::MutableHandleValue retval) {

    JS::RootedValue func(cx, JS_GetReservedSlot(obj, 0));

    if (func.isNullOrUndefined()) { return; }
    JS::RootedValue thisObj(cx, JS_GetReservedSlot(obj, 1));
    JSAutoCompartment ac(cx, obj);
    
    if (thisObj.isNullOrUndefined()) {
        JS_CallFunctionValue(cx, obj, func, dataVal, retval);
    } else {
        assert(!thisObj.isPrimitive());
        JS::RootedObject jsthis(cx, thisObj.toObjectOrNull());
        JS_CallFunctionValue(cx, jsthis, func, dataVal, retval);
    }
}

static std::string getTouchesFuncName(EventTouch::EventCode eventCode)
{
    std::string funcName;
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
        default:
            CCASSERT(false, "Invalid event code!");
            break;
    }
    return funcName;
}

static std::string getTouchFuncName(EventTouch::EventCode eventCode)
{
    std::string funcName;
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
        default:
            CCASSERT(false, "Invalid event code!");
    }
    
    return funcName;
}

static std::string getMouseFuncName(EventMouse::MouseEventType eventType)
{
    std::string funcName;
    switch(eventType) {
        case EventMouse::MouseEventType::MOUSE_DOWN:
            funcName = "onMouseDown";
            break;
        case EventMouse::MouseEventType::MOUSE_UP:
            funcName = "onMouseUp";
            break;
        case EventMouse::MouseEventType::MOUSE_MOVE:
            funcName = "onMouseMove";
            break;
        case EventMouse::MouseEventType::MOUSE_SCROLL:
            funcName = "onMouseScroll";
            break;
        default:
            CCASSERT(false, "Invalid event code!");
    }
    
    return funcName;
}

void removeJSObject(JSContext* cx, cocos2d::Ref* nativeObj)
{
    auto proxy = jsb_get_native_proxy(nativeObj);
    if (proxy)
    {
#if ! CC_ENABLE_GC_FOR_NATIVE_OBJECTS
        JS::RemoveObjectRoot(cx, &proxy->obj);
#endif
        // remove the proxy here, since this was a "stack" object, not heap
        // when js_finalize will be called, it will fail, but
        // the correct solution is to have a new finalize for event
        jsb_remove_proxy(proxy);
    }
    else CCLOG("removeJSObject: BUG: cannot find native object = %p", nativeObj);
}

void ScriptingCore::executeJSFunctionWithThisObj(JS::HandleValue thisObj, JS::HandleValue callback)
{
    JS::RootedValue retVal(_cx);
    executeJSFunctionWithThisObj(thisObj, callback, JS::HandleValueArray::empty(), &retVal);
}

void ScriptingCore::executeJSFunctionWithThisObj(JS::HandleValue thisObj,
                                                 JS::HandleValue callback,
                                                 const JS::HandleValueArray& vp,
                                                 JS::MutableHandleValue retVal)
{
    if (!callback.isNullOrUndefined() || !thisObj.isNullOrUndefined())
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        // Very important: The last parameter 'retVal' passed to 'JS_CallFunctionValue' should not be a NULL pointer.
        // If it's a NULL pointer, crash will be triggered in 'JS_CallFunctionValue'. To find out the reason of this crash is very difficult.
        // So we have to check the availability of 'retVal'.
//        if (retVal)
//        {
            JS::RootedObject jsthis(_cx, thisObj.toObjectOrNull());
            JS_CallFunctionValue(_cx, jsthis, callback, vp, retVal);
//        }
//        else
//        {
//            jsval jsRet;
//            JS_CallFunctionValue(_cx, JSVAL_TO_OBJECT(thisObj), callback, argc, vp, &jsRet);
//        }
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
        CCLOG("JS: %s", _js_log_buf);
    }
}

bool JSBCore_platform(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getPlatform");
        return false;
    }
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    Application::Platform platform;

    // config.deviceType: Device Type
    // 'mobile' for any kind of mobile devices, 'desktop' for PCs, 'browser' for Web Browsers
    // #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    //     platform = JS_InternString(_cx, "desktop");
    // #else
    platform = Application::getInstance()->getTargetPlatform();
    // #endif

    args.rval().set(INT_TO_JSVAL((int)platform));

    return true;
};

bool JSBCore_version(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getVersion");
        return false;
    }

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    char version[256];
    snprintf(version, sizeof(version)-1, "%s", cocos2dVersion());
    JSString * js_version = JS_InternString(cx, version);

    args.rval().set(STRING_TO_JSVAL(js_version));

    return true;
};

bool JSBCore_os(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc!=0)
    {
        JS_ReportError(cx, "Invalid number of arguments in __getOS");
        return false;
    }

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    JSString * os;

    // osx, ios, android, windows, linux, etc..
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    os = JS_InternString(cx, "iOS");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    os = JS_InternString(cx, "Android");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    os = JS_InternString(cx, "Windows");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
    os = JS_InternString(cx, "Marmalade");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    os = JS_InternString(cx, "Linux");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BADA)
    os = JS_InternString(cx, "Bada");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
    os = JS_InternString(cx, "Blackberry");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    os = JS_InternString(cx, "OS X");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    os = JS_InternString(cx, "WINRT");
#else
    os = JS_InternString(cx, "Unknown");
#endif

    args.rval().set(STRING_TO_JSVAL(os));

    return true;
};

bool JSB_cleanScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc != 1)
    {
        JS_ReportError(cx, "Invalid number of arguments in JSB_cleanScript");
        return false;
    }

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSString *jsPath = args.get(0).toString();
    JSB_PRECONDITION2(jsPath, cx, false, "Error js file in clean script");
    JSStringWrapper wrapper(jsPath);
    ScriptingCore::getInstance()->cleanScript(wrapper.get());

    args.rval().setUndefined();

    return true;
};

bool JSB_core_restartVM(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSB_PRECONDITION2(argc==0, cx, false, "Invalid number of arguments in executeScript");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    ScriptingCore::getInstance()->reset();
    args.rval().setUndefined();
    return true;
};

bool JSB_closeWindow(JSContext *cx, uint32_t argc, jsval *vp)
{
    ScriptingCore::getInstance()->cleanup();
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    return true;
};

void registerDefaultClasses(JSContext* cx, JS::HandleObject global) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, global, "cc", &nsval);
    // Not exist, create it
    if (nsval == JSVAL_VOID)
    {
        ns.set(JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, global, "cc", nsval);
    }
    else
    {
        ns.set(nsval.toObjectOrNull());
    }

    //
    // Javascript controller (__jsc__)
    //
    JS::RootedObject proto(cx);
    JS::RootedObject parent(cx);
    JS::RootedObject jsc(cx, JS_NewObject(cx, NULL, proto, parent));
    JS::RootedValue jscVal(cx);
    jscVal = OBJECT_TO_JSVAL(jsc);
    JS_SetProperty(cx, global, "__jsc__", jscVal);

    JS_DefineFunction(cx, jsc, "garbageCollect", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, jsc, "dumpRoot", ScriptingCore::dumpRoot, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, jsc, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );

    // register some global functions
    JS_DefineFunction(cx, global, "require", ScriptingCore::executeScript, 1, JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "forceGC", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, global, "__getPlatform", JSBCore_platform, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__getOS", JSBCore_os, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__getVersion", JSBCore_version, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__restartVM", JSB_core_restartVM, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, global, "__cleanScript", JSB_cleanScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "__isObjectValid", ScriptingCore::isObjectValid, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "close", JSB_closeWindow, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}

static void sc_finalize(JSFreeOp *freeOp, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (global class)", obj);
}

//static JSClass global_class = {
//    "global", JSCLASS_GLOBAL_FLAGS,
//    JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
//    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, sc_finalize,
//    JSCLASS_NO_OPTIONAL_MEMBERS
//};

static const JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_DeletePropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, sc_finalize,
    nullptr, nullptr, nullptr,
    JS_GlobalObjectTraceHook
};

ScriptingCore* ScriptingCore::getInstance()
{
    static ScriptingCore* instance = nullptr;
    if (instance == nullptr)
        instance = new (std::nothrow) ScriptingCore();

    return instance;
}

ScriptingCore::ScriptingCore()
: _rt(nullptr)
, _cx(nullptr)
, _jsInited(false)
, _needCleanup(false)
//, _global(nullptr)
//, _debugGlobal(nullptr)
, _callFromScript(false)
{
    // set utf8 strings internally (we don't need utf16)
    // XXX: Removed in SpiderMonkey 19.0
    //JS_SetCStringsAreUTF8();
    initRegister();
}

void ScriptingCore::initRegister()
{
    this->addRegisterCallback(registerDefaultClasses);
    this->_runLoop = new (std::nothrow) SimpleRunLoop();
}

void ScriptingCore::string_report(JS::HandleValue val) {
    if (val.isNull()) {
        LOGD("val : (JSVAL_IS_NULL(val)");
        // return 1;
    } else if (val.isBoolean() && false == val.toBoolean()) {
        LOGD("val : (return value is false");
        // return 1;
    } else if (val.isString()) {
        JSContext* cx = this->getGlobalContext();
        JS::RootedString str(cx, val.toString());
        if (str.get()) {
            LOGD("val : return string is NULL");
        } else {
            JSStringWrapper wrapper(str);
            LOGD("val : return string =\n%s\n", wrapper.get());
        }
    } else if (val.isNumber()) {
        double number = val.toNumber();
        LOGD("val : return number =\n%f", number);
    }
}

bool ScriptingCore::evalString(const char *string, JS::MutableHandleValue outVal, const char *filename, JSContext* cx, JS::HandleObject global)
{
    JSAutoCompartment ac(cx, global);
    return JS_EvaluateScript(cx, global, string, (unsigned)strlen(string), "ScriptingCore::evalString", 1, outVal);
}

bool ScriptingCore::evalString(const char *string, JS::MutableHandleValue outVal)
{
    return evalString(string, outVal, nullptr, _cx, _global.ref());
}

bool ScriptingCore::evalString(const char *string)
{
    JS::RootedValue retVal(_cx);
    return evalString(string, &retVal);
}

void ScriptingCore::start()
{
    // for now just this
    createGlobalContext();
}

void ScriptingCore::addRegisterCallback(sc_register_sth callback) {
    registrationList.push_back(callback);
}

void ScriptingCore::removeAllRoots(JSContext *cx)
{
    // Native -> JS. No need to free "second"
    _native_js_global_map.clear();

    // JS -> Native: free "second" and "unroot" it.
    auto it_js = _js_native_global_map.begin();
    while (it_js != _js_native_global_map.end())
    {
        JS::RemoveObjectRoot(cx, &it_js->second->obj);
        free(it_js->second);
        it_js = _js_native_global_map.erase(it_js);
    }
    _js_native_global_map.clear();
}

// Just a wrapper around JSPrincipals that allows static construction.
class CCJSPrincipals : public JSPrincipals
{
  public:
    explicit CCJSPrincipals(int rc = 0)
      : JSPrincipals()
    {
        refcount = rc;
    }
};

static CCJSPrincipals shellTrustedPrincipals(1);

static bool
CheckObjectAccess(JSContext *cx)
{
    return true;
}

static JSSecurityCallbacks securityCallbacks = {
    CheckObjectAccess,
    NULL
};

void ScriptingCore::createGlobalContext() {
    if (_cx && _rt) {
        ScriptingCore::removeAllRoots(_cx);
        JS_DestroyContext(_cx);
        JS_DestroyRuntime(_rt);
        _cx = NULL;
        _rt = NULL;
    }
    
    // Start the engine. Added in SpiderMonkey v25
    if (!_jsInited && !JS_Init())
    {
        return;
    }
    else
    {
        _jsInited = true;
    }
    
    // Removed from Spidermonkey 19.
    //JS_SetCStringsAreUTF8();
    _rt = JS_NewRuntime(8L * 1024L * 1024L);
    JS_SetGCParameter(_rt, JSGC_MAX_BYTES, 0xffffffff);
    
    JS_SetTrustedPrincipals(_rt, &shellTrustedPrincipals);
    JS_SetSecurityCallbacks(_rt, &securityCallbacks);
    JS_SetNativeStackQuota(_rt, JSB_MAX_STACK_QUOTA);
    
    _cx = JS_NewContext(_rt, 8192);
    
    // Removed in Firefox v27
//    JS_SetOptions(this->_cx, JSOPTION_TYPE_INFERENCE);
    // Removed in Firefox v33
//    JS::ContextOptionsRef(_cx).setTypeInference(true);

    JS::RuntimeOptionsRef(_rt).setIon(true);
    JS::RuntimeOptionsRef(_rt).setBaseline(true);

//    JS_SetVersion(this->_cx, JSVERSION_LATEST);
    
    JS_SetErrorReporter(_cx, ScriptingCore::reportError);
#if defined(JS_GC_ZEAL) && defined(DEBUG)
    JS_SetGCZeal(this->_cx, 2, JS_DEFAULT_ZEAL_FREQ);
#endif

    _global.construct(_cx);
    _global.ref() = NewGlobalObject(_cx);
    
    // Removed in Firefox v34
    js::SetDefaultObjectForContext(_cx, _global.ref());
    
    JSAutoCompartment ac(_cx, _global.ref());
    
    runScript("script/jsb_prepare.js");
    
    for (std::vector<sc_register_sth>::iterator it = registrationList.begin(); it != registrationList.end(); it++) {
        sc_register_sth callback = *it;
        callback(_cx, _global.ref());
    }
    
    _needCleanup = true;
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

JSScript* ScriptingCore::getScript(const char *path)
{
    // a) check jsc file first
    std::string byteCodePath = RemoveFileExt(std::string(path)) + BYTE_CODE_FILE_EXT;
    if (filename_script.find(byteCodePath) != filename_script.end())
        return filename_script[byteCodePath];
    
    // b) no jsc file, check js file
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
    if (filename_script.find(fullPath) != filename_script.end())
        return filename_script[fullPath];
    
    return NULL;
}

void ScriptingCore::compileScript(const char *path, JS::HandleObject global, JSContext* cx)
{
    if (!path) {
        return;
    }
    
    if (getScript(path)) {
        return;
    }

    cocos2d::FileUtils *futil = cocos2d::FileUtils::getInstance();

    if (cx == NULL) {
        cx = _cx;
    }

    JSAutoCompartment ac(cx, global);

    JS::RootedScript script(cx);
    JS::RootedObject obj(cx, global);

    // a) check jsc file first
    std::string byteCodePath = RemoveFileExt(std::string(path)) + BYTE_CODE_FILE_EXT;

    // Check whether '.jsc' files exist to avoid outputing log which says 'couldn't find .jsc file'.
    if (futil->isFileExist(byteCodePath))
    {
        Data data = futil->getDataFromFile(byteCodePath);
        if (!data.isNull())
        {
            script = JS_DecodeScript(cx, data.getBytes(), static_cast<uint32_t>(data.getSize()), nullptr);
        }
    }

    // b) no jsc file, check js file
    if (!script)
    {
        /* Clear any pending exception from previous failed decoding.  */
        ReportException(cx);

        std::string fullPath = futil->fullPathForFilename(path);

        JS::CompileOptions op(cx);
        op.setUTF8(true);
        op.setFileAndLine(fullPath.c_str(), 1);

        bool ok = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        std::string jsFileContent = futil->getStringFromFile(fullPath);
        if (!jsFileContent.empty())
        {
            ok = JS::Compile(cx, obj, op, jsFileContent.c_str(), jsFileContent.size(), &script);
        }
#else
        ok = JS::Compile(cx, obj, op, fullPath.c_str(), &script);
#endif
        if (ok) {
            filename_script[fullPath] = script;
        }
    }
    else {
        filename_script[byteCodePath] = script;
    }
}

void ScriptingCore::cleanScript(const char *path)
{
    std::string byteCodePath = RemoveFileExt(std::string(path)) + BYTE_CODE_FILE_EXT;
    auto it = filename_script.find(byteCodePath);
    if (it != filename_script.end())
    {
        filename_script.erase(it);
    }
    
    std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
    it = filename_script.find(fullPath);
    if (it != filename_script.end())
    {
        filename_script.erase(it);
    }
}

std::unordered_map<std::string, JSScript*>  &ScriptingCore::getFileScript()
{
    return filename_script;
}

void ScriptingCore::cleanAllScript()
{
    filename_script.clear();
}

bool ScriptingCore::runScript(const char *path)
{
    return runScript(path, _global.ref(), _cx);
}

bool ScriptingCore::runScript(const char *path, JS::HandleObject global, JSContext* cx)
{
    if (cx == NULL) {
        cx = _cx;
    }

    compileScript(path,global,cx);
    JS::RootedScript script(cx, getScript(path));
    bool evaluatedOK = false;
    if (script) {
        JS::RootedValue rval(cx);
        JSAutoCompartment ac(cx, global);
        evaluatedOK = JS_ExecuteScript(cx, global, script, &rval);
        if (false == evaluatedOK) {
            cocos2d::log("Evaluating %s failed (evaluatedOK == JS_FALSE)", path);
            JS_ReportPendingException(cx);
        }
    }
 
    return evaluatedOK;
}

bool ScriptingCore::requireScript(const char *path, JS::MutableHandleValue jsvalRet)
{
    return requireScript(path, _global.ref(), _cx, jsvalRet);
}

bool ScriptingCore::requireScript(const char *path, JS::HandleObject global, JSContext* cx, JS::MutableHandleValue jsvalRet)
{
    if (cx == NULL)
    {
        cx = _cx;
    }
    
    compileScript(path,global,cx);
    JS::RootedScript script(cx, getScript(path));
    bool evaluatedOK = false;
    if (script)
    {
        JSAutoCompartment ac(cx, global);
        evaluatedOK = JS_ExecuteScript(cx, global, script, jsvalRet);
        if (false == evaluatedOK)
        {
            cocos2d::log("(evaluatedOK == JS_FALSE)");
            JS_ReportPendingException(cx);
        }
    }
    
    return evaluatedOK;
}

void ScriptingCore::reset()
{
    Director::getInstance()->restart();
}

void ScriptingCore::restartVM()
{
    cleanup();
    initRegister();
    Application::getInstance()->applicationDidFinishLaunching();
}

ScriptingCore::~ScriptingCore()
{
    cleanup();
    JS_ShutDown();
}

void ScriptingCore::cleanup()
{
    if (!_needCleanup) {
        return;
    }
    localStorageFree();
    removeAllRoots(_cx);
    garbageCollect();
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
    _global.destroyIfConstructed();
    _debugGlobal.destroyIfConstructed();
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
    filename_script.clear();
    registrationList.clear();
    
    _needCleanup = false;
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
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc > 0) {
        JSString *string = JS::ToString(cx, args.get(0));
        if (string) {
            JSStringWrapper wrapper(string);
            js_log("%s", wrapper.get());
        }
    }
    args.rval().setUndefined();
    return true;
}


void ScriptingCore::retainScriptObject(cocos2d::Ref* owner, cocos2d::Ref* target)
{
    JS::RootedObject global(_cx, _global.ref());
    JS::RootedObject jsbObj(_cx);
    get_or_create_js_obj(_cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(_cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    js_proxy_t *pOwner = jsb_get_native_proxy(owner);
    js_proxy_t *pTarget = jsb_get_native_proxy(target);
    if (!pOwner || !pTarget)
    {
        return;
    }
    JS::RootedValue valOwner(_cx, OBJECT_TO_JSVAL(pOwner->obj));
    JS::RootedValue valTarget(_cx, OBJECT_TO_JSVAL(pTarget->obj));
    if (valTarget.isPrimitive())
    {
        return;
    }
    
    JS::RootedValue retval(_cx);
    jsval valArr[2];
    valArr[0] = valOwner;
    valArr[1] = valTarget;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    executeFunctionWithOwner(jsbVal, "registerNativeRef", args, &retval);
}

void ScriptingCore::rootScriptObject(cocos2d::Ref* target)
{
    JS::RootedObject global(_cx, _global.ref());
    JS::RootedObject jsbObj(_cx);
    get_or_create_js_obj(_cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(_cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    js_proxy_t *pTarget = jsb_get_native_proxy(target);
    if (!pTarget)
    {
        return;
    }
    JS::RootedValue valTarget(_cx, OBJECT_TO_JSVAL(pTarget->obj));
    if (valTarget.isPrimitive())
    {
        return;
    }
    
    JS::RootedObject root(_cx);
    get_or_create_js_obj(_cx, jsbObj, "_root", &root);
    JS::RootedValue valRoot(_cx, OBJECT_TO_JSVAL(root));
    
    JS::RootedValue retval(_cx);
    jsval valArr[2];
    valArr[0] = valRoot;
    valArr[1] = valTarget;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    executeFunctionWithOwner(jsbVal, "registerNativeRef", args, &retval);
}

void ScriptingCore::releaseScriptObject(cocos2d::Ref* owner, cocos2d::Ref* target)
{
    JS::RootedObject global(_cx, _global.ref());
    JS::RootedObject jsbObj(_cx);
    get_or_create_js_obj(_cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(_cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    js_proxy_t *pOwner = jsb_get_native_proxy(owner);
    js_proxy_t *pTarget = jsb_get_native_proxy(target);
    if (!pOwner || !pTarget)
    {
        return;
    }
    JS::RootedValue valOwner(_cx, OBJECT_TO_JSVAL(pOwner->obj));
    JS::RootedValue valTarget(_cx, OBJECT_TO_JSVAL(pTarget->obj));
    if (valTarget.isPrimitive())
    {
        return;
    }
    
    JS::RootedValue retval(_cx);
    jsval valArr[2];
    valArr[0] = valOwner;
    valArr[1] = valTarget;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    executeFunctionWithOwner(jsbVal, "unregisterNativeRef", args, &retval);
}

void ScriptingCore::unrootScriptObject(cocos2d::Ref* target)
{
    JS::RootedObject global(_cx, _global.ref());
    JS::RootedObject jsbObj(_cx);
    get_or_create_js_obj(_cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(_cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    js_proxy_t *pTarget = jsb_get_native_proxy(target);
    if (!pTarget)
    {
        return;
    }
    JS::RootedValue valTarget(_cx, OBJECT_TO_JSVAL(pTarget->obj));
    if (valTarget.isPrimitive())
    {
        return;
    }
    
    JS::RootedObject root(_cx);
    get_or_create_js_obj(_cx, jsbObj, "_root", &root);
    JS::RootedValue valRoot(_cx, OBJECT_TO_JSVAL(root));
    
    JS::RootedValue retval(_cx);
    jsval valArr[2];
    valArr[0] = valRoot;
    valArr[1] = valTarget;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    executeFunctionWithOwner(jsbVal, "unregisterNativeRef", args, &retval);
}

void ScriptingCore::releaseAllChildrenRecursive(cocos2d::Node *node)
{
    const Vector<Node*>& children = node->getChildren();
    for (auto child : children)
    {
        releaseScriptObject(node, child);
        releaseAllChildrenRecursive(child);
    }
}

void ScriptingCore::releaseAllNativeRefs(cocos2d::Ref* owner)
{
    JS::RootedObject global(_cx, _global.ref());
    JS::RootedObject jsbObj(_cx);
    get_or_create_js_obj(_cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(_cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    js_proxy_t *pOwner = jsb_get_native_proxy(owner);
    if (!pOwner)
    {
        return;
    }
    JS::RootedValue valOwner(_cx, OBJECT_TO_JSVAL(pOwner->obj));
    
    JS::RootedValue retval(_cx);
    jsval valArr[1];
    valArr[0] = valOwner;
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(1, valArr);
    executeFunctionWithOwner(jsbVal, "unregisterAllNativeRefs", args, &retval);
}


void ScriptingCore::removeScriptObjectByObject(Ref* pObj)
{
    auto proxy = jsb_get_native_proxy(pObj);
    if (proxy)
    {
        JSContext *cx = getGlobalContext();
        JS::RemoveObjectRoot(cx, &proxy->obj);
        jsb_remove_proxy(proxy);
    }
//    else CCLOG("removeScriptObjectByObject. BUG: nproxy not found = %p", nproxy);
}


bool ScriptingCore::setReservedSpot(uint32_t i, JSObject *obj, jsval value) {
    JS_SetReservedSlot(obj, i, value);
    return true;
}

bool ScriptingCore::executeScript(JSContext *cx, uint32_t argc, jsval *vp)
{
    ScriptingCore *engine = ScriptingCore::getInstance();
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc >= 1) {
        JS::RootedValue jsstr(cx, args.get(0));
        JSString* str = JS::ToString(cx, jsstr);
        JSStringWrapper path(str);
        bool res = false;
        JS::RootedValue jsret(cx);
        if (argc == 2 && args.get(1).isString()) {
            JSString* globalName = args.get(1).toString();
            JSStringWrapper name(globalName);

            JS::RootedObject debugObj(cx, engine->getDebugGlobal());
            if (debugObj) {
                res = engine->requireScript(path.get(), debugObj, cx, &jsret);
            } else {
                JS_ReportError(cx, "Invalid global object: %s", name.get());
                args.rval().setUndefined();
                return false;
            }
        } else {
            JS::RootedObject glob(cx, JS::CurrentGlobalOrNull(cx));
            res = engine->requireScript(path.get(), glob, cx, &jsret);
        }
        args.rval().set(jsret);
        return res;
    }
    args.rval().setUndefined();
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

void ScriptingCore::pauseSchedulesAndActions(js_proxy_t* p)
{
    JS::RootedObject obj(_cx, p->obj.get());
    __Array * arr = JSScheduleWrapper::getTargetForJSObject(obj);
    if (! arr) return;
    
    Node* node = (Node*)p->ptr;
    for(ssize_t i = 0; i < arr->count(); ++i) {
        if (arr->getObjectAtIndex(i)) {
            node->getScheduler()->pauseTarget(arr->getObjectAtIndex(i));
        }
    }
}


void ScriptingCore::resumeSchedulesAndActions(js_proxy_t* p)
{
    JS::RootedObject obj(_cx, p->obj.get());
    __Array * arr = JSScheduleWrapper::getTargetForJSObject(obj);
    if (!arr) return;
    
    Node* node = (Node*)p->ptr;
    for(ssize_t i = 0; i < arr->count(); ++i) {
        if (!arr->getObjectAtIndex(i)) continue;
        node->getScheduler()->resumeTarget(arr->getObjectAtIndex(i));
    }
}

void ScriptingCore::cleanupSchedulesAndActions(js_proxy_t* p)
{
    JS::RootedObject obj(_cx, p->obj.get());
    __Array* arr = JSScheduleWrapper::getTargetForJSObject(obj);
    if (arr) {
        Node* node = (Node*)p->ptr;
        Scheduler* pScheduler = node->getScheduler();
        Ref* pObj = nullptr;
        CCARRAY_FOREACH(arr, pObj)
        {
            pScheduler->unscheduleAllForTarget(pObj);
        }

        JSScheduleWrapper::removeAllTargetsForJSObject(obj);
    }
}

bool ScriptingCore::isFunctionOverridedInJS(JS::HandleObject obj, const std::string& name, JSNative native)
{
    JS::RootedObject jsobj(_cx, obj);
    JSAutoCompartment ac(_cx, jsobj);
    JS::RootedValue value(_cx);
    bool ok = JS_GetProperty(_cx, jsobj, name.c_str(), &value);
    if (ok && !value.isNullOrUndefined() && !JS_IsNativeFunction(value.toObjectOrNull(), native))
    {
        return true;
    }
    
    return false;
}

int ScriptingCore::handleActionEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    ActionObjectScriptData* actionObjectScriptData = static_cast<ActionObjectScriptData*>(data);
    if (NULL == actionObjectScriptData->nativeObject || NULL == actionObjectScriptData->eventType)
        return 0;
    
    Action* actionObject = static_cast<Action*>(actionObjectScriptData->nativeObject);
    int eventType = *((int*)(actionObjectScriptData->eventType));
    
    js_proxy_t * p = jsb_get_native_proxy(actionObject);
    if (!p) return 0;
    
    JSAutoCompartment ac(_cx, _global.ref());
    
    int ret = 0;
    JS::RootedValue retval(_cx);
    
    if (eventType == kActionUpdate)
    {
        JS::RootedObject jstarget(_cx, p->obj);
        if (isFunctionOverridedInJS(jstarget, "update", js_cocos2dx_Action_update))
        {
            jsval dataVal = DOUBLE_TO_JSVAL(*((float *)actionObjectScriptData->param));
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "update", 1, &dataVal, &retval);
        }
    }
    return ret;
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
    
    JSAutoCompartment ac(_cx, _global.ref());
    
    int ret = 0;
    JS::RootedValue retval(_cx);
    jsval dataVal = INT_TO_JSVAL(1);
    
    JS::RootedObject jstarget(_cx, p->obj);

    if (action == kNodeOnEnter)
    {
        if (isFunctionOverridedInJS(jstarget, "onEnter", js_cocos2dx_Node_onEnter))
        {
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onEnter", 1, &dataVal, &retval);
        }
        resumeSchedulesAndActions(p);
    }
    else if (action == kNodeOnExit)
    {
        if (isFunctionOverridedInJS(jstarget, "onExit", js_cocos2dx_Node_onExit))
        {
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onExit", 1, &dataVal, &retval);
        }
        pauseSchedulesAndActions(p);
    }
    else if (action == kNodeOnEnterTransitionDidFinish)
    {
        if (isFunctionOverridedInJS(jstarget, "onEnterTransitionDidFinish", js_cocos2dx_Node_onEnterTransitionDidFinish))
        {
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onEnterTransitionDidFinish", 1, &dataVal, &retval);
        }
    }
    else if (action == kNodeOnExitTransitionDidStart)
    {
        if (isFunctionOverridedInJS(jstarget, "onExitTransitionDidStart", js_cocos2dx_Node_onExitTransitionDidStart))
        {
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onExitTransitionDidStart", 1, &dataVal, &retval);
        }
    }
    else if (action == kNodeOnCleanup) {
        cleanupSchedulesAndActions(p);
        
        if (isFunctionOverridedInJS(jstarget, "cleanup", js_cocos2dx_Node_cleanup))
        {
            ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "cleanup", 1, &dataVal, &retval);
        }
    }

    return ret;
}

int ScriptingCore::handleComponentEvent(void* data)
{
    if (NULL == data)
        return 0;
    
    BasicScriptData* basicScriptData = static_cast<BasicScriptData*>(data);
    if (NULL == basicScriptData->nativeObject || NULL == basicScriptData->value)
        return 0;
    
    Component* node = static_cast<Component*>(basicScriptData->nativeObject);
    int action = *((int*)(basicScriptData->value));
    
    js_proxy_t * p = jsb_get_native_proxy(node);
    if (!p) return 0;
    
    JSAutoCompartment ac(_cx, _global.ref());
    
    int ret = 0;
    JS::RootedValue retval(_cx);
    jsval dataVal = INT_TO_JSVAL(1);
    
    JS::RootedValue nodeValue(_cx, OBJECT_TO_JSVAL(p->obj));
    
    if (action == kComponentOnAdd)
    {
        ret = executeFunctionWithOwner(nodeValue, "onAdd", 1, &dataVal, &retval);
    }
    else if (action == kComponentOnRemove)
    {
        ret = executeFunctionWithOwner(nodeValue, "onRemove", 1, &dataVal, &retval);
    }
    else if (action == kComponentOnEnter)
    {
        ret = executeFunctionWithOwner(nodeValue, "onEnter", 1, &dataVal, &retval);
        resumeSchedulesAndActions(p);
    }
    else if (action == kComponentOnExit)
    {
        ret = executeFunctionWithOwner(nodeValue, "onExit", 1, &dataVal, &retval);
        pauseSchedulesAndActions(p);
    }
    else if (action == kComponentOnUpdate)
    {
        ret = executeFunctionWithOwner(nodeValue, "update", 1, &dataVal, &retval);
    }
    
    return ret;
}

bool ScriptingCore::handleTouchesEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event)
{
    JS::RootedValue ret(_cx);
    return handleTouchesEvent(nativeObj, eventCode, touches, event, &ret);
}

bool ScriptingCore::handleTouchesEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event, JS::MutableHandleValue jsvalRet)
{
    JSAutoCompartment ac(_cx, _global.ref());
    
    bool ret = false;
    std::string funcName = getTouchesFuncName(eventCode);
    JS::RootedObject jsretArr(_cx, JS_NewArrayObject(_cx, 0));
    int count = 0;

    js_type_class_t *typeClassEvent = nullptr;
    js_type_class_t *typeClassTouch = nullptr;

    if (touches.size()>0)
        typeClassTouch = js_get_type_from_native<cocos2d::Touch>(touches[0]);
    typeClassEvent = js_get_type_from_native<cocos2d::EventTouch>((cocos2d::EventTouch*)event);

    for (const auto& touch : touches)
    {
        JS::RootedValue jsret(_cx, OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, touch, typeClassTouch, "cocos2d::Touch")));
        if (!JS_SetElement(_cx, jsretArr, count, jsret))
        {
            break;
        }
        ++count;
    }

    js_proxy_t* p = jsb_get_native_proxy(nativeObj);
    if (p)
    {
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(jsretArr);
        dataVal[1] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, event, typeClassEvent, "cocos2d::EventTouch"));
        ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), funcName.c_str(), 2, dataVal, jsvalRet);
    }

    for (auto& touch : touches)
    {
        removeJSObject(_cx, touch);
    }
    
    removeJSObject(_cx, event);

    return ret;
}

bool ScriptingCore::handleTouchEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, cocos2d::Touch* touch, cocos2d::Event* event)
{
    JS::RootedValue ret(_cx);
    return handleTouchEvent(nativeObj, eventCode, touch, event, &ret);
}

bool ScriptingCore::handleTouchEvent(void* nativeObj, cocos2d::EventTouch::EventCode eventCode, cocos2d::Touch* touch, cocos2d::Event* event, JS::MutableHandleValue jsvalRet)
{
    JSAutoCompartment ac(_cx, _global.ref());
    
    std::string funcName = getTouchFuncName(eventCode);
    bool ret = false;
    
    js_proxy_t * p = jsb_get_native_proxy(nativeObj);
    if (p)
    {
        js_type_class_t *typeClassTouch = js_get_type_from_native<cocos2d::Touch>(touch);
        js_type_class_t *typeClassEvent = js_get_type_from_native<cocos2d::EventTouch>((cocos2d::EventTouch*)event);

        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, touch, typeClassTouch, "cocos2d::Touch"));
        dataVal[1] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, event, typeClassEvent, "cocos2d::EventTouch"));

        ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), funcName.c_str(), 2, dataVal, jsvalRet);
    }

    removeJSObject(_cx, touch);
    removeJSObject(_cx, event);

    return ret;
}

bool ScriptingCore::handleMouseEvent(void* nativeObj, cocos2d::EventMouse::MouseEventType eventType, cocos2d::Event* event)
{
    JS::RootedValue ret(_cx);
    return handleMouseEvent(nativeObj, eventType, event, &ret);
}

bool ScriptingCore::handleMouseEvent(void* nativeObj, cocos2d::EventMouse::MouseEventType eventType, cocos2d::Event* event, JS::MutableHandleValue jsvalRet)
{
    JSAutoCompartment ac(_cx, _global.ref());
    
    std::string funcName = getMouseFuncName(eventType);
    bool ret = false;
    
    js_proxy_t * p = jsb_get_native_proxy(nativeObj);
    if (p)
    {
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::EventMouse>((cocos2d::EventMouse*)event);
        jsval dataVal = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, event, typeClass, "cocos2d::EventMouse"));
        ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), funcName.c_str(), 1, &dataVal, jsvalRet);

        removeJSObject(_cx, event);
    }
    else CCLOG("ScriptingCore::handleMouseEvent native proxy NOT found");
    
    return ret;
}

bool ScriptingCore::executeFunctionWithObjectData(void* nativeObj, const char *name, JSObject *obj)
{
    js_proxy_t * p = jsb_get_native_proxy(nativeObj);
    if (!p) return false;

    JS::RootedValue retval(_cx);
    jsval dataVal = OBJECT_TO_JSVAL(obj);

    executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), name, 1, &dataVal, &retval);
    if (retval.isNull()) {
        return false;
    }
    else if (retval.isBoolean()) {
        return retval.toBoolean();
    }
    return false;
}

bool ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp)
{
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(argc, vp);
    JS::RootedValue rval(_cx);
    return executeFunctionWithOwner(owner, name, args, &rval);
}

bool ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, uint32_t argc, jsval *vp, JS::MutableHandleValue retVal)
{
    //should not use CallArgs here, use HandleValueArray instead !!
    //because the "jsval* vp" is not the standard format from JSNative, the array doesn't contain this and retval
    //JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(argc, vp);
    return executeFunctionWithOwner(owner, name, args, retVal);
}

bool ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args)
{
    JS::RootedValue ret(_cx);
    return executeFunctionWithOwner(owner, name, args, &ret);
}

bool ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, const JS::HandleValueArray& args, JS::MutableHandleValue retVal)
{
    bool bRet = false;
    bool hasAction;
    JSContext* cx = this->_cx;
    JS::RootedValue temp_retval(cx);
    JS::RootedValue ownerval(cx, owner);
    JS::RootedObject obj(cx, ownerval.toObjectOrNull());
    
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

            bRet = JS_CallFunctionName(cx, obj, name, args, retVal);

        }
    }while(0);
    return bRet;
}

bool ScriptingCore::handleKeybardEvent(void* nativeObj, cocos2d::EventKeyboard::KeyCode keyCode, bool isPressed, cocos2d::Event* event)
{
    JSAutoCompartment ac(_cx, _global.ref());
    
    js_proxy_t * p = jsb_get_native_proxy(nativeObj);
    if (nullptr == p)
        return false;
    
    bool ret = false;

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::EventKeyboard>((cocos2d::EventKeyboard*)event);
    jsval args[2] = {
        int32_to_jsval(_cx, (int32_t)keyCode),
        OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, event, typeClass, "cocos2d::EventKeyboard"))
    };
    
    if (isPressed)
    {
        ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "_onKeyPressed", 2, args);
    }
    else
    {
        ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "_onKeyReleased", 2, args);
    }

    removeJSObject(_cx, event);
    
    return ret;
}

bool ScriptingCore::handleFocusEvent(void* nativeObj, cocos2d::ui::Widget* widgetLoseFocus, cocos2d::ui::Widget* widgetGetFocus)
{
    JSAutoCompartment ac(_cx, _global.ref());
    
    js_proxy_t * p = jsb_get_native_proxy(nativeObj);
    if (nullptr == p)
        return false;

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::ui::Widget>(widgetLoseFocus);

    jsval args[2] = {
        OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, widgetLoseFocus, typeClass, "cocos2d::ui::Widget")),
        OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(_cx, widgetGetFocus, typeClass, "cocos2d::ui::Widget"))
    };

    bool ret = executeFunctionWithOwner(OBJECT_TO_JSVAL(p->obj), "onFocusChanged", 2, args);

    return ret;
}


int ScriptingCore::executeCustomTouchesEvent(EventTouch::EventCode eventType,
                                       const std::vector<Touch*>& touches, JSObject *obj)
{
    std::string funcName = getTouchesFuncName(eventType);

    JS::RootedObject jsretArr(_cx, JS_NewArrayObject(this->_cx, 0));
    int count = 0;
    for (auto& touch : touches)
    {
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Touch>(touch);

        jsval jsret = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(this->_cx, touch, typeClass, "cocos2d::Touch"));
        JS::RootedValue jsval(_cx, jsret);
        if (!JS_SetElement(this->_cx, jsretArr, count, jsval)) {
            break;
        }
        ++count;
    }

    jsval jsretArrVal = OBJECT_TO_JSVAL(jsretArr);
    executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), funcName.c_str(), 1, &jsretArrVal);

    for (auto& touch : touches)
    {
        removeJSObject(this->_cx, touch);
    }

    return 1;
}


int ScriptingCore::executeCustomTouchEvent(EventTouch::EventCode eventType, Touch *touch, JSObject *obj)
{
    JS::RootedValue retval(_cx);
    std::string funcName = getTouchFuncName(eventType);

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Touch>(touch);
    jsval jsTouch = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(this->_cx, touch, typeClass, "cocos2d::Touch"));

    executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), funcName.c_str(), 1, &jsTouch, &retval);

    removeJSObject(this->_cx, touch);
    
    return 1;

}


int ScriptingCore::executeCustomTouchEvent(EventTouch::EventCode eventType,
                                           Touch *touch, JSObject *obj,
                                           JS::MutableHandleValue retval)
{
    std::string funcName = getTouchFuncName(eventType);

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Touch>(touch);
    jsval jsTouch = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(this->_cx, touch, typeClass, "cocos2d::Touch"));

    executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), funcName.c_str(), 1, &jsTouch, retval);

    removeJSObject(this->_cx, touch);

    return 1;
}

int ScriptingCore::sendEvent(ScriptEvent* evt)
{
    if (NULL == evt)
        return 0;
 
    // special type, can't use this code after JSAutoCompartment
    if (evt->type == kRestartGame)
    {
        restartVM();
        return 0;
    }
    
    switch (evt->type)
    {
        case kNodeEvent:
            {
                return handleNodeEvent(evt->data);
            }
            break;
        case kScriptActionEvent:
            {
                return handleActionEvent(evt->data);
            }
            break;
        case kMenuClickedEvent:
            break;
        case kTouchEvent:
            {
                TouchScriptData* data = (TouchScriptData*)evt->data;
                return handleTouchEvent(data->nativeObject, data->actionType, data->touch, data->event);
            }
            break;
        case kTouchesEvent:
            {
                TouchesScriptData* data = (TouchesScriptData*)evt->data;
                return handleTouchesEvent(data->nativeObject, data->actionType, data->touches, data->event);
            }
            break;
        case kComponentEvent:
            {
                return handleComponentEvent(evt->data);
            }
            break;
        default:
            CCASSERT(false, "Invalid script event.");
            break;
    }
    
    return 0;
}

bool ScriptingCore::parseConfig(ConfigType type, const std::string &str)
{
    jsval args[2];
    args[0] = int32_to_jsval(_cx, static_cast<int>(type));
    args[1] = std_string_to_jsval(_cx, str);
    return (true == executeFunctionWithOwner(OBJECT_TO_JSVAL(_global.ref().get()), "__onParseConfig", 2, args));
}

bool ScriptingCore::isObjectValid(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
        js_proxy_t *proxy = jsb_get_js_proxy(tmpObj);
        if (proxy && proxy->ptr) {
            args.rval().set(JSVAL_TRUE);
        }
        else {
            args.rval().set(JSVAL_FALSE);
        }
        return true;
    }
    else {
        JS_ReportError(cx, "Invalid number of arguments: %d. Expecting: 1", argc);
        return false;
    }
}

void ScriptingCore::rootObject(Ref* ref)
{
    auto proxy = jsb_get_native_proxy(ref);
    if (proxy) {
        JSContext *cx = getGlobalContext();
        JS::AddNamedObjectRoot(cx, &proxy->obj, typeid(*ref).name());
        ref->_rooted = true;
    }
    else CCLOG("rootObject: BUG. native not found: %p (%s)",  ref, typeid(*ref).name());
}

void ScriptingCore::unrootObject(Ref* ref)
{
    auto proxy = jsb_get_native_proxy(ref);
    if (proxy) {
        JSContext *cx = getGlobalContext();
        JS::RemoveObjectRoot(cx, &proxy->obj);
        ref->_rooted = false;
    }
    else CCLOG("unrootObject: BUG. native not found: %p (%s)",  ref, typeid(*ref).name());
}

void ScriptingCore::garbageCollect()
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    auto runtime = JS_GetRuntime(_cx);
    // twice: yep, call it twice since this is a generational GC
    // and we want to collect as much as possible when this is being called
    // from replaceScene().
    JS_GC(runtime);
    JS_GC(runtime);
#endif
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
    JSAutoCompartment ac(_cx, _debugGlobal.ref());
    
    JSString* jsstr = JS_NewStringCopyZ(_cx, str.c_str());
    jsval argv = STRING_TO_JSVAL(jsstr);
    JS::RootedValue outval(_cx);
    
    JS::RootedObject debugGlobal(_cx, _debugGlobal.ref());
    JS_CallFunctionName(_cx, debugGlobal, "processInput", JS::HandleValueArray::fromMarkedLocation(1, &argv), &outval);
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
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().set(UINT_TO_JSVAL(s_nestedLoopLevel));
    return true;
}

bool JSBDebug_exitNestedEventLoop(JSContext* cx, unsigned argc, jsval* vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (s_nestedLoopLevel > 0) {
        --s_nestedLoopLevel;
    } else {
        args.rval().set(UINT_TO_JSVAL(0));
        return true;
    }
    args.rval().setUndefined();
    return true;
}

bool JSBDebug_getEventLoopNestLevel(JSContext* cx, unsigned argc, jsval* vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().set(UINT_TO_JSVAL(s_nestedLoopLevel));
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

static void serverEntryPoint(unsigned int port)
{
    // start a server, accept the connection and keep reading data from it
    struct addrinfo hints, *result = nullptr, *rp = nullptr;
    int s = 0;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    
    std::stringstream portstr;
    portstr << port;
    
    int err = 0;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
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
            cc_closesocket(s);
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
        cc_closesocket(s);
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
            while ((readBytes = (int)::recv(clientSocket, buf, sizeof(buf), 0)) > 0)
            {
                buf[readBytes] = '\0';
                // TRACE_DEBUGGER_SERVER("debug server : received command >%s", buf);
                
                // no other thread is using this
                inData.append(buf);
                // process any input, send any output
                clearBuffers();
            } // while(read)
            
            cc_closesocket(clientSocket);
        }
    } // while(true)
}

bool JSBDebug_BufferWrite(JSContext* cx, unsigned argc, jsval* vp)
{
    if (argc == 1) {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JSStringWrapper strWrapper(args.get(0));
        // this is safe because we're already inside a lock (from clearBuffers)
        outData.append(strWrapper.get());
        _clientSocketWriteAndClearString(outData);
    }
    return true;
}

void ScriptingCore::enableDebugger(unsigned int port)
{
    if (_debugGlobal.empty())
    {
        JSAutoCompartment ac0(_cx, _global.ref().get());
        
        JS_SetDebugMode(_cx, true);
        
        _debugGlobal.construct(_cx);
        _debugGlobal.ref() = NewGlobalObject(_cx, true);
        // Adds the debugger object to root, otherwise it may be collected by GC.
        //AddObjectRoot(_cx, &_debugGlobal.ref()); no need, it's persistent rooted now
        //JS_WrapObject(_cx, &_debugGlobal.ref()); Not really needed, JS_WrapObject makes a cross-compartment wrapper for the given JS object
        JS::RootedObject rootedDebugObj(_cx, _debugGlobal.ref());
        JSAutoCompartment acDebug(_cx, rootedDebugObj);
        // these are used in the debug program
        JS_DefineFunction(_cx, rootedDebugObj, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_ENUMERATE | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, rootedDebugObj, "require", ScriptingCore::executeScript, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, rootedDebugObj, "_bufferWrite", JSBDebug_BufferWrite, 1, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, rootedDebugObj, "_enterNestedEventLoop", JSBDebug_enterNestedEventLoop, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, rootedDebugObj, "_exitNestedEventLoop", JSBDebug_exitNestedEventLoop, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        JS_DefineFunction(_cx, rootedDebugObj, "_getEventLoopNestLevel", JSBDebug_getEventLoopNestLevel, 0, JSPROP_READONLY | JSPROP_PERMANENT);
        
        JS::RootedObject globalObj(_cx, _global.ref());
        JS_WrapObject(_cx, &globalObj);
        
        runScript("script/jsb_debugger.js", rootedDebugObj);
        
        // prepare the debugger
        jsval argv = OBJECT_TO_JSVAL(globalObj);
        JS::RootedValue outval(_cx);
        JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(1, &argv);
        bool ok = JS_CallFunctionName(_cx, rootedDebugObj, "_prepareDebugger", args, &outval);
        if (!ok) {
            JS_ReportPendingException(_cx);
        }
        
        // start bg thread
        auto t = std::thread(&serverEntryPoint,port);
        t.detach();
        
        Scheduler* scheduler = Director::getInstance()->getScheduler();
        scheduler->scheduleUpdate(this->_runLoop, 0, false);
    }
}

JSObject* NewGlobalObject(JSContext* cx, bool debug)
{
    JS::CompartmentOptions options;
    options.setVersion(JSVERSION_LATEST);
    
    JS::RootedObject glob(cx, JS_NewGlobalObject(cx, &global_class, &shellTrustedPrincipals, JS::DontFireOnNewGlobalHook, options));
    if (!glob) {
        return nullptr;
    }
    JSAutoCompartment ac(cx, glob);
    bool ok = true;
    ok = JS_InitStandardClasses(cx, glob);
    if (ok)
        JS_InitReflect(cx, glob);
    if (ok && debug)
        ok = JS_DefineDebuggerObject(cx, glob);
    if (!ok)
        return nullptr;

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

js_proxy_t* jsb_new_proxy(void* nativeObj, JS::HandleObject jsHandle)
{
    js_proxy_t* proxy = nullptr;
    JSObject* jsObj = jsHandle.get();

    if (nativeObj && jsObj)
    {
        // native to JS index
        proxy = (js_proxy_t *)malloc(sizeof(js_proxy_t));
        CC_ASSERT(proxy && "not enough memory");

#if 0
        if (_js_native_global_map.find(jsObj) != _js_native_global_map.end())
        {
            CCLOG("BUG: old:%s new:%s", JS_GetClass(_js_native_global_map.at(jsObj)->_jsobj)->name, JS_GetClass(jsObj)->name);
        }
#endif

        CC_ASSERT(_native_js_global_map.find(nativeObj) == _native_js_global_map.end() && "Native Key should not be present");
//        CC_ASSERT(_js_native_global_map.find(jsObj) == _js_native_global_map.end() && "JS Key should not be present");
        // If native proxy doesn't exist, and js proxy exist, means previous js object in this location have already been released.
        // In some circumstances, js object may be released without calling its finalizer, so the proxy haven't been removed.
        // For ex: var seq = cc.sequence(moveBy, cc.callFunc(this.callback, this));
        // In this code, cc.callFunc is created in parameter, and directly released after the native function call, the finalizer won't be triggered.
        // The current solution keep the game running with a warning because it may cause memory leak as the native object may have been retained.
        auto existJSProxy = _js_native_global_map.find(jsObj);
        if (existJSProxy != _js_native_global_map.end()) {
#if COCOS2D_DEBUG
            CCLOG("jsbindings: Failed to remove proxy for native object: %p, force removing it, but it may cause memory leak", existJSProxy->second->ptr);
#endif
            jsb_remove_proxy(existJSProxy->second);
        }

        proxy->ptr = nativeObj;
        proxy->obj = jsObj;
        proxy->_jsobj = jsObj;

        // One Proxy in two entries
        _native_js_global_map[nativeObj] = proxy;
        _js_native_global_map[jsObj] = proxy;
    }
    else CCLOG("jsb_new_proxy: Invalid keys");

    return proxy;
}

js_proxy_t* jsb_get_native_proxy(void* nativeObj)
{
    auto search = _native_js_global_map.find(nativeObj);
    if(search != _native_js_global_map.end())
        return search->second;
    return nullptr;
}

js_proxy_t* jsb_get_js_proxy(JSObject* jsObj)
{
    auto search = _js_native_global_map.find(jsObj);
    if(search != _js_native_global_map.end())
        return search->second;
    return nullptr;
}

void jsb_remove_proxy(js_proxy_t* nativeProxy, js_proxy_t* jsProxy)
{
    js_proxy_t* proxy = nativeProxy ? nativeProxy : jsProxy;
    jsb_remove_proxy(proxy);
}

void jsb_remove_proxy(js_proxy_t* proxy)
{
    void* nativeKey = proxy->ptr;
    JSObject* jsKey = proxy->_jsobj;

    CC_ASSERT(nativeKey && "Invalid nativeKey");
    CC_ASSERT(jsKey && "Invalid JSKey");

    auto it_nat = _native_js_global_map.find(nativeKey);
    auto it_js = _js_native_global_map.find(jsKey);

#if 0
    // XXX FIXME: sanity check. Remove me once it is tested that it works Ok
    if (it_nat != _native_js_global_map.end() && it_js != _js_native_global_map.end())
    {
        CC_ASSERT(it_nat->second == it_js->second && "BUG. Different enties");
    }
#endif

    if (it_nat != _native_js_global_map.end())
    {
        _native_js_global_map.erase(it_nat);
    }
    else CCLOG("jsb_remove_proxy: failed. Native key not found");

    if (it_js != _js_native_global_map.end())
    {
        // Free it once, since we only have one proxy alloced entry
        free(it_js->second);
        _js_native_global_map.erase(it_js);
    }
    else CCLOG("jsb_remove_proxy: failed. JS key not found");
}

//
// Ref functions
//

// ref_create
JSObject* jsb_ref_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug)
{
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsObj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    js_proxy_t* newproxy = jsb_new_proxy(ref, jsObj);
    jsb_ref_init(cx, &newproxy->obj, ref, debug);
    return jsObj;
}

JSObject* jsb_ref_autoreleased_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug)
{
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsObj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    js_proxy_t* newproxy = jsb_new_proxy(ref, jsObj);
    jsb_ref_autoreleased_init(cx, &newproxy->obj, ref, debug);
    return jsObj;
}

JSObject* jsb_create_weak_jsobject(JSContext *cx, void *native, js_type_class_t *typeClass, const char* debug)
{
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsObj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    auto proxy = jsb_new_proxy(native, jsObj);
    
#if ! CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    JS::AddNamedObjectRoot(cx, &proxy->obj, debug);
#else
#if COCOS2D_DEBUG > 1
    CC_UNUSED_PARAM(proxy);
    CCLOG("++++++WEAK_REF++++++ Cpp(%s): %p - JS: %p", debug, native, jsObj.get());
#endif // COCOS2D_DEBUG
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    return jsObj;
}

// get_or_create
JSObject* jsb_ref_get_or_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug)
{
    auto proxy = jsb_get_native_proxy(ref);
    if (proxy)
    {
        JS::RootedObject obj(cx, proxy->obj);
        return obj;
    }

    // don't auto-release, don't retain.
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsObj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    js_proxy_t* newproxy = jsb_new_proxy(ref, jsObj);
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    CC_UNUSED_PARAM(newproxy);
    ref->retain();
    js_add_FinalizeHook(cx, jsObj);
#if COCOS2D_DEBUG > 1
    CCLOG("++++++RETAINED++++++ Cpp(%s): %p - JS: %p", debug, ref, jsObj.get());
#endif // COCOS2D_DEBUG
#else
    // don't autorelease it
    JS::AddNamedObjectRoot(cx, &newproxy->obj, debug);
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS

    return jsObj;
}

// get_or_create: Ref is already autoreleased (or created)
JSObject* jsb_ref_autoreleased_get_or_create_jsobject(JSContext *cx, cocos2d::Ref *ref, js_type_class_t *typeClass, const char* debug)
{
    auto proxy = jsb_get_native_proxy(ref);
    if (proxy)
    {
        JS::RootedObject obj(cx, proxy->obj);
        return obj;
    }
    // else
    return jsb_ref_autoreleased_create_jsobject(cx, ref, typeClass, debug);
}

// get_or_create: when native object isn't a ref object or when the native object life cycle don't need to be managed by js object
JSObject* jsb_get_or_create_weak_jsobject(JSContext *cx, void *native, js_type_class_t *typeClass, const char* debug)
{
    auto proxy = jsb_get_native_proxy(native);
    if (proxy)
    {
        JS::RootedObject obj(cx, proxy->obj);
        return obj;
    }
    
    // don't auto-release, don't retain.
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsObj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    proxy = jsb_new_proxy(native, jsObj);
    
#if ! CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    JS::AddNamedObjectRoot(cx, &proxy->obj, debug);
#else
#if COCOS2D_DEBUG > 1
    CCLOG("++++++WEAK_REF++++++ Cpp(%s): %p - JS: %p", debug, native, jsObj.get());
#endif // COCOS2D_DEBUG
#endif // CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    return jsObj;
}

// ref_init
void jsb_ref_init(JSContext* cx, JS::Heap<JSObject*> *obj, Ref* ref, const char* debug)
{
//    CCLOG("jsb_ref_init: JSObject address =  %p. %s", obj->get(), debug);
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    (void)ref;
    JS::RootedObject jsObj(cx, *obj);
    js_add_FinalizeHook(cx, jsObj);
    // don't retain it, already retained
#if COCOS2D_DEBUG > 1
    CCLOG("++++++RETAINED++++++ Cpp(%s): %p - JS: %p", debug, ref, jsObj.get());
#endif // COCOS2D_DEBUG
#else
    // autorelease it
    ref->autorelease();
    JS::AddNamedObjectRoot(cx, obj, debug);
#endif
}

void jsb_ref_autoreleased_init(JSContext* cx, JS::Heap<JSObject*> *obj, Ref* ref, const char* debug)
{
    //    CCLOG("jsb_ref_init: JSObject address =  %p. %s", obj->get(), debug);
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    (void)cx;
    (void)obj;
    ref->retain();
    JS::RootedObject jsObj(cx, *obj);
    js_add_FinalizeHook(cx, jsObj);
#else
    // don't autorelease it, since it is already autoreleased
    JS::AddNamedObjectRoot(cx, obj, debug);
#endif
}

// rebind
void jsb_ref_rebind(JSContext* cx, JS::HandleObject jsobj, js_proxy_t *proxy, cocos2d::Ref* oldRef, cocos2d::Ref* newRef, const char* debug)
{
#if CC_ENABLE_GC_FOR_NATIVE_OBJECTS
    // Release the old reference as it have been retained by jsobj previously,
    // and the jsobj won't have any chance to release it in the future
    oldRef->release();
#else
    JS::RemoveObjectRoot(cx, &proxy->obj);
#endif
    jsb_remove_proxy(proxy);

    // Rebind js obj with new action
    jsb_new_proxy(newRef, jsobj);
}

// Register finalize hook
void jsb_register_finalize_hook(JSObject *hook, JSObject *owner)
{
    _js_hook_owner_map.insert(std::make_pair(hook, owner));
}

// Remove hook owner entry in _js_hook_owner_map
JSObject *jsb_get_and_remove_hook_owner(JSObject *hook)
{
    auto ownerIt = _js_hook_owner_map.find(hook);
    // Found
    if (ownerIt != _js_hook_owner_map.cend())
    {
        JSObject *result = ownerIt->second;
        _js_hook_owner_map.erase(ownerIt);
        return result;
    }
    return nullptr;
}
