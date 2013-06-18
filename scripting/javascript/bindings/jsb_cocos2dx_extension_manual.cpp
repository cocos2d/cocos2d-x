//
//  jsb_cocos2d_extension_manual.cpp
//
//  Created by James Chen on 3/11/13.
//
//

#include "jsb_cocos2dx_extension_manual.h"
#include "cocos-ext.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"

USING_NS_CC;
USING_NS_CC_EXT;

class JSB_ScrollViewDelegate
: public CCNode
, public CCScrollViewDelegate
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
    
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "scrollViewDidScroll", 1, &arg, NULL);
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
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
    cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_ScrollViewDelegate* nativeDelegate = new JSB_ScrollViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JSB_ScrollViewDelegate* oldDelegate = (JSB_ScrollViewDelegate*)cobj->getDelegate();
        if (oldDelegate)
        {
            oldDelegate->removeFromParent();
        }
        cobj->addChild(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDelegate
: public CCNode
, public CCTableViewDelegate
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
    
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        callJSDelegate(view, "scrollViewDidScroll");
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        callJSDelegate(view, "scrollViewDidZoom");
    }
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellTouched");
    }
    
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellHighlight");
    }
    
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell)
    {
        callJSDelegate(table, cell, "tableCellUnhighlight");
    }
    
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell)
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
    void callJSDelegate(CCScrollView* view, std::string jsFunctionName)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), jsFunctionName.c_str(), 1, &arg, NULL);
    }
    
    void callJSDelegate(CCTableView* table, CCTableViewCell* cell, std::string jsFunctionName)
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
    cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_TableViewDelegate* nativeDelegate = new JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        
        JSB_TableViewDelegate* oldDelegate = (JSB_TableViewDelegate*)cobj->getDelegate();
        if (oldDelegate)
        {
            oldDelegate->removeFromParent();
        }
        cobj->addChild(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDataSource
: public CCNode
, public CCTableViewDataSource
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
    
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx)
    {
        jsval ret;
        bool ok = callJSDelegate(table, idx, "tableCellSizeForIndex", ret);
        if (!ok) {
            ok = callJSDelegate(table, "cellSizeForTable", ret);
        }
        if (ok) {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            CCSize size;
            JSBool isSucceed = jsval_to_ccsize(cx, ret, &size);
            if (isSucceed) return size;
        }
        return CCSizeZero;
        
    }
    
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx)
    {
        jsval ret;
        bool ok = callJSDelegate(table, idx, "tableCellAtIndex", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            cocos2d::extension::CCTableViewCell* arg0;
            do {
                js_proxy_t *proxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(ret);
                proxy = jsb_get_js_proxy(tmpObj);
                arg0 = (cocos2d::extension::CCTableViewCell*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg0, cx, NULL, "Invalid Native Object");
            } while (0);
            return arg0;
        }
        return NULL;
    }
    
    virtual unsigned int numberOfCellsInTableView(CCTableView *table)
    {
        jsval ret;
        bool ok = callJSDelegate(table, "numberOfCellsInTableView", ret);
        if (ok)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            uint32_t count = 0;
            JSBool isSucceed = jsval_to_uint32(cx, ret, &count);
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
    bool callJSDelegate(CCTableView* table, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return false;
        
        JSBool hasAction;
        jsval temp_retval;
        jsval dataVal = OBJECT_TO_JSVAL(p->obj);
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* obj = _JSTableViewDataSource;
        
        if (JS_HasProperty(cx, obj, jsFunctionName.c_str(), &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, jsFunctionName.c_str(), &temp_retval)) {
                return false;
            }
            if(temp_retval == JSVAL_VOID) {
                return false;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                                1, &dataVal, &retVal);
            return true;
        }
        return false;
    }
    
    bool callJSDelegate(CCTableView* table, int idx, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return false;
        
        
        JSBool hasAction;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        dataVal[1] = INT_TO_JSVAL(idx);
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* obj = _JSTableViewDataSource;
        
        if (JS_HasProperty(cx, obj, jsFunctionName.c_str(), &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, jsFunctionName.c_str(), &temp_retval)) {
                return false;
            }
            if(temp_retval == JSVAL_VOID) {
                return false;
            }
            JSAutoCompartment ac(cx, obj);
            JS_CallFunctionName(cx, obj, jsFunctionName.c_str(),
                                2, dataVal, &retVal);
            return true;
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
    cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
    
        JSB_TableViewDataSource* oldDataSource = (JSB_TableViewDataSource*)cobj->getDataSource();
        if (oldDataSource)
        {
            oldDataSource->removeFromParent();
        }
        cobj->addChild(pNativeSource);
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
    if (argc == 3 || argc == 2) {
        
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
        
        cocos2d::CCSize arg1;
        ok &= jsval_to_ccsize(cx, argv[1], &arg1);
        cocos2d::extension::CCTableView* ret = NULL;
        ret = new CCTableView();
        ret->autorelease();
        
        JSB_TableViewDataSource* oldDataSource = (JSB_TableViewDataSource*)ret->getDataSource();
        if (oldDataSource)
        {
            oldDataSource->removeFromParent();
        }
        
        ret->setDataSource(pNativeSource);
        
        jsval jsret;
        do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::extension::CCTableView>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        
        if (argc == 2)
        {
            ret->initWithViewSize(arg1);
        }
        else
        {
            cocos2d::CCNode* arg2;
            do {
                js_proxy_t *proxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
                proxy = jsb_get_js_proxy(tmpObj);
                arg2 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, JS_FALSE, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
            ret->initWithViewSize(arg1, arg2);
        }
        ret->reloadData();
        
        ret->addChild(pNativeSource);
        pNativeSource->release();
        
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

class JSB_EditBoxDelegate
: public CCNode
, public CCEditBoxDelegate
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
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxEditingDidBegin", 1, &arg, NULL);
    }
    
    virtual void editBoxEditingDidEnd(CCEditBox* editBox)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxEditingDidEnd", 1, &arg, NULL);
    }
    
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        std::string arg1 = text;
        dataVal[1] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), arg1);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "editBoxTextChanged", 2, dataVal, NULL);
    }
    
    virtual void editBoxReturn(CCEditBox* editBox)
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
    cocos2d::extension::CCEditBox* cobj = (cocos2d::extension::CCEditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_EditBoxDelegate* nativeDelegate = new JSB_EditBoxDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JSB_EditBoxDelegate* oldDelegate = (JSB_EditBoxDelegate*)cobj->getDelegate();
        if (oldDelegate)
        {
            oldDelegate->removeFromParent();
        }
        cobj->addChild(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}


extern JSObject* jsb_CCScrollView_prototype;
extern JSObject* jsb_CCTableView_prototype;
extern JSObject* jsb_CCEditBox_prototype;

void register_all_cocos2dx_extension_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_CCScrollView_prototype, "setDelegate", js_cocos2dx_CCScrollView_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCTableView_prototype, "setDelegate", js_cocos2dx_CCTableView_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCTableView_prototype, "setDataSource", js_cocos2dx_CCTableView_setDataSource, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCEditBox_prototype, "setDelegate", js_cocos2dx_CCEditBox_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JSObject *tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.TableView; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCTableView_create, 3, JSPROP_READONLY | JSPROP_PERMANENT);
}