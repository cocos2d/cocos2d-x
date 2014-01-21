#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
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
    
	pFileUtils->setSearchPaths(searchPaths);

    EGLView::getInstance()->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

    auto scene = Scene::create();
    auto layer = new TestController();
    layer->autorelease();

    scene->addChild(layer);
    director->runWithScene(scene);

    // Enable Remote Console
    auto console = director->getConsole();
    console->listenOnTCP(5678);

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
