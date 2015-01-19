/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "Runtime.h"
#include "FileServer.h"
#include "ConnectWaitLayer.h"
#include "ConsoleCommand.h"
#include "cocos2d.h"
#include "ConfigParser.h"
#include "lua_debugger.h"
#include "CCLuaEngine.h"
#include "LuaBasicConversions.h"

#include "RuntimeLuaImpl.h"
#include "RuntimeCCSImpl.h"

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
#include "DeviceEx.h"
#include "network/CCHTTPRequest.h"
#include "xxhash/xxhash.h"
#endif

#include <vector>

std::string g_projectPath;

void recvBuf(int fd, char *pbuf, unsigned long bufsize)
{
    unsigned long leftLength = bufsize;
    while (leftLength != 0)
    {
        size_t recvlen = recv(fd, pbuf + bufsize - leftLength, leftLength ,0);
        if (recvlen <= 0)
        {
            usleep(1);
            continue;
        }
        leftLength -= recvlen;
    }
}

void sendBuf(int fd, const char *pbuf, unsigned long bufsize)
{
    unsigned long leftLength = bufsize;
    while (leftLength != 0)
    {
        size_t sendlen = send(fd, pbuf + bufsize - leftLength, leftLength ,0);
        if (sendlen <= 0)
        {
            usleep(1);
            continue;
        }
        leftLength -= sendlen;
    }
}

std::string& replaceAll(std::string& str, const std::string& old_value, const std::string& new_value)
{
    size_t start = 0;
    while(true)
    {
        size_t pos = 0;
        if((pos = str.find(old_value, start)) != std::string::npos) {
            str.replace(pos, old_value.length(), new_value);
            start = pos + new_value.length();
        }
        else break;
    }
    return str;
}

const char* getRuntimeVersion()
{
    return "1.9";
}

//////////////////////// Loader ////////////////////

void resetDesignResolution()
{
    cocos2d::Size size = ConfigParser::getInstance()->getInitViewSize();
    if (!ConfigParser::getInstance()->isLanscape())
    {
        std::swap(size.width, size.height);
    }
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(size.width, size.height, ResolutionPolicy::EXACT_FIT);
}

//
// RuntimeEngine
//

RuntimeEngine::RuntimeEngine()
: _runtime(nullptr)
, _eventTrackingEnable(false)
, _launchEvent("empty")
{

}

RuntimeEngine* RuntimeEngine::getInstance()
{
    static RuntimeEngine *instance = nullptr;
    if (!instance)
    {
        instance = new RuntimeEngine();
    }
    return instance;
}

void RuntimeEngine::setupRuntime()
{
    CC_SAFE_DELETE(_runtime);
    //
    // 1. get project type fron config.json
    // 2. init Lua / Js runtime
    //

    updateConfigParser();
    auto entryFile = ConfigParser::getInstance()->getEntryFile();
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
    ConfigParser::getInstance()->readConfig();
    entryFile = ConfigParser::getInstance()->getEntryFile();
#endif

    // Lua
    if ((entryFile.rfind(".lua") != std::string::npos) ||
        (entryFile.rfind(".luac") != std::string::npos))
    {
        _launchEvent = "lua";
        _runtime = RuntimeLuaImpl::create();
    }
    // Js
    else if ((entryFile.rfind(".js") != std::string::npos) ||
             (entryFile.rfind(".jsc") != std::string::npos))
    {
        _launchEvent = "js";
    }
    // csb
    else if ((entryFile.rfind(".csb") != std::string::npos))
    {
        _launchEvent = "ccs";
        _runtime = RuntimeCCSImpl::create();
    }
    // csd
    else if ((entryFile.rfind(".csd") != std::string::npos))
    {
        _launchEvent = "ccs";
        _runtime = RuntimeCCSImpl::create();
    }
}

void RuntimeEngine::setProjectConfig(const ProjectConfig &config)
{
    _project = config;
}

const ProjectConfig &RuntimeEngine::getProjectConfig()
{
    return _project;
}

void RuntimeEngine::setProjectPath(const std::string &workPath)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    vector<std::string> searchPathArray = FileUtils::getInstance()->getSearchPaths();

    if (workPath.empty())
    {
        extern std::string getCurAppPath();
        std::string appPath = getCurAppPath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        appPath.append("/../../");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        appPath.append("/../../../");
#endif
        appPath = replaceAll(appPath, "\\", "/");
        g_projectPath = appPath;
    }
    else
    {
        g_projectPath = workPath;
    }

    // add project's root directory to search path
    searchPathArray.insert(searchPathArray.begin(), g_projectPath);

    // add writable path to search path
    searchPathArray.insert(searchPathArray.begin(), FileServer::getShareInstance()->getWritePath());
    FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif
}

void RuntimeEngine::startScript(const std::string &args)
{
    resetDesignResolution();

    if (_runtime)
    {
        _runtime->startScript(args);
    }

    trackLaunchEvent();
}

void RuntimeEngine::start()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC)
    _project.setDebuggerType(kCCRuntimeDebuggerCodeIDE);
#endif

    // set search path
    string path = FileUtils::getInstance()->fullPathForFilename(_project.getScriptFileRealPath().c_str());
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
        FileUtils::getInstance()->addSearchPath(workdir);
    }

    // update search pathes
    FileUtils::getInstance()->addSearchPath(_project.getProjectDir());
    auto &customizedPathes = _project.getSearchPath();
    for (auto &path : customizedPathes)
    {
        FileUtils::getInstance()->addSearchPath(path);
    }

    //
    if (_project.getDebuggerType() == kCCRuntimeDebuggerNone)
    {
        setupRuntime();
        startScript(_project.getScriptFileRealPath());
    }
    else
    {
        startNetwork();
    }
}

void RuntimeEngine::end()
{
    if (_runtime)
    {
        _runtime->end();
    }
    ConsoleCommand::purge();
    FileServer::getShareInstance()->stop();
    ConfigParser::purge();
//    FileServer::purge();
}

void RuntimeEngine::setEventTrackingEnable(bool enable)
{
    _eventTrackingEnable = enable;
}

RuntimeProtocol* RuntimeEngine::getRuntime()
{
    return _runtime;
}

//
// private
//

void RuntimeEngine::showUI()
{
    auto scene = Scene::create();
    auto connectLayer = new ConnectWaitLayer();
    connectLayer->autorelease();
    auto director = Director::getInstance();
    scene->addChild(connectLayer);
    director->runWithScene(scene);
}

bool RuntimeEngine::startNetwork()
{
    ConsoleCommand::getShareInstance()->init();
    showUI();

    return true;
}

void RuntimeEngine::updateConfigParser()
{
    // set entry file
    auto parser = ConfigParser::getInstance();
    string entryFile(_project.getScriptFileRealPath());
    if (entryFile.find(_project.getProjectDir()) != string::npos)
    {
        entryFile.erase(0, _project.getProjectDir().length());
    }
    std::replace(entryFile.begin(), entryFile.end(), '\\', '/');

    parser->setEntryFile(entryFile);
    parser->setBindAddress(_project.getBindAddress());
}

//
// NOTE: track event on windows / mac platform
//
void RuntimeEngine::trackEvent(const std::string &eventName)
{
    if (!_eventTrackingEnable)
    {
        return ;
    }

#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    const char *platform = "win";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    const char *platform = "mac";
#else
    const char *platform = "UNKNOWN";
#endif

    char cidBuf[64] = {0};
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
    request->addPOSTValue("ea", eventName.c_str());

    request->start();

#endif // ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC))
}

void RuntimeEngine::trackLaunchEvent()
{
    trackEvent(_launchEvent);
}
