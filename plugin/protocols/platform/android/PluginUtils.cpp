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
#include "PluginUtils.h"
#include <android/log.h>
#include <map>

#define MAX_LOG_LEN			256

namespace cocos2d { namespace plugin {

#define JAVAVM    cocos2d::PluginJniHelper::getJavaVM()

void PluginUtils::initPluginWrapper(android_app* app)
{
    PluginJniMethodInfo t;
    if (! PluginJniHelper::getStaticMethodInfo(t
        , "org/cocos2dx/plugin/PluginWrapper"
        , "initFromNativeActivity"
        , "(Landroid/app/Activity;)V"))
    {
        outputLog("PluginUtils", "Failed to init context of plugin");
        return;
    }

    t.env->CallStaticVoidMethod(t.classID, t.methodID, app->activity->clazz);
    t.env->DeleteLocalRef(t.classID);
}

jobject PluginUtils::createJavaMapObject(std::map<std::string, std::string>* paramMap)
{
    JNIEnv* env = getEnv();
	jclass class_Hashtable = env->FindClass("java/util/Hashtable");
	jmethodID construct_method = env->GetMethodID( class_Hashtable, "<init>","()V");
	jobject obj_Map = env->NewObject( class_Hashtable, construct_method, "");
	if (paramMap != NULL)
	{
		jmethodID add_method= env->GetMethodID( class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
		for (std::map<std::string, std::string>::const_iterator it = paramMap->begin(); it != paramMap->end(); ++it)
		{
            jstring first = env->NewStringUTF(it->first.c_str());
            jstring second = env->NewStringUTF(it->second.c_str());
			env->CallObjectMethod(obj_Map, add_method, first, second);
            env->DeleteLocalRef(first);
            env->DeleteLocalRef(second);
		}
	}
    env->DeleteLocalRef(class_Hashtable);
    return obj_Map;
}

void PluginUtils::initJavaPlugin(PluginProtocol* pPlugin, jobject jObj, const char* className)
{
	cocos2d::plugin::PluginJavaData* pUserData = new cocos2d::plugin::PluginJavaData();
	pUserData->jobj = PluginUtils::getEnv()->NewGlobalRef(jObj);
	pUserData->jclassName = className;
	cocos2d::plugin::PluginUtils::setPluginJavaData(pPlugin, pUserData);
}

JNIEnv* PluginUtils::getEnv()
{
    bool bRet = false;
    JNIEnv* env = NULL;
    do 
    {
        if (JAVAVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        {
        	outputLog("PluginUtils", "Failed to get the environment using GetEnv()");
            break;
        }

        if (JAVAVM->AttachCurrentThread(&env, 0) < 0)
        {
            outputLog("PluginUtils", "Failed to get the environment using AttachCurrentThread()");
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
std::map<std::string, PluginProtocol*> s_JObjPluginMap;

typedef std::map<PluginProtocol*, PluginJavaData*>::iterator ObjMapIter;
typedef std::map<std::string, PluginProtocol*>::iterator JObjPluginMapIter;

PluginJavaData* PluginUtils::getPluginJavaData(PluginProtocol* pKeyObj)
{
    PluginJavaData* ret = NULL;
    ObjMapIter it = s_PluginObjMap.find(pKeyObj);
    if (it != s_PluginObjMap.end()) {
        ret = it->second;
    }

    return ret;
}

PluginProtocol* PluginUtils::getPluginPtr(std::string className)
{
	PluginProtocol* ret = NULL;
	JObjPluginMapIter it = s_JObjPluginMap.find(className);
	if (it != s_JObjPluginMap.end()) {
		ret = it->second;
	}

	return ret;
}

void PluginUtils::setPluginJavaData(PluginProtocol* pKeyObj, PluginJavaData* pData)
{
    erasePluginJavaData(pKeyObj);
    s_PluginObjMap.insert(std::pair<PluginProtocol*, PluginJavaData*>(pKeyObj, pData));
    s_JObjPluginMap.insert(std::pair<std::string, PluginProtocol*>(pData->jclassName, pKeyObj));
}

void PluginUtils::erasePluginJavaData(PluginProtocol* pKeyObj)
{
    ObjMapIter it = s_PluginObjMap.find(pKeyObj);
    if (it != s_PluginObjMap.end()) {
        PluginJavaData* pData = it->second;
        if (pData != NULL)
        {
            jobject jobj = pData->jobj;

            JObjPluginMapIter pluginIt = s_JObjPluginMap.find(pData->jclassName);
            if (pluginIt != s_JObjPluginMap.end())
            {
            	s_JObjPluginMap.erase(pluginIt);
            }

            JNIEnv* pEnv = getEnv();
            outputLog("PluginUtils", "Delete global reference.");
            pEnv->DeleteGlobalRef(jobj);
            delete pData;
        }
        s_PluginObjMap.erase(it);
    }
}

void PluginUtils::outputLog(const char* logTag, const char* pFormat, ...)
{
	char buf[MAX_LOG_LEN + 1];

	va_list args;
	va_start(args, pFormat);
	vsnprintf(buf, MAX_LOG_LEN, pFormat, args);
	va_end(args);

	__android_log_print(ANDROID_LOG_DEBUG, logTag, "%s", buf);
}

jobject PluginUtils::getJObjFromParam(PluginParam* param)
{
	if (NULL == param)
	{
		return NULL;
	}

	jobject obj = NULL;
	PluginJniMethodInfo t;
	JNIEnv* env = PluginUtils::getEnv();

	switch(param->getCurrentType())
	{
	case PluginParam::kParamTypeInt:
		if (PluginJniHelper::getStaticMethodInfo(t, "java/lang/Integer", "valueOf", "(I)Ljava/lang/Integer;"))
		{
			obj = t.env->CallStaticObjectMethod(t.classID, t.methodID, param->getIntValue());
			t.env->DeleteLocalRef(t.classID);
		}
		break;
	case PluginParam::kParamTypeFloat:
		if (PluginJniHelper::getStaticMethodInfo(t, "java/lang/Float", "valueOf", "(F)Ljava/lang/Float;"))
		{
			obj = t.env->CallStaticObjectMethod(t.classID, t.methodID, param->getFloatValue());
			t.env->DeleteLocalRef(t.classID);
		}
		break;
	case PluginParam::kParamTypeBool:
		if (PluginJniHelper::getStaticMethodInfo(t, "java/lang/Boolean", "valueOf", "(Z)Ljava/lang/Boolean;"))
		{
			obj = t.env->CallStaticObjectMethod(t.classID, t.methodID, param->getBoolValue());
			t.env->DeleteLocalRef(t.classID);
		}
		break;
	case PluginParam::kParamTypeString:
		obj = env->NewStringUTF(param->getStringValue());
		break;
	case PluginParam::kParamTypeStringMap:
	    {
	        jclass cls = env->FindClass("org/json/JSONObject");
            jmethodID mid = env->GetMethodID(cls,"<init>","()V");
            obj = env->NewObject(cls,mid);
            env->DeleteLocalRef(cls);
            std::map<std::string, std::string>::iterator it;
            std::map<std::string, std::string> mapParam = param->getStrMapValue();
            for (it = mapParam.begin(); it != mapParam.end(); it++)
            {
                PluginJniMethodInfo tInfo;
                if (PluginJniHelper::getMethodInfo(tInfo, "org/json/JSONObject", "put", "(Ljava/lang/String;Ljava/lang/Object;)Lorg/json/JSONObject;"))
                {
                    jstring strKey = tInfo.env->NewStringUTF(it->first.c_str());
                    jstring strValue = tInfo.env->NewStringUTF(it->second.c_str());

                    tInfo.env->CallObjectMethod(obj, tInfo.methodID, strKey, strValue);
                    tInfo.env->DeleteLocalRef(tInfo.classID);

                    tInfo.env->DeleteLocalRef(strKey);
                    tInfo.env->DeleteLocalRef(strValue);
                }
            }
        }
	    break;
	case PluginParam::kParamTypeMap:
		{
			jclass cls = env->FindClass("org/json/JSONObject");
			jmethodID mid = env->GetMethodID(cls,"<init>","()V");
			obj = env->NewObject(cls,mid);
            env->DeleteLocalRef(cls);
			std::map<std::string, PluginParam*>::iterator it;
			std::map<std::string, PluginParam*> mapParam = param->getMapValue();
			for (it = mapParam.begin(); it != mapParam.end(); it++)
			{
				PluginJniMethodInfo tInfo;
				if (PluginJniHelper::getMethodInfo(tInfo, "org/json/JSONObject", "put", "(Ljava/lang/String;Ljava/lang/Object;)Lorg/json/JSONObject;"))
				{
					jstring strKey = tInfo.env->NewStringUTF(it->first.c_str());
					jobject objValue = PluginUtils::getJObjFromParam(it->second);

					tInfo.env->CallObjectMethod(obj, tInfo.methodID, strKey, objValue);
					tInfo.env->DeleteLocalRef(tInfo.classID);

					tInfo.env->DeleteLocalRef(strKey);
					PluginUtils::getEnv()->DeleteLocalRef(objValue);
				}
			}
		}
		break;
	default:
		break;
	}

	return obj;
}

}}// namespace cocos2d { namespace plugin {
