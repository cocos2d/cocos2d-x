#include "PaySDKNapi.h"
#include "../common/native_common.h"
#include "../sdk_plugin_manager.h"
#include "../../CCSDKLogOhos.h"
#include "../../CCSDKApplication.h"
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>

napi_value PaySDKNapi::onPaySDKCallBack(napi_env env, napi_callback_info info) {

    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    status = napi_typeof(env, args[0], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    size_t pInt;
    char result[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0],result,256, &pInt));
    cocos2d::SDKApplication::executePaySDKCallback(result);
    OHOS_LOGD("==========pullSDK executePaySDKCallback.=========");
    return nullptr;
}