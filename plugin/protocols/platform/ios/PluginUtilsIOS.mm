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

namespace cocos2d { namespace plugin {

bool PluginUtilsIOS::initOCPlugin(PluginProtocol* pPlugin, const char* className)
{
	return_val_if_fails(className != NULL && strlen(className) > 0, false);
	bool bRet = false;

    NSString* name = [NSString stringWithUTF8String:className];
    id obj = [[NSClassFromString(name) alloc] init];
    if (obj != nil)
    {
        PluginOCData* pData = new PluginOCData();
        pData->obj = obj;
        pData->className = className;
        PluginUtilsIOS::setPluginOCData(pPlugin, pData);
        bRet = true;
    }

	return bRet;
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

void PluginUtilsIOS::callOCFunctionWithName(PluginProtocol* pPlugin, const char* funcName)
{
    return_if_fails(funcName != NULL && strlen(funcName) > 0);

    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(pPlugin);
    if (pData) {
        id pOCObj = pData->obj;
        NSString* strFuncName = [NSString stringWithUTF8String:funcName];
        SEL selector = NSSelectorFromString(strFuncName);

        const char* className = class_getName([pOCObj class]);
        NSString* strClassName = [NSString stringWithUTF8String:className];
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector];
            NSLog(@"Function '%@' in class '%@' invoked", strFuncName, strClassName);
        } else {
            NSLog(@"Can't find function '%@' in class '%@'", strFuncName, strClassName);
        }
    } else {
        printf("Can't find function '%s' in plugin %p", funcName, pPlugin);
    }
}

void PluginUtilsIOS::callOCFunctionWithName_Object(PluginProtocol* pPlugin, const char* funcName, id obj)
{
    return_if_fails(funcName != NULL && strlen(funcName) > 0);
    
    PluginOCData* pData = PluginUtilsIOS::getPluginOCData(pPlugin);
    if (pData) {
        id pOCObj = pData->obj;
        NSString* strFuncName = [NSString stringWithUTF8String:funcName];
        SEL selector = NSSelectorFromString(strFuncName);
        
        const char* className = class_getName([pOCObj class]);
        NSString* strClassName = [NSString stringWithUTF8String:className];
        if ([pOCObj respondsToSelector:selector]) {
            [pOCObj performSelector:selector withObject:obj];
            NSLog(@"Function '%@' in class '%@' invoked", strFuncName, strClassName);
        } else {
            NSLog(@"Can't find function '%@' in class '%@'", strFuncName, strClassName);
        }
    } else {
        printf("Can't find function '%s' in plugin %p", funcName, pPlugin);
    }
}

}}// namespace cocos2d { namespace plugin {
