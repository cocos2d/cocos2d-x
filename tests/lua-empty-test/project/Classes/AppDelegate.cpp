#include "cocos2d.h"
#include "AppDelegate.h"
#include "audio/include/AudioEngine.h"
#include "base/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "lua_module_register.h"
#include "CCComponentLua.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
//    SimpleAudioEngine::getInstance()->end();
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
        glview = GLViewImpl::create("Lua Empty Test");
        director->setOpenGLView(glview);
    }
    
    // register lua engine
    LuaEngine* engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
    
    director->getEventDispatcher()->addCustomEventListener("game over", std::bind(&AppDelegate::onEvent, this, std::placeholders::_1));
    
    auto scene = createScene();
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
//    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
//    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::onEvent(EventCustom *event)
{
    experimental::AudioEngine::stopAll();
    auto scene = createScene();
    Director::getInstance()->replaceScene(scene);
}

Scene* AppDelegate::createScene() const
{
    // create game scene
    auto scene = Scene::create();
    auto sceneLuaComponent = ComponentLua::create("src/scene.lua");
    sceneLuaComponent->setName("sceneLuaComponent");
    scene->addComponent(sceneLuaComponent);
    
    // set background color
    auto bgLayer = LayerColor::create(Color4B(0, 128, 255, 255));
    scene->addChild(bgLayer);
    
    // add player
    auto player = Sprite::create("res/Player.png", Rect(0, 0, 27, 40));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    player->setPosition(origin.x + player->getContentSize().width/2,
                        origin.y + visibleSize.height/2);
    auto playerComponent = ComponentLua::create("src/player.lua");
    player->addComponent(playerComponent);
    scene->addChild(player);
    
    return scene;
}

