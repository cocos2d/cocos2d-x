#include <js_native_api.h>
#include <js_native_api_types.h>
#include "cocos2d.h"
#include "base/CCEventAcceleration.h"
#include "platform/ohos/CCLogOhos.h"
#include "SensorNapi.h"
#include "../common/native_common.h"

napi_value SensorNapi::onAccelerometerCallBack(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 4;
    napi_value args[4];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 4) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    status = napi_typeof(env, args[0], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    status = napi_typeof(env, args[3], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    double x;
    NAPI_CALL(env, napi_get_value_double(env, args[0], &x));
    double y;
    NAPI_CALL(env, napi_get_value_double(env, args[1], &y));
    double z;
    NAPI_CALL(env, napi_get_value_double(env, args[2], &z));
    long timestamp;
    NAPI_CALL(env, napi_get_value_int64(env, args[3], &timestamp));
    
    dispatchAccelerometer(x, y, z, timestamp);
    return nullptr;
}

#define TG3_GRAVITY_EARTH                    (9.80665f)

void SensorNapi::dispatchAccelerometer(double x, double y, double z, long timeStamp) {
    OHOS_LOGD("accelerometer callback, interval is %{public}d", timeStamp);
    cocos2d::Acceleration a;
    a.x = -(x / TG3_GRAVITY_EARTH);
    a.y = -(y / TG3_GRAVITY_EARTH);
    a.z = -(z / TG3_GRAVITY_EARTH);
    a.timestamp = (double)timeStamp;

    cocos2d::EventAcceleration event(a);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}