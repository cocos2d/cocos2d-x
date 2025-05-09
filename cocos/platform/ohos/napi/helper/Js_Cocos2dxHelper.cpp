#include <stdlib.h>
#include <string>
#include "NapiHelper.h"
#include "Js_Cocos2dxHelper.h"
#include "platform/ohos/CCLogOhos.h"

napi_env Js_Cocos2dxHelper::_env = nullptr;
napi_value Js_Cocos2dxHelper::initJsCocos2dxHelper(napi_env env, napi_callback_info info) {
    _env = env;
    return 0;
}

/**
 * If you have more information that can be obtained asynchronously, add it here.
 */
napi_value Js_Cocos2dxHelper::initAsyncInfo(napi_env env, napi_callback_info info) {
    return nullptr;
}

std::string Js_Cocos2dxHelper::_asyncInfoMap[AsyncInfo::LAST_INDEX];

void Js_Cocos2dxHelper::terminateProcess() {
    JSFunction::getFunction("ApplicationManager.exit").invoke<void>();
}
