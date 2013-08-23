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
#include "PluginJniHelper.h"
#include <android/log.h>
#include <string.h>

#if 1
#define  LOG_TAG    "PluginJniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

#define JAVAVM    cocos2d::PluginJniHelper::getJavaVM()

using namespace std;

extern "C"
{

    //////////////////////////////////////////////////////////////////////////
    // java vm helper function
    //////////////////////////////////////////////////////////////////////////

    static jclass _getClassIDByLoader(const char *className) {
        if (NULL == className) {
            return NULL;
        }

        JNIEnv* env = cocos2d::PluginJniHelper::getEnv();

        jstring _jstrClassName = env->NewStringUTF(className);

        jclass _clazz = (jclass) env->CallObjectMethod(cocos2d::PluginJniHelper::classloader,
                                                       cocos2d::PluginJniHelper::loadclassMethod_methodID,
                                                       _jstrClassName);

        if (NULL == _clazz) {
            LOGD("Classloader failed to find class of %s", className);
        }

        env->DeleteLocalRef(_jstrClassName);

        return _clazz;
    }

    static jclass _getClassID(const char *className, JNIEnv *env)
    {
        JNIEnv *pEnv = env;
        jclass ret = 0;

        do 
        {
            if (cocos2d::PluginJniHelper::classloader)
            {
                ret = _getClassIDByLoader(className);
                break;
            }

            if (! pEnv)
            {
                pEnv = cocos2d::PluginJniHelper::getEnv();
                if (! pEnv)
                {
                    break;
                }
            }

            ret = pEnv->FindClass(className);
            if (! ret)
            {
                 LOGD("Failed to find class of %s", className);
                break;
            }
        } while (0);

        return ret;
    }
}

namespace cocos2d {

JavaVM* PluginJniHelper::_psJavaVM = NULL;
jmethodID PluginJniHelper::loadclassMethod_methodID = NULL;
jobject PluginJniHelper::classloader = NULL;
JNIEnv* PluginJniHelper::env = NULL;

JavaVM* PluginJniHelper::getJavaVM()
{
    return _psJavaVM;
}

void PluginJniHelper::setJavaVM(JavaVM *javaVM)
{
    _psJavaVM = javaVM;
    PluginJniHelper::cacheEnv(javaVM);
}

JNIEnv* PluginJniHelper::getEnv()
{
    return env;
}

bool PluginJniHelper::getStaticMethodInfo(PluginJniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
{
    if ((NULL == className) ||
        (NULL == methodName) ||
        (NULL == paramCode)) {
        return false;
    }

    JNIEnv *pEnv = PluginJniHelper::getEnv();
    if (!pEnv) {
        LOGD("Failed to get JNIEnv");
        return false;
    }

    jclass classID = _getClassID(className, pEnv);
    if (! classID) {
        LOGD("Failed to find class %s", className);
        return false;
    }

    jmethodID methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
    if (! methodID) {
        LOGD("Failed to find static method id of %s", methodName);
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = pEnv;
    methodinfo.methodID = methodID;
    return true;
}

bool PluginJniHelper::getMethodInfo(PluginJniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
{
    if ((NULL == className) ||
        (NULL == methodName) ||
        (NULL == paramCode)) {
        return false;
    }

    JNIEnv *pEnv = PluginJniHelper::getEnv();
    if (!pEnv) {
        return false;
    }

    jclass classID = _getClassID(className, pEnv);
    if (! classID) {
        LOGD("Failed to find class %s", className);
        return false;
    }

    jmethodID methodID = pEnv->GetMethodID(classID, methodName, paramCode);
    if (! methodID) {
        LOGD("Failed to find method id of %s", methodName);
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = pEnv;
    methodinfo.methodID = methodID;

    return true;
}

string PluginJniHelper::jstring2string(jstring jstr)
{
    if (jstr == NULL) {
        return "";
    }

    JNIEnv *pEnv = PluginJniHelper::getEnv();
    if (!env) {
        return NULL;
    }

    const char* chars = env->GetStringUTFChars(jstr, NULL);
    std::string ret(chars);
    env->ReleaseStringUTFChars(jstr, chars);

    return ret;
}

bool PluginJniHelper::setClassLoaderFrom(jobject nativeactivityinstance) {
    PluginJniMethodInfo _getclassloaderMethod;
    if (!PluginJniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod,
                                                     "android/app/NativeActivity",
                                                     "getClassLoader",
                                                     "()Ljava/lang/ClassLoader;")) {
        return false;
    }

    jobject _c = cocos2d::PluginJniHelper::getEnv()->CallObjectMethod(nativeactivityinstance,
                                                                _getclassloaderMethod.methodID);

    if (NULL == _c) {
        return false;
    }

    PluginJniMethodInfo _m;
    if (!PluginJniHelper::getMethodInfo_DefaultClassLoader(_m,
                                                     "java/lang/ClassLoader",
                                                     "loadClass",
                                                     "(Ljava/lang/String;)Ljava/lang/Class;")) {
        return false;
    }

    PluginJniHelper::classloader = _c;
    PluginJniHelper::loadclassMethod_methodID = _m.methodID;

    return true;
}

bool PluginJniHelper::cacheEnv(JavaVM* jvm)
{
    JNIEnv* _env = NULL;
    // get jni environment
    jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_4);

    switch (ret) {
    case JNI_OK :
        // Success!
        PluginJniHelper::env = _env;
        return true;

    case JNI_EDETACHED :
        // Thread not attached

        // TODO : If calling AttachCurrentThread() on a native thread
        // must call DetachCurrentThread() in future.
        // see: http://developer.android.com/guide/practices/design/jni.html

        if (jvm->AttachCurrentThread(&_env, NULL) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");

                PluginJniHelper::env = NULL;
                return false;
            } else {
            // Success : Attached and obtained JNIEnv!
            PluginJniHelper::env = _env;
            return true;
        }

    case JNI_EVERSION :
        // Cannot recover from this error
        LOGD("JNI interface version 1.4 not supported");
    default :
        LOGD("Failed to get the environment using GetEnv()");
        PluginJniHelper::env = NULL;
        return false;
    }
}

bool PluginJniHelper::getMethodInfo_DefaultClassLoader(PluginJniMethodInfo &methodinfo,
                                                     const char *className,
                                                     const char *methodName,
                                                     const char *paramCode)
{
    if ((NULL == className) ||
        (NULL == methodName) ||
        (NULL == paramCode)) {
        return false;
    }

    JNIEnv *pEnv = PluginJniHelper::getEnv();
    if (!pEnv) {
        return false;
    }

    jclass classID = pEnv->FindClass(className);
    if (! classID) {
        LOGD("Failed to find class %s", className);
        return false;
    }

    jmethodID methodID = pEnv->GetMethodID(classID, methodName, paramCode);
    if (! methodID) {
        LOGD("Failed to find method id of %s", methodName);
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = pEnv;
    methodinfo.methodID = methodID;

    return true;
}

} // end of namespace cocos2d
