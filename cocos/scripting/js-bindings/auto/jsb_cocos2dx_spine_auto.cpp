#include "jsb_cocos2dx_spine_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "spine-cocos2dx.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JSObject* global = ScriptingCore::getInstance()->getGlobalObject();
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && JSVAL_TO_BOOLEAN(initializing);
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;    
}
JSClass  *jsb_spine_SkeletonRenderer_class;
JSObject *jsb_spine_SkeletonRenderer_prototype;

bool js_cocos2dx_spine_SkeletonRenderer_setTimeScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setTimeScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setTimeScale : Error processing arguments");
        cobj->setTimeScale(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setTimeScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_isOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_isOpacityModifyRGB : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isOpacityModifyRGB();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_isOpacityModifyRGB : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_drawSkeleton(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_drawSkeleton : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Mat4 arg0;
        unsigned int arg1;
        ok &= jsval_to_matrix(cx, argv[0], &arg0);
        ok &= jsval_to_uint32(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_drawSkeleton : Error processing arguments");
        cobj->drawSkeleton(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_drawSkeleton : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled : Error processing arguments");
        cobj->setDebugSlotsEnabled(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_getDebugSlotsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_getDebugSlotsEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getDebugSlotsEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_getDebugSlotsEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setBonesToSetupPose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setBonesToSetupPose : Invalid Native Object");
    if (argc == 0) {
        cobj->setBonesToSetupPose();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setBonesToSetupPose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setSlotsToSetupPose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setSlotsToSetupPose : Invalid Native Object");
    if (argc == 0) {
        cobj->setSlotsToSetupPose();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setSlotsToSetupPose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setAttachment(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setAttachment : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setAttachment : Error processing arguments");
        bool ret = cobj->setAttachment(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setAttachment : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setSkin(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setSkin : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setSkin : Error processing arguments");
        bool ret = cobj->setSkin(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setSkin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setToSetupPose(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setToSetupPose : Invalid Native Object");
    if (argc == 0) {
        cobj->setToSetupPose();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setToSetupPose : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_updateWorldTransform(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_updateWorldTransform : Invalid Native Object");
    if (argc == 0) {
        cobj->updateWorldTransform();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_updateWorldTransform : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setOpacityModifyRGB(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setOpacityModifyRGB : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setOpacityModifyRGB : Error processing arguments");
        cobj->setOpacityModifyRGB(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setOpacityModifyRGB : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(JS::RootedValue(cx, argv[0]));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled : Error processing arguments");
        cobj->setDebugBonesEnabled(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_getSkeleton(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_getSkeleton : Invalid Native Object");
    if (argc == 0) {
        spSkeleton* ret = cobj->getSkeleton();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR spSkeleton*;
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_getSkeleton : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_getDebugBonesEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_getDebugBonesEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getDebugBonesEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_getDebugBonesEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonRenderer_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_getTimeScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonRenderer* cobj = (spine::SkeletonRenderer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonRenderer_getTimeScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTimeScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_getTimeScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonRenderer_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, argv[1], &arg1);
            if (!ok) { ok = true; break; }
            spine::SkeletonRenderer* ret = spine::SkeletonRenderer::createWithFile(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonRenderer>(cx, (spine::SkeletonRenderer*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, argv[1], &arg1);
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
            if (!ok) { ok = true; break; }
            spine::SkeletonRenderer* ret = spine::SkeletonRenderer::createWithFile(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonRenderer>(cx, (spine::SkeletonRenderer*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            spAtlas* arg1;
            #pragma warning NO CONVERSION TO NATIVE FOR spAtlas*
			ok = false;
            if (!ok) { ok = true; break; }
            spine::SkeletonRenderer* ret = spine::SkeletonRenderer::createWithFile(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonRenderer>(cx, (spine::SkeletonRenderer*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            spAtlas* arg1;
            #pragma warning NO CONVERSION TO NATIVE FOR spAtlas*
			ok = false;
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
            if (!ok) { ok = true; break; }
            spine::SkeletonRenderer* ret = spine::SkeletonRenderer::createWithFile(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonRenderer>(cx, (spine::SkeletonRenderer*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonRenderer_createWithFile : wrong number of arguments");
    return false;
}

extern JSObject *jsb_cocos2d_Node_prototype;

void js_spine_SkeletonRenderer_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SkeletonRenderer)", obj);
}

void js_register_cocos2dx_spine_SkeletonRenderer(JSContext *cx, JSObject *global) {
    jsb_spine_SkeletonRenderer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_spine_SkeletonRenderer_class->name = "Skeleton";
    jsb_spine_SkeletonRenderer_class->addProperty = JS_PropertyStub;
    jsb_spine_SkeletonRenderer_class->delProperty = JS_DeletePropertyStub;
    jsb_spine_SkeletonRenderer_class->getProperty = JS_PropertyStub;
    jsb_spine_SkeletonRenderer_class->setProperty = JS_StrictPropertyStub;
    jsb_spine_SkeletonRenderer_class->enumerate = JS_EnumerateStub;
    jsb_spine_SkeletonRenderer_class->resolve = JS_ResolveStub;
    jsb_spine_SkeletonRenderer_class->convert = JS_ConvertStub;
    jsb_spine_SkeletonRenderer_class->finalize = js_spine_SkeletonRenderer_finalize;
    jsb_spine_SkeletonRenderer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setTimeScale", js_cocos2dx_spine_SkeletonRenderer_setTimeScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isOpacityModifyRGB", js_cocos2dx_spine_SkeletonRenderer_isOpacityModifyRGB, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("drawSkeleton", js_cocos2dx_spine_SkeletonRenderer_drawSkeleton, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugSlotsEnabled", js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDebugSlotsEnabled", js_cocos2dx_spine_SkeletonRenderer_getDebugSlotsEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBonesToSetupPose", js_cocos2dx_spine_SkeletonRenderer_setBonesToSetupPose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSlotsToSetupPose", js_cocos2dx_spine_SkeletonRenderer_setSlotsToSetupPose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAttachment", js_cocos2dx_spine_SkeletonRenderer_setAttachment, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_spine_SkeletonRenderer_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSkin", js_cocos2dx_spine_SkeletonRenderer_setSkin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setToSetupPose", js_cocos2dx_spine_SkeletonRenderer_setToSetupPose, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateWorldTransform", js_cocos2dx_spine_SkeletonRenderer_updateWorldTransform, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOpacityModifyRGB", js_cocos2dx_spine_SkeletonRenderer_setOpacityModifyRGB, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugBonesEnabled", js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSkeleton", js_cocos2dx_spine_SkeletonRenderer_getSkeleton, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDebugBonesEnabled", js_cocos2dx_spine_SkeletonRenderer_getDebugBonesEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_spine_SkeletonRenderer_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTimeScale", js_cocos2dx_spine_SkeletonRenderer_getTimeScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_spine_SkeletonRenderer_createWithFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_spine_SkeletonRenderer_prototype = JS_InitClass(
        cx, global,
        jsb_cocos2d_Node_prototype,
        jsb_spine_SkeletonRenderer_class,
        dummy_constructor<spine::SkeletonRenderer>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Skeleton", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<spine::SkeletonRenderer> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_spine_SkeletonRenderer_class;
        p->proto = jsb_spine_SkeletonRenderer_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_spine_SkeletonAnimation_class;
JSObject *jsb_spine_SkeletonAnimation_prototype;

bool js_cocos2dx_spine_SkeletonAnimation_setStartListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setStartListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (int)> arg0;
        do {
		    if(JS_TypeOfValue(cx, argv[0]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
		        auto lambda = [=](int larg0) -> void {
		            jsval largv[1];
		            largv[0] = int32_to_jsval(cx, larg0);
		            jsval rval;
		            bool ok = func->invoke(1, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setStartListener : Error processing arguments");
        cobj->setStartListener(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setStartListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener : Invalid Native Object");
    if (argc == 2) {
        spTrackEntry* arg0;
        std::function<void (int, spEvent *)> arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR spTrackEntry*
		ok = false;
        do {
		    if(JS_TypeOfValue(cx, argv[1]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[1]));
		        auto lambda = [=](int larg0, spEvent* larg1) -> void {
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            do {
		            if (larg1) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<spEvent>(cx, (spEvent*)larg1);
		                largv[1] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[1] = JSVAL_NULL;
		            }
		        } while (0);
		            jsval rval;
		            bool ok = func->invoke(2, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener : Error processing arguments");
        cobj->setTrackEventListener(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_getState : Invalid Native Object");
    if (argc == 0) {
        spAnimationState* ret = cobj->getState();
        jsval jsret = JSVAL_NULL;
        #pragma warning NO CONVERSION FROM NATIVE FOR spAnimationState*;
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_getState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener : Invalid Native Object");
    if (argc == 2) {
        spTrackEntry* arg0;
        std::function<void (int, int)> arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR spTrackEntry*
		ok = false;
        do {
		    if(JS_TypeOfValue(cx, argv[1]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[1]));
		        auto lambda = [=](int larg0, int larg1) -> void {
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            largv[1] = int32_to_jsval(cx, larg1);
		            jsval rval;
		            bool ok = func->invoke(2, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener : Error processing arguments");
        cobj->setTrackCompleteListener(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent : Invalid Native Object");
    if (argc == 4) {
        int arg0;
        spEventType arg1;
        spEvent* arg2;
        int arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        #pragma warning NO CONVERSION TO NATIVE FOR spEvent*
		ok = false;
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent : Error processing arguments");
        cobj->onTrackEntryEvent(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener : Invalid Native Object");
    if (argc == 2) {
        spTrackEntry* arg0;
        std::function<void (int)> arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR spTrackEntry*
		ok = false;
        do {
		    if(JS_TypeOfValue(cx, argv[1]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[1]));
		        auto lambda = [=](int larg0) -> void {
		            jsval largv[1];
		            largv[0] = int32_to_jsval(cx, larg0);
		            jsval rval;
		            bool ok = func->invoke(1, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener : Error processing arguments");
        cobj->setTrackStartListener(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_update(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_update : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_update : Error processing arguments");
        cobj->update(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_update : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setCompleteListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setCompleteListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (int, int)> arg0;
        do {
		    if(JS_TypeOfValue(cx, argv[0]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
		        auto lambda = [=](int larg0, int larg1) -> void {
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            largv[1] = int32_to_jsval(cx, larg1);
		            jsval rval;
		            bool ok = func->invoke(2, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setCompleteListener : Error processing arguments");
        cobj->setCompleteListener(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setCompleteListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener : Invalid Native Object");
    if (argc == 2) {
        spTrackEntry* arg0;
        std::function<void (int)> arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR spTrackEntry*
		ok = false;
        do {
		    if(JS_TypeOfValue(cx, argv[1]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[1]));
		        auto lambda = [=](int larg0) -> void {
		            jsval largv[1];
		            largv[0] = int32_to_jsval(cx, larg0);
		            jsval rval;
		            bool ok = func->invoke(1, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener : Error processing arguments");
        cobj->setTrackEndListener(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setEventListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (int, spEvent *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, argv[0]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
		        auto lambda = [=](int larg0, spEvent* larg1) -> void {
		            jsval largv[2];
		            largv[0] = int32_to_jsval(cx, larg0);
		            do {
		            if (larg1) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<spEvent>(cx, (spEvent*)larg1);
		                largv[1] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[1] = JSVAL_NULL;
		            }
		        } while (0);
		            jsval rval;
		            bool ok = func->invoke(2, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setEventListener : Error processing arguments");
        cobj->setEventListener(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setEventListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setMix(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setMix : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setMix : Error processing arguments");
        cobj->setMix(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setMix : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_setEndListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setEndListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (int)> arg0;
        do {
		    if(JS_TypeOfValue(cx, argv[0]) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), argv[0]));
		        auto lambda = [=](int larg0) -> void {
		            jsval largv[1];
		            largv[0] = int32_to_jsval(cx, larg0);
		            jsval rval;
		            bool ok = func->invoke(1, &largv[0], rval);
		            if (!ok && JS_IsExceptionPending(cx)) {
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_setEndListener : Error processing arguments");
        cobj->setEndListener(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_setEndListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_clearTracks(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_clearTracks : Invalid Native Object");
    if (argc == 0) {
        cobj->clearTracks();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_clearTracks : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_clearTrack(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_clearTrack : Invalid Native Object");
    if (argc == 0) {
        cobj->clearTrack();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_clearTrack : Error processing arguments");
        cobj->clearTrack(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_clearTrack : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    spine::SkeletonAnimation* cobj = (spine::SkeletonAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent : Invalid Native Object");
    if (argc == 4) {
        int arg0;
        spEventType arg1;
        spEvent* arg2;
        int arg3;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
        #pragma warning NO CONVERSION TO NATIVE FOR spEvent*
		ok = false;
        ok &= jsval_to_int32(cx, argv[3], (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent : Error processing arguments");
        cobj->onAnimationStateEvent(arg0, arg1, arg2, arg3);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_spine_SkeletonAnimation_createWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, argv[1], &arg1);
            if (!ok) { ok = true; break; }
            spine::SkeletonAnimation* ret = spine::SkeletonAnimation::createWithFile(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonAnimation>(cx, (spine::SkeletonAnimation*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, argv[1], &arg1);
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
            if (!ok) { ok = true; break; }
            spine::SkeletonAnimation* ret = spine::SkeletonAnimation::createWithFile(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonAnimation>(cx, (spine::SkeletonAnimation*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            spAtlas* arg1;
            #pragma warning NO CONVERSION TO NATIVE FOR spAtlas*
			ok = false;
            if (!ok) { ok = true; break; }
            spine::SkeletonAnimation* ret = spine::SkeletonAnimation::createWithFile(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonAnimation>(cx, (spine::SkeletonAnimation*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, argv[0], &arg0);
            if (!ok) { ok = true; break; }
            spAtlas* arg1;
            #pragma warning NO CONVERSION TO NATIVE FOR spAtlas*
			ok = false;
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[2]), &arg2);
            if (!ok) { ok = true; break; }
            spine::SkeletonAnimation* ret = spine::SkeletonAnimation::createWithFile(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<spine::SkeletonAnimation>(cx, (spine::SkeletonAnimation*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            JS_SET_RVAL(cx, vp, jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_spine_SkeletonAnimation_createWithFile : wrong number of arguments");
    return false;
}

extern JSObject *jsb_spine_SkeletonRenderer_prototype;

void js_spine_SkeletonAnimation_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SkeletonAnimation)", obj);
}

void js_register_cocos2dx_spine_SkeletonAnimation(JSContext *cx, JSObject *global) {
    jsb_spine_SkeletonAnimation_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_spine_SkeletonAnimation_class->name = "SkeletonAnimation";
    jsb_spine_SkeletonAnimation_class->addProperty = JS_PropertyStub;
    jsb_spine_SkeletonAnimation_class->delProperty = JS_DeletePropertyStub;
    jsb_spine_SkeletonAnimation_class->getProperty = JS_PropertyStub;
    jsb_spine_SkeletonAnimation_class->setProperty = JS_StrictPropertyStub;
    jsb_spine_SkeletonAnimation_class->enumerate = JS_EnumerateStub;
    jsb_spine_SkeletonAnimation_class->resolve = JS_ResolveStub;
    jsb_spine_SkeletonAnimation_class->convert = JS_ConvertStub;
    jsb_spine_SkeletonAnimation_class->finalize = js_spine_SkeletonAnimation_finalize;
    jsb_spine_SkeletonAnimation_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setStartListener", js_cocos2dx_spine_SkeletonAnimation_setStartListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTrackEventListener", js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_cocos2dx_spine_SkeletonAnimation_getState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTrackCompleteListener", js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTrackEntryEvent", js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTrackStartListener", js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("update", js_cocos2dx_spine_SkeletonAnimation_update, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCompleteListener", js_cocos2dx_spine_SkeletonAnimation_setCompleteListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTrackEndListener", js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEventListener", js_cocos2dx_spine_SkeletonAnimation_setEventListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMix", js_cocos2dx_spine_SkeletonAnimation_setMix, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEndListener", js_cocos2dx_spine_SkeletonAnimation_setEndListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearTracks", js_cocos2dx_spine_SkeletonAnimation_clearTracks, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clearTrack", js_cocos2dx_spine_SkeletonAnimation_clearTrack, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onAnimationStateEvent", js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_spine_SkeletonAnimation_createWithFile, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_spine_SkeletonAnimation_prototype = JS_InitClass(
        cx, global,
        jsb_spine_SkeletonRenderer_prototype,
        jsb_spine_SkeletonAnimation_class,
        dummy_constructor<spine::SkeletonAnimation>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SkeletonAnimation", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<spine::SkeletonAnimation> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_spine_SkeletonAnimation_class;
        p->proto = jsb_spine_SkeletonAnimation_prototype;
        p->parentProto = jsb_spine_SkeletonRenderer_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_spine(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "sp", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "sp", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_cocos2dx_spine_SkeletonRenderer(cx, obj);
    js_register_cocos2dx_spine_SkeletonAnimation(cx, obj);
}

