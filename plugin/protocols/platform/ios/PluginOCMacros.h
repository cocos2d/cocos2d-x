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


#define CALL_OC_FUNC(retType, defaultRet, retCode)                                              \
retType ret = defaultRet;                                                                       \
PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);                                    \
if (NULL == pData) {                                                                            \
    PluginUtilsIOS::outputLog("Can't find OC data for plugin : %s", this->getPluginName());     \
    return ret;                                                                                 \
}                                                                                               \
                                                                                                \
if (NULL == param)                                                                              \
{                                                                                               \
    ret = PluginUtilsIOS::callOC##retCode##FunctionWithName_oneParam(this, funcName, NULL);     \
} else                                                                                          \
{                                                                                               \
    PluginParam* pRetParam = NULL;                                                              \
    std::map<std::string, PluginParam*> allParams;                                              \
    va_list argp;                                                                               \
    int argno = 0;                                                                              \
    PluginParam* pArg = NULL;                                                                   \
                                                                                                \
    allParams["Param1"] = param;                                                                \
    va_start( argp, param );                                                                    \
    while (1)                                                                                   \
    {                                                                                           \
        pArg = va_arg(argp, PluginParam*);                                                      \
        if (pArg == NULL)                                                                       \
        {                                                                                       \
            break;                                                                              \
        }                                                                                       \
        argno++;                                                                                \
        char strKey[8] = { 0 };                                                                 \
        sprintf(strKey, "Param%d", argno + 1);                                                  \
        allParams[strKey] = pArg;                                                               \
    }                                                                                           \
    va_end(argp);                                                                               \
                                                                                                \
    PluginParam tempParam(allParams);                                                           \
    if (argno == 0)                                                                             \
    {                                                                                           \
        pRetParam = param;                                                                      \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        pRetParam = &tempParam;                                                                 \
    }                                                                                           \
                                                                                                \
    id ocParam = PluginUtilsIOS::getOCObjFromParam(pRetParam);                                  \
    ret = PluginUtilsIOS::callOC##retCode##FunctionWithName_oneParam(this, funcName, ocParam);  \
}                                                                                               \
return ret;                                                                                     \


#endif // __PLUGIN_OC_MACROS_H__
