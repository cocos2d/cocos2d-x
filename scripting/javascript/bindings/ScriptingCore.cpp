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
#include "ScriptingCore.h"
#include "cocos2d.h"
#include "cocos2d_specifics.hpp"

#ifdef ANDROID
#include <android/log.h>
#include <jni/JniHelper.h>
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

static void executeJSFunctionFromReservedSpot(JSContext *cx, JSObject *obj, 
                                              jsval &dataVal, jsval &retval) {

    //  if(p->jsclass->JSCLASS_HAS_RESERVED_SLOTS(1)) {
    jsval func = JS_GetReservedSlot(obj, 0);
    
    if(func == JSVAL_VOID) { return; }
    jsval thisObj = JS_GetReservedSlot(obj, 1);
    if(thisObj == JSVAL_VOID) {
        JS_CallFunctionValue(cx, obj, func, 1, &dataVal, &retval);
    } else {
        assert(!JSVAL_IS_PRIMITIVE(thisObj));
        JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(thisObj), func, 1, &dataVal, &retval);
    }        
    //  }
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
                                                 jsval data) {
    jsval retval;
    if(callback != JSVAL_VOID || thisObj != JSVAL_VOID) {
        JS_CallFunctionValue(cx, JSVAL_TO_OBJECT(thisObj), callback, 1, &data, &retval);
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

void registerDefaultClasses(JSContext* cx, JSObject* global) {
    if (!JS_InitStandardClasses(cx, global)) {
        js_log("error initializing the standard classes");
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

#if !defined(JS_NewCompartmentAndGlobalObject)
#if defined(JS_NewGlobalObject)
#  undef(JS_NewGlobalObject)
#endif
//#define JS_NewCompartmentAndGlobalObject(cx, clasp, ppals) JS_NewGlobalObject(cx, clasp, ppals)
#endif

ScriptingCore::ScriptingCore()
: rt(NULL)
, cx(NULL)
, global(NULL)
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

JSBool ScriptingCore::evalString(const char *string, jsval *outVal, const char *filename)
{
    jsval rval;
    const char *fname = (filename ? filename : "noname");
    uint32_t lineno = 1;
    if (outVal == NULL) {
        outVal = &rval;
    }

    JSBool evaluatedOK = JS_EvaluateScript(cx, global,
                                           string, strlen(string),
                                           fname, lineno, outVal);

    if (JS_FALSE == evaluatedOK) {
        LOGD("(evaluatedOK == JS_FALSE)");
    } else {
        this->string_report(*outVal);
    }

    return evaluatedOK;
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
    }
    HASH_CLEAR(hh, _js_native_global_ht);
    HASH_CLEAR(hh, _native_js_global_ht);
    HASH_CLEAR(hh, _js_global_type_ht);
}

void ScriptingCore::createGlobalContext() {
    if (this->cx && this->rt) {        
        ScriptingCore::removeAllRoots(this->cx);
        JS_DestroyContext(this->cx);
        JS_DestroyRuntime(this->rt);
        this->cx = NULL;
        this->rt = NULL;
    }
    this->rt = JS_NewRuntime(10 * 1024 * 1024);
    this->cx = JS_NewContext(rt, 10240);
    JS_SetOptions(this->cx, JSOPTION_TYPE_INFERENCE);
    JS_SetVersion(this->cx, JSVERSION_LATEST);
    JS_SetOptions(this->cx, JS_GetOptions(this->cx) & ~JSOPTION_METHODJIT);
    JS_SetOptions(this->cx, JS_GetOptions(this->cx) & ~JSOPTION_METHODJIT_ALWAYS);
    JS_SetErrorReporter(this->cx, ScriptingCore::reportError);
    this->global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
    for (std::vector<sc_register_sth>::iterator it = registrationList.begin(); it != registrationList.end(); it++) {
        sc_register_sth callback = *it;
        callback(this->cx, this->global);
    }
}

JSBool ScriptingCore::runScript(const char *path)
{
    CCLOG("ScriptingCore::runScript(%s)", path);

    cocos2d::CCFileUtils *futil = cocos2d::CCFileUtils::sharedFileUtils();

#ifdef ANDROID_SCRIPTINGCORE_LOAD_SCRIPTS_FROM_EXTERNAL_ASSET_DIRECTORY
    const char * externalAssetPath = cocos2d::JniHelper::getExternalAssetPath();

    std::string fullPath = std::string(externalAssetPath) + std::string(path);

    const char *realPath = fullPath.c_str();
#else
    const char *realPath = futil->fullPathFromRelativePath(path);
#endif

    if (!realPath) {
        CCLOG("!realPath. returning JS_FALSE");
        return JS_FALSE;
    }

    unsigned char *content = NULL;
    unsigned long contentSize = 0;

    content = (unsigned char*)CCString::createWithContentsOfFile(realPath)->getCString();
    contentSize = strlen((char*)content);

    JSBool ret = JS_FALSE;
    if (content && contentSize) {
        jsval rval;
        ret = this->evalString((const char *)content, &rval, path);
    } else {
        CCLOG("!(content && contentSize)");
    }

    return ret;
}

ScriptingCore::~ScriptingCore()
{
    JS_DestroyContext(cx);
    JS_DestroyRuntime(rt);
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
	JSBool ret = JS_FALSE;
	if (argc == 1) {
		JSString *string;
		if (JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string) == JS_TRUE) {
			ret = ScriptingCore::getInstance()->runScript(JS_EncodeString(cx, string));
		}
	}
	return ret;
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
    JSContext *_cx = ScriptingCore::getInstance()->getGlobalContext();
    JSRuntime *rt = JS_GetRuntime(_cx);
    JS_DumpNamedRoots(rt, dumpNamedRoot, NULL);
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
        executeJSFunctionWithName(this->cx, p->obj, "onEnter", dataVal, retval);
    } 
    else if(nAction == kCCNodeOnExit)
    {
        executeJSFunctionWithName(this->cx, p->obj, "onExit", dataVal, retval);
    }
    else if(nAction == kCCNodeOnEnterTransitionDidFinish)
    {
        executeJSFunctionWithName(this->cx, p->obj, "onEnterTransitionDidFinish", dataVal, retval);
    }
    else if(nAction == kCCNodeOnExitTransitionDidStart)
    {
        executeJSFunctionWithName(this->cx, p->obj, "onExitTransitionDidStart", dataVal, retval);
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

    executeJSFunctionFromReservedSpot(this->cx, p->obj, dataVal, retval);

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

    executeJSFunctionWithName(this->cx, p->obj, "update", dataVal, retval);

    return 1;
}

int ScriptingCore::executeLayerTouchesEvent(CCLayer* pLayer, int eventType, CCSet *pTouches)
{
    std::string funcName = "";
    getTouchesFuncName(eventType, funcName);

    JSObject *jsretArr = JS_NewArrayObject(this->cx, 0, NULL);

    JS_AddNamedObjectRoot(this->cx, &jsretArr, "touchArray");
    int count = 0;
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        getJSTouchObject(this->cx, (CCTouch *) *it, jsret);
        if(!JS_SetElement(this->cx, jsretArr, count, &jsret)) {
            break;
        }
    }

    executeFunctionWithObjectData(pLayer,  funcName.c_str(), jsretArr);

    JS_RemoveObjectRoot(this->cx, &jsretArr);

    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        removeJSTouchObject(this->cx, (CCTouch *) *it, jsret);
    }

    return 1;
}

int ScriptingCore::executeLayerTouchEvent(CCLayer* pLayer, int eventType, CCTouch *pTouch)
{
    return 0;
}

int ScriptingCore::executeFunctionWithObjectData(CCNode *self, const char *name, JSObject *obj) {
    
    js_proxy_t * p;
    JS_GET_PROXY(p, self);
    if (!p) return 0;
    
    jsval retval;
    jsval dataVal = OBJECT_TO_JSVAL(obj);
    
    executeJSFunctionWithName(this->cx, p->obj, name, dataVal, retval);
    
    return 1;
}

int ScriptingCore::executeFunctionWithOwner(jsval owner, const char *name, jsval data) {
    jsval retval;

    executeJSFunctionWithName(this->cx, JSVAL_TO_OBJECT(owner), name, data, retval);

    return 1;
}

int ScriptingCore::executeCustomTouchesEvent(int eventType, 
                                       CCSet *pTouches, JSObject *obj)
{
    jsval retval;
    std::string funcName;
    getTouchesFuncName(eventType, funcName);
    
    JSObject *jsretArr = JS_NewArrayObject(this->cx, 0, NULL);
    JS_AddNamedObjectRoot(this->cx, &jsretArr, "touchArray");
    int count = 0;
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        getJSTouchObject(this->cx, (CCTouch *) *it, jsret);
        if(!JS_SetElement(this->cx, jsretArr, count, &jsret)) {
            break;
        }
    }
    
    jsval jsretArrVal = OBJECT_TO_JSVAL(jsretArr);
    executeJSFunctionWithName(this->cx, obj, funcName.c_str(), jsretArrVal, retval);
    JS_RemoveObjectRoot(this->cx, &jsretArr);
    
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it, ++count) {
        jsval jsret;
        removeJSTouchObject(this->cx, (CCTouch *) *it, jsret);
    }
    
    return 1;
}


int ScriptingCore::executeCustomTouchEvent(int eventType, 
                                           CCTouch *pTouch, JSObject *obj) {
    jsval retval;
    std::string funcName;
    getTouchFuncName(eventType, funcName);
    
    jsval jsTouch;
    getJSTouchObject(this->cx, pTouch, jsTouch);
    
    executeJSFunctionWithName(this->cx, obj, funcName.c_str(), jsTouch, retval);
    return 1;
    
}  


int ScriptingCore::executeCustomTouchEvent(int eventType, 
                                           CCTouch *pTouch, JSObject *obj,
                                           jsval &retval) {

    std::string funcName;
    getTouchFuncName(eventType, funcName);
    
    jsval jsTouch;
    getJSTouchObject(this->cx, pTouch, jsTouch);

    executeJSFunctionWithName(this->cx, obj, funcName.c_str(), jsTouch, retval);
    return 1;
    
}  

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

    CCObject *obj = arr->objectAtIndex(i);
    js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCObject>(cx, obj);
    jsval arrElement = OBJECT_TO_JSVAL(proxy->obj);

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

jsval cccolor3b_to_jsval(JSContext* cx, ccColor3B& v) {
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
