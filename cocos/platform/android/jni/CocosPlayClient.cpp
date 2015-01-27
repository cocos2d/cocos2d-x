/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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
#include "CocosPlayClient.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <map>
#include "jni/JniHelper.h"
#include "platform/CCCommon.h"

using namespace cocos2d;

#define LOG_TAG    "CocosPlayClient.cpp"
#if COCOS2D_DEBUG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)
#define LOGW(...)
#define LOGE(...)
#endif

static std::string __gameRootPath;
static std::unordered_map<std::string, bool> __fileExistsCaches;
static bool __isCocosPlayInited = false;
static bool __isCocosPlayEnabled = false;
static bool __isDemo = false;
static bool __isNotifyFileLoadedEnabled = false;
static jobject __classLoader;
static jmethodID __findClassMethod;
static pthread_key_t __threadKey;


#define COCOSPLAYCLIENT_CLASS_NAME "com/chukong/cocosplay/client/CocosPlayClient"

extern "C" {
    jobjectArray Java_com_chukong_cocosplay_client_CocosPlayClient_getSearchPaths(JNIEnv*  env, jobject thiz)
    {
        auto stringClass = env->FindClass("java/lang/String");
        auto& paths = cocos2d::FileUtils::getInstance()->getSearchPaths();
        auto count = paths.size();
        auto pathArray = env->NewObjectArray(count, stringClass, 0);
        for (int i = 0; i < count; ++i)
        {
            env->SetObjectArrayElement(pathArray, i, env->NewStringUTF(paths[i].c_str()));
        }
    
        return pathArray;
    }
}

namespace cocosplay {

static void detachCurrentThread(void *env) {
    JniHelper::getJavaVM()->DetachCurrentThread();
}

static bool getEnv(JNIEnv **env)
{
    bool bRet = false;

    switch(JniHelper::getJavaVM()->GetEnv((void**)env, JNI_VERSION_1_4))
    {
    case JNI_OK:
        bRet = true;
        break;
    case JNI_EDETACHED:
        pthread_key_create (&__threadKey, detachCurrentThread);
        if (JniHelper::getJavaVM()->AttachCurrentThread(env, 0) < 0)
        {
            LOGD("%s", "Failed to get the environment using AttachCurrentThread()");
            break;
        }
        if (pthread_getspecific(__threadKey) == NULL) {
            pthread_setspecific(__threadKey, env);
        }
        bRet = true;
        break;
    default:
        LOGE("%s", "Failed to get the environment using GetEnv()");
        break;
    }

    return bRet;
}

static void initClassLoaderForMultiThread()
{
    JNIEnv *env = 0;
    do
    {
        if (! getEnv(&env))
        {
            break;
        }
        jclass cocos2dClass = env->FindClass(COCOSPLAYCLIENT_CLASS_NAME);
        if(env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
            LOGW("Exception initClassLoaderForMultiThread cocos2dClass is exception");
            break;
        }

        jclass classClass = env->GetObjectClass(cocos2dClass);
        if(env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
            LOGW("Exception initClassLoaderForMultiThread classClass is exception");
            break;
        }

        jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
        if(env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
            LOGW("Exception initClassLoaderForMultiThread classLoaderClass");
            break;
        }

        jmethodID getClassLoaderMethod = env->GetMethodID(classClass,"getClassLoader","()Ljava/lang/ClassLoader;");
        jobject classLoader = env->CallObjectMethod(cocos2dClass, getClassLoaderMethod);
        if(env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
            LOGW("Exception initClassLoaderForMultiThread classLoader");
            break;
        }
        __classLoader = env->NewGlobalRef(classLoader);
        jmethodID findClassMethod = env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        __findClassMethod = findClassMethod;

        if(env->ExceptionCheck())
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
            __findClassMethod = NULL;
            __classLoader = NULL;
            LOGW("Exception initClassLoaderForMultiThread findClassMethod");
            break;
        }
    }while(0);
}

static jclass getClassID_(const char *className, JNIEnv *env)
{
    JNIEnv *pEnv = env;
    jclass ret = 0;

    do
    {
        if (! pEnv)
        {
            if (! getEnv(&pEnv))
            {
                break;
            }
        }

        ret = pEnv->FindClass(className);
        if (! ret)
        {
            if(__classLoader)
            {
                pEnv->ExceptionClear();
                jstring jstrName = (pEnv)->NewStringUTF(className);
                ret = (jclass)pEnv->CallObjectMethod(__classLoader, __findClassMethod, jstrName);
                pEnv->DeleteLocalRef(jstrName);
                if(ret) break;
            }

            LOGE("Failed to find class of %s", className);
            break;
        }
    } while (0);

    return ret;
}

static bool getStaticMethodInfo(cocos2d::JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
{
    jmethodID methodID = 0;
    JNIEnv *pEnv = 0;
    bool bRet = false;

    do
    {
        if (! getEnv(&pEnv))
        {
            break;
        }

        jclass classID = getClassID_(className, pEnv);
        if(!classID) break;

        methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
        if (! methodID)
        {
            LOGW("Failed to find static method id of %s", methodName);
            break;
        }

        methodinfo.classID = classID;
        methodinfo.env = pEnv;
        methodinfo.methodID = methodID;

        bRet = true;
    } while (0);

    return bRet;
}

void lazyInit()
{
    if (__isCocosPlayInited)
        return;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "isEnabled", "()Z"))
    {
        __isCocosPlayEnabled = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        LOGD("isEnabled = %d", __isCocosPlayEnabled);
    }

    if (JniHelper::getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "isDemo", "()Z"))
    {
        __isDemo = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        LOGD("isDemo = %d",__isDemo);
    }

    if (JniHelper::getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "isNotifyFileLoadedEnabled", "()Z"))
    {
        __isNotifyFileLoadedEnabled = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        LOGD("isNotifyFileLoadedEnabled = %d", __isNotifyFileLoadedEnabled);
    }

    if (__isCocosPlayEnabled)
    {
        initClassLoaderForMultiThread();
    }

    __isCocosPlayInited = true;
}

bool isEnabled()
{
    return __isCocosPlayEnabled;
}

bool isDemo()
{
    return __isDemo;
}

void updateAssets(const std::string& filePath)
{
    if (!__isCocosPlayInited)
    {
        lazyInit();
    }

    if (!__isCocosPlayEnabled || __isDemo)
    {
        return;
    }

    if (!fileExists(filePath))
    {
        LOGD("file ( %s ) doesn't exist, updateAssets cancelled", filePath.c_str());
        return;
    }

    JniMethodInfo t;
    if (getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "updateAssets", "(Ljava/lang/String;)V"))
    {
        jstring stringArg = t.env->NewStringUTF(filePath.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
        t.env->DeleteLocalRef(stringArg);
        t.env->DeleteLocalRef(t.classID);
    }

    LOGD("updateAssets (%s) OK!", filePath.c_str());
}

bool fileExists(const std::string& filePath)
{
    auto iter = __fileExistsCaches.find(filePath);
    if (iter != __fileExistsCaches.end())
    {
        LOGD("Return file path ( %s ) in cache!", filePath.c_str());
        if(!iter->second)
        {
            auto fp = fopen(filePath.c_str(), "r");
            if (fp)
            {
                iter->second = true;
                fclose(fp);
            }
        }
        return iter->second;
    }

    bool ret = false;
    JniMethodInfo t;
    if (getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "fileExists", "(Ljava/lang/String;)Z"))
    {
        jstring stringArg = t.env->NewStringUTF(filePath.c_str());
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg);
        t.env->DeleteLocalRef(stringArg);
        t.env->DeleteLocalRef(t.classID);
    }

    __fileExistsCaches[filePath] = ret;

    LOGD("fileExists return (%d), path (%s)!", ret, filePath.c_str());
    return ret;
}

void notifyFileLoaded(const std::string& filePath)
{
    if (!__isNotifyFileLoadedEnabled)
        return;

    JniMethodInfo t;
    if (getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "notifyFileLoaded", "(Ljava/lang/String;)V"))
    {
        jstring stringArg = t.env->NewStringUTF(filePath.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg);
        t.env->DeleteLocalRef(stringArg);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string getGameRoot()
{
    if (!__isCocosPlayEnabled)
    {
        LOGW("CocosPlayClient isn't enabled!");
        return "";
    }

    if (__gameRootPath.empty())
    {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "getGameRoot", "()Ljava/lang/String;"))
        {
            jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            __gameRootPath = JniHelper::jstring2string(str);
            t.env->DeleteLocalRef(str);
            t.env->DeleteLocalRef(t.classID);
        }
        LOGD("GameRoot : %s", __gameRootPath.c_str());
    }
    return __gameRootPath;
}

void purgeCachedEntries()
{
    __fileExistsCaches.clear();
}

void purgeCachedByFile(const std::string& filePath)
{
    __fileExistsCaches.erase(filePath);
}

void notifyDemoEnded()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, COCOSPLAYCLIENT_CLASS_NAME, "notifyDemoEnded", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        LOGD("Game demo was ended!");
    }
}

} // namespace cocosplay {

#else

namespace cocosplay {

bool isEnabled() { return false; }
bool isDemo() { return false; }
void updateAssets(const std::string& filePath) {}
bool fileExists(const std::string& filePath) { return false; }
void notifyFileLoaded(const std::string& filePath) {}
std::string getGameRoot() { return ""; }
void purgeCachedEntries() {}
void notifyDemoEnded() {}
void purgeCachedByFile(const std::string& filePath){}
} // namespace cocosplay {

#endif
