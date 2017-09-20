#include "scripting/js-bindings/auto/jsb_cocos2dx_studio_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "editor-support/cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CCComExtensionData.h"
#include "scripting/js-bindings/manual/cocostudio/jsb_cocos2dx_studio_conversions.h"

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
JSClass  *jsb_cocostudio_ActionObject_class;
JSObject *jsb_cocostudio_ActionObject_prototype;

bool js_cocos2dx_studio_ActionObject_setCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setCurrentTime : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setCurrentTime : Error processing arguments");
        cobj->setCurrentTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setName : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setName : Error processing arguments");
        cobj->setName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_setUnitTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setUnitTime : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setUnitTime : Error processing arguments");
        cobj->setUnitTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setUnitTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getTotalTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getTotalTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTotalTime();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getTotalTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getName : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getName();
        JS::RootedValue jsret(cx);
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ActionObject* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_play : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::CallFunc* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::CallFunc*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->play(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->play();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_play : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ActionObject_getCurrentTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getCurrentTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCurrentTime();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getCurrentTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_removeActionNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_removeActionNode : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ActionNode* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ActionNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_removeActionNode : Error processing arguments");
        cobj->removeActionNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_removeActionNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getLoop : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getLoop();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getLoop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_initWithBinary : Invalid Native Object");
    if (argc == 3) {
        cocostudio::CocoLoader* arg0 = nullptr;
        cocostudio::stExpCocoNode* arg1 = nullptr;
        cocos2d::Ref* arg2 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::CocoLoader*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        #pragma warning NO CONVERSION TO NATIVE FOR stExpCocoNode*
		ok = false;
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_initWithBinary : Error processing arguments");
        cobj->initWithBinary(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_initWithBinary : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_studio_ActionObject_addActionNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_addActionNode : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ActionNode* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ActionNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_addActionNode : Error processing arguments");
        cobj->addActionNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_addActionNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_getUnitTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_getUnitTime : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getUnitTime();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_getUnitTime : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_isPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_isPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPlaying();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionObject_updateToFrameByTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_updateToFrameByTime : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_updateToFrameByTime : Error processing arguments");
        cobj->updateToFrameByTime(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_updateToFrameByTime : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_setLoop : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_setLoop : Error processing arguments");
        cobj->setLoop(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_setLoop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_simulationActionUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionObject* cobj = (cocostudio::ActionObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionObject_simulationActionUpdate : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionObject_simulationActionUpdate : Error processing arguments");
        cobj->simulationActionUpdate(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionObject_simulationActionUpdate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionObject_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ActionObject* cobj = new (std::nothrow) cocostudio::ActionObject();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ActionObject>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ActionObject"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_ActionObject(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ActionObject_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ActionObject_class->name = "ActionObject";
    jsb_cocostudio_ActionObject_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ActionObject_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ActionObject_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ActionObject_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ActionObject_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ActionObject_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ActionObject_class->convert = JS_ConvertStub;
    jsb_cocostudio_ActionObject_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setCurrentTime", js_cocos2dx_studio_ActionObject_setCurrentTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_studio_ActionObject_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setName", js_cocos2dx_studio_ActionObject_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUnitTime", js_cocos2dx_studio_ActionObject_setUnitTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTotalTime", js_cocos2dx_studio_ActionObject_getTotalTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getName", js_cocos2dx_studio_ActionObject_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_studio_ActionObject_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_studio_ActionObject_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTime", js_cocos2dx_studio_ActionObject_getCurrentTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeActionNode", js_cocos2dx_studio_ActionObject_removeActionNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLoop", js_cocos2dx_studio_ActionObject_getLoop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithBinary", js_cocos2dx_studio_ActionObject_initWithBinary, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addActionNode", js_cocos2dx_studio_ActionObject_addActionNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUnitTime", js_cocos2dx_studio_ActionObject_getUnitTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_studio_ActionObject_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateToFrameByTime", js_cocos2dx_studio_ActionObject_updateToFrameByTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_cocos2dx_studio_ActionObject_setLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("simulationActionUpdate", js_cocos2dx_studio_ActionObject_simulationActionUpdate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_ActionObject_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ActionObject_class,
        js_cocos2dx_studio_ActionObject_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ActionObject_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ActionObject"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ActionObject>(cx, jsb_cocostudio_ActionObject_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_ActionManagerEx_class;
JSObject *jsb_cocostudio_ActionManagerEx_prototype;

bool js_cocos2dx_studio_ActionManagerEx_stopActionByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_stopActionByName : Invalid Native Object");
    if (argc == 2) {
        const char* arg0 = nullptr;
        const char* arg1 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_stopActionByName : Error processing arguments");
        cocostudio::ActionObject* ret = cobj->stopActionByName(arg0, arg1);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_stopActionByName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_getActionByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_getActionByName : Invalid Native Object");
    if (argc == 2) {
        const char* arg0 = nullptr;
        const char* arg1 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_getActionByName : Error processing arguments");
        cocostudio::ActionObject* ret = cobj->getActionByName(arg0, arg1);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_getActionByName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_getStudioVersionNumber(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_getStudioVersionNumber : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getStudioVersionNumber();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_getStudioVersionNumber : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_initWithBinary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithBinary : Invalid Native Object");
    if (argc == 4) {
        const char* arg0 = nullptr;
        cocos2d::Ref* arg1 = nullptr;
        cocostudio::CocoLoader* arg2 = nullptr;
        cocostudio::stExpCocoNode* arg3 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocostudio::CocoLoader*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        #pragma warning NO CONVERSION TO NATIVE FOR stExpCocoNode*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithBinary : Error processing arguments");
        cobj->initWithBinary(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_initWithBinary : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_playActionByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ActionManagerEx* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_playActionByName : Invalid Native Object");
    do {
        if (argc == 3) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocos2d::CallFunc* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::CallFunc*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocostudio::ActionObject* ret = cobj->playActionByName(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocostudio::ActionObject* ret = cobj->playActionByName(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ActionObject>(cx, (cocostudio::ActionObject*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_playActionByName : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_releaseActions(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_releaseActions : Invalid Native Object");
    if (argc == 0) {
        cobj->releaseActions();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_releaseActions : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionManagerEx_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ActionManagerEx::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ActionManagerEx_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ActionManagerEx::getInstance();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ActionManagerEx>(ret);
        JS::RootedObject jsret(cx, jsb_ref_get_or_create_jsobject(cx, ret, typeClass, "cocostudio::ActionManagerEx"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_getInstance : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_studio_ActionManagerEx(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ActionManagerEx_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ActionManagerEx_class->name = "ActionManager";
    jsb_cocostudio_ActionManagerEx_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ActionManagerEx_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ActionManagerEx_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ActionManagerEx_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ActionManagerEx_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ActionManagerEx_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ActionManagerEx_class->convert = JS_ConvertStub;
    jsb_cocostudio_ActionManagerEx_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("stopActionByName", js_cocos2dx_studio_ActionManagerEx_stopActionByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionByName", js_cocos2dx_studio_ActionManagerEx_getActionByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStudioVersionNumber", js_cocos2dx_studio_ActionManagerEx_getStudioVersionNumber, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithBinary", js_cocos2dx_studio_ActionManagerEx_initWithBinary, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playActionByName", js_cocos2dx_studio_ActionManagerEx_playActionByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("releaseActions", js_cocos2dx_studio_ActionManagerEx_releaseActions, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_studio_ActionManagerEx_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_studio_ActionManagerEx_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ActionManagerEx_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ActionManagerEx_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ActionManagerEx_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ActionManagerEx"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ActionManagerEx>(cx, jsb_cocostudio_ActionManagerEx_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_BaseData_class;
JSObject *jsb_cocostudio_BaseData_prototype;

bool js_cocos2dx_studio_BaseData_getColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::BaseData* cobj = (cocostudio::BaseData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BaseData_getColor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Color4B ret = cobj->getColor();
        JS::RootedValue jsret(cx);
        jsret = cccolor4b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BaseData_getColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BaseData_setColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::BaseData* cobj = (cocostudio::BaseData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BaseData_setColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4B arg0;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BaseData_setColor : Error processing arguments");
        cobj->setColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BaseData_setColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BaseData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::BaseData::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::BaseData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::BaseData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_BaseData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_BaseData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::BaseData* cobj = new (std::nothrow) cocostudio::BaseData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::BaseData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::BaseData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_BaseData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_BaseData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_BaseData_class->name = "BaseData";
    jsb_cocostudio_BaseData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_BaseData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_BaseData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_BaseData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_BaseData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_BaseData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_BaseData_class->convert = JS_ConvertStub;
    jsb_cocostudio_BaseData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getColor", js_cocos2dx_studio_BaseData_getColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setColor", js_cocos2dx_studio_BaseData_setColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_BaseData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_BaseData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_BaseData_class,
        js_cocos2dx_studio_BaseData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_BaseData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "BaseData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::BaseData>(cx, jsb_cocostudio_BaseData_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_MovementData_class;
JSObject *jsb_cocostudio_MovementData_prototype;

bool js_cocos2dx_studio_MovementData_getMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::MovementData* cobj = (cocostudio::MovementData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_MovementData_getMovementBoneData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_MovementData_getMovementBoneData : Error processing arguments");
        cocostudio::MovementBoneData* ret = cobj->getMovementBoneData(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::MovementBoneData>(cx, (cocostudio::MovementBoneData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_MovementData_getMovementBoneData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_MovementData_addMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::MovementData* cobj = (cocostudio::MovementData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_MovementData_addMovementBoneData : Invalid Native Object");
    if (argc == 1) {
        cocostudio::MovementBoneData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::MovementBoneData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_MovementData_addMovementBoneData : Error processing arguments");
        cobj->addMovementBoneData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_MovementData_addMovementBoneData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_MovementData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::MovementData::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::MovementData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::MovementData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_MovementData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_MovementData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::MovementData* cobj = new (std::nothrow) cocostudio::MovementData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::MovementData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::MovementData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_MovementData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_MovementData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_MovementData_class->name = "MovementData";
    jsb_cocostudio_MovementData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_MovementData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_MovementData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_MovementData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_MovementData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_MovementData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_MovementData_class->convert = JS_ConvertStub;
    jsb_cocostudio_MovementData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getMovementBoneData", js_cocos2dx_studio_MovementData_getMovementBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addMovementBoneData", js_cocos2dx_studio_MovementData_addMovementBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_MovementData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_MovementData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_MovementData_class,
        js_cocos2dx_studio_MovementData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_MovementData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "MovementData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::MovementData>(cx, jsb_cocostudio_MovementData_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_AnimationData_class;
JSObject *jsb_cocostudio_AnimationData_prototype;

bool js_cocos2dx_studio_AnimationData_getMovement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnimationData_getMovement : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_AnimationData_getMovement : Error processing arguments");
        cocostudio::MovementData* ret = cobj->getMovement(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::MovementData>(cx, (cocostudio::MovementData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnimationData_getMovement : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_AnimationData_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnimationData_getMovementCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getMovementCount();
        JS::RootedValue jsret(cx);
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnimationData_getMovementCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_AnimationData_addMovement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnimationData_addMovement : Invalid Native Object");
    if (argc == 1) {
        cocostudio::MovementData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::MovementData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_AnimationData_addMovement : Error processing arguments");
        cobj->addMovement(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnimationData_addMovement : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_AnimationData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::AnimationData::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::AnimationData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::AnimationData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_AnimationData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_AnimationData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::AnimationData* cobj = new (std::nothrow) cocostudio::AnimationData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::AnimationData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::AnimationData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_AnimationData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_AnimationData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_AnimationData_class->name = "AnimationData";
    jsb_cocostudio_AnimationData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_AnimationData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_AnimationData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_AnimationData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_AnimationData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_AnimationData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_AnimationData_class->convert = JS_ConvertStub;
    jsb_cocostudio_AnimationData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getMovement", js_cocos2dx_studio_AnimationData_getMovement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMovementCount", js_cocos2dx_studio_AnimationData_getMovementCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addMovement", js_cocos2dx_studio_AnimationData_addMovement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_AnimationData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_AnimationData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_AnimationData_class,
        js_cocos2dx_studio_AnimationData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_AnimationData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "AnimationData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::AnimationData>(cx, jsb_cocostudio_AnimationData_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_ContourData_class;
JSObject *jsb_cocostudio_ContourData_prototype;

bool js_cocos2dx_studio_ContourData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ContourData* cobj = (cocostudio::ContourData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ContourData_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ContourData_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ContourData_addVertex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ContourData* cobj = (cocostudio::ContourData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ContourData_addVertex : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ContourData_addVertex : Error processing arguments");
        cobj->addVertex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ContourData_addVertex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ContourData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ContourData::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ContourData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::ContourData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ContourData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ContourData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ContourData* cobj = new (std::nothrow) cocostudio::ContourData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ContourData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ContourData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_ContourData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ContourData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ContourData_class->name = "ContourData";
    jsb_cocostudio_ContourData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ContourData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ContourData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ContourData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ContourData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ContourData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ContourData_class->convert = JS_ConvertStub;
    jsb_cocostudio_ContourData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_cocos2dx_studio_ContourData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addVertex", js_cocos2dx_studio_ContourData_addVertex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ContourData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ContourData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ContourData_class,
        js_cocos2dx_studio_ContourData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ContourData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ContourData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ContourData>(cx, jsb_cocostudio_ContourData_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_TextureData_class;
JSObject *jsb_cocostudio_TextureData_prototype;

bool js_cocos2dx_studio_TextureData_getContourData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureData_getContourData : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_TextureData_getContourData : Error processing arguments");
        cocostudio::ContourData* ret = cobj->getContourData(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ContourData>(cx, (cocostudio::ContourData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureData_getContourData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_TextureData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureData_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureData_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_TextureData_addContourData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureData_addContourData : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ContourData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ContourData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_TextureData_addContourData : Error processing arguments");
        cobj->addContourData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureData_addContourData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_TextureData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::TextureData::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::TextureData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::TextureData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_TextureData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_TextureData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::TextureData* cobj = new (std::nothrow) cocostudio::TextureData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::TextureData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::TextureData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_TextureData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_TextureData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_TextureData_class->name = "TextureData";
    jsb_cocostudio_TextureData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_TextureData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_TextureData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_TextureData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_TextureData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_TextureData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_TextureData_class->convert = JS_ConvertStub;
    jsb_cocostudio_TextureData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getContourData", js_cocos2dx_studio_TextureData_getContourData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_TextureData_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addContourData", js_cocos2dx_studio_TextureData_addContourData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_TextureData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_TextureData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_TextureData_class,
        js_cocos2dx_studio_TextureData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_TextureData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "TextureData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::TextureData>(cx, jsb_cocostudio_TextureData_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_ProcessBase_class;
JSObject *jsb_cocostudio_ProcessBase_prototype;

bool js_cocos2dx_studio_ProcessBase_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_play : Invalid Native Object");
    if (argc == 4) {
        int arg0 = 0;
        int arg1 = 0;
        int arg2 = 0;
        int arg3 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ProcessBase_play : Error processing arguments");
        cobj->play(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_play : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_getRawDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_getRawDuration : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getRawDuration();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_getRawDuration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_resume : Invalid Native Object");
    if (argc == 0) {
        cobj->resume();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_resume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_setIsComplete(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_setIsComplete : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ProcessBase_setIsComplete : Error processing arguments");
        cobj->setIsComplete(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_setIsComplete : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_update(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_update : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ProcessBase_update : Error processing arguments");
        cobj->update(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_update : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_getCurrentFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_getCurrentFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCurrentFrameIndex();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_getCurrentFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_isComplete(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_isComplete : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isComplete();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_isComplete : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_getCurrentPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_getCurrentPercent : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCurrentPercent();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_getCurrentPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_setIsPause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_setIsPause : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ProcessBase_setIsPause : Error processing arguments");
        cobj->setIsPause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_setIsPause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_getProcessScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_getProcessScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getProcessScale();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_getProcessScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_isPause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_isPause : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPause();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_isPause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_isPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_isPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPlaying();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_setProcessScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_setProcessScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ProcessBase_setProcessScale : Error processing arguments");
        cobj->setProcessScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_setProcessScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_setIsPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ProcessBase* cobj = (cocostudio::ProcessBase *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ProcessBase_setIsPlaying : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ProcessBase_setIsPlaying : Error processing arguments");
        cobj->setIsPlaying(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ProcessBase_setIsPlaying : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ProcessBase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ProcessBase* cobj = new (std::nothrow) cocostudio::ProcessBase();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ProcessBase>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ProcessBase"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_ProcessBase(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ProcessBase_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ProcessBase_class->name = "ProcessBase";
    jsb_cocostudio_ProcessBase_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ProcessBase_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ProcessBase_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ProcessBase_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ProcessBase_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ProcessBase_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ProcessBase_class->convert = JS_ConvertStub;
    jsb_cocostudio_ProcessBase_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("play", js_cocos2dx_studio_ProcessBase_play, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_studio_ProcessBase_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRawDuration", js_cocos2dx_studio_ProcessBase_getRawDuration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_cocos2dx_studio_ProcessBase_resume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsComplete", js_cocos2dx_studio_ProcessBase_setIsComplete, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_studio_ProcessBase_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("update", js_cocos2dx_studio_ProcessBase_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentFrameIndex", js_cocos2dx_studio_ProcessBase_getCurrentFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isComplete", js_cocos2dx_studio_ProcessBase_isComplete, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentPercent", js_cocos2dx_studio_ProcessBase_getCurrentPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsPause", js_cocos2dx_studio_ProcessBase_setIsPause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProcessScale", js_cocos2dx_studio_ProcessBase_getProcessScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPause", js_cocos2dx_studio_ProcessBase_isPause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_studio_ProcessBase_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProcessScale", js_cocos2dx_studio_ProcessBase_setProcessScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsPlaying", js_cocos2dx_studio_ProcessBase_setIsPlaying, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_ProcessBase_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ProcessBase_class,
        js_cocos2dx_studio_ProcessBase_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ProcessBase_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ProcessBase"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ProcessBase>(cx, jsb_cocostudio_ProcessBase_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_Tween_class;
JSObject *jsb_cocostudio_Tween_prototype;

bool js_cocos2dx_studio_Tween_getAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Tween* cobj = (cocostudio::Tween *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Tween_getAnimation : Invalid Native Object");
    if (argc == 0) {
        cocostudio::ArmatureAnimation* ret = cobj->getAnimation();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ArmatureAnimation>(cx, (cocostudio::ArmatureAnimation*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Tween_getAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Tween_gotoAndPause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Tween* cobj = (cocostudio::Tween *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Tween_gotoAndPause : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Tween_gotoAndPause : Error processing arguments");
        cobj->gotoAndPause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Tween_gotoAndPause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Tween_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Tween* cobj = (cocostudio::Tween *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Tween_play : Invalid Native Object");
    if (argc == 5) {
        cocostudio::MovementBoneData* arg0 = nullptr;
        int arg1 = 0;
        int arg2 = 0;
        int arg3 = 0;
        int arg4 = 0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::MovementBoneData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Tween_play : Error processing arguments");
        cobj->play(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Tween_play : wrong number of arguments: %d, was expecting %d", argc, 5);
    return false;
}
bool js_cocos2dx_studio_Tween_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Tween* cobj = (cocostudio::Tween *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Tween_gotoAndPlay : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Tween_gotoAndPlay : Error processing arguments");
        cobj->gotoAndPlay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Tween_gotoAndPlay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Tween_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Tween* cobj = (cocostudio::Tween *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Tween_init : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Tween_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Tween_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Tween_setAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Tween* cobj = (cocostudio::Tween *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Tween_setAnimation : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ArmatureAnimation* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ArmatureAnimation*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Tween_setAnimation : Error processing arguments");
        cobj->setAnimation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Tween_setAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Tween_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Tween_create : Error processing arguments");

        auto ret = cocostudio::Tween::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::Tween>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::Tween"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_Tween_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_Tween_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::Tween* cobj = new (std::nothrow) cocostudio::Tween();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::Tween>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::Tween"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_ProcessBase_prototype;

void js_register_cocos2dx_studio_Tween(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_Tween_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_Tween_class->name = "Tween";
    jsb_cocostudio_Tween_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_Tween_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_Tween_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_Tween_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_Tween_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_Tween_class->resolve = JS_ResolveStub;
    jsb_cocostudio_Tween_class->convert = JS_ConvertStub;
    jsb_cocostudio_Tween_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAnimation", js_cocos2dx_studio_Tween_getAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPause", js_cocos2dx_studio_Tween_gotoAndPause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_studio_Tween_play, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPlay", js_cocos2dx_studio_Tween_gotoAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_Tween_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimation", js_cocos2dx_studio_Tween_setAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_Tween_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_ProcessBase_prototype);
    jsb_cocostudio_Tween_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_Tween_class,
        js_cocos2dx_studio_Tween_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_Tween_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Tween"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::Tween>(cx, jsb_cocostudio_Tween_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_ColliderFilter_class;
JSObject *jsb_cocostudio_ColliderFilter_prototype;


void js_register_cocos2dx_studio_ColliderFilter(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ColliderFilter_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ColliderFilter_class->name = "ColliderFilter";
    jsb_cocostudio_ColliderFilter_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ColliderFilter_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ColliderFilter_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ColliderFilter_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ColliderFilter_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ColliderFilter_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ColliderFilter_class->convert = JS_ConvertStub;
    jsb_cocostudio_ColliderFilter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_ColliderFilter_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ColliderFilter_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ColliderFilter_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ColliderFilter"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ColliderFilter>(cx, jsb_cocostudio_ColliderFilter_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_ColliderBody_class;
JSObject *jsb_cocostudio_ColliderBody_prototype;


void js_register_cocos2dx_studio_ColliderBody(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ColliderBody_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ColliderBody_class->name = "ColliderBody";
    jsb_cocostudio_ColliderBody_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ColliderBody_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ColliderBody_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ColliderBody_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ColliderBody_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ColliderBody_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ColliderBody_class->convert = JS_ConvertStub;
    jsb_cocostudio_ColliderBody_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_ColliderBody_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ColliderBody_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ColliderBody_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ColliderBody"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ColliderBody>(cx, jsb_cocostudio_ColliderBody_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_ColliderDetector_class;
JSObject *jsb_cocostudio_ColliderDetector_prototype;

bool js_cocos2dx_studio_ColliderDetector_getBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_getBone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Bone* ret = cobj->getBone();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_getBone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_getActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_getActive : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getActive();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_getActive : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_getColliderBodyList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_getColliderBodyList : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocostudio::ColliderBody *>& ret = cobj->getColliderBodyList();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_getColliderBodyList : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_updateTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_updateTransform : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Mat4 arg0;
        ok &= jsval_to_matrix(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ColliderDetector_updateTransform : Error processing arguments");
        cobj->updateTransform(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_updateTransform : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_removeAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_removeAll : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAll();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_removeAll : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ColliderDetector* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_init : Invalid Native Object");
    do {
        if (argc == 1) {
            cocostudio::Bone* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            bool ret = cobj->init();
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_init : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_setActive(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_setActive : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ColliderDetector_setActive : Error processing arguments");
        cobj->setActive(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_setActive : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_setBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderDetector* cobj = (cocostudio::ColliderDetector *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColliderDetector_setBone : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ColliderDetector_setBone : Error processing arguments");
        cobj->setBone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_setBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ColliderDetector_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocostudio::Bone* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocostudio::ColliderDetector* ret = cocostudio::ColliderDetector::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ColliderDetector>(cx, (cocostudio::ColliderDetector*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::ColliderDetector* ret = cocostudio::ColliderDetector::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ColliderDetector>(cx, (cocostudio::ColliderDetector*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_ColliderDetector_create : wrong number of arguments");
    return false;
}

void js_register_cocos2dx_studio_ColliderDetector(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ColliderDetector_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ColliderDetector_class->name = "ColliderDetector";
    jsb_cocostudio_ColliderDetector_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ColliderDetector_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ColliderDetector_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ColliderDetector_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ColliderDetector_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ColliderDetector_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ColliderDetector_class->convert = JS_ConvertStub;
    jsb_cocostudio_ColliderDetector_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBone", js_cocos2dx_studio_ColliderDetector_getBone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActive", js_cocos2dx_studio_ColliderDetector_getActive, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getColliderBodyList", js_cocos2dx_studio_ColliderDetector_getColliderBodyList, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateTransform", js_cocos2dx_studio_ColliderDetector_updateTransform, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAll", js_cocos2dx_studio_ColliderDetector_removeAll, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ColliderDetector_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActive", js_cocos2dx_studio_ColliderDetector_setActive, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBone", js_cocos2dx_studio_ColliderDetector_setBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ColliderDetector_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ColliderDetector_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ColliderDetector_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ColliderDetector_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ColliderDetector"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ColliderDetector>(cx, jsb_cocostudio_ColliderDetector_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_DecorativeDisplay_class;
JSObject *jsb_cocostudio_DecorativeDisplay_prototype;

bool js_cocos2dx_studio_DecorativeDisplay_getColliderDetector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_getColliderDetector : Invalid Native Object");
    if (argc == 0) {
        cocostudio::ColliderDetector* ret = cobj->getColliderDetector();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ColliderDetector>(cx, (cocostudio::ColliderDetector*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_getColliderDetector : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_getDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_getDisplay : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getDisplay();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_getDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_setDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_setDisplay : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DecorativeDisplay_setDisplay : Error processing arguments");
        cobj->setDisplay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_setDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_setDisplayData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_setDisplayData : Invalid Native Object");
    if (argc == 1) {
        cocostudio::DisplayData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::DisplayData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DecorativeDisplay_setDisplayData : Error processing arguments");
        cobj->setDisplayData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_setDisplayData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_getDisplayData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_getDisplayData : Invalid Native Object");
    if (argc == 0) {
        cocostudio::DisplayData* ret = cobj->getDisplayData();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::DisplayData>(cx, (cocostudio::DisplayData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_getDisplayData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_setColliderDetector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DecorativeDisplay* cobj = (cocostudio::DecorativeDisplay *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DecorativeDisplay_setColliderDetector : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ColliderDetector* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ColliderDetector*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DecorativeDisplay_setColliderDetector : Error processing arguments");
        cobj->setColliderDetector(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_setColliderDetector : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DecorativeDisplay_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::DecorativeDisplay::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::DecorativeDisplay>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::DecorativeDisplay"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_DecorativeDisplay_create : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_studio_DecorativeDisplay(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_DecorativeDisplay_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_DecorativeDisplay_class->name = "DecorativeDisplay";
    jsb_cocostudio_DecorativeDisplay_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_DecorativeDisplay_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_DecorativeDisplay_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_DecorativeDisplay_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_DecorativeDisplay_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_DecorativeDisplay_class->resolve = JS_ResolveStub;
    jsb_cocostudio_DecorativeDisplay_class->convert = JS_ConvertStub;
    jsb_cocostudio_DecorativeDisplay_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getColliderDetector", js_cocos2dx_studio_DecorativeDisplay_getColliderDetector, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplay", js_cocos2dx_studio_DecorativeDisplay_getDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDisplay", js_cocos2dx_studio_DecorativeDisplay_setDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_DecorativeDisplay_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDisplayData", js_cocos2dx_studio_DecorativeDisplay_setDisplayData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayData", js_cocos2dx_studio_DecorativeDisplay_getDisplayData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setColliderDetector", js_cocos2dx_studio_DecorativeDisplay_setColliderDetector, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_DecorativeDisplay_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_DecorativeDisplay_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_DecorativeDisplay_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_DecorativeDisplay_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "DecorativeDisplay"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::DecorativeDisplay>(cx, jsb_cocostudio_DecorativeDisplay_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_DisplayManager_class;
JSObject *jsb_cocostudio_DisplayManager_prototype;

bool js_cocos2dx_studio_DisplayManager_getCurrentDecorativeDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getCurrentDecorativeDisplay : Invalid Native Object");
    if (argc == 0) {
        cocostudio::DecorativeDisplay* ret = cobj->getCurrentDecorativeDisplay();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::DecorativeDisplay>(cx, (cocostudio::DecorativeDisplay*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getCurrentDecorativeDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getDisplayRenderNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getDisplayRenderNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getDisplayRenderNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getDisplayRenderNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getAnchorPointInPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getAnchorPointInPoints : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getAnchorPointInPoints();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getAnchorPointInPoints : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_setCurrentDecorativeDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_setCurrentDecorativeDisplay : Invalid Native Object");
    if (argc == 1) {
        cocostudio::DecorativeDisplay* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::DecorativeDisplay*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_setCurrentDecorativeDisplay : Error processing arguments");
        cobj->setCurrentDecorativeDisplay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_setCurrentDecorativeDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getDisplayRenderNodeType();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_removeDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_removeDisplay : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_removeDisplay : Error processing arguments");
        cobj->removeDisplay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_removeDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_setForceChangeDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_setForceChangeDisplay : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_setForceChangeDisplay : Error processing arguments");
        cobj->setForceChangeDisplay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_setForceChangeDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_init : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getContentSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getContentSize();
        JS::RootedValue jsret(cx);
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getContentSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getBoundingBox : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getBoundingBox();
        JS::RootedValue jsret(cx);
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getBoundingBox : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_addDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::DisplayManager* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_addDisplay : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj->addDisplay(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocostudio::DisplayData* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::DisplayData*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj->addDisplay(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_addDisplay : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_DisplayManager_containPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::DisplayManager* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_containPoint : Invalid Native Object");
    do {
        if (argc == 2) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->containPoint(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= jsval_to_vector2(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->containPoint(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_containPoint : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_DisplayManager_initDisplayList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_initDisplayList : Invalid Native Object");
    if (argc == 1) {
        cocostudio::BoneData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::BoneData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_initDisplayList : Error processing arguments");
        cobj->initDisplayList(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_initDisplayList : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_changeDisplayWithIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_changeDisplayWithIndex : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        bool arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_changeDisplayWithIndex : Error processing arguments");
        cobj->changeDisplayWithIndex(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_changeDisplayWithIndex : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_changeDisplayWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_changeDisplayWithName : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_changeDisplayWithName : Error processing arguments");
        cobj->changeDisplayWithName(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_changeDisplayWithName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_isForceChangeDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_isForceChangeDisplay : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isForceChangeDisplay();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_isForceChangeDisplay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getDecorativeDisplayByIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getDecorativeDisplayByIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_getDecorativeDisplayByIndex : Error processing arguments");
        cocostudio::DecorativeDisplay* ret = cobj->getDecorativeDisplayByIndex(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::DecorativeDisplay>(cx, (cocostudio::DecorativeDisplay*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getDecorativeDisplayByIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCurrentDisplayIndex();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getAnchorPoint : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getAnchorPoint();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_getDecorativeDisplayList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_getDecorativeDisplayList : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocostudio::DecorativeDisplay *>& ret = cobj->getDecorativeDisplayList();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_getDecorativeDisplayList : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_isVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_isVisible : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isVisible();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_isVisible : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_setVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::DisplayManager* cobj = (cocostudio::DisplayManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_DisplayManager_setVisible : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_setVisible : Error processing arguments");
        cobj->setVisible(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_setVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_DisplayManager_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_DisplayManager_create : Error processing arguments");

        auto ret = cocostudio::DisplayManager::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::DisplayManager>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::DisplayManager"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_DisplayManager_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_DisplayManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::DisplayManager* cobj = new (std::nothrow) cocostudio::DisplayManager();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::DisplayManager>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::DisplayManager"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_DisplayManager(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_DisplayManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_DisplayManager_class->name = "DisplayManager";
    jsb_cocostudio_DisplayManager_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_DisplayManager_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_DisplayManager_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_DisplayManager_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_DisplayManager_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_DisplayManager_class->resolve = JS_ResolveStub;
    jsb_cocostudio_DisplayManager_class->convert = JS_ConvertStub;
    jsb_cocostudio_DisplayManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getCurrentDecorativeDisplay", js_cocos2dx_studio_DisplayManager_getCurrentDecorativeDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayRenderNode", js_cocos2dx_studio_DisplayManager_getDisplayRenderNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorPointInPoints", js_cocos2dx_studio_DisplayManager_getAnchorPointInPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentDecorativeDisplay", js_cocos2dx_studio_DisplayManager_setCurrentDecorativeDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayRenderNodeType", js_cocos2dx_studio_DisplayManager_getDisplayRenderNodeType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeDisplay", js_cocos2dx_studio_DisplayManager_removeDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setForceChangeDisplay", js_cocos2dx_studio_DisplayManager_setForceChangeDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_DisplayManager_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getContentSize", js_cocos2dx_studio_DisplayManager_getContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoundingBox", js_cocos2dx_studio_DisplayManager_getBoundingBox, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDisplay", js_cocos2dx_studio_DisplayManager_addDisplay, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("containPoint", js_cocos2dx_studio_DisplayManager_containPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initDisplayList", js_cocos2dx_studio_DisplayManager_initDisplayList, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeDisplayWithIndex", js_cocos2dx_studio_DisplayManager_changeDisplayWithIndex, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeDisplayWithName", js_cocos2dx_studio_DisplayManager_changeDisplayWithName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isForceChangeDisplay", js_cocos2dx_studio_DisplayManager_isForceChangeDisplay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDecorativeDisplayByIndex", js_cocos2dx_studio_DisplayManager_getDecorativeDisplayByIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentDisplayIndex", js_cocos2dx_studio_DisplayManager_getCurrentDisplayIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorPoint", js_cocos2dx_studio_DisplayManager_getAnchorPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDecorativeDisplayList", js_cocos2dx_studio_DisplayManager_getDecorativeDisplayList, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isVisible", js_cocos2dx_studio_DisplayManager_isVisible, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVisible", js_cocos2dx_studio_DisplayManager_setVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_DisplayManager_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_DisplayManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_DisplayManager_class,
        js_cocos2dx_studio_DisplayManager_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_DisplayManager_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "DisplayManager"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::DisplayManager>(cx, jsb_cocostudio_DisplayManager_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_Bone_class;
JSObject *jsb_cocostudio_Bone_prototype;

bool js_cocos2dx_studio_Bone_isTransformDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_isTransformDirty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTransformDirty();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_isTransformDirty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_isIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_isIgnoreMovementBoneData : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isIgnoreMovementBoneData();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_isIgnoreMovementBoneData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_updateZOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_updateZOrder : Invalid Native Object");
    if (argc == 0) {
        cobj->updateZOrder();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_updateZOrder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_getDisplayRenderNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getDisplayRenderNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getDisplayRenderNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getDisplayRenderNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_isBlendDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_isBlendDirty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBlendDirty();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_isBlendDirty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_addChildBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_addChildBone : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_addChildBone : Error processing arguments");
        cobj->addChildBone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_addChildBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_getWorldInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getWorldInfo : Invalid Native Object");
    if (argc == 0) {
        cocostudio::BaseData* ret = cobj->getWorldInfo();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::BaseData>(cx, (cocostudio::BaseData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getWorldInfo : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_getTween(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getTween : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Tween* ret = cobj->getTween();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Tween>(cx, (cocostudio::Tween*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getTween : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_getParentBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getParentBone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Bone* ret = cobj->getParentBone();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getParentBone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_updateColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_updateColor : Invalid Native Object");
    if (argc == 0) {
        cobj->updateColor();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_updateColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_setTransformDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setTransformDirty : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setTransformDirty : Error processing arguments");
        cobj->setTransformDirty(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setTransformDirty : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_getDisplayRenderNodeType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getDisplayRenderNodeType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getDisplayRenderNodeType();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getDisplayRenderNodeType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_removeDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_removeDisplay : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_removeDisplay : Error processing arguments");
        cobj->removeDisplay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_removeDisplay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_setBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setBoneData : Invalid Native Object");
    if (argc == 1) {
        cocostudio::BoneData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::BoneData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setBoneData : Error processing arguments");
        cobj->setBoneData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setBoneData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_init : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_setParentBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setParentBone : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setParentBone : Error processing arguments");
        cobj->setParentBone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setParentBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_addDisplay(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::Bone* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_addDisplay : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj->addDisplay(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocostudio::DisplayData* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::DisplayData*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj->addDisplay(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_addDisplay : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_Bone_setIgnoreMovementBoneData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setIgnoreMovementBoneData : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setIgnoreMovementBoneData : Error processing arguments");
        cobj->setIgnoreMovementBoneData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setIgnoreMovementBoneData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        cocos2d::BlendFunc ret = cobj->getBlendFunc();
        JS::RootedValue jsret(cx);
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_removeFromParent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_removeFromParent : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_removeFromParent : Error processing arguments");
        cobj->removeFromParent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_removeFromParent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_getColliderDetector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getColliderDetector : Invalid Native Object");
    if (argc == 0) {
        cocostudio::ColliderDetector* ret = cobj->getColliderDetector();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ColliderDetector>(cx, (cocostudio::ColliderDetector*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getColliderDetector : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_getChildArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getChildArmature : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Armature* ret = cobj->getChildArmature();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Armature>(cx, (cocostudio::Armature*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getChildArmature : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_changeDisplayWithIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_changeDisplayWithIndex : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        bool arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_changeDisplayWithIndex : Error processing arguments");
        cobj->changeDisplayWithIndex(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_changeDisplayWithIndex : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Bone_changeDisplayWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_changeDisplayWithName : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_changeDisplayWithName : Error processing arguments");
        cobj->changeDisplayWithName(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_changeDisplayWithName : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Bone_setArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setArmature : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Armature* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Armature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setArmature : Error processing arguments");
        cobj->setArmature(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setArmature : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_setBlendDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setBlendDirty : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setBlendDirty : Error processing arguments");
        cobj->setBlendDirty(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setBlendDirty : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_removeChildBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_removeChildBone : Invalid Native Object");
    if (argc == 2) {
        cocostudio::Bone* arg0 = nullptr;
        bool arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_removeChildBone : Error processing arguments");
        cobj->removeChildBone(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_removeChildBone : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Bone_setChildArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_setChildArmature : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Armature* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Armature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Bone_setChildArmature : Error processing arguments");
        cobj->setChildArmature(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_setChildArmature : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Bone_getNodeToArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getNodeToArmatureTransform : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getNodeToArmatureTransform();
        JS::RootedValue jsret(cx);
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getNodeToArmatureTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_getDisplayManager(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getDisplayManager : Invalid Native Object");
    if (argc == 0) {
        cocostudio::DisplayManager* ret = cobj->getDisplayManager();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::DisplayManager>(cx, (cocostudio::DisplayManager*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getDisplayManager : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_getArmature(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Bone* cobj = (cocostudio::Bone *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Bone_getArmature : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Armature* ret = cobj->getArmature();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Armature>(cx, (cocostudio::Armature*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Bone_getArmature : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Bone_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocostudio::Bone* ret = cocostudio::Bone::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::Bone* ret = cocostudio::Bone::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_Bone_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_Bone_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::Bone* cobj = new (std::nothrow) cocostudio::Bone();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::Bone>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::Bone"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_studio_Bone(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_Bone_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_Bone_class->name = "Bone";
    jsb_cocostudio_Bone_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_Bone_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_Bone_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_Bone_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_Bone_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_Bone_class->resolve = JS_ResolveStub;
    jsb_cocostudio_Bone_class->convert = JS_ConvertStub;
    jsb_cocostudio_Bone_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isTransformDirty", js_cocos2dx_studio_Bone_isTransformDirty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_studio_Bone_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isIgnoreMovementBoneData", js_cocos2dx_studio_Bone_isIgnoreMovementBoneData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateZOrder", js_cocos2dx_studio_Bone_updateZOrder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayRenderNode", js_cocos2dx_studio_Bone_getDisplayRenderNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBlendDirty", js_cocos2dx_studio_Bone_isBlendDirty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addChildBone", js_cocos2dx_studio_Bone_addChildBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getWorldInfo", js_cocos2dx_studio_Bone_getWorldInfo, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTween", js_cocos2dx_studio_Bone_getTween, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParentBone", js_cocos2dx_studio_Bone_getParentBone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateColor", js_cocos2dx_studio_Bone_updateColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTransformDirty", js_cocos2dx_studio_Bone_setTransformDirty, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayRenderNodeType", js_cocos2dx_studio_Bone_getDisplayRenderNodeType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeDisplay", js_cocos2dx_studio_Bone_removeDisplay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBoneData", js_cocos2dx_studio_Bone_setBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_Bone_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setParentBone", js_cocos2dx_studio_Bone_setParentBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDisplay", js_cocos2dx_studio_Bone_addDisplay, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIgnoreMovementBoneData", js_cocos2dx_studio_Bone_setIgnoreMovementBoneData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_studio_Bone_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFromParent", js_cocos2dx_studio_Bone_removeFromParent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getColliderDetector", js_cocos2dx_studio_Bone_getColliderDetector, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildArmature", js_cocos2dx_studio_Bone_getChildArmature, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeDisplayWithIndex", js_cocos2dx_studio_Bone_changeDisplayWithIndex, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeDisplayWithName", js_cocos2dx_studio_Bone_changeDisplayWithName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setArmature", js_cocos2dx_studio_Bone_setArmature, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendDirty", js_cocos2dx_studio_Bone_setBlendDirty, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeChildBone", js_cocos2dx_studio_Bone_removeChildBone, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setChildArmature", js_cocos2dx_studio_Bone_setChildArmature, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNodeToArmatureTransform", js_cocos2dx_studio_Bone_getNodeToArmatureTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayManager", js_cocos2dx_studio_Bone_getDisplayManager, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmature", js_cocos2dx_studio_Bone_getArmature, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_Bone_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocostudio_Bone_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_Bone_class,
        js_cocos2dx_studio_Bone_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_Bone_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Bone"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::Bone>(cx, jsb_cocostudio_Bone_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_BatchNode_class;
JSObject *jsb_cocostudio_BatchNode_prototype;

bool js_cocos2dx_studio_BatchNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::BatchNode::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::BatchNode>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::BatchNode"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_BatchNode_create : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_studio_BatchNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_BatchNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_BatchNode_class->name = "BatchNode";
    jsb_cocostudio_BatchNode_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_BatchNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_BatchNode_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_BatchNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_BatchNode_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_BatchNode_class->resolve = JS_ResolveStub;
    jsb_cocostudio_BatchNode_class->convert = JS_ConvertStub;
    jsb_cocostudio_BatchNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_BatchNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocostudio_BatchNode_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_BatchNode_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_BatchNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "BatchNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::BatchNode>(cx, jsb_cocostudio_BatchNode_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_ArmatureAnimation_class;
JSObject *jsb_cocostudio_ArmatureAnimation_prototype;

bool js_cocos2dx_studio_ArmatureAnimation_getSpeedScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_getSpeedScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSpeedScale();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_getSpeedScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_play : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_play : Error processing arguments");
        cobj->play(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        int arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_play : Error processing arguments");
        cobj->play(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        int arg1 = 0;
        int arg2 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_play : Error processing arguments");
        cobj->play(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_play : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_gotoAndPause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_gotoAndPause : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_gotoAndPause : Error processing arguments");
        cobj->gotoAndPause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_gotoAndPause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_playWithIndexes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndexes : Invalid Native Object");
    if (argc == 1) {
        std::vector<int> arg0;
        ok &= jsval_to_std_vector_int(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndexes : Error processing arguments");
        cobj->playWithIndexes(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::vector<int> arg0;
        int arg1 = 0;
        ok &= jsval_to_std_vector_int(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndexes : Error processing arguments");
        cobj->playWithIndexes(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::vector<int> arg0;
        int arg1 = 0;
        bool arg2;
        ok &= jsval_to_std_vector_int(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndexes : Error processing arguments");
        cobj->playWithIndexes(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_playWithIndexes : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_setAnimationData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_setAnimationData : Invalid Native Object");
    if (argc == 1) {
        cocostudio::AnimationData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::AnimationData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_setAnimationData : Error processing arguments");
        cobj->setAnimationData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_setAnimationData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_setSpeedScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_setSpeedScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_setSpeedScale : Error processing arguments");
        cobj->setSpeedScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_setSpeedScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_getAnimationData : Invalid Native Object");
    if (argc == 0) {
        cocostudio::AnimationData* ret = cobj->getAnimationData();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::AnimationData>(cx, (cocostudio::AnimationData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_getAnimationData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay : Error processing arguments");
        cobj->gotoAndPlay(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_init : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Armature* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Armature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_playWithNames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithNames : Invalid Native Object");
    if (argc == 1) {
        std::vector<std::string> arg0;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithNames : Error processing arguments");
        cobj->playWithNames(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::vector<std::string> arg0;
        int arg1 = 0;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithNames : Error processing arguments");
        cobj->playWithNames(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::vector<std::string> arg0;
        int arg1 = 0;
        bool arg2;
        ok &= jsval_to_std_vector_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithNames : Error processing arguments");
        cobj->playWithNames(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_playWithNames : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_getMovementCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_getMovementCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getMovementCount();
        JS::RootedValue jsret(cx);
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_getMovementCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_playWithIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndex : Error processing arguments");
        cobj->playWithIndex(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        int arg0 = 0;
        int arg1 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndex : Error processing arguments");
        cobj->playWithIndex(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        int arg0 = 0;
        int arg1 = 0;
        int arg2 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_playWithIndex : Error processing arguments");
        cobj->playWithIndex(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_playWithIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getCurrentMovementID();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureAnimation_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocostudio::Armature* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Armature*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureAnimation_create : Error processing arguments");

        auto ret = cocostudio::ArmatureAnimation::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ArmatureAnimation>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::ArmatureAnimation"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureAnimation_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ArmatureAnimation_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ArmatureAnimation* cobj = new (std::nothrow) cocostudio::ArmatureAnimation();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ArmatureAnimation>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ArmatureAnimation"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_ProcessBase_prototype;

void js_register_cocos2dx_studio_ArmatureAnimation(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ArmatureAnimation_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ArmatureAnimation_class->name = "ArmatureAnimation";
    jsb_cocostudio_ArmatureAnimation_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ArmatureAnimation_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ArmatureAnimation_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ArmatureAnimation_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ArmatureAnimation_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ArmatureAnimation_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ArmatureAnimation_class->convert = JS_ConvertStub;
    jsb_cocostudio_ArmatureAnimation_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getSpeedScale", js_cocos2dx_studio_ArmatureAnimation_getSpeedScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_studio_ArmatureAnimation_play, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPause", js_cocos2dx_studio_ArmatureAnimation_gotoAndPause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playWithIndexes", js_cocos2dx_studio_ArmatureAnimation_playWithIndexes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimationData", js_cocos2dx_studio_ArmatureAnimation_setAnimationData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSpeedScale", js_cocos2dx_studio_ArmatureAnimation_setSpeedScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationData", js_cocos2dx_studio_ArmatureAnimation_getAnimationData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoAndPlay", js_cocos2dx_studio_ArmatureAnimation_gotoAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ArmatureAnimation_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playWithNames", js_cocos2dx_studio_ArmatureAnimation_playWithNames, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMovementCount", js_cocos2dx_studio_ArmatureAnimation_getMovementCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playWithIndex", js_cocos2dx_studio_ArmatureAnimation_playWithIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentMovementID", js_cocos2dx_studio_ArmatureAnimation_getCurrentMovementID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ArmatureAnimation_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_ProcessBase_prototype);
    jsb_cocostudio_ArmatureAnimation_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_ArmatureAnimation_class,
        js_cocos2dx_studio_ArmatureAnimation_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ArmatureAnimation_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ArmatureAnimation"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ArmatureAnimation>(cx, jsb_cocostudio_ArmatureAnimation_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_ArmatureDataManager_class;
JSObject *jsb_cocostudio_ArmatureDataManager_prototype;

bool js_cocos2dx_studio_ArmatureDataManager_getAnimationDatas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getAnimationDatas : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Map<std::string, cocostudio::AnimationData *>& ret = cobj->getAnimationDatas();
        JS::RootedValue jsret(cx);
        jsret = ccmap_string_key_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_getAnimationDatas : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_removeAnimationData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeAnimationData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeAnimationData : Error processing arguments");
        cobj->removeAnimationData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_removeAnimationData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_addArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addArmatureData : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocostudio::ArmatureData* arg1 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocostudio::ArmatureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addArmatureData : Error processing arguments");
        cobj->addArmatureData(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        cocostudio::ArmatureData* arg1 = nullptr;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocostudio::ArmatureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addArmatureData : Error processing arguments");
        cobj->addArmatureData(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_addArmatureData : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ArmatureDataManager* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo : Invalid Native Object");
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cobj->addArmatureFileInfo(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->addArmatureFileInfo(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo : Error processing arguments");
        cobj->removeArmatureFileInfo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_getTextureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getTextureData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getTextureData : Error processing arguments");
        cocostudio::TextureData* ret = cobj->getTextureData(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::TextureData>(cx, (cocostudio::TextureData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_getTextureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getArmatureData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getArmatureData : Error processing arguments");
        cocostudio::ArmatureData* ret = cobj->getArmatureData(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ArmatureData>(cx, (cocostudio::ArmatureData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_getArmatureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_getAnimationData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getAnimationData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getAnimationData : Error processing arguments");
        cocostudio::AnimationData* ret = cobj->getAnimationData(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::AnimationData>(cx, (cocostudio::AnimationData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_getAnimationData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_addAnimationData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addAnimationData : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocostudio::AnimationData* arg1 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocostudio::AnimationData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addAnimationData : Error processing arguments");
        cobj->addAnimationData(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        cocostudio::AnimationData* arg1 = nullptr;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocostudio::AnimationData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addAnimationData : Error processing arguments");
        cobj->addAnimationData(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_addAnimationData : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_removeArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeArmatureData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeArmatureData : Error processing arguments");
        cobj->removeArmatureData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_removeArmatureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_getArmatureDatas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_getArmatureDatas : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Map<std::string, cocostudio::ArmatureData *>& ret = cobj->getArmatureDatas();
        JS::RootedValue jsret(cx);
        jsret = ccmap_string_key_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_getArmatureDatas : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_removeTextureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeTextureData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_removeTextureData : Error processing arguments");
        cobj->removeTextureData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_removeTextureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_addTextureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addTextureData : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocostudio::TextureData* arg1 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocostudio::TextureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addTextureData : Error processing arguments");
        cobj->addTextureData(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        cocostudio::TextureData* arg1 = nullptr;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocostudio::TextureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addTextureData : Error processing arguments");
        cobj->addTextureData(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_addTextureData : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isAutoLoadSpriteFile();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile : Error processing arguments");
        cobj->addSpriteFrameFromFile(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile : Error processing arguments");
        cobj->addSpriteFrameFromFile(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ArmatureDataManager_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocostudio::ArmatureDataManager::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ArmatureDataManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ArmatureDataManager::getInstance();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ArmatureDataManager>(ret);
        JS::RootedObject jsret(cx, jsb_ref_get_or_create_jsobject(cx, ret, typeClass, "cocostudio::ArmatureDataManager"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ArmatureDataManager_getInstance : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_studio_ArmatureDataManager(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ArmatureDataManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ArmatureDataManager_class->name = "ArmatureDataManager";
    jsb_cocostudio_ArmatureDataManager_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ArmatureDataManager_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ArmatureDataManager_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ArmatureDataManager_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ArmatureDataManager_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ArmatureDataManager_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ArmatureDataManager_class->convert = JS_ConvertStub;
    jsb_cocostudio_ArmatureDataManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAnimationDatas", js_cocos2dx_studio_ArmatureDataManager_getAnimationDatas, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAnimationData", js_cocos2dx_studio_ArmatureDataManager_removeAnimationData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addArmatureData", js_cocos2dx_studio_ArmatureDataManager_addArmatureData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addArmatureFileInfo", js_cocos2dx_studio_ArmatureDataManager_addArmatureFileInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeArmatureFileInfo", js_cocos2dx_studio_ArmatureDataManager_removeArmatureFileInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextureData", js_cocos2dx_studio_ArmatureDataManager_getTextureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureData", js_cocos2dx_studio_ArmatureDataManager_getArmatureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationData", js_cocos2dx_studio_ArmatureDataManager_getAnimationData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addAnimationData", js_cocos2dx_studio_ArmatureDataManager_addAnimationData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ArmatureDataManager_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeArmatureData", js_cocos2dx_studio_ArmatureDataManager_removeArmatureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureDatas", js_cocos2dx_studio_ArmatureDataManager_getArmatureDatas, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeTextureData", js_cocos2dx_studio_ArmatureDataManager_removeTextureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addTextureData", js_cocos2dx_studio_ArmatureDataManager_addTextureData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAutoLoadSpriteFile", js_cocos2dx_studio_ArmatureDataManager_isAutoLoadSpriteFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addSpriteFrameFromFile", js_cocos2dx_studio_ArmatureDataManager_addSpriteFrameFromFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_studio_ArmatureDataManager_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_studio_ArmatureDataManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_ArmatureDataManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_ArmatureDataManager_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ArmatureDataManager_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ArmatureDataManager"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ArmatureDataManager>(cx, jsb_cocostudio_ArmatureDataManager_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_Armature_class;
JSObject *jsb_cocostudio_Armature_prototype;

bool js_cocos2dx_studio_Armature_getBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getBone : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_getBone : Error processing arguments");
        cocostudio::Bone* ret = cobj->getBone(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_changeBoneParent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_changeBoneParent : Invalid Native Object");
    if (argc == 2) {
        cocostudio::Bone* arg0 = nullptr;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_changeBoneParent : Error processing arguments");
        cobj->changeBoneParent(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_changeBoneParent : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Armature_setAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_setAnimation : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ArmatureAnimation* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ArmatureAnimation*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_setAnimation : Error processing arguments");
        cobj->setAnimation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_setAnimation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_getBoneAtPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getBoneAtPoint : Invalid Native Object");
    if (argc == 2) {
        double arg0 = 0;
        double arg1 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_getBoneAtPoint : Error processing arguments");
        cocostudio::Bone* ret = cobj->getBoneAtPoint(arg0, arg1);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getBoneAtPoint : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Armature_getArmatureTransformDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getArmatureTransformDirty : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getArmatureTransformDirty();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getArmatureTransformDirty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_setVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_setVersion : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_setVersion : Error processing arguments");
        cobj->setVersion(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_setVersion : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_updateOffsetPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_updateOffsetPoint : Invalid Native Object");
    if (argc == 0) {
        cobj->updateOffsetPoint();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_updateOffsetPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_getParentBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getParentBone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Bone* ret = cobj->getParentBone();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getParentBone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_removeBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_removeBone : Invalid Native Object");
    if (argc == 2) {
        cocostudio::Bone* arg0 = nullptr;
        bool arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_removeBone : Error processing arguments");
        cobj->removeBone(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_removeBone : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Armature_getBatchNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getBatchNode : Invalid Native Object");
    if (argc == 0) {
        cocostudio::BatchNode* ret = cobj->getBatchNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::BatchNode>(cx, (cocostudio::BatchNode*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getBatchNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::Armature* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_init : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocostudio::Bone* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_init : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_Armature_setParentBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_setParentBone : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_setParentBone : Error processing arguments");
        cobj->setParentBone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_setParentBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_setBatchNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_setBatchNode : Invalid Native Object");
    if (argc == 1) {
        cocostudio::BatchNode* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::BatchNode*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_setBatchNode : Error processing arguments");
        cobj->setBatchNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_setBatchNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        JS::RootedValue jsret(cx);
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_setArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_setArmatureData : Invalid Native Object");
    if (argc == 1) {
        cocostudio::ArmatureData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::ArmatureData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_setArmatureData : Error processing arguments");
        cobj->setArmatureData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_setArmatureData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_addBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_addBone : Invalid Native Object");
    if (argc == 2) {
        cocostudio::Bone* arg0 = nullptr;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_addBone : Error processing arguments");
        cobj->addBone(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_addBone : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Armature_getArmatureData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getArmatureData : Invalid Native Object");
    if (argc == 0) {
        cocostudio::ArmatureData* ret = cobj->getArmatureData();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ArmatureData>(cx, (cocostudio::ArmatureData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getArmatureData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_getBoundingBox(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getBoundingBox : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getBoundingBox();
        JS::RootedValue jsret(cx);
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getBoundingBox : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_getVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getVersion : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getVersion();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_getAnimation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getAnimation : Invalid Native Object");
    if (argc == 0) {
        cocostudio::ArmatureAnimation* ret = cobj->getAnimation();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ArmatureAnimation>(cx, (cocostudio::ArmatureAnimation*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getAnimation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_getOffsetPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getOffsetPoints : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getOffsetPoints();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getOffsetPoints : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Armature_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Armature_getBoneDic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Armature* cobj = (cocostudio::Armature *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Armature_getBoneDic : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Map<std::string, cocostudio::Bone *>& ret = cobj->getBoneDic();
        JS::RootedValue jsret(cx);
        jsret = ccmap_string_key_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Armature_getBoneDic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Armature_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocostudio::Armature* ret = cocostudio::Armature::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Armature>(cx, (cocostudio::Armature*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::Armature* ret = cocostudio::Armature::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Armature>(cx, (cocostudio::Armature*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocostudio::Bone* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocostudio::Armature* ret = cocostudio::Armature::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Armature>(cx, (cocostudio::Armature*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_Armature_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_Armature_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::Armature* cobj = new (std::nothrow) cocostudio::Armature();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::Armature>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::Armature"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_studio_Armature_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::Armature *nobj = new (std::nothrow) cocostudio::Armature();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocostudio::Armature");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

    
void js_register_cocos2dx_studio_Armature(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_Armature_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_Armature_class->name = "Armature";
    jsb_cocostudio_Armature_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_Armature_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_Armature_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_Armature_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_Armature_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_Armature_class->resolve = JS_ResolveStub;
    jsb_cocostudio_Armature_class->convert = JS_ConvertStub;
    jsb_cocostudio_Armature_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBone", js_cocos2dx_studio_Armature_getBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeBoneParent", js_cocos2dx_studio_Armature_changeBoneParent, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimation", js_cocos2dx_studio_Armature_setAnimation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneAtPoint", js_cocos2dx_studio_Armature_getBoneAtPoint, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureTransformDirty", js_cocos2dx_studio_Armature_getArmatureTransformDirty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVersion", js_cocos2dx_studio_Armature_setVersion, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateOffsetPoint", js_cocos2dx_studio_Armature_updateOffsetPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParentBone", js_cocos2dx_studio_Armature_getParentBone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeBone", js_cocos2dx_studio_Armature_removeBone, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBatchNode", js_cocos2dx_studio_Armature_getBatchNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_Armature_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setParentBone", js_cocos2dx_studio_Armature_setParentBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBatchNode", js_cocos2dx_studio_Armature_setBatchNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_studio_Armature_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setArmatureData", js_cocos2dx_studio_Armature_setArmatureData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addBone", js_cocos2dx_studio_Armature_addBone, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArmatureData", js_cocos2dx_studio_Armature_getArmatureData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("boundingBox", js_cocos2dx_studio_Armature_getBoundingBox, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVersion", js_cocos2dx_studio_Armature_getVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimation", js_cocos2dx_studio_Armature_getAnimation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOffsetPoints", js_cocos2dx_studio_Armature_getOffsetPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_studio_Armature_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneDic", js_cocos2dx_studio_Armature_getBoneDic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_studio_Armature_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_Armature_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocostudio_Armature_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_Armature_class,
        js_cocos2dx_studio_Armature_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_Armature_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Armature"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::Armature>(cx, jsb_cocostudio_Armature_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { ccs.Armature.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_Skin_class;
JSObject *jsb_cocostudio_Skin_prototype;

bool js_cocos2dx_studio_Skin_getBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Skin* cobj = (cocostudio::Skin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Skin_getBone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::Bone* ret = cobj->getBone();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Bone>(cx, (cocostudio::Bone*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Skin_getBone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Skin_getNodeToWorldTransformAR(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Skin* cobj = (cocostudio::Skin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Skin_getNodeToWorldTransformAR : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mat4 ret = cobj->getNodeToWorldTransformAR();
        JS::RootedValue jsret(cx);
        jsret = matrix_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Skin_getNodeToWorldTransformAR : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Skin_getDisplayName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Skin* cobj = (cocostudio::Skin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Skin_getDisplayName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getDisplayName();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Skin_getDisplayName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Skin_updateArmatureTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Skin* cobj = (cocostudio::Skin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Skin_updateArmatureTransform : Invalid Native Object");
    if (argc == 0) {
        cobj->updateArmatureTransform();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Skin_updateArmatureTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Skin_setBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::Skin* cobj = (cocostudio::Skin *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Skin_setBone : Invalid Native Object");
    if (argc == 1) {
        cocostudio::Bone* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::Bone*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Skin_setBone : Error processing arguments");
        cobj->setBone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Skin_setBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Skin_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocostudio::Skin* ret = cocostudio::Skin::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Skin>(cx, (cocostudio::Skin*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::Skin* ret = cocostudio::Skin::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::Skin>(cx, (cocostudio::Skin*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_Skin_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_Skin_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Skin_createWithSpriteFrameName : Error processing arguments");

        auto ret = cocostudio::Skin::createWithSpriteFrameName(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::Skin>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::Skin"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_Skin_createWithSpriteFrameName : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_Skin_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::Skin* cobj = new (std::nothrow) cocostudio::Skin();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::Skin>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::Skin"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_register_cocos2dx_studio_Skin(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_Skin_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_Skin_class->name = "Skin";
    jsb_cocostudio_Skin_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_Skin_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_Skin_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_Skin_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_Skin_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_Skin_class->resolve = JS_ResolveStub;
    jsb_cocostudio_Skin_class->convert = JS_ConvertStub;
    jsb_cocostudio_Skin_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBone", js_cocos2dx_studio_Skin_getBone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNodeToWorldTransformAR", js_cocos2dx_studio_Skin_getNodeToWorldTransformAR, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDisplayName", js_cocos2dx_studio_Skin_getDisplayName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateArmatureTransform", js_cocos2dx_studio_Skin_updateArmatureTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBone", js_cocos2dx_studio_Skin_setBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_Skin_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrameName", js_cocos2dx_studio_Skin_createWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Sprite_prototype);
    jsb_cocostudio_Skin_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_Skin_class,
        js_cocos2dx_studio_Skin_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_Skin_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Skin"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::Skin>(cx, jsb_cocostudio_Skin_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_ComAttribute_class;
JSObject *jsb_cocostudio_ComAttribute_prototype;

bool js_cocos2dx_studio_ComAttribute_getFloat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getFloat : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getFloat : Error processing arguments");
        double ret = cobj->getFloat(arg0);
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        double arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getFloat : Error processing arguments");
        double ret = cobj->getFloat(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getFloat : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_getBool(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getBool : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getBool : Error processing arguments");
        bool ret = cobj->getBool(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getBool : Error processing arguments");
        bool ret = cobj->getBool(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getBool : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getString : Error processing arguments");
        std::string ret = cobj->getString(arg0);
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getString : Error processing arguments");
        std::string ret = cobj->getString(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setFloat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setFloat : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        double arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setFloat : Error processing arguments");
        cobj->setFloat(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setFloat : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setString : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setString : Error processing arguments");
        cobj->setString(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setString : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setInt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setInt : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        int arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setInt : Error processing arguments");
        cobj->setInt(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setInt : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_parse(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_parse : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_parse : Error processing arguments");
        bool ret = cobj->parse(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_parse : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_getInt(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_getInt : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getInt : Error processing arguments");
        int ret = cobj->getInt(arg0);
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        int arg1 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_getInt : Error processing arguments");
        int ret = cobj->getInt(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_getInt : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_setBool(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAttribute* cobj = (cocostudio::ComAttribute *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAttribute_setBool : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAttribute_setBool : Error processing arguments");
        cobj->setBool(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_setBool : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ComAttribute_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ComAttribute::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComAttribute>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::ComAttribute"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComAttribute_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComAttribute_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComAttribute* cobj = new (std::nothrow) cocostudio::ComAttribute();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComAttribute>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ComAttribute"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_register_cocos2dx_studio_ComAttribute(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComAttribute_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComAttribute_class->name = "ComAttribute";
    jsb_cocostudio_ComAttribute_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComAttribute_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComAttribute_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComAttribute_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComAttribute_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComAttribute_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComAttribute_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComAttribute_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getFloat", js_cocos2dx_studio_ComAttribute_getFloat, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBool", js_cocos2dx_studio_ComAttribute_getBool, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_studio_ComAttribute_getString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFloat", js_cocos2dx_studio_ComAttribute_setFloat, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_studio_ComAttribute_setString, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInt", js_cocos2dx_studio_ComAttribute_setInt, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("parse", js_cocos2dx_studio_ComAttribute_parse, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInt", js_cocos2dx_studio_ComAttribute_getInt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBool", js_cocos2dx_studio_ComAttribute_setBool, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComAttribute_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocostudio_ComAttribute_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_ComAttribute_class,
        js_cocos2dx_studio_ComAttribute_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ComAttribute_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ComAttribute"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ComAttribute>(cx, jsb_cocostudio_ComAttribute_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_ComAudio_class;
JSObject *jsb_cocostudio_ComAudio_prototype;

bool js_cocos2dx_studio_ComAudio_stopAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stopAllEffects : Invalid Native Object");
    if (argc == 0) {
        cobj->stopAllEffects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stopAllEffects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_getEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_getEffectsVolume : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getEffectsVolume();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_getEffectsVolume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_stopEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stopEffect : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_stopEffect : Error processing arguments");
        cobj->stopEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stopEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getBackgroundMusicVolume();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->willPlayBackgroundMusic();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume : Error processing arguments");
        cobj->setBackgroundMusicVolume(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_end(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_end : Invalid Native Object");
    if (argc == 0) {
        cobj->end();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_end : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_start(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_start : Invalid Native Object");
    if (argc == 0) {
        cobj->start();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_start : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_stopBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComAudio* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stopBackgroundMusic : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->stopBackgroundMusic();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            bool arg0;
            arg0 = JS::ToBoolean(args.get(0));
            cobj->stopBackgroundMusic(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stopBackgroundMusic : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComAudio_pauseBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_pauseBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        cobj->pauseBackgroundMusic();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_pauseBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBackgroundMusicPlaying();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_isLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_isLoop : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLoop();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_isLoop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_resumeAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_resumeAllEffects : Invalid Native Object");
    if (argc == 0) {
        cobj->resumeAllEffects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_resumeAllEffects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_pauseAllEffects(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_pauseAllEffects : Invalid Native Object");
    if (argc == 0) {
        cobj->pauseAllEffects();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_pauseAllEffects : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_preloadBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_preloadBackgroundMusic : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_preloadBackgroundMusic : Error processing arguments");
        cobj->preloadBackgroundMusic(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_preloadBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_playBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComAudio* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_playBackgroundMusic : Invalid Native Object");
    do {
        if (argc == 1) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            cobj->playBackgroundMusic(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->playBackgroundMusic(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->playBackgroundMusic();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_playBackgroundMusic : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComAudio_stop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_stop : Invalid Native Object");
    if (argc == 0) {
        cobj->stop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_stop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_playEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComAudio* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_playEffect : Invalid Native Object");
    do {
        if (argc == 1) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            unsigned int ret = cobj->playEffect(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = uint32_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            unsigned int ret = cobj->playEffect(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = uint32_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            unsigned int ret = cobj->playEffect();
            jsval jsret = JSVAL_NULL;
            jsret = uint32_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_playEffect : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComAudio_preloadEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_preloadEffect : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_preloadEffect : Error processing arguments");
        cobj->preloadEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_preloadEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setLoop : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setLoop : Error processing arguments");
        cobj->setLoop(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setLoop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_unloadEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_unloadEffect : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_unloadEffect : Error processing arguments");
        cobj->unloadEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_unloadEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_rewindBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_rewindBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        cobj->rewindBackgroundMusic();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_rewindBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_pauseEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_pauseEffect : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_pauseEffect : Error processing arguments");
        cobj->pauseEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_pauseEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_resumeBackgroundMusic(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_resumeBackgroundMusic : Invalid Native Object");
    if (argc == 0) {
        cobj->resumeBackgroundMusic();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_resumeBackgroundMusic : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setFile : Invalid Native Object");
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setFile : Error processing arguments");
        cobj->setFile(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_setEffectsVolume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_setEffectsVolume : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_setEffectsVolume : Error processing arguments");
        cobj->setEffectsVolume(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_setEffectsVolume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_getFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_getFile : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getFile();
        JS::RootedValue jsret(cx);
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_getFile : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComAudio_resumeEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComAudio* cobj = (cocostudio::ComAudio *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComAudio_resumeEffect : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComAudio_resumeEffect : Error processing arguments");
        cobj->resumeEffect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_resumeEffect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComAudio_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ComAudio::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComAudio>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::ComAudio"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComAudio_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComAudio_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComAudio* cobj = new (std::nothrow) cocostudio::ComAudio();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComAudio>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ComAudio"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_register_cocos2dx_studio_ComAudio(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComAudio_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComAudio_class->name = "ComAudio";
    jsb_cocostudio_ComAudio_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComAudio_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComAudio_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComAudio_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComAudio_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComAudio_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComAudio_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComAudio_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("stopAllEffects", js_cocos2dx_studio_ComAudio_stopAllEffects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEffectsVolume", js_cocos2dx_studio_ComAudio_getEffectsVolume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopEffect", js_cocos2dx_studio_ComAudio_stopEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackgroundMusicVolume", js_cocos2dx_studio_ComAudio_getBackgroundMusicVolume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("willPlayBackgroundMusic", js_cocos2dx_studio_ComAudio_willPlayBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundMusicVolume", js_cocos2dx_studio_ComAudio_setBackgroundMusicVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("end", js_cocos2dx_studio_ComAudio_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("start", js_cocos2dx_studio_ComAudio_start, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopBackgroundMusic", js_cocos2dx_studio_ComAudio_stopBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseBackgroundMusic", js_cocos2dx_studio_ComAudio_pauseBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBackgroundMusicPlaying", js_cocos2dx_studio_ComAudio_isBackgroundMusicPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoop", js_cocos2dx_studio_ComAudio_isLoop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeAllEffects", js_cocos2dx_studio_ComAudio_resumeAllEffects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseAllEffects", js_cocos2dx_studio_ComAudio_pauseAllEffects, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("preloadBackgroundMusic", js_cocos2dx_studio_ComAudio_preloadBackgroundMusic, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playBackgroundMusic", js_cocos2dx_studio_ComAudio_playBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stop", js_cocos2dx_studio_ComAudio_stop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("playEffect", js_cocos2dx_studio_ComAudio_playEffect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("preloadEffect", js_cocos2dx_studio_ComAudio_preloadEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_cocos2dx_studio_ComAudio_setLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadEffect", js_cocos2dx_studio_ComAudio_unloadEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("rewindBackgroundMusic", js_cocos2dx_studio_ComAudio_rewindBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseEffect", js_cocos2dx_studio_ComAudio_pauseEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeBackgroundMusic", js_cocos2dx_studio_ComAudio_resumeBackgroundMusic, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFile", js_cocos2dx_studio_ComAudio_setFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEffectsVolume", js_cocos2dx_studio_ComAudio_setEffectsVolume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFile", js_cocos2dx_studio_ComAudio_getFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resumeEffect", js_cocos2dx_studio_ComAudio_resumeEffect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComAudio_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocostudio_ComAudio_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_ComAudio_class,
        js_cocos2dx_studio_ComAudio_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ComAudio_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ComAudio"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ComAudio>(cx, jsb_cocostudio_ComAudio_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_InputDelegate_class;
JSObject *jsb_cocostudio_InputDelegate_prototype;

bool js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isAccelerometerEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setKeypadEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setKeypadEnabled : Error processing arguments");
        cobj->setKeypadEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setKeypadEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_getTouchMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_getTouchMode : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTouchMode();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_getTouchMode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled : Error processing arguments");
        cobj->setAccelerometerEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_isKeypadEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_isKeypadEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isKeypadEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_isKeypadEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_isTouchEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouchEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_isTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setTouchPriority(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchPriority : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchPriority : Error processing arguments");
        cobj->setTouchPriority(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setTouchPriority : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_getTouchPriority(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_getTouchPriority : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getTouchPriority();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_getTouchPriority : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchEnabled : Error processing arguments");
        cobj->setTouchEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InputDelegate_setTouchMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::InputDelegate* cobj = (cocostudio::InputDelegate *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchMode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Touch::DispatchMode arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InputDelegate_setTouchMode : Error processing arguments");
        cobj->setTouchMode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InputDelegate_setTouchMode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

void js_register_cocos2dx_studio_InputDelegate(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_InputDelegate_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_InputDelegate_class->name = "InputDelegate";
    jsb_cocostudio_InputDelegate_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_InputDelegate_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_InputDelegate_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_InputDelegate_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_InputDelegate_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_InputDelegate_class->resolve = JS_ResolveStub;
    jsb_cocostudio_InputDelegate_class->convert = JS_ConvertStub;
    jsb_cocostudio_InputDelegate_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isAccelerometerEnabled", js_cocos2dx_studio_InputDelegate_isAccelerometerEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setKeypadEnabled", js_cocos2dx_studio_InputDelegate_setKeypadEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchMode", js_cocos2dx_studio_InputDelegate_getTouchMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAccelerometerEnabled", js_cocos2dx_studio_InputDelegate_setAccelerometerEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isKeypadEnabled", js_cocos2dx_studio_InputDelegate_isKeypadEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchEnabled", js_cocos2dx_studio_InputDelegate_isTouchEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchPriority", js_cocos2dx_studio_InputDelegate_setTouchPriority, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchPriority", js_cocos2dx_studio_InputDelegate_getTouchPriority, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchEnabled", js_cocos2dx_studio_InputDelegate_setTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchMode", js_cocos2dx_studio_InputDelegate_setTouchMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_InputDelegate_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_InputDelegate_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_InputDelegate_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "InputDelegate"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::InputDelegate>(cx, jsb_cocostudio_InputDelegate_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_ComController_class;
JSObject *jsb_cocostudio_ComController_prototype;

bool js_cocos2dx_studio_ComController_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ComController::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComController>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::ComController"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComController_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComController_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComController* cobj = new (std::nothrow) cocostudio::ComController();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComController>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ComController"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_studio_ComController_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::ComController *nobj = new (std::nothrow) cocostudio::ComController();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocostudio::ComController");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

    
void js_register_cocos2dx_studio_ComController(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComController_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComController_class->name = "ComController";
    jsb_cocostudio_ComController_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComController_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComController_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComController_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComController_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComController_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComController_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComController_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("ctor", js_cocos2dx_studio_ComController_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComController_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocostudio_ComController_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_ComController_class,
        js_cocos2dx_studio_ComController_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ComController_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ComController"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ComController>(cx, jsb_cocostudio_ComController_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { ccs.ComController.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_ComRender_class;
JSObject *jsb_cocostudio_ComRender_prototype;

bool js_cocos2dx_studio_ComRender_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComRender* cobj = (cocostudio::ComRender *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComRender_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComRender_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComRender_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComRender* cobj = (cocostudio::ComRender *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComRender_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComRender_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocostudio::ComRender* ret = cocostudio::ComRender::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ComRender>(cx, (cocostudio::ComRender*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::ComRender* ret = cocostudio::ComRender::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::ComRender>(cx, (cocostudio::ComRender*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ComRender_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::ComRender* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocostudio::ComRender(arg0, arg1);

            js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComRender>(cobj);
            JS::RootedObject proto(cx, typeClass->proto.ref());
            JS::RootedObject parent(cx, typeClass->parentProto.ref());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            jsb_ref_init(cx, &p->obj, cobj, "cocostudio::ComRender");
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj = new (std::nothrow) cocostudio::ComRender();

            js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComRender>(cobj);
            JS::RootedObject proto(cx, typeClass->proto.ref());
            JS::RootedObject parent(cx, typeClass->parentProto.ref());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            jsb_ref_init(cx, &p->obj, cobj, "cocostudio::ComRender");
        }
    } while(0);

    if (cobj) {
        if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
                ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);

        args.rval().set(OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComRender_constructor : wrong number of arguments");
    return false;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_register_cocos2dx_studio_ComRender(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComRender_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComRender_class->name = "ComRender";
    jsb_cocostudio_ComRender_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComRender_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComRender_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComRender_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComRender_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComRender_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComRender_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComRender_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setNode", js_cocos2dx_studio_ComRender_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_cocos2dx_studio_ComRender_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComRender_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocostudio_ComRender_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_ComRender_class,
        js_cocos2dx_studio_ComRender_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ComRender_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ComRender"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ComRender>(cx, jsb_cocostudio_ComRender_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_Frame_class;
JSObject *jsb_cocostudio_timeline_Frame_prototype;

bool js_cocos2dx_studio_Frame_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_clone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::Frame* ret = cobj->clone();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::Frame>(cx, (cocostudio::timeline::Frame*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_setTweenType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setTweenType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::tweenfunc::TweenType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setTweenType : Error processing arguments");
        cobj->setTweenType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setTweenType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_setTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Timeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Timeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setTimeline : Error processing arguments");
        cobj->setTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_isEnterWhenPassed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_isEnterWhenPassed : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnterWhenPassed();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_isEnterWhenPassed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_getTweenType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getTweenType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTweenType();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getTweenType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_getFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getFrameIndex : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getFrameIndex();
        JS::RootedValue jsret(cx);
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_apply(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_apply : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_apply : Error processing arguments");
        cobj->apply(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_apply : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_isTween(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_isTween : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTween();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_isTween : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_setFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setFrameIndex : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setFrameIndex : Error processing arguments");
        cobj->setFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_setTween(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_setTween : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setTween : Error processing arguments");
        cobj->setTween(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_setTween : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Frame_getTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getTimeline : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::Timeline* ret = cobj->getTimeline();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::Timeline>(cx, (cocostudio::timeline::Timeline*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getTimeline : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Frame_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Frame_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Frame_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_register_cocos2dx_studio_Frame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_Frame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_Frame_class->name = "Frame";
    jsb_cocostudio_timeline_Frame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Frame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_Frame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Frame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_Frame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_Frame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_Frame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_Frame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("clone", js_cocos2dx_studio_Frame_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTweenType", js_cocos2dx_studio_Frame_setTweenType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNode", js_cocos2dx_studio_Frame_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeline", js_cocos2dx_studio_Frame_setTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnterWhenPassed", js_cocos2dx_studio_Frame_isEnterWhenPassed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTweenType", js_cocos2dx_studio_Frame_getTweenType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrameIndex", js_cocos2dx_studio_Frame_getFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("apply", js_cocos2dx_studio_Frame_apply, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTween", js_cocos2dx_studio_Frame_isTween, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFrameIndex", js_cocos2dx_studio_Frame_setFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTween", js_cocos2dx_studio_Frame_setTween, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeline", js_cocos2dx_studio_Frame_getTimeline, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_cocos2dx_studio_Frame_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocostudio_timeline_Frame_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_timeline_Frame_class,
        dummy_constructor<cocostudio::timeline::Frame>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Frame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::Frame>(cx, jsb_cocostudio_timeline_Frame_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_timeline_VisibleFrame_class;
JSObject *jsb_cocostudio_timeline_VisibleFrame_prototype;

bool js_cocos2dx_studio_VisibleFrame_isVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::VisibleFrame* cobj = (cocostudio::timeline::VisibleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_VisibleFrame_isVisible : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isVisible();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_VisibleFrame_isVisible : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_VisibleFrame_setVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::VisibleFrame* cobj = (cocostudio::timeline::VisibleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_VisibleFrame_setVisible : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_VisibleFrame_setVisible : Error processing arguments");
        cobj->setVisible(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_VisibleFrame_setVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_VisibleFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::VisibleFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::VisibleFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::VisibleFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_VisibleFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_VisibleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::VisibleFrame* cobj = new (std::nothrow) cocostudio::timeline::VisibleFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::VisibleFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::VisibleFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_VisibleFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_VisibleFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_VisibleFrame_class->name = "VisibleFrame";
    jsb_cocostudio_timeline_VisibleFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_VisibleFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_VisibleFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_VisibleFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_VisibleFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isVisible", js_cocos2dx_studio_VisibleFrame_isVisible, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVisible", js_cocos2dx_studio_VisibleFrame_setVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_VisibleFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_VisibleFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_VisibleFrame_class,
        js_cocos2dx_studio_VisibleFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_VisibleFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "VisibleFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::VisibleFrame>(cx, jsb_cocostudio_timeline_VisibleFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_TextureFrame_class;
JSObject *jsb_cocostudio_timeline_TextureFrame_prototype;

bool js_cocos2dx_studio_TextureFrame_getTextureName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::TextureFrame* cobj = (cocostudio::timeline::TextureFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureFrame_getTextureName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getTextureName();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureFrame_getTextureName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_TextureFrame_setTextureName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::TextureFrame* cobj = (cocostudio::timeline::TextureFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_TextureFrame_setTextureName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_TextureFrame_setTextureName : Error processing arguments");
        cobj->setTextureName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_TextureFrame_setTextureName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_TextureFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::TextureFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::TextureFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::TextureFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_TextureFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_TextureFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::TextureFrame* cobj = new (std::nothrow) cocostudio::timeline::TextureFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::TextureFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::TextureFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_TextureFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_TextureFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_TextureFrame_class->name = "TextureFrame";
    jsb_cocostudio_timeline_TextureFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_TextureFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_TextureFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_TextureFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_TextureFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getTextureName", js_cocos2dx_studio_TextureFrame_getTextureName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextureName", js_cocos2dx_studio_TextureFrame_setTextureName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_TextureFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_TextureFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_TextureFrame_class,
        js_cocos2dx_studio_TextureFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_TextureFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "TextureFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::TextureFrame>(cx, jsb_cocostudio_timeline_TextureFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_RotationFrame_class;
JSObject *jsb_cocostudio_timeline_RotationFrame_prototype;

bool js_cocos2dx_studio_RotationFrame_setRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::RotationFrame* cobj = (cocostudio::timeline::RotationFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_RotationFrame_setRotation : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_RotationFrame_setRotation : Error processing arguments");
        cobj->setRotation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_RotationFrame_setRotation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_RotationFrame_getRotation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::RotationFrame* cobj = (cocostudio::timeline::RotationFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_RotationFrame_getRotation : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRotation();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_RotationFrame_getRotation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_RotationFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::RotationFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::RotationFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::RotationFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_RotationFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_RotationFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::RotationFrame* cobj = new (std::nothrow) cocostudio::timeline::RotationFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::RotationFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::RotationFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_RotationFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_RotationFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_RotationFrame_class->name = "RotationFrame";
    jsb_cocostudio_timeline_RotationFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_RotationFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_RotationFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_RotationFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_RotationFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setRotation", js_cocos2dx_studio_RotationFrame_setRotation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRotation", js_cocos2dx_studio_RotationFrame_getRotation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_RotationFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_RotationFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_RotationFrame_class,
        js_cocos2dx_studio_RotationFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_RotationFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "RotationFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::RotationFrame>(cx, jsb_cocostudio_timeline_RotationFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_SkewFrame_class;
JSObject *jsb_cocostudio_timeline_SkewFrame_prototype;

bool js_cocos2dx_studio_SkewFrame_getSkewY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_getSkewY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSkewY();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_getSkewY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_setSkewX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewX : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewX : Error processing arguments");
        cobj->setSkewX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_setSkewX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_setSkewY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewY : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkewFrame_setSkewY : Error processing arguments");
        cobj->setSkewY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_setSkewY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_getSkewX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkewFrame* cobj = (cocostudio::timeline::SkewFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkewFrame_getSkewX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSkewX();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_getSkewX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_SkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::SkewFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::SkewFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::SkewFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_SkewFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_SkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::SkewFrame* cobj = new (std::nothrow) cocostudio::timeline::SkewFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::SkewFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::SkewFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_SkewFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_SkewFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_SkewFrame_class->name = "SkewFrame";
    jsb_cocostudio_timeline_SkewFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_SkewFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_SkewFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_SkewFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_SkewFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getSkewY", js_cocos2dx_studio_SkewFrame_getSkewY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkewX", js_cocos2dx_studio_SkewFrame_setSkewX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkewY", js_cocos2dx_studio_SkewFrame_setSkewY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSkewX", js_cocos2dx_studio_SkewFrame_getSkewX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_SkewFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_SkewFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_SkewFrame_class,
        js_cocos2dx_studio_SkewFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_SkewFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SkewFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::SkewFrame>(cx, jsb_cocostudio_timeline_SkewFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_RotationSkewFrame_class;
JSObject *jsb_cocostudio_timeline_RotationSkewFrame_prototype;

bool js_cocos2dx_studio_RotationSkewFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::RotationSkewFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::RotationSkewFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::RotationSkewFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_RotationSkewFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_RotationSkewFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::RotationSkewFrame* cobj = new (std::nothrow) cocostudio::timeline::RotationSkewFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::RotationSkewFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::RotationSkewFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_SkewFrame_prototype;

void js_register_cocos2dx_studio_RotationSkewFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_RotationSkewFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_RotationSkewFrame_class->name = "RotationSkewFrame";
    jsb_cocostudio_timeline_RotationSkewFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_RotationSkewFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_RotationSkewFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_SkewFrame_prototype);
    jsb_cocostudio_timeline_RotationSkewFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_RotationSkewFrame_class,
        js_cocos2dx_studio_RotationSkewFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_RotationSkewFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "RotationSkewFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::RotationSkewFrame>(cx, jsb_cocostudio_timeline_RotationSkewFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_PositionFrame_class;
JSObject *jsb_cocostudio_timeline_PositionFrame_prototype;

bool js_cocos2dx_studio_PositionFrame_getX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_getX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getX();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_getX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_getY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_getY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getY();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_getY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_setPosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_PositionFrame_setPosition : Error processing arguments");
        cobj->setPosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_setPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_setX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_setX : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_PositionFrame_setX : Error processing arguments");
        cobj->setX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_setX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_setY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_setY : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_PositionFrame_setY : Error processing arguments");
        cobj->setY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_setY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_getPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::PositionFrame* cobj = (cocostudio::timeline::PositionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_PositionFrame_getPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getPosition();
        JS::RootedValue jsret(cx);
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_getPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_PositionFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::PositionFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::PositionFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::PositionFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_PositionFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_PositionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::PositionFrame* cobj = new (std::nothrow) cocostudio::timeline::PositionFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::PositionFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::PositionFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_PositionFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_PositionFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_PositionFrame_class->name = "PositionFrame";
    jsb_cocostudio_timeline_PositionFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_PositionFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_PositionFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_PositionFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_PositionFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getX", js_cocos2dx_studio_PositionFrame_getX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getY", js_cocos2dx_studio_PositionFrame_getY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPosition", js_cocos2dx_studio_PositionFrame_setPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setX", js_cocos2dx_studio_PositionFrame_setX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setY", js_cocos2dx_studio_PositionFrame_setY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPosition", js_cocos2dx_studio_PositionFrame_getPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_PositionFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_PositionFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_PositionFrame_class,
        js_cocos2dx_studio_PositionFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_PositionFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "PositionFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::PositionFrame>(cx, jsb_cocostudio_timeline_PositionFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_ScaleFrame_class;
JSObject *jsb_cocostudio_timeline_ScaleFrame_prototype;

bool js_cocos2dx_studio_ScaleFrame_setScaleY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleY : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleY : Error processing arguments");
        cobj->setScaleY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_setScaleY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_setScaleX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleX : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ScaleFrame_setScaleX : Error processing arguments");
        cobj->setScaleX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_setScaleX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_getScaleY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_getScaleY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getScaleY();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_getScaleY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_getScaleX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_getScaleX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getScaleX();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_getScaleX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_setScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ScaleFrame* cobj = (cocostudio::timeline::ScaleFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ScaleFrame_setScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ScaleFrame_setScale : Error processing arguments");
        cobj->setScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_setScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ScaleFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::ScaleFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ScaleFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::ScaleFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ScaleFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ScaleFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ScaleFrame* cobj = new (std::nothrow) cocostudio::timeline::ScaleFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ScaleFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::ScaleFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_ScaleFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ScaleFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ScaleFrame_class->name = "ScaleFrame";
    jsb_cocostudio_timeline_ScaleFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ScaleFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ScaleFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ScaleFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ScaleFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setScaleY", js_cocos2dx_studio_ScaleFrame_setScaleY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScaleX", js_cocos2dx_studio_ScaleFrame_setScaleX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getScaleY", js_cocos2dx_studio_ScaleFrame_getScaleY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getScaleX", js_cocos2dx_studio_ScaleFrame_getScaleX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale", js_cocos2dx_studio_ScaleFrame_setScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ScaleFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_ScaleFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_ScaleFrame_class,
        js_cocos2dx_studio_ScaleFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_ScaleFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ScaleFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::ScaleFrame>(cx, jsb_cocostudio_timeline_ScaleFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_AnchorPointFrame_class;
JSObject *jsb_cocostudio_timeline_AnchorPointFrame_prototype;

bool js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AnchorPointFrame* cobj = (cocostudio::timeline::AnchorPointFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint : Error processing arguments");
        cobj->setAnchorPoint(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AnchorPointFrame* cobj = (cocostudio::timeline::AnchorPointFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Point ret = cobj->getAnchorPoint();
        JS::RootedValue jsret(cx);
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_AnchorPointFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::AnchorPointFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::AnchorPointFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::AnchorPointFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_AnchorPointFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_AnchorPointFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::AnchorPointFrame* cobj = new (std::nothrow) cocostudio::timeline::AnchorPointFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::AnchorPointFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::AnchorPointFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_AnchorPointFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_AnchorPointFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_AnchorPointFrame_class->name = "AnchorPointFrame";
    jsb_cocostudio_timeline_AnchorPointFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_AnchorPointFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setAnchorPoint", js_cocos2dx_studio_AnchorPointFrame_setAnchorPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorPoint", js_cocos2dx_studio_AnchorPointFrame_getAnchorPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_AnchorPointFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_AnchorPointFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_AnchorPointFrame_class,
        js_cocos2dx_studio_AnchorPointFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_AnchorPointFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "AnchorPointFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::AnchorPointFrame>(cx, jsb_cocostudio_timeline_AnchorPointFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_InnerActionFrame_class;
JSObject *jsb_cocostudio_timeline_InnerActionFrame_prototype;

bool js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getEndFrameIndex();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getStartFrameIndex();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_getInnerActionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getInnerActionType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getInnerActionType();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getInnerActionType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex : Error processing arguments");
        cobj->setEndFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setEnterWithName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEnterWithName : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setEnterWithName : Error processing arguments");
        cobj->setEnterWithName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setEnterWithName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex : Error processing arguments");
        cobj->setSingleFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex : Error processing arguments");
        cobj->setStartFrameIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getSingleFrameIndex();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setInnerActionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setInnerActionType : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::InnerActionType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setInnerActionType : Error processing arguments");
        cobj->setInnerActionType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setInnerActionType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_setAnimationName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::InnerActionFrame* cobj = (cocostudio::timeline::InnerActionFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_InnerActionFrame_setAnimationName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_InnerActionFrame_setAnimationName : Error processing arguments");
        cobj->setAnimationName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_setAnimationName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_InnerActionFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::InnerActionFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::InnerActionFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::InnerActionFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_InnerActionFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_InnerActionFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::InnerActionFrame* cobj = new (std::nothrow) cocostudio::timeline::InnerActionFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::InnerActionFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::InnerActionFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_InnerActionFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_InnerActionFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_InnerActionFrame_class->name = "InnerActionFrame";
    jsb_cocostudio_timeline_InnerActionFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_InnerActionFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getEndFrameIndex", js_cocos2dx_studio_InnerActionFrame_getEndFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartFrameIndex", js_cocos2dx_studio_InnerActionFrame_getStartFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInnerActionType", js_cocos2dx_studio_InnerActionFrame_getInnerActionType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndFrameIndex", js_cocos2dx_studio_InnerActionFrame_setEndFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEnterWithName", js_cocos2dx_studio_InnerActionFrame_setEnterWithName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSingleFrameIndex", js_cocos2dx_studio_InnerActionFrame_setSingleFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStartFrameIndex", js_cocos2dx_studio_InnerActionFrame_setStartFrameIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSingleFrameIndex", js_cocos2dx_studio_InnerActionFrame_getSingleFrameIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInnerActionType", js_cocos2dx_studio_InnerActionFrame_setInnerActionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimationName", js_cocos2dx_studio_InnerActionFrame_setAnimationName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_InnerActionFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_InnerActionFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_InnerActionFrame_class,
        js_cocos2dx_studio_InnerActionFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_InnerActionFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "InnerActionFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::InnerActionFrame>(cx, jsb_cocostudio_timeline_InnerActionFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_ColorFrame_class;
JSObject *jsb_cocostudio_timeline_ColorFrame_prototype;

bool js_cocos2dx_studio_ColorFrame_getColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ColorFrame* cobj = (cocostudio::timeline::ColorFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColorFrame_getColor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Color3B ret = cobj->getColor();
        JS::RootedValue jsret(cx);
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColorFrame_getColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ColorFrame_setColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ColorFrame* cobj = (cocostudio::timeline::ColorFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ColorFrame_setColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color3B arg0;
        ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ColorFrame_setColor : Error processing arguments");
        cobj->setColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ColorFrame_setColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ColorFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::ColorFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ColorFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::ColorFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ColorFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ColorFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ColorFrame* cobj = new (std::nothrow) cocostudio::timeline::ColorFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ColorFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::ColorFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_ColorFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ColorFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ColorFrame_class->name = "ColorFrame";
    jsb_cocostudio_timeline_ColorFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ColorFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ColorFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ColorFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ColorFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getColor", js_cocos2dx_studio_ColorFrame_getColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setColor", js_cocos2dx_studio_ColorFrame_setColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ColorFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_ColorFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_ColorFrame_class,
        js_cocos2dx_studio_ColorFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_ColorFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ColorFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::ColorFrame>(cx, jsb_cocostudio_timeline_ColorFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_AlphaFrame_class;
JSObject *jsb_cocostudio_timeline_AlphaFrame_prototype;

bool js_cocos2dx_studio_AlphaFrame_getAlpha(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AlphaFrame* cobj = (cocostudio::timeline::AlphaFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AlphaFrame_getAlpha : Invalid Native Object");
    if (argc == 0) {
        uint16_t ret = cobj->getAlpha();
        JS::RootedValue jsret(cx);
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AlphaFrame_getAlpha : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_AlphaFrame_setAlpha(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::AlphaFrame* cobj = (cocostudio::timeline::AlphaFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_AlphaFrame_setAlpha : Invalid Native Object");
    if (argc == 1) {
        uint16_t arg0;
        ok &= jsval_to_uint16(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_AlphaFrame_setAlpha : Error processing arguments");
        cobj->setAlpha(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_AlphaFrame_setAlpha : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_AlphaFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::AlphaFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::AlphaFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::AlphaFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_AlphaFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_AlphaFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::AlphaFrame* cobj = new (std::nothrow) cocostudio::timeline::AlphaFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::AlphaFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::AlphaFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_AlphaFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_AlphaFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_AlphaFrame_class->name = "AlphaFrame";
    jsb_cocostudio_timeline_AlphaFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_AlphaFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_AlphaFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_AlphaFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_AlphaFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAlpha", js_cocos2dx_studio_AlphaFrame_getAlpha, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAlpha", js_cocos2dx_studio_AlphaFrame_setAlpha, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_AlphaFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_AlphaFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_AlphaFrame_class,
        js_cocos2dx_studio_AlphaFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_AlphaFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "AlphaFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::AlphaFrame>(cx, jsb_cocostudio_timeline_AlphaFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_EventFrame_class;
JSObject *jsb_cocostudio_timeline_EventFrame_prototype;

bool js_cocos2dx_studio_EventFrame_setEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::EventFrame* cobj = (cocostudio::timeline::EventFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_EventFrame_setEvent : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_EventFrame_setEvent : Error processing arguments");
        cobj->setEvent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_setEvent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_EventFrame_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::EventFrame* cobj = (cocostudio::timeline::EventFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_EventFrame_init : Invalid Native Object");
    if (argc == 0) {
        cobj->init();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_EventFrame_getEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::EventFrame* cobj = (cocostudio::timeline::EventFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_EventFrame_getEvent : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getEvent();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_getEvent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_EventFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::EventFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::EventFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::EventFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_EventFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_EventFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::EventFrame* cobj = new (std::nothrow) cocostudio::timeline::EventFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::EventFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::EventFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_EventFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_EventFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_EventFrame_class->name = "EventFrame";
    jsb_cocostudio_timeline_EventFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_EventFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_EventFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_EventFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_EventFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setEvent", js_cocos2dx_studio_EventFrame_setEvent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_EventFrame_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEvent", js_cocos2dx_studio_EventFrame_getEvent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_EventFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_EventFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_EventFrame_class,
        js_cocos2dx_studio_EventFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_EventFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "EventFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::EventFrame>(cx, jsb_cocostudio_timeline_EventFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_ZOrderFrame_class;
JSObject *jsb_cocostudio_timeline_ZOrderFrame_prototype;

bool js_cocos2dx_studio_ZOrderFrame_getZOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ZOrderFrame* cobj = (cocostudio::timeline::ZOrderFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ZOrderFrame_getZOrder : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getZOrder();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ZOrderFrame_getZOrder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ZOrderFrame_setZOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ZOrderFrame* cobj = (cocostudio::timeline::ZOrderFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ZOrderFrame_setZOrder : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ZOrderFrame_setZOrder : Error processing arguments");
        cobj->setZOrder(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ZOrderFrame_setZOrder : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ZOrderFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::ZOrderFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ZOrderFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::ZOrderFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ZOrderFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ZOrderFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ZOrderFrame* cobj = new (std::nothrow) cocostudio::timeline::ZOrderFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ZOrderFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::ZOrderFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_ZOrderFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ZOrderFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ZOrderFrame_class->name = "ZOrderFrame";
    jsb_cocostudio_timeline_ZOrderFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ZOrderFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getZOrder", js_cocos2dx_studio_ZOrderFrame_getZOrder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZOrder", js_cocos2dx_studio_ZOrderFrame_setZOrder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ZOrderFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_ZOrderFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_ZOrderFrame_class,
        js_cocos2dx_studio_ZOrderFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_ZOrderFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ZOrderFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::ZOrderFrame>(cx, jsb_cocostudio_timeline_ZOrderFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_BlendFuncFrame_class;
JSObject *jsb_cocostudio_timeline_BlendFuncFrame_prototype;

bool js_cocos2dx_studio_BlendFuncFrame_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BlendFuncFrame* cobj = (cocostudio::timeline::BlendFuncFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BlendFuncFrame_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        cocos2d::BlendFunc ret = cobj->getBlendFunc();
        JS::RootedValue jsret(cx);
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BlendFuncFrame_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BlendFuncFrame_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BlendFuncFrame* cobj = (cocostudio::timeline::BlendFuncFrame *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BlendFuncFrame_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BlendFuncFrame_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BlendFuncFrame_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BlendFuncFrame_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::BlendFuncFrame::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::BlendFuncFrame>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::BlendFuncFrame"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_BlendFuncFrame_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_BlendFuncFrame_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::BlendFuncFrame* cobj = new (std::nothrow) cocostudio::timeline::BlendFuncFrame();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::BlendFuncFrame>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::BlendFuncFrame"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocostudio_timeline_Frame_prototype;

void js_register_cocos2dx_studio_BlendFuncFrame(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_BlendFuncFrame_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_BlendFuncFrame_class->name = "BlendFuncFrame";
    jsb_cocostudio_timeline_BlendFuncFrame_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_BlendFuncFrame_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBlendFunc", js_cocos2dx_studio_BlendFuncFrame_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_studio_BlendFuncFrame_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_BlendFuncFrame_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_Frame_prototype);
    jsb_cocostudio_timeline_BlendFuncFrame_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_BlendFuncFrame_class,
        js_cocos2dx_studio_BlendFuncFrame_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_BlendFuncFrame_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "BlendFuncFrame"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::BlendFuncFrame>(cx, jsb_cocostudio_timeline_BlendFuncFrame_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_Timeline_class;
JSObject *jsb_cocostudio_timeline_Timeline_prototype;

bool js_cocos2dx_studio_Timeline_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_clone : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::Timeline* ret = cobj->clone();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::Timeline>(cx, (cocostudio::timeline::Timeline*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_gotoFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_gotoFrame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_gotoFrame : Error processing arguments");
        cobj->gotoFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_gotoFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_setNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_setNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_setNode : Error processing arguments");
        cobj->setNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_setNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_getActionTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getActionTimeline : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::ActionTimeline* ret = cobj->getActionTimeline();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::ActionTimeline>(cx, (cocostudio::timeline::ActionTimeline*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getActionTimeline : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_insertFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_insertFrame : Invalid Native Object");
    if (argc == 2) {
        cocostudio::timeline::Frame* arg0 = nullptr;
        int arg1 = 0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Frame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_insertFrame : Error processing arguments");
        cobj->insertFrame(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_insertFrame : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_Timeline_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_addFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_addFrame : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Frame* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Frame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_addFrame : Error processing arguments");
        cobj->addFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_addFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_getFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getFrames : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocostudio::timeline::Frame *>& ret = cobj->getFrames();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getFrames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getActionTag : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getActionTag();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_getNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_getNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_getNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_Timeline_removeFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_removeFrame : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Frame* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Frame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_removeFrame : Error processing arguments");
        cobj->removeFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_removeFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_setActionTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_setActionTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::ActionTimeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::ActionTimeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_setActionTimeline : Error processing arguments");
        cobj->setActionTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_setActionTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_stepToFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Timeline* cobj = (cocostudio::timeline::Timeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_Timeline_stepToFrame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Timeline_stepToFrame : Error processing arguments");
        cobj->stepToFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_stepToFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_Timeline_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::Timeline::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::Timeline>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::Timeline"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_Timeline_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_Timeline_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::Timeline* cobj = new (std::nothrow) cocostudio::timeline::Timeline();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::Timeline>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::Timeline"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_Timeline(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_Timeline_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_Timeline_class->name = "Timeline";
    jsb_cocostudio_timeline_Timeline_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Timeline_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_Timeline_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_Timeline_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_Timeline_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_Timeline_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_Timeline_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_Timeline_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("clone", js_cocos2dx_studio_Timeline_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoFrame", js_cocos2dx_studio_Timeline_gotoFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setNode", js_cocos2dx_studio_Timeline_setNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTimeline", js_cocos2dx_studio_Timeline_getActionTimeline, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertFrame", js_cocos2dx_studio_Timeline_insertFrame, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActionTag", js_cocos2dx_studio_Timeline_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addFrame", js_cocos2dx_studio_Timeline_addFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFrames", js_cocos2dx_studio_Timeline_getFrames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_studio_Timeline_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNode", js_cocos2dx_studio_Timeline_getNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFrame", js_cocos2dx_studio_Timeline_removeFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActionTimeline", js_cocos2dx_studio_Timeline_setActionTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stepToFrame", js_cocos2dx_studio_Timeline_stepToFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_Timeline_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_Timeline_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_timeline_Timeline_class,
        js_cocos2dx_studio_Timeline_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_Timeline_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Timeline"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::Timeline>(cx, jsb_cocostudio_timeline_Timeline_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_timeline_ActionTimelineData_class;
JSObject *jsb_cocostudio_timeline_ActionTimelineData_prototype;

bool js_cocos2dx_studio_ActionTimelineData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimelineData* cobj = (cocostudio::timeline::ActionTimelineData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimelineData_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimelineData_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimelineData_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimelineData* cobj = (cocostudio::timeline::ActionTimelineData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimelineData_init : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimelineData_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimelineData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimelineData* cobj = (cocostudio::timeline::ActionTimelineData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimelineData_getActionTag : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getActionTag();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimelineData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimelineData_create : Error processing arguments");

        auto ret = cocostudio::timeline::ActionTimelineData::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ActionTimelineData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::ActionTimelineData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimelineData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ActionTimelineData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ActionTimelineData* cobj = new (std::nothrow) cocostudio::timeline::ActionTimelineData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ActionTimelineData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::ActionTimelineData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_studio_ActionTimelineData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ActionTimelineData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ActionTimelineData_class->name = "ActionTimelineData";
    jsb_cocostudio_timeline_ActionTimelineData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ActionTimelineData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setActionTag", js_cocos2dx_studio_ActionTimelineData_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ActionTimelineData_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_studio_ActionTimelineData_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ActionTimelineData_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocostudio_timeline_ActionTimelineData_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocostudio_timeline_ActionTimelineData_class,
        js_cocos2dx_studio_ActionTimelineData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_ActionTimelineData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ActionTimelineData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::ActionTimelineData>(cx, jsb_cocostudio_timeline_ActionTimelineData_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocostudio_timeline_ActionTimeline_class;
JSObject *jsb_cocostudio_timeline_ActionTimeline_prototype;

bool js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc : Invalid Native Object");
    if (argc == 1) {
        std::function<void (cocostudio::timeline::Frame *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0), args.thisv()));
		        auto lambda = [=](cocostudio::timeline::Frame* larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            if (larg0) {
		            largv[0] = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::Frame>(cx, (cocostudio::timeline::Frame*)larg0));
		        } else {
		            largv[0] = JSVAL_NULL;
		        };
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc : Error processing arguments");
        cobj->setFrameEventCallFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs : Invalid Native Object");
    if (argc == 0) {
        cobj->clearFrameEndCallFuncs();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::function<void ()> arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        do {
		    if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1), args.thisv()));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc : Error processing arguments");
        cobj->setAnimationEndCallFunc(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_addTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_addTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Timeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Timeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_addTimeline : Error processing arguments");
        cobj->addTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_addTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getCurrentFrame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCurrentFrame();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getCurrentFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getStartFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getStartFrame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getStartFrame();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getStartFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_pause : Invalid Native Object");
    if (argc == 0) {
        cobj->pause();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_start(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_start : Invalid Native Object");
    if (argc == 0) {
        cobj->start();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_start : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeTimeline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeTimeline : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::Timeline* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocostudio::timeline::Timeline*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeTimeline : Error processing arguments");
        cobj->removeTimeline(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeTimeline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc : Invalid Native Object");
    if (argc == 1) {
        std::function<void ()> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0), args.thisv()));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc : Error processing arguments");
        cobj->setLastFrameCallFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists : Error processing arguments");
        bool ret = cobj->IsAnimationInfoExists(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getTimelines(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getTimelines : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocostudio::timeline::Timeline *>& ret = cobj->getTimelines();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getTimelines : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_play : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        bool arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_play : Error processing arguments");
        cobj->play(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_play : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getAnimationInfo : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_getAnimationInfo : Error processing arguments");
        const cocostudio::timeline::AnimationInfo& ret = cobj->getAnimationInfo(arg0);
        JS::RootedValue jsret(cx);
        jsret = animationInfo_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getAnimationInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_resume : Invalid Native Object");
    if (argc == 0) {
        cobj->resume();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_resume : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc : Invalid Native Object");
    if (argc == 3) {
        int arg0 = 0;
        std::string arg1;
        std::function<void ()> arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        do {
		    if(JS_TypeOfValue(cx, args.get(2)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(2), args.thisv()));
		        auto lambda = [=]() -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(0, nullptr, &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg2 = lambda;
		    }
		    else
		    {
		        arg2 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc : Error processing arguments");
        cobj->addFrameEndCallFunc(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeAnimationInfo : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeAnimationInfo : Error processing arguments");
        cobj->removeAnimationInfo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeAnimationInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getTimeSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTimeSpeed();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getTimeSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_addAnimationInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_addAnimationInfo : Invalid Native Object");
    if (argc == 1) {
        cocostudio::timeline::AnimationInfo arg0;
        ok &= jsval_to_animationInfo(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_addAnimationInfo : Error processing arguments");
        cobj->addAnimationInfo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_addAnimationInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getDuration : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getDuration();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getDuration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause : Error processing arguments");
        cobj->gotoFrameAndPause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_isPlaying(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_isPlaying : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPlaying();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_isPlaying : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs : Error processing arguments");
        cobj->removeFrameEndCallFuncs(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::ActionTimeline* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay : Invalid Native Object");
    do {
        if (argc == 2) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->gotoFrameAndPlay(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj->gotoFrameAndPlay(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cobj->gotoFrameAndPlay(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 4) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            int arg2 = 0;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            bool arg3;
            arg3 = JS::ToBoolean(args.get(3));
            cobj->gotoFrameAndPlay(arg0, arg1, arg2, arg3);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc : Invalid Native Object");
    if (argc == 0) {
        cobj->clearFrameEventCallFunc();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_getEndFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_getEndFrame : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getEndFrame();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_getEndFrame : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setTimeSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setTimeSpeed : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setTimeSpeed : Error processing arguments");
        cobj->setTimeSpeed(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setTimeSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc : Invalid Native Object");
    if (argc == 0) {
        cobj->clearLastFrameCallFunc();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setDuration : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setDuration : Error processing arguments");
        cobj->setDuration(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setDuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_setCurrentFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_setCurrentFrame : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_setCurrentFrame : Error processing arguments");
        cobj->setCurrentFrame(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_setCurrentFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::ActionTimeline* cobj = (cocostudio::timeline::ActionTimeline *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        std::string arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc : Error processing arguments");
        cobj->removeFrameEndCallFunc(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_ActionTimeline_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::ActionTimeline::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ActionTimeline>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::ActionTimeline"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ActionTimeline_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ActionTimeline_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::ActionTimeline* cobj = new (std::nothrow) cocostudio::timeline::ActionTimeline();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::ActionTimeline>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::ActionTimeline"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Action_prototype;

void js_register_cocos2dx_studio_ActionTimeline(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_ActionTimeline_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_ActionTimeline_class->name = "ActionTimeline";
    jsb_cocostudio_timeline_ActionTimeline_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_ActionTimeline_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_ActionTimeline_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_ActionTimeline_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_ActionTimeline_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setFrameEventCallFunc", js_cocos2dx_studio_ActionTimeline_setFrameEventCallFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearFrameEndCallFuncs", js_cocos2dx_studio_ActionTimeline_clearFrameEndCallFuncs, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimationEndCallFunc", js_cocos2dx_studio_ActionTimeline_setAnimationEndCallFunc, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addTimeline", js_cocos2dx_studio_ActionTimeline_addTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentFrame", js_cocos2dx_studio_ActionTimeline_getCurrentFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartFrame", js_cocos2dx_studio_ActionTimeline_getStartFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_studio_ActionTimeline_pause, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("start", js_cocos2dx_studio_ActionTimeline_start, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_studio_ActionTimeline_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeTimeline", js_cocos2dx_studio_ActionTimeline_removeTimeline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLastFrameCallFunc", js_cocos2dx_studio_ActionTimeline_setLastFrameCallFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAnimationInfoExists", js_cocos2dx_studio_ActionTimeline_IsAnimationInfoExists, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimelines", js_cocos2dx_studio_ActionTimeline_getTimelines, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_cocos2dx_studio_ActionTimeline_play, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationInfo", js_cocos2dx_studio_ActionTimeline_getAnimationInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_cocos2dx_studio_ActionTimeline_resume, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addFrameEndCallFunc", js_cocos2dx_studio_ActionTimeline_addFrameEndCallFunc, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAnimationInfo", js_cocos2dx_studio_ActionTimeline_removeAnimationInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeSpeed", js_cocos2dx_studio_ActionTimeline_getTimeSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addAnimationInfo", js_cocos2dx_studio_ActionTimeline_addAnimationInfo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_cocos2dx_studio_ActionTimeline_getDuration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoFrameAndPause", js_cocos2dx_studio_ActionTimeline_gotoFrameAndPause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPlaying", js_cocos2dx_studio_ActionTimeline_isPlaying, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFrameEndCallFuncs", js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFuncs, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("gotoFrameAndPlay", js_cocos2dx_studio_ActionTimeline_gotoFrameAndPlay, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearFrameEventCallFunc", js_cocos2dx_studio_ActionTimeline_clearFrameEventCallFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEndFrame", js_cocos2dx_studio_ActionTimeline_getEndFrame, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTimeSpeed", js_cocos2dx_studio_ActionTimeline_setTimeSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearLastFrameCallFunc", js_cocos2dx_studio_ActionTimeline_clearLastFrameCallFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDuration", js_cocos2dx_studio_ActionTimeline_setDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCurrentFrame", js_cocos2dx_studio_ActionTimeline_setCurrentFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFrameEndCallFunc", js_cocos2dx_studio_ActionTimeline_removeFrameEndCallFunc, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ActionTimeline_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Action_prototype);
    jsb_cocostudio_timeline_ActionTimeline_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_ActionTimeline_class,
        js_cocos2dx_studio_ActionTimeline_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_ActionTimeline_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ActionTimeline"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::ActionTimeline>(cx, jsb_cocostudio_timeline_ActionTimeline_class, proto, parent_proto);
}

JSClass  *jsb_cocostudio_timeline_BoneNode_class;
JSObject *jsb_cocostudio_timeline_BoneNode_prototype;

bool js_cocos2dx_studio_BoneNode_getDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getDebugDrawWidth : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDebugDrawWidth();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getDebugDrawWidth : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getChildBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getChildBones : Invalid Native Object");
    do {
        if (argc == 0) {
            cocos2d::Vector<cocostudio::timeline::BoneNode *>& ret = cobj->getChildBones();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            const cocos2d::Vector<cocostudio::timeline::BoneNode *>& ret = cobj->getChildBones();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getChildBones : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        JS::RootedValue jsret(cx);
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getAllSubBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getAllSubBones : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocostudio::timeline::BoneNode *> ret = cobj->getAllSubBones();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getAllSubBones : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawEnabled : Error processing arguments");
        cobj->setDebugDrawEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getVisibleSkinsRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getVisibleSkinsRect : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getVisibleSkinsRect();
        JS::RootedValue jsret(cx);
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getVisibleSkinsRect : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getAllSubSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getAllSubSkins : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *> ret = cobj->getAllSubSkins();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getAllSubSkins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_displaySkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_displaySkin : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->displaySkin(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::timeline::SkinNode*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->displaySkin(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_displaySkin : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_isDebugDrawEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_isDebugDrawEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDebugDrawEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_isDebugDrawEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_addSkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_addSkin : Invalid Native Object");
    do {
        if (argc == 3) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::timeline::SkinNode*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cobj->addSkin(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Node* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocostudio::timeline::SkinNode*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->addSkin(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_addSkin : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_getRootSkeletonNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getRootSkeletonNode : Invalid Native Object");
    if (argc == 0) {
        cocostudio::timeline::SkeletonNode* ret = cobj->getRootSkeletonNode();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::SkeletonNode>(cx, (cocostudio::timeline::SkeletonNode*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getRootSkeletonNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawLength : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawLength : Error processing arguments");
        cobj->setDebugDrawLength(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawLength : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getSkins : Invalid Native Object");
    do {
        if (argc == 0) {
            cocos2d::Vector<cocos2d::Node *>& ret = cobj->getSkins();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::Node *>& ret = cobj->getSkins();
            jsval jsret = JSVAL_NULL;
            jsret = ccvector_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getSkins : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_getVisibleSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getVisibleSkins : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *> ret = cobj->getVisibleSkins();
        JS::RootedValue jsret(cx);
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getVisibleSkins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawWidth : Error processing arguments");
        cobj->setDebugDrawWidth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getDebugDrawLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getDebugDrawLength : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDebugDrawLength();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getDebugDrawLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_setDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4F arg0;
        ok &= jsval_to_cccolor4f(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_BoneNode_setDebugDrawColor : Error processing arguments");
        cobj->setDebugDrawColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_setDebugDrawColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_BoneNode_getDebugDrawColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::BoneNode* cobj = (cocostudio::timeline::BoneNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_BoneNode_getDebugDrawColor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Color4F ret = cobj->getDebugDrawColor();
        JS::RootedValue jsret(cx);
        jsret = cccolor4f_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_getDebugDrawColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_BoneNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            int arg0 = 0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cocostudio::timeline::BoneNode* ret = cocostudio::timeline::BoneNode::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::BoneNode>(cx, (cocostudio::timeline::BoneNode*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocostudio::timeline::BoneNode* ret = cocostudio::timeline::BoneNode::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::BoneNode>(cx, (cocostudio::timeline::BoneNode*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_studio_BoneNode_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_BoneNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::BoneNode* cobj = new (std::nothrow) cocostudio::timeline::BoneNode();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::BoneNode>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::BoneNode"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_studio_BoneNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::timeline::BoneNode *nobj = new (std::nothrow) cocostudio::timeline::BoneNode();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocostudio::timeline::BoneNode");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

    
void js_register_cocos2dx_studio_BoneNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_BoneNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_BoneNode_class->name = "BoneNode";
    jsb_cocostudio_timeline_BoneNode_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_BoneNode_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_BoneNode_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_BoneNode_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_BoneNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getDebugDrawWidth", js_cocos2dx_studio_BoneNode_getDebugDrawWidth, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChildBones", js_cocos2dx_studio_BoneNode_getChildBones, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_studio_BoneNode_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllSubBones", js_cocos2dx_studio_BoneNode_getAllSubBones, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_studio_BoneNode_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawEnabled", js_cocos2dx_studio_BoneNode_setDebugDrawEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVisibleSkinsRect", js_cocos2dx_studio_BoneNode_getVisibleSkinsRect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllSubSkins", js_cocos2dx_studio_BoneNode_getAllSubSkins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("displaySkin", js_cocos2dx_studio_BoneNode_displaySkin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDebugDrawEnabled", js_cocos2dx_studio_BoneNode_isDebugDrawEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addSkin", js_cocos2dx_studio_BoneNode_addSkin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRootSkeletonNode", js_cocos2dx_studio_BoneNode_getRootSkeletonNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawLength", js_cocos2dx_studio_BoneNode_setDebugDrawLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSkins", js_cocos2dx_studio_BoneNode_getSkins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVisibleSkins", js_cocos2dx_studio_BoneNode_getVisibleSkins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawWidth", js_cocos2dx_studio_BoneNode_setDebugDrawWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDebugDrawLength", js_cocos2dx_studio_BoneNode_getDebugDrawLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugDrawColor", js_cocos2dx_studio_BoneNode_setDebugDrawColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDebugDrawColor", js_cocos2dx_studio_BoneNode_getDebugDrawColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_studio_BoneNode_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_BoneNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocostudio_timeline_BoneNode_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_BoneNode_class,
        js_cocos2dx_studio_BoneNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_BoneNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "BoneNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::BoneNode>(cx, jsb_cocostudio_timeline_BoneNode_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { ccs.BoneNode.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_timeline_SkeletonNode_class;
JSObject *jsb_cocostudio_timeline_SkeletonNode_prototype;

bool js_cocos2dx_studio_SkeletonNode_getBoneNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkeletonNode* cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_getBoneNode : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkeletonNode_getBoneNode : Error processing arguments");
        cocostudio::timeline::BoneNode* ret = cobj->getBoneNode(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocostudio::timeline::BoneNode>(cx, (cocostudio::timeline::BoneNode*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_getBoneNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_changeSkins(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocostudio::timeline::SkeletonNode* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_changeSkins : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->changeSkins(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::map<std::string, std::string> arg0;
            ok &= jsval_to_std_map_string_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->changeSkins(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_changeSkins : wrong number of arguments");
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_addSkinGroup(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkeletonNode* cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_addSkinGroup : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::map<std::string, std::string> arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_map_string_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_SkeletonNode_addSkinGroup : Error processing arguments");
        cobj->addSkinGroup(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_addSkinGroup : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::SkeletonNode* cobj = (cocostudio::timeline::SkeletonNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Map<std::string, cocostudio::timeline::BoneNode *>& ret = cobj->getAllSubBonesMap();
        JS::RootedValue jsret(cx);
        jsret = ccmap_string_key_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_SkeletonNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::timeline::SkeletonNode::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::SkeletonNode>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::timeline::SkeletonNode"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_SkeletonNode_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_SkeletonNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::timeline::SkeletonNode* cobj = new (std::nothrow) cocostudio::timeline::SkeletonNode();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::timeline::SkeletonNode>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::timeline::SkeletonNode"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_studio_SkeletonNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocostudio::timeline::SkeletonNode *nobj = new (std::nothrow) cocostudio::timeline::SkeletonNode();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocostudio::timeline::SkeletonNode");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocostudio_timeline_BoneNode_prototype;

    
void js_register_cocos2dx_studio_SkeletonNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_timeline_SkeletonNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_timeline_SkeletonNode_class->name = "SkeletonNode";
    jsb_cocostudio_timeline_SkeletonNode_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_timeline_SkeletonNode_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_timeline_SkeletonNode_class->resolve = JS_ResolveStub;
    jsb_cocostudio_timeline_SkeletonNode_class->convert = JS_ConvertStub;
    jsb_cocostudio_timeline_SkeletonNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getBoneNode", js_cocos2dx_studio_SkeletonNode_getBoneNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeSkins", js_cocos2dx_studio_SkeletonNode_changeSkins, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addSkinGroup", js_cocos2dx_studio_SkeletonNode_addSkinGroup, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAllSubBonesMap", js_cocos2dx_studio_SkeletonNode_getAllSubBonesMap, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_studio_SkeletonNode_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_SkeletonNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocostudio_timeline_BoneNode_prototype);
    jsb_cocostudio_timeline_SkeletonNode_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_timeline_SkeletonNode_class,
        js_cocos2dx_studio_SkeletonNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_timeline_SkeletonNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SkeletonNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::timeline::SkeletonNode>(cx, jsb_cocostudio_timeline_SkeletonNode_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { ccs.SkeletonNode.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocostudio_ComExtensionData_class;
JSObject *jsb_cocostudio_ComExtensionData_prototype;

bool js_cocos2dx_studio_ComExtensionData_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComExtensionData_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_getCustomProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_getCustomProperty : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getCustomProperty();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_getCustomProperty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_getActionTag : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getActionTag();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_setCustomProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ComExtensionData* cobj = (cocostudio::ComExtensionData *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ComExtensionData_setCustomProperty : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ComExtensionData_setCustomProperty : Error processing arguments");
        cobj->setCustomProperty(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_setCustomProperty : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_studio_ComExtensionData_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocostudio::ComExtensionData::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComExtensionData>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocostudio::ComExtensionData"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_studio_ComExtensionData_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_studio_ComExtensionData_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocostudio::ComExtensionData* cobj = new (std::nothrow) cocostudio::ComExtensionData();

    js_type_class_t *typeClass = js_get_type_from_native<cocostudio::ComExtensionData>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocostudio::ComExtensionData"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_register_cocos2dx_studio_ComExtensionData(JSContext *cx, JS::HandleObject global) {
    jsb_cocostudio_ComExtensionData_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocostudio_ComExtensionData_class->name = "ComExtensionData";
    jsb_cocostudio_ComExtensionData_class->addProperty = JS_PropertyStub;
    jsb_cocostudio_ComExtensionData_class->delProperty = JS_DeletePropertyStub;
    jsb_cocostudio_ComExtensionData_class->getProperty = JS_PropertyStub;
    jsb_cocostudio_ComExtensionData_class->setProperty = JS_StrictPropertyStub;
    jsb_cocostudio_ComExtensionData_class->enumerate = JS_EnumerateStub;
    jsb_cocostudio_ComExtensionData_class->resolve = JS_ResolveStub;
    jsb_cocostudio_ComExtensionData_class->convert = JS_ConvertStub;
    jsb_cocostudio_ComExtensionData_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setActionTag", js_cocos2dx_studio_ComExtensionData_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCustomProperty", js_cocos2dx_studio_ComExtensionData_getCustomProperty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_studio_ComExtensionData_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCustomProperty", js_cocos2dx_studio_ComExtensionData_setCustomProperty, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_studio_ComExtensionData_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Component_prototype);
    jsb_cocostudio_ComExtensionData_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocostudio_ComExtensionData_class,
        js_cocos2dx_studio_ComExtensionData_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocostudio_ComExtensionData_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ComExtensionData"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocostudio::ComExtensionData>(cx, jsb_cocostudio_ComExtensionData_class, proto, parent_proto);
}

void register_all_cocos2dx_studio(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccs", &ns);

    js_register_cocos2dx_studio_BoneNode(cx, ns);
    js_register_cocos2dx_studio_SkeletonNode(cx, ns);
    js_register_cocos2dx_studio_Frame(cx, ns);
    js_register_cocos2dx_studio_ScaleFrame(cx, ns);
    js_register_cocos2dx_studio_ProcessBase(cx, ns);
    js_register_cocos2dx_studio_Tween(cx, ns);
    js_register_cocos2dx_studio_ContourData(cx, ns);
    js_register_cocos2dx_studio_ComAudio(cx, ns);
    js_register_cocos2dx_studio_ActionTimeline(cx, ns);
    js_register_cocos2dx_studio_InnerActionFrame(cx, ns);
    js_register_cocos2dx_studio_ActionTimelineData(cx, ns);
    js_register_cocos2dx_studio_MovementData(cx, ns);
    js_register_cocos2dx_studio_ArmatureDataManager(cx, ns);
    js_register_cocos2dx_studio_ColorFrame(cx, ns);
    js_register_cocos2dx_studio_ZOrderFrame(cx, ns);
    js_register_cocos2dx_studio_Timeline(cx, ns);
    js_register_cocos2dx_studio_ColliderBody(cx, ns);
    js_register_cocos2dx_studio_InputDelegate(cx, ns);
    js_register_cocos2dx_studio_ComController(cx, ns);
    js_register_cocos2dx_studio_DecorativeDisplay(cx, ns);
    js_register_cocos2dx_studio_SkewFrame(cx, ns);
    js_register_cocos2dx_studio_RotationSkewFrame(cx, ns);
    js_register_cocos2dx_studio_ColliderFilter(cx, ns);
    js_register_cocos2dx_studio_VisibleFrame(cx, ns);
    js_register_cocos2dx_studio_PositionFrame(cx, ns);
    js_register_cocos2dx_studio_RotationFrame(cx, ns);
    js_register_cocos2dx_studio_ColliderDetector(cx, ns);
    js_register_cocos2dx_studio_BatchNode(cx, ns);
    js_register_cocos2dx_studio_ActionObject(cx, ns);
    js_register_cocos2dx_studio_Skin(cx, ns);
    js_register_cocos2dx_studio_EventFrame(cx, ns);
    js_register_cocos2dx_studio_ComRender(cx, ns);
    js_register_cocos2dx_studio_DisplayManager(cx, ns);
    js_register_cocos2dx_studio_ArmatureAnimation(cx, ns);
    js_register_cocos2dx_studio_Armature(cx, ns);
    js_register_cocos2dx_studio_ActionManagerEx(cx, ns);
    js_register_cocos2dx_studio_Bone(cx, ns);
    js_register_cocos2dx_studio_ComAttribute(cx, ns);
    js_register_cocos2dx_studio_TextureData(cx, ns);
    js_register_cocos2dx_studio_BlendFuncFrame(cx, ns);
    js_register_cocos2dx_studio_AlphaFrame(cx, ns);
    js_register_cocos2dx_studio_ComExtensionData(cx, ns);
    js_register_cocos2dx_studio_AnimationData(cx, ns);
    js_register_cocos2dx_studio_AnchorPointFrame(cx, ns);
    js_register_cocos2dx_studio_TextureFrame(cx, ns);
    js_register_cocos2dx_studio_BaseData(cx, ns);
}

