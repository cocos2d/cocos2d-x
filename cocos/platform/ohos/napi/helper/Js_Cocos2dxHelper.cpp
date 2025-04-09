#include <string>
#include "Js_Cocos2dxHelper.h"
#include "aki/jsbind.h"

napi_env Js_Cocos2dxHelper::_env = nullptr;
napi_value Js_Cocos2dxHelper::initJsCocos2dxHelper(napi_env env, napi_callback_info info)
{
    _env = env;
    return 0;
}

/**
 * If you have more information that can be obtained asynchronously, add it here.
 */
napi_value Js_Cocos2dxHelper::initAsyncInfo(napi_env env, napi_callback_info info) {
    if (auto initScreenInfo = aki::JSBind::GetJSFunction("DeviceUtils.initScreenInfo")) {
            initScreenInfo->Invoke<void>();
    }
    return nullptr;
}

std::string Js_Cocos2dxHelper::_asyncInfoMap[AsyncInfo::LAST_INDEX];

void Js_Cocos2dxHelper::terminateProcess() {
    if (auto exit = aki::JSBind::GetJSFunction("ApplicationManager.exit")) {
            exit->Invoke<void>();
    }

}
