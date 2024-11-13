#include <stdlib.h>
#include <string>
#include "NapiHelper.h"
#include "Js_Cocos2dxHelper.h"
#include "platform/ohos/CCLogOhos.h"

napi_env Js_Cocos2dxHelper::_env = nullptr;
napi_value Js_Cocos2dxHelper::initJsCocos2dxHelper(napi_env env, napi_callback_info info) {
    _env = env;
    return 0;
}

/**
 * If you have more information that can be obtained asynchronously, add it here.
 */
napi_value Js_Cocos2dxHelper::initAsyncInfo(napi_env env, napi_callback_info info) {
    JSFunction::getFunction("DeviceUtils.initScreenInfo").invoke<void>();
    return nullptr;
}

std::string Js_Cocos2dxHelper::_asyncInfoMap[AsyncInfo::LAST_INDEX];

void Js_Cocos2dxHelper::terminateProcess() {
    JSFunction::getFunction("ApplicationManager.exit").invoke<void>();
}

// The default accelerometer interval is 10000000 ns, that is, 10 ms.
float Js_Cocos2dxHelper::_accelerometerInterval = 10000000.0f;
bool Js_Cocos2dxHelper::_accelerometerFlag = false;
void Js_Cocos2dxHelper::enableAccelerometer() {
    // Start accelerometer subscription when allowed use default interval
    JSFunction::getFunction("Accelerometer.enable").invoke<void>(_accelerometerInterval);
    _accelerometerFlag = true;
}
    
void Js_Cocos2dxHelper::disableAccelerometer() {
    JSFunction::getFunction("Accelerometer.disable").invoke<void>();
    _accelerometerFlag = false;
}

void Js_Cocos2dxHelper::setAccelerometerInterval(float interval) {
    OHOS_LOGD("accelerometer setAccelerometerInterval, change to %{public}f", interval);
    // Same as the original one. No handling is required.
    if(_accelerometerInterval == interval) {
        return;
    }
    _accelerometerInterval = interval;

    // if accelerometer running, restart with new interval
    if(_accelerometerFlag) {
        JSFunction::getFunction("Accelerometer.enable").invoke<void>(_accelerometerInterval);
    }
}

