/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <string>
#include <stdio.h>
#include "helper/JSRegisterUtils.h"
#include "helper/Js_Cocos2dxHelper.h"
#include "sdk_plugin_manager.h"
#include "modules/LoginSDKNapi.h"
#include "modules/PaySDKNapi.h"
#include "../CCSDKLogOhos.h"

const int32_t kMaxStringLen = 512;
enum ContextType {
    LOGINSDK_NAPI,
    PAYSDK_NAPI
};

napi_value SDKNapiManager::GetContext(napi_env env, napi_callback_info info)
{
    napi_status status;
    napi_value exports;
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

    int64_t value;
    NAPI_CALL(env, napi_get_value_int64(env, args[0], &value));

    NAPI_CALL(env, napi_create_object(env, &exports));

    switch (value) {
        case LOGINSDK_NAPI:
          {
               OHOS_LOGE("LoginSDKNapi::Export");
               napi_property_descriptor desc[] = {
                   DECLARE_NAPI_FUNCTION("syncLoginSDKResult", LoginSDKNapi::onLoginSDKCallBack),
               };
               NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
               OHOS_LOGE("LoginSDKNapi::Export finish");
          }
          break;
        case PAYSDK_NAPI:
          {
               OHOS_LOGE("PaySDKNapi::Export");
               napi_property_descriptor desc[] = {
                   DECLARE_NAPI_FUNCTION("syncPaySDKResult", PaySDKNapi::onPaySDKCallBack),
               };
               NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
               OHOS_LOGE("PaySDKNapi::Export finish");
          }
          break;
        default:
            OHOS_LOGE("unknown type");
    }
    return exports;
}