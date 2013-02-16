#include "DPIJni.h"
#include "jni/JniHelper.h"

USING_NS_CC;

extern "C" {

float getDPIJNI()
{
    JniMethodInfo t;
    jfloat ret = 0.0f;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getDPI", "()F")) {
        ret = t.env->CallStaticFloatMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return ret;
}

} // extern "C"