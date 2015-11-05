#include "jsb_cocos2dx_audioengine_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "cocos2d_specifics.hpp"
#include "AudioEngine.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_cocos2d_experimental_AudioProfile_class;
JSObject *jsb_cocos2d_experimental_AudioProfile_prototype;

bool js_cocos2dx_audioengine_AudioProfile_get_name(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(args.thisv().toObjectOrNull());
    cocos2d::experimental::AudioProfile* cobj = (cocos2d::experimental::AudioProfile *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_audioengine_AudioProfile_get_name : Invalid Native Object");

    jsval jsret = std_string_to_jsval(cx, cobj->name);
    args.rval().set(jsret);
    return true;
}
bool js_cocos2dx_audioengine_AudioProfile_set_name(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(args.thisv().toObjectOrNull());
    cocos2d::experimental::AudioProfile* cobj = (cocos2d::experimental::AudioProfile *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_audioengine_AudioProfile_set_name : Invalid Native Object");

    bool ok = true;
    std::string arg0;
    ok &= jsval_to_std_string(cx, args.get(0), &arg0);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioProfile_set_name : Error processing new value");
    cobj->name = arg0;
    return true;
}
bool js_cocos2dx_audioengine_AudioProfile_get_maxInstances(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(args.thisv().toObjectOrNull());
    cocos2d::experimental::AudioProfile* cobj = (cocos2d::experimental::AudioProfile *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_audioengine_AudioProfile_get_maxInstances : Invalid Native Object");

    jsval jsret = uint32_to_jsval(cx, cobj->maxInstances);
    args.rval().set(jsret);
    return true;
}
bool js_cocos2dx_audioengine_AudioProfile_set_maxInstances(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(args.thisv().toObjectOrNull());
    cocos2d::experimental::AudioProfile* cobj = (cocos2d::experimental::AudioProfile *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_audioengine_AudioProfile_set_maxInstances : Invalid Native Object");

    bool ok = true;
    unsigned int arg0 = 0;
    ok &= jsval_to_uint32(cx, args.get(0), &arg0);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioProfile_set_maxInstances : Error processing new value");
    cobj->maxInstances = arg0;
    return true;
}
bool js_cocos2dx_audioengine_AudioProfile_get_minDelay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(args.thisv().toObjectOrNull());
    cocos2d::experimental::AudioProfile* cobj = (cocos2d::experimental::AudioProfile *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_audioengine_AudioProfile_get_minDelay : Invalid Native Object");

    jsval jsret = DOUBLE_TO_JSVAL(cobj->minDelay);
    args.rval().set(jsret);
    return true;
}
bool js_cocos2dx_audioengine_AudioProfile_set_minDelay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(args.thisv().toObjectOrNull());
    cocos2d::experimental::AudioProfile* cobj = (cocos2d::experimental::AudioProfile *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_audioengine_AudioProfile_set_minDelay : Invalid Native Object");

    bool ok = true;
    double arg0 = 0;
    ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioProfile_set_minDelay : Error processing new value");
    cobj->minDelay = arg0;
    return true;
}
bool js_cocos2dx_audioengine_AudioProfile_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::experimental::AudioProfile* cobj = new (std::nothrow) cocos2d::experimental::AudioProfile();
    TypeTest<cocos2d::experimental::AudioProfile> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::experimental::AudioProfile");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

void js_cocos2d_experimental_AudioProfile_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AudioProfile)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        cocos2d::experimental::AudioProfile *nobj = static_cast<cocos2d::experimental::AudioProfile *>(jsproxy->ptr);
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        if (nobj) {
            jsb_remove_proxy(nproxy, jsproxy);
            delete nobj;
        }
        else jsb_remove_proxy(nullptr, jsproxy);
    }
}
void js_register_cocos2dx_audioengine_AudioProfile(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_experimental_AudioProfile_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_experimental_AudioProfile_class->name = "AudioProfile";
    jsb_cocos2d_experimental_AudioProfile_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_AudioProfile_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_experimental_AudioProfile_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_AudioProfile_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_experimental_AudioProfile_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_experimental_AudioProfile_class->resolve = JS_ResolveStub;
    jsb_cocos2d_experimental_AudioProfile_class->convert = JS_ConvertStub;
    jsb_cocos2d_experimental_AudioProfile_class->finalize = js_cocos2d_experimental_AudioProfile_finalize;
    jsb_cocos2d_experimental_AudioProfile_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PSGS("name", js_cocos2dx_audioengine_AudioProfile_get_name, js_cocos2dx_audioengine_AudioProfile_set_name, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PSGS("maxInstances", js_cocos2dx_audioengine_AudioProfile_get_maxInstances, js_cocos2dx_audioengine_AudioProfile_set_maxInstances, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PSGS("minDelay", js_cocos2dx_audioengine_AudioProfile_get_minDelay, js_cocos2dx_audioengine_AudioProfile_set_minDelay, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_experimental_AudioProfile_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_experimental_AudioProfile_class,
        js_cocos2dx_audioengine_AudioProfile_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AudioProfile", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::experimental::AudioProfile> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_experimental_AudioProfile_class;
        p->proto = jsb_cocos2d_experimental_AudioProfile_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_experimental_AudioEngine_class;
JSObject *jsb_cocos2d_experimental_AudioEngine_prototype;

bool js_cocos2dx_audioengine_AudioEngine_lazyInit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        bool ret = cocos2d::experimental::AudioEngine::lazyInit();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_lazyInit : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        double arg1 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_setCurrentTime : Error processing arguments");
        bool ret = cocos2d::experimental::AudioEngine::setCurrentTime(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_setCurrentTime : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_getVolume : Error processing arguments");
        double ret = cocos2d::experimental::AudioEngine::getVolume(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getVolume : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_uncache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_uncache : Error processing arguments");
        cocos2d::experimental::AudioEngine::uncache(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_uncache : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_resumeAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::AudioEngine::resumeAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_resumeAll : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_stopAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::AudioEngine::stopAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_stopAll : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_pause : Error processing arguments");
        cocos2d::experimental::AudioEngine::pause(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_pause : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_end(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::AudioEngine::end();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_end : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        int ret = cocos2d::experimental::AudioEngine::getMaxAudioInstance();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_getCurrentTime : Error processing arguments");
        double ret = cocos2d::experimental::AudioEngine::getCurrentTime(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getCurrentTime : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance : Error processing arguments");
        bool ret = cocos2d::experimental::AudioEngine::setMaxAudioInstance(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_isLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_isLoop : Error processing arguments");
        bool ret = cocos2d::experimental::AudioEngine::isLoop(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_isLoop : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_pauseAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::AudioEngine::pauseAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_pauseAll : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_uncacheAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::AudioEngine::uncacheAll();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_uncacheAll : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_setVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        double arg1 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_setVolume : Error processing arguments");
        cocos2d::experimental::AudioEngine::setVolume(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_setVolume : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_preload(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::function<void (bool)> arg1;
            do {
			    if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
			    {
			        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(1)));
			        auto lambda = [=](bool larg0) -> void {
			            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
			            jsval largv[1];
			            largv[0] = BOOLEAN_TO_JSVAL(larg0);
			            JS::RootedValue rval(cx);
			            bool succeed = func->invoke(1, &largv[0], &rval);
			            if (!succeed && JS_IsExceptionPending(cx)) {
			                JS_ReportPendingException(cx);
			            }
			        };
			        arg1 = lambda;
			    }
			    else
			    {
			        arg1 = nullptr;
			    }
			} while(0)
			;
            if (!ok) { ok = true; break; }
            cocos2d::experimental::AudioEngine::preload(arg0, arg1);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::experimental::AudioEngine::preload(arg0);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_preload : wrong number of arguments");
    return false;
}
bool js_cocos2dx_audioengine_AudioEngine_play2d(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_play2d : Error processing arguments");
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_play2d : Error processing arguments");
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        bool arg1;
        double arg2 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_play2d : Error processing arguments");
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        bool arg1;
        double arg2 = 0;
        const cocos2d::experimental::AudioProfile* arg3 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        do {
            if (args.get(3).isNull()) { arg3 = nullptr; break; }
            if (!args.get(3).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(3).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg3 = (const cocos2d::experimental::AudioProfile*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_play2d : Error processing arguments");
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_play2d : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_getState : Error processing arguments");
        int ret = (int)cocos2d::experimental::AudioEngine::getState(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getState : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_resume : Error processing arguments");
        cocos2d::experimental::AudioEngine::resume(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_resume : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_stop : Error processing arguments");
        cocos2d::experimental::AudioEngine::stop(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_stop : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_getDuration : Error processing arguments");
        double ret = cocos2d::experimental::AudioEngine::getDuration(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getDuration : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        bool arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_setLoop : Error processing arguments");
        cocos2d::experimental::AudioEngine::setLoop(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_setLoop : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getDefaultProfile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::AudioProfile* ret = cocos2d::experimental::AudioEngine::getDefaultProfile();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::AudioProfile>(cx, (cocos2d::experimental::AudioProfile*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getDefaultProfile : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_setFinishCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        int arg0 = 0;
        std::function<void (int, const std::basic_string<char> &)> arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        do {
		    if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(1)));
		        auto lambda = [=](int larg0, const std::basic_string<char> & larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            largv[1] = std_string_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(2, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg1 = lambda;
		    }
		    else
		    {
		        arg1 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_audioengine_AudioEngine_setFinishCallback : Error processing arguments");
        cocos2d::experimental::AudioEngine::setFinishCallback(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_setFinishCallback : wrong number of arguments");
    return false;
}

bool js_cocos2dx_audioengine_AudioEngine_getProfile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::experimental::AudioProfile* ret = cocos2d::experimental::AudioEngine::getProfile(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::AudioProfile>(cx, (cocos2d::experimental::AudioProfile*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 1) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cocos2d::experimental::AudioProfile* ret = cocos2d::experimental::AudioEngine::getProfile(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::AudioProfile>(cx, (cocos2d::experimental::AudioProfile*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_audioengine_AudioEngine_getProfile : wrong number of arguments");
    return false;
}

void js_cocos2d_experimental_AudioEngine_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AudioEngine)", obj);
}
void js_register_cocos2dx_audioengine_AudioEngine(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_experimental_AudioEngine_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_experimental_AudioEngine_class->name = "AudioEngine";
    jsb_cocos2d_experimental_AudioEngine_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_AudioEngine_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_experimental_AudioEngine_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_AudioEngine_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_experimental_AudioEngine_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_experimental_AudioEngine_class->resolve = JS_ResolveStub;
    jsb_cocos2d_experimental_AudioEngine_class->convert = JS_ConvertStub;
    jsb_cocos2d_experimental_AudioEngine_class->finalize = js_cocos2d_experimental_AudioEngine_finalize;
    jsb_cocos2d_experimental_AudioEngine_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("lazyInit", js_cocos2dx_audioengine_AudioEngine_lazyInit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentTime", js_cocos2dx_audioengine_AudioEngine_setCurrentTime, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVolume", js_cocos2dx_audioengine_AudioEngine_getVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("uncache", js_cocos2dx_audioengine_AudioEngine_uncache, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeAll", js_cocos2dx_audioengine_AudioEngine_resumeAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAll", js_cocos2dx_audioengine_AudioEngine_stopAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_audioengine_AudioEngine_pause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("end", js_cocos2dx_audioengine_AudioEngine_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxAudioInstance", js_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTime", js_cocos2dx_audioengine_AudioEngine_getCurrentTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxAudioInstance", js_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoop", js_cocos2dx_audioengine_AudioEngine_isLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseAll", js_cocos2dx_audioengine_AudioEngine_pauseAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("uncacheAll", js_cocos2dx_audioengine_AudioEngine_uncacheAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVolume", js_cocos2dx_audioengine_AudioEngine_setVolume, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("preload", js_cocos2dx_audioengine_AudioEngine_preload, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play2d", js_cocos2dx_audioengine_AudioEngine_play2d, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_cocos2dx_audioengine_AudioEngine_getState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_cocos2dx_audioengine_AudioEngine_resume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_audioengine_AudioEngine_stop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_cocos2dx_audioengine_AudioEngine_getDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_cocos2dx_audioengine_AudioEngine_setLoop, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultProfile", js_cocos2dx_audioengine_AudioEngine_getDefaultProfile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFinishCallback", js_cocos2dx_audioengine_AudioEngine_setFinishCallback, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProfile", js_cocos2dx_audioengine_AudioEngine_getProfile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_experimental_AudioEngine_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_experimental_AudioEngine_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AudioEngine", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::experimental::AudioEngine> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_experimental_AudioEngine_class;
        p->proto = jsb_cocos2d_experimental_AudioEngine_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_audioengine(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_audioengine_AudioProfile(cx, ns);
    js_register_cocos2dx_audioengine_AudioEngine(cx, ns);
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
