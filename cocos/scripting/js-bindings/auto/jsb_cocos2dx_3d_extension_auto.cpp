#include "scripting/js-bindings/auto/jsb_cocos2dx_3d_extension_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "cocos-ext.h"

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
JSClass  *jsb_cocos2d_ParticleSystem3D_class;
JSObject *jsb_cocos2d_ParticleSystem3D_prototype;

bool js_cocos2dx_3d_extension_ParticleSystem3D_resumeParticleSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_resumeParticleSystem : Invalid Native Object");
    if (argc == 0) {
        cobj->resumeParticleSystem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_resumeParticleSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_startParticleSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_startParticleSystem : Invalid Native Object");
    if (argc == 0) {
        cobj->startParticleSystem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_startParticleSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_isEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_getRender(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_getRender : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Particle3DRender* ret = cobj->getRender();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Particle3DRender>(cx, (cocos2d::Particle3DRender*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_getRender : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_isKeepLocal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_isKeepLocal : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isKeepLocal();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_isKeepLocal : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_getParticleQuota(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_getParticleQuota : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getParticleQuota();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_getParticleQuota : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_pauseParticleSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_pauseParticleSystem : Invalid Native Object");
    if (argc == 0) {
        cobj->pauseParticleSystem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_pauseParticleSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_getState : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getState();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_getState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_getAliveParticleCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_getAliveParticleCount : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getAliveParticleCount();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_getAliveParticleCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_setParticleQuota(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setParticleQuota : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setParticleQuota : Error processing arguments");
        cobj->setParticleQuota(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_setParticleQuota : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_stopParticleSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_stopParticleSystem : Invalid Native Object");
    if (argc == 0) {
        cobj->stopParticleSystem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_stopParticleSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_setKeepLocal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ParticleSystem3D* cobj = (cocos2d::ParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setKeepLocal : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_ParticleSystem3D_setKeepLocal : Error processing arguments");
        cobj->setKeepLocal(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_ParticleSystem3D_setKeepLocal : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_ParticleSystem3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ParticleSystem3D* cobj = new (std::nothrow) cocos2d::ParticleSystem3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::ParticleSystem3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::ParticleSystem3D"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_3d_extension_ParticleSystem3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ParticleSystem3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ParticleSystem3D_class->name = "ParticleSystem3D";
    jsb_cocos2d_ParticleSystem3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ParticleSystem3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ParticleSystem3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ParticleSystem3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ParticleSystem3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ParticleSystem3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ParticleSystem3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_ParticleSystem3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("resumeParticleSystem", js_cocos2dx_3d_extension_ParticleSystem3D_resumeParticleSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("startParticleSystem", js_cocos2dx_3d_extension_ParticleSystem3D_startParticleSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnabled", js_cocos2dx_3d_extension_ParticleSystem3D_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRender", js_cocos2dx_3d_extension_ParticleSystem3D_getRender, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isKeepLocal", js_cocos2dx_3d_extension_ParticleSystem3D_isKeepLocal, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEnabled", js_cocos2dx_3d_extension_ParticleSystem3D_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParticleQuota", js_cocos2dx_3d_extension_ParticleSystem3D_getParticleQuota, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_3d_extension_ParticleSystem3D_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pauseParticleSystem", js_cocos2dx_3d_extension_ParticleSystem3D_pauseParticleSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_cocos2dx_3d_extension_ParticleSystem3D_getState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAliveParticleCount", js_cocos2dx_3d_extension_ParticleSystem3D_getAliveParticleCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setParticleQuota", js_cocos2dx_3d_extension_ParticleSystem3D_setParticleQuota, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_3d_extension_ParticleSystem3D_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopParticleSystem", js_cocos2dx_3d_extension_ParticleSystem3D_stopParticleSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setKeepLocal", js_cocos2dx_3d_extension_ParticleSystem3D_setKeepLocal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocos2d_ParticleSystem3D_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_ParticleSystem3D_class,
        js_cocos2dx_3d_extension_ParticleSystem3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_ParticleSystem3D_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ParticleSystem3D"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::ParticleSystem3D>(cx, jsb_cocos2d_ParticleSystem3D_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_PUParticleSystem3D_class;
JSObject *jsb_cocos2d_PUParticleSystem3D_prototype;

bool js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePath : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePath : Error processing arguments");
        bool ret = cobj->initWithFilePath(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePath : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getParticleSystemScaleVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getParticleSystemScaleVelocity : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getParticleSystemScaleVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getParticleSystemScaleVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedSystemQuota(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedSystemQuota : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedSystemQuota : Error processing arguments");
        cobj->setEmittedSystemQuota(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedSystemQuota : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultDepth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultDepth : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDefaultDepth();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultDepth : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedSystemQuota(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedSystemQuota : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getEmittedSystemQuota();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedSystemQuota : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath : Error processing arguments");
        bool ret = cobj->initWithFilePathAndMaterialPath(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_clearAllParticles(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_clearAllParticles : Invalid Native Object");
    if (argc == 0) {
        cobj->clearAllParticles();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_clearAllParticles : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getMaterialName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getMaterialName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getMaterialName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getMaterialName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_calulateRotationOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_calulateRotationOffset : Invalid Native Object");
    if (argc == 0) {
        cobj->calulateRotationOffset();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_calulateRotationOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getMaxVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getMaxVelocity : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxVelocity();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getMaxVelocity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_forceUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_forceUpdate : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_forceUpdate : Error processing arguments");
        cobj->forceUpdate(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_forceUpdate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getTimeElapsedSinceStart(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getTimeElapsedSinceStart : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTimeElapsedSinceStart();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getTimeElapsedSinceStart : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedEmitterQuota(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedEmitterQuota : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getEmittedEmitterQuota();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedEmitterQuota : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_isMarkedForEmission(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_isMarkedForEmission : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isMarkedForEmission();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_isMarkedForEmission : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultWidth : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDefaultWidth();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultWidth : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedEmitterQuota(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedEmitterQuota : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedEmitterQuota : Error processing arguments");
        cobj->setEmittedEmitterQuota(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedEmitterQuota : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setMarkedForEmission(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMarkedForEmission : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMarkedForEmission : Error processing arguments");
        cobj->setMarkedForEmission(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMarkedForEmission : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_clone : Invalid Native Object");
    if (argc == 0) {
        cocos2d::PUParticleSystem3D* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::PUParticleSystem3D>(cx, (cocos2d::PUParticleSystem3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultWidth : Error processing arguments");
        cobj->setDefaultWidth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_copyAttributesTo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_copyAttributesTo : Invalid Native Object");
    if (argc == 1) {
        cocos2d::PUParticleSystem3D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::PUParticleSystem3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_copyAttributesTo : Error processing arguments");
        cobj->copyAttributesTo(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_copyAttributesTo : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setMaterialName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMaterialName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMaterialName : Error processing arguments");
        cobj->setMaterialName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMaterialName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getParentParticleSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getParentParticleSystem : Invalid Native Object");
    if (argc == 0) {
        cocos2d::PUParticleSystem3D* ret = cobj->getParentParticleSystem();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::PUParticleSystem3D>(cx, (cocos2d::PUParticleSystem3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getParentParticleSystem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setMaxVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMaxVelocity : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMaxVelocity : Error processing arguments");
        cobj->setMaxVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setMaxVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDefaultHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getDerivedPosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_rotationOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_rotationOffset : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_rotationOffset : Error processing arguments");
        cobj->rotationOffset(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_rotationOffset : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedOrientation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedOrientation : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Quaternion ret = cobj->getDerivedOrientation();
        jsval jsret = JSVAL_NULL;
        jsret = quaternion_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedOrientation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllEmitter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllEmitter : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllEmitter();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllEmitter : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setParticleSystemScaleVelocity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setParticleSystemScaleVelocity : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setParticleSystemScaleVelocity : Error processing arguments");
        cobj->setParticleSystemScaleVelocity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setParticleSystemScaleVelocity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedScale : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec3 ret = cobj->getDerivedScale();
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultHeight : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultHeight : Error processing arguments");
        cobj->setDefaultHeight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultHeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllListener : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllListener();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_initSystem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_initSystem : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_initSystem : Error processing arguments");
        bool ret = cobj->initSystem(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_initSystem : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultDepth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::PUParticleSystem3D* cobj = (cocos2d::PUParticleSystem3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultDepth : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultDepth : Error processing arguments");
        cobj->setDefaultDepth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultDepth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::PUParticleSystem3D* ret = cocos2d::PUParticleSystem3D::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::PUParticleSystem3D>(cx, (cocos2d::PUParticleSystem3D*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::PUParticleSystem3D* ret = cocos2d::PUParticleSystem3D::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::PUParticleSystem3D>(cx, (cocos2d::PUParticleSystem3D*)ret));
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
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::PUParticleSystem3D* ret = cocos2d::PUParticleSystem3D::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::PUParticleSystem3D>(cx, (cocos2d::PUParticleSystem3D*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_3d_extension_PUParticleSystem3D_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_extension_PUParticleSystem3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::PUParticleSystem3D* cobj = new (std::nothrow) cocos2d::PUParticleSystem3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::PUParticleSystem3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::PUParticleSystem3D"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ParticleSystem3D_prototype;

void js_register_cocos2dx_3d_extension_PUParticleSystem3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_PUParticleSystem3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_PUParticleSystem3D_class->name = "PUParticleSystem3D";
    jsb_cocos2d_PUParticleSystem3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_PUParticleSystem3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_PUParticleSystem3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_PUParticleSystem3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_PUParticleSystem3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_PUParticleSystem3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_PUParticleSystem3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_PUParticleSystem3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithFilePath", js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParticleSystemScaleVelocity", js_cocos2dx_3d_extension_PUParticleSystem3D_getParticleSystemScaleVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmittedSystemQuota", js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedSystemQuota, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultDepth", js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultDepth, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEmittedSystemQuota", js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedSystemQuota, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFilePathAndMaterialPath", js_cocos2dx_3d_extension_PUParticleSystem3D_initWithFilePathAndMaterialPath, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearAllParticles", js_cocos2dx_3d_extension_PUParticleSystem3D_clearAllParticles, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaterialName", js_cocos2dx_3d_extension_PUParticleSystem3D_getMaterialName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("calulateRotationOffset", js_cocos2dx_3d_extension_PUParticleSystem3D_calulateRotationOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxVelocity", js_cocos2dx_3d_extension_PUParticleSystem3D_getMaxVelocity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("forceUpdate", js_cocos2dx_3d_extension_PUParticleSystem3D_forceUpdate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeElapsedSinceStart", js_cocos2dx_3d_extension_PUParticleSystem3D_getTimeElapsedSinceStart, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEmittedEmitterQuota", js_cocos2dx_3d_extension_PUParticleSystem3D_getEmittedEmitterQuota, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isMarkedForEmission", js_cocos2dx_3d_extension_PUParticleSystem3D_isMarkedForEmission, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultWidth", js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultWidth, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEmittedEmitterQuota", js_cocos2dx_3d_extension_PUParticleSystem3D_setEmittedEmitterQuota, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMarkedForEmission", js_cocos2dx_3d_extension_PUParticleSystem3D_setMarkedForEmission, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clone", js_cocos2dx_3d_extension_PUParticleSystem3D_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDefaultWidth", js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("copyAttributesTo", js_cocos2dx_3d_extension_PUParticleSystem3D_copyAttributesTo, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaterialName", js_cocos2dx_3d_extension_PUParticleSystem3D_setMaterialName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getParentParticleSystem", js_cocos2dx_3d_extension_PUParticleSystem3D_getParentParticleSystem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxVelocity", js_cocos2dx_3d_extension_PUParticleSystem3D_setMaxVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDefaultHeight", js_cocos2dx_3d_extension_PUParticleSystem3D_getDefaultHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDerivedPosition", js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("rotationOffset", js_cocos2dx_3d_extension_PUParticleSystem3D_rotationOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDerivedOrientation", js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedOrientation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllEmitter", js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllEmitter, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setParticleSystemScaleVelocity", js_cocos2dx_3d_extension_PUParticleSystem3D_setParticleSystemScaleVelocity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDerivedScale", js_cocos2dx_3d_extension_PUParticleSystem3D_getDerivedScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDefaultHeight", js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultHeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllListener", js_cocos2dx_3d_extension_PUParticleSystem3D_removeAllListener, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initSystem", js_cocos2dx_3d_extension_PUParticleSystem3D_initSystem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDefaultDepth", js_cocos2dx_3d_extension_PUParticleSystem3D_setDefaultDepth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_extension_PUParticleSystem3D_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_ParticleSystem3D_prototype);
    jsb_cocos2d_PUParticleSystem3D_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_PUParticleSystem3D_class,
        js_cocos2dx_3d_extension_PUParticleSystem3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_PUParticleSystem3D_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "PUParticleSystem3D"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::PUParticleSystem3D>(cx, jsb_cocos2d_PUParticleSystem3D_class, proto, parent_proto);
}

void register_all_cocos2dx_3d_extension(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_3d_extension_ParticleSystem3D(cx, ns);
    js_register_cocos2dx_3d_extension_PUParticleSystem3D(cx, ns);
}

