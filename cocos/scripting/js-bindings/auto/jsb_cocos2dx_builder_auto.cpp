#include "jsb_cocos2dx_builder_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "CocosBuilder.h"

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
JSClass  *jsb_cocosbuilder_CCBAnimationManager_class;
JSObject *jsb_cocosbuilder_CCBAnimationManager_prototype;

bool js_cocos2dx_builder_CCBAnimationManager_moveAnimationsFromNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_moveAnimationsFromNode : Invalid Native Object");
    if (argc == 2) {
        cocos2d::Node* arg0;
        cocos2d::Node* arg1;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!argv[1].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_moveAnimationsFromNode : Error processing arguments");
        cobj->moveAnimationsFromNode(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_moveAnimationsFromNode : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setAutoPlaySequenceId(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setAutoPlaySequenceId : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setAutoPlaySequenceId : Error processing arguments");
        cobj->setAutoPlaySequenceId(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setAutoPlaySequenceId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNames : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector& ret = cobj->getDocumentCallbackNames();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_actionForSoundChannel(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_actionForSoundChannel : Invalid Native Object");
    if (argc == 1) {
        cocosbuilder::CCBSequenceProperty* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocosbuilder::CCBSequenceProperty*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_actionForSoundChannel : Error processing arguments");
        cocos2d::Sequence* ret = cobj->actionForSoundChannel(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sequence>(cx, (cocos2d::Sequence*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_actionForSoundChannel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setBaseValue(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setBaseValue : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Value arg0;
        cocos2d::Node* arg1;
        std::string arg2;
        ok &= jsval_to_ccvalue(cx, argv[0], &arg0);
        do {
            if (!argv[1].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setBaseValue : Error processing arguments");
        cobj->setBaseValue(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setBaseValue : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNodes : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getDocumentOutletNodes();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getLastCompletedSequenceName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getLastCompletedSequenceName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getLastCompletedSequenceName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getLastCompletedSequenceName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setRootNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setRootNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setRootNode : Error processing arguments");
        cobj->setRootNode(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setRootNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        double arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration : Error processing arguments");
        cobj->runAnimationsForSequenceNamedTweenDuration(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletName(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletName : Error processing arguments");
        cobj->addDocumentOutletName(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getRootContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getRootContainerSize : Invalid Native Object");
    if (argc == 0) {
        const cocos2d::Size& ret = cobj->getRootContainerSize();
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getRootContainerSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setDocumentControllerName(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setDocumentControllerName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setDocumentControllerName : Error processing arguments");
        cobj->setDocumentControllerName(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setDocumentControllerName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setObject(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setObject : Invalid Native Object");
    if (argc == 3) {
        cocos2d::Ref* arg0;
        cocos2d::Node* arg1;
        std::string arg2;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if (!argv[1].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg1 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setObject : Error processing arguments");
        cobj->setObject(arg0, arg1, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setObject : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getContainerSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getContainerSize : Error processing arguments");
        const cocos2d::Size& ret = cobj->getContainerSize(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = ccsize_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getContainerSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_actionForCallbackChannel(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_actionForCallbackChannel : Invalid Native Object");
    if (argc == 1) {
        cocosbuilder::CCBSequenceProperty* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocosbuilder::CCBSequenceProperty*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_actionForCallbackChannel : Error processing arguments");
        cocos2d::Sequence* ret = cobj->actionForCallbackChannel(arg0);
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sequence>(cx, (cocos2d::Sequence*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_actionForCallbackChannel : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNames : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector& ret = cobj->getDocumentOutletNames();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackControlEvents : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::EventType arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackControlEvents : Error processing arguments");
        cobj->addDocumentCallbackControlEvents(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackControlEvents : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_init : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->init();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_init : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getKeyframeCallbacks(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getKeyframeCallbacks : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector& ret = cobj->getKeyframeCallbacks();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getKeyframeCallbacks : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackControlEvents : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector& ret = cobj->getDocumentCallbackControlEvents();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackControlEvents : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setRootContainerSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setRootContainerSize : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Size arg0;
        ok &= jsval_to_ccsize(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setRootContainerSize : Error processing arguments");
        cobj->setRootContainerSize(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setRootContainerSize : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration : Invalid Native Object");
    if (argc == 2) {
        int arg0;
        double arg1;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[1]), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration : Error processing arguments");
        cobj->runAnimationsForSequenceIdTweenDuration(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getRunningSequenceName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getRunningSequenceName : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getRunningSequenceName();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getRunningSequenceName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getAutoPlaySequenceId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getAutoPlaySequenceId : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getAutoPlaySequenceId();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getAutoPlaySequenceId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackName(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackName : Error processing arguments");
        cobj->addDocumentCallbackName(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getRootNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getRootNode : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Node* ret = cobj->getRootNode();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Node>(cx, (cocos2d::Node*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getRootNode : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletNode : Error processing arguments");
        cobj->addDocumentOutletNode(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setDelegate : Invalid Native Object");
    if (argc == 1) {
        cocosbuilder::CCBAnimationManagerDelegate* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocosbuilder::CCBAnimationManagerDelegate*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setDelegate : Error processing arguments");
        cobj->setDelegate(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setDelegate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getSequenceDuration(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getSequenceDuration : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getSequenceDuration : Error processing arguments");
        double ret = cobj->getSequenceDuration(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getSequenceDuration : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackNode : Error processing arguments");
        cobj->addDocumentCallbackNode(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamed(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamed : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamed : Error processing arguments");
        cobj->runAnimationsForSequenceNamed(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamed : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getSequenceId(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getSequenceId : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getSequenceId : Error processing arguments");
        int ret = cobj->getSequenceId(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getSequenceId : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setCallFunc : Invalid Native Object");
    if (argc == 2) {
        cocos2d::CallFunc* arg0;
        std::string arg1;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::CallFunc*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setCallFunc : Error processing arguments");
        cobj->setCallFunc(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setCallFunc : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNodes : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getDocumentCallbackNodes();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_setSequences(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setSequences : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Vector<cocosbuilder::CCBSequence *> arg0;
        ok &= jsval_to_ccvector(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBAnimationManager_setSequences : Error processing arguments");
        cobj->setSequences(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_setSequences : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_debug(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_debug : Invalid Native Object");
    if (argc == 0) {
        cobj->debug();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_debug : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_getDocumentControllerName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBAnimationManager* cobj = (cocosbuilder::CCBAnimationManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBAnimationManager_getDocumentControllerName : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getDocumentControllerName();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBAnimationManager_getDocumentControllerName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBAnimationManager_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    cocosbuilder::CCBAnimationManager* cobj = new (std::nothrow) cocosbuilder::CCBAnimationManager();
    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
    if (_ccobj) {
        _ccobj->autorelease();
    }
    TypeTest<cocosbuilder::CCBAnimationManager> t;
    js_type_class_t *typeClass = nullptr;
    std::string typeName = t.s_name();
    auto typeMapIter = _js_global_type_map.find(typeName);
    CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
    typeClass = typeMapIter->second;
    CCASSERT(typeClass, "The value is null.");
    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
    JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
    // link the native object with the javascript object
    js_proxy_t* p = jsb_new_proxy(cobj, obj);
    JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBAnimationManager");
    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);
    return true;
}



void js_cocosbuilder_CCBAnimationManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCBAnimationManager)", obj);
}

void js_register_cocos2dx_builder_CCBAnimationManager(JSContext *cx, JSObject *global) {
    jsb_cocosbuilder_CCBAnimationManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocosbuilder_CCBAnimationManager_class->name = "BuilderAnimationManager";
    jsb_cocosbuilder_CCBAnimationManager_class->addProperty = JS_PropertyStub;
    jsb_cocosbuilder_CCBAnimationManager_class->delProperty = JS_DeletePropertyStub;
    jsb_cocosbuilder_CCBAnimationManager_class->getProperty = JS_PropertyStub;
    jsb_cocosbuilder_CCBAnimationManager_class->setProperty = JS_StrictPropertyStub;
    jsb_cocosbuilder_CCBAnimationManager_class->enumerate = JS_EnumerateStub;
    jsb_cocosbuilder_CCBAnimationManager_class->resolve = JS_ResolveStub;
    jsb_cocosbuilder_CCBAnimationManager_class->convert = JS_ConvertStub;
    jsb_cocosbuilder_CCBAnimationManager_class->finalize = js_cocosbuilder_CCBAnimationManager_finalize;
    jsb_cocosbuilder_CCBAnimationManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("moveAnimationsFromNode", js_cocos2dx_builder_CCBAnimationManager_moveAnimationsFromNode, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAutoPlaySequenceId", js_cocos2dx_builder_CCBAnimationManager_setAutoPlaySequenceId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDocumentCallbackNames", js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("actionForSoundChannel", js_cocos2dx_builder_CCBAnimationManager_actionForSoundChannel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBaseValue", js_cocos2dx_builder_CCBAnimationManager_setBaseValue, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDocumentOutletNodes", js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getLastCompletedSequenceName", js_cocos2dx_builder_CCBAnimationManager_getLastCompletedSequenceName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRootNode", js_cocos2dx_builder_CCBAnimationManager_setRootNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("runAnimationsForSequenceNamedTweenDuration", js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamedTweenDuration, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDocumentOutletName", js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRootContainerSize", js_cocos2dx_builder_CCBAnimationManager_getRootContainerSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDocumentControllerName", js_cocos2dx_builder_CCBAnimationManager_setDocumentControllerName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setObject", js_cocos2dx_builder_CCBAnimationManager_setObject, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getContainerSize", js_cocos2dx_builder_CCBAnimationManager_getContainerSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("actionForCallbackChannel", js_cocos2dx_builder_CCBAnimationManager_actionForCallbackChannel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDocumentOutletNames", js_cocos2dx_builder_CCBAnimationManager_getDocumentOutletNames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDocumentCallbackControlEvents", js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackControlEvents, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_cocos2dx_builder_CCBAnimationManager_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getKeyframeCallbacks", js_cocos2dx_builder_CCBAnimationManager_getKeyframeCallbacks, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDocumentCallbackControlEvents", js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackControlEvents, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setRootContainerSize", js_cocos2dx_builder_CCBAnimationManager_setRootContainerSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("runAnimationsForSequenceIdTweenDuration", js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceIdTweenDuration, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRunningSequenceName", js_cocos2dx_builder_CCBAnimationManager_getRunningSequenceName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAutoPlaySequenceId", js_cocos2dx_builder_CCBAnimationManager_getAutoPlaySequenceId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDocumentCallbackName", js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRootNode", js_cocos2dx_builder_CCBAnimationManager_getRootNode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDocumentOutletNode", js_cocos2dx_builder_CCBAnimationManager_addDocumentOutletNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDelegate", js_cocos2dx_builder_CCBAnimationManager_setDelegate, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSequenceDuration", js_cocos2dx_builder_CCBAnimationManager_getSequenceDuration, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDocumentCallbackNode", js_cocos2dx_builder_CCBAnimationManager_addDocumentCallbackNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("runAnimationsForSequenceNamed", js_cocos2dx_builder_CCBAnimationManager_runAnimationsForSequenceNamed, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSequenceId", js_cocos2dx_builder_CCBAnimationManager_getSequenceId, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCallFunc", js_cocos2dx_builder_CCBAnimationManager_setCallFunc, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDocumentCallbackNodes", js_cocos2dx_builder_CCBAnimationManager_getDocumentCallbackNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSequences", js_cocos2dx_builder_CCBAnimationManager_setSequences, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("debug", js_cocos2dx_builder_CCBAnimationManager_debug, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getDocumentControllerName", js_cocos2dx_builder_CCBAnimationManager_getDocumentControllerName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_cocosbuilder_CCBAnimationManager_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_cocosbuilder_CCBAnimationManager_class,
        js_cocos2dx_builder_CCBAnimationManager_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "BuilderAnimationManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocosbuilder::CCBAnimationManager> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocosbuilder_CCBAnimationManager_class;
        p->proto = jsb_cocosbuilder_CCBAnimationManager_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_cocosbuilder_CCBReader_class;
JSObject *jsb_cocosbuilder_CCBReader_prototype;

bool js_cocos2dx_builder_CCBReader_getAnimationManager(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getAnimationManager : Invalid Native Object");
    if (argc == 0) {
        cocosbuilder::CCBAnimationManager* ret = cobj->getAnimationManager();
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<cocosbuilder::CCBAnimationManager>(cx, (cocosbuilder::CCBAnimationManager*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getAnimationManager : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_setAnimationManager(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_setAnimationManager : Invalid Native Object");
    if (argc == 1) {
        cocosbuilder::CCBAnimationManager* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocosbuilder::CCBAnimationManager*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_setAnimationManager : Error processing arguments");
        cobj->setAnimationManager(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_setAnimationManager : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_addOwnerOutletName(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_addOwnerOutletName : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_addOwnerOutletName : Error processing arguments");
        cobj->addOwnerOutletName(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_addOwnerOutletName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getOwnerCallbackNames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getOwnerCallbackNames : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector ret = cobj->getOwnerCallbackNames();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getOwnerCallbackNames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_addDocumentCallbackControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_addDocumentCallbackControlEvents : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::EventType arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_addDocumentCallbackControlEvents : Error processing arguments");
        cobj->addDocumentCallbackControlEvents(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_addDocumentCallbackControlEvents : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_setCCBRootPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_setCCBRootPath : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_setCCBRootPath : Error processing arguments");
        cobj->setCCBRootPath(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_setCCBRootPath : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_addOwnerOutletNode(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_addOwnerOutletNode : Invalid Native Object");
    if (argc == 1) {
        cocos2d::Node* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_addOwnerOutletNode : Error processing arguments");
        cobj->addOwnerOutletNode(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_addOwnerOutletNode : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getOwnerCallbackNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getOwnerCallbackNodes : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getOwnerCallbackNodes();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getOwnerCallbackNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_readSoundKeyframesForSeq(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_readSoundKeyframesForSeq : Invalid Native Object");
    if (argc == 1) {
        cocosbuilder::CCBSequence* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocosbuilder::CCBSequence*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_readSoundKeyframesForSeq : Error processing arguments");
        bool ret = cobj->readSoundKeyframesForSeq(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_readSoundKeyframesForSeq : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getCCBRootPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getCCBRootPath : Invalid Native Object");
    if (argc == 0) {
        const std::string& ret = cobj->getCCBRootPath();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getCCBRootPath : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getOwnerCallbackControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getOwnerCallbackControlEvents : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector& ret = cobj->getOwnerCallbackControlEvents();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getOwnerCallbackControlEvents : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getOwnerOutletNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getOwnerOutletNodes : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getOwnerOutletNodes();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getOwnerOutletNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_readUTF8(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_readUTF8 : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->readUTF8();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_readUTF8 : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_addOwnerCallbackControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_addOwnerCallbackControlEvents : Invalid Native Object");
    if (argc == 1) {
        cocos2d::extension::Control::EventType arg0;
        ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_addOwnerCallbackControlEvents : Error processing arguments");
        cobj->addOwnerCallbackControlEvents(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_addOwnerCallbackControlEvents : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getOwnerOutletNames(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getOwnerOutletNames : Invalid Native Object");
    if (argc == 0) {
        cocos2d::ValueVector ret = cobj->getOwnerOutletNames();
        jsval jsret = JSVAL_NULL;
        jsret = ccvaluevector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getOwnerOutletNames : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_readCallbackKeyframesForSeq(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_readCallbackKeyframesForSeq : Invalid Native Object");
    if (argc == 1) {
        cocosbuilder::CCBSequence* arg0;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocosbuilder::CCBSequence*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_readCallbackKeyframesForSeq : Error processing arguments");
        bool ret = cobj->readCallbackKeyframesForSeq(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_readCallbackKeyframesForSeq : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getAnimationManagersForNodes(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getAnimationManagersForNodes : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocosbuilder::CCBAnimationManager *>& ret = cobj->getAnimationManagersForNodes();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getAnimationManagersForNodes : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_getNodesWithAnimationManagers(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocosbuilder::CCBReader* cobj = (cocosbuilder::CCBReader *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_builder_CCBReader_getNodesWithAnimationManagers : Invalid Native Object");
    if (argc == 0) {
        cocos2d::Vector<cocos2d::Node *>& ret = cobj->getNodesWithAnimationManagers();
        jsval jsret = JSVAL_NULL;
        jsret = ccvector_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_getNodesWithAnimationManagers : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_builder_CCBReader_setResolutionScale(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if (argc == 1) {
        double arg0;
        ok &= JS::ToNumber( cx, JS::RootedValue(cx, argv[0]), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_builder_CCBReader_setResolutionScale : Error processing arguments");
        cocosbuilder::CCBReader::setResolutionScale(arg0);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_setResolutionScale : wrong number of arguments");
    return false;
}

bool js_cocos2dx_builder_CCBReader_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;

    JSObject *obj = NULL;
    cocosbuilder::CCBReader* cobj = NULL;
    do {
        if (argc == 1) {
            cocosbuilder::CCBReader* arg0;
            do {
                if (!argv[0].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocosbuilder::CCBReader*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocosbuilder::CCBReader(arg0);
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }
            TypeTest<cocosbuilder::CCBReader> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBReader");
        }
    } while(0);

    do {
        if (argc == 1) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            do {
                if (!argv[0].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocosbuilder::NodeLoaderLibrary*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocosbuilder::CCBReader(arg0);
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }
            TypeTest<cocosbuilder::CCBReader> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBReader");
        }
    } while(0);

    do {
        if (argc == 2) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            do {
                if (!argv[0].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocosbuilder::NodeLoaderLibrary*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocosbuilder::CCBMemberVariableAssigner* arg1;
            do {
                if (!argv[1].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocosbuilder::CCBMemberVariableAssigner*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocosbuilder::CCBReader(arg0, arg1);
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }
            TypeTest<cocosbuilder::CCBReader> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBReader");
        }
    } while(0);

    do {
        if (argc == 3) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            do {
                if (!argv[0].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocosbuilder::NodeLoaderLibrary*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocosbuilder::CCBMemberVariableAssigner* arg1;
            do {
                if (!argv[1].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocosbuilder::CCBMemberVariableAssigner*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocosbuilder::CCBSelectorResolver* arg2;
            do {
                if (!argv[2].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocosbuilder::CCBSelectorResolver*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocosbuilder::CCBReader(arg0, arg1, arg2);
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }
            TypeTest<cocosbuilder::CCBReader> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBReader");
        }
    } while(0);

    do {
        if (argc == 4) {
            cocosbuilder::NodeLoaderLibrary* arg0;
            do {
                if (!argv[0].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocosbuilder::NodeLoaderLibrary*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocosbuilder::CCBMemberVariableAssigner* arg1;
            do {
                if (!argv[1].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[1]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg1 = (cocosbuilder::CCBMemberVariableAssigner*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg1, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocosbuilder::CCBSelectorResolver* arg2;
            do {
                if (!argv[2].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocosbuilder::CCBSelectorResolver*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cocosbuilder::NodeLoaderListener* arg3;
            do {
                if (!argv[3].isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[3]);
                jsProxy = jsb_get_js_proxy(tmpObj);
                arg3 = (cocosbuilder::NodeLoaderListener*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2( arg3, cx, false, "Invalid Native Object");
            } while (0);
            if (!ok) { ok = true; break; }
            cobj = new (std::nothrow) cocosbuilder::CCBReader(arg0, arg1, arg2, arg3);
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }
            TypeTest<cocosbuilder::CCBReader> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBReader");
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj = new (std::nothrow) cocosbuilder::CCBReader();
            cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
            if (_ccobj) {
                _ccobj->autorelease();
            }
            TypeTest<cocosbuilder::CCBReader> t;
            js_type_class_t *typeClass = nullptr;
            std::string typeName = t.s_name();
            auto typeMapIter = _js_global_type_map.find(typeName);
            CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
            typeClass = typeMapIter->second;
            CCASSERT(typeClass, "The value is null.");
            obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            JS_AddNamedObjectRoot(cx, &p->obj, "cocosbuilder::CCBReader");
        }
    } while(0);

    if (cobj) {
        if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
                ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", argc, argv);

        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_builder_CCBReader_constructor : wrong number of arguments");
    return false;
}



void js_cocosbuilder_CCBReader_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (CCBReader)", obj);
}

void js_register_cocos2dx_builder_CCBReader(JSContext *cx, JSObject *global) {
    jsb_cocosbuilder_CCBReader_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_cocosbuilder_CCBReader_class->name = "_Reader";
    jsb_cocosbuilder_CCBReader_class->addProperty = JS_PropertyStub;
    jsb_cocosbuilder_CCBReader_class->delProperty = JS_DeletePropertyStub;
    jsb_cocosbuilder_CCBReader_class->getProperty = JS_PropertyStub;
    jsb_cocosbuilder_CCBReader_class->setProperty = JS_StrictPropertyStub;
    jsb_cocosbuilder_CCBReader_class->enumerate = JS_EnumerateStub;
    jsb_cocosbuilder_CCBReader_class->resolve = JS_ResolveStub;
    jsb_cocosbuilder_CCBReader_class->convert = JS_ConvertStub;
    jsb_cocosbuilder_CCBReader_class->finalize = js_cocosbuilder_CCBReader_finalize;
    jsb_cocosbuilder_CCBReader_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getAnimationManager", js_cocos2dx_builder_CCBReader_getAnimationManager, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAnimationManager", js_cocos2dx_builder_CCBReader_setAnimationManager, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addOwnerOutletName", js_cocos2dx_builder_CCBReader_addOwnerOutletName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOwnerCallbackNames", js_cocos2dx_builder_CCBReader_getOwnerCallbackNames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addDocumentCallbackControlEvents", js_cocos2dx_builder_CCBReader_addDocumentCallbackControlEvents, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCCBRootPath", js_cocos2dx_builder_CCBReader_setCCBRootPath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addOwnerOutletNode", js_cocos2dx_builder_CCBReader_addOwnerOutletNode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOwnerCallbackNodes", js_cocos2dx_builder_CCBReader_getOwnerCallbackNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("readSoundKeyframesForSeq", js_cocos2dx_builder_CCBReader_readSoundKeyframesForSeq, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCCBRootPath", js_cocos2dx_builder_CCBReader_getCCBRootPath, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOwnerCallbackControlEvents", js_cocos2dx_builder_CCBReader_getOwnerCallbackControlEvents, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOwnerOutletNodes", js_cocos2dx_builder_CCBReader_getOwnerOutletNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("readUTF8", js_cocos2dx_builder_CCBReader_readUTF8, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("addOwnerCallbackControlEvents", js_cocos2dx_builder_CCBReader_addOwnerCallbackControlEvents, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOwnerOutletNames", js_cocos2dx_builder_CCBReader_getOwnerOutletNames, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("readCallbackKeyframesForSeq", js_cocos2dx_builder_CCBReader_readCallbackKeyframesForSeq, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnimationManagersForNodes", js_cocos2dx_builder_CCBReader_getAnimationManagersForNodes, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getNodesWithAnimationManagers", js_cocos2dx_builder_CCBReader_getNodesWithAnimationManagers, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("setResolutionScale", js_cocos2dx_builder_CCBReader_setResolutionScale, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_cocosbuilder_CCBReader_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
        jsb_cocosbuilder_CCBReader_class,
        js_cocos2dx_builder_CCBReader_constructor, 0, // constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "_Reader", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<cocosbuilder::CCBReader> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_cocosbuilder_CCBReader_class;
        p->proto = jsb_cocosbuilder_CCBReader_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_builder(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "cc", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "cc", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_cocos2dx_builder_CCBAnimationManager(cx, obj);
    js_register_cocos2dx_builder_CCBReader(cx, obj);
}

