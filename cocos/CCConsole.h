//
//  CCConsole.h
//  cocos2d_libs
//
//  Created by Ricardo Quesada on 11/26/13.
//
//

#ifndef __cocos2d_libs__CCConsole__
#define __cocos2d_libs__CCConsole__

#include <thread>
#include <vector>

#include "ccMacros.h"
#include "base/CCObject.h"


NS_CC_BEGIN

class Scheduler;

class CC_DLL Console : public Object
{

public:
    static Console* create();

    bool listenOnTCP(int port);
    bool listenOnStdin();
    bool listenOnFileDescriptor(int fd);

    void cancel();

    int getFileDescriptor() const { return _listenfd; }
    void setFileDescriptor(int fd) { _listenfd = fd; }


protected:
    Console();
    virtual ~Console();

    ssize_t readline(int fd);

    void loop();
    void parseToken();

    // weak ref
    Scheduler *_scheduler;

    // file descriptor: socket, console, etc.
    int _listenfd;
    int _maxfd;
    std::vector<int> _fds;
    std::thread _thread;

    bool _running;
    bool _endThread;

    char _buffer[512];

private:
    CC_DISALLOW_COPY_AND_ASSIGN(Console);
};


NS_CC_END

#endif /* defined(__cocos2d_libs__CCConsole__) */
