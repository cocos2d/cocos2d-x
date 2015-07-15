#include "jsb_cocos2dx_ui_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "CocosGUI.h"

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
JSClass  *jsb_cocos2d_ui_LayoutParameter_class;
JSObject *jsb_cocos2d_ui_LayoutParameter_prototype;

bool js_cocos2dx_ui_LayoutParameter_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutParameter* cobj = (cocos2d::ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutParameter_clone : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::LayoutParameter* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LayoutParameter>(cx, (cocos2d::ui::LayoutParameter*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutParameter_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutParameter_getLayoutType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutParameter* cobj = (cocos2d::ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutParameter_getLayoutType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getLayoutType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutParameter_getLayoutType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutParameter_createCloneInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutParameter* cobj = (cocos2d::ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutParameter_createCloneInstance : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::LayoutParameter* ret = cobj->createCloneInstance();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LayoutParameter>(cx, (cocos2d::ui::LayoutParameter*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutParameter_createCloneInstance : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutParameter_copyProperties(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutParameter* cobj = (cocos2d::ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutParameter_copyProperties : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::LayoutParameter* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::LayoutParameter*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutParameter_copyProperties : Error processing arguments");
        cobj->copyProperties(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutParameter_copyProperties : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::LayoutParameter* ret = cocos2d::ui::LayoutParameter::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LayoutParameter>(cx, (cocos2d::ui::LayoutParameter*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_LayoutParameter_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_LayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::LayoutParameter* cobj = new (std::nothrow) cocos2d::ui::LayoutParameter();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::LayoutParameter> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::LayoutParameter");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_cocos2d_ui_LayoutParameter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LayoutParameter)", obj);
}

void js_register_cocos2dx_ui_LayoutParameter(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_LayoutParameter_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_LayoutParameter_class->name = "LayoutParameter";
    jsb_cocos2d_ui_LayoutParameter_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LayoutParameter_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_LayoutParameter_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LayoutParameter_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_LayoutParameter_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_LayoutParameter_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_LayoutParameter_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_LayoutParameter_class->finalize = js_cocos2d_ui_LayoutParameter_finalize;
    jsb_cocos2d_ui_LayoutParameter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("clone", js_cocos2dx_ui_LayoutParameter_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLayoutType", js_cocos2dx_ui_LayoutParameter_getLayoutType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createCloneInstance", js_cocos2dx_ui_LayoutParameter_createCloneInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("copyProperties", js_cocos2dx_ui_LayoutParameter_copyProperties, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_LayoutParameter_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_LayoutParameter_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_ui_LayoutParameter_class,
        js_cocos2dx_ui_LayoutParameter_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LayoutParameter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::LayoutParameter> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_LayoutParameter_class;
        p->proto = jsb_cocos2d_ui_LayoutParameter_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_LinearLayoutParameter_class;
JSObject *jsb_cocos2d_ui_LinearLayoutParameter_prototype;

bool js_cocos2dx_ui_LinearLayoutParameter_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LinearLayoutParameter* cobj = (cocos2d::ui::LinearLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LinearLayoutParameter_setGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::LinearLayoutParameter::LinearGravity arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LinearLayoutParameter_setGravity : Error processing arguments");
        cobj->setGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LinearLayoutParameter_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LinearLayoutParameter_getGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LinearLayoutParameter* cobj = (cocos2d::ui::LinearLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LinearLayoutParameter_getGravity : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getGravity();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LinearLayoutParameter_getGravity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LinearLayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::LinearLayoutParameter* ret = cocos2d::ui::LinearLayoutParameter::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LinearLayoutParameter>(cx, (cocos2d::ui::LinearLayoutParameter*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_LinearLayoutParameter_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_LinearLayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::LinearLayoutParameter* cobj = new (std::nothrow) cocos2d::ui::LinearLayoutParameter();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::LinearLayoutParameter> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::LinearLayoutParameter");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_LayoutParameter_prototype;

void js_cocos2d_ui_LinearLayoutParameter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LinearLayoutParameter)", obj);
}

void js_register_cocos2dx_ui_LinearLayoutParameter(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_LinearLayoutParameter_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_LinearLayoutParameter_class->name = "LinearLayoutParameter";
    jsb_cocos2d_ui_LinearLayoutParameter_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_LinearLayoutParameter_class->finalize = js_cocos2d_ui_LinearLayoutParameter_finalize;
    jsb_cocos2d_ui_LinearLayoutParameter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setGravity", js_cocos2dx_ui_LinearLayoutParameter_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getGravity", js_cocos2dx_ui_LinearLayoutParameter_getGravity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_LinearLayoutParameter_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_LinearLayoutParameter_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_LayoutParameter_prototype),
        jsb_cocos2d_ui_LinearLayoutParameter_class,
        js_cocos2dx_ui_LinearLayoutParameter_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LinearLayoutParameter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::LinearLayoutParameter> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_LinearLayoutParameter_class;
        p->proto = jsb_cocos2d_ui_LinearLayoutParameter_prototype;
        p->parentProto = jsb_cocos2d_ui_LayoutParameter_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RelativeLayoutParameter_class;
JSObject *jsb_cocos2d_ui_RelativeLayoutParameter_prototype;

bool js_cocos2dx_ui_RelativeLayoutParameter_setAlign(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeLayoutParameter* cobj = (cocos2d::ui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_setAlign : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::RelativeLayoutParameter::RelativeAlign arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_setAlign : Error processing arguments");
        cobj->setAlign(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_setAlign : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_RelativeLayoutParameter_setRelativeToWidgetName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeLayoutParameter* cobj = (cocos2d::ui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_setRelativeToWidgetName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_setRelativeToWidgetName : Error processing arguments");
        cobj->setRelativeToWidgetName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_setRelativeToWidgetName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_RelativeLayoutParameter_getRelativeName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeLayoutParameter* cobj = (cocos2d::ui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_getRelativeName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getRelativeName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_getRelativeName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_RelativeLayoutParameter_getRelativeToWidgetName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeLayoutParameter* cobj = (cocos2d::ui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_getRelativeToWidgetName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getRelativeToWidgetName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_getRelativeToWidgetName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_RelativeLayoutParameter_setRelativeName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeLayoutParameter* cobj = (cocos2d::ui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_setRelativeName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_setRelativeName : Error processing arguments");
        cobj->setRelativeName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_setRelativeName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_RelativeLayoutParameter_getAlign(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeLayoutParameter* cobj = (cocos2d::ui::RelativeLayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeLayoutParameter_getAlign : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getAlign();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_getAlign : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_RelativeLayoutParameter_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::RelativeLayoutParameter* ret = cocos2d::ui::RelativeLayoutParameter::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RelativeLayoutParameter>(cx, (cocos2d::ui::RelativeLayoutParameter*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_RelativeLayoutParameter_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_RelativeLayoutParameter_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RelativeLayoutParameter* cobj = new (std::nothrow) cocos2d::ui::RelativeLayoutParameter();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RelativeLayoutParameter> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RelativeLayoutParameter");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_LayoutParameter_prototype;

void js_cocos2d_ui_RelativeLayoutParameter_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RelativeLayoutParameter)", obj);
}

void js_register_cocos2dx_ui_RelativeLayoutParameter(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RelativeLayoutParameter_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RelativeLayoutParameter_class->name = "RelativeLayoutParameter";
    jsb_cocos2d_ui_RelativeLayoutParameter_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->finalize = js_cocos2d_ui_RelativeLayoutParameter_finalize;
    jsb_cocos2d_ui_RelativeLayoutParameter_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setAlign", js_cocos2dx_ui_RelativeLayoutParameter_setAlign, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRelativeToWidgetName", js_cocos2dx_ui_RelativeLayoutParameter_setRelativeToWidgetName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRelativeName", js_cocos2dx_ui_RelativeLayoutParameter_getRelativeName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRelativeToWidgetName", js_cocos2dx_ui_RelativeLayoutParameter_getRelativeToWidgetName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRelativeName", js_cocos2dx_ui_RelativeLayoutParameter_setRelativeName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAlign", js_cocos2dx_ui_RelativeLayoutParameter_getAlign, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_RelativeLayoutParameter_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_RelativeLayoutParameter_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_LayoutParameter_prototype),
        jsb_cocos2d_ui_RelativeLayoutParameter_class,
        js_cocos2dx_ui_RelativeLayoutParameter_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RelativeLayoutParameter", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RelativeLayoutParameter> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RelativeLayoutParameter_class;
        p->proto = jsb_cocos2d_ui_RelativeLayoutParameter_prototype;
        p->parentProto = jsb_cocos2d_ui_LayoutParameter_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Widget_class;
JSObject *jsb_cocos2d_ui_Widget_prototype;

bool js_cocos2dx_ui_Widget_setLayoutComponentEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setLayoutComponentEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setLayoutComponentEnabled : Error processing arguments");
        cobj->setLayoutComponentEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setLayoutComponentEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setSizePercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setSizePercent : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setSizePercent : Error processing arguments");
        cobj->setSizePercent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setSizePercent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_getCustomSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getCustomSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getCustomSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getCustomSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getLeftBoundary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getLeftBoundary : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLeftBoundary();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getLeftBoundary : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setFlippedX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setFlippedX : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setFlippedX : Error processing arguments");
        cobj->setFlippedX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setFlippedX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setCallbackName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setCallbackName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setCallbackName : Error processing arguments");
        cobj->setCallbackName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setCallbackName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_getVirtualRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getVirtualRenderer : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getVirtualRenderer();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getVirtualRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setPropagateTouchEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setPropagateTouchEvents : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setPropagateTouchEvents : Error processing arguments");
        cobj->setPropagateTouchEvents(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setPropagateTouchEvents : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_isUnifySizeEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isUnifySizeEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isUnifySizeEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isUnifySizeEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getSizePercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getSizePercent : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getSizePercent();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getSizePercent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setPositionPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setPositionPercent : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setPositionPercent : Error processing arguments");
        cobj->setPositionPercent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setPositionPercent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setSwallowTouches(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setSwallowTouches : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setSwallowTouches : Error processing arguments");
        cobj->setSwallowTouches(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setSwallowTouches : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_getLayoutSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getLayoutSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getLayoutSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getLayoutSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setHighlighted(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setHighlighted : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setHighlighted : Error processing arguments");
        cobj->setHighlighted(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setHighlighted : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setPositionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setPositionType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Widget::PositionType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setPositionType : Error processing arguments");
        cobj->setPositionType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setPositionType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isIgnoreContentAdaptWithSize();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getVirtualRendererSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getVirtualRendererSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getVirtualRendererSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getVirtualRendererSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isHighlighted(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isHighlighted : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isHighlighted();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isHighlighted : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getLayoutParameter : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::LayoutParameter* ret = cobj->getLayoutParameter();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LayoutParameter>(cx, (cocos2d::ui::LayoutParameter*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getLayoutParameter : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_addCCSEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_addCCSEventListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (cocos2d::Ref *, int)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](cocos2d::Ref* larg0, int larg1) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            largv[1] = int32_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(2, &largv[0], &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_addCCSEventListener : Error processing arguments");
        cobj->addCCSEventListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_addCCSEventListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_getPositionType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getPositionType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getPositionType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getPositionType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getTopBoundary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getTopBoundary : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTopBoundary();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getTopBoundary : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_ignoreContentAdaptWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_ignoreContentAdaptWithSize : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_ignoreContentAdaptWithSize : Error processing arguments");
        cobj->ignoreContentAdaptWithSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_ignoreContentAdaptWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_findNextFocusedWidget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_findNextFocusedWidget : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::Widget::FocusDirection arg0;
        cocos2d::ui::Widget* arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_findNextFocusedWidget : Error processing arguments");
        cocos2d::ui::Widget* ret = cobj->findNextFocusedWidget(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_findNextFocusedWidget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_Widget_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isFocused(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isFocused : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFocused();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isFocused : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getTouchBeganPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getTouchBeganPosition : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getTouchBeganPosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getTouchBeganPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isTouchEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouchEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getCallbackName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getCallbackName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getCallbackName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getCallbackName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getActionTag : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getActionTag();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getActionTag : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getWorldPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getWorldPosition : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getWorldPosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getWorldPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isFocusEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isFocusEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFocusEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isFocusEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setFocused(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setFocused : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setFocused : Error processing arguments");
        cobj->setFocused(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setFocused : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setActionTag : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setActionTag : Error processing arguments");
        cobj->setActionTag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setActionTag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setTouchEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setTouchEnabled : Error processing arguments");
        cobj->setTouchEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setFlippedY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setFlippedY : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setFlippedY : Error processing arguments");
        cobj->setFlippedY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setFlippedY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_getRightBoundary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getRightBoundary : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRightBoundary();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getRightBoundary : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setBrightStyle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setBrightStyle : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Widget::BrightStyle arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setBrightStyle : Error processing arguments");
        cobj->setBrightStyle(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setBrightStyle : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setLayoutParameter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setLayoutParameter : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::LayoutParameter* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::LayoutParameter*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setLayoutParameter : Error processing arguments");
        cobj->setLayoutParameter(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setLayoutParameter : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_clone(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_clone : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::Widget* ret = cobj->clone();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_clone : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_setFocusEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setFocusEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setFocusEnabled : Error processing arguments");
        cobj->setFocusEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setFocusEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_getBottomBoundary(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getBottomBoundary : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getBottomBoundary();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getBottomBoundary : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isBright(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isBright : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBright();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isBright : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_dispatchFocusEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_dispatchFocusEvent : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::Widget* arg0;
        cocos2d::ui::Widget* arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_dispatchFocusEvent : Error processing arguments");
        cobj->dispatchFocusEvent(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_dispatchFocusEvent : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_Widget_setUnifySizeEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setUnifySizeEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setUnifySizeEnabled : Error processing arguments");
        cobj->setUnifySizeEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setUnifySizeEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_isPropagateTouchEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isPropagateTouchEvents : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPropagateTouchEvents();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isPropagateTouchEvents : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getCurrentFocusedWidget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getCurrentFocusedWidget : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::Widget* ret = cobj->getCurrentFocusedWidget();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getCurrentFocusedWidget : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_hitTest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_hitTest : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_hitTest : Error processing arguments");
        bool ret = cobj->hitTest(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_hitTest : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_isLayoutComponentEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isLayoutComponentEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLayoutComponentEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isLayoutComponentEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_requestFocus(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_requestFocus : Invalid Native Object");
    if (argc == 0) {
        cobj->requestFocus();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_requestFocus : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_updateSizeAndPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Widget* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_updateSizeAndPosition : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->updateSizeAndPosition(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->updateSizeAndPosition();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_updateSizeAndPosition : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Widget_onFocusChange(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_onFocusChange : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::Widget* arg0;
        cocos2d::ui::Widget* arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_onFocusChange : Error processing arguments");
        cobj->onFocusChange(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_onFocusChange : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_Widget_getTouchMovePosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getTouchMovePosition : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getTouchMovePosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getTouchMovePosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getSizeType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getSizeType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getSizeType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getSizeType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getCallbackType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getCallbackType : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getCallbackType();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getCallbackType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getTouchEndPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getTouchEndPosition : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getTouchEndPosition();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getTouchEndPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_getPositionPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_getPositionPercent : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getPositionPercent();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_getPositionPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_propagateTouchEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_propagateTouchEvent : Invalid Native Object");
    if (argc == 3) {
        cocos2d::ui::Widget::TouchEventType arg0;
        cocos2d::ui::Widget* arg1;
        cocos2d::Touch* arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_propagateTouchEvent : Error processing arguments");
        cobj->propagateTouchEvent(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_propagateTouchEvent : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_Widget_addClickEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_addClickEventListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (cocos2d::Ref *)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](cocos2d::Ref* larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            do {
		            if (larg0) {
		                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)larg0);
		                largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
		            } else {
		                largv[0] = JSVAL_NULL;
		            }
		        } while (0);
		            JS::RootedValue rval(cx);
		            bool ok = func->invoke(1, &largv[0], &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_addClickEventListener : Error processing arguments");
        cobj->addClickEventListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_addClickEventListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_isFlippedX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isFlippedX : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFlippedX();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isFlippedX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isFlippedY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isFlippedY : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFlippedY();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isFlippedY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_isClippingParentContainsPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isClippingParentContainsPoint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_isClippingParentContainsPoint : Error processing arguments");
        bool ret = cobj->isClippingParentContainsPoint(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isClippingParentContainsPoint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setSizeType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setSizeType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Widget::SizeType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setSizeType : Error processing arguments");
        cobj->setSizeType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setSizeType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_interceptTouchEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_interceptTouchEvent : Invalid Native Object");
    if (argc == 3) {
        cocos2d::ui::Widget::TouchEventType arg0;
        cocos2d::ui::Widget* arg1;
        cocos2d::Touch* arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(1).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_interceptTouchEvent : Error processing arguments");
        cobj->interceptTouchEvent(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_interceptTouchEvent : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_Widget_setBright(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setBright : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setBright : Error processing arguments");
        cobj->setBright(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setBright : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_setCallbackType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_setCallbackType : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_setCallbackType : Error processing arguments");
        cobj->setCallbackType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_setCallbackType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Widget_isSwallowTouches(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Widget_isSwallowTouches : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isSwallowTouches();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Widget_isSwallowTouches : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Widget_enableDpadNavigation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Widget_enableDpadNavigation : Error processing arguments");
        cocos2d::ui::Widget::enableDpadNavigation(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Widget_enableDpadNavigation : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Widget_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::Widget* ret = cocos2d::ui::Widget::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Widget_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Widget_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::Widget* cobj = new (std::nothrow) cocos2d::ui::Widget();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::Widget> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Widget");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ProtectedNode_prototype;

void js_cocos2d_ui_Widget_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Widget)", obj);
}

static bool js_cocos2d_ui_Widget_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::Widget *nobj = new (std::nothrow) cocos2d::ui::Widget();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Widget");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_Widget(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Widget_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Widget_class->name = "Widget";
    jsb_cocos2d_ui_Widget_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Widget_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Widget_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Widget_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Widget_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Widget_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Widget_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Widget_class->finalize = js_cocos2d_ui_Widget_finalize;
    jsb_cocos2d_ui_Widget_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setLayoutComponentEnabled", js_cocos2dx_ui_Widget_setLayoutComponentEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSizePercent", js_cocos2dx_ui_Widget_setSizePercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCustomSize", js_cocos2dx_ui_Widget_getCustomSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLeftBoundary", js_cocos2dx_ui_Widget_getLeftBoundary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFlippedX", js_cocos2dx_ui_Widget_setFlippedX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCallbackName", js_cocos2dx_ui_Widget_setCallbackName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVirtualRenderer", js_cocos2dx_ui_Widget_getVirtualRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPropagateTouchEvents", js_cocos2dx_ui_Widget_setPropagateTouchEvents, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isUnifySizeEnabled", js_cocos2dx_ui_Widget_isUnifySizeEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSizePercent", js_cocos2dx_ui_Widget_getSizePercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionPercent", js_cocos2dx_ui_Widget_setPositionPercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSwallowTouches", js_cocos2dx_ui_Widget_setSwallowTouches, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLayoutSize", js_cocos2dx_ui_Widget_getLayoutSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHighlighted", js_cocos2dx_ui_Widget_setHighlighted, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionType", js_cocos2dx_ui_Widget_setPositionType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isIgnoreContentAdaptWithSize", js_cocos2dx_ui_Widget_isIgnoreContentAdaptWithSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVirtualRendererSize", js_cocos2dx_ui_Widget_getVirtualRendererSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isHighlighted", js_cocos2dx_ui_Widget_isHighlighted, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLayoutParameter", js_cocos2dx_ui_Widget_getLayoutParameter, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addCCSEventListener", js_cocos2dx_ui_Widget_addCCSEventListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPositionType", js_cocos2dx_ui_Widget_getPositionType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTopBoundary", js_cocos2dx_ui_Widget_getTopBoundary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ignoreContentAdaptWithSize", js_cocos2dx_ui_Widget_ignoreContentAdaptWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("findNextFocusedWidget", js_cocos2dx_ui_Widget_findNextFocusedWidget, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnabled", js_cocos2dx_ui_Widget_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFocused", js_cocos2dx_ui_Widget_isFocused, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchBeganPosition", js_cocos2dx_ui_Widget_getTouchBeganPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchEnabled", js_cocos2dx_ui_Widget_isTouchEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCallbackName", js_cocos2dx_ui_Widget_getCallbackName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getActionTag", js_cocos2dx_ui_Widget_getActionTag, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getWorldPosition", js_cocos2dx_ui_Widget_getWorldPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFocusEnabled", js_cocos2dx_ui_Widget_isFocusEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFocused", js_cocos2dx_ui_Widget_setFocused, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActionTag", js_cocos2dx_ui_Widget_setActionTag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchEnabled", js_cocos2dx_ui_Widget_setTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFlippedY", js_cocos2dx_ui_Widget_setFlippedY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("_init", js_cocos2dx_ui_Widget_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setEnabled", js_cocos2dx_ui_Widget_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRightBoundary", js_cocos2dx_ui_Widget_getRightBoundary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBrightStyle", js_cocos2dx_ui_Widget_setBrightStyle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLayoutParameter", js_cocos2dx_ui_Widget_setLayoutParameter, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("clone", js_cocos2dx_ui_Widget_clone, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFocusEnabled", js_cocos2dx_ui_Widget_setFocusEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBottomBoundary", js_cocos2dx_ui_Widget_getBottomBoundary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBright", js_cocos2dx_ui_Widget_isBright, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dispatchFocusEvent", js_cocos2dx_ui_Widget_dispatchFocusEvent, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUnifySizeEnabled", js_cocos2dx_ui_Widget_setUnifySizeEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPropagateTouchEvents", js_cocos2dx_ui_Widget_isPropagateTouchEvents, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentFocusedWidget", js_cocos2dx_ui_Widget_getCurrentFocusedWidget, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hitTest", js_cocos2dx_ui_Widget_hitTest, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLayoutComponentEnabled", js_cocos2dx_ui_Widget_isLayoutComponentEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestFocus", js_cocos2dx_ui_Widget_requestFocus, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateSizeAndPosition", js_cocos2dx_ui_Widget_updateSizeAndPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onFocusChange", js_cocos2dx_ui_Widget_onFocusChange, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchMovePosition", js_cocos2dx_ui_Widget_getTouchMovePosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSizeType", js_cocos2dx_ui_Widget_getSizeType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCallbackType", js_cocos2dx_ui_Widget_getCallbackType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchEndPosition", js_cocos2dx_ui_Widget_getTouchEndPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPositionPercent", js_cocos2dx_ui_Widget_getPositionPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("propagateTouchEvent", js_cocos2dx_ui_Widget_propagateTouchEvent, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addClickEventListener", js_cocos2dx_ui_Widget_addClickEventListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFlippedX", js_cocos2dx_ui_Widget_isFlippedX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFlippedY", js_cocos2dx_ui_Widget_isFlippedY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isClippingParentContainsPoint", js_cocos2dx_ui_Widget_isClippingParentContainsPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSizeType", js_cocos2dx_ui_Widget_setSizeType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("interceptTouchEvent", js_cocos2dx_ui_Widget_interceptTouchEvent, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBright", js_cocos2dx_ui_Widget_setBright, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCallbackType", js_cocos2dx_ui_Widget_setCallbackType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isSwallowTouches", js_cocos2dx_ui_Widget_isSwallowTouches, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_Widget_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("enableDpadNavigation", js_cocos2dx_ui_Widget_enableDpadNavigation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("create", js_cocos2dx_ui_Widget_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Widget_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ProtectedNode_prototype),
        jsb_cocos2d_ui_Widget_class,
        js_cocos2dx_ui_Widget_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Widget", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Widget> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Widget_class;
        p->proto = jsb_cocos2d_ui_Widget_prototype;
        p->parentProto = jsb_cocos2d_ProtectedNode_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Layout_class;
JSObject *jsb_cocos2d_ui_Layout_prototype;

bool js_cocos2dx_ui_Layout_setBackGroundColorVector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColorVector : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColorVector : Error processing arguments");
        cobj->setBackGroundColorVector(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundColorVector : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setClippingType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setClippingType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Layout::ClippingType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setClippingType : Error processing arguments");
        cobj->setClippingType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setClippingType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundColorType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColorType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Layout::BackGroundColorType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColorType : Error processing arguments");
        cobj->setBackGroundColorType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundColorType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setLoopFocus(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setLoopFocus : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setLoopFocus : Error processing arguments");
        cobj->setLoopFocus(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setLoopFocus : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundImageColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color3B arg0;
        ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageColor : Error processing arguments");
        cobj->setBackGroundImageColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundImageColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundColorVector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundColorVector : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getBackGroundColorVector();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundColorVector : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getClippingType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getClippingType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getClippingType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getClippingType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_isLoopFocus(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_isLoopFocus : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLoopFocus();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_isLoopFocus : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_removeBackGroundImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_removeBackGroundImage : Invalid Native Object");
    if (argc == 0) {
        cobj->removeBackGroundImage();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_removeBackGroundImage : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundColorOpacity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundColorOpacity : Invalid Native Object");
    if (argc == 0) {
        uint16_t ret = cobj->getBackGroundColorOpacity();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundColorOpacity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_isClippingEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_isClippingEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isClippingEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_isClippingEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundImageOpacity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageOpacity : Invalid Native Object");
    if (argc == 1) {
        uint16_t arg0;
        ok &= jsval_to_uint16(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageOpacity : Error processing arguments");
        cobj->setBackGroundImageOpacity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundImageOpacity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImage : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImage : Error processing arguments");
        cobj->setBackGroundImage(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImage : Error processing arguments");
        cobj->setBackGroundImage(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundImage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Layout* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColor : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Color3B arg0;
            ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Color3B arg1;
            ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cobj->setBackGroundColor(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setBackGroundColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundColor : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Layout_requestDoLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_requestDoLayout : Invalid Native Object");
    if (argc == 0) {
        cobj->requestDoLayout();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_requestDoLayout : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundImageCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundImageCapInsets : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getBackGroundImageCapInsets();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundImageCapInsets : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color3B& ret = cobj->getBackGroundColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_setClippingEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setClippingEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setClippingEnabled : Error processing arguments");
        cobj->setClippingEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setClippingEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundImageColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundImageColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color3B& ret = cobj->getBackGroundImageColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundImageColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_isBackGroundImageScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_isBackGroundImageScale9Enabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBackGroundImageScale9Enabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_isBackGroundImageScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundColorType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundColorType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getBackGroundColorType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundColorType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundEndColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundEndColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color3B& ret = cobj->getBackGroundEndColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundEndColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundColorOpacity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColorOpacity : Invalid Native Object");
    if (argc == 1) {
        uint16_t arg0;
        ok &= jsval_to_uint16(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundColorOpacity : Error processing arguments");
        cobj->setBackGroundColorOpacity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundColorOpacity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundImageOpacity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundImageOpacity : Invalid Native Object");
    if (argc == 0) {
        uint16_t ret = cobj->getBackGroundImageOpacity();
        jsval jsret = JSVAL_NULL;
        jsret = uint32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundImageOpacity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_isPassFocusToChild(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_isPassFocusToChild : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPassFocusToChild();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_isPassFocusToChild : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundImageCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageCapInsets : Error processing arguments");
        cobj->setBackGroundImageCapInsets(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundImageCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundImageTextureSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundImageTextureSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getBackGroundImageTextureSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundImageTextureSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_forceDoLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_forceDoLayout : Invalid Native Object");
    if (argc == 0) {
        cobj->forceDoLayout();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_forceDoLayout : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_getLayoutType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getLayoutType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getLayoutType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getLayoutType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_setPassFocusToChild(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setPassFocusToChild : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setPassFocusToChild : Error processing arguments");
        cobj->setPassFocusToChild(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setPassFocusToChild : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_getBackGroundStartColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_getBackGroundStartColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color3B& ret = cobj->getBackGroundStartColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_getBackGroundStartColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Layout_setBackGroundImageScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageScale9Enabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setBackGroundImageScale9Enabled : Error processing arguments");
        cobj->setBackGroundImageScale9Enabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setBackGroundImageScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_setLayoutType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Layout* cobj = (cocos2d::ui::Layout *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Layout_setLayoutType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Layout::Type arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Layout_setLayoutType : Error processing arguments");
        cobj->setLayoutType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Layout_setLayoutType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Layout_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::Layout* ret = cocos2d::ui::Layout::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Layout>(cx, (cocos2d::ui::Layout*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Layout_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Layout_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::Layout::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Layout_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Layout_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::Layout* cobj = new (std::nothrow) cocos2d::ui::Layout();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::Layout> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Layout");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_Layout_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Layout)", obj);
}

static bool js_cocos2d_ui_Layout_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::Layout *nobj = new (std::nothrow) cocos2d::ui::Layout();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Layout");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_Layout(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Layout_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Layout_class->name = "Layout";
    jsb_cocos2d_ui_Layout_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Layout_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Layout_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Layout_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Layout_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Layout_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Layout_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Layout_class->finalize = js_cocos2d_ui_Layout_finalize;
    jsb_cocos2d_ui_Layout_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setBackGroundColorVector", js_cocos2dx_ui_Layout_setBackGroundColorVector, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setClippingType", js_cocos2dx_ui_Layout_setClippingType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundColorType", js_cocos2dx_ui_Layout_setBackGroundColorType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoopFocus", js_cocos2dx_ui_Layout_setLoopFocus, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundImageColor", js_cocos2dx_ui_Layout_setBackGroundImageColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundColorVector", js_cocos2dx_ui_Layout_getBackGroundColorVector, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getClippingType", js_cocos2dx_ui_Layout_getClippingType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoopFocus", js_cocos2dx_ui_Layout_isLoopFocus, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeBackGroundImage", js_cocos2dx_ui_Layout_removeBackGroundImage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundColorOpacity", js_cocos2dx_ui_Layout_getBackGroundColorOpacity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isClippingEnabled", js_cocos2dx_ui_Layout_isClippingEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundImageOpacity", js_cocos2dx_ui_Layout_setBackGroundImageOpacity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundImage", js_cocos2dx_ui_Layout_setBackGroundImage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundColor", js_cocos2dx_ui_Layout_setBackGroundColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestDoLayout", js_cocos2dx_ui_Layout_requestDoLayout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundImageCapInsets", js_cocos2dx_ui_Layout_getBackGroundImageCapInsets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundColor", js_cocos2dx_ui_Layout_getBackGroundColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setClippingEnabled", js_cocos2dx_ui_Layout_setClippingEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundImageColor", js_cocos2dx_ui_Layout_getBackGroundImageColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBackGroundImageScale9Enabled", js_cocos2dx_ui_Layout_isBackGroundImageScale9Enabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundColorType", js_cocos2dx_ui_Layout_getBackGroundColorType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundEndColor", js_cocos2dx_ui_Layout_getBackGroundEndColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundColorOpacity", js_cocos2dx_ui_Layout_setBackGroundColorOpacity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundImageOpacity", js_cocos2dx_ui_Layout_getBackGroundImageOpacity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPassFocusToChild", js_cocos2dx_ui_Layout_isPassFocusToChild, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundImageCapInsets", js_cocos2dx_ui_Layout_setBackGroundImageCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundImageTextureSize", js_cocos2dx_ui_Layout_getBackGroundImageTextureSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("forceDoLayout", js_cocos2dx_ui_Layout_forceDoLayout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLayoutType", js_cocos2dx_ui_Layout_getLayoutType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPassFocusToChild", js_cocos2dx_ui_Layout_setPassFocusToChild, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackGroundStartColor", js_cocos2dx_ui_Layout_getBackGroundStartColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackGroundImageScale9Enabled", js_cocos2dx_ui_Layout_setBackGroundImageScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLayoutType", js_cocos2dx_ui_Layout_setLayoutType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_Layout_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_Layout_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_Layout_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Layout_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_Layout_class,
        js_cocos2dx_ui_Layout_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Layout", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Layout> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Layout_class;
        p->proto = jsb_cocos2d_ui_Layout_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Button_class;
JSObject *jsb_cocos2d_ui_Button_prototype;

bool js_cocos2dx_ui_Button_getNormalTextureSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getNormalTextureSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getNormalTextureSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getNormalTextureSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_getTitleText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getTitleText : Invalid Native Object");
    if (argc == 0) {
        const std::string ret = cobj->getTitleText();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getTitleText : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_setTitleFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setTitleFontSize : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setTitleFontSize : Error processing arguments");
        cobj->setTitleFontSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setTitleFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setScale9Enabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setScale9Enabled : Error processing arguments");
        cobj->setScale9Enabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_getTitleRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getTitleRenderer : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Label* ret = cobj->getTitleRenderer();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Label>(cx, (cocos2d::Label*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getTitleRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getZoomScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getZoomScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getZoomScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_getCapInsetsDisabledRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getCapInsetsDisabledRenderer : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsetsDisabledRenderer();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getCapInsetsDisabledRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_setTitleColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setTitleColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color3B arg0;
        ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setTitleColor : Error processing arguments");
        cobj->setTitleColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setTitleColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setCapInsetsDisabledRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setCapInsetsDisabledRenderer : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setCapInsetsDisabledRenderer : Error processing arguments");
        cobj->setCapInsetsDisabledRenderer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setCapInsetsDisabledRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setCapInsets : Error processing arguments");
        cobj->setCapInsets(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_loadTextureDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_loadTextureDisabled : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextureDisabled : Error processing arguments");
        cobj->loadTextureDisabled(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextureDisabled : Error processing arguments");
        cobj->loadTextureDisabled(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_loadTextureDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_init : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::ui::Widget::TextureResType arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setTitleText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setTitleText : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setTitleText : Error processing arguments");
        cobj->setTitleText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setTitleText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setCapInsetsNormalRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setCapInsetsNormalRenderer : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setCapInsetsNormalRenderer : Error processing arguments");
        cobj->setCapInsetsNormalRenderer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setCapInsetsNormalRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_loadTexturePressed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_loadTexturePressed : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTexturePressed : Error processing arguments");
        cobj->loadTexturePressed(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTexturePressed : Error processing arguments");
        cobj->loadTexturePressed(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_loadTexturePressed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setTitleFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setTitleFontName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setTitleFontName : Error processing arguments");
        cobj->setTitleFontName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setTitleFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_getCapInsetsNormalRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getCapInsetsNormalRenderer : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsetsNormalRenderer();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getCapInsetsNormalRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_setTitleAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Button* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setTitleAlignment : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::TextHAlignment arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cocos2d::TextVAlignment arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cobj->setTitleAlignment(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::TextHAlignment arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj->setTitleAlignment(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setTitleAlignment : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Button_getCapInsetsPressedRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getCapInsetsPressedRenderer : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsetsPressedRenderer();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getCapInsetsPressedRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_loadTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_loadTextures : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextures : Error processing arguments");
        cobj->loadTextures(arg0, arg1);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextures : Error processing arguments");
        cobj->loadTextures(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::ui::Widget::TextureResType arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextures : Error processing arguments");
        cobj->loadTextures(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_loadTextures : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_Button_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_isScale9Enabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScale9Enabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_isScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_loadTextureNormal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_loadTextureNormal : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextureNormal : Error processing arguments");
        cobj->loadTextureNormal(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_loadTextureNormal : Error processing arguments");
        cobj->loadTextureNormal(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_loadTextureNormal : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setCapInsetsPressedRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setCapInsetsPressedRenderer : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setCapInsetsPressedRenderer : Error processing arguments");
        cobj->setCapInsetsPressedRenderer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setCapInsetsPressedRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_getTitleFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getTitleFontSize : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTitleFontSize();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getTitleFontSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_getTitleFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getTitleFontName : Invalid Native Object");
    if (argc == 0) {
        const std::string ret = cobj->getTitleFontName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getTitleFontName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_getTitleColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_getTitleColor : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Color3B ret = cobj->getTitleColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_getTitleColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Button_setPressedActionEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setPressedActionEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setPressedActionEnabled : Error processing arguments");
        cobj->setPressedActionEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setPressedActionEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Button* cobj = (cocos2d::ui::Button *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Button_setZoomScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Button_setZoomScale : Error processing arguments");
        cobj->setZoomScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Button_setZoomScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Button_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Button* ret = cocos2d::ui::Button::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Button>(cx, (cocos2d::ui::Button*)ret);
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
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Button* ret = cocos2d::ui::Button::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Button>(cx, (cocos2d::ui::Button*)ret);
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
            cocos2d::ui::Button* ret = cocos2d::ui::Button::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Button>(cx, (cocos2d::ui::Button*)ret);
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
        if (argc == 4) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg3;
            ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Button* ret = cocos2d::ui::Button::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Button>(cx, (cocos2d::ui::Button*)ret);
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
        if (argc == 0) {
            cocos2d::ui::Button* ret = cocos2d::ui::Button::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Button>(cx, (cocos2d::ui::Button*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_Button_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Button_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::Button::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Button_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Button_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::Button* cobj = new (std::nothrow) cocos2d::ui::Button();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::Button> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Button");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_Button_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Button)", obj);
}

static bool js_cocos2d_ui_Button_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::Button *nobj = new (std::nothrow) cocos2d::ui::Button();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Button");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_Button(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Button_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Button_class->name = "Button";
    jsb_cocos2d_ui_Button_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Button_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Button_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Button_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Button_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Button_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Button_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Button_class->finalize = js_cocos2d_ui_Button_finalize;
    jsb_cocos2d_ui_Button_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getNormalTextureSize", js_cocos2dx_ui_Button_getNormalTextureSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleText", js_cocos2dx_ui_Button_getTitleText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleFontSize", js_cocos2dx_ui_Button_setTitleFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale9Enabled", js_cocos2dx_ui_Button_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleRenderer", js_cocos2dx_ui_Button_getTitleRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getZoomScale", js_cocos2dx_ui_Button_getZoomScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsetsDisabledRenderer", js_cocos2dx_ui_Button_getCapInsetsDisabledRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleColor", js_cocos2dx_ui_Button_setTitleColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsetsDisabledRenderer", js_cocos2dx_ui_Button_setCapInsetsDisabledRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsets", js_cocos2dx_ui_Button_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureDisabled", js_cocos2dx_ui_Button_loadTextureDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_ui_Button_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleText", js_cocos2dx_ui_Button_setTitleText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsetsNormalRenderer", js_cocos2dx_ui_Button_setCapInsetsNormalRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTexturePressed", js_cocos2dx_ui_Button_loadTexturePressed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleFontName", js_cocos2dx_ui_Button_setTitleFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsetsNormalRenderer", js_cocos2dx_ui_Button_getCapInsetsNormalRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleAlignment", js_cocos2dx_ui_Button_setTitleAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsetsPressedRenderer", js_cocos2dx_ui_Button_getCapInsetsPressedRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextures", js_cocos2dx_ui_Button_loadTextures, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScale9Enabled", js_cocos2dx_ui_Button_isScale9Enabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureNormal", js_cocos2dx_ui_Button_loadTextureNormal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsetsPressedRenderer", js_cocos2dx_ui_Button_setCapInsetsPressedRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleFontSize", js_cocos2dx_ui_Button_getTitleFontSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleFontName", js_cocos2dx_ui_Button_getTitleFontName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleColor", js_cocos2dx_ui_Button_getTitleColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPressedActionEnabled", js_cocos2dx_ui_Button_setPressedActionEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomScale", js_cocos2dx_ui_Button_setZoomScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_Button_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_Button_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_Button_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Button_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_Button_class,
        js_cocos2dx_ui_Button_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Button", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Button> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Button_class;
        p->proto = jsb_cocos2d_ui_Button_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_CheckBox_class;
JSObject *jsb_cocos2d_ui_CheckBox_prototype;

bool js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected : Error processing arguments");
        cobj->loadTextureBackGroundSelected(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected : Error processing arguments");
        cobj->loadTextureBackGroundSelected(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled : Error processing arguments");
        cobj->loadTextureBackGroundDisabled(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled : Error processing arguments");
        cobj->loadTextureBackGroundDisabled(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_setSelected(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_setSelected : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_setSelected : Error processing arguments");
        cobj->setSelected(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_setSelected : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_loadTextureFrontCross(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureFrontCross : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureFrontCross : Error processing arguments");
        cobj->loadTextureFrontCross(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureFrontCross : Error processing arguments");
        cobj->loadTextureFrontCross(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_loadTextureFrontCross : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_isSelected(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_isSelected : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isSelected();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_isSelected : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_CheckBox_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_init : Invalid Native Object");
    if (argc == 5) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 6) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        cocos2d::ui::Widget::TextureResType arg5;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_init : wrong number of arguments: %d, was expecting %d", argc, 5);
    return false;
}
bool js_cocos2dx_ui_CheckBox_loadTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_loadTextures : Invalid Native Object");
    if (argc == 5) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextures : Error processing arguments");
        cobj->loadTextures(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 6) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        std::string arg4;
        cocos2d::ui::Widget::TextureResType arg5;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextures : Error processing arguments");
        cobj->loadTextures(arg0, arg1, arg2, arg3, arg4, arg5);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_loadTextures : wrong number of arguments: %d, was expecting %d", argc, 5);
    return false;
}
bool js_cocos2dx_ui_CheckBox_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_getZoomScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getZoomScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_getZoomScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_CheckBox_loadTextureBackGround(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGround : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGround : Error processing arguments");
        cobj->loadTextureBackGround(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureBackGround : Error processing arguments");
        cobj->loadTextureBackGround(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_loadTextureBackGround : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_setZoomScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_setZoomScale : Error processing arguments");
        cobj->setZoomScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_setZoomScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled : Error processing arguments");
        cobj->loadTextureFrontCrossDisabled(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled : Error processing arguments");
        cobj->loadTextureFrontCrossDisabled(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_CheckBox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 5) {
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
            cocos2d::ui::CheckBox* ret = cocos2d::ui::CheckBox::create(arg0, arg1, arg2, arg3, arg4);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::CheckBox>(cx, (cocos2d::ui::CheckBox*)ret);
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
            cocos2d::ui::Widget::TextureResType arg5;
            ok &= jsval_to_int32(cx, args.get(5), (int32_t *)&arg5);
            if (!ok) { ok = true; break; }
            cocos2d::ui::CheckBox* ret = cocos2d::ui::CheckBox::create(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::CheckBox>(cx, (cocos2d::ui::CheckBox*)ret);
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
        if (argc == 0) {
            cocos2d::ui::CheckBox* ret = cocos2d::ui::CheckBox::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::CheckBox>(cx, (cocos2d::ui::CheckBox*)ret);
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
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::CheckBox* ret = cocos2d::ui::CheckBox::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::CheckBox>(cx, (cocos2d::ui::CheckBox*)ret);
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
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::CheckBox* ret = cocos2d::ui::CheckBox::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::CheckBox>(cx, (cocos2d::ui::CheckBox*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_CheckBox_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::CheckBox::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_CheckBox_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_CheckBox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::CheckBox* cobj = new (std::nothrow) cocos2d::ui::CheckBox();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::CheckBox> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::CheckBox");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_CheckBox_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CheckBox)", obj);
}

static bool js_cocos2d_ui_CheckBox_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::CheckBox *nobj = new (std::nothrow) cocos2d::ui::CheckBox();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::CheckBox");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_CheckBox(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_CheckBox_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_CheckBox_class->name = "CheckBox";
    jsb_cocos2d_ui_CheckBox_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_CheckBox_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_CheckBox_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_CheckBox_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_CheckBox_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_CheckBox_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_CheckBox_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_CheckBox_class->finalize = js_cocos2d_ui_CheckBox_finalize;
    jsb_cocos2d_ui_CheckBox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("loadTextureBackGroundSelected", js_cocos2dx_ui_CheckBox_loadTextureBackGroundSelected, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureBackGroundDisabled", js_cocos2dx_ui_CheckBox_loadTextureBackGroundDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSelected", js_cocos2dx_ui_CheckBox_setSelected, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureFrontCross", js_cocos2dx_ui_CheckBox_loadTextureFrontCross, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isSelected", js_cocos2dx_ui_CheckBox_isSelected, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_ui_CheckBox_init, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextures", js_cocos2dx_ui_CheckBox_loadTextures, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getZoomScale", js_cocos2dx_ui_CheckBox_getZoomScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureBackGround", js_cocos2dx_ui_CheckBox_loadTextureBackGround, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomScale", js_cocos2dx_ui_CheckBox_setZoomScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTextureFrontCrossDisabled", js_cocos2dx_ui_CheckBox_loadTextureFrontCrossDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_CheckBox_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_CheckBox_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_CheckBox_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_CheckBox_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_CheckBox_class,
        js_cocos2dx_ui_CheckBox_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "CheckBox", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::CheckBox> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_CheckBox_class;
        p->proto = jsb_cocos2d_ui_CheckBox_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_ImageView_class;
JSObject *jsb_cocos2d_ui_ImageView_prototype;

bool js_cocos2dx_ui_ImageView_loadTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_loadTexture : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_loadTexture : Error processing arguments");
        cobj->loadTexture(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_loadTexture : Error processing arguments");
        cobj->loadTexture(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_loadTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ImageView_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_init : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_init : Error processing arguments");
        bool ret = cobj->init(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_init : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ImageView_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_setScale9Enabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_setScale9Enabled : Error processing arguments");
        cobj->setScale9Enabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ImageView_setTextureRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_setTextureRect : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_setTextureRect : Error processing arguments");
        cobj->setTextureRect(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_setTextureRect : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ImageView_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_setCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ImageView_setCapInsets : Error processing arguments");
        cobj->setCapInsets(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ImageView_getCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_getCapInsets : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsets();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_getCapInsets : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ImageView_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ImageView* cobj = (cocos2d::ui::ImageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ImageView_isScale9Enabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScale9Enabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_isScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ImageView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::ImageView* ret = cocos2d::ui::ImageView::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::ImageView>(cx, (cocos2d::ui::ImageView*)ret);
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
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::ImageView* ret = cocos2d::ui::ImageView::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::ImageView>(cx, (cocos2d::ui::ImageView*)ret);
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
        if (argc == 0) {
            cocos2d::ui::ImageView* ret = cocos2d::ui::ImageView::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::ImageView>(cx, (cocos2d::ui::ImageView*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_ImageView_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::ImageView::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_ImageView_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_ImageView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::ImageView* cobj = new (std::nothrow) cocos2d::ui::ImageView();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::ImageView> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::ImageView");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_ImageView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ImageView)", obj);
}

static bool js_cocos2d_ui_ImageView_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::ImageView *nobj = new (std::nothrow) cocos2d::ui::ImageView();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::ImageView");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_ImageView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_ImageView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_ImageView_class->name = "ImageView";
    jsb_cocos2d_ui_ImageView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_ImageView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_ImageView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_ImageView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_ImageView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_ImageView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_ImageView_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_ImageView_class->finalize = js_cocos2d_ui_ImageView_finalize;
    jsb_cocos2d_ui_ImageView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("loadTexture", js_cocos2dx_ui_ImageView_loadTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("_init", js_cocos2dx_ui_ImageView_init, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale9Enabled", js_cocos2dx_ui_ImageView_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextureRect", js_cocos2dx_ui_ImageView_setTextureRect, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsets", js_cocos2dx_ui_ImageView_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsets", js_cocos2dx_ui_ImageView_getCapInsets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScale9Enabled", js_cocos2dx_ui_ImageView_isScale9Enabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_ImageView_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_ImageView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_ImageView_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_ImageView_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_ImageView_class,
        js_cocos2dx_ui_ImageView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ImageView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::ImageView> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_ImageView_class;
        p->proto = jsb_cocos2d_ui_ImageView_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Text_class;
JSObject *jsb_cocos2d_ui_Text_prototype;

bool js_cocos2dx_ui_Text_enableShadow(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_enableShadow : Invalid Native Object");
    if (argc == 0) {
        cobj->enableShadow();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        cocos2d::Color4B arg0;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_enableShadow : Error processing arguments");
        cobj->enableShadow(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Color4B arg0;
        cocos2d::Size arg1;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_enableShadow : Error processing arguments");
        cobj->enableShadow(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 3) {
        cocos2d::Color4B arg0;
        cocos2d::Size arg1;
        int arg2;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_enableShadow : Error processing arguments");
        cobj->enableShadow(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_enableShadow : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_getFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getFontSize : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getFontSize();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getFontSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getString : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_disableEffect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Text* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_disableEffect : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::LabelEffect arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj->disableEffect(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->disableEffect();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Text_disableEffect : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Text_getTextColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getTextColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4B& ret = cobj->getTextColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getTextColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_setTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setTextVerticalAlignment : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextVAlignment arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setTextVerticalAlignment : Error processing arguments");
        cobj->setTextVerticalAlignment(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setTextVerticalAlignment : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_setFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setFontName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setFontName : Error processing arguments");
        cobj->setFontName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_setTouchScaleChangeEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setTouchScaleChangeEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setTouchScaleChangeEnabled : Error processing arguments");
        cobj->setTouchScaleChangeEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setTouchScaleChangeEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_setString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setString : Error processing arguments");
        cobj->setString(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_init : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        int arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_init : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_Text_isTouchScaleChangeEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_isTouchScaleChangeEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouchScaleChangeEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_isTouchScaleChangeEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_getFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getFontName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getFontName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getFontName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_setTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setTextAreaSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setTextAreaSize : Error processing arguments");
        cobj->setTextAreaSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setTextAreaSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_getStringLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getStringLength : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getStringLength();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getStringLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_getAutoRenderSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getAutoRenderSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getAutoRenderSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getAutoRenderSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_enableOutline(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_enableOutline : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4B arg0;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_enableOutline : Error processing arguments");
        cobj->enableOutline(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Color4B arg0;
        int arg1;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_enableOutline : Error processing arguments");
        cobj->enableOutline(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_enableOutline : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_getType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getType : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getType();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getType : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_getTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getTextHorizontalAlignment : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTextHorizontalAlignment();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getTextHorizontalAlignment : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_setFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setFontSize : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setFontSize : Error processing arguments");
        cobj->setFontSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_setTextColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setTextColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4B arg0;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setTextColor : Error processing arguments");
        cobj->setTextColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setTextColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_enableGlow(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_enableGlow : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4B arg0;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_enableGlow : Error processing arguments");
        cobj->enableGlow(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_enableGlow : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_getTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getTextVerticalAlignment : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTextVerticalAlignment();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getTextVerticalAlignment : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_getTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_getTextAreaSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getTextAreaSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_getTextAreaSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Text_setTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Text* cobj = (cocos2d::ui::Text *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Text_setTextHorizontalAlignment : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextHAlignment arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Text_setTextHorizontalAlignment : Error processing arguments");
        cobj->setTextHorizontalAlignment(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Text_setTextHorizontalAlignment : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Text_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            int arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Text* ret = cocos2d::ui::Text::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Text>(cx, (cocos2d::ui::Text*)ret);
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
        if (argc == 0) {
            cocos2d::ui::Text* ret = cocos2d::ui::Text::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Text>(cx, (cocos2d::ui::Text*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_Text_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Text_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::Text::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Text_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Text_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::Text* cobj = new (std::nothrow) cocos2d::ui::Text();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::Text> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Text");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_Text_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Text)", obj);
}

static bool js_cocos2d_ui_Text_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::Text *nobj = new (std::nothrow) cocos2d::ui::Text();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Text");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_Text(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Text_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Text_class->name = "Text";
    jsb_cocos2d_ui_Text_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Text_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Text_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Text_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Text_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Text_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Text_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Text_class->finalize = js_cocos2d_ui_Text_finalize;
    jsb_cocos2d_ui_Text_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("enableShadow", js_cocos2dx_ui_Text_enableShadow, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFontSize", js_cocos2dx_ui_Text_getFontSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_ui_Text_getString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("disableEffect", js_cocos2dx_ui_Text_disableEffect, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextColor", js_cocos2dx_ui_Text_getTextColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextVerticalAlignment", js_cocos2dx_ui_Text_setTextVerticalAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontName", js_cocos2dx_ui_Text_setFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchScaleChangeEnabled", js_cocos2dx_ui_Text_setTouchScaleChangeEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_ui_Text_setString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_ui_Text_init, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchScaleChangeEnabled", js_cocos2dx_ui_Text_isTouchScaleChangeEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFontName", js_cocos2dx_ui_Text_getFontName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextAreaSize", js_cocos2dx_ui_Text_setTextAreaSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringLength", js_cocos2dx_ui_Text_getStringLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAutoRenderSize", js_cocos2dx_ui_Text_getAutoRenderSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableOutline", js_cocos2dx_ui_Text_enableOutline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getType", js_cocos2dx_ui_Text_getType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextHorizontalAlignment", js_cocos2dx_ui_Text_getTextHorizontalAlignment, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontSize", js_cocos2dx_ui_Text_setFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextColor", js_cocos2dx_ui_Text_setTextColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("enableGlow", js_cocos2dx_ui_Text_enableGlow, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextVerticalAlignment", js_cocos2dx_ui_Text_getTextVerticalAlignment, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextAreaSize", js_cocos2dx_ui_Text_getTextAreaSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextHorizontalAlignment", js_cocos2dx_ui_Text_setTextHorizontalAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_Text_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_Text_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_Text_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Text_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_Text_class,
        js_cocos2dx_ui_Text_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Text", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Text> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Text_class;
        p->proto = jsb_cocos2d_ui_Text_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_TextAtlas_class;
JSObject *jsb_cocos2d_ui_TextAtlas_prototype;

bool js_cocos2dx_ui_TextAtlas_getStringLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextAtlas* cobj = (cocos2d::ui::TextAtlas *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextAtlas_getStringLength : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getStringLength();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_getStringLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextAtlas_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextAtlas* cobj = (cocos2d::ui::TextAtlas *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextAtlas_getString : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_getString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextAtlas_setString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextAtlas* cobj = (cocos2d::ui::TextAtlas *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextAtlas_setString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextAtlas_setString : Error processing arguments");
        cobj->setString(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_setString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextAtlas_setProperty(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextAtlas* cobj = (cocos2d::ui::TextAtlas *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextAtlas_setProperty : Invalid Native Object");
    if (argc == 5) {
        std::string arg0;
        std::string arg1;
        int arg2;
        int arg3;
        std::string arg4;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextAtlas_setProperty : Error processing arguments");
        cobj->setProperty(arg0, arg1, arg2, arg3, arg4);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_setProperty : wrong number of arguments: %d, was expecting %d", argc, 5);
    return false;
}
bool js_cocos2dx_ui_TextAtlas_adaptRenderers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextAtlas* cobj = (cocos2d::ui::TextAtlas *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextAtlas_adaptRenderers : Invalid Native Object");
    if (argc == 0) {
        cobj->adaptRenderers();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_adaptRenderers : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextAtlas_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 5) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            int arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            int arg3;
            ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
            if (!ok) { ok = true; break; }
            std::string arg4;
            ok &= jsval_to_std_string(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            cocos2d::ui::TextAtlas* ret = cocos2d::ui::TextAtlas::create(arg0, arg1, arg2, arg3, arg4);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::TextAtlas>(cx, (cocos2d::ui::TextAtlas*)ret);
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
        if (argc == 0) {
            cocos2d::ui::TextAtlas* ret = cocos2d::ui::TextAtlas::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::TextAtlas>(cx, (cocos2d::ui::TextAtlas*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_TextAtlas_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::TextAtlas::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_TextAtlas_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_TextAtlas_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::TextAtlas* cobj = new (std::nothrow) cocos2d::ui::TextAtlas();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::TextAtlas> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::TextAtlas");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_TextAtlas_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextAtlas)", obj);
}

static bool js_cocos2d_ui_TextAtlas_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::TextAtlas *nobj = new (std::nothrow) cocos2d::ui::TextAtlas();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::TextAtlas");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_TextAtlas(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_TextAtlas_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_TextAtlas_class->name = "TextAtlas";
    jsb_cocos2d_ui_TextAtlas_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_TextAtlas_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_TextAtlas_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_TextAtlas_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_TextAtlas_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_TextAtlas_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_TextAtlas_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_TextAtlas_class->finalize = js_cocos2d_ui_TextAtlas_finalize;
    jsb_cocos2d_ui_TextAtlas_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getStringLength", js_cocos2dx_ui_TextAtlas_getStringLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_ui_TextAtlas_getString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_ui_TextAtlas_setString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProperty", js_cocos2dx_ui_TextAtlas_setProperty, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("adaptRenderers", js_cocos2dx_ui_TextAtlas_adaptRenderers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_TextAtlas_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_TextAtlas_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_TextAtlas_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_TextAtlas_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_TextAtlas_class,
        js_cocos2dx_ui_TextAtlas_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "TextAtlas", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::TextAtlas> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_TextAtlas_class;
        p->proto = jsb_cocos2d_ui_TextAtlas_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_LoadingBar_class;
JSObject *jsb_cocos2d_ui_LoadingBar_prototype;

bool js_cocos2dx_ui_LoadingBar_setPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_setPercent : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LoadingBar_setPercent : Error processing arguments");
        cobj->setPercent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_setPercent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_loadTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_loadTexture : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LoadingBar_loadTexture : Error processing arguments");
        cobj->loadTexture(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LoadingBar_loadTexture : Error processing arguments");
        cobj->loadTexture(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_loadTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_setDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_setDirection : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::LoadingBar::Direction arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LoadingBar_setDirection : Error processing arguments");
        cobj->setDirection(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_setDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_setScale9Enabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LoadingBar_setScale9Enabled : Error processing arguments");
        cobj->setScale9Enabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_setCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LoadingBar_setCapInsets : Error processing arguments");
        cobj->setCapInsets(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_getDirection : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getDirection();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_getDirection : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_getCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_getCapInsets : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsets();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_getCapInsets : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_isScale9Enabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScale9Enabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_isScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_getPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LoadingBar* cobj = (cocos2d::ui::LoadingBar *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LoadingBar_getPercent : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPercent();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_getPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LoadingBar_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LoadingBar>(cx, (cocos2d::ui::LoadingBar*)ret);
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
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            double arg1;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LoadingBar>(cx, (cocos2d::ui::LoadingBar*)ret);
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
        if (argc == 0) {
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LoadingBar>(cx, (cocos2d::ui::LoadingBar*)ret);
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
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LoadingBar>(cx, (cocos2d::ui::LoadingBar*)ret);
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
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg1;
            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
            if (!ok) { ok = true; break; }
            double arg2;
            ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::LoadingBar* ret = cocos2d::ui::LoadingBar::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LoadingBar>(cx, (cocos2d::ui::LoadingBar*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_LoadingBar_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::LoadingBar::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_LoadingBar_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_LoadingBar_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::LoadingBar* cobj = new (std::nothrow) cocos2d::ui::LoadingBar();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::LoadingBar> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::LoadingBar");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_LoadingBar_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LoadingBar)", obj);
}

static bool js_cocos2d_ui_LoadingBar_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::LoadingBar *nobj = new (std::nothrow) cocos2d::ui::LoadingBar();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::LoadingBar");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_LoadingBar(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_LoadingBar_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_LoadingBar_class->name = "LoadingBar";
    jsb_cocos2d_ui_LoadingBar_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LoadingBar_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_LoadingBar_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LoadingBar_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_LoadingBar_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_LoadingBar_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_LoadingBar_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_LoadingBar_class->finalize = js_cocos2d_ui_LoadingBar_finalize;
    jsb_cocos2d_ui_LoadingBar_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setPercent", js_cocos2dx_ui_LoadingBar_setPercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadTexture", js_cocos2dx_ui_LoadingBar_loadTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDirection", js_cocos2dx_ui_LoadingBar_setDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale9Enabled", js_cocos2dx_ui_LoadingBar_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsets", js_cocos2dx_ui_LoadingBar_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDirection", js_cocos2dx_ui_LoadingBar_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsets", js_cocos2dx_ui_LoadingBar_getCapInsets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScale9Enabled", js_cocos2dx_ui_LoadingBar_isScale9Enabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercent", js_cocos2dx_ui_LoadingBar_getPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_LoadingBar_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_LoadingBar_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_LoadingBar_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_LoadingBar_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_LoadingBar_class,
        js_cocos2dx_ui_LoadingBar_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LoadingBar", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::LoadingBar> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_LoadingBar_class;
        p->proto = jsb_cocos2d_ui_LoadingBar_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_ScrollView_class;
JSObject *jsb_cocos2d_ui_ScrollView_prototype;

bool js_cocos2dx_ui_ScrollView_scrollToTop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToTop : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToTop : Error processing arguments");
        cobj->scrollToTop(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToTop : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToPercentHorizontal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToPercentHorizontal : Invalid Native Object");
    if (argc == 3) {
        double arg0;
        double arg1;
        bool arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToPercentHorizontal : Error processing arguments");
        cobj->scrollToPercentHorizontal(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToPercentHorizontal : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_ScrollView_isInertiaScrollEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_isInertiaScrollEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isInertiaScrollEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_isInertiaScrollEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToPercentBothDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToPercentBothDirection : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Vec2 arg0;
        double arg1;
        bool arg2;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToPercentBothDirection : Error processing arguments");
        cobj->scrollToPercentBothDirection(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToPercentBothDirection : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_ScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_getDirection : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getDirection();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_getDirection : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToBottomLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToBottomLeft : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToBottomLeft : Error processing arguments");
        cobj->scrollToBottomLeft(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToBottomLeft : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_getInnerContainer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_getInnerContainer : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::Layout* ret = cobj->getInnerContainer();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Layout>(cx, (cocos2d::ui::Layout*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_getInnerContainer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToBottom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToBottom : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToBottom();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToBottom : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_setDirection : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::ScrollView::Direction arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_setDirection : Error processing arguments");
        cobj->setDirection(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_setDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToTopLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToTopLeft : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToTopLeft : Error processing arguments");
        cobj->scrollToTopLeft(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToTopLeft : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToTopRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToTopRight : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToTopRight();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToTopRight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToBottomLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToBottomLeft : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToBottomLeft();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToBottomLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_setInnerContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_setInnerContainerSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_setInnerContainerSize : Error processing arguments");
        cobj->setInnerContainerSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_setInnerContainerSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_getInnerContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_getInnerContainerSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getInnerContainerSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_getInnerContainerSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_isBounceEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_isBounceEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBounceEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_isBounceEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToPercentVertical(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToPercentVertical : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_jumpToPercentVertical : Error processing arguments");
        cobj->jumpToPercentVertical(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToPercentVertical : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_setInertiaScrollEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_setInertiaScrollEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_setInertiaScrollEnabled : Error processing arguments");
        cobj->setInertiaScrollEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_setInertiaScrollEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToTopLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToTopLeft : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToTopLeft();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToTopLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToPercentHorizontal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToPercentHorizontal : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_jumpToPercentHorizontal : Error processing arguments");
        cobj->jumpToPercentHorizontal(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToPercentHorizontal : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToBottomRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToBottomRight : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToBottomRight();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToBottomRight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_setBounceEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_setBounceEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_setBounceEnabled : Error processing arguments");
        cobj->setBounceEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_setBounceEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToTop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToTop : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToTop();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToTop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToLeft : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToLeft : Error processing arguments");
        cobj->scrollToLeft(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToLeft : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToPercentBothDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToPercentBothDirection : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_jumpToPercentBothDirection : Error processing arguments");
        cobj->jumpToPercentBothDirection(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToPercentBothDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToPercentVertical(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToPercentVertical : Invalid Native Object");
    if (argc == 3) {
        double arg0;
        double arg1;
        bool arg2;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToPercentVertical : Error processing arguments");
        cobj->scrollToPercentVertical(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToPercentVertical : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToBottom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToBottom : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToBottom : Error processing arguments");
        cobj->scrollToBottom(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToBottom : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToBottomRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToBottomRight : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToBottomRight : Error processing arguments");
        cobj->scrollToBottomRight(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToBottomRight : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToLeft : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToLeft();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToRight : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToRight : Error processing arguments");
        cobj->scrollToRight(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToRight : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_jumpToRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_jumpToRight : Invalid Native Object");
    if (argc == 0) {
        cobj->jumpToRight();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_jumpToRight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ScrollView_scrollToTopRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ScrollView_scrollToTopRight : Invalid Native Object");
    if (argc == 2) {
        double arg0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ScrollView_scrollToTopRight : Error processing arguments");
        cobj->scrollToTopRight(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_scrollToTopRight : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ScrollView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::ScrollView* ret = cocos2d::ui::ScrollView::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::ScrollView>(cx, (cocos2d::ui::ScrollView*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_ScrollView_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::ScrollView::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_ScrollView_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_ScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::ScrollView* cobj = new (std::nothrow) cocos2d::ui::ScrollView();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::ScrollView> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::ScrollView");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Layout_prototype;

void js_cocos2d_ui_ScrollView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ScrollView)", obj);
}

static bool js_cocos2d_ui_ScrollView_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::ScrollView *nobj = new (std::nothrow) cocos2d::ui::ScrollView();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::ScrollView");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_ScrollView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_ScrollView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_ScrollView_class->name = "ScrollView";
    jsb_cocos2d_ui_ScrollView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_ScrollView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_ScrollView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_ScrollView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_ScrollView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_ScrollView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_ScrollView_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_ScrollView_class->finalize = js_cocos2d_ui_ScrollView_finalize;
    jsb_cocos2d_ui_ScrollView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("scrollToTop", js_cocos2dx_ui_ScrollView_scrollToTop, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToPercentHorizontal", js_cocos2dx_ui_ScrollView_scrollToPercentHorizontal, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isInertiaScrollEnabled", js_cocos2dx_ui_ScrollView_isInertiaScrollEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToPercentBothDirection", js_cocos2dx_ui_ScrollView_scrollToPercentBothDirection, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDirection", js_cocos2dx_ui_ScrollView_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToBottomLeft", js_cocos2dx_ui_ScrollView_scrollToBottomLeft, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInnerContainer", js_cocos2dx_ui_ScrollView_getInnerContainer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToBottom", js_cocos2dx_ui_ScrollView_jumpToBottom, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDirection", js_cocos2dx_ui_ScrollView_setDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToTopLeft", js_cocos2dx_ui_ScrollView_scrollToTopLeft, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToTopRight", js_cocos2dx_ui_ScrollView_jumpToTopRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToBottomLeft", js_cocos2dx_ui_ScrollView_jumpToBottomLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInnerContainerSize", js_cocos2dx_ui_ScrollView_setInnerContainerSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInnerContainerSize", js_cocos2dx_ui_ScrollView_getInnerContainerSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBounceEnabled", js_cocos2dx_ui_ScrollView_isBounceEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToPercentVertical", js_cocos2dx_ui_ScrollView_jumpToPercentVertical, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInertiaScrollEnabled", js_cocos2dx_ui_ScrollView_setInertiaScrollEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToTopLeft", js_cocos2dx_ui_ScrollView_jumpToTopLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToPercentHorizontal", js_cocos2dx_ui_ScrollView_jumpToPercentHorizontal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToBottomRight", js_cocos2dx_ui_ScrollView_jumpToBottomRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBounceEnabled", js_cocos2dx_ui_ScrollView_setBounceEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToTop", js_cocos2dx_ui_ScrollView_jumpToTop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToLeft", js_cocos2dx_ui_ScrollView_scrollToLeft, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToPercentBothDirection", js_cocos2dx_ui_ScrollView_jumpToPercentBothDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToPercentVertical", js_cocos2dx_ui_ScrollView_scrollToPercentVertical, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToBottom", js_cocos2dx_ui_ScrollView_scrollToBottom, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToBottomRight", js_cocos2dx_ui_ScrollView_scrollToBottomRight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToLeft", js_cocos2dx_ui_ScrollView_jumpToLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToRight", js_cocos2dx_ui_ScrollView_scrollToRight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("jumpToRight", js_cocos2dx_ui_ScrollView_jumpToRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToTopRight", js_cocos2dx_ui_ScrollView_scrollToTopRight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_ScrollView_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_ScrollView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_ScrollView_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_ScrollView_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Layout_prototype),
        jsb_cocos2d_ui_ScrollView_class,
        js_cocos2dx_ui_ScrollView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ScrollView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::ScrollView> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_ScrollView_class;
        p->proto = jsb_cocos2d_ui_ScrollView_prototype;
        p->parentProto = jsb_cocos2d_ui_Layout_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_ListView_class;
JSObject *jsb_cocos2d_ui_ListView_prototype;

bool js_cocos2dx_ui_ListView_getIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_getIndex : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Widget* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_getIndex : Error processing arguments");
        ssize_t ret = cobj->getIndex(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_getIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_removeAllItems(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_removeAllItems : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllItems();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_removeAllItems : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_setGravity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_setGravity : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::ListView::Gravity arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_setGravity : Error processing arguments");
        cobj->setGravity(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_setGravity : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_pushBackCustomItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_pushBackCustomItem : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Widget* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_pushBackCustomItem : Error processing arguments");
        cobj->pushBackCustomItem(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_pushBackCustomItem : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_getItems(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_getItems : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::ui::Widget *>& ret = cobj->getItems();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_getItems : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_removeItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_removeItem : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_removeItem : Error processing arguments");
        cobj->removeItem(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_removeItem : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_getCurSelectedIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_getCurSelectedIndex : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getCurSelectedIndex();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_getCurSelectedIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_insertDefaultItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_insertDefaultItem : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_insertDefaultItem : Error processing arguments");
        cobj->insertDefaultItem(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_insertDefaultItem : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_requestRefreshView(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_requestRefreshView : Invalid Native Object");
    if (argc == 0) {
        cobj->requestRefreshView();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_requestRefreshView : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_setItemsMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_setItemsMargin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_setItemsMargin : Error processing arguments");
        cobj->setItemsMargin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_setItemsMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_refreshView(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_refreshView : Invalid Native Object");
    if (argc == 0) {
        cobj->refreshView();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_refreshView : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_removeLastItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_removeLastItem : Invalid Native Object");
    if (argc == 0) {
        cobj->removeLastItem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_removeLastItem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_getItemsMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_getItemsMargin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getItemsMargin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_getItemsMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_getItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_getItem : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_getItem : Error processing arguments");
        cocos2d::ui::Widget* ret = cobj->getItem(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_getItem : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_setItemModel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_setItemModel : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Widget* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_setItemModel : Error processing arguments");
        cobj->setItemModel(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_setItemModel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_ListView_doLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_doLayout : Invalid Native Object");
    if (argc == 0) {
        cobj->doLayout();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_doLayout : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_pushBackDefaultItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_pushBackDefaultItem : Invalid Native Object");
    if (argc == 0) {
        cobj->pushBackDefaultItem();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_pushBackDefaultItem : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_ListView_insertCustomItem(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_ListView_insertCustomItem : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::Widget* arg0;
        ssize_t arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ssize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_ListView_insertCustomItem : Error processing arguments");
        cobj->insertCustomItem(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_ListView_insertCustomItem : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_ListView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::ListView* ret = cocos2d::ui::ListView::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::ListView>(cx, (cocos2d::ui::ListView*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_ListView_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_ListView_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::ListView::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_ListView_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_ListView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::ListView* cobj = new (std::nothrow) cocos2d::ui::ListView();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::ListView> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::ListView");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_ScrollView_prototype;

void js_cocos2d_ui_ListView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ListView)", obj);
}

static bool js_cocos2d_ui_ListView_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::ListView *nobj = new (std::nothrow) cocos2d::ui::ListView();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::ListView");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_ListView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_ListView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_ListView_class->name = "ListView";
    jsb_cocos2d_ui_ListView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_ListView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_ListView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_ListView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_ListView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_ListView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_ListView_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_ListView_class->finalize = js_cocos2d_ui_ListView_finalize;
    jsb_cocos2d_ui_ListView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getIndex", js_cocos2dx_ui_ListView_getIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllItems", js_cocos2dx_ui_ListView_removeAllItems, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setGravity", js_cocos2dx_ui_ListView_setGravity, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushBackCustomItem", js_cocos2dx_ui_ListView_pushBackCustomItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getItems", js_cocos2dx_ui_ListView_getItems, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeItem", js_cocos2dx_ui_ListView_removeItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurSelectedIndex", js_cocos2dx_ui_ListView_getCurSelectedIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertDefaultItem", js_cocos2dx_ui_ListView_insertDefaultItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("requestRefreshView", js_cocos2dx_ui_ListView_requestRefreshView, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setItemsMargin", js_cocos2dx_ui_ListView_setItemsMargin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("refreshView", js_cocos2dx_ui_ListView_refreshView, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeLastItem", js_cocos2dx_ui_ListView_removeLastItem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getItemsMargin", js_cocos2dx_ui_ListView_getItemsMargin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getItem", js_cocos2dx_ui_ListView_getItem, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setItemModel", js_cocos2dx_ui_ListView_setItemModel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("doLayout", js_cocos2dx_ui_ListView_doLayout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushBackDefaultItem", js_cocos2dx_ui_ListView_pushBackDefaultItem, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertCustomItem", js_cocos2dx_ui_ListView_insertCustomItem, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_ListView_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_ListView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_ListView_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_ListView_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_ScrollView_prototype),
        jsb_cocos2d_ui_ListView_class,
        js_cocos2dx_ui_ListView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ListView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::ListView> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_ListView_class;
        p->proto = jsb_cocos2d_ui_ListView_prototype;
        p->parentProto = jsb_cocos2d_ui_ScrollView_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Slider_class;
JSObject *jsb_cocos2d_ui_Slider_prototype;

bool js_cocos2dx_ui_Slider_setPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_setPercent : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_setPercent : Error processing arguments");
        cobj->setPercent(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_setPercent : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled : Error processing arguments");
        cobj->loadSlidBallTextureDisabled(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled : Error processing arguments");
        cobj->loadSlidBallTextureDisabled(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_loadSlidBallTextureNormal(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextureNormal : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextureNormal : Error processing arguments");
        cobj->loadSlidBallTextureNormal(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextureNormal : Error processing arguments");
        cobj->loadSlidBallTextureNormal(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_loadSlidBallTextureNormal : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_loadBarTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_loadBarTexture : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadBarTexture : Error processing arguments");
        cobj->loadBarTexture(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadBarTexture : Error processing arguments");
        cobj->loadBarTexture(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_loadBarTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_loadProgressBarTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_loadProgressBarTexture : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadProgressBarTexture : Error processing arguments");
        cobj->loadProgressBarTexture(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadProgressBarTexture : Error processing arguments");
        cobj->loadProgressBarTexture(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_loadProgressBarTexture : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_loadSlidBallTextures(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextures : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextures : Error processing arguments");
        cobj->loadSlidBallTextures(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextures : Error processing arguments");
        cobj->loadSlidBallTextures(arg0, arg1);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextures : Error processing arguments");
        cobj->loadSlidBallTextures(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        cocos2d::ui::Widget::TextureResType arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTextures : Error processing arguments");
        cobj->loadSlidBallTextures(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_loadSlidBallTextures : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_setCapInsetProgressBarRebderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_setCapInsetProgressBarRebderer : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_setCapInsetProgressBarRebderer : Error processing arguments");
        cobj->setCapInsetProgressBarRebderer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_setCapInsetProgressBarRebderer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_setCapInsetsBarRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_setCapInsetsBarRenderer : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_setCapInsetsBarRenderer : Error processing arguments");
        cobj->setCapInsetsBarRenderer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_setCapInsetsBarRenderer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_getCapInsetsProgressBarRebderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_getCapInsetsProgressBarRebderer : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsetsProgressBarRebderer();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_getCapInsetsProgressBarRebderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Slider_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_setScale9Enabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_setScale9Enabled : Error processing arguments");
        cobj->setScale9Enabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_setZoomScale : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_setZoomScale : Error processing arguments");
        cobj->setZoomScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_setZoomScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_setCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_setCapInsets : Error processing arguments");
        cobj->setCapInsets(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_getZoomScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getZoomScale();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_getZoomScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Slider_loadSlidBallTexturePressed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTexturePressed : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTexturePressed : Error processing arguments");
        cobj->loadSlidBallTexturePressed(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        std::string arg0;
        cocos2d::ui::Widget::TextureResType arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Slider_loadSlidBallTexturePressed : Error processing arguments");
        cobj->loadSlidBallTexturePressed(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_loadSlidBallTexturePressed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Slider_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_isScale9Enabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScale9Enabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_isScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Slider_getCapInsetsBarRenderer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_getCapInsetsBarRenderer : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Rect& ret = cobj->getCapInsetsBarRenderer();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_getCapInsetsBarRenderer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Slider_getPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Slider_getPercent : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getPercent();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Slider_getPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Slider_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Slider* ret = cocos2d::ui::Slider::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Slider>(cx, (cocos2d::ui::Slider*)ret);
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
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Slider* ret = cocos2d::ui::Slider::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Slider>(cx, (cocos2d::ui::Slider*)ret);
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
        if (argc == 0) {
            cocos2d::ui::Slider* ret = cocos2d::ui::Slider::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Slider>(cx, (cocos2d::ui::Slider*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_Slider_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Slider_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::Slider::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Slider_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Slider_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::Slider* cobj = new (std::nothrow) cocos2d::ui::Slider();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::Slider> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Slider");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_Slider_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Slider)", obj);
}

static bool js_cocos2d_ui_Slider_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::Slider *nobj = new (std::nothrow) cocos2d::ui::Slider();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Slider");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_Slider(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Slider_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Slider_class->name = "Slider";
    jsb_cocos2d_ui_Slider_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Slider_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Slider_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Slider_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Slider_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Slider_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Slider_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Slider_class->finalize = js_cocos2d_ui_Slider_finalize;
    jsb_cocos2d_ui_Slider_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setPercent", js_cocos2dx_ui_Slider_setPercent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadSlidBallTextureDisabled", js_cocos2dx_ui_Slider_loadSlidBallTextureDisabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadSlidBallTextureNormal", js_cocos2dx_ui_Slider_loadSlidBallTextureNormal, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadBarTexture", js_cocos2dx_ui_Slider_loadBarTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadProgressBarTexture", js_cocos2dx_ui_Slider_loadProgressBarTexture, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadSlidBallTextures", js_cocos2dx_ui_Slider_loadSlidBallTextures, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsetProgressBarRebderer", js_cocos2dx_ui_Slider_setCapInsetProgressBarRebderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsetsBarRenderer", js_cocos2dx_ui_Slider_setCapInsetsBarRenderer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsetsProgressBarRebderer", js_cocos2dx_ui_Slider_getCapInsetsProgressBarRebderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale9Enabled", js_cocos2dx_ui_Slider_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomScale", js_cocos2dx_ui_Slider_setZoomScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsets", js_cocos2dx_ui_Slider_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getZoomScale", js_cocos2dx_ui_Slider_getZoomScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadSlidBallTexturePressed", js_cocos2dx_ui_Slider_loadSlidBallTexturePressed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScale9Enabled", js_cocos2dx_ui_Slider_isScale9Enabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsetsBarRenderer", js_cocos2dx_ui_Slider_getCapInsetsBarRenderer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercent", js_cocos2dx_ui_Slider_getPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_Slider_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_Slider_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_Slider_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Slider_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_Slider_class,
        js_cocos2dx_ui_Slider_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Slider", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Slider> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Slider_class;
        p->proto = jsb_cocos2d_ui_Slider_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_UICCTextField_class;
JSObject *jsb_cocos2d_ui_UICCTextField_prototype;

bool js_cocos2dx_ui_UICCTextField_onTextFieldAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldAttachWithIME : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextFieldTTF* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::TextFieldTTF*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldAttachWithIME : Error processing arguments");
        bool ret = cobj->onTextFieldAttachWithIME(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_onTextFieldAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setPasswordText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setPasswordText : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setPasswordText : Error processing arguments");
        cobj->setPasswordText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setPasswordText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setAttachWithIME : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setAttachWithIME : Error processing arguments");
        cobj->setAttachWithIME(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_getDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_getDeleteBackward : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getDeleteBackward();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_getDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_getAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_getAttachWithIME : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getAttachWithIME();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_getAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_onTextFieldDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldDeleteBackward : Invalid Native Object");
    if (argc == 3) {
        cocos2d::TextFieldTTF* arg0;
        const char* arg1;
        unsigned long arg2;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::TextFieldTTF*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        ok &= jsval_to_ulong(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldDeleteBackward : Error processing arguments");
        bool ret = cobj->onTextFieldDeleteBackward(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_onTextFieldDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_getInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_getInsertText : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getInsertText();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_getInsertText : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_deleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_deleteBackward : Invalid Native Object");
    if (argc == 0) {
        cobj->deleteBackward();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_deleteBackward : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setInsertText : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setInsertText : Error processing arguments");
        cobj->setInsertText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setInsertText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_getDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_getDetachWithIME : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getDetachWithIME();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_getDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_getCharCount(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_getCharCount : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCharCount();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_getCharCount : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_closeIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_closeIME : Invalid Native Object");
    if (argc == 0) {
        cobj->closeIME();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_closeIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setPasswordEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setPasswordEnabled : Error processing arguments");
        cobj->setPasswordEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setPasswordEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setMaxLengthEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setMaxLengthEnabled : Error processing arguments");
        cobj->setMaxLengthEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setMaxLengthEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_isPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_isPasswordEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPasswordEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_isPasswordEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_insertText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_insertText : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        unsigned long arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_ulong(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_insertText : Error processing arguments");
        cobj->insertText(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_insertText : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setPasswordStyleText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setPasswordStyleText : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setPasswordStyleText : Error processing arguments");
        cobj->setPasswordStyleText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setPasswordStyleText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_onTextFieldInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldInsertText : Invalid Native Object");
    if (argc == 3) {
        cocos2d::TextFieldTTF* arg0;
        const char* arg1;
        unsigned long arg2;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::TextFieldTTF*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        ok &= jsval_to_ulong(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldInsertText : Error processing arguments");
        bool ret = cobj->onTextFieldInsertText(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_onTextFieldInsertText : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_onTextFieldDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldDetachWithIME : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextFieldTTF* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::TextFieldTTF*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_onTextFieldDetachWithIME : Error processing arguments");
        bool ret = cobj->onTextFieldDetachWithIME(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_onTextFieldDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_getMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_getMaxLength : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getMaxLength();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_getMaxLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_isMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_isMaxLengthEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isMaxLengthEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_isMaxLengthEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_openIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_openIME : Invalid Native Object");
    if (argc == 0) {
        cobj->openIME();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_openIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setDetachWithIME : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setDetachWithIME : Error processing arguments");
        cobj->setDetachWithIME(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setMaxLength : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setMaxLength : Error processing arguments");
        cobj->setMaxLength(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setMaxLength : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_setDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::UICCTextField* cobj = (cocos2d::ui::UICCTextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_UICCTextField_setDeleteBackward : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_setDeleteBackward : Error processing arguments");
        cobj->setDeleteBackward(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_setDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_UICCTextField_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        double arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_UICCTextField_create : Error processing arguments");
        cocos2d::ui::UICCTextField* ret = cocos2d::ui::UICCTextField::create(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::UICCTextField>(cx, (cocos2d::ui::UICCTextField*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_UICCTextField_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_UICCTextField_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::UICCTextField* cobj = new (std::nothrow) cocos2d::ui::UICCTextField();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::UICCTextField> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::UICCTextField");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_TextFieldTTF_prototype;

void js_cocos2d_ui_UICCTextField_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (UICCTextField)", obj);
}

void js_register_cocos2dx_ui_UICCTextField(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_UICCTextField_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_UICCTextField_class->name = "UICCTextField";
    jsb_cocos2d_ui_UICCTextField_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_UICCTextField_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_UICCTextField_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_UICCTextField_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_UICCTextField_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_UICCTextField_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_UICCTextField_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_UICCTextField_class->finalize = js_cocos2d_ui_UICCTextField_finalize;
    jsb_cocos2d_ui_UICCTextField_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("onTextFieldAttachWithIME", js_cocos2dx_ui_UICCTextField_onTextFieldAttachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPasswordText", js_cocos2dx_ui_UICCTextField_setPasswordText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAttachWithIME", js_cocos2dx_ui_UICCTextField_setAttachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeleteBackward", js_cocos2dx_ui_UICCTextField_getDeleteBackward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAttachWithIME", js_cocos2dx_ui_UICCTextField_getAttachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTextFieldDeleteBackward", js_cocos2dx_ui_UICCTextField_onTextFieldDeleteBackward, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInsertText", js_cocos2dx_ui_UICCTextField_getInsertText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("deleteBackward", js_cocos2dx_ui_UICCTextField_deleteBackward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInsertText", js_cocos2dx_ui_UICCTextField_setInsertText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDetachWithIME", js_cocos2dx_ui_UICCTextField_getDetachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCharCount", js_cocos2dx_ui_UICCTextField_getCharCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("closeIME", js_cocos2dx_ui_UICCTextField_closeIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPasswordEnabled", js_cocos2dx_ui_UICCTextField_setPasswordEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxLengthEnabled", js_cocos2dx_ui_UICCTextField_setMaxLengthEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPasswordEnabled", js_cocos2dx_ui_UICCTextField_isPasswordEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertText", js_cocos2dx_ui_UICCTextField_insertText, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPasswordStyleText", js_cocos2dx_ui_UICCTextField_setPasswordStyleText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTextFieldInsertText", js_cocos2dx_ui_UICCTextField_onTextFieldInsertText, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("onTextFieldDetachWithIME", js_cocos2dx_ui_UICCTextField_onTextFieldDetachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxLength", js_cocos2dx_ui_UICCTextField_getMaxLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isMaxLengthEnabled", js_cocos2dx_ui_UICCTextField_isMaxLengthEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("openIME", js_cocos2dx_ui_UICCTextField_openIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDetachWithIME", js_cocos2dx_ui_UICCTextField_setDetachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxLength", js_cocos2dx_ui_UICCTextField_setMaxLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDeleteBackward", js_cocos2dx_ui_UICCTextField_setDeleteBackward, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_UICCTextField_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_UICCTextField_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_TextFieldTTF_prototype),
        jsb_cocos2d_ui_UICCTextField_class,
        js_cocos2dx_ui_UICCTextField_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "UICCTextField", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::UICCTextField> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_UICCTextField_class;
        p->proto = jsb_cocos2d_ui_UICCTextField_prototype;
        p->parentProto = jsb_cocos2d_TextFieldTTF_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_TextField_class;
JSObject *jsb_cocos2d_ui_TextField_prototype;

bool js_cocos2dx_ui_TextField_setAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setAttachWithIME : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setAttachWithIME : Error processing arguments");
        cobj->setAttachWithIME(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getFontSize : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getFontSize();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getFontSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getString : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setPasswordStyleText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setPasswordStyleText : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setPasswordStyleText : Error processing arguments");
        cobj->setPasswordStyleText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setPasswordStyleText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getDeleteBackward : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getDeleteBackward();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getTextColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getTextColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4B& ret = cobj->getTextColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getTextColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getPlaceHolder : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getPlaceHolder();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getPlaceHolder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getAttachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getAttachWithIME : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getAttachWithIME();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getAttachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setFontName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setFontName : Error processing arguments");
        cobj->setFontName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getInsertText : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getInsertText();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getInsertText : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setInsertText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setInsertText : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setInsertText : Error processing arguments");
        cobj->setInsertText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setInsertText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_setString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setString : Error processing arguments");
        cobj->setString(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getDetachWithIME : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getDetachWithIME();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setTextVerticalAlignment : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextVAlignment arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setTextVerticalAlignment : Error processing arguments");
        cobj->setTextVerticalAlignment(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setTextVerticalAlignment : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_didNotSelectSelf(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_didNotSelectSelf : Invalid Native Object");
    if (argc == 0) {
        cobj->didNotSelectSelf();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_didNotSelectSelf : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getFontName : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getFontName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getFontName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setTextAreaSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setTextAreaSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setTextAreaSize : Error processing arguments");
        cobj->setTextAreaSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setTextAreaSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_attachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_attachWithIME : Invalid Native Object");
    if (argc == 0) {
        cobj->attachWithIME();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_attachWithIME : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getStringLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getStringLength : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getStringLength();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getStringLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getAutoRenderSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getAutoRenderSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getAutoRenderSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getAutoRenderSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setPasswordEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setPasswordEnabled : Error processing arguments");
        cobj->setPasswordEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setPasswordEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getPlaceHolderColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getPlaceHolderColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color4B& ret = cobj->getPlaceHolderColor();
        jsval jsret = JSVAL_NULL;
        jsret = cccolor4b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getPlaceHolderColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_getPasswordStyleText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getPasswordStyleText : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getPasswordStyleText();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getPasswordStyleText : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setMaxLengthEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setMaxLengthEnabled : Error processing arguments");
        cobj->setMaxLengthEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setMaxLengthEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_isPasswordEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_isPasswordEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPasswordEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_isPasswordEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setDeleteBackward(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setDeleteBackward : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setDeleteBackward : Error processing arguments");
        cobj->setDeleteBackward(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setDeleteBackward : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getTextHorizontalAlignment : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTextHorizontalAlignment();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getTextHorizontalAlignment : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setFontSize : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setFontSize : Error processing arguments");
        cobj->setFontSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_setPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setPlaceHolder : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setPlaceHolder : Error processing arguments");
        cobj->setPlaceHolder(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setPlaceHolder : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_setPlaceHolderColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::TextField* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setPlaceHolderColor : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setPlaceHolderColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setPlaceHolderColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setPlaceHolderColor : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_TextField_setTextHorizontalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setTextHorizontalAlignment : Invalid Native Object");
    if (argc == 1) {
        cocos2d::TextHAlignment arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setTextHorizontalAlignment : Error processing arguments");
        cobj->setTextHorizontalAlignment(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setTextHorizontalAlignment : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_setTextColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setTextColor : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Color4B arg0;
        ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setTextColor : Error processing arguments");
        cobj->setTextColor(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setTextColor : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getMaxLength : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getMaxLength();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getMaxLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_isMaxLengthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_isMaxLengthEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isMaxLengthEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_isMaxLengthEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setDetachWithIME(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setDetachWithIME : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setDetachWithIME : Error processing arguments");
        cobj->setDetachWithIME(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setDetachWithIME : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getTextVerticalAlignment(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getTextVerticalAlignment : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getTextVerticalAlignment();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getTextVerticalAlignment : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_setTouchAreaEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setTouchAreaEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setTouchAreaEnabled : Error processing arguments");
        cobj->setTouchAreaEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setTouchAreaEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_setMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setMaxLength : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setMaxLength : Error processing arguments");
        cobj->setMaxLength(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setMaxLength : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_setTouchSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_setTouchSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextField_setTouchSize : Error processing arguments");
        cobj->setTouchSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_setTouchSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextField_getTouchSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextField_getTouchSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getTouchSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextField_getTouchSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextField_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            int arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::TextField* ret = cocos2d::ui::TextField::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::TextField>(cx, (cocos2d::ui::TextField*)ret);
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
        if (argc == 0) {
            cocos2d::ui::TextField* ret = cocos2d::ui::TextField::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::TextField>(cx, (cocos2d::ui::TextField*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_TextField_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_TextField_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::TextField::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_TextField_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_TextField_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::TextField* cobj = new (std::nothrow) cocos2d::ui::TextField();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::TextField> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::TextField");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_TextField_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextField)", obj);
}

static bool js_cocos2d_ui_TextField_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::TextField *nobj = new (std::nothrow) cocos2d::ui::TextField();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::TextField");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_TextField(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_TextField_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_TextField_class->name = "TextField";
    jsb_cocos2d_ui_TextField_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_TextField_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_TextField_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_TextField_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_TextField_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_TextField_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_TextField_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_TextField_class->finalize = js_cocos2d_ui_TextField_finalize;
    jsb_cocos2d_ui_TextField_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setAttachWithIME", js_cocos2dx_ui_TextField_setAttachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFontSize", js_cocos2dx_ui_TextField_getFontSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_ui_TextField_getString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPasswordStyleText", js_cocos2dx_ui_TextField_setPasswordStyleText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDeleteBackward", js_cocos2dx_ui_TextField_getDeleteBackward, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextColor", js_cocos2dx_ui_TextField_getTextColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlaceHolder", js_cocos2dx_ui_TextField_getPlaceHolder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAttachWithIME", js_cocos2dx_ui_TextField_getAttachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontName", js_cocos2dx_ui_TextField_setFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInsertText", js_cocos2dx_ui_TextField_getInsertText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInsertText", js_cocos2dx_ui_TextField_setInsertText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_ui_TextField_setString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDetachWithIME", js_cocos2dx_ui_TextField_getDetachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextVerticalAlignment", js_cocos2dx_ui_TextField_setTextVerticalAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("didNotSelectSelf", js_cocos2dx_ui_TextField_didNotSelectSelf, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFontName", js_cocos2dx_ui_TextField_getFontName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextAreaSize", js_cocos2dx_ui_TextField_setTextAreaSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("attachWithIME", js_cocos2dx_ui_TextField_attachWithIME, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringLength", js_cocos2dx_ui_TextField_getStringLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAutoRenderSize", js_cocos2dx_ui_TextField_getAutoRenderSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPasswordEnabled", js_cocos2dx_ui_TextField_setPasswordEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlaceHolderColor", js_cocos2dx_ui_TextField_getPlaceHolderColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPasswordStyleText", js_cocos2dx_ui_TextField_getPasswordStyleText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxLengthEnabled", js_cocos2dx_ui_TextField_setMaxLengthEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPasswordEnabled", js_cocos2dx_ui_TextField_isPasswordEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDeleteBackward", js_cocos2dx_ui_TextField_setDeleteBackward, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextHorizontalAlignment", js_cocos2dx_ui_TextField_getTextHorizontalAlignment, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontSize", js_cocos2dx_ui_TextField_setFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceHolder", js_cocos2dx_ui_TextField_setPlaceHolder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceHolderColor", js_cocos2dx_ui_TextField_setPlaceHolderColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextHorizontalAlignment", js_cocos2dx_ui_TextField_setTextHorizontalAlignment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTextColor", js_cocos2dx_ui_TextField_setTextColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxLength", js_cocos2dx_ui_TextField_getMaxLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isMaxLengthEnabled", js_cocos2dx_ui_TextField_isMaxLengthEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDetachWithIME", js_cocos2dx_ui_TextField_setDetachWithIME, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTextVerticalAlignment", js_cocos2dx_ui_TextField_getTextVerticalAlignment, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchAreaEnabled", js_cocos2dx_ui_TextField_setTouchAreaEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxLength", js_cocos2dx_ui_TextField_setMaxLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchSize", js_cocos2dx_ui_TextField_setTouchSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchSize", js_cocos2dx_ui_TextField_getTouchSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_TextField_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_TextField_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_TextField_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_TextField_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_TextField_class,
        js_cocos2dx_ui_TextField_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "TextField", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::TextField> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_TextField_class;
        p->proto = jsb_cocos2d_ui_TextField_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_TextBMFont_class;
JSObject *jsb_cocos2d_ui_TextBMFont_prototype;

bool js_cocos2dx_ui_TextBMFont_setFntFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextBMFont* cobj = (cocos2d::ui::TextBMFont *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextBMFont_setFntFile : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextBMFont_setFntFile : Error processing arguments");
        cobj->setFntFile(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextBMFont_setFntFile : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextBMFont_getStringLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextBMFont* cobj = (cocos2d::ui::TextBMFont *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextBMFont_getStringLength : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getStringLength();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextBMFont_getStringLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextBMFont_setString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextBMFont* cobj = (cocos2d::ui::TextBMFont *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextBMFont_setString : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_TextBMFont_setString : Error processing arguments");
        cobj->setString(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextBMFont_setString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_TextBMFont_getString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextBMFont* cobj = (cocos2d::ui::TextBMFont *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_TextBMFont_getString : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getString();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_TextBMFont_getString : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_TextBMFont_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::TextBMFont* ret = cocos2d::ui::TextBMFont::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::TextBMFont>(cx, (cocos2d::ui::TextBMFont*)ret);
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
        if (argc == 0) {
            cocos2d::ui::TextBMFont* ret = cocos2d::ui::TextBMFont::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::TextBMFont>(cx, (cocos2d::ui::TextBMFont*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_TextBMFont_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_TextBMFont_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::TextBMFont::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_TextBMFont_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_TextBMFont_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::TextBMFont* cobj = new (std::nothrow) cocos2d::ui::TextBMFont();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::TextBMFont> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::TextBMFont");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_TextBMFont_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (TextBMFont)", obj);
}

static bool js_cocos2d_ui_TextBMFont_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::TextBMFont *nobj = new (std::nothrow) cocos2d::ui::TextBMFont();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::TextBMFont");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_TextBMFont(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_TextBMFont_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_TextBMFont_class->name = "TextBMFont";
    jsb_cocos2d_ui_TextBMFont_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_TextBMFont_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_TextBMFont_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_TextBMFont_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_TextBMFont_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_TextBMFont_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_TextBMFont_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_TextBMFont_class->finalize = js_cocos2d_ui_TextBMFont_finalize;
    jsb_cocos2d_ui_TextBMFont_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setFntFile", js_cocos2dx_ui_TextBMFont_setFntFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStringLength", js_cocos2dx_ui_TextBMFont_getStringLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_ui_TextBMFont_setString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getString", js_cocos2dx_ui_TextBMFont_getString, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_TextBMFont_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_TextBMFont_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_TextBMFont_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_TextBMFont_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_TextBMFont_class,
        js_cocos2dx_ui_TextBMFont_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "TextBMFont", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::TextBMFont> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_TextBMFont_class;
        p->proto = jsb_cocos2d_ui_TextBMFont_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_PageView_class;
JSObject *jsb_cocos2d_ui_PageView_prototype;

bool js_cocos2dx_ui_PageView_getCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_getCustomScrollThreshold : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCustomScrollThreshold();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_getCustomScrollThreshold : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_PageView_getCurPageIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_getCurPageIndex : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getCurPageIndex();
        jsval jsret = JSVAL_NULL;
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_getCurPageIndex : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_PageView_addWidgetToPage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_addWidgetToPage : Invalid Native Object");
    if (argc == 3) {
        cocos2d::ui::Widget* arg0;
        ssize_t arg1;
        bool arg2;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ssize(cx, args.get(1), &arg1);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_addWidgetToPage : Error processing arguments");
        cobj->addWidgetToPage(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_addWidgetToPage : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_PageView_isUsingCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_isUsingCustomScrollThreshold : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isUsingCustomScrollThreshold();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_isUsingCustomScrollThreshold : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_PageView_getPage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_getPage : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_getPage : Error processing arguments");
        cocos2d::ui::Layout* ret = cobj->getPage(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Layout>(cx, (cocos2d::ui::Layout*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_getPage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_removePage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_removePage : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Layout* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Layout*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_removePage : Error processing arguments");
        cobj->removePage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_removePage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_setUsingCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_setUsingCustomScrollThreshold : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_setUsingCustomScrollThreshold : Error processing arguments");
        cobj->setUsingCustomScrollThreshold(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_setUsingCustomScrollThreshold : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_setCustomScrollThreshold(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_setCustomScrollThreshold : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_setCustomScrollThreshold : Error processing arguments");
        cobj->setCustomScrollThreshold(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_setCustomScrollThreshold : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_insertPage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_insertPage : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::Layout* arg0;
        int arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Layout*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_insertPage : Error processing arguments");
        cobj->insertPage(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_insertPage : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_PageView_scrollToPage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_scrollToPage : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_scrollToPage : Error processing arguments");
        cobj->scrollToPage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_scrollToPage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_removePageAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_removePageAtIndex : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_removePageAtIndex : Error processing arguments");
        cobj->removePageAtIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_removePageAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_getPages(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_getPages : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::ui::Layout *>& ret = cobj->getPages();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_getPages : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_PageView_removeAllPages(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_removeAllPages : Invalid Native Object");
    if (argc == 0) {
        cobj->removeAllPages();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_removeAllPages : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_PageView_addPage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_PageView_addPage : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Layout* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Layout*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_PageView_addPage : Error processing arguments");
        cobj->addPage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_PageView_addPage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_PageView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::PageView* ret = cocos2d::ui::PageView::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::PageView>(cx, (cocos2d::ui::PageView*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_PageView_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_PageView_createInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::Ref* ret = cocos2d::ui::PageView::createInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Ref>(cx, (cocos2d::Ref*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_PageView_createInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_PageView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::PageView* cobj = new (std::nothrow) cocos2d::ui::PageView();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::PageView> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::PageView");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Layout_prototype;

void js_cocos2d_ui_PageView_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PageView)", obj);
}

static bool js_cocos2d_ui_PageView_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::PageView *nobj = new (std::nothrow) cocos2d::ui::PageView();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::PageView");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_PageView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_PageView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_PageView_class->name = "PageView";
    jsb_cocos2d_ui_PageView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_PageView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_PageView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_PageView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_PageView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_PageView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_PageView_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_PageView_class->finalize = js_cocos2d_ui_PageView_finalize;
    jsb_cocos2d_ui_PageView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getCustomScrollThreshold", js_cocos2dx_ui_PageView_getCustomScrollThreshold, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurPageIndex", js_cocos2dx_ui_PageView_getCurPageIndex, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addWidgetToPage", js_cocos2dx_ui_PageView_addWidgetToPage, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isUsingCustomScrollThreshold", js_cocos2dx_ui_PageView_isUsingCustomScrollThreshold, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPage", js_cocos2dx_ui_PageView_getPage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removePage", js_cocos2dx_ui_PageView_removePage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUsingCustomScrollThreshold", js_cocos2dx_ui_PageView_setUsingCustomScrollThreshold, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCustomScrollThreshold", js_cocos2dx_ui_PageView_setCustomScrollThreshold, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertPage", js_cocos2dx_ui_PageView_insertPage, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollToPage", js_cocos2dx_ui_PageView_scrollToPage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removePageAtIndex", js_cocos2dx_ui_PageView_removePageAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPages", js_cocos2dx_ui_PageView_getPages, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeAllPages", js_cocos2dx_ui_PageView_removeAllPages, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addPage", js_cocos2dx_ui_PageView_addPage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_PageView_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_PageView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createInstance", js_cocos2dx_ui_PageView_createInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_PageView_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Layout_prototype),
        jsb_cocos2d_ui_PageView_class,
        js_cocos2dx_ui_PageView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PageView", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::PageView> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_PageView_class;
        p->proto = jsb_cocos2d_ui_PageView_prototype;
        p->parentProto = jsb_cocos2d_ui_Layout_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Helper_class;
JSObject *jsb_cocos2d_ui_Helper_prototype;

bool js_cocos2dx_ui_Helper_getSubStringOfUTF8String(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        std::string arg0;
        unsigned long arg1;
        unsigned long arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_ulong(cx, args.get(1), &arg1);
        ok &= jsval_to_ulong(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_getSubStringOfUTF8String : Error processing arguments");
        std::string ret = cocos2d::ui::Helper::getSubStringOfUTF8String(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_getSubStringOfUTF8String : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Helper_changeLayoutSystemActiveState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_changeLayoutSystemActiveState : Error processing arguments");
        cocos2d::ui::Helper::changeLayoutSystemActiveState(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_changeLayoutSystemActiveState : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Helper_seekActionWidgetByActionTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::ui::Widget* arg0;
        int arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_seekActionWidgetByActionTag : Error processing arguments");
        cocos2d::ui::Widget* ret = cocos2d::ui::Helper::seekActionWidgetByActionTag(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_seekActionWidgetByActionTag : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Helper_seekWidgetByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::ui::Widget* arg0;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_seekWidgetByName : Error processing arguments");
        cocos2d::ui::Widget* ret = cocos2d::ui::Helper::seekWidgetByName(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_seekWidgetByName : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Helper_seekWidgetByTag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::ui::Widget* arg0;
        int arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Widget*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_seekWidgetByTag : Error processing arguments");
        cocos2d::ui::Widget* ret = cocos2d::ui::Helper::seekWidgetByTag(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Widget>(cx, (cocos2d::ui::Widget*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_seekWidgetByTag : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Helper_restrictCapInsetRect(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Rect arg0;
        cocos2d::Size arg1;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_restrictCapInsetRect : Error processing arguments");
        cocos2d::Rect ret = cocos2d::ui::Helper::restrictCapInsetRect(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_restrictCapInsetRect : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_Helper_doLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_doLayout : Error processing arguments");
        cocos2d::ui::Helper::doLayout(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_Helper_doLayout : wrong number of arguments");
    return false;
}



void js_cocos2d_ui_Helper_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Helper)", obj);
}

void js_register_cocos2dx_ui_Helper(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Helper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Helper_class->name = "Helper";
    jsb_cocos2d_ui_Helper_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Helper_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Helper_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Helper_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Helper_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Helper_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Helper_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Helper_class->finalize = js_cocos2d_ui_Helper_finalize;
    jsb_cocos2d_ui_Helper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getSubStringOfUTF8String", js_cocos2dx_ui_Helper_getSubStringOfUTF8String, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeLayoutSystemActiveState", js_cocos2dx_ui_Helper_changeLayoutSystemActiveState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("seekActionWidgetByActionTag", js_cocos2dx_ui_Helper_seekActionWidgetByActionTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("seekWidgetByName", js_cocos2dx_ui_Helper_seekWidgetByName, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("seekWidgetByTag", js_cocos2dx_ui_Helper_seekWidgetByTag, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("restrictCapInsetRect", js_cocos2dx_ui_Helper_restrictCapInsetRect, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("doLayout", js_cocos2dx_ui_Helper_doLayout, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Helper_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_ui_Helper_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Helper", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Helper> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Helper_class;
        p->proto = jsb_cocos2d_ui_Helper_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RichElement_class;
JSObject *jsb_cocos2d_ui_RichElement_prototype;

bool js_cocos2dx_ui_RichElement_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichElement* cobj = (cocos2d::ui::RichElement *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichElement_init : Invalid Native Object");
    if (argc == 3) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElement_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichElement_init : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ui_RichElement_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RichElement* cobj = new (std::nothrow) cocos2d::ui::RichElement();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RichElement> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElement");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}



void js_cocos2d_ui_RichElement_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RichElement)", obj);
}

static bool js_cocos2d_ui_RichElement_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::RichElement *nobj = new (std::nothrow) cocos2d::ui::RichElement();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElement");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_RichElement(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RichElement_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RichElement_class->name = "RichElement";
    jsb_cocos2d_ui_RichElement_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElement_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RichElement_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElement_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RichElement_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RichElement_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RichElement_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RichElement_class->finalize = js_cocos2d_ui_RichElement_finalize;
    jsb_cocos2d_ui_RichElement_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_cocos2dx_ui_RichElement_init, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_RichElement_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_ui_RichElement_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_cocos2d_ui_RichElement_class,
        js_cocos2dx_ui_RichElement_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RichElement", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RichElement> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RichElement_class;
        p->proto = jsb_cocos2d_ui_RichElement_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RichElementText_class;
JSObject *jsb_cocos2d_ui_RichElementText_prototype;

bool js_cocos2dx_ui_RichElementText_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichElementText* cobj = (cocos2d::ui::RichElementText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichElementText_init : Invalid Native Object");
    if (argc == 6) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        std::string arg4;
        double arg5;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        ok &= JS::ToNumber( cx, args.get(5), &arg5) && !isnan(arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElementText_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichElementText_init : wrong number of arguments: %d, was expecting %d", argc, 6);
    return false;
}
bool js_cocos2dx_ui_RichElementText_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 6) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        std::string arg4;
        double arg5;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        ok &= jsval_to_std_string(cx, args.get(4), &arg4);
        ok &= JS::ToNumber( cx, args.get(5), &arg5) && !isnan(arg5);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElementText_create : Error processing arguments");
        cocos2d::ui::RichElementText* ret = cocos2d::ui::RichElementText::create(arg0, arg1, arg2, arg3, arg4, arg5);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RichElementText>(cx, (cocos2d::ui::RichElementText*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_RichElementText_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_RichElementText_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RichElementText* cobj = new (std::nothrow) cocos2d::ui::RichElementText();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RichElementText> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElementText");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_RichElement_prototype;

void js_cocos2d_ui_RichElementText_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RichElementText)", obj);
}

static bool js_cocos2d_ui_RichElementText_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::RichElementText *nobj = new (std::nothrow) cocos2d::ui::RichElementText();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElementText");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_RichElementText(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RichElementText_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RichElementText_class->name = "RichElementText";
    jsb_cocos2d_ui_RichElementText_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElementText_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RichElementText_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElementText_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RichElementText_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RichElementText_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RichElementText_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RichElementText_class->finalize = js_cocos2d_ui_RichElementText_finalize;
    jsb_cocos2d_ui_RichElementText_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_cocos2dx_ui_RichElementText_init, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_RichElementText_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_RichElementText_create, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_RichElementText_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_RichElement_prototype),
        jsb_cocos2d_ui_RichElementText_class,
        js_cocos2dx_ui_RichElementText_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RichElementText", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RichElementText> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RichElementText_class;
        p->proto = jsb_cocos2d_ui_RichElementText_prototype;
        p->parentProto = jsb_cocos2d_ui_RichElement_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RichElementImage_class;
JSObject *jsb_cocos2d_ui_RichElementImage_prototype;

bool js_cocos2dx_ui_RichElementImage_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichElementImage* cobj = (cocos2d::ui::RichElementImage *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichElementImage_init : Invalid Native Object");
    if (argc == 4) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElementImage_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichElementImage_init : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_ui_RichElementImage_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        std::string arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElementImage_create : Error processing arguments");
        cocos2d::ui::RichElementImage* ret = cocos2d::ui::RichElementImage::create(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RichElementImage>(cx, (cocos2d::ui::RichElementImage*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_RichElementImage_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_RichElementImage_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RichElementImage* cobj = new (std::nothrow) cocos2d::ui::RichElementImage();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RichElementImage> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElementImage");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_RichElement_prototype;

void js_cocos2d_ui_RichElementImage_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RichElementImage)", obj);
}

static bool js_cocos2d_ui_RichElementImage_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::RichElementImage *nobj = new (std::nothrow) cocos2d::ui::RichElementImage();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElementImage");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_RichElementImage(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RichElementImage_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RichElementImage_class->name = "RichElementImage";
    jsb_cocos2d_ui_RichElementImage_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElementImage_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RichElementImage_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElementImage_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RichElementImage_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RichElementImage_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RichElementImage_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RichElementImage_class->finalize = js_cocos2d_ui_RichElementImage_finalize;
    jsb_cocos2d_ui_RichElementImage_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_cocos2dx_ui_RichElementImage_init, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_RichElementImage_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_RichElementImage_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_RichElementImage_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_RichElement_prototype),
        jsb_cocos2d_ui_RichElementImage_class,
        js_cocos2dx_ui_RichElementImage_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RichElementImage", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RichElementImage> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RichElementImage_class;
        p->proto = jsb_cocos2d_ui_RichElementImage_prototype;
        p->parentProto = jsb_cocos2d_ui_RichElement_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RichElementCustomNode_class;
JSObject *jsb_cocos2d_ui_RichElementCustomNode_prototype;

bool js_cocos2dx_ui_RichElementCustomNode_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichElementCustomNode* cobj = (cocos2d::ui::RichElementCustomNode *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichElementCustomNode_init : Invalid Native Object");
    if (argc == 4) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        cocos2d::Node* arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        do {
            if (args.get(3).isNull()) { arg3 = nullptr; break; }
            if (!args.get(3).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(3).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg3 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElementCustomNode_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichElementCustomNode_init : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_ui_RichElementCustomNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        int arg0;
        cocos2d::Color3B arg1;
        uint16_t arg2;
        cocos2d::Node* arg3;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_cccolor3b(cx, args.get(1), &arg1);
        ok &= jsval_to_uint16(cx, args.get(2), &arg2);
        do {
            if (args.get(3).isNull()) { arg3 = nullptr; break; }
            if (!args.get(3).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(3).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg3 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichElementCustomNode_create : Error processing arguments");
        cocos2d::ui::RichElementCustomNode* ret = cocos2d::ui::RichElementCustomNode::create(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RichElementCustomNode>(cx, (cocos2d::ui::RichElementCustomNode*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_RichElementCustomNode_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_RichElementCustomNode_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RichElementCustomNode* cobj = new (std::nothrow) cocos2d::ui::RichElementCustomNode();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RichElementCustomNode> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElementCustomNode");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_RichElement_prototype;

void js_cocos2d_ui_RichElementCustomNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RichElementCustomNode)", obj);
}

static bool js_cocos2d_ui_RichElementCustomNode_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::RichElementCustomNode *nobj = new (std::nothrow) cocos2d::ui::RichElementCustomNode();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichElementCustomNode");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_RichElementCustomNode(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RichElementCustomNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RichElementCustomNode_class->name = "RichElementCustomNode";
    jsb_cocos2d_ui_RichElementCustomNode_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RichElementCustomNode_class->finalize = js_cocos2d_ui_RichElementCustomNode_finalize;
    jsb_cocos2d_ui_RichElementCustomNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("init", js_cocos2dx_ui_RichElementCustomNode_init, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_RichElementCustomNode_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_RichElementCustomNode_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_RichElementCustomNode_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_RichElement_prototype),
        jsb_cocos2d_ui_RichElementCustomNode_class,
        js_cocos2dx_ui_RichElementCustomNode_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RichElementCustomNode", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RichElementCustomNode> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RichElementCustomNode_class;
        p->proto = jsb_cocos2d_ui_RichElementCustomNode_prototype;
        p->parentProto = jsb_cocos2d_ui_RichElement_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RichText_class;
JSObject *jsb_cocos2d_ui_RichText_prototype;

bool js_cocos2dx_ui_RichText_insertElement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichText* cobj = (cocos2d::ui::RichText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichText_insertElement : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::RichElement* arg0;
        int arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::RichElement*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichText_insertElement : Error processing arguments");
        cobj->insertElement(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichText_insertElement : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_RichText_pushBackElement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichText* cobj = (cocos2d::ui::RichText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichText_pushBackElement : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::RichElement* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::RichElement*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichText_pushBackElement : Error processing arguments");
        cobj->pushBackElement(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichText_pushBackElement : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_RichText_setVerticalSpace(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichText* cobj = (cocos2d::ui::RichText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichText_setVerticalSpace : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RichText_setVerticalSpace : Error processing arguments");
        cobj->setVerticalSpace(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichText_setVerticalSpace : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_RichText_formatText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RichText* cobj = (cocos2d::ui::RichText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichText_formatText : Invalid Native Object");
    if (argc == 0) {
        cobj->formatText();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RichText_formatText : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_RichText_removeElement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::RichText* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::RichText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RichText_removeElement : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::ui::RichElement* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::ui::RichElement*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj->removeElement(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            int arg0;
            ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
            if (!ok) { ok = true; break; }
            cobj->removeElement(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_RichText_removeElement : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_RichText_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::RichText* ret = cocos2d::ui::RichText::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RichText>(cx, (cocos2d::ui::RichText*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_RichText_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_RichText_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RichText* cobj = new (std::nothrow) cocos2d::ui::RichText();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RichText> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichText");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_RichText_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RichText)", obj);
}

static bool js_cocos2d_ui_RichText_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::RichText *nobj = new (std::nothrow) cocos2d::ui::RichText();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RichText");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_RichText(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RichText_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RichText_class->name = "RichText";
    jsb_cocos2d_ui_RichText_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichText_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RichText_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RichText_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RichText_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RichText_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RichText_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RichText_class->finalize = js_cocos2d_ui_RichText_finalize;
    jsb_cocos2d_ui_RichText_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("insertElement", js_cocos2dx_ui_RichText_insertElement, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushBackElement", js_cocos2dx_ui_RichText_pushBackElement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVerticalSpace", js_cocos2dx_ui_RichText_setVerticalSpace, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("formatText", js_cocos2dx_ui_RichText_formatText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeElement", js_cocos2dx_ui_RichText_removeElement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_RichText_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_RichText_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_RichText_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_RichText_class,
        js_cocos2dx_ui_RichText_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RichText", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RichText> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RichText_class;
        p->proto = jsb_cocos2d_ui_RichText_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_HBox_class;
JSObject *jsb_cocos2d_ui_HBox_prototype;

bool js_cocos2dx_ui_HBox_initWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::HBox* cobj = (cocos2d::ui::HBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_HBox_initWithSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_HBox_initWithSize : Error processing arguments");
        bool ret = cobj->initWithSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_HBox_initWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_HBox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::HBox* ret = cocos2d::ui::HBox::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::HBox>(cx, (cocos2d::ui::HBox*)ret);
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
        if (argc == 0) {
            cocos2d::ui::HBox* ret = cocos2d::ui::HBox::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::HBox>(cx, (cocos2d::ui::HBox*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_HBox_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_HBox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::HBox* cobj = new (std::nothrow) cocos2d::ui::HBox();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::HBox> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::HBox");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Layout_prototype;

void js_cocos2d_ui_HBox_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (HBox)", obj);
}

static bool js_cocos2d_ui_HBox_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::HBox *nobj = new (std::nothrow) cocos2d::ui::HBox();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::HBox");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_HBox(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_HBox_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_HBox_class->name = "HBox";
    jsb_cocos2d_ui_HBox_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_HBox_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_HBox_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_HBox_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_HBox_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_HBox_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_HBox_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_HBox_class->finalize = js_cocos2d_ui_HBox_finalize;
    jsb_cocos2d_ui_HBox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithSize", js_cocos2dx_ui_HBox_initWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_HBox_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_HBox_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_HBox_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Layout_prototype),
        jsb_cocos2d_ui_HBox_class,
        js_cocos2dx_ui_HBox_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "HBox", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::HBox> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_HBox_class;
        p->proto = jsb_cocos2d_ui_HBox_prototype;
        p->parentProto = jsb_cocos2d_ui_Layout_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_VBox_class;
JSObject *jsb_cocos2d_ui_VBox_prototype;

bool js_cocos2dx_ui_VBox_initWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::VBox* cobj = (cocos2d::ui::VBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_VBox_initWithSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_VBox_initWithSize : Error processing arguments");
        bool ret = cobj->initWithSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_VBox_initWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_VBox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::VBox* ret = cocos2d::ui::VBox::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::VBox>(cx, (cocos2d::ui::VBox*)ret);
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
        if (argc == 0) {
            cocos2d::ui::VBox* ret = cocos2d::ui::VBox::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::VBox>(cx, (cocos2d::ui::VBox*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_VBox_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_VBox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::VBox* cobj = new (std::nothrow) cocos2d::ui::VBox();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::VBox> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::VBox");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Layout_prototype;

void js_cocos2d_ui_VBox_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (VBox)", obj);
}

static bool js_cocos2d_ui_VBox_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::VBox *nobj = new (std::nothrow) cocos2d::ui::VBox();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::VBox");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_VBox(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_VBox_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_VBox_class->name = "VBox";
    jsb_cocos2d_ui_VBox_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_VBox_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_VBox_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_VBox_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_VBox_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_VBox_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_VBox_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_VBox_class->finalize = js_cocos2d_ui_VBox_finalize;
    jsb_cocos2d_ui_VBox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithSize", js_cocos2dx_ui_VBox_initWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_VBox_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_VBox_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_VBox_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Layout_prototype),
        jsb_cocos2d_ui_VBox_class,
        js_cocos2dx_ui_VBox_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "VBox", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::VBox> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_VBox_class;
        p->proto = jsb_cocos2d_ui_VBox_prototype;
        p->parentProto = jsb_cocos2d_ui_Layout_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_RelativeBox_class;
JSObject *jsb_cocos2d_ui_RelativeBox_prototype;

bool js_cocos2dx_ui_RelativeBox_initWithSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::RelativeBox* cobj = (cocos2d::ui::RelativeBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_RelativeBox_initWithSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_RelativeBox_initWithSize : Error processing arguments");
        bool ret = cobj->initWithSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_RelativeBox_initWithSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_RelativeBox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::RelativeBox* ret = cocos2d::ui::RelativeBox::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RelativeBox>(cx, (cocos2d::ui::RelativeBox*)ret);
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
        if (argc == 0) {
            cocos2d::ui::RelativeBox* ret = cocos2d::ui::RelativeBox::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::RelativeBox>(cx, (cocos2d::ui::RelativeBox*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_RelativeBox_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_RelativeBox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::RelativeBox* cobj = new (std::nothrow) cocos2d::ui::RelativeBox();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::RelativeBox> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RelativeBox");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Layout_prototype;

void js_cocos2d_ui_RelativeBox_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (RelativeBox)", obj);
}

static bool js_cocos2d_ui_RelativeBox_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::RelativeBox *nobj = new (std::nothrow) cocos2d::ui::RelativeBox();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::RelativeBox");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_RelativeBox(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_RelativeBox_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_RelativeBox_class->name = "RelativeBox";
    jsb_cocos2d_ui_RelativeBox_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RelativeBox_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_RelativeBox_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_RelativeBox_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_RelativeBox_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_RelativeBox_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_RelativeBox_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_RelativeBox_class->finalize = js_cocos2d_ui_RelativeBox_finalize;
    jsb_cocos2d_ui_RelativeBox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithSize", js_cocos2dx_ui_RelativeBox_initWithSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_RelativeBox_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_RelativeBox_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_RelativeBox_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Layout_prototype),
        jsb_cocos2d_ui_RelativeBox_class,
        js_cocos2dx_ui_RelativeBox_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "RelativeBox", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::RelativeBox> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_RelativeBox_class;
        p->proto = jsb_cocos2d_ui_RelativeBox_prototype;
        p->parentProto = jsb_cocos2d_ui_Layout_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_Scale9Sprite_class;
JSObject *jsb_cocos2d_ui_Scale9Sprite_prototype;

bool js_cocos2dx_ui_Scale9Sprite_disableCascadeColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_disableCascadeColor : Invalid Native Object");
    if (argc == 0) {
        cobj->disableCascadeColor();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_disableCascadeColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_updateWithSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Scale9Sprite* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_updateWithSprite : Invalid Native Object");
    do {
        if (argc == 6) {
            cocos2d::Sprite* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cocos2d::Vec2 arg3;
            ok &= jsval_to_vector2(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Size arg4;
            ok &= jsval_to_ccsize(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg5;
            ok &= jsval_to_ccrect(cx, args.get(5), &arg5);
            if (!ok) { ok = true; break; }
            bool ret = cobj->updateWithSprite(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cocos2d::Rect arg3;
            ok &= jsval_to_ccrect(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            bool ret = cobj->updateWithSprite(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_updateWithSprite : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_isFlippedX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_isFlippedX : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFlippedX();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_isFlippedX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setScale9Enabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setScale9Enabled : Error processing arguments");
        cobj->setScale9Enabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setFlippedY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setFlippedY : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setFlippedY : Error processing arguments");
        cobj->setFlippedY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setFlippedY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setFlippedX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setFlippedX : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setFlippedX : Error processing arguments");
        cobj->setFlippedX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setFlippedX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets : Error processing arguments");
        cocos2d::ui::Scale9Sprite* ret = cobj->resizableSpriteWithCapInsets(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity : Invalid Native Object");
    if (argc == 0) {
        cobj->disableCascadeOpacity();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getState : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getState();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Scale9Sprite::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setState : Error processing arguments");
        cobj->setState(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setInsetBottom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetBottom : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetBottom : Error processing arguments");
        cobj->setInsetBottom(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setInsetBottom : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Scale9Sprite* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSpriteFrameName(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSpriteFrameName(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getSprite();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setInsetTop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetTop : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetTop : Error processing arguments");
        cobj->setInsetTop(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setInsetTop : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Scale9Sprite* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_init : Invalid Native Object");
    do {
        if (argc == 3) {
            cocos2d::Sprite* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg2;
            ok &= jsval_to_ccrect(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 4) {
            cocos2d::Sprite* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cocos2d::Rect arg3;
            ok &= jsval_to_ccrect(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 6) {
            cocos2d::Sprite* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            cocos2d::Vec2 arg3;
            ok &= jsval_to_vector2(cx, args.get(3), &arg3);
            if (!ok) { ok = true; break; }
            cocos2d::Size arg4;
            ok &= jsval_to_ccsize(cx, args.get(4), &arg4);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg5;
            ok &= jsval_to_ccrect(cx, args.get(5), &arg5);
            if (!ok) { ok = true; break; }
            bool ret = cobj->init(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_init : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setPreferredSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setPreferredSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setPreferredSize : Error processing arguments");
        cobj->setPreferredSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setPreferredSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setSpriteFrame : Invalid Native Object");
    if (argc == 1) {
        cocos2d::SpriteFrame* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setSpriteFrame : Error processing arguments");
        cobj->setSpriteFrame(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::SpriteFrame* arg0;
        cocos2d::Rect arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setSpriteFrame : Error processing arguments");
        cobj->setSpriteFrame(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setSpriteFrame : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getBlendFunc : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        jsval jsret = JSVAL_NULL;
        jsret = blendfunc_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getInsetBottom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getInsetBottom : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getInsetBottom();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getInsetBottom : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getCapInsets : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Rect ret = cobj->getCapInsets();
        jsval jsret = JSVAL_NULL;
        jsret = ccrect_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getCapInsets : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_isScale9Enabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_isScale9Enabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isScale9Enabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_isScale9Enabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getInsetRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getInsetRight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getInsetRight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getInsetRight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getOriginalSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getOriginalSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getOriginalSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getOriginalSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_initWithFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Scale9Sprite* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_initWithFile : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithFile(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg2;
            ok &= jsval_to_ccrect(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithFile(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Rect arg0;
            ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithFile(arg0, arg1);
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
            bool ret = cobj->initWithFile(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_initWithFile : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setBlendFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setBlendFunc : Invalid Native Object");
    if (argc == 1) {
        cocos2d::BlendFunc arg0;
        ok &= jsval_to_blendfunc(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setBlendFunc : Error processing arguments");
        cobj->setBlendFunc(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setBlendFunc : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getInsetTop(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getInsetTop : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getInsetTop();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getInsetTop : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setInsetLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetLeft : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetLeft : Error processing arguments");
        cobj->setInsetLeft(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setInsetLeft : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::Scale9Sprite* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::SpriteFrame* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSpriteFrame(arg0);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::SpriteFrame* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSpriteFrame(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getPreferredSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getPreferredSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getPreferredSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getPreferredSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setCapInsets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setCapInsets : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Rect arg0;
        ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setCapInsets : Error processing arguments");
        cobj->setCapInsets(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setCapInsets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_isFlippedY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_isFlippedY : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isFlippedY();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_isFlippedY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_getInsetLeft(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_getInsetLeft : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getInsetLeft();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_getInsetLeft : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_setInsetRight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Scale9Sprite* cobj = (cocos2d::ui::Scale9Sprite *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetRight : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Scale9Sprite_setInsetRight : Error processing arguments");
        cobj->setInsetRight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_setInsetRight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg2;
            ok &= jsval_to_ccrect(cx, args.get(2), &arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
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
        if (argc == 0) {
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create();
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
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
        if (argc == 2) {
            cocos2d::Rect arg0;
            ok &= jsval_to_ccrect(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
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
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
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
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::create(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_createWithSpriteFrameName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
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
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_createWithSpriteFrameName : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_createWithSpriteFrame(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            cocos2d::SpriteFrame* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Rect arg1;
            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
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
            cocos2d::SpriteFrame* arg0;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(0).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* ret = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(arg0);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_Scale9Sprite_createWithSpriteFrame : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_Scale9Sprite_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::Scale9Sprite* cobj = new (std::nothrow) cocos2d::ui::Scale9Sprite();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::Scale9Sprite> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Scale9Sprite");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

void js_cocos2d_ui_Scale9Sprite_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Scale9Sprite)", obj);
}

static bool js_cocos2d_ui_Scale9Sprite_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::Scale9Sprite *nobj = new (std::nothrow) cocos2d::ui::Scale9Sprite();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::Scale9Sprite");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_Scale9Sprite(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_Scale9Sprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_Scale9Sprite_class->name = "Scale9Sprite";
    jsb_cocos2d_ui_Scale9Sprite_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Scale9Sprite_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_Scale9Sprite_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_Scale9Sprite_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_Scale9Sprite_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_Scale9Sprite_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_Scale9Sprite_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_Scale9Sprite_class->finalize = js_cocos2d_ui_Scale9Sprite_finalize;
    jsb_cocos2d_ui_Scale9Sprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("disableCascadeColor", js_cocos2dx_ui_Scale9Sprite_disableCascadeColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateWithSprite", js_cocos2dx_ui_Scale9Sprite_updateWithSprite, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFlippedX", js_cocos2dx_ui_Scale9Sprite_isFlippedX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScale9Enabled", js_cocos2dx_ui_Scale9Sprite_setScale9Enabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFlippedY", js_cocos2dx_ui_Scale9Sprite_setFlippedY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFlippedX", js_cocos2dx_ui_Scale9Sprite_setFlippedX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resizableSpriteWithCapInsets", js_cocos2dx_ui_Scale9Sprite_resizableSpriteWithCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("disableCascadeOpacity", js_cocos2dx_ui_Scale9Sprite_disableCascadeOpacity, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_cocos2dx_ui_Scale9Sprite_getState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setState", js_cocos2dx_ui_Scale9Sprite_setState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInsetBottom", js_cocos2dx_ui_Scale9Sprite_setInsetBottom, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithSpriteFrameName", js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSprite", js_cocos2dx_ui_Scale9Sprite_getSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInsetTop", js_cocos2dx_ui_Scale9Sprite_setInsetTop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_ui_Scale9Sprite_init, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPreferredSize", js_cocos2dx_ui_Scale9Sprite_setPreferredSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSpriteFrame", js_cocos2dx_ui_Scale9Sprite_setSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBlendFunc", js_cocos2dx_ui_Scale9Sprite_getBlendFunc, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInsetBottom", js_cocos2dx_ui_Scale9Sprite_getInsetBottom, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCapInsets", js_cocos2dx_ui_Scale9Sprite_getCapInsets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isScale9Enabled", js_cocos2dx_ui_Scale9Sprite_isScale9Enabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInsetRight", js_cocos2dx_ui_Scale9Sprite_getInsetRight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOriginalSize", js_cocos2dx_ui_Scale9Sprite_getOriginalSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithFile", js_cocos2dx_ui_Scale9Sprite_initWithFile, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBlendFunc", js_cocos2dx_ui_Scale9Sprite_setBlendFunc, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInsetTop", js_cocos2dx_ui_Scale9Sprite_getInsetTop, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInsetLeft", js_cocos2dx_ui_Scale9Sprite_setInsetLeft, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithSpriteFrame", js_cocos2dx_ui_Scale9Sprite_initWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPreferredSize", js_cocos2dx_ui_Scale9Sprite_getPreferredSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCapInsets", js_cocos2dx_ui_Scale9Sprite_setCapInsets, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isFlippedY", js_cocos2dx_ui_Scale9Sprite_isFlippedY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInsetLeft", js_cocos2dx_ui_Scale9Sprite_getInsetLeft, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInsetRight", js_cocos2dx_ui_Scale9Sprite_setInsetRight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_Scale9Sprite_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_Scale9Sprite_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrameName", js_cocos2dx_ui_Scale9Sprite_createWithSpriteFrameName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("createWithSpriteFrame", js_cocos2dx_ui_Scale9Sprite_createWithSpriteFrame, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_Scale9Sprite_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Node_prototype),
        jsb_cocos2d_ui_Scale9Sprite_class,
        js_cocos2dx_ui_Scale9Sprite_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Scale9Sprite", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::Scale9Sprite> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_Scale9Sprite_class;
        p->proto = jsb_cocos2d_ui_Scale9Sprite_prototype;
        p->parentProto = jsb_cocos2d_Node_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_EditBox_class;
JSObject *jsb_cocos2d_ui_EditBox_prototype;

bool js_cocos2dx_ui_EditBox_getText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_getText : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getText();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_getText : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_EditBox_setFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setFontSize : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setFontSize : Error processing arguments");
        cobj->setFontSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setPlaceholderFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFontName : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFontName : Error processing arguments");
        cobj->setPlaceholderFontName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setPlaceholderFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_getPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_getPlaceHolder : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getPlaceHolder();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_getPlaceHolder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_EditBox_setFontName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setFontName : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setFontName : Error processing arguments");
        cobj->setFontName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setFontName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setText(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setText : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setText : Error processing arguments");
        cobj->setText(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setText : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setPlaceholderFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFontSize : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFontSize : Error processing arguments");
        cobj->setPlaceholderFontSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setPlaceholderFontSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setInputMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setInputMode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::EditBox::InputMode arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setInputMode : Error processing arguments");
        cobj->setInputMode(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setInputMode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setPlaceholderFontColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::EditBox* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFontColor : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setPlaceholderFontColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setPlaceholderFontColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setPlaceholderFontColor : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_EditBox_setFontColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::EditBox* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setFontColor : Invalid Native Object");
    do {
        if (argc == 1) {
            cocos2d::Color4B arg0;
            ok &= jsval_to_cccolor4b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setFontColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            cocos2d::Color3B arg0;
            ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->setFontColor(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setFontColor : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_EditBox_setPlaceholderFont(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFont : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setPlaceholderFont : Error processing arguments");
        cobj->setPlaceholderFont(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setPlaceholderFont : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    cocos2d::ui::EditBox* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite : Invalid Native Object");
    do {
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSizeAndBackgroundSprite(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_EditBox_setPlaceHolder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setPlaceHolder : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setPlaceHolder : Error processing arguments");
        cobj->setPlaceHolder(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setPlaceHolder : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setReturnType(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setReturnType : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::EditBox::KeyboardReturnType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setReturnType : Error processing arguments");
        cobj->setReturnType(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setReturnType : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setInputFlag(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setInputFlag : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::EditBox::InputFlag arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setInputFlag : Error processing arguments");
        cobj->setInputFlag(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setInputFlag : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_getMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_getMaxLength : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getMaxLength();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_getMaxLength : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_EditBox_setMaxLength(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setMaxLength : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setMaxLength : Error processing arguments");
        cobj->setMaxLength(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setMaxLength : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_EditBox_setFont(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_EditBox_setFont : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_EditBox_setFont : Error processing arguments");
        cobj->setFont(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_setFont : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_ui_EditBox_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::EditBox>(cx, (cocos2d::ui::EditBox*)ret);
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
        if (argc == 3) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Widget::TextureResType arg2;
            ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
            if (!ok) { ok = true; break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::EditBox>(cx, (cocos2d::ui::EditBox*)ret);
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
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::EditBox>(cx, (cocos2d::ui::EditBox*)ret);
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
        if (argc == 3) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg2;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(2).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::EditBox>(cx, (cocos2d::ui::EditBox*)ret);
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
        if (argc == 4) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg1;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(1).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg2;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(2).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::Scale9Sprite* arg3;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = args.get(3).toObjectOrNull();
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::ui::EditBox* ret = cocos2d::ui::EditBox::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            do {
                if (ret) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::EditBox>(cx, (cocos2d::ui::EditBox*)ret);
                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    jsret = JSVAL_NULL;
                }
            } while (0);
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_ui_EditBox_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_ui_EditBox_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::EditBox* cobj = new (std::nothrow) cocos2d::ui::EditBox();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::EditBox> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::EditBox");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_cocos2d_ui_EditBox_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (EditBox)", obj);
}

static bool js_cocos2d_ui_EditBox_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::EditBox *nobj = new (std::nothrow) cocos2d::ui::EditBox();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::EditBox");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_EditBox(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_EditBox_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_EditBox_class->name = "EditBox";
    jsb_cocos2d_ui_EditBox_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_EditBox_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_EditBox_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_EditBox_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_EditBox_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_EditBox_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_EditBox_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_EditBox_class->finalize = js_cocos2d_ui_EditBox_finalize;
    jsb_cocos2d_ui_EditBox_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getString", js_cocos2dx_ui_EditBox_getText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontSize", js_cocos2dx_ui_EditBox_setFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceholderFontName", js_cocos2dx_ui_EditBox_setPlaceholderFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlaceHolder", js_cocos2dx_ui_EditBox_getPlaceHolder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontName", js_cocos2dx_ui_EditBox_setFontName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setString", js_cocos2dx_ui_EditBox_setText, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceholderFontSize", js_cocos2dx_ui_EditBox_setPlaceholderFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInputMode", js_cocos2dx_ui_EditBox_setInputMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceholderFontColor", js_cocos2dx_ui_EditBox_setPlaceholderFontColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFontColor", js_cocos2dx_ui_EditBox_setFontColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceholderFont", js_cocos2dx_ui_EditBox_setPlaceholderFont, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithSizeAndBackgroundSprite", js_cocos2dx_ui_EditBox_initWithSizeAndBackgroundSprite, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlaceHolder", js_cocos2dx_ui_EditBox_setPlaceHolder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setReturnType", js_cocos2dx_ui_EditBox_setReturnType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setInputFlag", js_cocos2dx_ui_EditBox_setInputFlag, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxLength", js_cocos2dx_ui_EditBox_getMaxLength, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxLength", js_cocos2dx_ui_EditBox_setMaxLength, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setFont", js_cocos2dx_ui_EditBox_setFont, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_EditBox_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_EditBox_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_EditBox_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_ui_Widget_prototype),
        jsb_cocos2d_ui_EditBox_class,
        js_cocos2dx_ui_EditBox_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "EditBox", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::EditBox> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_EditBox_class;
        p->proto = jsb_cocos2d_ui_EditBox_prototype;
        p->parentProto = jsb_cocos2d_ui_Widget_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocos2d_ui_LayoutComponent_class;
JSObject *jsb_cocos2d_ui_LayoutComponent_prototype;

bool js_cocos2dx_ui_LayoutComponent_setStretchWidthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setStretchWidthEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setStretchWidthEnabled : Error processing arguments");
        cobj->setStretchWidthEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setStretchWidthEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPercentWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentWidth : Error processing arguments");
        cobj->setPercentWidth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPercentWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getAnchorPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getAnchorPosition : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Point& ret = cobj->getAnchorPosition();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getAnchorPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPositionPercentXEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentXEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentXEnabled : Error processing arguments");
        cobj->setPositionPercentXEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPositionPercentXEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setStretchHeightEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setStretchHeightEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setStretchHeightEnabled : Error processing arguments");
        cobj->setStretchHeightEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setStretchHeightEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setActiveEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setActiveEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setActiveEnabled : Error processing arguments");
        cobj->setActiveEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setActiveEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getRightMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getRightMargin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getRightMargin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getRightMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setAnchorPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setAnchorPosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setAnchorPosition : Error processing arguments");
        cobj->setAnchorPosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setAnchorPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_refreshLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_refreshLayout : Invalid Native Object");
    if (argc == 0) {
        cobj->refreshLayout();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_refreshLayout : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_isPercentWidthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_isPercentWidthEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPercentWidthEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_isPercentWidthEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setVerticalEdge(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setVerticalEdge : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::LayoutComponent::VerticalEdge arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setVerticalEdge : Error processing arguments");
        cobj->setVerticalEdge(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setVerticalEdge : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getTopMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getTopMargin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getTopMargin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getTopMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setSizeWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setSizeWidth : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setSizeWidth : Error processing arguments");
        cobj->setSizeWidth(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setSizeWidth : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getPercentContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getPercentContentSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getPercentContentSize();
        jsval jsret = JSVAL_NULL;
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getPercentContentSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getVerticalEdge(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getVerticalEdge : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getVerticalEdge();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getVerticalEdge : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPercentWidthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentWidthEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentWidthEnabled : Error processing arguments");
        cobj->setPercentWidthEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPercentWidthEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_isStretchWidthEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_isStretchWidthEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isStretchWidthEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_isStretchWidthEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setLeftMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setLeftMargin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setLeftMargin : Error processing arguments");
        cobj->setLeftMargin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setLeftMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getSizeWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getSizeWidth : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSizeWidth();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getSizeWidth : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPositionPercentYEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentYEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentYEnabled : Error processing arguments");
        cobj->setPositionPercentYEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPositionPercentYEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getSizeHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getSizeHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSizeHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getSizeHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getPositionPercentY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getPositionPercentY : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPositionPercentY();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getPositionPercentY : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getPositionPercentX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getPositionPercentX : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPositionPercentX();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getPositionPercentX : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setTopMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setTopMargin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setTopMargin : Error processing arguments");
        cobj->setTopMargin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setTopMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getPercentHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getPercentHeight : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPercentHeight();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getPercentHeight : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getUsingPercentContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getUsingPercentContentSize : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getUsingPercentContentSize();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getUsingPercentContentSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPositionPercentY(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentY : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentY : Error processing arguments");
        cobj->setPositionPercentY(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPositionPercentY : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPositionPercentX(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentX : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPositionPercentX : Error processing arguments");
        cobj->setPositionPercentX(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPositionPercentX : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setRightMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setRightMargin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setRightMargin : Error processing arguments");
        cobj->setRightMargin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setRightMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_isPositionPercentYEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_isPositionPercentYEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPositionPercentYEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_isPositionPercentYEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPercentHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentHeight : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentHeight : Error processing arguments");
        cobj->setPercentHeight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPercentHeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPercentOnlyEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentOnlyEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentOnlyEnabled : Error processing arguments");
        cobj->setPercentOnlyEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPercentOnlyEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setHorizontalEdge(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setHorizontalEdge : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::LayoutComponent::HorizontalEdge arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setHorizontalEdge : Error processing arguments");
        cobj->setHorizontalEdge(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setHorizontalEdge : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPosition : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Point arg0;
        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPosition : Error processing arguments");
        cobj->setPosition(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPosition : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setUsingPercentContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setUsingPercentContentSize : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setUsingPercentContentSize : Error processing arguments");
        cobj->setUsingPercentContentSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setUsingPercentContentSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getLeftMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getLeftMargin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getLeftMargin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getLeftMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getPosition(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getPosition : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Point& ret = cobj->getPosition();
        jsval jsret = JSVAL_NULL;
        jsret = ccpoint_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getPosition : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setSizeHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setSizeHeight : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setSizeHeight : Error processing arguments");
        cobj->setSizeHeight(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setSizeHeight : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_isPositionPercentXEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_isPositionPercentXEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPositionPercentXEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_isPositionPercentXEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getBottomMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getBottomMargin : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getBottomMargin();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getBottomMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPercentHeightEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentHeightEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentHeightEnabled : Error processing arguments");
        cobj->setPercentHeightEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPercentHeightEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setPercentContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentContentSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setPercentContentSize : Error processing arguments");
        cobj->setPercentContentSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setPercentContentSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_isPercentHeightEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_isPercentHeightEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPercentHeightEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_isPercentHeightEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getPercentWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getPercentWidth : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPercentWidth();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getPercentWidth : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_getHorizontalEdge(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_getHorizontalEdge : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getHorizontalEdge();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_getHorizontalEdge : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_isStretchHeightEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_isStretchHeightEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isStretchHeightEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_isStretchHeightEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setBottomMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setBottomMargin : Invalid Native Object");
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setBottomMargin : Error processing arguments");
        cobj->setBottomMargin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setBottomMargin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_setSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutComponent* cobj = (cocos2d::ui::LayoutComponent *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ui_LayoutComponent_setSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_setSize : Error processing arguments");
        cobj->setSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_setSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ui_LayoutComponent_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        cocos2d::ui::LayoutComponent* ret = cocos2d::ui::LayoutComponent::create();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LayoutComponent>(cx, (cocos2d::ui::LayoutComponent*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_LayoutComponent_bindLayoutComponent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_LayoutComponent_bindLayoutComponent : Error processing arguments");
        cocos2d::ui::LayoutComponent* ret = cocos2d::ui::LayoutComponent::bindLayoutComponent(arg0);
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::ui::LayoutComponent>(cx, (cocos2d::ui::LayoutComponent*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ui_LayoutComponent_bindLayoutComponent : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ui_LayoutComponent_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::ui::LayoutComponent* cobj = new (std::nothrow) cocos2d::ui::LayoutComponent();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocos2d::ui::LayoutComponent> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    // JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS::RootedObject proto(cx, typeClass->proto.get());
    JS::RootedObject parent(cx, typeClass->parentProto.get());
    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
    args.rval().set(OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::LayoutComponent");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Component_prototype;

void js_cocos2d_ui_LayoutComponent_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LayoutComponent)", obj);
}

static bool js_cocos2d_ui_LayoutComponent_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::ui::LayoutComponent *nobj = new (std::nothrow) cocos2d::ui::LayoutComponent();
    if (nobj) {
        nobj->autorelease();
    }
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    AddNamedObjectRoot(cx, &p->obj, "cocos2d::ui::LayoutComponent");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}
void js_register_cocos2dx_ui_LayoutComponent(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_ui_LayoutComponent_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_ui_LayoutComponent_class->name = "LayoutComponent";
    jsb_cocos2d_ui_LayoutComponent_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LayoutComponent_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_ui_LayoutComponent_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_ui_LayoutComponent_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_ui_LayoutComponent_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_ui_LayoutComponent_class->resolve = JS_ResolveStub;
    jsb_cocos2d_ui_LayoutComponent_class->convert = JS_ConvertStub;
    jsb_cocos2d_ui_LayoutComponent_class->finalize = js_cocos2d_ui_LayoutComponent_finalize;
    jsb_cocos2d_ui_LayoutComponent_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setStretchWidthEnabled", js_cocos2dx_ui_LayoutComponent_setStretchWidthEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPercentWidth", js_cocos2dx_ui_LayoutComponent_setPercentWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnchorPosition", js_cocos2dx_ui_LayoutComponent_getAnchorPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionPercentXEnabled", js_cocos2dx_ui_LayoutComponent_setPositionPercentXEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStretchHeightEnabled", js_cocos2dx_ui_LayoutComponent_setStretchHeightEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setActiveEnabled", js_cocos2dx_ui_LayoutComponent_setActiveEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRightMargin", js_cocos2dx_ui_LayoutComponent_getRightMargin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSize", js_cocos2dx_ui_LayoutComponent_getSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnchorPosition", js_cocos2dx_ui_LayoutComponent_setAnchorPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("refreshLayout", js_cocos2dx_ui_LayoutComponent_refreshLayout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPercentWidthEnabled", js_cocos2dx_ui_LayoutComponent_isPercentWidthEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVerticalEdge", js_cocos2dx_ui_LayoutComponent_setVerticalEdge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTopMargin", js_cocos2dx_ui_LayoutComponent_getTopMargin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSizeWidth", js_cocos2dx_ui_LayoutComponent_setSizeWidth, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercentContentSize", js_cocos2dx_ui_LayoutComponent_getPercentContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVerticalEdge", js_cocos2dx_ui_LayoutComponent_getVerticalEdge, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPercentWidthEnabled", js_cocos2dx_ui_LayoutComponent_setPercentWidthEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isStretchWidthEnabled", js_cocos2dx_ui_LayoutComponent_isStretchWidthEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLeftMargin", js_cocos2dx_ui_LayoutComponent_setLeftMargin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSizeWidth", js_cocos2dx_ui_LayoutComponent_getSizeWidth, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionPercentYEnabled", js_cocos2dx_ui_LayoutComponent_setPositionPercentYEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSizeHeight", js_cocos2dx_ui_LayoutComponent_getSizeHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPositionPercentY", js_cocos2dx_ui_LayoutComponent_getPositionPercentY, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPositionPercentX", js_cocos2dx_ui_LayoutComponent_getPositionPercentX, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTopMargin", js_cocos2dx_ui_LayoutComponent_setTopMargin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercentHeight", js_cocos2dx_ui_LayoutComponent_getPercentHeight, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUsingPercentContentSize", js_cocos2dx_ui_LayoutComponent_getUsingPercentContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionPercentY", js_cocos2dx_ui_LayoutComponent_setPositionPercentY, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPositionPercentX", js_cocos2dx_ui_LayoutComponent_setPositionPercentX, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRightMargin", js_cocos2dx_ui_LayoutComponent_setRightMargin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPositionPercentYEnabled", js_cocos2dx_ui_LayoutComponent_isPositionPercentYEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPercentHeight", js_cocos2dx_ui_LayoutComponent_setPercentHeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPercentOnlyEnabled", js_cocos2dx_ui_LayoutComponent_setPercentOnlyEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHorizontalEdge", js_cocos2dx_ui_LayoutComponent_setHorizontalEdge, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPosition", js_cocos2dx_ui_LayoutComponent_setPosition, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUsingPercentContentSize", js_cocos2dx_ui_LayoutComponent_setUsingPercentContentSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLeftMargin", js_cocos2dx_ui_LayoutComponent_getLeftMargin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPosition", js_cocos2dx_ui_LayoutComponent_getPosition, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSizeHeight", js_cocos2dx_ui_LayoutComponent_setSizeHeight, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPositionPercentXEnabled", js_cocos2dx_ui_LayoutComponent_isPositionPercentXEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBottomMargin", js_cocos2dx_ui_LayoutComponent_getBottomMargin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPercentHeightEnabled", js_cocos2dx_ui_LayoutComponent_setPercentHeightEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPercentContentSize", js_cocos2dx_ui_LayoutComponent_setPercentContentSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isPercentHeightEnabled", js_cocos2dx_ui_LayoutComponent_isPercentHeightEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercentWidth", js_cocos2dx_ui_LayoutComponent_getPercentWidth, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHorizontalEdge", js_cocos2dx_ui_LayoutComponent_getHorizontalEdge, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isStretchHeightEnabled", js_cocos2dx_ui_LayoutComponent_isStretchHeightEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBottomMargin", js_cocos2dx_ui_LayoutComponent_setBottomMargin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSize", js_cocos2dx_ui_LayoutComponent_setSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2d_ui_LayoutComponent_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_ui_LayoutComponent_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("bindLayoutComponent", js_cocos2dx_ui_LayoutComponent_bindLayoutComponent, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_ui_LayoutComponent_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_cocos2d_Component_prototype),
        jsb_cocos2d_ui_LayoutComponent_class,
        js_cocos2dx_ui_LayoutComponent_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "LayoutComponent", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocos2d::ui::LayoutComponent> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocos2d_ui_LayoutComponent_class;
        p->proto = jsb_cocos2d_ui_LayoutComponent_prototype;
        p->parentProto = jsb_cocos2d_Component_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_ui(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "ccui", &ns);

    js_register_cocos2dx_ui_Widget(cx, ns);
    js_register_cocos2dx_ui_Layout(cx, ns);
    js_register_cocos2dx_ui_RelativeBox(cx, ns);
    js_register_cocos2dx_ui_CheckBox(cx, ns);
    js_register_cocos2dx_ui_TextAtlas(cx, ns);
    js_register_cocos2dx_ui_TextBMFont(cx, ns);
    js_register_cocos2dx_ui_LoadingBar(cx, ns);
    js_register_cocos2dx_ui_TextField(cx, ns);
    js_register_cocos2dx_ui_RichText(cx, ns);
    js_register_cocos2dx_ui_Scale9Sprite(cx, ns);
    js_register_cocos2dx_ui_VBox(cx, ns);
    js_register_cocos2dx_ui_RichElement(cx, ns);
    js_register_cocos2dx_ui_RichElementCustomNode(cx, ns);
    js_register_cocos2dx_ui_Slider(cx, ns);
    js_register_cocos2dx_ui_ScrollView(cx, ns);
    js_register_cocos2dx_ui_ListView(cx, ns);
    js_register_cocos2dx_ui_LayoutComponent(cx, ns);
    js_register_cocos2dx_ui_Button(cx, ns);
    js_register_cocos2dx_ui_LayoutParameter(cx, ns);
    js_register_cocos2dx_ui_LinearLayoutParameter(cx, ns);
    js_register_cocos2dx_ui_ImageView(cx, ns);
    js_register_cocos2dx_ui_HBox(cx, ns);
    js_register_cocos2dx_ui_RichElementText(cx, ns);
    js_register_cocos2dx_ui_PageView(cx, ns);
    js_register_cocos2dx_ui_Helper(cx, ns);
    js_register_cocos2dx_ui_EditBox(cx, ns);
    js_register_cocos2dx_ui_Text(cx, ns);
    js_register_cocos2dx_ui_RichElementImage(cx, ns);
    js_register_cocos2dx_ui_RelativeLayoutParameter(cx, ns);
    js_register_cocos2dx_ui_UICCTextField(cx, ns);
}

