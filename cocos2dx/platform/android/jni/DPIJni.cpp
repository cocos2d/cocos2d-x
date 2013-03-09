#include "DPIJni.h"
#include "jni/JniHelper.h"

USING_NS_CC;

extern "C" {

int getDPIJNI()
{
    JniMethodInfo t;
    jint ret = -1;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxHelper", "getDPI", "()I")) {
        ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

} // extern "C"