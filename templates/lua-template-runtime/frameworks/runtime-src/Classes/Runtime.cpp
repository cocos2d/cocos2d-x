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
#include "lua_debugger.h"
#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

std::string g_resourcePath;
static rapidjson::Document g_filecfgjson; 

extern string getIPAddress();
const char* getRuntimeVersion()
{
    return "0.0.1";
}
void startScript(string strDebugArg)
{
    // register lua engine
    auto engine = LuaEngine::getInstance();
    if (!strDebugArg.empty())
    {
        engine->executeString(strDebugArg.c_str());
    }
    cocos2d::log("debug args = %s",strDebugArg.c_str());
    engine->executeScriptFile("src/main.lua");
}

bool reloadScript(const string& modulefile)
{
    string strfile = modulefile;
    if (strfile.empty())
    {
        strfile = "src/main.lua";
    }

    auto director = Director::getInstance();
    FontFNT::purgeCachedData();
    if (director->getOpenGLView())
    {
        SpriteFrameCache::getInstance()->removeSpriteFrames();
        director->getTextureCache()->removeAllTextures();
    }
    FileUtils::getInstance()->purgeCachedEntries();

    director->getScheduler()->unscheduleAll();
    director->getScheduler()->scheduleUpdate(director->getActionManager(), Scheduler::PRIORITY_SYSTEM, false);

    return (LuaEngine::getInstance()->reload(strfile.c_str())==0);
}


class VisibleRect
{
public:
    static Rect getVisibleRect();
    
    static Point left();
    static Point right();
    static Point top();
    static Point bottom();
    static Point center();
    static Point leftTop();
    static Point rightTop();
    static Point leftBottom();
    static Point rightBottom();
private:
    static void lazyInit();
    static Rect s_visibleRect;
};

Rect VisibleRect::s_visibleRect;

void VisibleRect::lazyInit()
{
    // no lazy init
    // Useful if we change the resolution in runtime
    s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect VisibleRect::getVisibleRect()
{
    lazyInit();
    return s_visibleRect;
}

Point VisibleRect::left()
{
    lazyInit();
    return Point(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Point VisibleRect::right()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Point VisibleRect::top()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Point VisibleRect::bottom()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

Point VisibleRect::center()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Point VisibleRect::leftTop()
{
    lazyInit();
    return Point(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Point VisibleRect::rightTop()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Point VisibleRect::leftBottom()
{
    lazyInit();
    return s_visibleRect.origin;
}

Point VisibleRect::rightBottom()
{
    lazyInit();
    return Point(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}

class ConnectWaitLayer: public Layer
{
public:

    ConnectWaitLayer()
    {
        string strip = getIPAddress();
        char szIPAddress[512]={0};
        sprintf(szIPAddress, "LocalIP: %s",strip.c_str());
        auto label = LabelTTF::create(szIPAddress, "Arial", 24);
        addChild(label, 9999);
        label->setPosition( Point(VisibleRect::center().x, VisibleRect::top().y - 30) );
        
        string strShowMsg ="";
        if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM || CC_PLATFORM_MAC == CC_TARGET_PLATFORM)
        {
            strShowMsg = "waiting for debugger to connect ...";
        }else
        {
            strShowMsg = "waiting for file transfer ...";
        }		
        auto labelwait = LabelTTF::create(strShowMsg.c_str(), "Arial", 22);
        addChild(labelwait, 10000);
        labelwait->setPosition( Point(VisibleRect::center().x, VisibleRect::center().y) );
        
        
        auto labelPlay = LabelTTF::create("play", "Arial", 20);
        auto menuItem = MenuItemLabel::create(labelPlay, CC_CALLBACK_1(ConnectWaitLayer::playerCallback, this));
        auto menu = Menu::create(menuItem, NULL);
        
        menu->setPosition( Point::ZERO );
        menuItem->setPosition( Point( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
        addChild(menu, 1);
    }
    
    void playerCallback(Object* sender)
    {
        startScript("");
    }

};


#if defined(_MSC_VER) || defined(__MINGW32__)
#include <io.h>
#include <WS2tcpip.h>

#define bzero(a, b) memset(a, 0, b);

#else
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#endif

class  FileServer
{
public:
    
    FileServer()
    {
        _listenfd = -1;
        _running = false;
        _endThread = false;
    }
    
    bool listenOnTCP(int port);
    void stop();
    
private:
    bool receiveFile(int fd);
    void addClient();
    void loop();
 
    // file descriptor: socket, console, etc.
    int _listenfd;
    int _maxfd;
    std::vector<int> _fds;
    std::thread _thread;
    fd_set _read_set;
    bool _running;
    bool _endThread;
};

bool FileServer::listenOnTCP(int port)
{
    int listenfd, n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;
    char serv[30];

    snprintf(serv, sizeof(serv)-1, "%d", port );
    serv[sizeof(serv)-1]=0;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET; // AF_UNSPEC: Do we need IPv6 ?
    hints.ai_socktype = SOCK_STREAM;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    WSADATA wsaData;
    n = WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif

    if ( (n = getaddrinfo(NULL, serv, &hints, &res)) != 0) {
        fprintf(stderr,"net_listen error for %s: %s", serv, gai_strerror(n));
        return false;
    }

    ressave = res;
    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;       /* error, try next one */
        
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));
        if (::bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */
        
        close(listenfd);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
        perror("net_listen:");
        freeaddrinfo(ressave);
        return false;
    }

    listen(listenfd, 1);

    if (res->ai_family == AF_INET) 
    {
        char buf[INET_ADDRSTRLEN] = "";
        struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin_addr, buf, sizeof(buf)) != NULL )
            cocos2d::log("Console: listening on  %s : %d", buf, ntohs(sin->sin_port));
        else
            perror("inet_ntop");
    } else if (res->ai_family == AF_INET6) 
    {
        char buf[INET6_ADDRSTRLEN] = "";
        struct sockaddr_in6 *sin = (struct sockaddr_in6*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin6_addr, buf, sizeof(buf)) != NULL )
            cocos2d::log("Console: listening on  %s : %d", buf, ntohs(sin->sin6_port));
        else
            perror("inet_ntop");
    }
    freeaddrinfo(ressave);
    _listenfd = listenfd;
    _thread = std::thread( std::bind( &FileServer::loop, this) );
    return true;	
}
    
void FileServer::stop()
{
    if( _running ) {
        _endThread = true;
        _thread.join();
    }
}

string& replaceAll(string& str,const string& old_value,const string& new_value)
{
    while(true)
    {
        int pos=0;
        if((pos=str.find(old_value,0))!=string::npos)
            str.replace(pos,old_value.length(),new_value);
        else break;
    }
    return str;
}

bool CreateDir(const char *sPathName)
{
    char   DirName[256]={0};
    strcpy(DirName,   sPathName);
    int   i,len   =   strlen(DirName);
    if(DirName[len-1]!='/')
        strcat(DirName,   "/");
    
    len   =   strlen(DirName);
    for(i=1;   i<len;   i++)
    {
        if(DirName[i]=='/')
        {
            DirName[i]   =   0;
            if(access(DirName,   NULL)!=0   )
            {
#ifdef _WIN32
                if(mkdir(DirName/*,   0755*/)==-1)
#else
                if(mkdir(DirName,   0755)==-1)
#endif
                {
                    perror("mkdir   error");
                    return  false;
                }
            }  
            DirName[i]   =   '/';  
        }  
    }  
    
    return   true;  
}

static bool updateResFileInfo()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
    g_filecfgjson.Accept(writer);
    const char* str = buffer.GetString();

    string filecfg = g_resourcePath;
    filecfg.append("/");
    filecfg.append("fileinfo_debug.json");
    FILE * pFile = fopen (filecfg.c_str() , "w");
    if (!pFile)
        return false;
    
    fwrite(str,sizeof(char),strlen(str),pFile);
    fclose(pFile);

    return true;
}

static void readResFileFinfo()
{
    string filecfg = g_resourcePath;
    filecfg.append("/");
    filecfg.append("fileinfo_debug.json");
    FILE * pFile = fopen (filecfg.c_str() , "r");
    if(pFile)
    {
        rapidjson::FileStream inputStream(pFile);
        g_filecfgjson.ParseStream<0>(inputStream);
        fclose(pFile);
    }
    if(!g_filecfgjson.IsObject())
    {
        g_filecfgjson.SetObject();
    }
}

bool FileServer::receiveFile(int fd)
{
    char headlen[5]={0};
    if (recv(fd, headlen, 4,0)<=0) {
        return  false;
    }
    char *headSeg = new char[atoi(headlen)+1];
    if (!headSeg)
    {
        return false;
    }
    memset(headSeg,0,atoi(headlen)+1);

    if (recv(fd, headSeg, atoi(headlen),0)<=0) {
        return  false;
    }
    rapidjson::Document headjson; 
    headjson.Parse<0>(headSeg);
    if (headjson.HasMember("filename"))
    {
        string filename = headjson["filename"].GetString();
        char fullfilename[1024]={0};
        sprintf(fullfilename,"%s%s",g_resourcePath.c_str(),filename.c_str());
        string file(fullfilename);
        file=replaceAll(file,"\\","/");
        sprintf(fullfilename, "%s", file.c_str());
        cocos2d::log("recv fullfilename = %s",fullfilename);
        CreateDir(file.substr(0,file.find_last_of("/")).c_str());
        FILE *fp =fopen(fullfilename, "wb");
        int length =0;
        while ((length=recv(fd, fullfilename, sizeof(fullfilename),0)) > 0) {
            fwrite(fullfilename, sizeof(char), length,fp);
        }
        fclose(fp);

        if (headjson.HasMember("lastmodifytime"))
        {
            string filemodifytime = headjson["lastmodifytime"].GetString();
            if (g_filecfgjson.HasMember(filename.c_str()))
            {
                g_filecfgjson.RemoveMember(filename.c_str());
            }
            rapidjson::Value filetimeValue(rapidjson::kStringType);
            filetimeValue.SetString(filemodifytime.c_str(),g_filecfgjson.GetAllocator());
            rapidjson::Value filenameValue(rapidjson::kStringType);
            filenameValue.SetString(filename.c_str(),g_filecfgjson.GetAllocator());
            g_filecfgjson.AddMember(filenameValue.GetString(),filetimeValue,g_filecfgjson.GetAllocator());
            updateResFileInfo();
        }
    }

    if (headSeg)
    {
        delete [] headSeg;
        headSeg =nullptr;
    }
    
    string finish("finish\n");
    send(fd, finish.c_str(), finish.size(),0);
    return true;
}
    
void FileServer::addClient()
{
    struct sockaddr client;
    socklen_t client_len;

    /* new client */
    client_len = sizeof( client );
    int fd = accept(_listenfd, (struct sockaddr *)&client, &client_len );

    // add fd to list of FD
    if( fd != -1 ) {
        FD_SET(fd, &_read_set);
        _fds.push_back(fd);
        _maxfd = std::max(_maxfd,fd);
    }
}

void FileServer::loop()
{
    fd_set copy_set;
    struct timeval timeout, timeout_copy;

    _running = true;

    FD_ZERO(&_read_set);
    FD_SET(_listenfd, &_read_set);
    _maxfd = _listenfd;

    timeout.tv_sec = 0;

    /* 0.016 seconds. Wake up once per frame at 60PFS */
    timeout.tv_usec = 16000;

    while(!_endThread) {

        copy_set = _read_set;
        timeout_copy = timeout;
        int nready = select(_maxfd+1, &copy_set, NULL, NULL, &timeout_copy);

        if( nready == -1 )
        {
            /* error */
            if(errno != EINTR)
                log("Abnormal error in select()\n");
            continue;
        }
        else if( nready == 0 )
        {
            /* timeout. do somethig ? */
        }
        else
        {
            /* new client */
            if(FD_ISSET(_listenfd, &copy_set)) {
                addClient();
                if(--nready <= 0)
                    continue;
            }

            /* data from client */
            std::vector<int> to_remove;
            for(const auto &fd: _fds) {
                if(FD_ISSET(fd,&copy_set)) {
                    if( ! receiveFile(fd) ) {
                        to_remove.push_back(fd);
                    }
                    if(--nready <= 0)
                        break;
                }
            }

            /* remove closed conections */
            for(int fd: to_remove) {
                FD_CLR(fd, &_read_set);
                _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
            }
        }
    }

    // clean up: ignore stdin, stdout and stderr
    for(const auto &fd: _fds )
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        closesocket(fd);
#else
        close(fd);
#endif
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    closesocket(_listenfd);
    WSACleanup();
#else
    close(_listenfd);
#endif
    _running = false;
}


class ConsoleCustomCommand
{
public:
    ConsoleCustomCommand():_fileserver(nullptr)
    {
        cocos2d::Console *_console = Director::getInstance()->getConsole();
        static struct Console::Command commands[] = {
            {"sendrequest","send command to runtime.Args[json format]",std::bind(&ConsoleCustomCommand::onSendCommand, this, std::placeholders::_1, std::placeholders::_2)},
        };
        for (int i=0;i< sizeof(commands)/sizeof(Console::Command);i++) {
            _console->addCommand(commands[i]);
        }
        _console->listenOnTCP(6010);
        
        _fileserver=new FileServer();
        _fileserver->listenOnTCP(6020);
    }
    ~ConsoleCustomCommand()
    {
        Director::getInstance()->getConsole()->stop();
        _fileserver->stop();
        if (_fileserver) {
            delete _fileserver;
            _fileserver = nullptr;
        }
    }
    
    void onSendCommand(int fd, const std::string &args)
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
                if (dArgParse.HasMember("seq")) {
                    dReplyParse.AddMember("seq",dArgParse["seq"],dReplyParse.GetAllocator());
                }
                
                if(strcmp(strcmd.c_str(),"start-logic")==0)
                {
                    char szDebugArg[1024]={0};
                    sprintf(szDebugArg, "require('debugger')(%s,'%s')",dArgParse["debugcfg"].GetString(),g_resourcePath.c_str());
                    startScript(szDebugArg);
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());

                }else if(strcmp(strcmd.c_str(),"reload")==0)
                {
                    if (dArgParse.HasMember("modulefiles"))
                    {
                        rapidjson::Value bodyvalue(rapidjson::kObjectType);
                        const rapidjson::Value& objectfiles = dArgParse["modulefiles"];
                        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
                        {
                            if (!reloadScript(objectfiles[i].GetString())) {
                                bodyvalue.AddMember(objectfiles[i].GetString(),1,dReplyParse.GetAllocator());
                            }
                        }
                        if (0 == objectfiles.Size())
                        {
                            reloadScript("");
                        }
                        
                        dReplyParse.AddMember("body",bodyvalue,dReplyParse.GetAllocator());
                    }
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
                }else if(strcmp(strcmd.c_str(),"getversion")==0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    bodyvalue.AddMember("version",getRuntimeVersion(),dReplyParse.GetAllocator());
                    dReplyParse.AddMember("body",bodyvalue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
                }else if(strcmp(strcmd.c_str(),"getfileinfo")==0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    for (auto it=g_filecfgjson.MemberonBegin();it!=g_filecfgjson.MemberonEnd();++it)
                    {
                        bodyvalue.AddMember(it->name.GetString(),it->value.GetString(),dReplyParse.GetAllocator());
                    }
                    dReplyParse.AddMember("body",bodyvalue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
                    
                }else if(strcmp(strcmd.c_str(),"getIP")==0)
                {
                    rapidjson::Value bodyvalue(rapidjson::kObjectType);
                    rapidjson::Value IPValue(rapidjson::kStringType);
                    IPValue.SetString(getIPAddress().c_str(),dReplyParse.GetAllocator());
                    bodyvalue.AddMember("IP",IPValue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("body",bodyvalue,dReplyParse.GetAllocator());
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());

                }else if(strcmp(strcmd.c_str(),"updatefileinfo")==0)
                {
                    if(updateResFileInfo())
                    {
                        dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());
                    }else
                    {
                        dReplyParse.AddMember("code",1,dReplyParse.GetAllocator());
                    }
                    
                }else if(strcmp(strcmd.c_str(),"remove")==0)
                {
                    if (dArgParse.HasMember("files"))
                    {
                        rapidjson::Value bodyvalue(rapidjson::kObjectType);
                        const rapidjson::Value& objectfiles = dArgParse["files"];
                        for (rapidjson::SizeType i = 0; i < objectfiles.Size(); i++)
                        {
                            string filename(g_resourcePath);
                            filename.append("/");
                            filename.append(objectfiles[i].GetString());
                            if (FileUtils::getInstance()->isFileExist(filename)) 
                            {
                                if(remove(filename.c_str())==0)
                                {
                                    if (g_filecfgjson.HasMember(objectfiles[i].GetString())) {
                                        g_filecfgjson.RemoveMember(objectfiles[i].GetString());
                                    }
                                }	
                                else
                                {
                                    bodyvalue.AddMember(objectfiles[i].GetString(),2,dReplyParse.GetAllocator());
                                }
                            }else
                            {
                                bodyvalue.AddMember(objectfiles[i].GetString(),1,dReplyParse.GetAllocator());
                            }
                            
                        }
                        dReplyParse.AddMember("body",bodyvalue,dReplyParse.GetAllocator());
                        updateResFileInfo();
                    }
                    dReplyParse.AddMember("code",0,dReplyParse.GetAllocator());

                }else if(strcmp(strcmd.c_str(),"shutdownapp")==0)
                {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
                    extern void shutDownApp();
                    shutDownApp();
#else
                    exit(0);
#endif	
                }
                
                rapidjson::StringBuffer buffer;
                rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
                dReplyParse.Accept(writer);
                const char* str = buffer.GetString();
                char msgSize[64]={0x1,0};
                sprintf(msgSize+1,"%d:",strlen(str));
                string replymsg(msgSize);
                replymsg.append(str);
                send(fd,replymsg.c_str(),replymsg.size(),0);
            }
        });
    }
private:
    FileServer* _fileserver;
};

bool startRuntime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#ifndef _DEBUG
    return false;
#endif
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef NDEBUG
    return false;
#endif
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#ifndef COCOS2D_DEBUG
    return false;
#endif
#endif

    vector<string> searchPathArray;
    searchPathArray=FileUtils::getInstance()->getSearchPaths();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    if (g_resourcePath.empty())
    {
        extern std::string getCurAppPath();
        string resourcePath = getCurAppPath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        resourcePath.append("/../../");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        resourcePath.append("/../../../");
#endif
        resourcePath =replaceAll(resourcePath,"\\","/");
        g_resourcePath = resourcePath;
    }

#else
    g_resourcePath = FileUtils::getInstance()->getWritablePath();
    
#endif
   
    g_resourcePath=replaceAll(g_resourcePath,"\\","/");
    searchPathArray.insert(searchPathArray.begin(),g_resourcePath);
    FileUtils::getInstance()->setSearchPaths(searchPathArray);
    static ConsoleCustomCommand s_customCommand;
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    luaopen_debugger(engine->getLuaStack()->getLuaState());
    
    readResFileFinfo();
    auto scene = Scene::create();
    auto layer = new ConnectWaitLayer();
    layer->autorelease();
    auto director = Director::getInstance();
    scene->addChild(layer);
    director->runWithScene(scene);
    return true;
}


// SimulatorConfig
SimulatorConfig *SimulatorConfig::s_sharedInstance = NULL;
SimulatorConfig *SimulatorConfig::getInstance(void)
{
    if (!s_sharedInstance)
    {
        s_sharedInstance = new SimulatorConfig();
    }
    return s_sharedInstance;
}

SimulatorConfig::SimulatorConfig(void)
{
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 3Gs (480x320)", 480, 320));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 4 (960x640)", 960, 640));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPhone 5 (1136x640)", 1136, 640));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPad (1024x768)", 1024, 768));
    m_screenSizeArray.push_back(SimulatorScreenSize("iPad Retina (2048x1536)", 2048, 1536));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (800x480)", 800, 480));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (854x480)", 854, 480));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (960x540)", 960, 540));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (1024x600)", 1024, 600));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (1280x720)", 1280, 720));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (1280x800)", 1280, 800));
    m_screenSizeArray.push_back(SimulatorScreenSize("Android (1920x1080)", 1920, 1080));
}

int SimulatorConfig::getScreenSizeCount(void)
{
    return (int)m_screenSizeArray.size();
}

const SimulatorScreenSize SimulatorConfig::getScreenSize(int index)
{
    return m_screenSizeArray.at(index);
}