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
#include "PluginProtocol.h"
#include "PluginUtils.h"

namespace cocos2d { namespace plugin {

PluginProtocol::~PluginProtocol()
{
    PluginUtils::erasePluginJavaData(this);
}

const char* PluginProtocol::getPluginVersion()
{
    std::string verName;

    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "getPluginVersion"
        , "()Ljava/lang/String;"))
    {
        jstring ret = (jstring)(t.env->CallObjectMethod(pData->jobj, t.methodID));
        verName = PluginJniHelper::jstring2string(ret);
    }
    return verName.c_str();
}

const char* PluginProtocol::getSDKVersion()
{
    std::string verName;

    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    PluginJniMethodInfo t;
    if (PluginJniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "getSDKVersion"
        , "()Ljava/lang/String;"))
    {
        jstring ret = (jstring)(t.env->CallObjectMethod(pData->jobj, t.methodID));
        verName = PluginJniHelper::jstring2string(ret);
    }
    return verName.c_str();
}

void PluginProtocol::setDebugMode(bool isDebugMode)
{
    PluginUtils::callJavaFunctionWithName_oneParam(this, "setDebugMode", "(Z)V", isDebugMode);
}

void PluginProtocol::callFuncWithParam(const char* funcName, PluginParam* param)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    if (NULL == pData) {
        PluginUtils::outputLog("PluginProtocol", "Can't find java data for plugin : %s", this->getPluginName());
        return;
    }

    if (NULL == param)
    {
        PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "()V", NULL);
    } else
    {
        switch(param->getCurrentType())
        {
        case PluginParam::kParamTypeInt:
            PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(I)V", param->getIntValue());
            break;
        case PluginParam::kParamTypeFloat:
            PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(F)V", param->getFloatValue());
            break;
        case PluginParam::kParamTypeBool:
            PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(Z)V", param->getBoolValue());
            break;
        case PluginParam::kParamTypeString:
            {
                jstring jstr = PluginUtils::getEnv()->NewStringUTF(param->getStringValue());
                PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(Ljava/lang/String;)V", jstr);
                PluginUtils::getEnv()->DeleteLocalRef(jstr);
            }
            break;
        case PluginParam::kParamTypeStringMap:
        case PluginParam::kParamTypeMap:
            {
                jobject jMap = PluginUtils::getJObjFromParam(param);
                PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(Lorg/json/JSONObject;)V", jMap);
                PluginUtils::getEnv()->DeleteLocalRef(jMap);
            }
            break;
        default:
            break;
        }
    }
}

const char* PluginProtocol::callStringFuncWithParam(const char* funcName, PluginParam* param)
{
    CALL_JAVA_FUNC(const char*, String, "", "Ljava/lang/String;")
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, PluginParam* param)
{
    CALL_JAVA_FUNC(int, Int, 0, "I")
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, PluginParam* param)
{
    CALL_JAVA_FUNC(bool, Bool, false, "Z")
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, PluginParam* param)
{
    CALL_JAVA_FUNC(float, Float, 0.0f, "F")
}

}} //namespace cocos2d { namespace plugin {
