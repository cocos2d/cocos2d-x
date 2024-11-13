//
// Created on 2024/01/05.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include <js_native_api.h>
#include <js_native_api_types.h>
#include "MouseNapi.h"
#include "platform/ohos/napi/plugin_manager.h"
#include "../../CCLogOhos.h"
#include "ui/UIEditBox/UIEditBoxImpl-ohos.h"
#include "base/CCIMEDispatcher.h"
#include "platform/ohos/napi/render/plugin_render.h"
#include <string>

napi_value MouseNapi::mouseWheelCB(napi_env env, napi_callback_info info) {
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
  if (valuetype != napi_string) {
    napi_throw_type_error(env, NULL, "Wrong arguments");
    return nullptr;
  }

  status = napi_typeof(env, args[1], &valuetype);
  if (status != napi_ok) {
    return nullptr;
  }
  if (valuetype != napi_number) {
    napi_throw_type_error(env, NULL, "Wrong arguments");
    return nullptr;
  }
  size_t pInt;
  char eventType[256];
  NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], eventType, 256, &pInt));
  double scrollY;
  NAPI_CALL(env, napi_get_value_double(env, args[1], &scrollY));
  PluginRender::MouseWheelCB(eventType, scrollY);
  return nullptr;
}