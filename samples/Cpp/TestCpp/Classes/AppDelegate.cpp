#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "CCArmature/utils/CCArmatureDataManager.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
//    SimpleAudioEngine::end();
	cocos2d::extension::armature::ArmatureDataManager::purgeArmatureSystem();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// As an example, load config file
	// XXX: This should be loaded before the Director is initialized,
	// XXX: but at this point, the director is already initialized
	Configuration::getInstance()->loadConfigFile("configs/config-example.plist");

    // initialize director
    Director *director = Director::getInstance();
    director->setOpenGLView(EGLView::getInstance());

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    Size screenSize = EGLView::getInstance()->getFrameSize();

    Size designSize = Size(480, 320);

    FileUtils* pFileUtils = FileUtils::getInstance();
    
    if (screenSize.height > 320)
    {
        Size resourceSize = Size(960, 640);
        std::vector<std::string> searchPaths;
        searchPaths.push_back("hd");
        pFileUtils->setSearchPaths(searchPaths);
        director->setContentScaleFactor(resourceSize.height/designSize.height);
    }

    EGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

    auto scene = Scene::create();
    auto layer = new TestController();
    layer->autorelease();

    scene->addChild(layer);
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
