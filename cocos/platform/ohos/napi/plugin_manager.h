#ifndef _PLUGIN_MANAGER_H_
#define _PLUGIN_MANAGER_H_

#include <string>
#include <unordered_map>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>
#include <uv.h>

#include "common/native_common.h"
#include "WorkerMessageQueue.h"
#include "render/plugin_render.h"

class NapiManager {
public:
    ~NapiManager() {}

    static NapiManager* GetInstance() {
        return &NapiManager::manager_;
    }

    static napi_value GetContext(napi_env env, napi_callback_info info);

    /******************************APP Lifecycle******************************/
    static napi_value NapiOnCreate(napi_env env, napi_callback_info info);
    static napi_value NapiOnShow(napi_env env, napi_callback_info info);
    static napi_value NapiOnHide(napi_env env, napi_callback_info info);
    static napi_value NapiOnBackPress(napi_env env, napi_callback_info info);
    static napi_value NapiOnDestroy(napi_env env, napi_callback_info info);
    /*********************************************************************/

    /******************************JS Page : Lifecycle*****************************/
    static napi_value NapiOnPageShow(napi_env env, napi_callback_info info);
    static napi_value NapiOnPageHide(napi_env env, napi_callback_info info);
    void OnPageShowNative();
    void OnPageHideNative();
    /*************************************************************************/

    // Worker Func
    static napi_value napiWorkerInit(napi_env env, napi_callback_info info);
    static napi_value napiNativeEngineStart(napi_env env, napi_callback_info info);
    static napi_value napiWritablePathInit(napi_env env, napi_callback_info info);

    OH_NativeXComponent* GetNativeXComponent();
    void SetNativeXComponent(OH_NativeXComponent* nativeXComponent);

public:
    // Napi export
    bool Export(napi_env env, napi_value exports);
private:
    static void MainOnMessage(const uv_async_t* req);
    static NapiManager manager_;

    OH_NativeXComponent* nativeXComponent_ = nullptr;

public:
    napi_env mainEnv_ = nullptr;
    uv_loop_t* mainLoop_ = nullptr;
    uv_async_t mainOnMessageSignal_ {};
};

#endif // _PLUGIN_MANAGER_H_
