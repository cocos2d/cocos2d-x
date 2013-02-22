//
//  AssetsManagerTestAppDelegate.cpp
//  AssetsManagerTest
//
//  Created by minggo on 2/5/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ScriptingCore.h"
#include "generated/cocos2dx.hpp"
#include "cocos2d_specifics.hpp"
#include "js_bindings_chipmunk_registration.h"
#include "js_bindings_system_registration.h"
#include "js_bindings_ccbreader.h"

USING_NS_CC;
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
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->addRegisterCallback(register_all_cocos2dx);
    sc->addRegisterCallback(register_cocos2dx_js_extensions);
    sc->addRegisterCallback(register_CCBuilderReader);
    sc->addRegisterCallback(jsb_register_chipmunk);
    sc->addRegisterCallback(jsb_register_system);
    
    sc->start();
    
    CCScene *scene = CCScene::create();
    UpdateLayer *updateLayer = new UpdateLayer();
    scene->addChild(updateLayer);
    updateLayer->release();
    
    pDirector->runWithScene(scene);
    
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

UpdateLayer::UpdateLayer()
: pAssetManager(NULL)
, pItemEnter(NULL)
, pItemReset(NULL)
, pItemUpdate(NULL)
{
    init();
}

UpdateLayer::~UpdateLayer()
{
    CC_SAFE_DELETE(pAssetManager);
}

void UpdateLayer::update(cocos2d::CCObject *pSender)
{
    // update resources
    pAssetManager = new AssetsManager("http://localhost/package.zip", "http://localhost/version");
    pAssetManager->update();
    delete pAssetManager;
    pAssetManager = NULL;
    
    // Run new version
    CCScriptEngineProtocol *pEngine = ScriptingCore::getInstance();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    ScriptingCore::getInstance()->runScript("main.js");
}

void UpdateLayer::reset(cocos2d::CCObject *pSender)
{
    
}

void UpdateLayer::enter(cocos2d::CCObject *pSender)
{
    
}

bool UpdateLayer::init()
{
    CCLayer::init();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    pItemReset = CCMenuItemFont::create("reset", this, menu_selector(UpdateLayer::reset));
    pItemEnter = CCMenuItemFont::create("enter", this, menu_selector(UpdateLayer::enter));
    pItemUpdate = CCMenuItemFont::create("update", this, menu_selector(UpdateLayer::update));
    
    pItemEnter->setPosition(ccp(size.width/2, size.height/2 + 50));
    pItemReset->setPosition(ccp(size.width/2, size.height/2));
    pItemUpdate->setPosition(ccp(size.width/2, size.height/2 - 50));
    
    CCMenu *menu = CCMenu::create(pItemUpdate, pItemEnter, pItemReset, NULL);
    menu->setPosition(ccp(0,0));
    addChild(menu);
    
    return true;
}
