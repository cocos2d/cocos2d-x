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


#ifndef __CCCONSOLE_H__
#define __CCCONSOLE_H__

#if defined(_MSC_VER) || defined(__MINGW32__)
#include <BaseTsd.h>
#include <WinSock2.h>

#ifndef __SSIZE_T
#define __SSIZE_T
typedef SSIZE_T ssize_t;
#endif // __SSIZE_T

#else
#include <sys/select.h>
#endif

#include <thread>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <mutex>
#include <stdarg.h>

#include "base/ccMacros.h"
#include "base/CCPlatformMacros.h"


NS_CC_BEGIN

/// CCLog 信息的最大长度
static const int MAX_LOG_LENGTH = 16*1024;

/**
 @brief 输出调试信息.
 */
void CC_DLL log(const char * format, ...) CC_FORMAT_PRINTF(1, 2);

/** 
 Console 是一个让开发者通过 TCP 连接控制游戏的助手(helper)类.
 Console将产生一个监听特定 TCP 端口的新线程.
 Console有一个基本的命令解析器(token parser).每一条命令都会调用`std::function<void(int)>`.
 如果`std::function<>`需要使用 cocos2d API, 它需要调用
 ```
 scheduler->performFunctionInCocosThread( ... );
 ```
 */

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
class CC_DLL Console
{
public:
    struct Command {
        std::string name;
        std::string help;
        std::function<void(int, const std::string&)> callback;
    };

    /** 构造函数 */
    Console();

    /** 析构函数 */
    virtual ~Console();

    /** 开始监听特定的 TCP 端口 */
    bool listenOnTCP(int port);

    /** 开始监听特定的文件描述符(file descriptor) */
    bool listenOnFileDescriptor(int fd);

    /** 停止Console. 'stop' 也会在析构函数执行时被调用 */
    void stop();

    /** 添加用户自定义的命令 */
    void addCommand(const Command& cmd);
    /** 添加一些日志到Console */
    void log(const char *buf);
 
protected:
    void loop();
    ssize_t readline(int fd, char *buf, size_t maxlen);
    ssize_t readBytes(int fd, char* buffer, size_t maxlen, bool* more);
    bool parseCommand(int fd);
    
    void addClient();

    // 添加命令
    void commandHelp(int fd, const std::string &args);
    void commandExit(int fd, const std::string &args);
    void commandSceneGraph(int fd, const std::string &args);
    void commandFileUtils(int fd, const std::string &args);
    void commandConfig(int fd, const std::string &args);
    void commandTextures(int fd, const std::string &args);
    void commandResolution(int fd, const std::string &args);
    void commandProjection(int fd, const std::string &args);
    void commandDirector(int fd, const std::string &args);
    void commandTouch(int fd, const std::string &args);
    void commandUpload(int fd);
    // 文件描述符(file descriptor): 套接字(socket), 控制台(console)等.
    int _listenfd;
    int _maxfd;
    std::vector<int> _fds;
    std::thread _thread;

    fd_set _read_set;

    bool _running;
    bool _endThread;

    std::string _writablePath;

    std::map<std::string, Command> _commands;

    // cocos2d 产生并发往远程控制台(console)的字符串.
    bool _sendDebugStrings;
    std::mutex _DebugStringsMutex;
    std::vector<std::string> _DebugStrings;

    intptr_t _touchId;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Console);
};

#endif /* #if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) */
NS_CC_END

#endif /* defined(__CCCONSOLE_H__) */
