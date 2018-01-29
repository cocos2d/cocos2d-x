/*
 * Created by James Chen on 3/11/13.
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

#include "scripting/js-bindings/manual/extension/jsb_cocos2dx_extension_manual.h"
#include "extensions/cocos-ext.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/auto/jsb_cocos2dx_auto.hpp"
#include <thread>
#include <chrono>

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "network/CCDownloader.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCTextureCube.h"
#include "renderer/CCTexture2D.h"

USING_NS_CC;
USING_NS_CC_EXT;


class JSB_ScrollViewDelegate
: public Ref
, public ScrollViewDelegate
{
public:
    JSB_ScrollViewDelegate()
    {
        _JSDelegate = nullptr;
    }

    virtual void scrollViewDidScroll(ScrollView* view) override
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;

        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "scrollViewDidScroll", 1, &arg);
    }

    virtual void scrollViewDidZoom(ScrollView* view) override
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;

        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "scrollViewDidZoom", 1, &arg);
    }

    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_cocos2dx_CCScrollView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_ScrollViewDelegate* nativeDelegate = new (std::nothrow) JSB_ScrollViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);

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


#define KEY_TABLEVIEW_DATA_SOURCE  "TableViewDataSource"
#define KEY_TABLEVIEW_DELEGATE     "TableViewDelegate"

class JSB_TableViewDelegate
: public Ref
, public TableViewDelegate
{
public:
    JSB_TableViewDelegate()
    {
        _JSDelegate = nullptr;
    }

    virtual void scrollViewDidScroll(ScrollView* view) override
    {
        callJSDelegate(view, "scrollViewDidScroll");
    }

    virtual void scrollViewDidZoom(ScrollView* view) override
    {
        callJSDelegate(view, "scrollViewDidZoom");
    }

    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override
    {
        callJSDelegate(table, cell, "tableCellTouched");
    }

    virtual void tableCellHighlight(TableView* table, TableViewCell* cell) override
    {
        callJSDelegate(table, cell, "tableCellHighlight");
    }

    virtual void tableCellUnhighlight(TableView* table, TableViewCell* cell) override
    {
        callJSDelegate(table, cell, "tableCellUnhighlight");
    }

    virtual void tableCellWillRecycle(TableView* table, TableViewCell* cell) override
    {
        callJSDelegate(table, cell, "tableCellWillRecycle");
    }

    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }

private:
    void callJSDelegate(ScrollView* view, std::string jsFunctionName)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;

        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), jsFunctionName.c_str(), 1, &arg);
    }

    void callJSDelegate(TableView* table, TableViewCell* cell, std::string jsFunctionName)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return;

        js_proxy_t * pCellProxy = jsb_get_native_proxy(cell);
        if (!pCellProxy) return;

        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = OBJECT_TO_JSVAL(pCellProxy->obj);

        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), jsFunctionName.c_str(), 2, args);
    }

    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_cocos2dx_CCTableView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_TableViewDelegate* nativeDelegate = new (std::nothrow) JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);

        JS_SetProperty(cx, obj, "_delegate", args.get(0));

        auto userDict = static_cast<JSBinding::DictionaryRef*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) JSBinding::DictionaryRef();
            cobj->setUserObject(userDict);
            userDict->release();
        }

        userDict->data.insert(KEY_TABLEVIEW_DELEGATE, nativeDelegate);

        cobj->setDelegate(nativeDelegate);

        nativeDelegate->release();

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

class JSB_TableViewDataSource
: public Ref
, public TableViewDataSource
{
public:
    JSB_TableViewDataSource()
    {
        _JSTableViewDataSource = nullptr;
    }

    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) override
    {
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue ret(cx);
        bool ok = callJSDelegate(table, idx, "tableCellSizeForIndex", &ret);
        if (!ok)
        {
            ok = callJSDelegate(table, "cellSizeForTable", &ret);
        }
        if (ok)
        {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

            Size size;
            bool isSucceed = jsval_to_ccsize(cx, ret, &size);
            if (isSucceed) return size;
        }
        return Size::ZERO;

    }

    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override
    {
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue ret(cx);
        bool ok = callJSDelegate(table, idx, "tableCellAtIndex", &ret);
        if (ok)
        {
            cocos2d::extension::TableViewCell* arg0;
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx, ret.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::extension::TableViewCell*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, NULL, "Invalid Native Object");
            } while (0);
            return arg0;
        }
        return NULL;
    }

    virtual ssize_t numberOfCellsInTableView(TableView *table) override
    {
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue ret(cx);
        bool ok = callJSDelegate(table, "numberOfCellsInTableView", &ret);
        if (ok)
        {
            ssize_t count = 0;
            bool isSucceed = jsval_to_ssize(cx, ret, &count);
            if (isSucceed) return count;
        }
        return 0;
    }

    void setTableViewDataSource(JS::HandleObject pJSSource)
    {
        _JSTableViewDataSource = pJSSource;
    }

private:
    bool callJSDelegate(TableView* table, std::string jsFunctionName, JS::MutableHandleValue retVal)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return false;

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();

        bool hasAction;
        JS::RootedValue temp_retval(cx);
        jsval dataVal = OBJECT_TO_JSVAL(p->obj);

        JS::RootedObject obj(cx, _JSTableViewDataSource);

        if (JS_HasProperty(cx, obj, jsFunctionName.c_str(), &hasAction) && hasAction)
        {
            if(!JS_GetProperty(cx, obj, jsFunctionName.c_str(), &temp_retval))
            {
                return false;
            }
            if(temp_retval == JSVAL_VOID)
            {
                return false;
            }

            JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                                JS::HandleValueArray::fromMarkedLocation(1, &dataVal), retVal);
            return true;
        }
        return false;
    }

    bool callJSDelegate(TableView* table, ssize_t idx, std::string jsFunctionName, JS::MutableHandleValue retVal)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return false;

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        bool hasAction;
        JS::RootedValue temp_retval(cx);
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        dataVal[1] = ssize_to_jsval(cx,idx);

        JS::RootedObject obj(cx, _JSTableViewDataSource);

        if (JS_HasProperty(cx, obj, jsFunctionName.c_str(), &hasAction) && hasAction)
        {
            if(!JS_GetProperty(cx, obj, jsFunctionName.c_str(), &temp_retval))
            {
                return false;
            }

            if(temp_retval == JSVAL_VOID)
            {
                return false;
            }

            bool ret = JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                JS::HandleValueArray::fromMarkedLocation(2, dataVal), retVal);
            return ret == true ? true : false;
        }
        return false;
    }

private:
    JS::Heap<JSObject*> _JSTableViewDataSource;
};

static bool js_cocos2dx_CCTableView_setDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_TableViewDataSource* pNativeSource = new (std::nothrow) JSB_TableViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setTableViewDataSource(jsdata);

        JS_SetProperty(cx, obj, "_dataSource", args.get(0));

        auto userDict = static_cast<JSBinding::DictionaryRef*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) JSBinding::DictionaryRef();
            cobj->setUserObject(userDict);
            userDict->release();
        }

        userDict->data.insert(KEY_TABLEVIEW_DATA_SOURCE, pNativeSource);

        cobj->setDataSource(pNativeSource);

        pNativeSource->release();

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

static bool js_cocos2dx_CCTableView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 3 || argc == 2)
    {

        JSB_TableViewDataSource* pNativeSource = new (std::nothrow) JSB_TableViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setTableViewDataSource(jsdata);

        cocos2d::Size arg1;
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        cocos2d::extension::TableView* ret = NULL;
        ret = new (std::nothrow) TableView();
        ret->autorelease();

        ret->setDataSource(pNativeSource);

        jsval jsret;
        do {
            if (ret)
            {
                JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::extension::TableView>(cx, ret));
                jsret = OBJECT_TO_JSVAL(jsobj);

                JS_SetProperty(cx, jsobj, "_dataSource", args.get(0));
            }
            else
            {
                jsret = JSVAL_NULL;
            }
        } while (0);

        if (argc == 2)
        {
            ret->initWithViewSize(arg1);
        }
        else
        {
            cocos2d::Node* arg2;
            do
            {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
            ret->initWithViewSize(arg1, arg2);
        }
        ret->reloadData();

        JSBinding::DictionaryRef* userDict = new (std::nothrow) JSBinding::DictionaryRef();
        userDict->data.insert(KEY_TABLEVIEW_DATA_SOURCE, pNativeSource);
        ret->setUserObject(userDict);
        userDict->release();

        pNativeSource->release();

        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

static bool js_cocos2dx_CCTableView_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_dequeueCell : Invalid Native Object");
    bool ok = true;
    if (argc == 3 || argc == 2)
    {

        JSB_TableViewDataSource* pNativeSource = new (std::nothrow) JSB_TableViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setTableViewDataSource(jsdata);
        cobj->setDataSource(pNativeSource);

        JS_SetProperty(cx, obj, "_dataSource", args.get(0));

        cocos2d::Size arg1;
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);

        if (argc == 2)
        {
            cobj->initWithViewSize(arg1);
        }
        else
        {
            cocos2d::Node* arg2;
            do
            {
                JS::RootedObject tmpObj(cx, args.get(2).toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
            cobj->initWithViewSize(arg1, arg2);
        }
        cobj->reloadData();

        JSBinding::DictionaryRef* userDict = new (std::nothrow) JSBinding::DictionaryRef();
        userDict->data.insert(KEY_TABLEVIEW_DATA_SOURCE, pNativeSource);
        cobj->setUserObject(userDict);
        userDict->release();

        pNativeSource->release();

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments");
    return false;
}



class JSB_ControlButtonTarget : public Ref
{
public:
    JSB_ControlButtonTarget()
    : _callback(nullptr),
      _type(Control::EventType::TOUCH_DOWN)
    {
        _jsFunc = nullptr;
    }

    virtual ~JSB_ControlButtonTarget()
    {
        CCLOGINFO("In the destruction of JSB_ControlButtonTarget ...");

        if (_callback != nullptr)
        {
            CC_SAFE_DELETE(_callback);
        }

        for (auto iter = _jsNativeTargetMap.begin(); iter != _jsNativeTargetMap.end(); ++iter)
        {
            if (this == iter->second)
            {
                _jsNativeTargetMap.erase(iter);
                break;
            }
        }
    }

    virtual void onEvent(Ref *controlButton, Control::EventType event)
    {
        js_proxy_t* p = jsb_get_native_proxy(controlButton);
        if (!p)
        {
            log("Failed to get proxy for control button %p", controlButton);
            return;
        }

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();

        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        int arg1 = (int)event;
        dataVal[1] = INT_TO_JSVAL(arg1);
        JS::RootedValue jsRet(cx);

        _callback->invoke(2, dataVal, &jsRet);
    }

    void setJSCallback(JS::HandleValue jsFunc, JS::HandleObject jsTarget)
    {
        if (_callback != nullptr)
        {
            CC_SAFE_DELETE(_callback);
        }
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        _callback = new (std::nothrow) JSFunctionWrapper(cx, jsTarget, jsFunc);
        _jsFunc = jsFunc.toObjectOrNull();
    }

    void setEventType(Control::EventType type)
    {
        _type = type;
    }
public:

    static std::multimap<JSObject*, JSB_ControlButtonTarget*> _jsNativeTargetMap;
    JSFunctionWrapper *_callback;
    Control::EventType _type;
    JS::Heap<JSObject*> _jsFunc;
};

std::multimap<JSObject*, JSB_ControlButtonTarget*> JSB_ControlButtonTarget::_jsNativeTargetMap;

static bool js_cocos2dx_CCControl_addTargetWithActionForControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    bool ok = true;
    if (argc == 3)
    {
        JSObject* jsDelegate = args.get(0).toObjectOrNull();
        JSObject* jsFunc = args.get(1).toObjectOrNull();
        Control::EventType arg2;
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "Error processing control event");

        // Check whether the target already exists.
        auto range = JSB_ControlButtonTarget::_jsNativeTargetMap.equal_range(jsDelegate);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second->_jsFunc.get() == jsFunc && arg2 == it->second->_type)
            {
                // Return true directly.
                args.rval().setUndefined();
                return true;
            }
        }

        // save the delegate
        JSB_ControlButtonTarget* nativeDelegate = new (std::nothrow) JSB_ControlButtonTarget();

        JS::RootedObject jscb(cx, jsDelegate);
        nativeDelegate->setJSCallback(args.get(1), jscb);
        nativeDelegate->setEventType(arg2);

        auto nativeDelegateArray = static_cast<JSBinding::ArrayRef*>(cobj->getUserObject());
        if (nullptr == nativeDelegateArray)
        {
            nativeDelegateArray = new (std::nothrow) JSBinding::ArrayRef();
            cobj->setUserObject(nativeDelegateArray);  // The reference of nativeDelegateArray is added to 2
            nativeDelegateArray->release(); // Release nativeDelegateArray to make the reference to 1
        }

        nativeDelegateArray->data.pushBack(nativeDelegate); // The reference of nativeDelegate is added to 2
        nativeDelegate->release(); // Release nativeDelegate to make the reference to 1

        js_add_object_reference(args.thisv(), args.get(1));

        cobj->addTargetWithActionForControlEvents(nativeDelegate, cccontrol_selector(JSB_ControlButtonTarget::onEvent), arg2);

        JSB_ControlButtonTarget::_jsNativeTargetMap.insert(std::make_pair(jsDelegate, nativeDelegate));

        args.rval().setUndefined();

        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

static bool js_cocos2dx_CCControl_removeTargetWithActionForControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    bool ok = true;
    if (argc == 3)
    {
        Control::EventType arg2;
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "Error processing control event");

        obj = args.get(0).toObjectOrNull();
        JSObject* jsFunc = args.get(1).toObjectOrNull();

        JSB_ControlButtonTarget* nativeTargetToRemoved = nullptr;

        auto range = JSB_ControlButtonTarget::_jsNativeTargetMap.equal_range(obj);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second->_jsFunc.get() == jsFunc && arg2 == it->second->_type)
            {
                nativeTargetToRemoved = it->second;
                JSB_ControlButtonTarget::_jsNativeTargetMap.erase(it);
                break;
            }
        }

        js_remove_object_reference(args.thisv(), args.get(1));

        cobj->removeTargetWithActionForControlEvents(nativeTargetToRemoved, cccontrol_selector(JSB_ControlButtonTarget::onEvent), arg2);

        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

bool js_cocos2dx_extension_EventListenerAssetsManagerEx_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EventListenerAssetsManagerEx* cobj = (cocos2d::extension::EventListenerAssetsManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_EventListenerAssetsManagerEx_init : Invalid Native Object");
    if (argc == 2) {
        const cocos2d::extension::AssetsManagerEx* arg0 = nullptr;
        std::function<void (cocos2d::extension::EventAssetsManagerEx *)> arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (const cocos2d::extension::AssetsManagerEx*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1), args.thisv()));
                auto lambda = [=](cocos2d::extension::EventAssetsManagerEx* larg0) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[1];
                    do {
                        if (larg0) {
                            js_type_class_t* typeClass = js_get_type_from_native<cocos2d::extension::EventAssetsManagerEx>(larg0);
                            largv[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, larg0, typeClass, "cocos2d::extension::EventAssetsManagerEx"));
                        } else {
                            largv[0] = JSVAL_NULL;
                        }
                    } while (0);
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(1, &largv[0], &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_EventListenerAssetsManagerEx_init : Error processing arguments");
        bool ret = cobj->init(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_extension_EventListenerAssetsManagerEx_init : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_cocos2dx_extension_EventListenerAssetsManagerEx_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::extension::AssetsManagerEx* arg0 = nullptr;
        std::function<void (cocos2d::extension::EventAssetsManagerEx *)> arg1;
        JSFunctionWrapper *wrapper = nullptr;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::extension::AssetsManagerEx*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        do {
            if(JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
            {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(1)));
                wrapper = func.get();
                auto lambda = [=](cocos2d::extension::EventAssetsManagerEx* larg0) -> void {
                    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                    jsval largv[1];
                    do {
                        if (larg0) {
                            js_type_class_t* typeClass = js_get_type_from_native<cocos2d::extension::EventAssetsManagerEx>(larg0);
                            largv[0] = OBJECT_TO_JSVAL(jsb_get_or_create_weak_jsobject(cx, larg0, typeClass, "cocos2d::extension::EventAssetsManagerEx"));
                        } else {
                            largv[0] = JSVAL_NULL;
                        }
                    } while (0);
                    JS::RootedValue rval(cx);
                    bool succeed = func->invoke(1, &largv[0], &rval);
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
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_EventListenerAssetsManagerEx_create : Error processing arguments");
        cocos2d::extension::EventListenerAssetsManagerEx* ret = cocos2d::extension::EventListenerAssetsManagerEx::create(arg0, arg1);
        JS::RootedValue jsret(cx);
        if (ret) {
            JS::RootedObject jsobj(cx, js_get_or_create_jsobject<cocos2d::extension::EventListenerAssetsManagerEx>(cx, ret));
            jsret = OBJECT_TO_JSVAL(jsobj);
        } else {
            jsret = JS::NullValue();
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_extension_EventListenerAssetsManagerEx_create : wrong number of arguments");
    return false;
}

class JSDownloaderDelegator : cocos2d::Ref
{
public:
    void download();

    static JSDownloaderDelegator *create(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleValue callback);

protected:
    JSDownloaderDelegator(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleValue callback);
    ~JSDownloaderDelegator();

    void startDownload();

private:
    void onSuccess(cocos2d::Texture2D *tex);
    void onError();
    std::shared_ptr<cocos2d::network::Downloader> _downloader;
    std::string _url;
    JSContext *_cx;
    JS::PersistentRootedValue* _jsCallback;
    JS::PersistentRootedObject* _obj;
};

JSDownloaderDelegator::JSDownloaderDelegator(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleValue callback)
: _cx(cx)
, _url(url)
{
    _obj = new (std::nothrow) JS::PersistentRootedObject(cx, obj);
    _jsCallback = new (std::nothrow) JS::PersistentRootedValue(cx, callback);
}

JSDownloaderDelegator::~JSDownloaderDelegator()
{
    CC_SAFE_DELETE(_obj);
    CC_SAFE_DELETE(_jsCallback);

    _downloader->onTaskError = nullptr;
    _downloader->onDataTaskSuccess = nullptr;
}

JSDownloaderDelegator *JSDownloaderDelegator::create(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleValue callback)
{
    JSDownloaderDelegator *delegate = new (std::nothrow) JSDownloaderDelegator(cx, obj, url, callback);
    delegate->autorelease();
    return delegate;
}

void JSDownloaderDelegator::startDownload()
{
    if (auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(_url))
    {
        onSuccess(texture);
    }
    else
    {
        _downloader = std::make_shared<cocos2d::network::Downloader>();
//        _downloader->setConnectionTimeout(8);
        _downloader->onTaskError = [this](const cocos2d::network::DownloadTask& task,
                                          int errorCode,
                                          int errorCodeInternal,
                                          const std::string& errorStr)
        {
            this->onError();
        };

        _downloader->onDataTaskSuccess = [this](const cocos2d::network::DownloadTask& task,
                                                std::vector<unsigned char>& data)
        {
            Image* img = new (std::nothrow) Image();
            Texture2D *tex = nullptr;
            do
            {
                if (false == img->initWithImageData(data.data(), data.size()))
                {
                    break;
                }
                tex = Director::getInstance()->getTextureCache()->addImage(img, _url);
            } while (0);

            CC_SAFE_RELEASE(img);

            if (tex)
            {
                this->onSuccess(tex);
            }
            else
            {
                this->onError();
            }
        };

        _downloader->createDownloadDataTask(_url);
    }
}

void JSDownloaderDelegator::download()
{
    retain();
    startDownload();
}

void JSDownloaderDelegator::onError()
{
    JS::RootedValue callback(_cx, *_jsCallback);
    if (!callback.isNull()) {
        JS::RootedObject global(_cx, ScriptingCore::getInstance()->getGlobalObject());

        jsval succeed = BOOLEAN_TO_JSVAL(false);
        JS::RootedValue retval(_cx);
        JS_CallFunctionValue(_cx, global, callback, JS::HandleValueArray::fromMarkedLocation(1, &succeed), &retval);
    }
    release();
}

void JSDownloaderDelegator::onSuccess(Texture2D *tex)
{
    CCASSERT(tex, "JSDownloaderDelegator::onSuccess must make sure tex not null!");
    JS::RootedObject global(_cx, ScriptingCore::getInstance()->getGlobalObject());

    jsval valArr[2];
    if (tex)
    {
        valArr[0] = BOOLEAN_TO_JSVAL(true);
        JS::RootedObject jsobj(_cx, js_get_or_create_jsobject<Texture2D>(_cx, tex));
        valArr[1] = OBJECT_TO_JSVAL(jsobj);
    }
    else
    {
        valArr[0] = BOOLEAN_TO_JSVAL(false);
        valArr[1] = JSVAL_NULL;
    }

    JS::RootedValue callback(_cx, *_jsCallback);
    if (!callback.isNull())
    {
        JS::RootedValue retval(_cx);
        JS_CallFunctionValue(_cx, global, callback, JS::HandleValueArray::fromMarkedLocation(2, valArr), &retval);
    }
    release();
}

// jsb.loadRemoteImg(url, function(succeed, result) {})
bool js_load_remote_image(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 2)
    {
        std::string url;
        bool ok = jsval_to_std_string(cx, args.get(0), &url);
        JSB_PRECONDITION2(ok, cx, false, "js_load_remote_image : Error processing arguments");
        JSDownloaderDelegator *delegate = JSDownloaderDelegator::create(cx, obj, url, args[1]);
        delegate->download();

        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_load_remote_image : wrong number of arguments");
    return false;
}

using namespace std::chrono;

bool js_performance_now(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	auto now = steady_clock::now();
	auto micro = duration_cast<microseconds>(now - ScriptingCore::getInstance()->getEngineStartTime()).count();
	args.rval().set(DOUBLE_TO_JSVAL((double)micro * 0.001));
	return true;
}

extern JSObject* jsb_cocos2d_extension_ScrollView_prototype;
extern JSObject* jsb_cocos2d_extension_TableView_prototype;
extern JSObject* jsb_cocos2d_extension_Control_prototype;
extern JSObject* jsb_cocos2d_extension_AssetsManagerEx_prototype;
extern JSObject* jsb_cocos2d_extension_EventListenerAssetsManagerEx_prototype;
extern JSObject* jsb_cocos2d_extension_Manifest_prototype;

void register_all_cocos2dx_extension_manual(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    JS::RootedObject jsbObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "cc", &ccObj);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);

    tmpObj.set(jsb_cocos2d_extension_AssetsManagerEx_prototype);
    JS_DefineFunction(cx, tmpObj, "retain", js_cocos2dx_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "release", js_cocos2dx_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_cocos2d_extension_Manifest_prototype);
    JS_DefineFunction(cx, tmpObj, "retain", js_cocos2dx_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "release", js_cocos2dx_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "EventListenerAssetsManager", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_extension_EventListenerAssetsManagerEx_create, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    tmpObj.set(jsb_cocos2d_extension_EventListenerAssetsManagerEx_prototype);
    JS_DefineFunction(cx, tmpObj, "init", js_cocos2dx_extension_EventListenerAssetsManagerEx_init, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    tmpObj.set(jsb_cocos2d_extension_ScrollView_prototype);
    JS_DefineFunction(cx, tmpObj, "setDelegate", js_cocos2dx_CCScrollView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS::RootedObject tableview(cx, jsb_cocos2d_extension_TableView_prototype);
    JS_DefineFunction(cx, tableview, "setDelegate", js_cocos2dx_CCTableView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tableview, "setDataSource", js_cocos2dx_CCTableView_setDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tableview, "_init", js_cocos2dx_CCTableView_init, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS::RootedObject control(cx, jsb_cocos2d_extension_Control_prototype);
    JS_DefineFunction(cx, control, "addTargetWithActionForControlEvents", js_cocos2dx_CCControl_addTargetWithActionForControlEvents, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, control, "removeTargetWithActionForControlEvents", js_cocos2dx_CCControl_removeTargetWithActionForControlEvents, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_GetProperty(cx, ccObj, "TableView", &tmpVal);
    tmpObj.set(tmpVal.toObjectOrNull());
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCTableView_create, 3, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsbObj, "loadRemoteImg", js_load_remote_image, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS::RootedObject performance(cx);
    get_or_create_js_obj(cx, global, "performance", &performance);
    JS_DefineFunction(cx, performance, "now", js_performance_now, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
