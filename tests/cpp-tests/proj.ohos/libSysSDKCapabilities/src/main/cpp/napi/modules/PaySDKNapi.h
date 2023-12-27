#include <napi/native_api.h>

class PaySDKNapi {
public:
    static napi_value onPaySDKCallBack(napi_env env, napi_callback_info info);
};