#include "CCLogOhos.h"
#include "plugin_manager.h"

/*
 * function for module exports
 */
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] ={
        DECLARE_NAPI_FUNCTION("getContext", NapiManager::GetContext),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));

    bool ret = NapiManager::GetInstance()->Export(env, exports);
    if (!ret) {
        OHOS_LOGE("Init failed");
    }
    return exports;
}

/*
 * Napi Module define
 */
static napi_module nativerenderModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "nativerender",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};
/*
 * Module register function
 */
extern "C" __attribute__((constructor)) void RegisterModule(void) {
    napi_module_register(&nativerenderModule);
}