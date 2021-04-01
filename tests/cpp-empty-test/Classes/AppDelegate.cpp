/****************************************************************************
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

#include <vector>
#include <string>

#include "HelloWorldScene.h"
#include "AppMacros.h"

//Uncomment the following line to use localize manager
//#include "editor-support/cocostudio/LocalizationManager.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }

    // Set window icon with best resolution (windows and linux)
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    // assert error when using listFilesRecursively on Windows 10
    // refer to: https://github.com/cocos2d/cocos2d-x/issues/18835
    // don't use listFiles as workaround (it will return directory itself)
    // refer to: https://github.com/cocos2d/cocos2d-x/issues/18834
    std::vector<std::string> icons;
    FileUtils::getInstance()->listFilesRecursively("icons", &icons);
    #else
    std::string icons = "icons/Icon-60@3x.png";
    #endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX) */
    glview->setIcon(icons);

    director->setOpenGLView(glview);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);

    Size frameSize = glview->getFrameSize();
    
    vector<string> searchPath;

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // This can make sure that the resource's height could fit for the height of design resolution.

    // If the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > mediumResource.size.height)
    {
        searchPath.push_back(largeResource.directory);

        director->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
    }
    // If the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
        director->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // If the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        searchPath.push_back(smallResource.directory);

        director->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }
    
    // Set searching path
    FileUtils::getInstance()->setSearchPaths(searchPath);

    // Uncomment follow block to use localize manager to set localize strings

    //  If you want to load json localize data, use follow block
    /*
    cocostudio::ILocalizationManager * lm = cocostudio::JsonLocalizationManager::getInstance();
    lm->initLanguageData("your localize file name.lang.json");
    cocostudio::LocalizationHelper::setCurrentManager(lm, false);
    */

    //  If you want to load binary localize data, use follow block
    /*
    cocostudio::ILocalizationManager * lm = cocostudio::BinLocalizationManager::getInstance();
    lm->initLanguageData("your localize file name.lang.csb");
    cocostudio::LocalizationHelper::setCurrentManager(lm, true);
    */

    // to enable VR, uncomment the following lines
//    auto vrImpl = new VRGenericRenderer;
//    glview->setVR(vrImpl);

    // Turn on display FPS
    director->setDisplayStats(true);

    // Set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Create a scene. it's an autorelease object
    auto scene = HelloWorld::scene();

    // Run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // If you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// This function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // If you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
