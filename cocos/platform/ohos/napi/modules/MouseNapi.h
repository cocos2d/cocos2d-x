//
// Created on 2024/01/05.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef MyApplication_MouseNapi_H
#define MyApplication_MouseNapi_H

#include <string>
#include <napi/native_api.h>

class MouseNapi {
public:
    static napi_value mouseWheelCB(napi_env env, napi_callback_info info);
};

#endif //MyApplication_MouseNapi_H