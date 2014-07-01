#ifndef __PLUGIN_JNI_MACROS_H__
#define __PLUGIN_JNI_MACROS_H__

#define return_if_fails(cond) if (!(cond)) return;
#define return_val_if_fails(cond, ret) if(!(cond)) return (ret);

#define CALL_BASERET_JAVA_FUNC_WITH_PARAM(retType, paramCode, param, retCode, defaultRet)     \
retType ret = defaultRet;                                        \
return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);       \
return_val_if_fails(paramCode != NULL && strlen(paramCode) > 0, ret);     \
PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);    \
return_val_if_fails(pData != NULL, ret);                         \
                                                                 \
PluginJniMethodInfo t;                                           \
if (PluginJniHelper::getMethodInfo(t                             \
    , pData->jclassName.c_str()                                  \
    , funcName                                                   \
    , paramCode))                                                \
{                                                                \
    ret = t.env->Call##retCode##Method(pData->jobj, t.methodID, param);  \
    t.env->DeleteLocalRef(t.classID);                            \
}                                                                \
return ret;                                                      \


#define CALL_BASERET_JAVA_FUNC(retType, paramCode, retCode, defaultRet)   \
retType ret = defaultRet;                                        \
return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);       \
PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);    \
return_val_if_fails(pData != NULL, ret);                         \
                                                                 \
PluginJniMethodInfo t;                                           \
if (PluginJniHelper::getMethodInfo(t                             \
    , pData->jclassName.c_str()                                  \
    , funcName                                                   \
    , paramCode))                                                \
{                                                                \
    ret = t.env->Call##retCode##Method(pData->jobj, t.methodID); \
    t.env->DeleteLocalRef(t.classID);                            \
}                                                                \
return ret;                                                      \


#define CALL_JAVA_FUNC_WITH_VALIST(retCode)                  \
std::vector<PluginParam*> allParams;                         \
if (NULL != param)                                           \
{                                                            \
    allParams.push_back(param);                              \
                                                             \
    va_list argp;                                            \
    PluginParam* pArg = NULL;                                \
    va_start( argp, param );                                 \
    while (1)                                                \
    {                                                        \
        pArg = va_arg(argp, PluginParam*);                   \
        if (pArg == NULL)                                    \
            break;                                           \
                                                             \
        allParams.push_back(pArg);                           \
    }                                                        \
    va_end(argp);                                            \
}                                                            \
                                                             \
return call##retCode##FuncWithParam(funcName, allParams);    \


#define CALL_JAVA_FUNC(retType, retCode, defaultRet, jRetCode)    \
retType ret = defaultRet;                                                                                     \
PluginJavaData* pData = PluginUtils::getPluginJavaData(this);                                                 \
if (NULL == pData) {                                                                                          \
    PluginUtils::outputLog("PluginProtocol", "Can't find java data for plugin : %s", this->getPluginName());  \
    return ret;                                                                                               \
}                                                                                                             \
                                                                                                              \
std::string paramCode;                                                                                        \
int nParamNum = params.size();                                                                                \
if (0 == nParamNum)                                                                                           \
{                                                                                                             \
    paramCode = "()";                                                                                         \
    paramCode.append(jRetCode);                                                                               \
    ret = PluginUtils::callJava##retCode##FuncWithName(this, funcName);                                       \
} else                                                                                                        \
{                                                                                                             \
    PluginParam* pRetParam = NULL;                                                                            \
    bool needDel = false;                                                                                     \
    if (nParamNum == 1) {                                                                                     \
        pRetParam = params[0];                                                                                \
    } else {                                                                                                  \
        std::map<std::string, PluginParam*> allParams;                                                        \
        for (int i = 0; i < nParamNum; i++)                                                                   \
        {                                                                                                     \
            PluginParam* pArg = params[i];                                                                    \
            if (pArg == NULL)                                                                                 \
            {                                                                                                 \
                break;                                                                                        \
            }                                                                                                 \
                                                                                                              \
            char strKey[8] = { 0 };                                                                           \
            sprintf(strKey, "Param%d", i + 1);                                                                \
            allParams[strKey] = pArg;                                                                         \
        }                                                                                                     \
                                                                                                              \
        pRetParam = new PluginParam(allParams);                                                               \
        needDel = true;                                                                                       \
    }                                                                                                         \
                                                                                                              \
    switch(pRetParam->getCurrentType())                                                                       \
    {                                                                                                         \
    case PluginParam::kParamTypeInt:                                                                          \
        paramCode = "(I)";                                                                                    \
        paramCode.append(jRetCode);                                                                           \
        ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), pRetParam->getIntValue());         \
        break;                                                                                                \
    case PluginParam::kParamTypeFloat:                                                                        \
        paramCode = "(F)";                                                                                    \
        paramCode.append(jRetCode);                                                                           \
        ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), pRetParam->getFloatValue());       \
        break;                                                                                                \
    case PluginParam::kParamTypeBool:                                                                         \
        paramCode = "(Z)";                                                                                    \
        paramCode.append(jRetCode);                                                                           \
        ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), pRetParam->getBoolValue());        \
        break;                                                                                                \
    case PluginParam::kParamTypeString:                                                                       \
        {                                                                                                     \
            jstring jstr = PluginUtils::getEnv()->NewStringUTF(pRetParam->getStringValue());                  \
            paramCode = "(Ljava/lang/String;)";                                                               \
            paramCode.append(jRetCode);                                                                      \
            ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), jstr);    \
            PluginUtils::getEnv()->DeleteLocalRef(jstr);                                                      \
        }                                                                                                     \
        break;                                                                                                \
    case PluginParam::kParamTypeStringMap:                                                                    \
    case PluginParam::kParamTypeMap:                                                                          \
        {                                                                                                     \
            jobject jMap = PluginUtils::getJObjFromParam(pRetParam);                                          \
            paramCode = "(Lorg/json/JSONObject;)";                                                            \
            paramCode.append(jRetCode);                                                                       \
            ret = PluginUtils::callJava##retCode##FuncWithName_oneParam(this, funcName, paramCode.c_str(), jMap); \
            PluginUtils::getEnv()->DeleteLocalRef(jMap);                                                      \
        }                                                                                                     \
        break;                                                                                                \
    default:                                                                                                  \
        break;                                                                                                \
    }                                                                                                         \
                                                                                                              \
    if (needDel && pRetParam != NULL)                                                                         \
    {                                                                                                         \
        delete pRetParam;                                                                                     \
        pRetParam = NULL;                                                                                     \
    }                                                                                                         \
}                                                                                                             \
return ret;                                                                                                   \


#endif // __PLUGIN_JNI_MACROS_H__
