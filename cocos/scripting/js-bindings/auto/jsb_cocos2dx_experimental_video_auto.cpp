#include "scripting/js-bindings/auto/jsb_cocos2dx_experimental_video_auto.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "ui/UIVideoPlayer.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
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
        JS::RootedValue jsret(cx);
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
        JS::RootedValue jsret(cx);
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
bool js_cocos2dx_experimental_video_VideoPlayer_isUserInputEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_isUserInputEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isUserInputEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isUserInputEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
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
bool js_cocos2dx_experimental_video_VideoPlayer_setStyle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setStyle : Invalid Native Object");
    if (argc == 1) {
        cocos2d::experimental::ui::VideoPlayer::StyleType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setStyle : Error processing arguments");
        cobj->setStyle(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setStyle : wrong number of arguments: %d, was expecting %d", argc, 1);
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
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_seekTo : Error processing arguments");
        cobj->seekTo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_seekTo : wrong number of arguments: %d, was expecting %d", argc, 1);
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
        JS::RootedValue jsret(cx);
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
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_isLooping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_isLooping : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLooping();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isLooping : wrong number of arguments: %d, was expecting %d", argc, 0);
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
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_setLooping(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setLooping : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setLooping : Error processing arguments");
        cobj->setLooping(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setLooping : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_setUserInputEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::ui::VideoPlayer* cobj = (cocos2d::experimental::ui::VideoPlayer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setUserInputEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_video_VideoPlayer_setUserInputEnabled : Error processing arguments");
        cobj->setUserInputEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_video_VideoPlayer_setUserInputEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_video_VideoPlayer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocos2d::experimental::ui::VideoPlayer::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::experimental::ui::VideoPlayer>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::experimental::ui::VideoPlayer"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
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

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::experimental::ui::VideoPlayer>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::experimental::ui::VideoPlayer"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

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
    jsb_cocos2d_experimental_ui_VideoPlayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFileName", js_cocos2dx_experimental_video_VideoPlayer_getFileName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getURL", js_cocos2dx_experimental_video_VideoPlayer_getURL, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_experimental_video_VideoPlayer_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isUserInputEnabled", js_cocos2dx_experimental_video_VideoPlayer_isUserInputEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setKeepAspectRatioEnabled", js_cocos2dx_experimental_video_VideoPlayer_setKeepAspectRatioEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_experimental_video_VideoPlayer_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFullScreenEnabled", js_cocos2dx_experimental_video_VideoPlayer_setFullScreenEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFileName", js_cocos2dx_experimental_video_VideoPlayer_setFileName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setURL", js_cocos2dx_experimental_video_VideoPlayer_setURL, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStyle", js_cocos2dx_experimental_video_VideoPlayer_setStyle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("seekTo", js_cocos2dx_experimental_video_VideoPlayer_seekTo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isKeepAspectRatioEnabled", js_cocos2dx_experimental_video_VideoPlayer_isKeepAspectRatioEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onPlayEvent", js_cocos2dx_experimental_video_VideoPlayer_onPlayEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFullScreenEnabled", js_cocos2dx_experimental_video_VideoPlayer_isFullScreenEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLooping", js_cocos2dx_experimental_video_VideoPlayer_isLooping, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_experimental_video_VideoPlayer_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLooping", js_cocos2dx_experimental_video_VideoPlayer_setLooping, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUserInputEnabled", js_cocos2dx_experimental_video_VideoPlayer_setUserInputEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_experimental_video_VideoPlayer_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_ui_Widget_prototype);
    jsb_cocos2d_experimental_ui_VideoPlayer_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_experimental_ui_VideoPlayer_class,
        js_cocos2dx_experimental_video_VideoPlayer_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_experimental_ui_VideoPlayer_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "VideoPlayer"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::experimental::ui::VideoPlayer>(cx, jsb_cocos2d_experimental_ui_VideoPlayer_class, proto, parent_proto);
}

void register_all_cocos2dx_experimental_video(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccui", &ns);

    js_register_cocos2dx_experimental_video_VideoPlayer(cx, ns);
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
