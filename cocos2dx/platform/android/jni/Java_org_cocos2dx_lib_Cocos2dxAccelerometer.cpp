#include "cocoa/CCGeometry.h"
#include "platform/android/CCAccelerometer.h"
#include "../CCEGLView.h"
#include "JniHelper.h"
#include <jni.h>
#include "CCDirector.h"

USING_NS_CC;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxAccelerometer_onSensorChanged(JNIEnv*  env, jobject thiz, jfloat x, jfloat y, jfloat z, jlong timeStamp) {
        Director* pDirector = Director::getInstance();
        pDirector->getAccelerometer()->update(x, y, z, timeStamp);
    }    
}
