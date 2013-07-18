/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
#include "JniHelper.h"
#include <android/log.h>
#include <string.h>
#include <pthread.h>

#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C"
{

    static JNIEnv* _getJNIEnv(void) {
        
        JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
        if (NULL == jvm) {
            LOGD("Failed to get JNIEnv. JniHelper::getJavaVM() is NULL");
            return NULL;
        }
        
        JNIEnv *env = NULL;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
        
        switch (ret) {
        case JNI_OK :
            // Success!
            return env;
                
        case JNI_EDETACHED :
            // Thread not attached
                
            // TODO : If calling AttachCurrentThread() on a native thread
            // must call DetachCurrentThread() in future.
            // see: http://developer.android.com/guide/practices/design/jni.html
                
            if (jvm->AttachCurrentThread(&env, NULL) < 0)
                {
                    LOGD("Failed to get the environment using AttachCurrentThread()");
                    return NULL;
                } else {
                // Success : Attached and obtained JNIEnv!
                return env;
            }
                
        case JNI_EVERSION :
            // Cannot recover from this error
            LOGD("JNI interface version 1.4 not supported");
        default :
            LOGD("Failed to get the environment using GetEnv()");
            return NULL;
        }
    }

    jclass _getClassID(const char *className, JNIEnv *env) {
        if (NULL == className) {
            return NULL;
        }

        jclass ret = env->FindClass(className);
        if (!ret) {
            LOGD("Failed to find class of %s", className);
        }
        
        return ret;
    }


}

namespace cocos2d {

    JavaVM* JniHelper::_psJavaVM = NULL;

    JavaVM* JniHelper::getJavaVM() {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::getJavaVM(), pthread_self() = %X", thisthread);
        return _psJavaVM;
    }

    void JniHelper::setJavaVM(JavaVM *javaVM) {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::setJavaVM(%p), pthread_self() = %X", javaVM, thisthread);
        _psJavaVM = javaVM;
    }

    bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo,
                                        const char *className, 
                                        const char *methodName,
                                        const char *paramCode) {
        if ((NULL == className) ||
            (NULL == methodName) ||
            (NULL == paramCode)) {
            return false;
        }

        JNIEnv *pEnv = _getJNIEnv();
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

    bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo,
                                  const char *className,
                                  const char *methodName,
                                  const char *paramCode) {
        if ((NULL == className) ||
            (NULL == methodName) ||
            (NULL == paramCode)) {
            return false;
        }

        JNIEnv *pEnv = _getJNIEnv();
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

    std::string JniHelper::jstring2string(jstring jstr) {
        if (jstr == NULL) {
            return "";
        }
        
        JNIEnv *env = _getJNIEnv();
        if (!env) {
            return NULL;
        }

        const char* chars = env->GetStringUTFChars(jstr, NULL);
        std::string ret(chars);
        env->ReleaseStringUTFChars(jstr, chars);

        return ret;
    }

} //namespace cocos2d
