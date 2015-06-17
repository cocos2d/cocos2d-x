#include "cocos2d.h"
#include "AppDelegate.h"
#include "audio/include/SimpleAudioEngine.h"
#include "base/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "lua_module_register.h"
#include "CCComponentLua.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::getInstance()->end();
    //CCScriptEngineManager::destroyInstance();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Cpp Empty Test");
        director->setOpenGLView(glview);
    }
    
    director->setOpenGLView(glview);
    auto& winSize = director->getWinSize();
    
    auto sprite = Sprite::create("res/crop.png");
    sprite->setPosition(Vec2(winSize.width/2, winSize.height/2));
    auto scene = Scene::create();
    scene->addChild(sprite);
    
    auto luaUpdateComponent = new ComponentLua;
    luaUpdateComponent->_scriptPath = "src/hello.lua";
    luaUpdateComponent->bindEvent("update", "update");
    sprite->addComponent(luaUpdateComponent);
    luaUpdateComponent->release();
    sprite->scheduleUpdate();
    
   
    auto menuItem = MenuItemFont::create("click me", [luaUpdateComponent](Ref* item) { luaUpdateComponent->_scriptPath = "src/hello2.lua"; });
    menuItem->setPosition(Vec2(winSize.width/2, winSize.height/2 - 100));
    auto menu = Menu::create(menuItem, nullptr);
    menu->setPosition(Vec2(0,0));
    scene->addChild(menu);
    
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
