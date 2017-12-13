#include "scripting/js-bindings/auto/jsb_cocos2dx_extension_auto.hpp"
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
JSClass  *jsb_cocos2d_extension_Control_class;
JSObject *jsb_cocos2d_extension_Control_prototype;

bool js_cocos2dx_extension_Control_setEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_setEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_Control_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_setEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_Control_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_getState : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getState();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_getState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Control_sendActionsForControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_sendActionsForControlEvents : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::EventType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_Control_sendActionsForControlEvents : Error processing arguments");
        cobj->sendActionsForControlEvents(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_sendActionsForControlEvents : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_Control_setSelected(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_setSelected : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_Control_setSelected : Error processing arguments");
        cobj->setSelected(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_setSelected : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_Control_isEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_isEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_isEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Control_needsLayout(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_needsLayout : Invalid Native Object");
    if (argc == 0) {
        cobj->needsLayout();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_needsLayout : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Control_hasVisibleParents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_hasVisibleParents : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->hasVisibleParents();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_hasVisibleParents : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Control_isSelected(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_isSelected : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isSelected();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_isSelected : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Control_isTouchInside(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_isTouchInside : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Touch* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_Control_isTouchInside : Error processing arguments");
        bool ret = cobj->isTouchInside(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_isTouchInside : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_Control_setHighlighted(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_setHighlighted : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_Control_setHighlighted : Error processing arguments");
        cobj->setHighlighted(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_setHighlighted : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_Control_getTouchLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_getTouchLocation : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Touch* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_Control_getTouchLocation : Error processing arguments");
        cocos2d::Vec2 ret = cobj->getTouchLocation(arg0);
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_getTouchLocation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_Control_isHighlighted(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Control_isHighlighted : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isHighlighted();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Control_isHighlighted : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Control_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocos2d::extension::Control::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::Control>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::Control"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_Control_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_Control_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::Control* cobj = new (std::nothrow) cocos2d::extension::Control();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::Control>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::Control"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_Layer_prototype;

void js_register_cocos2dx_extension_Control(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_Control_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_Control_class->name = "Control";
    jsb_cocos2d_extension_Control_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_Control_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_Control_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_Control_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_Control_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_Control_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_Control_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_Control_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setEnabled", js_cocos2dx_extension_Control_setEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getState", js_cocos2dx_extension_Control_getState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("sendActionsForControlEvents", js_cocos2dx_extension_Control_sendActionsForControlEvents, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSelected", js_cocos2dx_extension_Control_setSelected, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isEnabled", js_cocos2dx_extension_Control_isEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("needsLayout", js_cocos2dx_extension_Control_needsLayout, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasVisibleParents", js_cocos2dx_extension_Control_hasVisibleParents, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isSelected", js_cocos2dx_extension_Control_isSelected, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchInside", js_cocos2dx_extension_Control_isTouchInside, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHighlighted", js_cocos2dx_extension_Control_setHighlighted, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTouchLocation", js_cocos2dx_extension_Control_getTouchLocation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isHighlighted", js_cocos2dx_extension_Control_isHighlighted, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_Control_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Layer_prototype);
    jsb_cocos2d_extension_Control_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_Control_class,
        js_cocos2dx_extension_Control_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_Control_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Control"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::Control>(cx, jsb_cocos2d_extension_Control_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_extension_ControlButton_class;
JSObject *jsb_cocos2d_extension_ControlButton_prototype;

bool js_cocos2dx_extension_ControlButton_isPushed(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_isPushed : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isPushed();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_isPushed : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleLabelForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleLabelForState : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Node* arg0 = nullptr;
        cocos2d::extension::Control::State arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleLabelForState : Error processing arguments");
        cobj->setTitleLabelForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleLabelForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setAdjustBackgroundImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setAdjustBackgroundImage : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setAdjustBackgroundImage : Error processing arguments");
        cobj->setAdjustBackgroundImage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setAdjustBackgroundImage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleForState : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::extension::Control::State arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleForState : Error processing arguments");
        cobj->setTitleForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setLabelAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setLabelAnchorPoint : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setLabelAnchorPoint : Error processing arguments");
        cobj->setLabelAnchorPoint(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setLabelAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getLabelAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getLabelAnchorPoint : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Vec2& ret = cobj->getLabelAnchorPoint();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getLabelAnchorPoint : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_initWithBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_initWithBackgroundSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Scale9Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_initWithBackgroundSprite : Error processing arguments");
        bool ret = cobj->initWithBackgroundSprite(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_initWithBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleTTFSizeForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleTTFSizeForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getTitleTTFSizeForState : Error processing arguments");
        double ret = cobj->getTitleTTFSizeForState(arg0);
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleTTFSizeForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleTTFForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleTTFForState : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::extension::Control::State arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleTTFForState : Error processing arguments");
        cobj->setTitleTTFForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleTTFForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleTTFSizeForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleTTFSizeForState : Invalid Native Object");
    if (argc == 2) {
        double arg0 = 0;
        cocos2d::extension::Control::State arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleTTFSizeForState : Error processing arguments");
        cobj->setTitleTTFSizeForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleTTFSizeForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleLabel : Invalid Native Object");
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleLabel : Error processing arguments");
        cobj->setTitleLabel(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleLabel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setPreferredSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setPreferredSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setPreferredSize : Error processing arguments");
        cobj->setPreferredSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setPreferredSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getCurrentTitleColor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getCurrentTitleColor : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Color3B& ret = cobj->getCurrentTitleColor();
        JS::RootedValue jsret(cx);
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getCurrentTitleColor : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setZoomOnTouchDown(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setZoomOnTouchDown : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setZoomOnTouchDown : Error processing arguments");
        cobj->setZoomOnTouchDown(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setZoomOnTouchDown : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setBackgroundSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::Scale9Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setBackgroundSprite : Error processing arguments");
        cobj->setBackgroundSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getBackgroundSpriteForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getBackgroundSpriteForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getBackgroundSpriteForState : Error processing arguments");
        cocos2d::ui::Scale9Sprite* ret = cobj->getBackgroundSpriteForState(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getBackgroundSpriteForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getHorizontalOrigin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getHorizontalOrigin : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getHorizontalOrigin();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getHorizontalOrigin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize : Invalid Native Object");
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        double arg2 = 0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !std::isnan(arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize : Error processing arguments");
        bool ret = cobj->initWithTitleAndFontNameAndFontSize(arg0, arg1, arg2);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleBMFontForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleBMFontForState : Invalid Native Object");
    if (argc == 2) {
        std::string arg0;
        cocos2d::extension::Control::State arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleBMFontForState : Error processing arguments");
        cobj->setTitleBMFontForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleBMFontForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getScaleRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getScaleRatio : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getScaleRatio();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getScaleRatio : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleTTFForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleTTFForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getTitleTTFForState : Error processing arguments");
        const std::string& ret = cobj->getTitleTTFForState(arg0);
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleTTFForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getBackgroundSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ui::Scale9Sprite* ret = cobj->getBackgroundSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::ui::Scale9Sprite>(cx, (cocos2d::ui::Scale9Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleColorForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleColorForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getTitleColorForState : Error processing arguments");
        cocos2d::Color3B ret = cobj->getTitleColorForState(arg0);
        JS::RootedValue jsret(cx);
        jsret = cccolor3b_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleColorForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setTitleColorForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setTitleColorForState : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Color3B arg0;
        cocos2d::extension::Control::State arg1;
        ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setTitleColorForState : Error processing arguments");
        cobj->setTitleColorForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setTitleColorForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->doesAdjustBackgroundImage();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState : Invalid Native Object");
    if (argc == 2) {
        cocos2d::SpriteFrame* arg0 = nullptr;
        cocos2d::extension::Control::State arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::SpriteFrame*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState : Error processing arguments");
        cobj->setBackgroundSpriteFrameForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setBackgroundSpriteForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setBackgroundSpriteForState : Invalid Native Object");
    if (argc == 2) {
        cocos2d::ui::Scale9Sprite* arg0 = nullptr;
        cocos2d::extension::Control::State arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setBackgroundSpriteForState : Error processing arguments");
        cobj->setBackgroundSpriteForState(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setBackgroundSpriteForState : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setScaleRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setScaleRatio : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setScaleRatio : Error processing arguments");
        cobj->setScaleRatio(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setScaleRatio : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleBMFontForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleBMFontForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getTitleBMFontForState : Error processing arguments");
        const std::string& ret = cobj->getTitleBMFontForState(arg0);
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleBMFontForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleLabel : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getTitleLabel();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleLabel : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getPreferredSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getPreferredSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getPreferredSize();
        JS::RootedValue jsret(cx);
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getPreferredSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getVerticalMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getVerticalMargin : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getVerticalMargin();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getVerticalMargin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleLabelForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleLabelForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getTitleLabelForState : Error processing arguments");
        cocos2d::Node* ret = cobj->getTitleLabelForState(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleLabelForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_setMargins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_setMargins : Invalid Native Object");
    if (argc == 2) {
        int arg0 = 0;
        int arg1 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_setMargins : Error processing arguments");
        cobj->setMargins(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_setMargins : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getCurrentTitle(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::extension::ControlButton* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getCurrentTitle : Invalid Native Object");
    do {
        if (argc == 0) {
            std::string ret = cobj->getCurrentTitle();
            jsval jsret = JSVAL_NULL;
            jsret = std_string_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            const std::string& ret = cobj->getCurrentTitle();
            jsval jsret = JSVAL_NULL;
            jsret = std_string_to_jsval(cx, ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getCurrentTitle : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Node* arg0 = nullptr;
        cocos2d::ui::Scale9Sprite* arg1 = nullptr;
        bool arg2;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        arg2 = JS::ToBoolean(args.get(2));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite : Error processing arguments");
        bool ret = cobj->initWithLabelAndBackgroundSprite(arg0, arg1, arg2);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getZoomOnTouchDown(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getZoomOnTouchDown : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->getZoomOnTouchDown();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getZoomOnTouchDown : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlButton_getTitleForState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlButton* cobj = (cocos2d::extension::ControlButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlButton_getTitleForState : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::State arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlButton_getTitleForState : Error processing arguments");
        std::string ret = cobj->getTitleForState(arg0);
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_getTitleForState : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlButton_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 1) {
            cocos2d::ui::Scale9Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlButton>(cx, (cocos2d::extension::ControlButton*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 0) {
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlButton>(cx, (cocos2d::extension::ControlButton*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
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
            cocos2d::ui::Scale9Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlButton>(cx, (cocos2d::extension::ControlButton*)ret));
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
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            double arg2 = 0;
            ok &= JS::ToNumber( cx, args.get(2), &arg2) && !std::isnan(arg2);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlButton>(cx, (cocos2d::extension::ControlButton*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 3) {
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
            cocos2d::ui::Scale9Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::ui::Scale9Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool arg2;
            arg2 = JS::ToBoolean(args.get(2));
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlButton* ret = cocos2d::extension::ControlButton::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlButton>(cx, (cocos2d::extension::ControlButton*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_extension_ControlButton_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlButton_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlButton* cobj = new (std::nothrow) cocos2d::extension::ControlButton();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlButton>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlButton"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ControlButton_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ControlButton *nobj = new (std::nothrow) cocos2d::extension::ControlButton();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ControlButton");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

    
void js_register_cocos2dx_extension_ControlButton(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlButton_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlButton_class->name = "ControlButton";
    jsb_cocos2d_extension_ControlButton_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlButton_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlButton_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlButton_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlButton_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlButton_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlButton_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlButton_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isPushed", js_cocos2dx_extension_ControlButton_isPushed, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleLabelForState", js_cocos2dx_extension_ControlButton_setTitleLabelForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAdjustBackgroundImage", js_cocos2dx_extension_ControlButton_setAdjustBackgroundImage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleForState", js_cocos2dx_extension_ControlButton_setTitleForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLabelAnchorPoint", js_cocos2dx_extension_ControlButton_setLabelAnchorPoint, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLabelAnchorPoint", js_cocos2dx_extension_ControlButton_getLabelAnchorPoint, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithBackgroundSprite", js_cocos2dx_extension_ControlButton_initWithBackgroundSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleTTFSizeForState", js_cocos2dx_extension_ControlButton_getTitleTTFSizeForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleTTFForState", js_cocos2dx_extension_ControlButton_setTitleTTFForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleTTFSizeForState", js_cocos2dx_extension_ControlButton_setTitleTTFSizeForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleLabel", js_cocos2dx_extension_ControlButton_setTitleLabel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPreferredSize", js_cocos2dx_extension_ControlButton_setPreferredSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTitleColor", js_cocos2dx_extension_ControlButton_getCurrentTitleColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomOnTouchDown", js_cocos2dx_extension_ControlButton_setZoomOnTouchDown, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundSprite", js_cocos2dx_extension_ControlButton_setBackgroundSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackgroundSpriteForState", js_cocos2dx_extension_ControlButton_getBackgroundSpriteForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHorizontalOrigin", js_cocos2dx_extension_ControlButton_getHorizontalOrigin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithTitleAndFontNameAndFontSize", js_cocos2dx_extension_ControlButton_initWithTitleAndFontNameAndFontSize, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleBMFontForState", js_cocos2dx_extension_ControlButton_setTitleBMFontForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getScaleRatio", js_cocos2dx_extension_ControlButton_getScaleRatio, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleTTFForState", js_cocos2dx_extension_ControlButton_getTitleTTFForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackgroundSprite", js_cocos2dx_extension_ControlButton_getBackgroundSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleColorForState", js_cocos2dx_extension_ControlButton_getTitleColorForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTitleColorForState", js_cocos2dx_extension_ControlButton_setTitleColorForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("doesAdjustBackgroundImage", js_cocos2dx_extension_ControlButton_doesAdjustBackgroundImage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundSpriteFrameForState", js_cocos2dx_extension_ControlButton_setBackgroundSpriteFrameForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackgroundSpriteForState", js_cocos2dx_extension_ControlButton_setBackgroundSpriteForState, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setScaleRatio", js_cocos2dx_extension_ControlButton_setScaleRatio, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleBMFontForState", js_cocos2dx_extension_ControlButton_getTitleBMFontForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleLabel", js_cocos2dx_extension_ControlButton_getTitleLabel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPreferredSize", js_cocos2dx_extension_ControlButton_getPreferredSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVerticalMargin", js_cocos2dx_extension_ControlButton_getVerticalMargin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleLabelForState", js_cocos2dx_extension_ControlButton_getTitleLabelForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMargins", js_cocos2dx_extension_ControlButton_setMargins, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCurrentTitle", js_cocos2dx_extension_ControlButton_getCurrentTitle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithLabelAndBackgroundSprite", js_cocos2dx_extension_ControlButton_initWithLabelAndBackgroundSprite, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getZoomOnTouchDown", js_cocos2dx_extension_ControlButton_getZoomOnTouchDown, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getTitleForState", js_cocos2dx_extension_ControlButton_getTitleForState, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ControlButton_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlButton_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlButton_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlButton_class,
        js_cocos2dx_extension_ControlButton_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlButton_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlButton"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlButton>(cx, jsb_cocos2d_extension_ControlButton_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ControlButton.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_ControlHuePicker_class;
JSObject *jsb_cocos2d_extension_ControlHuePicker_prototype;

bool js_cocos2dx_extension_ControlHuePicker_initWithTargetAndPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_initWithTargetAndPos : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Node* arg0 = nullptr;
        cocos2d::Vec2 arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlHuePicker_initWithTargetAndPos : Error processing arguments");
        bool ret = cobj->initWithTargetAndPos(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_initWithTargetAndPos : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_setHue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_setHue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlHuePicker_setHue : Error processing arguments");
        cobj->setHue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_setHue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_getStartPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_getStartPos : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getStartPos();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_getStartPos : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_getHue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_getHue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getHue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_getHue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_getSlider(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_getSlider : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getSlider();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_getSlider : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_setBackground(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_setBackground : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlHuePicker_setBackground : Error processing arguments");
        cobj->setBackground(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_setBackground : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_setHuePercentage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_setHuePercentage : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlHuePicker_setHuePercentage : Error processing arguments");
        cobj->setHuePercentage(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_setHuePercentage : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_getBackground(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_getBackground : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getBackground();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_getBackground : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_getHuePercentage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_getHuePercentage : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getHuePercentage();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_getHuePercentage : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_setSlider(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlHuePicker* cobj = (cocos2d::extension::ControlHuePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlHuePicker_setSlider : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlHuePicker_setSlider : Error processing arguments");
        cobj->setSlider(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_setSlider : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlHuePicker_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Node* arg0 = nullptr;
        cocos2d::Vec2 arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlHuePicker_create : Error processing arguments");

        auto ret = cocos2d::extension::ControlHuePicker::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlHuePicker>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::ControlHuePicker"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_ControlHuePicker_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_ControlHuePicker_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlHuePicker* cobj = new (std::nothrow) cocos2d::extension::ControlHuePicker();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlHuePicker>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlHuePicker"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

void js_register_cocos2dx_extension_ControlHuePicker(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlHuePicker_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlHuePicker_class->name = "ControlHuePicker";
    jsb_cocos2d_extension_ControlHuePicker_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlHuePicker_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlHuePicker_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlHuePicker_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlHuePicker_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlHuePicker_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlHuePicker_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlHuePicker_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("initWithTargetAndPos", js_cocos2dx_extension_ControlHuePicker_initWithTargetAndPos, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHue", js_cocos2dx_extension_ControlHuePicker_setHue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartPos", js_cocos2dx_extension_ControlHuePicker_getStartPos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHue", js_cocos2dx_extension_ControlHuePicker_getHue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlider", js_cocos2dx_extension_ControlHuePicker_getSlider, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackground", js_cocos2dx_extension_ControlHuePicker_setBackground, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHuePercentage", js_cocos2dx_extension_ControlHuePicker_setHuePercentage, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackground", js_cocos2dx_extension_ControlHuePicker_getBackground, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHuePercentage", js_cocos2dx_extension_ControlHuePicker_getHuePercentage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSlider", js_cocos2dx_extension_ControlHuePicker_setSlider, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlHuePicker_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlHuePicker_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlHuePicker_class,
        js_cocos2dx_extension_ControlHuePicker_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlHuePicker_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlHuePicker"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlHuePicker>(cx, jsb_cocos2d_extension_ControlHuePicker_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class;
JSObject *jsb_cocos2d_extension_ControlSaturationBrightnessPicker_prototype;

bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getShadow(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getShadow : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getShadow();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getShadow : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_initWithTargetAndPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_initWithTargetAndPos : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Node* arg0 = nullptr;
        cocos2d::Vec2 arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_initWithTargetAndPos : Error processing arguments");
        bool ret = cobj->initWithTargetAndPos(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_initWithTargetAndPos : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getStartPos(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getStartPos : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getStartPos();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getStartPos : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getOverlay(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getOverlay : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getOverlay();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getOverlay : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSlider(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSlider : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getSlider();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSlider : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBackground(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBackground : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getBackground();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBackground : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSaturation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSaturation : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getSaturation();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSaturation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBrightness(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = (cocos2d::extension::ControlSaturationBrightnessPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBrightness : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getBrightness();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBrightness : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Node* arg0 = nullptr;
        cocos2d::Vec2 arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_create : Error processing arguments");

        auto ret = cocos2d::extension::ControlSaturationBrightnessPicker::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlSaturationBrightnessPicker>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::ControlSaturationBrightnessPicker"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_ControlSaturationBrightnessPicker_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_ControlSaturationBrightnessPicker_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlSaturationBrightnessPicker* cobj = new (std::nothrow) cocos2d::extension::ControlSaturationBrightnessPicker();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlSaturationBrightnessPicker>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlSaturationBrightnessPicker"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

void js_register_cocos2dx_extension_ControlSaturationBrightnessPicker(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->name = "ControlSaturationBrightnessPicker";
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getShadow", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getShadow, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithTargetAndPos", js_cocos2dx_extension_ControlSaturationBrightnessPicker_initWithTargetAndPos, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStartPos", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getStartPos, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOverlay", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getOverlay, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSlider", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSlider, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackground", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBackground, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSaturation", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getSaturation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBrightness", js_cocos2dx_extension_ControlSaturationBrightnessPicker_getBrightness, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlSaturationBrightnessPicker_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlSaturationBrightnessPicker_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class,
        js_cocos2dx_extension_ControlSaturationBrightnessPicker_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlSaturationBrightnessPicker_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlSaturationBrightnessPicker"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlSaturationBrightnessPicker>(cx, jsb_cocos2d_extension_ControlSaturationBrightnessPicker_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_extension_ControlColourPicker_class;
JSObject *jsb_cocos2d_extension_ControlColourPicker_prototype;

bool js_cocos2dx_extension_ControlColourPicker_hueSliderValueChanged(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_hueSliderValueChanged : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Ref* arg0 = nullptr;
        cocos2d::extension::Control::EventType arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlColourPicker_hueSliderValueChanged : Error processing arguments");
        cobj->hueSliderValueChanged(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_hueSliderValueChanged : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_getHuePicker(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_getHuePicker : Invalid Native Object");
    if (argc == 0) {
        cocos2d::extension::ControlHuePicker* ret = cobj->getHuePicker();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlHuePicker>(cx, (cocos2d::extension::ControlHuePicker*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_getHuePicker : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_getcolourPicker(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_getcolourPicker : Invalid Native Object");
    if (argc == 0) {
        cocos2d::extension::ControlSaturationBrightnessPicker* ret = cobj->getcolourPicker();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSaturationBrightnessPicker>(cx, (cocos2d::extension::ControlSaturationBrightnessPicker*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_getcolourPicker : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_setBackground(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_setBackground : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlColourPicker_setBackground : Error processing arguments");
        cobj->setBackground(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_setBackground : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_setcolourPicker(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_setcolourPicker : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::ControlSaturationBrightnessPicker* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::extension::ControlSaturationBrightnessPicker*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlColourPicker_setcolourPicker : Error processing arguments");
        cobj->setcolourPicker(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_setcolourPicker : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_colourSliderValueChanged(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_colourSliderValueChanged : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Ref* arg0 = nullptr;
        cocos2d::extension::Control::EventType arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlColourPicker_colourSliderValueChanged : Error processing arguments");
        cobj->colourSliderValueChanged(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_colourSliderValueChanged : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_setHuePicker(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_setHuePicker : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::ControlHuePicker* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::extension::ControlHuePicker*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlColourPicker_setHuePicker : Error processing arguments");
        cobj->setHuePicker(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_setHuePicker : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_getBackground(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlColourPicker* cobj = (cocos2d::extension::ControlColourPicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlColourPicker_getBackground : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getBackground();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_getBackground : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlColourPicker_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocos2d::extension::ControlColourPicker::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlColourPicker>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::ControlColourPicker"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_ControlColourPicker_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_ControlColourPicker_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlColourPicker* cobj = new (std::nothrow) cocos2d::extension::ControlColourPicker();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlColourPicker>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlColourPicker"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ControlColourPicker_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ControlColourPicker *nobj = new (std::nothrow) cocos2d::extension::ControlColourPicker();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ControlColourPicker");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

    
void js_register_cocos2dx_extension_ControlColourPicker(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlColourPicker_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlColourPicker_class->name = "ControlColourPicker";
    jsb_cocos2d_extension_ControlColourPicker_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlColourPicker_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlColourPicker_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlColourPicker_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlColourPicker_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlColourPicker_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlColourPicker_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlColourPicker_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("hueSliderValueChanged", js_cocos2dx_extension_ControlColourPicker_hueSliderValueChanged, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getHuePicker", js_cocos2dx_extension_ControlColourPicker_getHuePicker, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getcolourPicker", js_cocos2dx_extension_ControlColourPicker_getcolourPicker, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBackground", js_cocos2dx_extension_ControlColourPicker_setBackground, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setcolourPicker", js_cocos2dx_extension_ControlColourPicker_setcolourPicker, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("colourSliderValueChanged", js_cocos2dx_extension_ControlColourPicker_colourSliderValueChanged, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setHuePicker", js_cocos2dx_extension_ControlColourPicker_setHuePicker, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackground", js_cocos2dx_extension_ControlColourPicker_getBackground, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ControlColourPicker_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlColourPicker_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlColourPicker_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlColourPicker_class,
        js_cocos2dx_extension_ControlColourPicker_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlColourPicker_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlColourPicker"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlColourPicker>(cx, jsb_cocos2d_extension_ControlColourPicker_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ControlColourPicker.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_ControlPotentiometer_class;
JSObject *jsb_cocos2d_extension_ControlPotentiometer_prototype;

bool js_cocos2dx_extension_ControlPotentiometer_setPreviousLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setPreviousLocation : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setPreviousLocation : Error processing arguments");
        cobj->setPreviousLocation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_setPreviousLocation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_setValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setValue : Error processing arguments");
        cobj->setValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_setValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_getProgressTimer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_getProgressTimer : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ProgressTimer* ret = cobj->getProgressTimer();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::ProgressTimer>(cx, (cocos2d::ProgressTimer*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_getProgressTimer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_getMaximumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_getMaximumValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaximumValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_getMaximumValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint : Invalid Native Object");
    if (argc == 4) {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        cocos2d::Vec2 arg2;
        cocos2d::Vec2 arg3;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        ok &= jsval_to_vector2(cx, args.get(2), &arg2);
        ok &= jsval_to_vector2(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint : Error processing arguments");
        double ret = cobj->angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint(arg0, arg1, arg2, arg3);
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_potentiometerBegan(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_potentiometerBegan : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_potentiometerBegan : Error processing arguments");
        cobj->potentiometerBegan(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_potentiometerBegan : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_setMaximumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setMaximumValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setMaximumValue : Error processing arguments");
        cobj->setMaximumValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_setMaximumValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_getMinimumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_getMinimumValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMinimumValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_getMinimumValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_setThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setThumbSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setThumbSprite : Error processing arguments");
        cobj->setThumbSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_setThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_getValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_getValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_getValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_getPreviousLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_getPreviousLocation : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getPreviousLocation();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_getPreviousLocation : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_distanceBetweenPointAndPoint(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_distanceBetweenPointAndPoint : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec2 arg0;
        cocos2d::Vec2 arg1;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        ok &= jsval_to_vector2(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_distanceBetweenPointAndPoint : Error processing arguments");
        double ret = cobj->distanceBetweenPointAndPoint(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_distanceBetweenPointAndPoint : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_potentiometerEnded(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_potentiometerEnded : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_potentiometerEnded : Error processing arguments");
        cobj->potentiometerEnded(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_potentiometerEnded : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_setProgressTimer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setProgressTimer : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ProgressTimer* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::ProgressTimer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setProgressTimer : Error processing arguments");
        cobj->setProgressTimer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_setProgressTimer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_setMinimumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setMinimumValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_setMinimumValue : Error processing arguments");
        cobj->setMinimumValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_setMinimumValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_getThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_getThumbSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getThumbSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_getThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_initWithTrackSprite_ProgressTimer_ThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_initWithTrackSprite_ProgressTimer_ThumbSprite : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Sprite* arg0 = nullptr;
        cocos2d::ProgressTimer* arg1 = nullptr;
        cocos2d::Sprite* arg2 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::ProgressTimer*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(2).isNull()) { arg2 = nullptr; break; }
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_initWithTrackSprite_ProgressTimer_ThumbSprite : Error processing arguments");
        bool ret = cobj->initWithTrackSprite_ProgressTimer_ThumbSprite(arg0, arg1, arg2);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_initWithTrackSprite_ProgressTimer_ThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_potentiometerMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlPotentiometer* cobj = (cocos2d::extension::ControlPotentiometer *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlPotentiometer_potentiometerMoved : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_potentiometerMoved : Error processing arguments");
        cobj->potentiometerMoved(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_potentiometerMoved : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlPotentiometer_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3) {
        const char* arg0 = nullptr;
        const char* arg1 = nullptr;
        const char* arg2 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= jsval_to_std_string(cx, args.get(2), &arg2_tmp); arg2 = arg2_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlPotentiometer_create : Error processing arguments");

        auto ret = cocos2d::extension::ControlPotentiometer::create(arg0, arg1, arg2);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlPotentiometer>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::ControlPotentiometer"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_ControlPotentiometer_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_ControlPotentiometer_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlPotentiometer* cobj = new (std::nothrow) cocos2d::extension::ControlPotentiometer();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlPotentiometer>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlPotentiometer"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ControlPotentiometer_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ControlPotentiometer *nobj = new (std::nothrow) cocos2d::extension::ControlPotentiometer();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ControlPotentiometer");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

    
void js_register_cocos2dx_extension_ControlPotentiometer(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlPotentiometer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlPotentiometer_class->name = "ControlPotentiometer";
    jsb_cocos2d_extension_ControlPotentiometer_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlPotentiometer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setPreviousLocation", js_cocos2dx_extension_ControlPotentiometer_setPreviousLocation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setValue", js_cocos2dx_extension_ControlPotentiometer_setValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProgressTimer", js_cocos2dx_extension_ControlPotentiometer_getProgressTimer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaximumValue", js_cocos2dx_extension_ControlPotentiometer_getMaximumValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint", js_cocos2dx_extension_ControlPotentiometer_angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("potentiometerBegan", js_cocos2dx_extension_ControlPotentiometer_potentiometerBegan, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaximumValue", js_cocos2dx_extension_ControlPotentiometer_setMaximumValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMinimumValue", js_cocos2dx_extension_ControlPotentiometer_getMinimumValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setThumbSprite", js_cocos2dx_extension_ControlPotentiometer_setThumbSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getValue", js_cocos2dx_extension_ControlPotentiometer_getValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPreviousLocation", js_cocos2dx_extension_ControlPotentiometer_getPreviousLocation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("distanceBetweenPointAndPoint", js_cocos2dx_extension_ControlPotentiometer_distanceBetweenPointAndPoint, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("potentiometerEnded", js_cocos2dx_extension_ControlPotentiometer_potentiometerEnded, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProgressTimer", js_cocos2dx_extension_ControlPotentiometer_setProgressTimer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinimumValue", js_cocos2dx_extension_ControlPotentiometer_setMinimumValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getThumbSprite", js_cocos2dx_extension_ControlPotentiometer_getThumbSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithTrackSprite_ProgressTimer_ThumbSprite", js_cocos2dx_extension_ControlPotentiometer_initWithTrackSprite_ProgressTimer_ThumbSprite, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("potentiometerMoved", js_cocos2dx_extension_ControlPotentiometer_potentiometerMoved, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ControlPotentiometer_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlPotentiometer_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlPotentiometer_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlPotentiometer_class,
        js_cocos2dx_extension_ControlPotentiometer_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlPotentiometer_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlPotentiometer"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlPotentiometer>(cx, jsb_cocos2d_extension_ControlPotentiometer_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ControlPotentiometer.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_ControlSlider_class;
JSObject *jsb_cocos2d_extension_ControlSlider_prototype;

bool js_cocos2dx_extension_ControlSlider_setBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setBackgroundSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setBackgroundSprite : Error processing arguments");
        cobj->setBackgroundSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getMaximumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getMaximumAllowedValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaximumAllowedValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getMaximumAllowedValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_initWithSprites(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::extension::ControlSlider* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_initWithSprites : Invalid Native Object");
    do {
        if (argc == 4) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg3 = nullptr;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(3).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSprites(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 3) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithSprites(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_initWithSprites : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getMinimumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getMinimumAllowedValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMinimumAllowedValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getMinimumAllowedValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getMaximumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getMaximumValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMaximumValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getMaximumValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getSelectedThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getSelectedThumbSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getSelectedThumbSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getSelectedThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setProgressSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setProgressSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setProgressSprite : Error processing arguments");
        cobj->setProgressSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setProgressSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setMaximumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setMaximumValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setMaximumValue : Error processing arguments");
        cobj->setMaximumValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setMaximumValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getMinimumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getMinimumValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getMinimumValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getMinimumValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setThumbSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setThumbSprite : Error processing arguments");
        cobj->setThumbSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getBackgroundSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getBackgroundSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getBackgroundSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getBackgroundSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getThumbSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getThumbSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setValue : Error processing arguments");
        cobj->setValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_locationFromTouch(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_locationFromTouch : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Touch* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_locationFromTouch : Error processing arguments");
        cocos2d::Vec2 ret = cobj->locationFromTouch(arg0);
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_locationFromTouch : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setMinimumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setMinimumValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setMinimumValue : Error processing arguments");
        cobj->setMinimumValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setMinimumValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setMinimumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setMinimumAllowedValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setMinimumAllowedValue : Error processing arguments");
        cobj->setMinimumAllowedValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setMinimumAllowedValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_getProgressSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_getProgressSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getProgressSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_getProgressSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setSelectedThumbSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setSelectedThumbSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setSelectedThumbSprite : Error processing arguments");
        cobj->setSelectedThumbSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setSelectedThumbSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_setMaximumAllowedValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSlider* cobj = (cocos2d::extension::ControlSlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSlider_setMaximumAllowedValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSlider_setMaximumAllowedValue : Error processing arguments");
        cobj->setMaximumAllowedValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_setMaximumAllowedValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSlider_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 3) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSlider>(cx, (cocos2d::extension::ControlSlider*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 3) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg2 = nullptr;
            std::string arg2_tmp; ok &= jsval_to_std_string(cx, args.get(2), &arg2_tmp); arg2 = arg2_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSlider>(cx, (cocos2d::extension::ControlSlider*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 4) {
            const char* arg0 = nullptr;
            std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg1 = nullptr;
            std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg2 = nullptr;
            std::string arg2_tmp; ok &= jsval_to_std_string(cx, args.get(2), &arg2_tmp); arg2 = arg2_tmp.c_str();
            if (!ok) { ok = true; break; }
            const char* arg3 = nullptr;
            std::string arg3_tmp; ok &= jsval_to_std_string(cx, args.get(3), &arg3_tmp); arg3 = arg3_tmp.c_str();
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSlider>(cx, (cocos2d::extension::ControlSlider*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 4) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg3 = nullptr;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(3).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlSlider* ret = cocos2d::extension::ControlSlider::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSlider>(cx, (cocos2d::extension::ControlSlider*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_extension_ControlSlider_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlSlider_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlSlider* cobj = new (std::nothrow) cocos2d::extension::ControlSlider();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlSlider>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlSlider"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ControlSlider_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ControlSlider *nobj = new (std::nothrow) cocos2d::extension::ControlSlider();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ControlSlider");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

    
void js_register_cocos2dx_extension_ControlSlider(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlSlider_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlSlider_class->name = "ControlSlider";
    jsb_cocos2d_extension_ControlSlider_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlSlider_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlSlider_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlSlider_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlSlider_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlSlider_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlSlider_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlSlider_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setBackgroundSprite", js_cocos2dx_extension_ControlSlider_setBackgroundSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaximumAllowedValue", js_cocos2dx_extension_ControlSlider_getMaximumAllowedValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithSprites", js_cocos2dx_extension_ControlSlider_initWithSprites, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMinimumAllowedValue", js_cocos2dx_extension_ControlSlider_getMinimumAllowedValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaximumValue", js_cocos2dx_extension_ControlSlider_getMaximumValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSelectedThumbSprite", js_cocos2dx_extension_ControlSlider_getSelectedThumbSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProgressSprite", js_cocos2dx_extension_ControlSlider_setProgressSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaximumValue", js_cocos2dx_extension_ControlSlider_setMaximumValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMinimumValue", js_cocos2dx_extension_ControlSlider_getMinimumValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setThumbSprite", js_cocos2dx_extension_ControlSlider_setThumbSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getValue", js_cocos2dx_extension_ControlSlider_getValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getBackgroundSprite", js_cocos2dx_extension_ControlSlider_getBackgroundSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getThumbSprite", js_cocos2dx_extension_ControlSlider_getThumbSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setValue", js_cocos2dx_extension_ControlSlider_setValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("locationFromTouch", js_cocos2dx_extension_ControlSlider_locationFromTouch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinimumValue", js_cocos2dx_extension_ControlSlider_setMinimumValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinimumAllowedValue", js_cocos2dx_extension_ControlSlider_setMinimumAllowedValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getProgressSprite", js_cocos2dx_extension_ControlSlider_getProgressSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSelectedThumbSprite", js_cocos2dx_extension_ControlSlider_setSelectedThumbSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaximumAllowedValue", js_cocos2dx_extension_ControlSlider_setMaximumAllowedValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ControlSlider_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlSlider_create, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlSlider_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlSlider_class,
        js_cocos2dx_extension_ControlSlider_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlSlider_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlSlider"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlSlider>(cx, jsb_cocos2d_extension_ControlSlider_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ControlSlider.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_ControlStepper_class;
JSObject *jsb_cocos2d_extension_ControlStepper_prototype;

bool js_cocos2dx_extension_ControlStepper_getMinusSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_getMinusSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getMinusSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_getMinusSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setValue : Error processing arguments");
        cobj->setValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setStepValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setStepValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setStepValue : Error processing arguments");
        cobj->setStepValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setStepValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_initWithMinusSpriteAndPlusSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_initWithMinusSpriteAndPlusSprite : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Sprite* arg0 = nullptr;
        cocos2d::Sprite* arg1 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_initWithMinusSpriteAndPlusSprite : Error processing arguments");
        bool ret = cobj->initWithMinusSpriteAndPlusSprite(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_initWithMinusSpriteAndPlusSprite : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setValueWithSendingEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setValueWithSendingEvent : Invalid Native Object");
    if (argc == 2) {
        double arg0 = 0;
        bool arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setValueWithSendingEvent : Error processing arguments");
        cobj->setValueWithSendingEvent(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setValueWithSendingEvent : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setMaximumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setMaximumValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setMaximumValue : Error processing arguments");
        cobj->setMaximumValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setMaximumValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_getMinusLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_getMinusLabel : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Label* ret = cobj->getMinusLabel();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Label>(cx, (cocos2d::Label*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_getMinusLabel : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_getPlusLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_getPlusLabel : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Label* ret = cobj->getPlusLabel();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Label>(cx, (cocos2d::Label*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_getPlusLabel : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setWraps(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setWraps : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setWraps : Error processing arguments");
        cobj->setWraps(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setWraps : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setMinusLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setMinusLabel : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Label* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Label*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setMinusLabel : Error processing arguments");
        cobj->setMinusLabel(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setMinusLabel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_startAutorepeat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_startAutorepeat : Invalid Native Object");
    if (argc == 0) {
        cobj->startAutorepeat();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_startAutorepeat : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_updateLayoutUsingTouchLocation(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_updateLayoutUsingTouchLocation : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_updateLayoutUsingTouchLocation : Error processing arguments");
        cobj->updateLayoutUsingTouchLocation(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_updateLayoutUsingTouchLocation : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_isContinuous(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_isContinuous : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isContinuous();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_isContinuous : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_stopAutorepeat(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_stopAutorepeat : Invalid Native Object");
    if (argc == 0) {
        cobj->stopAutorepeat();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_stopAutorepeat : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setMinimumValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setMinimumValue : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setMinimumValue : Error processing arguments");
        cobj->setMinimumValue(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setMinimumValue : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setPlusLabel(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setPlusLabel : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Label* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Label*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setPlusLabel : Error processing arguments");
        cobj->setPlusLabel(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setPlusLabel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_getValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_getValue : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getValue();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_getValue : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_getPlusSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_getPlusSprite : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Sprite* ret = cobj->getPlusSprite();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_getPlusSprite : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setPlusSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setPlusSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setPlusSprite : Error processing arguments");
        cobj->setPlusSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setPlusSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_setMinusSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlStepper* cobj = (cocos2d::extension::ControlStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlStepper_setMinusSprite : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Sprite* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_setMinusSprite : Error processing arguments");
        cobj->setMinusSprite(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_setMinusSprite : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlStepper_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Sprite* arg0 = nullptr;
        cocos2d::Sprite* arg1 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlStepper_create : Error processing arguments");

        auto ret = cocos2d::extension::ControlStepper::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlStepper>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::ControlStepper"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_ControlStepper_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_ControlStepper_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlStepper* cobj = new (std::nothrow) cocos2d::extension::ControlStepper();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlStepper>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlStepper"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ControlStepper_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ControlStepper *nobj = new (std::nothrow) cocos2d::extension::ControlStepper();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ControlStepper");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

    
void js_register_cocos2dx_extension_ControlStepper(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlStepper_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlStepper_class->name = "ControlStepper";
    jsb_cocos2d_extension_ControlStepper_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlStepper_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlStepper_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlStepper_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlStepper_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlStepper_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlStepper_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlStepper_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getMinusSprite", js_cocos2dx_extension_ControlStepper_getMinusSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setValue", js_cocos2dx_extension_ControlStepper_setValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStepValue", js_cocos2dx_extension_ControlStepper_setStepValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithMinusSpriteAndPlusSprite", js_cocos2dx_extension_ControlStepper_initWithMinusSpriteAndPlusSprite, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setValueWithSendingEvent", js_cocos2dx_extension_ControlStepper_setValueWithSendingEvent, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaximumValue", js_cocos2dx_extension_ControlStepper_setMaximumValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMinusLabel", js_cocos2dx_extension_ControlStepper_getMinusLabel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlusLabel", js_cocos2dx_extension_ControlStepper_getPlusLabel, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setWraps", js_cocos2dx_extension_ControlStepper_setWraps, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinusLabel", js_cocos2dx_extension_ControlStepper_setMinusLabel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("startAutorepeat", js_cocos2dx_extension_ControlStepper_startAutorepeat, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateLayoutUsingTouchLocation", js_cocos2dx_extension_ControlStepper_updateLayoutUsingTouchLocation, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isContinuous", js_cocos2dx_extension_ControlStepper_isContinuous, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAutorepeat", js_cocos2dx_extension_ControlStepper_stopAutorepeat, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinimumValue", js_cocos2dx_extension_ControlStepper_setMinimumValue, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlusLabel", js_cocos2dx_extension_ControlStepper_setPlusLabel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getValue", js_cocos2dx_extension_ControlStepper_getValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlusSprite", js_cocos2dx_extension_ControlStepper_getPlusSprite, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlusSprite", js_cocos2dx_extension_ControlStepper_setPlusSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinusSprite", js_cocos2dx_extension_ControlStepper_setMinusSprite, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ControlStepper_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlStepper_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlStepper_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlStepper_class,
        js_cocos2dx_extension_ControlStepper_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlStepper_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlStepper"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlStepper>(cx, jsb_cocos2d_extension_ControlStepper_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ControlStepper.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_ControlSwitch_class;
JSObject *jsb_cocos2d_extension_ControlSwitch_prototype;

bool js_cocos2dx_extension_ControlSwitch_setOn(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::extension::ControlSwitch* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::extension::ControlSwitch *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSwitch_setOn : Invalid Native Object");
    do {
        if (argc == 1) {
            bool arg0;
            arg0 = JS::ToBoolean(args.get(0));
            cobj->setOn(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            bool arg0;
            arg0 = JS::ToBoolean(args.get(0));
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->setOn(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSwitch_setOn : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlSwitch_locationFromTouch(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSwitch* cobj = (cocos2d::extension::ControlSwitch *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSwitch_locationFromTouch : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Touch* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Touch*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ControlSwitch_locationFromTouch : Error processing arguments");
        cocos2d::Vec2 ret = cobj->locationFromTouch(arg0);
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSwitch_locationFromTouch : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ControlSwitch_isOn(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSwitch* cobj = (cocos2d::extension::ControlSwitch *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSwitch_isOn : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isOn();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSwitch_isOn : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSwitch_initWithMaskSprite(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::extension::ControlSwitch* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::extension::ControlSwitch *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSwitch_initWithMaskSprite : Invalid Native Object");
    do {
        if (argc == 6) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg3 = nullptr;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(3).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Label* arg4 = nullptr;
            do {
                if (args.get(4).isNull()) { arg4 = nullptr; break; }
                if (!args.get(4).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(4).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg4 = (cocos2d::Label*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Label* arg5 = nullptr;
            do {
                if (args.get(5).isNull()) { arg5 = nullptr; break; }
                if (!args.get(5).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(5).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg5 = (cocos2d::Label*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithMaskSprite(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    do {
        if (argc == 4) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg3 = nullptr;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(3).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            bool ret = cobj->initWithMaskSprite(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            jsret = BOOLEAN_TO_JSVAL(ret);
            args.rval().set(jsret);
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSwitch_initWithMaskSprite : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlSwitch_hasMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ControlSwitch* cobj = (cocos2d::extension::ControlSwitch *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ControlSwitch_hasMoved : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->hasMoved();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ControlSwitch_hasMoved : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ControlSwitch_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 4) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg3 = nullptr;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(3).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlSwitch* ret = cocos2d::extension::ControlSwitch::create(arg0, arg1, arg2, arg3);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSwitch>(cx, (cocos2d::extension::ControlSwitch*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 6) {
            cocos2d::Sprite* arg0 = nullptr;
            do {
                if (args.get(0).isNull()) { arg0 = nullptr; break; }
                if (!args.get(0).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg2 = nullptr;
            do {
                if (args.get(2).isNull()) { arg2 = nullptr; break; }
                if (!args.get(2).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Sprite* arg3 = nullptr;
            do {
                if (args.get(3).isNull()) { arg3 = nullptr; break; }
                if (!args.get(3).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(3).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocos2d::Sprite*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Label* arg4 = nullptr;
            do {
                if (args.get(4).isNull()) { arg4 = nullptr; break; }
                if (!args.get(4).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(4).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg4 = (cocos2d::Label*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg4, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::Label* arg5 = nullptr;
            do {
                if (args.get(5).isNull()) { arg5 = nullptr; break; }
                if (!args.get(5).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(5).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg5 = (cocos2d::Label*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg5, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ControlSwitch* ret = cocos2d::extension::ControlSwitch::create(arg0, arg1, arg2, arg3, arg4, arg5);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ControlSwitch>(cx, (cocos2d::extension::ControlSwitch*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_extension_ControlSwitch_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ControlSwitch_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ControlSwitch* cobj = new (std::nothrow) cocos2d::extension::ControlSwitch();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ControlSwitch>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ControlSwitch"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ControlSwitch_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ControlSwitch *nobj = new (std::nothrow) cocos2d::extension::ControlSwitch();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ControlSwitch");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_Control_prototype;

    
void js_register_cocos2dx_extension_ControlSwitch(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ControlSwitch_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ControlSwitch_class->name = "ControlSwitch";
    jsb_cocos2d_extension_ControlSwitch_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlSwitch_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ControlSwitch_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ControlSwitch_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ControlSwitch_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ControlSwitch_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ControlSwitch_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ControlSwitch_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setOn", js_cocos2dx_extension_ControlSwitch_setOn, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("locationFromTouch", js_cocos2dx_extension_ControlSwitch_locationFromTouch, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isOn", js_cocos2dx_extension_ControlSwitch_isOn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithMaskSprite", js_cocos2dx_extension_ControlSwitch_initWithMaskSprite, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasMoved", js_cocos2dx_extension_ControlSwitch_hasMoved, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ControlSwitch_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ControlSwitch_create, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_Control_prototype);
    jsb_cocos2d_extension_ControlSwitch_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ControlSwitch_class,
        js_cocos2dx_extension_ControlSwitch_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ControlSwitch_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ControlSwitch"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ControlSwitch>(cx, jsb_cocos2d_extension_ControlSwitch_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ControlSwitch.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_ScrollView_class;
JSObject *jsb_cocos2d_extension_ScrollView_prototype;

bool js_cocos2dx_extension_ScrollView_isClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_isClippingToBounds : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isClippingToBounds();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_isClippingToBounds : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setContainer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setContainer : Invalid Native Object");
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setContainer : Error processing arguments");
        cobj->setContainer(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setContainer : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setContentOffsetInDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setContentOffsetInDuration : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Vec2 arg0;
        double arg1 = 0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setContentOffsetInDuration : Error processing arguments");
        cobj->setContentOffsetInDuration(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setContentOffsetInDuration : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setZoomScaleInDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setZoomScaleInDuration : Invalid Native Object");
    if (argc == 2) {
        double arg0 = 0;
        double arg1 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setZoomScaleInDuration : Error processing arguments");
        cobj->setZoomScaleInDuration(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setZoomScaleInDuration : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ScrollView_updateTweenAction(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_updateTweenAction : Invalid Native Object");
    if (argc == 2) {
        double arg0 = 0;
        std::string arg1;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_updateTweenAction : Error processing arguments");
        cobj->updateTweenAction(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_updateTweenAction : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setMaxScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setMaxScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setMaxScale : Error processing arguments");
        cobj->setMaxScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setMaxScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_hasVisibleParents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_hasVisibleParents : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->hasVisibleParents();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_hasVisibleParents : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setSwallowTouches(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setSwallowTouches : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setSwallowTouches : Error processing arguments");
        cobj->setSwallowTouches(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setSwallowTouches : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_getContainer(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_getContainer : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getContainer();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_getContainer : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setMinScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setMinScale : Invalid Native Object");
    if (argc == 1) {
        double arg0 = 0;
        ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setMinScale : Error processing arguments");
        cobj->setMinScale(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setMinScale : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_getZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_getZoomScale : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getZoomScale();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_getZoomScale : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_updateInset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_updateInset : Invalid Native Object");
    if (argc == 0) {
        cobj->updateInset();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_updateInset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_initWithViewSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_initWithViewSize : Error processing arguments");
        bool ret = cobj->initWithViewSize(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        cocos2d::Size arg0;
        cocos2d::Node* arg1 = nullptr;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_initWithViewSize : Error processing arguments");
        bool ret = cobj->initWithViewSize(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_initWithViewSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_pause(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_pause : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_pause : Error processing arguments");
        cobj->pause(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_pause : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setDirection : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::ScrollView::Direction arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setDirection : Error processing arguments");
        cobj->setDirection(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setDirection : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_stopAnimatedContentOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_stopAnimatedContentOffset : Invalid Native Object");
    if (argc == 0) {
        cobj->stopAnimatedContentOffset();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_stopAnimatedContentOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setContentOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setContentOffset : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vec2 arg0;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setContentOffset : Error processing arguments");
        cobj->setContentOffset(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        cocos2d::Vec2 arg0;
        bool arg1;
        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
        arg1 = JS::ToBoolean(args.get(1));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setContentOffset : Error processing arguments");
        cobj->setContentOffset(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setContentOffset : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_isDragging(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_isDragging : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isDragging();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_isDragging : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_isTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_isTouchEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouchEnabled();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_isTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_isBounceable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_isBounceable : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isBounceable();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_isBounceable : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setTouchEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setTouchEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setTouchEnabled : Error processing arguments");
        cobj->setTouchEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setTouchEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_getContentOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_getContentOffset : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->getContentOffset();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_getContentOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_resume(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_resume : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Ref* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_resume : Error processing arguments");
        cobj->resume(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_resume : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setClippingToBounds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setClippingToBounds : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setClippingToBounds : Error processing arguments");
        cobj->setClippingToBounds(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setClippingToBounds : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setViewSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setViewSize : Error processing arguments");
        cobj->setViewSize(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setViewSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_getViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_getViewSize : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Size ret = cobj->getViewSize();
        JS::RootedValue jsret(cx);
        jsret = ccsize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_getViewSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_maxContainerOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_maxContainerOffset : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->maxContainerOffset();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_maxContainerOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setBounceable(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setBounceable : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_setBounceable : Error processing arguments");
        cobj->setBounceable(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setBounceable : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_isTouchMoved(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_isTouchMoved : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isTouchMoved();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_isTouchMoved : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_isNodeVisible(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_isNodeVisible : Invalid Native Object");
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_ScrollView_isNodeVisible : Error processing arguments");
        bool ret = cobj->isNodeVisible(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_isNodeVisible : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_ScrollView_minContainerOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_minContainerOffset : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vec2 ret = cobj->minContainerOffset();
        JS::RootedValue jsret(cx);
        jsret = vector2_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_minContainerOffset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_getDirection(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_getDirection : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getDirection();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_getDirection : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_ScrollView_setZoomScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    cocos2d::extension::ScrollView* cobj = nullptr;

    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_ScrollView_setZoomScale : Invalid Native Object");
    do {
        if (argc == 2) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
            if (!ok) { ok = true; break; }
            bool arg1;
            arg1 = JS::ToBoolean(args.get(1));
            cobj->setZoomScale(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 1) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
            if (!ok) { ok = true; break; }
            cobj->setZoomScale(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_setZoomScale : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ScrollView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    
    do {
        if (argc == 0) {
            cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ScrollView>(cx, (cocos2d::extension::ScrollView*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    
    do {
        if (argc == 1) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ScrollView>(cx, (cocos2d::extension::ScrollView*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    do {
        if (argc == 2) {
            cocos2d::Size arg0;
            ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cocos2d::Node* arg1 = nullptr;
            do {
                if (args.get(1).isNull()) { arg1 = nullptr; break; }
                if (!args.get(1).isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocos2d::extension::ScrollView* ret = cocos2d::extension::ScrollView::create(arg0, arg1);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::ScrollView>(cx, (cocos2d::extension::ScrollView*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while (0);
    JS_ReportError(cx, "js_cocos2dx_extension_ScrollView_create : wrong number of arguments");
    return false;
}
bool js_cocos2dx_extension_ScrollView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::ScrollView* cobj = new (std::nothrow) cocos2d::extension::ScrollView();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::ScrollView>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::ScrollView"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_ScrollView_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::ScrollView *nobj = new (std::nothrow) cocos2d::extension::ScrollView();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::ScrollView");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Layer_prototype;

    
void js_register_cocos2dx_extension_ScrollView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_ScrollView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_ScrollView_class->name = "ScrollView";
    jsb_cocos2d_extension_ScrollView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ScrollView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_ScrollView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_ScrollView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_ScrollView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_ScrollView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_ScrollView_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_ScrollView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isClippingToBounds", js_cocos2dx_extension_ScrollView_isClippingToBounds, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setContainer", js_cocos2dx_extension_ScrollView_setContainer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setContentOffsetInDuration", js_cocos2dx_extension_ScrollView_setContentOffsetInDuration, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomScaleInDuration", js_cocos2dx_extension_ScrollView_setZoomScaleInDuration, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateTweenAction", js_cocos2dx_extension_ScrollView_updateTweenAction, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxScale", js_cocos2dx_extension_ScrollView_setMaxScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hasVisibleParents", js_cocos2dx_extension_ScrollView_hasVisibleParents, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSwallowTouches", js_cocos2dx_extension_ScrollView_setSwallowTouches, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getContainer", js_cocos2dx_extension_ScrollView_getContainer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMinScale", js_cocos2dx_extension_ScrollView_setMinScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getZoomScale", js_cocos2dx_extension_ScrollView_getZoomScale, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("updateInset", js_cocos2dx_extension_ScrollView_updateInset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithViewSize", js_cocos2dx_extension_ScrollView_initWithViewSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pause", js_cocos2dx_extension_ScrollView_pause, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDirection", js_cocos2dx_extension_ScrollView_setDirection, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopAnimatedContentOffset", js_cocos2dx_extension_ScrollView_stopAnimatedContentOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setContentOffset", js_cocos2dx_extension_ScrollView_setContentOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isDragging", js_cocos2dx_extension_ScrollView_isDragging, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchEnabled", js_cocos2dx_extension_ScrollView_isTouchEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isBounceable", js_cocos2dx_extension_ScrollView_isBounceable, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setTouchEnabled", js_cocos2dx_extension_ScrollView_setTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getContentOffset", js_cocos2dx_extension_ScrollView_getContentOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("resume", js_cocos2dx_extension_ScrollView_resume, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setClippingToBounds", js_cocos2dx_extension_ScrollView_setClippingToBounds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setViewSize", js_cocos2dx_extension_ScrollView_setViewSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getViewSize", js_cocos2dx_extension_ScrollView_getViewSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("maxContainerOffset", js_cocos2dx_extension_ScrollView_maxContainerOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBounceable", js_cocos2dx_extension_ScrollView_setBounceable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isTouchMoved", js_cocos2dx_extension_ScrollView_isTouchMoved, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isNodeVisible", js_cocos2dx_extension_ScrollView_isNodeVisible, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("minContainerOffset", js_cocos2dx_extension_ScrollView_minContainerOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDirection", js_cocos2dx_extension_ScrollView_getDirection, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setZoomScale", js_cocos2dx_extension_ScrollView_setZoomScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_ScrollView_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_ScrollView_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Layer_prototype);
    jsb_cocos2d_extension_ScrollView_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_ScrollView_class,
        js_cocos2dx_extension_ScrollView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_ScrollView_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "ScrollView"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::ScrollView>(cx, jsb_cocos2d_extension_ScrollView_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.ScrollView.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_TableViewCell_class;
JSObject *jsb_cocos2d_extension_TableViewCell_prototype;

bool js_cocos2dx_extension_TableViewCell_reset(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableViewCell* cobj = (cocos2d::extension::TableViewCell *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableViewCell_reset : Invalid Native Object");
    if (argc == 0) {
        cobj->reset();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableViewCell_reset : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_TableViewCell_getIdx(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableViewCell* cobj = (cocos2d::extension::TableViewCell *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableViewCell_getIdx : Invalid Native Object");
    if (argc == 0) {
        ssize_t ret = cobj->getIdx();
        JS::RootedValue jsret(cx);
        jsret = ssize_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableViewCell_getIdx : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_TableViewCell_setIdx(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableViewCell* cobj = (cocos2d::extension::TableViewCell *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableViewCell_setIdx : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0 = 0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableViewCell_setIdx : Error processing arguments");
        cobj->setIdx(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableViewCell_setIdx : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableViewCell_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        auto ret = cocos2d::extension::TableViewCell::create();
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::TableViewCell>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::TableViewCell"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_TableViewCell_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_TableViewCell_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::TableViewCell* cobj = new (std::nothrow) cocos2d::extension::TableViewCell();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::TableViewCell>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::TableViewCell"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_TableViewCell_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::TableViewCell *nobj = new (std::nothrow) cocos2d::extension::TableViewCell();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::TableViewCell");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_Node_prototype;

    
void js_register_cocos2dx_extension_TableViewCell(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_TableViewCell_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_TableViewCell_class->name = "TableViewCell";
    jsb_cocos2d_extension_TableViewCell_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_TableViewCell_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_TableViewCell_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_TableViewCell_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_TableViewCell_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_TableViewCell_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_TableViewCell_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_TableViewCell_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("reset", js_cocos2dx_extension_TableViewCell_reset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getIdx", js_cocos2dx_extension_TableViewCell_getIdx, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIdx", js_cocos2dx_extension_TableViewCell_setIdx, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_TableViewCell_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_TableViewCell_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_cocos2d_extension_TableViewCell_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_TableViewCell_class,
        js_cocos2dx_extension_TableViewCell_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_TableViewCell_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "TableViewCell"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::TableViewCell>(cx, jsb_cocos2d_extension_TableViewCell_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.TableViewCell.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_TableView_class;
JSObject *jsb_cocos2d_extension_TableView_prototype;

bool js_cocos2dx_extension_TableView_updateCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_updateCellAtIndex : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0 = 0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_updateCellAtIndex : Error processing arguments");
        cobj->updateCellAtIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_updateCellAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_setVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_setVerticalFillOrder : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::TableView::VerticalFillOrder arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_setVerticalFillOrder : Error processing arguments");
        cobj->setVerticalFillOrder(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_setVerticalFillOrder : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_scrollViewDidZoom(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_scrollViewDidZoom : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::ScrollView* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::extension::ScrollView*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_scrollViewDidZoom : Error processing arguments");
        cobj->scrollViewDidZoom(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_scrollViewDidZoom : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView__updateContentSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView__updateContentSize : Invalid Native Object");
    if (argc == 0) {
        cobj->_updateContentSize();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView__updateContentSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_TableView_getVerticalFillOrder(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_getVerticalFillOrder : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getVerticalFillOrder();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_getVerticalFillOrder : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_TableView_removeCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_removeCellAtIndex : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0 = 0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_removeCellAtIndex : Error processing arguments");
        cobj->removeCellAtIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_removeCellAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_initWithViewSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_initWithViewSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_initWithViewSize : Error processing arguments");
        bool ret = cobj->initWithViewSize(arg0);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 2) {
        cocos2d::Size arg0;
        cocos2d::Node* arg1 = nullptr;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_initWithViewSize : Error processing arguments");
        bool ret = cobj->initWithViewSize(arg0, arg1);
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_initWithViewSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_scrollViewDidScroll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_scrollViewDidScroll : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::ScrollView* arg0 = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::extension::ScrollView*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_scrollViewDidScroll : Error processing arguments");
        cobj->scrollViewDidScroll(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_scrollViewDidScroll : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_reloadData(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_reloadData : Invalid Native Object");
    if (argc == 0) {
        cobj->reloadData();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_reloadData : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_TableView_insertCellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_insertCellAtIndex : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0 = 0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_insertCellAtIndex : Error processing arguments");
        cobj->insertCellAtIndex(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_insertCellAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_cellAtIndex(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_cellAtIndex : Invalid Native Object");
    if (argc == 1) {
        ssize_t arg0 = 0;
        ok &= jsval_to_ssize(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_TableView_cellAtIndex : Error processing arguments");
        cocos2d::extension::TableViewCell* ret = cobj->cellAtIndex(arg0);
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::TableViewCell>(cx, (cocos2d::extension::TableViewCell*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_cellAtIndex : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_TableView_dequeueCell(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_dequeueCell : Invalid Native Object");
    if (argc == 0) {
        cocos2d::extension::TableViewCell* ret = cobj->dequeueCell();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::TableViewCell>(cx, (cocos2d::extension::TableViewCell*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_TableView_dequeueCell : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_TableView_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::TableView* cobj = new (std::nothrow) cocos2d::extension::TableView();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::TableView>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::TableView"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}
static bool js_cocos2dx_extension_TableView_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    cocos2d::extension::TableView *nobj = new (std::nothrow) cocos2d::extension::TableView();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "cocos2d::extension::TableView");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}


extern JSObject *jsb_cocos2d_extension_ScrollView_prototype;

    
void js_register_cocos2dx_extension_TableView(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_TableView_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_TableView_class->name = "TableView";
    jsb_cocos2d_extension_TableView_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_TableView_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_TableView_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_TableView_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_TableView_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_TableView_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_TableView_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_TableView_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("updateCellAtIndex", js_cocos2dx_extension_TableView_updateCellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVerticalFillOrder", js_cocos2dx_extension_TableView_setVerticalFillOrder, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollViewDidZoom", js_cocos2dx_extension_TableView_scrollViewDidZoom, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("_updateContentSize", js_cocos2dx_extension_TableView__updateContentSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVerticalFillOrder", js_cocos2dx_extension_TableView_getVerticalFillOrder, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeCellAtIndex", js_cocos2dx_extension_TableView_removeCellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("initWithViewSize", js_cocos2dx_extension_TableView_initWithViewSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("scrollViewDidScroll", js_cocos2dx_extension_TableView_scrollViewDidScroll, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("reloadData", js_cocos2dx_extension_TableView_reloadData, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("insertCellAtIndex", js_cocos2dx_extension_TableView_insertCellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("cellAtIndex", js_cocos2dx_extension_TableView_cellAtIndex, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("dequeueCell", js_cocos2dx_extension_TableView_dequeueCell, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_cocos2dx_extension_TableView_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_cocos2d_extension_ScrollView_prototype);
    jsb_cocos2d_extension_TableView_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_TableView_class,
        js_cocos2dx_extension_TableView_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_TableView_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "TableView"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::TableView>(cx, jsb_cocos2d_extension_TableView_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { cc.TableView.extend = cc.Class.extend; })()");
}

JSClass  *jsb_cocos2d_extension_EventAssetsManagerEx_class;
JSObject *jsb_cocos2d_extension_EventAssetsManagerEx_prototype;

bool js_cocos2dx_extension_EventAssetsManagerEx_getAssetsManagerEx(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getAssetsManagerEx : Invalid Native Object");
    if (argc == 0) {
        cocos2d::extension::AssetsManagerEx* ret = cobj->getAssetsManagerEx();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::AssetsManagerEx>(cx, (cocos2d::extension::AssetsManagerEx*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getAssetsManagerEx : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getAssetId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getAssetId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getAssetId();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getAssetId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getCURLECode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getCURLECode : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCURLECode();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getCURLECode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getMessage(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getMessage : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getMessage();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getMessage : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getCURLMCode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getCURLMCode : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getCURLMCode();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getCURLMCode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getPercentByFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getPercentByFile : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPercentByFile();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getPercentByFile : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getEventCode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getEventCode : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getEventCode();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getEventCode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_getPercent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventAssetsManagerEx* cobj = (cocos2d::extension::EventAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_getPercent : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getPercent();
        JS::RootedValue jsret(cx);
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventAssetsManagerEx_getPercent : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_EventAssetsManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    std::string arg0;
    cocos2d::extension::AssetsManagerEx* arg1 = nullptr;
    cocos2d::extension::EventAssetsManagerEx::EventCode arg2;
    ok &= jsval_to_std_string(cx, args.get(0), &arg0);
    do {
            if (args.get(1).isNull()) { arg1 = nullptr; break; }
            if (!args.get(1).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(1).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::extension::AssetsManagerEx*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
    ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_EventAssetsManagerEx_constructor : Error processing arguments");
    cocos2d::extension::EventAssetsManagerEx* cobj = new (std::nothrow) cocos2d::extension::EventAssetsManagerEx(arg0, arg1, arg2);

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::EventAssetsManagerEx>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::EventAssetsManagerEx"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_EventCustom_prototype;

void js_register_cocos2dx_extension_EventAssetsManagerEx(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_EventAssetsManagerEx_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_EventAssetsManagerEx_class->name = "EventAssetsManager";
    jsb_cocos2d_extension_EventAssetsManagerEx_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_EventAssetsManagerEx_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAssetsManagerEx", js_cocos2dx_extension_EventAssetsManagerEx_getAssetsManagerEx, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAssetId", js_cocos2dx_extension_EventAssetsManagerEx_getAssetId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCURLECode", js_cocos2dx_extension_EventAssetsManagerEx_getCURLECode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMessage", js_cocos2dx_extension_EventAssetsManagerEx_getMessage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCURLMCode", js_cocos2dx_extension_EventAssetsManagerEx_getCURLMCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercentByFile", js_cocos2dx_extension_EventAssetsManagerEx_getPercentByFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getEventCode", js_cocos2dx_extension_EventAssetsManagerEx_getEventCode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPercent", js_cocos2dx_extension_EventAssetsManagerEx_getPercent, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_cocos2d_EventCustom_prototype);
    jsb_cocos2d_extension_EventAssetsManagerEx_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_EventAssetsManagerEx_class,
        js_cocos2dx_extension_EventAssetsManagerEx_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_EventAssetsManagerEx_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "EventAssetsManagerEx"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::EventAssetsManagerEx>(cx, jsb_cocos2d_extension_EventAssetsManagerEx_class, proto, parent_proto);
}

JSClass  *jsb_cocos2d_extension_Manifest_class;
JSObject *jsb_cocos2d_extension_Manifest_prototype;

bool js_cocos2dx_extension_Manifest_getManifestFileUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_getManifestFileUrl : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getManifestFileUrl();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_getManifestFileUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Manifest_isVersionLoaded(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_isVersionLoaded : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isVersionLoaded();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_isVersionLoaded : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Manifest_isLoaded(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_isLoaded : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLoaded();
        JS::RootedValue jsret(cx);
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_isLoaded : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Manifest_getPackageUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_getPackageUrl : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getPackageUrl();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_getPackageUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Manifest_getVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_getVersion : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getVersion();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_getVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Manifest_getVersionFileUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_getVersionFileUrl : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getVersionFileUrl();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_getVersionFileUrl : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_Manifest_getSearchPaths(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Manifest* cobj = (cocos2d::extension::Manifest *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_Manifest_getSearchPaths : Invalid Native Object");
    if (argc == 0) {
        std::vector<std::string> ret = cobj->getSearchPaths();
        JS::RootedValue jsret(cx);
        jsret = std_vector_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_Manifest_getSearchPaths : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_register_cocos2dx_extension_Manifest(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_Manifest_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_Manifest_class->name = "Manifest";
    jsb_cocos2d_extension_Manifest_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_Manifest_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_Manifest_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_Manifest_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_Manifest_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_Manifest_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_Manifest_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_Manifest_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getManifestFileUrl", js_cocos2dx_extension_Manifest_getManifestFileUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isVersionLoaded", js_cocos2dx_extension_Manifest_isVersionLoaded, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLoaded", js_cocos2dx_extension_Manifest_isLoaded, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPackageUrl", js_cocos2dx_extension_Manifest_getPackageUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVersion", js_cocos2dx_extension_Manifest_getVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getVersionFileUrl", js_cocos2dx_extension_Manifest_getVersionFileUrl, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSearchPaths", js_cocos2dx_extension_Manifest_getSearchPaths, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocos2d_extension_Manifest_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_extension_Manifest_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_Manifest_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Manifest"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::Manifest>(cx, jsb_cocos2d_extension_Manifest_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocos2d_extension_AssetsManagerEx_class;
JSObject *jsb_cocos2d_extension_AssetsManagerEx_prototype;

bool js_cocos2dx_extension_AssetsManagerEx_getState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_getState : Invalid Native Object");
    if (argc == 0) {
        int ret = (int)cobj->getState();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_getState : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_getMaxConcurrentTask(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_getMaxConcurrentTask : Invalid Native Object");
    if (argc == 0) {
        const int ret = cobj->getMaxConcurrentTask();
        JS::RootedValue jsret(cx);
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_getMaxConcurrentTask : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_checkUpdate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_checkUpdate : Invalid Native Object");
    if (argc == 0) {
        cobj->checkUpdate();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_checkUpdate : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_setVerifyCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_setVerifyCallback : Invalid Native Object");
    if (argc == 1) {
        std::function<bool (const std::string&, cocos2d::extension::ManifestAsset)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0), args.thisv()));
		        auto lambda = [=](const std::string& larg0, cocos2d::extension::ManifestAsset larg1) -> bool {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            largv[0] = std_string_to_jsval(cx, larg0);
		            largv[1] = asset_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(2, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		            bool ok = true;
		            bool ret;
		            ret = JS::ToBoolean(rval);
		            JSB_PRECONDITION2(ok, cx, false, "lambda function : Error processing return value with type bool");
		            return ret;
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManagerEx_setVerifyCallback : Error processing arguments");
        cobj->setVerifyCallback(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_setVerifyCallback : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_getStoragePath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_getStoragePath : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getStoragePath();
        JS::RootedValue jsret(cx);
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_getStoragePath : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_update(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_update : Invalid Native Object");
    if (argc == 0) {
        cobj->update();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_update : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_setVersionCompareHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_setVersionCompareHandle : Invalid Native Object");
    if (argc == 1) {
        std::function<int (const std::string&, const std::string&)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0), args.thisv()));
		        auto lambda = [=](const std::string& larg0, const std::string& larg1) -> int {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[2];
		            largv[0] = std_string_to_jsval(cx, larg0);
		            largv[1] = std_string_to_jsval(cx, larg1);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(2, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		            bool ok = true;
		            int ret;
		            ok &= jsval_to_int32(cx, rval, (int32_t *)&ret);
		            JSB_PRECONDITION2(ok, cx, false, "lambda function : Error processing return value with type int");
		            return ret;
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManagerEx_setVersionCompareHandle : Error processing arguments");
        cobj->setVersionCompareHandle(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_setVersionCompareHandle : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_setMaxConcurrentTask(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_setMaxConcurrentTask : Invalid Native Object");
    if (argc == 1) {
        int arg0 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManagerEx_setMaxConcurrentTask : Error processing arguments");
        cobj->setMaxConcurrentTask(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_setMaxConcurrentTask : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_getLocalManifest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_getLocalManifest : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::extension::Manifest* ret = cobj->getLocalManifest();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::Manifest>(cx, (cocos2d::extension::Manifest*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_getLocalManifest : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_getRemoteManifest(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_getRemoteManifest : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::extension::Manifest* ret = cobj->getRemoteManifest();
        JS::RootedValue jsret(cx);
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::extension::Manifest>(cx, (cocos2d::extension::Manifest*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_getRemoteManifest : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManagerEx* cobj = (cocos2d::extension::AssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets : Invalid Native Object");
    if (argc == 0) {
        cobj->downloadFailedAssets();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_extension_AssetsManagerEx_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManagerEx_create : Error processing arguments");

        auto ret = cocos2d::extension::AssetsManagerEx::create(arg0, arg1);
        js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::AssetsManagerEx>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "cocos2d::extension::AssetsManagerEx"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManagerEx_create : wrong number of arguments");
    return false;
}

bool js_cocos2dx_extension_AssetsManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    std::string arg0;
    std::string arg1;
    ok &= jsval_to_std_string(cx, args.get(0), &arg0);
    ok &= jsval_to_std_string(cx, args.get(1), &arg1);
    JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManagerEx_constructor : Error processing arguments");
    cocos2d::extension::AssetsManagerEx* cobj = new (std::nothrow) cocos2d::extension::AssetsManagerEx(arg0, arg1);

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::AssetsManagerEx>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::AssetsManagerEx"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


void js_register_cocos2dx_extension_AssetsManagerEx(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_AssetsManagerEx_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_AssetsManagerEx_class->name = "AssetsManager";
    jsb_cocos2d_extension_AssetsManagerEx_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_AssetsManagerEx_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getState", js_cocos2dx_extension_AssetsManagerEx_getState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getMaxConcurrentTask", js_cocos2dx_extension_AssetsManagerEx_getMaxConcurrentTask, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("checkUpdate", js_cocos2dx_extension_AssetsManagerEx_checkUpdate, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVerifyCallback", js_cocos2dx_extension_AssetsManagerEx_setVerifyCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getStoragePath", js_cocos2dx_extension_AssetsManagerEx_getStoragePath, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("update", js_cocos2dx_extension_AssetsManagerEx_update, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setVersionCompareHandle", js_cocos2dx_extension_AssetsManagerEx_setVersionCompareHandle, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setMaxConcurrentTask", js_cocos2dx_extension_AssetsManagerEx_setMaxConcurrentTask, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLocalManifest", js_cocos2dx_extension_AssetsManagerEx_getLocalManifest, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRemoteManifest", js_cocos2dx_extension_AssetsManagerEx_getRemoteManifest, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("downloadFailedAssets", js_cocos2dx_extension_AssetsManagerEx_downloadFailedAssets, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_cocos2dx_extension_AssetsManagerEx_create, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocos2d_extension_AssetsManagerEx_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_cocos2d_extension_AssetsManagerEx_class,
        js_cocos2dx_extension_AssetsManagerEx_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_AssetsManagerEx_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "AssetsManagerEx"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::AssetsManagerEx>(cx, jsb_cocos2d_extension_AssetsManagerEx_class, proto, JS::NullPtr());
}

JSClass  *jsb_cocos2d_extension_EventListenerAssetsManagerEx_class;
JSObject *jsb_cocos2d_extension_EventListenerAssetsManagerEx_prototype;

bool js_cocos2dx_extension_EventListenerAssetsManagerEx_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    cocos2d::extension::EventListenerAssetsManagerEx* cobj = new (std::nothrow) cocos2d::extension::EventListenerAssetsManagerEx();

    js_type_class_t *typeClass = js_get_type_from_native<cocos2d::extension::EventListenerAssetsManagerEx>(cobj);

    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "cocos2d::extension::EventListenerAssetsManagerEx"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


extern JSObject *jsb_cocos2d_EventListenerCustom_prototype;

void js_register_cocos2dx_extension_EventListenerAssetsManagerEx(JSContext *cx, JS::HandleObject global) {
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->name = "EventListenerAssetsManager";
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->addProperty = JS_PropertyStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->delProperty = JS_DeletePropertyStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->getProperty = JS_PropertyStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->setProperty = JS_StrictPropertyStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->enumerate = JS_EnumerateStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->resolve = JS_ResolveStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->convert = JS_ConvertStub;
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    JS::RootedObject parent_proto(cx, jsb_cocos2d_EventListenerCustom_prototype);
    jsb_cocos2d_extension_EventListenerAssetsManagerEx_prototype = JS_InitClass(
        cx, global,
        parent_proto,
        jsb_cocos2d_extension_EventListenerAssetsManagerEx_class,
        js_cocos2dx_extension_EventListenerAssetsManagerEx_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_cocos2d_extension_EventListenerAssetsManagerEx_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "EventListenerAssetsManagerEx"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<cocos2d::extension::EventListenerAssetsManagerEx>(cx, jsb_cocos2d_extension_EventListenerAssetsManagerEx_class, proto, parent_proto);
}

void register_all_cocos2dx_extension(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);

    js_register_cocos2dx_extension_AssetsManagerEx(cx, ns);
    js_register_cocos2dx_extension_Control(cx, ns);
    js_register_cocos2dx_extension_ControlHuePicker(cx, ns);
    js_register_cocos2dx_extension_TableViewCell(cx, ns);
    js_register_cocos2dx_extension_ControlStepper(cx, ns);
    js_register_cocos2dx_extension_ControlColourPicker(cx, ns);
    js_register_cocos2dx_extension_ControlButton(cx, ns);
    js_register_cocos2dx_extension_ControlSlider(cx, ns);
    js_register_cocos2dx_extension_ControlSaturationBrightnessPicker(cx, ns);
    js_register_cocos2dx_extension_ScrollView(cx, ns);
    js_register_cocos2dx_extension_Manifest(cx, ns);
    js_register_cocos2dx_extension_ControlPotentiometer(cx, ns);
    js_register_cocos2dx_extension_EventAssetsManagerEx(cx, ns);
    js_register_cocos2dx_extension_TableView(cx, ns);
    js_register_cocos2dx_extension_EventListenerAssetsManagerEx(cx, ns);
    js_register_cocos2dx_extension_ControlSwitch(cx, ns);
}

