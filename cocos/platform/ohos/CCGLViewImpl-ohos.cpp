#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "CCGLViewImpl-ohos.h"
#include "base/CCDirector.h"
#include "base/ccMacros.h"
#include "base/CCIMEDispatcher.h"
#include "napi/helper/Js_Cocos2dxHelper.h"
#include "CCGL-ohos.h"

#include <stdlib.h>
#include "CCLogOhos.h"
#include "napi/helper/NapiHelper.h"



//#if CC_TEXTURE_ATLAS_USE_VAO

// <EGL/egl.h> exists since android 2.3
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
        JSFunction::getFunction("DiaLog.showTextInputDialog").invoke<void>(pszText);
    } else {
        JSFunction::getFunction("DiaLog.hideTextInputDialog").invoke<void>();
    }
}

Rect GLViewImpl::getSafeAreaRect() const {
    Rect safeAreaRect = GLView::getSafeAreaRect();
    float deviceAspectRatio = 0;
    if(safeAreaRect.size.height > safeAreaRect.size.width) {
        deviceAspectRatio = safeAreaRect.size.height / safeAreaRect.size.width;
    } else {
        deviceAspectRatio = safeAreaRect.size.width / safeAreaRect.size.height;
    }

    float marginX = DEFAULT_MARGIN_OHOS / _scaleX;
    float marginY = DEFAULT_MARGIN_OHOS / _scaleY;

    bool isScreenRound = JSFunction::getFunction("DeviceUtils.isRoundScreen").invoke<bool>();
    bool hasSoftKeys = JSFunction::getFunction("DeviceUtils.hasSoftKeys").invoke<bool>();
    bool isCutoutEnabled = JSFunction::getFunction("DeviceUtils.isCutoutEnable").invoke<bool>();

    if(isScreenRound) {
        // edge screen
        if(safeAreaRect.size.width < safeAreaRect.size.height) {
            safeAreaRect.origin.y += marginY * 2.f;
            safeAreaRect.size.height -= (marginY * 2.f);

            safeAreaRect.origin.x += marginX;
            safeAreaRect.size.width -= (marginX * 2.f);
        } else {
            safeAreaRect.origin.y += marginY;
            safeAreaRect.size.height -= (marginY * 2.f);

            // landscape: no changes with X-coords
        }
    } else if (deviceAspectRatio >= WIDE_SCREEN_ASPECT_RATIO_OHOS) {
        // almost all devices on the market have round corners
        float bottomMarginIfPortrait = 0;
        if(hasSoftKeys) {
            bottomMarginIfPortrait = marginY * 2.f;
        }

        if(safeAreaRect.size.width < safeAreaRect.size.height) {
            // portrait: double margin space if device has soft menu
            safeAreaRect.origin.y += bottomMarginIfPortrait;
            safeAreaRect.size.height -= (bottomMarginIfPortrait + marginY);
        } else {
            // landscape: ignore double margin at the bottom in any cases
            // prepare signle margin for round corners
            safeAreaRect.origin.y += marginY;
            safeAreaRect.size.height -= (marginY * 2.f);
        }
    } else {
        if(hasSoftKeys && (safeAreaRect.size.width < safeAreaRect.size.height)) {
            // portrait: preserve only for soft system menu
            safeAreaRect.origin.y += marginY * 2.f;
            safeAreaRect.size.height -= (marginY * 2.f);
        }
    }

    if (isCutoutEnabled) {
        // screen with enabled cutout area
        int orientation = JSFunction::getFunction("DeviceUtils.getOrientation").invoke<int>();

        if(static_cast<int>(GLViewImpl::Orientation::PORTRAIT) == orientation) {
            double height = JSFunction::getFunction("DeviceUtils.getCutoutHeight").invoke<int>() / _scaleY;
            safeAreaRect.origin.y += height;
            safeAreaRect.size.height -= height;
        } else if(static_cast<int>(GLViewImpl::Orientation::PORTRAIT_INVERTED) == orientation) {
            double height =JSFunction::getFunction("DeviceUtils.getCutoutHeight").invoke<int>() / _scaleY;
            safeAreaRect.size.height -= height;
        } else if(static_cast<int>(GLViewImpl::Orientation::LANDSCAPE) == orientation) {
            double width = JSFunction::getFunction("DeviceUtils.getCutoutWidth").invoke<int>() / _scaleX;
            safeAreaRect.size.width -= width;
        } else if(static_cast<int>(GLViewImpl::Orientation::LANDSCAPE_INVERTED) == orientation) {
            double width = JSFunction::getFunction("DeviceUtils.getCutoutWidth").invoke<int>() / _scaleX;
            safeAreaRect.origin.x += width;
            safeAreaRect.size.width -= width;
        }
    }

    return safeAreaRect;
}
NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
