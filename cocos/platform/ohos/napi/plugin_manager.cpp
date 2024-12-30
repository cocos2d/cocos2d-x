#include <stdint.h>
#include <string>
#include <stdio.h>

#include <ace/xcomponent/native_interface_xcomponent.h>

#include "modules/RawFileUtils.h"
#include "modules/InputNapi.h"
#include "modules/MouseNapi.h"
#include "modules/WebViewNapi.h"
#include "modules/SensorNapi.h"
#include "modules/VideoPlayerNapi.h"
#include "plugin_manager.h"
#include "../CCLogOhos.h"
#include "cocos2d.h"
#include "platform/CCApplication.h"
#include "platform/ohos/CCFileUtils-ohos.h"
#include "platform/ohos/napi/helper/JSRegisterUtils.h"
#include "platform/ohos/napi/helper/Js_Cocos2dxHelper.h"
#include "base/CCDirector.h"
#include "base/CCEventKeyboard.h"

const int32_t kMaxStringLen = 512;
enum ContextType {
    APP_LIFECYCLE = 0,
    JS_PAGE_LIFECYCLE,
    RAW_FILE_UTILS,
    WORKER_INIT,
    NATIVE_API,
    INPUT_NAPI,
    MOUSE_NAPI,
    WEBVIEW_NAPI,
    VIDEOPLAYER_NAPI,
    SENSOR_API
};

NapiManager NapiManager::manager_;

napi_value NapiManager::GetContext(napi_env env, napi_callback_info info) {
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
        case APP_LIFECYCLE: {
                /**** AppInit corresponds to the application life cycle in app.ets. onCreate, onShow, onHide, onDestroy ******/
                OHOS_LOGD("GetContext APP_LIFECYCLE");
                /**** Register App Lifecycle  ******/
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onCreate", NapiManager::NapiOnCreate),
                    DECLARE_NAPI_FUNCTION("onShow", NapiManager::NapiOnShow),
                    DECLARE_NAPI_FUNCTION("onHide", NapiManager::NapiOnHide),
                    DECLARE_NAPI_FUNCTION("onBackPress", NapiManager::NapiOnBackPress),
                    DECLARE_NAPI_FUNCTION("onDestroy", NapiManager::NapiOnDestroy),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case JS_PAGE_LIFECYCLE: {
                /****************  Declarative Development Paradigm JS Page Lifecycle Registration ****************************/
                OHOS_LOGD("GetContext JS_PAGE_LIFECYCLE");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onPageShow", NapiManager::NapiOnPageShow),
                    DECLARE_NAPI_FUNCTION("onPageHide", NapiManager::NapiOnPageHide),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case RAW_FILE_UTILS: {
                /****************  Declarative Development Paradigm JS Page Lifecycle Registration ****************************/
                OHOS_LOGD("GetContext RAW_FILE_UTILS");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("nativeResourceManagerInit", RawFileUtils::nativeResourceManagerInit),
                    DECLARE_NAPI_FUNCTION("writablePathInit", NapiManager::napiWritablePathInit),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));

            }
            break;
        case WORKER_INIT: {
                OHOS_LOGD("NapiManager::GetContext WORKER_INIT");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("workerInit", NapiManager::napiWorkerInit),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case NATIVE_API: {
                OHOS_LOGD("NapiManager::GetContext NATIVE_RENDER_API");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("nativeEngineStart", NapiManager::napiNativeEngineStart),
                    DECLARE_NAPI_FUNCTION("registerFunction", registerFunction),
                    DECLARE_NAPI_FUNCTION("initAsyncInfo", Js_Cocos2dxHelper::initAsyncInfo),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case INPUT_NAPI: {
                OHOS_LOGD("NapiManager::GetContext INPUT_NAPI");
                napi_property_descriptor desc[] = {
				    DECLARE_NAPI_FUNCTION("editBoxOnFocusCB", InputNapi::editBoxOnFocusCB),
                    DECLARE_NAPI_FUNCTION("editBoxOnChangeCB", InputNapi::editBoxOnChangeCB),
                    DECLARE_NAPI_FUNCTION("editBoxOnEnterCB", InputNapi::editBoxOnEnterCB),
                    DECLARE_NAPI_FUNCTION("textFieldTTFOnChangeCB", InputNapi::textFieldTTFOnChangeCB),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case MOUSE_NAPI:
            {
                OHOS_LOGD("NapiManager::GetContext INPUT_NAPI");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("mouseWheelCB", MouseNapi::mouseWheelCB),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        case WEBVIEW_NAPI:
            {
                OHOS_LOGD("NapiManager::GetContext WEBVIEW_NAPI");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("shouldStartLoading", WebViewNapi::shouldStartLoading),
                    DECLARE_NAPI_FUNCTION("finishLoading", WebViewNapi::finishLoading),
                    DECLARE_NAPI_FUNCTION("failLoading", WebViewNapi::failLoading),
                    DECLARE_NAPI_FUNCTION("jsCallback", WebViewNapi::jsCallback),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
		case VIDEOPLAYER_NAPI: {
                OHOS_LOGE("VideoPlayerNapi::Export");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onVideoCallBack", VideoPlayerNapi::onVideoCallBack),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
                OHOS_LOGE("VideoPlayerNapi::Export finish");
            }
            break;
        case SENSOR_API: {
                OHOS_LOGD("NapiManager::GetContext SENSOR_API");
                napi_property_descriptor desc[] = {
                    DECLARE_NAPI_FUNCTION("onAccelerometerCallBack", SensorNapi::onAccelerometerCallBack),
                };
                NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
            }
            break;
        default:
            OHOS_LOGE("unknown type");
    }
    return exports;
}

bool NapiManager::Export(napi_env env, napi_value exports) {
    OHOS_LOGD("NapiManager::Export");
    napi_status status;
    napi_value exportInstance = nullptr;
    OH_NativeXComponent *nativeXComponent = nullptr;
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;

    status = napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance);
    if (status != napi_ok) {
        return false;
    }

    status = napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent));
    if (status != napi_ok) {
        return false;
    }

    auto context = NapiManager::GetInstance();
    if (context) {
        context->SetNativeXComponent(nativeXComponent);
        PluginRender::GetInstance()->SetNativeXComponent(nativeXComponent);
        PluginRender::GetInstance()->Export(env, exports);
        return true;
    }
    return false;
}

void NapiManager::SetNativeXComponent(OH_NativeXComponent* nativeXComponent) {
    nativeXComponent_ = nativeXComponent;
}

OH_NativeXComponent* NapiManager::GetNativeXComponent() {
    return nativeXComponent_;
}

void NapiManager::MainOnMessage(const uv_async_t* req) {
    OHOS_LOGD("MainOnMessage Triggered");
}

napi_value NapiManager::NapiOnCreate(napi_env env, napi_callback_info info) {
    return nullptr;
}

napi_value NapiManager::NapiOnShow(napi_env env, napi_callback_info info) {
    WorkerMessageData data{MessageType::WM_APP_SHOW, nullptr, nullptr};
    PluginRender::GetInstance()->enqueue(data);
    return nullptr;
}

napi_value NapiManager::NapiOnHide(napi_env env, napi_callback_info info) {
    WorkerMessageData data{MessageType::WM_APP_HIDE, nullptr, nullptr};
    PluginRender::GetInstance()->enqueue(data);
    return nullptr;
}

napi_value NapiManager::NapiOnBackPress(napi_env env, napi_callback_info info)
{
    OHOS_LOGD("NapiManager::NapiOnBackPress");
    cocos2d::EventKeyboard event(cocos2d::EventKeyboard::KeyCode::KEY_BACK, false);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    return nullptr;
}

napi_value NapiManager::NapiOnDestroy(napi_env env, napi_callback_info info) {
    WorkerMessageData data{MessageType::WM_APP_DESTROY, nullptr, nullptr};
    PluginRender::GetInstance()->enqueue(data);
    return nullptr;
}

napi_value NapiManager::napiWorkerInit(napi_env env, napi_callback_info info) {
    OHOS_LOGD("NapiManager::napiWorkerInit");
    uv_loop_t* loop = nullptr;
    NAPI_CALL(env, napi_get_uv_event_loop(env, &loop));
    PluginRender::GetInstance()->workerInit(env, loop);
    return nullptr;
}

napi_value NapiManager::napiNativeEngineStart(napi_env env, napi_callback_info info) {
    OHOS_LOGD("NapiManager::napiNativeEngineStart");
    PluginRender::GetInstance()->run();
    Js_Cocos2dxHelper::initJsCocos2dxHelper(env, nullptr);
    return nullptr;
}

napi_value NapiManager::napiWritablePathInit(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value  args[1];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));

    char buffer[kMaxStringLen];
    size_t result = 0;
    NAPI_CALL(env, napi_get_value_string_utf8(env, args[0], buffer, kMaxStringLen, &result));
    cocos2d::FileUtilsOhos::ohWritablePath = std::string(buffer) + '/';
    return nullptr;
}

napi_value NapiManager::NapiOnPageShow(napi_env env, napi_callback_info info) {
    OHOS_LOGD("NapiManager::NapiOnPageShow");
    return nullptr;
}

napi_value NapiManager::NapiOnPageHide(napi_env env, napi_callback_info info) {
    OHOS_LOGD("NapiManager::NapiOnPageHide");
    return nullptr;
}

void NapiManager::OnPageShowNative() {
    OHOS_LOGD("NapiManager::OnPageShowNative");
}

void NapiManager::OnPageHideNative() {
    OHOS_LOGD("NapiManager::OnPageHideNative");
}