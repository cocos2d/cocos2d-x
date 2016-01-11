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

#include "RuntimeProtocol.h"
#include "cocos2d.h"
using namespace cocos2d;

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

    // set bind address
    _console->setBindAddress(ConfigParser::getInstance()->getBindAddress());
    _console->listenOnTCP(ConfigParser::getInstance()->getConsolePort()); // 6010,6050

    _fileserver = FileServer::getShareInstance();
    _fileserver->listenOnTCP(ConfigParser::getInstance()->getUploadPort()); // 6020,6060
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
            rapidjson::Document::AllocatorType& allocator = dReplyParse.GetAllocator();
            dReplyParse.AddMember("cmd", rapidjson::Value(strcmd.c_str(), allocator)
                                  , allocator);
            if (dArgParse.HasMember("seq"))
            {
                dReplyParse.AddMember("seq",dArgParse["seq"],allocator);
            }
            
            if(strcmp(strcmd.c_str(), "start-logic") == 0)
            {
                auto runtime = RuntimeEngine::getInstance()->getRuntime();
                if (!runtime)
                {
                    RuntimeEngine::getInstance()->setupRuntime();
                    runtime = RuntimeEngine::getInstance()->getRuntime();
                }
                if (runtime) runtime->onStartDebuger(dArgParse, dReplyParse);
            } else if (strcmp(strcmd.c_str(),"clearcompile")==0)
            {
                auto runtime = RuntimeEngine::getInstance()->getRuntime();
                if (!runtime)
                {
                    RuntimeEngine::getInstance()->setupRuntime();
                    runtime = RuntimeEngine::getInstance()->getRuntime();
                }
                if (runtime) runtime->onClearCompile(dArgParse, dReplyParse);
            } else if(strcmp(strcmd.c_str(),"precompile")==0)
            {
                auto runtime = RuntimeEngine::getInstance()->getRuntime();
                if (!runtime)
                {
                    RuntimeEngine::getInstance()->setupRuntime();
                    runtime = RuntimeEngine::getInstance()->getRuntime();
                }
                if (runtime) runtime->onPrecompile(dArgParse, dReplyParse);
            } else if(strcmp(strcmd.c_str(), "reload") == 0)
            {
                auto runtime = RuntimeEngine::getInstance()->getRuntime();
                if (!runtime)
                {
                    RuntimeEngine::getInstance()->setupRuntime();
                    runtime = RuntimeEngine::getInstance()->getRuntime();
                }
                if (runtime) runtime->onReload(dArgParse, dReplyParse);
            } else if(strcmp(strcmd.c_str(), "getversion") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                bodyvalue.AddMember("version", rapidjson::Value(getRuntimeVersion(), allocator)
                                    , allocator);
                dReplyParse.AddMember("body", bodyvalue, allocator);
                dReplyParse.AddMember("code", 0, allocator);
            } else if(strcmp(strcmd.c_str(), "getfileinfo") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Document* filecfgjson = _fileserver->getFileCfgJson();
                for (rapidjson::Value::MemberIterator itr = filecfgjson->MemberBegin()
                     ; itr != filecfgjson->MemberEnd()
                     ; ++itr)
                {
                    bodyvalue.AddMember(itr->name, itr->value, allocator);
                }
                
                dReplyParse.AddMember("body", bodyvalue, allocator);
                dReplyParse.AddMember("code", 0, allocator);
               
            } else if (strcmp(strcmd.c_str(), "getEntryfile") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Value entryFileValue(rapidjson::kStringType);
                entryFileValue.SetString(ConfigParser::getInstance()->getEntryFile().c_str(), allocator);
                bodyvalue.AddMember("entryfile", entryFileValue, allocator);
                dReplyParse.AddMember("body", bodyvalue,allocator);
                dReplyParse.AddMember("code", 0, allocator);
            } else if(strcmp(strcmd.c_str(), "getIP") == 0)
            {
                rapidjson::Value bodyvalue(rapidjson::kObjectType);
                rapidjson::Value IPValue(rapidjson::kStringType);
                IPValue.SetString(getIPAddress().c_str(), allocator);
                bodyvalue.AddMember("IP", IPValue,allocator);
                dReplyParse.AddMember("body", bodyvalue,allocator);
                dReplyParse.AddMember("code", 0, allocator);

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
                        
                        // remove js compiled script
                        auto runtime = RuntimeEngine::getInstance()->getRuntime();
                        if (runtime) runtime->onRemove(filename);
                        
                        // remove file from disk
                        string filepath(_fileserver->getWritePath() + "/" + filename);
                        if (FileUtils::getInstance()->isFileExist(filepath)) 
                        {
                            if(remove(filepath.c_str()) != 0) 
                            {
                                // remove failed
                                bodyvalue.AddMember(rapidjson::Value(filename, allocator)
                                                    , rapidjson::Value(2)
                                                    , allocator);
                            }
                        } else
                        {
                            // file not exist
                            bodyvalue.AddMember(rapidjson::Value(filename, allocator)
                                                , rapidjson::Value(1)
                                                , allocator);
                        }

                        // file remove success, remove it from record
                        if (! FileUtils::getInstance()->isFileExist(filepath))
                            _fileserver->removeResFileInfo(filename);
                    }

                    dReplyParse.AddMember("body", bodyvalue, allocator);
                }

                dReplyParse.AddMember("code",0,allocator);
            } else if(strcmp(strcmd.c_str(), "shutdownapp") == 0)
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
                auto glview = dynamic_cast<GLViewImpl*> (Director::getInstance()->getOpenGLView());
                HWND hWnd = glview->getWin32Window();
                ::SendMessage(hWnd, WM_CLOSE, NULL, NULL);
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
                platformValue.SetString(platform.c_str(), allocator);
                bodyvalue.AddMember("platform", platformValue, allocator);
                dReplyParse.AddMember("body", bodyvalue, allocator);
                dReplyParse.AddMember("code", 0, allocator);
            } else if(strcmp(strcmd.c_str(), "usewritablepath") == 0)
            {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                // only iOS and Android need to open using write path by Code IDE
                FileServer::getShareInstance()->setIsUsingWritePath(true);
                
                std::vector<std::string> searchPathArray = FileUtils::getInstance()->getSearchPaths();
                searchPathArray.insert(searchPathArray.begin(), FileServer::getShareInstance()->getWritePath());
                FileUtils::getInstance()->setSearchPaths(searchPathArray);
#endif
                
                dReplyParse.AddMember("code", 0, allocator);
            }
            else if (strcmp(strcmd.c_str(), "workdir") == 0)
            {
                if (dArgParse.HasMember("path"))
                {
                    const rapidjson::Value& objectPath = dArgParse["path"];
                    FileUtils::getInstance()->setDefaultResourceRootPath(objectPath.GetString());
                    
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    bodyvalue.AddMember("path", rapidjson::Value(objectPath.GetString(), allocator)
                                        , allocator);
                    dReplyParse.AddMember("body", bodyvalue, allocator);
                }
                dReplyParse.AddMember("code", 0, allocator);
            }
            else if (strcmp(strcmd.c_str(), "writablePath") == 0)
            {
                if (dArgParse.HasMember("path"))
                {
                    const rapidjson::Value& objectPath = dArgParse["path"];
                    FileUtils::getInstance()->setWritablePath(objectPath.GetString());
                    
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    bodyvalue.AddMember("path", rapidjson::Value(objectPath.GetString(), allocator)
                                        , allocator);
                    dReplyParse.AddMember("body", bodyvalue, allocator);
                }
                dReplyParse.AddMember("code", 0, allocator);
            }
            
            rapidjson::StringBuffer buffer;
            rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
            dReplyParse.Accept(writer);
            string msgContent = buffer.GetString();
            char msgLength[64] = {0x1, 0};
            sprintf(msgLength + 1, "%ld:", msgContent.size());
            
            string msg(msgLength + msgContent);
            
            sendBuf(fd, msg.c_str(), msg.size());
        }
    });
}

ConsoleCommand::~ConsoleCommand()
{
	Director::getInstance()->getConsole()->stop();
}
