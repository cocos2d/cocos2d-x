/*
 * Created by LinWenhai on 17/11/13.
 * Copyright (c) 2013-2017 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "scripting/js-bindings/manual/ui/jsb_cocos2dx_ui_manual.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

static bool js_cocos2dx_LayoutParameter_setMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ui::LayoutParameter* cobj = (ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 1) {
        JS::RootedObject tmp(cx);
        JS::RootedValue jsleft(cx), jstop(cx),jsright(cx),jsbottom(cx);
        double left, top,right,bottom;
        bool ok = args[0].isObject() &&
            JS_ValueToObject(cx, args[0], &tmp) &&
            JS_GetProperty(cx, tmp, "left", &jsleft) &&
            JS_GetProperty(cx, tmp, "top", &jstop) &&
            JS_GetProperty(cx, tmp, "right", &jsright) &&
            JS_GetProperty(cx, tmp, "bottom", &jsbottom);
        
        left = jsleft.toNumber();
        top = jstop.toNumber();
        right = jsright.toNumber();
        bottom = jsbottom.toNumber();

        JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

        cobj->setMargin(ui::Margin(left,top,right,bottom));
        return true;
    }
    else if (argc == 4) {
        bool ok = true;
        double left, top,right,bottom;
        JS::RootedValue jsv(cx, args[0]);
        ok &= JS::ToNumber( cx, jsv, &left);
        jsv.set(args[1]);
        ok &= JS::ToNumber( cx, jsv, &top);
        jsv.set(args[2]);
        ok &= JS::ToNumber( cx, jsv, &right);
        jsv.set(args[3]);
        ok &= JS::ToNumber( cx, jsv, &bottom);

        JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");

        cobj->setMargin(ui::Margin(left,top,right,bottom));
        return true;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

static bool js_cocos2dx_LayoutParameter_getMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ui::LayoutParameter* cobj = (ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 0) {
        JS::RootedObject tmp(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        if (!tmp) return false;
        ui::Margin margin = cobj->getMargin();
        bool ok = JS_DefineProperty(cx, tmp, "left", margin.left, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "top", margin.top, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "right", margin.right, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
            JS_DefineProperty(cx, tmp, "bottom", margin.bottom, JSPROP_ENUMERATE | JSPROP_PERMANENT);
        if (ok) 
        {
            args.rval().set(OBJECT_TO_JSVAL(tmp));
        }
        else
        {
            return false;
        }
        return true;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

class JSB_EditBoxDelegate
: public Ref
, public EditBoxDelegate
{
public:
    JSB_EditBoxDelegate()
    {
        _JSDelegate = JS::NullValue();
    }
    
    virtual void editBoxEditingDidBegin(EditBox* editBox) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        JS::RootedValue delegateVal(ScriptingCore::getInstance()->getGlobalContext(), _JSDelegate);
        ScriptingCore::getInstance()->executeFunctionWithOwner(delegateVal, "editBoxEditingDidBegin", 1, &arg);
    }
    
    virtual void editBoxEditingDidEnd(EditBox* editBox) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        JS::RootedValue delegateVal(ScriptingCore::getInstance()->getGlobalContext(), _JSDelegate);
        ScriptingCore::getInstance()->executeFunctionWithOwner(delegateVal, "editBoxEditingDidEnd", 1, &arg);
    }
    
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        std::string arg1 = text;
        dataVal[1] = std_string_to_jsval(cx, arg1);
        
        JS::RootedValue delegateVal(cx, _JSDelegate);
        ScriptingCore::getInstance()->executeFunctionWithOwner(delegateVal, "editBoxTextChanged", 2, dataVal);
    }
    
    virtual void editBoxReturn(EditBox* editBox) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        JS::RootedValue delegateVal(ScriptingCore::getInstance()->getGlobalContext(), _JSDelegate);
        ScriptingCore::getInstance()->executeFunctionWithOwner(delegateVal, "editBoxReturn", 1, &arg);
    }
    
    void setJSDelegate(JS::HandleValue pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
private:
    JS::Heap<JS::Value> _JSDelegate;
};

static bool js_cocos2dx_CCEditBox_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::EditBox* cobj = (cocos2d::ui::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JSB_EditBoxDelegate* nativeDelegate = new (std::nothrow) JSB_EditBoxDelegate();
        nativeDelegate->setJSDelegate(args.get(0));
        
        JS_SetProperty(cx, obj, "_delegate", args.get(0));
        
        cobj->setUserObject(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

extern JSObject* jsb_cocos2d_ui_LayoutParameter_prototype;
extern JSObject* jsb_cocos2d_ui_EditBox_prototype;

void register_all_cocos2dx_ui_manual(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject proto(cx, jsb_cocos2d_ui_LayoutParameter_prototype);
    JS_DefineFunction(cx, proto, "setMargin", js_cocos2dx_LayoutParameter_setMargin, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, proto, "getMargin", js_cocos2dx_LayoutParameter_getMargin, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    proto.set(jsb_cocos2d_ui_EditBox_prototype);
    JS_DefineFunction(cx, proto, "setDelegate", js_cocos2dx_CCEditBox_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
