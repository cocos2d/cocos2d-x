//
//  jsb_cocos2dx_studio_manual.h
//
//  Created by LinWenhai on 20/10/13.
//
//
#include "jsb_cocos2dx_studio_manual.h"
#include "ScriptingCore.h"
#include "cocos2d_specifics.hpp"
#include "cocostudio/CocoStudio.h"

class JSArmatureWrapper: public JSCallbackWrapper {
public:
    JSArmatureWrapper();
    virtual ~JSArmatureWrapper();

    virtual void setJSCallbackThis(jsval thisObj);

    void movementCallbackFunc(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);
    void frameCallbackFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);
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
        JSObject *thisObj = JSVAL_TO_OBJECT(_jsThisObj);
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_RemoveObjectRoot(cx, &thisObj);
    }
}

void JSArmatureWrapper::setJSCallbackThis(jsval _jsThisObj)
{
    JSCallbackWrapper::setJSCallbackThis(_jsThisObj);

    JSObject *thisObj = JSVAL_TO_OBJECT(_jsThisObj);
    js_proxy *p = jsb_get_js_proxy(thisObj);
    if (!p)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_AddObjectRoot(cx, &thisObj);
        m_bNeedUnroot = true;
    }
}

void JSArmatureWrapper::movementCallbackFunc(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
    js_proxy_t *proxy = js_get_or_create_proxy(cx, armature);
    jsval retval;
    if (_jsCallback != JSVAL_VOID)
    {
        int movementEventType = (int)movementType;
        jsval movementVal = INT_TO_JSVAL(movementEventType);

        jsval idVal = std_string_to_jsval(cx, movementID);

        jsval valArr[3];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = movementVal;
        valArr[2] = idVal;

        JS_AddValueRoot(cx, valArr);
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
}

void JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc(float percent)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
    jsval retval;
    if (_jsCallback != JSVAL_VOID)
    {
        jsval percentVal = DOUBLE_TO_JSVAL(percent);

        JS_AddValueRoot(cx, &percentVal);
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JS_CallFunctionValue(cx, thisObj, _jsCallback, 1, &percentVal, &retval);
        JS_RemoveValueRoot(cx, &percentVal);
    }
}


void JSArmatureWrapper::frameCallbackFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
    js_proxy_t *proxy = js_get_or_create_proxy(cx, bone);
    jsval retval;
    if (_jsCallback != JSVAL_VOID)
    {
        jsval nameVal = std_string_to_jsval(cx, evt);
        jsval originIndexVal = INT_TO_JSVAL(originFrameIndex);
        jsval currentIndexVal = INT_TO_JSVAL(currentFrameIndex);

        jsval valArr[4];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = nameVal;
        valArr[2] = originIndexVal;
        valArr[3] = currentIndexVal;

        JS_AddValueRoot(cx, valArr);
        
        JS_CallFunctionValue(cx, thisObj, _jsCallback, 4, valArr, &retval);
        JS_RemoveValueRoot(cx, valArr);
    }
}

static JSBool js_cocos2dx_ArmatureAnimation_setMovementEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->setMovementEventCallFunc(CC_CALLBACK_0(JSArmatureWrapper::movementCallbackFunc, tmpObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        
        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool js_cocos2dx_ArmatureAnimation_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");

    if (argc == 2) {
        jsval *argv = JS_ARGV(cx, vp);

        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        cobj->setUserObject(tmpObj);
        tmpObj->release();

        tmpObj->setJSCallbackFunc(argv[0]);
        tmpObj->setJSCallbackThis(argv[1]);

        cobj->setFrameEventCallFunc(CC_CALLBACK_0(JSArmatureWrapper::frameCallbackFunc, tmpObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

        return JS_TRUE;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return JS_FALSE;
}

static JSBool jsb_Animation_addArmatureFileInfoAsyncCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
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

JSBool js_cocos2dx_studio_ColliderBody_getCalculatedVertexList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderBody* cobj = (cocostudio::ColliderBody *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        const std::vector<cocos2d::Point>& ret = cobj->getCalculatedVertexList();
        JSObject *jsretArr = JS_NewArrayObject(cx, 0, nullptr);
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        for(std::vector<cocos2d::Point>::const_iterator it = ret.begin(); it != ret.end(); it++)
        {
            const cocos2d::Point& point = *it;
            JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
            if (!tmp) break;
            JSBool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(point.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(point.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
            jsval jsTmp = OBJECT_TO_JSVAL(tmp);
            if(!ok || !JS_SetElement(cx, jsretArr, i, &jsTmp))
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

extern JSObject* jsb_cocostudio_ArmatureAnimation_prototype;
extern JSObject* jsb_cocostudio_ArmatureDataManager_prototype;
extern JSObject* jsb_cocostudio_ColliderBody_prototype;

void register_all_cocos2dx_studio_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_cocostudio_ColliderBody_prototype, "getCalculatedVertexList", js_cocos2dx_studio_ColliderBody_getCalculatedVertexList, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocostudio_ArmatureAnimation_prototype, "setMovementEventCallFunc", js_cocos2dx_ArmatureAnimation_setMovementEventCallFunc, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocostudio_ArmatureAnimation_prototype, "setFrameEventCallFunc", js_cocos2dx_ArmatureAnimation_setFrameEventCallFunc, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocostudio_ArmatureDataManager_prototype, "addArmatureFileInfoAsync", jsb_Animation_addArmatureFileInfoAsyncCallFunc, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}