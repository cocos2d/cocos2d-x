#include "JniHelper.h"
#include <jni.h>
#include <android/sensor.h>
#include "base/CCDirector.h"
#include "base/CCEvent.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventSensor.h"
#include "base/ccTypes.h"

using namespace cocos2d;

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxSensor_onSensorChanged(JNIEnv*  env, jobject thiz, jint sensorType, jfloatArray sensorValues, jlong timeStamp) {
        jsize len = env->GetArrayLength(sensorValues);
        jfloat *values = env->GetFloatArrayElements(sensorValues, 0);
        Sensor sensor;
        sensor.values.insert(sensor.values.end(), &values[0], &values[len]);
        sensor.sensorType = static_cast<SensorType>(sensorType);
        sensor.timestamp = (double)timeStamp;

        EventSensor event(sensor);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        env->ReleaseFloatArrayElements(sensorValues, values, 0);
    }
}

//ASENSOR_TYPE_ACCELEROMETER
