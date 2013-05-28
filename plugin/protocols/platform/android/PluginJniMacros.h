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
#ifndef __PLUGIN_JNI_MACROS_H__
#define __PLUGIN_JNI_MACROS_H__

#define return_if_fails(cond) if (!(cond)) return;
#define return_val_if_fails(cond, ret) if(!(cond)) return (ret);

#define CALL_BASERET_JAVA_FUNC_WITH_PARAM(retType, paramCode, param, retCode, defaultRet)     \
retType ret = defaultRet;                                        \
return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);       \
return_val_if_fails(paramCode != NULL && strlen(paramCode) > 0, ret);     \
PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);    \
return_val_if_fails(pData != NULL, ret);                                  \
                                                                 \
PluginJniMethodInfo t;                                           \
if (PluginJniHelper::getMethodInfo(t                             \
    , pData->jclassName.c_str()                                  \
    , funcName                                                   \
    , paramCode))                                                \
{                                                                \
    if (NULL != param)                                           \
    {                                                            \
        ret = t.env->Call##retCode##Method(pData->jobj, t.methodID, param);  \
    } else {                                                     \
        ret = t.env->Call##retCode##Method(pData->jobj, t.methodID);  \
    }                                                            \
    t.env->DeleteLocalRef(t.classID);                            \
}                                                                \
return ret;                                                      \



#define CALL_JAVA_FUNC(retType, retCode, defaultRet, jRetCode)    \
retType ret = defaultRet;                                                                                     \
PluginJavaData* pData = PluginUtils::getPluginJavaData(this);                                                 \
if (NULL == pData) {                                                                                          \
    PluginUtils::outputLog("PluginProtocol", "Can't find java data for plugin : %s", this->getPluginName());  \
    return ret;                                                                                               \
}                                                                                                             \
                                                                                                              \
std::string paramCode;                                                                                        \
if (NULL == param)                                                                                            \
{                                                                                                             \
    paramCode = "()";                                                                                         \
    paramCode.append(jRetCode);                                                                              \
    ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), NULL);     \
} else                                                                                                        \
{                                                                                                             \
    switch(param->getCurrentType())                                                                           \
    {                                                                                                         \
    case PluginParam::kParamTypeInt:                                                                          \
        paramCode = "(I)";                                                                                    \
        paramCode.append(jRetCode);                                                                          \
        ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), param->getIntValue());         \
        break;                                                                                                \
    case PluginParam::kParamTypeFloat:                                                                        \
        paramCode = "(F)";                                                                                    \
        paramCode.append(jRetCode);                                                                          \
        ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), param->getFloatValue());       \
        break;                                                                                                \
    case PluginParam::kParamTypeBool:                                                                         \
        paramCode = "(Z)";                                                                                    \
        paramCode.append(jRetCode);                                                                          \
        ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), param->getBoolValue());        \
        break;                                                                                                \
    case PluginParam::kParamTypeString:                                                                       \
        {                                                                                                     \
            jstring jstr = PluginUtils::getEnv()->NewStringUTF(param->getStringValue());                      \
            paramCode = "(Ljava/lang/String;)";                                                               \
            paramCode.append(jRetCode);                                                                      \
            ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), jstr);    \
            PluginUtils::getEnv()->DeleteLocalRef(jstr);                                                      \
        }                                                                                                     \
        break;                                                                                                \
    case PluginParam::kParamTypeStringMap:                                                                    \
    case PluginParam::kParamTypeMap:                                                                          \
        {                                                                                                     \
            jobject jMap = PluginUtils::getJObjFromParam(param);                                              \
            paramCode = "(Lorg/json/JSONObject;)";                                                            \
            paramCode.append(jRetCode);                                                                      \
            ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), jMap); \
            PluginUtils::getEnv()->DeleteLocalRef(jMap);                                                      \
        }                                                                                                     \
        break;                                                                                                \
    default:                                                                                                  \
        break;                                                                                                \
    }                                                                                                         \
}                                                                                                             \
return ret;                                                                                                   \


#endif // __PLUGIN_JNI_MACROS_H__
