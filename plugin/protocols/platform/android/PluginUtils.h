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
#ifndef __PLUGIN_UTILS_H__
#define __PLUGIN_UTILS_H__

#include "PluginJniHelper.h"
#include <android/log.h>
#include "PluginJavaData.h"
#include "PluginProtocol.h"
#include <map>

namespace cocos2d { namespace plugin {

#define return_if_fails(cond) if (!(cond)) return; 
#define return_val_if_fails(cond, ret) if(!(cond)) return (ret);

class PluginUtils
{
public:
    static jobject createJavaMapObject(PluginJniMethodInfo&t, std::map<std::string, std::string>* paramMap);
    static bool initJavaPlugin(PluginProtocol* pPlugin, const char* className);
    static JNIEnv* getEnv();

    static PluginJavaData* getPluginJavaData(PluginProtocol* pKeyObj);
    static void setPluginJavaData(PluginProtocol* pKeyObj, PluginJavaData* pData);
    static void erasePluginJavaData(PluginProtocol* pKeyObj);

    static PluginProtocol* getPluginPtr(jobject jobj);

    template <typename T>
    static void callJavaFunctionWithName_oneBaseType(PluginProtocol* thiz, const char* funcName, const char* paramCode, T param)
    {
        return_if_fails(funcName != NULL && strlen(funcName) > 0);
        return_if_fails(paramCode != NULL && strlen(paramCode) > 0);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);
         PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , funcName
            , paramCode))
        {
            t.env->CallVoidMethod(pData->jobj, t.methodID, param);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    
    static void callJavaFunctionWithName(PluginProtocol* thiz, const char* funcName)
    {
        return_if_fails(funcName != NULL && strlen(funcName) > 0);
        PluginJavaData* pData = PluginUtils::getPluginJavaData(thiz);
        PluginJniMethodInfo t;
        if (PluginJniHelper::getMethodInfo(t
            , pData->jclassName.c_str()
            , funcName
            , "()V"))
        {
            t.env->CallVoidMethod(pData->jobj, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }
};

}} // namespace cocos2d { namespace plugin {

#endif //__PLUGIN_UTILS_H__
