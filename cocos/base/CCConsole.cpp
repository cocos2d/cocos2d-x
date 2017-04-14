/****************************************************************************
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#include "base/CCConsole.h"

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
#include <Winsock2.h>
#if defined(__MINGW32__)
#include "platform/win32/inet_pton_mingw.h"
#endif
#define bzero(a, b) memset(a, 0, b);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#include "platform/winrt/inet_ntop_winrt.h"
#include "platform/winrt/inet_pton_winrt.h"
#include "platform/winrt/CCWinRTUtils.h"
#endif
#else
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#endif

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "platform/CCPlatformConfig.h"
#include "base/CCConfiguration.h"
#include "2d/CCScene.h"
#include "platform/CCFileUtils.h"
#include "renderer/CCTextureCache.h"
#include "base/base64.h"
#include "base/ccUtils.h"
#include "base/allocator/CCAllocatorDiagnostics.h"
NS_CC_BEGIN

extern const char* cocos2dVersion(void);

#define PROMPT  "> "

static const size_t SEND_BUFSIZ = 512;

/** private functions */
namespace {
#if defined(__MINGW32__)
    // inet
    const char* inet_ntop(int af, const void* src, char* dst, int cnt)
    {
        struct sockaddr_in srcaddr;
        
        memset(&srcaddr, 0, sizeof(struct sockaddr_in));
        memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));
        
        srcaddr.sin_family = af;
        if (WSAAddressToStringA((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD) &cnt) != 0)
        {
            return nullptr;
        }
        return dst;
    }
#endif
    
    //
    // Free functions to log
    //
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    void SendLogToWindow(const char *log)
    {
        static const int CCLOG_STRING_TAG = 1;
        // Send data as a message
        COPYDATASTRUCT myCDS;
        myCDS.dwData = CCLOG_STRING_TAG;
        myCDS.cbData = (DWORD)strlen(log) + 1;
        myCDS.lpData = (PVOID)log;
        if (Director::getInstance()->getOpenGLView())
        {
            HWND hwnd = Director::getInstance()->getOpenGLView()->getWin32Window();
            SendMessage(hwnd,
                        WM_COPYDATA,
                        (WPARAM)(HWND)hwnd,
                        (LPARAM)(LPVOID)&myCDS);
        }
    }
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
    void SendLogToWindow(const char *log)
    {
    }
#endif
    
    void _log(const char *format, va_list args)
    {
        int bufferSize = MAX_LOG_LENGTH;
        char* buf = nullptr;
        
        do
        {
            buf = new (std::nothrow) char[bufferSize];
            if (buf == nullptr)
                return; // not enough memory
            
            int ret = vsnprintf(buf, bufferSize - 3, format, args);
            if (ret < 0)
            {
                bufferSize *= 2;
                
                delete [] buf;
            }
            else
                break;
            
        } while (true);
        
        strcat(buf, "\n");
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info", "%s", buf);
        
#elif CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
        
        int pos = 0;
        int len = strlen(buf);
        char tempBuf[MAX_LOG_LENGTH + 1] = { 0 };
        WCHAR wszBuf[MAX_LOG_LENGTH + 1] = { 0 };
        
        do
        {
            std::copy(buf + pos, buf + pos + MAX_LOG_LENGTH, tempBuf);
            
            tempBuf[MAX_LOG_LENGTH] = 0;
            
            MultiByteToWideChar(CP_UTF8, 0, tempBuf, -1, wszBuf, sizeof(wszBuf));
            OutputDebugStringW(wszBuf);
            WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, tempBuf, sizeof(tempBuf), nullptr, FALSE);
            printf("%s", tempBuf);
            
            pos += MAX_LOG_LENGTH;
            
        } while (pos < len);
        SendLogToWindow(buf);
        fflush(stdout);
#else
        // Linux, Mac, iOS, etc
        fprintf(stdout, "%s", buf);
        fflush(stdout);
#endif
        
        Director::getInstance()->getConsole()->log(buf);
        delete [] buf;
    }
}

// FIXME: Deprecated
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
//  Utility code
//

std::string Console::Utility::_prompt(PROMPT);

//TODO: these general utils should be in a separate class
//
// Trimming functions were taken from: http://stackoverflow.com/a/217605
//
// trim from start

std::string& Console::Utility::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string& Console::Utility::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string& Console::Utility::trim(std::string& s) {
    return Console::Utility::ltrim(Console::Utility::rtrim(s));
}

std::vector<std::string>& Console::Utility::split(const std::string& s, char delim, std::vector<std::string>& elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> Console::Utility::split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    Console::Utility::split(s, delim, elems);
    return elems;
}

//isFloat taken from http://stackoverflow.com/questions/447206/c-isfloat-function
bool Console::Utility::isFloat(const std::string& myString) {
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

ssize_t Console::Utility::sendToConsole(int fd, const void* buffer, size_t length, int flags)
{
    if (_prompt.length() == length) {
        if (strncmp(_prompt.c_str(), static_cast<const char*>(buffer), length) == 0) {
            fprintf(stderr,"bad parameter error: a buffer is the prompt string.\n");
            return 0;
        }
    }
    
    const char* buf = static_cast<const char*>(buffer);
    ssize_t retLen = 0;
    for (size_t i = 0; i < length; ) {
        size_t len = length - i;
        if (SEND_BUFSIZ < len) len = SEND_BUFSIZ;
        retLen += send(fd, buf + i, len, flags);
        i += len;
    }
    return retLen;
}

// dprintf() is not defined in Android
// so we add our own 'dpritnf'
ssize_t Console::Utility::mydprintf(int sock, const char *format, ...)
{
    va_list args;
    char buf[16386];
    
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    return sendToConsole(sock, buf, strlen(buf));
}

void Console::Utility::sendPrompt(int fd)
{
    const char* prompt = _prompt.c_str();
    send(fd, prompt, strlen(prompt), 0);
}

void Console::Utility::setPrompt(const std::string &prompt)
{
    _prompt = prompt;
}

const std::string& Console::Utility::getPrompt()
{
    return _prompt;
}

//
// Command code
//

void Console::Command::addCallback(const Callback& callback_)
{
    callback = callback_;
}

void Console::Command::addSubCommand(const Command& subCmd)
{
    subCommands[subCmd.name] = subCmd;
}

const Console::Command* Console::Command::getSubCommand(const std::string& subCmdName) const
{
    auto it = subCommands.find(subCmdName);
    if(it != subCommands.end()) {
        auto& subCmd = it->second;
        return &subCmd;
    }
    return nullptr;
}

void Console::Command::delSubCommand(const std::string& subCmdName)
{
    auto it = subCommands.find(subCmdName);
    if(it != subCommands.end()) {
        subCommands.erase(it);
    }
}

void Console::Command::commandHelp(int fd, const std::string& /*args*/)
{
    if (! help.empty()) {
        Console::Utility::mydprintf(fd, "%s\n", help.c_str());
    }
    
    if (! subCommands.empty()) {
        sendHelp(fd, subCommands, "");
    }
}

void Console::Command::commandGeneric(int fd, const std::string& args)
{
    // The first argument (including the empty)
    std::string key(args);
    auto pos = args.find(" ");
    if ((pos != std::string::npos) && (0 < pos)) {
        key = args.substr(0, pos);
    }
    
    // help
    if (key == "help" || key == "-h") {
        commandHelp(fd, args);
        return;
    }
    
    // find sub command
    auto it = subCommands.find(key);
    if (it != subCommands.end()) {
        auto subCmd = it->second;
        if (subCmd.callback) {
            subCmd.callback(fd, args);
        }
        return;
    }
    
    // can not find
    if (callback) {
        callback(fd, args);
    }
}

//
// Console code
//

Console::Console()
: _listenfd(-1)
, _running(false)
, _endThread(false)
, _isIpv6Server(false)
, _sendDebugStrings(false)
, _bindAddress("")
{
    createCommandAllocator();
    createCommandConfig();
    createCommandDebugMsg();
    createCommandDirector();
    createCommandExit();
    createCommandFileUtils();
    createCommandFps();
    createCommandHelp();
    createCommandProjection();
    createCommandResolution();
    createCommandSceneGraph();
    createCommandTexture();
    createCommandTouch();
    createCommandUpload();
    createCommandVersion();
}

Console::~Console()
{
    stop();
}

bool Console::listenOnTCP(int port)
{
    int listenfd = -1, n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;
    char serv[30];

    snprintf(serv, sizeof(serv)-1, "%d", port );

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    WSADATA wsaData;
    n = WSAStartup(MAKEWORD(2, 2),&wsaData);
#endif

    if ( (n = getaddrinfo(nullptr, serv, &hints, &res)) != 0) {
        fprintf(stderr,"net_listen error for %s: %s", serv, gai_strerror(n));
        return false;
    }

    ressave = res;

    do {
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenfd < 0)
            continue;       /* error, try next one */

        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));

        // bind address
        if (!_bindAddress.empty())
        {
            if (res->ai_family == AF_INET)
            {
                struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
                inet_pton(res->ai_family, _bindAddress.c_str(), (void*)&sin->sin_addr);
            }
            else if (res->ai_family == AF_INET6)
            {
                struct sockaddr_in6 *sin = (struct sockaddr_in6*) res->ai_addr;
                inet_pton(res->ai_family, _bindAddress.c_str(), (void*)&sin->sin6_addr);
            }
        }

        if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */

/* bind error, close and try next one */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        closesocket(listenfd);
#else
        close(listenfd);
#endif
    } while ( (res = res->ai_next) != nullptr);
    
    if (res == nullptr) {
        perror("net_listen:");
        freeaddrinfo(ressave);
        return false;
    }

    listen(listenfd, 50);

    if (res->ai_family == AF_INET) {
        _isIpv6Server = false;
        char buf[INET_ADDRSTRLEN] = {0};
        struct sockaddr_in *sin = (struct sockaddr_in*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin_addr, buf, sizeof(buf)) != nullptr )
            cocos2d::log("Console: IPV4 server is listening on %s:%d", buf, ntohs(sin->sin_port));
        else
            perror("inet_ntop");
    } else if (res->ai_family == AF_INET6) {
        _isIpv6Server = true;
        char buf[INET6_ADDRSTRLEN] = {0};
        struct sockaddr_in6 *sin = (struct sockaddr_in6*) res->ai_addr;
        if( inet_ntop(res->ai_family, &sin->sin6_addr, buf, sizeof(buf)) != nullptr )
            cocos2d::log("Console: IPV6 server is listening on [%s]:%d", buf, ntohs(sin->sin6_port));
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
        if (_thread.joinable())
        {
            _thread.join();
        }
    }
}

void Console::addCommand(const Command& cmd)
{
    _commands[cmd.name] = cmd;
}

void Console::addSubCommand(const std::string& cmdName, const Command& subCmd)
{
    auto it = _commands.find(cmdName);
    if(it != _commands.end()) {
        auto& cmd = it->second;
        addSubCommand(cmd, subCmd);
    }
}

void Console::addSubCommand(Command& cmd, const Command& subCmd)
{
    cmd.subCommands[subCmd.name] = subCmd;
}

const Console::Command* Console::getCommand(const std::string& cmdName)
{
    auto it = _commands.find(cmdName);
    if(it != _commands.end()) {
        auto& cmd = it->second;
        return &cmd;
    }
    return nullptr;
}

const Console::Command* Console::getSubCommand(const std::string& cmdName, const std::string& subCmdName)
{
    auto it = _commands.find(cmdName);
    if(it != _commands.end()) {
        auto& cmd = it->second;
        return getSubCommand(cmd, subCmdName);
    }
    return nullptr;
}

const Console::Command* Console::getSubCommand(const Command& cmd, const std::string& subCmdName)
{
    return cmd.getSubCommand(subCmdName);
}

void Console::delCommand(const std::string& cmdName)
{
    auto it = _commands.find(cmdName);
    if(it != _commands.end()) {
        _commands.erase(it);
    }
}

void Console::delSubCommand(const std::string& cmdName, const std::string& subCmdName)
{
    auto it = _commands.find(cmdName);
    if(it != _commands.end()) {
        auto& cmd = it->second;
        delSubCommand(cmd, subCmdName);
    }
}

void Console::delSubCommand(Command& cmd, const std::string& subCmdName)
{
    cmd.delSubCommand(subCmdName);
}

void Console::log(const char* buf)
{
    if( _sendDebugStrings ) {
        _DebugStringsMutex.lock();
        _DebugStrings.push_back(buf);
        _DebugStringsMutex.unlock();
    }
}

void Console::setBindAddress(const std::string &address)
{
    _bindAddress = address;
}

bool Console::isIpv6Server() const
{
    return _isIpv6Server;
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
        
        int nready = select(_maxfd+1, &copy_set, nullptr, nullptr, &timeout_copy);
        
        if( nready == -1 )
        {
            /* error */
            if(errno != EINTR)
                cocos2d::log("Abnormal error in select()\n");
            continue;
        }
        else if( nready == 0 )
        {
            /* timeout. do something ? */
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
                if(FD_ISSET(fd,&copy_set))
                {
                    //fix Bug #4302 Test case ConsoleTest--ConsoleUploadFile crashed on Linux
                    //On linux, if you send data to a closed socket, the sending process will
                    //receive a SIGPIPE, which will cause linux system shutdown the sending process.
                    //Add this ioctl code to check if the socket has been closed by peer.
                    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
                    u_long n = 0;
                    ioctlsocket(fd, FIONREAD, &n);
#else
                    int n = 0;
                    ioctl(fd, FIONREAD, &n);
#endif
                    if(n == 0)
                    {
                        //no data received, or fd is closed
                        continue;
                    }
                    
                    if( ! parseCommand(fd) )
                    {
                        to_remove.push_back(fd);
                    }
                    if(--nready <= 0)
                        break;
                }
            }
            
            /* remove closed connections */
            for(int fd: to_remove) {
                FD_CLR(fd, &_read_set);
                _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
            }
        }
        
        /* Any message for the remote console ? send it! */
        if( !_DebugStrings.empty() ) {
            if (_DebugStringsMutex.try_lock())
            {
                for (const auto &str : _DebugStrings) {
                    for (auto fd : _fds) {
                        Console::Utility::sendToConsole(fd, str.c_str(), str.length());
                    }
                }
                _DebugStrings.clear();
                _DebugStringsMutex.unlock();
            }
        }
    }
    
    // clean up: ignore stdin, stdout and stderr
    for(const auto &fd: _fds )
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        closesocket(fd);
#else
        close(fd);
#endif
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    closesocket(_listenfd);
    WSACleanup();
#else
    close(_listenfd);
#endif
    _running = false;
}

//
// Helpers
//

ssize_t Console::readline(int fd, char* ptr, size_t maxlen)
{
    size_t n, rc;
    char c;
    
    for( n = 0; n < maxlen - 1; n++ ) {
        if( (rc = recv(fd, &c, 1, 0)) ==1 ) {
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

ssize_t Console::readBytes(int fd, char* buffer, size_t maxlen, bool* more)
{
    size_t n, rc;
    char c, *ptr = buffer;
    *more = false;
    for( n = 0; n < maxlen; n++ ) {
        if( (rc = recv(fd, &c, 1, 0)) ==1 ) {
            *ptr++ = c;
            if(c == '\n') {
                return n;
            }
        } else if( rc == 0 ) {
            return 0;
        } else if( errno == EINTR ) {
            continue;
        } else {
            return -1;
        }
    }
    *more = true;
    return n;
}

bool Console::parseCommand(int fd)
{
    char buf[512];
    bool more_data;
    auto h = readBytes(fd, buf, 6, &more_data);
    if( h < 0)
    {
        return false;
    }
    if(strncmp(buf, "upload", 6) == 0)
    {
        char c = '\0';
        recv(fd, &c, 1, 0);
        if(c == ' ')
        {
            commandUpload(fd);
            Console::Utility::sendPrompt(fd);
            return true;
        }
        else
        {
            const char err[] = "upload: invalid args! Type 'help' for options\n";
            Console::Utility::sendToConsole(fd, err, strlen(err));
            Console::Utility::sendPrompt(fd);
            return true;
            
        }
    }
    if(!more_data)
    {
        buf[h] = 0;
    }
    else
    {
        char *pb = buf + 6;
        auto r = readline(fd, pb, sizeof(buf)-6);
        if(r < 0)
        {
            const char err[] = "Unknown error!\n";
            Console::Utility::sendPrompt(fd);
            Console::Utility::sendToConsole(fd, err, strlen(err));
            return false;
        }
    }
    std::string cmdLine;
    
    std::vector<std::string> args;
    cmdLine = std::string(buf);
    
    args = Console::Utility::split(cmdLine, ' ');
    if(args.empty())
    {
        const char err[] = "Unknown command. Type 'help' for options\n";
        Console::Utility::sendToConsole(fd, err, strlen(err));
        Console::Utility::sendPrompt(fd);
        return true;
    }
    
    auto it = _commands.find(Console::Utility::trim(args[0]));
    if(it != _commands.end())
    {
        std::string args2;
        for(size_t i = 1; i < args.size(); ++i)
        {
            if(i > 1)
            {
                args2 += ' ';
            }
            args2 += Console::Utility::trim(args[i]);
            
        }
        auto cmd = it->second;
        cmd.commandGeneric(fd, args2);
    }else if(strcmp(buf, "\r\n") != 0) {
        const char err[] = "Unknown command. Type 'help' for options\n";
        Console::Utility::sendToConsole(fd, err, strlen(err));
    }
    Console::Utility::sendPrompt(fd);
    
    return true;
}

void Console::addClient()
{
    struct sockaddr_in6 ipv6Addr;
    struct sockaddr_in ipv4Addr;
    struct sockaddr* addr = _isIpv6Server ? (struct sockaddr*)&ipv6Addr : (struct sockaddr*)&ipv4Addr;
    socklen_t addrLen = _isIpv6Server ? sizeof(ipv6Addr) : sizeof(ipv4Addr);
    
    /* new client */
    int fd = accept(_listenfd, addr, &addrLen);
    
    // add fd to list of FD
    if( fd != -1 ) {
        FD_SET(fd, &_read_set);
        _fds.push_back(fd);
        _maxfd = std::max(_maxfd,fd);
        
        Console::Utility::sendPrompt(fd);
        
        /**
         * A SIGPIPE is sent to a process if it tried to write to socket that had been shutdown for
         * writing or isn't connected (anymore) on iOS.
         *
         * The default behaviour for this signal is to end the process.So we make the process ignore SIGPIPE.
         */
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        int set = 1;
        setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, (void*)&set, sizeof(int));
#endif
    }
}

//
// create commands
//

void Console::createCommandAllocator()
{
    addCommand({"allocator", "Display allocator diagnostics for all allocators. Args: [-h | help | ]",
        CC_CALLBACK_2(Console::commandAllocator, this)});
}

void Console::createCommandConfig()
{
    addCommand({"config", "Print the Configuration object. Args: [-h | help | ]",
        CC_CALLBACK_2(Console::commandConfig, this)});
}

void Console::createCommandDebugMsg()
{
    addCommand({"debugmsg", "Whether or not to forward the debug messages on the console. Args: [-h | help | on | off | ]",
        CC_CALLBACK_2(Console::commandDebugMsg, this)});
    addSubCommand("debugmsg", {"on", "enable debug logging", CC_CALLBACK_2(Console::commandDebugMsgSubCommandOnOff, this)});
    addSubCommand("debugmsg", {"off", "disable debug logging", CC_CALLBACK_2(Console::commandDebugMsgSubCommandOnOff, this)});
}

void Console::createCommandDirector()
{
    addCommand({"director", "director commands, type -h or [director help] to list supported directives"});
    addSubCommand("director", {"pause",  "pause all scheduled timers, the draw rate will be 4 FPS to reduce CPU consumption",
        CC_CALLBACK_2(Console::commandDirectorSubCommandPause, this)});
    addSubCommand("director", {"resume", "resume all scheduled timers",
        CC_CALLBACK_2(Console::commandDirectorSubCommandResume, this)});
    addSubCommand("director", {"stop",   "Stops the animation. Nothing will be drawn.",
        CC_CALLBACK_2(Console::commandDirectorSubCommandStop, this)});
    addSubCommand("director", {"start",  "Restart the animation again, Call this function only if [director stop] was called earlier",
        CC_CALLBACK_2(Console::commandDirectorSubCommandStart, this)});
    addSubCommand("director", {"end",    "exit this app.",
        CC_CALLBACK_2(Console::commandDirectorSubCommandEnd, this)});
}

void Console::createCommandExit()
{
    addCommand({"exit", "Close connection to the console. Args: [-h | help | ]", CC_CALLBACK_2(Console::commandExit, this)});
}

void Console::createCommandFileUtils()
{
    addCommand({"fileutils", "Flush or print the FileUtils info. Args: [-h | help | flush | ]",
        CC_CALLBACK_2(Console::commandFileUtils, this)});
    addSubCommand("fileutils", {"flush", "Purges the file searching cache.",
        CC_CALLBACK_2(Console::commandFileUtilsSubCommandFlush, this)});
}

void Console::createCommandFps()
{
    addCommand({"fps", "Turn on / off the FPS. Args: [-h | help | on | off | ]", CC_CALLBACK_2(Console::commandFps, this)});
    addSubCommand("fps", {"on", "Display the FPS on the bottom-left corner.", CC_CALLBACK_2(Console::commandFpsSubCommandOnOff, this)});
    addSubCommand("fps", {"off", "Hide the FPS on the bottom-left corner.", CC_CALLBACK_2(Console::commandFpsSubCommandOnOff, this)});
}

void Console::createCommandHelp()
{
    addCommand({"help", "Print this message. Args: [ ]", CC_CALLBACK_2(Console::commandHelp, this)});
}

void Console::createCommandProjection()
{
    addCommand({"projection", "Change or print the current projection. Args: [-h | help | 2d | 3d | ]",
        CC_CALLBACK_2(Console::commandProjection, this)});
    addSubCommand("projection", {"2d", "sets a 2D projection (orthogonal projection).",
        CC_CALLBACK_2(Console::commandProjectionSubCommand2d, this)});
    addSubCommand("projection", {"3d", "sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.",
        CC_CALLBACK_2(Console::commandProjectionSubCommand3d, this)});
}

void Console::createCommandResolution()
{
    addCommand({"resolution", "Change or print the window resolution. Args: [-h | help | width height resolution_policy | ]",
        CC_CALLBACK_2(Console::commandResolution, this)});
    addSubCommand("resolution", {"", "", CC_CALLBACK_2(Console::commandResolutionSubCommandEmpty, this)});
}

void Console::createCommandSceneGraph()
{
    addCommand({"scenegraph", "Print the scene graph", CC_CALLBACK_2(Console::commandSceneGraph, this)});
}

void Console::createCommandTexture()
{
    addCommand({"texture", "Flush or print the TextureCache info. Args: [-h | help | flush | ] ",
        CC_CALLBACK_2(Console::commandTextures, this)});
    addSubCommand("texture", {"flush", "Purges the dictionary of loaded textures.",
        CC_CALLBACK_2(Console::commandTexturesSubCommandFlush, this)});
}

void Console::createCommandTouch()
{
    addCommand({"touch", "simulate touch event via console, type -h or [touch help] to list supported directives"});
    addSubCommand("touch", {"tap", "touch tap x y: simulate touch tap at (x,y).",
        CC_CALLBACK_2(Console::commandTouchSubCommandTap, this)});
    addSubCommand("touch", {"swipe", "touch swipe x1 y1 x2 y2: simulate touch swipe from (x1,y1) to (x2,y2).",
        CC_CALLBACK_2(Console::commandTouchSubCommandSwipe, this)});
}

void Console::createCommandUpload()
{
    addCommand({"upload", "upload file. Args: [filename base64_encoded_data]", CC_CALLBACK_1(Console::commandUpload, this)});
}

void Console::createCommandVersion()
{
    addCommand({"version", "print version string ", CC_CALLBACK_2(Console::commandVersion, this)});
}

//
// commands
//

void Console::commandAllocator(int fd, const std::string& /*args*/)
{
#if CC_ENABLE_ALLOCATOR_DIAGNOSTICS
    auto info = allocator::AllocatorDiagnostics::instance()->diagnostics();
    Console::Utility::mydprintf(fd, info.c_str());
#else
    Console::Utility::mydprintf(fd, "allocator diagnostics not available. CC_ENABLE_ALLOCATOR_DIAGNOSTICS must be set to 1 in ccConfig.h\n");
#endif
}

void Console::commandConfig(int fd, const std::string& /*args*/)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [=](){
        Console::Utility::mydprintf(fd, "%s", Configuration::getInstance()->getInfo().c_str());
        Console::Utility::sendPrompt(fd);
    });
}

void Console::commandDebugMsg(int fd, const std::string& /*args*/)
{
    Console::Utility::mydprintf(fd, "Debug message is: %s\n", _sendDebugStrings ? "on" : "off");
}

void Console::commandDebugMsgSubCommandOnOff(int /*fd*/, const std::string& args)
{
    _sendDebugStrings = (args.compare("on") == 0);
}

void Console::commandDirectorSubCommandPause(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    Scheduler *sched = director->getScheduler();
    sched->performFunctionInCocosThread( [](){
        Director::getInstance()->pause();
    });
}

void Console::commandDirectorSubCommandResume(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    director->resume();
}

void Console::commandDirectorSubCommandStop(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    Scheduler *sched = director->getScheduler();
    sched->performFunctionInCocosThread( [](){
        Director::getInstance()->stopAnimation();
    });
}

void Console::commandDirectorSubCommandStart(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    director->startAnimation();
}

void Console::commandDirectorSubCommandEnd(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    director->end();
}

void Console::commandExit(int fd, const std::string& /*args*/)
{
    FD_CLR(fd, &_read_set);
    _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    closesocket(fd);
#else
    close(fd);
#endif
}

void Console::commandFileUtils(int fd, const std::string& /*args*/)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&Console::printFileUtils, this, fd) );
}

void Console::commandFileUtilsSubCommandFlush(int /*fd*/, const std::string& /*args*/)
{
    FileUtils::getInstance()->purgeCachedEntries();
}

void Console::commandFps(int fd, const std::string& /*args*/)
{
    Console::Utility::mydprintf(fd, "FPS is: %s\n", Director::getInstance()->isDisplayStats() ? "on" : "off");
}

void Console::commandFpsSubCommandOnOff(int /*fd*/, const std::string& args)
{
    bool state = (args.compare("on") == 0);
    Director *dir = Director::getInstance();
    Scheduler *sched = dir->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&Director::setDisplayStats, dir, state));
}

void Console::commandHelp(int fd, const std::string& /*args*/)
{
    sendHelp(fd, _commands, "\nAvailable commands:\n");
}

void Console::commandProjection(int fd, const std::string& /*args*/)
{
    auto director = Director::getInstance();
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
    Console::Utility::mydprintf(fd, "Current projection: %s\n", buf);
}

void Console::commandProjectionSubCommand2d(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    Scheduler *sched = director->getScheduler();
    sched->performFunctionInCocosThread( [=](){
        director->setProjection(Director::Projection::_2D);
    } );
}

void Console::commandProjectionSubCommand3d(int /*fd*/, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    Scheduler *sched = director->getScheduler();
    sched->performFunctionInCocosThread( [=](){
        director->setProjection(Director::Projection::_3D);
    } );
}

void Console::commandResolution(int /*fd*/, const std::string& args)
{
    int width, height, policy;
    
    std::istringstream stream( args );
    stream >> width >> height>> policy;
    
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [=](){
        Director::getInstance()->getOpenGLView()->setDesignResolutionSize(width, height, static_cast<ResolutionPolicy>(policy));
    } );
}

void Console::commandResolutionSubCommandEmpty(int fd, const std::string& /*args*/)
{
    auto director = Director::getInstance();
    Size points = director->getWinSize();
    Size pixels = director->getWinSizeInPixels();
    auto glview = director->getOpenGLView();
    Size design = glview->getDesignResolutionSize();
    ResolutionPolicy res = glview->getResolutionPolicy();
    Rect visibleRect = glview->getVisibleRect();
    
    Console::Utility::mydprintf(fd, "Window Size:\n"
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
}

void Console::commandSceneGraph(int fd, const std::string& /*args*/)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( std::bind(&Console::printSceneGraphBoot, this, fd) );
}

void Console::commandTextures(int fd, const std::string& /*args*/)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [=](){
        Console::Utility::mydprintf(fd, "%s", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
        Console::Utility::sendPrompt(fd);
    });
}

void Console::commandTexturesSubCommandFlush(int /*fd*/, const std::string& /*args*/)
{
    Scheduler *sched = Director::getInstance()->getScheduler();
    sched->performFunctionInCocosThread( [](){
        Director::getInstance()->getTextureCache()->removeAllTextures();
    });
}

void Console::commandTouchSubCommandTap(int fd, const std::string& args)
{
    auto argv = Console::Utility::split(args,' ');
    
    if((argv.size() == 3 ) && (Console::Utility::isFloat(argv[1]) && Console::Utility::isFloat(argv[2])))
    {
        
        float x = utils::atof(argv[1].c_str());
        float y = utils::atof(argv[2].c_str());
        
        std::srand ((unsigned)time(nullptr));
        _touchId = rand();
        Scheduler *sched = Director::getInstance()->getScheduler();
        sched->performFunctionInCocosThread( [&](){
            Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &_touchId, &x, &y);
            Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &_touchId, &x, &y);
        });
    }
    else
    {
        const char msg[] = "touch: invalid arguments.\n";
        Console::Utility::sendToConsole(fd, msg, strlen(msg));
    }
}

void Console::commandTouchSubCommandSwipe(int fd, const std::string& args)
{
    auto argv = Console::Utility::split(args,' ');
    
    if((argv.size() == 5)
       && (Console::Utility::isFloat(argv[1])) && (Console::Utility::isFloat(argv[2]))
       && (Console::Utility::isFloat(argv[3])) && (Console::Utility::isFloat(argv[4])))
    {
        
        float x1 = utils::atof(argv[1].c_str());
        float y1 = utils::atof(argv[2].c_str());
        float x2 = utils::atof(argv[3].c_str());
        float y2 = utils::atof(argv[4].c_str());
        
        std::srand ((unsigned)time(nullptr));
        _touchId = rand();
        
        Scheduler *sched = Director::getInstance()->getScheduler();
        sched->performFunctionInCocosThread( [=](){
            float tempx = x1, tempy = y1;
            Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &_touchId, &tempx, &tempy);
        });
        
        float dx = std::abs(x1 - x2);
        float dy = std::abs(y1 - y2);
        float _x_ = x1, _y_ = y1;
        if(dx > dy)
        {
            while(dx > 1)
            {
                
                if(x1 < x2)
                {
                    _x_ += 1;
                }
                if(x1 > x2)
                {
                    _x_ -= 1;
                }
                if(y1 < y2)
                {
                    _y_ += dy/dx;
                }
                if(y1 > y2)
                {
                    _y_ -= dy/dx;
                }
                sched->performFunctionInCocosThread( [=](){
                    float tempx = _x_, tempy = _y_;
                    Director::getInstance()->getOpenGLView()->handleTouchesMove(1, &_touchId, &tempx, &tempy);
                });
                dx -= 1;
            }
            
        }
        else
        {
            while(dy > 1)
            {
                if(x1 < x2)
                {
                    _x_ += dx/dy;
                }
                if(x1 > x2)
                {
                    _x_ -= dx/dy;
                }
                if(y1 < y2)
                {
                    _y_ += 1;
                }
                if(y1 > y2)
                {
                    _y_ -= 1;
                }
                sched->performFunctionInCocosThread( [=](){
                    float tempx = _x_, tempy = _y_;
                    Director::getInstance()->getOpenGLView()->handleTouchesMove(1, &_touchId, &tempx, &tempy);
                });
                dy -= 1;
            }
            
        }
        
        sched->performFunctionInCocosThread( [=](){
            float tempx = x2, tempy = y2;
            Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &_touchId, &tempx, &tempy);
        });
        
    }
    else
    {
        const char msg[] = "touch: invalid arguments.\n";
        Console::Utility::sendToConsole(fd, msg, strlen(msg));
    }
}

static char invalid_filename_char[] = {':', '/', '\\', '?', '%', '*', '<', '>', '"', '|', '\r', '\n', '\t'};

void Console::commandUpload(int fd)
{
    ssize_t n, rc;
    char buf[512] = {0};
    char c = 0;
    char *ptr = buf;
    //read file name
    for( n = 0; n < sizeof(buf) - 1; n++ )
    {
        if( (rc = recv(fd, &c, 1, 0)) == 1 )
        {
            for(char x : invalid_filename_char)
            {
                if (c == x)
                {
                    const char err[] = "upload: invalid file name!\n";
                    Console::Utility::sendToConsole(fd, err, strlen(err));
                    return;
                }
            }
            if (c == ' ')
            {
                break;
            }
            *ptr++ = c;
        } 
        else if( rc == 0 ) 
        {
            break;
        } 
        else if( errno == EINTR ) 
        {
            continue;
        } 
        else 
        {
            break;
        }
    }
    *ptr = 0;

    static std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string filepath = writablePath + std::string(buf);

    FILE* fp = fopen(FileUtils::getInstance()->getSuitableFOpen(filepath).c_str(), "wb");
    if(!fp)
    {
        const char err[] = "can't create file!\n";
        Console::Utility::sendToConsole(fd, err, strlen(err));
        return;
    }

    while (true)
    {
        char data[4];
        for(int i = 0; i < 4; i++)
        {
            data[i] = '=';
        }
        bool more_data;
        readBytes(fd, data, 4, &more_data);
        if(!more_data)
        {
            break;
        }
        unsigned char *decode;
        unsigned char *in = (unsigned char *)data;
        int dt = base64Decode(in, 4, &decode);
        if (dt > 0)
        {
            fwrite(decode, dt, 1, fp);
        }
        free(decode);
    }
    fclose(fp);
}

void Console::commandVersion(int fd, const std::string& /*args*/)
{
    Console::Utility::mydprintf(fd, "%s\n", cocos2dVersion());
}

// helper free functions

int Console::printSceneGraph(int fd, Node* node, int level)
{
    int total = 1;
    for(int i=0; i<level; ++i)
        Console::Utility::sendToConsole(fd, "-", 1);
    
    Console::Utility::mydprintf(fd, " %s\n", node->getDescription().c_str());
    
    for(const auto& child: node->getChildren())
        total += printSceneGraph(fd, child, level+1);
    
    return total;
}

void Console::printSceneGraphBoot(int fd)
{
    Console::Utility::sendToConsole(fd,"\n",1);
    auto scene = Director::getInstance()->getRunningScene();
    int total = printSceneGraph(fd, scene, 0);
    Console::Utility::mydprintf(fd, "Total Nodes: %d\n", total);
    Console::Utility::sendPrompt(fd);
}

void Console::printFileUtils(int fd)
{
    FileUtils* fu = FileUtils::getInstance();
    
    Console::Utility::mydprintf(fd, "\nSearch Paths:\n");
    auto& list = fu->getSearchPaths();
    for( const auto &item : list) {
        Console::Utility::mydprintf(fd, "%s\n", item.c_str());
    }
    
    Console::Utility::mydprintf(fd, "\nResolution Order:\n");
    auto& list1 = fu->getSearchResolutionsOrder();
    for( const auto &item : list1) {
        Console::Utility::mydprintf(fd, "%s\n", item.c_str());
    }
    
    Console::Utility::mydprintf(fd, "\nWritable Path:\n");
    Console::Utility::mydprintf(fd, "%s\n", fu->getWritablePath().c_str());
    
    Console::Utility::mydprintf(fd, "\nFull Path Cache:\n");
    auto& cache = fu->getFullPathCache();
    for( const auto &item : cache) {
        Console::Utility::mydprintf(fd, "%s -> %s\n", item.first.c_str(), item.second.c_str());
    }
    Console::Utility::sendPrompt(fd);
}

void Console::sendHelp(int fd, const std::map<std::string, Command>& commands, const char* msg)
{
    Console::Utility::sendToConsole(fd, msg, strlen(msg));
    for(auto& it : commands)
    {
        auto command = it.second;
        if (command.help.empty()) continue;
        
        Console::Utility::mydprintf(fd, "\t%s", command.name.c_str());
        ssize_t tabs = strlen(command.name.c_str()) / 8;
        tabs = 3 - tabs;
        for(int j=0;j<tabs;j++){
            Console::Utility::mydprintf(fd, "\t");
        }
        Console::Utility::mydprintf(fd,"%s\n", command.help.c_str());
    }
}

NS_CC_END
