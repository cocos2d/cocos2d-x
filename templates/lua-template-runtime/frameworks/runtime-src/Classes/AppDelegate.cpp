#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "CodeIDESupport.h"
#include "Runtime.h"
#include "ConfigParser.h"
#include "lua_module_register.h"

#include "cocostudio/CocoStudio.h"

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
#include "service/DeviceEx.h"
#include "network/CCHTTPRequest.h"
#endif

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
    auto config = ConfigParser::getInstance();
    _project.setScriptFile(config->getEntryFile());
#endif
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

    if (_project.getDebuggerType() != kCCRuntimeDebuggerNone)
    {
        // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
        endRuntime();
    }

	ConfigParser::purge();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    //
#if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_CODE_IDE_DEBUG_SUPPORT > 0))
    _project.setDebuggerType(kCCRuntimeDebuggerCodeIDE);
#endif

    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);
   
    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

    // If you want to use Quick-Cocos2d-X, please uncomment below code
    // register_all_quick_manual(L);

    LuaStack* stack = engine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
    
    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());
    
    StartupCall *call = StartupCall::create(this);
    call->startup();
    
	cocos2d::log("iShow!");
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


void AppDelegate::setProjectConfig(const ProjectConfig& project)
{
    _project = project;
}

void AppDelegate::reopenProject()
{
    auto fileUtils = FileUtils::getInstance();
    
    //
    // set root path
    // set search root **MUST** before set search paths
    //
    fileUtils->setDefaultResourceRootPath(_project.getProjectDir());
    
    // clean
    Director::getInstance()->getTextureCache()->removeAllTextures();
    Director::getInstance()->purgeCachedData();
    SimpleAudioEngine::getInstance()->stopAllEffects();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    vector<string> searchPaths;
    fileUtils->setSearchPaths(searchPaths);
    
    const string writablePath = _project.getWritableRealPath();
    if (writablePath.length())
    {
        FileUtils::getInstance()->setWritablePath(writablePath.c_str());
    }

    resetDesignResolution();
    
    StartupCall *call = StartupCall::create(this);
    call->startup();
}

// ----------------------------------------

StartupCall *StartupCall::create(AppDelegate *app)
{
    StartupCall *call = new StartupCall();
    call->_app = app;
    call->autorelease();
    return call;
}

StartupCall::StartupCall()
    : _launchEvent("empty")
{
}

static bool endWithString(const std::string &buf, const std::string &suffix)
{
    return ((buf.find(suffix) + suffix.length()) == buf.length());
}

void StartupCall::startup()
{
    auto engine = LuaEngine::getInstance();
    auto stack = engine->getLuaStack();
    
    const ProjectConfig &project = _app->_project;
    
    // set search path
    string path = FileUtils::getInstance()->fullPathForFilename(project.getScriptFileRealPath().c_str());
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
        stack->addSearchPath(workdir.c_str());
        FileUtils::getInstance()->addSearchPath(workdir);
    }
    
    // update search pathes
    FileUtils::getInstance()->addSearchPath(project.getProjectDir());
    auto &customizedPathes = project.getSearchPath();
    for (auto &path : customizedPathes)
    {
        FileUtils::getInstance()->addSearchPath(path);
    }
    
    updateConfigParser(project);
    if (FileUtils::getInstance()->isFileExist(path))
    {
        updatePreviewFuncForPath(path);
        
        // launch
        if (project.getDebuggerType() == kCCRuntimeDebuggerNone)
        {
            _previewFunc(path);
        }
        else
        {
            // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
            initRuntime(project.getProjectDir());
            startRuntime();
        }
    }
    else
    {
        CCLOG("[ERROR]: %s is not exist.", path.c_str());
    }

    // track start event
    trackLaunchEvent();
}

// *NOTE*
// track event on windows / mac platform
//
void StartupCall::trackEvent(const char *eventName)
{
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    const char *platform = "win";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    const char *platform = "mac";
#else
    const char *platform = "UNKNOWN";
#endif
    
    auto request = extra::HTTPRequest::createWithUrl(NULL,
                                                      "http://www.google-analytics.com/collect",
                                                      kCCHTTPRequestMethodPOST);
    request->addPOSTValue("v", "1");
    request->addPOSTValue("tid", "UA-55061270-1");
    request->addPOSTValue("cid", player::DeviceEx::getInstance()->getUserGUID().c_str());
    request->addPOSTValue("t", "event");
    
    request->addPOSTValue("an", "simulator");
    request->addPOSTValue("av", cocos2dVersion());
    
    request->addPOSTValue("ec", platform);
    request->addPOSTValue("ea", eventName);
    
    request->start();

#endif // ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
}

void StartupCall::trackLaunchEvent()
{
    trackEvent(_launchEvent.c_str());
}

void StartupCall::onPreviewCocosCSD(const std::string &path)
{
    std::string filepath = path;
    if (filepath.empty())
    {
        filepath = ConfigParser::getInstance()->getEntryFile();
    }
    
    CCLOG("------------------------------------------------");
    CCLOG("LOAD Cocos Studio FILE (.csd): %s", filepath.c_str());
    CCLOG("------------------------------------------------");
    
    auto node = CSLoader::getInstance()->createNodeWithFlatBuffersForSimulator(filepath.c_str());
	auto action = cocostudio::timeline::ActionTimelineCache::getInstance()->createActionWithFlatBuffersForSimulator(filepath.c_str());
	if (action)
	{
		node->runAction(action);
		action->gotoFrameAndPlay(0);
	}

    if (node)
    {
        if (Director::getInstance()->getRunningScene())
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->replaceScene(scene);
        }
        else
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->runWithScene(scene);
        }
    }
}

void StartupCall::onPreviewCocosCSB(const std::string &path)
{
    std::string filepath = path;
    if (filepath.empty())
    {
        filepath = ConfigParser::getInstance()->getEntryFile();
    }
    CCLOG("\n------------------------------------------------\n");
    CCLOG("[WARNING]: using **SUITABLE** Cocos Studio generate csb file!!");
    CCLOG("LOAD Cocos Studio FILE (.csb): %s", filepath.c_str());
    CCLOG("\n------------------------------------------------\n");
    
    auto node = CSLoader::getInstance()->createNode(filepath);
    if (node)
    {
        if (Director::getInstance()->getRunningScene())
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->replaceScene(scene);
        }
        else
        {
            auto scene = Scene::create();
            scene->addChild(node);
            Director::getInstance()->runWithScene(scene);
        }
    }
}

void StartupCall::onPreviewLua(const std::string &path)
{
    CCLOG("------------------------------------------------");
    CCLOG("LOAD Lua FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    
    LuaEngine::getInstance()->executeScriptFile(path.c_str());
}

void StartupCall::onPreviewJs(const std::string &path)
{
    CCLOG("------------------------------------------------");
    CCLOG("LOAD Js FILE: %s", path.c_str());
    CCLOG("------------------------------------------------");
    
    CCLOG("TODO: ");
}

void StartupCall::updateConfigParser(const ProjectConfig& project)
{
    // set entry file
    auto parser = ConfigParser::getInstance();
    string entryFile(project.getScriptFileRealPath());
    if (entryFile.find(project.getProjectDir()) != string::npos)
    {
        entryFile.erase(0, project.getProjectDir().length());
    }
    entryFile = replaceAll(entryFile, "\\", "/");
    parser->setEntryFile(entryFile);
    
    parser->setBindAddress(project.getBindAddress());
}

void StartupCall::updatePreviewFuncForPath(const std::string &path)
{
    // set loader
    _previewFunc = [](const std::string &path) { CCLOG("[WARNING]: unsupport %s", path.c_str()); };
    
    if (!FileUtils::getInstance()->isFileExist(path))
    {
        CCLOG("[ERROR]: %s is not exist.", path.c_str());
        return ;
    }
    
    if (endWithString(path, ".lua"))
    {
        _launchEvent = "lua";
        _previewFunc = std::bind(&StartupCall::onPreviewLua, this, std::placeholders::_1);
        setLoader(std::bind(&luaScriptLoader, std::placeholders::_1));
    }
    else if (endWithString(path, ".csd"))
    {
        _launchEvent = "ccs";
        _previewFunc = std::bind(&StartupCall::onPreviewCocosCSD, this, std::placeholders::_1);
        setLoader(std::bind(&StartupCall::onPreviewCocosCSD, this, std::placeholders::_1));
    }
    else if (endWithString(path, ".csb"))
    {
        _launchEvent = "ccs";
        _previewFunc = std::bind(&StartupCall::onPreviewCocosCSB, this, std::placeholders::_1);
        setLoader(std::bind(&StartupCall::onPreviewCocosCSB, this, std::placeholders::_1));
    }
    else if (endWithString(path, ".js"))
    {
        _launchEvent = "js";
        _previewFunc = std::bind(&StartupCall::onPreviewJs, this, std::placeholders::_1);
    }
}
