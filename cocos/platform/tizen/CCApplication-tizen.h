/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN

#ifndef CCAPLICATION_TIZEN_H_
#define CCAPLICATION_TIZEN_H_

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>

#include <Elementary.h>

NS_CC_BEGIN
class Rect;

class Application : public ApplicationProtocol
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
     @brief Callback by Director for limit FPS.
     @param interval    The time, which expressed in second in second, between current frame and next.
     */
    void setAnimationInterval(float interval) override;

    /**
     @brief Run the message loop.
     */
    int run();

    /**
     @brief Get current application instance.
     @return Current application instance pointer.
     */
    static Application* getInstance();

    /** @deprecated Use getInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static Application* sharedApplication();
    
    /* override functions */
    virtual LanguageType getCurrentLanguage() override;

    std::string getVersion() override;

    /**
    @brief Get current language iso 639-1 code
    @return Current language iso 639-1 code
    */
    virtual const char * getCurrentLanguageCode() override;
    
  /**
   @brief Open url in default browser
   @param String with url to open.
   @return true if the resource located by the URL was successfully opened; otherwise false.
   */
  virtual bool openURL(const std::string &url) override;

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
  
  void setDeviceOrientation(int orientation);
  void setMainArgs(int argc, char **argv);
  void setPauseFlag(bool pause){_paused = pause;}
  bool isPaused(){return _paused;}
public:
    Evas_Object * _win;
    Evas_Object * _conform;

    Evas_GL * _evasGL;
    Evas_GL_Context * _ctx;
    Evas_GL_Surface * _sfc;
    Ecore_Animator * _ani;

    int _orientation;
    int _argc;
    char **_argv;
protected:
    long _animationInterval;  //micro second
    std::string _resourceRootPath;
    bool _paused;
    static Application * __instance;
};

NS_CC_END

#endif // CCAPLICATION_TIZEN_H_

#endif /* CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN */
