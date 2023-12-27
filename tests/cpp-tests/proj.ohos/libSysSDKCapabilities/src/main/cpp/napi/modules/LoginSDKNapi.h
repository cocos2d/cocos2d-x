#include <napi/native_api.h>

class LoginSDKNapi {
public:
    static napi_value onLoginSDKCallBack(napi_env env, napi_callback_info info);
};