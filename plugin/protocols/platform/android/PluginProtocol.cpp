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

#define LOG_TAG     "PluginProtocol"

namespace cocos2d { namespace plugin {

PluginProtocol::~PluginProtocol()
{
    PluginUtils::erasePluginJavaData(this);
}

std::string PluginProtocol::getPluginVersion()
{
    return PluginUtils::callJavaStringFuncWithName(this, "getPluginVersion");
}

std::string PluginProtocol::getSDKVersion()
{
    return PluginUtils::callJavaStringFuncWithName(this, "getSDKVersion");
}

void PluginProtocol::setDebugMode(bool isDebugMode)
{
    PluginUtils::callJavaFunctionWithName_oneParam(this, "setDebugMode", "(Z)V", isDebugMode);
}

void PluginProtocol::callFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    std::vector<PluginParam*> allParams;
    if (NULL != param)
    {
        allParams.push_back(param);

        va_list argp;
        PluginParam* pArg = NULL;
        va_start( argp, param );
        while (1)
        {
            pArg = va_arg(argp, PluginParam*);
            if (pArg == NULL)
                break;

            allParams.push_back(pArg);
        }
        va_end(argp);
    }

    callFuncWithParam(funcName, allParams);
}

void PluginProtocol::callFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    PluginJavaData* pData = PluginUtils::getPluginJavaData(this);
    if (NULL == pData) {
        PluginUtils::outputLog(LOG_TAG, "Can't find java data for plugin : %s", this->getPluginName());
        return;
    }

    int nParamNum = params.size();
    if (nParamNum == 0)
    {
        PluginUtils::callJavaFunctionWithName(this, funcName);
    } else
    {
        PluginParam* pRetParam = NULL;
        bool needDel = false;
        if (nParamNum == 1) {
            pRetParam = params[0];
        } else {
            std::map<std::string, PluginParam*> allParams;
            for (int i = 0; i < nParamNum; i++)
            {
                PluginParam* pArg = params[i];
                if (pArg == NULL)
                {
                    break;
                }

                char strKey[8] = { 0 };
                sprintf(strKey, "Param%d", i + 1);
                allParams[strKey] = pArg;
            }

            pRetParam = new PluginParam(allParams);
            needDel = true;
        }

        switch(pRetParam->getCurrentType())
        {
        case PluginParam::kParamTypeInt:
            PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(I)V", pRetParam->getIntValue());
            break;
        case PluginParam::kParamTypeFloat:
            PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(F)V", pRetParam->getFloatValue());
            break;
        case PluginParam::kParamTypeBool:
            PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(Z)V", pRetParam->getBoolValue());
            break;
        case PluginParam::kParamTypeString:
            {
                jstring jstr = PluginUtils::getEnv()->NewStringUTF(pRetParam->getStringValue());
                PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(Ljava/lang/String;)V", jstr);
                PluginUtils::getEnv()->DeleteLocalRef(jstr);
            }
            break;
        case PluginParam::kParamTypeStringMap:
        case PluginParam::kParamTypeMap:
            {
                jobject jMap = PluginUtils::getJObjFromParam(pRetParam);
                PluginUtils::callJavaFunctionWithName_oneParam(this, funcName, "(Lorg/json/JSONObject;)V", jMap);
                PluginUtils::getEnv()->DeleteLocalRef(jMap);
            }
            break;
        default:
            break;
        }

        if (needDel && pRetParam != NULL)
        {
            delete pRetParam;
            pRetParam = NULL;
        }
    }
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(String)
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(std::string, String, "", "Ljava/lang/String;")
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(Int)
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(int, Int, 0, "I")
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(Bool)
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(bool, Bool, false, "Z")
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_JAVA_FUNC_WITH_VALIST(Float)
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_JAVA_FUNC(float, Float, 0.0f, "F")
}

}} //namespace cocos2d { namespace plugin {
