//
//  jsb_cocos2dx_gui_manual.h
//
//  Created by LinWenhai on 17/11/13.
//
//
#include "jsb_cocos2dx_gui_manual.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "gui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::gui;

class JSStudioEventListenerWrapper: public JSCallbackWrapper {
public:
    JSStudioEventListenerWrapper();
    virtual ~JSStudioEventListenerWrapper();

    virtual void setJSCallbackThis(jsval thisObj);

    virtual void eventCallbackFunc(Object*,int);

private:
    bool m_bNeedUnroot;
};

JSStudioEventListenerWrapper::JSStudioEventListenerWrapper()
    : m_bNeedUnroot(false)
{

}

JSStudioEventListenerWrapper::~JSStudioEventListenerWrapper()
{
    if (m_bNeedUnroot)
    {
        JSObject *thisObj = JSVAL_TO_OBJECT(_jsThisObj);
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_RemoveObjectRoot(cx, &thisObj);
    }
}

void JSStudioEventListenerWrapper::setJSCallbackThis(jsval jsThisObj)
{
    JSCallbackWrapper::setJSCallbackThis(jsThisObj);

    JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
    js_proxy *p = jsb_get_js_proxy(thisObj);
    if (!p)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_AddObjectRoot(cx, &thisObj);
        m_bNeedUnroot = true;
    }
}

void JSStudioEventListenerWrapper::eventCallbackFunc(Object* sender,int eventType)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
    js_proxy_t *proxy = js_get_or_create_proxy(cx, sender);
    jsval retval;
    if (_jsCallback != JSVAL_VOID)
    {
        jsval touchVal = INT_TO_JSVAL(eventType);

        jsval valArr[2];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = touchVal;

        JS_AddValueRoot(cx, valArr);

        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
}

static JSBool js_cocos2dx_UIWidget_addTouchEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::Widget* cobj = (gui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);
        
        cobj->addTouchEventListener(tmpObj, toucheventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_UICheckBox_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::CheckBox* cobj = (gui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerCheckBox(tmpObj, checkboxselectedeventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_UISlider_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::Slider* cobj = (gui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerSlider(tmpObj, sliderpercentchangedselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_UITextField_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::TextField* cobj = (gui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerTextField(tmpObj, textfieldeventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_UIPageView_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::PageView* cobj = (gui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerPageView(tmpObj, pagevieweventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_UIListView_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::ListView* cobj = (gui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerListView(tmpObj, listvieweventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_LayoutParameter_setMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::LayoutParameter* cobj = (gui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 1) {
        jsval *argv = JS_ARGV(cx, vp);

        JSObject *tmp;
        JS::RootedValue jsleft(cx), jstop(cx),jsright(cx),jsbottom(cx);
        double left, top,right,bottom;
        JSBool ok = argv[0].isObject() &&
            JS_ValueToObject(cx, argv[0], &tmp) &&
            JS_GetProperty(cx, tmp, "left", &jsleft) &&
            JS_GetProperty(cx, tmp, "top", &jstop) &&
            JS_GetProperty(cx, tmp, "right", &jsright) &&
            JS_GetProperty(cx, tmp, "bottom", &jsbottom) &&
            JS_ValueToNumber(cx, jsleft, &left) &&
            JS_ValueToNumber(cx, jstop, &top) &&
            JS_ValueToNumber(cx, jsright, &right) &&
            JS_ValueToNumber(cx, jsbottom, &bottom);

        JSB_PRECONDITION3(ok, cx, JS_FALSE, "Error processing arguments");

        cobj->setMargin(gui::Margin(left,top,right,bottom));
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_LayoutParameter_getMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    gui::LayoutParameter* cobj = (gui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 0) {
        JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
        if (!tmp) return JS_FALSE;
        gui::Margin margin = cobj->getMargin();
        JSBool ok = JS_DefineProperty(cx, tmp, "left", DOUBLE_TO_JSVAL(margin.left), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "top", DOUBLE_TO_JSVAL(margin.top), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "right", DOUBLE_TO_JSVAL(margin.right), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "bottom", DOUBLE_TO_JSVAL(margin.bottom), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
        if (ok) 
        {
            JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));
        }
        else
        {
            return JS_FALSE;
        }
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

extern JSObject* jsb_cocos2d_gui_Widget_prototype;
extern JSObject* jsb_cocos2d_gui_CheckBox_prototype;
extern JSObject* jsb_cocos2d_gui_Slider_prototype;
extern JSObject* jsb_cocos2d_gui_TextField_prototype;
extern JSObject* jsb_cocos2d_gui_LayoutParameter_prototype;
extern JSObject* jsb_cocos2d_gui_PageView_prototype;
extern JSObject* jsb_cocos2d_gui_ListView_prototype;

void register_all_cocos2dx_gui_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_cocos2d_gui_Widget_prototype, "addTouchEventListener", js_cocos2dx_UIWidget_addTouchEventListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_CheckBox_prototype, "addEventListenerCheckBox", js_cocos2dx_UICheckBox_addEventListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_Slider_prototype, "addEventListenerSlider", js_cocos2dx_UISlider_addEventListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_TextField_prototype, "addEventListenerTextField", js_cocos2dx_UITextField_addEventListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_PageView_prototype, "addEventListenerPageView", js_cocos2dx_UIPageView_addEventListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_ListView_prototype, "addEventListenerListView", js_cocos2dx_UIListView_addEventListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_LayoutParameter_prototype, "setMargin", js_cocos2dx_LayoutParameter_setMargin, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocos2d_gui_LayoutParameter_prototype, "getMargin", js_cocos2dx_LayoutParameter_getMargin, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}