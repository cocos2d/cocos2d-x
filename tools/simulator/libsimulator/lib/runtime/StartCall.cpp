//
//  StartCall.cpp
//  simulator
//
//

#include "StartCall.h"
#include "CCLuaEngine.h"
#include "cocostudio/CocoStudio.h"

#include "Runtime.h"
#include "ConfigParser.h"
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
#include "DeviceEx.h"
#include "network/CCHTTPRequest.h"
#endif
#include "xxhash/xxhash.h"

USING_NS_CC;

// ----------------------------------------

StartupCall *StartupCall::create()
{
    StartupCall *call = new StartupCall();
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
    
    const ProjectConfig &project = RuntimeEngine::getInstance()->getProjectConfig();
    
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
    updatePreviewFuncForPath(path);
    
    // launch
    if (project.getDebuggerType() == kCCRuntimeDebuggerNone)
    {
        _previewFunc(path);
    }
    
    // track start event
    trackLaunchEvent();
}

//
// NOTE: track event on windows / mac platform
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
    
    char cidBuf[56] = {0};
    auto guid = player::DeviceEx::getInstance()->getUserGUID();
    snprintf(cidBuf, sizeof(cidBuf), "%x", XXH32(guid.c_str(), (int)guid.length(), 0));
    auto request = extra::HTTPRequest::createWithUrl(NULL,
                                                     "http://www.google-analytics.com/collect",
                                                     kCCHTTPRequestMethodPOST);
    request->addPOSTValue("v", "1");
    request->addPOSTValue("tid", "UA-58200293-1");
    request->addPOSTValue("cid", cidBuf);
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
    std::replace(entryFile.begin(), entryFile.end(), '\\', '/');
    parser->setEntryFile(entryFile);
    
    parser->setBindAddress(project.getBindAddress());
}

void StartupCall::updatePreviewFuncForPath(const std::string &path)
{
    // set loader
    _previewFunc = [](const std::string &path) { };
    
    if (endWithString(path, ".lua") || endWithString(path, ".luac"))
    {
        _launchEvent = "lua";
        _previewFunc = std::bind(&StartupCall::onPreviewLua, this, std::placeholders::_1);
    }
    else if (endWithString(path, ".csd"))
    {
        _launchEvent = "ccs";
        _previewFunc = std::bind(&StartupCall::onPreviewCocosCSD, this, std::placeholders::_1);
    }
    else if (endWithString(path, ".csb"))
    {
        _launchEvent = "ccs";
        _previewFunc = std::bind(&StartupCall::onPreviewCocosCSB, this, std::placeholders::_1);
    }
    else if (endWithString(path, ".js") || endWithString(path, ".jsc"))
    {
        _launchEvent = "js";
    }
}
