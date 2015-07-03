/*
 * Created by James Chen on 3/11/13.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
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

#include "jsb_cocos2dx_extension_manual.h"
#include "extensions/cocos-ext.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "jsb_cocos2dx_auto.hpp"
#include <thread>

USING_NS_CC;
USING_NS_CC_EXT;


class JSB_ScrollViewDelegate
: public Ref
, public ScrollViewDelegate
{
public:
    JSB_ScrollViewDelegate()
    : _JSDelegate(NULL)
    , _needUnroot(false)
    {}
    
    virtual ~JSB_ScrollViewDelegate()
    {
        if (_needUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RemoveObjectRoot(cx, &_JSDelegate);
        }
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
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(_JSDelegate);
        if (!p)
        {
            _needUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::AddNamedObjectRoot(cx, &_JSDelegate, "TableViewDelegate");
        }
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
    bool _needUnroot;
};

static bool js_cocos2dx_CCScrollView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        JSB_ScrollViewDelegate* nativeDelegate = new JSB_ScrollViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
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
    : _JSDelegate(NULL)
    , _needUnroot(false)
    {}
    
    virtual ~JSB_TableViewDelegate()
    {
        if (_needUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RemoveObjectRoot(cx, &_JSDelegate);
        }
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
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(_JSDelegate);
        if (!p)
        {
            _needUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::AddNamedObjectRoot(cx, &_JSDelegate, "TableViewDelegate");
        }
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
    bool _needUnroot;
};

static bool js_cocos2dx_CCTableView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JSObject *jsDelegate = args.get(0).toObjectOrNull();
        JSB_TableViewDelegate* nativeDelegate = new JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        __Dictionary* userDict = static_cast<__Dictionary*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new __Dictionary();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->setObject(nativeDelegate, KEY_TABLEVIEW_DELEGATE);
        
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
    : _JSTableViewDataSource(NULL)
    , _needUnroot(false)
    {}
    
    virtual ~JSB_TableViewDataSource()
    {
        if (_needUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::RemoveObjectRoot(cx, &_JSTableViewDataSource);
        }
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
                JSObject *tmpObj = ret.toObjectOrNull();
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
    
    
    void setTableViewDataSource(JSObject* pJSSource)
    {
        _JSTableViewDataSource = pJSSource;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(_JSTableViewDataSource);
        if (!p)
        {
            _needUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::AddNamedObjectRoot(cx, &_JSTableViewDataSource, "TableViewDataSource");
        }
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
        JSAutoCompartment ac(cx, obj);
        
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
        JSAutoCompartment ac(cx, obj);
        
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
    bool _needUnroot;
};

static bool js_cocos2dx_CCTableView_setDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(args.get(0).toObjectOrNull());
    
        __Dictionary* userDict = static_cast<__Dictionary*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new __Dictionary();
            cobj->setUserObject(userDict);
            userDict->release();
        }

        userDict->setObject(pNativeSource, KEY_TABLEVIEW_DATA_SOURCE);

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
        
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(args.get(0).toObjectOrNull());
        
        cocos2d::Size arg1;
        ok &= jsval_to_ccsize(cx, args.get(1), &arg1);
        cocos2d::extension::TableView* ret = NULL;
        ret = new TableView();
        ret->autorelease();
        
        ret->setDataSource(pNativeSource);
        
        jsval jsret;
        do {
            if (ret)
            {
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::TableView>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
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
                JSObject *tmpObj = args.get(2).toObjectOrNull();
                proxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
            ret->initWithViewSize(arg1, arg2);
        }
        ret->reloadData();
        
        __Dictionary* userDict = new __Dictionary();
        userDict->setObject(pNativeSource, KEY_TABLEVIEW_DATA_SOURCE);
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
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_TableView_dequeueCell : Invalid Native Object");
    bool ok = true;
    if (argc == 3 || argc == 2)
    {
        
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(args.get(0).toObjectOrNull());
        cobj->setDataSource(pNativeSource);

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
                js_proxy_t *proxy;
                JSObject *tmpObj = args.get(2).toObjectOrNull();
                proxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
            cobj->initWithViewSize(arg1, arg2);
        }
        cobj->reloadData();
        
        __Dictionary* userDict = new __Dictionary();
        userDict->setObject(pNativeSource, KEY_TABLEVIEW_DATA_SOURCE);
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
    : _jsFunc(nullptr),
      _type(Control::EventType::TOUCH_DOWN),
      _jsTarget(nullptr),
      _needUnroot(false)
    {}
    
    virtual ~JSB_ControlButtonTarget()
    {
        CCLOGINFO("In the destruction of JSB_ControlButtonTarget ...");
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        if (_needUnroot)
        {
            JS::RemoveObjectRoot(cx, &_jsTarget);
        }
        
        JS::RemoveObjectRoot(cx, &_jsFunc);

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
        js_proxy_t * p;
        JS_GET_PROXY(p, controlButton);
        if (!p)
        {
            log("Failed to get proxy for control button");
            return;
        }
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        int arg1 = (int)event;
        dataVal[1] = INT_TO_JSVAL(arg1);

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue jsRet(cx);

        ScriptingCore::getInstance()->executeJSFunctionWithThisObj(JS::RootedValue(cx, OBJECT_TO_JSVAL(_jsTarget)), JS::RootedValue(cx, OBJECT_TO_JSVAL(_jsFunc)), JS::HandleValueArray::fromMarkedLocation(2, dataVal), &jsRet);
    }
    
    void setJSTarget(JSObject* pJSTarget)
    {
        _jsTarget = pJSTarget;
        
        js_proxy_t* p = jsb_get_js_proxy(_jsTarget);
        if (!p)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS::AddNamedObjectRoot(cx, &_jsTarget, "JSB_ControlButtonTarget, target");
            _needUnroot = true;
        }
    }
    
    void setJSAction(JSObject* jsFunc)
    {
        _jsFunc = jsFunc;

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::AddNamedObjectRoot(cx, &_jsFunc, "JSB_ControlButtonTarget, func");
    }
    
    void setEventType(Control::EventType type)
    {
        _type = type;
    }
public:
    
    static std::multimap<JSObject*, JSB_ControlButtonTarget*> _jsNativeTargetMap;
    JS::Heap<JSObject*> _jsFunc;
    Control::EventType _type;
private:
    JS::Heap<JSObject*> _jsTarget;
    bool _needUnroot;
};

std::multimap<JSObject*, JSB_ControlButtonTarget*> JSB_ControlButtonTarget::_jsNativeTargetMap;

static bool js_cocos2dx_CCControl_addTargetWithActionForControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
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
            if (it->second->_jsFunc == jsFunc && arg2 == it->second->_type)
            {
                // Return true directly.
                args.rval().setUndefined();
                return true;
            }
        }
        
        // save the delegate
        JSB_ControlButtonTarget* nativeDelegate = new JSB_ControlButtonTarget();
        
        nativeDelegate->setJSTarget(jsDelegate);
        nativeDelegate->setJSAction(jsFunc);
        nativeDelegate->setEventType(arg2);

        __Array* nativeDelegateArray = static_cast<__Array*>(cobj->getUserObject());
        if (nullptr == nativeDelegateArray)
        {
            nativeDelegateArray = new __Array();
            nativeDelegateArray->init();
            cobj->setUserObject(nativeDelegateArray);  // The reference of nativeDelegateArray is added to 2
            nativeDelegateArray->release(); // Release nativeDelegateArray to make the reference to 1
        }
        
        nativeDelegateArray->addObject(nativeDelegate); // The reference of nativeDelegate is added to 2
        nativeDelegate->release(); // Release nativeDelegate to make the reference to 1
        
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
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
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
            if (it->second->_jsFunc == jsFunc && arg2 == it->second->_type)
            {
                nativeTargetToRemoved = it->second;
                JSB_ControlButtonTarget::_jsNativeTargetMap.erase(it);
                break;
            }
        }
        
        cobj->removeTargetWithActionForControlEvents(nativeTargetToRemoved, cccontrol_selector(JSB_ControlButtonTarget::onEvent), arg2);

        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

/*
static bool js_cocos2dx_ext_AssetsManager_updateAssets(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManager* cobj = (cocos2d::extension::AssetsManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManager_updateAssets : Invalid Native Object");
    if (argc == 1) {
        std::unordered_map<std::string, Downloader::DownloadUnit> dict;
        do {
            if (!argv[0].isObject()) { ok = false; break; }
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
            
            if (!tmpObj) {
                CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
                return false;
            }
            
            JSObject* it = JS_NewPropertyIterator(cx, tmpObj);
            while (true)
            {
                jsid idp;
                jsval key;
                if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
                    return false; // error
                }
                
                if (key == JSVAL_VOID) {
                    break; // end of iteration
                }
                
                if (!JSVAL_IS_STRING(key)) {
                    continue; // ignore integer properties
                }
                
                JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);
                std::string keystr = keyWrapper.get();
                
                JS::RootedValue value(cx);
                JS_GetPropertyById(cx, tmpObj, idp, &value);
                
                JS::RootedObject tmp(cx);
                JS::RootedValue jsSrcUrl(cx);
                JS::RootedValue jsStoragePath(cx);
                JS::RootedValue jsCustomId(cx);
                ok = value.isObject() &&
                JS_ValueToObject(cx, JS::RootedValue(cx, value), &tmp) &&
                JS_GetProperty(cx, tmp, "srcUrl", &jsSrcUrl) &&
                JS_GetProperty(cx, tmp, "storagePath", &jsStoragePath) &&
                JS_GetProperty(cx, tmp, "customId", &jsCustomId);
                JSB_PRECONDITION3(ok, cx, false, "Error parsing map entry");
                
                Downloader::DownloadUnit unit;
                
                JSString *jsstr = JS::ToString(cx, jsSrcUrl);
                JSB_PRECONDITION3(jsstr, cx, false, "Error processing srcUrl value of entry: %s", keystr);
                JSStringWrapper srcUrlStr(jsstr);
                unit.srcUrl = srcUrlStr.get();
                
                jsstr = JS::ToString(cx, jsStoragePath);
                JSB_PRECONDITION3(jsstr, cx, false, "Error processing storagePath value of entry: %s", keystr);
                JSStringWrapper storagePathStr(jsstr);
                unit.storagePath = storagePathStr.get();
                
                jsstr = JS::ToString(cx, jsCustomId);
                JSB_PRECONDITION3(jsstr, cx, false, "Error processing customId value of entry: %s", keystr);
                JSStringWrapper customIdStr(jsstr);
                unit.customId = customIdStr.get();
                
                dict[keystr] = unit;
            }
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManager_updateAssets : Error processing arguments");
        cobj->updateAssets(dict);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManager_updateAssets : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_cocos2dx_ext_AssetsManager_getFailedAssets(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::AssetsManager* cobj = (cocos2d::extension::AssetsManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_extension_AssetsManager_getFailedAssets : Invalid Native Object");
    if (argc == 0) {
        const std::unordered_map<std::string, Downloader::DownloadUnit> &ret = cobj->getFailedAssets();
        jsval jsret = JSVAL_NULL;
        do {
            JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
            
            for (auto it = ret.cbegin(); it != ret.cend(); ++it) {
                std::string key = it->first;
                const Downloader::DownloadUnit& unit = it->second;
                
                JSObject *elem = JS_NewObject(cx, NULL, NULL, NULL);
                if (!elem)
                {
                    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManager_getFailedAssets : can not create js object");
                    break;
                }
                bool ok = JS_DefineProperty(cx, elem, "srcUrl", std_string_to_jsval(cx, unit.srcUrl), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, elem, "storagePath", std_string_to_jsval(cx, unit.storagePath), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, elem, "customId", std_string_to_jsval(cx, unit.customId), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
                JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_extension_AssetsManager_getFailedAssets : Error processing DownloadUnit struct");
                
                if (!key.empty())
                {
                    JS::RootedValue dictElement(cx);
                    dictElement = OBJECT_TO_JSVAL(elem);
                    JS_SetProperty(cx, jsRet, key.c_str(), dictElement);
                }
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_cocos2dx_extension_AssetsManager_getFailedAssets : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
*/

__JSDownloaderDelegator::__JSDownloaderDelegator(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleObject callback)
: _cx(cx)
, _url(url)
, _buffer(nullptr)
{
    _obj.construct(_cx);
    _obj.ref().set(obj);
    _jsCallback.construct(_cx);
    _jsCallback.ref().set(callback);
}

__JSDownloaderDelegator::~__JSDownloaderDelegator()
{
    _obj.destroyIfConstructed();
    _jsCallback.destroyIfConstructed();
    if (_buffer != nullptr)
        free(_buffer);
    _downloader->setErrorCallback(nullptr);
    _downloader->setSuccessCallback(nullptr);
}

__JSDownloaderDelegator *__JSDownloaderDelegator::create(JSContext *cx, JS::HandleObject obj, const std::string &url, JS::HandleObject callback)
{
    __JSDownloaderDelegator *delegate = new (std::nothrow) __JSDownloaderDelegator(cx, obj, url, callback);
    delegate->autorelease();
    return delegate;
}

void __JSDownloaderDelegator::startDownload()
{
    if (Director::getInstance()->getTextureCache()->getTextureForKey(_url))
    {
        onSuccess(nullptr, nullptr, nullptr);
    }
    else
    {
        _downloader = std::make_shared<cocos2d::extension::Downloader>();
        _downloader->setConnectionTimeout(8);
        _downloader->setErrorCallback( std::bind(&__JSDownloaderDelegator::onError, this, std::placeholders::_1) );
        _downloader->setSuccessCallback( std::bind(&__JSDownloaderDelegator::onSuccess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3) );
        
        cocos2d::extension::Downloader::HeaderInfo info = _downloader->getHeader(_url);
        long contentSize = info.contentSize;
        if (contentSize > 0 && info.responseCode < 400) {
            _size = contentSize / sizeof(unsigned char);
            _buffer = (unsigned char*)malloc(contentSize);
            _downloader->downloadToBufferSync(_url, _buffer, _size);
        }
    }
}

void __JSDownloaderDelegator::download()
{
    retain();
    startDownload();
}

void __JSDownloaderDelegator::downloadAsync()
{
    retain();
    auto t = std::thread(&__JSDownloaderDelegator::startDownload, this);
    t.detach();
}

void __JSDownloaderDelegator::onError(const cocos2d::extension::Downloader::Error &error)
{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([this]
    {
        JS::RootedValue callback(_cx, OBJECT_TO_JSVAL(_jsCallback.ref()));
        if (!callback.isNull()) {
            JS::RootedObject global(_cx, ScriptingCore::getInstance()->getGlobalObject());
            JSAutoCompartment ac(_cx, global);
            
            jsval succeed = BOOLEAN_TO_JSVAL(false);
            JS::RootedValue retval(_cx);
            JS_CallFunctionValue(_cx, global, callback, JS::HandleValueArray::fromMarkedLocation(1, &succeed), &retval);
        }
        release();
    });
}

void __JSDownloaderDelegator::onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId)
{
    Image *image = new Image();
    cocos2d::TextureCache *cache = Director::getInstance()->getTextureCache();
    
    Texture2D *tex = cache->getTextureForKey(_url);
    if (!tex)
    {
        if (image->initWithImageData(_buffer, _size))
        {
            tex = Director::getInstance()->getTextureCache()->addImage(image, _url);
        }
    }
    image->release();
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([this, tex]
    {
        JS::RootedObject global(_cx, ScriptingCore::getInstance()->getGlobalObject());
        JSAutoCompartment ac(_cx, global);
        
        jsval valArr[2];
        if (tex)
        {
            valArr[0] = BOOLEAN_TO_JSVAL(true);
            js_proxy_t* p = jsb_get_native_proxy(tex);
            if (!p)
            {
                JS::RootedObject texProto(_cx, jsb_cocos2d_Texture2D_prototype);
                JSObject *obj = JS_NewObject(_cx, jsb_cocos2d_Texture2D_class, texProto, global);
                // link the native object with the javascript object
                p = jsb_new_proxy(tex, obj);
                JS::AddNamedObjectRoot(_cx, &p->obj, "cocos2d::Texture2D");
            }
            valArr[1] = OBJECT_TO_JSVAL(p->obj);
        }
        else
        {
            valArr[0] = BOOLEAN_TO_JSVAL(false);
            valArr[1] = JSVAL_NULL;
        }
    
        JS::RootedValue callback(_cx, OBJECT_TO_JSVAL(_jsCallback.ref()));
        if (!callback.isNull())
        {
            JS::RootedValue retval(_cx);
            JS_CallFunctionValue(_cx, global, callback, JS::HandleValueArray::fromMarkedLocation(2, valArr), &retval);
        }
        release();
    });
}

// jsb.loadRemoteImg(url, function(succeed, result) {})
bool js_load_remote_image(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, JS_THIS_OBJECT(cx, vp));
    if (argc == 2)
    {
        std::string url;
        bool ok = jsval_to_std_string(cx, args.get(0), &url);
        JSB_PRECONDITION2(ok, cx, false, "js_load_remote_image : Error processing arguments");
        JS::RootedObject callback(cx, args.get(1).toObjectOrNull());
        
        __JSDownloaderDelegator *delegate = __JSDownloaderDelegator::create(cx, obj, url, callback);
        delegate->downloadAsync();
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_load_remote_image : wrong number of arguments");
    return false;
}

extern JSObject* jsb_cocos2d_extension_ScrollView_prototype;
extern JSObject* jsb_cocos2d_extension_TableView_prototype;
extern JSObject* jsb_cocos2d_extension_Control_prototype;
extern JSObject* jsb_cocos2d_extension_AssetsManagerEx_prototype;
extern JSObject* jsb_cocos2d_extension_Manifest_prototype;

void register_all_cocos2dx_extension_manual(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "cc", &ccObj);
    
    JS::RootedObject am(cx, jsb_cocos2d_extension_AssetsManagerEx_prototype); 
    JS_DefineFunction(cx, am, "retain", js_cocos2dx_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, am, "release", js_cocos2dx_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS::RootedObject manifest(cx, jsb_cocos2d_extension_Manifest_prototype); 
    JS_DefineFunction(cx, manifest, "retain", js_cocos2dx_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, manifest, "release", js_cocos2dx_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    //JS_DefineFunction(cx, jsb_cocos2d_extension_AssetsManager_prototype, "updateAssets", js_cocos2dx_ext_AssetsManager_updateAssets, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    //JS_DefineFunction(cx, jsb_cocos2d_extension_AssetsManager_prototype, "getFailedAssets", js_cocos2dx_ext_AssetsManager_getFailedAssets, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocos2d_extension_ScrollView_prototype), "setDelegate", js_cocos2dx_CCScrollView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS::RootedObject tableview(cx, jsb_cocos2d_extension_TableView_prototype);
    JS_DefineFunction(cx, tableview, "setDelegate", js_cocos2dx_CCTableView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tableview, "setDataSource", js_cocos2dx_CCTableView_setDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tableview, "_init", js_cocos2dx_CCTableView_init, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS::RootedObject control(cx, jsb_cocos2d_extension_Control_prototype);
    JS_DefineFunction(cx, control, "addTargetWithActionForControlEvents", js_cocos2dx_CCControl_addTargetWithActionForControlEvents, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, control, "removeTargetWithActionForControlEvents", js_cocos2dx_CCControl_removeTargetWithActionForControlEvents, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_GetProperty(cx, ccObj, "TableView", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCTableView_create, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS::RootedObject jsbObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    
    JS_DefineFunction(cx, jsbObj, "loadRemoteImg", js_load_remote_image, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}