#ifndef __Js_Cocos2dxHelper_H__
#define __Js_Cocos2dxHelper_H__

#include <new>
#include <string>
#include <hilog/log.h>
#include <napi/native_api.h>

#define APP_LOG_DOMAIN 0x0001
#define APP_LOG_TAG "Js_Cocos2dxHelper"
#define LOGI(...) ((void)OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))

enum AsyncInfo {
    // VERSION_NAME = 0,
    LAST_INDEX // 仅为表明用于保存数据的数组大小，无意义，后续如新增枚举，请保持 LAST_INDEX 在最后一个
};

class Js_Cocos2dxHelper
{
public:
    static napi_value initJsCocos2dxHelper(napi_env env, napi_callback_info info);
    static napi_value initAsyncInfo(napi_env env, napi_callback_info info);
    static void setAsyncInfo(AsyncInfo key, const std::string& value) {
        _asyncInfoMap[key] = value;
    }

    static std::string getAsyncInfo(AsyncInfo key) {
        return _asyncInfoMap[key];
    }

    static void terminateProcess();
    static void enableAccelerometer();
    static void disableAccelerometer();
    static void setAccelerometerInterval(float interval);
    
private:
    static std::string _asyncInfoMap[];
    static napi_env _env;
    static float _accelerometerInterval;
    static bool _accelerometerFlag;
};
#endif /* __Js_Cocos2dxHelper_H__ */
