#include <js_native_api.h>
#include <js_native_api_types.h>
#include "InputNapi.h"
#include "platform/ohos/napi/plugin_manager.h"
#include "../../CCLogOhos.h"
#include "ui/UIEditBox/UIEditBoxImpl-ohos.h"
#include "base/CCIMEDispatcher.h"

napi_value InputNapi::editBoxOnFocusCB(napi_env env, napi_callback_info info) {

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
    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong arguments");
        return nullptr;
    }

    int32_t index;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &index));

    cocos2d::ui::EditBoxImplOhos::onBeginCallBack(index);
    return nullptr;
}

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

    auto dispatcher = cocos2d::IMEDispatcher::sharedDispatcher();
    const std::string& oldContent = dispatcher->getContentText();
    
    size_t textLen;
    char text[2560] = {0};
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], text, 2560, &textLen));


    std::string_view oldView(oldContent);
    std::string_view newView(text, textLen);

    size_t commonPrefixLen = 0;
    const size_t minLen = std::min(oldView.length(), newView.length());
    while (commonPrefixLen < minLen && oldView[commonPrefixLen] == newView[commonPrefixLen]) {
        commonPrefixLen++;
    }

    const size_t charsToDelete = oldView.length() - commonPrefixLen;
    const size_t deleteOperations = [&](){
        size_t count =0;
        size_t pos = oldView.length() -1;
        size_t remaining = charsToDelete;
        while(remaining >0){
            bool  isChineseChar = (pos >= 2 && 
                (unsigned char)oldView[pos -2]>=0xE0 &&
                (unsigned char)oldView[pos -2] <= 0xEF);
            remaining -= isChineseChar? 3:1;
            pos -= isChineseChar?3:1;
            count++;
        }
        return count;
    }();
    for (size_t i = 0; i < deleteOperations; i++) {
        dispatcher->dispatchDeleteBackward();
    }

    const size_t insertLen = newView.length() - commonPrefixLen;
    if (insertLen > 0) {
        const char* newText = text + commonPrefixLen;
        dispatcher->dispatchInsertText(newText, insertLen);
    }
    return nullptr;

}