#ifndef __PLUGIN_JNI_HELPER_H__
#define __PLUGIN_JNI_HELPER_H__

#include <jni.h>
#include <string>

namespace anysdk {namespace framework{

typedef struct PluginJniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} PluginJniMethodInfo;

class PluginJniHelper
{
public:
    static JavaVM* getJavaVM();
    static void setJavaVM(JavaVM *javaVM);
    static JNIEnv* getEnv();

    static bool getStaticMethodInfo(PluginJniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
    static bool getMethodInfo(PluginJniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
    static std::string jstring2string(jstring jstr);

    static bool setClassLoaderFrom(jobject nativeActivityInstance);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;

private:
    static JavaVM *_psJavaVM;
    static bool getMethodInfo_DefaultClassLoader(PluginJniMethodInfo &methodinfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode);
};

}}

#endif // __PLUGIN_JNI_HELPER_H__
