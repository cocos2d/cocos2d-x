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

#include <stdio.h>
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

NS_CC_BEGIN


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
    OutputDebugStringA("\n");

    WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), buf, sizeof(buf), NULL, FALSE);
    printf("%s\n", buf);

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
, _userCommands(nullptr)
, _maxUserCommands(0)
, _sendDebugStrings(false)
{
    // VS2012 doesn't support initializer list, so we create a new array and assign its elements to '_command'.
	Command commands[] = {     
        { "config", std::bind(&Console::commandConfig, this, std::placeholders::_1, std::placeholders::_2) },
        { "debug msg on", [&](int fd, const char* command) {
            _sendDebugStrings = true;
        } },
        { "debug msg off", [&](int fd, const char* command) {
            _sendDebugStrings = false;
        } },
        { "exit", std::bind(&Console::commandExit, this, std::placeholders::_1, std::placeholders::_2) },
        { "fileutils dump", std::bind(&Console::commandFileUtilsDump, this, std::placeholders::_1, std::placeholders::_2) },
        { "fps on", [](int fd, const char* command) {
            Director *dir = Director::getInstance();
            Scheduler *sched = dir->getScheduler();
            sched->performFunctionInCocosThread( std::bind(&Director::setDisplayStats, dir, true));
        } },
        { "fps off", [](int fd, const char* command) {
            Director *dir = Director::getInstance();
            Scheduler *sched = dir->getScheduler();
            sched->performFunctionInCocosThread( std::bind(&Director::setDisplayStats, dir, false));
        } },
        { "help", std::bind(&Console::commandHelp, this, std::placeholders::_1, std::placeholders::_2) },
        { "scene graph", std::bind(&Console::commandSceneGraph, this, std::placeholders::_1, std::placeholders::_2) },
        { "textures", std::bind(&Console::commandTextures, this, std::placeholders::_1, std::placeholders::_2) },
    };

    _maxCommands = sizeof(commands)/sizeof(commands[0]);
	for (int i = 0; i < _maxCommands; ++i)
	{
		_commands[i] = commands[i];
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

void Console::setUserCommands(Command *commands, int numberOfCommands)
{
    _userCommands = commands;
    _maxUserCommands = numberOfCommands;
}


//
// commands
//

void Console::commandHelp(int fd, const char* command)
{
    const char help[] = "\nAvailable commands:\n";
    write(fd, help, sizeof(help));
    for(int i=0; i<_maxCommands; ++i) {
        write(fd,"\t",1);
        write(fd, _commands[i].name, strlen(_commands[i].name));
        write(fd,"\n",1);
    }

    // User commands
    for(int i=0; i<_maxUserCommands; ++i) {
        write(fd,"\t",1);
        write(fd, _userCommands[i].name, strlen(_userCommands[i].name));
        write(fd,"\n",1);
    }

}

void Console::commandExit(int fd, const char *command)
{
    FD_CLR(fd, &_read_set);
    _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
    close(fd);
}

void Console::commandSceneGraph(int fd, const char *command)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&printSceneGraphBoot, fd) );
}

void Console::commandFileUtilsDump(int fd, const char *command)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&printFileUtils, fd) );
}

void Console::commandConfig(int fd, const char *command)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [&](){
        mydprintf(fd, "%s", Configuration::getInstance()->getInfo().c_str());
    }
                                        );
}

void Console::commandTextures(int fd, const char *command)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [&](){
        mydprintf(fd, "%s", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    }
                                        );
}


bool Console::parseCommand(int fd)
{
    auto r = readline(fd);
    if(r < 1)
        return false;

    bool found=false;
    for(int i=0; i < _maxCommands; ++i) {
        if( strncmp(_buffer, _commands[i].name,strlen(_commands[i].name)) == 0 ) {
            // XXX TODO FIXME
            // Ideally this loop should execute the function in the cocos2d according to a variable
            // But clang crashes in runtime when doing that (bug in clang, not in the code).
            // So, unfortunately, the only way to fix it was to move that logic to the callback itself
            _commands[i].callback(fd, _buffer);
            found = true;
            break;
        }
    }

    // user commands
    for(int i=0; i < _maxUserCommands && !found; ++i) {
        if( strncmp(_buffer, _userCommands[i].name,strlen(_userCommands[i].name)) == 0 ) {
            _userCommands[i].callback(fd, _buffer);
            found = true;
            break;
        }
    }

    if(!found && strcmp(_buffer, "\r\n")!=0) {
        const char err[] = "Unknown command. Type 'help' for options\n";
        write(fd, err, sizeof(err));
    }

    sendPrompt(fd);

    return true;
}

//
// Helpers
//
void Console::sendPrompt(int fd)
{
    const char prompt[] = "\n> ";
    write(fd, prompt, sizeof(prompt));
}

ssize_t Console::readline(int fd)
{
    int maxlen = sizeof(_buffer)-1;
    ssize_t n, rc;
    char c, *ptr;

    ptr = _buffer;

    for( n=1; n<maxlen; n++ ) {
        if( (rc = read(fd, &c, 1 )) ==1 ) {
            *ptr++ = c;
            if( c=='\n' )
                break;
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
    timeout.tv_usec = 016000;

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
