#ifndef _SENSOR_NAPI_H
#define _SENSOR_NAPI_H

#include <napi/native_api.h>

class SensorNapi {
public:
    static napi_value onAccelerometerCallBack(napi_env env, napi_callback_info info);

private:
    static void dispatchAccelerometer(double x, double y, double z, long timeStamp);
};

#endif //_SENSOR_NAPI_H