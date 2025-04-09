/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
// #include "editor-support/cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
#include "audio/include/AudioEngine.h"
#include "editor-support/cocostudio/CocoStudio.h"
#endif
USING_NS_CC;

AppDelegate::AppDelegate()
: _testController(nullptr)
{
}

AppDelegate::~AppDelegate()
{
    //SimpleAudioEngine::end();
  #if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
    cocostudio::ArmatureDataManager::destroyInstance();
  #endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // As an example, load config file
    // FIXME:: This should be loaded before the Director is initialized,
    // FIXME:: but at this point, the director is already initialized
    Configuration::getInstance()->loadConfigFile("configs/config-example.plist");
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Cpp Tests");   
        director->setOpenGLView(glview);
    }
    
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);

    auto screenSize = glview->getFrameSize();
    auto designSize = Size(1024/2, 2112/2);

    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > 320)
    {
        auto resourceSize = Size(1024, 2112);
        searchPaths.push_back("hd");
        searchPaths.push_back("ccs-res/hd");
        searchPaths.push_back("ccs-res");
        searchPaths.push_back("Manifests");
        director->setContentScaleFactor(resourceSize.height/designSize.height);

        searchPaths.push_back("hd/ActionTimeline");
    }
    else
    {
        searchPaths.push_back("ccs-res");
        
        searchPaths.push_back("ActionTimeline");
    }
    
    fileUtils->setSearchPaths(searchPaths);

    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

    // Enable Remote Console
    auto console = director->getConsole();
    console->listenOnTCP(5678);

    _testController = TestController::getInstance();

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    if (_testController)
    {
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
        _testController->onEnterBackground();
	#endif
    }
    
    Director::getInstance()->stopAnimation();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
       _testController->onEnterBackground();
	#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    if (_testController)
    {
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
          _testController->onEnterForeground();
		#endif
    }
    
    Director::getInstance()->startAnimation();
    // resume audioEngine, otherwise the opensl audioPlayer will always be suspended.
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_OHOS)
      _testController->onEnterForeground();
    #endif
}

void AppDelegate::applicationScreenSizeChanged(int newWidth, int newHeight)
{
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if (glview != NULL) {
        // Set ResolutionPolicy to a proper value. here use the original value when the game is started.
        ResolutionPolicy resolutionPolicy = glview->getResolutionPolicy();
        Size designSize = glview->getDesignResolutionSize();
         glview->setFrameSize(newWidth, newHeight);
         // Set the design resolution to a proper value. here use the original value when the game is started. 
         glview->setDesignResolutionSize(designSize.width, designSize.height, resolutionPolicy);
    }
}
