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
#include "PluginUtilsIOS.h"
#include "PluginOCMacros.h"


@protocol OCPluginProtocol
@optional
- (void)setDebugMode:(BOOL)debug;
- (NSString *)getPluginVersion;
- (NSString *)getSDKVersion;
@end


namespace cocos2d { namespace plugin {

PluginProtocol::~PluginProtocol()
{
    PluginUtilsIOS::erasePluginOCData(this);
}

std::string PluginProtocol::getPluginVersion()
{
    std::string verName;
    
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"getPluginVersion");
        
        if ([pOCObj respondsToSelector:selector]) {
            NSString* strRet = [pOCObj getPluginVersion];
            if (strRet) {
                verName = [strRet UTF8String];
            }
        } else {
            PluginUtilsIOS::outputLog("Can't find function 'getPluginVersion' in class '%s'", pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %p is not initialized", this);
    }
    
    return verName;
}

std::string PluginProtocol::getSDKVersion()
{
    std::string verName;

    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"getSDKVersion");

        if ([pOCObj respondsToSelector:selector]) {
            NSString* strRet = [pOCObj getSDKVersion];
            if (strRet) {
                verName = [strRet UTF8String];
            }
        } else {
            PluginUtilsIOS::outputLog("Can't find function 'getSDKVersion' in class '%s'", pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %s is not initialized", this->getPluginName());
    }

    return verName;
}

void PluginProtocol::setDebugMode(bool isDebugMode)
{
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (pData) {
        id pOCObj = pData->obj;
        SEL selector = NSSelectorFromString(@"setDebugMode:");

        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj setDebugMode:(BOOL)isDebugMode];
        } else {
            PluginUtilsIOS::outputLog("Can't find function 'setDebugMode' in class '%s'", pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %s is not initialized", this->getPluginName());
    }
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
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(this);
    if (NULL == pData) {
        PluginUtilsIOS::outputLog("Can't find OC data for plugin : %s", this->getPluginName());
        return;
    }

    size_t nParamNum = params.size();
    if (0 == nParamNum)
    {
        PluginUtilsIOS::callOCFunctionWithName(this, funcName);
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

        id ocParam = PluginUtilsIOS::getOCObjFromParam(pRetParam);
        PluginUtilsIOS::callOCFunctionWithName_oneParam(this, funcName, ocParam);

        if (needDel && NULL != pRetParam) {
            delete pRetParam;
            pRetParam = NULL;
        }
    }
}

std::string PluginProtocol::callStringFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_OC_FUNC_WITH_VALIST(String)
}
    
std::string PluginProtocol::callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_OC_FUNC(std::string, "", String)
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_OC_FUNC_WITH_VALIST(Int)
}

int PluginProtocol::callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_OC_FUNC(int, 0, Int)
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_OC_FUNC_WITH_VALIST(Bool)
}

bool PluginProtocol::callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_OC_FUNC(bool, false, Bool)
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, PluginParam* param, ...)
{
    CALL_OC_FUNC_WITH_VALIST(Float)
}

float PluginProtocol::callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params)
{
    CALL_OC_FUNC(float, 0.0f, Float)
}

}} //namespace cocos2d { namespace plugin {
