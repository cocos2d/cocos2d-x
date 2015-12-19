#include "jsb_cocos2dx_3d_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "cocos2d.h"
#include "CCBundle3D.h"
#include "3d/jsb_cocos2dx_3d_manual.h"

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
JSClass  *jsb_cocos2d_Animation3D_class;
JSObject *jsb_cocos2d_Animation3D_prototype;

bool js_cocos2dx_3d_Animation3D_initWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animation3D* cobj = (cocos2d::Animation3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animation3D_initWithFile : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animation3D_initWithFile : Error processing arguments");
        bool ret = cobj->initWithFile(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animation3D_initWithFile : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Animation3D_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animation3D* cobj = (cocos2d::Animation3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animation3D_init : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Animation3DData arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR Animation3DData
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animation3D_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animation3D_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Animation3D_getBoneCurveByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animation3D* cobj = (cocos2d::Animation3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animation3D_getBoneCurveByName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animation3D_getBoneCurveByName : Error processing arguments");
        cocos2d::Animation3D::Curve* ret = cobj->getBoneCurveByName(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Animation3D::Curve>(cx, (cocos2d::Animation3D::Curve*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animation3D_getBoneCurveByName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Animation3D_getDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animation3D* cobj = (cocos2d::Animation3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animation3D_getDuration : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getDuration();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animation3D_getDuration : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Animation3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Animation3D* cobj = new (std::nothrow) cocos2d::Animation3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Animation3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Animation3D"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_3d_Animation3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Animation3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Animation3D_class->name = "Animation3D";
    jsb_cocos2d_Animation3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Animation3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Animation3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Animation3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Animation3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Animation3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Animation3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Animation3D_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Animation3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithFile", js_cocos2dx_3d_Animation3D_initWithFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_3d_Animation3D_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneCurveByName", js_cocos2dx_3d_Animation3D_getBoneCurveByName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDuration", js_cocos2dx_3d_Animation3D_getDuration, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Animation3D_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_Animation3D_class,
        js_cocos2dx_3d_Animation3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Animation3D_prototype);
    jsb_register_class<cocos2d::Animation3D>(cx, jsb_cocos2d_Animation3D_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocos2d_Animate3D_class;
JSObject *jsb_cocos2d_Animate3D_prototype;

bool js_cocos2dx_3d_Animate3D_setKeyFrameUserInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_setKeyFrameUserInfo : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        cocos2d::ValueMap arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_ccvaluemap(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_setKeyFrameUserInfo : Error processing arguments");
        cobj->setKeyFrameUserInfo(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_setKeyFrameUserInfo : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Animate3D_getSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_getSpeed : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSpeed();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_getSpeed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Animate3D_setQuality(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_setQuality : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Animate3DQuality arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_setQuality : Error processing arguments");
        cobj->setQuality(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_setQuality : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Animate3D_setWeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_setWeight : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_setWeight : Error processing arguments");
        cobj->setWeight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_setWeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Animate3D_removeFromMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_removeFromMap : Invalid Native Object");
    if (argc == 0) {
        cobj->removeFromMap();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_removeFromMap : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Animate3D_initWithFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_initWithFrames : Invalid Native Object");
    if (argc == 4) {
        cocos2d::Animation3D* arg0 = nullptr;
        int arg1 = 0;
        int arg2 = 0;
        double arg3 = 0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_initWithFrames : Error processing arguments");
        bool ret = cobj->initWithFrames(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_initWithFrames : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_3d_Animate3D_getOriginInterval(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_getOriginInterval : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getOriginInterval();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_getOriginInterval : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Animate3D_setSpeed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_setSpeed : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_setSpeed : Error processing arguments");
        cobj->setSpeed(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_setSpeed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Animate3D_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::Animate3D* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_init : Invalid Native Object");
    do {
        if (argc == 3) {
            cocos2d::Animation3D* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            double arg2 = 0;
            ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Animation3D* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
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

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_init : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Animate3D_setOriginInterval(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_setOriginInterval : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_setOriginInterval : Error processing arguments");
        cobj->setOriginInterval(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_setOriginInterval : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Animate3D_getWeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_getWeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getWeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_getWeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Animate3D_getQuality(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Animate3D* cobj = (cocos2d::Animate3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Animate3D_getQuality : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getQuality();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_getQuality : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Animate3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            cocos2d::Animation3D* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            double arg2 = 0;
            ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
            if (!ok) { ok = true; break; }
            cocos2d::Animate3D* ret = cocos2d::Animate3D::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Animate3D>(cx, (cocos2d::Animate3D*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 1) {
            cocos2d::Animation3D* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Animate3D* ret = cocos2d::Animate3D::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Animate3D>(cx, (cocos2d::Animate3D*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Animate3D_getTransitionTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        double ret = cocos2d::Animate3D::getTransitionTime();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_getTransitionTime : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Animate3D_createWithFrames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        cocos2d::Animation3D* arg0 = nullptr;
        int arg1 = 0;
        int arg2 = 0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_createWithFrames : Error processing arguments");

        auto ret = cocos2d::Animate3D::createWithFrames(arg0, arg1, arg2);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Animate3D>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::Animate3D"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    if (argc == 4) {
        cocos2d::Animation3D* arg0 = nullptr;
        int arg1 = 0;
        int arg2 = 0;
        double arg3 = 0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Animation3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_createWithFrames : Error processing arguments");

        auto ret = cocos2d::Animate3D::createWithFrames(arg0, arg1, arg2, arg3);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Animate3D>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::Animate3D"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_createWithFrames : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Animate3D_setTransitionTime(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Animate3D_setTransitionTime : Error processing arguments");
        cocos2d::Animate3D::setTransitionTime(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Animate3D_setTransitionTime : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Animate3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Animate3D* cobj = new (std::nothrow) cocos2d::Animate3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Animate3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Animate3D"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ActionInterval_prototype;

void js_register_cocos2dx_3d_Animate3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Animate3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Animate3D_class->name = "Animate3D";
    jsb_cocos2d_Animate3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Animate3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Animate3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Animate3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Animate3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Animate3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Animate3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Animate3D_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Animate3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setKeyFrameUserInfo", js_cocos2dx_3d_Animate3D_setKeyFrameUserInfo, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpeed", js_cocos2dx_3d_Animate3D_getSpeed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setQuality", js_cocos2dx_3d_Animate3D_setQuality, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setWeight", js_cocos2dx_3d_Animate3D_setWeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeFromMap", js_cocos2dx_3d_Animate3D_removeFromMap, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFrames", js_cocos2dx_3d_Animate3D_initWithFrames, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOriginInterval", js_cocos2dx_3d_Animate3D_getOriginInterval, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSpeed", js_cocos2dx_3d_Animate3D_setSpeed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_3d_Animate3D_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOriginInterval", js_cocos2dx_3d_Animate3D_setOriginInterval, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getWeight", js_cocos2dx_3d_Animate3D_getWeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getQuality", js_cocos2dx_3d_Animate3D_getQuality, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_Animate3D_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTransitionTime", js_cocos2dx_3d_Animate3D_getTransitionTime, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithFrames", js_cocos2dx_3d_Animate3D_createWithFrames, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTransitionTime", js_cocos2dx_3d_Animate3D_setTransitionTime, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_ActionInterval_prototype);
    jsb_cocos2d_Animate3D_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_Animate3D_class,
        js_cocos2dx_3d_Animate3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Animate3D_prototype);
    jsb_register_class<cocos2d::Animate3D>(cx, jsb_cocos2d_Animate3D_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_TextureCube_class;
JSObject *jsb_cocos2d_TextureCube_prototype;

bool js_cocos2dx_3d_TextureCube_reloadTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::TextureCube* cobj = (cocos2d::TextureCube *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_TextureCube_reloadTexture : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->reloadTexture();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_TextureCube_reloadTexture : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_TextureCube_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 6) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        std::string arg5;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        ok &= jsval_to_std_string(cx, args.get(5), &arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_TextureCube_create : Error processing arguments");

        auto ret = cocos2d::TextureCube::create(arg0, arg1, arg2, arg3, arg4, arg5);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::TextureCube>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::TextureCube"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_TextureCube_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_TextureCube_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::TextureCube* cobj = new (std::nothrow) cocos2d::TextureCube();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::TextureCube>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::TextureCube"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Texture2D_prototype;

void js_register_cocos2dx_3d_TextureCube(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_TextureCube_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_TextureCube_class->name = "TextureCube";
    jsb_cocos2d_TextureCube_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_TextureCube_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_TextureCube_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_TextureCube_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_TextureCube_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_TextureCube_class->resolve = JS_ResolveStub;
    jsb_cocos2d_TextureCube_class->convert = JS_ConvertStub;
    jsb_cocos2d_TextureCube_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_TextureCube_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("reloadTexture", js_cocos2dx_3d_TextureCube_reloadTexture, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_TextureCube_create, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Texture2D_prototype);
    jsb_cocos2d_TextureCube_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_TextureCube_class,
        js_cocos2dx_3d_TextureCube_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_TextureCube_prototype);
    jsb_register_class<cocos2d::TextureCube>(cx, jsb_cocos2d_TextureCube_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_AttachNode_class;
JSObject *jsb_cocos2d_AttachNode_prototype;

bool js_cocos2dx_3d_AttachNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Bone3D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Bone3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_AttachNode_create : Error processing arguments");

        auto ret = cocos2d::AttachNode::create(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::AttachNode>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::AttachNode"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_AttachNode_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_AttachNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::AttachNode* cobj = new (std::nothrow) cocos2d::AttachNode();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::AttachNode>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::AttachNode"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_3d_AttachNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_AttachNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_AttachNode_class->name = "AttachNode";
    jsb_cocos2d_AttachNode_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_AttachNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_AttachNode_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_AttachNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_AttachNode_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_AttachNode_class->resolve = JS_ResolveStub;
    jsb_cocos2d_AttachNode_class->convert = JS_ConvertStub;
    jsb_cocos2d_AttachNode_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_AttachNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_AttachNode_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocos2d_AttachNode_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_AttachNode_class,
        js_cocos2dx_3d_AttachNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_AttachNode_prototype);
    jsb_register_class<cocos2d::AttachNode>(cx, jsb_cocos2d_AttachNode_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_BillBoard_class;
JSObject *jsb_cocos2d_BillBoard_prototype;

bool js_cocos2dx_3d_BillBoard_getMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillBoard* cobj = (cocos2d::BillBoard *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_BillBoard_getMode : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getMode();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_BillBoard_getMode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_BillBoard_setMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::BillBoard* cobj = (cocos2d::BillBoard *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_BillBoard_setMode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BillBoard::Mode arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_BillBoard_setMode : Error processing arguments");
        cobj->setMode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_BillBoard_setMode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_BillBoard_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::BillBoard>(cx, (cocos2d::BillBoard*)ret));
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
            cocos2d::BillBoard::Mode arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::BillBoard>(cx, (cocos2d::BillBoard*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::BillBoard>(cx, (cocos2d::BillBoard*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 1) {
            cocos2d::BillBoard::Mode arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::BillBoard>(cx, (cocos2d::BillBoard*)ret));
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
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::BillBoard>(cx, (cocos2d::BillBoard*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::BillBoard::Mode arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            cocos2d::BillBoard* ret = cocos2d::BillBoard::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::BillBoard>(cx, (cocos2d::BillBoard*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_3d_BillBoard_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_BillBoard_createWithTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Texture2D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_BillBoard_createWithTexture : Error processing arguments");

        auto ret = cocos2d::BillBoard::createWithTexture(arg0);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::BillBoard>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::BillBoard"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    if (argc == 2) {
        cocos2d::Texture2D* arg0 = nullptr;
        cocos2d::BillBoard::Mode arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_BillBoard_createWithTexture : Error processing arguments");

        auto ret = cocos2d::BillBoard::createWithTexture(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::BillBoard>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::BillBoard"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_BillBoard_createWithTexture : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_BillBoard_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::BillBoard* cobj = new (std::nothrow) cocos2d::BillBoard();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::BillBoard>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::BillBoard"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Sprite_prototype;

void js_register_cocos2dx_3d_BillBoard(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_BillBoard_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_BillBoard_class->name = "BillBoard";
    jsb_cocos2d_BillBoard_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_BillBoard_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_BillBoard_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_BillBoard_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_BillBoard_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_BillBoard_class->resolve = JS_ResolveStub;
    jsb_cocos2d_BillBoard_class->convert = JS_ConvertStub;
    jsb_cocos2d_BillBoard_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_BillBoard_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getMode", js_cocos2dx_3d_BillBoard_getMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMode", js_cocos2dx_3d_BillBoard_setMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_BillBoard_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithTexture", js_cocos2dx_3d_BillBoard_createWithTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Sprite_prototype);
    jsb_cocos2d_BillBoard_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_BillBoard_class,
        js_cocos2dx_3d_BillBoard_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_BillBoard_prototype);
    jsb_register_class<cocos2d::BillBoard>(cx, jsb_cocos2d_BillBoard_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_Mesh_class;
JSObject *jsb_cocos2d_Mesh_prototype;

bool js_cocos2dx_3d_Mesh_getSkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getSkin : Invalid Native Object");
    if (argc == 0) {
        cocos2d::MeshSkin* ret = cobj->getSkin();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::MeshSkin>(cx, (cocos2d::MeshSkin*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getSkin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getMaterial(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getMaterial : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Material* ret = cobj->getMaterial();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Material>(cx, (cocos2d::Material*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getMaterial : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getVertexSizeInBytes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getVertexSizeInBytes : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getVertexSizeInBytes();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getVertexSizeInBytes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_setMaterial(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setMaterial : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Material* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Material*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setMaterial : Error processing arguments");
        cobj->setMaterial(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setMaterial : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_getName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getIndexFormat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getIndexFormat : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getIndexFormat();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getIndexFormat : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getGLProgramState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getGLProgramState : Invalid Native Object");
    if (argc == 0) {
        cocos2d::GLProgramState* ret = cobj->getGLProgramState();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::GLProgramState>(cx, (cocos2d::GLProgramState*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getGLProgramState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getVertexBuffer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getVertexBuffer : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getVertexBuffer();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getVertexBuffer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_calculateAABB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_calculateAABB : Invalid Native Object");
    if (argc == 0) {
        cobj->calculateAABB();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_calculateAABB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_hasVertexAttrib(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_hasVertexAttrib : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_hasVertexAttrib : Error processing arguments");
        bool ret = cobj->hasVertexAttrib(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_hasVertexAttrib : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getMeshIndexData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getMeshIndexData : Invalid Native Object");
    if (argc == 0) {
        cocos2d::MeshIndexData* ret = cobj->getMeshIndexData();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::MeshIndexData>(cx, (cocos2d::MeshIndexData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getMeshIndexData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_setName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setName : Error processing arguments");
        cobj->setName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_getIndexCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getIndexCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getIndexCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getIndexCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_setMeshIndexData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setMeshIndexData : Invalid Native Object");
    if (argc == 1) {
        cocos2d::MeshIndexData* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::MeshIndexData*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setMeshIndexData : Error processing arguments");
        cobj->setMeshIndexData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setMeshIndexData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_getMeshVertexAttribCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getMeshVertexAttribCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getMeshVertexAttribCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getMeshVertexAttribCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_setForce2DQueue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setForce2DQueue : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setForce2DQueue : Error processing arguments");
        cobj->setForce2DQueue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setForce2DQueue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_getPrimitiveType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getPrimitiveType : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getPrimitiveType();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getPrimitiveType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_setSkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setSkin : Invalid Native Object");
    if (argc == 1) {
        cocos2d::MeshSkin* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::MeshSkin*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setSkin : Error processing arguments");
        cobj->setSkin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setSkin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_isVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_isVisible : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isVisible();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_isVisible : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_getIndexBuffer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_getIndexBuffer : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getIndexBuffer();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_getIndexBuffer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Mesh_setGLProgramState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setGLProgramState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::GLProgramState* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::GLProgramState*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setGLProgramState : Error processing arguments");
        cobj->setGLProgramState(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setGLProgramState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_setVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Mesh* cobj = (cocos2d::Mesh *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Mesh_setVisible : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Mesh_setVisible : Error processing arguments");
        cobj->setVisible(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Mesh_setVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Mesh_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Mesh* cobj = new (std::nothrow) cocos2d::Mesh();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Mesh>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Mesh"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_3d_Mesh(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Mesh_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Mesh_class->name = "Mesh";
    jsb_cocos2d_Mesh_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Mesh_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Mesh_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Mesh_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Mesh_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Mesh_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Mesh_class->convert = JS_ConvertStub;
    jsb_cocos2d_Mesh_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Mesh_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getSkin", js_cocos2dx_3d_Mesh_getSkin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaterial", js_cocos2dx_3d_Mesh_getMaterial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVertexSizeInBytes", js_cocos2dx_3d_Mesh_getVertexSizeInBytes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaterial", js_cocos2dx_3d_Mesh_setMaterial, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getName", js_cocos2dx_3d_Mesh_getName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIndexFormat", js_cocos2dx_3d_Mesh_getIndexFormat, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGLProgramState", js_cocos2dx_3d_Mesh_getGLProgramState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVertexBuffer", js_cocos2dx_3d_Mesh_getVertexBuffer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("calculateAABB", js_cocos2dx_3d_Mesh_calculateAABB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasVertexAttrib", js_cocos2dx_3d_Mesh_hasVertexAttrib, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_3d_Mesh_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshIndexData", js_cocos2dx_3d_Mesh_getMeshIndexData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setName", js_cocos2dx_3d_Mesh_setName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIndexCount", js_cocos2dx_3d_Mesh_getIndexCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMeshIndexData", js_cocos2dx_3d_Mesh_setMeshIndexData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshVertexAttribCount", js_cocos2dx_3d_Mesh_getMeshVertexAttribCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_3d_Mesh_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setForce2DQueue", js_cocos2dx_3d_Mesh_setForce2DQueue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPrimitiveType", js_cocos2dx_3d_Mesh_getPrimitiveType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkin", js_cocos2dx_3d_Mesh_setSkin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isVisible", js_cocos2dx_3d_Mesh_isVisible, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIndexBuffer", js_cocos2dx_3d_Mesh_getIndexBuffer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGLProgramState", js_cocos2dx_3d_Mesh_setGLProgramState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVisible", js_cocos2dx_3d_Mesh_setVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Mesh_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_Mesh_class,
        js_cocos2dx_3d_Mesh_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Mesh_prototype);
    jsb_register_class<cocos2d::Mesh>(cx, jsb_cocos2d_Mesh_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocos2d_Skeleton3D_class;
JSObject *jsb_cocos2d_Skeleton3D_prototype;

bool js_cocos2dx_3d_Skeleton3D_removeAllBones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_removeAllBones : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllBones();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_removeAllBones : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_addBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_addBone : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Bone3D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Bone3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skeleton3D_addBone : Error processing arguments");
        cobj->addBone(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_addBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_getBoneByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneByName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneByName : Error processing arguments");
        cocos2d::Bone3D* ret = cobj->getBoneByName(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Bone3D>(cx, (cocos2d::Bone3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_getBoneByName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_getRootBone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_getRootBone : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skeleton3D_getRootBone : Error processing arguments");
        cocos2d::Bone3D* ret = cobj->getRootBone(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Bone3D>(cx, (cocos2d::Bone3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_getRootBone : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_updateBoneMatrix(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_updateBoneMatrix : Invalid Native Object");
    if (argc == 0) {
        cobj->updateBoneMatrix();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_updateBoneMatrix : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_getBoneByIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneByIndex : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneByIndex : Error processing arguments");
        cocos2d::Bone3D* ret = cobj->getBoneByIndex(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Bone3D>(cx, (cocos2d::Bone3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_getBoneByIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_getRootCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_getRootCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getRootCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_getRootCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_getBoneIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneIndex : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Bone3D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Bone3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneIndex : Error processing arguments");
        int ret = cobj->getBoneIndex(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_getBoneIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_getBoneCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skeleton3D* cobj = (cocos2d::Skeleton3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skeleton3D_getBoneCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getBoneCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skeleton3D_getBoneCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Skeleton3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Skeleton3D* cobj = new (std::nothrow) cocos2d::Skeleton3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Skeleton3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Skeleton3D"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_3d_Skeleton3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Skeleton3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Skeleton3D_class->name = "Skeleton3D";
    jsb_cocos2d_Skeleton3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Skeleton3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Skeleton3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Skeleton3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Skeleton3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Skeleton3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Skeleton3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Skeleton3D_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Skeleton3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("removeAllBones", js_cocos2dx_3d_Skeleton3D_removeAllBones, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addBone", js_cocos2dx_3d_Skeleton3D_addBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneByName", js_cocos2dx_3d_Skeleton3D_getBoneByName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRootBone", js_cocos2dx_3d_Skeleton3D_getRootBone, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateBoneMatrix", js_cocos2dx_3d_Skeleton3D_updateBoneMatrix, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneByIndex", js_cocos2dx_3d_Skeleton3D_getBoneByIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRootCount", js_cocos2dx_3d_Skeleton3D_getRootCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneIndex", js_cocos2dx_3d_Skeleton3D_getBoneIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBoneCount", js_cocos2dx_3d_Skeleton3D_getBoneCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_Skeleton3D_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_Skeleton3D_class,
        js_cocos2dx_3d_Skeleton3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Skeleton3D_prototype);
    jsb_register_class<cocos2d::Skeleton3D>(cx, jsb_cocos2d_Skeleton3D_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocos2d_Skybox_class;
JSObject *jsb_cocos2d_Skybox_prototype;

bool js_cocos2dx_3d_Skybox_reload(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skybox* cobj = (cocos2d::Skybox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skybox_reload : Invalid Native Object");
    if (argc == 0) {
        cobj->reload();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skybox_reload : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Skybox_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skybox* cobj = (cocos2d::Skybox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skybox_init : Invalid Native Object");
    if (argc == 6) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        std::string arg5;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        ok &= jsval_to_std_string(cx, args.get(5), &arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skybox_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skybox_init : wrong number of arguments: %d, was expecting %d", argc, 6);
    return false;
}
bool js_cocos2dx_3d_Skybox_setTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Skybox* cobj = (cocos2d::Skybox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Skybox_setTexture : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextureCube* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::TextureCube*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Skybox_setTexture : Error processing arguments");
        cobj->setTexture(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Skybox_setTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Skybox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 6) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            std::string arg3;
            ok &= jsval_to_std_string(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            std::string arg4;
            ok &= jsval_to_std_string(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            std::string arg5;
            ok &= jsval_to_std_string(cx, args.get(5), &arg5);
            if (!ok) { ok = true; break; }
            cocos2d::Skybox* ret = cocos2d::Skybox::create(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Skybox>(cx, (cocos2d::Skybox*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::Skybox* ret = cocos2d::Skybox::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Skybox>(cx, (cocos2d::Skybox*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_3d_Skybox_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Skybox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Skybox* cobj = new (std::nothrow) cocos2d::Skybox();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Skybox>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Skybox"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_3d_Skybox(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Skybox_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Skybox_class->name = "Skybox";
    jsb_cocos2d_Skybox_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Skybox_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Skybox_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Skybox_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Skybox_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Skybox_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Skybox_class->convert = JS_ConvertStub;
    jsb_cocos2d_Skybox_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Skybox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("reload", js_cocos2dx_3d_Skybox_reload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_3d_Skybox_init, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTexture", js_cocos2dx_3d_Skybox_setTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_Skybox_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocos2d_Skybox_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_Skybox_class,
        js_cocos2dx_3d_Skybox_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Skybox_prototype);
    jsb_register_class<cocos2d::Skybox>(cx, jsb_cocos2d_Skybox_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_Sprite3D_class;
JSObject *jsb_cocos2d_Sprite3D_prototype;

bool js_cocos2dx_3d_Sprite3D_setCullFaceEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setCullFaceEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setCullFaceEnabled : Error processing arguments");
        cobj->setCullFaceEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setCullFaceEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::Sprite3D* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setTexture : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Texture2D* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->setTexture(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setTexture(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setTexture : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getLightMask(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getLightMask : Invalid Native Object");
    if (argc == 0) {
        unsigned int ret = cobj->getLightMask();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getLightMask : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_createAttachSprite3DNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_createAttachSprite3DNode : Invalid Native Object");
    if (argc == 2) {
        cocos2d::NodeData* arg0 = nullptr;
        cocos2d::MaterialDatas arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeData*
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_createAttachSprite3DNode : Error processing arguments");
        cobj->createAttachSprite3DNode(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_createAttachSprite3DNode : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_loadFromFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_loadFromFile : Invalid Native Object");
    if (argc == 4) {
        std::string arg0;
        cocos2d::NodeDatas* arg1 = nullptr;
        cocos2d::MeshDatas* arg2 = nullptr;
        cocos2d::MaterialDatas* arg3 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        #pragma warning NO CONVERSION TO NATIVE FOR NodeDatas*
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MeshDatas*
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_loadFromFile : Error processing arguments");
        bool ret = cobj->loadFromFile(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_loadFromFile : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMaterial(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMaterial : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_getMaterial : Error processing arguments");
        cocos2d::Material* ret = cobj->getMaterial(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Material>(cx, (cocos2d::Material*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMaterial : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setCullFace(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setCullFace : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setCullFace : Error processing arguments");
        cobj->setCullFace(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setCullFace : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMeshes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshes : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vector<cocos2d::Mesh *>& ret = cobj->getMeshes();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMeshes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_addMesh(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_addMesh : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Mesh* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Mesh*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_addMesh : Error processing arguments");
        cobj->addMesh(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_addMesh : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_removeAllAttachNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_removeAllAttachNode : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllAttachNode();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_removeAllAttachNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setMaterial(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::Sprite3D* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setMaterial : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Material* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Material*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            int arg1 = 0;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj->setMaterial(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Material* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Material*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->setMaterial(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setMaterial : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMesh(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMesh : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Mesh* ret = cobj->getMesh();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Mesh>(cx, (cocos2d::Mesh*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMesh : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_createSprite3DNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_createSprite3DNode : Invalid Native Object");
    if (argc == 3) {
        cocos2d::NodeData* arg0 = nullptr;
        cocos2d::ModelData* arg1 = nullptr;
        cocos2d::MaterialDatas arg2;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeData*
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR ModelData*
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_createSprite3DNode : Error processing arguments");
        cocos2d::Sprite3D* ret = cobj->createSprite3DNode(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite3D>(cx, (cocos2d::Sprite3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_createSprite3DNode : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMeshCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshCount : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getMeshCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMeshCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_onAABBDirty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_onAABBDirty : Invalid Native Object");
    if (argc == 0) {
        cobj->onAABBDirty();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_onAABBDirty : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMeshByIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshByIndex : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshByIndex : Error processing arguments");
        cocos2d::Mesh* ret = cobj->getMeshByIndex(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Mesh>(cx, (cocos2d::Mesh*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMeshByIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_createNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_createNode : Invalid Native Object");
    if (argc == 4) {
        cocos2d::NodeData* arg0 = nullptr;
        cocos2d::Node* arg1 = nullptr;
        cocos2d::MaterialDatas arg2;
        bool arg3;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeData*
		ok = false;
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        arg3 = JS::ToBoolean(args.get(3));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_createNode : Error processing arguments");
        cobj->createNode(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_createNode : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_isForceDepthWrite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_isForceDepthWrite : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isForceDepthWrite();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_isForceDepthWrite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMeshIndexData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshIndexData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshIndexData : Error processing arguments");
        cocos2d::MeshIndexData* ret = cobj->getMeshIndexData(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::MeshIndexData>(cx, (cocos2d::MeshIndexData*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMeshIndexData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setLightMask(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setLightMask : Invalid Native Object");
    if (argc == 1) {
        unsigned int arg0 = 0;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setLightMask : Error processing arguments");
        cobj->setLightMask(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setLightMask : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_afterAsyncLoad(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_afterAsyncLoad : Invalid Native Object");
    if (argc == 1) {
        void* arg0 = nullptr;
        #pragma warning NO CONVERSION TO NATIVE FOR void*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_afterAsyncLoad : Error processing arguments");
        cobj->afterAsyncLoad(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_afterAsyncLoad : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_loadFromCache(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_loadFromCache : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_loadFromCache : Error processing arguments");
        bool ret = cobj->loadFromCache(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_loadFromCache : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_initFrom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_initFrom : Invalid Native Object");
    if (argc == 3) {
        cocos2d::NodeDatas arg0;
        cocos2d::MeshDatas arg1;
        cocos2d::MaterialDatas arg2;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeDatas
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MeshDatas
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_initFrom : Error processing arguments");
        bool ret = cobj->initFrom(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_initFrom : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getAttachNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getAttachNode : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_getAttachNode : Error processing arguments");
        cocos2d::AttachNode* ret = cobj->getAttachNode(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::AttachNode>(cx, (cocos2d::AttachNode*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getAttachNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_initWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_initWithFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_initWithFile : Error processing arguments");
        bool ret = cobj->initWithFile(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_initWithFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setForce2DQueue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setForce2DQueue : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setForce2DQueue : Error processing arguments");
        cobj->setForce2DQueue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setForce2DQueue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_genMaterial(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_genMaterial : Invalid Native Object");
    if (argc == 0) {
        cobj->genMaterial();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_genMaterial : Error processing arguments");
        cobj->genMaterial(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_genMaterial : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_removeAttachNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_removeAttachNode : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_removeAttachNode : Error processing arguments");
        cobj->removeAttachNode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_removeAttachNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getSkeleton(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getSkeleton : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Skeleton3D* ret = cobj->getSkeleton();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Skeleton3D>(cx, (cocos2d::Skeleton3D*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getSkeleton : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_setForceDepthWrite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_setForceDepthWrite : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_setForceDepthWrite : Error processing arguments");
        cobj->setForceDepthWrite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_setForceDepthWrite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_getMeshByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3D* cobj = (cocos2d::Sprite3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshByName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3D_getMeshByName : Error processing arguments");
        cocos2d::Mesh* ret = cobj->getMeshByName(arg0);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Mesh>(cx, (cocos2d::Mesh*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_getMeshByName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3D_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite3D* ret = cocos2d::Sprite3D::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite3D>(cx, (cocos2d::Sprite3D*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::Sprite3D* ret = cocos2d::Sprite3D::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite3D>(cx, (cocos2d::Sprite3D*)ret));
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
            cocos2d::Sprite3D* ret = cocos2d::Sprite3D::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite3D>(cx, (cocos2d::Sprite3D*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3D_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Sprite3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Sprite3D* cobj = new (std::nothrow) cocos2d::Sprite3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Sprite3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Sprite3D"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_3d_Sprite3D_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::Sprite3D *nobj = new (std::nothrow) cocos2d::Sprite3D();
    auto newproxy = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &newproxy->obj, nobj, "cocos2d::Sprite3D");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

    
void js_register_cocos2dx_3d_Sprite3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Sprite3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Sprite3D_class->name = "Sprite3D";
    jsb_cocos2d_Sprite3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Sprite3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Sprite3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Sprite3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Sprite3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Sprite3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Sprite3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Sprite3D_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Sprite3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setCullFaceEnabled", js_cocos2dx_3d_Sprite3D_setCullFaceEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTexture", js_cocos2dx_3d_Sprite3D_setTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLightMask", js_cocos2dx_3d_Sprite3D_getLightMask, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createAttachSprite3DNode", js_cocos2dx_3d_Sprite3D_createAttachSprite3DNode, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadFromFile", js_cocos2dx_3d_Sprite3D_loadFromFile, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaterial", js_cocos2dx_3d_Sprite3D_getMaterial, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCullFace", js_cocos2dx_3d_Sprite3D_setCullFace, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshes", js_cocos2dx_3d_Sprite3D_getMeshes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addMesh", js_cocos2dx_3d_Sprite3D_addMesh, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllAttachNode", js_cocos2dx_3d_Sprite3D_removeAllAttachNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaterial", js_cocos2dx_3d_Sprite3D_setMaterial, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMesh", js_cocos2dx_3d_Sprite3D_getMesh, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createSprite3DNode", js_cocos2dx_3d_Sprite3D_createSprite3DNode, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshCount", js_cocos2dx_3d_Sprite3D_getMeshCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onAABBDirty", js_cocos2dx_3d_Sprite3D_onAABBDirty, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshByIndex", js_cocos2dx_3d_Sprite3D_getMeshByIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createNode", js_cocos2dx_3d_Sprite3D_createNode, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isForceDepthWrite", js_cocos2dx_3d_Sprite3D_isForceDepthWrite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_3d_Sprite3D_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshIndexData", js_cocos2dx_3d_Sprite3D_getMeshIndexData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLightMask", js_cocos2dx_3d_Sprite3D_setLightMask, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("afterAsyncLoad", js_cocos2dx_3d_Sprite3D_afterAsyncLoad, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadFromCache", js_cocos2dx_3d_Sprite3D_loadFromCache, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initFrom", js_cocos2dx_3d_Sprite3D_initFrom, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAttachNode", js_cocos2dx_3d_Sprite3D_getAttachNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFile", js_cocos2dx_3d_Sprite3D_initWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_3d_Sprite3D_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setForce2DQueue", js_cocos2dx_3d_Sprite3D_setForce2DQueue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("genMaterial", js_cocos2dx_3d_Sprite3D_genMaterial, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAttachNode", js_cocos2dx_3d_Sprite3D_removeAttachNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSkeleton", js_cocos2dx_3d_Sprite3D_getSkeleton, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setForceDepthWrite", js_cocos2dx_3d_Sprite3D_setForceDepthWrite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMeshByName", js_cocos2dx_3d_Sprite3D_getMeshByName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_3d_Sprite3D_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_3d_Sprite3D_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocos2d_Sprite3D_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_Sprite3D_class,
        js_cocos2dx_3d_Sprite3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Sprite3D_prototype);
    jsb_register_class<cocos2d::Sprite3D>(cx, jsb_cocos2d_Sprite3D_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { jsb.Sprite3D.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_Sprite3DCache_class;
JSObject *jsb_cocos2d_Sprite3DCache_prototype;

bool js_cocos2dx_3d_Sprite3DCache_removeSprite3DData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3DCache* cobj = (cocos2d::Sprite3DCache *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3DCache_removeSprite3DData : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Sprite3DCache_removeSprite3DData : Error processing arguments");
        cobj->removeSprite3DData(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3DCache_removeSprite3DData : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Sprite3DCache_removeAllSprite3DData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Sprite3DCache* cobj = (cocos2d::Sprite3DCache *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Sprite3DCache_removeAllSprite3DData : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllSprite3DData();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3DCache_removeAllSprite3DData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Sprite3DCache_destroyInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Sprite3DCache::destroyInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3DCache_destroyInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Sprite3DCache_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        cocos2d::Sprite3DCache* ret = cocos2d::Sprite3DCache::getInstance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite3DCache>(cx, (cocos2d::Sprite3DCache*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Sprite3DCache_getInstance : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_3d_Sprite3DCache(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Sprite3DCache_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Sprite3DCache_class->name = "Sprite3DCache";
    jsb_cocos2d_Sprite3DCache_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Sprite3DCache_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Sprite3DCache_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Sprite3DCache_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Sprite3DCache_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Sprite3DCache_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Sprite3DCache_class->convert = JS_ConvertStub;
    jsb_cocos2d_Sprite3DCache_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Sprite3DCache_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("removeSprite3DData", js_cocos2dx_3d_Sprite3DCache_removeSprite3DData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllSprite3DData", js_cocos2dx_3d_Sprite3DCache_removeAllSprite3DData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destroyInstance", js_cocos2dx_3d_Sprite3DCache_destroyInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_3d_Sprite3DCache_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Sprite3DCache_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_Sprite3DCache_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Sprite3DCache_prototype);
    jsb_register_class<cocos2d::Sprite3DCache>(cx, jsb_cocos2d_Sprite3DCache_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocos2d_Terrain_class;
JSObject *jsb_cocos2d_Terrain_prototype;

bool js_cocos2dx_3d_Terrain_initHeightMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_initHeightMap : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_initHeightMap : Error processing arguments");
        bool ret = cobj->initHeightMap(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_initHeightMap : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setMaxDetailMapAmount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setMaxDetailMapAmount : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setMaxDetailMapAmount : Error processing arguments");
        cobj->setMaxDetailMapAmount(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setMaxDetailMapAmount : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setDrawWire(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setDrawWire : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setDrawWire : Error processing arguments");
        cobj->setDrawWire(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setDrawWire : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setDetailMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setDetailMap : Invalid Native Object");
    if (argc == 2) {
        unsigned int arg0 = 0;
        cocos2d::Terrain::DetailMap arg1;
        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
        #pragma warning NO CONVERSION TO NATIVE FOR DetailMap
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setDetailMap : Error processing arguments");
        cobj->setDetailMap(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setDetailMap : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Terrain_resetHeightMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_resetHeightMap : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_resetHeightMap : Error processing arguments");
        cobj->resetHeightMap(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_resetHeightMap : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setLightDir(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setLightDir : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setLightDir : Error processing arguments");
        cobj->setLightDir(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setLightDir : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setAlphaMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setAlphaMap : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Texture2D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setAlphaMap : Error processing arguments");
        cobj->setAlphaMap(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setAlphaMap : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setSkirtHeightRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setSkirtHeightRatio : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setSkirtHeightRatio : Error processing arguments");
        cobj->setSkirtHeightRatio(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setSkirtHeightRatio : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_convertToTerrainSpace(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_convertToTerrainSpace : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_convertToTerrainSpace : Error processing arguments");
        cocos2d::Vec2 ret = cobj->convertToTerrainSpace(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_convertToTerrainSpace : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_initTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_initTextures : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->initTextures();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_initTextures : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Terrain_initProperties(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_initProperties : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->initProperties();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_initProperties : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Terrain_getHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::Terrain* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getHeight : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Vec2 arg0;
            ok &= jsval_to_vector2(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            double ret = cobj->getHeight(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = DOUBLE_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Vec2 arg0;
            ok &= jsval_to_vector2(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Vec3*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            double ret = cobj->getHeight(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = DOUBLE_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            double ret = cobj->getHeight(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = DOUBLE_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
            if (!ok) { ok = true; break; }
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Vec3*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            double ret = cobj->getHeight(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            jsret = DOUBLE_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getHeight : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Terrain_initWithTerrainData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_initWithTerrainData : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Terrain::TerrainData arg0;
        cocos2d::Terrain::CrackFixedType arg1;
        ok &= jsval_to_TerrainData(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_initWithTerrainData : Error processing arguments");
        bool ret = cobj->initWithTerrainData(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_initWithTerrainData : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Terrain_setLODDistance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setLODDistance : Invalid Native Object");
    if (argc == 3) {
        double arg0 = 0;
        double arg1 = 0;
        double arg2 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setLODDistance : Error processing arguments");
        cobj->setLODDistance(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setLODDistance : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_3d_Terrain_getTerrainSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getTerrainSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getTerrainSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getTerrainSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Terrain_getIntersectionPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::Terrain* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getIntersectionPoint : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Ray arg0;
            ok &= jsval_to_ray(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 arg1;
            ok &= jsval_to_vector3(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->getIntersectionPoint(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Ray arg0;
            ok &= jsval_to_ray(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Vec3 ret = cobj->getIntersectionPoint(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = vector3_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getIntersectionPoint : wrong number of arguments");
    return false;
}
bool js_cocos2dx_3d_Terrain_getNormal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getNormal : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        int arg1 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_getNormal : Error processing arguments");
        cocos2d::Vec3 ret = cobj->getNormal(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = vector3_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getNormal : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Terrain_reload(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_reload : Invalid Native Object");
    if (argc == 0) {
        cobj->reload();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_reload : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Terrain_getImageHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getImageHeight : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        int arg1 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_getImageHeight : Error processing arguments");
        double ret = cobj->getImageHeight(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getImageHeight : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Terrain_setLightMap(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setLightMap : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setLightMap : Error processing arguments");
        cobj->setLightMap(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setLightMap : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_setIsEnableFrustumCull(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_setIsEnableFrustumCull : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Terrain_setIsEnableFrustumCull : Error processing arguments");
        cobj->setIsEnableFrustumCull(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_setIsEnableFrustumCull : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Terrain_getMinHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getMinHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMinHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getMinHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Terrain_getMaxHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Terrain* cobj = (cocos2d::Terrain *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Terrain_getMaxHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaxHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Terrain_getMaxHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Terrain_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Terrain* cobj = new (std::nothrow) cocos2d::Terrain();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Terrain>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::Terrain"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_register_cocos2dx_3d_Terrain(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Terrain_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Terrain_class->name = "Terrain";
    jsb_cocos2d_Terrain_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Terrain_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Terrain_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Terrain_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Terrain_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Terrain_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Terrain_class->convert = JS_ConvertStub;
    jsb_cocos2d_Terrain_class->finalize = jsb_ref_finalize;
    jsb_cocos2d_Terrain_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initHeightMap", js_cocos2dx_3d_Terrain_initHeightMap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxDetailMapAmount", js_cocos2dx_3d_Terrain_setMaxDetailMapAmount, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDrawWire", js_cocos2dx_3d_Terrain_setDrawWire, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDetailMap", js_cocos2dx_3d_Terrain_setDetailMap, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resetHeightMap", js_cocos2dx_3d_Terrain_resetHeightMap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLightDir", js_cocos2dx_3d_Terrain_setLightDir, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAlphaMap", js_cocos2dx_3d_Terrain_setAlphaMap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkirtHeightRatio", js_cocos2dx_3d_Terrain_setSkirtHeightRatio, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("convertToTerrainSpace", js_cocos2dx_3d_Terrain_convertToTerrainSpace, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initTextures", js_cocos2dx_3d_Terrain_initTextures, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initProperties", js_cocos2dx_3d_Terrain_initProperties, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHeight", js_cocos2dx_3d_Terrain_getHeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithTerrainData", js_cocos2dx_3d_Terrain_initWithTerrainData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLODDistance", js_cocos2dx_3d_Terrain_setLODDistance, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTerrainSize", js_cocos2dx_3d_Terrain_getTerrainSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIntersectionPoint", js_cocos2dx_3d_Terrain_getIntersectionPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNormal", js_cocos2dx_3d_Terrain_getNormal, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reload", js_cocos2dx_3d_Terrain_reload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getImageHeight", js_cocos2dx_3d_Terrain_getImageHeight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLightMap", js_cocos2dx_3d_Terrain_setLightMap, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsEnableFrustumCull", js_cocos2dx_3d_Terrain_setIsEnableFrustumCull, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMinHeight", js_cocos2dx_3d_Terrain_getMinHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxHeight", js_cocos2dx_3d_Terrain_getMaxHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocos2d_Terrain_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_Terrain_class,
        js_cocos2dx_3d_Terrain_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Terrain_prototype);
    jsb_register_class<cocos2d::Terrain>(cx, jsb_cocos2d_Terrain_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_Bundle3D_class;
JSObject *jsb_cocos2d_Bundle3D_prototype;

bool js_cocos2dx_3d_Bundle3D_load(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_load : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_load : Error processing arguments");
        bool ret = cobj->load(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_load : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_loadSkinData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_loadSkinData : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::SkinData* arg1 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        #pragma warning NO CONVERSION TO NATIVE FOR SkinData*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadSkinData : Error processing arguments");
        bool ret = cobj->loadSkinData(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_loadSkinData : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_clear(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_clear : Invalid Native Object");
    if (argc == 0) {
        cobj->clear();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_clear : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_loadMaterials(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_loadMaterials : Invalid Native Object");
    if (argc == 1) {
        cocos2d::MaterialDatas arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadMaterials : Error processing arguments");
        bool ret = cobj->loadMaterials(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_loadMaterials : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_loadMeshDatas(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_loadMeshDatas : Invalid Native Object");
    if (argc == 1) {
        cocos2d::MeshDatas arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR MeshDatas
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadMeshDatas : Error processing arguments");
        bool ret = cobj->loadMeshDatas(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_loadMeshDatas : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_loadNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_loadNodes : Invalid Native Object");
    if (argc == 1) {
        cocos2d::NodeDatas arg0;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeDatas
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadNodes : Error processing arguments");
        bool ret = cobj->loadNodes(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_loadNodes : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_loadAnimationData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Bundle3D* cobj = (cocos2d::Bundle3D *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_3d_Bundle3D_loadAnimationData : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::Animation3DData* arg1 = nullptr;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        #pragma warning NO CONVERSION TO NATIVE FOR Animation3DData*
		ok = false;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadAnimationData : Error processing arguments");
        bool ret = cobj->loadAnimationData(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_loadAnimationData : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_3d_Bundle3D_createBundle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        cocos2d::Bundle3D* ret = cocos2d::Bundle3D::createBundle();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Bundle3D>(cx, (cocos2d::Bundle3D*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_createBundle : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Bundle3D_destroyBundle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Bundle3D* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Bundle3D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_destroyBundle : Error processing arguments");
        cocos2d::Bundle3D::destroyBundle(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_destroyBundle : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Bundle3D_loadObj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        cocos2d::MeshDatas arg0;
        cocos2d::MaterialDatas arg1;
        cocos2d::NodeDatas arg2;
        std::string arg3;
        #pragma warning NO CONVERSION TO NATIVE FOR MeshDatas
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeDatas
		ok = false;
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadObj : Error processing arguments");

        bool ret = cocos2d::Bundle3D::loadObj(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 5) {
        cocos2d::MeshDatas arg0;
        cocos2d::MaterialDatas arg1;
        cocos2d::NodeDatas arg2;
        std::string arg3;
        const char* arg4 = nullptr;
        #pragma warning NO CONVERSION TO NATIVE FOR MeshDatas
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR MaterialDatas
		ok = false;
        #pragma warning NO CONVERSION TO NATIVE FOR NodeDatas
		ok = false;
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        std::string arg4_tmp; ok &= jsval_to_std_string(cx, args.get(4), &arg4_tmp); arg4 = arg4_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_3d_Bundle3D_loadObj : Error processing arguments");

        bool ret = cocos2d::Bundle3D::loadObj(arg0, arg1, arg2, arg3, arg4);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_3d_Bundle3D_loadObj : wrong number of arguments");
    return false;
}

bool js_cocos2dx_3d_Bundle3D_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::Bundle3D* cobj = new (std::nothrow) cocos2d::Bundle3D();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::Bundle3D>(cobj);

    // link the native object with the javascript object
    JS::RootedObject proto(cx, typeClass->proto.ref());
    JS::RootedObject parent(cx, typeClass->parentProto.ref());
    JS::RootedObject jsobj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    js_proxy_t* p = jsb_new_proxy(cobj, jsobj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::Bundle3D");
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_cocos2d_Bundle3D_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Bundle3D)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy) {
        cocos2d::Bundle3D *nobj = static_cast<cocos2d::Bundle3D *>(jsproxy->ptr);
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        if (nobj) {
            jsb_remove_proxy(nproxy, jsproxy);
            delete nobj;
        }
        else
            jsb_remove_proxy(nullptr, jsproxy);
    }
}
void js_register_cocos2dx_3d_Bundle3D(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_Bundle3D_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_Bundle3D_class->name = "Bundle3D";
    jsb_cocos2d_Bundle3D_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_Bundle3D_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_Bundle3D_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_Bundle3D_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_Bundle3D_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_Bundle3D_class->resolve = JS_ResolveStub;
    jsb_cocos2d_Bundle3D_class->convert = JS_ConvertStub;
    jsb_cocos2d_Bundle3D_class->finalize = js_cocos2d_Bundle3D_finalize;
    jsb_cocos2d_Bundle3D_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("load", js_cocos2dx_3d_Bundle3D_load, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadSkinData", js_cocos2dx_3d_Bundle3D_loadSkinData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clear", js_cocos2dx_3d_Bundle3D_clear, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadMaterials", js_cocos2dx_3d_Bundle3D_loadMaterials, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadMeshDatas", js_cocos2dx_3d_Bundle3D_loadMeshDatas, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadNodes", js_cocos2dx_3d_Bundle3D_loadNodes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadAnimationData", js_cocos2dx_3d_Bundle3D_loadAnimationData, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("createBundle", js_cocos2dx_3d_Bundle3D_createBundle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("destroyBundle", js_cocos2dx_3d_Bundle3D_destroyBundle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadObj", js_cocos2dx_3d_Bundle3D_loadObj, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_Bundle3D_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_Bundle3D_class,
        js_cocos2dx_3d_Bundle3D_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_cocos2d_Bundle3D_prototype);
    jsb_register_class<cocos2d::Bundle3D>(cx, jsb_cocos2d_Bundle3D_class, proto, JS::NullPtr());
}

void register_all_cocos2dx_3d(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "jsb", &ns);

    js_register_cocos2dx_3d_Animate3D(cx, ns);
    js_register_cocos2dx_3d_Sprite3D(cx, ns);
    js_register_cocos2dx_3d_AttachNode(cx, ns);
    js_register_cocos2dx_3d_TextureCube(cx, ns);
    js_register_cocos2dx_3d_Sprite3DCache(cx, ns);
    js_register_cocos2dx_3d_Terrain(cx, ns);
    js_register_cocos2dx_3d_Skybox(cx, ns);
    js_register_cocos2dx_3d_Bundle3D(cx, ns);
    js_register_cocos2dx_3d_Skeleton3D(cx, ns);
    js_register_cocos2dx_3d_BillBoard(cx, ns);
    js_register_cocos2dx_3d_Animation3D(cx, ns);
    js_register_cocos2dx_3d_Mesh(cx, ns);
}

