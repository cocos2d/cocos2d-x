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
    Rect safeAreaRect = GLView::getSafeAreaRect();
    float deviceAspectRatio = 0;
    if(safeAreaRect.size.height > safeAreaRect.size.width) {
        deviceAspectRatio = safeAreaRect.size.height / safeAreaRect.size.width;
    } else {
        deviceAspectRatio = safeAreaRect.size.width / safeAreaRect.size.height;
    }

    float marginX = DEFAULT_MARGIN_OHOS / _scaleX;
    float marginY = DEFAULT_MARGIN_OHOS / _scaleY;
    bool isScreenRound;
    if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.isRoundScreen")) {
        isScreenRound = function->Invoke<bool>(); 
    }
    bool hasSoftKeys;
    if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.hasSoftKeys")) {
        hasSoftKeys = function->Invoke<bool>(); 
    }
    bool isCutoutEnabled;
    if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.isCutoutEnable")) {
        isCutoutEnabled = function->Invoke<bool>(); 
    }

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
        
        int orientation;
        if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.getOrientation")) {
            orientation = function->Invoke<int>(); 
        }

        if(static_cast<int>(GLViewImpl::Orientation::PORTRAIT) == orientation) {
            int result;
            if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.getCutoutHeight")) {
                result = function->Invoke<int>(); 
            }
            double height = result / _scaleY;
            safeAreaRect.origin.y += height;
            safeAreaRect.size.height -= height;
        } else if(static_cast<int>(GLViewImpl::Orientation::PORTRAIT_INVERTED) == orientation) {
            int result;
            if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.getCutoutHeight")) {
                result = function->Invoke<int>(); 
            }
            double height = result / _scaleY;
            safeAreaRect.size.height -= height;
        } else if(static_cast<int>(GLViewImpl::Orientation::LANDSCAPE) == orientation) {
            int result;
            if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.getCutoutWidth")) {
                result = function->Invoke<int>(); 
            }
            double width = result / _scaleX;
            safeAreaRect.size.width -= width;
        } else if(static_cast<int>(GLViewImpl::Orientation::LANDSCAPE_INVERTED) == orientation) {
            int result;
            if (auto function = aki::JSBind::GetJSFunction("DeviceUtils.getCutoutWidth")) {
                result = function->Invoke<int>(); 
            }
            double width = result / _scaleX;
            safeAreaRect.origin.x += width;
            safeAreaRect.size.width -= width;
        }
    }

    return safeAreaRect;
}
NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
