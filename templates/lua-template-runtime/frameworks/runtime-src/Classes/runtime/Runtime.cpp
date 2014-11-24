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

#include <vector>

static std::string g_projectPath;

void startScript(string strDebugArg)
{
    // register lua engine
    auto engine = LuaEngine::getInstance();
    if (!strDebugArg.empty())
    {
        // open debugger.lua module
        cocos2d::log("debug args = %s", strDebugArg.c_str());
        luaopen_lua_debugger(engine->getLuaStack()->getLuaState());
        engine->executeString(strDebugArg.c_str());
    }
    engine->executeScriptFile(ConfigParser::getInstance()->getEntryFile().c_str());
}


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

string& replaceAll(string& str, const string& old_value, const string& new_value)
{
    size_t start = 0;
    while(true)
    {
        size_t pos = 0;
        if((pos = str.find(old_value, start)) != string::npos) {
            str.replace(pos, old_value.length(), new_value);
            start = pos + new_value.length();
        }
        else break;
    }
    return str;
}

const char* getRuntimeVersion()
{
    return "1.5";
}

int lua_cocos2dx_runtime_addSearchPath(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_FileUtils_addSearchPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1 || argc == 2) 
    {
        std::string arg0;
        bool arg1 = false;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        if (argc == 2) {
            ok &= luaval_to_boolean(tolua_S, 3, &arg1);
        }

        if(!ok)
            return 0;
        std::string originPath = arg0;
        if (!FileUtils::getInstance()->isAbsolutePath(originPath))
            arg0 = FileServer::getShareInstance()->getWritePath() + originPath;
        cobj->addSearchPath(arg0, arg1);

        if (!FileUtils::getInstance()->isAbsolutePath(originPath))
#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            cobj->addSearchPath(g_projectPath + originPath, arg1);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            cobj->addSearchPath(originPath, arg1);
#endif
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addSearchPath",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_FileUtils_addSearchPath'.",&tolua_err);
#endif

    return 0;
}

int lua_cocos2dx_runtime_setSearchPaths(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::FileUtils* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.FileUtils",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::FileUtils*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_runtime_setSearchPaths'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::vector<std::string> vecPaths;

        ok &= luaval_to_std_vector_string(tolua_S, 2,&vecPaths);
        if(!ok)
            return 0;
        std::vector<std::string> originPath; // for IOS platform.
        std::vector<std::string> projPath; // for Desktop platform.
        for (int i = 0; i < vecPaths.size(); i++)
        {
            if (!FileUtils::getInstance()->isAbsolutePath(vecPaths[i]))
            {
                originPath.push_back(vecPaths[i]); // for IOS platform.
                projPath.push_back(g_projectPath+vecPaths[i]); //for Desktop platform.
                vecPaths[i] = FileServer::getShareInstance()->getWritePath() + vecPaths[i];
            }
        }
#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        vecPaths.insert(vecPaths.end(),projPath.begin(),projPath.end());
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        vecPaths.insert(vecPaths.end(),originPath.begin(),originPath.end());
#endif
        cobj->setSearchPaths(vecPaths);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSearchPaths",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_runtime_setSearchPaths'.",&tolua_err);
#endif

    return 0;
}

static void register_runtime_override_function(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.FileUtils");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1)){
        tolua_function(tolua_S,"addSearchPath",lua_cocos2dx_runtime_addSearchPath);
        tolua_function(tolua_S,"setSearchPaths",lua_cocos2dx_runtime_setSearchPaths);
    }
    lua_pop(tolua_S, 1);
}

void initRuntime()
{
    vector<string> searchPathArray = FileUtils::getInstance()->getSearchPaths();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    // add peoject's root directory to search path
    if (g_projectPath.empty())
    {
        extern std::string getCurAppPath();
        string appPath = getCurAppPath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        appPath.append("/../../");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        appPath.append("/../../../");
#endif
        appPath = replaceAll(appPath, "\\", "/");
        g_projectPath = appPath;
    }    
    searchPathArray.insert(searchPathArray.begin(), g_projectPath);
#endif
    
    // add writable path to search path
    searchPathArray.insert(searchPathArray.begin(), FileServer::getShareInstance()->getWritePath());
    FileUtils::getInstance()->setSearchPaths(searchPathArray);

    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    register_runtime_override_function(engine->getLuaStack()->getLuaState());

    static ConsoleCommand *g_customCommand;
    g_customCommand = new ConsoleCommand();
    g_customCommand->init();
}

void startRuntime()
{
    auto scene = Scene::create();
    auto connectLayer = new ConnectWaitLayer();
    connectLayer->autorelease();
    auto director = Director::getInstance();
    scene->addChild(connectLayer);
    director->runWithScene(scene);
}
