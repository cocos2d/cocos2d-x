#include <js_native_api.h>
#include <js_native_api_types.h>

#include "WebViewNapi.h"
#include "platform/ohos/napi/plugin_manager.h"
#include "../../CCLogOhos.h"
#include "ui/UIWebView/UIWebViewImpl-ohos.h"

napi_value WebViewNapi::shouldStartLoading(napi_env env, napi_callback_info info) {

    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 2) {
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

    status = napi_typeof(env, args[1], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    int32_t viewTag;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &viewTag));
    size_t pInt;
    char url[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[1], url, 256, &pInt));

    cocos2d::ui::WebViewImpl::shouldStartLoading(viewTag, url);
    return nullptr;
}

napi_value WebViewNapi::finishLoading(napi_env env, napi_callback_info info) {

    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 2) {
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

    status = napi_typeof(env, args[1], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    int32_t viewTag;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &viewTag));
    size_t pInt;
    char url[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[1], url, 256, &pInt));

    cocos2d::ui::WebViewImpl::finishLoading(viewTag, url);
    return nullptr;
}

napi_value WebViewNapi::failLoading(napi_env env, napi_callback_info info) {

    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 2) {
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

    status = napi_typeof(env, args[1], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    int32_t viewTag;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &viewTag));
    size_t pInt;
    char url[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[1], url, 256, &pInt));

    cocos2d::ui::WebViewImpl::failLoading(viewTag, url);
    return nullptr;
}

napi_value WebViewNapi::jsCallback(napi_env env, napi_callback_info info) {

    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    if (argc != 2) {
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

    status = napi_typeof(env, args[1], &valuetype);
    if (status != napi_ok) {
        return nullptr;
    }
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    int32_t viewTag;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &viewTag));
    size_t pInt;
    char url[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[1], url, 256, &pInt));

    cocos2d::ui::WebViewImpl::jsCallback(viewTag, url);
    return nullptr;
}