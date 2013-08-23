/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __PLUGIN_UTILS_H__
#define __PLUGIN_UTILS_H__

#include "PluginJniHelper.h"
#include "PluginJavaData.h"
#include <map>
#include "PluginParam.h"
#include "PluginJniMacros.h"
#include <android_native_app_glue.h>

namespace cocos2d { namespace plugin {

class PluginProtocol;
class PluginUtils
{
public:
    static void initPluginWrapper(android_app* app);
    static jobject createJavaMapObject(std::map<std::string, std::string>* paramMap);
    static void initJavaPlugin(PluginProtocol* pPlugin, jobject jObj, const char* className);
    static JNIEnv* getEnv();

    static PluginJavaData* getPluginJavaData(PluginProtocol* pKeyObj);
    static void setPluginJavaData(PluginProtocol* pKeyObj, PluginJavaData* pData);
    static void erasePluginJavaData(PluginProtocol* pKeyObj);

    static PluginProtocol* getPluginPtr(std::string className);

    static jobject getJObjFromParam(PluginParam* param);

    // methods have no return value
    template <typename T>
    static void callJavaFunctionWithName_oneParam(PluginProtocol* thiz, const char* funcName, const char* paramCode, T param)
    {
        return_if_fails(funcName != NULL && strlen(funcName) > 0);
        return_if_fails(paramCode != NULL && strlen(paramCode) > 0);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);
        return_if_fails(pData != NULL);

        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , funcName
            , paramCode))
        {
            t.env->CallVoidMethod(pData->jobj, t.methodID, param);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    static void callJavaFunctionWithName(PluginProtocol* thiz, const char* funcName)
    {
        return_if_fails(funcName != NULL && strlen(funcName) > 0);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);
        return_if_fails(pData != NULL);

        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , funcName
            , "()V"))
        {
            t.env->CallVoidMethod(pData->jobj, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    // methods return value is string
    template <typename T>
    static std::string callJavaStringFuncWithName_oneParam(PluginProtocol* thiz, const char* funcName, const char* paramCode, T param)
    {
        std::string ret = "";
        return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);
        return_val_if_fails(paramCode != NULL && strlen(paramCode) > 0, ret);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);
        return_val_if_fails(pData != NULL, ret);

        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , funcName
            , paramCode))
        {
            jstring strRet = (jstring)t.env->CallObjectMethod(pData->jobj, t.methodID, param);
            ret = PluginJniHelper::jstring2string(strRet);
            t.env->DeleteLocalRef(t.classID);
        }
        return ret;
    }
    static std::string callJavaStringFuncWithName(PluginProtocol* thiz, const char* funcName)
    {
        std::string ret = "";
        return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);
        return_val_if_fails(pData != NULL, ret);

        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , funcName
            , "()Ljava/lang/String;"))
        {
            jstring strRet = (jstring) t.env->CallObjectMethod(pData->jobj, t.methodID);
            ret = PluginJniHelper::jstring2string(strRet);
            t.env->DeleteLocalRef(t.classID);
        }
        return ret;
    }

    // methods return value is int
    template <typename T>
    static int callJavaIntFuncWithName_oneParam(PluginProtocol* thiz, const char* funcName, const char* paramCode, T param)
    {
        CALL_BASERET_JAVA_FUNC_WITH_PARAM(int, paramCode, param, Int, 0)
    }
    static int callJavaIntFuncWithName(PluginProtocol* thiz, const char* funcName)
    {
        CALL_BASERET_JAVA_FUNC(int, "()I", Int, 0)
    }

    // methods return value is float
    template <typename T>
    static float callJavaFloatFuncWithName_oneParam(PluginProtocol* thiz, const char* funcName, const char* paramCode, T param)
    {
        CALL_BASERET_JAVA_FUNC_WITH_PARAM(float, paramCode, param, Float, 0.0f)
    }
    static float callJavaFloatFuncWithName(PluginProtocol* thiz, const char* funcName)
    {
        CALL_BASERET_JAVA_FUNC(float, "()F", Float, 0.0f);
    }

    // methods return value is bool
    template <typename T>
    static bool callJavaBoolFuncWithName_oneParam(PluginProtocol* thiz, const char* funcName, const char* paramCode, T param)
    {
        CALL_BASERET_JAVA_FUNC_WITH_PARAM(bool, paramCode, param, Boolean, false)
    }
    static bool callJavaBoolFuncWithName(PluginProtocol* thiz, const char* funcName)
    {
        CALL_BASERET_JAVA_FUNC(bool, "()Z", Boolean, false)
    }

    static void outputLog(const char* logTag, const char* pFormat, ...);
};

}} // namespace cocos2d { namespace plugin {

#endif //__PLUGIN_UTILS_H__
