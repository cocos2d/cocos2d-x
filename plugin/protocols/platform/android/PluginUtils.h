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
};

}} // namespace cocos2d { namespace plugin {

#endif //__PLUGIN_UTILS_H__
