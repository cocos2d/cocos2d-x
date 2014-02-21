/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#include "CCConsole.h"

#include <thread>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

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

#include "CCDirector.h"
#include "CCScheduler.h"
#include "CCScene.h"
#include "CCPlatformConfig.h"
#include "platform/CCFileUtils.h"
#include "CCConfiguration.h"
#include "CCTextureCache.h"
#include "CCGLView.h"

NS_CC_BEGIN

//TODO: these general utils should be in a seperate class
//
// Trimming functions were taken from: http://stackoverflow.com/a/217605
//
// trim from start
static std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


// helper free functions

// dprintf() is not defined in Android
// so we add our own 'dpritnf'
static ssize_t mydprintf(int sock, const char *format, ...)
{
    va_list args;
	char buf[16386];

	va_start(args, format);
	vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

	return write(sock, buf, strlen(buf));
}

static void sendPrompt(int fd)
{
    const char prompt[] = "> ";
    write(fd, prompt, sizeof(prompt));
}

static int printSceneGraph(int fd, Node* node, int level)
{
    int total = 1;
    for(int i=0; i<level; ++i)
        write(fd, "-", 1);

    mydprintf(fd, " %s\n", node->getDescription().c_str());

    for(const auto& child: node->getChildren())
        total += printSceneGraph(fd, child, level+1);

    return total;
}

static void printSceneGraphBoot(int fd)
{
    write(fd,"\n",1);
    auto scene = Director::getInstance()->getRunningScene();
    int total = printSceneGraph(fd, scene, 0);
    mydprintf(fd, "Total Nodes: %d\n", total);
    sendPrompt(fd);
}

static void printFileUtils(int fd)
{
    FileUtils* fu = FileUtils::getInstance();

    mydprintf(fd, "\nSearch Paths:\n");
    auto list = fu->getSearchPaths();
    for( const auto &item : list) {
        mydprintf(fd, "%s\n", item.c_str());
    }

    mydprintf(fd, "\nResolution Order:\n");
    list = fu->getSearchResolutionsOrder();
    for( const auto &item : list) {
        mydprintf(fd, "%s\n", item.c_str());
    }

    mydprintf(fd, "\nWriteble Path:\n");
    mydprintf(fd, "%s\n", fu->getWritablePath().c_str());

    mydprintf(fd, "\nFull Path Cache:\n");
    auto cache = fu->getFullPathCache();
    for( const auto &item : cache) {
        mydprintf(fd, "%s -> %s\n", item.first.c_str(), item.second.c_str());
    }
    sendPrompt(fd);
}


#if defined(__MINGW32__)
static const char* inet_ntop(int af, const void* src, char* dst, int cnt)
{
    struct sockaddr_in srcaddr;

    memset(&srcaddr, 0, sizeof(struct sockaddr_in));
    memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));

    srcaddr.sin_family = af;
    if (WSAAddressToString((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0)
    {
        return nullptr;
    }
    return dst;
}
#endif


//
// Free functions to log
//

static void _log(const char *format, va_list args)
{
    char buf[MAX_LOG_LENGTH];

    vsnprintf(buf, MAX_LOG_LENGTH-3, format, args);
    strcat(buf, "\n");

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info",  "%s", buf);

#elif CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32
    WCHAR wszBuf[MAX_LOG_LENGTH] = {0};
    MultiByteToWideChar(CP_UTF8, 0, buf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
    WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), buf, sizeof(buf), NULL, FALSE);
    printf("%s", buf);

#else
    // Linux, Mac, iOS, etc
    fprintf(stdout, "cocos2d: %s", buf);
    fflush(stdout);
#endif

    Director::getInstance()->getConsole()->log(buf);
}

// XXX: Deprecated
void CCLog(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    _log(format, args);
    va_end(args);
}

void log(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    _log(format, args);
    va_end(args);
}

//
// Console code
//

Console::Console()
: _listenfd(-1)
, _running(false)
, _endThread(false)
, _sendDebugStrings(false)
{
    // VS2012 doesn't support initializer list, so we create a new array and assign its elements to '_command'.
	Command commands[] = {     
        { "config", "Print the Configuration object", std::bind(&Console::commandConfig, this, std::placeholders::_1, std::placeholders::_2) },
        { "debugmsg", "Whether or not to forward the debug messages on the console. Args: [on | off]", [&](int fd, const std::string& args) {
            if( args.compare("on")==0 || args.compare("off")==0) {
                _sendDebugStrings = (args.compare("on") == 0);
            } else {
                mydprintf(fd, "Debug message is: %s\n", _sendDebugStrings ? "on" : "off");
            }
        } },
        { "exit", "Close connection to the console", std::bind(&Console::commandExit, this, std::placeholders::_1, std::placeholders::_2) },
        { "fileutils", "Flush or print the FileUtils info. Args: [flush | ] ", std::bind(&Console::commandFileUtils, this, std::placeholders::_1, std::placeholders::_2) },
        { "fps", "Turn on / off the FPS. Args: [on | off] ", [](int fd, const std::string& args) {
            if( args.compare("on")==0 || args.compare("off")==0) {
                bool state = (args.compare("on") == 0);
                Director *dir = Director::getInstance();
                Scheduler *sched = dir->getScheduler();
                sched->performFunctionInCocosThread( std::bind(&Director::setDisplayStats, dir, state));
            } else {
                mydprintf(fd, "FPS is: %s\n", Director::getInstance()->isDisplayStats() ? "on" : "off");
            }
        } },
        { "help", "Print this message", std::bind(&Console::commandHelp, this, std::placeholders::_1, std::placeholders::_2) },
        { "projection", "Change or print the current projection. Args: [2d | 3d]", std::bind(&Console::commandProjection, this, std::placeholders::_1, std::placeholders::_2) },
        { "resolution", "Change or print the window resolution. Args: [width height resolution_policy | ]", std::bind(&Console::commandResolution, this, std::placeholders::_1, std::placeholders::_2) },
        { "scenegraph", "Print the scene graph", std::bind(&Console::commandSceneGraph, this, std::placeholders::_1, std::placeholders::_2) },
        { "texture", "Flush or print the TextureCache info. Args: [flush | ] ", std::bind(&Console::commandTextures, this, std::placeholders::_1, std::placeholders::_2) },
        { "director", "director commands, type -h or [director help] to list supported directives", std::bind(&Console::commandDirector, this, std::placeholders::_1, std::placeholders::_2) },

    };

     ;
	for (int i = 0; i < sizeof(commands)/sizeof(commands[0]); ++i)
	{
		_commands.insert ( std::pair<std::string,Command>(commands[i].name,commands[i]) );
	}
}

Console::~Console()
{
    stop();
}

bool Console::listenOnTCP(int port)
{
    int listenfd, n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;
    char serv[30];

    snprintf(serv, sizeof(serv)-1, "%d", port );

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
        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */

        close(listenfd);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);
    
    if (res == NULL) {
        perror("net_listen:");
        freeaddrinfo(ressave);
        return false;
    }

    listen(listenfd, 50);

    if (res->ai_family == AF_INET) {
        char buf[INET_ADDRSTRLEN] = "";
        struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin_addr, buf, sizeof(buf)) != NULL )
            cocos2d::log("Console: listening on  %s : %d", buf, ntohs(sin->sin_port));
        else
            perror("inet_ntop");
    } else if (res->ai_family == AF_INET6) {
        char buf[INET6_ADDRSTRLEN] = "";
        struct sockaddr_in6 *sin = (struct sockaddr_in6*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin6_addr, buf, sizeof(buf)) != NULL )
            cocos2d::log("Console: listening on  %s : %d", buf, ntohs(sin->sin6_port));
        else
            perror("inet_ntop");
    }


    freeaddrinfo(ressave);

    return listenOnFileDescriptor(listenfd);
}

bool Console::listenOnFileDescriptor(int fd)
{
    if(_running) {
        cocos2d::log("Console already started. 'stop' it before calling 'listen' again");
        return false;
    }

    _listenfd = fd;
    _thread = std::thread( std::bind( &Console::loop, this) );

    return true;
}

void Console::stop()
{
    if( _running ) {
        _endThread = true;
        _thread.join();
    }
}

void Console::addCommand(const Command& cmd)
{
    _commands[cmd.name]=cmd;
}

//
// commands
//

void Console::commandHelp(int fd, const std::string &args)
{
    const char help[] = "\nAvailable commands:\n";
    write(fd, help, sizeof(help));
    for(auto it=_commands.begin();it!=_commands.end();++it)
    {
        auto cmd = it->second;
        mydprintf(fd, "\t%s", cmd.name);
        ssize_t tabs = strlen(cmd.name) / 8;
        tabs = 3 - tabs;
        for(int j=0;j<tabs;j++){
             mydprintf(fd, "\t");
        }
        mydprintf(fd,"%s\n", cmd.help);
    } 
}

void Console::commandExit(int fd, const std::string &args)
{
    FD_CLR(fd, &_read_set);
    _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
    close(fd);
}

void Console::commandSceneGraph(int fd, const std::string &args)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&printSceneGraphBoot, fd) );
}

void Console::commandFileUtils(int fd, const std::string &args)
{
    Scheduler *sched = Director::getInstance()->getScheduler();

    if( args.compare("flush") == 0 )
    {
        FileUtils::getInstance()->purgeCachedEntries();
    }
    else if( args.length()==0)
    {
        sched->performFunctionInCocosThread( std::bind(&printFileUtils, fd) );
    }
    else
    {
        mydprintf(fd, "Unsupported argument: '%s'. Supported arguments: 'flush' or nothing", args.c_str());
    }
}

void Console::commandConfig(int fd, const std::string& args)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [&](){
        mydprintf(fd, "%s", Configuration::getInstance()->getInfo().c_str());
        sendPrompt(fd);
    }
                                        );
}

void Console::commandResolution(int fd, const std::string& args)
{
    if(args.length()==0) {
        auto director = Director::getInstance();
        Size points = director->getWinSize();
        Size pixels = director->getWinSizeInPixels();
        auto glview = director->getOpenGLView();
        Size design = glview->getDesignResolutionSize();
        ResolutionPolicy res = glview->getResolutionPolicy();
        Rect visibleRect = glview->getVisibleRect();

        mydprintf(fd, "Window Size:\n"
                        "\t%d x %d (points)\n"
                        "\t%d x %d (pixels)\n"
                        "\t%d x %d (design resolution)\n"
                        "Resolution Policy: %d\n"
                        "Visible Rect:\n"
                        "\torigin: %d x %d\n"
                        "\tsize: %d x %d\n",
                  (int)points.width, (int)points.height,
                  (int)pixels.width, (int)pixels.height,
                  (int)design.width, (int)design.height,
                  (int)res,
                  (int)visibleRect.origin.x, (int)visibleRect.origin.y,
                  (int)visibleRect.size.width, (int)visibleRect.size.height
                  );

    } else {
        int width, height, policy;

        std::istringstream stream( args );
        stream >> width >> height>> policy;

        Scheduler *sched = Director::getInstance()->getScheduler();
        sched->performFunctionInCocosThread( [&](){
            Director::getInstance()->getOpenGLView()->setDesignResolutionSize(width, height, static_cast<ResolutionPolicy>(policy));
        } );
    }
}

void Console::commandProjection(int fd, const std::string& args)
{
    auto director = Director::getInstance();
    Scheduler *sched = director->getScheduler();

    if(args.length()==0)
    {
        char buf[20];
        auto proj = director->getProjection();
        switch (proj) {
            case cocos2d::Director::Projection::_2D:
                sprintf(buf,"2d");
                break;
            case cocos2d::Director::Projection::_3D:
                sprintf(buf,"3d");
                break;
            case cocos2d::Director::Projection::CUSTOM:
                sprintf(buf,"custom");
                break;

            default:
                sprintf(buf,"unknown");
                break;
        }
        mydprintf(fd, "Current projection: %s\n", buf);
    }
    else if( args.compare("2d") == 0)
    {
        sched->performFunctionInCocosThread( [&](){
            director->setProjection(Director::Projection::_2D);
        } );
    }
    else if( args.compare("3d") == 0)
    {
        sched->performFunctionInCocosThread( [&](){
            director->setProjection(Director::Projection::_3D);
        } );
    }
    else
    {
        mydprintf(fd, "Unsupported argument: '%s'. Supported arguments: '2d' or '3d'\n", args.c_str());
    }
}

void Console::commandTextures(int fd, const std::string& args)
{
    Scheduler *sched = Director::getInstance()->getScheduler();

    if( args.compare("flush")== 0)
    {
        sched->performFunctionInCocosThread( [&](){
            Director::getInstance()->getTextureCache()->removeAllTextures();
        }
                                            );
    }
    else if(args.length()==0)
    {
        sched->performFunctionInCocosThread( [&](){
            mydprintf(fd, "%s", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
            sendPrompt(fd);
        }
                                            );
    }
    else
    {
        mydprintf(fd, "Unsupported argument: '%s'. Supported arguments: 'flush' or nothing", args.c_str());
    }
}


void Console::commandDirector(int fd, const std::string& args)
{
     auto director = Director::getInstance();
    if(args =="help" || args == "-h")
    {
        const char help[] = "available director directives:\n"
                            "\tpause, pause all scheduled timers, the draw rate will be 4 FPS to reduce CPU consumption\n"
                            "\tresume, resume all scheduled timers\n"
                            "\tstop, Stops the animation. Nothing will be drawn.\n"
                            "\tstart, Restart the animation again, Call this function only if [director stop] was called earlier\n";
         write(fd, help, sizeof(help) - 1);
    }
    else if(args == "pause")
    {
        Scheduler *sched = director->getScheduler();
            sched->performFunctionInCocosThread( [&](){
            Director::getInstance()->pause();
        }
                                        );

    }
    else if(args == "resume")
    {
        director->resume();
    }
    else if(args == "stop")
    {
        Scheduler *sched = director->getScheduler();
        sched->performFunctionInCocosThread( [&](){
            Director::getInstance()->stopAnimation();
        }
                                        );
    }
    else if(args == "start")
    {
        director->startAnimation();
    }

}

bool Console::parseCommand(int fd)
{
    char buf[512];
    auto r = readline(fd, buf, sizeof(buf)-1);
    if(r < 1)
    {
        const char err[] = "Unknown error!\n";
        sendPrompt(fd);
        write(fd, err, sizeof(err));
        return false;
    }
    std::string cmdLine;

    std::vector<std::string> args;
    cmdLine = std::string(buf);
   
    args = split(cmdLine, ' ');
    if(args.empty())
    {
        const char err[] = "Unknown command. Type 'help' for options\n";
        write(fd, err, sizeof(err));
        sendPrompt(fd);
        return false;
    }

    auto it = _commands.find(trim(args[0]));
    if(it != _commands.end())
    {
        std::string args2;
        for(int i = 1; i < args.size(); ++i)
        {   
            if(i > 1)
            {
                args2 += ' ';
            }
            args2 += trim(args[i]);
            
        }
        auto cmd = it->second;
        cmd.callback(fd, args2);
    }else if(strcmp(buf, "\r\n") != 0) {
        const char err[] = "Unknown command. Type 'help' for options\n";
        write(fd, err, sizeof(err));
    }

    sendPrompt(fd);

    return true;
}

//
// Helpers
//


ssize_t Console::readline(int fd, char* ptr, int maxlen)
{
    ssize_t n, rc;
    char c;

    for( n=1; n<maxlen-1; n++ ) {
        if( (rc = read(fd, &c, 1 )) ==1 ) {
            *ptr++ = c;
            if(c == '\n') {
                break;
            }
        } else if( rc == 0 ) {
            return 0;
        } else if( errno == EINTR ) {
            continue;
        } else {
            return -1;
        }
    }

    *ptr = 0;
    return n;
}

void Console::addClient()
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

        sendPrompt(fd);
    }
}

void Console::log(const char* buf)
{
    if( _sendDebugStrings ) {
        _DebugStringsMutex.lock();
        _DebugStrings.push_back(buf);
        _DebugStringsMutex.unlock();
    }
}

//
// Main Loop
//

void Console::loop()
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
                    if( ! parseCommand(fd) ) {
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

        /* Any message for the remote console ? send it! */
        if( !_DebugStrings.empty() ) {
            _DebugStringsMutex.lock();
            for(const auto &str : _DebugStrings) {
                for(const auto &fd : _fds) {
                    write(fd, str.c_str(), str.length());
                }
            }
            _DebugStrings.clear();
            _DebugStringsMutex.unlock();
        }
    }

    // clean up: ignore stdin, stdout and stderr
    for(const auto &fd: _fds )
        close(fd);
    close(_listenfd);

    _running = false;
}

NS_CC_END
