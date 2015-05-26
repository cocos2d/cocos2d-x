#include "jsb_cocos2dx_experimental.hpp"
#include "cocos2d_specifics.hpp"
#include "SpritePolygon.h"

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
JSClass  *jsb_cocos2d_experimental_SpritePolygon_class;
JSObject *jsb_cocos2d_experimental_SpritePolygon_prototype;

bool js_cocos2dx_experimental_SpritePolygon_setTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::experimental::SpritePolygon* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_setTexture : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Texture2D* arg0;
            do {
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
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

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_setTexture : wrong number of arguments");
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_initWithTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_initWithTexture : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Texture2D* arg0;
        do {
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Texture2D*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_SpritePolygon_initWithTexture : Error processing arguments");
        bool ret = cobj->initWithTexture(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_initWithTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_showDebug(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_showDebug : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_SpritePolygon_showDebug : Error processing arguments");
        cobj->showDebug(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_showDebug : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_getTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_getTexture : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Texture2D* ret = cobj->getTexture();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Texture2D>(cx, (cocos2d::Texture2D*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_getTexture : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_getArea(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_getArea : Invalid Native Object");
    if (argc == 0) {
        const float ret = cobj->getArea();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_getArea : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_initWithMarching(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_initWithMarching : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        cocos2d::Rect arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_experimental_SpritePolygon_initWithMarching : Error processing arguments");
        bool ret = cobj->initWithMarching(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_initWithMarching : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_getVertCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_getVertCount : Invalid Native Object");
    if (argc == 0) {
        const ssize_t ret = cobj->getVertCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_getVertCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_experimental_SpritePolygon_getTrianglesCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::experimental::SpritePolygon* cobj = (cocos2d::experimental::SpritePolygon *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_experimental_SpritePolygon_getTrianglesCount : Invalid Native Object");
    if (argc == 0) {
        const ssize_t ret = cobj->getTrianglesCount();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_experimental_SpritePolygon_getTrianglesCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_experimental_SpritePolygon_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SpritePolygon)", obj);
}

void js_register_cocos2dx_experimental_SpritePolygon(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_experimental_SpritePolygon_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_experimental_SpritePolygon_class->name = "SpritePolygon";
    jsb_cocos2d_experimental_SpritePolygon_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_SpritePolygon_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_experimental_SpritePolygon_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_experimental_SpritePolygon_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_experimental_SpritePolygon_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_experimental_SpritePolygon_class->resolve = JS_ResolveStub;
    jsb_cocos2d_experimental_SpritePolygon_class->convert = JS_ConvertStub;
    jsb_cocos2d_experimental_SpritePolygon_class->finalize = js_cocos2d_experimental_SpritePolygon_finalize;
    jsb_cocos2d_experimental_SpritePolygon_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setTexture", js_cocos2dx_experimental_SpritePolygon_setTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithTexture", js_cocos2dx_experimental_SpritePolygon_initWithTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showDebug", js_cocos2dx_experimental_SpritePolygon_showDebug, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTexture", js_cocos2dx_experimental_SpritePolygon_getTexture, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getArea", js_cocos2dx_experimental_SpritePolygon_getArea, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithMarching", js_cocos2dx_experimental_SpritePolygon_initWithMarching, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVertCount", js_cocos2dx_experimental_SpritePolygon_getVertCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTrianglesCount", js_cocos2dx_experimental_SpritePolygon_getTrianglesCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_experimental_SpritePolygon_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_cocos2d_experimental_SpritePolygon_class,
        dummy_constructor<cocos2d::experimental::SpritePolygon>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "SpritePolygon", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::experimental::SpritePolygon> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_experimental_SpritePolygon_class;
        p->proto = jsb_cocos2d_experimental_SpritePolygon_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_experimental(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccexp", &ns);

    js_register_cocos2dx_experimental_SpritePolygon(cx, ns);
}

