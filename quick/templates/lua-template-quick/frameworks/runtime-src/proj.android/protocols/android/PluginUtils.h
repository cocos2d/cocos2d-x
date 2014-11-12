#ifndef __PLUGIN_UTILS_H__
#define __PLUGIN_UTILS_H__

#include "PluginJniHelper.h"
#include "PluginJavaData.h"
#include <map>
#include <list>
#include "PluginParam.h"
#include "PluginJniMacros.h"
#include <android_native_app_glue.h>

namespace anysdk { namespace framework {

class PluginProtocol;
class PluginUtils
{
public:
    static void initPluginWrapper(android_app* app);
    static jobject createJavaMapObject(std::map<std::string, std::string>* paramMap);
    static jobject createJavaListObject(std::list<std::string>* paramList);
    static void initJavaPlugin(PluginProtocol* pPlugin, jobject jObj, const char* className, int type);
    static JNIEnv* getEnv();

    static PluginJavaData* getPluginJavaData(PluginProtocol* pKeyObj);
    static void setPluginJavaData(PluginProtocol* pKeyObj, PluginJavaData* pData, int type);
    static void erasePluginJavaData(PluginProtocol* pKeyObj);
    static void erasePluginJavaData(std::string key);

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

}} // namespace anysdk { namespace framework {

#endif //__PLUGIN_UTILS_H__
