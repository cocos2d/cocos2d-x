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
#include "js_manual_conversions.h"
#include "js_bindings_chipmunk_auto_classes.h"

USING_NS_CC;
USING_NS_CC_EXT;

class JSB_ScrollViewDelegate
: public CCObject
, public CCScrollViewDelegate
{
public:
    JSB_ScrollViewDelegate()
    : m_pJSDelegate(NULL)
    , m_bNeedUnroot(false)
    {}
    
    virtual ~JSB_ScrollViewDelegate()
    {
        if (m_bNeedUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_RemoveObjectRoot(cx, &m_pJSDelegate);
        }
    }
    
    virtual void scrollViewDidScroll(CCScrollView* view)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewDidScroll", 1, &arg, NULL);
    }
    
    virtual void scrollViewDidZoom(CCScrollView* view)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "scrollViewDidZoom", 1, &arg, NULL);
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(m_pJSDelegate);
        if (!p)
        {
            m_bNeedUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_AddNamedObjectRoot(cx, &m_pJSDelegate, "TableViewDelegate");
        }
    }
private:
    JSObject* m_pJSDelegate;
    bool m_bNeedUnroot;
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
: public CCObject
, public CCTableViewDelegate
{
public:
    JSB_TableViewDelegate()
    : m_pJSDelegate(NULL)
    , m_bNeedUnroot(false)
    {}
    
    virtual ~JSB_TableViewDelegate()
    {
        if (m_bNeedUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_RemoveObjectRoot(cx, &m_pJSDelegate);
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
        m_pJSDelegate = pJSDelegate;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(m_pJSDelegate);
        if (!p)
        {
            m_bNeedUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_AddNamedObjectRoot(cx, &m_pJSDelegate, "TableViewDelegate");
        }
    }
    
    
private:
    void callJSDelegate(CCScrollView* view, std::string jsFunctionName)
    {
        js_proxy_t * p = jsb_get_native_proxy(view);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), jsFunctionName.c_str(), 1, &arg, NULL);
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
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), jsFunctionName.c_str(), 2, args, NULL);
    }
    
    JSObject* m_pJSDelegate;
    bool m_bNeedUnroot;
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
        
        CCDictionary* userDict = static_cast<CCDictionary*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new CCDictionary();
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
: public CCObject
, public CCTableViewDataSource
{
public:
    JSB_TableViewDataSource()
    : m_pJSTableViewDataSource(NULL)
    , m_bNeedUnroot(false)
    {}
    
    virtual ~JSB_TableViewDataSource()
    {
        if (m_bNeedUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_RemoveObjectRoot(cx, &m_pJSTableViewDataSource);
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
        m_pJSTableViewDataSource = pJSSource;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(m_pJSTableViewDataSource);
        if (!p)
        {
            m_bNeedUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_AddNamedObjectRoot(cx, &m_pJSTableViewDataSource, "TableViewDataSource");
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
        js_proxy_t * p = jsb_get_native_proxy(table);
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
    bool m_bNeedUnroot;
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
    
        CCDictionary* userDict = static_cast<CCDictionary*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new CCDictionary();
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
    if (argc == 3 || argc == 2) {
        
        JSB_TableViewDataSource* pNativeSource = new JSB_TableViewDataSource();
        pNativeSource->setTableViewDataSource(JSVAL_TO_OBJECT(argv[0]));
        
        cocos2d::CCSize arg1;
        ok &= jsval_to_ccsize(cx, argv[1], &arg1);
        cocos2d::extension::CCTableView* ret = NULL;
        ret = new CCTableView();
        ret->autorelease();
        
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
        
        CCDictionary* userDict = new CCDictionary();
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
: public CCObject
, public CCEditBoxDelegate
{
public:
    JSB_EditBoxDelegate()
    : m_pJSDelegate(NULL)
    , m_bNeedUnroot(false)
    {}
    
    virtual ~JSB_EditBoxDelegate()
    {
        if (m_bNeedUnroot)
        {
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_RemoveObjectRoot(cx, &m_pJSDelegate);
        }
    }
    
    virtual void editBoxEditingDidBegin(CCEditBox* editBox)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxEditingDidBegin", 1, &arg, NULL);
    }
    
    virtual void editBoxEditingDidEnd(CCEditBox* editBox)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxEditingDidEnd", 1, &arg, NULL);
    }
    
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        std::string arg1 = text;
        dataVal[1] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), arg1);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxTextChanged", 2, dataVal, NULL);
    }
    
    virtual void editBoxReturn(CCEditBox* editBox)
    {
        js_proxy_t * p = jsb_get_native_proxy(editBox);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(m_pJSDelegate), "editBoxReturn", 1, &arg, NULL);
    }
    
    void setJSDelegate(JSObject* pJSDelegate)
    {
        m_pJSDelegate = pJSDelegate;
        
        // Check whether the js delegate is a pure js object.
        js_proxy_t* p = jsb_get_js_proxy(m_pJSDelegate);
        if (!p)
        {
            m_bNeedUnroot = true;
            JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
            JS_AddNamedObjectRoot(cx, &m_pJSDelegate, "TableViewDelegate");
        }
    }
private:
    JSObject* m_pJSDelegate;
    bool m_bNeedUnroot;
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
        
        cobj->setUserObject(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        
        nativeDelegate->release();
        
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

class JSB_ControlButtonTarget : public CCObject
{
public:
    JSB_ControlButtonTarget()
        : _jsFunc(NULL),
        _type(CCControlEventTouchDown),
        _jsTarget(NULL),
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

        for (std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator iter = _jsNativeTargetMap.begin(); iter != _jsNativeTargetMap.end(); ++iter)
        {
            if (this == iter->second)
            {
                _jsNativeTargetMap.erase(iter);
                break;
            }
        }
    }

    virtual void onEvent(CCObject *controlButton, CCControlEvent event)
    {
        js_proxy_t * p;
        JS_GET_PROXY(p, controlButton);
        if (!p)
        {
            CCLOGERROR("Failed to get proxy for control button");
            return;
        }

        jsval dataVal[2];
        dataVal[0] = OBJECT_TO_JSVAL(p->obj);
        int arg1 = (int)event;
        dataVal[1] = INT_TO_JSVAL(arg1);
        jsval jsRet;

        ScriptingCore::getInstance()->executeJSFunctionWithThisObj(OBJECT_TO_JSVAL(_jsTarget), OBJECT_TO_JSVAL(_jsFunc), 2,dataVal,&jsRet);
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

    void setEventType(CCControlEvent type)
    {
        _type = type;
    }
public:

    static std::multimap<JSObject*, JSB_ControlButtonTarget*> _jsNativeTargetMap;
    JSObject* _jsFunc;
    CCControlEvent _type;
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
    cocos2d::extension::CCControl* cobj = (cocos2d::extension::CCControl *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    JSBool ok = JS_TRUE;
    if (argc == 3)
    {
        JSObject* jsDelegate = JSVAL_TO_OBJECT(argv[0]);
        JSObject* jsFunc = JSVAL_TO_OBJECT(argv[1]);
        CCControlEvent arg2;
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing control event");

        // Check whether the target already exists.
        std::pair<std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator,std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator> range;
        range = JSB_ControlButtonTarget::_jsNativeTargetMap.equal_range(jsDelegate);
        std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator it = range.first;
        for (; it != range.second; ++it)
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

        CCArray* nativeDelegateArray = static_cast<CCArray*>(cobj->getUserObject());
        if (NULL == nativeDelegateArray)
        {
            nativeDelegateArray = new CCArray();
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
    cocos2d::extension::CCControl* cobj = (cocos2d::extension::CCControl *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    JSBool ok = JS_TRUE;
    if (argc == 3)
    {
        CCControlEvent arg2;
        ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing control event");

        obj = JSVAL_TO_OBJECT(argv[0]);
        JSObject* jsFunc = JSVAL_TO_OBJECT(argv[1]);

        JSB_ControlButtonTarget* nativeTargetToRemoved = NULL;

        std::pair<std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator,std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator> range;
        range = JSB_ControlButtonTarget::_jsNativeTargetMap.equal_range(obj);
        std::multimap<JSObject*, JSB_ControlButtonTarget*>::iterator it = range.first;
        for (; it != range.second; ++it)
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

class JSArmatureWrapper: public JSCallbackWrapper {
public:
    JSArmatureWrapper();
    virtual ~JSArmatureWrapper();
    
    virtual void setJSCallbackThis(jsval thisObj);
    
    void movementCallbackFunc(cocos2d::extension::CCArmature * pArmature, cocos2d::extension::MovementEventType pMovementEventType, const char *pMovementId);
    void frameCallbackFunc(cocos2d::extension::CCBone *pBone, const char *frameEventName, int originFrameIndex, int currentFrameIndex);
    void addArmatureFileInfoAsyncCallbackFunc(float percent);
    
private:
    bool m_bNeedUnroot;
};

JSArmatureWrapper::JSArmatureWrapper()
: m_bNeedUnroot(false)
{
    
}

JSArmatureWrapper::~JSArmatureWrapper()
{
    if (m_bNeedUnroot)
    {
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_RemoveObjectRoot(cx, &thisObj);
    }
}

void JSArmatureWrapper::setJSCallbackThis(jsval jsThisObj)
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

void JSArmatureWrapper::movementCallbackFunc(cocos2d::extension::CCArmature *pArmature, cocos2d::extension::MovementEventType pMovementEventType, const char *pMovementId)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(jsThisObj) ? NULL : JSVAL_TO_OBJECT(jsThisObj);
    js_proxy_t *proxy = js_get_or_create_proxy(cx, pArmature);
    jsval retval;
    if (jsCallback != JSVAL_VOID)
    {
        int movementEventType = (int)pMovementEventType;
        jsval movementVal = INT_TO_JSVAL(movementEventType);
        
        jsval idVal = c_string_to_jsval(cx, pMovementId);
        
        jsval valArr[3];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = movementVal;
        valArr[2] = idVal;
        
        JS_AddValueRoot(cx, valArr);
        JS_CallFunctionValue(cx, thisObj, jsCallback, 3, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
}

void JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc(float percent)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(jsThisObj) ? NULL : JSVAL_TO_OBJECT(jsThisObj);
    jsval retval;
    if (jsCallback != JSVAL_VOID)
    {
        jsval percentVal = DOUBLE_TO_JSVAL(percent);
        
        JS_AddValueRoot(cx, &percentVal);
        JS_CallFunctionValue(cx, thisObj, jsCallback, 1, &percentVal, &retval);
        JS_RemoveValueRoot(cx, &percentVal);
    }
}


void JSArmatureWrapper::frameCallbackFunc(cocos2d::extension::CCBone *pBone, const char *frameEventName, int originFrameIndex, int currentFrameIndex)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(jsThisObj) ? NULL : JSVAL_TO_OBJECT(jsThisObj);
    js_proxy_t *proxy = js_get_or_create_proxy(cx, pBone);
    jsval retval;
    if (jsCallback != JSVAL_VOID)
    {
        jsval nameVal = c_string_to_jsval(cx, frameEventName);
        jsval originIndexVal = INT_TO_JSVAL(originFrameIndex);
        jsval currentIndexVal = INT_TO_JSVAL(currentFrameIndex);
        
        jsval valArr[4];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = nameVal;
        valArr[2] = originIndexVal;
        valArr[3] = currentIndexVal;
        
        JS_AddValueRoot(cx, valArr);
        JS_CallFunctionValue(cx, thisObj, jsCallback, 4, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
}

static JSBool js_cocos2dx_CCArmatureAnimation_setMovementEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureAnimation* cobj = (cocos2d::extension::CCArmatureAnimation *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 2) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();
        
        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);
        
        cobj->setMovementEventCallFunc(tmpObj, movementEvent_selector(JSArmatureWrapper::movementCallbackFunc));
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_CCArmatureAnimation_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureAnimation* cobj = (cocos2d::extension::CCArmatureAnimation *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 2) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();
        
        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);
        
        cobj->setFrameEventCallFunc(tmpObj, frameEvent_selector(JSArmatureWrapper::frameCallbackFunc));
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool jsb_Animation_addArmatureFileInfoAsyncCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cocos2d::extension::CCArmatureDataManager* cobj = (cocos2d::extension::CCArmatureDataManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 3) {
		jsval *argv = JS_ARGV(cx, vp);
        
        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();
        
        tmpObj->setJSCallbackFunc(argv[2]);
        tmpObj->setJSCallbackThis(argv[1]);
        
        std::string ret;
        jsval_to_std_string(cx, argv[0], &ret);
        
        cobj->addArmatureFileInfoAsync(ret.c_str(), tmpObj, schedule_selector(JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc));
        
        return JS_TRUE;
    }
    
    if(argc == 5){
		jsval *argv = JS_ARGV(cx, vp);
        
        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();
        
        tmpObj->setJSCallbackFunc(argv[4]);
        tmpObj->setJSCallbackThis(argv[3]);
        
        std::string imagePath;
        jsval_to_std_string(cx ,argv[0] , &imagePath);
        
        std::string plistPath;
        jsval_to_std_string(cx ,argv[1] , &plistPath);
        
        std::string configFilePath;
        jsval_to_std_string(cx ,argv[2] , &configFilePath);
        
        cobj->addArmatureFileInfoAsync(imagePath.c_str(), plistPath.c_str(), configFilePath.c_str(), tmpObj, schedule_selector(JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc));
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool jsb_CCArmature_setCPBody(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CCArmature* real = (CCArmature *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    jsval *argvp = JS_ARGV(cx,vp);
    JSBool ok = JS_TRUE;

    cpBody* arg0;

    ok &= jsval_to_opaque( cx, *argvp++, (void**)&arg0 );
    if( ! ok ) return JS_FALSE;

    real->setBody((cpBody*)arg0);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

static JSBool jsb_CCArmature_getShapeList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CCArmature* real = (CCArmature *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, real)

    if (argc == 0)
    {
        cpShape* shape = real->getShapeList();

        JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);

        int i = 0;
        while (shape)
        {
            cpShape *next = shape->next_private;

            jsval ret_jsval = c_class_to_jsval( cx, shape, JSB_cpShape_object, JSB_cpShape_class, "cpShape" );

            if(!JS_SetElement(cx, jsretArr, i, &ret_jsval)) {
                break;
            }
            shape = next;
            ++i;
        }

        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(jsretArr));
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

extern JSObject* jsb_CCScrollView_prototype;
extern JSObject* jsb_CCTableView_prototype;
extern JSObject* jsb_CCEditBox_prototype;
extern JSObject* jsb_CCArmatureAnimation_prototype;
extern JSObject* jsb_CCArmatureDataManager_prototype;
extern JSObject* jsb_CCControl_prototype;
extern JSObject* jsb_CCArmature_prototype;

void register_all_cocos2dx_extension_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_CCScrollView_prototype, "setDelegate", js_cocos2dx_CCScrollView_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCTableView_prototype, "setDelegate", js_cocos2dx_CCTableView_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCTableView_prototype, "setDataSource", js_cocos2dx_CCTableView_setDataSource, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCEditBox_prototype, "setDelegate", js_cocos2dx_CCEditBox_setDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCControl_prototype, "addTargetWithActionForControlEvents", js_cocos2dx_CCControl_addTargetWithActionForControlEvents, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, jsb_CCControl_prototype, "removeTargetWithActionForControlEvents", js_cocos2dx_CCControl_removeTargetWithActionForControlEvents, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCArmatureAnimation_prototype, "setMovementEventCallFunc", js_cocos2dx_CCArmatureAnimation_setMovementEventCallFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_CCArmatureAnimation_prototype, "setFrameEventCallFunc", js_cocos2dx_CCArmatureAnimation_setFrameEventCallFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCArmatureDataManager_prototype, "addArmatureFileInfoAsync", jsb_Animation_addArmatureFileInfoAsyncCallFunc, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCArmature_prototype, "_setCPBody", jsb_CCArmature_setCPBody, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCArmature_prototype, "getShapeList", jsb_CCArmature_getShapeList, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JSObject *tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, global, "(function () { return cc.TableView; })()"));
	JS_DefineFunction(cx, tmpObj, "create", js_cocos2dx_CCTableView_create, 3, JSPROP_READONLY | JSPROP_PERMANENT);
}
