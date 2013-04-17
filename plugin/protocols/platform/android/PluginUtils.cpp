#include "PluginUtils.h"
#include <android/log.h>
#include <map>

namespace cocos2d { namespace plugin {

#define JAVAVM    cocos2d::PluginJniHelper::getJavaVM()

#if 1
#define  LOG_TAG    "PluginUtils"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

static cocos2d::plugin::PluginProtocol* s_pPluginInstance = NULL;

extern "C" {

JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_PluginWrapper_nativeInitPlugin(JNIEnv*  env, jobject thiz, jobject obj, jstring className)
{
    if (s_pPluginInstance != NULL) {
        cocos2d::plugin::PluginJavaData* pUserData = new cocos2d::plugin::PluginJavaData();
        pUserData->jobj = env->NewGlobalRef(obj);
        pUserData->jclassName = cocos2d::PluginJniHelper::jstring2string(className);
        cocos2d::plugin::PluginUtils::setPluginJavaData(s_pPluginInstance, pUserData);
        s_pPluginInstance = NULL;
    }
}

}

jobject PluginUtils::createJavaMapObject(PluginJniMethodInfo&t, std::map<std::string, std::string>* paramMap)
{
	jclass class_Hashtable = t.env->FindClass("java/util/Hashtable"); 
	jmethodID construct_method = t.env->GetMethodID( class_Hashtable, "<init>","()V"); 
	jobject obj_Map = t.env->NewObject( class_Hashtable, construct_method, "");
	if (paramMap != NULL)
	{
		jmethodID add_method= t.env->GetMethodID( class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"); 
		for (std::map<std::string, std::string>::const_iterator it = paramMap->begin(); it != paramMap->end(); ++it)
		{
			t.env->CallObjectMethod(obj_Map, add_method, t.env->NewStringUTF(it->first.c_str()), t.env->NewStringUTF(it->second.c_str()));  
		}
	}
    t.env->DeleteLocalRef(class_Hashtable);
    return obj_Map;
}

bool PluginUtils::initJavaPlugin(PluginProtocol* pPlugin, const char* className)
{
	return_val_if_fails(className != NULL && strlen(className) > 0, false);
	bool bRet = false;
	PluginJniMethodInfo t;
	s_pPluginInstance = pPlugin;
	if (PluginJniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/PluginWrapper"
		, "initPlugin"
		, "(Ljava/lang/String;)Z"))
	{
		jstring jclassName = t.env->NewStringUTF(className);
		bRet = (bool)t.env->CallStaticBooleanMethod(t.classID, t.methodID, jclassName);
		t.env->DeleteLocalRef(jclassName);
		t.env->DeleteLocalRef(t.classID);
	}

	return bRet;
}

JNIEnv* PluginUtils::getEnv()
{
    bool bRet = false;
    JNIEnv* env = NULL;
    do 
    {
        if (JAVAVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        {
            LOGD("Failed to get the environment using GetEnv()");
            break;
        }

        if (JAVAVM->AttachCurrentThread(&env, 0) < 0)
        {
            LOGD("Failed to get the environment using AttachCurrentThread()");
            break;
        }

        bRet = true;
    } while (0);        

    if (!bRet) {
    	env = NULL; 
    }

    return env;
}

std::map<PluginProtocol*, PluginJavaData*> s_PluginObjMap;

typedef std::map<PluginProtocol*, PluginJavaData*>::iterator ObjMapIter;

PluginJavaData* PluginUtils::getPluginJavaData(PluginProtocol* pKeyObj)
{
    PluginJavaData* ret = NULL;
    ObjMapIter it = s_PluginObjMap.find(pKeyObj);
    if (it != s_PluginObjMap.end()) {
        ret = it->second;
    }

    return ret;
}

void PluginUtils::setPluginJavaData(PluginProtocol* pKeyObj, PluginJavaData* pData)
{
    erasePluginJavaData(pKeyObj);
    s_PluginObjMap.insert(std::pair<PluginProtocol*, PluginJavaData*>(pKeyObj, pData));
}

void PluginUtils::erasePluginJavaData(PluginProtocol* pKeyObj)
{
    ObjMapIter it = s_PluginObjMap.find(pKeyObj);
    if (it != s_PluginObjMap.end()) {
        PluginJavaData* pData = it->second;
        if (pData != NULL)
        {
            jobject jobj = pData->jobj;
            JNIEnv* pEnv = getEnv();
            LOGD("Delete global reference.");
            pEnv->DeleteGlobalRef(jobj);
            delete pData;
        }
        s_PluginObjMap.erase(it);
    }
}

}}// namespace cocos2d { namespace plugin {
