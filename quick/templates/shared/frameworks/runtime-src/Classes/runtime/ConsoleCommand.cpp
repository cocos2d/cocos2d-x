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
#include "ConfigParser.h"
#include "ConsoleCommand.h"
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "CCLuaEngine.h"

#include "cocos2d.h"
using namespace cocos2d;

static void resetLuaModule(const string& fileName)
{
    if (fileName.empty())
    {
        return;
    }
    auto engine = LuaEngine::getInstance();
    LuaStack* luaStack = engine->getLuaStack();
    lua_State* stack = luaStack->getLuaState();
    lua_getglobal(stack, "package");                         /* L: package */
    lua_getfield(stack, -1, "loaded");                       /* L: package loaded */
    lua_pushnil(stack);                                     /* L: lotable ?-.. nil */
    while (0 != lua_next(stack, -2))                     /* L: lotable ?-.. key value */
    {
        //CCLOG("%s - %s \n", tolua_tostring(stack, -2, ""), lua_typename(stack, lua_type(stack, -1)));
        std::string key = tolua_tostring(stack, -2, "");
        std::string tableKey = key;
        size_t found = tableKey.rfind(".lua");
        if (found != std::string::npos)
            tableKey = tableKey.substr(0, found);
        tableKey = replaceAll(tableKey, ".", "/");
        tableKey = replaceAll(tableKey, "\\", "/");
        tableKey.append(".lua");
        found = fileName.rfind(tableKey);
        if (0 == found || (found != std::string::npos && fileName.at(found - 1) == '/'))
        {
            lua_pushstring(stack, key.c_str());
            lua_pushnil(stack);
            if (lua_istable(stack, -5))
            {
                lua_settable(stack, -5);
            }
        }
        lua_pop(stack, 1);
    }
    lua_pop(stack, 2);
}

bool reloadScript(const string& file)
{
    auto director = Director::getInstance();
    FontFNT::purgeCachedData();
    if (director->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        director->getTextureCache()->removeAllTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();
    string modulefile = file;
    
    if (! modulefile.empty())
    {
        resetLuaModule(modulefile);
    }
    else
    {
        modulefile = ConfigParser::getInstance()->getEntryFile().c_str();
    }
    
    auto engine = LuaEngine::getInstance();
    LuaStack* luaStack = engine->getLuaStack();
    std::string require = "require \'" + modulefile + "\'";
    return luaStack->executeString(require.c_str());
}

ConsoleCommand* ConsoleCommand::s_sharedConsoleCommand = nullptr;
ConsoleCommand* ConsoleCommand::getShareInstance() 
{
	if (s_sharedConsoleCommand == nullptr)
	{
		s_sharedConsoleCommand = new ConsoleCommand();
	}
	return s_sharedConsoleCommand;
}

void ConsoleCommand::purge()
{
	if (s_sharedConsoleCommand != nullptr)
	{
		delete s_sharedConsoleCommand;
	}
}

void ConsoleCommand::init()
{
    cocos2d::Console *_console = Director::getInstance()->getConsole();
    static struct Console::Command commands[] =
    {
        {"sendrequest","send command to runtime.Args[json format]",std::bind(&ConsoleCommand::onSendCommand, this, std::placeholders::_1, std::placeholders::_2)},
    };
    for (int i = 0;i< sizeof(commands) / sizeof(Console::Command);i++)
    {
        _console->addCommand(commands[i]);
    }
#if(CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
    _console->listenOnTCP(ConfigParser::getInstance()->getConsolePort());
#else
    _console->listenOnTCP(6010);
#endif

    _fileserver = FileServer::getShareInstance();
#if(CC_PLATFORM_MAC == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
    _fileserver->listenOnTCP(ConfigParser::getInstance()->getUploadPort());
#else
    _fileserver->listenOnTCP(6020);
#endif
    _fileserver->readResFileFinfo();
}

void ConsoleCommand::onSendCommand(int fd, const std::string &args)
{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        rapidjson::Document dArgParse;
        dArgParse.Parse<0>(args.c_str());
        if (dArgParse.HasMember("cmd"))
        {
            string strcmd = dArgParse["cmd"].GetString();
            
            rapidjson::Document dReplyParse;
            dReplyParse.SetObject();
            dReplyParse.AddMember("cmd",strcmd.c_str(),dReplyParse.GetAllocator());
            if (dArgParse.HasMember("seq"))
            {
                dReplyParse.AddMember("seq",dArgParse["seq"],dReplyParse.GetAllocator());
            }
            
            if(strcmp(strcmd.c_str(), "start-logic") == 0)
            {
                char szDebugArg[1024] = {0};
                sprintf(szDebugArg, "require('debugger')(%s,'%s')",dArgParse["debugcfg"].GetString(), "");
                startScript(szDebugArg);
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());

            } else if(strcmp(strcmd.c_str(), "reload") == 0)
            {
                if (dArgParse.HasMember("modulefiles"))
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
                    for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
                    {
                        if (!reloadScript(objectfiles[i].GetString()))
                        {
                            bodyvalue.AddMember(objectfiles[i].GetString(), 1, dReplyParse.GetAllocator());
                        }
                    }
                    if (0 == objectfiles.Size())
                    {
                        reloadScript("");
                    }
                    dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                }
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
            } else if(strcmp(strcmd.c_str(), "getversion") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                bodyvalue.AddMember("version", getRuntimeVersion(), dReplyParse.GetAllocator());
                dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
            } else if(strcmp(strcmd.c_str(), "getfileinfo") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Document* filecfgjson = _fileserver->getFileCfgJson();
                for (auto it = filecfgjson->MemberonBegin(); it != filecfgjson->MemberonEnd(); ++it)
                {
                    bodyvalue.AddMember(it->name.GetString(), it->value.GetString(), dReplyParse.GetAllocator());
                }
                dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
               
            } else if (strcmp(strcmd.c_str(), "getEntryfile") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Value entryFileValue(rapidjson::kStringType);
                entryFileValue.SetString(ConfigParser::getInstance()->getEntryFile().c_str(), dReplyParse.GetAllocator());
                bodyvalue.AddMember("entryfile", entryFileValue, dReplyParse.GetAllocator());
                dReplyParse.AddMember("body", bodyvalue,dReplyParse.GetAllocator());
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
            } else if(strcmp(strcmd.c_str(), "getIP") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Value IPValue(rapidjson::kStringType);
                IPValue.SetString(getIPAddress().c_str(), dReplyParse.GetAllocator());
                bodyvalue.AddMember("IP", IPValue,dReplyParse.GetAllocator());
                dReplyParse.AddMember("body", bodyvalue,dReplyParse.GetAllocator());
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());

            } else if(strcmp(strcmd.c_str(), "remove") == 0)
            {
                if (dArgParse.HasMember("files"))
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    const rapidjson::Value& objectfiles = dArgParse["files"];
                    const char* filename = NULL;
                    for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
                    {
                        filename = objectfiles[i].GetString();
                        
                        // remove file from disk
                        string filepath(_fileserver->getWritePath() + "/" + filename);
                        if (FileUtils::getInstance()->isFileExist(filepath)) 
                        {
                            if(remove(filepath.c_str()) != 0) 
                            {
                                // remove failed
                                bodyvalue.AddMember(filename, 2, dReplyParse.GetAllocator());
                            }
                        } else
                        {
                            // file not exist
                            bodyvalue.AddMember(filename, 1, dReplyParse.GetAllocator());
                        }

                        // file remove success, remove it from record
                        if (! FileUtils::getInstance()->isFileExist(filepath))
                            _fileserver->removeResFileInfo(filename);
                    }

                    dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                }

                dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
            } else if(strcmp(strcmd.c_str(), "shutdownapp") == 0)
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
                extern void shutDownApp();
                shutDownApp();
#else
                exit(0);
#endif	
            } else if(strcmp(strcmd.c_str(), "getplatform") == 0)
            {
                string platform="UNKNOW";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
                platform = "WIN32";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
                platform = "MAC";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                platform = "IOS";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                platform = "ANDROID";
#endif
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Value platformValue(rapidjson::kStringType);
                platformValue.SetString(platform.c_str(), dReplyParse.GetAllocator());
                bodyvalue.AddMember("platform", platformValue, dReplyParse.GetAllocator());
                dReplyParse.AddMember("body", bodyvalue, dReplyParse.GetAllocator());
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
            } else if(strcmp(strcmd.c_str(), "usewritablepath") == 0)
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                // only iOS and Android need to open using write path by Code IDE
                FileServer::getShareInstance()->setIsUsingWritePath(true);
                
                std::vector<std::string> searchPathArray = FileUtils::getInstance()->getSearchPaths();
                searchPathArray.insert(searchPathArray.begin(), FileServer::getShareInstance()->getWritePath());
                FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif
                
                dReplyParse.AddMember("code", 0, dReplyParse.GetAllocator());
            }
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
            dReplyParse.Accept(writer);
            string msgContent = buffer.GetString();
            char msgLength[64] = {0x1, 0};
            sprintf(msgLength + 1, "%d:", msgContent.size());
            
            string msg(msgLength + msgContent);
            
            sendBuf(fd, msg.c_str(), msg.size());
        }
    });
}

ConsoleCommand::~ConsoleCommand()
{
	Director::getInstance()->getConsole()->stop();
}
