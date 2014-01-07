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

#if defined(_MSC_VER)
#include <BaseTsd.h>
//typedef SSIZE_T ssize_t;
// ssize_t was redefined as int in libwebsockets.h.
// Therefore, to avoid conflict, we needs the same definition.
typedef int ssize_t;
#else
#include <sys/select.h>
#endif

#include <thread>
#include <vector>
#include <functional>

#include "ccMacros.h"
#include "CCObject.h"


NS_CC_BEGIN

/** Console is helper class that lets the developer control the game from TCP connection.
 Console will spawn a new thread that will listen to a specified TCP port.
 Console has a basic token parser. Each token is associated with an std::function<void(int)>.
 If the std::function<> needs to use the cocos2d API, it needs to call
 
 ```
 scheduler->performFunctionInCocosThread( ... );
 ```
 */
class CC_DLL Console : public Object
{
public:

    struct Command {
        const char *name;
        std::function<void(int, const char*)> callback;
    };

    /** creates a new instnace of the Console */
    static Console* create();

    /** starts listening to specifed TCP port */
    bool listenOnTCP(int port);

    /** starts listening to specifed file descriptor */
    bool listenOnFileDescriptor(int fd);

    /** cancels the Console. Cancel will be called at destruction time as well */
    void cancel();

    /** sets user tokens */
    void setUserCommands( Command* commands, int numberOfCommands);

protected:
    Console();
    virtual ~Console();

    void loop();

    ssize_t readline(int fd);
    bool parseCommand(int fd);
    void sendPrompt(int fd);
    void addClient();

    // Add commands here
    void commandHelp(int fd, const char *command);
    void commandExit(int fd, const char *command);
    void commandSceneGraph(int fd, const char *command);

    // file descriptor: socket, console, etc.
    int _listenfd;
    int _maxfd;
    std::vector<int> _fds;
    std::thread _thread;

    fd_set _read_set;

    bool _running;
    bool _endThread;

    char _buffer[512];

    struct Command _commands[15];
    int _maxCommands;
    struct Command *_userCommands;
    int _maxUserCommands;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Console);
};


NS_CC_END

#endif /* defined(__CCCONSOLE_H__) */
