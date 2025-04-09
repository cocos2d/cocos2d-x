#include "CCLogOhos.h"
#include "napi/plugin_manager.h"
#include "aki/jsbind.h"

/*
 * function for module exports
 */
extern napi_value Init(napi_env env, napi_value exports);

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