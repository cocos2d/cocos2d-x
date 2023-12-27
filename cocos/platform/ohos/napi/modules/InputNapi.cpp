#include <js_native_api.h>
#include <js_native_api_types.h>
#include "InputNapi.h"
#include "platform/ohos/napi/plugin_manager.h"
#include "../../CCLogOhos.h"
#include "ui/UIEditBox/UIEditBoxImpl-ohos.h"
#include "base/CCIMEDispatcher.h"

napi_value InputNapi::editBoxOnChangeCB(napi_env env, napi_callback_info info) {

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

    int32_t index;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &index));
    size_t pInt;
    char text[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[1], text, 256, &pInt));

    cocos2d::ui::EditBoxImplOhos::onChangeCallBack(index, text);
    return nullptr;
}

napi_value InputNapi::editBoxOnEnterCB(napi_env env, napi_callback_info info) {

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

    int32_t index;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &index));
    size_t pInt;
    char text[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[1], text, 256, &pInt));

    cocos2d::ui::EditBoxImplOhos::onEnterCallBack(index, text);
    return nullptr;
}

napi_value InputNapi::textFieldTTFOnChangeCB(napi_env env, napi_callback_info info) {

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

    const char* oldStr = cocos2d::IMEDispatcher::sharedDispatcher()->getContentText().c_str();
    size_t pInt;
    char text[256];
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], text, 256, &pInt));

    // Calculate the difference position
    int oldIndex = 0;
    int newIndex = 0;
    while(oldIndex < strlen(oldStr) && newIndex < strlen(text)) {
        if(oldStr[oldIndex] != text[newIndex]) {
            break;
        }
        oldIndex++;
        newIndex++;
    }

    // Delete the characters after the difference position of the original character string.
    int oldLength = strlen(oldStr);
    for(; oldIndex < oldLength; oldIndex++) {
        cocos2d::IMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }

    // Truncate the part after the difference position of the new character string and insert it.
    if(strlen(text) > newIndex) {
        std::string newStr(text, sizeof(text));
        const char* modify = newStr.substr(newIndex).c_str();
        cocos2d::IMEDispatcher::sharedDispatcher()->dispatchInsertText(modify, strlen(modify));
    }

    return nullptr;
}