#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

#include "platform/CCCommon.h"
#include "CCLogOhos.h"
#include "aki/jsbind.h"

NS_CC_BEGIN

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

void MessageBox(const char * pszMsg, const char * pszTitle) {
    std::string msg(pszMsg);
    std::string title(pszTitle);
    if (auto showDialog = aki::JSBind::GetJSFunction("DiaLog.showDialog")) {
        showDialog->Invoke<void>(msg, title); 
    }
}

void LuaLog(const char * pszFormat) {
    OHOS_LOGI("cocos2d-x debug info %{public}s", pszFormat);
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS

