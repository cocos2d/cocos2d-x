#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"


using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();    
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#else
        glview = GLView::createWithRect(title.c_str(), Rect(0,0,960,640));
        director->setOpenGLView(glview);
#endif
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
   
    // register lua engine
    LuaEngine* pEngine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(pEngine);
    
    StartupCall *call = StartupCall::create(this);
    if (m_projectConfig.getDebuggerType() != kCCLuaDebuggerNone)
    {
        Scene *scene = Scene::create();
        LabelTTF *label = LabelTTF::create("WAITING FOR CONNECT TO DEBUGGER...", "Arial", 32);
        const Size winSize = director->getWinSize();
        label->setPosition(winSize.width / 2, winSize.height / 2);
        scene->addChild(label);
        director->runWithScene(scene);
        scene->runAction(CallFunc::create(call, callfunc_selector(StartupCall::startup)));
    }
    else
    {
        call->startup();
    }
    
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

void AppDelegate::setProjectConfig(const ProjectConfig& config)
{
    m_projectConfig = config;
}

void AppDelegate::setOpenRecents(const LuaValueArray& recents)
{
    m_openRecents = recents;
}

// ----------------------------------------

StartupCall *StartupCall::create(AppDelegate *app)
{
    StartupCall *call = new StartupCall();
    call->m_app = app;
    call->autorelease();
    return call;
}

void StartupCall::startup()
{
    LuaEngine *pEngine = LuaEngine::getInstance();
    LuaStack *pStack = pEngine->getLuaStack();
    
    ProjectConfig &projectConfig = m_app->m_projectConfig;
    
    // set search path
    string path = FileUtils::getInstance()->fullPathForFilename(projectConfig.getScriptFileRealPath().c_str());
    size_t pos;
    while ((pos = path.find_first_of("\\")) != std::string::npos)
    {
        path.replace(pos, 1, "/");
    }
    size_t p = path.find_last_of("/");
    string workdir;
    if (p != path.npos)
    {
        workdir = path.substr(0, p);
        pStack->addSearchPath(workdir.c_str());
    }
    
    // connect debugger
    if (projectConfig.getDebuggerType() != kCCLuaDebuggerNone)
    {
        pStack->connectDebugger(projectConfig.getDebuggerType(), NULL, 0, NULL, workdir.c_str());
    }
    
    // load framework
    if (projectConfig.isLoadPrecompiledFramework())
    {
        const string precompiledFrameworkPath = SimulatorConfig::sharedDefaults()->getPrecompiledFrameworkPath();
        pStack->loadChunksFromZIP(precompiledFrameworkPath.c_str());
    }
    
    // set default scene
    Scene *scene = Scene::create();
    if (Director::getInstance()->getRunningScene())
    {
        Director::getInstance()->replaceScene(scene);
    }
    else
    {
        Director::getInstance()->runWithScene(scene);
    }
    
    // load script
    string env = "__LUA_STARTUP_FILE__=\"";
    env.append(path);
    env.append("\"");
    pEngine->executeString(env.c_str());
    
    // set open recents
    lua_State *L = pEngine->getLuaStack()->getLuaState();
    lua_newtable(L);
    int i = 1;
    for (LuaValueArrayIterator it = m_app->m_openRecents.begin(); it != m_app->m_openRecents.end(); ++it)
    {
        lua_pushstring(L, it->stringValue().c_str());
        lua_rawseti(L, -2, i);
        ++i;
    }
    lua_setglobal(L, "__G__OPEN_RECENTS__");
    
    // set quick-cocos2d-x root path
    std::string quickPath = SimulatorConfig::sharedDefaults()->getQuickCocos2dxRootPath();
    lua_pushstring(L, quickPath.c_str());
    lua_setglobal(L, "__G__QUICK_PATH__");
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD LUA FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    pEngine->executeScriptFile(path.c_str());
}

