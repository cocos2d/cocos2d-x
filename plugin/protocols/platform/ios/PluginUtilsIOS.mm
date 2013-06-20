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

#include "PluginUtilsIOS.h"
#include <map>
#import <objc/runtime.h>
#include "PluginOCMacros.h"

#define MAX_LOG_LEN         256

namespace cocos2d { namespace plugin {

void PluginUtilsIOS::initOCPlugin(PluginProtocol* pPlugin, id ocObj, const char* className)
{
    PluginOCData* pData = new PluginOCData();
    pData->obj = ocObj;
    pData->className = className;
    PluginUtilsIOS::setPluginOCData(pPlugin, pData);
}

std::map<PluginProtocol*, PluginOCData*> s_PluginOCObjMap;
std::map<id, PluginProtocol*> s_OCObjPluginMap;

typedef std::map<PluginProtocol*, PluginOCData*>::iterator OCObjMapIter;
typedef std::map<id, PluginProtocol*>::iterator OCObjPluginMapIter;

PluginOCData* PluginUtilsIOS::getPluginOCData(PluginProtocol* pKeyObj)
{
    PluginOCData* ret = NULL;
    OCObjMapIter it = s_PluginOCObjMap.find(pKeyObj);
    if (it != s_PluginOCObjMap.end()) {
        ret = it->second;
    }

    return ret;
}

PluginProtocol* PluginUtilsIOS::getPluginPtr(id obj)
{
	PluginProtocol* ret = NULL;
	OCObjPluginMapIter it = s_OCObjPluginMap.find(obj);
	if (it != s_OCObjPluginMap.end()) {
		ret = it->second;
	}

	return ret;
}

id PluginUtilsIOS::getOCObjFromParam(PluginParam* param)
{
    if (NULL == param)
	{
		return nil;
	}
    
	id obj = nil;
	switch(param->getCurrentType())
	{
        case PluginParam::kParamTypeInt:
            obj = [NSNumber numberWithInt:param->getIntValue()];
            break;
        case PluginParam::kParamTypeFloat:
            obj = [NSNumber numberWithFloat:param->getFloatValue()];
            break;
        case PluginParam::kParamTypeBool:
            obj = [NSNumber numberWithBool:param->getBoolValue()];
            break;
        case PluginParam::kParamTypeString:
            obj = [NSString stringWithUTF8String:param->getStringValue()];
            break;
        case PluginParam::kParamTypeStringMap:
            {
                std::map<std::string, std::string> mapValue = param->getStrMapValue();
                obj = createDictFromMap(&mapValue);
            }
            break;
        case PluginParam::kParamTypeMap:
            {
                obj = [NSMutableDictionary dictionary];
                std::map<std::string, PluginParam*> paramMap = param->getMapValue();
                std::map<std::string, PluginParam*>::const_iterator it;
                for (it = paramMap.begin(); it != paramMap.end(); ++it)
                {
                    NSString* pKey = [NSString stringWithUTF8String:it->first.c_str()];
                    id objValue = PluginUtilsIOS::getOCObjFromParam(it->second);
                    [obj setValue:objValue forKey:pKey];
                }
            }
            break;
        default:
            break;
	}
    
	return obj;
}

void PluginUtilsIOS::setPluginOCData(PluginProtocol* pKeyObj, PluginOCData* pData)
{
    erasePluginOCData(pKeyObj);
    s_PluginOCObjMap.insert(std::pair<PluginProtocol*, PluginOCData*>(pKeyObj, pData));
    s_OCObjPluginMap.insert(std::pair<id, PluginProtocol*>(pData->obj, pKeyObj));
}

void PluginUtilsIOS::erasePluginOCData(PluginProtocol* pKeyObj)
{
    OCObjMapIter it = s_PluginOCObjMap.find(pKeyObj);
    if (it != s_PluginOCObjMap.end()) {
        PluginOCData* pData = it->second;
        if (pData != NULL)
        {
            id jobj = pData->obj;

            OCObjPluginMapIter pluginIt = s_OCObjPluginMap.find(jobj);
            if (pluginIt != s_OCObjPluginMap.end())
            {
            	s_OCObjPluginMap.erase(pluginIt);
            }

            [jobj release];
            delete pData;
        }
        s_PluginOCObjMap.erase(it);
    }
}

NSMutableDictionary* PluginUtilsIOS::createDictFromMap(std::map<std::string, std::string>* paramMap)
{
    if (NULL == paramMap)
    {
        return nil;
    }

    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
    std::map<std::string, std::string>::const_iterator it;
    for (it = paramMap->begin(); it != paramMap->end(); ++it)
    {
        NSString* pKey = [NSString stringWithUTF8String:it->first.c_str()];
        NSString* pValue = [NSString stringWithUTF8String:it->second.c_str()];
        [dict setValue:pValue forKey:pKey];
    }
    
    return dict;
}

void PluginUtilsIOS::callOCFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
{
    return_if_fails(funcName != NULL && strlen(funcName) > 0);
    
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(pPlugin);
    if (pData) {
        id pOCObj = pData->obj;

        NSString* strFuncName = [NSString stringWithUTF8String:funcName];
        strFuncName = [strFuncName stringByAppendingString:@":"];

        SEL selector = NSSelectorFromString(strFuncName);
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector withObject:param];
        } else {
            outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
    }
}
    
void PluginUtilsIOS::callOCFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
{
    return_if_fails(funcName != NULL && strlen(funcName) > 0);
    
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(pPlugin);
    if (pData) {
        id pOCObj = pData->obj;
        
        NSString* strFuncName = [NSString stringWithUTF8String:funcName];
        SEL selector = NSSelectorFromString(strFuncName);
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector];
        } else {
            outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
    }
}

int PluginUtilsIOS::callOCIntFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
{
    NSNumber* num = (NSNumber*) callRetFunctionWithParam(pPlugin, funcName, param);
    int ret = [num integerValue];
    return ret;
}

int PluginUtilsIOS::callOCIntFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
{
    NSNumber* num = (NSNumber*) callRetFunction(pPlugin, funcName);
    int ret = [num integerValue];
    return ret;
}

float PluginUtilsIOS::callOCFloatFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
{
    float ret = 0.0f;
    NSNumber* pRet = (NSNumber*)callRetFunctionWithParam(pPlugin, funcName, param);
    if (nil != pRet) {
        ret = [pRet floatValue];
    }
    
    return ret;
}

float PluginUtilsIOS::callOCFloatFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
{
    float ret = 0.0f;
    NSNumber* pRet = (NSNumber*)callRetFunction(pPlugin, funcName);
    if (nil != pRet) {
        ret = [pRet floatValue];
    }
    
    return ret;
}

bool PluginUtilsIOS::callOCBoolFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
{
    bool ret = false;
    NSNumber* pRet = (NSNumber*)callRetFunctionWithParam(pPlugin, funcName, param);
    if (nil != pRet) {
        ret = [pRet boolValue];
    }

    return ret;
}

bool PluginUtilsIOS::callOCBoolFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
{
    bool ret = false;
    NSNumber* pRet = (NSNumber*)callRetFunction(pPlugin, funcName);
    if (nil != pRet) {
        ret = [pRet boolValue];
    }
    
    return ret;
}

const char* PluginUtilsIOS::callOCStringFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param)
{
    const char* ret = "";
    NSString* pRet = (NSString*)callRetFunctionWithParam(pPlugin, funcName, param);
    if (nil != pRet) {
        ret = [pRet UTF8String];
    }

    return ret;
}
    
const char* PluginUtilsIOS::callOCStringFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
{
    const char* ret = "";
    NSString* pRet = (NSString*)callRetFunction(pPlugin, funcName);
    if (nil != pRet) {
        ret = [pRet UTF8String];
    }
    
    return ret;
}

id PluginUtilsIOS::callRetFunction(PluginProtocol* pPlugin, const char* funcName)
{
    id ret = nil;
    return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);
    
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(pPlugin);
    if (pData) {
        id pOCObj = pData->obj;
        
        NSString* strFuncName = [NSString stringWithUTF8String:funcName];
        SEL selector = NSSelectorFromString(strFuncName);
        if ([pOCObj respondsToSelector:selector]) {
            ret = [pOCObj performSelector:selector];
        } else {
            outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
    }
    
    return ret;
}

id PluginUtilsIOS::callRetFunctionWithParam(PluginProtocol* pPlugin, const char* funcName, id param)
{
    id ret = nil;
    return_val_if_fails(funcName != NULL && strlen(funcName) > 0, ret);
    
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(pPlugin);
    if (pData) {
        id pOCObj = pData->obj;
        
        NSString* strFuncName = [NSString stringWithUTF8String:funcName];
        strFuncName = [strFuncName stringByAppendingString:@":"];
        SEL selector = NSSelectorFromString(strFuncName);
        if ([pOCObj respondsToSelector:selector]) {
            ret = [pOCObj performSelector:selector withObject:param];
        } else {
            outputLog("Can't find function '%s' in class '%s'", [strFuncName UTF8String], pData->className.c_str());
        }
    } else {
        PluginUtilsIOS::outputLog("Plugin %s not right initilized", pPlugin->getPluginName());
    }

    return ret;
}

void PluginUtilsIOS::outputLog(const char* pFormat, ...)
{
    printf("Plugin-x: ");
    char szBuf[MAX_LOG_LEN+1] = {0};
    va_list ap;
    va_start(ap, pFormat);
    vsnprintf(szBuf, MAX_LOG_LEN, pFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}

}}// namespace cocos2d { namespace plugin {
