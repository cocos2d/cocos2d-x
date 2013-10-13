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
//    SimpleAudioEngine::end();
	cocos2d::extension::armature::ArmatureDataManager::destoryInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	// As an example, load config file
	// XXX: This should be loaded before the Director is initialized,
	// XXX: but at this point, the director is already initialized
	Configuration::getInstance()->loadConfigFile("configs/config-example.plist");

    // initialize director
    auto director = Director::getInstance();
    director->setOpenGLView(EGLView::getInstance());

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    auto screenSize = EGLView::getInstance()->getFrameSize();

    auto designSize = Size(480, 320);

    auto pFileUtils = FileUtils::getInstance();
	std::vector<std::string> searchPaths;
    
    if (screenSize.height > 320)
    {
        auto resourceSize = Size(960, 640);
        searchPaths.push_back("hd");
		searchPaths.push_back("hd/scenetest");
        director->setContentScaleFactor(resourceSize.height/designSize.height);
    }
	else
	{
		searchPaths.push_back("scenetest");
	}
	pFileUtils->setSearchPaths(searchPaths);

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
