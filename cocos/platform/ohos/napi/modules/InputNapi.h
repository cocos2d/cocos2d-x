#ifndef MyApplication_InputNapi_H
#define MyApplication_InputNapi_H

#include <string>
#include <napi/native_api.h>

class InputNapi {
public:
    static napi_value editBoxOnFocusCB(napi_env env, napi_callback_info info);
    static napi_value editBoxOnChangeCB(napi_env env, napi_callback_info info);
    static napi_value editBoxOnEnterCB(napi_env env, napi_callback_info info);
    static napi_value textFieldTTFOnChangeCB(napi_env env, napi_callback_info info);
};

#endif //MyApplication_InputNapi_H