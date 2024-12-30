#ifndef __CC_EGLVIEWIMPL_OHOS_H__
#define __CC_EGLVIEWIMPL_OHOS_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#include "math/CCGeometry.h"
#include "platform/CCGLView.h"

NS_CC_BEGIN

class CC_DLL GLViewImpl : public GLView
{
public:
    enum class Orientation {
        PORTRAIT = 0,
        LANDSCAPE,
        PORTRAIT_INVERTED,
        LANDSCAPE_INVERTED,
        UNKNOWN
    };

    // static function
    static GLViewImpl* create(const std::string &viewname);
    static GLViewImpl* createWithRect(const std::string& viewName, Rect rect, float frameZoomFactor = 1.0f);
    static GLViewImpl* createWithFullScreen(const std::string& viewName);	

    bool isOpenGLReady() override;

    // keep compatible
    void end() override;
    void swapBuffers() override;
    void setIMEKeyboardState(bool bOpen) override;
    virtual Rect getSafeAreaRect() const;
    
    // static function
    /**
    @brief    get the shared main open gl window
    */
    static GLViewImpl* sharedOpenGLView();

protected:	
	GLViewImpl();
    virtual ~GLViewImpl();
	
    bool initWithRect(const std::string& viewName, Rect rect, float frameZoomFactor);
    bool initWithFullScreen(const std::string& viewName);	
};

NS_CC_END
#endif    // end of CC_TARGET_PLATFORM == CC_PLATFORM_OHOS
#endif    // end of __CC_EGLVIEW_ANDROID_H__
