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
        JS::RemoveValueRoot(cx, &_jsThisObj);
    }
}

void JSArmatureWrapper::setJSCallbackThis(jsval obj)
{
    JSCallbackWrapper::setJSCallbackThis(obj);

    JSObject *thisObj = obj.toObjectOrNull();
    js_proxy *p = jsb_get_js_proxy(thisObj);
    if (!p)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        m_bNeedUnroot = true;
        m_bNeedUnroot &= JS::AddValueRoot(cx, &_jsThisObj);
    }
}

void JSArmatureWrapper::movementCallbackFunc(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject thisObj(cx, _jsThisObj.toObjectOrNull());
    js_proxy_t *proxy = js_get_or_create_proxy(cx, armature);
    JS::RootedValue retval(cx);
    if (_jsCallback != JSVAL_VOID)
    {
        int movementEventType = (int)movementType;
        jsval movementVal = INT_TO_JSVAL(movementEventType);

        jsval idVal = std_string_to_jsval(cx, movementID);

        jsval valArr[3];
        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
        valArr[1] = movementVal;
        valArr[2] = idVal;

        //JS_AddValueRoot(cx, valArr);
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
            JS_CallFunctionValue(cx, thisObj, JS::RootedValue(cx, _jsCallback), JS::HandleValueArray::fromMarkedLocation(3, valArr), &retval);
        //JS_RemoveValueRoot(cx, valArr);
    }
}

void JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc(float percent)
{
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject thisObj(cx, _jsThisObj.toObjectOrNull());
    JS::RootedValue retval(cx);
    if (_jsCallback != JSVAL_VOID)
    {
        jsval percentVal = DOUBLE_TO_JSVAL(percent);

        //JS_AddValueRoot(cx, &percentVal);
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        JS_CallFunctionValue(cx, thisObj, JS::RootedValue(cx, _jsCallback), JS::HandleValueArray::fromMarkedLocation(1, &percentVal), &retval);
        //JS_RemoveValueRoot(cx, &percentVal);
    }
}


void JSArmatureWrapper::frameCallbackFunc(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject thisObj(cx, _jsThisObj.toObjectOrNull());
    js_proxy_t *proxy = js_get_or_create_proxy(cx, bone);
    JS::RootedValue retval(cx);
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

        //JS_AddValueRoot(cx, valArr);
        
        JS_CallFunctionValue(cx, thisObj, JS::RootedValue(cx, _jsCallback), JS::HandleValueArray::fromMarkedLocation(4, valArr), &retval);
        //JS_RemoveValueRoot(cx, valArr);
    }
}

static bool js_cocos2dx_ArmatureAnimation_setMovementEventCallFunc(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ArmatureAnimation* cobj = (cocostudio::ArmatureAnimation *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");

    if (argc > 0) {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        if (args.get(0).isNull()) {
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
            
            tmpObj->setJSCallbackFunc(args.get(0));
            if (argc == 1)
            {
                tmpObj->setJSCallbackThis(JSVAL_NULL);
            }
            else
            {
                tmpObj->setJSCallbackThis(args.get(1));
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
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        if (args.get(0).isNull()) {
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
            
            tmpObj->setJSCallbackFunc(args.get(0));
            if (argc == 1)
            {
                tmpObj->setJSCallbackThis(JSVAL_NULL);
            }
            else
            {
                tmpObj->setJSCallbackThis(args.get(1));
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
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();

        tmpObj->setJSCallbackFunc(args.get(1));
        tmpObj->setJSCallbackThis(args.get(2));

        std::string ret;
        jsval_to_std_string(cx, args.get(0), &ret);

        cobj->addArmatureFileInfoAsync(ret.c_str(), tmpObj, schedule_selector(JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc));

        return true;
    }

    if(argc == 5){
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        JSArmatureWrapper *tmpObj = new JSArmatureWrapper();
        tmpObj->autorelease();

        tmpObj->setJSCallbackFunc(args.get(3));
        tmpObj->setJSCallbackThis(args.get(4));

        std::string imagePath;
        jsval_to_std_string(cx ,args.get(0) , &imagePath);

        std::string plistPath;
        jsval_to_std_string(cx ,args.get(1) , &plistPath);

        std::string configFilePath;
        jsval_to_std_string(cx ,args.get(2) , &configFilePath);

        cobj->addArmatureFileInfoAsync(imagePath.c_str(), plistPath.c_str(), configFilePath.c_str(), tmpObj, schedule_selector(JSArmatureWrapper::addArmatureFileInfoAsyncCallbackFunc));

        return true;
    }
    JS_ReportError(cx, "Invalid number of arguments");
    return false;
}

static bool js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::ActionManagerEx* cobj = (cocostudio::ActionManagerEx *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : Invalid Native Object");
    if (argc == 3) {
        const char* arg0;
        const char* arg1;
        cocos2d::Ref* arg2;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        rapidjson::Document arg1Jsondoc;
        arg1Jsondoc.Parse<0>(arg1);
        if (arg1Jsondoc.HasParseError()) {
            CCLOG("GetParseError %d\n",arg1Jsondoc.GetParseError());
        }
        do {
            if (!args.get(2).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(2).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg2 = (cocos2d::Ref*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg2, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx : Error processing arguments");
        cobj->initWithDictionary(arg0, arg1Jsondoc, arg2);
        args.rval().setUndefined();
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
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        const std::vector<cocos2d::Point>& ret = cobj->getCalculatedVertexList();
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        JS::RootedObject tmp(cx);
        for(const auto& point : ret)
        {
            tmp = JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr());
            if (!tmp) break;
            bool ok = JS_DefineProperty(cx, tmp, "x", point.x, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&
                JS_DefineProperty(cx, tmp, "y", point.y, JSPROP_ENUMERATE | JSPROP_PERMANENT);
            JS::RootedValue jsTmp(cx, OBJECT_TO_JSVAL(tmp));
            if(!ok || !JS_SetElement(cx, jsretArr, i, jsTmp))
            {
                break;
            }
            ++i;
        }
        jsret = OBJECT_TO_JSVAL(jsretArr);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

static bool js_cocos2dx_studio_Frame_setEasingParams(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if(argc == 1)
    {
        JS::RootedObject jsobj(cx);
        bool ok = args.get(0).isObject() && JS_ValueToObject( cx, args.get(0), &jsobj );
        JSB_PRECONDITION3( ok, cx, false, "Error converting value to object");
        JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "argument must be an array");

        std::vector<float> arg0;
        uint32_t length = 0;
        ok &= JS_GetArrayLength(cx, jsobj, & length);
        arg0.reserve(length);

        for (uint32_t i = 0; i < length; ++i)
        {
            JS::RootedValue value(cx);
            if (JS_GetElement(cx, jsobj, i, &value))
            {
                arg0.push_back(value.toNumber());
            }
            else
            {
                ok = false;
                break;
            }
        }
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_setEasingParams : Error processing arguments");

        cobj->setEasingParams(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

static bool js_cocos2dx_studio_Frame_getEasingParams(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocostudio::timeline::Frame* cobj = (cocostudio::timeline::Frame *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if(argc == 0)
    {
        const std::vector<float> ret = cobj->getEasingParams();

        JS::RootedObject jsobj(cx, JS_NewArrayObject(cx, ret.size()));
        bool ok = true;
        for(size_t i = 0; i < ret.size(); ++i)
        {
            ok &= JS_SetElement(cx, jsobj, i, ret[i]);
        }
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_studio_Frame_getEasingParams : Error processing arguments");

        args.rval().set(OBJECT_TO_JSVAL(jsobj));
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
        cobj->x = (float)vp.get().toDouble();
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
        cobj->y = (float)vp.get().toDouble();
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
        cobj->y = (int)vp.get().toDouble();
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
        cobj->skewX = (float)vp.get().toDouble();
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
        cobj->skewY = (float)vp.get().toDouble();
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
        cobj->scaleX = (float)vp.get().toDouble();
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
        cobj->scaleY = (float)vp.get().toDouble();
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
        cobj->tweenRotate = (float)vp.get().toDouble();
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
        cobj->isUseColorInfo = vp.get().toBoolean();
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
        cobj->a = vp.get().toInt32();
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
        cobj->r = vp.get().toInt32();
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
        cobj->g = vp.get().toInt32();
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
        cobj->b = vp.get().toInt32();
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
        bool ok = jsval_to_std_string(cx, JS::RootedValue(cx, vp.get()), &name);
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
        bool ok = jsval_to_std_vector_string(cx, JS::RootedValue(cx, vp.get()), &movementNames);
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
        JS::RootedObject jsRet(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        
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
        if (vp.isNullOrUndefined())
        {
            return true;
        }
        JS::RootedObject tmp(cx, vp.toObjectOrNull());
        JSB_PRECONDITION2(tmp, cx, false, "js_set_AnimationData_movementDataDic: the js value is not an object.");

        cocos2d::Map<std::string, cocostudio::MovementData*> dict;
        
        JS::RootedObject it(cx, JS_NewPropertyIterator(cx, tmp));
        while (true)
        {
            JS::RootedId idp(cx);
            JS::RootedValue key(cx);
            if (! JS_NextProperty(cx, it, idp.address()) || ! JS_IdToValue(cx, idp, &key)) {
                CCLOGERROR("js_set_AnimationData_movementDataDic : Error processing arguments.");
                return false; // error
            }
            if (key == JSVAL_VOID) {
                break; // end of iteration
            }
            if (!key.isString()) {
                continue; // ignore integer properties
            }
            
            JSStringWrapper keyWrapper(key.toString(), cx);
            
            JS::RootedValue value(cx);
            JS_GetPropertyById(cx, tmp, idp, &value);
            cocostudio::MovementData* movementData;
            bool ok = true;
            do {
                if (!value.isObject()) { ok = false; break; }
                js_proxy_t *jsProxy;
                JSObject *tmpObj = value.toObjectOrNull();
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
        bool ok = jsval_to_std_string(cx, JS::RootedValue(cx, vp.get()), &name);
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
        cobj->duration = vp.get().toInt32();
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
        cobj->scale = (float)vp.get().toDouble();
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
        cobj->durationTo = vp.get().toInt32();
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
        cobj->durationTween = vp.get().toInt32();
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
        cobj->loop = vp.get().toBoolean();
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
        cobj->tweenEasing = (cocos2d::tweenfunc::TweenType)vp.get().toInt32();
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
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        for(const auto& vec2 : ret)
        {
            JS::RootedValue arrElement(cx);
            arrElement = vector2_to_jsval(cx, vec2);
            
            if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
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
        jsListObj = vp.get().toObjectOrNull();
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
        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
        jsval jsret;
        //CCObject* obj;
        int i = 0;
        for(const auto& contourData : ret)
        {
            JS::RootedValue arrElement(cx);
            js_proxy_t *jsProxy = js_get_or_create_proxy<cocostudio::ContourData>(cx, (cocostudio::ContourData*)contourData);
            arrElement = OBJECT_TO_JSVAL(jsProxy->obj);
            
            if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
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
        jsListObj = vp.get().toObjectOrNull();
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
                    JSObject *tmpObj = value.toObjectOrNull();
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
        cobj->width = (float)(vp.get().toNumber());
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
        cobj->height = (float)vp.get().toNumber();
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
        cobj->pivotX = (float)vp.get().toNumber();
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
        cobj->pivotY = (float)vp.get().toNumber();
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
        bool ok = jsval_to_std_string(cx, JS::RootedValue(cx, vp.get()), &name);
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
extern JSObject* jsb_cocostudio_timeline_Frame_prototype;

void register_all_cocos2dx_studio_manual(JSContext* cx, JS::HandleObject global)
{
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocostudio_ColliderBody_prototype), "getCalculatedVertexList", js_cocos2dx_studio_ColliderBody_getCalculatedVertexList, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocostudio_ArmatureAnimation_prototype), "setMovementEventCallFunc", js_cocos2dx_ArmatureAnimation_setMovementEventCallFunc, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocostudio_ArmatureAnimation_prototype), "setFrameEventCallFunc", js_cocos2dx_ArmatureAnimation_setFrameEventCallFunc, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocostudio_ArmatureDataManager_prototype), "addArmatureFileInfoAsync", jsb_Animation_addArmatureFileInfoAsyncCallFunc, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
   
    JS_DefineFunction(cx, JS::RootedObject(cx, jsb_cocostudio_ActionManagerEx_prototype), "initWithDictionaryEx", js_cocos2dx_studio_ActionManagerEx_initWithDictionaryEx, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    JS::RootedObject frame(cx, jsb_cocostudio_timeline_Frame_prototype);
    JS_DefineFunction(cx, frame, "setEasingParams", js_cocos2dx_studio_Frame_setEasingParams, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE);
    JS_DefineFunction(cx, frame, "getEasingParams", js_cocos2dx_studio_Frame_getEasingParams, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE);

    JS::RootedObject baseData(cx, jsb_cocostudio_BaseData_prototype);
    JS_DefineProperty(cx, baseData, "x", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_x, js_set_BaseData_x);
    JS_DefineProperty(cx, baseData, "y", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_y, js_set_BaseData_y); 
    JS_DefineProperty(cx, baseData, "zOrder", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_zOrder, js_set_BaseData_zOrder); 
    JS_DefineProperty(cx, baseData, "skewX", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_skewX, js_set_BaseData_skewX); 
    JS_DefineProperty(cx, baseData, "skewY", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_skewY, js_set_BaseData_skewY); 
    JS_DefineProperty(cx, baseData, "scaleX", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_scaleX, js_set_BaseData_scaleX); 
    JS_DefineProperty(cx, baseData, "scaleY", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_scaleY, js_set_BaseData_scaleY); 
    JS_DefineProperty(cx, baseData, "tweenRotate", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_tweenRotate, js_set_BaseData_tweenRotate); 
    JS_DefineProperty(cx, baseData, "isUseColorInfo", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_isUseColorInfo, js_set_BaseData_isUseColorInfo); 
    JS_DefineProperty(cx, baseData, "a", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_a, js_set_BaseData_a);
    JS_DefineProperty(cx, baseData, "r", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_r, js_set_BaseData_r);
    JS_DefineProperty(cx, baseData, "g", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_g, js_set_BaseData_g);
    JS_DefineProperty(cx, baseData, "b", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_BaseData_b, js_set_BaseData_b); 

    
    JS::RootedObject animationData(cx, jsb_cocostudio_AnimationData_prototype);
    JS_DefineProperty(cx, animationData, "name", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_AnimationData_name, js_set_AnimationData_name);
    JS_DefineProperty(cx, animationData, "movementNames", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_AnimationData_movementNames, js_set_AnimationData_movementNames);
    JS_DefineProperty(cx, animationData, "movementDataDic", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_AnimationData_movementDataDic, js_set_AnimationData_movementDataDic);

    JS::RootedObject movementData(cx, jsb_cocostudio_MovementData_prototype);
    JS_DefineProperty(cx, movementData, "name", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_name, js_set_MovementData_name);
    JS_DefineProperty(cx, movementData, "duration", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_duration, js_set_MovementData_duration);
    JS_DefineProperty(cx, movementData, "scale", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_scale, js_set_MovementData_scale);
    JS_DefineProperty(cx, movementData, "durationTo", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_durationTo, js_set_MovementData_durationTo);
    JS_DefineProperty(cx, movementData, "durationTween", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_durationTween, js_set_MovementData_durationTween);
    JS_DefineProperty(cx, movementData, "loop", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_loop, js_set_MovementData_loop);
    JS_DefineProperty(cx, movementData, "tweenEasing", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_MovementData_tweenEasing, js_set_MovementData_tweenEasing);

    JS_DefineProperty(cx, JS::RootedObject(cx, jsb_cocostudio_ContourData_prototype), "vertextList", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_ContourData_vertexList, js_set_ContourData_vertexList);
    
    JS::RootedObject textureData(cx, jsb_cocostudio_TextureData_prototype);
    JS_DefineProperty(cx, textureData, "contourDataList", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_TextureData_contourDataList, js_set_TextureData_contourDataList);
    JS_DefineProperty(cx, textureData, "name", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_TextureData_name, js_set_TextureData_name);
    JS_DefineProperty(cx, textureData, "width", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_TextureData_width, js_set_TextureData_width);
    JS_DefineProperty(cx, textureData, "height", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_TextureData_height, js_set_TextureData_height);
    JS_DefineProperty(cx, textureData, "pivotX", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_TextureData_pivotX, js_set_TextureData_pivotX);
    JS_DefineProperty(cx, textureData, "pivotY", JS::UndefinedHandleValue, JSPROP_ENUMERATE | JSPROP_PERMANENT | JSPROP_SHARED, js_get_TextureData_pivotY, js_set_TextureData_pivotY);

}
