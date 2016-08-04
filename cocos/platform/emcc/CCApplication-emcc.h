/****************************************************************************
Copyright (c) 2011      Laschweinski
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CC_APPLICATION_EMSCRIPTEN_H__
#define __CC_APPLICATION_EMSCRIPTEN_H__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>

NS_CC_BEGIN

class Rect;

class CC_DLL Application : public ApplicationProtocol
{
public:
    /**
     * @js ctor
     */
    Application();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Application();
    
    /**
     @brief	Callback by Director for limit FPS.
     @param interval    The time, which expressed in second in second, between current frame and next.
     */
    virtual void setAnimationInterval(float interval) override;
    
    /**
     @brief	Run the message loop.
     */
    int run();
    
    /**
     @brief	Get current applicaiton instance.
     @return Current application instance pointer.
     */
    static Application* getInstance();
    
    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Application* sharedApplication();
    
    /* override functions */
    virtual LanguageType getCurrentLanguage() override;
    
    /**
     @brief Get current language iso 639-1 code
     @return Current language iso 639-1 code
     */
    virtual const char * getCurrentLanguageCode() override;
    
    /**
     @brief Get application version
     */
    virtual std::string getVersion() override;
    
    /**
     @brief Get application build version.
     */
    virtual std::string getBuildVersion() override;
    
    
    /**
     *  Sets the Resource root path.
     *  @deprecated Please use FileUtils::getInstance()->setSearchPaths() instead.
     */
    CC_DEPRECATED_ATTRIBUTE void setResourceRootPath(const std::string& rootResDir);
    
    /**
     *  Gets the Resource root path.
     *  @deprecated Please use FileUtils::getInstance()->getSearchPaths() instead.
     */
    CC_DEPRECATED_ATTRIBUTE const std::string& getResourceRootPath(void);
    
    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform() override;
    
    /**
     @brief Open url in default browser
     @param String with url to open.
     @return true if the resource located by the URL was successfully opened; otherwise false.
     * @js NA
     * @lua NA
     */
    virtual bool openURL(const std::string &url) override;
    
    static void setAppVersion(const std::string &version);
    static void setAppBuildVersion(const std::string &version);
    
    void setCurrentLocale(const std::string &locale);
    
    void toggleToFullscreen();
    bool isFullscreen();
    
    void setForegroundMainLoop();
    void setBackgroundMainLoop();
    
protected:
    long       _animationInterval;  //micro second
    std::string _resourceRootPath;
    std::string _currentLocale;
    
    static Application * sm_pSharedApplication;
    static std::string _appVersion;
    static std::string _appBuildVersion;
};

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#endif /* __CC_APPLICATION_EMSCRIPTEN_H__ */
