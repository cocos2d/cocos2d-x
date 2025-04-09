#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "napi/render/plugin_render.h"
#include "platform/CCApplication.h"
#include "base/CCDirector.h"
#include "base/ccUtils.h"
#include "CCLogOhos.h"
#include <string>
#include "aki/jsbind.h"

NS_CC_BEGIN

// sharedApplication pointer
Application * Application::sm_pSharedApplication = nullptr;

Application::Application() {
    CCAssert(! sm_pSharedApplication, "");
    sm_pSharedApplication = this;
}

Application::~Application() {
    CCAssert(this == sm_pSharedApplication, "");
    sm_pSharedApplication = nullptr;
}

int Application::run() {
    // Initialize instance and cocos2d.
    if (! applicationDidFinishLaunching()) {
        return 0;
    }
    
    return -1;
}

void Application::setAnimationInterval(float interval) {
    OHOS_LOGD("setAnimationInterval param is [%{public}f] =========", interval);
    PluginRender::GetInstance()->changeFPS((uint64_t)(interval * 1000));  // s to ms
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
Application* Application::getInstance() {
    CCAssert(sm_pSharedApplication, "");
    return sm_pSharedApplication;
}

// @deprecated Use getInstance() instead
Application* Application::sharedApplication() {
    return Application::getInstance();
}

const char * Application::getCurrentLanguageCode() {
    static char code[3]={0};
    std::string result;
    if (auto getSystemLanguage = aki::JSBind::GetJSFunction("DeviceUtils.getSystemLanguage")) {
        result = getSystemLanguage->Invoke<std::string>(); 
    }
    OHOS_LOGD("==========getCurrentLanguageCode is [%{public}s] =========",result.c_str());
    strncpy(code, result.c_str(), 2);
    code[2]='\0';
    return code;
}

LanguageType Application::getCurrentLanguage() {
    const char* code = getCurrentLanguageCode();
    return utils::getLanguageTypeByISO2(code);
}

ApplicationProtocol::Platform Application::getTargetPlatform() {
    return ApplicationProtocol::Platform::OS_HARMONY_NEXT;
}


std::string Application::getVersion() {
    std::string result;
    if (auto getVersionName = aki::JSBind::GetJSFunction("ApplicationManager.getVersionName")) {
        result = getVersionName->Invoke<std::string>(); 
    }
    return result;
}

bool Application::openURL(const std::string &url) {
    try {
        if (auto openUrl = aki::JSBind::GetJSFunction("JumpManager.openUrl")) {
            openUrl->Invoke<void>(); 
        }
    } catch (std::exception& e) {
        return false;
    }
    return true;
}

void Application::applicationScreenSizeChanged(int newWidth, int newHeight) {
    // You can implemented it in AppDelgate
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
