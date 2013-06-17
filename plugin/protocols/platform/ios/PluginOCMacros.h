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
#ifndef __PLUGIN_OC_MACROS_H__
#define __PLUGIN_OC_MACROS_H__

#define return_if_fails(cond) if (!(cond)) return;
#define return_val_if_fails(cond, ret) if(!(cond)) return (ret);

#define CALL_OC_FUNC_WITH_VALIST(retCode)                                                       \
std::vector<PluginParam*> allParams;                                                            \
if (NULL != param)                                                                              \
{                                                                                               \
    allParams.push_back(param);                                                                 \
                                                                                                \
    va_list argp;                                                                               \
    PluginParam* pArg = NULL;                                                                   \
    va_start( argp, param );                                                                    \
    while (1)                                                                                   \
    {                                                                                           \
        pArg = va_arg(argp, PluginParam*);                                                      \
        if (pArg == NULL)                                                                       \
            break;                                                                              \
                                                                                                \
        allParams.push_back(pArg);                                                              \
    }                                                                                           \
    va_end(argp);                                                                               \
}                                                                                               \
                                                                                                \
return call##retCode##FuncWithParam(funcName, allParams);                                       \


#define CALL_OC_FUNC(retType, defaultRet, retCode)                                              \
retType ret = defaultRet;                                                                       \
PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);                                    \
if (NULL == pData) {                                                                            \
    PluginUtilsIOS::outputLog("Can't find OC data for plugin : %s", this->getPluginName());     \
    return ret;                                                                                 \
}                                                                                               \
                                                                                                \
int nParamNum = params.size();                                                                  \
if (0 == nParamNum)                                                                             \
{                                                                                               \
    ret = PluginUtilsIOS::callOC##retCode##FunctionWithName(this, funcName);                    \
} else                                                                                          \
{                                                                                               \
    PluginParam* pRetParam = NULL;                                                              \
    bool needDel = false;                                                                       \
    if (nParamNum == 1) {                                                                       \
        pRetParam = params[0];                                                                  \
    } else {                                                                                    \
        std::map<std::string, PluginParam*> allParams;                                          \
        for (int i = 0; i < nParamNum; i++)                                                     \
        {                                                                                       \
            PluginParam* pArg = params[i];                                                      \
            if (pArg == NULL)                                                                   \
            {                                                                                   \
                break;                                                                          \
            }                                                                                   \
                                                                                                \
            char strKey[8] = { 0 };                                                             \
            sprintf(strKey, "Param%d", i + 1);                                                  \
            allParams[strKey] = pArg;                                                           \
        }                                                                                       \
                                                                                                \
        pRetParam = new PluginParam(allParams);                                                 \
        needDel = true;                                                                         \
    }                                                                                           \
                                                                                                \
    id ocParam = PluginUtilsIOS::getOCObjFromParam(pRetParam);                                  \
    ret = PluginUtilsIOS::callOC##retCode##FunctionWithName_oneParam(this, funcName, ocParam);  \
                                                                                                \
    if (needDel && NULL != pRetParam) {                                                         \
        delete pRetParam;                                                                       \
        pRetParam = NULL;                                                                       \
    }                                                                                           \
}                                                                                               \
return ret;                                                                                     \


#endif // __PLUGIN_OC_MACROS_H__
