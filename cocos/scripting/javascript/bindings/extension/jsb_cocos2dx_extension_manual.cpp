//
//  jsb_cocos2d_extension_manual.cpp
//
//  Created by James Chen on 3/11/13.
//
//

#include "jsb_cocos2dx_extension_manual.h"
#include "extensions/cocos-ext.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

USING_NS_CC;
USING_NS_CC_EXT;


class JSB_ScrollViewDelegate
: public Object
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
            JS_RemoveObjectRoot(cx, &_JSDelegate);
        }
    }
    
    virtual void scrollViewDidScroll(ScrollView* view) override
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "scrollViewDidScroll", 1, &arg, NULL);
    }
    
    virtual void scrollViewDidZoom(ScrollView* view) override
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "scrollViewDidZoom", 1, &arg, NULL);
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
            JS_AddNamedObjectRoot(cx, &_JSDelegate, "TableViewDelegate");
        }
    }
private:
    JSObject* _JSDelegate;
    bool _needUnroot;
};

static JSBool js_cocos2dx_CCScrollView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ScrollView* cobj = (cocos2d::extension::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_ScrollViewDelegate* nativeDelegate = new JSB_ScrollViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        cobj->setUserObject(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}


#define KEY_TABLEVIEW_DATA_SOURCE  "TableViewDataSource"
#define KEY_TABLEVIEW_DELEGATE     "TableViewDelegate"

class JSB_TableViewDelegate
: public Object
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
            JS_RemoveObjectRoot(cx, &_JSDelegate);
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
            JS_AddNamedObjectRoot(cx, &_JSDelegate, "TableViewDelegate");
        }
    }
    
    
private:
    void callJSDelegate(ScrollView* view, std::string jsFunctionName)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), jsFunctionName.c_str(), 1, &arg, NULL);
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
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), jsFunctionName.c_str(), 2, args, NULL);
    }
    
    JSObject* _JSDelegate;
    bool _needUnroot;
};

static JSBool js_cocos2dx_CCTableView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_TableViewDelegate* nativeDelegate = new JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        Dictionary* userDict = static_cast<Dictionary*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new Dictionary();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->setObject(nativeDelegate, KEY_TABLEVIEW_DELEGATE);
        
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDataSource
: public Object
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
            JS_RemoveObjectRoot(cx, &_JSTableViewDataSource);
        }
    }
    
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) override
    {
        jsval ret;
        bool ok = callJSDelegate(table, idx, "tableCellSizeForIndex", ret);
        if (!ok) 
        {
            ok = callJSDelegate(table, "cellSizeForTable", ret);
        }
        if (ok) 
        {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            Size size;
            JSBool isSucceed = jsval_to_ccsize(cx, ret, &size);
            if (isSucceed) return size;
        }
        return Size::ZERO;
        
    }
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override
    {
        jsval ret;
        bool ok = callJSDelegate(table, idx, "tableCellAtIndex", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            cocos2d::extension::TableViewCell* arg0;
            do {
                js_proxy_t *proxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(ret);
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
        jsval ret;
        bool ok = callJSDelegate(table, "numberOfCellsInTableView", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            ssize_t count = 0;
            JSBool isSucceed = jsval_to_ssize(cx, ret, &count);
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
            JS_AddNamedObjectRoot(cx, &_JSTableViewDataSource, "TableViewDataSource");
        }
    }
    
private:
    bool callJSDelegate(TableView* table, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return false;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        
        JSBool hasAction;
        JS::RootedValue temp_retval(cx);
        jsval dataVal = OBJECT_TO_JSVAL(p->obj);
        
        JSObject* obj = _JSTableViewDataSource;
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
                                1, &dataVal, &retVal);
            return true;
        }
        return false;
    }
    
    bool callJSDelegate(TableView* table, ssize_t idx, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return false;
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSBool hasAction;
        JS::RootedValue temp_retval(cx);
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        dataVal[1] = ssize_to_jsval(cx,idx);
        
        JSObject* obj = _JSTableViewDataSource;
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

            JSBool ret = JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                                2, dataVal, &retVal);
            return ret == JS_TRUE ? true : false;
        }
        return false;
    }
    
private:
    JSObject* _JSTableViewDataSource;
    bool _needUnroot;
};

static JSBool js_cocos2dx_CCTableView_setDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::TableView* cobj = (cocos2d::extension::TableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
    
        Dictionary* userDict = static_cast<Dictionary*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new Dictionary();
            cobj->setUserObject(userDict);
            userDict->release();
        }

        userDict->setObject(pNativeSource, KEY_TABLEVIEW_DATA_SOURCE);

        cobj->setDataSource(pNativeSource);
        
        pNativeSource->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_CCTableView_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    if (argc == 3 || argc == 2)
    {
        
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
        
        cocos2d::Size arg1;
        ok &= jsval_to_ccsize(cx, argv[1], &arg1);
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
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
                proxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::Node*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, JS_FALSE, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
            ret->initWithViewSize(arg1, arg2);
        }
        ret->reloadData();
        
        Dictionary* userDict = new Dictionary();
        userDict->setObject(pNativeSource, KEY_TABLEVIEW_DATA_SOURCE);
        ret->setUserObject(userDict);
        userDict->release();
        
        pNativeSource->release();
        
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

class JSB_EditBoxDelegate
: public Object
, public EditBoxDelegate
{
public:
    JSB_EditBoxDelegate()
    : _JSDelegate(NULL)
    , _needUnroot(false)
    {}
    
    virtual ~JSB_EditBoxDelegate()
    {
        if (_needUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_RemoveObjectRoot(cx, &_JSDelegate);
        }
    }
    
    virtual void editBoxEditingDidBegin(EditBox* editBox) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxEditingDidBegin", 1, &arg, NULL);
    }
    
    virtual void editBoxEditingDidEnd(EditBox* editBox) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxEditingDidEnd", 1, &arg, NULL);
    }
    
    virtual void editBoxTextChanged(EditBox* editBox, const std::string& text) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        std::string arg1 = text;
        dataVal[1] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), arg1);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxTextChanged", 2, dataVal, NULL);
    }
    
    virtual void editBoxReturn(EditBox* editBox) override
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxReturn", 1, &arg, NULL);
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
            JS_AddNamedObjectRoot(cx, &_JSDelegate, "TableViewDelegate");
        }
    }
private:
    JSObject* _JSDelegate;
    bool _needUnroot;
};

static JSBool js_cocos2dx_CCEditBox_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::EditBox* cobj = (cocos2d::extension::EditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_EditBoxDelegate* nativeDelegate = new JSB_EditBoxDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        cobj->setUserObject(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}



class JSB_ControlButtonTarget : public Object
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
            JS_RemoveObjectRoot(cx, &_jsTarget);
        }
        
        JS_RemoveObjectRoot(cx, &_jsFunc);

        for (auto iter = _jsNativeTargetMap.begin(); iter != _jsNativeTargetMap.end(); ++iter)
        {
            if (this == iter->second)
            {
                _jsNativeTargetMap.erase(iter);
                break;
            }
        }
    }
    
    virtual void onEvent(Object *controlButton, Control::EventType event)
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
        jsval jsRet;

        ScriptingCore::getInstance()->executeJSFunctionWithThisObj(OBJECT_TO_JSVAL(_jsTarget), OBJECT_TO_JSVAL(_jsFunc), 2, dataVal, &jsRet);
    }
    
    void setJSTarget(JSObject* pJSTarget)
    {
        _jsTarget = pJSTarget;
        
        js_proxy_t* p = jsb_get_js_proxy(_jsTarget);
        if (!p)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_AddNamedObjectRoot(cx, &_jsTarget, "JSB_ControlButtonTarget, target");
            _needUnroot = true;
        }
    }
    
    void setJSAction(JSObject* jsFunc)
    {
        _jsFunc = jsFunc;

        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_AddNamedObjectRoot(cx, &_jsFunc, "JSB_ControlButtonTarget, func");
    }
    
    void setEventType(Control::EventType type)
    {
        _type = type;
    }
public:
    
    static std::multimap<JSObject*, JSB_ControlButtonTarget*> _jsNativeTargetMap;
    JSObject* _jsFunc;
    Control::EventType _type;
private:
    JSObject* _jsTarget;
    bool _needUnroot;
};

std::multimap<JSObject*, JSB_ControlButtonTarget*> JSB_ControlButtonTarget::_jsNativeTargetMap;

static JSBool js_cocos2dx_CCControl_addTargetWithActionForControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    JSBool ok = JS_TRUE;
    if (argc == 3)
    {
        JSObject* jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSObject* jsFunc = JSVAL_TO_OBJECT(argv[1]);
        Control::EventType arg2;
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing control event");
        
        // Check whether the target already exists.
        auto range = JSB_ControlButtonTarget::_jsNativeTargetMap.equal_range(jsDelegate);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second->_jsFunc == jsFunc && arg2 == it->second->_type)
            {
                // Return true directly.
                JS_SET_RVAL(cx, vp, JSVAL_VOID);
                return JS_TRUE;
            }
        }
        
        // save the delegate
        JSB_ControlButtonTarget* nativeDelegate = new JSB_ControlButtonTarget();
        
        nativeDelegate->setJSTarget(jsDelegate);
        nativeDelegate->setJSAction(jsFunc);
        nativeDelegate->setEventType(arg2);

        Array* nativeDelegateArray = static_cast<Array*>(cobj->getUserObject());
        if (nullptr == nativeDelegateArray)
        {
            nativeDelegateArray = new Array();
            nativeDelegateArray->init();
            cobj->setUserObject(nativeDelegateArray);  // The reference of nativeDelegateArray is added to 2
            nativeDelegateArray->release(); // Release nativeDelegateArray to make the reference to 1
        }
        
        nativeDelegateArray->addObject(nativeDelegate); // The reference of nativeDelegate is added to 2
        nativeDelegate->release(); // Release nativeDelegate to make the reference to 1
        
        cobj->addTargetWithActionForControlEvents(nativeDelegate, cccontrol_selector(JSB_ControlButtonTarget::onEvent), arg2);
        
        JSB_ControlButtonTarget::_jsNativeTargetMap.insert(std::make_pair(jsDelegate, nativeDelegate));
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return JS_FALSE;
}

static JSBool js_cocos2dx_CCControl_removeTargetWithActionForControlEvents(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::Control* cobj = (cocos2d::extension::Control *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    JSBool ok = JS_TRUE;
    if (argc == 3)
    {
        Control::EventType arg2;
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing control event");
        
        obj = JSVAL_TO_OBJECT(argv[0]);
        JSObject* jsFunc = JSVAL_TO_OBJECT(argv[1]);
        
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

        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
    return JS_FALSE;
}

extern JSObject* jsb_cocos2d_extension_ScrollView_prototype;
extern JSObject* jsb_cocos2d_extension_TableView_prototype;
extern JSObject* jsb_cocos2d_extension_EditBox_prototype;
extern JSObject* jsb_cocos2d_extension_Control_prototype;

void register_all_cocos2dx_extension_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_cocos2d_extension_ScrollView_prototype, "setDelegate", js_cocos2dx_CCScrollView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_extension_TableView_prototype, "setDelegate", js_cocos2dx_CCTableView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_extension_TableView_prototype, "setDataSource", js_cocos2dx_CCTableView_setDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_extension_EditBox_prototype, "setDelegate", js_cocos2dx_CCEditBox_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_extension_Control_prototype, "addTargetWithActionForControlEvents", js_cocos2dx_CCControl_addTargetWithActionForControlEvents, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_cocos2d_extension_Control_prototype, "removeTargetWithActionForControlEvents", js_cocos2dx_CCControl_removeTargetWithActionForControlEvents, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JSObject *tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.TableView; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCTableView_create, 3, JSPROP_READONLY | JSPROP_PERMANENT);
}