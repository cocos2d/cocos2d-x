#include "jsb_cocos2dx_extension_manual.h"
#include "cocos-ext.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "js_manual_conversions.h"
#include "js_bindings_chipmunk_auto_classes.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class JSStudioEventListenerWrapper: public JSCallbackWrapper {
public:
    JSStudioEventListenerWrapper();
    virtual ~JSStudioEventListenerWrapper();

    virtual void setJSCallbackThis(jsval thisObj);

    virtual void eventCallbackFunc(CCObject*,int);
    
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
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
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

void JSStudioEventListenerWrapper::eventCallbackFunc(CCObject* sender,int eventType)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(jsThisObj) ? NULL : JSVAL_TO_OBJECT(jsThisObj);
    js_proxy_t *proxy = js_get_or_create_proxy(cx, sender);
    jsval retval;
    if (jsCallback != JSVAL_VOID)
    {
        jsval touchVal = INT_TO_JSVAL(eventType);

        jsval valArr[2];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = touchVal;

        JS_AddValueRoot(cx, valArr);
        JS_CallFunctionValue(cx, thisObj, jsCallback, 2, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
}

static JSBool js_cocos2dx_Widget_addTouchEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Widget* cobj = (cocos2d::ui::Widget *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "widgetTouchEvent");

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addTouchEventListener(tmpObj, toucheventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_CheckBox_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::CheckBox* cobj = (cocos2d::ui::CheckBox *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "checkBoxEventListener");

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerCheckBox(tmpObj, checkboxselectedeventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_Slider_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::Slider* cobj = (cocos2d::ui::Slider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "sliderEventListener");

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerSlider(tmpObj, sliderpercentchangedselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_TextField_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::TextField* cobj = (cocos2d::ui::TextField *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "textfieldEventListener");

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerTextField(tmpObj, textfieldeventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_PageView_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::PageView* cobj = (cocos2d::ui::PageView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "pageViewEventListener");

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerPageView(tmpObj, pagevieweventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_ScrollView_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ScrollView* cobj = (cocos2d::ui::ScrollView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    
    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);
        
        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "scrollViewEventListener");
        
        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);
        
        cobj->addEventListenerScrollView(tmpObj, scrollvieweventselector(JSStudioEventListenerWrapper::eventCallbackFunc));
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_ListView_addEventListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::ListView* cobj = (cocos2d::ui::ListView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSStudioEventListenerWrapper *tmpObj = new JSStudioEventListenerWrapper();
        tmpObj->autorelease();
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == dict)
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "listViewEventListener");

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->addEventListenerListView(tmpObj, listvieweventselector(JSStudioEventListenerWrapper::eventCallbackFunc));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

class JSArmatureWrapper: public JSStudioEventListenerWrapper {
public: 
    void movementCallbackFunc(cocos2d::extension::CCArmature * pArmature, cocos2d::extension::MovementEventType pMovementEventType, const char *pMovementId);
    void frameCallbackFunc(cocos2d::extension::CCBone *pBone, const char *frameEventName, int originFrameIndex, int currentFrameIndex);
    void addArmatureFileInfoAsyncCallbackFunc(float percent);
    
};

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
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == cobj->getScriptObjectDict())
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "moveEvent");

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
        
        CCDictionary* dict = static_cast<CCDictionary*>(cobj->getScriptObjectDict());
        if (NULL == cobj->getScriptObjectDict())
        {
            dict = CCDictionary::create();
            cobj->setScriptObjectDict(dict);
        }
        dict->setObject(tmpObj, "frameEvent");

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

        tmpObj->setJSCallbackFunc(argv[1]);
        tmpObj->setJSCallbackThis(argv[2]);
        
        std::string ret;
        jsval_to_std_string(cx, argv[0], &ret);
        
        cobj->addArmatureFileInfoAsync(ret.c_str(), tmpObj, schedule_selector(JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc));
        
        return JS_TRUE;
    }
    
    if(argc == 5){
		jsval *argv = JS_ARGV(cx, vp);
        
        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();
        
        tmpObj->setJSCallbackFunc(argv[3]);
        tmpObj->setJSCallbackThis(argv[4]);
        
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

#if ENABLE_PHYSICS_CHIPMUNK_DETECT
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
#endif //ENABLE_PHYSICS_CHIPMUNK_DETECT

static JSBool js_cocos2dx_LayoutParameter_setMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutParameter* cobj = (cocos2d::ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 1) {
        jsval *argv = JS_ARGV(cx, vp);

        JSObject *tmp;
        jsval jsleft, jstop,jsright,jsbottom;
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

        cobj->setMargin(cocos2d::ui::Margin(left,top,right,bottom));
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_LayoutParameter_getMargin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::ui::LayoutParameter* cobj = (cocos2d::ui::LayoutParameter *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 0) {
        JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
        if (!tmp) return JS_FALSE;
        cocos2d::ui::Margin margin = cobj->getMargin();
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

JSBool js_cocos2dx_studio_ColliderBody_getCalculatedVertexList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::extension::ColliderBody* cobj = (cocos2d::extension::ColliderBody *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        cocos2d::CCArray* ret = cobj->getCalculatedVertexList();
        JSObject *jsretArr = JS_NewArrayObject(cx, 0, nullptr);
        jsval jsret;
        CCObject* obj;
        int i = 0;
        CCARRAY_FOREACH(ret, obj)
        {
            CCContourVertex2* contourVertex = static_cast<CCContourVertex2*>(obj);
            if (contourVertex)
            {
                JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
                if (!tmp) break;
                JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(contourVertex->x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                    JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(contourVertex->y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
                jsval jsTmp = OBJECT_TO_JSVAL(tmp);
                if(!ok || !JS_SetElement(cx, jsretArr, i, &jsTmp))
                {
                    break;
                }
            }
            else
            {
                break;
            }
            ++i;
        }
        jsret = OBJECT_TO_JSVAL(jsretArr);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}


extern JSObject* jsb_Widget_prototype;
extern JSObject* jsb_CheckBox_prototype;
extern JSObject* jsb_Slider_prototype;
extern JSObject* jsb_TextField_prototype;
extern JSObject* jsb_LayoutParameter_prototype;
extern JSObject* jsb_ScrollView_prototype;
extern JSObject* jsb_PageView_prototype;
extern JSObject* jsb_ListView_prototype;
extern JSObject* jsb_CCArmatureAnimation_prototype;
extern JSObject* jsb_CCArmatureDataManager_prototype;
extern JSObject* jsb_CCArmature_prototype;
extern JSObject* jsb_ColliderBody_prototype;

void register_all_cocos2dx_studio_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_ColliderBody_prototype, "getCalculatedVertexList", js_cocos2dx_studio_ColliderBody_getCalculatedVertexList, 0, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_Widget_prototype, "addTouchEventListener", js_cocos2dx_Widget_addTouchEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_CheckBox_prototype, "addEventListenerCheckBox", js_cocos2dx_CheckBox_addEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_Slider_prototype, "addEventListenerSlider", js_cocos2dx_Slider_addEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_TextField_prototype, "addEventListenerTextField", js_cocos2dx_TextField_addEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_PageView_prototype, "addEventListenerPageView", js_cocos2dx_PageView_addEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_ScrollView_prototype, "addEventListenerScrollView", js_cocos2dx_ScrollView_addEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_ListView_prototype, "addEventListenerListView", js_cocos2dx_ListView_addEventListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_LayoutParameter_prototype, "setMargin", js_cocos2dx_LayoutParameter_setMargin, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_LayoutParameter_prototype, "getMargin", js_cocos2dx_LayoutParameter_getMargin, 0, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_CCArmatureAnimation_prototype, "setMovementEventCallFunc", js_cocos2dx_CCArmatureAnimation_setMovementEventCallFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_CCArmatureAnimation_prototype, "setFrameEventCallFunc", js_cocos2dx_CCArmatureAnimation_setFrameEventCallFunc, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCArmatureDataManager_prototype, "addArmatureFileInfoAsync", jsb_Animation_addArmatureFileInfoAsyncCallFunc, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    
#if ENABLE_PHYSICS_CHIPMUNK_DETECT
    JS_DefineFunction(cx, jsb_CCArmature_prototype, "_setCPBody", jsb_CCArmature_setCPBody, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_CCArmature_prototype, "getShapeList", jsb_CCArmature_getShapeList, 0, JSPROP_READONLY | JSPROP_PERMANENT);
#endif
}
