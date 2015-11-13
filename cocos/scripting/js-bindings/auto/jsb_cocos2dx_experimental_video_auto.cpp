#include "jsb_cocos2dx_experimental_video_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "cocos2d_specifics.hpp"
#include "UIVideoPlayer.h"

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
JSClass  *jsb_cocos2d_experimental_ui_VideoPlayer_class;
JSObject *jsb_cocos2d_experimental_ui_VideoPlayer_prototype;

bool js_cocos2dx_experimental_video_VideoPlayer_getFileName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_getFileName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getFileName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_getFileName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_getURL(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_getURL : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getURL();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_getURL : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_play : Invalid Native Object");
    if (argc == 0) {
        cobj->play();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_play : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled : Error processing arguments");
        cobj->setKeepAspectRatioEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled : Error processing arguments");
        cobj->setFullScreenEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_setFileName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setFileName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setFileName : Error processing arguments");
        cobj->setFileName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setFileName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_setURL(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setURL : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setURL : Error processing arguments");
        cobj->setURL(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setURL : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_isKeepAspectRatioEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_isKeepAspectRatioEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isKeepAspectRatioEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isKeepAspectRatioEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent : Error processing arguments");
        cobj->onPlayEvent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFullScreenEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_isPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_isPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPlaying();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_seekTo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_seekTo : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_seekTo : Error processing arguments");
        cobj->seekTo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_seekTo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::experimental::ui::VideoPlayer* ret = cocos2d::experimental::ui::VideoPlayer::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::experimental::ui::VideoPlayer>(cx, (cocos2d::experimental::ui::VideoPlayer*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_experimental_video_VideoPlayer_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::experimental::ui::VideoPlayer* cobj = new (std::nothrow) cocos2d::experimental::ui::VideoPlayer();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::experimental::ui::VideoPlayer> t;
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
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::experimental::ui::VideoPlayer");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}

extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_experimental_ui_VideoPlayer_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (VideoPlayer)", obj);
}
void js_register_cocos2dx_experimental_video_VideoPlayer(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_experimental_ui_VideoPlayer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_experimental_ui_VideoPlayer_class->name = "VideoPlayer";
    jsb_cocos2d_experimental_ui_VideoPlayer_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->resolve = JS_ResolveStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->convert = JS_ConvertStub;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->finalize = js_cocos2d_experimental_ui_VideoPlayer_finalize;
    jsb_cocos2d_experimental_ui_VideoPlayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFileName", js_cocos2dx_experimental_video_VideoPlayer_getFileName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getURL", js_cocos2dx_experimental_video_VideoPlayer_getURL, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_experimental_video_VideoPlayer_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setKeepAspectRatioEnabled", js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_experimental_video_VideoPlayer_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFullScreenEnabled", js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFileName", js_cocos2dx_experimental_video_VideoPlayer_setFileName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setURL", js_cocos2dx_experimental_video_VideoPlayer_setURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isKeepAspectRatioEnabled", js_cocos2dx_experimental_video_VideoPlayer_isKeepAspectRatioEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onPlayEvent", js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFullScreenEnabled", js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_experimental_video_VideoPlayer_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("seekTo", js_cocos2dx_experimental_video_VideoPlayer_seekTo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_experimental_video_VideoPlayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_experimental_ui_VideoPlayer_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_experimental_ui_VideoPlayer_class,
        js_cocos2dx_experimental_video_VideoPlayer_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "VideoPlayer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::experimental::ui::VideoPlayer> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_experimental_ui_VideoPlayer_class;
        p->proto = jsb_cocos2d_experimental_ui_VideoPlayer_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_experimental_video(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccui", &ns);

    js_register_cocos2dx_experimental_video_VideoPlayer(cx, ns);
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
