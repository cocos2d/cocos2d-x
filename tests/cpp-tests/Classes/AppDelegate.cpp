/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
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

#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

AppDelegate::AppDelegate()
:_curTest(nullptr)
{
}

AppDelegate::~AppDelegate()
{
//    SimpleAudioEngine::end();
    cocostudio::ArmatureDataManager::destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // As an example, load config file
    // XXX: This should be loaded before the Director is initialized,
    // XXX: but at this point, the director is already initialized
    Configuration::getInstance()->loadConfigFile("configs/config-example.plist");

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Cpp Tests");
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = glview->getFrameSize();

    auto designSize = Size(480, 320);

    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > 320)
    {
        auto resourceSize = Size(960, 640);
        searchPaths.push_back("hd");
        searchPaths.push_back("hd/scenetest");
        searchPaths.push_back("hd/scenetest/ArmatureComponentTest");
        searchPaths.push_back("hd/scenetest/AttributeComponentTest");
        searchPaths.push_back("hd/scenetest/BackgroundComponentTest");
        searchPaths.push_back("hd/scenetest/EffectComponentTest");
        searchPaths.push_back("hd/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.push_back("hd/scenetest/ParticleComponentTest");
        searchPaths.push_back("hd/scenetest/SpriteComponentTest");
        searchPaths.push_back("hd/scenetest/TmxMapComponentTest");
        searchPaths.push_back("hd/scenetest/UIComponentTest");
        searchPaths.push_back("hd/scenetest/TriggerTest");
        director->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        searchPaths.push_back("scenetest/ArmatureComponentTest");
        searchPaths.push_back("scenetest/AttributeComponentTest");
        searchPaths.push_back("scenetest/BackgroundComponentTest");
        searchPaths.push_back("scenetest/EffectComponentTest");
        searchPaths.push_back("scenetest/LoadSceneEdtiorFileTest");
        searchPaths.push_back("scenetest/ParticleComponentTest");
        searchPaths.push_back("scenetest/SpriteComponentTest");
        searchPaths.push_back("scenetest/TmxMapComponentTest");
        searchPaths.push_back("scenetest/UIComponentTest");
        searchPaths.push_back("scenetest/TriggerTest");
    }
    
    fileUtils->setSearchPaths(searchPaths);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
#endif

    auto scene = Scene::create();
    auto layer = new TestController();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    layer->addConsoleAutoTest();
#endif

    layer->autorelease();

    scene->addChild(layer);
    director->runWithScene(scene);

    // Enable Remote Console
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
    auto console = director->getConsole();
    console->listenOnTCP(5678);
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}

void AppDelegate::setCurrentTest(BaseTest* curTest)
{
    _curTest = curTest;
}

BaseTest* AppDelegate::getCurrentTest()
{
    return _curTest;
}