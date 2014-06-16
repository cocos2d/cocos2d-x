/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

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
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    // SimpleAudioEngine::end();
    cocos2d::extension::CCArmatureDataManager::purge();
    cocos2d::extension::DictionaryHelper::purgeDictionaryHelper();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // As an example, load config file
    // XXX: This should be loaded before the Director is initialized,
    // XXX: but at this point, the director is already initialized
    CCConfiguration::sharedConfiguration()->loadConfigFile("configs/config-example.plist");

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

    CCSize designSize = CCSizeMake(480, 320);

    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths;

    if (screenSize.height > 320)
    {
        CCSize resourceSize = CCSizeMake(960, 640);
        searchPaths.push_back("hd");
        searchPaths.push_back("ccs-res/hd");
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
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
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
    pFileUtils->setSearchPaths(searchPaths);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
#else
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
#endif

    CCScene * pScene = CCScene::create();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
