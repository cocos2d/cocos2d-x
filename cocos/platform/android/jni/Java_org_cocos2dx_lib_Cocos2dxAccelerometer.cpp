#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventAcceleration.h"

#define TG3_GRAVITY_EARTH                    (9.80665f)

using namespace cocos2d;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged(JNIEnv*  env, jobject thiz, jfloat x, jfloat y, jfloat z, jlong timeStamp) {
        Acceleration a;
        a.x = -((double)x / TG3_GRAVITY_EARTH);
        a.y = -((double)y / TG3_GRAVITY_EARTH);
        a.z = -((double)z / TG3_GRAVITY_EARTH);
        a.timestamp = (double)timeStamp / 1e9;

        EventAcceleration event(a);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }    
}
