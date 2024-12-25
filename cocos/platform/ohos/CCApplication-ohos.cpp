#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "napi/helper/NapiHelper.h"
#include "napi/render/plugin_render.h"
#include "platform/CCApplication.h"
#include "base/CCDirector.h"
#include "CCLogOhos.h"
#include <string>

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
    if (!applicationDidFinishLaunching())
    {
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
    std::string systemLanguage = JSFunction::getFunction("DeviceUtils.getSystemLanguage").invoke<std::string>();
    OHOS_LOGD("==========getCurrentLanguageCode is [%{public}s] =========",systemLanguage.c_str());
    strncpy(code, systemLanguage.c_str(), 2);
    code[2]='\0';
    return code;
}

LanguageType Application::getCurrentLanguage() {
    const char* pLanguageName = getCurrentLanguageCode();

    OHOS_LOGD("current language:%{public}s", pLanguageName);
    LanguageType ret = LanguageType::ENGLISH;

    if (0 == strcmp("zh", pLanguageName)) {
        ret = LanguageType::CHINESE;
    } else if (0 == strcmp("en", pLanguageName)) {
        ret = LanguageType::ENGLISH;
    } else if (0 == strcmp("fr", pLanguageName)) {
        ret = LanguageType::FRENCH;
    } else if (0 == strcmp("it", pLanguageName)) {
        ret = LanguageType::ITALIAN;
    } else if (0 == strcmp("de", pLanguageName)) {
        ret = LanguageType::GERMAN;
    } else if (0 == strcmp("es", pLanguageName)) {
        ret = LanguageType::SPANISH;
    } else if (0 == strcmp("nl", pLanguageName)) {
        ret = LanguageType::SPANISH;
    } else if (0 == strcmp("ru", pLanguageName)) {
        ret = LanguageType::RUSSIAN;
    } else if (0 == strcmp("ko", pLanguageName)) {
        ret = LanguageType::KOREAN;
    } else if (0 == strcmp("ja", pLanguageName)) {
        ret = LanguageType::JAPANESE;
    } else if (0 == strcmp("hu", pLanguageName)) {
        ret = LanguageType::HUNGARIAN;
    } else if (0 == strcmp("pt", pLanguageName)) {
        ret = LanguageType::PORTUGUESE;
    } else if (0 == strcmp("ar", pLanguageName)) {
        ret = LanguageType::ARABIC;
    }
    return ret;
}

ApplicationProtocol::Platform Application::getTargetPlatform() {
    return ApplicationProtocol::Platform::OS_HARMONY_NEXT;
}


std::string Application::getVersion() {
    return JSFunction::getFunction("ApplicationManager.getVersionName").invoke<std::string>();
}

bool Application::openURL(const std::string &url) {
    try {
        JSFunction::getFunction("JumpManager.openUrl").invoke<void>(url);
    } catch (std::exception& e) {
        return false;
    }
    return true;
}

void Application::applicationScreenSizeChanged(int newWidth, int newHeight) {

}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
