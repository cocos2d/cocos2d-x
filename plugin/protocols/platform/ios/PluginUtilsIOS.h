/****************************************************************************
Copyright (c) 2012+2013 cocos2d+x.org

http://www.cocos2d+x.org

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

#ifndef __PLUGIN_UTILS_IOS_H__
#define __PLUGIN_UTILS_IOS_H__

#include "PluginProtocol.h"
#include <string>
#include <map>
#include "PluginParam.h"

namespace cocos2d { namespace plugin {

typedef struct _PluginOCData
{
    id obj;
    std::string className;
} PluginOCData;

class PluginUtilsIOS
{
public:
    static void initOCPlugin(PluginProtocol* pPlugin, id ocObj, const char* className);

    static PluginOCData* getPluginOCData(PluginProtocol* pKeyObj);
    static void setPluginOCData(PluginProtocol* pKeyObj, PluginOCData* pData);
    static void erasePluginOCData(PluginProtocol* pKeyObj);

    static PluginProtocol* getPluginPtr(id obj);

    static id getOCObjFromParam(PluginParam* param);

    static NSMutableDictionary* createDictFromMap(std::map<std::string, std::string>* paramMap);

    /**
     @brief method don't have return value
     */
    static void callOCFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
    static void callOCFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

    /**
     @brief method return int value
     */
    static int callOCIntFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
    static int callOCIntFunctionWithName(PluginProtocol* pPlugin, const char* funcName);
    
    /**
     @brief method return float value
     */
    static float callOCFloatFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
    static float callOCFloatFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

    /**
     @brief method return bool value
     */
    static bool callOCBoolFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
    static bool callOCBoolFunctionWithName(PluginProtocol* pPlugin, const char* funcName);
    
    /**
     @brief method return string value
     */
    static std::string callOCStringFunctionWithName_oneParam(PluginProtocol* pPlugin, const char* funcName, id param);
    static std::string callOCStringFunctionWithName(PluginProtocol* pPlugin, const char* funcName);

    static void outputLog(const char* pFormat, ...);
private:
    static id callRetFunctionWithParam(PluginProtocol* pPlugin, const char* funcName, id param);
    static id callRetFunction(PluginProtocol* pPlugin, const char* funcName);
};

}} // namespace cocos2d { namespace plugin {

#endif //__PLUGIN_UTILS_IOS_H__
