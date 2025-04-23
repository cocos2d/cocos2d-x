#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include <stdlib.h>
#include "CCGLViewImpl-ohos.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "base/CCIMEDispatcher.h"
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "CCGL-ohos.h"
#include "CCLogOhos.h"
#include "aki/jsbind.h"



//#if CC_TEXTURE_ATLAS_USE_VAO
#include <EGL/egl.h>
PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

//#endif

#define DEFAULT_MARGIN_OHOS				30.0f
#define WIDE_SCREEN_ASPECT_RATIO_OHOS	2.0f

void initExtensions() {
//#if CC_TEXTURE_ATLAS_USE_VAO
     glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
     glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
     glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");
//#endif
}

NS_CC_BEGIN

GLViewImpl* GLViewImpl::createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor) {
    auto ret = new GLViewImpl;
    if(ret && ret->initWithRect(viewName, rect, frameZoomFactor)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::create(const std::string& viewName) {
    auto ret = new GLViewImpl;
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl* GLViewImpl::createWithFullScreen(const std::string& viewName) {
    auto ret = new GLViewImpl();
    if(ret && ret->initWithFullScreen(viewName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

GLViewImpl::GLViewImpl() {
    initExtensions();
}

GLViewImpl::~GLViewImpl() {

}

bool GLViewImpl::initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor) {
    return true;
}

bool GLViewImpl::initWithFullScreen(const std::string& viewName) {
    return true;
}

bool GLViewImpl::isOpenGLReady() {
    return (_screenSize.width != 0 && _screenSize.height != 0);
}

void GLViewImpl::end() {
    OHOS_LOGD("GLViewImpl terminateProcess");
    Js_Cocos2dxHelper::terminateProcess();
}

void GLViewImpl::swapBuffers() {
}

GLViewImpl* GLViewImpl::sharedOpenGLView() {
    static GLViewImpl instance;
    return &instance;
}

void GLViewImpl::setIMEKeyboardState(bool bOpen) {
    if (bOpen) {
        std::string pszText = cocos2d::IMEDispatcher::sharedDispatcher()->getContentText();
        if (auto showTextInputDialog = aki::JSBind::GetJSFunction("DiaLog.showTextInputDialog")) {
            showTextInputDialog->Invoke<void>(pszText); 
        }
    } else {
        if (auto hideTextInputDialog = aki::JSBind::GetJSFunction("DiaLog.hideTextInputDialog")) {
            hideTextInputDialog->Invoke<void>(); 
        }
    }
}

Rect GLViewImpl::getSafeAreaRect() const {
    Rect safeAreaRect1;
    int left;
    if (auto getSafeAreaLeft = aki::JSBind::GetJSFunction("DeviceUtils.getSafeAreaLeft")) {
        left = getSafeAreaLeft->Invoke<int>(); 
    }
    int top;
    if (auto getSafeAreaTop = aki::JSBind::GetJSFunction("DeviceUtils.getSafeAreaTop")) {
        top = getSafeAreaTop->Invoke<int>(); 
    }
    int width;
    if (auto getSafeAreaWidth = aki::JSBind::GetJSFunction("DeviceUtils.getSafeAreaWidth")) {
        width = getSafeAreaWidth->Invoke<int>(); 
    }
    int height;
    if (auto getSafeAreaHeight = aki::JSBind::GetJSFunction("DeviceUtils.getSafeAreaHeight")) {
        height = getSafeAreaHeight->Invoke<int>(); 
    }
    safeAreaRect1.origin.x = left / _scaleX;
    safeAreaRect1.origin.y = top / _scaleY;
    safeAreaRect1.size.width = width / _scaleX;
    safeAreaRect1.size.height = height / _scaleX;
    OHOS_LOGD("GLViewImpl getsafeAreaRect1, x:%{public}f, y:%{public}f, width:%{public}f, height:%{public}f", safeAreaRect1.origin.x, safeAreaRect1.origin.y, safeAreaRect1.size.width, safeAreaRect1.size.height);
    return safeAreaRect1;
}
NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
