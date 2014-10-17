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

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

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
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = glview->getFrameSize();

    auto designSize = Size(480, 320);

    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > 320)
    {
        auto resourceSize = Size(960, 640);
        searchPaths.push_back("hd");
        searchPaths.push_back("ccs-res/hd");
        searchPaths.push_back("ccs-res/hd/scenetest");
        searchPaths.push_back("ccs-res/hd/scenetest/ArmatureComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/AttributeComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/BackgroundComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/EffectComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.push_back("ccs-res/hd/scenetest/ParticleComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/SpriteComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/TmxMapComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/UIComponentTest");
        searchPaths.push_back("ccs-res/hd/scenetest/TriggerTest");
        searchPaths.push_back("ccs-res");
        searchPaths.push_back("Manifests");
        director->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        searchPaths.push_back("ccs-res");
        searchPaths.push_back("ccs-res/scenetest/ArmatureComponentTest");
        searchPaths.push_back("ccs-res/scenetest/AttributeComponentTest");
        searchPaths.push_back("ccs-res/scenetest/BackgroundComponentTest");
        searchPaths.push_back("ccs-res/scenetest/EffectComponentTest");
        searchPaths.push_back("ccs-res/scenetest/LoadSceneEdtiorFileTest");
        searchPaths.push_back("ccs-res/scenetest/ParticleComponentTest");
        searchPaths.push_back("ccs-res/scenetest/SpriteComponentTest");
        searchPaths.push_back("ccs-res/scenetest/TmxMapComponentTest");
        searchPaths.push_back("ccs-res/scenetest/UIComponentTest");
        searchPaths.push_back("ccs-res/scenetest/TriggerTest");
    }
    
    fileUtils->setSearchPaths(searchPaths);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#endif

    auto scene = Scene::create();
    auto layer = new (std::nothrow) TestController();
    layer->autorelease();
    layer->addConsoleAutoTest();
    scene->addChild(layer);
    director->runWithScene(scene);

    // Enable Remote Console
    auto console = director->getConsole();
    console->listenOnTCP(5678);
    Configuration *conf = Configuration::getInstance();
    bool isAutoRun = conf->getValue("cocos2d.x.testcpp.autorun", Value(false)).asBool();
    if(isAutoRun)
    {
        layer->startAutoRun();
    }
    
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
