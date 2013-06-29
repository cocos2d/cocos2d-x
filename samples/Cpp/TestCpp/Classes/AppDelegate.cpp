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
	Configuration::sharedConfiguration()->loadConfigFile("configs/config-example.plist");

    // initialize director
    Director *pDirector = Director::sharedDirector();
    pDirector->setOpenGLView(EGLView::sharedOpenGLView());

    Size screenSize = EGLView::sharedOpenGLView()->getFrameSize();

    Size designSize = CCSizeMake(480, 320);

    FileUtils* pFileUtils = FileUtils::sharedFileUtils();
    
    if (screenSize.height > 320)
    {
        Size resourceSize = CCSizeMake(960, 640);
        std::vector<std::string> searchPaths;
        searchPaths.push_back("hd");
        pFileUtils->setSearchPaths(searchPaths);
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }

    EGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);

    Scene * pScene = Scene::create();
    Layer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
