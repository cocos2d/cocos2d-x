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

class JSB_ScrollViewDelegate : public CCScrollViewDelegate
{
public:
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewDidScroll", 1, &arg, NULL);
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewDidZoom", 1, &arg, NULL);
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }
private:
    JSObject* m_pJSDelegate;
};

static JSBool js_cocos2dx_CCScrollView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCScrollView* cobj = (cocos2d::extension::CCScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_ScrollViewDelegate* nativeDelegate = new JSB_ScrollViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setDelegate(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDelegate : public CCTableViewDelegate
{
public:
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
        m_pJSDelegate = pJSDelegate;
    }
    
    
private:
    void callJSDelegate(CCScrollView* view, std::string jsFunctionName)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), jsFunctionName.c_str(), 1, &arg, NULL);
    }
    
    void callJSDelegate(CCTableView* table, CCTableViewCell* cell, std::string jsFunctionName)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, table);
        if (!p) return;
        
        js_proxy_t * pCellProxy;
        JS_GET_PROXY(pCellProxy, cell);
        if (!pCellProxy) return;
        
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = OBJECT_TO_JSVAL(pCellProxy->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), jsFunctionName.c_str(), 2, args, NULL);
    }
    
    JSObject* m_pJSDelegate;
};

static JSBool js_cocos2dx_CCTableView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_TableViewDelegate* nativeDelegate = new JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setDelegate(nativeDelegate);
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_TableViewDataSource : public CCTableViewDataSource
{
public:
    virtual CCSize cellSizeForTable(CCTableView *table)
    {
        jsval ret;
        bool ok = callJSDelegate(table, "cellSizeForTable", ret);
        if (ok)
        {
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
                JS_GET_NATIVE_PROXY(proxy, tmpObj);
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
        m_pJSTableViewDataSource = pJSSource;
    }
    
private:
    bool callJSDelegate(CCTableView* table, std::string jsFunctionName, jsval& retVal)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, table);
        if (!p) return false;
        
        JSBool hasAction;
        jsval temp_retval;
        jsval dataVal = OBJECT_TO_JSVAL(p->obj);
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* obj = m_pJSTableViewDataSource;
        
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
        js_proxy_t * p;
        JS_GET_PROXY(p, table);
        if (!p) return false;
        
        
        JSBool hasAction;
        jsval temp_retval;
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        dataVal[1] = INT_TO_JSVAL(idx);
        
        JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject* obj = m_pJSTableViewDataSource;
        
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
    JSObject* m_pJSTableViewDataSource;
};

static JSBool js_cocos2dx_CCTableView_setDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCTableView* cobj = (cocos2d::extension::CCTableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1)
    {
        CCTableViewDataSource* pOldDataSource = cobj->getDataSource();
        CC_SAFE_DELETE(pOldDataSource);
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
        cobj->setDataSource(pNativeSource);
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
        ret->setDataSource(pNativeSource);
        ret->autorelease();
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
                JS_GET_NATIVE_PROXY(proxy, tmpObj);
                arg2 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( arg2, cx, JS_FALSE, "Invalid Native Object");
            } while (0);
            JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
            ret->initWithViewSize(arg1, arg2);
        }
        ret->_updateContentSize();
        
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}

class JSB_EditBoxDelegate : public CCEditBoxDelegate
{
public:
    virtual void editBoxEditingDidBegin(CCEditBox* editBox)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxEditingDidBegin", 1, &arg, NULL);
    }
    
    virtual void editBoxEditingDidEnd(CCEditBox* editBox)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxEditingDidEnd", 1, &arg, NULL);
    }
    
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        std::string arg1 = text;
        dataVal[1] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), arg1);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxTextChanged", 2, dataVal, NULL);
    }
    
    virtual void editBoxReturn(CCEditBox* editBox)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxReturn", 1, &arg, NULL);
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
    }
private:
    JSObject* m_pJSDelegate;
};

static JSBool js_cocos2dx_CCEditBox_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
    cocos2d::extension::CCEditBox* cobj = (cocos2d::extension::CCEditBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 1) {
        // save the delegate
        JSObject *jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSB_EditBoxDelegate* nativeDelegate = new JSB_EditBoxDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        cobj->setDelegate(nativeDelegate);
        
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