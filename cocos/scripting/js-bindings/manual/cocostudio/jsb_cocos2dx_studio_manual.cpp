/*
 * Created by LinWenhai on 20/10/13.
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
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS_RemoveValueRoot(cx, &_jsThisObj);
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
        m_bNeedUnroot = true;
        m_bNeedUnroot &= JS_AddValueRoot(cx, &_jsThisObj);
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

static bool js_cocos2dx_ArmatureAnimation_setMovementEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc > 0) {
        jsval *argv = JS_ARGV(cx, vp);
        
        if (JSVAL_IS_NULL(argv[0])) {
            cobj->setMovementEventCallFunc(nullptr);
            
            return true;
        }
        else if (argc == 1 || argc == 2) {
            JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
            tmpObj->autorelease();
            
            cocos2d::__Dictionary* dict = static_cast<cocos2d::__Dictionary*>(cobj->getUserObject());
            if (nullptr == dict)
            {
                dict = cocos2d::__Dictionary::create();
                cobj->setUserObject(dict);
            }
            dict->setObject(tmpObj, "moveEvent");
            
            tmpObj->setJSCallbackFunc(argv[0]);
            if (argc == 1)
            {
                tmpObj->setJSCallbackThis(JSVAL_NULL);
            }
            else
            {
                tmpObj->setJSCallbackThis(argv[1]);
            }
            
            cobj->setMovementEventCallFunc(CC_CALLBACK_0(JSArmatureWrapper::movementCallbackFunc, tmpObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
            
            return true;
        }
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

static bool js_cocos2dx_ArmatureAnimation_setFrameEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc > 0) {
        jsval *argv = JS_ARGV(cx, vp);
        
        if (JSVAL_IS_NULL(argv[0])) {
            cobj->setFrameEventCallFunc(nullptr);
            
            return true;
        }
        else if (argc == 1 || argc == 2) {
            JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
            tmpObj->autorelease();
            
            cocos2d::__Dictionary* dict = static_cast<cocos2d::__Dictionary*>(cobj->getUserObject());
            if (nullptr == dict)
            {
                dict = cocos2d::__Dictionary::create();
                cobj->setUserObject(dict);
            }
            dict->setObject(tmpObj, "frameEvent");
            
            tmpObj->setJSCallbackFunc(argv[0]);
            if (argc == 1)
            {
                tmpObj->setJSCallbackThis(JSVAL_NULL);
            }
            else
            {
                tmpObj->setJSCallbackThis(argv[1]);
            }
            
            cobj->setFrameEventCallFunc(CC_CALLBACK_0(JSArmatureWrapper::frameCallbackFunc, tmpObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
            
            return true;
        }
    }
    
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

static bool jsb_Animation_addArmatureFileInfoAsyncCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureDataManager* cobj = (cocostudio::ArmatureDataManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc == 3) {
        jsval *argv = JS_ARGV(cx, vp);

        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();

        tmpObj->setJSCallbackFunc(argv[1]);
        tmpObj->setJSCallbackThis(argv[2]);

        std::string ret;
        jsval_to_std_string(cx, argv[0], &ret);

        cobj->addArmatureFileInfoAsync(ret.c_str(), tmpObj, schedule_selector(JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc));

        return true;
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

        return true;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

static bool js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : Invalid Native Object");
    if (argc == 3) {
        const char* arg0;
        const char* arg1;
        cocos2d::Ref* arg2;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        rapidjson::Document arg1Jsondoc;
        arg1Jsondoc.Parse<0>(arg1);
        if (arg1Jsondoc.HasParseError()) {
            CCLOG("GetParseError %s\n",arg1Jsondoc.GetParseError());
        }
        do {
            if (!argv[2].isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = JSVAL_TO_OBJECT(argv[2]);
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : Error processing arguments");
        cobj->initWithDictionary(arg0, arg1Jsondoc, arg2);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

bool js_cocos2dx_studio_ColliderBody_getCalculatedVertexList(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ColliderBody* cobj = (cocostudio::ColliderBody *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 0) {
        const std::vector<cocos2d::Point>& ret = cobj->getCalculatedVertexList();
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0, nullptr));
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        for(const auto& point : ret)
        {
            JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
            if (!tmp) break;
            bool ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(point.x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(point.y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
            JS::RootedValue jsTmp(cx, OBJECT_TO_JSVAL(tmp));
            if(!ok || !JS_SetElement(cx, jsretArr, i, &jsTmp))
            {
                break;
            }
            ++i;
        }
        jsret = OBJECT_TO_JSVAL(jsretArr);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

// BaseData Properties

bool js_get_BaseData_x(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->x);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_x : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_x : Invalid native object.");
    return false;
}
bool js_set_BaseData_x(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->x = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_x : Invalid native object.");
    return false;
}

bool js_get_BaseData_y(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->y);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_y : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_y : Invalid native object.");
    return false;
}
bool js_set_BaseData_y(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->y = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_y : Invalid native object.");
    return false;
}

bool js_get_BaseData_zOrder(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->zOrder);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_zOrder : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_zOrder : Invalid native object.");
    return false;
}
bool js_set_BaseData_zOrder(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->y = (int)JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_zOrder : Invalid native object.");
    return false;
}

bool js_get_BaseData_skewX(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->skewX);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_skewX : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_skewX : Invalid native object.");
    return false;
}
bool js_set_BaseData_skewX(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->skewX = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_skewX : Invalid native object.");
    return false;
}

bool js_get_BaseData_skewY(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->skewY);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_skewY : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_skewY : Invalid native object.");
    return false;
}
bool js_set_BaseData_skewY(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->skewY = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_skewY : Invalid native object.");
    return false;
}

bool js_get_BaseData_scaleX(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->scaleX);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_scaleX : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_scaleX : Invalid native object.");
    return false;
}
bool js_set_BaseData_scaleX(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->scaleX = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_scaleX : Invalid native object.");
    return false;
}

bool js_get_BaseData_scaleY(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->scaleY);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_scaleY : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_scaleY : Invalid native object.");
    return false;
}
bool js_set_BaseData_scaleY(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->scaleY = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_scaleY : Invalid native object.");
    return false;
}

bool js_get_BaseData_tweenRotate(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->tweenRotate);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_tweenRotate : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_tweenRotate : Invalid native object.");
    return false;
}
bool js_set_BaseData_tweenRotate(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->tweenRotate = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_tweenRotate : Invalid native object.");
    return false;
}

bool js_get_BaseData_isUseColorInfo(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = BOOLEAN_TO_JSVAL(cobj->isUseColorInfo);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_isUseColorInfo : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_isUseColorInfo : Invalid native object.");
    return false;
}
bool js_set_BaseData_isUseColorInfo(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->isUseColorInfo = JSVAL_TO_BOOLEAN(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_isUseColorInfo : Invalid native object.");
    return false;
}

bool js_get_BaseData_a(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->a);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_a : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_a : Invalid native object.");
    return false;
}
bool js_set_BaseData_a(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->a = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_a : Invalid native object.");
    return false;
}

bool js_get_BaseData_r(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->r);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_r : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_r : Invalid native object.");
    return false;
}
bool js_set_BaseData_r(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->r = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_r : Invalid native object.");
    return false;
}

bool js_get_BaseData_g(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->g);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_g : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_g : Invalid native object.");
    return false;
}
bool js_set_BaseData_g(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->g = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_g : Invalid native object.");
    return false;
}

bool js_get_BaseData_b(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->b);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_BaseData_b : Fail to retrieve property from BaseData.");
        return false;
    }
    JS_ReportError(cx, "js_get_BaseData_b : Invalid native object.");
    return false;
}
bool js_set_BaseData_b(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::BaseData* cobj = (cocostudio::BaseData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->b = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_BaseData_b : Invalid native object.");
    return false;
}

// AnimationData Properties

bool js_get_AnimationData_name(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = std_string_to_jsval(cx, cobj->name);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_AnimationData_name : Fail to retrieve property name of AnimationData.");
        return false;
    }
    JS_ReportError(cx, "js_get_AnimationData_name : Invalid native object.");
    return false;
}
bool js_set_AnimationData_name(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData*)JS_GetPrivate(obj);
    if (cobj) {
        std::string name;
        bool ok = jsval_to_std_string(cx, vp.get(), &name);
        JSB_PRECONDITION2(ok, cx, false, "js_set_AnimationData_name : Error processing arguments");
        cobj->name = name;
        return true;
    }
    JS_ReportError(cx, "js_set_AnimationData_name : Invalid native object.");
    return false;
}

bool js_get_AnimationData_movementNames(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = std_vector_string_to_jsval(cx, cobj->movementNames);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_AnimationData_movementNames : Fail to retrieve property movementNames of AnimationData.");
        return false;
    }
    JS_ReportError(cx, "js_get_AnimationData_movementNames : Invalid native object.");
    return false;
}
bool js_set_AnimationData_movementNames(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData*)JS_GetPrivate(obj);
    if (cobj) {
        std::vector<std::string> movementNames;
        bool ok = jsval_to_std_vector_string(cx, vp.get(), &movementNames);
        JSB_PRECONDITION2(ok, cx, false, "js_set_AnimationData_movementNames : Error processing arguments.");
        cobj->movementNames.clear();
        cobj->movementNames = movementNames;
        return true;
    }
    JS_ReportError(cx, "js_set_AnimationData_movementNames : Invalid native object.");
    return false;
}

bool js_get_AnimationData_movementDataDic(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData*)JS_GetPrivate(obj);
    if (cobj) {
        cocos2d::Map<std::string, cocostudio::MovementData*> dic = cobj->movementDataDic;
        JSObject* jsRet = JS_NewObject(cx, NULL, NULL, NULL);
        
        for (auto iter = dic.begin(); iter != dic.end(); ++iter)
        {
            JS::RootedValue dictElement(cx);
            
            std::string key = iter->first;
            cocostudio::MovementData* movementData = iter->second;
            do {
                if (movementData) {
                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::MovementData>(cx, (cocostudio::MovementData*)movementData);
                    dictElement = OBJECT_TO_JSVAL(jsProxy->obj);
                } else {
                    CCLOGERROR("js_get_AnimationData_movementDataDic : Fail to retrieve property movementDataDic of AnimationData.");
                    return false;
                }
            } while (0);
            
            if (!key.empty())
            {
                JS_SetProperty(cx, jsRet, key.c_str(), dictElement);
            }
        }
        jsval ret = OBJECT_TO_JSVAL(jsRet);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_AnimationData_movementDataDic : Fail to retrieve property movementDataDic of AnimationData.");
        return false;
    }
    JS_ReportError(cx, "js_get_AnimationData_movementDataDic : Invalid native object.");
    return false;
}
bool js_set_AnimationData_movementDataDic(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::AnimationData* cobj = (cocostudio::AnimationData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval val = vp.get();
        if (JSVAL_IS_NULL(val) || JSVAL_IS_VOID(val))
        {
            return true;
        }
        JSObject* tmp = JSVAL_TO_OBJECT(val);
        JSB_PRECONDITION2(tmp, cx, false, "js_set_AnimationData_movementDataDic: the js value is not an object.");

        cocos2d::Map<std::string, cocostudio::MovementData*> dict;
        
        JSObject* it = JS_NewPropertyIterator(cx, tmp);
        while (true)
        {
            jsid idp;
            jsval key;
            if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
                CCLOGERROR("js_set_AnimationData_movementDataDic : Error processing arguments.");
                return false; // error
            }
            if (key == JSVAL_VOID) {
                break; // end of iteration
            }
            if (!JSVAL_IS_STRING(key)) {
                continue; // ignore integer properties
            }
            
            JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);
            
            JS::RootedValue value(cx);
            JS_GetPropertyById(cx, tmp, idp, &value);
            cocostudio::MovementData* movementData;
            bool ok = true;
            do {
                if (!value.isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = JSVAL_TO_OBJECT(value);
                jsProxy = jsb_get_js_proxy(tmpObj);
                movementData = (cocostudio::MovementData*)(jsProxy ? jsProxy->ptr : NULL);
                JSB_PRECONDITION2(movementData, cx, false, "js_set_AnimationData_movementDataDic : Invalid Native Object.");
            } while (0);
            JSB_PRECONDITION2(ok, cx, false, "js_set_AnimationData_movementDataDic : Error processing arguments.");
        }
        
        cobj->movementDataDic.clear();
        cobj->movementDataDic = dict;
        return true;
    }
    JS_ReportError(cx, "js_set_AnimationData_movementDataDic : Invalid native object.");
    return false;
}

// MovementData properties

bool js_get_MovementData_name(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = std_string_to_jsval(cx, cobj->name);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_name : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_name : Invalid native object.");
    return false;
}
bool js_set_MovementData_name(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        std::string name;
        bool ok = jsval_to_std_string(cx, vp.get(), &name);
        JSB_PRECONDITION2(ok, cx, false, "js_set_MovementData_name : Error processing arguments");
        cobj->name = name;
        return true;
    }
    JS_ReportError(cx, "js_set_MovementData_name : Invalid native object.");
    return false;
}

bool js_get_MovementData_duration(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->duration);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_duration : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_duration : Invalid native object.");
    return false;
}
bool js_set_MovementData_duration(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->duration = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_MovementData_duration : Invalid native object.");
    return false;
}

bool js_get_MovementData_scale(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->scale);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_scale : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_scale : Invalid native object.");
    return false;
}
bool js_set_MovementData_scale(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->scale = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_MovementData_scale : Invalid native object.");
    return false;
}

bool js_get_MovementData_durationTo(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->durationTo);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_durationTo : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_durationTo : Invalid native object.");
    return false;
}
bool js_set_MovementData_durationTo(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->durationTo = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_MovementData_durationTo : Invalid native object.");
    return false;
}

bool js_get_MovementData_durationTween(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->durationTween);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_durationTween : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_durationTween : Invalid native object.");
    return false;
}
bool js_set_MovementData_durationTween(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->durationTween = JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_MovementData_durationTween : Invalid native object.");
    return false;
}

bool js_get_MovementData_loop(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = BOOLEAN_TO_JSVAL(cobj->loop);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_loop : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_loop : Invalid native object.");
    return false;
}
bool js_set_MovementData_loop(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->loop = JSVAL_TO_BOOLEAN(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_get_MovementData_loop : Invalid native object.");
    return false;
}

bool js_get_MovementData_tweenEasing(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        jsval ret = INT_TO_JSVAL(cobj->tweenEasing);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_MovementData_tweenEasing : Fail to retrieve property from MovementData.");
        return false;
    }
    JS_ReportError(cx, "js_get_MovementData_tweenEasing : Invalid native object.");
    return false;
}
bool js_set_MovementData_tweenEasing(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp) {
    cocostudio::MovementData* cobj = (cocostudio::MovementData*)JS_GetPrivate(obj);
    if (cobj) {
        cobj->tweenEasing = (cocos2d::tweenfunc::TweenType)JSVAL_TO_INT(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_MovementData_tweenEasing : Invalid native object.");
    return false;
}

// ContourData properties

bool js_get_ContourData_vertexList(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::ContourData* cobj = (cocostudio::ContourData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        const std::vector<cocos2d::Vec2>& ret = cobj->vertexList;
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0, nullptr));
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        for(const auto& vec2 : ret)
        {
            JS::RootedValue arrElement(cx);
            arrElement = vector2_to_jsval(cx, vec2);
            
            if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
                break;
            }
            ++i;
        }
        jsret = OBJECT_TO_JSVAL(jsretArr);
        if (jsret != JSVAL_NULL)
        {
            vp.set(jsret);
            return true;
        }
        CCLOGERROR("js_get_ContourData_vertexList : Fail to retrieve property from ContourData.");
        return false;
    }
    JS_ReportError(cx, "js_get_ContourData_vertexList : Invalid native object.");
    return false;
}
bool js_set_ContourData_vertexList(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::ContourData* cobj = (cocostudio::ContourData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        JS::RootedObject jsListObj(cx);
        jsListObj = JSVAL_TO_OBJECT(vp.get());
        JSB_PRECONDITION3(jsListObj && JS_IsArrayObject(cx, jsListObj),  cx, false, "Object must be an array");
        
        std::vector<cocos2d::Vec2> list;
        uint32_t len = 0;
        JS_GetArrayLength(cx, jsListObj, &len);
        bool ok;
        
        for (uint32_t i=0; i < len; i++)
        {
            JS::RootedValue value(cx);
            if (JS_GetElement(cx, jsListObj, i, &value))
            {
                cocos2d::Vec2 vec2;
                ok = jsval_to_vector2(cx, value, &vec2);
                if (ok)
                {
                    list.push_back(vec2);
                }
            }
        }
        
        cobj->vertexList = list;
        return true;
    }
    JS_ReportError(cx, "js_set_ContourData_vertexList : Invalid native object.");
    return false;
}

// TextureData properties

bool js_get_TextureData_contourDataList(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        const cocos2d::Vector<cocostudio::ContourData *>& ret = cobj->contourDataList;
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0, nullptr));
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        for(const auto& contourData : ret)
        {
            JS::RootedValue arrElement(cx);
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ContourData>(cx, (cocostudio::ContourData*)contourData);
            arrElement = OBJECT_TO_JSVAL(jsProxy->obj);
            
            if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
                break;
            }
            ++i;
        }
        jsret = OBJECT_TO_JSVAL(jsretArr);
        if (jsret != JSVAL_NULL)
        {
            vp.set(jsret);
            return true;
        }
        CCLOGERROR("js_get_TextureData_contourDataList : Fail to retrieve property from TextureData.");
        return false;
    }
    JS_ReportError(cx, "js_get_TextureData_contourDataList : Invalid native object.");
    return false;
}
bool js_set_TextureData_contourDataList(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        JS::RootedObject jsListObj(cx);
        jsListObj = JSVAL_TO_OBJECT(vp.get());
        JSB_PRECONDITION3(jsListObj && JS_IsArrayObject(cx, jsListObj),  cx, false, "Object must be an array");
        
        cocos2d::Vector<cocostudio::ContourData *> list;
        uint32_t len = 0;
        JS_GetArrayLength(cx, jsListObj, &len);
        bool ok;
        
        for (uint32_t i=0; i < len; i++)
        {
            JS::RootedValue value(cx);
            if (JS_GetElement(cx, jsListObj, i, &value))
            {
                cocostudio::ContourData* contourData;
                do {
                    if (!value.isObject()) { ok = false; break; }
                    js_proxy_t *jsProxy;
                    JSObject *tmpObj = JSVAL_TO_OBJECT(value);
                    jsProxy = jsb_get_js_proxy(tmpObj);
                    contourData = (cocostudio::ContourData*)(jsProxy ? jsProxy->ptr : NULL);
                    JSB_PRECONDITION2(contourData, cx, false, "Invalid Native Object");
                } while (0);
                JSB_PRECONDITION2(ok, cx, false, "js_set_TextureData_contourDataList : Error processing arguments");
                
                list.pushBack(contourData);
            }
        }
        
        cobj->contourDataList = list;
        return true;
    }
    JS_ReportError(cx, "js_set_TextureData_contourDataList : Invalid native object.");
    return false;
}

bool js_get_TextureData_width(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    
    //struct jsb_c_proxy_s *proxy = jsb_get_c_proxy_for_jsobject(obj);
    //cocostudio::TextureData* cobj = (cocostudio::TextureData*)proxy->handle;
    
    //jsval argv;
    //cocostudio::TextureData* cobj = (cocostudio::TextureData*)JS_GetInstancePrivate(cx, obj.get(), jsb_cocostudio_TextureData_class, &argv);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->width);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_TextureData_width : Fail to retrieve property from TextureData.");
        return false;
    }
    JS_ReportError(cx, "js_get_TextureData_width : Invalid native object.");
    return false;
}
bool js_set_TextureData_width(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        cobj->width = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_TextureData_width : Invalid native object.");
    return false;
}

bool js_get_TextureData_height(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->height);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_TextureData_height : Fail to retrieve property from TextureData.");
        return false;
    }
    JS_ReportError(cx, "js_get_TextureData_height : Invalid native object.");
    return false;
}
bool js_set_TextureData_height(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        cobj->height = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_TextureData_height : Invalid native object.");
    return false;
}

bool js_get_TextureData_pivotX(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->pivotX);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_TextureData_pivotX : Fail to retrieve property from TextureData.");
        return false;
    }
    JS_ReportError(cx, "js_get_TextureData_pivotX : Invalid native object.");
    return false;
}
bool js_set_TextureData_pivotX(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        cobj->pivotX = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_TextureData_pivotX : Invalid native object.");
    return false;
}

bool js_get_TextureData_pivotY(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        jsval ret = DOUBLE_TO_JSVAL(cobj->pivotY);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_TextureData_pivotY : Fail to retrieve property from TextureData.");
        return false;
    }
    JS_ReportError(cx, "js_get_TextureData_pivotY : Invalid native object.");
    return false;
}
bool js_set_TextureData_pivotY(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        cobj->pivotY = (float)JSVAL_TO_DOUBLE(vp.get());
        return true;
    }
    JS_ReportError(cx, "js_set_TextureData_pivotY : Invalid native object.");
    return false;
}

bool js_get_TextureData_name(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        jsval ret = std_string_to_jsval(cx, cobj->name);
        
        if (ret != JSVAL_NULL)
        {
            vp.set(ret);
            return true;
        }
        CCLOGERROR("js_get_TextureData_name : Fail to retrieve property name of TextureData.");
        return false;
    }
    JS_ReportError(cx, "js_get_TextureData_name : Invalid native object.");
    return false;
}
bool js_set_TextureData_name(JSContext *cx, JS::HandleObject obj, JS::HandleId id, bool strict, JS::MutableHandleValue vp)
{
    JSObject* jsobj = obj.get();
    js_proxy_t *proxy = jsb_get_js_proxy(jsobj);
    cocostudio::TextureData* cobj = (cocostudio::TextureData*)(proxy ? proxy->ptr : NULL);
    if (cobj) {
        std::string name;
        bool ok = jsval_to_std_string(cx, vp.get(), &name);
        JSB_PRECONDITION2(ok, cx, false, "js_set_TextureData_name : Error processing arguments");
        cobj->name = name;
        return true;
    }
    JS_ReportError(cx, "js_set_TextureData_name : Invalid native object.");
    return false;
}


extern JSObject* jsb_cocostudio_ArmatureAnimation_prototype;
extern JSObject* jsb_cocostudio_ArmatureDataManager_prototype;
extern JSObject* jsb_cocostudio_ColliderBody_prototype;
extern JSObject* jsb_cocostudio_BaseData_prototype;
extern JSObject* jsb_cocostudio_AnimationData_prototype;
extern JSObject* jsb_cocostudio_MovementData_prototype;
extern JSObject* jsb_cocostudio_ActionManagerEx_prototype;
extern JSObject* jsb_cocostudio_ContourData_prototype;
extern JSObject* jsb_cocostudio_TextureData_prototype;

void register_all_cocos2dx_studio_manual(JSContext* cx, JSObject* global)
{
    JS_DefineFunction(cx, jsb_cocostudio_ColliderBody_prototype, "getCalculatedVertexList", js_cocos2dx_studio_ColliderBody_getCalculatedVertexList, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocostudio_ArmatureAnimation_prototype, "setMovementEventCallFunc", js_cocos2dx_ArmatureAnimation_setMovementEventCallFunc, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocostudio_ArmatureAnimation_prototype, "setFrameEventCallFunc", js_cocos2dx_ArmatureAnimation_setFrameEventCallFunc, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, jsb_cocostudio_ArmatureDataManager_prototype, "addArmatureFileInfoAsync", jsb_Animation_addArmatureFileInfoAsyncCallFunc, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, jsb_cocostudio_ActionManagerEx_prototype, "initWithDictionaryEx", js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    static JSPropertySpec baseDataProps[] = {
        {"x", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_x), JSOP_WRAPPER(js_set_BaseData_x)},
        {"y", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_y), JSOP_WRAPPER(js_set_BaseData_y)},
        {"zOrder", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_zOrder), JSOP_WRAPPER(js_set_BaseData_zOrder)},
        {"skewX", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_skewX), JSOP_WRAPPER(js_set_BaseData_skewX)},
        {"skewY", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_skewY), JSOP_WRAPPER(js_set_BaseData_skewY)},
        {"scaleX", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_scaleX), JSOP_WRAPPER(js_set_BaseData_scaleX)},
        {"scaleY", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_scaleY), JSOP_WRAPPER(js_set_BaseData_scaleY)},
        {"tweenRotate", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_tweenRotate), JSOP_WRAPPER(js_set_BaseData_tweenRotate)},
        {"isUseColorInfo", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_isUseColorInfo), JSOP_WRAPPER(js_set_BaseData_isUseColorInfo)},
        {"a", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_a), JSOP_WRAPPER(js_set_BaseData_a)},
        {"r", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_r), JSOP_WRAPPER(js_set_BaseData_r)},
        {"g", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_g), JSOP_WRAPPER(js_set_BaseData_g)},
        {"b", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_BaseData_b), JSOP_WRAPPER(js_set_BaseData_b)},
        {0, 0, 0, 0, 0}
    };
    JS_DefineProperties(cx, jsb_cocostudio_BaseData_prototype, baseDataProps);
    
    static JSPropertySpec animationDataProps[] = {
        {"name", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_AnimationData_name), JSOP_WRAPPER(js_set_AnimationData_name)},
        {"movementNames", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_AnimationData_movementNames), JSOP_WRAPPER(js_set_AnimationData_movementNames)},
        {"movementDataDic", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_AnimationData_movementDataDic), JSOP_WRAPPER(js_set_AnimationData_movementDataDic)},
        {0, 0, 0, 0, 0}
    };
    JS_DefineProperties(cx, jsb_cocostudio_AnimationData_prototype, animationDataProps);
    
    static JSPropertySpec movementDataProps[] = {
        {"name", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_name), JSOP_WRAPPER(js_set_MovementData_name)},
        {"duration", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_duration), JSOP_WRAPPER(js_set_MovementData_duration)},
        {"scale", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_scale), JSOP_WRAPPER(js_set_MovementData_scale)},
        {"durationTo", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_durationTo), JSOP_WRAPPER(js_set_MovementData_durationTo)},
        {"durationTween", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_durationTween), JSOP_WRAPPER(js_set_MovementData_durationTween)},
        {"loop", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_loop), JSOP_WRAPPER(js_set_MovementData_loop)},
        {"tweenEasing", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_MovementData_tweenEasing), JSOP_WRAPPER(js_set_MovementData_tweenEasing)},
        {0, 0, 0, 0, 0}
    };
    JS_DefineProperties(cx, jsb_cocostudio_AnimationData_prototype, movementDataProps);
    
    static JSPropertySpec contourDataProps[] = {
        {"vertexList", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_ContourData_vertexList), JSOP_WRAPPER(js_set_ContourData_vertexList)},
        {0, 0, 0, 0, 0}
    };
    JS_DefineProperties(cx, jsb_cocostudio_ContourData_prototype, contourDataProps);
    
    static JSPropertySpec textureDataProps[] = {
        {"contourDataList", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_TextureData_contourDataList), JSOP_WRAPPER(js_set_TextureData_contourDataList)},
        {"name", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_TextureData_name), JSOP_WRAPPER(js_set_TextureData_name)},
        {"width", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_TextureData_width), JSOP_WRAPPER(js_set_TextureData_width)},
        {"height", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_TextureData_height), JSOP_WRAPPER(js_set_TextureData_height)},
        {"pivotX", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_TextureData_pivotX), JSOP_WRAPPER(js_set_TextureData_pivotX)},
        {"pivotY", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, JSOP_WRAPPER(js_get_TextureData_pivotY), JSOP_WRAPPER(js_set_TextureData_pivotY)},
        {0, 0, 0, 0, 0}
    };
    JS_DefineProperties(cx, jsb_cocostudio_TextureData_prototype, textureDataProps);
    
}