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

namespace cocos2d { namespace plugin {

#define return_if_fails(cond) if (!(cond)) return; 
#define return_val_if_fails(cond, ret) if(!(cond)) return (ret);

typedef struct _PluginOCData
{
    id obj;
    std::string className;
} PluginOCData;

class PluginUtilsIOS
{
public:
    static bool initOCPlugin(PluginProtocol* pPlugin, const char* className);

    static PluginOCData* getPluginOCData(PluginProtocol* pKeyObj);
    static void setPluginOCData(PluginProtocol* pKeyObj, PluginOCData* pData);
    static void erasePluginOCData(PluginProtocol* pKeyObj);

    static PluginProtocol* getPluginPtr(id obj);

    static NSMutableDictionary* createDictFromMap(std::map<std::string, std::string>* paramMap);
    static void callOCFunctionWithName(PluginProtocol* pPlugin, const char* funcName);
    static void callOCFunctionWithName_Object(PluginProtocol* pPlugin, const char* funcName, id obj);
};

}} // namespace cocos2d { namespace plugin {

#endif //__PLUGIN_UTILS_IOS_H__
