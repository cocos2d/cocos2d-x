//
//  AssetsManagerTestAppDelegate.cpp
//  AssetsManagerTest
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "jsb_cocos2dx_auto.hpp"
#include "cocos2d_specifics.hpp"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    director->setOpenGLView(EGLView::getInstance());

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    
    
    sc->start();
    
    auto scene = Scene::create();
    auto updateLayer = new UpdateLayer();
    scene->addChild(updateLayer);
    updateLayer->release();
    
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

UpdateLayer::UpdateLayer()
: pItemEnter(NULL)
, pItemReset(NULL)
, pItemUpdate(NULL)
, pProgressLabel(NULL)
, isUpdateItemClicked(false)
{
    init();
}

UpdateLayer::~UpdateLayer()
{
}

void UpdateLayer::update(cocos2d::Object *pSender)
{
    pProgressLabel->setString("");
    
    // update resources
    pAssetsManager->update();
    
    isUpdateItemClicked = true;
}

void UpdateLayer::reset(cocos2d::Object *pSender)
{
    pProgressLabel->setString(" ");
    
    // Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    string command = "rm -r ";
    // Path may include space.
    command += "\"" + pathToSave + "\"";
    system(command.c_str());
#else
    string command = "rd /s /q ";
    // Path may include space.
    command += "\"" + pathToSave + "\"";
    system(command.c_str());
#endif
    // Delete recorded version codes.
    pAssetsManager->deleteVersion();
    
    createDownloadedDir();
}

void UpdateLayer::enter(cocos2d::Object *pSender)
{
    // Should set search resource path before running script if "update" is not clicked.
    // Because AssetsManager will set 
    if (! isUpdateItemClicked)
    {
        vector<string> searchPaths = FileUtils::getInstance()->getSearchPaths();
        searchPaths.insert(searchPaths.begin(), pathToSave);
        FileUtils::getInstance()->setSearchPaths(searchPaths);
    }
    
    auto pEngine = ScriptingCore::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    ScriptingCore::getInstance()->runScript("main.js");
}

bool UpdateLayer::init()
{
    Layer::init();
    
    createDownloadedDir();

    /** Creates assets manager */
    pAssetsManager = new AssetsManager("https://raw.github.com/minggo/AssetsManagerTest/master/package.zip",
                                       "https://raw.github.com/minggo/AssetsManagerTest/master/version",
                                       pathToSave.c_str());
    pAssetsManager->setDelegate(this);
    pAssetsManager->setConnectionTimeout(3);
    addChild(pAssetsManager);
    pAssetsManager->release();
    
    auto size = Director::getInstance()->getWinSize();

    pItemReset = MenuItemFont::create("reset", CC_CALLBACK_1(UpdateLayer::reset,this));
    pItemEnter = MenuItemFont::create("enter", CC_CALLBACK_1(UpdateLayer::enter, this));
    pItemUpdate = MenuItemFont::create("update", CC_CALLBACK_1(UpdateLayer::update, this));
    
    pItemEnter->setPosition(Point(size.width/2, size.height/2 + 50));
    pItemReset->setPosition(Point(size.width/2, size.height/2));
    pItemUpdate->setPosition(Point(size.width/2, size.height/2 - 50));
    
    auto menu = Menu::create(pItemUpdate, pItemEnter, pItemReset, NULL);
    menu->setPosition(Point(0,0));
    addChild(menu);
    
    pProgressLabel = LabelTTF::create("", "Arial", 20);
    pProgressLabel->setPosition(Point(100, 50));
    addChild(pProgressLabel);
    
    return true;
}

void UpdateLayer::createDownloadedDir()
{
    pathToSave = FileUtils::getInstance()->getWritablePath();
    pathToSave += "tmpdir";
    
    // Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    DIR *pDir = NULL;
    
    pDir = opendir (pathToSave.c_str());
    if (! pDir)
    {
        mkdir(pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    }
#else
	if ((GetFileAttributesA(pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(pathToSave.c_str(), 0);
	}
#endif
}

void UpdateLayer::onError(AssetsManager::ErrorCode errorCode)
{
    if (errorCode == AssetsManager::ErrorCode::NO_NEW_VERSION)
    {
        pProgressLabel->setString("no new version");
    }
    
    if (errorCode == AssetsManager::ErrorCode::NETWORK)
    {
        pProgressLabel->setString("network error");
    }
}

void UpdateLayer::onProgress(int percent)
{
    char progress[20];
    snprintf(progress, 20, "downloading %d%%", percent);
    pProgressLabel->setString(progress);
}

void UpdateLayer::onSuccess()
{
    pProgressLabel->setString("download ok");
}
